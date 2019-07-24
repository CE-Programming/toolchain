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
	sensecount	rb 1
	sensebuffer	rb 512	; todo: evaluate if needed
	length		rl 1
	descriptor	rb 18
	size := $-.
end struct

; msd structures
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
	dir		rb 1
	lun		rb 1
	cbd		packetCBD
end struct
struct msdDevice
	local size
	label .: size
	dev		rl 1
	epin		rl 1
	epout		rl 1
	epctrl		rl 1
	cbw		packetCBW
	csw		packetCSW
	lba		rb 4
	reserved	rb 1	; technically part of block size
	blocksize	rl 1
	interface	rb 1
	maxlun		rb 1
	lun		rb 1
	buffer		rl 1
	size := $-.
end struct

struct setup, requestType: ?, request: ?, value: ?, index: ?, length: ?
	label .: 8
	bmRequestType	db requestType
	bRequest	db request
	wValue		dw value
	wIndex		dw index
	wLength		dw length
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

DEFAULT_RETRIES := 50
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Initialize a USB connected Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : usb device to initialize as msd
;  sp + 9  : internal user-supplied buffer
; return:
;  hl = error status
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

	call	util_msd_reset
	compare_hl_zero
	ret	nz
	call	util_msd_get_max_lun
	compare_hl_zero
	ret	nz
	jq	util_scsi_init		; return success if init scsi

;-------------------------------------------------------------------------------
; Gets the block size from the device.
; The library assumes that sector size == msd block size.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store block size to
; return:
;  hl = error status
msd_GetSectorSize:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 3)
	compare_hl_zero
	jr	z,.error
	ld	hl,(iy + 6)
	compare_hl_zero
	jr	z,.error
	ld	iy,(iy + 3)
	ld	de,(ymsdDevice.blocksize)
	ld	(hl),de
	or	a,a
	sbc	hl,hl
	ret
.error:
	ld	hl,USB_ERROR_FAILED
	ret

;-------------------------------------------------------------------------------
; Gets the sector count of the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store sector count to
; return:
;  hl = error status
msd_GetSectorCount:

.error:
	or	a,a
	sbc	hl,hl
	ret

;-------------------------------------------------------------------------------
; Reads sectors from a Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : lba of starting sector to read
;  sp + 12 : number of sectors to read
;  sp + 15 : user buffer to read into
; return:
;  hl = error status
msd_ReadSectors:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 12)
	jq	.start
.loop:
	lea	hl,iy + 6
	ld	de,packetSCSI_Read10Lba + 3
	ld	a,(hl)
	ld	(de),a
	inc	hl
	dec	de
	ld	a,(hl)
	ld	(de),a
	inc	hl
	dec	de
	ld	a,(hl)
	ld	(de),a
	inc	hl
	dec	de
	ld	a,(hl)
	ld	(de),a
	inc	(iy + 6)		; increment the lba
	jr	nz,.nocarry
	ld	hl,(iy + 7)
	inc	hl
	ld	(iy + 7),hl
.nocarry:
	ld	de,(iy + 15)
	push	iy
	ld	iy,(iy + 3)
	ld	hl,packetSCSI_Read10
	call	util_scsi_request
	pop	iy
	compare_hl_zero
	ret	nz
	ld	hl,(iy + 12)
	dec	hl
.start:
	ld	(iy + 12),hl
	compare_hl_zero
	jr	nz,.loop
	or	a,a
	sbc	hl,hl		; return success
	ret

;-------------------------------------------------------------------------------
; Writes sectors to a Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : lba of starting sector to write
;  sp + 12 : number of sectors to write
;  sp + 15 : user buffer to write from
; return:
;  hl = error status
msd_WriteSectors:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 12)
	jq	.start
.loop:
	lea	hl,iy + 6
	ld	de,packetSCSI_Write10Lba + 3
	ld	a,(hl)
	ld	(de),a
	inc	hl
	dec	de
	ld	a,(hl)
	ld	(de),a
	inc	hl
	dec	de
	ld	a,(hl)
	ld	(de),a
	inc	hl
	dec	de
	ld	a,(hl)
	ld	(de),a
	inc	(iy + 6)		; increment the lba
	jr	nz,.nocarry
	ld	hl,(iy + 7)
	inc	hl
	ld	(iy + 7),hl
.nocarry:
	ld	de,(iy + 15)
	push	iy
	ld	iy,(iy + 3)
	ld	hl,packetSCSI_Write10
	call	util_scsi_request
	pop	iy
	compare_hl_zero
	ret	nz
	ld	hl,(iy + 12)
	dec	hl
.start:
	ld	(iy + 12),hl
	compare_hl_zero
	jr	nz,.loop
	or	a,a
	sbc	hl,hl		; return success
	ret

;-------------------------------------------------------------------------------
; utility functions
;-------------------------------------------------------------------------------

util_scsi_init:
	push	iy
	ld	hl,packetSCSI_Inquiry
	call	util_scsi_request_default
	pop	iy
	compare_hl_zero
	ret	nz
.unitattention:
	push	iy
	ld	hl,packetSCSI_TestUnitReady
	call	util_scsi_request_default
	pop	iy
	compare_hl_zero
	ret	nz
	and	a,$f
	cp	a,6
	jr	z,.unitattention
	push	iy
	ld	hl,packetSCSI_ReadCapacity
	lea	de,ymsdDevice.lba
	call	util_scsi_request	; store the logical block address/size
	pop	iy
	compare_hl_zero
	ret	nz
	push	iy
	ld	hl,packetSCSI_TestUnitReady
	call	util_scsi_request_default
	pop	iy
	compare_hl_zero
	ret	nz
	ld	hl,(ymsdDevice.blocksize)
	or	a,a
	sbc	hl,hl
	ret

; input:
;  hl : ptr to scsi command
;  de : ptr to storage (non-default)
;  iy : ptr to msd structure (for default)
; output;
;   z : success
;  nz : failure
util_scsi_request_default:
	ld	de,(ymsdDevice.buffer)
util_scsi_request:
	xor	a,a
	ld	(tmp.sensecount),a
.sense:
	ld	(util_get_out_ep.structure),iy
	lea	bc,ymsdDevice.cbw
	ld	(util_msd_transport_command.cbw_ptr),bc
	ld	(util_msd_transport_data.ptr),de
	ld	a,(hl)
	ld	(util_msd_transport_data.ep),a
	inc	hl
	ld	bc,(hl)
	ld	(util_msd_transport_data.len),bc
	inc	hl
	inc	hl
	inc	hl
	ld	(util_msd_transport_command.cbd_ptr),hl
	push	ix
.resendCbw:
	call	util_msd_transport_command
	call	util_msd_transport_data
	call	util_msd_transport_status
	jr	nz,.resendCbw
.abort:
	pop	ix
	ret

; input:
;  iy : msd structure
; output:
;  hopefully recovers transfer state
util_msd_reset_recovery:
	ld	iy,(util_get_out_ep.structure)
	call	util_msd_reset
	compare_hl_zero
	jr	z,.resetsuccess
	pop	bc			; abort if cannot reset
	pop	bc			; pop call and top level call
	jq	util_scsi_request.abort
.resetsuccess:
	call	util_msd_clr_in_stall
	jq	util_msd_clr_out_stall
util_msd_clr_out_stall:
	ld	bc,(ymsdDevice.epout)
	jr	util_msd_clr_stall
util_msd_clr_in_stall:
	ld	bc,(ymsdDevice.epin)
util_msd_clr_stall:
	push	bc
	call	usb_ClearEndpointHalt
	pop	bc
	ret

; inputs:
;  hl : data to transfer
;  de : buffer to recieve into
util_msd_transport_command:
	ld	hl,0
.cbd_ptr := $ - 3
	ld	ix,0
.cbw_ptr := $ - 3
	ld	a,(util_msd_transport_data.ep)
	ld	(xpacketCBW.dir),a	; direction flag
	ld	bc,(util_msd_transport_data.len)
	ld	(xpacketCBW.length),bc	; i/o length
	ld	bc,0
	ld	c,(hl)			; cbd length
	inc	c
	lea	de,xpacketCBW.cbd	; cbd location
	ldir
	ld	hl,(xpacketCBW.tag)	; increment tag
	inc	hl
	ld	(xpacketCBW.tag),hl
	call	util_get_out_ep
	ld	bc,sizeof packetCBW
	call	util_msd_bulk_transfer
	compare_hl_zero
	ret	z			; check the command was accepted
	call	util_msd_reset_recovery
	jr	util_msd_transport_command

; bc = length of transfer
util_msd_transport_data:
	ld	bc,0
.len := $ - 3
	sbc	hl,hl
	adc	hl,bc
	ret	z			; no transfer if 0 length
	ld	ix,0
.ptr := $ - 3
	ld	a,0
.ep := $ - 1
	or	a,a
	jr	z,.data_out
.data_in:
	call	util_get_in_ep
	call	util_msd_bulk_transfer
	compare_hl_zero
	ret	z
	jq	util_msd_clr_in_stall
.data_out:
	call	util_get_out_ep
	call	util_msd_bulk_transfer
	compare_hl_zero
	ret	z
	jq	util_msd_clr_out_stall

util_msd_transport_status:
	call	util_msd_status_xfer
	compare_hl_zero
	jr	z,.checkcsw
.stall:
	call	util_msd_clr_in_stall	; clear stall
	call	util_msd_status_xfer	; attempt to read csw again
	compare_hl_zero
	jr	z,.checkcsw
	call	util_msd_reset_recovery
	xor	a,a
	inc	a			; return failure code
	ret
.checkcsw:
	ld	iy,(util_get_out_ep.structure)
	ld	a,(ymsdDevice.csw.status)
	or	a,a			; check for good status of transfer
	jr	nz,.invalid
.valid:
	ld	hl,(ymsdDevice.csw.residue + 0)
	ld	a,(ymsdDevice.csw.residue + 3)
	add	hl,de
	or	a,a
	ld	a,$10
	ret	nz
	sbc	hl,de
	ret	nz			; if residue != 0, fail
	xor	a,a			; return success
	ret
.invalid:
	dec	a			; check for sense error (we can recover)
	jr	z,.senseerror		; handle command fail
.phaseerror:
	call	util_msd_reset_recovery
	xor	a,a
	inc	a
	ret
.senseerror:
	ld	hl,tmp.sensecount
	or	a,(hl)
	ret	nz
	inc	(hl)
	ld	de,tmp.sensebuffer
	ld	hl,packetSCSI_RequestSense
	call	util_scsi_request.sense
	xor	a,a
	ld	(tmp.sensebuffer),a
	ld	a,(tmp.sensebuffer + 2)
	ret

util_msd_status_xfer:
	call	util_get_in_ep
	ld	ix,(ymsdDevice.csw)
	ld	bc,sizeof packetCSW
	jq	util_msd_bulk_transfer

util_get_out_ep:
	ld	iy,0
.structure := $ - 3
	ld	de,(ymsdDevice.epout)
	ret
util_get_in_ep:
	ld	iy,(util_get_out_ep.structure)
	ld	de,(ymsdDevice.epin)
	ret

; inputs:
;  bc : packet len
;  ix : data buffer
;  de : endpoint
util_msd_bulk_transfer:
	or	a,a
	sbc	hl,hl
	push	hl
	ld	l,DEFAULT_RETRIES
	push	hl
	push	bc
	push	ix			; packet to send
	push	de
	call	usb_Transfer
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ret

; iy -> msd structure
util_msd_reset:
	lea	hl,ymsdDevice.cbw.signature
	ld	(hl),$55
	inc	hl
	ld	(hl),$53
	inc	hl
	ld	(hl),$42
	inc	hl
	ld	(hl),$43
	xor	a,a
	sbc	hl,hl
	ld	(ymsdDevice.cbw.tag + 0),hl
	ld	(ymsdDevice.cbw.tag + 3),a	; reset tag
	ld	a,(ymsdDevice.interface)
	ld	(packetMSDReset + 4),a
	ld	hl,packetMSDReset
	jq	util_msd_ctl_packet

; inputs:
;  iy : msd structure
util_msd_get_max_lun:
	ld	a,(ymsdDevice.interface)
	ld	(packetMSDMaxLUN + 4),a
	ld	hl,packetMSDMaxLUN
	ld	de,(ymsdDevice.maxlun)
	jq	util_msd_ctl_packet

; inputs:
;   a : lun
;  iy : msd structure
util_SetLunMsd:
	ld	(ymsdDevice.cbw.lun),a
	ret

; inputs:
;  iy : msd structure
;  hl : packet
;  de : location to store data to
util_msd_ctl_packet:
	push	iy
	ld	bc,0
	push	bc			; don't care about transfer size
	ld	bc,DEFAULT_RETRIES
	push	bc			; retry as needed
	push	de			; send data packet
	push	hl			; send setup packet
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

packetMSDReset setup $21, $FF, 0, 0, 0
packetMSDMaxLUN setup $A1, $FE, 0, 0, 1

; scsi format:
; <[1] in/out>,<[3] i/o length>,<[1] cdb length>,<[n] cdb>

packetSCSI_Inquiry:
	db	$80,$fc,$00,$00,$06,$12,$00,$00,$00,$fc,$00
packetSCSI_TestUnitReady:
	db	$00,$00,$00,$00,$06,$00,$00,$00,$00,$00,$00
packetSCSI_ModeSense6:
	db	$80,$fc,$00,$00,$06,$1a,$00,$3f,$00,$fc,$00
packetSCSI_RequestSense:
	db	$80,$12,$00,$00,$06,$03,$00,$00,$00,$12,$00
packetSCSI_ReadCapacity:
	db	$80,$08,$00,$00,$0a,$25,$00,$00,$00,$00,$00,$00,$00,$00,$00
packetSCSI_Read10:
	db	$80,$00,$02,$00,$0a,$28,$00
packetSCSI_Read10Lba:
	db	$00,$00,$00,$00
packetSCSI_Read10GroupNum:
	db	$00
packetSCSI_Read10Length:
	db	$00,$01
packetSCSI_Read10Ctrl:
	db	$00
packetSCSI_Write10:
	db	$00,$00,$02,$00,$0a,$2a,$00
packetSCSI_Write10Lba:
	db	$00,$00,$00,$00
packetSCSI_Write10GroupNum:
	db	$00
packetSCSI_Write10Length:
	db	$00,$01
packetSCSI_Write10Ctrl:
	db	$00

tmp tmp_data
