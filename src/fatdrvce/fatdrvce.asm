;-------------------------------------------------------------------------------
include '../include/library.inc'
include '../include/include_library.inc'
;-------------------------------------------------------------------------------

library 'FATDRVCE',1

;-------------------------------------------------------------------------------
; Dependencies
;-------------------------------------------------------------------------------
include_library '../usbdrvce/usbdrvce.asm'

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export msd_Init
	export msd_GetBlockSize
	export msd_GetSectorCount
	export msd_GetSectorSize
	export msd_ReadSectors
	export msd_WriteSectors
;-------------------------------------------------------------------------------

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
macro struct? name*
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
 struc name
  namespace .
end macro

struct tmp_data
	label .: 25
	length		rl 1
	descriptor	rb 18
	dword		rb 4
end struct

; msd structures
struct msdDevice
	label .: 18
	dev		rl 1
	epin		rl 1
	epout		rl 1
	epctrl		rl 1
	interface	rb 1
	maxlun		rb 1
	lun		rb 1
	buffer		rl 1
end struct
struct packetCSW
	label .: 13
	signature	rb 4
	tag		rb 4
	residue		rb 4
	status		rb 1
end struct
struct packetCBD
	label .: 17
	length		rb 1
	opcode		rb 1
	data		rb 15
end struct
struct packetCBW
	label .: 14+17
	signature	rb 4
	tag		rb 4
	length		rb 4
	flags		rb 1
	lun		rb 1
	cbd		packetCBD
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
	USB_SUCCESS		rb 1
	USB_IGNORE		rb 1
	USB_ERROR_SYSTEM	rb 1
	USB_ERROR_INVALID_PARAM	rb 1
	USB_ERROR_SCHEDULE_FULL	rb 1
	USB_ERROR_NO_DEVICE	rb 1
	USB_ERROR_NO_MEMORY	rb 1
	USB_ERROR_NOT_SUPPORTED	rb 1
	USB_ERROR_TIMEOUT	rb 1
	USB_ERROR_FAILED	rb 1
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
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Initialize a USB connected Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : usb device to initialize as msd
;  sp + 9  : internal user-supplied buffer
; return:
;  a = error status
msd_Init:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 6)		; usb device
	compare_hl_zero
	jq	z,.error
	push	iy
	ld	bc,tmp.length		; storage for size of descriptor
	push	bc
	ld	bc,18			; size of device descriptor
	push	bc
	ld	bc,tmp.descriptor	; storage for descriptor
	push	bc
	ld	bc,0
	push	bc
	inc	bc			; USB_DEVICE_DESCRIPTOR = 1
	push	bc
	push	hl
	call	usb_GetDescriptor
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	iy
	compare_hl_zero
	ret	nz			; return if error
	ld	de,18
	ld	hl,(tmp.length)
	compare_hl_de			; ensure enough bytes were fetched
	jq	nz,.error
	xor	a,a
	ld	(.configindex),a	; set starting index
	jq	.getconfigcheck
.getconfiguration:			; bc = index
	push	iy
	ld	c,0
.configindex := $ - 1
	push	bc
	ld	bc,(iy + 6)		; usb device
	push	bc
	call	usb_GetConfigurationDescriptorTotalLength
	pop	bc
	pop	bc
	pop	iy
	push	iy
	ld	bc,tmp.length		; storage for length of descriptor
	push	bc
	push	hl			; length of configuration descriptor
	ld	bc,(iy + 9)		; storage for configuration descriptor
	push	bc
	ld	hl,.configindex
	ld	c,(hl)
	push	bc			; configuration index
	inc	(hl)
	ld	bc,2			; USB_CONFIGURATION_DESCRIPTOR
	push	bc
	ld	bc,(iy + 6)		; usb device
	push	bc
	call	usb_GetDescriptor
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	iy
	compare_hl_zero
	ret	nz			; ensure success

	; parse the configuration here for interfaces / endpoints for msd
	; we want to just grab the first bulk endpoints and msd interface

	xor	a,a
	ld	(.interfacenumber),a
	ld	(.inep),a
	ld	(.outep),a
	ld	hl,(tmp.length)
	ld	(.configlengthend),hl
	ld	hl,(iy + 9)
	ld	(.configptr),hl
	push	iy
.parseinterfaces:
	ld	hl,(.configlengthend)
	ld	de,2			; check for end of configuration
	compare_hl_de
	jq	c,.parsedone		; todo: check if bLength > remaining?
	ld	iy,(.configptr)
	ld	a,(ydescriptor.bDescriptorType)
	cp	a,INTERFACE_DESCRIPTOR
	jq	z,.parseinterface
	cp	a,ENDPOINT_DESCRIPTOR
	jq	z,.parseendpoint
	jq	.parsenext
.parseinterface:
	ld	a,(yinterfaceDescriptor.bInterfaceClass)
	cp	a,$08
	jr	nz,.parsenext
	ld	a,(yinterfaceDescriptor.bInterfaceSubClass)
	cp	a,$06
	jr	nz,.parsenext
	ld	a,(yinterfaceDescriptor.bInterfaceProtocol)
	cp	a,$50
	jr	nz,.parsenext
	ld	a,(yinterfaceDescriptor.bInterfaceNumber)
	inc	a
	ld	(.interfacenumber),a
	jq	.parsenext
.parseendpoint:
	ld	a,0			; mark as valid
.interfacenumber := $ - 1
	or	a,a
	jq	z,.parsenext
	ld	a,(yendpointDescriptor.bmAttributes)
	cp	a,BULK_TRANSFER
	jq	nz,.parsenext
	ld	a,(yendpointDescriptor.bEndpointAddress)
	ld	b,a
	and	a,DEVICE_TO_HOST
	ld	a,b
	jr	z,.parseoutendpointout
.parseoutendpointin:
	ld	(.inep),a
	jq	.parsenext
.parseoutendpointout:
	ld	(.outep),a
.parsenext:
	ld	de,0
	ld	e,(ydescriptor.bLength)
	ld	hl,0
.configlengthend := $ - 3
	or	a,a
	sbc	hl,de
	ld	(.configlengthend),hl
	jq	z,.parsedone
	ld	hl,0
.configptr := $ - 3
	add	hl,de
	ld	(.configptr),hl		; move to next interface
	jq	.parseinterfaces

.parsedone:
	pop	iy
	ld	a,0
.inep := $ - 1
	or	a,a
	jq	z,.getconfigcheck	; no endpoints for msd, keep parsing
	ld	a,0
.outep := $ - 1
	or	a,a
	jq	z,.getconfigcheck	; no endpoints for msd, keep parsing

	; successfully found bulk endpoints for msd
	; now get the actual endpoint addresses
	; and set the configuration

	push	iy
	ld	bc,(tmp.length)
	push	bc
	ld	bc,(iy + 9)
	push	bc
	ld	bc,(iy + 6)
	push	bc
	call	usb_SetConfiguration
	pop	bc
	pop	bc
	pop	bc
	pop	iy
	compare_hl_zero
	jq	nz,.getconfigcheck

	push	iy
	ld	a,(.inep)
	ld	c,a
	push	bc
	ld	bc,(iy + 6)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc
	pop	iy
	push	hl
	push	iy
	ld	a,(.outep)
	ld	c,a
	push	bc
	ld	bc,(iy + 6)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc
	pop	iy

	ld	de,(iy + 9)
	ld	bc,(iy + 6)
	ld	iy,(iy + 3)
	ld	(ymsdDevice.buffer),de
	ld	(ymsdDevice.dev),bc
	ld	(ymsdDevice.epout),hl	; setup msd structure with endpoints and buffer
	pop	de
	ld	(ymsdDevice.epin),de
	ld	a,(.interfacenumber)
	dec	a
	ld	(ymsdDevice.interface),a

	push	iy			; get the control transfer pipe
	ld	bc,0
	push	bc
	ld	bc,(ymsdDevice.dev)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc
	pop	iy
	ld	(ymsdDevice.epctrl),hl

	jq	.foundmsd

.getconfigcheck:
	ld	hl,tmp.descriptor + 17
	ld	a,(.configindex)
	cp	a,(hl)
	jq	nz,.getconfiguration
.error:
	ld	hl,USB_ERROR_NO_DEVICE
	ret
.foundmsd:

	; the usb device was successfully configured
	; now let's set up the msd device configuration

	call	util_ResetMsd
	compare_hl_zero
	jr	nz,.reporterror
	call	util_GetMaxLunMsd
	compare_hl_zero
	jr	nz,.reporterror

	or	a,a
	sbc	hl,hl			; return success
	ret

.reporterror:
	push	hl
	ld	iy,flags
	call	_DispHL
	call	_NewLine
	pop	hl
	ret

;-------------------------------------------------------------------------------
; Gets the block size from the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store block size to
; return:
;  a = error status
msd_GetBlockSize:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; Gets the sector count of the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store sector count to
; return:
;  a = error status
msd_GetSectorCount:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; Gets the sector size of each sector on the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store sector size to
; return:
;  a = error status
msd_GetSectorSize:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; Reads sectors from a Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : lba of starting sector to read
;  sp + 9  : number of sectors to read
;  sp + 12 : user buffer to read into
; return:
;  a = error status
msd_ReadSectors:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; Writes sectors to a Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : lba of starting sector to write
;  sp + 9  : number of sectors to write
;  sp + 12 : user buffer to write from
; return:
;  a = error status
msd_WriteSectors:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; utility functions
;-------------------------------------------------------------------------------

util_ResetMsd:
	ld	a,$55
	ld	(msdCBW.signature + 0),a
	ld	a,$53
	ld	(msdCBW.signature + 1),a
	ld	a,$42
	ld	(msdCBW.signature + 2),a
	ld	a,$43
	ld	(msdCBW.signature + 3),a
	xor	a,a
	sbc	hl,hl
	ld	(ymsdDevice.maxlun),a
	ld	(ymsdDevice.lun),a
	ld	(msdCBW.tag + 0),hl
	ld	(msdCBW.tag + 3),a	; reset tag
	ld	(msdCBW.flags),a
	ld	(msdCBW.lun),a
	ld	a,(ymsdDevice.interface)
	ld	(packetMSDReset + 4),a
	ld	(packetMSDMaxLUN + 4),a	; set selected interface
	ld	hl,packetMSDReset
	ld	de,tmp.dword
	jq	util_msd_ctl_packet

; iy -> msd structure
util_GetMaxLunMsd:
	ld	hl,packetMSDMaxLUN
	ld	de,(ymsdDevice.maxlun)
	jq	util_msd_ctl_packet

; a = lun
util_SetLunMsd:
	ld	(msdCBW.lun),a
	ret

; iy -> msd structure
; hl -> packet
; de -> location to store data to
util_msd_ctl_packet:
	push	iy
	ld	bc,0
	push	bc			; don't care about transfer size
	ld	bc,50
	push	bc			; retry 50 times
	push	hl
	push	de			; send setup packet
	ld	bc,(ymsdDevice.epctrl)
	push	bc
	call	usb_ControlTransfer
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	iy
	ret

;-------------------------------------------------------------------------------
; library data
;-------------------------------------------------------------------------------

packetMSDReset:
	db	$21,$FF,$00,$00,$00,$00,$00,$00
packetMSDMaxLUN:
	db	$A1,$FE,$00,$00,$00,$00,$01,$00

msdCSW packetCSW
msdCBW packetCBW

tmp tmp_data
