;--------------------------------
; Incldudes

  !include "MUI2.nsh"
  !include "EnvVarUpdate.nsh"
  !include "winmessages.nsh"
  
;--------------------------------
;Names

  Name "CE C SDK"
  BrandingText "CE C Software Development Kit"
  
;--------------------------------
;Input and output

  OutFile "CEdev.exe"
  InstallDir "$INSTDIR"
  RequestExecutionLevel admin

;--------------------------------
;Interface and defines

  !define env_hklm 'HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"'
  !define env_hkcu 'HKCU "Environment"'
  !define MUI_ABORTWARNING
  !define MUI_ICON "icon.ico"
  
;--------------------------------
;Pages

  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  
;--------------------------------
;Installer Section

Section ""

  SetOutPath "$INSTDIR"

  GetFullPathName /SHORT $0 $INSTDIR
  StrCpy $INSTDIR $0

  File /r ${DIST_PATH}\*.*

  DeleteRegValue ${env_hkcu} "CEDEV"
  ReadRegStr $R1 ${env_hklm} "CEDEV"

  ${EnvVarUpdate} $0 "PATH" "R" "HKLM" "$R1\bin"
  ${EnvVarUpdate} $0 "PATH" "P" "HKLM" "$INSTDIR\bin"

  WriteRegExpandStr ${env_hklm} "CEDEV" "$INSTDIR"

  SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000

SectionEnd

;--------------------------------
; Find system drive

Function .onInit

  ReadEnvStr $R0 SYSTEMDRIVE
  StrCpy $INSTDIR "$R0\CEdev"
  
FunctionEnd

;--------------------------------