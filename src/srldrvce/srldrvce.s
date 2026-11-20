;-------------------------------------------------------------------------------
.include "library.inc"
;-------------------------------------------------------------------------------

library SRLDRVCE, 0

; Imports are emitted in the order of their export slots.
.set import_usb_RefDevice, 1
.set import_usb_UnrefDevice, 1
.set import_usb_GetDeviceFlags, 1
.set import_usb_FindDevice, 1
.set import_usb_GetConfigurationDescriptorTotalLength, 1
.set import_usb_GetDescriptor, 1
.set import_usb_GetConfiguration, 1
.set import_usb_SetConfiguration, 1
.set import_usb_GetDeviceEndpoint, 1
.set import_usb_GetRole, 1
.set import_usb_ControlTransfer, 1
.set import_usb_ScheduleControlTransfer, 1
.set import_usb_ScheduleTransfer, 1
.include "usbdrvce-exports.inc"
lib_dependency USBDRVCE, USBDRVCE_VERSION
usbdrvce_exports lib_import

;-------------------------------------------------------------------------------
; v0 functions (not final, subject to change!)
;-------------------------------------------------------------------------------
	lib_export srl_Open
	lib_export srl_Close
	lib_export srl_Read
	lib_export srl_Write
	lib_export srl_GetCDCStandardDescriptors
	lib_export srl_UsbEventCallback
;-------------------------------------------------------------------------------
.macro compare_hl_zero
	add	hl, de
	or	a, a
	sbc	hl, de
.endm

.macro compare_hl_de
	or	a, a
	sbc	hl, de
	add	hl, de
.endm

;-------------------------------------------------------------------------------
; memory structures
;-------------------------------------------------------------------------------

.struct 0
ring_buf_ctrl:
ring_buf_ctrl.buf_start:	.space 3
ring_buf_ctrl.buf_end:	.space 3
ring_buf_ctrl.data_start:	.space 3
ring_buf_ctrl.data_break:	.space 3
ring_buf_ctrl.data_end:	.space 3
ring_buf_ctrl.dma_active:	.space 1
.equ ring_buf_ctrl_size, . - ring_buf_ctrl

.struct 0
srl_device:
srl_device.dev:	.space 3
srl_device.rx_addr:	.space 1
srl_device.tx_addr:	.space 1
srl_device.type:	.space 1
srl_device.subtype:	.space 1
srl_device.rx_buf:	.space ring_buf_ctrl_size
srl_device.tx_buf:	.space ring_buf_ctrl_size
srl_device.error:	.space 3
.equ srl_device_size, . - srl_device
.equ srl_device.rx_buf.buf_start, srl_device.rx_buf + ring_buf_ctrl.buf_start - ring_buf_ctrl
.equ srl_device.rx_buf.buf_end, srl_device.rx_buf + ring_buf_ctrl.buf_end - ring_buf_ctrl
.equ srl_device.rx_buf.data_start, srl_device.rx_buf + ring_buf_ctrl.data_start - ring_buf_ctrl
.equ srl_device.rx_buf.data_break, srl_device.rx_buf + ring_buf_ctrl.data_break - ring_buf_ctrl
.equ srl_device.rx_buf.data_end, srl_device.rx_buf + ring_buf_ctrl.data_end - ring_buf_ctrl
.equ srl_device.rx_buf.dma_active, srl_device.rx_buf + ring_buf_ctrl.dma_active - ring_buf_ctrl
.equ srl_device.tx_buf.buf_start, srl_device.tx_buf + ring_buf_ctrl.buf_start - ring_buf_ctrl
.equ srl_device.tx_buf.buf_end, srl_device.tx_buf + ring_buf_ctrl.buf_end - ring_buf_ctrl
.equ srl_device.tx_buf.data_start, srl_device.tx_buf + ring_buf_ctrl.data_start - ring_buf_ctrl
.equ srl_device.tx_buf.data_break, srl_device.tx_buf + ring_buf_ctrl.data_break - ring_buf_ctrl
.equ srl_device.tx_buf.data_end, srl_device.tx_buf + ring_buf_ctrl.data_end - ring_buf_ctrl
.equ srl_device.tx_buf.dma_active, srl_device.tx_buf + ring_buf_ctrl.dma_active - ring_buf_ctrl

.struct 0
setuppkt:
setuppkt.bmRequestType:	.space 1
setuppkt.bRequest:	.space 1
setuppkt.wValue:	.space 2
setuppkt.wIndex:	.space 2
setuppkt.wLength:	.space 2
.equ setuppkt_size, . - setuppkt
assert (setuppkt_size == 8)

.struct 0
descriptor:
descriptor.bLength:	.space 1
descriptor.bDescriptorType:	.space 1
.equ descriptor_size, . - descriptor
assert (descriptor_size == 2)

.struct 0
deviceDescriptor:
deviceDescriptor.descriptor:	.space descriptor_size
deviceDescriptor.bcdUSB:	.space 2
deviceDescriptor.bDeviceClass:	.space 1
deviceDescriptor.bDeviceSubClass:	.space 1
deviceDescriptor.bDeviceProtocol:	.space 1
deviceDescriptor.bMaxPacketSize0:	.space 1
deviceDescriptor.idVendor:	.space 2
deviceDescriptor.idProduct:	.space 2
deviceDescriptor.bcdDevice:	.space 2
deviceDescriptor.iManufacturer:	.space 1
deviceDescriptor.iProduct:	.space 1
deviceDescriptor.iSerialNumber:	.space 1
deviceDescriptor.bNumConfigurations:	.space 1
.equ deviceDescriptor_size, . - deviceDescriptor
assert (deviceDescriptor_size == 18)

.struct 0
configurationDescriptor:
configurationDescriptor.descriptor:	.space descriptor_size
configurationDescriptor.wTotalLength:	.space 2
configurationDescriptor.bNumInterfaces:	.space 1
configurationDescriptor.bConfigurationValue:	.space 1
configurationDescriptor.iConfiguration:	.space 1
configurationDescriptor.bmAttributes:	.space 1
configurationDescriptor.bMaxPower:	.space 1
.equ configurationDescriptor_size, . - configurationDescriptor
assert (configurationDescriptor_size == 9)

.struct 0
interfaceDescriptor:
interfaceDescriptor.descriptor:	.space descriptor_size
interfaceDescriptor.bInterfaceNumber:	.space 1
interfaceDescriptor.bAlternateSetting:	.space 1
interfaceDescriptor.bNumEndpoints:	.space 1
interfaceDescriptor.bInterfaceClass:	.space 1
interfaceDescriptor.bInterfaceSubClass:	.space 1
interfaceDescriptor.bInterfaceProtocol:	.space 1
interfaceDescriptor.iInterface:	.space 1
.equ interfaceDescriptor_size, . - interfaceDescriptor
assert (interfaceDescriptor_size == 9)

.struct 0
endpointDescriptor:
endpointDescriptor.descriptor:	.space descriptor_size
endpointDescriptor.bEndpointAddress:	.space 1
endpointDescriptor.bmAttributes:	.space 1
endpointDescriptor.wMaxPacketSize:	.space 2
endpointDescriptor.bInterval:	.space 1
.equ endpointDescriptor_size, . - endpointDescriptor
assert (endpointDescriptor_size == 7)

.macro setup_packet request_type, request, value, index, length
	.db \request_type, \request
	.dw \value, \index, \length
.endm

.text

.struct 0
SRL_TYPE_UNKNOWN:	.space 1	; Incompatible or non-serial device
SRL_TYPE_HOST:	.space 1	; Calc is acting as a device
SRL_TYPE_CDC:	.space 1	; CDC device
SRL_TYPE_FTDI:	.space 1	; FTDI device
SRL_TYPE_PL2303:	.space 1	; PL2303 device
.text

.struct 0
SRL_SUBTYPE_FTDI_UNKNOWN:	.space 1
SRL_SUBTYPE_SIO:	.space 1
SRL_SUBTYPE_FT8U232AM:	.space 1
SRL_SUBTYPE_FT232BM:	.space 1
SRL_SUBTYPE_FT2232C:	.space 1
SRL_SUBTYPE_FT232RL:	.space 1
SRL_SUBTYPE_FTX:	.space 1
SRL_SUBTYPE_FT2232H:	.space 1
SRL_SUBTYPE_FT4232H:	.space 1
SRL_SUBTYPE_FT232H:	.space 1
.text

.struct 0
SRL_SUBTYPE_PL2303_01:	.space 1
SRL_SUBTYPE_PL2303_HX:	.space 1
.text

.equ SRL_INTERFACE_ANY, 0xFF

.equ SRL_SUCCESS, 0
.equ SRL_ERROR_INVALID_PARAM, -1
.equ SRL_ERROR_USB_FAILED, -2
.equ SRL_ERROR_NOT_SUPPORTED, -3
.equ SRL_ERROR_INVALID_DEVICE, -4
.equ SRL_ERROR_INVALID_INTERFACE, -5
.equ SRL_ERROR_NO_MEMORY, -6
.equ SRL_ERROR_DEVICE_DISCONNECTED, -7

; enum usb_transfer_status
.equ USB_TRANSFER_COMPLETED, 0
.equ USB_TRANSFER_STALLED, 1 << 0
.equ USB_TRANSFER_NO_DEVICE, 1 << 1
.equ USB_TRANSFER_HOST_ERROR, 1 << 2
.equ USB_TRANSFER_ERROR, 1 << 3
.equ USB_TRANSFER_OVERFLOW, 1 << 4
.equ USB_TRANSFER_BUS_ERROR, 1 << 5
.equ USB_TRANSFER_FAILED, 1 << 6
.equ USB_TRANSFER_CANCELLED, 1 << 7

; enum usb_find_flag
.equ IS_NONE, 0
.equ IS_DISABLED, 1 << 0
.equ IS_ENABLED, 1 << 1
.equ IS_DEVICE, 1 << 2
.equ IS_HUB, 1 << 3
.equ IS_ATTACHED, 1 << 4

; enum usb_descriptor_type
.struct 1
DEVICE_DESCRIPTOR:	.space 1
CONFIGURATION_DESCRIPTOR:	.space 1
STRING_DESCRIPTOR:	.space 1
INTERFACE_DESCRIPTOR:	.space 1
ENDPOINT_DESCRIPTOR:	.space 1
.text

;srl_error_t srl_Open(srl_device_t *srl,
;                     usb_device_t dev,
;                     void *buffer,
;                     size_t size,
;                     uint8_t interface,
;                     uint24_t rate);
srl_Open:
	ld	iy, 0
	add	iy, sp
	push	ix
	ld	ix, (iy+3)				; ix = srl

	ld	hl, (iy+6)				; hl = dev
	compare_hl_zero					; check if device is null
	ld	a, SRL_ERROR_INVALID_DEVICE
	jp	z, srl_Open.exit
	ld	(ix + srl_device.dev), hl

	ld	hl, (iy+12)				; hl = size
	ld	de, 128					; check if buffer is large enough
	compare_hl_de
	ld	a, SRL_ERROR_NO_MEMORY
	jp	c, srl_Open.exit

	ld	(ix + srl_device.rx_buf.buf_end), hl		; divide size by 2
	srl	(ix + srl_device.rx_buf.buf_end+2)
	rr	(ix + srl_device.rx_buf.buf_end+1)
	rr	(ix + srl_device.rx_buf.buf_end)
	ld	de, (ix + srl_device.rx_buf.buf_end)		; de = size / 2

	ld	hl, (iy+9)				; hl = buffer
	ld	(ix + srl_device.rx_buf.buf_start), hl
	ld	(ix + srl_device.rx_buf.data_start), hl
	ld	(ix + srl_device.rx_buf.data_end), hl

	add	hl, de					; hl = buffer + size/2
	ld	(ix + srl_device.rx_buf.buf_end), hl
	ld	(ix + srl_device.tx_buf.buf_start), hl
	ld	(ix + srl_device.tx_buf.data_start), hl
	ld	(ix + srl_device.tx_buf.data_end), hl

	add	hl, de					; hl = buffer + size
	ld	(ix + srl_device.tx_buf.buf_end), hl

	xor	a, a					; set break positions to null
	sbc	hl, hl
	ld	(ix + srl_device.rx_buf.data_break), hl
	ld	(ix + srl_device.tx_buf.data_break), hl
	ld	(ix + srl_device.rx_buf.dma_active), a	; reset dma_active
	ld	(ix + srl_device.tx_buf.dma_active), a

	ld	(ix + srl_device.error), hl			; reset error

	push	iy
	call	usb_GetRole
	pop	iy
	bit	4, l
	jr	z, srl_Open.role_host

	; calc is acting as device
	ld	a, SRL_TYPE_HOST
	ld	(ix + srl_device.type), a
	ld	a, 0x83
	ld	(ix + srl_device.tx_addr), a
	ld	a, 0x04
	ld	(ix + srl_device.rx_addr), a
	jp	srl_Open.shared

srl_Open.role_host:
	; check if device is enabled
	push	iy
	ld	bc, (ix + srl_device.dev)
	push	bc
	call	usb_GetDeviceFlags
	pop	bc
	pop	iy

	ld	a, SRL_ERROR_INVALID_DEVICE
	bit	IS_ENABLED, l
	jp	z, srl_Open.exit

	; get descriptors
	push	iy
	ld	bc, srl_Open.transferred
	push	bc
	ld	bc, 18					; length
	push	bc
	ld	bc, (iy+9)				; descriptor = buffer
	push	bc
	ld	bc, 0					; index = 0
	push	bc
	ld	bc, DEVICE_DESCRIPTOR
	push	bc
	ld	bc, (ix + srl_device.dev)
	push	bc
	call	usb_GetDescriptor
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	iy

	ld	a, SRL_ERROR_USB_FAILED
	compare_hl_zero
	jp	nz, srl_Open.exit

	ld	hl, 0					; check transferred == length
.set srl_Open.transferred, .-3
	ld	bc, 18
	or	a, a
	sbc	hl, bc
	jp	nz, srl_Open.exit				; a = USB_FAILED

	push	iy
	ld	bc, srl_Open.current_config			; get current config
	push	bc
	ld	bc, (ix + srl_device.dev)
	push	bc
	call	usb_GetConfiguration
	pop	bc
	pop	bc
	pop	iy

	ld	a, SRL_ERROR_USB_FAILED
	compare_hl_zero
	jp	nz, srl_Open.exit

	push	iy
	ld	de, 0
.set srl_Open.current_config, .-3
	ld	a, e
	or	a, a
	jr	z, srl_Open.noPrevConfig
	dec	de
srl_Open.noPrevConfig:
	push	de
	ld	bc, (ix + srl_device.dev)
	push	bc
	call	usb_GetConfigurationDescriptorTotalLength
	pop	bc
	pop	bc
	pop	iy

	ld	a, SRL_ERROR_USB_FAILED
	compare_hl_zero
	jp	z, srl_Open.exit

	ex	de, hl					; de = desc. length

	ld	hl, 18					; get length of both descriptors
	add	hl, de
	ld	bc, (iy + 12)				; check if buffer is large enough
	or	a, a
	sbc	hl, bc
	ld	a, SRL_ERROR_NO_MEMORY
	jp	nc, srl_Open.exit

	push	iy					; de = desc. length
	push	de
	ld	bc, srl_Open.config_transferred
	push	bc
	push	de					; length
	ld	hl, (iy+9)				; descriptor = buffer + sizeof deviceDescriptor
	ld	bc, 18
	add	hl, bc
	push	hl
	ld	bc, (srl_Open.current_config)			; index = current config - 1
	ld	a, c
	or	a, a
	jr	z, srl_Open.noPrevConfig2
	dec	bc
srl_Open.noPrevConfig2:
	push	bc
	ld	c, CONFIGURATION_DESCRIPTOR
	push	bc
	ld	bc, (ix + srl_device.dev)
	push	bc
	call	usb_GetDescriptor
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	de					; de = desc. length
	pop	iy

	ld	a, SRL_ERROR_USB_FAILED
	compare_hl_zero
	jr	nz, srl_Open.exit

	ld	hl, 0
.set srl_Open.config_transferred, .-3
	or	a, a
	sbc	hl, de
	jr	nz, srl_Open.exit

	ld	a, (srl_Open.current_config)
	or	a, a
	jr	nz, srl_Open.configured

	push	iy
	push	de					; size of conf. descriptor
	ld	hl, (iy+9)				; buffer
	ld	bc, 18
	add	hl, bc
	push	hl
	ld	bc, (ix + srl_device.dev)
	push	bc
	call	usb_SetConfiguration
	pop	bc
	pop	bc
	pop	bc
	pop	iy

	ld	a, SRL_ERROR_USB_FAILED
	compare_hl_zero
	jr	nz, srl_Open.exit

srl_Open.configured:
	ld	a, (iy+15)				; a = interface number
	push	iy
	call	get_device_type
	pop	iy
	ld	a, (ix + srl_device.type)			; check if type is unknown
	cp	a, SRL_TYPE_UNKNOWN
	ld	a, SRL_ERROR_INVALID_DEVICE
	jr	z, srl_Open.exit

	call	init_device
	ld	a, l					; check for error
	or	a, a
	jr	nz, srl_Open.exit_hl

	ld	hl, (iy+18)				; hl = baud rate
	ld	c, (iy+15)				; a = interface number
	call	set_rate
	ld	a, l					; check for error
	or	a, a
	jr	nz, srl_Open.exit_hl

srl_Open.shared:
	ld	hl, (ix + srl_device.dev)
	push	iy
	push	hl
	call	usb_RefDevice
	pop	hl
	pop	iy

	lea	ix, ix + srl_device.rx_buf
	call	start_read

	xor	a, a					; a = USB_SUCCESS
srl_Open.exit:
	scf
	sbc	hl, hl
	dec	a
	ld	l, a
	inc	hl
srl_Open.exit_hl:
	pop	ix
	ret

;void srl_Close(srl_device_t *srl);
srl_Close:
	; todo: cancel transfers somehow?
	jp	usb_UnrefDevice

;size_t srl_Read(srl_device_t *srl,
;                void *data,
;                size_t length);
srl_Read:
	ld	iy, 0
	add	iy, sp
	push	ix
	ld	ix, (iy+3)
	ld	hl, (ix + srl_device.error)
	compare_hl_zero
	jr	nz, srl_Read.exit

	ld	hl, (iy+6)
	ld	bc, (iy+9)
	lea	ix, ix + srl_device.rx_buf
	call	ring_buf_pop
	ld	a, (ix + ring_buf_ctrl.dma_active)		; check if dma active
	or	a, a
	jr	nz, srl_Read.exit
	push	hl
	call	start_read
	pop	hl
srl_Read.exit:
	pop	ix
	ret

;size_t srl_Write(srl_device_t *srl,
;                 const void *data,
;                 size_t length);
srl_Write:
	ld	iy, 0
	add	iy, sp
	push	ix
	ld	ix, (iy+3)
	ld	hl, (ix + srl_device.error)
	compare_hl_zero
	jr	nz, srl_Write.exit

	ld	hl, (iy+6)
	ld	bc, (iy+9)
	lea	ix, ix + srl_device.tx_buf
	call	ring_buf_push
	ld	a, (ix + ring_buf_ctrl.dma_active)		; check if dma active
	or	a, a
	jr	nz, srl_Write.exit
	push	hl
	call	start_write
	pop	hl
srl_Write.exit:
	pop	ix
	ret

;usb_standard_descriptors_t *srl_GetCDCStandardDescriptors(void);
srl_GetCDCStandardDescriptors:
	call	ti.os.GetSystemInfo
	ld	de, 4
	add	hl, de
	bit	0, (hl)
	jr	z, srl_GetCDCStandardDescriptors.84pce

	ld	a, 0x60
	ld	(srl_GetCDCStandardDescriptors.device+deviceDescriptor.bcdDevice), a
	ld	hl, srl_GetCDCStandardDescriptors.string83
	ld	(srl_GetCDCStandardDescriptors.model), hl
srl_GetCDCStandardDescriptors.84pce:
	ld	iy, ti.flags	; get serial number
	call	ti.GetSerial
	jr	nz, srl_GetCDCStandardDescriptors.noserial

	ld	a, 3
	ld	(srl_GetCDCStandardDescriptors.device+deviceDescriptor.iSerialNumber), a

	ld	de, srl_GetCDCStandardDescriptors.stringserialnum + 2
	ld	hl, ti.OP4
	ld	b, 5
srl_GetCDCStandardDescriptors.loop_byte:
	ld	a, (hl)
	rra
	rra
	rra
	rra
	call	srl_GetCDCStandardDescriptors.conv_hex
	ld	a, (hl)
	call	srl_GetCDCStandardDescriptors.conv_hex
	inc	hl
	djnz	srl_GetCDCStandardDescriptors.loop_byte
srl_GetCDCStandardDescriptors.noserial:
	ld	hl, srl_GetCDCStandardDescriptors.descriptors
	ret
srl_GetCDCStandardDescriptors.conv_hex:
	and	a, 0xf
	add	a, 0x30
	cp	a, 0x39+1
	jr	c, srl_GetCDCStandardDescriptors.store
	add	a, 0x41-0x39-1
srl_GetCDCStandardDescriptors.store:
	ld	(de), a
	inc	de
	inc	de
	ret

srl_GetCDCStandardDescriptors.descriptors:
	.d24	srl_GetCDCStandardDescriptors.device, srl_GetCDCStandardDescriptors.configurations, srl_GetCDCStandardDescriptors.langids
	.db	3
	.d24	srl_GetCDCStandardDescriptors.strings
srl_GetCDCStandardDescriptors.device:
	.db 0x12, 0x01, 0x00, 0x02, 0x02, 0x00, 0x00, 0x40, 0xC0, 0x16, 0xE1, 0x05, 0x20, 0x02, 0x01, 0x02
	.db 0x00, 0x01
srl_GetCDCStandardDescriptors.configurations:
	.d24	srl_GetCDCStandardDescriptors.configuration1
srl_GetCDCStandardDescriptors.configuration1:
	.db 0x09, 0x02, 0x3E, 0x00, 0x02, 0x01, 0x00, 0xC0, 0x32, 0x09, 0x04, 0x00, 0x00, 0x01, 0x02, 0x02
	.db 0x00, 0x00, 0x05, 0x24, 0x00, 0x01, 0x10, 0x04, 0x24, 0x02, 0x00, 0x05, 0x24, 0x06, 0x00, 0x01
	.db 0x07, 0x05, 0x82, 0x03, 0x08, 0x00, 0xFF, 0x09, 0x04, 0x01, 0x00, 0x02, 0x0A, 0x02, 0x00, 0x00
	.db 0x07, 0x05, 0x04, 0x02, 0x40, 0x00, 0x01, 0x07, 0x05, 0x83, 0x02, 0x40, 0x00, 0x01
srl_GetCDCStandardDescriptors.langids:
	.dw	0x0304, 0x0409
srl_GetCDCStandardDescriptors.strings:
	.d24	srl_GetCDCStandardDescriptors.string1
srl_GetCDCStandardDescriptors.model:
	.d24	srl_GetCDCStandardDescriptors.string84
srl_GetCDCStandardDescriptors.serial:
	.d24	srl_GetCDCStandardDescriptors.stringserialnum
srl_GetCDCStandardDescriptors.string1:
	.dw	0x033E, 0x54, 0x65, 0x78, 0x61, 0x73, 0x20, 0x49, 0x6e, 0x73, 0x74, 0x72, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x73, 0x20, 0x49, 0x6e, 0x63, 0x6f, 0x72, 0x70, 0x6f, 0x72, 0x61, 0x74, 0x65, 0x64
srl_GetCDCStandardDescriptors.string83:
	.dw	0x0322, 0x54, 0x49, 0x2d, 0x38, 0x33, 0x20, 0x50, 0x72, 0x65, 0x6d, 0x69, 0x75, 0x6d, 0x20, 0x43, 0x45
srl_GetCDCStandardDescriptors.string84:
	.dw	0x031C, 0x54, 0x49, 0x2d, 0x38, 0x34, 0x20, 0x50, 0x6c, 0x75, 0x73, 0x20, 0x43, 0x45
srl_GetCDCStandardDescriptors.stringserialnum:
	.dw	0x0316, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30

;usb_error_t srl_UsbEventCallback(usb_event_t event, void *event_data,
;                                    usb_callback_data_t *callback_data) {
;    if (event == USB_DEFAULT_SETUP_EVENT) {
;        static uint8_t line_coding[7];
;        usb_control_setup_t *setup = (usb_control_setup_t*)event_data;
;        // Hack because Windows doesn't follow the damn specification
;        if ((setup->bmRequestType == 0xA1 && setup->bRequest == 0x21) ||
;            (setup->bmRequestType == 0x21 && setup->bRequest == 0x20)) {
;                usb_ScheduleDefaultControlTransfer(usb_FindDevice(NULL, NULL, USB_SKIP_HUBS), setup, line_coding, NULL, NULL);
;            return USB_IGNORE;
;        }
;    }
;    return USB_SUCCESS;
;}
srl_UsbEventCallback:
	call	ti._frameset0
	ld	hl, (ix + 6)
	ld	bc, 0
	ld	de, 11
	sbc	hl, de
	jr	nz, srl_UsbEventCallback.BB0_5
	ld	iy, (ix + 9)
	ld	a, (iy)
	cp	a, -95
	jr	nz, srl_UsbEventCallback.BB0_2
	ld	a, (iy + 1)
	cp	a, 33
	jr	z, srl_UsbEventCallback.BB0_4
	jr	srl_UsbEventCallback.BB0_5
srl_UsbEventCallback.BB0_2:
	cp	a, 33
	jr	nz, srl_UsbEventCallback.BB0_5
	ld	a, (iy + 1)
	cp	a, 32
	jr	nz, srl_UsbEventCallback.BB0_5
srl_UsbEventCallback.BB0_4:
	ld	de, 0
	ld	hl, 8
	push	hl
	push	de
	push	de
	call	usb_FindDevice
	ld	sp, ix
	ld	de, 0
	push	de
	push	hl
	call	usb_GetDeviceEndpoint
	ld	sp, ix
	ld	de, 0
	push	de
	push	de
	ld	de, srl_UsbEventCallback.line_coding
	push	de
	ld	de, (ix + 9)
	push	de
	push	hl
	call	usb_ScheduleControlTransfer
	ld	bc, 1
	ld	sp, ix
srl_UsbEventCallback.BB0_5:
	push	bc
	pop	hl
	pop	ix
	ret
srl_UsbEventCallback.line_coding:
	.space 7

; Gets the device type and subtype based on the descriptors
; Inputs:
;  ix: Serial device struct
;  a: Interface number
;  xsrl_device.rx_buf.buf_start: Device descriptor, followed by config descriptor
; Returns:
;  xsrl_device.type: Device type
;  xsrl_device.subtype: Device subtype
;  xsrl_device.rx_addr: Receive endpoint address
;  xsrl_device.tx_addr: Transmit endpoint address
get_device_type:
	ld	(get_device_type.expectedIntNum), a

; todo: vendor-specific devices

; check for CDC ACM device
	ld	hl, (ix + srl_device.rx_buf.buf_start)
	call	next_descriptor
	inc	hl
	inc	hl
	inc.s	de	; clear UDE
	ld	e, (hl)	; total descriptor length
	inc	hl
	ld	d, (hl)
	dec	hl
	dec	hl
	dec	hl
	ex	de, hl
	add	hl, de
	ex	de, hl	; hl, de = start, end of config desc.
get_device_type.find_int_loop:
	call	next_interface_descriptor
	jr	nc, get_device_type.none
get_device_type.process_int:
	push	hl
	pop	iy
	ld	a, 0
.set get_device_type.expectedIntNum, .-1
	cp	a, SRL_INTERFACE_ANY
	jr	z, get_device_type.any
	cp	a, (iy + interfaceDescriptor.bInterfaceNumber)
	jr	nz, get_device_type.find_int_loop
get_device_type.any:
	ld	bc, 0
	ld	a, (iy + interfaceDescriptor.bInterfaceClass)
	cp	a, 0xa	; CDC data class
	jr	nz, get_device_type.find_int_loop

get_device_type.find_ep_loop:
	push	bc
	call	next_descriptor
	pop	bc
	jr	nc, get_device_type.int_complete
	push	hl
	pop	iy
	ld	a, (iy + descriptor.bDescriptorType)
	cp	a, INTERFACE_DESCRIPTOR
	jr	nz, get_device_type.not_int
get_device_type.int_complete:
	; check if both EPs found
	ld	a, b
	or	a, a
	jr	z, get_device_type.process_int
	ld	a, c
	or	a, a
	jr	z, get_device_type.process_int

	ld	(ix + srl_device.tx_addr), b
	ld	(ix + srl_device.rx_addr), c
	ld	a, SRL_TYPE_CDC
	ld	(ix + srl_device.type), a
	ret
get_device_type.not_int:
	cp	a, ENDPOINT_DESCRIPTOR
	jr	nz, get_device_type.find_int_loop

	ld	a, (iy + endpointDescriptor.bmAttributes)
	cp	a, 2	; bulk endpoint
	jr	nz, get_device_type.find_ep_loop

	ld	a, (iy + endpointDescriptor.bEndpointAddress)
	cp	a, 0x80
	jr	c, get_device_type.outEp
	ld	c, a
	jr	get_device_type.find_ep_loop
get_device_type.outEp:
	ld	b, a
	jr	get_device_type.find_ep_loop

get_device_type.none:
	xor	a, a
	ld	(ix + srl_device.type), a
	ld	(ix + srl_device.subtype), a
	ld	(ix + srl_device.rx_addr), a
	ld	(ix + srl_device.tx_addr), a
	ret

; Skips to the next descriptor
; Inputs:
;  hl: The current descriptor
;  de: The end of the config descriptor
; Outputs:
;  hl: The next descriptor
;  nc if end of config descriptor was reached
; Destroys: bc
next_descriptor:
	ld	bc, 0
	ld	c, (hl)
	add	hl, bc
	compare_hl_de
	ret

; Skips to the next interface descriptor
; Inputs:
;  hl: The current descriptor
;  de: The end of the config descriptor
; Outputs:
;  hl: The next interface descriptor
;  nc if end of config descriptor was reached
; Destroys: a, bc
next_interface_descriptor:
	ld	a, INTERFACE_DESCRIPTOR
next_interface_descriptor.loop:
	call	next_descriptor
	ret	nc
	inc	hl
	cp	a, (hl)
	dec	hl
	jr	nz, next_interface_descriptor.loop
	scf
	ret

; Initializes a serial device whose type has been determined
; Inputs:
;  ix: Serial device struct
; Returns:
;  hl: Error or SRL_SUCCESS
init_device:
	ld	hl, 0
	ret

; Sets the baud rate of a serial device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
;  c: Interface number
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate:
	ld	a, (ix + srl_device.type)
	or	a, a
	jr	z, set_rate.invalid_device
	dec	a					; type == HOST
	jr	z, set_rate.success
	dec	a					; type == CDC
	jr	z, set_rate_cdc
	dec	a					; type == FTDI
	jr	z, set_rate_ftdi
	dec	a					; type == PL2303
	jr	z, set_rate_cdc
set_rate.invalid_device:
	ld	hl, SRL_ERROR_INVALID_DEVICE
	ret
set_rate.success:
	or	a, a
	sbc	hl, hl
	ret

; Sets the baud rate of a USB CDC device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
;  c: Interface number
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate_cdc:
	ld	(set_rate_cdc.linecoding), hl
	ld	bc, 0
	push	bc	; transferred
	ld	c, 50	; ld bc, 50
	push	bc	; num retries
	ld	bc, set_rate_cdc.linecoding
	push	bc	; data
	ld	bc, set_rate_cdc.setup
	push	bc	; setup

	ld	bc, 0
	push	bc	; ep addr
	ld	bc, (ix + srl_device.dev)
	push	bc	; device
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc

	push	hl	; endpoint
	call	usb_ControlTransfer
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	a, l
	or	a, a
	ret	z
	ld	l, SRL_ERROR_USB_FAILED
	ret
set_rate_cdc.setup:
	setup_packet 0x21,0x20,0x0000,0x0000,0x0007
set_rate_cdc.linecoding:
	.db	0x80, 0x25, 0, 0, 0, 0, 8

; Sets the baud rate of a FTDI device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
;  c: Interface number
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate_ftdi:
	ret

; Sets the baud rate of a PL2303 device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
;  c: Interface number
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate_pl2303:
	ret

; Checks how many contiguous bytes are available in a ring buffer
; Inputs:
;  ix: ring_buf_ctrl struct
; Returns:
;  hl: Number of available bytes
ring_buf_contig_avail:
	ld	hl, (ix + ring_buf_ctrl.data_break)
	compare_hl_zero
	jr	z, ring_buf_contig_avail.no_break
	ld	bc, (ix + ring_buf_ctrl.data_start)
	or	a, a
	sbc	hl, bc
	ret
ring_buf_contig_avail.no_break:
	ld	hl, (ix + ring_buf_ctrl.data_end)
	ld	bc, (ix + ring_buf_ctrl.data_start)
	or	a, a
	sbc	hl, bc
	ret

; Checks if there is a consecutive region of the given size
; following the last available byte
; Inputs:
;  ix: ring_buf_ctrl struct
;  a: Size
; Returns:
;  c if the region does not exist
ring_buf_has_consecutive_region:
	ld	hl, (ix + ring_buf_ctrl.data_break)
	compare_hl_zero
	jr	nz, ring_buf_has_consecutive_region.break
	ld	hl, (ix + ring_buf_ctrl.buf_end)
	ld	bc, (ix + ring_buf_ctrl.data_end)
ring_buf_has_consecutive_region.compare:
	or	a, a
	sbc	hl, bc
	ld	bc, 0
	ld	c, a
	sbc	hl, bc
	ret
ring_buf_has_consecutive_region.break:
	ld	hl, (ix + ring_buf_ctrl.data_start)
	ld	bc, (ix + ring_buf_ctrl.data_end)
	jr	ring_buf_has_consecutive_region.compare

; Pushes bytes to a ring buffer
; Assumes that this buffer does not have any consecutive byte requirements
; Inputs:
;  ix: ring_buf_ctrl struct
;  hl: Data to push
;  bc: Number of bytes to push
; Returns:
;  hl: Number of bytes pushed
ring_buf_push:
	ex	de, hl					; de = data to push
	ld	hl, (ix + ring_buf_ctrl.data_break)
	compare_hl_zero
	jr	nz, ring_buf_push.break
	ld	hl, (ix + ring_buf_ctrl.buf_end)
	or	a, a
	sbc	hl, bc
	push	bc
	ld	bc, (ix + ring_buf_ctrl.data_end)
	or	a, a
	sbc	hl, bc
	jr	nc, ring_buf_push.pop_copy

	ld	hl, (ix + ring_buf_ctrl.buf_end)
	ld	(ix + ring_buf_ctrl.data_break), hl
	ld	bc, (ix + ring_buf_ctrl.data_end)
	or	a, a
	sbc	hl, bc					; hl = len
	push	hl
	pop	bc					; bc = len
	push	de
	call	ring_buf_push.copy					; hl = len
	ld	bc, (ix + ring_buf_ctrl.buf_start)
	ld	(ix + ring_buf_ctrl.data_end), bc
	ex	de, hl					; de = len
	pop	iy					; iy = data
	add	iy, de					; iy = data + len
	pop	hl					; hl = size
	sbc	hl, de
	push	hl
	pop	bc					; bc = size - len
	push	de
	lea	de, iy+0
	call	ring_buf_push.break
	pop	de
	add	hl, de
	ret
ring_buf_push.break:
	push	bc
	ld	hl, (ix + ring_buf_ctrl.data_start)
	ld	bc, (ix + ring_buf_ctrl.data_end)
	or	a, a
	sbc	hl, bc					; hl = len
	pop	bc					; bc = size
	or	a, a
	sbc	hl, bc
	add	hl, bc
	jr	nc, ring_buf_push.copy				; bc = len = size
	push	hl
ring_buf_push.pop_copy:
	pop	bc					; bc = len
ring_buf_push.copy:
	sbc	hl, hl					; check if bc is 0
	adc	hl, bc
	ret	z
	ld	hl, (ix + ring_buf_ctrl.data_end)
	ex	de, hl					; hl = data
	push	bc
	ldir						; de = data_end + len
	ld	(ix + ring_buf_ctrl.data_end), de
	pop	hl					; hl = len
	ret

; Takes bytes from a ring buffer
; Inputs:
;  ix: ring_buf_ctrl struct
;  hl: Location to copy data to
;  bc: Number of bytes to take
; Returns:
;  hl: Number of bytes taken
ring_buf_pop:
	ex	de, hl					; de = data
	ld	hl, (ix + ring_buf_ctrl.data_break)
	compare_hl_zero
	jr	nz, ring_buf_pop.break
ring_buf_pop.no_break:
	push	bc
	ld	hl, (ix + ring_buf_ctrl.data_end)
	ld	bc, (ix + ring_buf_ctrl.data_start)
	or	a, a
	sbc	hl, bc					; hl = len
	pop	bc					; bc = size
	or	a, a
	sbc	hl, bc
	add	hl, bc
	jr	nc, ring_buf_pop.copy				; bc = len = size
	push	hl
ring_buf_pop.pop_copy:
	pop	bc					; bc = len
ring_buf_pop.copy:
	sbc	hl, hl					; check if bc is 0
	adc	hl, bc
	ret	z
	ld	hl, (ix + ring_buf_ctrl.data_start)
	push	bc
	ldir						; hl = data_start + len
	ld	(ix + ring_buf_ctrl.data_start), hl
	pop	hl					; hl = len
	ret
ring_buf_pop.break:
	ld	hl, (ix + ring_buf_ctrl.data_break)
	or	a, a
	sbc	hl, bc
	push	bc
	ld	bc, (ix + ring_buf_ctrl.data_start)
	or	a, a
	sbc	hl, bc
	jr	nc, ring_buf_pop.pop_copy

	ld	hl, (ix + ring_buf_ctrl.data_break)
	ld	bc, (ix + ring_buf_ctrl.data_start)
	or	a, a
	sbc	hl, bc					; hl = len
	push	hl
	pop	bc					; bc = len
	push	de					; de = data
	call	ring_buf_pop.copy					; hl = len
	ld	bc, (ix + ring_buf_ctrl.buf_start)
	ld	(ix + ring_buf_ctrl.data_start), bc
	ld	bc, 0
	ld	(ix + ring_buf_ctrl.data_break), bc
	ex	de, hl					; de = len
	pop	iy					; iy = data
	add	iy, de					; iy = data + len
	pop	hl					; hl = size
	sbc	hl, de
	push	hl
	pop	bc					; bc = size - len
	push	de
	lea	de, iy+0
	call	ring_buf_pop.no_break
	pop	de
	add	hl, de
	ret

;usb_error_t (usb_endpoint_t endpoint, usb_transfer_status_t status, size_t transferred, srl_device_t *data);
read_callback:
	ld	iy, 0
	add	iy, sp
	push	ix
	ld	ix, (iy+12)

	ld	a, (iy+6)				; a = status
	and	a, USB_TRANSFER_NO_DEVICE
	jr	nz, read_callback.no_device

	ld	bc, (iy+9)
	lea	ix, ix + srl_device.rx_buf
	ld	hl, (ix + ring_buf_ctrl.data_end)
	add	hl, bc
	ld	(ix + ring_buf_ctrl.data_end), hl
	call	start_read
	pop	ix
	xor	a, a
	ret

read_callback.no_device:
	ld	a, SRL_ERROR_DEVICE_DISCONNECTED
	ld	(ix + srl_device.error), a
	xor	a, a
	ld	(ix + srl_device.rx_buf.dma_active), a
	pop	ix
	ret

;usb_error_t (usb_endpoint_t endpoint, usb_transfer_status_t status, size_t transferred, srl_device_t *data);
write_callback:
	ld	iy, 0
	add	iy, sp
	push	ix
	ld	ix, (iy+12)

	ld	a, (iy+6)				; a = status
	and	a, USB_TRANSFER_NO_DEVICE
	jr	nz, write_callback.no_device

	ld	bc, (iy+9)
	lea	ix, ix + srl_device.tx_buf
	ld	hl, (ix + ring_buf_ctrl.data_start)
	add	hl, bc
	ld	(ix + ring_buf_ctrl.data_start), hl
	call	start_write
	pop	ix
	xor	a, a
	ret

write_callback.no_device:
	ld	a, SRL_ERROR_DEVICE_DISCONNECTED
	ld	(ix + srl_device.error), a
	xor	a, a
	ld	(ix + srl_device.tx_buf.dma_active), a
	pop	ix
	ret

; Starts the receive transfer, if possible
; Inputs:
;  ix: rx_buf of a serial device struct
; Returns:
;  ix.dma_active: 1 if transfer was started, 0 otherwise
start_read:
	ld	a, 64
	call	ring_buf_has_consecutive_region
	jr	nc, start_read.has_region

	ld	hl, (ix + ring_buf_ctrl.data_break)
	compare_hl_zero
	jr	nz, start_read.error2

	; no break - add one

	ld	hl, (ix + ring_buf_ctrl.data_end)
	ld	(ix + ring_buf_ctrl.data_break), hl
	ld	hl, (ix + ring_buf_ctrl.buf_start)
	ld	(ix + ring_buf_ctrl.data_end), hl
	jr	start_read

start_read.has_region:
	lea	ix, ix - srl_device.rx_buf
	ld	c, (ix + srl_device.rx_addr)			; ix = srl device
	push	bc
	ld	bc, (ix + srl_device.dev)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc

	ld	a, l					; check if null
	or	a, a
	jr	z, start_read.error

	push	ix					; srl device
	ld	bc, read_callback
	push	bc					; handler
	ld	bc, 64
	push	bc					; length
	ld	bc, (ix + srl_device.rx_buf.data_end)
	push	bc					; buffer
	push	hl					; endpoint
	call	usb_ScheduleTransfer
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc

	ld	a, l
	or	a, a
	jr	nz, start_read.error

	inc	a					; a = 1
	ld	(ix + srl_device.rx_buf.dma_active), a
	ret
start_read.error2:
	lea	ix, ix - srl_device.rx_buf
start_read.error:
	xor	a, a
	ld	(ix + srl_device.rx_buf.dma_active), a
	ret

; Starts the transmit transfer, if possible
; Inputs:
;  ix: tx_buf of a serial device struct
; Returns:
;  ix.dma_active: 1 if transfer was started, 0 otherwise
start_write:
	call	ring_buf_contig_avail
	compare_hl_zero
	jr	nz, start_write.has_data

	ld	hl, (ix + ring_buf_ctrl.data_break)
	compare_hl_zero
	jr	z, start_write.error2

	; has break - try removing it

	ld	hl, (ix + ring_buf_ctrl.buf_start)
	ld	(ix + ring_buf_ctrl.data_start), hl
	or	a, a
	sbc	hl, hl
	ld	(ix + ring_buf_ctrl.data_break), hl

	jr	start_write

start_write.has_data:
	lea	ix, ix - srl_device.tx_buf
	push	hl

	ld	c, (ix + srl_device.tx_addr)			; ix = srl device
	push	bc
	ld	bc, (ix + srl_device.dev)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc
	pop	de					; de = length

	ld	a, l					; check if null
	or	a, a
	jr	z, start_write.error

	push	ix					; srl device
	ld	bc, write_callback
	push	bc					; handler
	push	de					; length
	ld	bc, (ix + srl_device.tx_buf.data_start)
	push	bc					; buffer
	push	hl					; endpoint
	call	usb_ScheduleTransfer
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc

	ld	a, l
	or	a, a
	jr	nz, start_write.error

	inc	a					; a = 1
	ld	(ix + srl_device.tx_buf.dma_active), a
	ret
start_write.error2:
	lea	ix, ix - srl_device.tx_buf
start_write.error:
	xor	a, a
	ld	(ix + srl_device.tx_buf.dma_active), a
	ret
