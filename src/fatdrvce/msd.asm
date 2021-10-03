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
	rb 31	; padding needed because some msd drives were built by idiots
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
	rb 31	; padding needed because some msd drives were built by idiots
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

struct msd
	local size
	label .: size
	dev rl 1
	bulkin rb 1
	bulkout rb 1
	config rb 1
	interface rb 1
	tag rd 1
	last rl 1			; pointer to last transfer
	haslast rb 1
	buffer rb 768
	size := $-.
end struct

struct msdXfer
	local size
	label .: size
	msd rl 1
	lba rb 4
	buffer rl 1
	count rl 1
	callback rl 1
	userptr rl 1
	next rl 1
	stall rb 1
	cbw rb 31+1
	csw rb 13+19
	size := $-.
end struct

virtual at 0
	MSD_SUCCESS rb 1
	MSD_ERROR_INVALID_PARAM rb 1
	MSD_ERROR_USB_FAILED rb 1
	MSD_ERROR_SCSI_FAILED rb 1
	MSD_ERROR_SCSI_CHECK_CONDITION rb 1
	MSD_ERROR_NOT_SUPPORTED rb 1
	MSD_ERROR_INVALID_DEVICE rb 1
	MSD_ERROR_TIMEOUT rb 1
end virtual

;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Initialize a Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : usb device structure
; return:
;  hl = error status
msd_Open:
	ld	iy,0
	add	iy,sp
	push	iy
	ld	iy,(iy + 3)		; storage for descriptor (user buffer)
	lea	hl,ymsd.buffer
	ld	(.buffer),hl
	pop	iy
	push	iy
	ld	bc,.descriptor_length	; storage for size of descriptor
	push	bc
	ld	bc,18			; size of device descriptor
	push	bc
	ld	hl,0			; storage for descriptor (user buffer)
.buffer := $-3
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
	ld	hl,(.buffer)
	ld	de,17
	add	hl,de
	ld	a,(hl)
	ld	(.num_config),a		; get the number of interfaces
	xor	a,a
	ld	(.config),a		; set starting index
	jq	.getconfigcheck
.getconfiguration:			; bc = index
	push	iy
	ld	c,0
.config := $ - 1
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
	ld	bc,(.buffer)		; storage for configuration descriptor
	push	bc
	ld	hl,.config
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
	ld	(.interface),a
	ld	(.bulkin),a
	ld	(.bulkout),a
	ld	hl,0
.config_length := $-3
	ld	(.configlengthend),hl
	ld	hl,(.buffer)
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
	ld	(.interface),a
	jq	.parsenext
.parseendpoint:
	ld	a,0			; mark as valid
.interface := $ - 1
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
	ld	(.bulkin),a
	jq	.parsenext
.parseoutendpointout:
	ld	(.bulkout),a
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
.bulkin := $ - 1
	or	a,a
	jq	z,.getconfigcheck	; no endpoints for msd, keep parsing
	ld	a,0
.bulkout := $ - 1
	or	a,a
	jq	z,.getconfigcheck	; no endpoints for msd, keep parsing

	ld	bc,(iy + 6)
	ld	iy,(iy + 3)		; setup msd structure with endpoints and buffer
	ld	(ymsd.dev),bc
	ld	a,(.bulkout)
	ld	(ymsd.bulkout),a
	ld	a,(.bulkin)
	ld	(ymsd.bulkin),a
	ld	a,(.config)
	dec	a
	ld	(ymsd.config),a
	ld	a,(.interface)
	dec	a
	ld	(ymsd.interface),a

	push	bc			; holds the usbdrvce device
	call	usb_RefDevice		; prevent random crashes if the user messes up
	pop	bc

	; successfully found bulk endpoints for msd
	; now reset the msd device

	jq	msd_Reset.enter

.getconfigcheck:
	ld	a,(.config)
	cp	a,0
.num_config := $-1
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
	push	hl
	ld	hl,scsi.synchronizecache
	call	scsi_sync_command
	jq	z,.done
	ld	hl,scsi.requestsense
	call	scsi_sync_command
.done:
	push	iy
	ld	hl,(ymsd.dev)
	push	hl
	call	usb_UnrefDevice
	pop	de,de
	add	hl,de
	ld	(hl),0
	inc	de
	ld	bc,sizeof msd - 1
	ldir
	ret

;-------------------------------------------------------------------------------
; Attempts to reset and restore normal working order of the device.
; args:
;  sp + 3  : msd device structure
; return:
;  hl = error status
msd_Reset:
	pop	de,iy
	push	iy,de
.enter:
	ld	hl,(ymsd.dev)	; check if non-zero msd device
	compare_hl_zero
	jq	z,.invalidparam
	push	iy
	or	a,a
	sbc	hl,hl
	ld	l,(ymsd.config)
	push	hl
	ld	bc,(ymsd.dev)	; usb device
	push	bc
	call	usb_GetConfigurationDescriptorTotalLength
	pop	bc,bc
	pop	iy
	compare_hl_zero
	jq	z,.usberror
	push	iy
	ld	bc,.length		; storage for length of descriptor
	push	bc
	push	hl			; length of configuration descriptor
	lea	hl,ymsd.buffer
	push	hl
	or	a,a
	sbc	hl,hl
	ld	l,(ymsd.config)
	push	hl			; configuration index
	ld	l,2			; USB_CONFIGURATION_DESCRIPTOR
	push	hl
	ld	hl,(ymsd.dev)
	push	hl
	call	usb_GetDescriptor
	pop	bc,bc,bc,bc,bc,bc
	pop	iy
	compare_hl_zero
	ret	nz			; ensure success
	push	iy
	ld	hl,0
.length := $-3
	push	hl
	lea	hl,ymsd.buffer
	push	hl
	ld	hl,(ymsd.dev)
	push	hl
	call	usb_SetConfiguration
	pop	bc,bc,bc
	pop	iy
	compare_hl_zero
	jq	z,.configured
.usberror:
	ld	hl,MSD_ERROR_USB_FAILED
	ret
.invalidparam:
	ld	hl,MSD_ERROR_INVALID_PARAM
	ret
.configured:
	xor	a,a
	sbc	hl,hl
	ld	(ymsd.haslast),a
	ld	(ymsd.tag + 0),hl
	ld	(ymsd.tag + 3),a	; reset tag
;	call	util_msd_reset		; some drives were written by idiots
;	compare_hl_zero			; (looking at you sandisk!) and they
;	ret	nz			; can't be reset -- just don't even try
	call	util_msd_get_max_lun
	compare_hl_zero
	ret	nz
	jq	scsi_init		; return success if init scsi

;-------------------------------------------------------------------------------
; Gets the number of and size of each block (sector) on the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store info to
; return:
;  hl = error status
msd_Info:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 3)
	compare_hl_zero
	jr	z,.paramerror
	ld	hl,(iy + 6)
	compare_hl_zero
	jr	z,.paramerror
	push	iy
	ld	iy,(iy + 3)
	ld	hl,scsi.readcapacity
	call	scsi_sync_command	; store the logical block address / size
	lea	de,ymsd.buffer
	pop	iy
	jr	nz,.error
	ld	hl,(iy + 6)
	ld	bc,7
	add	hl,bc
	ld	a,(de)
	ld	(hl),a
	inc	de
	dec	hl
	ld	a,(de)
	ld	(hl),a
	inc	de
	dec	hl
	ld	a,(de)
	ld	(hl),a
	inc	de
	dec	hl
	ld	a,(de)
	ld	(hl),a
	inc	de
	dec	hl
	ld	a,(de)
	ld	(hl),a
	inc	de
	dec	hl
	ld	a,(de)
	ld	(hl),a
	inc	de
	dec	hl
	ld	a,(de)
	ld	(hl),a
	inc	de
	dec	hl
	ld	a,(de)
	ld	(hl),a
	xor	a,a
	sbc	hl,hl
	ret
.paramerror:
	ld	hl,MSD_ERROR_INVALID_PARAM
	ret
.error:
	ld	hl,MSD_ERROR_SCSI_FAILED
	ret

;-------------------------------------------------------------------------------
msd_Read:
; Synchronous block read
; inputs:
;  sp + 3: msd struct
;  sp + 6: lba
;  sp + 12: count
;  sp + 15: buffer
; outputs:
;  hl: error status
	ld	iy,0
	add	iy,sp
	lea	hl,iy + 6		; lba
	ld	de,(iy + 12)		; count
	push	iy
	ld	iy,scsi.read10
	call	scsi_pktrw_setup
	pop	iy
	ld	de,(iy + 15)
	ld	iy,(iy + 3)
	ld	hl,scsi.read10
	jq	scsi_sync_command.buf

;-------------------------------------------------------------------------------
msd_Write:
; Synchronous block write
; inputs:
;  sp + 3: msd struct
;  sp + 6: lba
;  sp + 12: count
;  sp + 15: const buffer
; outputs:
;  hl: error status
	ld	iy,0
	add	iy,sp
	lea	hl,iy + 6		; lba
	ld	de,(iy + 12)		; count
	push	iy
	ld	iy,scsi.write10
	call	scsi_pktrw_setup
	pop	iy
	ld	de,(iy + 15)
	ld	iy,(iy + 3)
	ld	hl,scsi.write10
	jq	scsi_sync_command.buf

;-------------------------------------------------------------------------------
msd_ReadAsync:
; Asynchronous block read
; inputs:
;  sp + 3: msd transfer struct
; outputs:
;  hl: error status
	ld	iy,0
	add	iy,sp
	ld	iy,(iy + 3)		; xfer struct
.enter:
	lea	hl,ymsdXfer.lba
	ld	de,(ymsdXfer.count)
	push	iy
	ld	iy,scsi.read10
	call	scsi_pktrw_setup
	pop	iy
	ld	hl,scsi.read10
	lea	de,ymsdXfer.cbw
	ld	bc,sizeof packetCBW
	ldir
	jq	scsi_async_cbw

;-------------------------------------------------------------------------------
msd_WriteAsync:
; Asynchronous block write
; inputs:
;  sp + 3: msd transfer structure
; outputs:
;  hl: error status
	ld	iy,0
	add	iy,sp
	ld	iy,(iy + 3)		; xfer struct
	lea	hl,ymsdXfer.lba
	ld	de,(ymsdXfer.count)
	push	iy
	ld	iy,scsi.write10
	call	scsi_pktrw_setup
	pop	iy
	ld	hl,scsi.write10
	lea	de,ymsdXfer.cbw
	ld	bc,sizeof packetCBW
	ldir
	jq	scsi_async_cbw

;-------------------------------------------------------------------------------
; utility functions
;-------------------------------------------------------------------------------

; inputs:
;  iy : msd struct
scsi_init:
	ld	b,5			; number of inquire retries
.loop:
	push	bc
	ld	hl,scsi.inquiry		; some devices are slow to start
	call	scsi_sync_command
	pop	bc
	jq	z,scsi_test_unit_ready
	call	util_delay_200ms
	djnz	.loop
.error:
	ld	hl,MSD_ERROR_SCSI_FAILED
	ret
scsi_test_unit_ready:
	ld	b,15			; number of test unit retries
.loop:
	push	bc
	ld	hl,scsi.testunitready
	call	scsi_sync_command
	jq	z,.done
	ld	hl,scsi.requestsense
	call	scsi_sync_command
	pop	bc
	jq	nz,scsi_init.error
	call	util_delay_200ms
	djnz	.loop
	jq	scsi_init.error
.done:
	pop	bc
scsi_read_capacity:
	ld	b,5			; number of read capacitiy retries
.loop:
	push	bc
	ld	hl,scsi.readcapacity
	call	scsi_sync_command
	jq	z,.done
	ld	hl,scsi.requestsense
	call	scsi_sync_command
	pop	bc
	jq	nz,scsi_init.error
	call	util_delay_200ms
	djnz	.loop
	jq	scsi_init.error
.done:
	pop	bc
	xor	a,a
	sbc	hl,hl			; success
	ret

; inputs:
;  sp + 3 : status
;  sp + 6 : xfer
scsi_sync_command_callback:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 3)		; status
	compare_hl_zero
	ld	hl,scsi_sync_command.done
	jq	nz,.fail
	set	0,(hl)			; success
	ret
.fail:
	set	1,(hl)
	ret

; inputs:
;  iy : msd struct
;  hl : cbw structure
scsi_sync_command:
	lea	de,ymsd.buffer		; use the user buffer by default
.buf:
	push	iy
	ld	(.xfer),iy		; first element is msd
	ld	iy,.xfer
	ld	(ymsdXfer.buffer),de
	lea	de,ymsdXfer.cbw
	ld	bc,sizeof packetCBW
	ldir				; copy cbw to packet structure
	ld	de,scsi_sync_command_callback
	ld	(ymsdXfer.callback),de
	xor	a,a
	ld	(.done),a
	call	scsi_async_cbw
	compare_hl_zero			; make sure it succeeded
	jq	nz,.fail
.wait_done:
	call	usb_HandleEvents	; todo: add timeout in here?
	compare_hl_zero
	jq	nz,.fail
	ld	a,0
.done := $-1
	or	a,a
	jq	z,.wait_done
	bit	1,a			; nz = fail, z = success
.fail:
	pop	iy
	ret
.xfer:
	rb	sizeof msdXfer

; inputs:
;  iy : xfer struct
scsi_async_cbw:
	xor	a,a
	sbc	hl,hl
	ld	(ymsdXfer.next),hl	; clear next pointer
	ld	(ymsdXfer.stall),a	; clear stall for csw
	ld	hl,(ymsdXfer.cbw + packetCBW.len)
	push	iy
	lea	de,iy			; de = xfer struct
	ld	iy,(ymsdXfer.msd)
	or	a,(ymsd.haslast)
	jq	z,.send
.queue:					; if currently sending, queue it
	lea	hl,ymsd.last
	ld	iy,(hl)
	ld	(ymsdXfer.next),de	; queue the next bulk transfer
	ld	(hl),de			; make this xfer the new last
	pop	iy
	xor	a,a
	sbc	hl,hl			; return success
	ret
.send:
	ld	(ymsd.last),de
	ld	(ymsd.haslast),1
.do_xfer:
	inc	(ymsd.tag)		; incremet cbw tag
	jq	nz,.skip
	ld	de,(ymsd.tag + 1)
	inc	de
	ld	(ymsd.tag + 1),de
.skip:
	ld	c,(ymsd.bulkout)
	compare_hl_zero			; check if cbw length is zero
	ld	hl,scsi_async_data
	jq	nz,.not_zero_length
	ld	hl,scsi_async_csw	; if zero length, skip data callback
.not_zero_length:
	ld	a,de,(ymsd.tag)
	pop	iy
	push	iy
	lea	iy,ymsdXfer.cbw
	ld	(ypacketCBW.tag),a,de
	pop	iy
	lea	de,ymsdXfer.cbw		; send cbw
	ld	a,c
	ld	bc,sizeof packetCBW
	jq	scsi_async_xfer

; inputs:
;  sp + 3 : endpoint
;  sp + 6 : status
;  sp + 9 : transferred size
;  sp + 12 : data
scsi_async_data:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 6)		; verify cbw transfer
	compare_hl_zero
	ld	iy,(iy + 12)		; xfer struct
	jq	nz,scsi_async_issue_callback_fail
	bit 	7,(ymsdXfer.cbw + packetCBW.dir)
	push	iy
	ld	iy,(ymsdXfer.msd)	; get msd struct
	ld	a,(ymsd.bulkin)
	jr	nz,.xfer
	ld	a,(ymsd.bulkout)
.xfer:
	pop	iy			; restore xfer struct
	ld	hl,scsi_async_csw
	ld	de,(ymsdXfer.buffer)
	ld	bc,(ymsdXfer.cbw + packetCBW.len)
	jq	scsi_async_xfer

; inputs:
;  sp + 3 : endpoint
;  sp + 6 : status
;  sp + 9 : transferred size
;  sp + 12 : data
scsi_async_csw:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 6)		; verify cbw transfer
	compare_hl_zero
	ld	iy,(iy + 12)		; xfer struct
	jq	nz,scsi_async_issue_callback_fail
.retry:
	push	iy
	ld	iy,(ymsdXfer.msd)	; msd struct
	ld	a,(ymsd.bulkin)
	pop	iy			; restore xfer struct
	lea	de,ymsdXfer.csw
	ld	bc,sizeof packetCSW
	ld	hl,scsi_async_done
	jq	scsi_async_xfer

; inputs:
;  a  : endpoint
;  hl : callback
;  bc : length
;  de : buffer
;  iy : xfer struct
scsi_async_xfer:
	push	iy
	push	iy			; xfer struct
	push	hl			; callback
	push	bc			; length
	push	de			; buffer
	or	a,a
	sbc	hl,hl			; todo: is this needed
	ld	l,a			; endpoint
	push	hl
	ld	iy,(ymsdXfer.msd)	; msd struct
	ld	hl,(ymsd.dev)		; usb struct
	push	hl
	call	usb_GetDeviceEndpoint
	pop	bc,bc
	push	hl
	call	usb_ScheduleTransfer
	pop	bc,bc,bc,bc,bc
	pop	iy
	ret

; inputs:
;  sp + 3 : endpoint
;  sp + 6 : status
;  sp + 9 : transferred size
;  sp + 12 : data
scsi_async_done:
	; things we could do:
	; check residue: some devices are bad at this though?
	; check signature: but why?
	; check tag: but why?
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 6)		; verify cbw transfer
	compare_hl_zero
	ld	iy,(iy + 12)		; xfer struct
	jq	nz,.check_stall
	ld	a,(ymsdXfer.csw + packetCSW.status)
	or	a,a			; cmd success
	ld	bc,MSD_SUCCESS
	jr	z,scsi_async_issue_callback
	dec	a			; cmd failed (but valid csw)
	ld	c,MSD_ERROR_SCSI_CHECK_CONDITION
	jr	z,scsi_async_issue_callback
.check_stall:
	bit	0,l			; USB_TRANSFER_STALLED
	jq	z,.failed
	bit	0,(ymsdXfer.stall)
	set	0,(ymsdXfer.stall)	; retry once if stalled
	jq	z,scsi_async_csw.retry
.failed:
	jq	scsi_async_issue_callback_fail

; inputs:
;  iy : xfer struct
scsi_async_issue_callback_fail:
;	push	iy			; some drives die upon reset
;	call	scsi_reset_recovery	; so just don't reset them, even though
;	pop	iy			; the spec says I should
	ld	bc,MSD_ERROR_SCSI_FAILED
	jq	scsi_async_issue_callback

; inputs:
;  de : status
;  iy : xfer struct
scsi_async_issue_callback:
	push	iy
	lea	de,iy
	ld	iy,(ymsdXfer.msd)
	ld	hl,(ymsd.last)
	compare_hl_de
	jq	nz,.dont_clear		; if xfer->msd->last == xfer
	ld	(ymsd.haslast),0	; xfer->msd->last = NULL
.dont_clear:
	pop	iy
	ld	hl,(ymsdXfer.next)
	push	hl
	ld	hl,(ymsdXfer.callback)
	compare_hl_zero
	jq	z,.no_callback
	push	iy
	push	bc
	ld	bc,.return
	push	bc
	jp	(hl)
.return:
	pop	de,iy
.no_callback:
	pop	hl
	compare_hl_zero			; if there's a next pointer, issue it
	ret	z
	push	hl
	ld	iy,(hl)			; msd is first element in xfer
	jq	scsi_async_cbw.do_xfer	; send the next cbw

; inputs:
;  iy : xfer struct
;scsi_reset_recovery:
;	ld	iy,(ymsdXfer.msd)
;	jq	util_msd_reset		; perform reset, usbdrvce clears stalls

; inputs:
;  iy : msd structure
;util_msd_reset:
;	xor	a,a
;	sbc	hl,hl
;	ld	(ymsd.haslast),a
;	ld	(ymsd.tag + 0),hl
;	ld	(ymsd.tag + 3),a	; reset tag
;	ld	a,(ymsd.interface)
;	ld	(setup.msdreset + 4),a
;	ld	hl,setup.msdreset
;	jq	util_msd_ctl_packet

; inputs:
;  iy : msd structure
util_msd_get_max_lun:
	ld	a,(ymsd.interface)
	ld	(setup.msdmaxlun + 4),a
	ld	hl,setup.msdmaxlun
	lea	de,ymsd.buffer
	jq	util_msd_ctl_packet

; inputs:
;  iy : msd structure
;  hl : packet
;  de : location to store data to
util_msd_ctl_packet:
	push	iy
	ld	bc,0
	push	bc			; don't care about callback data
	ld	bc,.callback		; callback
	push	bc
	push	de			; send data packet
	push	hl			; send setup packet
	xor	a,a
	sbc	hl,hl
	push	hl
	ld	(.done),a
	ld	bc,(ymsd.dev)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc,bc
	push	hl
	call	usb_ScheduleControlTransfer
	pop	bc,bc,bc,bc,bc
	compare_hl_zero
	jq	nz,.fail
	ld	hl,2
	push	hl
	ld	hl,14445568		; ~1 second timeout
	push	hl
	ld	hl,.struct
	push	hl
	call	usb_StartTimerCycles	; set up timeout
	pop	bc,bc,bc
.wait:
	call	usb_HandleEvents	; todo: add timeout in here?
	compare_hl_zero
	jq	nz,.fail
	ld	a,0
.done := $-1
	or	a,a
	jq	z,.wait
.fail:
	pop	iy
	ret
.callback:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 6)		; get transfer status
.complete:
	ld	a,1
	ld	(.done),a
	ret
.timeout:
	ld	hl,MSD_ERROR_TIMEOUT
	jq	.complete
.struct:
	dd	0
	dl	0
	dl	.timeout

; inputs:
;  hl : points to lba
;  de : count
;  iy : scsi.read10 or scsi.write10
scsi_pktrw_setup:
	lea	bc,yscsipktrw.lba + 3
	ld	a,(hl)
	ld	(bc),a
	inc	hl
	dec	bc
	ld	a,(hl)
	ld	(bc),a
	inc	hl
	dec	bc
	ld	a,(hl)
	ld	(bc),a
	inc	hl
	dec	bc
	ld	a,(hl)
	ld	(bc),a			; store big endian fields
	ld	(yscsipktrw.len + 0),d
	ld	(yscsipktrw.len + 1),e
	ex	de,hl
	add	hl,hl			; assume block size of 512
	ld	(yscsipktrw + 9),hl	; number of bytes in data section
	ret

util_delay_200ms:
	ld	a,20
.loop:
	push	af
	push	bc
	call	$3B4			; waits for ~10ms
	pop	bc
	pop	af
	dec	a
	jq	nz,.loop
	ret

;-------------------------------------------------------------------------------
; utility data
;-------------------------------------------------------------------------------

;setup.msdreset          setuppkt        $21,$ff,0,0,0
setup.msdmaxlun         setuppkt        $a1,$fe,0,0,1

scsi.inquiry            scsipkt         1,$05, $12,$00,$00,$00,$05,$00
scsi.modesense          scsipkt         1,$c0, $1a,$00,$3f,$00,$c0,$00
scsi.requestsense       scsipkt         1,$12, $03,$00,$00,$00,$12,$00
scsi.testunitready      scsipkt         0,$00, $00,$00,$00,$00,$00,$00
scsi.readcapacity       scsipkt         1,$08, $25,$00,$00,$00,$00,$00,$00,$00,$00,$00
scsi.synchronizecache   scsipkt         0,$00, $35,$00,$00,$00,$00,$00,$00,$00,$00,$00

scsi.read10             scsipktrw       1,$28
scsi.write10            scsipktrw       0,$2a
