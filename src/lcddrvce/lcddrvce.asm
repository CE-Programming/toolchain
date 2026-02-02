;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library LCDDRVCE, 0

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v1 functions
;-------------------------------------------------------------------------------
	export lcd_Init
	export lcd_Cleanup
	export lcd_Wait
	export lcd_SendSizedCommandRaw
	export lcd_SendParamsRaw
	export lcd_SendCommand
	export lcd_SendCommand1
	export lcd_SendCommand2
	export lcd_SendSizedCommandBytes
	export lcd_SendSizedCommandWords
	export lcd_SetUniformGamma
	export lcd_SetDefaultGamma

macro checked_param param, limit
	assert (param) >= 0 & (param) <= (limit)
	db param
end macro

macro checked_param2 param1, limit1, param2, limit2
	assert (param1) >= 0 & (param1) <= (limit1)
	assert (param2) >= 0 & (param2) <= (limit2)
	db ((param2) shl 4) or (param1)
end macro

; Gamma voltage levels are specified here.
; V0-V2, V20, V43, V61-V63 are the main points, ranging from 129 to 0.
; V4, V6, V13 are interpolated between V2 and V20, ranging from 60 to 0.
; V27, V36 are interpolated between V20 and V43, ranging from 25 to 0.
; V50, V57, V59 are interpolated between V43 and V61, ranging from 60 to 0.
; J0 and J1 are values between 0 and 3 affecting interpolations for remaining voltages.
macro gamma_params V0, V1, V2, V20, V43, V61, V62, V63, V4, V6, V13, V27, V36, V50, V57, V59, J0, J1
	checked_param2 129-(V0),  $0F, 23-(V63), $0F
	checked_param  128-(V1),  $3F
	checked_param  128-(V2),  $3F
	checked_param   57-(V4),  $1F
	checked_param   47-(V6),  $1F
	checked_param2  21-(V13), $0F, J0, $03
	checked_param  128-(V20), $7F
	checked_param2  20-(V27), $07, 11-(V36), $07
	checked_param  128-(V43), $7F
	checked_param2  54-(V50), $0F, J1, $03
	checked_param   44-(V57), $1F
	checked_param   34-(V59), $1F
	checked_param   64-(V61), $3F
	checked_param   64-(V62), $3F
end macro

lcd_Init:
	; Increase the refcount
	scf
	sbc hl,hl
	ld de, 0
.refcount := $-3
	add hl, de
	ld (.refcount), hl
	ret c
	; Initialize if the old refcount was 0
	; Always fully initialize on the first call per program invocation
	ld hl, .fullinit
	srl (hl)
	jr c, .checkPython
	; Additionally, fully initialize if an APD reset the SPI state to something other than LCD
	ld a, (ti.mpSpiCtrl0)
	cp a, ti.bmSpiMasterMono or ti.bmSpiClkPhase or ti.bmSpiClkPolarity
	jr z, .fastinit
.checkPython:
	; Check certificate for Python model
	ld de, $0330
	call ti.FindFirstCertField
	jr nz, .notPython
	call ti.GetFieldSizeFromType
	ld de, $0430
	call ti.FindField
	jr nz, .notPython
	; Reinitializes Python hardware, probably (routine available on rev M+ boot code)
	; Without this, LCD SPI transfers start failing a short time after init
	call $000654
	; Magic SPI initialization sequence to work on Python models
	ld de, ti.spiSpiFrFmt or ti.bmSpiFlash or ti.bmSpiFsPolarity or ti.bmSpiMasterMono
.loop:
	ld (ti.mpSpiCtrl0), de
	ld hl, ti.bmSpiTxClr or ti.bmSpiRxClr
	ld (ti.mpSpiCtrl2), hl
.fullinit:
	; Becomes a nop after being shifted
	db 1
	ld hl, ti.bmSpiChipReset
	ld (ti.mpSpiCtrl2), hl
	call ti.Delay10ms
	bit ti.bSpiClkPolarity, e
	ld e, ti.bmSpiFsPolarity or ti.bmSpiMasterMono or ti.bmSpiClkPhase or ti.bmSpiClkPolarity
	jr z, .loop
	ld hl, $21
	ld (ti.mpSpiIntCtrl), hl
.notPython:
	ld a, ti.bmSpiMasterMono or ti.bmSpiClkPhase or ti.bmSpiClkPolarity
	ld (ti.mpSpiCtrl0), a
.fastinit:
	ld hl, ((9-1) shl 16) or (2-1)
	ld (ti.mpSpiCtrl1), hl
	ld hl, ti.bmSpiTxEn or ti.bmSpiTxClr or ti.bmSpiRxClr or ti.bmSpiChipEn
	ld (ti.mpSpiCtrl2), hl
	ret

lcd_Cleanup:
	; Decrease the refcount
	ld hl, (lcd_Init.refcount)
	ld de, 1
	add hl, de
	ld (lcd_Init.refcount), hl
	ret nc
	; Deinitialize if the new refcount is 0
	call lcd_Wait
	ld hl, ((3-1) shl 16) or (12-1)
	ld (ti.mpSpiCtrl1), hl
	ld hl, ti.bmSpiTxEn or ti.bmSpiTxClr or ti.bmSpiRxClr
	ld (ti.mpSpiCtrl2), hl
	ret

lcd_Wait:
	ld hl, ti.mpSpiStatus + 1
	ld a, (1 shl (ti.bSpiTxFifoBytes - 8)) - 1
.waitEmpty:
	cp a, (hl)
	jr c, .waitEmpty
	dec hl
.waitBusy:
	bit ti.bSpiChipBusy, (hl)
	jr nz, .waitBusy
	ret

lcd_SetUniformGamma:
	ld de, uniformGammaParams
	jr _Gamma
lcd_SetDefaultGamma:
	ld de, defaultGammaParams
_Gamma:
	; Set positive gamma
	ld bc, (14 shl 8) or $E0
	push bc
	call lcd_SendSizedCommandRaw.entry
	; Set negative gamma
	ex de, hl
	pop bc
	inc c
	jr lcd_SendSizedCommandRaw.entry

lcd_SendSizedCommandRaw:
	pop hl
	pop bc
	pop de
	push de
	push bc
	push hl

.entry:
	ld hl, ti.mpSpiStatus + 1
	ld a, ((ti.bmSpiTxFifoBytes shr 8) and $FF) - 1
.waitNotFull:
	cp a, (hl)
	jr c, .waitNotFull
	ld l, ti.spiData + 1
	ld (hl), h
	dec hl
	ld (hl), c
	ld c, 1
	mlt bc
	ex de, hl
	xor a, a
	sub a, c
	jr nz, lcd_SendParamsRaw.entry
	ret

lcd_SendParamsRaw:
	pop hl
	pop bc
	pop de
	push de
	push bc
	push hl
	scf
	sbc hl, hl
	add hl, bc
	ex de, hl
	ret nc

	ld de, ti.mpSpiRange
	xor a, a
	sub a, c
.entry:
	and a, 7
	add a, a
	add a, a
	ld (.sendParamsOffsetSMC), a
.sendParamsLoop:
	ld e, ti.spiStatus + 1
	scf
.waitForEight:
	ld a, (de)
	rla
	jr c, .waitForEight
	ld e, ti.spiData + 1
	jr nz, $
.sendParamsOffsetSMC = $-1
	repeat 8
	ld (de), a
	dec de
	ldi
	end repeat
	ret po
	cp a, a
	jr .sendParamsLoop

_sendSingleByte:
	ld l, ti.spiStatus + 1
	ld a, ((ti.bmSpiTxFifoBytes shr 8) and $FF) - 1
.waitNotFull:
	cp a, (hl)
	jr c, .waitNotFull
	ld l, ti.spiData
	ld a, (de)
	ld (hl), a
	inc hl
	ld (hl), l
	ret

lcd_SendCommand:
	ld b, 0+1
	jr lcd_SendSizedCommandBytes.entry

lcd_SendCommand1:
	ld b, 1+1
	jr lcd_SendSizedCommandBytes.entry

lcd_SendCommand2:
	ld b, 2+1
	jr lcd_SendSizedCommandBytes.entry

lcd_SendSizedCommandBytes:
	pop hl
	pop bc
	push bc
	push hl
	inc b
.entry:
	ld hl, 3
	add hl, sp
	ex de, hl
	ld hl, ti.mpSpiData + 1
	ld (hl), h
.loop:
	call _sendSingleByte
	inc de
	inc de
	inc de
	djnz .loop
	ret

lcd_SendSizedCommandWords:
	ld hl, 4
	add hl, sp
	ld b, (hl)
	inc b
	ex de, hl
	ld hl, ti.mpSpiData + 1
	ld (hl), h
.loop:
	dec de
	call _sendSingleByte
	dec b
	ret z
	inc de
	inc de
	inc de
	inc de
	call _sendSingleByte
	jr .loop

defaultGammaParams:
	; Positive gamma
	gamma_params 129, 128, 128, 83, 65, 45, 41, 10,  41, 32, 11,  16, 6,  43, 20, 11,  1, 3
	; Negative gamma
	gamma_params 129, 128, 128, 85, 64, 45, 41, 10,  41, 32, 12,  17, 7,  43, 20, 11,  0, 3

uniformGammaParams:
	; Positive gamma
	gamma_params 129, 125, 121, 83, 65, 45, 41, 10,  49, 38, 13,  16, 6,  43, 20, 11,  1, 3
	; Negative gamma
	gamma_params 129, 125, 121, 85, 64, 45, 41, 10,  49, 38, 14,  17, 7,  43, 20, 11,  0, 3
