;-------------------------------------------------------------------------------
include '../include/library.inc'
include '../include/include_library.inc'
;-------------------------------------------------------------------------------

library 'SRLDRVCE', 0

;-------------------------------------------------------------------------------
; Dependencies
;-------------------------------------------------------------------------------
include_library '../usbdrvce/usbdrvce.asm'

;-------------------------------------------------------------------------------
; v0 functions (not final, subject to change!)
;-------------------------------------------------------------------------------
	export srl_Init
	export srl_SetRate
	export srl_Available
	export srl_Read
	export srl_Write
	export srl_Read_Blocking
	export srl_Write_Blocking
	export srl_GetCDCStandardDescriptors
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

struct tmp_data
	local size
	label .: size
	length		rl 1
	descriptor	rb 18
	size := $-.
end struct

struct srl_Device
	local size
	label .: size
	dev		rl 1		; USB device
	?in		rl 1		; USB bulk in endpoint
	?out		rl 1		; USB bulk out endpoint
	type		rb 1		; Device type
	subType		rb 1		; Device sub-type
	readBuf		rl 1		; Pointer to the read buffer
	readBufSize	rl 1		; Size of the read buffer
	readBufStart	rl 1		; First byte with data in the read buffer
	readBufEnd	rl 1		; Last byte with data in the read buffer
	readBufBreak	rl 1		; Last byte before the buffer "loops"
	readBufActive	rb 1		; Whether data is being read into the read buffer
	stopRead	rb 1		; Set when waiting for the read to stop
	writeBuf	rl 1		; Pointer to the write buffer
	writeBufSize	rl 1		; Size of the write buffer
	writeBufStart	rl 1		; First byte with data in the write buffer
	writeBufEnd	rl 1		; Last byte with data in the write buffer
	size := $-.
end struct

; enum srl_DeviceType
virtual at 0
	SRL_UNKNOWN	rb 1		; Incompatible or non-serial device
	SRL_HOST	rb 1		; Calc is acting as a device
	SRL_CDC		rb 1		; CDC device
	SRL_FTDI	rb 1		; FTDI device
end virtual

; enum srl_SubType_FTDI
virtual at 0
	FTDI_UNKNOWN	rb 1
	SIO		rb 1
	FT8U232AM	rb 1
	FT232BM		rb 1
	FT2232C		rb 1
	FT232RL		rb 1
	FTX		rb 1
	FT2232H		rb 1
	FT4232H		rb 1
	FT232H		rb 1
end virtual

SRL_INTERFACE_ANY := $FF

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

; enum usb_transfer_direction
virtual at 0
	?HOST_TO_DEVICE				rb 1 shl 7
	?DEVICE_TO_HOST				rb 1 shl 7
end virtual

virtual at 0
	USB_SUCCESS				rb 1
	USB_IGNORE				rb 1
	USB_ERROR_SYSTEM			rb 1
	USB_ERROR_INVALID_PARAM			rb 1
	USB_ERROR_SCHEDULE_FULL			rb 1
	USB_ERROR_NO_DEVICE			rb 1
	USB_ERROR_NO_MEMORY			rb 1
	USB_ERROR_NOT_SUPPORTED			rb 1
	USB_ERROR_TIMEOUT			rb 1
	USB_ERROR_FAILED			rb 1
end virtual

virtual at 0
	SRL_SUCCESS				rb 1
	SRL_IGNORE				rb 1
	SRL_ERROR_SYSTEM			rb 1
	SRL_ERROR_INVALID_PARAM			rb 1
	SRL_ERROR_SCHEDULE_FULL			rb 1
	SRL_ERROR_NO_DEVICE			rb 1
	SRL_ERROR_NO_MEMORY			rb 1
	SRL_ERROR_NOT_SUPPORTED			rb 1
	SRL_ERROR_TIMEOUT			rb 1
	SRL_ERROR_FAILED			rb 1
	SRL_ERROR_INVALID_INTERFACE		rb 1
end virtual

; enum usb_descriptor_type
virtual at 1
	?DEVICE_DESCRIPTOR			rb 1
	?CONFIGURATION_DESCRIPTOR		rb 1
	?STRING_DESCRIPTOR			rb 1
	?INTERFACE_DESCRIPTOR			rb 1
	?ENDPOINT_DESCRIPTOR			rb 1
end virtual

; enum usb_transfer_type
virtual at 0
	?CONTROL_TRANSFER			rb 1
	?ISOCHRONOUS_TRANSFER			rb 1
	?BULK_TRANSFER				rb 1
	?INTERRUPT_TRANSFER			rb 1
end virtual

virtual at 0
  USB_IS_DISABLED				rb 1
  USB_IS_ENABLED				rb 1
  USB_IS_DEVICES				rb 1
  USB_IS_HUBS					rb 1
end virtual

;-------------------------------------------------------------------------------
;srl_error_t srl_Init(srl_device_t *srl, usb_device_t dev, void *buf, size_t size, uint8_t interface);
srl_Init:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 3)

	ld	hl,(iy + 12)			; check if buffer is large enough
	ld	de,128
	compare_hl_de
	ld	a,SRL_ERROR_NO_MEMORY
	jq	c,.exit

	ld	hl,(iy + 6)			; usb device
	compare_hl_zero
	jq	z,.err_nd
	ex	hl,de
	ld	hl,(iy + 3)
	ld	(hl),de

	call	usb_GetRole			; check if calc is acting as device
	or	a,a
	jq	z,.host

	ld	a,SRL_HOST			; calc is acting as device
	ld	(xsrl_Device.type),a
	ld	a,$83				; set endpoints
	ld	(.epIn),a
	ld	a,$04
	ld	(.epOut),a
	jq	.getEndpoints

.host:
	push	iy
	ld	bc,(xsrl_Device.dev)
	push	bc
	call	usb_GetDeviceFlags		; check if device is enabled
	pop	bc
	bit	USB_IS_ENABLED,l
	jq	nz,.enabled

	ld	bc,(xsrl_Device.dev)
	push	bc				; enable device
	call	usb_ResetDevice
	pop	bc

	call	usb_WaitForEvents

.enabled:					; get descriptor
	ld	bc,tmp.length			; storage for size of descriptor
	push	bc
	ld	bc,18				; size of device descriptor
	push	bc
	ld	bc,tmp.descriptor		; storage for descriptor
	push	bc
	ld	bc,0
	push	bc
	inc	bc				; USB_DEVICE_DESCRIPTOR = 1
	push	bc
	ld	bc,(xsrl_Device.dev)
	push	bc
	call	usb_GetDescriptor
	pop	bc,bc,bc,bc,bc,bc,iy
	compare_hl_zero
	jq	nz,.exit			; return if error
	ld	de,18
	ld	hl,(tmp.length)
	compare_hl_de				; ensure enough bytes were fetched
	jq	nz,.err_nd

	push	iy
	ld	bc,.configNum			; get current configuration number
	push	bc
	ld	bc,(xsrl_Device.dev)
	push	bc
	call	usb_GetConfiguration
	pop	bc,bc,iy

	ld	a,(.configNum)
	or	a,a
	ld	(.prevConfig),a
	jr	nz,.configSet
	ld	a,1
.configSet:
	ld	(.configNum),a

	push	iy
	ld	bc,0				; get config length
	.configNum = $-3
	dec	bc
	push	bc
	ld	bc,(xsrl_Device.dev)
	push	bc
	call	usb_GetConfigurationDescriptorTotalLength
	pop	bc
	pop	bc
	ld	(.configSize),hl

	pop	iy

	ld	de,(iy + 12)			; error if not enough space
	ex	hl,de
	compare_hl_de
	ld	a,SRL_ERROR_NO_MEMORY
	jq	c,.exit

	push	iy				; get config into buffer
	ld	bc,tmp.length
	push	bc
	push	hl				; descriptor length
	ld	bc,(iy + 9)
	push	bc
	ld	bc,(.configNum)
	dec	bc
	push	bc
	ld	bc,CONFIGURATION_DESCRIPTOR
	push	bc
	ld	bc,(xsrl_Device.dev)
	push	bc
	call	usb_GetDescriptor
	pop	de,hl,hl,bc,hl,hl,iy

	ld	hl,tmp.descriptor + deviceDescriptor.idVendor		; check if device is an FTDI
	ld	a,(hl)
	cp	a,$03				; check if idVendor is $0403
	jq	nz,.nonFTDI
	inc	hl
	ld	a,(hl)
	cp	a,$04
	jq	nz,.nonFTDI

	ld	a,SRL_FTDI			; set device type
	ld	(xsrl_Device.type),a

	ld	a,(iy + 15)			; if interface == -1, interface = 0
	inc	a
	jq	nz,.specificInterface
	ld	(iy + 15),a
.specificInterface:

	ld	hl,configurationDescriptor.bNumInterfaces		; check if device has multiple interfaces
	ld	de,(iy + 9)
	add	hl,de
	ld	a,(hl)
	dec	a
	ld	hl,(tmp.descriptor + deviceDescriptor.bcdDevice)	; get device version in de
	ex.s	hl,de
	jq	z,.singleInterface

	ld	b,(iy + 15)			; error if interface >= nNumInterfaces
	cp	a,b
	ld	a,SRL_ERROR_INVALID_INTERFACE
	jq	c,.exit

	sla	b				; multiply interface by 2
	ld	a,$81				; add $81 to get in endpoint
	add	a,b
	ld	(.epIn),a
	xor	a,a				; add $02 to get out endpoint
	inc	a
	inc	a
	add	a,b
	ld	(.epOut),a

	xor	a,a
	ld	hl,$0800			; check each version number for multi-interface devices
	sbc	hl,de
	ld	a,FT4232H
	jq	z,.ftdiSubtypeSet
	ld	hl,$0700
	sbc	hl,de
	ld	a,FT2232H
	jq	z,.ftdiSubtypeSet
	ld	a,FT2232C			; default to FT2232C
	jq	.ftdiSubtypeSet

.singleInterface:
	ld	a,(iy + 15)			; if interface is non-zero, error
	or	a,a
	ld	a,SRL_ERROR_INVALID_INTERFACE
	jq	nz,.exit

	ld	a,$81
	ld	(.epOut),a
	ld	a,$02
	ld	(.epIn),a

	scf
	ld	hl,$0200
	sbc	hl,de
	ld	a,SIO
	jq	nc,.ftdiSubtypeSet
	ld	hl,$0400
	sbc	hl,de
	ld	a,FT8U232AM
	jq	nc,.ftdiSubtypeSet
	ld	hl,$0600
	sbc	hl,de
	ld	a,FT232BM
	jq	nc,.ftdiSubtypeSet
	ld	hl,$0900
	sbc	hl,de
	ld	a,FT232RL
	jq	nc,.ftdiSubtypeSet
	ld	hl,$1000
	sbc	hl,de
	ld	a,FT232H
	jq	nc,.ftdiSubtypeSet
	ld	a,FTX
	jq	.ftdiSubtypeSet

.ftdiSubtypeSet:
	ld	(xsrl_Device.subType),a
	jq	.shared

.nonFTDI:
	ld	de,(iy + 9)			; address of configuration descriptor
	ld	hl,(.configSize)
	add	hl,de
	ex	hl,de

	xor	a,a				; reset endpoints to zero
	ld	(.epIn),a
	ld	(.epOut),a

	ld	a,(iy + 15)			; check for CDC interface
	cp	a,SRL_INTERFACE_ANY
	jq	z,.findAnyInterface

.findSpecificInterface:
	ld	bc,.loopFindSpecificInterface
	ld	(.retVect),bc
.loopFindSpecificInterface:
	inc	hl
	ld	a,(hl)
	dec	hl
	cp	a,INTERFACE_DESCRIPTOR		; check if interface descriptor
	jq	nz,.nextDescriptor
	inc	hl
	inc	hl
	ld	a,(hl)
	cp	a,(iy + 15)
	dec	hl
	dec	hl
	jq	nz,.nextDescriptor
	ld	bc,5
	add	hl,bc
	ld	a,(hl)
	sbc	hl,bc
	cp	a,10
	ld	a,SRL_ERROR_INVALID_INTERFACE
	jq	nz,.exit
	jq	.findEndpoints

.findAnyInterface:
	ld	bc,.loopFindAnyInterface
	ld	(.retVect),bc
.loopFindAnyInterface:
	inc	hl
	ld	a,(hl)
	dec	hl
	cp	a,INTERFACE_DESCRIPTOR		; check if interface descriptor
	jq	nz,.nextDescriptor
	ld	bc,5
	add	hl,bc
	ld	a,(hl)
	sbc	hl,bc
	cp	a,10
	jq	nz,.nextDescriptor
	jq	.findEndpoints

.findEndpoints:
	ld	bc,.loopFindEndpoints
	ld	(.retVect),bc
	jq	.nextDescriptor
.loopFindEndpoints:
	inc	hl
	ld	a,(hl)
	cp	a,INTERFACE_DESCRIPTOR
	jq	z,.cdcCheckDone
	cp	a,ENDPOINT_DESCRIPTOR
	jq	nz,.nextDescriptor
	inc	hl
	ld	a,(hl)
	dec	hl
	dec	hl
	bit	7,a				; check endpoint direction
	jq	z,.foundEpIn
	ld	(.epOut),a
	jq	.nextDescriptor
.foundEpIn:
	ld	(.epIn),a
	jq	.nextDescriptor

.nextDescriptor:
	ld	bc,0
	ld	c,(hl)
	add	hl,bc
	compare_hl_de
	jq	nc,.cdcCheckDone
	jq	.err_nd
	.retVect = $-3

.cdcCheckDone:
	ld	a,(.epIn)			; check if any endpoints were found
	or	a,a
	jq	nz,.cdcFound
	ld	a,(.epOut)
	or	a,a
	jq	z,.err_nd
	jq	.cdcFound

.cdcFound:
	ld	a,SRL_CDC
	ld	(xsrl_Device.type),a

.shared:
	ld	a,0				; check if configuration is already set
	.prevConfig = $-1
	or	a,a
	jr	nz,.getEndpoints

	push	iy

	ld	hl,0
	.configSize = $-3
	push	hl
	ld	bc,(iy + 9)
	push	bc
	ld	bc,(xsrl_Device.dev)
	push	bc
	call	usb_SetConfiguration
	pop	de,bc,bc

	pop	iy				; needed to keep stack balanced

.getEndpoints:
	push	iy
	ld	bc,$83				; get endpoint
	.epOut = $-3
	push	bc
	ld	de,(xsrl_Device.dev)
	push	de
	call	usb_GetDeviceEndpoint
	pop	de
	pop	bc
	ld	(xsrl_Device.in),hl
	dec	hl
	jq	c,.err_nd

	ld	bc,$04				; get endpoint
	.epIn = $-3
	push	bc
	ld	de,(xsrl_Device.dev)
	push	de
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc
	ld	(xsrl_Device.out),hl
	dec	hl
	jq	c,.err_nd
	pop	iy

.deviceConfigured:
	ld	hl,(iy + 9)			; set read buffer pointer, start, and end
	ld	(xsrl_Device.readBuf),hl
	ld	(xsrl_Device.readBufStart),hl
	ld	(xsrl_Device.readBufEnd),hl
	ld	de,(iy + 12)			; set buffer sizes to size/2
	ld	(xsrl_Device.readBufSize),de
	srl	(xsrl_Device.readBufSize)
	rr	(xsrl_Device.readBufSize+1)
	rr	(xsrl_Device.readBufSize+2)
	ld	de,(xsrl_Device.readBufSize)
	ld	(xsrl_Device.writeBufSize),de
	xor	a,a				; set write buffer pointer, start, and end
	adc	hl,de
	ld	(xsrl_Device.writeBuf),hl
	ld	(xsrl_Device.writeBufStart),hl
	ld	(xsrl_Device.writeBufEnd),hl
	ld	hl,0				; set read buffer break to 0
	ld	(xsrl_Device.readBufBreak),hl
	xor	a,a				; unstop read
	ld	(xsrl_Device.stopRead),a
	ld	(xsrl_Device.readBufActive),a	; mark read buffer as inactive
	ld	a,SRL_SUCCESS
.exit:
	pop	ix
	ret
.err_nd:
	ld	a,SRL_ERROR_NO_DEVICE
	jq	.exit

;-------------------------------------------------------------------------------
;srl_error_t srl_SetRate(srl_device_t *srl, uint24_t rate);
srl_SetRate:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 3)
	ld	a,SRL_UNKNOWN			; check device type
	cp	a,(xsrl_Device.type)
	jq	z,.exit
	inc	a				; SRL_HOST
	cp	a,(xsrl_Device.type)
	jq	z,.exit
	inc	a
	cp	a,(xsrl_Device.type)
	jq	z,.cdc
	inc	a
	cp	a,(xsrl_Device.type)
	jq	z,.ftdi
	jq	.exit
.cdc:						; if a CDC device:
	ld	hl,(iy + 6)			; change the rate of the default line coding
	ld	(defaultlinecoding),hl
	ld	de,defaultlinecoding
	ld	hl,setup.setlinecoding
	jq	.sendctrl
.ftdi:						; if a FTDI device:
	ld	a,(xsrl_Device.readBufActive)	; check if read needs to be stopped
	or	a,a
	jq	z,.noStop
	ld	(xsrl_Device.stopRead),a	; stop read
.loop:
	call	usb_WaitForEvents		; wait for read to stop
	ld	a,(xsrl_Device.readBufActive)
	jq	nz,.loop
.noStop:
	ld	a,(xsrl_Device.subType)		; check device type
	cp	a,SIO
	jq	nz,.nonSIO

	ld	de,(iy + 6)			; get SIO data
	ld	c,0
repeat 10
if %=1
	ld	hl,300
else if %=9
	ld	hl,57600
else
	add	hl,hl
end if
	compare_hl_de
	jq	z,.sioPrepTransfer
	inc	bc
end repeat
	
	ld	l,SRL_ERROR_NOT_SUPPORTED	; invalid SIO baud rate
	jq	.exit

.sioPrepTransfer:
	ld	a,c
	ld	(setup.ftdisetrate + setuppkt.wValue),a
	xor	a,a
	ld	(setup.ftdisetrate + setuppkt.wValue + 1),a
	jq	.sendFTDICtrl

.nonSIO:
	xor	a,a
	ld	(.highSpeed),a
	ld	bc,1200				; high speed is set for FT*232H if baud > 1200
	ld	hl,(iy + 6)			; hl = baud rate
	sbc	hl,bc
	add	hl,bc
	jq	c,.lowSpeed
	ld	a,(xsrl_Device.subType)
	cp	a,FT2232H
	jq	c,.lowSpeed

	ld	a,1				; high-speed specific stuff
	ld	(.highSpeed),a
	xor	a,a
	add	hl,hl				; multiply baud by 8
	rl	a
	add	hl,hl
	rl	a
	push	hl
	pop	bc				; half of baud rate
	ld	d,a
	add	hl,hl
	rl	a
	push	hl,af

	ld	e,1200000000 shr 24		; base = 120000000
	ld	hl,1200000000 and $FFFFFF

	jq	.speedIndep

.lowSpeed:
	xor	a,a
	push	hl
	pop	bc				; half of divisor
	ld	d,a
	add	hl,hl				; double baud rate
	rl	a
	push	hl,af

	ld	e,48000000 shr 24		; base = 48000000
	ld	hl,48000000 and $FFFFFF

	; divide base by baud * 2, round to nearest integer
.speedIndep:
	add	hl,bc				; add half of divisor so that result is rounded
	ld	a,e
	adc	a,d
	ld	e,a

	pop	af,bc

	call	__ldivu				; euhl / aubc -> euhl

	ld	bc,.bmNums

	ld	a,(xsrl_Device.subType)
	cp	a,FT8U232AM
	jq	nz,.nonAM
	

	ld	bc,.amNums			; device is an AM
	ld	a,l
	and	a,$07
	cp	a,$07
	jq	nz,.nonAM			; if FT232AM and last 3 bits are set, increment result
	xor	a,a
	inc	hl
	adc	a,e
	ld	e,a

.nonAM:
	ld	a,e
	ld	(setup.ftdisetrate + setuppkt.wIndex + 1),a
	ld	(setup.ftdisetrate + setuppkt.wValue),hl
	ld	a,l
	and	a,$07				; div3 & 7

	ld	e,3
.shiftLoop:
	ld	hl,setup.ftdisetrate + setuppkt.wIndex + 1
	rr	(hl)
	dec	hl
	rr	(hl)
	dec	hl
	rr	(hl)
	dec	hl
	rr	(hl)
	dec	e
	jq	nz,.shiftLoop			; div = div3 >> 3

	ld	hl,0
	ld	l,a
	add	hl,bc
	ld	a,(hl)				; divnums[div3 & 7]
	sla	a

	ld	hl,setup.ftdisetrate + setuppkt.wValue + 1
	jq	nc,.noExtraBit

	inc	hl				; set 17th bit, in index field
	set	0,(hl)
	dec	hl

.noExtraBit:
	or	a,(hl)
	ld	(hl),a				; div |= divnums[div3 & 7] << 14
	
	dec	hl
	ld	a,(hl)
	dec	a
	jq	nz,.noSpecialCase
	inc	hl
	ld	hl,(hl)				; check if $00000001
	compare_hl_zero
	jq	nz,.divNonZero
	xor	a,a
	ld	(setup.ftdisetrate + setuppkt.wIndex),a
	jq	.noSpecialCase
.divNonZero:
	ld	de,$40				; check if $00004001
	compare_hl_de
	jq	nz,.noSpecialCase
	ld	a,(xsrl_Device.subType)		; if AM ignore this
	cp	a,FT8U232AM
	jq	z,.noSpecialCase
	ld	a,1
	ld	(setup.ftdisetrate + setuppkt.wIndex + 1),a
.noSpecialCase:
	ld	a,0				; check if high speed device
	.highSpeed = $-1
	or	a,a
	jq	z,.sendFTDICtrl

	ld	hl,setup.ftdisetrate + setuppkt.wIndex
	set	1,(hl)				; for high speed div |= 0x00020000;

.sendFTDICtrl:
	ld	hl,setup.ftdisetrate
	jq	.sendctrl

.sendctrl:	;de: data, hl: request
	ld	bc,0				; don't need transfer length
	push	bc
	ld	bc,50				; number of retries
	push	bc
	push	de
	push	hl
	ld	bc,0				; get endpoint
	push	bc
	ld	hl,(iy + 3)			; get usb_device_t
	ld	bc,(hl)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc
	push	hl
	call	usb_ControlTransfer		; send control request
	pop	bc,bc,bc,bc,bc
	ld	a,(xsrl_Device.readBufActive)	; check if read needs to be started
	or	a,a
	call	z,srl_StartAsyncRead
	jq	.exit				; return error, if any
.exit:
	ld	a,l
	pop	ix
	ret

.amNums:
	db	0 shl 5, 3 shl 5, 0 shl 5, 0 shl 5, 1 shl 5, 1 shl 5, 1 shl 5
.bmNums:
	db	0 shl 5, 3 shl 5, 2 shl 5, 4 shl 5, 1 shl 5, 5 shl 5, 6 shl 5, 7 shl 5

;-------------------------------------------------------------------------------
;size_t srl_Available(srl_device_t *srl);
srl_Available:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 3)
	ld	hl,(xsrl_Device.readBufBreak)	; if readBufBreak == 0
	compare_hl_zero
	jq	nz,.break
	jq	.nobreak
.nobreak:
	ld	hl,(xsrl_Device.readBufEnd)	; readBufEnd - readBufStart
	ld	de,(xsrl_Device.readBufStart)
	sbc	hl,de
	jq	.exit
.break:
	ld	hl,(xsrl_Device.readBufBreak)	; (readBufBreak - readBufStart) + (readBufEnd - readBuf)
	ld	de,(xsrl_Device.readBufEnd)
	add	hl,de
	ld	de,(xsrl_Device.readBuf)
	sbc	hl,de
	ld	de,(xsrl_Device.readBufStart)
	sbc	hl,de
	jq	.exit
.exit:
	pop	ix
	ret

;-------------------------------------------------------------------------------
;size_t srl_Read(srl_device_t *srl, void *buffer, size_t length);
srl_Read:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 3)
	ld	de,(iy + 9)			; set remaining to length
	ld	hl,0
	xor	a,a
	sbc	hl,de
	jq	z,.exit
.rec:
	ld	hl,(xsrl_Device.readBufStart)	; check if buffer has *any* data
	ld	bc,(xsrl_Device.readBufEnd)
	xor	a,a
	sbc	hl,bc				
	jq	z,.sched
	ld	hl,(xsrl_Device.readBufBreak)	; if readBufBreak
	compare_hl_zero
	jq	z,.nobreak
	jq	.break
.break:
	ld	hl,(xsrl_Device.readBufStart)	; if readBufStart + remaining < readBufBreak:
	add	hl,de
	ld	bc,(xsrl_Device.readBufBreak)
	sbc	hl,bc
	jq	c,.space

	ld	bc,(xsrl_Device.readBufStart)
	ld	hl,(xsrl_Device.readBufBreak)
	sbc	hl,bc
	push	hl
	pop	bc
	ld	hl,(xsrl_Device.readBufStart)
	push	bc
	push	de
	ld	de,(iy + 6)			; copy readBufBreak - readBufStart bytes to buffer
	ldir
	ld	hl,0				; set readBufBreak to 0
	ld	(xsrl_Device.readBufBreak),hl
	ld	hl,(xsrl_Device.readBuf)	; set readBufStart to readBuf
	ld	(xsrl_Device.readBufStart),hl
	pop	hl				; remaining -= readBufBreak - readBufStart
	pop	bc
	sbc	hl,bc
	ex	hl,de
	jq	.rec				; read remaining data
.nobreak:
	ld	hl,(xsrl_Device.readBufStart)	; if readBufStart + remaining < readBufEnd:
	add	hl,de
	ld	bc,(xsrl_Device.readBufEnd)
	sbc	hl,bc
	jq	nc,.nospace
	jq	.space
.space:
	push	de				; copy remaining bytes to buffer + length - remaining
	ld	hl,(iy + 6)
	ld	bc,(iy + 9)
	add	hl,bc
	sbc	hl,de
	ex	hl,de
	ld	hl,(xsrl_Device.readBufStart)
	pop	bc
	push	bc
	ldir
	pop	de
	ld	hl,(xsrl_Device.readBufStart)	; readBufStart += remaining
	add	hl,de
	ld	(xsrl_Device.readBufStart),hl
	ld	de,0				; remaining = 0
	jq	.sched
.nospace:
	push	de				; copy readBufEnd - readBufStart bytes to buffer + length - remaining
	ld	hl,(iy + 6)
	ld	bc,(iy + 9)
	add	hl,bc
	sbc	hl,de
	ex	hl,de
	ld	hl,(xsrl_Device.readBufEnd)
	ld	bc,(xsrl_Device.readBufStart)
	sbc	hl,bc
	push	hl
	pop	bc
	ld	hl,(xsrl_Device.readBufStart)
	ldir
	pop	hl
	ld	bc,(xsrl_Device.readBufStart)	; remaining -= readBufEnd - readBufStart
	add	hl,bc
	ld	bc,(xsrl_Device.readBufEnd)
	sbc	hl,bc
	ex	hl,de
	ld	(xsrl_Device.readBufStart),bc	; set readBufStart to readBufEnd
	jq	.sched
.sched:
	ld	a,(xsrl_Device.readBufActive)	; if read is inactive
	or	a,a
	push	de
	call	z,srl_StartAsyncRead		; attempt to schedule async transfer
	pop	de
	xor	a,a				; get number of bytes transferred
	ld	hl,(iy + 9)
	sbc	hl,de
.exit:
	pop	ix
	ret

;-------------------------------------------------------------------------------
;size_t srl_Write(srl_device_t *srl, const void *buffer, size_t length);
srl_Write:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 3)
	ld	de,0				; transferred = 0
	xor	a,a
	ld	bc,(xsrl_Device.writeBufStart)	; writeBufStart == writeBufEnd
	ld	hl,(xsrl_Device.writeBufEnd)
	sbc	hl,bc
	push	af
	jq	c,.wrap				; if writeBufStart > writeBufEnd
	jq	.nowrap
.nowrap:
	xor	a,a
	ld	hl,(xsrl_Device.writeBufEnd)	; if writeBufEnd + length < writeBuf + writeBufSize
	ld	bc,(iy + 9)
	add	hl,bc
	ld	bc,(xsrl_Device.writeBuf)
	sbc	hl,bc
	ld	bc,(xsrl_Device.writeBufSize)
	sbc	hl,bc
	jq	c,.space

	ld	hl,(xsrl_Device.writeBuf)	; transferred = writeBuf + writeBufSize - writeBufEnd
	ld	bc,(xsrl_Device.writeBufSize)
	add	hl,bc
	ld	bc,(xsrl_Device.writeBufEnd)
	sbc	hl,bc
	push	hl
	push	hl
	pop	bc

	ld	hl,(iy + 6)			; copy transferred bytes from buffer to writeBufEnd
	ld	de,(xsrl_Device.writeBufEnd)
	ldir
	ld	hl,(xsrl_Device.writeBuf)	; writeBufEnd = writeBuf
	ld	(xsrl_Device.writeBufEnd),hl
	pop	de				; transferred = writeBuf + writeBufSize - writeBufEnd
	jq	.wrap
.wrap:
	ld	hl,(xsrl_Device.writeBufEnd)	; if writeBufEnd + length - transferred < writeBufStart:
	ld	bc,(iy + 9)
	add	hl,bc
	sbc	hl,de
	ld	bc,(xsrl_Device.writeBufStart)
	sbc	hl,bc
	jq	c,.space

	scf					; copy writeBufStart - writeBufEnd - 1 bytes from buffer + transferred to writeBufEnd
	ld	hl,(xsrl_Device.writeBufStart)
	ld	bc,(xsrl_Device.writeBufEnd)
	sbc	hl,bc
	push	hl
	push	hl
	pop	bc
	push	de
	ld	hl,(iy + 6)
	add	hl,de
	ld	de,(xsrl_Device.writeBufEnd)
	ldir
	pop	de
	pop	hl				; transferred += writeBufStart - writeBufEnd - 1
	add	hl,de
	ex	de,hl

	ld	hl,(xsrl_Device.writeBufStart)
	dec	hl
	ld	(xsrl_Device.writeBufEnd),hl	; writeBufEnd = writeBufStart - 1
	jq	.exit
.space:
	xor	a,a
	ld	hl,(iy + 9)			; copy length - transferred bytes from buffer + transferred to writeBufEnd
	sbc	hl,de
	push	hl
	pop	bc				; length - transferred
	push	bc
	ld	hl,(iy + 6)
	add	hl,de
	ld	de,(xsrl_Device.writeBufEnd)
	ldir
	pop	bc
	ld	hl,(xsrl_Device.writeBufEnd)	; writeBufEnd += length - transferred
	add	hl,bc
	ld	(xsrl_Device.writeBufEnd),hl
	ld	de,(iy + 9)			; transferred = length
.exit:
	ex	hl,de
	pop	af
	push	hl
	call	z,srl_StartAsyncWrite		; attempt to schedule async transfer if buffer was empty
	pop	hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
;size_t srl_Read_Blocking(srl_device_t *srl, void *buffer, size_t length, uint24_t timeout);
srl_Read_Blocking:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 3)
	call	usb_GetFrameNumber
	ex	hl,de
	ld	bc,0				; total
.loop:
	ld	a,(iy + 12)
	or	a,a
	jq	z,.noTimeout
	push	de
	call	usb_GetFrameNumber
	pop	de
	xor	a,a
	sbc	hl,de				; frame_new - frame_init - timeout
	push	bc
	ld	bc,(iy + 12)
	sbc	hl,bc
	pop	bc
	jq	nc,.exit
.noTimeout:
	push	de
	push	iy
	push	bc
	xor	a,a
	ld	hl,(iy + 9)			; length - total
	sbc	hl,bc
	push	hl
	ld	hl,(iy + 6)			; buffer + total
	add	hl,bc
	push	hl
	push	ix
	call	srl_Read			; srl_Read(srl, buffer + total, length - total)
	pop	bc,bc,bc,bc
	add	hl,bc				; total += len
	push	hl
	call	usb_HandleEvents
	pop	bc,iy,de
	xor	a,a
	ld	hl,(iy + 9)
	sbc	hl,bc
	jq	nz,.loop
.exit:
	push	bc
	pop	hl
	pop	ix
	ret

;-------------------------------------------------------------------------------
;size_t srl_Write_Blocking(srl_device_t *srl, const void *buffer, size_t length, uint24_t timeout);
srl_Write_Blocking:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 3)
	ld	bc,0				; total
.loop:
;todo: check timeout
	xor	a,a
	push	iy
	push	bc
	ld	hl,(iy + 9)
	sbc	hl,bc
	push	hl
	ld	hl,(iy + 6)
	add	hl,bc
	push	hl
	push	ix
	call	srl_Write			; srl_Write(srl, buffer + total, length - total)
	pop	de,de,de,bc
	add	hl,bc				; total += len
	push	hl
	call	usb_HandleEvents
	pop	bc
	pop	iy
	xor	a,a
	ld	hl,(iy + 9)
	sbc	hl,bc
	jq	c,.loop
	pop	ix
	ret

;-------------------------------------------------------------------------------
;usb_error_t (usb_endpoint_t endpoint, usb_transfer_status_t status, size_t transferred, srl_device_t *data);
srl_ReadCallback:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 12)
	ld	hl,(iy + 9)			; return if nothing was transferred
	compare_hl_zero
	jq	z,.exit

	ld	a,SRL_FTDI
	cp	a,(xsrl_Device.type)
	jq	nz,.nonftdi
	dec	hl				; transferred -= 2
	dec	hl
	compare_hl_zero
	jq	z,.exit				; nothing was transferred

	push	hl
	pop	bc
	push	bc
	ld	hl,(xsrl_Device.readBufEnd)	; copy data from readBufEnd + 2 to readBufEnd
	ld	de,(xsrl_Device.readBufEnd)
	inc	hl
	inc	hl
	ldir
	pop	hl
	jq	.nonftdi
.nonftdi:
	ld	bc,(xsrl_Device.readBufEnd)	;readBufEnd += transferred
	add	hl,bc
	ld	(xsrl_Device.readBufEnd),hl
.exit:
	call	srl_StartAsyncRead
	pop	ix
	ld	hl,USB_SUCCESS
	ret

;-------------------------------------------------------------------------------
;usb_error_t (usb_endpoint_t endpoint, usb_transfer_status_t status, size_t transferred, srl_device_t *data);
srl_WriteCallback:
	ld	iy,0
	add	iy,sp
	push	ix
	ld	ix,(iy + 12)
	ld	bc,(iy + 9)			; writeBufStart += transferred
	ld	hl,(xsrl_Device.writeBufStart)
	add	hl,bc
	ld	(xsrl_Device.writeBufStart),hl
	xor	a,a				; if writeBufStart == writeBuf + writeBufSize:
	ld	bc,(xsrl_Device.writeBufSize)
	sbc	hl,bc
	ld	bc,(xsrl_Device.writeBuf)
	sbc	hl,bc
	jq	nz,.norestart
	ld	(xsrl_Device.writeBufStart),bc	; writeBufStart = writeBuf
.norestart:
	xor	a,a				; if writeBufStart == writeBufEnd:
	ld	bc,(xsrl_Device.writeBufStart)
	ld	hl,(xsrl_Device.writeBufEnd)
	sbc	hl,bc
	jq	z,.exit				; don't reschedule
	call	srl_StartAsyncWrite
.exit:
	pop	ix
	ld	hl,USB_SUCCESS
	ret

;-------------------------------------------------------------------------------
; ix: srl_device_t
srl_StartAsyncRead:
	ld	a,(xsrl_Device.stopRead)	; check if we are trying to stop
	or	a,a
	jq	z,.noStop			; default to no continuing transfer
	xor	a,a
	ld	(xsrl_Device.stopRead),a	; acknowledge that we have stopped
	jq	.exit
.noStop:
	ld	hl,(xsrl_Device.readBufBreak)	; check if there is room in the buffer
	compare_hl_zero
	jq	nz,.break
	jq	.nobreak
.nobreak:
	ld	hl,64				; if readBufEnd + 64 >= readBuf + readBufSize loop buffer
	ld	de,(xsrl_Device.readBufEnd)
	add	hl,de
	ld	bc,(xsrl_Device.readBufSize)
	sbc	hl,bc
	ld	bc,(xsrl_Device.readBuf)
	sbc	hl,bc
	jq	c,.schedule
	ld	hl,(xsrl_Device.readBufStart)
	sbc	hl,bc
	jq	z,.exit				; reset readBufActive - no room
	ld	(xsrl_Device.readBufBreak),de	; set readBufBreak
	ld	(xsrl_Device.readBufEnd),bc	; set readBufEnd to readBuf
	jq	.break
.break:
	ld	hl,64				; if readBufEnd + 64 >= readBufStart cancel
	ld	de,(xsrl_Device.readBufEnd)
	add	hl,de
	ld	bc,(xsrl_Device.readBufStart)
	sbc	hl,bc
	jq	nc,.exit			; reset readBufActive - no room
	jq	.schedule
.schedule:
	push	ix				; schedule a transfer with 64 bytes
	ld	bc,srl_ReadCallback
	push	bc
	ld	hl,64
	push	hl
	push	de				; readBufEnd
	ld	bc,(xsrl_Device.in)
	push	bc
	call	usb_ScheduleTransfer
	pop	bc,bc,bc,bc,bc
	ld	a,1				; set readBufActive
.exit:
	ld	(xsrl_Device.readBufActive),a
	ret

;-------------------------------------------------------------------------------
; ix: srl_device_t
srl_StartAsyncWrite:
	xor	a,a
	ld	hl,(xsrl_Device.writeBufEnd)
	ld	bc,(xsrl_Device.writeBufStart)
	sbc	hl,bc				; size = writeBufEnd - writeBufStart
	ret	z				; do nothing if buffer is empty
	jq	nc,.schedule
	jq	.wrap
.wrap:
	ld	hl,(xsrl_Device.writeBuf)	; size = writeBuf + writeBufSize - writeBufStart
	ld	bc,(xsrl_Device.writeBufSize)
	add	hl,bc
	ld	bc,(xsrl_Device.writeBufStart)
	sbc	hl,bc
	jq	.schedule
.schedule:
	push	ix				; schedule a transfer
	ld	bc,srl_WriteCallback
	push	bc
	push	hl
	ld	bc,(xsrl_Device.writeBufStart)
	push	bc
	ld	bc,(xsrl_Device.out)
	push	bc
	call	usb_ScheduleTransfer
	pop	bc,bc,bc,bc,bc
	ret

;temp
openDebug:
	push	hl
	scf					; open debugger
	sbc	hl,hl
	ld	(hl),2
	pop	hl
	ret

;temp: device in ix, byte in a
dbg_WriteByte:
	push	hl,bc,de,ix,iy
	ld	(.byte),a
	ld	bc,0
	push	bc		; transferred
	dec	bc
	push	bc		; retries
	inc	bc
	inc	bc
	push	bc		; length
	ld	bc,.byte	; data
	push	bc
	ld	bc,(xsrl_Device.out)
	push	bc
	call	usb_Transfer
	pop	bc,bc,bc,bc,bc,iy,ix,de,bc,hl
	ret
.byte:
	rb	1

;-------------------------------------------------------------------------------
; library data
;-------------------------------------------------------------------------------

setup.setlinecoding	setuppkt	$21,$20,$0000,$0000,7
setup.ftdisetrate	setuppkt	$40,$03,$0000,$0000,0

defaultlinecoding:
db	$80,$25,0,0,0,0,8

tmp tmp_data

srl_GetCDCStandardDescriptors:
	ld	hl,.descriptors
	ret
.descriptors:
	dl .device, .configurations, .langids
	db 2
	dl .strings
.device emit $12: $1201000200000040510408E0200201020001 bswap $12
.configurations dl .configuration1
.configuration1 emit $3e: $09023e00020100c0320904000001020200000524000110042402000524060001070582030800ff09040100020a0000000705040240000107058302400001 bswap $3e
.langids dw $0304, $0409
.strings dl .string1
.model dl .string84
.string1 dw $033E, 'T','e','x','a','s',' ','I','n','s','t','r','u','m','e','n','t','s',' ','I','n','c','o','r','p','o','r','a','t','e','d'
.string83 dw $0322, 'T','I','-','8','3',' ','P','r','e','m','i','u','m',' ','C','E'
.string84 dw $031C, 'T','I','-','8','4',' ','P','l','u','s',' ','C','E'
