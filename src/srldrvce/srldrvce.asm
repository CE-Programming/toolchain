;-------------------------------------------------------------------------------
include '../include/library.inc'
include '../include/include_library.inc'
;-------------------------------------------------------------------------------

library 'SRLDRVCE', 0

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
; temp
	export	get_device_type_
	export	ring_buf_contig_avail_
	export	ring_buf_has_consecutive_region_
	export	ring_buf_push_
	export	ring_buf_pop_
	export	ring_buf_update_read_
	export	ring_buf_update_write_
	export	set_rate_
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
	prefix#name	name
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
	rx_buf				ring_buf_ctrl
	tx_buf				ring_buf_ctrl
	size := $-.
end struct

virtual at 0
	SRL_TYPE_UNKNOWN		rb 1	; Incompatible or non-serial device
	SRL_TYPE_HOST			rb 1	; Calc is acting as a device
	SRL_TYPE_CDC			rb 1	; CDC device
	SRL_TYPE_FTDI			rb 1	; FTDI device
	SRL_TYPE_PL2303			rb 1	; PL2303 device
end virtual

virtual at 0
	SRL_SUBTYPE_FTDI_UNKNOWN	rb 1
	SRL_SUBTYPE_SIO			rb 1
	SRL_SUBTYPE_FT8U232AM		rb 1
	SRL_SUBTYPE_FT232BM		rb 1
	SRL_SUBTYPE_FT2232C		rb 1
	SRL_SUBTYPE_FT232RL		rb 1
	SRL_SUBTYPE_FTX			rb 1
	SRL_SUBTYPE_FT2232H		rb 1
	SRL_SUBTYPE_FT4232H		rb 1
	SRL_SUBTYPE_FT232H		rb 1
end virtual

virtual at 0
	SRL_SUBTYPE_PL2303_01		rb 1
	SRL_SUBTYPE_PL2303_HX		rb 1
end virtual

SRL_INTERFACE_ANY	:= $FF

virtual at 0
	SRL_SUCCESS			rb 1
	SRL_ERROR_INVALID_PARAM		rb 1
	SRL_ERROR_USB_FAILED		rb 1
	SRL_ERROR_NOT_SUPPORTED		rb 1
	SRL_ERROR_INVALID_DEVICE	rb 1
	SRL_ERROR_INVALID_INTERFACE	rb 1
	SRL_ERROR_NO_MEMORY		rb 1
end virtual

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

struct setuppkt, requestType: ?, request: ?, value: ?, index: ?, length: ?
	label .: 8
	bmRequestType		db requestType
	bRequest		db request
	wValue			dw value
	wIndex			dw index
	wLength			dw length
end struct

struct descriptor
	label .: 2
	bLength			rb 1
	bDescriptorType		rb 1
end struct
struct deviceDescriptor
	label .: 18
	descriptor		descriptor
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
	descriptor		descriptor
	wTotalLength		rw 1
	bNumInterfaces		rb 1
	bConfigurationValue	rb 1
	iConfiguration		rb 1
	bmAttributes		rb 1
	bMaxPower		rb 1
end struct
struct interfaceDescriptor
	label .: 9
	descriptor		descriptor
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
	descriptor		descriptor
	bEndpointAddress	rb 1
	bmAttributes		rb 1
	wMaxPacketSize		rw 1
	bInterval		rb 1
end struct

; enum usb_find_flag
?IS_NONE		:= 0
?IS_DISABLED		:= 1 shl 0
?IS_ENABLED		:= 1 shl 1
?IS_DEVICE		:= 1 shl 2
?IS_HUB			:= 1 shl 3
?IS_ATTACHED		:= 1 shl 4

; enum usb_descriptor_type
virtual at 1
	?DEVICE_DESCRIPTOR			rb 1
	?CONFIGURATION_DESCRIPTOR		rb 1
	?STRING_DESCRIPTOR			rb 1
	?INTERFACE_DESCRIPTOR			rb 1
	?ENDPOINT_DESCRIPTOR			rb 1
end virtual

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
	ld	hl,0
	ld	l,a
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
	call	ti.os.GetSystemStats
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
.configuration1 emit $3e: $09023e00020100c0320904000001020200000524000110042402000524060001070582030800ff09040100020a0000000705040240000107058302400001 bswap $3e
.langids dw $0304, $0409
.strings dl .string1
.model dl .string84
.serial dl .stringserialnum
.string1 dw $033E, 'T','e','x','a','s',' ','I','n','s','t','r','u','m','e','n','t','s',' ','I','n','c','o','r','p','o','r','a','t','e','d'
.string83 dw $0322, 'T','I','-','8','3',' ','P','r','e','m','i','u','m',' ','C','E'
.string84 dw $031C, 'T','I','-','8','4',' ','P','l','u','s',' ','C','E'
.stringserialnum dw $0316, '0','0','0','0','0','0','0','0','0','0'


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

; check for CDC ACM device
	ld	hl,(xsrl_device.rx_buf.buf_start)
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
	jq	nz,.find_int_loop

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
	ld	a,SRL_TYPE_CDC
	ld	(xsrl_device.type),a
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
	or	a,a
	jq	z,.invalid_device
	dec	a					; type == HOST
	jq	z,.success
	dec	a					; type == CDC
	jq	z,set_rate_cdc
	dec	a					; type == FTDI
	jq	z,set_rate_ftdi
	dec	a					; type == PL2303
	jq	z,set_rate_cdc
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
	ld	(.linecoding),hl
	ld	bc,0
	push	bc	; transferred
	ld	bc,50
	push	bc	; num retries
	ld	bc,.linecoding
	push	bc	; data
	ld	bc,.setup
	push	bc	; setup

	ld	bc,0
	push	bc	; ep addr
	ld	bc,(xsrl_device.dev)
	push	bc	; device
	call	usb_GetDeviceEndpoint
	pop	bc,bc

	push	hl	; endpoint
	call	usb_ControlTransfer
	pop	bc,bc,bc,bc,bc
	ld	a,l
	or	a,a
	ret	z
	ld	l,SRL_ERROR_USB_FAILED
	ret
.setup	setuppkt	$21,$20,$0000,$0000,$0007
.linecoding:
	db	$80,$25,0,0,0,0,8


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

; Update a ring buffer after it's been DMA'd into
; Inputs:
;  ix: ring_buf_ctrl struct
;  bc: Number of bytes written
;  a: Size of minimum consecutive region
ring_buf_update_read:
	ld	hl,(xring_buf_ctrl.data_end)
	add	hl,bc
	ld	(xring_buf_ctrl.data_end),hl
	ex	de,hl					; de = data_end
	ld	hl,(xring_buf_ctrl.data_break)
	compare_hl_zero
	ret	nz
	ld	hl,(xring_buf_ctrl.buf_end)
	or	a,a
	sbc	hl,de
	ld	bc,0
	ld	c,a
	or	a,a
	sbc	hl,bc
	ret	nc					; ret if >= region
	ld	(xring_buf_ctrl.data_break),de		; data_break = data_end
	ld	de,(xring_buf_ctrl.buf_start)
	ld	(xring_buf_ctrl.data_end),de
	ret

; Update a ring buffer after it's been DMA'd from
; Inputs:
;  ix: ring_buf_ctrl struct
;  bc: Number of bytes written
ring_buf_update_write:
	ld	hl,(xring_buf_ctrl.data_start)
	add	hl,bc
	ld	(xring_buf_ctrl.data_start),hl
	ld	bc,(xring_buf_ctrl.data_break)
	or	a,a
	sbc	hl,bc
	ret	nz
	ld	(xring_buf_ctrl.data_break),hl		; hl = 0
	ld	hl,(xring_buf_ctrl.buf_start)
	ld	(xring_buf_ctrl.data_start),hl
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
	ld	a,64
	lea	ix,xsrl_device.rx_buf
	call	ring_buf_update_read
	call	start_read
	pop	ix
	xor	a,a
	ret

.no_device:
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
	call	ring_buf_update_write
	call	start_write
	pop	ix
	xor	a,a
	ret

.no_device:
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
	lea	ix,ix - srl_device.rx_buf
	jq	c,.error

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
	lea	ix,ix - srl_device.tx_buf
	compare_hl_zero
	jq	z,.error
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
.error:
	xor	a,a
	ld	(xsrl_device.tx_buf.dma_active),a
	ret

;temp
get_device_type_:
	push	ix
	pop	bc,de,ix
	push	ix,de,bc
	call	get_device_type
	pop	ix
	ret
ring_buf_contig_avail_:
	push	ix
	pop	bc,de,ix
	push	ix,de,bc
	call	ring_buf_contig_avail
	pop	ix
	ret
ring_buf_has_consecutive_region_:
	push	ix
	ld	ix,3
	add	ix,sp
	ld	a,(ix+6)
	ld	ix,(ix+3)
	call	ring_buf_has_consecutive_region
	ld	a,1
	sbc	a,0
	pop	ix
	ret
ring_buf_push_:
	push	ix
	ld	ix,3
	add	ix,sp
	ld	hl,(ix+6)
	ld	bc,(ix+9)
	ld	ix,(ix+3)
	call	ring_buf_push
	pop	ix
	ret
ring_buf_pop_:
	push	ix
	ld	ix,3
	add	ix,sp
	ld	hl,(ix+6)
	ld	bc,(ix+9)
	ld	ix,(ix+3)
	call	ring_buf_pop
	pop	ix
	ret
ring_buf_update_read_:
	push	ix
	ld	ix,3
	add	ix,sp
	ld	bc,(ix+6)
	ld	a,(ix+9)
	ld	ix,(ix+3)
	call	ring_buf_update_read
	pop	ix
	ret
ring_buf_update_write_:
	push	ix
	ld	ix,3
	add	ix,sp
	ld	bc,(ix+6)
	ld	ix,(ix+3)
	call	ring_buf_update_write
	pop	ix
	ret

set_rate_:
	push	ix
	ld	ix,3
	add	ix,sp
	ld	hl,(ix+6)
	ld	ix,(ix+3)
	call	set_rate
	pop	ix
	ret
