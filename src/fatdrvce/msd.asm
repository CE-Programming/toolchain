; msd driver supported using bulk-only transport via scsi

;-------------------------------------------------------------------------------
; scsi packet structures
;-------------------------------------------------------------------------------

struct setuppkt, requestType: ?, request: ?, value: ?, index: ?, length: ?
	label .: 8
	bmRequestType db requestType
	bRequest db request
	wValue dw value
	wIndex dw index
	wLength dw length
end struct

struct scsipkt, dir: 0, length: 1, data: 0&
.:	iterate @, data
		dd 'USBC', 0, length
		db (dir) shl 7, 0, %%, data
		break
	end iterate
	rb 31		; padding needed because some msd drives were built by idiots
end struct

struct scsipktrw, dir: 0, type: 0
.:	iterate @, data
		dd 'USBC', 0, 512
		db (dir) shl 7, 0, 10, type, 0
		break
	end iterate
	lba dd 0
	groupnum db 0
	len dw 1 bswap 2
	ctrl db 0
	rb 31 ; padding needed because some msd drives were built by idiots
end struct

;-------------------------------------------------------------------------------
; usb descriptor structures
;-------------------------------------------------------------------------------

struct descriptor
	label .: 2
	bLength rb 1
	bDescriptorType rb 1
end struct

struct deviceDescriptor
	label .: 18
	descriptor descriptor
	bcdUSB rw 1
	bDeviceClass rb 1
	bDeviceSubClass rb 1
	bDeviceProtocol rb 1
	bMaxPacketSize0 rb 1
	idVendor rw 1
	idProduct rw 1
	bcdDevice rw 1
	iManufacturer rb 1
	iProduct rb 1
	iSerialNumber rb 1
	bNumConfigurations rb 1
end struct

struct interfaceDescriptor
	label .: 9
	descriptor descriptor
	bInterfaceNumber rb 1
	bAlternateSetting rb 1
	bNumEndpoints rb 1
	bInterfaceClass rb 1
	bInterfaceSubClass rb 1
	bInterfaceProtocol rb 1
	iInterface rb 1
end struct

struct endpointDescriptor
	label .: 7
	descriptor descriptor
	bEndpointAddress rb 1
	bmAttributes rb 1
	wMaxPacketSize rw 1
	bInterval rb 1
end struct

virtual at 0
	?HOST_TO_DEVICE rb 1 shl 7
	?DEVICE_TO_HOST rb 1 shl 7
end virtual

virtual at 0
	?CONTROL_TRANSFER rb 1
	?ISOCHRONOUS_TRANSFER rb 1
	?BULK_TRANSFER rb 1
	?INTERRUPT_TRANSFER rb 1
end virtual

virtual at 1
	?DEVICE_DESCRIPTOR rb 1
	?CONFIGURATION_DESCRIPTOR rb 1
	?STRING_DESCRIPTOR rb 1
	?INTERFACE_DESCRIPTOR rb 1
	?ENDPOINT_DESCRIPTOR rb 1
end virtual

;-------------------------------------------------------------------------------
; msd bulk structures
;-------------------------------------------------------------------------------

struct packetCSW
	label .: 13
	signature rb 4
	tag rb 4
	residue rb 4
	status rb 1
end struct

struct packetCBD
	label .: 17
	len rb 1
	opcode rb 1
	data rb 15
end struct

struct packetCBW
	label .: 14+17
	signature rb 4
	tag rb 4
	len rb 4
	dir rb 1
	lun rb 1
	cbd packetCBD
end struct

struct msdDevice
	local size
	label .: size
	dev rl 1
	bulkinaddr rb 1
	bulkoutaddr rb 1
	configindex rb 1
	tag rl 1
	lba rb 4
	reserved rb 1	; technically part of block size
	blocksize rl 1
	interface rb 1
	maxlun rb 1
	buffer rl 1
	size := $-.
end struct

struct msdTransfer
	local size
	label .: size
	msd rl 1
	lba rb 4
	data rl 1
	count rl 1
	callback rl 1
	next rl 1
	size := $-.
end struct

virtual at 0
	MSD_SUCCESS rb 1
	MSD_ERROR_INVALID_PARAM rb 1
	MSD_ERROR_USB_FAILED rb 1
	MSD_ERROR_NOT_SUPPORTED rb 1
	MSD_ERROR_INVALID_DEVICE rb 1
end virtual

;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Initialize a Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : usb device structure
;  sp + 9  : user buffer storage
; return:
;  hl = error status
msd_Open:
	ld	iy,0
	add	iy,sp
	push	iy
	ld	bc,.descriptor_length	; storage for size of descriptor
	push	bc
	ld	bc,18			; size of device descriptor
	push	bc
	ld	hl,(iy + 9)		; storage for descriptor (user buffer)
	push	hl
	or	a,a
	sbc	hl,hl
	push	hl
	inc	hl			; USB_DEVICE_DESCRIPTOR = 1
	push	hl
	ld	hl,(iy + 6)
	push	hl
	call	usb_GetDescriptor
	pop	bc,bc,bc,bc,bc,bc
	pop	iy
	compare_hl_zero
	ret	nz			; return if error
	ld	de,18
	ld	hl,0
.descriptor_length := $-3
	compare_hl_de			; ensure enough bytes were fetched
	jq	nz,.msddeverror
	ld	hl,(iy + 9)
	ld	de,17
	add	hl,de
	ld	a,(hl)
	ld	(.num_interfaces),a	; get the number of interfaces
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
	ld	bc,.config_length	; storage for length of descriptor
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
	pop	bc,bc,bc,bc,bc,bc
	pop	iy
	compare_hl_zero
	ret	nz			; ensure success

	; parse the configuration here for interfaces / endpoints for msd
	; just grab the first bulk endpoints for a valid msd interface

	xor	a,a
	ld	(.interfacenumber),a
	ld	(.bulkinaddr),a
	ld	(.bulkoutaddr),a
	ld	hl,0
.config_length := $-3
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
	ld	(.bulkinaddr),a
	jq	.parsenext
.parseoutendpointout:
	ld	(.bulkoutaddr),a
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
.bulkinaddr := $ - 1
	or	a,a
	jq	z,.getconfigcheck	; no endpoints for msd, keep parsing
	ld	a,0
.bulkoutaddr := $ - 1
	or	a,a
	jq	z,.getconfigcheck	; no endpoints for msd, keep parsing

	ld	de,(iy + 9)
	ld	bc,(iy + 6)
	ld	iy,(iy + 3)		; setup msd structure with endpoints and buffer
	ld	(ymsdDevice.buffer),de
	ld	(ymsdDevice.dev),bc
	ld	a,(.bulkoutaddr)
	ld	(ymsdDevice.bulkoutaddr),a
	ld	a,(.bulkinaddr)
	ld	(ymsdDevice.bulkinaddr),a
	ld	a,(.configindex)
	dec	a
	ld	(ymsdDevice.configindex),a
	ld	a,(.interfacenumber)
	dec	a
	ld	(ymsdDevice.interface),a

	push	bc			; holds the usbdrvce device
	call	usb_RefDevice		; prevent random crashes if the user messes up
	pop	bc

	; successfully found bulk endpoints for msd
	; now reset the msd device

	ld	hl,0
	ret

.getconfigcheck:
	ld	a,(.configindex)
	cp	a,0
.num_interfaces := $-1
	jq	nz,.getconfiguration
.msddeverror:
	ld	hl,MSD_ERROR_INVALID_DEVICE
	ret

;-------------------------------------------------------------------------------
msd_Close:
; Closes and deinitializes the MSD structures.
; args:
;  sp + 3  : msd device structure
; return:
;  hl = error status
	pop	hl
	ex	(sp),iy
	push	hl,iy
	ld	hl,(ymsdDevice.dev)
	push	hl
	call	usb_UnrefDevice
	pop	de,de
	add	hl,de
	ld	(hl),0
	inc	de
	ld	bc,sizeof msdDevice - 1
	ldir
	ret

;-------------------------------------------------------------------------------
; Attempts to reset and restore normal working order of the device.
; args:
;  sp + 3  : msd device structure
; return:
;  hl = error status
msd_Reset:
	ret

;-------------------------------------------------------------------------------
; Gets the number of and size of each block (sector) on the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store sector count to
;  sp + 9  : pointer to store sector size to
; return:
;  hl = error status
msd_Info:
	ret

;-------------------------------------------------------------------------------
msd_ReadAsync:
; Asynchronous block read
; inputs:
;  sp + 3: msd transfer structure
; outputs:
;  hl: error status
	ret

;-------------------------------------------------------------------------------
msd_WriteAsync:
; Asynchronous block write
; inputs:
;  sp + 3: msd transfer structure
; outputs:
;  hl: error status
	ret

;-------------------------------------------------------------------------------
; utility functions
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; utility data
;-------------------------------------------------------------------------------

setup.msdreset          setuppkt        $21,$ff,0,0,0
setup.msdmaxlun         setuppkt        $a1,$fe,0,0,1

scsi.inquiry            scsipkt         1,$0005, $12, $00,$00,$00,$05,$00
scsi.testunitready      scsipkt         0,$0000, $00, $00,$00,$00,$00,$00
scsi.modesense6         scsipkt         1,$00fc, $1a, $00,$3f,$00,$fc,$00
scsi.requestsense       scsipkt         1,$0012, $03, $00,$00,$00,$12,$00
scsi.readcapacity       scsipkt         1,$0008, $25, $00,$00,$00,$00,$00,$00,$00,$00,$00
scsi.read10             scsipktrw       1,$28
scsi.write10            scsipktrw       0,$2a
