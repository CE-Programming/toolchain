;-------------------------------------------------------------------------------
.include "library.inc"
;-------------------------------------------------------------------------------

library MSDDRVCE, 1

; Imports are emitted in the order of their export slots.
.set import_usb_HandleEvents, 1
.set import_usb_RefDevice, 1
.set import_usb_UnrefDevice, 1
.set import_usb_GetConfigurationDescriptorTotalLength, 1
.set import_usb_GetDescriptor, 1
.set import_usb_SetConfiguration, 1
.set import_usb_SetInterface, 1
.set import_usb_GetDeviceEndpoint, 1
.set import_usb_ScheduleControlTransfer, 1
.set import_usb_ScheduleTransfer, 1
.set import_usb_StartTimerCycles, 1
.include "usbdrvce-exports.inc"
lib_dependency USBDRVCE, USBDRVCE_VERSION
usbdrvce_exports lib_import

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	lib_export msd_Open
	lib_export msd_Close
	lib_export msd_Reset
	lib_export msd_Info
	lib_export msd_Read
	lib_export msd_Write
	lib_export msd_ReadAsync
	lib_export msd_WriteAsync
	lib_export msd_FindPartitions
;-------------------------------------------------------------------------------

.include "compare.inc"

; mass storage driver -- bulk-only transport via scsi

;-------------------------------------------------------------------------------
; scsi packet structures
;-------------------------------------------------------------------------------

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

.struct 0
packetCSW:
packetCSW.signature:	.space 4
packetCSW.tag:	.space 4
packetCSW.residue:	.space 4
packetCSW.status:	.space 1
.equ packetCSW_size, . - packetCSW
assert (packetCSW_size == 13)

.struct 0
packetCBD:
packetCBD.len:	.space 1
packetCBD.opcode:	.space 1
packetCBD.data:	.space 15
.equ packetCBD_size, . - packetCBD
assert (packetCBD_size == 17)

.struct 0
packetCBW:
packetCBW.signature:	.space 4
packetCBW.tag:	.space 4
packetCBW.len:	.space 4
packetCBW.dir:	.space 1
packetCBW.lun:	.space 1
packetCBW.cbd:	.space packetCBD_size
.equ packetCBW_size, . - packetCBW
assert (packetCBW_size == 14+17)

.struct 0
msd:
msd.dev:	.space 3
msd.bulkin:	.space 1
msd.bulkout:	.space 1
msd.config:	.space 1
msd.interface:	.space 1
msd.tag:	.space 4
msd.last:	.space 3	; pointer to last transfer
msd.haslast:	.space 1
msd.buffer:	.space 768
.equ msd_size, . - msd

.struct 0
msdXfer:
msdXfer.msd:	.space 3
msdXfer.lba:	.space 4
msdXfer.buffer:	.space 3
msdXfer.count:	.space 3
msdXfer.callback:	.space 3
msdXfer.userptr:	.space 3
msdXfer.next:	.space 3
msdXfer.stall:	.space 1
msdXfer.cbw:	.space 31+1
msdXfer.csw:	.space 13+19
.equ msdXfer_size, . - msdXfer

.macro setup_packet request_type, request, value, index, length
	.db \request_type, \request
	.dw \value, \index, \length
.endm

.macro scsi_packet direction, length, count, data:vararg
	.db "USBC"
	.d32 0, \length
	.db \direction << 7, 0, \count, \data
	.space 31	; Extra padding for drives that require it.
.endm

.struct 13 + 4	; Fields following the command block wrapper and opcode.
scsipktrw.lba:	.space 4
scsipktrw.groupnum:	.space 1
scsipktrw.len:	.space 2
scsipktrw.ctrl:	.space 1
.equ scsipktrw, 0

.macro scsi_rw_packet direction, opcode
	.db "USBC"
	.d32 0, 512
	.db \direction << 7, 0, 10, \opcode, 0
	.d32 0	; LBA
	.db 0	; Group number
	.db 0, 1	; Transfer length in big-endian order
	.db 0	; Control
	.space 31
.endm

.text

;-------------------------------------------------------------------------------
; usb descriptor structures
;-------------------------------------------------------------------------------

.struct 0
HOST_TO_DEVICE:	.space 1 << 7
DEVICE_TO_HOST:	.space 1 << 7
.text

.struct 0
CONTROL_TRANSFER:	.space 1
ISOCHRONOUS_TRANSFER:	.space 1
BULK_TRANSFER:	.space 1
INTERRUPT_TRANSFER:	.space 1
.text

.struct 1
DEVICE_DESCRIPTOR:	.space 1
CONFIGURATION_DESCRIPTOR:	.space 1
STRING_DESCRIPTOR:	.space 1
INTERFACE_DESCRIPTOR:	.space 1
ENDPOINT_DESCRIPTOR:	.space 1
.text

;-------------------------------------------------------------------------------
; msd bulk structures
;-------------------------------------------------------------------------------

.struct 0
MSD_SUCCESS:	.space 1
MSD_ERROR_INVALID_PARAM:	.space 1
MSD_ERROR_USB_FAILED:	.space 1
MSD_ERROR_SCSI_FAILED:	.space 1
MSD_ERROR_SCSI_CHECK_CONDITION:	.space 1
MSD_ERROR_NOT_SUPPORTED:	.space 1
MSD_ERROR_INVALID_DEVICE:	.space 1
MSD_ERROR_TIMEOUT:	.space 1
.text

;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Initialize a Mass Storage Device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : usb device structure
; return:
;  hl = error status
msd_Open:
	ld	iy, 0
	add	iy, sp
	push	iy
	ld	iy, (iy + 3)		; storage for descriptor (user buffer)
	lea	hl, iy + msd.buffer
	ld	(msd_Open.buffer), hl
	pop	iy
	push	iy
	ld	bc, msd_Open.descriptor_length	; storage for size of descriptor
	push	bc
	ld	bc, 18			; size of device descriptor
	push	bc
	ld	hl, 0			; storage for descriptor (user buffer)
.equ msd_Open.buffer, .-3
	push	hl
	or	a, a
	sbc	hl, hl
	push	hl
	inc	hl			; USB_DEVICE_DESCRIPTOR = 1
	push	hl
	ld	hl, (iy + 6)
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
	ld	de, 18
	ld	hl, 0
.equ msd_Open.descriptor_length, .-3
	compare_hl_de			; ensure enough bytes were fetched
	jp	nz, msd_Open.msddeverror
	ld	hl, (msd_Open.buffer)
	ld	de, 17
	add	hl, de
	ld	a, (hl)
	ld	(msd_Open.num_config), a		; get the number of interfaces
	xor	a, a
	ld	(msd_Open.config), a		; set starting index
	jp	msd_Open.getconfigcheck
msd_Open.getconfiguration:			; bc = index
	push	iy
	ld	c, 0
.equ msd_Open.config, . - 1
	push	bc
	ld	bc, (iy + 6)		; usb device
	push	bc
	call	usb_GetConfigurationDescriptorTotalLength
	pop	bc
	pop	bc
	pop	iy
	push	iy
	ld	bc, msd_Open.config_length	; storage for length of descriptor
	push	bc
	push	hl			; length of configuration descriptor
	ld	bc, (msd_Open.buffer)		; storage for configuration descriptor
	push	bc
	ld	hl, msd_Open.config
	ld	c, (hl)
	push	bc			; configuration index
	inc	(hl)
	ld	bc, 2			; USB_CONFIGURATION_DESCRIPTOR
	push	bc
	ld	bc, (iy + 6)		; usb device
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
	; just grab the first bulk endpoints for a valid msd interface

	xor	a, a
	ld	(msd_Open.interface), a
	ld	(msd_Open.bulkin), a
	ld	(msd_Open.bulkout), a
	ld	hl, 0
.equ msd_Open.config_length, .-3
	ld	(msd_Open.configlengthend), hl
	ld	hl, (msd_Open.buffer)
	ld	(msd_Open.configptr), hl
	push	iy
msd_Open.parseinterfaces:
	ld	hl, (msd_Open.configlengthend)
	ld	de, 2			; check for end of configuration
	compare_hl_de
	jp	c, msd_Open.parsedone		; todo: check if bLength > remaining?
	ld	iy, (msd_Open.configptr)
	ld	a, (iy + descriptor.bDescriptorType)
	cp	a, INTERFACE_DESCRIPTOR
	jr	z, msd_Open.parseinterface
	cp	a, ENDPOINT_DESCRIPTOR
	jr	z, msd_Open.parseendpoint
	jr	msd_Open.parsenext
msd_Open.parseinterface:
	ld	de, (msd_Open.configlengthend)
	ld	(msd_Open.interface_len_rem), de
	ld	(msd_Open.interface_ptr), iy	; store for later set of interface
	ld	a, (iy + interfaceDescriptor.bInterfaceClass)
	cp	a, 0x08
	jr	nz, msd_Open.parsenext
	ld	a, (iy + interfaceDescriptor.bInterfaceSubClass)
	cp	a, 0x06
	jr	nz, msd_Open.parsenext
	ld	a, (iy + interfaceDescriptor.bInterfaceProtocol)
	cp	a, 0x50
	jr	nz, msd_Open.parsenext
	ld	a, (iy + interfaceDescriptor.bInterfaceNumber)
	inc	a
	ld	(msd_Open.interface), a
	jr	msd_Open.parsenext
msd_Open.parseendpoint:
	ld	a, 0			; check if interface set
.equ msd_Open.interface, . - 1
	or	a, a
	jr	z, msd_Open.parsenext
	ld	a, (iy + endpointDescriptor.bmAttributes)
	cp	a, BULK_TRANSFER
	jr	nz, msd_Open.parsenext
	ld	a, (iy + endpointDescriptor.bEndpointAddress)
	ld	b, a
	and	a, DEVICE_TO_HOST
	ld	a, b
	jr	z, msd_Open.parseoutendpointout
msd_Open.parseoutendpointin:
	ld	(msd_Open.bulkin), a
	ld	a, (msd_Open.bulkout)
	or	a, a
	jr	nz, msd_Open.parsedone
	jr	msd_Open.parsenext
msd_Open.parseoutendpointout:
	ld	(msd_Open.bulkout), a
	ld	a, (msd_Open.bulkin)
	or	a, a
	jr	nz, msd_Open.parsedone
msd_Open.parsenext:
	ld	de, 0
	ld	e, (iy + descriptor.bLength)
	ld	hl, 0
.equ msd_Open.configlengthend, . - 3
	or	a, a
	sbc	hl, de
	ld	(msd_Open.configlengthend), hl
	jr	z, msd_Open.parsedone
	ld	hl, 0
.equ msd_Open.configptr, . - 3
	add	hl, de
	ld	(msd_Open.configptr), hl		; move to next interface
	jp	msd_Open.parseinterfaces

msd_Open.parsedone:
	pop	iy
	ld	a, 0
.equ msd_Open.bulkin, . - 1
	or	a, a
	jr	z, msd_Open.getconfigcheck	; no endpoints for msd, keep parsing
	ld	a, 0
.equ msd_Open.bulkout, . - 1
	or	a, a
	jr	z, msd_Open.getconfigcheck	; no endpoints for msd, keep parsing

	ld	bc, (iy + 6)
	ld	iy, (iy + 3)		; setup msd structure with endpoints and buffer
	ld	(iy + msd.dev), bc
	ld	a, (msd_Open.bulkout)
	ld	(iy + msd.bulkout), a
	ld	a, (msd_Open.bulkin)
	ld	(iy + msd.bulkin), a
	ld	a, (msd_Open.config)
	dec	a
	ld	(iy + msd.config), a
	ld	a, (msd_Open.interface)
	dec	a
	ld	(iy + msd.interface), a

	push	iy
	push	bc			; holds the usbdrvce device
	call	usb_RefDevice		; prevent random crashes if the user messes up
	pop	bc
	pop	iy

	push	iy
	ld	bc, 0
.equ msd_Open.interface_len_rem, .-3
	push	bc
	ld	bc, 0
.equ msd_Open.interface_ptr, .-3
	push	bc
	ld	bc, (iy + msd.dev)		; usb device
	push	bc
	call	usb_SetInterface
	pop	bc
	pop	bc
	pop	bc
	pop	iy

	; successfully found bulk endpoints for msd
	; now reset the msd device

	jr	msd_Reset.enter

msd_Open.getconfigcheck:
	ld	a, (msd_Open.config)
	cp	a, 0
.equ msd_Open.num_config, .-1
	jp	nz, msd_Open.getconfiguration
msd_Open.msddeverror:
	ld	hl, MSD_ERROR_INVALID_DEVICE
	ret

;-------------------------------------------------------------------------------
msd_Close:
; Closes and deinitializes the MSD structures.
; args:
;  sp + 3  : msd device structure
; return:
;  hl = error status
	pop	hl
	ex	(sp), iy
	push	hl
	push	iy
	ld	hl, (iy + msd.dev)
	push	hl
	call	usb_UnrefDevice
	pop	de
	pop	de
	add	hl, de
	ld	(hl), 0
	inc	de
	ld	bc, msd_size - 1
	ldir
	ret

;-------------------------------------------------------------------------------
; Attempts to reset and restore normal working order of the device.
; args:
;  sp + 3  : msd device structure
; return:
;  hl = error status
msd_Reset:
	pop	de
	pop	iy
	push	iy
	push	de
msd_Reset.enter:
	ld	hl, (iy + msd.dev)	; check if non-zero msd device
	compare_hl_zero
	jr	z, msd_Reset.invalidparam
	push	iy
	or	a, a
	sbc	hl, hl
	ld	l, (iy + msd.config)
	push	hl
	ld	bc, (iy + msd.dev)	; usb device
	push	bc
	call	usb_GetConfigurationDescriptorTotalLength
	pop	bc
	pop	bc
	pop	iy
	compare_hl_zero
	jr	z, msd_Reset.usberror
	push	iy
	ld	bc, msd_Reset.length		; storage for length of descriptor
	push	bc
	push	hl			; length of configuration descriptor
	lea	hl, iy + msd.buffer
	push	hl
	or	a, a
	sbc	hl, hl
	ld	l, (iy + msd.config)
	push	hl			; configuration index
	ld	l, 2			; USB_CONFIGURATION_DESCRIPTOR
	push	hl
	ld	hl, (iy + msd.dev)
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
	ret	nz			; ensure success
	push	iy
	ld	hl, 0
.equ msd_Reset.length, .-3
	push	hl
	lea	hl, iy + msd.buffer
	push	hl
	ld	hl, (iy + msd.dev)
	push	hl
	call	usb_SetConfiguration
	pop	bc
	pop	bc
	pop	bc
	pop	iy
	compare_hl_zero
	jr	z, msd_Reset.configured
msd_Reset.usberror:
	ld	hl, MSD_ERROR_USB_FAILED
	ret
msd_Reset.invalidparam:
	ld	hl, MSD_ERROR_INVALID_PARAM
	ret
msd_Reset.configured:
	xor	a, a
	sbc	hl, hl
	ld	(iy + msd.haslast), a
	ld	(iy + msd.tag + 0), hl
	ld	(iy + msd.tag + 3), a	; reset tag
;	call	util_msd_reset		; some drives were written by idiots
;	compare_hl_zero			; (looking at you sandisk!) and they
;	ret	nz			; can't be reset -- just don't even try
	call	util_msd_get_max_lun
	compare_hl_zero
	ret	nz
	jp	scsi_init		; return success if init scsi

;-------------------------------------------------------------------------------
; Gets the number of and size of each block (sector) on the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store info to
; return:
;  hl = error status
msd_Info:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	compare_hl_zero
	jr	z, msd_Info.paramerror
	ld	hl, (iy + 6)
	compare_hl_zero
	jr	z, msd_Info.paramerror
	push	iy
	ld	iy, (iy + 3)
	ld	hl, scsi.readcapacity
	call	scsi_sync_command	; store the logical block address / size
	lea	de, iy + msd.buffer
	pop	iy
	jr	nz, msd_Info.error
	ld	hl, (iy + 6)
	ld	bc, 7
	add	hl, bc
	ld	a, (de)
	ld	(hl), a
	inc	de
	dec	hl
	ld	a, (de)
	ld	(hl), a
	inc	de
	dec	hl
	ld	a, (de)
	ld	(hl), a
	inc	de
	dec	hl
	ld	a, (de)
	ld	(hl), a
	inc	de
	dec	hl
	ld	a, (de)
	ld	(hl), a
	inc	de
	dec	hl
	ld	a, (de)
	ld	(hl), a
	inc	de
	dec	hl
	ld	a, (de)
	ld	(hl), a
	inc	de
	dec	hl
	ld	a, (de)
	ld	(hl), a
	xor	a, a
	sbc	hl, hl
	ret
msd_Info.paramerror:
	ld	hl, MSD_ERROR_INVALID_PARAM
	ret
msd_Info.error:
	ld	hl, MSD_ERROR_SCSI_FAILED
	ret

;-------------------------------------------------------------------------------
msd_ReadAsync:
; Asynchronous block read
; inputs:
;  sp + 3: msd transfer struct
; outputs:
;  hl: error status
	ld	iy, 0
	add	iy, sp
	ld	iy, (iy + 3)		; xfer struct
msd_ReadAsync.enter:
	lea	hl, iy + msdXfer.lba
	ld	de, (iy + msdXfer.count)
	push	iy
	ld	iy, scsi.read10
	call	scsi_pktrw_setup
	pop	iy
	ld	hl, scsi.read10
	lea	de, iy + msdXfer.cbw
	ld	bc, packetCBW_size
	ldir
	jp	scsi_async_cbw

;-------------------------------------------------------------------------------
msd_WriteAsync:
; Asynchronous block write
; inputs:
;  sp + 3: msd transfer structure
; outputs:
;  hl: error status
	ld	iy, 0
	add	iy, sp
	ld	iy, (iy + 3)		; xfer struct
	lea	hl, iy + msdXfer.lba
	ld	de, (iy + msdXfer.count)
	push	iy
	ld	iy, scsi.write10
	call	scsi_pktrw_setup
	pop	iy
	ld	hl, scsi.write10
	lea	de, iy + msdXfer.cbw
	ld	bc, packetCBW_size
	ldir
	jp	scsi_async_cbw

;-------------------------------------------------------------------------------
msd_Read:
; Synchronous block read
; inputs:
;  sp + 3: msd struct
;  sp + 6: lba
;  sp + 12: count
;  sp + 15: buffer
; outputs:
;  hl: number of blocks read
	ld	iy, 0
	add	iy, sp
	lea	hl, iy + 6		; lba
	ld	de, (iy + 12)		; count
	push	iy
	ld	iy, scsi.read10
	call	scsi_pktrw_setup
	pop	iy
	push	iy
	ld	de, (iy + 15)
	ld	iy, (iy + 3)
	ld	hl, scsi.read10
	call	scsi_sync_command.buf
	pop	iy
	jr	nz, msd_Read.error
	ld	hl, (iy + 12)		; if no error, return full count
	ret
msd_Read.error:
	xor	a, a
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
msd_Write:
; Synchronous block write
; inputs:
;  sp + 3: msd struct
;  sp + 6: lba
;  sp + 12: count
;  sp + 15: const buffer
; outputs:
;  hl: number of blocks written
	ld	iy, 0
	add	iy, sp
	lea	hl, iy + 6		; lba
	ld	de, (iy + 12)		; count
	push	iy
	ld	iy, scsi.write10
	call	scsi_pktrw_setup
	pop	iy
	push	iy
	ld	de, (iy + 15)
	ld	iy, (iy + 3)
	ld	hl, scsi.write10
	call	scsi_sync_command.buf
	pop	iy
	jr	nz, msd_Write.error
	ld	hl, (iy + 12)		; if no error, return full count
	ret
msd_Write.error:
	xor	a, a
	sbc	hl, hl
	ret

;-------------------------------------------------------------------------------
msd_FindPartitions:
; Locates MBR/EBR/GPT partitions on the MSD
; Arguments:
;  sp + 3 : msd device structure
;  sp + 6 : storage for found partitions
;  sp + 9 : maximum number of partitions to find
; Returns:
;  Number of found partitions
	call	0x130			; frameset0
	xor	a, a
	ld	(msd_FindPartitions.smc.num_partitions), a
	ld	a, (ix + 9 + 3)
	or	a, a
	jr	z, msd_FindPartitions.done
	ld	(msd_FindPartitions.smc.max_partitions), a
	ld	(msd_FindPartitions.smc.max_gpt_partitions), a
	ld	hl, (ix + 6 + 3)
	ld	(msd_FindPartitions.smc.partitions), hl
	ld	hl, (ix + 3 + 3)
	ld	(msd_FindPartitions.smc.msd), hl
	sbc	hl, hl			; start at partition 0
	push	hl
	push	hl
	call	msd_FindPartitions.recursive_loop
msd_FindPartitions.done:
	ld	sp, ix
	pop	ix
	ld	a, 0
.equ msd_FindPartitions.smc.num_partitions, .-1
	cp	a, 1			; protective MBR, maybe GPT
	ret	nz
	jp	msd_FindPartitions.check_for_gpt
msd_FindPartitions.recursive_loop:
	ld	hl, -74
	call	0x12C			; frameset
	ld	iy, 0
.equ msd_FindPartitions.smc.msd, .-3
	lea	hl, ix + 6
	call	scsi_read_block
	jr	nz, msd_FindPartitions.return
	call	util_check_mbr_magic
	jr	nz, msd_FindPartitions.return
	lea	hl, iy + msd.buffer
	ld	de, 446
	add	hl, de
	lea	de, ix - 64
	ld	bc, 64
	ldir
	ld	iy, 0
msd_FindPartitions.for_each_entry:
	ld	de, 64
	lea	hl, iy+0
	or	a, a
	sbc	hl, de
	jr	nz, msd_FindPartitions.no_return
msd_FindPartitions.return:
	ld	sp, ix
	pop	ix
	ret
msd_FindPartitions.no_return:
	ld	a, (msd_FindPartitions.smc.num_partitions)
	cp	a, 0
.equ msd_FindPartitions.smc.max_partitions, .-1
	jr	z, msd_FindPartitions.return
	ld	(ix - 70), iy
	lea	iy, ix - 64
	ld	hl, (iy + 8)
	ld	e, (iy + 11)
	call	0x1B0			; check zero
	jr	z, msd_FindPartitions.continue
	ld	de, (ix - 70)
	lea	iy, ix - 64
	add	iy, de
	ld	hl, (iy + 12)
	ld	e, (iy + 15)
	ld	(ix - 73), hl
	ld	(ix - 74), e
	call	0x1B0			; check zero
	jr	z, msd_FindPartitions.continue
	ld	hl, (iy + 8)
	ld	e, (iy + 11)
	ld	bc, (ix + 6)
	ld	a, (ix + 9)
	add	hl, bc
	adc	a, e
	ld	e, a
	ld	bc, (ix - 70)
	lea	iy, ix - 64
	add	iy, bc
	ld	a, (iy + 4)
	cp	a, 0x05
	jr	z, msd_FindPartitions.ebr
	cp	a, 0x0F
	jr	nz, msd_FindPartitions.not_ebr
msd_FindPartitions.ebr:
	push	de
	push	hl
	call	msd_FindPartitions.recursive_loop
	pop	hl
	pop	hl
	jr	msd_FindPartitions.continue
msd_FindPartitions.not_ebr:
	ld	iy, 0
.equ msd_FindPartitions.smc.partitions, .-3
	ld	(iy + 0), hl
	ld	(iy + 3), e
	ld	bc, -1
	add	hl, bc
	adc	a, c
	ld	bc, (ix - 73)
	add	hl, bc
	adc	a, (ix - 74)
	ld	(iy + 4), hl
	ld	(iy + 7), a
	lea	hl, iy + 8
	ld	(msd_FindPartitions.smc.partitions), hl
	ld	hl, msd_FindPartitions.smc.num_partitions
	inc	(hl)
msd_FindPartitions.continue:
	ld	iy, (ix - 70)
	lea	iy, iy + 16
	jp	msd_FindPartitions.for_each_entry
msd_FindPartitions.check_for_gpt:
	ld	hl, msd_FindPartitions.gpt_lba
	ld	iy, (msd_FindPartitions.smc.msd)
	call	scsi_read_block		; read lba 1
	lea	hl, iy + msd.buffer
	ld	de, msd_FindPartitions.gpt_signature
	ld	b, 8
msd_FindPartitions.check_gpt_signature:
	ld	a, (de)
	cp	a, (hl)
	jr	z, msd_FindPartitions.maybe_gpt
	ld	a, 1			; just return the mbr
	ret
msd_FindPartitions.maybe_gpt:
	inc	hl
	inc	de
	djnz	msd_FindPartitions.check_gpt_signature
	ld	a, (iy + msd.buffer + 0x50)	; number of entries
	ld	hl, (iy + msd.buffer + 0x51)	; only try to get the first 63 lbas
	compare_hl_zero
	jr	z, msd_FindPartitions.reasonable_gpt
	ld	a, 255
msd_FindPartitions.reasonable_gpt:
	srl	a
	srl	a			; divide by 4
	ld	(msd_FindPartitions.smc.num_gpt_loops), a
	xor	a, a
	ld	(msd_FindPartitions.smc.num_partitions), a
	ld	hl, (iy + msd.buffer + 0x54)
	ld	de, 128
	compare_hl_de
	ret	nz			; only support 128 byte entry sizes
	lea	hl, iy + msd.buffer + 0x48	; parition table lba
	ld	de, msd_FindPartitions.gpt_entry_lba
	ldi
	ldi
	ldi
	ldi
	ld	iy, (msd_FindPartitions.smc.partitions)
	lea	hl, iy - 8
	ld	(msd_FindPartitions.smc.partitions), hl	; remove the first partition
	ex	de, hl
msd_FindPartitions.gpt_loop:
	push	de
	ld	hl, msd_FindPartitions.gpt_entry_lba
	ld	iy, (msd_FindPartitions.smc.msd)
	call	scsi_read_block
	ld	hl, (msd_FindPartitions.gpt_entry_lba)
	ld	a, (msd_FindPartitions.gpt_entry_lba + 3)
	ld	bc, 1
	add	hl, bc
	adc	a, b
	ld	(msd_FindPartitions.gpt_entry_lba), hl
	ld	(msd_FindPartitions.gpt_entry_lba + 3), a
	pop	de
	lea	hl, iy + msd.buffer + 0x20	; first lba
	ld	c, 4
msd_FindPartitions.get_gpt_entries:
	push	hl
	ld	b, 8
msd_FindPartitions.check_gpt_end:
	ld	a, (hl)
	or	a, a
	jr	nz, msd_FindPartitions.not_gpt_end
	inc	hl
	djnz	msd_FindPartitions.check_gpt_end
	pop	hl			; reached end of list if slba = 0
	ld	a, (msd_FindPartitions.smc.num_partitions)
	ret
msd_FindPartitions.not_gpt_end:
	pop	hl
	push	hl
	push	de
	push	bc
	ldi
	ldi
	ldi
	ldi				; only support 32-bit lba :(
	ld	b, 4
msd_FindPartitions.check_slba:
	ld	a, (hl)
	or	a, a
	jr	nz, msd_FindPartitions.skip_entry
	inc	hl
	djnz	msd_FindPartitions.check_slba
	ldi
	ldi
	ldi
	ldi				; only support 32-bit lba :(
	ld	b, 4
msd_FindPartitions.check_elba:
	ld	a, (hl)
	or	a, a
	jr	nz, msd_FindPartitions.skip_entry
	inc	hl
	djnz	msd_FindPartitions.check_elba
	pop	bc
	ld	a, (msd_FindPartitions.smc.num_partitions)
	inc	a
	ld	(msd_FindPartitions.smc.num_partitions), a
	cp	a, 0
.equ msd_FindPartitions.smc.max_gpt_partitions, .-1
	jr	nz, msd_FindPartitions.not_gpt_max
	pop	de
	pop	hl
	ld	a, (msd_FindPartitions.smc.num_partitions)
	ret
msd_FindPartitions.not_gpt_max:
	push	bc
msd_FindPartitions.skip_entry:
	pop	bc
	pop	hl
	ld	de, 8
	add	hl, de
	ex	de, hl
	pop	hl			; entry pointer
	push	de
	ld	de, 128
	add	hl, de
	pop	de
	dec	c
	jr	nz, msd_FindPartitions.get_gpt_entries
	ld	a, 0
.equ msd_FindPartitions.smc.num_gpt_loops, .-1
	dec	a
	ld	(msd_FindPartitions.smc.num_gpt_loops), a
	ld	a, (msd_FindPartitions.smc.num_partitions)
	ret	z
	jp	msd_FindPartitions.gpt_loop
msd_FindPartitions.gpt_signature:
	.db	0x45, 0x46, 0x49, 0x20, 0x50, 0x41, 0x52, 0x54
msd_FindPartitions.gpt_lba:
	.db	1, 0, 0, 0
msd_FindPartitions.gpt_entry_lba:
	.db	0, 0, 0, 0

;-------------------------------------------------------------------------------
; utility functions
;-------------------------------------------------------------------------------

; inputs:
;  iy : msd struct
scsi_init:
	ld	b, 5			; number of inquire retries
scsi_init.loop:
	push	bc
	ld	hl, scsi.inquiry		; some devices are slow to start
	call	scsi_sync_command
	pop	bc
	jr	z, scsi_test_unit_ready
	call	util_delay_200ms
	djnz	scsi_init.loop
scsi_init.error:
	ld	hl, MSD_ERROR_SCSI_FAILED
	ret
scsi_test_unit_ready:
	ld	b, 15			; number of test unit retries
scsi_test_unit_ready.loop:
	push	bc
	ld	hl, scsi.testunitready
	call	scsi_sync_command
	jr	z, scsi_test_unit_ready.done
	ld	hl, scsi.requestsense
	call	scsi_sync_command
	pop	bc
	jr	nz, scsi_init.error
	call	util_delay_200ms
	djnz	scsi_test_unit_ready.loop
	jr	scsi_init.error
scsi_test_unit_ready.done:
	pop	bc
scsi_read_capacity:
	ld	b, 5			; number of read capacitiy retries
scsi_read_capacity.loop:
	push	bc
	ld	hl, scsi.readcapacity
	call	scsi_sync_command
	jr	z, scsi_read_capacity.done
	ld	hl, scsi.requestsense
	call	scsi_sync_command
	pop	bc
	jr	nz, scsi_init.error
	call	util_delay_200ms
	djnz	scsi_read_capacity.loop
	jr	scsi_init.error
scsi_read_capacity.done:
	pop	bc
	xor	a, a
	sbc	hl, hl			; success
	ret

; inputs:
;  sp + 3 : status
;  sp + 6 : xfer
scsi_sync_command_callback:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)		; status
	compare_hl_zero
	ld	hl, scsi_sync_command.done
	jr	nz, scsi_sync_command_callback.fail
	set	0, (hl)			; success
	or	a, a
	sbc	hl, hl
	ret
scsi_sync_command_callback.fail:
	set	1, (hl)
	or	a, a
	sbc	hl, hl
	ret

; inputs:
;  iy : msd struct
;  hl : cbw structure
; outputs:
;   z : success
scsi_sync_command:
	lea	de, iy + msd.buffer		; use the user buffer by default
scsi_sync_command.buf:
	push	iy
	ld	(scsi_sync_command.xfer), iy		; first element is msd
	ld	iy, scsi_sync_command.xfer
	ld	(iy + msdXfer.buffer), de
	lea	de, iy + msdXfer.cbw
	ld	bc, packetCBW_size
	ldir				; copy cbw to packet structure
	ld	de, scsi_sync_command_callback
	ld	(iy + msdXfer.callback), de
	xor	a, a
	ld	(scsi_sync_command.done), a
	call	scsi_async_cbw
	compare_hl_zero			; make sure it succeeded
	jr	nz, scsi_sync_command.fail
scsi_sync_command.wait_done:
	call	usb_HandleEvents	; todo: add timeout in here?
	compare_hl_zero
	jr	nz, scsi_sync_command.fail
	ld	a, 0
.equ scsi_sync_command.done, .-1
	or	a, a
	jr	z, scsi_sync_command.wait_done
	bit	1, a			; nz = fail, z = success
scsi_sync_command.fail:
	pop	iy
	ret
scsi_sync_command.xfer:
	.space msdXfer_size

; inputs:
;  iy : xfer struct
scsi_async_cbw:
	xor	a, a
	sbc	hl, hl
	ld	(iy + msdXfer.next), hl	; clear next pointer
	ld	(iy + msdXfer.stall), a	; clear stall for csw
	ld	hl, (iy + msdXfer.cbw + packetCBW.len)
	push	iy
	lea	de, iy+0			; de = xfer struct
	ld	iy, (iy + msdXfer.msd)
	or	a, (iy + msd.haslast)
	jr	z, scsi_async_cbw.send
scsi_async_cbw.queue:					; if currently sending, queue it
	lea	hl, iy + msd.last
	ld	iy, (hl)
	ld	(iy + msdXfer.next), de	; queue the next bulk transfer
	ld	(hl), de			; make this xfer the new last
	pop	iy
	xor	a, a
	sbc	hl, hl			; return success
	ret
scsi_async_cbw.send:
	ld	(iy + msd.last), de
	ld	(iy + msd.haslast), 1
scsi_async_cbw.do_xfer:
	inc	(iy + msd.tag)		; incremet cbw tag
	jr	nz, scsi_async_cbw.skip
	ld	de, (iy + msd.tag + 1)
	inc	de
	ld	(iy + msd.tag + 1), de
scsi_async_cbw.skip:
	ld	c, (iy + msd.bulkout)
	compare_hl_zero			; check if cbw length is zero
	ld	hl, scsi_async_data
	jr	nz, scsi_async_cbw.not_zero_length
	ld	hl, scsi_async_csw	; if zero length, skip data callback
scsi_async_cbw.not_zero_length:
	ld	de, (iy + msd.tag)
	ld	a, (iy + msd.tag + 3)
	pop	iy
	push	iy
	lea	iy, iy + msdXfer.cbw
	ld	(iy + packetCBW.tag), de
	ld	(iy + packetCBW.tag + 3), a
	pop	iy
	lea	de, iy + msdXfer.cbw		; send cbw
	ld	a, c
	ld	bc, packetCBW_size
	jr	scsi_async_xfer

; inputs:
;  sp + 3 : endpoint
;  sp + 6 : status
;  sp + 9 : transferred size
;  sp + 12 : data
scsi_async_data:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)		; verify cbw transfer
	compare_hl_zero
	ld	iy, (iy + 12)		; xfer struct
	jp	nz, scsi_async_issue_callback_fail
	bit	7, (iy + msdXfer.cbw + packetCBW.dir)
	push	iy
	ld	iy, (iy + msdXfer.msd)	; get msd struct
	ld	a, (iy + msd.bulkin)
	jr	nz, scsi_async_data.xfer
	ld	a, (iy + msd.bulkout)
scsi_async_data.xfer:
	pop	iy			; restore xfer struct
	ld	hl, scsi_async_csw
	ld	de, (iy + msdXfer.buffer)
	ld	bc, (iy + msdXfer.cbw + packetCBW.len)
	jr	scsi_async_xfer

; inputs:
;  sp + 3 : endpoint
;  sp + 6 : status
;  sp + 9 : transferred size
;  sp + 12 : data
scsi_async_csw:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)		; verify cbw transfer
	compare_hl_zero
	ld	iy, (iy + 12)		; xfer struct
	jr	nz, scsi_async_issue_callback_fail
scsi_async_csw.retry:
	push	iy
	ld	iy, (iy + msdXfer.msd)	; msd struct
	ld	a, (iy + msd.bulkin)
	pop	iy			; restore xfer struct
	lea	de, iy + msdXfer.csw
	ld	bc, packetCSW_size
	ld	hl, scsi_async_done

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
	or	a, a
	sbc	hl, hl			; todo: is this needed
	ld	l, a			; endpoint
	push	hl
	ld	iy, (iy + msdXfer.msd)	; msd struct
	ld	hl, (iy + msd.dev)		; usb struct
	push	hl
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc
	push	hl
	call	usb_ScheduleTransfer
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
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
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)		; verify cbw transfer
	compare_hl_zero
	ld	iy, (iy + 12)		; xfer struct
	jr	nz, scsi_async_done.check_stall
	ld	a, (iy + msdXfer.csw + packetCSW.status)
	or	a, a			; cmd success
	ld	bc, MSD_SUCCESS
	jr	z, scsi_async_issue_callback
	dec	a			; cmd failed (but valid csw)
	ld	c, MSD_ERROR_SCSI_CHECK_CONDITION
	jr	z, scsi_async_issue_callback
scsi_async_done.check_stall:
	bit	0, l			; USB_TRANSFER_STALLED
	jr	z, scsi_async_done.failed
	bit	0, (iy + msdXfer.stall)
	set	0, (iy + msdXfer.stall)	; retry once if stalled
	jr	z, scsi_async_csw.retry
scsi_async_done.failed:

; inputs:
;  iy : xfer struct
scsi_async_issue_callback_fail:
;	push	iy			; some drives die upon reset
;	call	scsi_reset_recovery	; so just don't reset them, even though
;	pop	iy			; the spec says I should
	ld	bc, MSD_ERROR_SCSI_FAILED

; inputs:
;  de : status
;  iy : xfer struct
scsi_async_issue_callback:
	push	iy
	lea	de, iy+0
	ld	iy, (iy + msdXfer.msd)
	ld	hl, (iy + msd.last)
	compare_hl_de
	jr	nz, scsi_async_issue_callback.dont_clear		; if xfer->msd->last == xfer
	ld	(iy + msd.haslast), 0	; xfer->msd->last = NULL
scsi_async_issue_callback.dont_clear:
	pop	iy
	ld	hl, (iy + msdXfer.next)
	push	hl
	ld	hl, (iy + msdXfer.callback)
	compare_hl_zero
	jr	z, scsi_async_issue_callback.no_callback
	push	iy
	push	bc
	ld	bc, scsi_async_issue_callback.return
	push	bc
	jp	(hl)
scsi_async_issue_callback.return:
	pop	de
	pop	iy
scsi_async_issue_callback.no_callback:
	pop	hl
	compare_hl_zero			; if there's a next pointer, issue it
	ret	z
	push	hl
	ld	iy, (hl)			; msd is first element in xfer
	jp	scsi_async_cbw.do_xfer	; send the next cbw

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
	ld	a, (iy + msd.interface)
	ld	(setup.msdmaxlun + 4), a
	ld	hl, setup.msdmaxlun
	lea	de, iy + msd.buffer

; inputs:
;  iy : msd structure
;  hl : packet
;  de : location to store data to
util_msd_ctl_packet:
	push	iy
	ld	bc, 0
	push	bc			; don't care about callback data
	ld	bc, util_msd_ctl_packet.callback		; callback
	push	bc
	push	de			; send data packet
	push	hl			; send setup packet
	xor	a, a
	sbc	hl, hl
	push	hl
	ld	(util_msd_ctl_packet.done), a
	ld	bc, (iy + msd.dev)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc
	push	hl
	call	usb_ScheduleControlTransfer
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	compare_hl_zero
	jr	nz, util_msd_ctl_packet.fail
	ld	hl, 2
	push	hl
	ld	hl, 14445568		; ~1 second timeout
	push	hl
	ld	hl, util_msd_ctl_packet.struct
	push	hl
	call	usb_StartTimerCycles	; set up timeout
	pop	bc
	pop	bc
	pop	bc
util_msd_ctl_packet.wait:
	call	usb_HandleEvents	; todo: add timeout in here?
	compare_hl_zero
	jr	nz, util_msd_ctl_packet.fail
	ld	a, 0
.equ util_msd_ctl_packet.done, .-1
	or	a, a
	jr	z, util_msd_ctl_packet.wait
util_msd_ctl_packet.fail:
	pop	iy
	ret
util_msd_ctl_packet.callback:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 6)		; get transfer status
util_msd_ctl_packet.complete:
	ld	a, 1
	ld	(util_msd_ctl_packet.done), a
	ret
util_msd_ctl_packet.timeout:
	ld	hl, MSD_ERROR_TIMEOUT
	jr	util_msd_ctl_packet.complete
util_msd_ctl_packet.struct:
	.d32	0
	.d24	0
	.d24	util_msd_ctl_packet.timeout

; inputs:
;  hl : points to lba
;  de : count
;  iy : scsi.read10 or scsi.write10
scsi_pktrw_setup:
	lea	bc, iy + scsipktrw.lba + 3
	ld	a, (hl)
	ld	(bc), a
	inc	hl
	dec	bc
	ld	a, (hl)
	ld	(bc), a
	inc	hl
	dec	bc
	ld	a, (hl)
	ld	(bc), a
	inc	hl
	dec	bc
	ld	a, (hl)
	ld	(bc), a			; store big endian fields
	ld	(iy + scsipktrw.len + 0), d
	ld	(iy + scsipktrw.len + 1), e
	ex	de, hl
	add	hl, hl			; assume block size of 512
	ld	(iy + 9), hl	; number of bytes in data section
	ret

scsi_read_block:
	ld	de, 1
scsi_read_blocks:
	push	iy
	ld	iy, scsi.read10
	push	iy
	call	scsi_pktrw_setup
	pop	hl
	pop	iy
	jp	scsi_sync_command

util_delay_200ms:
	ld	a, 20
util_delay_200ms.loop:
	push	af
	push	bc
	call	0x3B4			; waits for ~10ms
	pop	bc
	pop	af
	dec	a
	jr	nz, util_delay_200ms.loop
	ret

;  iy : msd struct
util_check_mbr_magic:
	push	hl
	push	de
	lea	hl, iy + msd.buffer
	ld	de, 510
	add	hl, de
	ld	de, (hl)
	ld	hl, 0xAA55
	ex.s	de, hl
	compare_hl_de
	pop	de
	pop	hl
	ret

;-------------------------------------------------------------------------------
; utility data
;-------------------------------------------------------------------------------

;setup.msdreset          setuppkt        $21,$ff,0,0,0
setup.msdmaxlun:
	setup_packet 0xa1,0xfe,0,0,1

scsi.inquiry:
	scsi_packet 1, 0x05, 6, 0x12, 0x00, 0x00, 0x00, 0x05, 0x00
scsi.modesense:
	scsi_packet 1, 0xc0, 6, 0x1a, 0x00, 0x3f, 0x00, 0xc0, 0x00
scsi.requestsense:
	scsi_packet 1, 0x12, 6, 0x03, 0x00, 0x00, 0x00, 0x12, 0x00
scsi.testunitready:
	scsi_packet 0, 0x00, 6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
scsi.readcapacity:
	scsi_packet 1, 0x08, 10, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

scsi.read10:
	scsi_rw_packet 1, 0x28
scsi.write10:
	scsi_rw_packet 0, 0x2a
