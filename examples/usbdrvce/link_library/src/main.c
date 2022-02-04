#include "linklib.h"

#include <string.h>

#include <graphx.h>
#include <tice.h>

#define CHAR_HEIGHT 8

struct textarea {
    gfx_region_t window;
    int x, y;
};

static void scroll(struct textarea *area) {
    area->x = 0;
    if (area->y + CHAR_HEIGHT < area->window.ymax - area->window.ymin) {
        area->y += CHAR_HEIGHT;
        return;
    }
    for (int y = area->window.ymin; y < area->window.ymax - CHAR_HEIGHT; ++y)
        memmove(&gfx_vbuffer[y][area->window.xmin],
                &gfx_vbuffer[y + CHAR_HEIGHT][area->window.xmin],
                area->window.xmax - area->window.xmin);
    for (int y = area->window.ymax - CHAR_HEIGHT; y < area->window.ymax; ++y)
        memset(&gfx_vbuffer[y][area->window.xmin], 0xFF,
               area->window.xmax - area->window.xmin);
}

static void printc(struct textarea *area, char c) {
    switch (c) {
        default: break;
        case '\r': if (!area->x) return; __attribute__((fallthrough));
        case '\n': scroll(area); return;
    }
    int width = gfx_GetCharWidth(c);
    if (area->x + width >= area->window.xmax - area->window.xmin)
        scroll(area);
    gfx_SetTextXY(area->window.xmin + area->x, area->window.ymin + area->y);
    gfx_PrintChar(c);
    area->x += width;
}

static void prints(struct textarea *area, const char *s) {
    while (*s)
        printc(area, *s++);
}

static void printsz(struct textarea *area, const char *s, size_t z) {
    while (z--)
        printc(area, *s++);
}

static const char map[] = {
    [sk_Mode  ] = '\e',
    [sk_Clear ] = '\r',
    [sk_Math  ] = 'A',
    [sk_Apps  ] = 'B',
    [sk_Prgm  ] = 'C',
    [sk_Recip ] = 'D',
    [sk_Sin   ] = 'E',
    [sk_Cos   ] = 'F',
    [sk_Tan   ] = 'G',
    [sk_Power ] = 'H',
    [sk_Square] = 'I',
    [sk_Comma ] = 'J',
    [sk_LParen] = 'K',
    [sk_RParen] = 'L',
    [sk_Div   ] = 'M',
    [sk_Log   ] = 'N',
    [sk_7     ] = 'O',
    [sk_8     ] = 'P',
    [sk_9     ] = 'Q',
    [sk_Mul   ] = 'R',
    [sk_Ln    ] = 'S',
    [sk_4     ] = 'T',
    [sk_5     ] = 'U',
    [sk_6     ] = 'V',
    [sk_Sub   ] = 'W',
    [sk_Store ] = 'X',
    [sk_1     ] = 'Y',
    [sk_2     ] = 'Z',
    [sk_Add   ] = '"',
    [sk_0     ] = ' ',
    [sk_DecPnt] = ':',
    [sk_Chs   ] = '?',
    [sk_Enter ] = '\n',
};

int main() {
    gfx_Begin();

    static struct textarea output = {
        .window = {
            .xmin = 0,
            .ymin = 0,
            .xmax = LCD_WIDTH,
            .ymax = LCD_HEIGHT - CHAR_HEIGHT,
        },
        .x = 0,
        .y = 0,
    }, input = {
        .window = {
            .xmin = 0,
            .ymin = LCD_HEIGHT - CHAR_HEIGHT,
            .xmax = LCD_WIDTH,
            .ymax = LCD_HEIGHT,
        },
        .x = 0,
        .y = 0,
    };

    bool connected = false;
    uint8_t write_index = 0;
    size_t read_size = 0, write_size = 0;
    char read_buffer[64], write_buffer[64];

    while (true) {
        link_devices_t *devices = (link_devices_t *)link_Devices();
        if (devices->count && !connected)
            prints(&output, "\rConnected!\n");
        else if (!devices->count && connected)
            prints(&output, "\rDisconnected!\n");
        connected = devices->count;
        if (read_size != LINK_PENDING) {
            printsz(&output, read_buffer, read_size);
            read_size = 0;
            if (devices->count) {
                read_size = sizeof(read_buffer);
                link_QueueRead(devices->ids[0], read_buffer, &read_size);
            }
        }
        if (write_size != LINK_PENDING) {
            write_index -= write_size;
            memmove(&write_buffer[0], &write_buffer[write_size], write_index);
            write_size = 0;
            if (devices->count && write_index) {
                write_size = write_index;
                link_QueueWrite(devices->ids[0], write_buffer, &write_size);
            }
        }

        sk_key_t key = os_GetCSC();
        char command = key < sizeof(map) / sizeof(*map) ? map[key] : '\0';
        switch (command) {
            case '\0':
                break;
            case '\e':
                gfx_End();
                return 0;
            default:
                if (write_index == sizeof(write_buffer))
                    break;
                write_buffer[write_index++] = command;
                printc(&input, command);
                break;
        }
    }
}
