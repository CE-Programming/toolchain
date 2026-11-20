.equ USBDRVCE_VERSION, 0

; Export order defines the LibLoad ABI. Append new entries at the end.
.macro usbdrvce_exports emit

; v0 functions (not final, subject to change!)
	\emit usb_Init
	\emit usb_Cleanup
	\emit usb_PollTransfers
	\emit usb_HandleEvents
	\emit usb_WaitForEvents
	\emit usb_WaitForInterrupt
	\emit usb_RefDevice
	\emit usb_UnrefDevice
	\emit usb_GetDeviceHub
	\emit usb_SetDeviceData
	\emit usb_GetDeviceData
	\emit usb_GetDeviceFlags
	\emit usb_FindDevice
	\emit usb_ResetDevice
	\emit usb_DisableDevice
	\emit usb_GetDeviceAddress
	\emit usb_GetDeviceSpeed
	\emit usb_GetConfigurationDescriptorTotalLength
	\emit usb_GetDescriptor
	\emit usb_SetDescriptor
	\emit usb_GetStringDescriptor
	\emit usb_SetStringDescriptor
	\emit usb_GetConfiguration
	\emit usb_SetConfiguration
	\emit usb_GetInterface
	\emit usb_SetInterface
	\emit usb_SetEndpointHalt
	\emit usb_ClearEndpointHalt
	\emit usb_GetDeviceEndpoint
	\emit usb_GetEndpointDevice
	\emit usb_SetEndpointData
	\emit usb_GetEndpointData
	\emit usb_GetEndpointAddress
	\emit usb_GetEndpointTransferType
	\emit usb_GetEndpointMaxPacketSize
	\emit usb_GetEndpointInterval
	\emit usb_SetEndpointFlags
	\emit usb_GetEndpointFlags
	\emit usb_GetRole
	\emit usb_GetFrameNumber
	\emit usb_ControlTransfer
	\emit usb_Transfer
	\emit usb_ScheduleControlTransfer
	\emit usb_ScheduleTransfer
	\emit usb_MsToCycles
	\emit usb_GetCycleCounter
	\emit usb_GetCounter
	\emit usb_StopTimer
	\emit usb_StartTimerCycles
	\emit usb_RepeatTimerCycles
.endm
