;-------------------------------------------------------------------------------
include '../include/library.inc'
include '../include/include_library.inc'
;-------------------------------------------------------------------------------

library 'USBDRVCE', 0

;-------------------------------------------------------------------------------
; dependencies
;-------------------------------------------------------------------------------
include_library '../usbdrvce/usbdrvce.asm'

;-------------------------------------------------------------------------------
; v0 functions (not final, subject to change!)
;-------------------------------------------------------------------------------
	export	srl_Open
	export	srl_Close
	export	srl_Available
	export	srl_Read
	export	srl_Write
	export	srl_GetCDCStandardDescriptors

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
	buf_size			rl 1
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


;srl_error_t srl_Open(srl_device_t *srl,
;                     usb_device_t dev,
;                     void *buffer,
;                     size_t size,
;                     uint8_t interface,
;                     uint24_t rate);
srl_Open:
	ret

;void srl_Close(srl_device_t *srl);
srl_Close:
	ret

;size_t srl_Available(srl_device_t *srl);
srl_Available:
	ret

;size_t srl_Read(srl_device_t *srl,
;                void *data,
;                size_t length);
srl_Read:
	ret

;size_t srl_Write(srl_device_t *srl,
;                 const void *data,
;                 size_t length);
srl_Write:
	ret

;usb_standard_descriptors_t *srl_GetCDCStandardDescriptors(void);
srl_GetCDCStandardDescriptors:
	ret

; Gets the device type and subtype based on the descriptors
; Inputs:
;  ix: Serial device struct
;  xsrl_device.buffer: Device descriptor, followed by config descriptor
; Returns:
;  xsrl_device.type: Device type
;  xsrl_device.subtype: Device subtype
get_device_type:
	ret

; Gets the endpoint addresses based on the descriptors and device type
; Inputs:
;  ix: Serial device struct
;  a: Interface number
;  xsrl_device.buffer: Device descriptor, followed by config descriptor
;  xsrl_device.type: Device type
;  xsrl_device.subtype: Device subtype
; Returns:
;  xsrl_device.rx_addr: Receive endpoint address
;  xsrl_device.tx_addr: Transmit endpoint address
;  hl: Error or SRL_SUCCESS
get_endpoint_addresses:
	ret

; Initializes a serial device whose type has been determined
; Inputs:
;  ix: Serial device struct
; Returns:
;  hl: Error or SRL_SUCCESS
init_device:
	ret

; Sets the baud rate of a serial device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
;  c: Interface number
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate:
	ret

; Sets the baud rate of a USB CDC device
; Inputs:
;  ix: Serial device struct
;  hl: Baud rate
;  c: Interface number
; Returns:
;  hl: Error or SRL_SUCCESS
set_rate_cdc:
	ret

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

; Checks how many bytes are available in a ring buffer
; Inputs:
;  ix: ring_buf_ctrl struct
; Returns:
;  hl: Number of available bytes
ring_buf_avail:
	ret

; Checks if there is a consecutive region of the given size
; following the last available byte
; Inputs:
;  ix: ring_buf_ctrl struct
;  a: Size
; Returns:
;  nc if the region does not exist
ring_buf_has_consecutive_region:
	ret

; Pushes bytes to a ring buffer
; Assumes that this buffer does not have any consecutive byte requirements
; Inputs:
;  ix: ring_buf_ctrl struct
;  hl: Data to push
;  bc: Number of bytes to push
; Returns:
;  hl: Number of bytes pushed
ring_buf_push:
	ret

; Takes bytes from a ring buffer
; Inputs:
;  ix: ring_buf_ctrl struct
;  hl: Location to copy data to
;  bc: Number of bytes to take
; Returns:
;  hl: Number of bytes taken
ring_buf_pop:
	ret

; Update a ring buffer after it's been DMA'd to
; Inputs:
;  ix: ring_buf_ctrl struct
;  bc: Number of bytes written
;  a: Size of minimum consecutive region
ring_buf_update:
	ret

;usb_error_t (usb_endpoint_t endpoint, usb_transfer_status_t status, size_t transferred, srl_device_t *data);
read_callback:
	ret

;usb_error_t (usb_endpoint_t endpoint, usb_transfer_status_t status, size_t transferred, srl_device_t *data);
write_callback:
	ret

; Starts the receive transfer
; Inputs:
;  ix: Serial device struct
start_read:
	ret

; Starts the transmit transfer
; Inputs:
;  ix: Serial device struct
start_write:
	ret
