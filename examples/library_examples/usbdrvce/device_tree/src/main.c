struct gui;
#define usb_callback_data_t struct gui

struct item;
#define usb_device_data_t struct item

#include <graphx.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tice.h>
#include <usbdrvce.h>

#define CHAR_HEIGHT 8
#define SPACES "        "

enum
{
    background_color,
    text_color,
    selection_color,
    selected_text_color,
    transparent_color,
};

static const uint16_t palette[transparent_color] =
{
    [background_color] = 0xFFFF,
    [text_color] = 0x0000,
    [selection_color] = 0x8D53,
    [selected_text_color] = 0xFFFF,
};

struct gui
{
    bool dirty;
    usb_device_t first_device;
    usb_device_t selected_device;
    int selected_y;
};

struct item
{
    struct gui *gui;
    uint8_t depth;
    bool collapsed;
    usb_control_setup_t setup;
    usb_device_descriptor_t device_descriptor;
    uint16_t langid;
    char manufacturer[0x80];
    char product[0x80];
    char serial_number[0x80];
    union
    {
        usb_string_descriptor_t string_descriptor;
        usb_configuration_descriptor_t configuration_descriptor;
        uint8_t buffer[0xFF];
    };
};

void outchar(char c)
{
    int x = gfx_GetTextX(), y = gfx_GetTextY(), width;
    if (c == '\n')
    {
        if (y >= 0 && y + CHAR_HEIGHT <= LCD_HEIGHT &&
            x >= 0 && x < LCD_WIDTH)
        {
            gfx_FillRectangle_NoClip(x, y, LCD_WIDTH - x, CHAR_HEIGHT);
        }
        gfx_SetTextXY(0, y + CHAR_HEIGHT);
        return;
    }
    if (c < ' ' || c > '~')
    {
        return;
    }
    width = gfx_GetCharWidth(c);
    if (y >= 0 && y + CHAR_HEIGHT <= LCD_HEIGHT &&
        x >= 0 && x + width <= LCD_WIDTH)
    {
        gfx_PrintChar(c);
        return;
    }
    if (y <= -CHAR_HEIGHT || y >= LCD_HEIGHT ||
        x <= -width || x >= LCD_WIDTH)
    {
        gfx_SetTextConfig(gfx_text_clip);
        gfx_PrintChar(c);
        gfx_SetTextConfig(gfx_text_noclip);
    }
}

static void set_colors(uint8_t bg, uint8_t fg)
{
    gfx_SetColor(bg);
    gfx_SetTextBGColor(bg);
    gfx_SetTextFGColor(fg);
}

static void set_device(usb_device_t *variable, usb_device_t value)
{
    usb_UnrefDevice(*variable);
    *variable = usb_RefDevice(value);
}

static void move_device(usb_device_t *variable, usb_device_t *value)
{
    usb_UnrefDevice(*variable);
    *variable = *value;
    *value = NULL;
}

static bool move_to_next_device(usb_device_t *device)
{
    usb_device_t next = NULL;
    struct item *item = usb_GetDeviceData(*device);
    usb_find_device_flags_t flags = USB_SKIP_DISABLED;
    if (item != NULL && item->collapsed)
    {
        flags |= USB_SKIP_ATTACHED;
    }
    set_device(&next, usb_FindDevice(NULL, *device, flags));
    if (next == NULL)
    {
        return false;
    }
    move_device(device, &next);
    return true;
}

static bool move_to_previous_device(usb_device_t *device)
{
    usb_device_t previous = NULL, current = NULL;
    set_device(&current, usb_RootHub());
    do
    {
        set_device(&previous, current);
        if (!move_to_next_device(&current))
        {
            return false;
        }
    }
    while (current != *device);
    move_device(device, &previous);
    set_device(&current, NULL);
    return true;
}

static void move_to_nearby_device(usb_device_t *device)
{
    if (!move_to_next_device(device) && !move_to_previous_device(device))
    {
        set_device(device, usb_RootHub());
    }
}

static void gui_draw(struct gui *gui)
{
    int y = 0;
    usb_device_t device = NULL;

    if (!gui->dirty)
    {
        return;
    }

    gfx_SetTextXY(0, y);
    set_colors(background_color, text_color);

    set_device(&device, gui->first_device);

    do
    {
        bool is_hub = usb_GetDeviceFlags(device) & USB_IS_HUB;
        struct item *item = usb_GetDeviceData(device);
        if (item == NULL)
        {
            continue;
        }

        if (device == gui->selected_device)
        {
            gui->selected_y = y;
            set_colors(selection_color, selected_text_color);
        }

        printf("%.*s%c%04X:%04X %s %s %s\n",
               item->depth, SPACES,
               is_hub ? item->collapsed ? '+' : '-' : '=',
               item->device_descriptor.idVendor,
               item->device_descriptor.idProduct,
               item->manufacturer,
               item->product,
               item->serial_number);

        if (device == gui->selected_device)
        {
            set_colors(background_color, text_color);
        }

        y = gfx_GetTextY();
    }
    while (y + CHAR_HEIGHT <= LCD_HEIGHT && move_to_next_device(&device));

    set_device(&device, NULL);

    if (y >= 0 && y < LCD_HEIGHT)
    {
        gfx_FillRectangle_NoClip(0, y, LCD_WIDTH, LCD_HEIGHT - y);
    }

    gfx_SwapDraw();
    gui->dirty = false;
}

static struct item *create_item(struct gui *gui, usb_device_t device)
{
    struct item *parent = usb_GetDeviceData(usb_GetDeviceHub(device));
    struct item *item = malloc(sizeof(struct item));
    if (item == NULL)
    {
        return NULL;
    }
    item->gui = gui;
    item->depth = parent ? parent->depth + 1 : 0;
    item->collapsed = false;
    item->device_descriptor.bLength = 0;
    item->device_descriptor.bDescriptorType = 0;
    item->device_descriptor.idVendor = 0;
    item->device_descriptor.idProduct = 0;
    item->langid = 0;
    strcpy(item->manufacturer, "Unknown");
    strcpy(item->product, "Unknown");
    strcpy(item->serial_number, "Unknown");
    item->string_descriptor.bLength = 0;
    item->string_descriptor.bDescriptorType = 0;
    return item;
}

static void usb_string_descriptor_to_ascii(const usb_string_descriptor_t *string, char *ascii)
{
    uint8_t index = 0, length = string->bLength;
    while (length >= 4)
    {
        wchar_t wc = string->bString[index++];
        if (wc == L'\0')
        {
            break;
        }
        if (wc < ' ' || wc > '~')
        {
            wc = '?';
        }
        *ascii++ = wc;
        length -= 2;
    }
    *ascii = '\0';
    return;
}

static usb_error_t get_configuration_descriptor_handler(usb_endpoint_t endpoint,
                                                        usb_transfer_status_t status,
                                                        size_t transferred, usb_transfer_data_t *data)
{
    usb_device_t device = usb_GetEndpointDevice(endpoint);
    struct item *item = usb_GetDeviceData(device);
    const usb_configuration_descriptor_t *configuration_descriptor = data;
    if (item && item->gui)
    {
        item->gui->dirty = true;
    }
    if (item == NULL || configuration_descriptor == NULL || status != USB_TRANSFER_COMPLETED ||
        transferred != item->configuration_descriptor.wTotalLength ||
        configuration_descriptor->bLength < sizeof(usb_configuration_descriptor_t) ||
        configuration_descriptor->wTotalLength != item->configuration_descriptor.wTotalLength)
    {
        return USB_SUCCESS;
    }

    return usb_SetConfiguration(device,
                                configuration_descriptor, item->configuration_descriptor.wTotalLength);
}

static usb_error_t get_total_length_handler(usb_endpoint_t endpoint, usb_transfer_status_t status,
                                            size_t transferred, usb_transfer_data_t *data)
{
    usb_device_t device = usb_GetEndpointDevice(endpoint);
    struct item *item = usb_GetDeviceData(device);
    usb_configuration_descriptor_t *configuration_descriptor;
    (void)data;
    if (item == NULL || status != USB_TRANSFER_COMPLETED ||
        transferred != 4 ||
        item->configuration_descriptor.bLength < transferred ||
        item->configuration_descriptor.bDescriptorType != USB_CONFIGURATION_DESCRIPTOR)
    {
        if (item && item->gui)
        {
             item->gui->dirty = true;
        }
        return USB_SUCCESS;
    }

    configuration_descriptor = malloc(item->configuration_descriptor.wTotalLength);
    if (configuration_descriptor == NULL)
    {
        if (item && item->gui)
        {
             item->gui->dirty = true;
        }
        return USB_SUCCESS;
    }
    item->setup.bmRequestType = USB_DEVICE_TO_HOST | USB_STANDARD_REQUEST | USB_RECIPIENT_DEVICE;
    item->setup.bRequest = USB_GET_DESCRIPTOR_REQUEST;
    item->setup.wValue = USB_CONFIGURATION_DESCRIPTOR << 8;
    item->setup.wIndex = 0;
    item->setup.wLength = item->configuration_descriptor.wTotalLength;
    return usb_ScheduleControlTransfer(endpoint, &item->setup, configuration_descriptor,
                                       &get_configuration_descriptor_handler, configuration_descriptor);
}

static usb_error_t get_serial_number_handler(usb_endpoint_t endpoint, usb_transfer_status_t status,
                                             size_t transferred, usb_transfer_data_t *data)
{
    usb_device_t device = usb_GetEndpointDevice(endpoint);
    struct item *item = usb_GetDeviceData(device);
    if (item == NULL || status != USB_TRANSFER_COMPLETED ||
        transferred < 2 || transferred > sizeof(item->buffer) ||
        item->string_descriptor.bLength < 2 || item->string_descriptor.bLength > transferred ||
        item->string_descriptor.bDescriptorType != USB_STRING_DESCRIPTOR)
    {
        if (item && item->gui)
        {
             item->gui->dirty = true;
        }
        return USB_SUCCESS;
    }
    usb_string_descriptor_to_ascii(&item->string_descriptor, item->serial_number);

    item->setup.bmRequestType = USB_DEVICE_TO_HOST | USB_STANDARD_REQUEST | USB_RECIPIENT_DEVICE;
    item->setup.bRequest = USB_GET_DESCRIPTOR_REQUEST;
    item->setup.wValue = USB_CONFIGURATION_DESCRIPTOR << 8;
    item->setup.wIndex = 0;
    item->setup.wLength = 4;
    return usb_ScheduleControlTransfer(endpoint, &item->setup, &item->configuration_descriptor,
                                       &get_total_length_handler, data);
}

static usb_error_t get_product_handler(usb_endpoint_t endpoint, usb_transfer_status_t status,
                                       size_t transferred, usb_transfer_data_t *data)
{
    usb_device_t device = usb_GetEndpointDevice(endpoint);
    struct item *item = usb_GetDeviceData(device);
    if (item == NULL || status != USB_TRANSFER_COMPLETED ||
        transferred < 2 || transferred > sizeof(item->buffer) ||
        item->string_descriptor.bLength < 2 || item->string_descriptor.bLength > transferred ||
        item->string_descriptor.bDescriptorType != USB_STRING_DESCRIPTOR)
    {
        if (item && item->gui)
        {
             item->gui->dirty = true;
        }
        return USB_SUCCESS;
    }
    usb_string_descriptor_to_ascii(&item->string_descriptor, item->product);

    if (item->device_descriptor.iSerialNumber == 0)
    {
        item->string_descriptor.bLength = sizeof(L"N/A");
        item->string_descriptor.bDescriptorType = USB_STRING_DESCRIPTOR;
        memcpy(item->string_descriptor.bString, L"N/A", sizeof(L"N/A") - sizeof(L'\0'));
        return get_serial_number_handler(endpoint, status, item->string_descriptor.bLength, data);
    }
    item->setup.bmRequestType = USB_DEVICE_TO_HOST | USB_STANDARD_REQUEST | USB_RECIPIENT_DEVICE;
    item->setup.bRequest = USB_GET_DESCRIPTOR_REQUEST;
    item->setup.wValue = USB_STRING_DESCRIPTOR << 8 | item->device_descriptor.iSerialNumber;
    item->setup.wIndex = item->langid;
    item->setup.wLength = sizeof(item->buffer);
    return usb_ScheduleControlTransfer(endpoint, &item->setup, &item->string_descriptor,
                                       &get_serial_number_handler, data);
}

static usb_error_t get_manufacturer_handler(usb_endpoint_t endpoint, usb_transfer_status_t status,
                                            size_t transferred, usb_transfer_data_t *data)
{
    usb_device_t device = usb_GetEndpointDevice(endpoint);
    struct item *item = usb_GetDeviceData(device);
    if (item == NULL || status != USB_TRANSFER_COMPLETED ||
        transferred < 2 || transferred > sizeof(item->buffer) ||
        item->string_descriptor.bLength < 2 || item->string_descriptor.bLength > transferred ||
        item->string_descriptor.bDescriptorType != USB_STRING_DESCRIPTOR)
    {
        if (item && item->gui)
        {
             item->gui->dirty = true;
        }
        return USB_SUCCESS;
    }
    usb_string_descriptor_to_ascii(&item->string_descriptor, item->manufacturer);

    if (item->device_descriptor.iProduct == 0)
    {
        item->string_descriptor.bLength = sizeof(L"N/A");
        item->string_descriptor.bDescriptorType = USB_STRING_DESCRIPTOR;
        memcpy(item->string_descriptor.bString, L"N/A", sizeof(L"N/A") - sizeof(L'\0'));
        return get_product_handler(endpoint, status, item->string_descriptor.bLength, data);
    }
    item->setup.bmRequestType = USB_DEVICE_TO_HOST | USB_STANDARD_REQUEST | USB_RECIPIENT_DEVICE;
    item->setup.bRequest = USB_GET_DESCRIPTOR_REQUEST;
    item->setup.wValue = USB_STRING_DESCRIPTOR << 8 | item->device_descriptor.iProduct;
    item->setup.wIndex = item->langid;
    item->setup.wLength = sizeof(item->buffer);
    return usb_ScheduleControlTransfer(endpoint, &item->setup, &item->string_descriptor,
                                       &get_product_handler, data);
}

static usb_error_t get_langid_handler(usb_endpoint_t endpoint, usb_transfer_status_t status,
                                      size_t transferred, usb_transfer_data_t *data)
{
    usb_device_t device = usb_GetEndpointDevice(endpoint);
    struct item *item = usb_GetDeviceData(device);
    if (status & USB_TRANSFER_STALLED)
    {
        status &= ~(USB_TRANSFER_FAILED | USB_TRANSFER_STALLED);
        transferred = 4;
        item->string_descriptor.bLength = 4;
        item->string_descriptor.bDescriptorType = USB_STRING_DESCRIPTOR;
        item->string_descriptor.bString[0] = 0x0409;
    }
    if (item == NULL || status != USB_TRANSFER_COMPLETED ||
        transferred != 4 ||
        item->string_descriptor.bLength < transferred ||
        item->string_descriptor.bDescriptorType != USB_STRING_DESCRIPTOR)
    {
        if (item && item->gui)
        {
             item->gui->dirty = true;
        }
        return USB_SUCCESS;
    }
    item->langid = item->string_descriptor.bString[0];

    if (item->device_descriptor.iManufacturer == 0)
    {
        item->string_descriptor.bLength = sizeof(L"N/A");
        item->string_descriptor.bDescriptorType = USB_STRING_DESCRIPTOR;
        memcpy(item->string_descriptor.bString, L"N/A", sizeof(L"N/A") - sizeof(L'\0'));
        return get_manufacturer_handler(endpoint, status, item->string_descriptor.bLength, data);
    }
    item->setup.bmRequestType = USB_DEVICE_TO_HOST | USB_STANDARD_REQUEST | USB_RECIPIENT_DEVICE;
    item->setup.bRequest = USB_GET_DESCRIPTOR_REQUEST;
    item->setup.wValue = USB_STRING_DESCRIPTOR << 8 | item->device_descriptor.iManufacturer;
    item->setup.wIndex = item->langid;
    item->setup.wLength = sizeof(item->buffer);
    return usb_ScheduleControlTransfer(endpoint, &item->setup, &item->string_descriptor,
                                       &get_manufacturer_handler, data);
}

static usb_error_t get_device_descriptor_handler(usb_endpoint_t endpoint, usb_transfer_status_t status,
                                                 size_t transferred, usb_transfer_data_t *data)
{
    usb_device_t device = usb_GetEndpointDevice(endpoint);
    struct item *item = usb_GetDeviceData(device);
    if (item == NULL || status != USB_TRANSFER_COMPLETED ||
        transferred != sizeof(usb_device_descriptor_t) ||
        item->device_descriptor.bLength < transferred ||
        item->device_descriptor.bDescriptorType != USB_DEVICE_DESCRIPTOR)
    {
        if (item && item->gui)
        {
             item->gui->dirty = true;
        }
        return USB_SUCCESS;
    }

    item->setup.bmRequestType = USB_DEVICE_TO_HOST | USB_STANDARD_REQUEST | USB_RECIPIENT_DEVICE;
    item->setup.bRequest = USB_GET_DESCRIPTOR_REQUEST;
    item->setup.wValue = USB_STRING_DESCRIPTOR << 8;
    item->setup.wIndex = 0;
    item->setup.wLength = 4;
    return usb_ScheduleControlTransfer(endpoint, &item->setup, &item->string_descriptor,
                                       &get_langid_handler, data);
}

static usb_error_t enabled_handler(usb_device_t device)
{
    struct item *item = usb_GetDeviceData(device);
    if (item == NULL)
    {
        return USB_SUCCESS;
    }
    item->setup.bmRequestType = USB_DEVICE_TO_HOST | USB_STANDARD_REQUEST | USB_RECIPIENT_DEVICE;
    item->setup.bRequest = USB_GET_DESCRIPTOR_REQUEST;
    item->setup.wValue = USB_DEVICE_DESCRIPTOR << 8;
    item->setup.wIndex = 0;
    item->setup.wLength = sizeof(usb_device_descriptor_t);
    return usb_ScheduleDefaultControlTransfer(device, &item->setup,
                                              &item->device_descriptor,
                                              &get_device_descriptor_handler, NULL);
}

static usb_error_t event_handler(usb_event_t event, void *data, struct gui *gui)
{
    usb_error_t error = USB_SUCCESS;
    struct item *item;

    switch (event) {
        default:
            break;
        case USB_DEVICE_DISCONNECTED_EVENT:
            if (gui->first_device == data)
            {
                move_to_nearby_device(&gui->first_device);
            }
            if (gui->selected_device == data)
            {
                move_to_nearby_device(&gui->selected_device);
            }
            item = usb_GetDeviceData(data);
            usb_SetDeviceData(data, NULL);
            free(item);
            gui->dirty = true;
            break;
        case USB_DEVICE_CONNECTED_EVENT:
            usb_SetDeviceData(data, create_item(gui, data));
            if (!(usb_GetRole() & USB_ROLE_DEVICE))
            {
                usb_ResetDevice(data);
            }
            break;
        case USB_DEVICE_ENABLED_EVENT:
            if (error == USB_SUCCESS)
            {
                error = enabled_handler(data);
            }
            break;
    }
    return error;
}

static void event_loop(struct gui *gui)
{
    gui->dirty = true;
    while (true)
    {
        bool is_hub_selected = usb_GetDeviceFlags(gui->selected_device) & USB_IS_HUB;
        struct item *selected_item = usb_GetDeviceData(gui->selected_device);
        switch (os_GetCSC())
        {
            case 0: /* Idle */
                if (usb_HandleEvents() != USB_SUCCESS)
                {
                    return;
                }
                break;
            case sk_Up: /* Move selection up */
                if (gui->selected_device == gui->first_device)
                {
                    move_to_previous_device(&gui->first_device);
                }
                if (!move_to_previous_device(&gui->selected_device))
                {
                    break;
                }
                gui->dirty = true;
                break;
            case sk_Down: /* Move selection down */
                if (!move_to_next_device(&gui->selected_device))
                {
                    break;
                }
                if (gui->selected_y + CHAR_HEIGHT * 2 > LCD_HEIGHT)
                {
                    move_to_next_device(&gui->first_device);
                }
                gui->dirty = true;
                break;
            case sk_Left: /* Collapse current selection */
                if (selected_item == NULL || !is_hub_selected || selected_item->collapsed)
                {
                    break;
                }
                selected_item->collapsed = true;
                gui->dirty = true;
                break;
            case sk_Right: /* Expand current selection */
                if (selected_item == NULL || !is_hub_selected || !selected_item->collapsed)
                {
                    break;
                }
                selected_item->collapsed = false;
                gui->dirty = true;
                break;
            case sk_2nd:
            case sk_Enter: /* Toggle collapsed state */
                if (selected_item == NULL || !is_hub_selected)
                {
                    break;
                }
                selected_item->collapsed = !selected_item->collapsed;
                gui->dirty = true;
                break;
            case sk_Clear: /* Exit */
                return;
        }
        gui_draw(gui);
    }
}

int main()
{
    /* Initialize gui */
    static struct gui gui;
    struct item *root_item = create_item(&gui, usb_RootHub());
    set_device(&gui.first_device, usb_RootHub());
    set_device(&gui.selected_device, usb_RootHub());
    strcpy(root_item->manufacturer, "TI");
    strcpy(root_item->product, "Root Hub");
    strcpy(root_item->serial_number, "N/A");

    /* Initialize usb */
    usb_Init(&event_handler, &gui, NULL, USB_DEFAULT_INIT_FLAGS);
    usb_SetDeviceData(usb_RootHub(), root_item);

    /* Initialize graphics drawing */
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetPalette(palette, sizeof(palette), 0);
    gfx_SetTransparentColor(transparent_color);
    gfx_SetTextTransparentColor(transparent_color);

    /* Main loop */
    event_loop(&gui);

    /* End graphics drawing */
    gfx_End();

    /* Cleanup usb */
    usb_Cleanup();
    free(root_item);

    return 0;
}
