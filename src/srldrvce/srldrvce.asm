;-------------------------------------------------------------------------------
include '../include/library.inc'
include '../include/include_library.inc'
;-------------------------------------------------------------------------------

library SRLDRVCE, 0

;-------------------------------------------------------------------------------
; dependencies
;-------------------------------------------------------------------------------
include_library '../usbdrvce/usbdrvce.asm'

;-------------------------------------------------------------------------------
; v0 functions (not final, subject to change!)
;-------------------------------------------------------------------------------
	export	srl_Open
	export	srl_Close
	export	srl_Read
	export	srl_Write
	export	srl_GetCDCStandardDescriptors
	export	srl_UsbEventCallback
;-------------------------------------------------------------------------------
macro compare_hl_zero?
	add	hl,de
	or	a,a
	sbc	hl,de
end macro

macro compare_hl_de?
	or	a,a
	sbc	hl,de
	add	hl,de
end macro

;-------------------------------------------------------------------------------
; memory structures
;-------------------------------------------------------------------------------
macro struct? name*, parameters&
 local anon
 anon = 0
 macro name args&
  anon = anon + 1
  repeat 1, @anon: anon
   .@anon name args
  end repeat
 end macro
 macro end?.struct?!
     iterate base, ., .base
      if defined base
       assert base+sizeof base=$
      end if
     end iterate
   end namespace
  end struc
  iterate <base,prefix>, 0,, ix-name,x, iy-name,y
   virtual at base
	?prefix#name	name
   end virtual
  end iterate
  purge end?.struct?
 end macro
 struc name parameters
  namespace .
end macro

struct ring_buf_ctrl
	local size
	label  .: size
	buf_start			rl 1
	buf_end				rl 1
	data_start			rl 1
	data_break			rl 1
	data_end			rl 1
	dma_active			rb 1
	size := $-.
end struct

struct srl_device
	local size
	label  .: size
	dev				rl 1
	rx_addr				rb 1
	tx_addr				rb 1
	type				rb 1
	subtype				rb 1
	idvendor			rw 1
	idproduct			rw 1
	bcddevice			rw 1
	baudtype			rb 1
	rx_buf				ring_buf_ctrl
	tx_buf				ring_buf_ctrl
	error				rl 1
	size := $-.
end struct

virtual at 0
	SRL_TYPE_UNKNOWN		rb 1	; Incompatible or non-serial device
	SRL_TYPE_HOST			rb 1	; Calc is acting as a device
	SRL_TYPE_CDC			rb 1	; CDC device
	SRL_TYPE_FTDI			rb 1	; FTDI device
	SRL_TYPE_PL2303			rb 1	; PL2303 device
	SRL_TYPE_CH34X			rb 1	; CH34X device
	SRL_TYPE_CP210X			rb 1	; CP210X device
end virtual

virtual at 0
	SRL_SUBTYPE_FTDI_UNKNOWN	rb 1
;	SRL_SUBTYPE_SIO			rb 1
;	SRL_SUBTYPE_FT8U232AM		rb 1
;	SRL_SUBTYPE_FT232BM		rb 1
;	SRL_SUBTYPE_FT2232C		rb 1
;	SRL_SUBTYPE_FT232RL		rb 1
;	SRL_SUBTYPE_FTX			rb 1
;	SRL_SUBTYPE_FT2232H		rb 1
;	SRL_SUBTYPE_FT4232H		rb 1
;	SRL_SUBTYPE_FT232H		rb 1
	
	SRL_SUBTYPE_SIO			rb 1
	SRL_SUBTYPE_FT232A		rb 1
	SRL_SUBTYPE_FT232B		rb 1
	SRL_SUBTYPE_FT2232C		rb 1
	SRL_SUBTYPE_FT232R		rb 1				; FT232RL tested
	SRL_SUBTYPE_FT232H		rb 1
	SRL_SUBTYPE_FT2232H		rb 1
	SRL_SUBTYPE_FT4232H		rb 1
	SRL_SUBTYPE_FT4232HA		rb 1
	SRL_SUBTYPE_FT232HP		rb 1
	SRL_SUBTYPE_FT233HP		rb 1
	SRL_SUBTYPE_FT2232HP		rb 1
	SRL_SUBTYPE_FT2233HP		rb 1
	SRL_SUBTYPE_FT4232HP		rb 1
	SRL_SUBTYPE_FT4233HP		rb 1
	SRL_SUBTYPE_FTX			rb 1
end virtual

virtual at 0
	SRL_SUBTYPE_PL2303_01		rb 1
	SRL_SUBTYPE_PL2303_HX		rb 1
end virtual

virtual at 0
	SRL_SUBTYPE_CH340		rb 1				; CH340 tested
	SRL_SUBTYPE_CH341		rb 1
end virtual

virtual at 0
	SRL_SUBTYPE_CP2101		rb 1
	SRL_SUBTYPE_CP2102		rb 1				; CP2102 tested
	SRL_SUBTYPE_CP2103		rb 1
end virtual

virtual at 0
	BAUD_TYPE_UNKNOWN		rb 1
	BAUD_TYPE_HOST			rb 1
	BAUD_TYPE_CDC			rb 1
	BAUD_TYPE_FTDI_SIO		rb 1
	BAUD_TYPE_FTDI_AM		rb 1
	BAUD_TYPE_FTDI_BM		rb 1
	BAUD_TYPE_FTDI_H		rb 1
	BAUD_TYPE_PL2303		rb 1
	BAUD_TYPE_CH34X			rb 1
	BAUD_TYPE_CP210X		rb 1
end virtual

SRL_INTERFACE_ANY		:= $FF

SRL_SUCCESS			:= 0
SRL_ERROR_INVALID_PARAM		:= -1
SRL_ERROR_USB_FAILED		:= -2
SRL_ERROR_NOT_SUPPORTED		:= -3
SRL_ERROR_INVALID_DEVICE	:= -4
SRL_ERROR_INVALID_INTERFACE	:= -5
SRL_ERROR_NO_MEMORY		:= -6
SRL_ERROR_DEVICE_DISCONNECTED	:= -7

; enum usb_transfer_status
?USB_TRANSFER_COMPLETED		:= 0
?USB_TRANSFER_STALLED		:= 1 shl 0
?USB_TRANSFER_NO_DEVICE		:= 1 shl 1
?USB_TRANSFER_HOST_ERROR	:= 1 shl 2
?USB_TRANSFER_ERROR		:= 1 shl 3
?USB_TRANSFER_OVERFLOW		:= 1 shl 4
?USB_TRANSFER_BUS_ERROR		:= 1 shl 5
?USB_TRANSFER_FAILED		:= 1 shl 6
?USB_TRANSFER_CANCELLED		:= 1 shl 7

; vendor device matching equates
mtEquals		:= $20						; jr nz - for equal to (test succeeds on opposite of flag)
mtGreaterThanOrEqualTo	:= $38						; jr c - for greater than (or equal to) (adjust your table value by 1 to achieve 'greater than' behaviour)
mtLessThan		:= $30						; jr nc - for less than

struct setuppkt, requestType: ?, request: ?, value: ?, index: ?, length: ?, data: 0
	label .: 11
	bmRequestType		db requestType
	bRequest		db request
	wValue			dw value
	wIndex			dw index
	wLength			dw length
	ldata			dl data
end struct

struct baud, deviceType: ?, value: ?, index: ?
	label .: 5
	bdeviceSubType		db deviceType
	wValue			dw value
	wIndex			dw index
end struct

struct devchk, param: ?, matchtype: ?, value: ?
	label .: 4
	bParameter		db param
	bMatchType		db matchtype
	wValue			dw value
end struct

struct descriptor
	label .: 2
	bLength			rb 1
	bDescriptorType		rb 1
end struct
struct deviceDescriptor
	label .: 18
	?descriptor		descriptor
	bcdUSB			rw 1
	bDeviceClass		rb 1
	bDeviceSubClass		rb 1
	bDeviceProtocol		rb 1
	bMaxPacketSize0		rb 1
	idVendor		rw 1
	idProduct		rw 1
	bcdDevice		rw 1
	iManufacturer		rb 1
	iProduct		rb 1
	iSerialNumber		rb 1
	bNumConfigurations	rb 1
end struct
struct configurationDescriptor
	label .: 9
	?descriptor		descriptor
	wTotalLength		rw 1
	bNumInterfaces		rb 1
	bConfigurationValue	rb 1
	iConfiguration		rb 1
	bmAttributes		rb 1
	bMaxPower		rb 1
end struct
struct interfaceDescriptor
	label .: 9
	?descriptor		descriptor
	bInterfaceNumber	rb 1
	bAlternateSetting	rb 1
	bNumEndpoints		rb 1
	bInterfaceClass		rb 1
	bInterfaceSubClass	rb 1
	bInterfaceProtocol	rb 1
	iInterface		rb 1
end struct
struct endpointDescriptor
	label .: 7
	?descriptor		descriptor
	bEndpointAddress	rb 1
	bmAttributes		rb 1
	wMaxPacketSize		rw 1
	bInterval		rb 1
end struct

; enum usb_find_flag
?IS_NONE			:= 0
?IS_DISABLED			:= 1 shl 0
?IS_ENABLED			:= 1 shl 1
?IS_DEVICE			:= 1 shl 2
?IS_HUB				:= 1 shl 3
?IS_ATTACHED			:= 1 shl 4

; enum usb_descriptor_type
virtual at 1
	?DEVICE_DESCRIPTOR			rb 1
	?CONFIGURATION_DESCRIPTOR		rb 1
	?STRING_DESCRIPTOR			rb 1
	?INTERFACE_DESCRIPTOR			rb 1
	?ENDPOINT_DESCRIPTOR			rb 1
end virtual

null				:= 0

;srl_error_t srl_Open(srl_device_t *srl,
;                     usb_device_t dev,
;                     void *buffer,
;                     size_t size,
;                     uint8_t interface,
;                     uint24_t rate);
srl_Open:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy+3)				; ix = srl

	ld	hl,(iy+6)				; hl = dev
	compare_hl_zero					; check if device is null
	ld	a,SRL_ERROR_INVALID_DEVICE
	jq	z,.exit
	ld	(xsrl_device.dev),hl

	ld	hl,(iy+12)				; hl = size
	ld	de,128					; check if buffer is large enough
	compare_hl_de
	ld	a,SRL_ERROR_NO_MEMORY
	jq	c,.exit

	ld	(xsrl_device.rx_buf.buf_end),hl		; divide size by 2
	srl	(xsrl_device.rx_buf.buf_end+2)
	rr	(xsrl_device.rx_buf.buf_end+1)
	rr	(xsrl_device.rx_buf.buf_end)
	ld	de,(xsrl_device.rx_buf.buf_end)		; de = size / 2

	ld	hl,(iy+9)				; hl = buffer
	ld	(xsrl_device.rx_buf.buf_start),hl
	ld	(xsrl_device.rx_buf.data_start),hl
	ld	(xsrl_device.rx_buf.data_end),hl

	add	hl,de					; hl = buffer + size/2
	ld	(xsrl_device.rx_buf.buf_end),hl
	ld	(xsrl_device.tx_buf.buf_start),hl
	ld	(xsrl_device.tx_buf.data_start),hl
	ld	(xsrl_device.tx_buf.data_end),hl

	add	hl,de					; hl = buffer + size
	ld	(xsrl_device.tx_buf.buf_end),hl

	xor	a,a					; set break positions to null
	sbc	hl,hl
	ld	(xsrl_device.rx_buf.data_break),hl
	ld	(xsrl_device.tx_buf.data_break),hl
	ld	(xsrl_device.rx_buf.dma_active),a	; reset dma_active
	ld	(xsrl_device.tx_buf.dma_active),a

	ld	(xsrl_device.error),hl			; reset error

	push	iy
	call	usb_GetRole
	pop	iy
	bit	4,l
	jq	z,.role_host

	; calc is acting as device
	ld	a,SRL_TYPE_HOST
	ld	(xsrl_device.type),a
	ld	a,$83
	ld	(xsrl_device.tx_addr),a
	ld	a,$04
	ld	(xsrl_device.rx_addr),a
	jq	.shared

.role_host:
	; check if device is enabled
	push	iy
	ld	bc,(xsrl_device.dev)
	push	bc
	call	usb_GetDeviceFlags
	pop	bc,iy

	ld	a,SRL_ERROR_INVALID_DEVICE
	bit	IS_ENABLED,l
	jq	z,.exit

	; get descriptors
	push	iy
	ld	bc,.transferred
	push	bc
	ld	bc,18					; length
	push	bc
	ld	bc,(iy+9)				; descriptor = buffer
	push	bc
	ld	bc,0					; index = 0
	push	bc
	ld	bc,DEVICE_DESCRIPTOR
	push	bc
	ld	bc,(xsrl_device.dev)
	push	bc
	call	usb_GetDescriptor
	pop	bc,bc,bc,bc,bc,bc,iy

	ld	a,SRL_ERROR_USB_FAILED
	compare_hl_zero
	jq	nz,.exit

	ld	hl,0					; check transferred == length
.transferred = $-3
	ld	bc,18
	or	a,a
	sbc	hl,bc
	jq	nz,.exit				; a = USB_FAILED

	push	iy
	ld	bc,.current_config			; get current config
	push	bc	
	ld	bc,(xsrl_device.dev)
	push	bc
	call	usb_GetConfiguration
	pop	bc,bc,iy

	ld	a,SRL_ERROR_USB_FAILED
	compare_hl_zero
	jq	nz,.exit

	push	iy
	ld	de,0
.current_config = $-3
	ld	a,e
	or	a,a
	jq	z,.noPrevConfig
	dec	de
.noPrevConfig:
	push	de
	ld	bc,(xsrl_device.dev)
	push	bc
	call	usb_GetConfigurationDescriptorTotalLength
	pop	bc,bc,iy

	ld	a,SRL_ERROR_USB_FAILED
	compare_hl_zero
	jq	z,.exit

	ex	de,hl					; de = desc. length

	ld	hl,18					; get length of both descriptors
	add	hl,de
	ld	bc,(iy + 12)				; check if buffer is large enough
	or	a,a
	sbc	hl,bc
	ld	a,SRL_ERROR_NO_MEMORY
	jq	nc,.exit

	push	iy,de					; de = desc. length
	ld	bc,.config_transferred
	push	bc
	push	de					; length
	ld	hl,(iy+9)				; descriptor = buffer + sizeof deviceDescriptor
	ld	bc,18
	add	hl,bc
	push	hl
	ld	bc,(.current_config)			; index = current config - 1
	ld	a,c
	or	a,a
	jq	z,.noPrevConfig2
	dec	bc
.noPrevConfig2:
	push	bc
	ld	c,CONFIGURATION_DESCRIPTOR
	push	bc
	ld	bc,(xsrl_device.dev)
	push	bc
	call	usb_GetDescriptor
	pop	bc, bc, bc, bc, bc, bc
	pop	de,iy					; de = desc. length

	ld	a,SRL_ERROR_USB_FAILED
	compare_hl_zero
	jq	nz,.exit

	ld	hl,0
.config_transferred = $-3
	or	a,a
	sbc	hl,de
	jq	nz,.exit

	ld	a,(.current_config)
	or	a,a
	jq	nz,.configured

	push	iy
	push	de					; size of conf. descriptor
	ld	hl,(iy+9)				; buffer
	ld	bc,18
	add	hl,bc
	push	hl
	ld	bc,(xsrl_device.dev)
	push	bc
	call	usb_SetConfiguration
	pop	bc,bc,bc,iy

	ld	a,SRL_ERROR_USB_FAILED
	compare_hl_zero
	jq	nz,.exit

.configured:
	ld	a,(iy+15)				; a = interface number
	push	iy
	call	get_device_type
	pop	iy
	ld	a,(xsrl_device.type)			; check if type is unknown
	
	cp	a,SRL_TYPE_UNKNOWN
	ld	a,SRL_ERROR_INVALID_DEVICE
	jq	z,.exit

	call	init_device
	ld	a,l					; check for error
	or	a,a
	jq	nz,.exit_hl

	ld	hl,(iy+18)				; hl = baud rate
	ld	c,(iy+15)				; a = interface number
	call	set_rate
	ld	a,l					; check for error
	or	a,a
	jq	nz,.exit_hl

.shared:
	ld	hl,(xsrl_device.dev)
	push	iy,hl
	call	usb_RefDevice
	pop	hl,iy
	
	lea	ix,xsrl_device.rx_buf
	call	start_read

	xor	a,a					; a = USB_SUCCESS
.exit:
	scf
	sbc	hl,hl
	dec	a
	ld	l,a
	inc	hl
.exit_hl:
	pop	ix
	ret

;void srl_Close(srl_device_t *srl);
srl_Close:
	; todo: cancel transfers somehow?
	jq	usb_UnrefDevice

;size_t srl_Read(srl_device_t *srl,
;                void *data,
;                size_t length);
srl_Read:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy+3)
	ld	hl,(xsrl_device.error)
	compare_hl_zero
	jq	nz,.exit

	ld	hl,(iy+6)
	ld	bc,(iy+9)
	lea	ix,xsrl_device.rx_buf
	call	ring_buf_pop
	ld	a,(xring_buf_ctrl.dma_active)		; check if dma active
	or	a,a
	jq	nz,.exit
	push	hl
	call	start_read
	pop	hl
.exit:
	pop	ix
	ret

;size_t srl_Write(srl_device_t *srl,
;                 const void *data,
;                 size_t length);
srl_Write:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy+3)
	ld	hl,(xsrl_device.error)
	compare_hl_zero
	jq	nz,.exit

	ld	hl,(iy+6)
	ld	bc,(iy+9)
	lea	ix,xsrl_device.tx_buf
	call	ring_buf_push
	ld	a,(xring_buf_ctrl.dma_active)		; check if dma active
	or	a,a
	jq	nz,.exit
	push	hl
	call	start_write
	pop	hl
.exit:
	pop	ix
	ret

;usb_standard_descriptors_t *srl_GetCDCStandardDescriptors(void);
srl_GetCDCStandardDescriptors:
	call	ti.os.GetSystemInfo
	ld	de,4
	add	hl,de
	bit	0,(hl)
	jq	z,.84pce

	ld	a,$60
	ld	(.device+deviceDescriptor.bcdDevice),a
	ld	hl,.string83
	ld	(.model),hl
.84pce:
	ld	iy,ti.flags	; get serial number
	call	ti.GetSerial
	jq	nz,.noserial

	ld	a,3
	ld	hl,.device+deviceDescriptor.iSerialNumber
	ld	(hl),a

	ld	de,.stringserialnum + 2
	ld	hl,ti.OP4
	ld	b,5
.loop_byte:
	ld	a,(hl)
	rra
	rra
	rra
	rra
	call	.conv_hex
	ld	a,(hl)
	call	.conv_hex
	inc	hl
	djnz	.loop_byte
.noserial:
	ld	hl,.descriptors
	ret
.conv_hex:
	and	a,$f
	add	a,'0'
	cp	a,'9'+1
	jq	c,.store
	add	a,'A'-'9'-1
.store:
	ex	de,hl
	ld	(hl),a
	ex	de,hl
	inc	de
	inc	de
	ret

.descriptors:
	dl .device, .configurations, .langids
	db 3
	dl .strings
.device emit $12: $1201000202000040C016E105200201020001 bswap $12
.configurations dl .configuration1
.configuration1 emit $3e: $09023e00020100c0320904000001020200000524000110042402000524060001070582030800ff09040100020a0200000705040240000107058302400001 bswap $3e
.langids dw $0304, $0409
.strings dl .string1
.model dl .string84
.serial dl .stringserialnum
.string1 dw $033E, 'T','e','x','a','s',' ','I','n','s','t','r','u','m','e','n','t','s',' ','I','n','c','o','r','p','o','r','a','t','e','d'
.string83 dw $0322, 'T','I','-','8','3',' ','P','r','e','m','i','u','m',' ','C','E'
.string84 dw $031C, 'T','I','-','8','4',' ','P','l','u','s',' ','C','E'
.stringserialnum dw $0316, '0','0','0','0','0','0','0','0','0','0'

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
	jq	nz, .BB0_5
	ld	iy, (ix + 9)
	ld	a, (iy)
	cp	a, -95
	jq	nz, .BB0_2
	ld	a, (iy + 1)
	cp	a, 33
	jq	z, .BB0_4
	jq	.BB0_5
.BB0_2:
	cp	a, 33
	jq	nz, .BB0_5
	ld	a, (iy + 1)
	cp	a, 32
	jq	nz, .BB0_5
.BB0_4:
	ld	de, 0
	ld	hl, 8
	push	hl
	push	de
	push	de
	call	usb_FindDevice
	pop	de
	pop	de
	pop	de
	ld	de, 0
	push	de
	push	hl
	call	usb_GetDeviceEndpoint
	pop	de
	pop	de
	ld	de, 0
	push	de
	push	de
	ld	de, .line_coding
	push	de
	ld	de, (ix + 9)
	push	de
	push	hl
	call	usb_ScheduleControlTransfer
	ld	bc, 1
	pop	hl
	pop	hl
	pop	hl
	pop	hl
	pop	hl
.BB0_5:
	push	bc
	pop	hl
	pop	ix
	ret
.line_coding:
	rb	7

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
	ld	(.expectedIntNum),a

; todo: vendor-specific devices

	ld	hl,(xsrl_device.rx_buf.buf_start)
	push	hl
	ld	de,deviceDescriptor.idVendor
	add	hl,de
	lea	de,xsrl_device.idvendor
	ld	bc,6
	ldir								; set idVendor, idProduct & bcdDevice (expand if device matching requires it)
	pop	hl
	
; check for CDC ACM device
	call	next_descriptor
	inc	hl
	inc	hl
	ld	de,0
	ld	e,(hl)	; total descriptor length
	inc	hl
	ld	d,(hl)
	dec	hl
	dec	hl
	dec	hl
	ex	de,hl
	add	hl,de
	ex	de,hl	; hl, de = start, end of config desc.
.find_int_loop:
	call	next_interface_descriptor
	jq	nc,.none
.process_int:
	push	hl
	pop	iy
	ld	a,0
.expectedIntNum = $-1
	cp	a,SRL_INTERFACE_ANY
	jq	z,.any
	cp	a,(yinterfaceDescriptor.bInterfaceNumber)
	jq	nz,.find_int_loop
.any:
	ld	bc,0
	ld	a,(yinterfaceDescriptor.bInterfaceClass)
	cp	a,$a	; CDC data class
	jq	z,.cdc_int_found
	cp	$FF	; Vendor specific
	jq	nz,.find_int_loop

	call	check_vendor_specific_device
	jq	c,.find_int_loop
	
	ld	a,(bc)							; set type, subtype and baudtype from table
	ld	(xsrl_device.type),a
	inc	bc
	ld	a,(bc)
	ld	(xsrl_device.subtype),a
	inc	bc
	ld	a,(bc)
	ld	(xsrl_device.baudtype),a
	ld	bc,0
	jr	.find_ep_loop

.cdc_int_found:
	ld	a,SRL_TYPE_CDC
	ld	(xsrl_device.type),a

.find_ep_loop:
	push	bc
	call	next_descriptor
	pop	bc
	jq	nc,.int_complete
	push	hl
	pop	iy
	ld	a,(ydescriptor.bDescriptorType)
	cp	a,INTERFACE_DESCRIPTOR
	jq	nz,.not_int
.int_complete:
	; check if both EPs found
	ld	a,b
	or	a,a
	jq	z,.process_int
	ld	a,c
	or	a,a
	jq	z,.process_int
	
	ld	(xsrl_device.tx_addr),b
	ld	(xsrl_device.rx_addr),c
	ret
.not_int:
	cp	a,ENDPOINT_DESCRIPTOR
	jq	nz,.find_int_loop

	ld	a,(yendpointDescriptor.bmAttributes)
	cp	a,2	; bulk endpoint
	jq	nz,.find_ep_loop

	ld	a,(yendpointDescriptor.bEndpointAddress)
	cp	a,$80
	jq	c,.outEp
	ld	c,a
	jq	.find_ep_loop
.outEp:
	ld	b,a
	jq	.find_ep_loop

.none:
	xor	a,a
	ld	(xsrl_device.type),a
	ld	(xsrl_device.subtype),a
	ld	(xsrl_device.rx_addr),a
	ld	(xsrl_device.tx_addr),a
	ret

; Checks for compatible Vendor Specific device
; Inputs:
;  ix: Serial device struct
; Outputs:
;  bc = address for device type, subtype & baudtype
;  carry = error or SUCCESS
; Destroys: af
check_vendor_specific_device:
	push	hl,de
	ld	hl,vendor_device_match_table
	ld	b,(hl)							; total devices to check
	inc	hl
.loop1:
	push	hl,bc
	ld	hl,(hl)							; get current device
	ld	b,(hl)							; number of conditional check to perform
	inc	hl
.loop2:
	push	hl,bc
	ld	de,0							; deal with upper byte :S
	ld	a,(hl)							; device parameter to match
	ld	(.srl_device_param),a
	lea	bc,xsrl_device
.srl_device_param = $-1
	ld	a,(bc)
	ld	e,a
	inc	bc
	ld	a,(bc)
	ld	d,a							; de = get parameter to check	
	inc	hl
	ld	a,(hl)
	ld	(.match_type),a						; match mode (self-modify comparison)
	inc	hl
	ld	bc,0							; deal with upper byte :S
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	push	bc
	pop	hl							; hl = value to check against
	ex	de,hl
	or	a
	sbc	hl,de							; hl = srl_device, de = current table value
.match_type = $+0
	jr	nz,.match_not_found
.match_found:
	pop	bc,hl
	ld	de,1+1+2						; size of each match entry
	add	hl,de
	djnz	.loop2
.vendor_specific_device_found:
	push	hl
	pop	bc							; return pointer
	pop	hl,hl,de,hl
	or	a							; nc = SUCCESS
	ret
.match_not_found:
	pop	bc,hl,bc,hl
	inc	hl
	inc	hl
	inc	hl							; next device in table
	djnz	.loop1
.no_vendor_specific_device_found:
	pop	de,hl
	scf								; c = error
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
	ld	bc,0
	ld	c,(hl)
	add	hl,bc
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
	ld	a,INTERFACE_DESCRIPTOR
.loop:
	call	next_descriptor
	ret	nc
	inc	hl
	cp	a,(hl)
	dec	hl
	jr	nz,.loop
	scf
	ret

; Initializes a serial device whose type has been determined
; Inputs:
;  ix: Serial device struct
; Returns:
;  hl: Error or SRL_SUCCESS
init_device:
	ld	hl,0
	ret

; Sets the baud rate of a serial device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
;  c: Interface number
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate:
	ld	a,(xsrl_device.type)
	cp	SRL_TYPE_UNKNOWN			; UNKNOWN
	jq	z,.invalid_device
	cp	SRL_TYPE_HOST				; type == HOST
	jq	z,.success
	cp	SRL_TYPE_CDC				; type == CDC
	jq	z,set_rate_cdc
	cp	SRL_TYPE_FTDI				; type == FTDI
	jq	z,set_rate_ftdi
	cp	SRL_TYPE_PL2303				; type == PL2303
	jq	z,set_rate_cdc
	cp	SRL_TYPE_CH34X				; type == ch340x
	jq	z,set_rate_ch34x
	cp	SRL_TYPE_CP210X				; type == cp210x
	jq	z,set_rate_cp210x
.invalid_device:
	ld	hl,SRL_ERROR_INVALID_DEVICE
	ret
.success:
	or	a,a
	sbc	hl,hl
	ret

; Sets the baud rate of a USB CDC device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
;  c: Interface number
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate_cdc:
	ld	(default_cdc_setup.linecoding),hl			; set baud rate
	jq	set_rate_ct						; set

; Sets the baud rate of a FTDI device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
;  c: Interface number
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate_ftdi:								; mine is FT232RL, use some kind of gettype to determine correct table
	ld	a,(xsrl_device.baudtype)
	call	get_baud_settings_from_table
	or	a
	jq	nz,set_rate_ct.error
	ld	a,(hl)
	ld	(ft232rl_setup.baudDivisor + 0),a
	inc	hl
	ld	a,(hl)
	ld	(ft232rl_setup.baudDivisor + 1),a			; divisor & 0xFFFF
	inc	hl
	ld	a,(hl)
	ld	(ft232rl_setup.baudDivisor + 2),a
	inc	hl
	ld	a,(hl)
	ld	(ft232rl_setup.baudDivisor + 3),a			; divisor >> 16
	ld	hl,ft232rl_setup
	jq	set_rate_ct

; Sets the baud rate of a PL2303 device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
;  c: Interface number
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate_pl2303:
	ret

; Sets the baud rate of a CH34X device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
; Returns:
;  l: Error or SRL_SUCCESS
set_rate_ch34x:
	ld	a,(xsrl_device.baudtype)
	call	get_baud_settings_from_table
	or	a
	jq	nz,set_rate_ct.error
	ld	a,(hl)
	ld	(ch34x_setup.baudFactor + 0),a
	inc	hl
	ld	a,(hl)
	ld	(ch34x_setup.baudFactor + 1),a				; baud factor
	inc	hl
	ld	a,(hl)
	ld	(ch34x_setup.baudfOffset + 0),a
	inc	hl
	ld	a,(hl)
	ld	(ch34x_setup.baudfOffset + 1),a				; baud offset
	ld	hl,ch34x_setup
	jq	set_rate_ct	

; Sets the baud rate of a CP210X device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
; Returns:
;  l: Error or SRL_SUCCESS
set_rate_cp210x:
	ld	a,(xsrl_device.baudtype)
	call	get_baud_settings_from_table
	or	a
	jq	nz,set_rate_ct.error
	ld	a,(hl)
	ld	(cp210x_setup.baudRate + 0),a
	inc	hl
	ld	a,(hl)
	ld	(cp210x_setup.baudRate + 1),a				; baud rate (0x384000 / baudrate)
	ld	hl,cp210x_setup
	jq	set_rate_ct

; Sets the baud rate of a compatible USB device
; Inputs:
;  ix: Serial device struct
;  hl: Pointer to setup data
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate_ct:
	ld	b,(hl)							; total number of packets
	inc	hl
.loop:
	push	bc,hl
	ld	bc,0
	push	bc							; transferred
	ld	bc,50
	push	bc							; num retries
	ex	de,hl
	ld	bc,sizeof setuppkt - 3
	add	hl,bc
	ld	bc,(hl)
	push	bc							; data
	push	de							; setup
	ld	bc,0
	push	bc							; ep addr
	ld	bc,(xsrl_device.dev)
	push	bc							; device
	call	usb_GetDeviceEndpoint
	pop	bc,bc
	push	hl							; endpoint
	call	usb_ControlTransfer
	pop	bc,bc,bc,bc,bc,de,bc
	ld	a,l							; returned error code
	or	a,a
	jq	nz,.error						; something went wrong
	ld	hl,sizeof setuppkt
	add	hl,de							; next setup packet
	djnz	.loop
	ld	l,SRL_SUCCESS
	ret
.error:
	ld	hl,SRL_ERROR_USB_FAILED
	ret

; Gets baud settings for device based on baud type and baud rate
; Inputs:
;  a: device baud type
;  hl: baud rate
; Returns:
;  hl: pointer to baud table entry
;  a: Error or SRL_SUCCESS
get_baud_settings_from_table:
	push	af							; save subtype
	ld	a,(baud_rate_table)
	ld	de,baud_rate_table + 1
	ex	de,hl
.findLoop:
	ld	bc,(hl)
	ex	de,hl
	or	a
	sbc	hl,bc
	add	hl,bc
	ex	de,hl
	jr	z,get_baud_settings_table_data
	ld	bc,6
	add	hl,bc
	dec	a
	jr	nz,.findLoop
.error:
	pop	af
	ld	a,SRL_ERROR_USB_FAILED					; baud rate not found
	ret
get_baud_settings_table_data:
	inc	hl
	inc	hl
	inc	hl
	ld	hl,(hl)
	ld	b,(hl)
	inc	hl
	ld	de,sizeof baud
	pop	af							; restore subtype
.findLoop:
	cp	(hl)
	jr	z,.get_baud_rate
	add	hl,de
	djnz	.findLoop
	jr	get_baud_settings_from_table.error			; device subtype not found
.get_baud_rate:
	inc	hl
	xor	a
	ret

; Checks how many contiguous bytes are available in a ring buffer
; Inputs:
;  ix: ring_buf_ctrl struct
; Returns:
;  hl: Number of available bytes
ring_buf_contig_avail:
	ld	hl,(xring_buf_ctrl.data_break)
	compare_hl_zero
	jq	z,.no_break
	ld	bc,(xring_buf_ctrl.data_start)
	or	a,a
	sbc	hl,bc
	ret
.no_break:
	ld	hl,(xring_buf_ctrl.data_end)
	ld	bc,(xring_buf_ctrl.data_start)
	or	a,a
	sbc	hl,bc
	ret

; Checks if there is a consecutive region of the given size
; following the last available byte
; Inputs:
;  ix: ring_buf_ctrl struct
;  a: Size
; Returns:
;  c if the region does not exist
ring_buf_has_consecutive_region:
	ld	hl,(xring_buf_ctrl.data_break)
	compare_hl_zero
	jq	nz,.break
	ld	hl,(xring_buf_ctrl.buf_end)
	ld	bc,(xring_buf_ctrl.data_end)
.compare:
	or	a,a
	sbc	hl,bc
	ld	bc,0
	ld	c,a
	sbc	hl,bc
	ret
.break:
	ld	hl,(xring_buf_ctrl.data_start)
	ld	bc,(xring_buf_ctrl.data_end)
	jq	.compare

; Pushes bytes to a ring buffer
; Assumes that this buffer does not have any consecutive byte requirements
; Inputs:
;  ix: ring_buf_ctrl struct
;  hl: Data to push
;  bc: Number of bytes to push
; Returns:
;  hl: Number of bytes pushed
ring_buf_push:
	ex	de,hl					; de = data to push
	ld	hl,(xring_buf_ctrl.data_break)
	compare_hl_zero
	jq	nz,.break
	ld	hl,(xring_buf_ctrl.buf_end)
	or	a,a
	sbc	hl,bc
	push	bc
	ld	bc,(xring_buf_ctrl.data_end)
	or	a,a
	sbc	hl,bc
	jq	nc,.pop_copy

	ld	hl,(xring_buf_ctrl.buf_end)
	ld	(xring_buf_ctrl.data_break),hl
	ld	bc,(xring_buf_ctrl.data_end)
	or	a,a
	sbc	hl,bc					; hl = len
	push	hl
	pop	bc					; bc = len
	push	de
	call	.copy					; hl = len
	ld	bc,(xring_buf_ctrl.buf_start)
	ld	(xring_buf_ctrl.data_end),bc
	ex	de,hl					; de = len
	pop	iy					; iy = data
	add	iy,de					; iy = data + len
	pop	hl					; hl = size
	sbc	hl,de
	push	hl
	pop	bc					; bc = size - len
	push	de
	lea	de,iy
	call	.break
	pop	de
	add	hl,de
	ret
.break:
	push	bc
	ld	hl,(xring_buf_ctrl.data_start)
	ld	bc,(xring_buf_ctrl.data_end)
	or	a,a
	sbc	hl,bc					; hl = len
	pop	bc					; bc = size
	or	a,a
	sbc	hl,bc
	add	hl,bc
	jq	nc,.copy				; bc = len = size
	push	hl
.pop_copy:
	pop	bc					; bc = len
.copy:
	sbc	hl,hl					; check if bc is 0
	adc	hl,bc
	ret	z
	ex	de,hl					; hl = data
	ld	de,(xring_buf_ctrl.data_end)
	push	bc
	ldir						; de = data_end + len
	ld	(xring_buf_ctrl.data_end),de
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
	ex	de,hl					; de = data
	ld	hl,(xring_buf_ctrl.data_break)
	compare_hl_zero
	jq	nz,.break
.no_break:
	push	bc
	ld	hl,(xring_buf_ctrl.data_end)
	ld	bc,(xring_buf_ctrl.data_start)
	or	a,a
	sbc	hl,bc					; hl = len
	pop	bc					; bc = size
	or	a,a
	sbc	hl,bc
	add	hl,bc
	jq	nc,.copy				; bc = len = size
	push	hl
.pop_copy:
	pop	bc					; bc = len
.copy:
	sbc	hl,hl					; check if bc is 0
	adc	hl,bc
	ret	z
	ld	hl,(xring_buf_ctrl.data_start)
	push	bc
	ldir						; hl = data_start + len
	ld	(xring_buf_ctrl.data_start),hl
	pop	hl					; hl = len
	ret
.break:
	ld	hl,(xring_buf_ctrl.data_break)
	or	a,a
	sbc	hl,bc
	push	bc
	ld	bc,(xring_buf_ctrl.data_start)
	or	a,a
	sbc	hl,bc
	jq	nc,.pop_copy

	ld	hl,(xring_buf_ctrl.data_break)
	ld	bc,(xring_buf_ctrl.data_start)
	or	a,a
	sbc	hl,bc					; hl = len
	push	hl
	pop	bc					; bc = len
	push	de					; de = data
	call	.copy					; hl = len
	ld	bc,(xring_buf_ctrl.buf_start)
	ld	(xring_buf_ctrl.data_start),bc
	ld	bc,0
	ld	(xring_buf_ctrl.data_break),bc
	ex	de,hl					; de = len
	pop	iy					; iy = data
	add	iy,de					; iy = data + len
	pop	hl					; hl = size
	sbc	hl,de
	push	hl
	pop	bc					; bc = size - len
	push	de
	lea	de,iy
	call	.no_break
	pop	de
	add	hl,de
	ret

;usb_error_t (usb_endpoint_t endpoint, usb_transfer_status_t status, size_t transferred, srl_device_t *data);
read_callback:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy+12)

	ld	a,(iy+6)				; a = status
	and	a,USB_TRANSFER_NO_DEVICE
	jq	nz,.no_device

	ld	bc,(iy+9)
	lea	ix,xsrl_device.rx_buf
	ld	hl,(xring_buf_ctrl.data_end)
	add	hl,bc
	ld	(xring_buf_ctrl.data_end),hl
	call	start_read
	pop	ix
	xor	a,a
	ret

.no_device:
	ld	a,SRL_ERROR_DEVICE_DISCONNECTED
	ld	(xsrl_device.error),a
	xor	a,a
	ld	(xsrl_device.rx_buf.dma_active),a
	pop	ix
	ret

;usb_error_t (usb_endpoint_t endpoint, usb_transfer_status_t status, size_t transferred, srl_device_t *data);
write_callback:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy+12)

	ld	a,(iy+6)				; a = status
	and	a,USB_TRANSFER_NO_DEVICE
	jq	nz,.no_device

	ld	bc,(iy+9)
	lea	ix,xsrl_device.tx_buf
	ld	hl,(xring_buf_ctrl.data_start)
	add	hl,bc
	ld	(xring_buf_ctrl.data_start),hl
	call	start_write
	pop	ix
	xor	a,a
	ret

.no_device:
	ld	a,SRL_ERROR_DEVICE_DISCONNECTED
	ld	(xsrl_device.error),a
	xor	a,a
	ld	(xsrl_device.tx_buf.dma_active),a
	pop	ix
	ret

; Starts the receive transfer, if possible
; Inputs:
;  ix: rx_buf of a serial device struct
; Returns:
;  ix.dma_active: 1 if transfer was started, 0 otherwise
start_read:
	ld	a,64
	call	ring_buf_has_consecutive_region
	jq	nc,.has_region

	ld	hl,(xring_buf_ctrl.data_break)
	compare_hl_zero
	jq	nz,.error2

	; no break - add one

	ld	hl,(xring_buf_ctrl.data_end)
	ld	(xring_buf_ctrl.data_break),hl
	ld	hl,(xring_buf_ctrl.buf_start)
	ld	(xring_buf_ctrl.data_end),hl
	jq	start_read

.has_region:
	lea	ix,ix - srl_device.rx_buf
	ld	c,(xsrl_device.rx_addr)			; ix = srl device
	push	bc
	ld	bc,(xsrl_device.dev)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc,bc

	ld	a,l					; check if null
	or	a,a
	jq	z,.error

	push	ix					; srl device
	ld	bc,read_callback
	push	bc					; handler
	ld	bc,64
	push	bc					; length
	ld	bc,(xsrl_device.rx_buf.data_end)
	push	bc					; buffer
	push	hl					; endpoint
	call	usb_ScheduleTransfer
	pop	bc,bc,bc,bc,bc

	ld	a,l
	or	a,a
	jq	nz,.error

	inc	a					; a = 1
	ld	(xsrl_device.rx_buf.dma_active),a
	ret
.error2:
	lea	ix,ix - srl_device.rx_buf
.error:
	xor	a,a
	ld	(xsrl_device.rx_buf.dma_active),a
	ret

; Starts the transmit transfer, if possible
; Inputs:
;  ix: tx_buf of a serial device struct
; Returns:
;  ix.dma_active: 1 if transfer was started, 0 otherwise
start_write:
	call	ring_buf_contig_avail
	compare_hl_zero
	jq	nz,.has_data

	ld	hl,(xring_buf_ctrl.data_break)
	compare_hl_zero
	jq	z,.error2

	; has break - try removing it

	ld	hl,(xring_buf_ctrl.buf_start)
	ld	(xring_buf_ctrl.data_start),hl
	or	a,a
	sbc	hl,hl
	ld	(xring_buf_ctrl.data_break),hl

	jq	start_write

.has_data:
	lea	ix,ix - srl_device.tx_buf
	push	hl

	ld	c,(xsrl_device.tx_addr)			; ix = srl device
	push	bc
	ld	bc,(xsrl_device.dev)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc,bc
	pop	de					; de = length

	ld	a,l					; check if null
	or	a,a
	jq	z,.error

	push	ix					; srl device
	ld	bc,write_callback
	push	bc					; handler
	push	de					; length
	ld	bc,(xsrl_device.tx_buf.data_start)
	push	bc					; buffer
	push	hl					; endpoint
	call	usb_ScheduleTransfer
	pop	bc,bc,bc,bc,bc

	ld	a,l
	or	a,a
	jq	nz,.error

	inc	a					; a = 1
	ld	(xsrl_device.tx_buf.dma_active),a
	ret
.error2:
	lea	ix,ix - srl_device.tx_buf
.error:
	xor	a,a
	ld	(xsrl_device.tx_buf.dma_active),a
	ret

;========================================================================
; Data tables
;========================================================================
; Vendor match table
; Each table consists of a set of paramters to check to confirm a device
vendor_device_match_table:
	db	18							; total number of devices in table (8-bits for now)
	dl	.device_id_ftdi_sio
	dl	.device_id_ftdi_ft232a
	dl	.device_id_ftdi_ft232b
	dl	.device_id_ftdi_ft2232c
	dl	.device_id_ftdi_ft232r
	dl	.device_id_ftdi_ft2232h
	dl	.device_id_ftdi_ft4232h
	dl	.device_id_ftdi_ft232h
	dl	.device_id_ftdi_ftx
	dl	.device_id_ftdi_ft2233hp
	dl	.device_id_ftdi_ft4233hp
	dl	.device_id_ftdi_ft2232hp
	dl	.device_id_ftdi_ft4232hp
	dl	.device_id_ftdi_ft233hp
	dl	.device_id_ftdi_ft232hp
	dl	.device_id_ftdi_ft4232ha
	dl	.device_id_ch340
	dl	.device_id_cp2102

.device_id_ftdi_sio:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtLessThan, $0200			; < $0200 = SIO
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_SIO, BAUD_TYPE_FTDI_SIO
.device_id_ftdi_ft232a:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $0200			; $0200 = FT232A
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT232A, BAUD_TYPE_FTDI_AM
.device_id_ftdi_ft232b:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $0400			; $0400 = FT232B
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT232B, BAUD_TYPE_FTDI_BM
.device_id_ftdi_ft2232c:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $0500			; $0500 = FT2232C
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT2232C, BAUD_TYPE_FTDI_BM
.device_id_ftdi_ft232r:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $0600			; $0600 = FT232R
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT232R, BAUD_TYPE_FTDI_BM
.device_id_ftdi_ft2232h:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $0700			; $0700 = FT2232H
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT2232H, BAUD_TYPE_FTDI_H
.device_id_ftdi_ft4232h:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $0800			; $0800 = FT4232H
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT4232H, BAUD_TYPE_FTDI_H
.device_id_ftdi_ft232h:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $0900			; $0900 = FT232H
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT232H, BAUD_TYPE_FTDI_H
.device_id_ftdi_ftx:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $1000			; $1000 = FTX
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FTX, BAUD_TYPE_FTDI_BM
.device_id_ftdi_ft2233hp:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $2800			; $2800 = FT2233HP
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT2233HP, BAUD_TYPE_FTDI_H
.device_id_ftdi_ft4233hp:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $2900			; $2900 = FT4233HP
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT4233HP, BAUD_TYPE_FTDI_H
.device_id_ftdi_ft2232hp:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $3000			; $3000 = FT2232HP
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT2232HP, BAUD_TYPE_FTDI_H
.device_id_ftdi_ft4232hp:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $3100			; $3100 = FT4232HP
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT4232HP, BAUD_TYPE_FTDI_H
.device_id_ftdi_ft233hp:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $3200			; $3200 = FT233HP
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT233HP, BAUD_TYPE_FTDI_H
.device_id_ftdi_ft232hp:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $3300			; $3300 = FT232HP
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT232HP, BAUD_TYPE_FTDI_H
.device_id_ftdi_ft4232ha:
	db	2
	devchk	srl_device.idvendor, mtEquals, $0403			; idVendor = FTDI
	devchk	srl_device.bcddevice, mtEquals, $3600			; $3600 = FT4232HA
	db	SRL_TYPE_FTDI, SRL_SUBTYPE_FT4232HA, BAUD_TYPE_FTDI_H

.device_id_ch340:
	db	2							; number of conditional checks to perform
	devchk	srl_device.idvendor, mtEquals, $1A86			; paramter to check, match mode (equal, greater than, less than), value to check against
	devchk	srl_device.idproduct, mtEquals, $7523
	db	SRL_TYPE_CH34X, SRL_SUBTYPE_CH340, BAUD_TYPE_CH34X	; device data if matched: type, sub type and baud type
.device_id_cp2102:
	db	2
	devchk	srl_device.idvendor, mtEquals, $10C4
	devchk	srl_device.idproduct, mtEquals, $EA60
	db	SRL_TYPE_CP210X, SRL_SUBTYPE_CP2102, BAUD_TYPE_CP210X

;========================================================================
; Device specific init & baud rate usb control data
;
; Default CDC baud settings
default_cdc_setup:
	db	1							; number of packets to transfer
	setuppkt $21,$20,$0000,$0000,$0007,.linecoding			; set baud rate
.linecoding = $ + 0
	db	$80,$25,0,0,0,0,8

; CH34X baud settings
ch34x_setup:
	db	6							; number of packets to transfer
;	setuppkt $C0,$5F,$0000,$0000,$0002,.buf				; get vendor version
 	setuppkt $40,$A1,$0000,$0000,$0000,null				; serial init
.baudFactor = $ + 4
	setuppkt $40,$9A,$1312,$B282,$0000,null				; baud factor	
.baudfOffset = $ + 4
	setuppkt $40,$9A,$0F2C,$0008,$0000,null				; baud offset
;	setuppkt $C0,$95,$2518,$0000,$0000,.buf
	setuppkt $40,$9A,$2518,$00C3,$0000,null				; parity
	setuppkt $40,$9A,$2727,$0000,$0000,null				; control lines
	setuppkt $40,$A4,$009F,$0000,$0000,null				; modem call
;.buf:	dw 0

; FT232RL baud settings
ft232rl_setup:
	db	1
.baudDivisor = $ + 2
	setuppkt $40,$03,$4138,$0000,$0000,null				; 9600 for FT232RL (divisor, divisor >> 16)

; CP201X baud settings
cp210x_setup:
	db	4
	setuppkt $40,$00,$0001,$0000,$0000,null				; CP210X_IFC_ENABLE
	setuppkt $40,$07,$0303,$0000,$0000,null				; CP210X_SET_MHS (RTS/DTR)
.baudRate = $ + 2
	setuppkt $40,$01,$0180,$0000,$0000,null				; 9600 for CP2102 (0x384000 / baudrate)
	setuppkt $40,$03,$0800,$0000,$0000,null				; CP210X_SET_LINE_CTL ((dataBits << 8) | parity | stopBits)

;========================================================================
; Baud rate data look-up tables
;
; Baud rate table
; Default baud rates: 9600, 19200, 38400, 57600, 115200			; expand to include more baud rates
baud_rate_table:
	db	5							; number of entries in table
	dl	9600,	.baud_rate_table_9600
	dl	19200,	.baud_rate_table_19200
	dl	38400,	.baud_rate_table_38400
	dl	57600,	.baud_rate_table_57600
	dl	115200,	.baud_rate_table_115200
.baud_rate_table_9600:
	db	6							; number of entries in table
	baud	BAUD_TYPE_FTDI_SIO,	$0005,$0000
	baud	BAUD_TYPE_FTDI_AM,	$4138,$0000
	baud	BAUD_TYPE_FTDI_BM,	$4138,$0000
	baud	BAUD_TYPE_FTDI_H,	$04E2,$0002
	baud	BAUD_TYPE_CH34X,	$B282,$0008
	baud	BAUD_TYPE_CP210X,	$0180,$0000
.baud_rate_table_19200:
	db	6
	baud	BAUD_TYPE_FTDI_SIO,	$0006,$0000
	baud	BAUD_TYPE_FTDI_AM,	$809C,$0000
	baud	BAUD_TYPE_FTDI_BM,	$809C,$0000
	baud	BAUD_TYPE_FTDI_H,	$0271,$0002
	baud	BAUD_TYPE_CH34X,	$D982,$0007
	baud	BAUD_TYPE_CP210X,	$00C0,$0000
.baud_rate_table_38400:
	db	6
	baud	BAUD_TYPE_FTDI_SIO,	$0007,$0000
	baud	BAUD_TYPE_FTDI_AM,	$C04E,$0000
	baud	BAUD_TYPE_FTDI_BM,	$C04E,$0000
	baud	BAUD_TYPE_FTDI_H,	$4138,$0000
	baud	BAUD_TYPE_CH34X,	$6483,$0000
	baud	BAUD_TYPE_CP210X,	$0060,$0000
.baud_rate_table_57600:
	db	6
	baud	BAUD_TYPE_FTDI_SIO,	$0008,$0000
	baud	BAUD_TYPE_FTDI_AM,	$0034,$0000
	baud	BAUD_TYPE_FTDI_BM,	$0034,$0000
	baud	BAUD_TYPE_FTDI_H,	$80D0,$0000
	baud	BAUD_TYPE_CH34X,	$9883,$0000
	baud	BAUD_TYPE_CP210X,	$0040,$0000
.baud_rate_table_115200:
	db	6
	baud	BAUD_TYPE_FTDI_SIO,	$0009,$0000
	baud	BAUD_TYPE_FTDI_AM,	$001A,$0000
	baud	BAUD_TYPE_FTDI_BM,	$001A,$0000
	baud	BAUD_TYPE_FTDI_H,	$C068,$0000
	baud	BAUD_TYPE_CH34X,	$CC83,$0000
	baud	BAUD_TYPE_CP210X,	$0020,$0000
