# Copyright (C) 2015-2026 CE Programming
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

include $(CURDIR)/../common.mk


OBJECTS =
OBJECTS += $(patsubst %.c,build/%.c.o,$(wildcard *.c))
OBJECTS += $(patsubst %.cpp,build/%.cpp.o,$(wildcard *.cpp))
OBJECTS += $(patsubst %.src,build/%.o,$(wildcard *.src))

WILDCARD_SRC = $(wildcard *.src)
WILDCARD_H = $(wildcard include/*.h)
WILDCARD_HW_H = $(wildcard include/sys/*.h)
WILDCARD_TI_H = $(wildcard include/ti/*.h)

WILDCARD_CXX_H = $(wildcard include/c++/*)
WILDCARD_CXX_TI_H = $(wildcard include/ti/c++/*)

LIB_CE = build/libce.a

# independent object symbols to allow garbage collection
BOOT_SYMBOLS := \
    _boot_GetBootMajorVer@0x000080 \
    _boot_GetHardwareVer@0x000084 \
    _boot_GetBootMinorVer@0x00008C \
    _boot_DebugPrintf@0x0000B4 \
    _boot_ClearVRAM@0x000374 \
    _boot_TurnOn@0x000384 \
    _boot_TurnOff@0x000388 \
    _boot_NewLine@0x000390 \
    _boot_Set6MHzMode@0x00039C \
    _boot_Set48MHzMode@0x0003A0 \
    _boot_Set6MHzModeI@0x0003A4 \
    _boot_Set48MHzModeI@0x0003A8 \
    _boot_GetBatteryStatus@0x0003B0 \
    _boot_WaitShort@0x0003B4 \
    _boot_BatteryCharging@0x0003CC \
    _boot_USBBusPowered@0x0003E4 \
    _boot_USBSelfPowered@0x0003E8 \
    _boot_USBResetChip@0x0003F4 \
    _boot_USBResetTimers@0x0004F0 \
    _boot_USBDisableTimers@0x0004F4 \
    _boot_USBEnableTimers@0x0004F8 \
    _boot_CheckOnPressed@0x00057C \
    _boot_SetDate@0x000598 \
    _boot_GetDate@0x0005A8 \
    _boot_GetTime@0x0005B0 \
    _boot_SetTime@0x0005B4 \
    _boot_IsAfterNoon@0x0005C8 \
    _boot_sprintf@0x0000BC \
    _os_NewLine@0x0207F0 \
    _os_MoveDown@0x0207F4 \
    _os_MoveUp@0x020800 \
    _os_ClrLCDFull@0x020808 \
    _os_ClrLCD@0x02080C \
    _os_ClrTxtShd@0x020818 \
    _os_HomeUp@0x020828 \
    _os_RunIndicOn@0x020844 \
    _os_RunIndicOff@0x020848 \
    _os_DelRes@0x020E5C \
    _os_DisableAPD@0x021134 \
    _os_EnableAPD@0x021138 \
    _os_DrawStatusBar@0x021A3C \
    _os_PushErrorHandler@0x021C78 \
    _os_PopErrorHandler@0x021C7C \
    _os_ThrowError@0x021C80 \
    _os_RealCopy@0x021C84 \
    _os_RealAcosRad@0x021C88 \
    _os_RealAsinRad@0x021C8C \
    _os_RealAtanRad@0x021C90 \
    _os_RealAdd@0x021C94 \
    _os_CplxSquare@0x021C98 \
    _os_RealCompare@0x021C9C \
    _os_RealCosRad@0x021CA0 \
    _os_RealRadToDeg@0x021CA4 \
    _os_RealDiv@0x021CA8 \
    _os_RealExp@0x021CAC \
    _os_RealFloor@0x021CB0 \
    _os_RealToStr@0x021CB4 \
    _os_RealFrac@0x021CB8 \
    _os_RealGcd@0x021CBC \
    _os_RealRoundInt@0x021CC0 \
    _os_RealLcm@0x021CC4 \
    _os_RealLog@0x021CC8 \
    _os_RealMax@0x021CCC \
    _os_RealMin@0x021CD0 \
    _os_RealMul@0x021CD4 \
    _os_RealNcr@0x021CD8 \
    _os_RealNeg@0x021CDC \
    _os_RealNpr@0x021CE0 \
    _os_RealPow@0x021CE4 \
    _os_RealDegToRad@0x021CE8 \
    _os_RealRandInt@0x021CEC \
    _os_RealInv@0x021CF0 \
    _os_RealMod@0x021CF4 \
    _os_RealRound@0x021CF8 \
    _os_RealSinRad@0x021CFC \
    _os_RealSqrt@0x021D00 \
    _os_RealSub@0x021D04 \
    _os_RealTanRad@0x021D08 \
    _os_StrToReal@0x021D0C \
    _os_RealInt@0x021D10 \
    _os_SetFlagBits@0x021D14 \
    _os_ResetFlagBits@0x021D18 \
    _os_TestFlagBits@0x021D1C \
    _os_SetFlagByte@0x021D20 \
    _os_GetFlagByte@0x021D24 \
    _os_GetCursorPos@0x021D28 \
    _os_PutStrFull@0x021D2C \
    _os_PutStrLine@0x021D30 \
    _os_SetCursorPos@0x021D34 \
    _os_GetKey@0x021D38 \
    _os_GetCSC@0x021D3C \
    _os_AppInit@0x021D40 \
    _os_DisableCursor@0x021DE4 \
    _os_EnableCursor@0x021DE8 \
    _os_FontDrawText@0x021E00 \
    _os_FontGetHeight@0x021E14 \
    _os_FontGetWidth@0x021E18 \
    _os_InitDrawing@0x021E1C \
    _os_SetDrawBGColor@0x021E20 \
    _os_SetDrawFGColor@0x021E24 \
    _os_FontSelect@0x021E28 \
    _os_GetAnsData@0x021E70 \
    _os_SetTimer1@0x021EC8 \
    _os_DisableTimer1@0x021ECC \
    _os_GetSystemInfo@0x021ED4 \
    _os_GetDrawBGColor@0x021EE4 \
    _os_GetDrawFGColor@0x021EE8 \
    _os_FontGetID@0x021EEC \
    _os_RealToInt24@0x021EF4 \
    _os_Int24ToReal@0x021EF8 \
    _os_ForceCmdNoChar@0x021FA8 \
    _os_DelSymEntry@0x021FAC \
    _os_GetSymTablePtr@0x021FB0 \
    _os_NextSymEntry@0x021FB4 \
    _os_ChkFindSym@0x021FB8 \
    _os_GetVarSize@0x021FBC \
    _os_GetMatrixDims@0x021FC0 \
    _os_GetRealListElement@0x021FC4 \
    _os_GetMatrixElement@0x021FC8 \
    _os_GetRealVar@0x021FCC \
    _os_SetListDim@0x021FD0 \
    _os_SetMatrixDims@0x021FD4 \
    _os_SetRealListElement@0x021FD8 \
    _os_SetMatrixElement@0x021FDC \
    _os_SetRealVar@0x021FE0 \
    _os_MemChk@0x021FF0 \
    _os_ArcChk@0x022040 \
    _os_SetTimer2@0x022080 \
    _os_DisableTimer2@0x022084 \
    _os_FloatToReal@0x022170 \
    _os_RealToFloat@0x022174 \
    _os_FontDrawTransText@0x022178 \
    _os_DelAppVar@0x02217C \
    _os_GetAppVarData@0x022180 \
    _os_CreateAppVar@0x022184 \
    _os_CreateString@0x022198 \
    _os_GetStringData@0x02219C \
    _os_CreateEquation@0x022240 \
    _os_GetEquationData@0x022244 \
    _os_MSDGetMaxLUN@0x022280 \
    _os_MSDReset@0x022284 \
    _os_MSDInquiry@0x022288 \
    _os_MSDTestUnitReady@0x02228C \
    _os_MSDReadCapacity@0x022290 \
    _os_MSDRead@0x022294 \
    _os_MSDWrite@0x022298 \
    _os_USBGetRequestStatus@0x0222D0 \
    _os_TestFlagBitsFast@0x0222FC

define MAKE_BOOT_SYMBOL
build/$(word 1,$(subst @, ,$(1))).s:
	$(Q)$$(call MKDIR,build)
	$(Q)echo .assume adl=1 > $$@
	$(Q)echo .section .text >> $$@
	$(Q)echo .global $(word 1,$(subst @, ,$(1))) >> $$@
	$(Q)echo .type $(word 1,$(subst @, ,$(1))), @function >> $$@
	$(Q)echo .set $(word 1,$(subst @, ,$(1))), $(word 2,$(subst @, ,$(1))) >> $$@

build/$(word 1,$(subst @, ,$(1))).o: build/$(word 1,$(subst @, ,$(1))).s
	$(Q)$(EZAS) $(EZASFLAGS) -o $$@ $$<
endef

BOOT_OBJS := $(addprefix build/,$(addsuffix .o,$(foreach sym,$(BOOT_SYMBOLS),$(word 1,$(subst @, ,$(sym))))))

.SECONDARY:

all: $(LIB_CE)

$(LIB_CE): $(OBJECTS) $(BOOT_OBJS)
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAR) rcs $@ $^

$(foreach sym,$(BOOT_SYMBOLS),\
    $(eval $(call MAKE_BOOT_SYMBOL,$(sym))))

build/%.c.src: %.c
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCFLAGS) $< -o $@

build/%.cpp.src: %.cpp
	$(Q)$(call MKDIR,build)
	$(Q)$(EZCC) $(EZCXXFLAGS) $< -o $@

build/%.c.o: build/%.c.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

build/%.cpp.o: build/%.cpp.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

build/%.o: %.src
	$(Q)$(call MKDIR,build)
	$(Q)$(EZAS) $(EZASFLAGS) $< -o $@

install: $(addprefix install-,$(TARGETS))
	$(Q)$(call MKDIR,$(INSTALL_H))
	$(Q)$(call MKDIR,$(INSTALL_TI_H))
	$(Q)$(call MKDIR,$(INSTALL_HW_H))
	$(Q)$(call MKDIR,$(INSTALL_CE))
	$(Q)$(call MKDIR,$(INSTALL_CXX_H))
	$(Q)$(call MKDIR,$(INSTALL_CXX_TI_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_HW_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_HW_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_TI_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_TI_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_CXX_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_CXX_H))
	$(Q)$(call COPY,$(foreach file,$(call NATIVEPATH,$(WILDCARD_CXX_TI_H)),$(call QUOTE_ARG,$(file))),$(INSTALL_CXX_TI_H))
	$(Q)$(call COPY,$(call NATIVEPATH,$(LIB_CE)),$(INSTALL_CE))

clean:
	$(Q)$(call RMDIR,build)

.PHONY: all install clean
