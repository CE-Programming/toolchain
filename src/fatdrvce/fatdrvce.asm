;-------------------------------------------------------------------------------
; fatdrvce: Provides MSD and FAT API functions for the TI84+CE calculators.
; Copyright (C) 2019 MateoConLechuga, jacobly0
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU Lesser General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU Lesser General Public License for more details.
;
; You should have received a copy of the GNU Lesser General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; Includes
;-------------------------------------------------------------------------------
include '../include/library.inc'
include '../include/include_library.inc'

library 'FATDRVCE',1

;-------------------------------------------------------------------------------
; Dependencies
;-------------------------------------------------------------------------------
include_library '../usbdrvce/usbdrvce.asm'

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export msd_Init
	export msd_IsInit
	export msd_Deinit
	export msd_Reset
	export msd_GetSectorCount
	export msd_GetSectorSize
	export msd_ReadSectors
	export msd_WriteSectors
	export fat_Find
	export fat_Init
	export fat_Deinit
	export fat_DirList
	export fat_GetVolumeLabel
	export fat_Open
	export fat_Close
	export fat_SetSize
	export fat_GetSize
	export fat_SetAttrib
	export fat_GetAttrib
	export fat_SetFilePos
	export fat_GetFilePos
	export fat_ReadSectors
	export fat_WriteSectors
	export fat_Create
	export fat_Delete
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
macro compare_hl_zero?
	add	hl,de
	or	a,a
	sbc	hl,de
end macro

macro compare_auhl_zero?
	compare_hl_zero
	jr	nz,$+3
	or	a,a
end macro

macro compare_hl_de?
	or	a,a
	sbc	hl,de
	add	hl,de
end macro

macro compare_bc_zero?
	push	hl
	sbc	hl,hl
	adc	hl,bc
	pop	hl
end macro

;-------------------------------------------------------------------------------
; memory structures
;-------------------------------------------------------------------------------
macro ?!
 macro assertpo2? value*
  local val
  val = value
  if ~val | val <> 1 shl bsr val
   err '"', `value, '" is not a power of two'
  end if
 end macro

 iterate op, bit, res, set
  macro op#msk? index*, value
   local idx, val, rest
   idx = index
   assertpo2 idx
   match @, value
    val equ value
   else
    val equ
    rest equ index
    while 1
     match car.cdr, rest
      match any, val
       val equ any.car
      else
       val equ car
      end match
      rest equ cdr
     else
      val equ (val)
      break
     end match
    end while
   end match
   match v, val
	op	bsr idx,v
   end match
  end macro
 end iterate

 macro struct? name*, parameters&
  macro end?.struct?!
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

 macro ld? @dst, @mid*, @src
  local dst, mid, src
   iterate <arg,@arg>, dst,@dst, mid,@mid, src,@src
    @ez80.classify arg, @arg
    @ez80.size arg
   end iterate
   if ~defined src
    ld? @dst, @mid
   else if dst.ind & src.ind | mid.ind
    err 'invalid indirection'
   else if dst.ind & defined src.size
    ld? (dst), src
    ld? (dst + src.size), mid
   else if src.ind & defined mid.size
    ld? mid, (src)
    ld? dst, (src + mid.size)
   else
    err 'invalid arguments'
   end if
  end macro

 purge ?
end macro

; msd structures
struct packetCSW
	label .: 13
	signature rd 1
	tag rd 1
	residue rd 1
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
	signature rd 1
	tag rd 1
	len rd 1
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
	lba rd 1
	reserved rb 1	; technically part of block size
	blocksize rl 1
	interface rb 1
	maxlun rb 1
	flags rb 1
	lun rb 1
	buffer rl 1
	size := $-.
end struct

MSD_FLAG_IS_INIT := 0
MAX_FAT_FILES := 5
BIT_READ := 0
BIT_WRITE := 1
BIT_OPEN := 7

struct fatFile
	local size
	label .: size
	fat rl 1
	flags rb 1
	entry_sector rd 1
	first_cluster rd 1
	current_cluster rd 1
	file_size rd 1
	file_size_sectors rl 1
	fpossector rl 1
	cluster_sector rb 1
	current_sector rd 1
	working_buffer rl 1
	entry_pointer rl 1
	size := $-.
end struct
struct fatPartition
	local size
	label .: size
	lba rd 1
	msd rl 1
	size := $-.
end struct
struct fatType
	local size
	label .: size
	partition rl 1
	cluster_size rb 1
	clusters rd 1
	fat_size rl 1
	fat_pos rl 1
	fs_info rl 1
	fat_base_lba rd 1
	root_dir_pos rd 1
	data_region rd 1
	working_sector rd 1
	working_cluster rd 1
	working_next_cluster rd 1
	working_prev_cluster rd 1
	working_size rd 1
	working_pointer rl 1
	working_entry rl 1
	working_next_entry rl 1
	working_prev_entry rl 1
	size := $-.
end struct
struct fatDirEntry
	local size
	label .: size
	name rb 13
	attrib rb 1
	entrysize rd 1
	size := $-.
end struct

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
	rb 31 ; padding needed because some msd drives were built by idiots
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

; enum usb_transfer_direction
virtual at 0
	?HOST_TO_DEVICE rb 1 shl 7
	?DEVICE_TO_HOST rb 1 shl 7
end virtual

virtual at 0
	FAT_SUCCESS rb 1
	FAT_ERROR_INVALID_PARAM rb 1
	FAT_ERROR_USB_FAILED rb 1
	FAT_ERROR_NOT_SUPPORTED rb 1
	FAT_ERROR_INVALID_CLUSTER rb 1
	FAT_ERROR_EOF rb 1
	FAT_ERROR_EXISTS rb 1
	FAT_ERROR_INVALID_PATH rb 1
	FAT_ERROR_FAILED_ALLOC rb 1
	FAT_ERROR_CLUSTER_CHAIN rb 1
	FAT_ERROR_DIRECTORY_NOT_EMPTY rb 1
	FAT_ERROR_NO_VOLUME_LABEL rb 1
	FAT_ERROR_RDONLY rb 1
	FAT_ERROR_WRONLY rb 1
end virtual

virtual at 0
	MSD_SUCCESS rb 1
	MSD_ERROR_INVALID_PARAM rb 1
	MSD_ERROR_USB_FAILED rb 1
	MSD_ERROR_NOT_SUPPORTED rb 1
	MSD_ERROR_INVALID_DEVICE rb 1
	MSD_ERROR_NOT_INITIALIZED rb 1
end virtual

virtual at 0
	FAT_LIST_FILEONLY rb 1
	FAT_LIST_DIRONLY rb 1
	FAT_LIST_ALL rb 1
end virtual

; enum usb_descriptor_type
virtual at 1
	?DEVICE_DESCRIPTOR rb 1
	?CONFIGURATION_DESCRIPTOR rb 1
	?STRING_DESCRIPTOR rb 1
	?INTERFACE_DESCRIPTOR rb 1
	?ENDPOINT_DESCRIPTOR rb 1
end virtual

; enum usb_transfer_type
virtual at 0
	?CONTROL_TRANSFER rb 1
	?ISOCHRONOUS_TRANSFER rb 1
	?BULK_TRANSFER rb 1
	?INTERRUPT_TRANSFER rb 1
end virtual

struct tmp_data
	local size
	label .: size
	sensecount rb 1
	sensebuffer rb 512	; todo: evaluate if needed
	sectorbuffer rb 576	; todo: evaluate if user-supplied
	length rl 1
	descriptor rb 18
	msdstruct rl 1
	string rb 20
	csw packetCSW
	size := $-.
end struct

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
	push	ix
	ld	ix,(iy + 3)
	res	MSD_FLAG_IS_INIT,(xmsdDevice.flags)
	pop	ix
	ld	hl,(iy + 6)		; usb device
	compare_hl_zero
	jq	z,.paramerror
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
	jq	nz,.msddeverror
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
	ld	(.bulkinaddr),a
	ld	(.bulkoutaddr),a
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

	; successfully found bulk endpoints for msd
	; now reset the device

	call	msd_Reset.enter
	compare_hl_zero
	ret	nz
	set	MSD_FLAG_IS_INIT,(ymsdDevice.flags)
	or	a,a
	sbc	hl,hl
	ret

.getconfigcheck:
	ld	hl,tmp.descriptor + 17
	ld	a,(.configindex)
	cp	a,(hl)
	jq	nz,.getconfiguration
.msddeverror:
	ld	hl,MSD_ERROR_INVALID_DEVICE
	ret
.usberror:
	ld	hl,MSD_ERROR_USB_FAILED
	ret
.paramerror:
	ld	hl,MSD_ERROR_INVALID_PARAM
	ret

;-------------------------------------------------------------------------------
msd_IsInit:
; Checks if the MSD has been successfully initialized.
; args:
;  sp + 3  : msd device structure
; return:
;  hl = error status
	ld	iy,0
	add	iy,sp
	ld	iy,(iy + 3)
	bit	MSD_FLAG_IS_INIT,(ymsdDevice.flags)
	jq	z,.notinit
	or	a,a
	sbc	hl,hl
	ret
.notinit:
	ld	hl,MSD_ERROR_NOT_INITIALIZED
	ret

;-------------------------------------------------------------------------------
msd_Deinit:
; Deinitializes the MSD structure as needed.
; args:
;  sp + 3  : msd device structure
; return:
;  hl = error status
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 3)
	push	hl
	pop	de
	ld	(hl),0
	inc	hl
	ld	bc,sizeof msdDevice
	ldir
	ret

;-------------------------------------------------------------------------------
msd_Reset:
; Attempts to reset and restore normal working order.
; args:
;  sp + 3  : msd device structure
; return:
;  hl = error status
	pop	de,iy
	push	iy,de
	bit	MSD_FLAG_IS_INIT,(ymsdDevice.flags)
	jq	nz,.enter
	ld	hl,MSD_ERROR_NOT_INITIALIZED
	ret
.enter:
	push	iy
	ld	bc,0
	ld	c,(ymsdDevice.configindex)
	push	bc
	ld	bc,(ymsdDevice.dev)	; usb device
	push	bc
	call	usb_GetConfigurationDescriptorTotalLength
	pop	bc,bc
	pop	iy
	compare_hl_zero
	jq	z,.usberror
	push	iy
	ld	bc,tmp.length		; storage for length of descriptor
	push	bc
	push	hl			; length of configuration descriptor
	ld	bc,(ymsdDevice.buffer)
	push	bc
	ld	bc,0
	ld	c,(ymsdDevice.configindex)
	push	bc			; configuration index
	ld	bc,2			; USB_CONFIGURATION_DESCRIPTOR
	push	bc
	ld	bc,(ymsdDevice.dev)
	push	bc
	call	usb_GetDescriptor
	pop	bc,bc,bc,bc,bc,bc
	pop	iy
	compare_hl_zero
	jq	nz,.usberror			; ensure success
	push	iy
	ld	bc,(tmp.length)
	push	bc
	ld	bc,(ymsdDevice.buffer)
	push	bc
	ld	bc,(ymsdDevice.dev)
	push	bc
	call	usb_SetConfiguration
	pop	bc
	pop	bc
	pop	bc
	pop	iy
	compare_hl_zero
	jq	z,.configuredmsd
.usberror:
	ld	hl,MSD_ERROR_USB_FAILED
	ret
.configuredmsd:
	call	util_msd_reset
	compare_hl_zero
	jq	nz,.usberror
	call	util_msd_get_max_lun
	compare_hl_zero
	jq	nz,.usberror
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
	jr	z,.paramerror
	ld	hl,(iy + 6)
	compare_hl_zero
	jr	z,.paramerror
	push	hl
	ld	iy,(iy + 3)
	ld	hl,scsi.readcapacity
	lea	de,ymsdDevice.lba
	call	util_scsi_request	; store the logical block address / size
	pop	hl
	jr	nz,.error
	ld	de,(ymsdDevice.blocksize)
	ld	(hl),de
	or	a,a
	sbc	hl,hl
	ret
.paramerror:
	ld	hl,MSD_ERROR_INVALID_PARAM
	ret
.error:
	ld	hl,MSD_ERROR_USB_FAILED
	ret

;-------------------------------------------------------------------------------
; Gets the sector count of the device.
; args:
;  sp + 3  : msd device structure
;  sp + 6  : pointer to store sector count to
; return:
;  hl = error status
msd_GetSectorCount:
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
	lea	de,ymsdDevice.lba
	push	de
	call	util_scsi_request	; store the logical block address / size
	pop	hl
	pop	iy
	jr	nz,.error
	ld	de,(iy + 6)
	ld	bc,4
	ldir
	or	a,a
	sbc	hl,hl
	ret
.paramerror:
	ld	hl,MSD_ERROR_INVALID_PARAM
	ret
.error:
	ld	hl,MSD_ERROR_USB_FAILED
	ret

;-------------------------------------------------------------------------------
msd_ReadSectors:
; Reads sectors from a Mass Storage Device
; inputs:
;  sp + 3: msd device structure
;  sp + 6 & 9: first lba
;  sp + 12: number of sectors
;  sp + 15: user buffer to read into
; outputs:
;  hl: error status
	push	ix
	ld	ix,scsi.read10
	jq	util_msd_read_write_sectors

;-------------------------------------------------------------------------------
msd_WriteSectors:
; Writes sectors to a Mass Storage Device
; inputs:
;  sp + 3: msd device structure
;  sp + 6 & 9: first lba
;  sp + 12: number of sectors
;  sp + 15: user buffer to write from
; outputs:
;  hl: error status
	push	ix
	ld	ix,scsi.write10
	jq	util_msd_read_write_sectors

;-------------------------------------------------------------------------------
; utility functions
;-------------------------------------------------------------------------------

util_msd_read_write_sectors:
	ld	iy,3
	add	iy,sp
	lea	hl,iy + 6
	lea	de,xscsipktrw.lba + 3
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
	lea	hl,xscsipktrw.len
	ld	de,(iy + 12)
	ld	(hl),d
	inc	hl
	ld	(hl),e
	ex	de,hl
	add	hl,hl
	ld	(xscsipktrw + 9),hl
	ld	de,(iy + 15)
	ld	iy,(iy + 3)
	lea	hl,xscsipktrw
	call	util_scsi_request
	pop	ix
	ld	hl,MSD_ERROR_USB_FAILED
	ret	nz
	or	a,a
	sbc	hl,hl			; return success
	ret

util_scsi_init:
	ld	hl,scsi.inquiry
	call	util_scsi_request_default
	jr	nz,.error
.unitattention:
	ld	hl,scsi.testunitready
	call	util_scsi_request_default
	jr	nz,.error
	and	a,$f
	cp	a,6
	jr	z,.unitattention
	ld	hl,scsi.readcapacity
	lea	de,ymsdDevice.lba
	call	util_scsi_request	; store the logical block address / size
	jr	nz,.error
	ld	hl,scsi.testunitready
	call	util_scsi_request_default
	jr	nz,.error
	or	a,a
	sbc	hl,hl
	ret
.error:
	ld	hl,MSD_ERROR_USB_FAILED
	ret

; input:
;  hl : ptr to scsi command
;  de : ptr to storage (non-default)
;  iy : ptr to msd structure
; output;
;   z : success
;  nz : failure
util_scsi_request_default:
	ld	de,(ymsdDevice.buffer)
util_scsi_request:
	push	ix
	ld	(.msdstruct),iy
	xor	a,a
	ld	(tmp.sensecount),a
	ld	(util_msd_reset_recovery.errorsp),sp
	ld	(util_msd_xfer_cbw.cbw),hl
	ld	(util_msd_xfer_data.data),de
.resendcbw:
	call	util_msd_xfer_cbw
	call	util_msd_xfer_data
	call	util_msd_xfer_csw
	pop	ix
	ld	iy,0
.msdstruct = $-3
	ret

util_msd_xfer_cbw:
	ld	iy,(util_scsi_request.msdstruct)
	ld	a,hl,(ymsdDevice.tag)
	ld	ix,0
.cbw := $-3
	ld	(xpacketCBW.tag),a,hl
	ld	bc,1
	add	hl,bc
	adc	a,b
	ld	(ymsdDevice.tag),a,hl	; increment the tag
	ld	bc,sizeof packetCBW
	ld	a,(ymsdDevice.bulkoutaddr)
	call	util_msd_bulk_transfer
	ret	z			; check the command was accepted
.retry:
	call	util_msd_reset_recovery
	jq	util_msd_xfer_cbw

util_msd_xfer_data:
	ld	bc,(xpacketCBW.len)
	sbc	hl,hl
	adc	hl,bc
	ret	z			; no transfer if 0 len
	ld	a,(xpacketCBW.dir)	; check direction
	ld	iy,(util_scsi_request.msdstruct)
	ld	ix,0
.data := $ - 3
	or	a,a
	ld	a,(ymsdDevice.bulkinaddr)
	jr	nz,.xfer
	ld	a,(ymsdDevice.bulkoutaddr)
.xfer:
	call	util_msd_bulk_transfer
	ret	z
	call	util_msd_xfer_cbw.retry
	jq	util_msd_xfer_data

util_msd_xfer_csw:
	ld	iy,(util_scsi_request.msdstruct)
	call	util_msd_status_xfer
	jr	z,.checkcsw
	call	util_msd_status_xfer	; attempt to read csw again
	jr	z,.checkcsw
.retry:
	call	util_msd_xfer_cbw.retry
	call	util_msd_xfer_data
	jq	util_msd_xfer_csw
.checkcsw:
	ld	a,(tmp.csw.status)
	or	a,a			; check for good status of transfer
	jr	nz,.invalid
.valid:
	ld	a,hl,(tmp.csw.residue)
	add	hl,de
	or	a,a
	ld	a,16
	ret	nz
	sbc	hl,de
	ret	nz			; if residue != 0, retry transfer
	xor	a,a			; return success
	ret
.invalid:
	dec	a			; check for sense error (we can recover)
	jr	nz,.retry		; handle command fail (phase error)
.senseerror:
	ld	hl,tmp.sensecount
	or	a,(hl)
	ret	nz
	inc	(hl)
	ld	de,tmp.sensebuffer
	ld	hl,scsi.requestsense
	ld	(util_msd_xfer_cbw.cbw),hl
	ld	(util_msd_xfer_data.data),de
.senseresendcbw:
	call	util_msd_xfer_cbw
	call	util_msd_xfer_data
	call	util_msd_xfer_csw
	xor	a,a
	ld	(tmp.sensebuffer),a
	ld	a,(tmp.sensebuffer + 2)
	ret

util_msd_status_xfer:
	ld	a,(ymsdDevice.bulkinaddr)
	ld	ix,tmp.csw
	ld	bc,sizeof packetCSW
	jq	util_msd_bulk_transfer

;  hopefully recovers transfer state
util_msd_reset_recovery:
	ld	iy,(util_scsi_request.msdstruct)
	call	util_msd_reset
	compare_hl_zero
	jr	z,.resetsuccess
.fatalerror:
	ld	sp,0
.errorsp := $ - 3
	pop	ix
	xor	a,a
	inc	a
	ret
.resetsuccess:
	ld	iy,(util_scsi_request.msdstruct)
	ld	a,(ymsdDevice.bulkinaddr)
	call	util_ep_stall
	ld	a,(ymsdDevice.bulkoutaddr)
util_ep_stall:
	push	iy
	or	a,a
	sbc	hl,hl
	ld	l,a
	push	hl
	ld	bc,(ymsdDevice.dev)
	push	bc
	call	usb_GetDeviceEndpoint
	compare_hl_zero
	jq	z,util_msd_reset_recovery.fatalerror
	pop	bc
	pop	bc
	push	hl
	call	usb_ClearEndpointHalt
	pop	bc
	pop	iy
	ret

; inputs:
;   a : bulk endpoint address
;  bc : packet len
;  ix : data buffer
util_msd_bulk_transfer:
	push	iy
	or	a,a
	sbc	hl,hl
	push	hl
	push	hl			; zero retries (handled by states)
	push	bc
	push	ix			; packet to send
	ld	l,a
	push	hl
	ld	bc,(ymsdDevice.dev)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc,bc
	push	hl
	call	usb_Transfer
	pop	bc,bc,bc,bc,bc
	pop	iy
	compare_hl_zero
	ret

; iy -> msd structure
util_msd_reset:
	xor	a,a
	sbc	hl,hl
	ld	(ymsdDevice.tag + 0),hl
	ld	(ymsdDevice.tag + 3),a	; reset tag
	ld	a,(ymsdDevice.interface)
	ld	(setup.msdreset + 4),a
	ld	hl,setup.msdreset
	jq	util_msd_ctl_packet

; inputs:
;  iy : msd structure
util_msd_get_max_lun:
	ld	a,(ymsdDevice.interface)
	ld	(setup.msdmaxlun + 4),a
	ld	hl,setup.msdmaxlun
	lea	de,ymsdDevice.maxlun
	jq	util_msd_ctl_packet

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
	ld	bc,0
	push	bc
	ld	bc,(ymsdDevice.dev)
	push	bc
	call	usb_GetDeviceEndpoint
	pop	bc
	pop	bc
	push	hl
	call	usb_ControlTransfer
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	iy
	ret

include 'fat.asm'

;-------------------------------------------------------------------------------
; library data
;-------------------------------------------------------------------------------

setup.msdreset          setuppkt        $21,$ff,0,0,0
setup.msdmaxlun         setuppkt        $a1,$fe,0,0,1

scsi.inquiry            scsipkt         1,$0005,  $12, $00,$00,$00,$05,$00
scsi.testunitready      scsipkt         0,$0000,  $00, $00,$00,$00,$00,$00
scsi.modesense6         scsipkt         1,$00fc,  $1a, $00,$3f,$00,$fc,$00
scsi.requestsense       scsipkt         1,$0012,  $03, $00,$00,$00,$12,$00
scsi.readcapacity       scsipkt         1,$0008,  $25, $00,$00,$00,$00,$00,$00,$00,$00,$00
scsi.read10             scsipktrw       1,$28
scsi.write10            scsipktrw       0,$2a

tmp tmp_data

fatFile0 fatFile
fatFile1 fatFile
fatFile2 fatFile
fatFile3 fatFile
fatFile4 fatFile
