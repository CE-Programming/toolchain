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
;  sp + 6  : usb device to initialize as msd
; return:
;  hl = error status
msd_Open:
	ret

;-------------------------------------------------------------------------------
msd_Close:
; Closes and deinitializes a Mass Storage Device.
; args:
;  sp + 3  : msd device structure
; return:
;  hl = error status
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
