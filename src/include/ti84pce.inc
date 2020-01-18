;TI-84 Plus CE Include File

;Various Parts Contributed by
;- BrandonW
;- calc84
;- MateoConLechuga
;- Runer112
;- tr1p1ea
;- Kerm Martian
;- Texas Instruments (ti83plus.inc)
.nolist

#ifndef TI84PCE
#define TI84PCE

; Included for Assembler Compatibility
;------------------------------------
#define equ .equ
#define EQU .equ
#define end .end
#define END .end

; Hardware Defines
;------------------------------
lcdWidth		equ 320
lcdHeight		equ 240

; System Calls
; Jump Table located at 020104h
;--------------------------------
_OSSize                    equ 0020104h ; not a routine; jump location is end of OS
_BootOS	                   equ 0020108h
_InterruptHandler          equ 002010Ch
_Rst10Handler              equ 0020110h
_Rst18Handler              equ 0020114h
_Rst20Handler              equ 0020118h
_Rst28Handler              equ 002011Ch
_Rst30Handler              equ 0020120h
;                          equ 0020124h
;                          equ 0020128h
_JErrorNo                  equ 002012Ch
_CallFontHook              equ 0020130h
_CallLocalizeHook          equ 0020134h
_LoadHLInd_s               equ 0020138h
_CpHLDE                    equ 002013Ch
_DivHLBy10_s               equ 0020140h
_DivHLByA_s                equ 0020144h
_KbdScan                   equ 0020148h
_GetCSC                    equ 002014Ch
_CoorMon                   equ 0020150h
_Mon                       equ 0020154h
_MonForceKey               equ 0020158h
_SendKPress                equ 002015Ch
_JForceCmdNoChar           equ 0020160h
_JForceCmd                 equ 0020164h
_SysErrHandler             equ 0020168h
_NewContext                equ 002016Ch
_NewContext0               equ 0020170h
_PPutawayPrompt            equ 0020174h
_PPutAway                  equ 0020178h
_PutAway                   equ 002017Ch
_SizeWind                  equ 0020180h
_ErrorEP                   equ 0020184h
_CallMain                  equ 0020188h
_MonErrHand                equ 002018Ch
_AppInit                   equ 0020190h
_Initialize                equ 0020194h
_Min                       equ 0020198h
_Max                       equ 002019Ch
_AbsO1PAbsO2               equ 00201A0h
_Intgr                     equ 00201A4h
_TRunc                     equ 00201A8h
_InvSub                    equ 00201ACh
_Times2                    equ 00201B0h
_Plus1                     equ 00201B4h
_Minus1                    equ 00201B8h
_FPSub                     equ 00201BCh
_FPAdd                     equ 00201C0h
_DToR                      equ 00201C4h
_RToD                      equ 00201C8h
_Cube                      equ 00201CCh
_TimesPT5                  equ 00201D0h
_FPSquare                  equ 00201D4h
_FPMult                    equ 00201D8h
_LJRnd                     equ 00201DCh
_InvOP1Sc                  equ 00201E0h
_InvOP1S                   equ 00201E4h
_InvOP2S                   equ 00201E8h
_Frac                      equ 00201ECh
_FPRecip                   equ 00201F0h
_FPDiv                     equ 00201F4h
_SqRoot                    equ 00201F8h
_RndGuard                  equ 00201FCh
_Rnfx                      equ 0020200h
_Int                       equ 0020204h
_Round                     equ 0020208h
_LnX                       equ 002020Ch
_LogX                      equ 0020210h
_LJNoRnd                   equ 0020214h
_EToX                      equ 0020218h
_TenX                      equ 002021Ch
_SinCosRad                 equ 0020220h
_Sin                       equ 0020224h
_Cos                       equ 0020228h
_Tan                       equ 002022Ch
_SinhCosh                  equ 0020230h
_Tanh                      equ 0020234h
_Cosh                      equ 0020238h
_Sinh                      equ 002023Ch
_ACosRad                   equ 0020240h
_ATanRad                   equ 0020244h
_ATan2Rad                  equ 0020248h
_ASinRad                   equ 002024Ch
_ACos                      equ 0020250h
_ATan                      equ 0020254h
_ASin                      equ 0020258h
_ATan2                     equ 002025Ch
_ATanh                     equ 0020260h
_ASinh                     equ 0020264h
_ACosh                     equ 0020268h
_PToR                      equ 002026Ch
_RToP                      equ 0020270h
_HLTimes9                  equ 0020274h
_CkOP1Cplx                 equ 0020278h
_CkOP1Real                 equ 002027Ch
_Angle                     equ 0020280h
_COP1Set0                  equ 0020284h
_Cpop4OP3                  equ 0020288h
_Mov9OP2Cp                 equ 002028Ch
_AbsO1O2Cp                 equ 0020290h
_CpOP1OP2                  equ 0020294h
_OP3ToOP4                  equ 0020298h
_OP1ToOP4                  equ 002029Ch
_OP2ToOP4                  equ 00202A0h
_OP4ToOP2                  equ 00202A4h
_OP3ToOP2                  equ 00202A8h
_OP1ToOP3                  equ 00202ACh
_OP5ToOP2                  equ 00202B0h
_OP5ToOP6                  equ 00202B4h
_OP5ToOP4                  equ 00202B8h
_OP1ToOP2                  equ 00202BCh
_OP6ToOP2                  equ 00202C0h
_OP6ToOP1                  equ 00202C4h
_OP4ToOP1                  equ 00202C8h
_OP5ToOP1                  equ 00202CCh
_OP3ToOP1                  equ 00202D0h
_OP6ToOP5                  equ 00202D4h
_OP4ToOP5                  equ 00202D8h
_OP3ToOP5                  equ 00202DCh
_OP2ToOP5                  equ 00202E0h
_OP2ToOP6                  equ 00202E4h
_OP1ToOP6                  equ 00202E8h
_OP1ToOP5                  equ 00202ECh
_OP2ToOP1                  equ 00202F0h
_Mov11b                    equ 00202F4h
_Mov10b                    equ 00202F8h
_Mov9b                     equ 00202FCh
_Mov9b_                    equ 0020300h
_Mov8b                     equ 0020304h
_Mov7b                     equ 0020308h
_Mov7b_                    equ 002030Ch
_OP2ToOP3                  equ 0020310h
_OP4ToOP3                  equ 0020314h
_OP5ToOP3                  equ 0020318h
_OP4ToOP6                  equ 002031Ch
_Mov9ToOP1                 equ 0020320h
_Mov9OP1OP2                equ 0020324h
_Mov9ToOP2                 equ 0020328h
_MovFROP1                  equ 002032Ch
_OP4Set1                   equ 0020330h
_OP3Set1                   equ 0020334h
_OP2Set8                   equ 0020338h
_OP2Set5                   equ 002033Ch
_OP2SetA                   equ 0020340h
_OP2Set4                   equ 0020344h
_OP2Set3                   equ 0020348h
_OP1Set1                   equ 002034Ch
_OP1Set4                   equ 0020350h
_OP1Set3                   equ 0020354h
_OP3Set2                   equ 0020358h
_OP1Set2                   equ 002035Ch
_OP2Set2                   equ 0020360h
_OP2Set1                   equ 0020364h
_Zero16D                   equ 0020368h
_OP5Set0                   equ 002036Ch
_OP4Set0                   equ 0020370h
_OP3Set0                   equ 0020374h
_OP2Set0                   equ 0020378h
_OP1Set0                   equ 002037Ch
_SetNum0                   equ 0020380h
_ZeroOP1                   equ 0020384h
_ZeroOP2                   equ 0020388h
_ZeroOP3                   equ 002038Ch
_ZeroOP                    equ 0020390h
_ClrLP                     equ 0020394h
_ShrACC                    equ 0020398h
_ShlACC                    equ 002039Ch
_Shr18                     equ 00203A0h
_Shr18a                    equ 00203A4h
_Shr16                     equ 00203A8h
_Shr14                     equ 00203ACh
_Shl16                     equ 00203B0h
_Shl14                     equ 00203B4h
_Srdo1                     equ 00203B8h
_ShrdRnd                   equ 00203BCh
_MantPa                    equ 00203C0h
_AddPrOP                   equ 00203C4h
_AddPrOPlP                 equ 00203C8h
;                          equ 00203CCh
;                          equ 00203D0h
_Sub16d                    equ 00203D4h
_Sub14d                    equ 00203D8h
_OP2ExOP6                  equ 00203DCh
_OP5ExOP6                  equ 00203E0h
_OP1ExOP5                  equ 00203E4h
_OP1ExOP6                  equ 00203E8h
_OP2ExOP4                  equ 00203ECh
_OP2ExOP5                  equ 00203F0h
_OP1ExOP3                  equ 00203F4h
_OP1ExOP4                  equ 00203F8h
_OP1ExOP2                  equ 00203FCh
_ExLP                      equ 0020400h
_CkOP10                    equ 0020404h
_CkOP1FP0                  equ 0020408h
_CkOP2FP0                  equ 002040Ch
_PosNo0Int                 equ 0020410h
_CkPosInt                  equ 0020414h
_CkInt                     equ 0020418h
_CkOdd                     equ 002041Ch
_CkOP1EX                   equ 0020420h
_GetCon1                   equ 0020424h
_GetCon                    equ 0020428h
_PiDiv2                    equ 002042Ch
_PiDiv4                    equ 0020430h
_TwoPi                     equ 0020434h
_PiCon                     equ 0020438h
_ExpToHex                  equ 002043Ch
_OP1ExpToDec               equ 0020440h
_CkOP2Pos                  equ 0020444h
_CkOP1Pos                  equ 0020448h
_ClrOP2S                   equ 002044Ch
_ClrOP1S                   equ 0020450h
_FDiv100                   equ 0020454h
_FDiv10                    equ 0020458h
_DecO1Exp                  equ 002045Ch
_IncO1exp                  equ 0020460h
_IncExp                    equ 0020464h
_CkValidNum                equ 0020468h
_GetExp                    equ 002046Ch
_HtimesL                   equ 0020470h
_EOP1NotReal               equ 0020474h
_ThetaName                 equ 0020478h
_RName                     equ 002047Ch
_RegEqName                 equ 0020480h
_RecurNName                equ 0020484h
_XName                     equ 0020488h
_YName                     equ 002048Ch
_TName                     equ 0020490h
_RealName                  equ 0020494h
_SetEStoFPS                equ 0020498h
_ChkTempDirt               equ 002049Ch
_OP1ExOP2Exp               equ 00204A0h
_OP1ExpMinusE              equ 00204A4h
_ChkErrBreak               equ 00204A8h
_Isa2ByteTok               equ 00204ACh
_GetLastEntry              equ 00204B0h
_GetLastEntryPtr           equ 00204B4h
_RegRclrChng               equ 00204B8h
_ResetWinTop               equ 00204BCh
_IsO1NonTLstOrProg         equ 00204C0h
_IsO1NonTempLst            equ 00204C4h
_Is_A_LstOrCLst            equ 00204C8h
_Chk_HL_999                equ 00204CCh
_Equ_Or_NewEqu             equ 00204D0h
_Errd_OP1NotPos            equ 00204D4h
_Errd_OP1Not_R             equ 00204D8h
_Errd_OP1NotPosInt         equ 00204DCh
_Errd_OP1_le_0             equ 00204E0h
_Errd_OP1_0                equ 00204E4h
_ChkFindSym_Get_Size       equ 00204E8h
_Sto_StatVar               equ 00204ECh
_Rcl_StatVar               equ 00204F0h
_CkOP2Real                 equ 00204F4h
_Get_X_Indirect            equ 00204F8h
_MemChk                    equ 00204FCh
_CmpPrgNamLen1             equ 0020500h
_CmpPrgNamLen              equ 0020504h
_FindProgSym               equ 0020508h
_ChkFindSym                equ 002050Ch
_FindSym                   equ 0020510h
_InsertMem                 equ 0020514h
_InsertMemA                equ 0020518h
_EnoughMem                 equ 002051Ch
_CmpMemNeed                equ 0020520h
_CreatePVar4               equ 0020524h
_CreatePVar3               equ 0020528h
_CreateVar3                equ 002052Ch
_CreateCplx                equ 0020530h
_CreateReal                equ 0020534h
_CreateTRList              equ 0020538h
_CreateRList               equ 002053Ch
_CreateTCList              equ 0020540h
_CreateCList               equ 0020544h
_CreateTRMat               equ 0020548h
_CreateRMat                equ 002054Ch
_CreateTStrng              equ 0020550h
_CreateStrng               equ 0020554h
_Create0Equ                equ 0020558h
_CreatetEqu                equ 002055Ch
_CreateEqu                 equ 0020560h
_CreateGDB                 equ 0020564h
_CreateProg                equ 0020568h
_ChkDel                    equ 002056Ch
_ChkDelA                   equ 0020570h
_AdjParser                 equ 0020574h
_AdjMath                   equ 0020578h
_AdjM7                     equ 002057Ch
_DelMemA                   equ 0020580h
_Get_Form_Num              equ 0020584h
_DelVar                    equ 0020588h
_DelVarIO                  equ 002058Ch
_DelMem                    equ 0020590h
_DelVar3D                  equ 0020594h
_DelVar3C                  equ 0020598h
_DelVar3DC                 equ 002059Ch
_Sym_Prog_non_t_Lst        equ 00205A0h
_AdjSymPtrs                equ 00205A4h
_DataSizeA                 equ 00205A8h
_DataSize                  equ 00205ACh
_PopMCplxO1                equ 00205B0h
_PopMCplx                  equ 00205B4h
_MovCplx                   equ 00205B8h
_PopOP5                    equ 00205BCh
_PopOP3                    equ 00205C0h
_PopOP1                    equ 00205C4h
_PopRealO6                 equ 00205C8h
_PopRealO5                 equ 00205CCh
_PopRealO4                 equ 00205D0h
_PopRealO3                 equ 00205D4h
_PopRealO2                 equ 00205D8h
_PopRealO1                 equ 00205DCh
_PopReal                   equ 00205E0h
_FPopCplx                  equ 00205E4h
_FPopReal                  equ 00205E8h
_FPopFPS                   equ 00205ECh
_DeallocFPS                equ 00205F0h
_DeallocFPS1               equ 00205F4h
_AllocFPS                  equ 00205F8h
_AllocFPS1                 equ 00205FCh
_PushRealO6                equ 0020600h
_PushRealO5                equ 0020604h
_PushRealO4                equ 0020608h
_PushRealO3                equ 002060Ch
_PushRealO2                equ 0020610h
_PushRealO1                equ 0020614h
_PushReal                  equ 0020618h
_PushOP5                   equ 002061Ch
_PushOP3                   equ 0020620h
_PushMCplxO3               equ 0020624h
_PushOP1                   equ 0020628h
_PushMCplxO1               equ 002062Ch
_PushMCplx                 equ 0020630h
_ExMCplxO1                 equ 0020634h
_Exch9                     equ 0020638h
_CpyTo1FPS11               equ 002063Ch
_CpyTo2FPS5                equ 0020640h
_CpyTo1FPS5                equ 0020644h
_CpyTo2FPS6                equ 0020648h
_CpyTo1FPS6                equ 002064Ch
_CpyTo2FPS7                equ 0020650h
_CpyTo1FPS7                equ 0020654h
_CpyTo1FPS8                equ 0020658h
_CpyTo2FPS8                equ 002065Ch
_CpyTo1FPS10               equ 0020660h
_CpyTo1FPS9                equ 0020664h
_CpyTo2FPS4                equ 0020668h
_CpyTo6FPS3                equ 002066Ch
_CpyTo6FPS2                equ 0020670h
_CpyTo2FPS3                equ 0020674h
_Cpycto1FPS3               equ 0020678h
_CpyTo1FPS3                equ 002067Ch
_CpyFPS3                   equ 0020680h
_CpyTo1FPS4                equ 0020684h
_CpyTo3FPS2                equ 0020688h
_CpyTo5FPST                equ 002068Ch
_CpyTo6FPST                equ 0020690h
_CpyTo4FPST                equ 0020694h
_CpyTo3FPST                equ 0020698h
_CpyTo2FPST                equ 002069Ch
_CpyTo1FPST                equ 00206A0h
_CpyFPST                   equ 00206A4h
_CpyStack                  equ 00206A8h
_CpyTo3FPS1                equ 00206ACh
_CpyTo2FPS1                equ 00206B0h
_CpyTo1FPS1                equ 00206B4h
_CpyFPS1                   equ 00206B8h
_CpyTo2FPS2                equ 00206BCh
_CpyTo1FPS2                equ 00206C0h
_CpyFPS2                   equ 00206C4h
_CpyO3ToFPST               equ 00206C8h
_CpyO2ToFPST               equ 00206CCh
_CpyO6ToFPST               equ 00206D0h
_CpyO1ToFPST               equ 00206D4h
_CpyToFPST                 equ 00206D8h
_CpyToStack                equ 00206DCh
_CpyO3ToFPS1               equ 00206E0h
_CpyO5ToFPS1               equ 00206E4h
_CpyO2ToFPS1               equ 00206E8h
_CpyO1ToFPS1               equ 00206ECh
_CpyToFPS1                 equ 00206F0h
_CpyO2ToFPS2               equ 00206F4h
_CpyO3ToFPS2               equ 00206F8h
_CpyO6ToFPS2               equ 00206FCh
_CpyO1ToFPS2               equ 0020700h
_CpyToFPS2                 equ 0020704h
_CpyO5ToFPS3               equ 0020708h
_CpyO2ToFPS3               equ 002070Ch
_CpyO1ToFPS3               equ 0020710h
_CpyToFPS3                 equ 0020714h
_CpyO1ToFPS6               equ 0020718h
_CpyO1ToFPS7               equ 002071Ch
_CpyO1ToFPS5               equ 0020720h
_CpyO2ToFPS4               equ 0020724h
_CpyO1ToFPS4               equ 0020728h
_ErrNotEnoughMem           equ 002072Ch
_FPSMinus9                 equ 0020730h
_HLMinus9                  equ 0020734h
_ErrOverflow               equ 0020738h
_ErrDivBy0                 equ 002073Ch
_ErrSingularMat            equ 0020740h
_ErrDomain                 equ 0020744h
_ErrIncrement              equ 0020748h
_ErrNon_Real               equ 002074Ch
_ErrSyntax                 equ 0020750h
_ErrDataType               equ 0020754h
_ErrArgument               equ 0020758h
_ErrDimMismatch            equ 002075Ch
_ErrDimension              equ 0020760h
_ErrUndefined              equ 0020764h
_ErrMemory                 equ 0020768h
_ErrInvalid                equ 002076Ch
_ErrBreak                  equ 0020770h
_ErrStat                   equ 0020774h
_ErrSignChange             equ 0020778h
_ErrIterations             equ 002077Ch
_ErrBadGuess               equ 0020780h
_ErrTolTooSmall            equ 0020784h
_ErrStatPlot               equ 0020788h
_ErrLinkXmit               equ 002078Ch
_JError                    equ 0020790h
_NoErrorEntry              equ 0020794h
_PushErrorHandler          equ 0020798h
_PopErrorHandler           equ 002079Ch
_StrCopy                   equ 00207A0h
_StrngCat                  equ 00207A4h
_IsInSet                   equ 00207A8h
_GEQNameA                  equ 00207ACh
_RecName                   equ 00207B0h
_PutMap                    equ 00207B4h
_PutC                      equ 00207B8h
_DispHL_s                  equ 00207BCh
_PutS                      equ 00207C0h
_PutPSB                    equ 00207C4h
_PutPS                     equ 00207C8h
_WPutPS                    equ 00207CCh
_PutBuf                    equ 00207D0h
_PutBuf1                   equ 00207D4h
_WPutC                     equ 00207D8h
_WPutS                     equ 00207DCh
_WPutSEOL                  equ 00207E0h
_WDispEOL                  equ 00207E4h
_WHomeUp                   equ 00207E8h
_SetNumWindow              equ 00207ECh
_NewLine                   equ 00207F0h
_MoveDown                  equ 00207F4h
_ScrollUp                  equ 00207F8h
_ShrinkWindow              equ 00207FCh
_MoveUp                    equ 0020800h
_ScrollDown                equ 0020804h
_ClrLCDFull                equ 0020808h
_ClrLCD                    equ 002080Ch
_ClrScrnFull               equ 0020810h
_ClrScrn                   equ 0020814h
_ClrTxtShd                 equ 0020818h
_ClrWindow                 equ 002081Ch
_EraseEOL                  equ 0020820h
_EraseEOW                  equ 0020824h
_HomeUp                    equ 0020828h
_GetCurloc                 equ 002082Ch
_VPutMap                   equ 0020830h
_VPutS                     equ 0020834h
_VPutSN                    equ 0020838h
_VPutSNG                   equ 002083Ch
_VPutSNT                   equ 0020840h
_RunIndicOn                equ 0020844h
_RunIndicOff               equ 0020848h
_SaveCmdShadow             equ 002084Ch
_SaveShadow                equ 0020850h
_RStrShadow                equ 0020854h
_RStrPartial               equ 0020858h
_RStrCurRow                equ 002085Ch
_RStrUnderMenu             equ 0020860h
_RStrbotRow                equ 0020864h
_GetKeypress               equ 0020868h
_GetTokLen                 equ 002086Ch
_Get_Tok_Strng             equ 0020870h
_GetTokString              equ 0020874h
_PutBPatBuf2               equ 0020878h
_PutBPatBuf                equ 002087Ch
_PutBPat                   equ 0020880h
_PutcChkScroll             equ 0020884h
_DispEOL                   equ 0020888h
_FDispEOL                  equ 002088Ch
_MakeRowCmd                equ 0020890h
_ToToStrp                  equ 0020894h
_SetVarName                equ 0020898h
_DispDone                  equ 002089Ch
_FinishOutput              equ 00208A0h
_CurBlink                  equ 00208A4h
_CursorOff                 equ 00208A8h
_HideCursor                equ 00208ACh
_CursorOn                  equ 00208B0h
_ShowCursor                equ 00208B4h
_KeyToString               equ 00208B8h
_PullDownChk               equ 00208BCh
_MenuCatCommon             equ 00208C0h
_LoadCurCat                equ 00208C4h
_NCIFPrgmedMode            equ 00208C8h
_LoadMenuNum               equ 00208CCh
_LoadMenuNuml              equ 00208D0h
_MenuEdKey                 equ 00208D4h
_MenCatRet                 equ 00208D8h
_NotAlphNum                equ 00208DCh
_SetMenuFlags              equ 00208E0h
_ResetSomeFlags            equ 00208E4h
;                          equ 00208E8h
;                          equ 00208ECh
_DispListName              equ 00208F0h
_DispLAlphaName            equ 00208F4h
_AbortPrgmode              equ 00208F8h
_IsFullCntx                equ 00208FCh
_AdrMRow                   equ 0020900h
_AdrmeLE                   equ 0020904h
_GetmatOP1A                equ 0020908h
_Getm1toOP1                equ 002090Ch
_Getm1tOP1A                equ 0020910h
_GetMToOP1                 equ 0020914h
_PutToM1A                  equ 0020918h
_PutToMA1                  equ 002091Ch
_PutToMat                  equ 0020920h
_MatELDiv                  equ 0020924h
_CMatFun                   equ 0020928h
_RowEchPoly                equ 002092Ch
_RowEchelon                equ 0020930h
_AdrLELE                   equ 0020934h
_Getl1ToOP1                equ 0020938h
_Getl1TOP1A                equ 002093Ch
_GetlToOP1                 equ 0020940h
_Getl1ToOP2                equ 0020944h
_Getl1TOP2A                equ 0020948h
_Getl2TOP1A                equ 002094Ch
_PutTola1                  equ 0020950h
_PutToL                    equ 0020954h
_MaxMinLst                 equ 0020958h
_LLow                      equ 002095Ch
_LHigh                     equ 0020960h
_LSum                      equ 0020964h
_CumSum                    equ 0020968h
_ToFrac                    equ 002096Ch
_SeqSet                    equ 0020970h
_SeqSolve                  equ 0020974h
_CmpNumInit                equ 0020978h
_BinopExec                 equ 002097Ch
_ExMeanL                   equ 0020980h
_Set2MVLPtrs               equ 0020984h
_SetMat1                   equ 0020988h
_CreateTLIst               equ 002098Ch
_UnopExec                  equ 0020990h
_ThreeExec                 equ 0020994h
_RestoreErrNo              equ 0020998h
_FourExec                  equ 002099Ch
_FiveExec                  equ 00209A0h
_CpyTo2ES1                 equ 00209A4h
_CpyTo6ES1                 equ 00209A8h
_CpyTo1ES1                 equ 00209ACh
_CpyTo3ES1                 equ 00209B0h
_CpyTo3ES2                 equ 00209B4h
_CpyTo2ES2                 equ 00209B8h
_CpyTo1ES2                 equ 00209BCh
_CpyTo2ES3                 equ 00209C0h
_CpyTo1ES3                 equ 00209C4h
_CpyTo3ES4                 equ 00209C8h
_CpyTo6ES3                 equ 00209CCh
_CpyTo2ES4                 equ 00209D0h
_CpyTo1ES4                 equ 00209D4h
_CpyTo2ES5                 equ 00209D8h
_CpyTo1ES5                 equ 00209DCh
_CpyTo4ESt                 equ 00209E0h
_CpyTo2ESt                 equ 00209E4h
_CpyTo1ESt                 equ 00209E8h
_CpyTo2ES6                 equ 00209ECh
_CpyTo1ES6                 equ 00209F0h
_CpyTo2ES7                 equ 00209F4h
_CpyTo1ES7                 equ 00209F8h
_CpyTo2ES8                 equ 00209FCh
_CpyTo1ES8                 equ 0020A00h
_CpyTo1ES9                 equ 0020A04h
_CpyTo2ES9                 equ 0020A08h
_CpyTo2ES10                equ 0020A0Ch
_CpyTo1ES10                equ 0020A10h
_CpyTo2ES11                equ 0020A14h
_CpyTo1ES11                equ 0020A18h
_CpyTo2ES12                equ 0020A1Ch
_CpyTo1ES12                equ 0020A20h
_CpyTo2ES13                equ 0020A24h
_CpyTo1ES13                equ 0020A28h
_CpyTo1ES14                equ 0020A2Ch
_CpyTo1ES16                equ 0020A30h
_CpyTo1ES17                equ 0020A34h
_CpyTo1ES18                equ 0020A38h
_CpyTo1ES15                equ 0020A3Ch
_CpyTo2ES15                equ 0020A40h
_CpyO1ToESt                equ 0020A44h
_CpyO1ToES1                equ 0020A48h
_CpyO6ToES1                equ 0020A4Ch
_CpyO6ToES3                equ 0020A50h
_CpyO1ToES2                equ 0020A54h
_CpyO2ToES2                equ 0020A58h
_CpyO1ToES3                equ 0020A5Ch
_CpyO1ToES4                equ 0020A60h
_CpyO1ToES5                equ 0020A64h
_CpyO1ToES6                equ 0020A68h
_CpyO1ToES7                equ 0020A6Ch
_CpyO2ToES4                equ 0020A70h
_CpyO2ToES5                equ 0020A74h
_CpyO2ToES6                equ 0020A78h
_CpyO2ToES7                equ 0020A7Ch
_CpyO2ToES8                equ 0020A80h
_CpyO2ToES9                equ 0020A84h
_CpyO1ToES8                equ 0020A88h
_CpyO1ToES9                equ 0020A8Ch
_CpyO1ToES10               equ 0020A90h
_CpyO1ToES11               equ 0020A94h
_CpyO1ToES12               equ 0020A98h
_CpyO1ToES13               equ 0020A9Ch
_CpyO1ToES14               equ 0020AA0h
_EvalF3A                   equ 0020AA4h
_GetK                      equ 0020AA8h
_SetTitle                  equ 0020AACh
_DispVarVal                equ 0020AB0h
_RecallEd                  equ 0020AB4h
_SetUpBuffer               equ 0020AB8h
_CreateNumEditBuf          equ 0020ABCh
_CallCommon                equ 0020AC0h
_CommonKeys                equ 0020AC4h
_LeftMore                  equ 0020AC8h
_FDel                      equ 0020ACCh
_FClear                    equ 0020AD0h
_FInsDisp                  equ 0020AD4h
_FInsDispNoConv            equ 0020AD8h
_SetIndicator              equ 0020ADCh
_CloseEditBufNoR           equ 0020AE0h
_ReleaseBuffer             equ 0020AE4h
_VarNameToOP1HL            equ 0020AE8h
_NameToOP1                 equ 0020AECh
_NumpPutAway               equ 0020AF0h
_NumReDisp                 equ 0020AF4h
_NumError02                equ 0020AF8h
_Load_Sfont                equ 0020AFCh
_Sfont_Len                 equ 0020B00h
_InitNumVec                equ 0020B04h
_SetxxOP1                  equ 0020B08h
_SetxxOP2                  equ 0020B0Ch
_SetxxxxOP2                equ 0020B10h
_UCLines                   equ 0020B14h
_CLine                     equ 0020B18h
_CLines                    equ 0020B1Ch
_XrootY                    equ 0020B20h
_YtoX                      equ 0020B24h
_ZmStats                   equ 0020B28h
_PointStatHelp             equ 0020B2Ch
_DrawSPlot                 equ 0020B30h
_InitNewTraceP             equ 0020B34h
_SPlotCoord                equ 0020B38h
_SPlotRight                equ 0020B3Ch
_SPlotLeft                 equ 0020B40h
_CmpBoxInfo                equ 0020B44h
_NextPlot                  equ 0020B48h
_PrevPlot                  equ 0020B4Ch
_ClrPrevPlot               equ 0020B50h
_PutIndexList              equ 0020B54h
_GetIndexList              equ 0020B58h
_HeapSort                  equ 0020B5Ch
_StoGDB2                   equ 0020B60h
_RclGDB2                   equ 0020B64h
_CircCmd                   equ 0020B68h
_GrphCirc                  equ 0020B6Ch
_Mov18b                    equ 0020B70h
_DarkLine                  equ 0020B74h
_ILine                     equ 0020B78h
_IPoint                    equ 0020B7Ch
_XYRndBoth                 equ 0020B80h
_XYRnd                     equ 0020B84h
_CheckTOP                  equ 0020B88h
_CheckXY                   equ 0020B8Ch
_DarkPnt                   equ 0020B90h
_CPointS                   equ 0020B94h
_WToV                      equ 0020B98h
_VtoWHLDE                  equ 0020B9Ch
_Xitof                     equ 0020BA0h
_YftoI                     equ 0020BA4h
_XftoI                     equ 0020BA8h
_TraceOff                  equ 0020BACh
_GrRedisp                  equ 0020BB0h
_GDispToken                equ 0020BB4h
_GrdeCoda                  equ 0020BB8h
_LabCoor                   equ 0020BBCh
_CoorDisp                  equ 0020BC0h
_TmpEquNoSrc               equ 0020BC4h
_GrLabels                  equ 0020BC8h
_YPixSet                   equ 0020BCCh
_XPixSet                   equ 0020BD0h
_CopyRng                   equ 0020BD4h
_ValCur                    equ 0020BD8h
_GrPutAway                 equ 0020BDCh
_RstGFlags                 equ 0020BE0h
_GrReset                   equ 0020BE4h
_XYCent                    equ 0020BE8h
_ZoomXYCmd                 equ 0020BECh
_CptDelY                   equ 0020BF0h
_CptDelX                   equ 0020BF4h
_SetFuncM                  equ 0020BF8h
_SetSeqM                   equ 0020BFCh
_SetPolM                   equ 0020C00h
_SetParM                   equ 0020C04h
_ZmInt                     equ 0020C08h
_ZmDecml                   equ 0020C0Ch
_ZmPrev                    equ 0020C10h
_ZmUsr                     equ 0020C14h
_SetUZM                    equ 0020C18h
_ZmFit                     equ 0020C1Ch
_ZmSquare                  equ 0020C20h
_ZmTrig                    equ 0020C24h
_SetXMinMax                equ 0020C28h
_ZooDefault                equ 0020C2Ch
_GrBufCpy                  equ 0020C30h
_DrawSplitLine             equ 0020C34h
;                          equ 0020C38h
;                          equ 0020C3Ch
;                          equ 0020C40h
;                          equ 0020C44h
;                          equ 0020C48h
;                          equ 0020C4Ch
;                          equ 0020C50h
;                          equ 0020C54h
_ChkTextCurs               equ 0020C58h
_Regraph                   equ 0020C5Ch
_DoRefFlags02              equ 0020C60h
_InitNSeq                  equ 0020C64h
_YRes                      equ 0020C68h
_Ceiling                   equ 0020C6Ch
_PutXY                     equ 0020C70h
_PutEquNo                  equ 0020C74h
_PDspGrph                  equ 0020C78h
_HorizCmd                  equ 0020C7Ch
_VertCmd                   equ 0020C80h
_LineCmd                   equ 0020C84h
_UnLineCmd                 equ 0020C88h
_PointCmd                  equ 0020C8Ch
_PixelTest                 equ 0020C90h
_PixelCmd                  equ 0020C94h
_TanLnF                    equ 0020C98h
_DrawCmdInit               equ 0020C9Ch
_DrawCmd                   equ 0020CA0h
_ShadeCmd                  equ 0020CA4h
_InvCmd                    equ 0020CA8h
_StatShade                 equ 0020CACh
_DspMatTable               equ 0020CB0h
_DspLsts                   equ 0020CB4h
_CloseEditBuf              equ 0020CB8h
_ParseEditBuf              equ 0020CBCh
_PutSM                     equ 0020CC0h
_DspCurTbl                 equ 0020CC4h
_DspGrTbl                  equ 0020CC8h
_ZeroTemplate              equ 0020CCCh
_SetTblRefs                equ 0020CD0h
_DispTblBot                equ 0020CD4h
_DispTblTop                equ 0020CD8h
_DispTblBody               equ 0020CDCh
_VPutBlank                 equ 0020CE0h
_TblTrace                  equ 0020CE4h
_DispListNameY             equ 0020CE8h
_CurNameLength             equ 0020CECh
_NameToBuf                 equ 0020CF0h
_JPromptCursor             equ 0020CF4h
_BufLeft                   equ 0020CF8h
_BufRight                  equ 0020CFCh
_BufInsert                 equ 0020D00h
_BufQueueChar              equ 0020D04h
_BufReplace                equ 0020D08h
_BufDelete                 equ 0020D0Ch
_BufPeek                   equ 0020D10h
_BufPeek1                  equ 0020D14h
_BufPeek2                  equ 0020D18h
_BufPeek3                  equ 0020D1Ch
_BufToBtm                  equ 0020D20h
_SetupEditEqu              equ 0020D24h
_BufToTop                  equ 0020D28h
_IsEditFull                equ 0020D2Ch
_IsEditEmpty               equ 0020D30h
_IsAtTop                   equ 0020D34h
_IsAtBtm                   equ 0020D38h
_BufClear                  equ 0020D3Ch
_JCursorFirst              equ 0020D40h
_JCursorLast               equ 0020D44h
_CursorLeft                equ 0020D48h
_CursorRight               equ 0020D4Ch
_CursorUp                  equ 0020D50h
_CursorDown                equ 0020D54h
_CursorToOffset            equ 0020D58h
_InsDisp                   equ 0020D5Ch
_FDispBOL1                 equ 0020D60h
_FDispBOL                  equ 0020D64h
_DispEOW                   equ 0020D68h
_DispHead                  equ 0020D6Ch
_DispTail                  equ 0020D70h
_PutTokString              equ 0020D74h
_SetUpEditCmd              equ 0020D78h
_SetEmptyeditEqu           equ 0020D7Ch
_SetEmptyEditPtr           equ 0020D80h
_CloseEditEqu              equ 0020D84h
_GetPrevTok                equ 0020D88h
_GetKey                    equ 0020D8Ch
_CanIndic                  equ 0020D90h
_DFMin                     equ 0020D94h
_FormDisp                  equ 0020D98h
_FormMatrix                equ 0020D9Ch
_WScrollLeft               equ 0020DA0h
_WScrollUp                 equ 0020DA4h
_WScrollDown               equ 0020DA8h
_WScrollRight              equ 0020DACh
_FormEReal                 equ 0020DB0h
_FormERealTok              equ 0020DB4h
_FormDCplx                 equ 0020DB8h
_FormReal                  equ 0020DBCh
_SetWinAbove               equ 0020DC0h
_DisarmScroll              equ 0020DC4h
_MinToEdit                 equ 0020DC8h
_RclVarToEdit              equ 0020DCCh
_RclVarToEditPtr           equ 0020DD0h
_RclEntryToEdit            equ 0020DD4h
_RclToQueue                equ 0020DD8h
_FormToTok                 equ 0020DDCh
_DispInterval              equ 0020DE0h
_DispLstName               equ 0020DE4h
_DispSLstNameHL            equ 0020DE8h
_EditEqu                   equ 0020DECh
_CloseEquField             equ 0020DF0h
_AutoSelect                equ 0020DF4h
_DispYEOS                  equ 0020DF8h
_DispNumEOS                equ 0020DFCh
_SetupDispEq               equ 0020E00h
_DispForward               equ 0020E04h
_DispYPrompt2              equ 0020E08h
_StringWidth               equ 0020E0Ch
_DispErrorScreen           equ 0020E10h
_PopCX                     equ 0020E14h
_LoadNoEEntry              equ 0020E18h
_SaveScreen                equ 0020E1Ch
_RetScreen                 equ 0020E20h
_RetScreenErr              equ 0020E24h
_CheckSplitFlag            equ 0020E28h
_SolveRedisp               equ 0020E2Ch
_SolveDisp                 equ 0020E30h
_ItemName                  equ 0020E34h
_SetNorm_Vals              equ 0020E38h
_SetYOffset                equ 0020E3Ch
_ConvKeyToTok              equ 0020E40h
_ConvFCKeyToTok            equ 0020E44h
_ConvFEKeyToTok            equ 0020E48h
_TokToKey                  equ 0020E4Ch
_GetVarCmdUSB              equ 0020E50h
;                          equ 0020E54h
_DeselectAllVars           equ 0020E58h
_DelRes                    equ 0020E5Ch
_ConvLcToLr                equ 0020E60h
_RedimMat                  equ 0020E64h
_IncLstSize                equ 0020E68h
_InsertList                equ 0020E6Ch
_DelListEl                 equ 0020E70h
_EditProg                  equ 0020E74h
_CloseProg                 equ 0020E78h
_ClrGraphRef               equ 0020E7Ch
_FixTempCnt                equ 0020E80h
_SaveData                  equ 0020E84h
_RestoreData               equ 0020E88h
_FindAlphaUp               equ 0020E8Ch
_FindAlphaDn               equ 0020E90h
_CmpSyms                   equ 0020E94h
_CreateTemp                equ 0020E98h
_CleanAll                  equ 0020E9Ch
_MoveToNextSym             equ 0020EA0h
_ConvLrToLc                equ 0020EA4h
_TblScreenDown             equ 0020EA8h
_TblScreenUp               equ 0020EACh
_ScreenScrollPixelsUp      equ 0020EB0h
;;_ret                     equ 0020EB4h
_ZIfRclHandler             equ 0020EB8h
_ZIfRclKApp                equ 0020EBCh
;                          equ 0020EC0h
;                          equ 0020EC4h
_InitNamePrompt            equ 0020EC8h
_InitNamePrompt_           equ 0020ECCh
_CatalogChk                equ 0020ED0h
_ClrTR                     equ 0020ED4h
;                          equ 0020ED8h
;                          equ 0020EDCh
;                          equ 0020EE0h
;                          equ 0020EE4h
_ErrNonReal_FPST_FPS1      equ 0020EE8h
_ErrNonReal                equ 0020EECh
_WriteText                 equ 0020EF0h
;                          equ 0020EF4h
_GraphPars                 equ 0020EF8h
_PlotPars                  equ 0020EFCh
_ParseInp                  equ 0020F00h
_ParseOn                   equ 0020F04h
_ParseScan                 equ 0020F08h
_GetParse                  equ 0020F0Ch
_SaveParse                 equ 0020F10h
_InitPFlgs                 equ 0020F14h
_CkEndLineRR               equ 0020F18h
_OP2Set60                  equ 0020F1Ch
_GetStatPtr                equ 0020F20h
_CmpStatPtr                equ 0020F24h
_VarSysAdr                 equ 0020F28h
_StoSysTok                 equ 0020F2Ch
_StoAns                    equ 0020F30h
_StoTheta                  equ 0020F34h
_StoR                      equ 0020F38h
_StoY                      equ 0020F3Ch
_StoN                      equ 0020F40h
_StoT                      equ 0020F44h
_StoX                      equ 0020F48h
_StoOther                  equ 0020F4Ch
_RclAns                    equ 0020F50h
_RclY                      equ 0020F54h
_RclN                      equ 0020F58h
_RclX                      equ 0020F5Ch
_RclVarSym                 equ 0020F60h
_RclsyStok                 equ 0020F64h
_StMatel                   equ 0020F68h
_StLstvecel                equ 0020F6Ch
_ConvOP1                   equ 0020F70h
_FindParseFormula          equ 0020F74h
_ParseFormula              equ 0020F78h
_StrngEnt1                 equ 0020F7Ch
_Prgrdlp                   equ 0020F80h
_VarEnt                    equ 0020F84h
_ParseOnC                  equ 0020F88h
_ParseOn_                  equ 0020F8Ch
_ParseCmd                  equ 0020F90h
_StoType                   equ 0020F94h
_CreatePair                equ 0020F98h
_PushNum                   equ 0020F9Ch
_IncCurPCErrEnd            equ 0020FA0h
_ErrEnd                    equ 0020FA4h
_CommaErrF                 equ 0020FA8h
_CommaErr                  equ 0020FACh
_StEQArg2                  equ 0020FB0h
_StEQArg                   equ 0020FB4h
_InpArg                    equ 0020FB8h
_StEQArg3                  equ 0020FBCh
_NxtFetch                  equ 0020FC0h
_CkFetchVar                equ 0020FC4h
_FetchVarA                 equ 0020FC8h
_FetchVar                  equ 0020FCCh
_CkEndLin                  equ 0020FD0h
_CkEndExp                  equ 0020FD4h
_CkParsEnd                 equ 0020FD8h
_StoTypeArg                equ 0020FDCh
_ConvDim                   equ 0020FE0h
_ConvDim00                 equ 0020FE4h
_AheadEqual                equ 0020FE8h
_ParseHeads                equ 0020FECh
_ParseHead                 equ 0020FF0h
_AnsName                   equ 0020FF4h
_StoCmpReals               equ 0020FF8h
_GetDEPtr                  equ 0020FFCh
_Push2BOper                equ 0021000h
_Push3BOper                equ 0021004h
_Pop2BOper                 equ 0021008h
_Pop3BOper                 equ 002100Ch
_PushOper                  equ 0021010h
_PopOper                   equ 0021014h
_FindEUndef                equ 0021018h
_SttmpEQ                   equ 002101Ch
_FindEOL                   equ 0021020h
_BrkInc                    equ 0021024h
_IncFetch                  equ 0021028h
_CurFetch                  equ 002102Ch
_Random                    equ 0021030h
_StoRand                   equ 0021034h
_RandInit                  equ 0021038h
_ResetStacks               equ 002103Ch
_Factorial                 equ 0021040h
_YEquOnOff                 equ 0021044h
_EquSelUnsel               equ 0021048h
_ITSolver                  equ 002104Ch
_GRITSolver                equ 0021050h
_ITSolverB                 equ 0021054h
_ITSolverNB                equ 0021058h
_ExTestInt                 equ 002105Ch
_DistFun                   equ 0021060h
_LogGamma                  equ 0021064h
_OneVar                    equ 0021068h
_OneVars0                  equ 002106Ch
_OrdStat                   equ 0021070h
_InitStatAns               equ 0021074h
_AnovaSpec                 equ 0021078h
_OutputExpr                equ 002107Ch
_CentCursor                equ 0021080h
;                          equ 0021084h
;                          equ 0021088h
;                          equ 002108Ch
;                          equ 0021090h
_CkValDeltaX               equ 0021094h
_CkValDelta                equ 0021098h
_GrBufClr                  equ 002109Ch
_GrBufCpyV                 equ 00210A0h
_FndSelEQ                  equ 00210A4h
_ClrGraphXY                equ 00210A8h
_NEDXTYStyle               equ 00210ACh
_PlotPt                    equ 00210B0h
_NewWindEP                 equ 00210B4h
_DrawAxes                  equ 00210B8h
_SetPenX                   equ 00210BCh
_SetPenY                   equ 00210C0h
_SetPenT                   equ 00210C4h
_TanEquDisp                equ 00210C8h
_PutAns                    equ 00210CCh
_DispOP1A                  equ 00210D0h
;                          equ 00210D4h
_SetTblGraphDraw           equ 00210D8h
_MemClear                  equ 00210DCh
_MemSet                    equ 00210E0h
_PointOn                   equ 00210E4h
_ExecuteNewPrgm            equ 00210E8h
_StrLength                 equ 00210ECh
_VPutMapRec                equ 00210F0h
_FindAppUp                 equ 00210F4h
_FindAppDown               equ 00210F8h
_FindApp                   equ 00210FCh
_os_FindAppStart           equ 0021100h
_SkipAppHeader             equ 0021104h
_FindAppStart              equ 0021108h
_IBounds                   equ 002110Ch
_IOffset                   equ 0021110h
_DrawCirc                  equ 0021114h
_CanAlphIns                equ 0021118h
_CxReDisp                  equ 002111Ch
_GetBaseVer                equ 0021120h
_OPSet0                    equ 0021124h
_AppGetCBLUSB              equ 0021128h
_SetIgnoreKey              equ 002112Ch
_SetSendThisKeyBack        equ 0021130h
_DisableAPD                equ 0021134h
_EnableAPD                 equ 0021138h
_Set2IY34                  equ 002113Ch
_ForceCmd                  equ 0021140h
_ApdSetup                  equ 0021144h
_AppSetup                  equ 0021148h
;                          equ 002114Ch
_ReleaseSedit              equ 0021150h
_InitSmallEditLine         equ 0021154h
_StartSmallEdit            equ 0021158h
;                          equ 002115Ch
_SGetTokString             equ 0021160h
_LoadPattern               equ 0021164h
_SStringLength             equ 0021168h
_RestorePenCol             equ 002116Ch
;                          equ 0021170h
_EmptyHook                 equ 0021174h
_ForceSmallEditReturn      equ 0021178h
_SaveContext               equ 002117Ch
;                          equ 0021180h
_ClearRow                  equ 0021184h
;                          equ 0021188h
;                          equ 002118Ch
;                          equ 0021190h
;                          equ 0021194h
;                          equ 0021198h
;                          equ 002119Ch
;                          equ 00211A0h
;                          equ 00211A4h
;                          equ 00211A8h
;                          equ 00211ACh
;                          equ 00211B0h
;                          equ 00211B4h
;                          equ 00211B8h
;                          equ 00211BCh
;                          equ 00211C0h
;                          equ 00211C4h
;                          equ 00211C8h
;                          equ 00211CCh
;                          equ 00211D0h
;                          equ 00211D4h
;                          equ 00211D8h
;                          equ 00211DCh
;                          equ 00211E0h
;                          equ 00211E4h
;                          equ 00211E8h
;                          equ 00211ECh
;;_ret                     equ 00211F0h
;                          equ 00211F4h
_InitSmallEditLineVar      equ 00211F8h
_InitSmallEditLineOP1      equ 00211FCh
_InitSmallEditBoxVar       equ 0021200h
_InitSmallEditBoxOP1       equ 0021204h
_RclEntryToEditA           equ 0021208h
_ErrCustom1                equ 002120Ch
_ErrCustom2                equ 0021210h
;;_ret                     equ 0021214h
_ClearRect                 equ 0021218h
_InvertRect                equ 002121Ch
_FillRect                  equ 0021220h
_RestoreTextFlags          equ 0021224h
_InitCellBox               equ 0021228h
_DrawCell                  equ 002122Ch
;                          equ 0021230h
_InvertCell                equ 0021234h
_SetCellOverride           equ 0021238h
_DrawRectBorder            equ 002123Ch
_ClearCell                 equ 0021240h
_CoverCell                 equ 0021244h
_EraseRectBorder           equ 0021248h
_FillRectPattern           equ 002124Ch
_DrawRectBorderClear       equ 0021250h
;                          equ 0021254h
_VerticalLine              equ 0021258h
_IBoundsFull               equ 002125Ch
;                          equ 0021260h
;                          equ 0021264h
_CPoint                    equ 0021268h
_DeleteApp                 equ 002126Ch
_GetModeCellFlagOR         equ 0021270h
_ResetModeCellFlag         equ 0021274h
_IsModeCellSet             equ 0021278h
_GetModeCellFlag           equ 002127Ch
;                          equ 0021280h
_SetCurCellBoxManager      equ 0021284h
;                          equ 0021288h
_CellBoxManager            equ 002128Ch
_StartNewCell              equ 0021290h
_RunInCellOveride          equ 0021294h
_RunCellOveride            equ 0021298h
_ClearCurCell              equ 002129Ch
_DrawCurCell               equ 00212A0h
_InvertCurCell             equ 00212A4h
_CoverCurCell              equ 00212A8h
_BlinkCell                 equ 00212ACh
_BlinkCellNoLookUp         equ 00212B0h
_BlinkCurCell              equ 00212B4h
_BlinkCellToOn             equ 00212B8h
_BlinkCellToOnNoLookUp     equ 00212BCh
_BlinkCurCellToOn          equ 00212C0h
_BlinkCellToOff            equ 00212C4h
_BlinkCellToOffNoLookUp    equ 00212C8h
_BlinkCurCellToOff         equ 00212CCh
_GetCurModeCellFlag        equ 00212D0h
;                          equ 00212D4h
_StartSmallEditReturn      equ 00212D8h
;                          equ 00212DCh
;                          equ 00212E0h
_CellKeyHandle             equ 00212E4h
;                          equ 00212E8h
;                          equ 00212ECh
;                          equ 00212F0h
;                          equ 00212F4h
;                          equ 00212F8h
_EraseAllCells             equ 00212FCh
_IsCurModeCellSet          equ 0021300h
;                          equ 0021304h
;                          equ 0021308h
;                          equ 002130Ch
;                          equ 0021310h
_DrawBlnkCell              equ 0021314h
_ClearBlnkCell             equ 0021318h
_InvertBlnkCell            equ 002131Ch
_GetStringInput            equ 0021320h
_GetStringInput2           equ 0021324h
_WaitEnterKeyValue         equ 0021328h
_HorizontalLine            equ 002132Ch
_CreateAppVar              equ 0021330h
_CreateProtProg            equ 0021334h
_CreateVar                 equ 0021338h
_AsmComp                   equ 002133Ch
_GetAsmSize                equ 0021340h
_SquishPrgm                equ 0021344h
_ExecutePrgm               equ 0021348h
_ChkFindSymAsm             equ 002134Ch
_ParsePrgmName             equ 0021350h
_CSub                      equ 0021354h
_CAdd                      equ 0021358h
_CSquare                   equ 002135Ch
_CMult                     equ 0021360h
_CRecip                    equ 0021364h
_CDiv                      equ 0021368h
_CAbs                      equ 002136Ch
_AddSquares                equ 0021370h
_CSqRoot                   equ 0021374h
_CLN                       equ 0021378h
_CLog                      equ 002137Ch
_CTenX                     equ 0021380h
_CEtoX                     equ 0021384h
_CXrootY                   equ 0021388h
;                          equ 002138Ch
_CYtoX                     equ 0021390h
_InvertNonReal             equ 0021394h
_CTrunc                    equ 0021398h
_CFrac                     equ 002139Ch
_CFloor                    equ 00213A0h
_SrchVLstUp                equ 00213A4h
_SrchVLstDn                equ 00213A8h
_FlashWriteDisable         equ 00213ACh
_Disp                      equ 00213B0h
_GetBytePaged              equ 00213B4h
_RunCursorHook             equ 00213B8h
_RunLibraryHook            equ 00213BCh
_RunRawKeyHook             equ 00213C0h
_SetCursorHook             equ 00213C4h
_SetLibraryHook            equ 00213C8h
_SetGetKeyHook             equ 00213CCh
_ClrCursorHook             equ 00213D0h
_ClrLibraryHook            equ 00213D4h
_ClrRawKeyHook             equ 00213D8h
_GetKeyHook                equ 00213DCh
_SetGetCSCHook             equ 00213E0h
_ClrGetKeyHook             equ 00213E4h
_SetCatalog2Hook           equ 00213E8h
_ClrCatalog2Hook           equ 00213ECh
_SetLocalizeHook           equ 00213F0h
_ClrLocalizeHook           equ 00213F4h
_SetTokenHook              equ 00213F8h
_ClrTokenHook              equ 00213FCh
;                          equ 0021400h
;                          equ 0021404h
_DispListElementOffLA      equ 0021408h
_BitVertSplit              equ 002140Ch
_SetHomescreenHook         equ 0021410h
_ClrHomescreenHook         equ 0021414h
_SetWindowHook             equ 0021418h
_ClrWindowHook             equ 002141Ch
_SetGraphModeHook          equ 0021420h
_ClrGraphModeHook          equ 0021424h
_ParseAndStoreSysVar       equ 0021428h
_DisplayEditSysVar         equ 002142Ch
_JForceWIndowSettings      equ 0021430h
_DelVarArc                 equ 0021434h
_DelVarNoArc               equ 0021438h
_SetAllPlots               equ 002143Ch
_SetYeditHook              equ 0021440h
_ClrYeditHook              equ 0021444h
_Arc_Unarc                 equ 0021448h
_ArchiveVar                equ 002144Ch
_UnarchiveVar              equ 0021450h
_SetFontHook               equ 0021454h
_ClrFontHook               equ 0021458h
_SetRegraphHook            equ 002145Ch
_ClrRegraphHook            equ 0021460h
_RunGraphingHook           equ 0021464h
_SetTraceHook              equ 0021468h
_ClrTraceHook              equ 002146Ch
_RunTraceHook              equ 0021470h
_NDeriv                    equ 0021474h
_PolarDerivative           equ 0021478h
_JForceGraphNoKey          equ 002147Ch
_JForceGraphKey            equ 0021480h
_PowerOff                  equ 0021484h
_GetKeyRetOff              equ 0021488h
_FindGroupSym              equ 002148Ch
_LoadDEIndPaged            equ 0021490h
_SetUpPagedPtr             equ 0021494h
_PagedGet                  equ 0021498h
_SetParserHook             equ 002149Ch
_ClrParserHook             equ 00214A0h
_SetAppChangeHook          equ 00214A4h
_ClrAppChangeHook          equ 00214A8h
_SetGraphicsHook           equ 00214ACh
_ClrGraphicsHook           equ 00214B0h
_ILineNoGraphicsHook       equ 00214B4h
_ILineNoHook               equ 00214B8h
;                          equ 00214BCh
_DeleteTempPrograms        equ 00214C0h
_SetCatalog1Hook           equ 00214C4h
_ClrCatalog1Hook           equ 00214C8h
_SetHelpHook               equ 00214CCh
_ClrHelpHook               equ 00214D0h
_DispCatalogEnd            equ 00214D4h
_GetMenuKeypress           equ 00214D8h
_GetCatalogItem            equ 00214DCh
_RunCatalog2Hook           equ 00214E0h
_RunCatalog1Hook           equ 00214E4h
;                          equ 00214E8h
;                          equ 00214ECh
_DispMenuTitle             equ 00214F0h
;                          equ 00214F4h
_SetCxReDispHook           equ 00214F8h
_ClrCxReDispHook           equ 00214FCh
_DrawStatusBarMode         equ 0021500h
_BufClr                    equ 0021504h
_UnOPExec2                 equ 0021508h
_BinOPExec2                equ 002150Ch
_LoadMenuB                 equ 0021510h
_DisplayVarInfo            equ 0021514h
_SetMenuHook               equ 0021518h
_ClrMenuHook               equ 002151Ch
_GetBCOffSetIX             equ 0021520h
_GetBCOffSetIX_            equ 0021524h
_ForceFullScreen           equ 0021528h
_HLMinus5                  equ 002152Ch
;;_ret                     equ 0021530h
;                          equ 0021534h
;                          equ 0021538h
_Arc_Unarc_                equ 002153Ch
_RclExit                   equ 0021540h
_SetSilentLinkHook         equ 0021544h
_ClrSilentLinkHook         equ 0021548h
_TwoVarSet                 equ 002154Ch
_ExecClassCToken           equ 0021550h
_ExecClass3Token           equ 0021554h
_GetSysInfo                equ 0021558h
_RunChkCTenX               equ 002155Ch
_TenXNoClr                 equ 0021560h
;                          equ 0021564h
;                          equ 0021568h
_GetVarVersion             equ 002156Ch
_ParseGraphCmdToken        equ 0021570h
;                          equ 0021574h
_DeleteTempEditEqu         equ 0021578h
_PromptMoveBackLeft        equ 002157Ch
_WPutSEOLRes10E            equ 0021580h
_InvertTextInsMode         equ 0021584h
;                          equ 0021588h
_ResetDefaults             equ 002158Ch
_ZeroFinanceVars           equ 0021590h
_DispHeader                equ 0021594h
_JForceGroup               equ 0021598h
;                          equ 002159Ch
;                          equ 00215A0h
_DispCoords                equ 00215A4h
;                          equ 00215A8h
;                          equ 00215ACh
_ChkTmr                    equ 00215B0h
_ClockOff                  equ 00215B4h
_ClockOn                   equ 00215B8h
;                          equ 00215BCh
_GetDate                   equ 00215C0h
_GetDateString             equ 00215C4h
_GetDtFmt                  equ 00215C8h
_GetDtStr                  equ 00215CCh
_GetTime                   equ 00215D0h
_FormTime                  equ 00215D4h
_GetTmFmt                  equ 00215D8h
_GetTmStr                  equ 00215DCh
_SetZeroOne                equ 00215E0h
_SetDate                   equ 00215E4h
_IsOneTwoThree             equ 00215E8h
_SetTime                   equ 00215ECh
_IsOP112or24               equ 00215F0h
_ChkTimer0                 equ 00215F4h
_TimeCnv                   equ 00215F8h
_ClrWindowAndFlags         equ 00215FCh
_ResetAllLists             equ 0021600h
_DispValue                 equ 0021604h
;                          equ 0021608h
;                          equ 002160Ch
;                          equ 0021610h
_CpOP1OP2Rounded           equ 0021614h
_CpOP1OP2Rounded2          equ 0021618h
;                          equ 002161Ch
;                          equ 0021620h
_ResetIOPrompt             equ 0021624h
;                          equ 0021628h
_SetUpEditor               equ 002162Ch
_SortA                     equ 0021630h
_SortD                     equ 0021634h
;                          equ 0021638h
_IsOP1ResID                equ 002163Ch
;                          equ 0021640h
;                          equ 0021644h
;                          equ 0021648h
_ForceModeKeypress         equ 002164Ch
_DispAboutScreen           equ 0021650h
_ChkHelpHookVer            equ 0021654h
_Draw32                    equ 0021658h
;                          equ 002165Ch
;                          equ 0021660h
;                          equ 0021664h
_DrawPlotStatus            equ 0021668h
_DrawTableEditor           equ 002166Ch
_DisplayListNameEquals     equ 0021670h
_DisplayListHeader         equ 0021674h
_DispMatrixDimensions      equ 0021678h
_HighlightListEdItem       equ 002167Ch
;                          equ 0021680h
;                          equ 0021684h
_MatrixName                equ 0021688h
;                          equ 002168Ch
;                          equ 0021690h
;                          equ 0021694h
;                          equ 0021698h
;                          equ 002169Ch
_ChkCxMainPtr              equ 00216A0h
_NumError02_               equ 00216A4h
;                          equ 00216A8h
_SetupEmptyEditTempEqu     equ 00216ACh
_Res1IY0E                  equ 00216B0h
_RestoreBuffer             equ 00216B4h
;                          equ 00216B8h
;                          equ 00216BCh
;                          equ 00216C0h
;                          equ 00216C4h
;                          equ 00216C8h
;                          equ 00216CCh
_DisplayListEquals         equ 00216D0h
_GetCurPlotListOffset      equ 00216D4h
_GoToLastRow               equ 00216D8h
_DrawRectBorder_           equ 00216DCh
;                          equ 00216E0h
;                          equ 00216E4h
;                          equ 00216E8h
;                          equ 00216ECh
_NamedListToOP1            equ 00216F0h
;                          equ 00216F4h
;                          equ 00216F8h
;                          equ 00216FCh
_InitUSBDeviceCallback     equ 0021700h
_KillUSBDevice             equ 0021704h
_SetUSBConfiguration       equ 0021708h
_RequestUSBData            equ 002170Ch
_StopReceivingUSBData      equ 0021710h
_SetVertGraphActive        equ 0021714h
_ClrVertGraphActive        equ 0021718h
_SetUSBActivityHook        equ 002171Ch
_ClrUSBActivityHook        equ 0021720h
;;_ret                     equ 0021724h
_GetCurPlotOffsetPrev      equ 0021728h
_SplitUpdateStatPlotLists  equ 002172Ch
_GraphLine                 equ 0021730h
;                          equ 0021734h
;                          equ 0021738h
;                          equ 002173Ch
;                          equ 0021740h
;                          equ 0021744h
;                          equ 0021748h
_ZIfInTblEditor            equ 002174Ch
;                          equ 0021750h
_GetCurPlotOffset          equ 0021754h
;                          equ 0021758h
;                          equ 002175Ch
;                          equ 0021760h
;                          equ 0021764h
;                          equ 0021768h
_UpdateStatPlotLists       equ 002176Ch
_ChkSomethingElseFPS5      equ 0021770h
_ChkSomethingFPS5          equ 0021774h
_VDispRealOP1              equ 0021778h
_DispXEqualsNum            equ 002177Ch
_ResetGraphSettings        equ 0021780h
_InitializeVariables       equ 0021784h
;;_ret                     equ 0021788h
_DelVarSym                 equ 002178Ch
_FindAppUpNoCase           equ 0021790h
_FindAppDnNoCase           equ 0021794h
_SetupHome                 equ 0021798h
_GrPutawayFull             equ 002179Ch
;;_ret                     equ 00217A0h
_ToggleUSBSmartPadInput    equ 00217A4h
_IsUSBDeviceConnected      equ 00217A8h
_PolarEquToOP1             equ 00217ACh
_ParamXEquToOP1            equ 00217B0h
_ParamYEquToOP1            equ 00217B4h
_DispTestModeResetComplete equ 00217B8h
_PTTReset                  equ 00217BCh
_FindAppCustom             equ 00217C0h
_ClearGraphStyles          equ 00217C4h
_BufToNextBASICSeparator   equ 00217C8h
;                          equ 00217CCh
;                          equ 00217D0h
_ZooStandard               equ 00217D4h
;                          equ 00217D8h
;                          equ 00217DCh
;                          equ 00217E0h
;                          equ 00217E4h
;                          equ 00217E8h
;                          equ 00217ECh
;                          equ 00217F0h
;                          equ 00217F4h
;                          equ 00217F8h
;                          equ 00217FCh
;                          equ 0021800h
;                          equ 0021804h
;                          equ 0021808h
;                          equ 002180Ch
_AddHistoryEntryString     equ 0021810h
_CurrEntryToPrevEntry      equ 0021814h
;                          equ 0021818h
;                          equ 002181Ch
;                          equ 0021820h
;                          equ 0021824h
;                          equ 0021828h
;                          equ 002182Ch
;                          equ 0021830h
;                          equ 0021834h
;                          equ 0021838h
;                          equ 002183Ch
;                          equ 0021840h
;                          equ 0021844h
;                          equ 0021848h
;                          equ 002184Ch
;                          equ 0021850h
;                          equ 0021854h
;                          equ 0021858h
;                          equ 002185Ch
;                          equ 0021860h
;                          equ 0021864h
;                          equ 0021868h
;                          equ 002186Ch
;                          equ 0021870h
;                          equ 0021874h
;                          equ 0021878h
;                          equ 002187Ch
;                          equ 0021880h
;                          equ 0021884h
;                          equ 0021888h
;                          equ 002188Ch
;                          equ 0021890h
;                          equ 0021894h
;                          equ 0021898h
;                          equ 002189Ch
;                          equ 00218A0h
;                          equ 00218A4h
;                          equ 00218A8h
;                          equ 00218ACh
;                          equ 00218B0h
;                          equ 00218B4h
;                          equ 00218B8h
;                          equ 00218BCh
;                          equ 00218C0h
;                          equ 00218C4h
;                          equ 00218C8h
;                          equ 00218CCh
;                          equ 00218D0h
;                          equ 00218D4h
;                          equ 00218D8h
;                          equ 00218DCh
;                          equ 00218E0h
;                          equ 00218E4h
;                          equ 00218E8h
;                          equ 00218ECh
_RunInitialBootMenu        equ 00218F0h
;                          equ 00218F4h
;                          equ 00218F8h
;                          equ 00218FCh
_Clr05RclFlags             equ 0021900h
;                          equ 0021904h
;                          equ 0021908h
;                          equ 002190Ch
;                          equ 0021910h
_DeleteHistoryEntry        equ 0021914h
;                          equ 0021918h
;                          equ 002191Ch
;                          equ 0021920h
;                          equ 0021924h
;                          equ 0021928h
;                          equ 002192Ch
;                          equ 0021930h
;                          equ 0021934h
;                          equ 0021938h
;                          equ 002193Ch
_CommonKeys_               equ 0021940h
;                          equ 0021944h
;                          equ 0021948h
;                          equ 002194Ch
;                          equ 0021950h
;                          equ 0021954h
;                          equ 0021958h
;                          equ 002195Ch
;                          equ 0021960h
;                          equ 0021964h
;                          equ 0021968h
;                          equ 002196Ch
;                          equ 0021970h
;                          equ 0021974h
;                          equ 0021978h
;                          equ 002197Ch
;                          equ 0021980h
;                          equ 0021984h
;                          equ 0021988h
;                          equ 002198Ch
;                          equ 0021990h
;                          equ 0021994h
_ResetLastEntryStack       equ 0021998h
;                          equ 002199Ch
;                          equ 00219A0h
_jp_JForceCmdNoChar        equ 00219A4h
_Load_LFont                equ 00219A8h
;                          equ 00219ACh
;                          equ 00219B0h
;                          equ 00219B4h
;                          equ 00219B8h
;                          equ 00219BCh
;                          equ 00219C0h
;                          equ 00219C4h
;                          equ 00219C8h
;                          equ 00219CCh
;                          equ 00219D0h
;                          equ 00219D4h
;                          equ 00219D8h
_EnterSelfTest             equ 00219DCh
_DrawEntrySepLine          equ 00219E0h
;                          equ 00219E4h
_GetGraphModeProperties    equ 00219E8h
;                          equ 00219ECh
;                          equ 00219F0h
;                          equ 00219F4h
;                          equ 00219F8h
;                          equ 00219FCh
;                          equ 0021A00h
;                          equ 0021A04h
;                          equ 0021A08h
;                          equ 0021A0Ch
_ClrLCDAll                 equ 0021A10h
_BufIPoint                 equ 0021A14h
;                          equ 0021A18h
;                          equ 0021A1Ch
;                          equ 0021A20h
;                          equ 0021A24h
_SetDrawFGColorA           equ 0021A28h
;                          equ 0021A2Ch
;                          equ 0021A30h
;                          equ 0021A34h
_DrawGraphBackground       equ 0021A38h
_DrawStatusBar             equ 0021A3Ch
;                          equ 0021A40h
;                          equ 0021A44h
;                          equ 0021A48h
;                          equ 0021A4Ch
_DrawBatteryIndicator      equ 0021A50h
_DrawBatteryStatus         equ 0021A54h
_VDispHL                   equ 0021A58h
_PDspGrphNoColorReload     equ 0021A5Ch
;                          equ 0021A60h
;                          equ 0021A64h
;                          equ 0021A68h
;                          equ 0021A6Ch
;                          equ 0021A70h
;                          equ 0021A74h
;                          equ 0021A78h
;                          equ 0021A7Ch
;                          equ 0021A80h
;                          equ 0021A84h
;                          equ 0021A88h
;                          equ 0021A8Ch
;                          equ 0021A90h
;                          equ 0021A94h
;                          equ 0021A98h
;                          equ 0021A9Ch
;                          equ 0021AA0h
;                          equ 0021AA4h
;                          equ 0021AA8h
;                          equ 0021AACh
;                          equ 0021AB0h
_DrawStatusBarInfo         equ 0021AB4h
_RestoreLCDBrightness      equ 0021AB8h
_RestoreLCDBrightness_     equ 0021ABCh
_DimLCDSlow                equ 0021AC0h
;                          equ 0021AC4h
;                          equ 0021AC8h
;                          equ 0021ACCh
;                          equ 0021AD0h
;                          equ 0021AD4h
;                          equ 0021AD8h
;                          equ 0021ADCh
_SetTextFGBGcolors         equ 0021AE0h
_SetTextFGBGcolors_        equ 0021AE4h
_SetTextBGcolor            equ 0021AE8h
_VPutPS                    equ 0021AECh
;                          equ 0021AF0h
;                          equ 0021AF4h
;                          equ 0021AF8h
;                          equ 0021AFCh
_DrawTILogo                equ 0021B00h
_DrawThickRectBorder       equ 0021B04h
;                          equ 0021B08h
_DrawStatusBarTextClr      equ 0021B0Ch
;                          equ 0021B10h
;                          equ 0021B14h
;                          equ 0021B18h
;                          equ 0021B1Ch
_VPutPSN                   equ 0021B20h
;                          equ 0021B24h
;                          equ 0021B28h
;                          equ 0021B2Ch
;                          equ 0021B30h
_RStrGraphFlags            equ 0021B34h
;                          equ 0021B38h
;                          equ 0021B3Ch
_VPutMapSpecial            equ 0021B40h
;                          equ 0021B44h
;                          equ 0021B48h
;                          equ 0021B4Ch
;                          equ 0021B50h
;                          equ 0021B54h
;                          equ 0021B58h
;                          equ 0021B5Ch
;                          equ 0021B60h
_DrawSprite16bpp           equ 0021B64h
;                          equ 0021B68h
;                          equ 0021B6Ch
;                          equ 0021B70h
;                          equ 0021B74h
;                          equ 0021B78h
;                          equ 0021B7Ch
;                          equ 0021B80h
;                          equ 0021B84h
;                          equ 0021B88h
;                          equ 0021B8Ch
;                          equ 0021B90h
;                          equ 0021B94h
;                          equ 0021B98h
;                          equ 0021B9Ch
;                          equ 0021BA0h
;                          equ 0021BA4h
;                          equ 0021BA8h
_GetColorValue             equ 0021BACh
;                          equ 0021BB0h
;                          equ 0021BB4h
;                          equ 0021BB8h
;                          equ 0021BBCh
;                          equ 0021BC0h
_GraphBGColorToDrawBGColor equ 0021BC4h
_SetWhiteDrawBGColor       equ 0021BC8h
;                          equ 0021BCCh
_ChkResAppTextSave         equ 0021BD0h
_ChkCxMain                 equ 0021BD4h
;                          equ 0021BD8h
;                          equ 0021BDCh
_DrawRectBorder__          equ 0021BE0h
;                          equ 0021BE4h
;                          equ 0021BE8h
;                          equ 0021BECh
;                          equ 0021BF0h
;                          equ 0021BF4h
;                          equ 0021BF8h
;                          equ 0021BFCh
;                          equ 0021C00h
;                          equ 0021C04h
;                          equ 0021C08h
;                          equ 0021C0Ch
;                          equ 0021C10h
;                          equ 0021C14h
;                          equ 0021C18h
;                          equ 0021C1Ch
;                          equ 0021C20h
;                          equ 0021C24h
;                          equ 0021C28h
;                          equ 0021C2Ch
;                          equ 0021C30h
;                          equ 0021C34h
;                          equ 0021C38h
;                          equ 0021C3Ch
;                          equ 0021C40h
;                          equ 0021C44h
_DrawLineEndEntry          equ 0021C48h
;                          equ 0021C4Ch
;                          equ 0021C50h
;;_ret                     equ 0021C54h
;                          equ 0021C58h
;                          equ 0021C5Ch
;                          equ 0021C60h
;                          equ 0021C64h
;                          equ 0021C68h
_BitGrfFuncM               equ 0021C6Ch
;;_ret                     equ 0021C70h
_GetScrollPxlAmount        equ 0021C74h
_os_PushErrorHandler       equ 0021C78h
_os_PopErrorHandler        equ 0021C7Ch
_os_ThrowError             equ 0021C80h
_os_RealCopy               equ 0021C84h
_os_RealAsinRad            equ 0021C88h
_os_RealAcosRad            equ 0021C8Ch
_os_RealAtanRad            equ 0021C90h
_os_RealAdd                equ 0021C94h
_os_CplxAdd                equ 0021C98h
_os_RealCompare            equ 0021C9Ch
_os_RealCosRad             equ 0021CA0h
_os_RealRadToDeg           equ 0021CA4h
_os_RealDiv                equ 0021CA8h
_os_RealExp                equ 0021CACh
_os_RealFloor              equ 0021CB0h
_os_RealToStr              equ 0021CB4h
_os_RealFrac               equ 0021CB8h
_os_RealGcd                equ 0021CBCh
_os_RealRoundInt           equ 0021CC0h
_os_RealLcm                equ 0021CC4h
_os_RealLog                equ 0021CC8h
_os_RealMax                equ 0021CCCh
_os_RealMin                equ 0021CD0h
_os_RealMul                equ 0021CD4h
_os_RealNcr                equ 0021CD8h
_os_RealNeg                equ 0021CDCh
_os_RealNpr                equ 0021CE0h
_os_RealPow                equ 0021CE4h
_os_RealDegToRad           equ 0021CE8h
_os_RealRandInt            equ 0021CECh
_os_RealInv                equ 0021CF0h
_os_RealMod                equ 0021CF4h
_os_RealRound              equ 0021CF8h
_os_RealSinRad             equ 0021CFCh
_os_RealSqrt               equ 0021D00h
_os_RealSub                equ 0021D04h
_os_RealTanRad             equ 0021D08h
_os_StrToReal              equ 0021D0Ch
_os_RealTrunc              equ 0021D10h
_os_SetFlagBits            equ 0021D14h
_os_ResetFlagBits          equ 0021D18h
_os_TestFlagBits           equ 0021D1Ch
_os_SetFlagByte            equ 0021D20h
_os_GetFlagByte            equ 0021D24h
_os_GetCursorPos           equ 0021D28h
_os_PutStrFull             equ 0021D2Ch
_os_PutStrLine             equ 0021D30h
_os_SetCursorPos           equ 0021D34h
_os_GetKey                 equ 0021D38h
_os_GetCSC                 equ 0021D3Ch
_os_AppInit                equ 0021D40h
;                          equ 0021D44h
_ChkBCIs0                  equ 0021D48h
_ChkDEIs0                  equ 0021D4Ch
_ChkHLIs0                  equ 0021D50h
_SetAToBCU                 equ 0021D54h
_SetAToDEU                 equ 0021D58h
_SetAToHLU                 equ 0021D5Ch
_SetBCUToA                 equ 0021D60h
_SetBCUToB                 equ 0021D64h
_SetDEUToA                 equ 0021D68h
_SetDEUToB                 equ 0021D6Ch
_SetHLUToA                 equ 0021D70h
_SetHLUToB                 equ 0021D74h
_SignExtendBC              equ 0021D78h
_SignExtendDE              equ 0021D7Ch
_SignExtendHL              equ 0021D80h
_SetBCUTo0                 equ 0021D84h
_SetDEUTo0                 equ 0021D88h
_SetHLUTo0                 equ 0021D8Ch
_DivHLByA                  equ 0021D90h
_CpHLDE_s                  equ 0021D94h
_CpHLDE_                   equ 0021D98h
_LoadDEInd_s               equ 0021D9Ch
_LoadDEInd                 equ 0021DA0h
_CpHLDEBC                  equ 0021DA4h
_NegBC                     equ 0021DA8h
_NegDE                     equ 0021DACh
_StrCmpre                  equ 0021DB0h
_AddHLAndA                 equ 0021DB4h
_NextFlashPage             equ 0021DB8h
_PrevFlashPage             equ 0021DBCh
_SwapEndianHL_s            equ 0021DC0h
_ReloadAppEntryVecs        equ 0021DC4h
;                          equ 0021DC8h
;                          equ 0021DCCh
;                          equ 0021DD0h
;                          equ 0021DD4h
;                          equ 0021DD8h
;                          equ 0021DDCh
_os_ClearVRAMLines         equ 0021DE0h
_os_DisableCursor          equ 0021DE4h
_os_EnableCursor           equ 0021DE8h
;                          equ 0021DECh
;                          equ 0021DF0h
;                          equ 0021DF4h
;                          equ 0021DF8h
;                          equ 0021DFCh
_os_FontDrawText           equ 0021E00h
;                          equ 0021E04h
;                          equ 0021E08h
;                          equ 0021E0Ch
;                          equ 0021E10h
_os_FontGetHeight          equ 0021E14h
_os_FontGetWidth           equ 0021E18h
_os_InitDrawing            equ 0021E1Ch
_os_SetDrawBGColor         equ 0021E20h
_os_SetDrawFGColor         equ 0021E24h
_os_FontSelect             equ 0021E28h
;                          equ 0021E2Ch
;                          equ 0021E30h
_os_ReturnByte             equ 0021E34h
_os_ReturnByteEvenBetter   equ 0021E38h
;                          equ 0021E3Ch
;                          equ 0021E40h
;                          equ 0021E44h
;                          equ 0021E48h
;                          equ 0021E4Ch
;                          equ 0021E50h
;                          equ 0021E54h
;                          equ 0021E58h
;                          equ 0021E5Ch
;                          equ 0021E60h
;                          equ 0021E64h
_ChkACplx                  equ 0021E68h
;                          equ 0021E6Ch
_os_RclAns                 equ 0021E70h
;                          equ 0021E74h
;                          equ 0021E78h
;                          equ 0021E7Ch
;                          equ 0021E80h
;                          equ 0021E84h
;                          equ 0021E88h
_SetPolarEquToOP1          equ 0021E8Ch
;                          equ 0021E90h
;                          equ 0021E94h
;                          equ 0021E98h
;                          equ 0021E9Ch
;                          equ 0021EA0h
;                          equ 0021EA4h
;                          equ 0021EA8h
;                          equ 0021EACh
;                          equ 0021EB0h
;                          equ 0021EB4h
;                          equ 0021EB8h
;                          equ 0021EBCh
;                          equ 0021EC0h
;                          equ 0021EC4h
_os_SetTimer1              equ 0021EC8h
_os_DisableTimer1          equ 0021ECCh
_os_SetKbdKey              equ 0021ED0h
_os_GetSystemInfo          equ 0021ED4h
;                          equ 0021ED8h
;                          equ 0021EDCh
_DispHL                    equ 0021EE0h
_os_GetDrawBGColor_BROKEN  equ 0021EE4h		; fixed in OS 5.2
_os_GetDrawFGColor         equ 0021EE8h
_os_FontGetID              equ 0021EECh
;                          equ 0021EF0h
_os_RealToInt24            equ 0021EF4h
_os_Int24ToReal            equ 0021EF8h
_GetOpenLibPtr             equ 0021EFCh
_RestoreColCoordinates     equ 0021F00h
;                          equ 0021F04h
;                          equ 0021F08h
;                          equ 0021F0Ch
;                          equ 0021F10h
;                          equ 0021F14h
;                          equ 0021F18h
;                          equ 0021F1Ch
;                          equ 0021F20h
;                          equ 0021F24h
;                          equ 0021F28h
;                          equ 0021F2Ch
;                          equ 0021F30h
;                          equ 0021F34h
;                          equ 0021F38h
;                          equ 0021F3Ch
;                          equ 0021F40h
_VPutMapNoReset0IY23       equ 0021F44h
;                          equ 0021F48h
;                          equ 0021F4Ch
_BufCpy                    equ 0021F50h
;                          equ 0021F54h
;                          equ 0021F58h
;                          equ 0021F5Ch
_DrawStandardEntrySepLine  equ 0021F60h
_DrawHomeNewSepLine        equ 0021F64h
_DrawStatusBarText         equ 0021F68h
;                          equ 0021F6Ch
;                          equ 0021F70h
;                          equ 0021F74h
;                          equ 0021F78h
;                          equ 0021F7Ch
_MovFrOP1OP2               equ 0021F80h
;                          equ 0021F84h
;                          equ 0021F88h
;                          equ 0021F8Ch
;                          equ 0021F90h
;                          equ 0021F94h
_ChkInRam                  equ 0021F98h
;                          equ 0021F9Ch
;                          equ 0021FA0h
_FontGetWidth              equ 0021FA4h
_os_ForceCmdNoChar         equ 0021FA8h
_os_DelVarEntry            equ 0021FACh
_os_GetSymTablePtr         equ 0021FB0h
_os_NextSymEntry           equ 0021FB4h
_os_ChkFindSym             equ 0021FB8h
_os_GetVarSize             equ 0021FBCh
_os_GetVarSizeBytes        equ 0021FC0h
;                          equ 0021FC4h
_os_GetRealListElement     equ 0021FC8h
_os_GetRealVar             equ 0021FCCh
_os_ResizeList             equ 0021FD0h
_os_ResizeMatrix           equ 0021FD4h
;                          equ 0021FD8h
_os_SetRealListElement     equ 0021FDCh
_os_SetRealVar             equ 0021FE0h
_os_GetAppVersionString    equ 0021FE4h
;                          equ 0021FE8h
;                          equ 0021FECh
_os_MemChk                 equ 0021FF0h
;                          equ 0021FF4h
;                          equ 0021FF8h
;                          equ 0021FFCh
;                          equ 0022000h
;                          equ 0022004h
;                          equ 0022008h
;                          equ 002200Ch
;                          equ 0022010h
;                          equ 0022014h
;                          equ 0022018h
;                          equ 002201Ch
;                          equ 0022020h
;                          equ 0022024h
;                          equ 0022028h
;                          equ 002202Ch
;                          equ 0022030h
;                          equ 0022034h
;                          equ 0022038h
;                          equ 002203Ch
_ArcChk                    equ 0022040h
_LoadDEIndFlash            equ 0022044h
_ChkInRamB                 equ 0022048h
;                          equ 002204Ch
;                          equ 0022050h
;                          equ 0022054h
_os_InitUSBDeviceCallback  equ 0022058h
_os_KillUSBDevice          equ 002205Ch
_os_SetUSBConfiguration    equ 0022060h
_os_RequestUSBData         equ 0022064h
_os_StopReceivingUSBData   equ 0022068h
;                          equ 002206Ch
;                          equ 0022070h
_Mov11ToOP1                equ 0022074h
_FindFreeArcSpot           equ 0022078h
;                          equ 002207Ch
_os_SetTimer2              equ 0022080h
_os_DisableTimer2          equ 0022084h
;                          equ 0022088h
;;_ret                     equ 002208Ch
_os_GetYDrawLocation       equ 0022090h
_os_SetYDrawLocation       equ 0022094h
_RunLocalizeHook           equ 0022098h
_os_IntSize                equ 002209Ch
_os_ClearStatusBarLow      equ 00220A0h
;                          equ 00220A4h
_NMIHandler                equ 00220A8h
;                          equ 00220ACh
;                          equ 00220B0h
;                          equ 00220B4h
;                          equ 00220B8h
;                          equ 00220BCh
;                          equ 00220C0h
;                          equ 00220C4h
;                          equ 00220C8h
;                          equ 00220CCh
;                          equ 00220D0h
;                          equ 00220D4h
;                          equ 00220D8h
;                          equ 00220DCh
;                          equ 00220E0h
;                          equ 00220E4h
;                          equ 00220E8h
;                          equ 00220ECh
;                          equ 00220F0h
;                          equ 00220F4h
;                          equ 00220F8h
;                          equ 00220FCh
;                          equ 0022100h
;                          equ 0022104h
;                          equ 0022108h
;                          equ 002210Ch
;                          equ 0022110h
;                          equ 0022114h
;                          equ 0022118h
;                          equ 002211Ch
;                          equ 0022120h
;                          equ 0022124h
;                          equ 0022128h
;                          equ 002212Ch
;                          equ 0022130h
;                          equ 0022134h
;                          equ 0022138h
;                          equ 002213Ch
;                          equ 0022140h
;                          equ 0022144h
;                          equ 0022148h
;                          equ 002214Ch
;                          equ 0022150h
;                          equ 0022154h
;                          equ 0022158h
;                          equ 002215Ch
;                          equ 0022160h
_os_RToP                   equ 0022164h
_os_PToR                   equ 0022168h
_os_ResetEditOpen          equ 002216Ch
_os_FloatToReal            equ 0022170h
_os_RealToFloat            equ 0022174h
_os_FontDrawTransText      equ 0022178h
_os_DelAppVar              equ 002217Ch
_os_GetAppVarDataPtr       equ 0022180h
_os_CreateAppVar           equ 0022184h
;                          equ 0022188h
;                          equ 002218Ch
;                          equ 0022190h
;                          equ 0022194h
_os_CreateString           equ 0022198h
_os_GetStringDataPtr       equ 002219Ch
;                          equ 00221A0h
;                          equ 00221A4h
;                          equ 00221A8h
;                          equ 00221ACh
;                          equ 00221B0h
;                          equ 00221B4h
;                          equ 00221B8h
;                          equ 00221BCh
;                          equ 00221C0h
;                          equ 00221C4h
;                          equ 00221C8h
;                          equ 00221CCh
;                          equ 00221D0h
;                          equ 00221D4h
;                          equ 00221D8h
;                          equ 00221DCh
;                          equ 00221E0h
;                          equ 00221E4h
;                          equ 00221E8h
;                          equ 00221ECh
;                          equ 00221F0h
;                          equ 00221F4h
;                          equ 00221F8h

; Boot Calls
;-----------------------------------
_boot_GetHardwareVers      equ 0000084h
_boot_GetKeyID             equ 0000088h
_boot_GetBootVerMinor      equ 000008Ch
_boot_GetBootVerBuild      equ 0000090h
_dbgout                    equ 0000094h
__longjmp                  equ 0000098h
__memchr                   equ 000009Ch
__memcmp                   equ 00000A0h
__memcpy                   equ 00000A4h
__memmove                  equ 00000A8h
__memset                   equ 00000ACh
__memclear                 equ 00000B0h
_printf                    equ 00000B4h
__setjmp                   equ 00000B8h
_sprintf                   equ 00000BCh
__strcat                   equ 00000C0h
__strchr                   equ 00000C4h
__strcmp                   equ 00000C8h
__strcpy                   equ 00000CCh
__strcspn                  equ 00000D0h
__strlen                   equ 00000D4h
__strncat                  equ 00000D8h
__strncmp                  equ 00000DCh
__strncpy                  equ 00000E0h
__strpbrk                  equ 00000E4h
__strrchr                  equ 00000E8h
__strspn                   equ 00000ECh
__strstr                   equ 00000F0h
_strtok                    equ 00000F4h
_ret                       equ 00000F8h
__bldiy                    equ 00000FCh
__bshl                     equ 0000100h
__bshru                    equ 0000104h
__bstiy                    equ 0000108h
__bstix                    equ 000010Ch
__case                     equ 0000110h
__case16                   equ 0000114h
__case16D                  equ 0000118h
__case24                   equ 000011Ch
__case24D                  equ 0000120h
__case8                    equ 0000124h
__case8D                   equ 0000128h
__frameset                 equ 000012Ch
__frameset0                equ 0000130h
__iand                     equ 0000134h
__icmpzero                 equ 0000138h
__idivs                    equ 000013Ch
__idivu                    equ 0000140h
__idvrmu                   equ 0000144h
__ildix                    equ 0000148h
__ildiy                    equ 000014Ch
__imul_b                   equ 0000150h
__imulu                    equ 0000154h
__imuls                    equ 0000158h
__indcall                  equ 000015Ch
__ineg                     equ 0000160h
__inot                     equ 0000164h
__ior                      equ 0000168h
__irems                    equ 000016Ch
__iremu                    equ 0000170h
__ishl                     equ 0000174h
__ishl_b                   equ 0000178h
__ishrs                    equ 000017Ch
__ishrs_b                  equ 0000180h
__ishru                    equ 0000184h
__ishru_b                  equ 0000188h
__istix                    equ 000018Ch
__istiy                    equ 0000190h
__itol                     equ 0000194h
__ixor                     equ 0000198h
__ladd                     equ 000019Ch
__ladd_b                   equ 00001A0h
__land                     equ 00001A4h
__lcmps                    equ 00001A8h
__lcmpu                    equ 00001ACh
__lcmpzero                 equ 00001B0h
__ldivs                    equ 00001B4h
__ldivu                    equ 00001B8h
__ldvrmu                   equ 00001BCh
__lldix                    equ 00001C0h
__lldiy                    equ 00001C4h
__lmuls                    equ 00001C8h
__lmulu                    equ 00001CCh
__lneg                     equ 00001D0h
__lnot                     equ 00001D4h
__lor                      equ 00001D8h
__lrems                    equ 00001DCh
__lremu                    equ 00001E0h
__lshl                     equ 00001E4h
__lshrs                    equ 00001E8h
__lshru                    equ 00001ECh
__lstix                    equ 00001F0h
__lstiy                    equ 00001F4h
__lsub                     equ 00001F8h
__lxor                     equ 00001FCh
__sand                     equ 0000200h
__scmpzero                 equ 0000204h
__sdivs                    equ 0000208h
__sdivu                    equ 000020Ch
__seqcase                  equ 0000210h
__seqcaseD                 equ 0000214h
__setflag                  equ 0000218h
__sldix                    equ 000021Ch
__sldiy                    equ 0000220h
__smuls                    equ 0000224h
__smulu                    equ 0000228h
__sneg                     equ 000022Ch
__snot                     equ 0000230h
__sor                      equ 0000234h
__srems                    equ 0000238h
__sremu                    equ 000023Ch
__sshl                     equ 0000240h
__sshl_b                   equ 0000244h
__sshrs                    equ 0000248h
__sshrs_b                  equ 000024Ch
__sshru                    equ 0000250h
__sshru_b                  equ 0000254h
__sstix                    equ 0000258h
__sstiy                    equ 000025Ch
__stoi                     equ 0000260h
__stoiu                    equ 0000264h
__sxor                     equ 0000268h
__fppack                   equ 000026Ch
__fadd                     equ 0000270h
__fcmp                     equ 0000274h
__fdiv                     equ 0000278h
__ftol                     equ 000027Ch
__ultof                    equ 0000280h
__ltof                     equ 0000284h
__fmul                     equ 0000288h
__fneg                     equ 000028Ch
__fsub                     equ 0000290h
_FLTMAX                    equ 0000294h
_sqrtf                     equ 0000298h
__frbtof                   equ 000029Ch
__frftob                   equ 00002A0h
__frftoub                  equ 00002A4h
__frftoi                   equ 00002A8h
__frftoui                  equ 00002ACh
__frftos                   equ 00002B0h
__frftous                  equ 00002B4h
__fritof                   equ 00002B8h
__fruitof                  equ 00002BCh
__frstof                   equ 00002C0h
__frubtof                  equ 00002C4h
__frustof                  equ 00002C8h
_ResetPorts                equ 00002CCh
_ChkIfOSInterruptAvailable equ 00002D0h
_WriteFlashByte            equ 00002D4h
_EraseFlash                equ 00002D8h
_EraseFlashSector          equ 00002DCh
_WriteFlash                equ 00002E0h
_WriteFlashByteDuplicate   equ 00002E4h
_WriteFlashA               equ 00002E8h
_CleanupCertificate        equ 00002ECh
_ClrHeap                   equ 00002F0h
_CpyToHeap                 equ 00002F4h
_ChkHeapTop                equ 00002F8h
_ExecuteInRAM              equ 00002FCh
_ExecuteInRAMDup           equ 0000300h
_ExecuteInRAMDup2          equ 0000304h
_ChkCertSpace              equ 0000308h
_GetFieldSizeFromType      equ 000030Ch
_FindFirstCertField        equ 0000310h
_FindField                 equ 0000314h
_FindNextField             equ 0000318h
_GetCertificateEnd         equ 000031Ch
_GetFieldSizeFromType_     equ 0000320h
_GetFieldFromSize          equ 0000324h
_NextFieldFromSize         equ 0000328h
_NextFieldFromType         equ 000032Ch
_GetOffsetToNextField      equ 0000330h
_WriteFlashUnsafe          equ 0000334h
_boot_GetCertCalcString    equ 0000338h
_boot_GetCertCalcID        equ 000033Ch
_GetSerial                 equ 0000340h
;                          equ 0000344h
_Mult16By8                 equ 0000348h
_Div16By8                  equ 000034Ch
_Div16By16                 equ 0000350h
_Div32By16                 equ 0000354h
_CmpStr                    equ 0000358h
_boot_Sha256Init           equ 000035Ch
_boot_Sha256Part           equ 0000360h
_boot_Sha256Hash           equ 0000364h
_FindAppHeaderSubField     equ 0000368h
;                          equ 000036Ch
_FindAppHeaderTimestamp    equ 0000370h
_boot_ClearVRAM            equ 0000374h
_boot_PutS                 equ 0000378h
_PutSpinner                equ 000037Ch
_boot_GetLFontPtr          equ 0000380h
_boot_InitializeHardware   equ 0000384h
_boot_TurnOffHardware      equ 0000388h
_MakeColCmd                equ 000038Ch
_boot_NewLine              equ 0000390h
_PutBootVersion            equ 0000394h
_DrawSectorProtectionTable equ 0000398h
_boot_Set6MHzMode          equ 000039Ch
_boot_Set48MHzMode         equ 00003A0h
_boot_Set6MHzModeI         equ 00003A4h
_boot_Set48MHzModeI        equ 00003A8h
_CheckHardware             equ 00003ACh
_GetBatteryStatus          equ 00003B0h
_Delay10ms                 equ 00003B4h
_DelayTenTimesAms          equ 00003B8h
;                          equ 00003BCh
;                          equ 00003C0h
;                          equ 00003C4h
;                          equ 00003C8h
_usb_IsBusPowered          equ 00003CCh
_KeypadScan                equ 00003D0h
_KeypadScanFull            equ 00003D4h
;_ret                      equ 00003D8h
;_ret                      equ 00003DCh
_MarkOSInvalid             equ 00003E0h
_usb_BusPowered            equ 00003E4h
_usb_SelfPowered           equ 00003E8h
;                          equ 00003ECh
;                          equ 00003F0h
;                          equ 00003F4h
;                          equ 00003F8h
_usb_SetDeviceB            equ 00003FCh
;                          equ 0000400h
_usb_DMACXReadNext         equ 0000404h
_usb_DMACXWrite            equ 0000408h
_usb_DMACXRead             equ 000040Ch
_usb_DMACXWriteNext        equ 0000410h
_usb_DMACXWriteCheck       equ 0000414h
;                          equ 0000418h
;                          equ 000041Ch
;                          equ 0000420h
;                          equ 0000424h
;                          equ 0000428h
;                          equ 000042Ch
;                          equ 0000430h
;                          equ 0000434h
;                          equ 0000438h
;                          equ 000043Ch
;                          equ 0000440h
;                          equ 0000444h
;                          equ 0000448h
;                          equ 000044Ch
;                          equ 0000450h
;                          equ 0000454h
;                          equ 0000458h
;                          equ 000045Ch
_MarkOSValid               equ 0000460h
;                          equ 0000464h
;                          equ 0000468h
;                          equ 000046Ch
;                          equ 0000470h
;                          equ 0000474h
;                          equ 0000478h
;                          equ 000047Ch
;                          equ 0000480h
;                          equ 0000484h
;                          equ 0000488h
;                          equ 000048Ch
;                          equ 0000490h
;                          equ 0000494h
;                          equ 0000498h
;                          equ 000049Ch
;                          equ 00004A0h
;                          equ 00004A4h
_usb_SetDMAState           equ 00004A8h
_usb_DMATransfer           equ 00004ACh
_usb_DMACXTransferWait     equ 00004B0h
;                          equ 00004B4h
;                          equ 00004B8h
_usb_ResetFIFOS            equ 00004BCh
;                          equ 00004C0h
;                          equ 00004C4h
;                          equ 00004C8h
;                          equ 00004CCh
;                          equ 00004D0h
;                          equ 00004D4h
;                          equ 00004D8h
;                          equ 00004DCh
;                          equ 00004E0h
;                          equ 00004E4h
;                          equ 00004E8h
;                          equ 00004ECh
_usb_ResetTimer            equ 00004F0h
_usb_DisableTimer          equ 00004F4h
_usb_EnableTimer           equ 00004F8h
;                          equ 00004FCh
;                          equ 0000500h
;                          equ 0000504h
;                          equ 0000508h
;                          equ 000050Ch
;                          equ 0000510h
;                          equ 0000514h
;                          equ 0000518h
;                          equ 000051Ch
_boot_SetTimersControl     equ 0000520h
_boot_GetTimersControl     equ 0000524h
_boot_SetTimersInterrupt   equ 0000528h
_boot_GetTimersInterrupt   equ 000052Ch
_boot_SetTimersInterruptM  equ 0000530h
_boot_GetTimersInterruptM  equ 0000534h
_boot_SetTimer1Counter     equ 0000538h
_boot_GetTimer1Counter     equ 000053Ch
_boot_SetTimer1ReloadValue equ 0000540h
_boot_GetTimer1ReloadValue equ 0000544h
_boot_SetTimer1MatchValue1 equ 0000548h
_boot_GetTimer1MatchValue1 equ 000054Ch
_boot_SetTimer1MatchValue2 equ 0000550h
_boot_GetTimer1MatchValue2 equ 0000554h
_boot_SetTimer2Counter     equ 0000558h
_boot_GetTimer2Counter     equ 000055Ch
_boot_SetTimer2ReloadValue equ 0000560h
_boot_GetTimer2ReloadValue equ 0000564h
_boot_SetTimer2MatchValue1 equ 0000568h
_boot_GetTimer2MatchValue1 equ 000056Ch
_boot_SetTimer2MatchValue2 equ 0000570h
_boot_GetTimer2MatchValue2 equ 0000574h
_CheckIfEmulated           equ 0000578h
_boot_GetOnInt             equ 000057Ch
_boot_RTCIntHandler        equ 0000580h
_boot_RTCInitialize        equ 0000584h
_boot_RTCGetInitStatus     equ 0000588h
_boot_RTCEnable            equ 000058Ch
_boot_RTCDisable           equ 0000590h
_boot_RTCSet24Hours        equ 0000594h
;                          equ 0000598h
;                          equ 000059Ch
_boot_RTCAckAlarmInt       equ 00005A0h
;                          equ 00005A4h
_boot_RTCWriteTime         equ 00005A8h
_boot_RTCGetTime12Hour     equ 00005ACh
_boot_RTCGetTime           equ 00005B0h
_boot_RTCSetTime           equ 00005B4h
_boot_RTCGetAlarm          equ 00005B8h
_boot_RTCSetAlarmSafe      equ 00005BCh
_boot_RTCCheckAlarmInt     equ 00005C0h
_boot_RTCSetAlarmInt       equ 00005C4h
_boot_RTCIsAfternoon       equ 00005C8h
_boot_RTCGetDay            equ 00005CCh
_boot_RTCSetAlarmIntSafe   equ 00005D0h
_boot_RTCSetAlarm          equ 00005D4h
_boot_RTCEnableInt         equ 00005D8h
_boot_RTCDisableInt        equ 00005DCh
_boot_RTCSetCallback       equ 00005E0h
_boot_RTCResetTimeStruct   equ 00005E4h
;                          equ 00005E8h
_boot_RTCSetFlags          equ 00005ECh
;                          equ 00005F0h
_CheckEmulationBit         equ 00005F4h
_usb_SetDMAAddress         equ 00005F8h
;                          equ 00005FCh
_boot_SectorsBegin         equ 0000600h
;                          equ 0000604h
_usb_InEndpointClrStall    equ 0000608h
_usb_InEndpointSetStall    equ 000060Ch
_usb_InEndpointClrReset    equ 0000610h
_usb_InEndpointSetReset    equ 0000614h
_usb_InEndpointSendZlp     equ 0000618h
_usb_OutEndpointClrStall   equ 000061Ch
_usb_OutEndpointSetStall   equ 0000620h
_usb_OutEndpointClrReset   equ 0000624h
_usb_OutEndpointSetReset   equ 0000628h
_usb_SetFifoMap            equ 000062Ch
_usb_SetEndpointConfig     equ 0000630h
_usb_ClrEndpointConfig     equ 0000634h
_usb_SetFifoConfig         equ 0000638h
;                          equ 000063Ch

;RAM Equates
;--------------------------------
ramStart		equ 0D00000h
flags			equ 0D00080h		; location of OS Flags (+-80h)
textFlagsLoc		equ 0D00085h            ; location of Text Flags
apdFlagsLoc		equ 0D00088h		; location of APD Flags
appFlagsLoc		equ 0D0008Dh		; location of App Flags
rclFlagsLoc		equ 0D0008Eh            ; location of RCLQueue Flags
shiftFlagsLoc		equ 0D00092h            ; location of Shifting Flags
mathprintFlagsLoc	equ 0D000C4h		; location of MathPrint Flags

strtokPtr		equ 0D000FFh            ; location of pointer used by C strtok
printRoutine		equ 0D00108h            ; stores pointer to printing routines (3 scrap)

flashByte		equ 0D00125h		; used for writing to flash

cellOverrideAddr	equ 0D00166h
curCell			equ 0D0016Eh            ; selected list cell

SmallEditCancelParse	equ 0D001A4h

curRowBackup		equ 0D0033Ch		; backup of curRow
shiftFlagsLocBackup	equ 0D00358h		; backup of shiftFlagsLoc
appFlagsLocBackup	equ 0D00366h		; backup of appFlagsLoc
penRowBackup		equ 0D003E3h		; backup of penRow
mathprintBackup		equ 0D003E6h		; backup of mathprint flags
winLeftEdgeBackup	equ 0D003D2h		; backup of winLeftEdge
catalogCurrentBackup	equ 0D003D3h		; backup of catalogCurrent
menuCurrentSubBackup	equ 0D003D6h		; backup of menuCurrentSub
menuNumMenusBackup	equ 0D003D8h		; backup of menuNumMenus
menuCurrentBackup	equ 0D003DAh		; backup of menuCurrent
cxCurAppBackup		equ 0D003DDh		; backup of cxCurApp

curUnderBackup		equ 0D003E8h		; backup of curUnder

appData			equ 0D00429h		; used for OFFSCRPT and ONSCRPT

arcPtrEnd		equ 0D0052Fh

tempSP			equ 0D0053Fh		; 3 byte scrap

arcInfo			equ 0D00543h
savedArcInfo		equ 0D0055Bh
appBank_jump		equ 0D00584h

kbdScanCode		equ 0D00587h		; scancode returned by GetCSC
kbdLGSC			equ 0D00588h
kbdPSC			equ 0D00589h
kbdWUR			equ 0D0058Ah
kbdDebncCnt		equ 0D0058Bh
kbdKey			equ 0D0058Ch
kbdGetKy		equ 0D0058Dh
keyExtend		equ 0D0058Eh
brightness		equ 0D0058Fh
apdSubTimer		equ 0D00590h
apdTimer		equ 0D00591h
curTime			equ 0D00594h
curRow			equ 0D00595h
curCol			equ 0D00596h
curOffset		equ 0D00598h
curUnder		equ 0D00599h
curYCol			equ 0D0059Ch
curType			equ 0D0059Fh
curXRow			equ 0D005A0h
prevDData		equ 0D005A1h
lFont_record		equ 0D005A4h
sFont_record		equ 0D005C5h
tokVarPtr		equ 0D005E9h
tokLen			equ 0D005ECh

indicCounter		equ 0D005F6h

OP1			equ 0D005F8h
OP1M			equ 0D005FAh
OP2			equ 0D00603h
OP2M			equ 0D00605h
OP2EXT			equ 0D0060Ch
OP3			equ 0D0060Eh
OP3M			equ 0D00610h
OP4			equ 0D00619h
OP4M			equ 0D0061Bh
OP5			equ 0D00624h
OP5M			equ 0D00626h
OP6			equ 0D0062Fh
OP6M			equ 0D00631h
OP6EXT			equ 0D00638h

progToEdit		equ 0D0065Bh
nameBuff		equ 0D00663h

equ_edit_save		equ 0D0066Eh
iMathPtr1		equ 0D0066Fh
iMathPtr2		equ 0D00672h
iMathPtr3		equ 0D00675h
iMathPtr4		equ 0D00678h
iMathPtr5		equ 0D0067Bh
asm_data_ptr1		equ 0D0067Eh
asm_data_ptr2		equ 0D00681h

asm_ram			equ 0D00687h

textShadow		equ 0D006C0h
textShadCur		equ 0D007C4h
textShadTop		equ 0D007C7h
textShadAlph		equ 0D007C8h
textShadIns		equ 0D007C9h
cxMain			equ 0D007CAh
cxPPutAway		equ 0D007CDh
cxPutAway		equ 0D007D0h
cxReDisp		equ 0D007D3h
cxErrorEP		equ 0D007D6h
cxSizeWind		equ 0D007D9h
cxPage			equ 0D007DCh
cxCurApp		equ 0D007E0h
cxPrev			equ 0D007E2h ; 23 bytes are shadows of cxMain through cxCurApp and appFlags
cxAppReturn		equ 0D007EBh

onSP			equ 0D007FAh

promptRow		equ 0D00800h
promptCol		equ 0D00801h
promptIns		equ 0D00802h
promptShift		equ 0D00803h
promptRet		equ 0D00804h
promptValid		equ 0D00807h

varType			equ 0D00813h
varCurrent		equ 0D00814h
varClass		equ 0D0081Ch

catalogCurrent		equ 0D0081Dh ; word at this location starting with 6007h corresponds to what is highlighted in catalog
catalogCurrentBackupM	equ 0D00820h ; backup of catalogCurrent for menus
menuAppDepth		equ 0D00823h
menuCurrent		equ 0D00824h
menuCurrentSub		equ 0D00825h ; holds current submenu index
menuSelected		equ 0D00826h ; holds currently selected item in current submenu
menuNumMenus		equ 0D00827h ; holds number of submenus for this menu
menuNumItems		equ 0D00828h ; holds number of items in this submenu
appFlagsBackup		equ 0D00829h ; iy+appFlags backup for menu stuff
cursorFlagsBackup	equ 0D0082Ah ; iy+cursorFlags backup for menu stuff
curGStyleBackup		equ 0D0082Bh ; curGStyle backup for menu stuff
graphFlagsBackup	equ 0D0082Ch ; iy+graphFlags backup for menu stuff

progCurrent		equ 0D0082Dh
;D0082E	; something used to execute apps with _NewContext0
userMenuSA		equ 0D00838h

tempErrorMessage	equ 0D00842h

ioPrompt		equ 0D00879h
ioFlag			equ 0D00894h
sndRecState		equ 0D00896h
ioErrState		equ 0D00897h
ioData			equ 0D008A1h

penCol			equ 0D008D2h
penRow			equ 0D008D5h
rclQueue		equ 0D008D6h
rclQueueEnd		equ 0D008D9h
errNo			equ 0D008DFh
errSP			equ 0D008E0h
errOffset		equ 0D008E3h

entryString		equ 0D008E6h
entryResult		equ 0D008EAh

statVarsOffset		equ 0D0117Fh
asm_prgm_size		equ 0D0118Ch
bstCounter		equ 0D0118Fh
statVars		equ 0D01191h
infVars			equ 0D013A4h
infVar1			equ 0D013ADh
infVar2			equ 0D013B6h
infVar3			equ 0D013BFh
infVar4			equ 0D013C8h
infVar5			equ 0D013D1h
infVar6			equ 0D013DAh
infVar7			equ 0D013E3h
infVar8			equ 0D013ECh
infVar9			equ 0D013F5h
infVar10		equ 0D013FEh
infVar11		equ 0D01407h
infVar12		equ 0D01410h
infVar13		equ 0D01419h
infVar14		equ 0D01422h
infVar15		equ 0D0142Bh
infVar16		equ 0D01434h
infVar17		equ 0D0143Dh
infVar18		equ 0D01446h
infVar19		equ 0D0144Fh
infVar20		equ 0D01458h

curGStyle		equ 0D0146Dh
curGY			equ 0D0146Eh
curGY2			equ 0D01470h
curGX2			equ 0D01471h ; currently selected equation while graphing
freeSaveY		equ 0D01472h
freeSaveX		equ 0D01474h

XOffset			equ 0D014FAh
YOffset			equ 0D014FCh
lcdTallP		equ 0D014FDh
pixWideP		equ 0D014FEh
pixWide_m_1		equ 0D014FFh
pixWide_m_2		equ 0D01501h
lastEntryStkPtr		equ 0D01508h
lastEntryStk		equ 0D0150Bh
numLastEntries		equ 0D01D0Bh
currLastEntry		equ 0D01D0Ch

curPlotNumber		equ 0D01D45h

curInc			equ 0D01D49h

uXmin			equ 0D01D61h
uXmax			equ 0D01D6Ah
uXscl			equ 0D01D73h
uYmin			equ 0D01D7Ch
uYmax			equ 0D01D85h
uYscl			equ 0D01D8Eh
uThetMin		equ 0D01D97h
uThetMax		equ 0D01DA0h
uThetStep		equ 0D01DA9h
uTmin			equ 0D01DB2h
uTmax			equ 0D01DBBh
uTStep			equ 0D01DC4h
uPlotStart		equ 0D01DCDh
unMax			equ 0D01DD6h
uu0			equ 0D01DDFh
uv0			equ 0D01DE8h
unMin			equ 0D01DF1h
uu02			equ 0D01DFAh
uv02			equ 0D01E03h
uw0			equ 0D01E0Ch
uPlotStep		equ 0D01E15h
uXres			equ 0D01E1Eh
uw02			equ 0D01E27h
Xmin			equ 0D01E33h
Xmax			equ 0D01E3Ch
Xscl			equ 0D01E45h
Ymin			equ 0D01E4Eh
Ymax			equ 0D01E57h
Yscl			equ 0D01E60h
ThetaMin		equ 0D01E69h
ThetaMax		equ 0D01E72h
ThetaStep		equ 0D01E7Bh
TminPar			equ 0D01E84h
TmaxPar			equ 0D01E8Dh
Tstep			equ 0D01E96h
PlotStart		equ 0D01E9Fh
nMax			equ 0D01EA8h
u0			equ 0D01EB1h
v0			equ 0D01EBAh
nMin			equ 0D01EC3h
u02			equ 0D01ECCh
v02			equ 0D01ED5h
w0			equ 0D01EDEh
PlotStep		equ 0D01EE7h
XresO			equ 0D01EF0h
w02			equ 0D01EF9h
un1			equ 0D01F02h
un2			equ 0D01F0Bh
vn1			equ 0D01F14h
vn2			equ 0D01F1Dh
wn1			equ 0D01F26h
wn2			equ 0D01F2Fh
fin_N			equ 0D01F38h
fin_I			equ 0D01F41h
fin_PV			equ 0D01F4Ah
fin_PMT			equ 0D01F53h
fin_FV			equ 0D01F5Ch
fin_PY			equ 0D01F65h
fin_CY			equ 0D01F6Eh
cal_N			equ 0D01F77h
cal_I			equ 0D01F80h
cal_PV			equ 0D01F89h
cal_PMT			equ 0D01F92h
cal_FV			equ 0D01F9Bh
cal_PY			equ 0D01FA4h
DeltaX			equ 0D01FAEh
DeltaY			equ 0D01FB7h
TraceStep		equ 0D0203Dh

TblStart		equ 0D02267h
DeltaTbl		equ 0D02270h
Plot1MarkType		equ 0D0227Eh
Plot1List1		equ 0D0227Fh
Plot1List2		equ 0D02284h
Plot1FreqList		equ 0D02289h
Plot1XYOnOff		equ 0D0228Eh
Plot1Color		equ 0D0228Fh

Plot2MarkType		equ 0D02290h
Plot2List1		equ 0D02291h
Plot2List2		equ 0D02296h
Plot2FreqList		equ 0D0229Bh
Plot2XYOnOff		equ 0D022A0h
Plot2Color		equ 0D022A1h

Plot3MarkType		equ 0D022A2h
Plot3List1		equ 0D022A3h
Plot3List2		equ 0D022A8h
Plot3FreqList		equ 0D022ADh
Plot3XYOnOff		equ 0D022B2h
Plot3Color		equ 0D022B3h

ES			equ 0D022BAh

seed1			equ 0D022FCh
seed2			equ 0D02305h
basic_prog		equ 0D0230Eh
begPC			equ 0D02317h
curPC			equ 0D0231Ah
endPC			equ 0D0231Dh
numArguments		equ 0D02320h

cmdShadow		equ 0D0232Dh
cmdShadCur		equ 0D02431h
cmdShadAlph		equ 0D02433h
cmdShadIns		equ 0D02435h
cmdCursor		equ 0D02434h
editTop			equ 0D02437h
editCursor		equ 0D0243Ah
editTail		equ 0D0243Dh
editBtm			equ 0D02440h

currListHighlight	equ 0D0244Bh ; word, this is offset into list for currently-highlighted element in list editor
editSym			equ 0D0244Eh ; pointer to vat of variable being edited
editDat			equ 0D02451h ; pointer to data of variable being edited

currListPageOffset	equ 0D02457h
currList		equ 0D02458h
listName1		equ 0D02459h
listName2		equ 0D0245Eh
listName3		equ 0D02463h
listName4		equ 0D02468h
listName5		equ 0D0246Dh
listName6		equ 0D02472h
listName7		equ 0D02477h
listName8		equ 0D0247Ch
listName9		equ 0D02481h
listName10		equ 0D02486h
listName11		equ 0D0248Bh
listName12		equ 0D02490h
listName13		equ 0D02495h
listName14		equ 0D0249Ah
listName15		equ 0D0249Fh
listName16		equ 0D024A4h
listName17		equ 0D024A9h
listName18		equ 0D024AEh
listName19		equ 0D024B3h
listName20		equ 0D024B8h
currGrphStyle		equ 0D024BEh
y1LineType		equ 0D024BFh
y2LineType		equ 0D024C0h
y3LineType		equ 0D024C1h
y4LineType		equ 0D024C2h
y5LineType		equ 0D024C3h
y6LineType		equ 0D024C4h
y7LineType		equ 0D024C5h
y8LineType		equ 0D024C6h
y9LineType		equ 0D024C7h
y0LineType		equ 0D024C8h
para1LineType		equ 0D024C9h
para2LineType		equ 0D024CAh
para3LineType		equ 0D024CBh
para4LineType		equ 0D024CCh
para5LineType		equ 0D024CDh
para6LineType		equ 0D024CEh
polar1LineType		equ 0D024CFh
polar2LineType		equ 0D024D0h
polar3LineType		equ 0D024D1h
polar4LineType		equ 0D024D2h
polar5LineType		equ 0D024D3h
polar6LineType		equ 0D024D4h
secULineType		equ 0D024D5h
secVLineType		equ 0D024D6h
secWLineType		equ 0D024D7h
y1LineColor		equ 0D024D8h
y2LineColor		equ 0D024D9h
y3LineColor		equ 0D024DAh
y4LineColor		equ 0D024DBh
y5LineColor		equ 0D024DCh
y6LineColor		equ 0D024DDh
y7LineColor		equ 0D024DEh
y8LineColor		equ 0D024DFh
y9LineColor		equ 0D024E0h
y0LineColor		equ 0D024E1h
para1LineColor		equ 0D024E2h
para2LineColor		equ 0D024E3h
para3LineColor		equ 0D024E4h
para4LineColor		equ 0D024E5h
para5LineColor		equ 0D024E6h
para6LineColor		equ 0D024E7h
polar1LineColor		equ 0D024E8h
polar2LineColor		equ 0D024E9h
polar3LineColor		equ 0D024EAh
polar4LineColor		equ 0D024EBh
polar5LineColor		equ 0D024ECh
polar6LineColor		equ 0D024EDh
secULineColor		equ 0D024EEh
secVLineColor		equ 0D024EFh
secWLineColor		equ 0D024F0h

winTop			equ 0D02504h
winBtm			equ 0D02505h
winLeftEdge		equ 0D02506h
winLeft			equ 0D02507h
winAbove		equ 0D02509h
winRow			equ 0D0250Bh
winCol			equ 0D0250Dh
fmtDigits		equ 0D0250Fh
fmtString		equ 0D02510h
fmtLeft			equ 0D02561h
fmtIndex		equ 0D02564h
fmtMatSym		equ 0D02567h
fmtMatMem		equ 0D0256Ah

tSymPtr1		equ 0D0257Bh
tSymPtr2		equ 0D0257Eh
chkDelPtr3		equ 0D02581h
chkDelPtr4		equ 0D02584h

tempMem			equ 0D02587h
FPSbase			equ 0D0258Ah
FPS			equ 0D0258Dh
OPBase			equ 0D02590h
OPS			equ 0D02593h
pTempCnt		equ 0D02596h
cleanTmp		equ 0D02598h
pTemp			equ 0D0259Ah
progPtr			equ 0D0259Dh
newDataPtr		equ 0D025A0h
pagedGetPtr		equ 0D025A3h ; 3 byte scrap (unstable)
pagedPutPtr		equ 0D025A6h

appErr1			equ 0D025A9h ; use with _ErrCustom1
appErr2			equ 0D025B6h ; use with _ErrCustom2

arcPtr			equ 0D025C8h
appRawKeyHandle		equ 0D025CBh
customHeight		equ 0D025CEh
localLanguage		equ 0D025CFh
hookExecTemp		equ 0D025D2h
cursorHookPtr		equ 0D025D5h
libraryHookPtr		equ 0D025D8h
rawKeyHookPtr		equ 0D025DBh
getKeyHookPtr		equ 0D025DEh
homescreenHookPtr	equ 0D025E1h
windowHookPtr		equ 0D025E4h
graphHookPtr		equ 0D025E7h
yEqualsHookPtr		equ 0D025EAh
fontHookPtr		equ 0D025EDh
regraphHookPtr		equ 0D025F0h
graphicsHookPtr		equ 0D025F3h
traceHookPtr		equ 0D025F6h
parserHookPtr		equ 0D025F9h
appChangeHookPtr	equ 0D025FCh
catalog1HookPtr		equ 0D025FFh
helpHookPtr		equ 0D02602h
cxRedispHookPtr		equ 0D02605h
menuHookPtr		equ 0D02608h
catalog2HookPtr		equ 0D0260Bh
tokenHookPtr		equ 0D0260Eh
localizeHookPtr		equ 0D02611h
silentLinkHookPtr	equ 0D02614h
USBActivityHookPtr	equ 0D0261Ah

tempFreeArc		equ 0D02655h ; set after _ArcChk call

textBGcolor		equ 0D02688h
textFGcolor		equ 0D0268Ah

drawBGColor		equ 0D026AAh
drawFGColor		equ 0D026ACh
drawColorCode		equ 0D026AEh

keyToStrRam		equ 0D026EAh

sEditMonSp		equ 0D02706h
bpSave			equ 0D02709h

batteryStatus		equ 0D02A86h

graphBGColor		equ 0D02A98h

errorLineY		equ 0D02A1Bh
errorLineX		equ 0D02A23h

fillRectColor		equ 0D02AC0h
statusBarBGColor	equ 0D02ACCh

scrapMem		equ 0D02AD7h ; 3 byte scrap (unstable)

TempOP2ToOP6		equ 0D02B39h ; 55 bytes where OP2 to OP6 are temporary saved

gCurYLoc		equ 0D02FD6h ; current y pixel location for C functions

;safeRAM Locations
;---------------------------------------------
;appData		equ 0D00429h ; 256 bytes
;textShadow		equ 0D006C0h ; 260 bytes	; Call _ClrTxtShdw to put spaces in here
;cmdShadow		equ 0D0232Dh ; 260 bytes
pixelShadow		equ 0D031F6h ; 8400 bytes
pixelShadow2		equ 0D052C6h ; 8400 bytes
cmdPixelShadow		equ 0D07396h ; 8400 bytes
plotSScreen		equ 0D09466h ; 21945 bytes	; Set GraphDraw Flag to redraw graph if used
saveSScreen		equ 0D0EA1Fh ; 21945 bytes	; Set GraphDraw Flag to redraw graph if used
cursorImage		equ 0E30800h ; 1020 bytes

;semiSafeRAM Locations
;---------------------------------------------
usbArea			equ 0D13FD8h ; 14306 bytes used for usb, probably need to disable timer3/usb interrupts to use
usbInited		equ 0D177B7h ; zero this byte while using usbArea and to reset the usb stack when interrupts are re-enabled
heapBot			equ 0D1887Ch ; 1024 bytes used for flash ram routines, rest used rarely
ramCodeTop		equ 0D18C7Ch
heapTop			equ 0D1987Ch
stackBot		equ 0D1987Eh
stackTop		equ 0D1A87Eh

;RAM Equates Continued
;---------------------------------------------
userMem			equ 0D1A881h
symTable		equ 0D3FFFFh
vRam			equ 0D40000h
vRamEnd			equ 0D65800h

;Ports
;--------------------------------
pCpuSpeed		equ 0001h
pHardwareId		equ 0003h

;SHA256 Ports
;--------------------------------
pShaRange		equ 02000h
mpShaRange		equ 0E10000h

shaCtrl			equ 00h ; 1 byte
pShaCtrl		equ pShaRange + shaCtrl
mpShaCtrl		equ mpShaRange + shaCtrl

shaData			equ 10h ; 40h bytes
pShaData		equ pShaRange + shaData
mpShaData		equ mpShaRange + shaData

shaState		equ 60h ; 20h bytes
pShaState		equ pShaRange + shaState
mpShaState		equ mpShaRange + shaState

;USB Ports
;--------------------------------
pUsbRange		equ 03000h
mpUsbRange		equ 0E20000h

usbCapLen		equ 0000h
pUsbCapLen		equ pUsbRange + usbCapLen
mpUsbCapLen		equ mpUsbRange + usbCapLen

usbHciVer		equ 0002h
pUsbHciVer		equ pUsbRange + usbHciVer
mpUsbHciVer		equ mpUsbRange + usbHciVer

usbHcsParams		equ 0004h
pUsbHcsParams		equ pUsbRange + usbHcsParams
mpUsbHcsParams		equ mpUsbRange + usbHcsParams
bUsbNumPorts		equ 0
bmUsbNumPorts		equ 0Fh << bUsbNumPorts
bUsbPortPwrCtrl		equ 4
bmUsbPortPwrCtrl	equ 1 << bUsbPortPwrCtrl
bUsbPortRoutRules	equ 7
bmUsbPortRoutRules	equ 1 << bUsbPortRoutRules
bUsbNumPortsPerCC	equ 8
bmUsbNumPortsPerCC	equ 0Fh << bUsbNumPortsPerCC
bUsbNumCC		equ 12
bmUsbNumCC		equ 0Fh << bUsbNumCC
bUsbPortIndics		equ 16
bmUsbPortIndics		equ 1 << bUsbPortIndics
bUsbDebugPortNum	equ 20
bmUsbDebugPortNum	equ 0Fh << bUsbDebugPortNum

usbHccParams		equ 0008h
pUsbHccParams		equ pUsbRange + usbHccParams
mpUsbHccParams		equ mpUsbRange + usbHccParams
bUsb64Bit		equ 0
bmUsb64Bit		equ 1 << bUsb64Bit
bUsbProgFrameList	equ 1
bmUsbProgFrameList	equ 1 << bUsbProgFrameList
bUsbAsyncSchedParkCap	equ 2
bmUsbAsyncSchedParkCap	equ 1 << bUsbAsyncSchedParkCap
bUsbIsochSchedThresh	equ 4
bmUsbIsochSchedThresh	equ 0Fh << bUsbIsochSchedThresh
bUsbEhciExtendCap	equ 8
bmUsbEhciExtendCap	equ 0FFh << bUsbEhciExtendCap

usbHcspPortRout		equ 000Ch
pUsbHcspPortRout	equ pUsbRange + usbHcspPortRout
mpUsbHcspPortRout	equ mpUsbRange + usbHcspPortRout

usbCmd			equ 0010h
pUsbCmd			equ pUsbRange + usbCmd
mpUsbCmd		equ mpUsbRange + usbCmd
bUsbRunStop		equ 0
bmUsbRunStop		equ 1 << bUsbRunStop
bUsbHcReset		equ 1
bmUsbHcReset		equ 1 << bUsbHcReset
bUsbFrameListSize	equ 2
bmUsbFrameListSize	equ 3 << bUsbFrameListSize
bUsbPeriodicSchedEn	equ 4
bmUsbPeriodicSchedEn	equ 1 << bUsbPeriodicSchedEn
bUsbAsyncSchedEn	equ 5
bmUsbAsyncSchedEn	equ 1 << bUsbAsyncSchedEn
bUsbIntAsyncAdvDrbl	equ 6
bmUsbIntAsyncAdvDrbl	equ 1 << bUsbIntAsyncAdvDrbl
bUsbLightHcReset	equ 7
bmUsbLightHcReset	equ 1 << bUsbLightHcReset
bUsbAsyncSchedParkCnt	equ 8
bmUsbAsyncSchedParkCnt	equ 3 << bUsbAsyncSchedParkCnt
bUsbAsyncSchedParkEn	equ 11
bmUsbAsyncSchedParkEn	equ 1 << bUsbAsyncSchedParkEn
bUsbIntThreshCtrl	equ 16
bmUsbIntThreshCtrl	equ 0FFh << bUsbIntThreshCtrl

usbSts			equ 0014h
pUsbSts			equ pUsbRange + usbSts
mpUsbSts		equ mpUsbRange + usbSts
usbIntEn		equ 0018h
pUsbIntEn		equ pUsbRange + usbIntEn
mpUsbIntEn		equ mpUsbRange + usbIntEn
bUsbInt			equ 0
bmUsbInt		equ 1 << bUsbInt
bUsbIntErr		equ 1
bmUsbIntErr		equ 1 << bUsbIntErr
bUsbIntPortChgDetect	equ 2
bmUsbIntPortChgDetect	equ 1 << bUsbIntPortChgDetect
bUsbIntFrameListOver	equ 3
bmUsbIntFrameListOver	equ 1 << bUsbIntFrameListOver
bUsbIntHostSysErr	equ 4
bmUsbIntHostSysErr	equ 1 << bUsbIntHostSysErr
bUsbIntAsyncAdv		equ 5
bmUsbIntAsyncAdv	equ 1 << bUsbIntAsyncAdv
bUsbHcHalted		equ 12
bmUsbHcHalted		equ 1 << bUsbHcHalted
bUsbReclamation		equ 13
bmUsbReclamation	equ 1 << bUsbReclamation
bUsbPeriodicSchedSts	equ 14
bmUsbPeriodicSchedSts	equ 1 << bUsbPeriodicSchedSts
bUsbAsyncSchedSts	equ 15
bmUsbAsyncSchedSts	equ 1 << bUsbAsyncSchedSts

usbFrameIdx		equ 001Ch
pUsbFrameIdx		equ pUsbRange + usbFrameIdx
mpUsbFrameIdx		equ mpUsbRange + usbFrameIdx
bUsbFrameIdx		equ 0
bmUsbFrameIdx		equ 03FFFh << bUsbFrameIdx

usbCtrlDsSeg		equ 0020h
pUsbCtrlDsSeg		equ pUsbRange + usbCtrlDsSeg
mpUsbCtrlDsSeg		equ mpUsbRange + usbCtrlDsSeg

usbPeriodicListBase	equ 0024h
pUsbPeriodicListBase	equ pUsbRange + usbPeriodicListBase
mpUsbPeriodicListBase	equ mpUsbRange + usbPeriodicListBase
bUsbPeriodicListBase	equ 12
bmUsbPeriodicListBase	equ 0FFFFFh << bUsbPeriodicListBase

usbAsyncListAddr	equ 0028h
pUsbAsyncListAddr	equ pUsbRange + usbAsyncListAddr
mpUsbAsyncListAddr	equ mpUsbRange + usbAsyncListAddr
bUsbAsyncListAddr	equ 5
bmUsbAsyncListAddr	equ 07FFFFFFh << bUsbAsyncListAddr

usbPortStsCtrl		equ 0030h
pUsbPortStsCtrl		equ pUsbRange + usbPortStsCtrl
mpUsbPortStsCtrl	equ mpUsbRange + usbPortStsCtrl
bUsbCurConnSts		equ 0
bmUsbCurConnSts		equ 1 << bUsbCurConnSts
bUsbConnStsChg		equ 1
bmUsbConnStsChg		equ 1 << bUsbConnStsChg
bUsbPortEn		equ 2
bmUsbPortEn		equ 1 << bUsbPortEn
bUsbPortEnChg		equ 3
bmUsbPortEnChg		equ 1 << bUsbPortEnChg
bUsbOvercurrActive	equ 4
bmUsbOvercurrActive	equ 1 << bUsbOvercurrActive
bUsbOvercurrChg		equ 5
bmUsbOvercurrChg	equ 1 << bUsbOvercurrChg
bUsbForcePortResume	equ 6
bmUsbForcePortResume	equ 1 << bUsbForcePortResume
bUsbPortSuspended	equ 7
bmUsbPortSuspended	equ 1 << bUsbPortSuspended
bUsbPortReset		equ 8
bmUsbPortReset		equ 1 << bUsbPortReset
bUsbLineSts		equ 10
bmUsbLineSts		equ 3 << bUsbLineSts
bUsbPortPwr		equ 12
bmUsbPortPwr		equ 1 << bUsbPortPwr
bUsbPortOwner		equ 13
bmUsbPortOwner		equ 1 << bUsbPortOwner
bUsbPortIndicCtrl	equ 14
bmUsbPortIndicCtrl	equ 3 << bUsbPortIndicCtrl
bUsbPortTestCtrl	equ 16
bmUsbPortTestCtrl	equ 0Fh << bUsbPortTestCtrl
bUsbWakeConnEn		equ 20
bmUsbWakeConnEn		equ 1 << bUsbWakeConnEn
bUsbWakeDiscEn		equ 21
bmUsbWakeDiscEn		equ 1 << bUsbWakeDiscEn
bUsbWakeOvercurrEn	equ 22
bmUsbWakeOvercurrEn	equ 1 << bUsbWakeOvercurrEn

usbMisc			equ 0040h
pUsbMisc		equ pUsbRange + usbMisc
mpUsbMisc		equ mpUsbRange + usbMisc
bUsbAsyncSchedSleepTmr	equ 0
bmUsbAsyncSchedSleepTmr	equ 3 << bUsbAsyncSchedSleepTmr
bUsbEof1Timing		equ 2
bmUsbEof1Timing		equ 3 << bUsbEof1Timing
bUsbEof2Timing		equ 4
bmUsbEof2Timing		equ 3 << bUsbEof2Timing
bUsbHostSuspend		equ 6
bmUsbHostSuspend	equ 1 << bUsbHostSuspend

usbOtgCsr		equ 0080h
pUsbOtgCsr		equ pUsbRange + usbOtgCsr
mpUsbOtgCsr		equ mpUsbRange + usbOtgCsr
bUsbBBusReq		equ 0
bmUsbBBusReq		equ 1 << bUsbBBusReq
bUsbBHnp		equ 1
bmUsbBHnp		equ 1 << bUsbBHnp
bUsbBVbusDisc		equ 2
bmUsbBVbusDisc		equ 1 << bUsbBVbusDisc
bUsbABusReq		equ 4
bmUsbABusReq		equ 1 << bUsbABusReq
bUsbABusDrop		equ 5
bmUsbABusDrop		equ 1 << bUsbABusDrop
bUsbAHnp		equ 6
bmUsbAHnp		equ 1 << bUsbAHnp
bUsbASrpEn		equ 7
bmUsbASrpEn		equ 1 << bUsbASrpEn
bUsbASrpMode		equ 8
usbASrpModeVbus		equ 0 << bUsbASrpMode
usbASrpModeData		equ 1 << bUsbASrpMode
bmUsbASrpMode		equ 1 << bUsbASrpMode
bUsbIdFilt		equ 9
usbIdFiltShort		equ 0 << bUsbIdFilt
usbIdFiltLong		equ 1 << bUsbIdFilt
bmUsbIdFilt		equ 1 << bUsbIdFilt
bUsbVbusFilt		equ 10
usbVbusFiltShort	equ 0 << bUsbVbusFilt
usbVbusFiltLong		equ 1 << bUsbVbusFilt
bmUsbVbusFilt		equ 1 << bUsbVbusFilt
bUsbHdiscFilt		equ 11
usbHdiscFiltShort	equ 0 << bUsbHdiscFilt
usbHdiscFiltLong	equ 1 << bUsbHdiscFilt
bmUsbHdiscFilt		equ 1 << bUsbHdiscFilt
bUsbBSessEnd		equ 16
bmUsbBSessEnd		equ 1 << bUsbBSessEnd
bUsbBSessVld		equ 17
bmUsbBSessVld		equ 1 << bUsbBSessVld
bUsbASessVld		equ 18
bmUsbASessVld		equ 1 << bUsbASessVld
bUsbAVbusVld		equ 19
bmUsbAVbusVld		equ 1 << bUsbAVbusVld
bUsbRole		equ 20
usbRoleHost		equ 0 << bUsbRole
usbRoleDev		equ 1 << bUsbRole
bmUsbRole		equ 1 << bUsbRole
bUsbId			equ 21
usbIdA			equ 0 << bUsbId
usbIdB			equ 1 << bUsbId
bmUsbId			equ 1 << bUsbId
bUsbSpd			equ 22
usbSpdFull		equ 0 << bUsbSpd
usbSpdLow		equ 1 << bUsbSpd
usbSpdHigh		equ 2 << bUsbSpd
bmUsbSpd		equ 3 << bUsbSpd

usbOtgIsr		equ 0084h
pUsbOtgIsr		equ pUsbRange + usbOtgIsr
mpUsbOtgIsr		equ mpUsbRange + usbOtgIsr
usbOtgIer		equ 0088h
pUsbOtgIer		equ pUsbRange + usbOtgIer
mpUsbOtgIer		equ mpUsbRange + usbOtgIer
bUsbIntBSrpComplete	equ 0
bmUsbIntBSrpComplete	equ 1 << bUsbIntBSrpComplete
bUsbIntASrpDetect	equ 4
bmUsbIntASrpDetect	equ 1 << bUsbIntASrpDetect
bUsbIntAVbusErr		equ 5
bmUsbIntAVbusErr	equ 1 << bUsbIntAVbusErr
bUsbIntBSessEnd		equ 6
bmUsbIntBSessEnd	equ 1 << bUsbIntBSessEnd
bUsbIntRoleChg		equ 8
bmUsbIntRoleChg		equ 1 << bUsbIntRoleChg
bUsbIntIdChg		equ 9
bmUsbIntIdChg		equ 1 << bUsbIntIdChg
bUsbIntOvercurr		equ 10
bmUsbIntOvercurr	equ 1 << bUsbIntOvercurr
bUsbIntBPlugRemoved	equ 11
bmUsbIntBPlugRemoved	equ 1 << bUsbIntBPlugRemoved
bUsbIntAPlugRemoved	equ 12
bmUsbIntAPlugRemoved	equ 1 << bUsbIntAPlugRemoved

usbIsr			equ 00C0h
pUsbIsr			equ pUsbRange + usbIsr
mpUsbIsr		equ mpUsbRange + usbIsr
usbImr			equ 00C4h
pUsbImr			equ pUsbRange + usbImr
mpUsbImr		equ mpUsbRange + usbImr
bUsbIntDev		equ 0
bmUsbIntDev		equ 1 << bUsbIntDev
bUsbIntOtg		equ 1
bmUsbIntOtg		equ 1 << bUsbIntOtg
bUsbIntHost		equ 2
bmUsbIntHost		equ 1 << bUsbIntHost
bUsbIntLevel		equ 3
usbIntLevelLow		equ 0 << bUsbIntLevel
usbIntLevelHigh		equ 1 << bUsbIntLevel
bmUsbIntLevel		equ 1 << bUsbIntLevel

usbDevCtrl		equ 0100h
pUsbDevCtrl		equ pUsbRange + usbDevCtrl
mpUsbDevCtrl		equ mpUsbRange + usbDevCtrl
bUsbRemoteWake		equ 0
bmUsbRemoteWake		equ 1 << bUsbRemoteWake
bUsbHalfSpd		equ 1
bmUsbHalfSpd		equ 1 << bUsbHalfSpd
bUsbGirqEn		equ 2
bmUsbGirqEn		equ 1 << bUsbGirqEn
bUsbDevSuspend		equ 3
bmUsbDevSuspend		equ 1 << bUsbDevSuspend
bUsbDevReset		equ 4
bmUsbDevReset		equ 1 << bUsbDevReset
bUsbDevEn		equ 5
bmUsbDevEn		equ 1 << bUsbDevEn
bUsbDevSpd		equ 6
bmUsbDevSpd		equ 1 << bUsbDevSpd
bUsbDevForceFullSpd	equ 9
bmUsbDevForceFullSpd	equ 1 << bUsbDevForceFullSpd

usbDevAddr		equ 0104h
pUsbDevAddr		equ pUsbRange + usbDevAddr
mpUsbDevAddr		equ mpUsbRange + usbDevAddr
bUsbDevAddr		equ 0
bmUsbDevAddr		equ 07Fh << bUsbDevAddr
bUsbDevConf		equ 7
bmUsbDevConf		equ 1 << bUsbDevConf

usbDevTest		equ 0108h
pUsbDevTest		equ pUsbRange + usbDevTest
mpUsbDevTest		equ mpUsbRange + usbDevTest
bUsbTstClrFifo		equ 0
bmUsbTstClrFifo		equ 1 << bUsbTstClrFifo
bUsbTstCxLp		equ 1
bmUsbTstCxLp		equ 1 << bUsbTstCxLp
bUsbTstClrEa		equ 2
bmUsbTstClrEa		equ 1 << bUsbTstClrEa
bUsbTstNoCrc		equ 3
bmUsbTstNoCrc		equ 1 << bUsbTstNoCrc
bUsbTstNoTs		equ 4
bmUsbTstNoTs		equ 1 << bUsbTstNoTs
bUsbTstMode		equ 5
bmUsbTstMode		equ 1 << bUsbTstMode
bUsbNoSof		equ 6
bmUsbNoSof		equ 1 << bUsbNoSof

usbSofFrNum		equ 010Ch
pUsbSofFrNum		equ pUsbRange + usbSofFrNum
mpUsbSofFrNum		equ mpUsbRange + usbSofFrNum
bUsbSofFrNum		equ 0
bmUsbSofFrNum		equ 07FFh << bUsbSofFrNum
bUsbSofUFrNum		equ 11
bmUsbSofUFrNum		equ 7 << bUsbSofUFrNum

usbSofMtr		equ 0110h
pUsbSofMtr		equ pUsbRange + usbSofMtr
mpUsbSofMtr		equ mpUsbRange + usbSofMtr
bUsbSofMtrTmr		equ 0
bmUsbSofMtrTmr		equ 0FFFFh << bUsbSofMtrTmr

usbPhyTmsr		equ 0114h
pUsbPhyTmsr		equ pUsbRange + usbPhyTmsr
mpUsbPhyTmsr		equ mpUsbRange + usbPhyTmsr
bUsbUnplug		equ 0
bmUsbUnplug		equ 1 << bUsbUnplug
bUsbTstJState		equ 1
bmUsbTstJState		equ 1 << bUsbTstJState
bUsbTstKState		equ 2
bmUsbTstKState		equ 1 << bUsbTstKState
bUsbTstSe0Nak		equ 3
bmUsbTstSe0Nak		equ 1 << bUsbTstSe0Nak
bUsbTstPkt		equ 4
bmUsbTstPkt		equ 1 << bUsbTstPkt

usbCxsr			equ 011Ch
pUsbCxsr		equ pUsbRange + usbCxsr
mpUsbCxsr		equ mpUsbRange + usbCxsr

usbCxFifo		equ 0120h
pUsbCxFifo		equ pUsbRange + usbCxFifo
mpUsbCxFifo		equ mpUsbRange + usbCxFifo
bCxFifoFin		equ 0
bmCxFifoFin		equ 1 << bCxFifoFin
bTstPktFin		equ 1
bmTstPktFin		equ 1 << bTstPktFin
bCxFifoStall		equ 2
bmCxFifoStall		equ 1 << bCxFifoStall
bCxFifoClr		equ 3
bmCxFifoClr		equ 1 << bCxFifoClr
bCxFifoFull		equ 4
bmCxFifoFull		equ 1 << bCxFifoFull
bCxFifoEmpty		equ 5
bmCxFifoEmpty		equ 1 << bCxFifoEmpty
bFifo0Empty		equ 8
bmFifo0Empty		equ 1 << bFifo0Empty
bFifo1Empty		equ 9
bmFifo1Empty		equ 1 << bFifo1Empty
bFifo2Empty		equ 10
bmFifo2Empty		equ 1 << bFifo2Empty
bFifo3Empty		equ 11
bmFifo3Empty		equ 1 << bFifo3Empty
bFifoEmpty		equ 8
bmFifoEmpty		equ 0Fh << bFifoEmpty

usbIdle			equ 0124h
pUsbIdle		equ pUsbRange + usbIdle
mpUsbIdle		equ mpUsbRange + usbIdle
bUsbIdleMs		equ 0
bmUsbIdleMs		equ 7 << bUsbIdleMs

usbGimr			equ 0130h
pUsbGimr		equ pUsbRange + usbGimr
mpUsbGimr		equ mpUsbRange + usbGimr
usbGisr			equ 0140h
pUsbGisr		equ pUsbRange + usbGisr
mpUsbGisr		equ mpUsbRange + usbGisr
bUsbDevIntCx		equ 0
bmUsbDevIntCx		equ 1 << bUsbDevIntCx
bUsbDevIntFifo		equ 1
bmUsbDevIntFifo		equ 1 << bUsbDevIntFifo
bUsbDevIntDev		equ 2
bmUsbDevIntDev		equ 1 << bUsbDevIntDev

usbCxImr		equ 0134h
pUsbCxImr		equ pUsbRange + usbCxImr
mpUsbCxImr		equ mpUsbRange + usbCxImr
usbCxIsr		equ 0144h
pUsbCxIsr		equ pUsbRange + usbCxIsr
mpUsbCxIsr		equ mpUsbRange + usbCxIsr
bUsbIntCxSetup		equ 0
bmUsbIntCxSetup		equ 1 << bUsbIntCxSetup
bUsbIntCxIn		equ 1
bmUsbIntCxIn		equ 1 << bUsbIntCxIn
bUsbIntCxOut		equ 2
bmUsbIntCxOut		equ 1 << bUsbIntCxOut
bUsbIntCxEnd		equ 3
bmUsbIntCxEnd		equ 1 << bUsbIntCxEnd
bUsbIntCxErr		equ 4
bmUsbIntCxErr		equ 1 << bUsbIntCxErr
bUsbIntCxAbort		equ 5
bmUsbIntCxAbort		equ 1 << bUsbIntCxAbort
bUsbIntCx		equ 0
bmUsbIntCx		equ 01Fh << bUsbIntCx

usbFifoRxImr		equ 0138h
pUsbFifoRxImr		equ pUsbRange + usbFifoRxImr
mpUsbFifoRxImr		equ mpUsbRange + usbFifoRxImr
usbFifoRxIsr		equ 0148h
pUsbFifoRxIsr		equ pUsbRange + usbFifoRxIsr
mpUsbFifoRxIsr		equ mpUsbRange + usbFifoRxIsr
bUsbIntFifo0Out		equ 0
bmUsbIntFifo0Out	equ 1 << bUsbIntFifo0Out
bUsbIntFifo0Spk		equ 1
bmUsbIntFifo0Spk	equ 1 << bUsbIntFifo0Spk
bUsbIntFifo1Out		equ 2
bmUsbIntFifo1Out	equ 1 << bUsbIntFifo1Out
bUsbIntFifo1Spk		equ 3
bmUsbIntFifo1Spk	equ 1 << bUsbIntFifo1Spk
bUsbIntFifo2Out		equ 4
bmUsbIntFifo2Out	equ 1 << bUsbIntFifo2Out
bUsbIntFifo2Spk		equ 5
bmUsbIntFifo2Spk	equ 1 << bUsbIntFifo2Spk
bUsbIntFifo3Out		equ 6
bmUsbIntFifo3Out	equ 1 << bUsbIntFifo3Out
bUsbIntFifo3Spk		equ 7
bmUsbIntFifo3Spk	equ 1 << bUsbIntFifo3Spk
bUsbFifoRxInts		equ 0
bmUsbFifoRxInts		equ 0FFh << bUsbFifoRxInts

usbFifoTxImr		equ 013Ah
pUsbFifoTxImr		equ pUsbRange + usbFifoTxImr
mpUsbFifoTxImr		equ mpUsbRange + usbFifoTxImr
usbFifoTxIsr		equ 014Ah
pUsbFifoTxIsr		equ pUsbRange + usbFifoTxIsr
mpUsbFifoTxIsr		equ mpUsbRange + usbFifoTxIsr
bUsbIntFifo0In		equ 0
bmUsbIntFifo0In		equ 1 << bUsbIntFifo0In
bUsbIntFifo1In		equ 1
bmUsbIntFifo1In		equ 1 << bUsbIntFifo1In
bUsbIntFifo2In		equ 2
bmUsbIntFifo2In		equ 1 << bUsbIntFifo2In
bUsbIntFifo3In		equ 3
bmUsbIntFifo3In		equ 1 << bUsbIntFifo3In
bUsbFifoTxInts		equ 0
bmUsbFifoTxInts		equ 0Fh << bUsbFifoTxInts

usbDevImr		equ 013Ch
pUsbDevImr		equ pUsbRange + usbDevImr
mpUsbDevImr		equ mpUsbRange + usbDevImr
usbDevIsr		equ 014Ch
pUsbDevIsr		equ pUsbRange + usbDevIsr
mpUsbDevIsr		equ mpUsbRange + usbDevIsr
bUsbIntDevReset		equ 0
bmUsbIntDevReset	equ 1 << bUsbIntDevReset
bUsbIntDevSuspend	equ 1
bmUsbIntDevSuspend	equ 1 << bUsbIntDevSuspend
bUsbIntDevResume	equ 2
bmUsbIntDevResume	equ 1 << bUsbIntDevResume
bUsbIntDevIsocErr	equ 3
bmUsbIntDevIsocErr	equ 1 << bUsbIntDevIsocErr
bUsbIntDevIsocAbt	equ 4
bmUsbIntDevIsocAbt	equ 1 << bUsbIntDevIsocAbt
bUsbIntDevZlpTx		equ 5
bmUsbIntDevZlpTx	equ 1 << bUsbIntDevZlpTx
bUsbIntDevZlpRx		equ 6
bmUsbIntDevZlpRx	equ 1 << bUsbIntDevZlpRx
bUsbIntDevDmaFin	equ 7
bmUsbIntDevDmaFin	equ 1 << bUsbIntDevDmaFin
bUsbIntDevDmaErr	equ 8
bmUsbIntDevDmaErr	equ 1 << bUsbIntDevDmaErr
bUsbIntDevIdle		equ 9
bmUsbIntDevIdle		equ 1 << bUsbIntDevIdle
bUsbIntDevWakeup	equ 10
bmUsbIntDevWakeup	equ 1 << bUsbIntDevWakeup
bUsbDevInts		equ 0
bmUsbDevInts		equ 07FFh << bUsbDevInts

usbRxZlp		equ 0150h
pUsbRxZlp		equ pUsbRange + usbRxZlp
mpUsbRxZlp		equ mpUsbRange + usbRxZlp
usbTxZlp		equ 0154h
pUsbTxZlp		equ pUsbRange + usbTxZlp
mpUsbTxZlp		equ mpUsbRange + usbTxZlp
bUsbEp1Zlp		equ 0
bmUsbEp1Zlp		equ 1 << bUsbEp1Zlp
bUsbEp2Zlp		equ 1
bmUsbEp2Zlp		equ 1 << bUsbEp2Zlp
bUsbEp3Zlp		equ 2
bmUsbEp3Zlp		equ 1 << bUsbEp3Zlp
bUsbEp4Zlp		equ 3
bmUsbEp4Zlp		equ 1 << bUsbEp4Zlp
bUsbEp5Zlp		equ 4
bmUsbEp5Zlp		equ 1 << bUsbEp5Zlp
bUsbEp6Zlp		equ 5
bmUsbEp6Zlp		equ 1 << bUsbEp6Zlp
bUsbEp7Zlp		equ 6
bmUsbEp7Zlp		equ 1 << bUsbEp7Zlp
bUsbEp8Zlp		equ 7
bmUsbEp8Zlp		equ 1 << bUsbEp8Zlp
bUsbZlp			equ 0
bmUsbZlp		equ 0FFh << bUsbZlp

usbIsoEasr		equ 0158h
pUsbIsoEasr		equ pUsbRange + usbIsoEasr
mpUsbIsoEasr		equ mpUsbRange + usbIsoEasr
bUsbEp1IsocAbort	equ 0
bmUsbEp1IsocAbort	equ 1 << bUsbEp1IsocAbort
bUsbEp2IsocAbort	equ 1
bmUsbEp2IsocAbort	equ 1 << bUsbEp2IsocAbort
bUsbEp3IsocAbort	equ 2
bmUsbEp3IsocAbort	equ 1 << bUsbEp3IsocAbort
bUsbEp4IsocAbort	equ 3
bmUsbEp4IsocAbort	equ 1 << bUsbEp4IsocAbort
bUsbEp5IsocAbort	equ 4
bmUsbEp5IsocAbort	equ 1 << bUsbEp5IsocAbort
bUsbEp6IsocAbort	equ 5
bmUsbEp6IsocAbort	equ 1 << bUsbEp6IsocAbort
bUsbEp7IsocAbort	equ 6
bmUsbEp7IsocAbort	equ 1 << bUsbEp7IsocAbort
bUsbEp8IsocAbort	equ 7
bmUsbEp8IsocAbort	equ 1 << bUsbEp8IsocAbort
bUsbEp1IsocErr		equ 16
bmUsbEp1IsocErr		equ 1 << bUsbEp1IsocErr
bUsbEp2IsocErr		equ 17
bmUsbEp2IsocErr		equ 1 << bUsbEp2IsocErr
bUsbEp3IsocErr		equ 18
bmUsbEp3IsocErr		equ 1 << bUsbEp3IsocErr
bUsbEp4IsocErr		equ 19
bmUsbEp4IsocErr		equ 1 << bUsbEp4IsocErr
bUsbEp5IsocErr		equ 20
bmUsbEp5IsocErr		equ 1 << bUsbEp5IsocErr
bUsbEp6IsocErr		equ 21
bmUsbEp6IsocErr		equ 1 << bUsbEp6IsocErr
bUsbEp7IsocErr		equ 22
bmUsbEp7IsocErr		equ 1 << bUsbEp7IsocErr
bUsbEp8IsocErr		equ 23
bmUsbEp8IsocErr		equ 1 << bUsbEp8IsocErr

usbInEp1		equ 0160h
pUsbInEp1		equ pUsbRange + usbInEp1
mpUsbInEp1		equ mpUsbRange + usbInEp1
usbInEp2		equ 0164h
pUsbInEp2		equ pUsbRange + usbInEp2
mpUsbInEp2		equ mpUsbRange + usbInEp2
usbInEp3		equ 0168h
pUsbInEp3		equ pUsbRange + usbInEp3
mpUsbInEp3		equ mpUsbRange + usbInEp3
usbInEp4		equ 016Ch
pUsbInEp4		equ pUsbRange + usbInEp4
mpUsbInEp4		equ mpUsbRange + usbInEp4
usbInEp5		equ 0170h
pUsbInEp5		equ pUsbRange + usbInEp5
mpUsbInEp5		equ mpUsbRange + usbInEp5
usbInEp6		equ 0174h
pUsbInEp6		equ pUsbRange + usbInEp6
mpUsbInEp6		equ mpUsbRange + usbInEp6
usbInEp7		equ 0178h
pUsbInEp7		equ pUsbRange + usbInEp7
mpUsbInEp7		equ mpUsbRange + usbInEp7
usbInEp8		equ 017Ch
pUsbInEp8		equ pUsbRange + usbInEp8
mpUsbInEp8		equ mpUsbRange + usbInEp8
usbOutEp1		equ 0180h
pUsbOutEp1		equ pUsbRange + usbOutEp1
mpUsbOutEp1		equ mpUsbRange + usbOutEp1
usbOutEp2		equ 0184h
pUsbOutEp2		equ pUsbRange + usbOutEp2
mpUsbOutEp2		equ mpUsbRange + usbOutEp2
usbOutEp3		equ 0188h
pUsbOutEp3		equ pUsbRange + usbOutEp3
mpUsbOutEp3		equ mpUsbRange + usbOutEp3
usbOutEp4		equ 018Ch
pUsbOutEp4		equ pUsbRange + usbOutEp4
mpUsbOutEp4		equ mpUsbRange + usbOutEp4
usbOutEp5		equ 0190h
pUsbOutEp5		equ pUsbRange + usbOutEp5
mpUsbOutEp5		equ mpUsbRange + usbOutEp5
usbOutEp6		equ 0194h
pUsbOutEp6		equ pUsbRange + usbOutEp6
mpUsbOutEp6		equ mpUsbRange + usbOutEp6
usbOutEp7		equ 0198h
pUsbOutEp7		equ pUsbRange + usbOutEp7
mpUsbOutEp7		equ mpUsbRange + usbOutEp7
usbOutEp8		equ 019Ch
pUsbOutEp8		equ pUsbRange + usbOutEp8
mpUsbOutEp8		equ mpUsbRange + usbOutEp8
bUsbEpMaxPktSz		equ 0
bmUsbEpMaxPktSz		equ 07FFh << bUsbEpMaxPktSz
bUsbEpStall		equ 11
bmUsbEpStall		equ 1 << bUsbEpStall
bUsbEpReset		equ 12
bmUsbEpReset		equ 1 << bUsbEpReset
bUsbInEpTxNum		equ 13
bmUsbInEpTxNum		equ 3 << bUsbInEpTxNum
bUsbInEpSendZlp		equ 15
bmUsbInEpSendZlp	equ 1 << bUsbInEpSendZlp

usbEp1Map		equ 01A0h
pUsbEp1Map		equ pUsbRange + usbEp1Map
mpUsbEp1Map		equ mpUsbRange + usbEp1Map
usbEp2Map		equ 01A1h
pUsbEp2Map		equ pUsbRange + usbEp2Map
mpUsbEp2Map		equ mpUsbRange + usbEp2Map
usbEp3Map		equ 01A2h
pUsbEp3Map		equ pUsbRange + usbEp3Map
mpUsbEp3Map		equ mpUsbRange + usbEp3Map
usbEp4Map		equ 01A3h
pUsbEp4Map		equ pUsbRange + usbEp4Map
mpUsbEp4Map		equ mpUsbRange + usbEp4Map
usbEp5Map		equ 01A4h
pUsbEp5Map		equ pUsbRange + usbEp5Map
mpUsbEp5Map		equ mpUsbRange + usbEp5Map
usbEp6Map		equ 01A5h
pUsbEp6Map		equ pUsbRange + usbEp6Map
mpUsbEp6Map		equ mpUsbRange + usbEp6Map
usbEp7Map		equ 01A6h
pUsbEp7Map		equ pUsbRange + usbEp7Map
mpUsbEp7Map		equ mpUsbRange + usbEp7Map
usbEp8Map		equ 01A7h
pUsbEp8Map		equ pUsbRange + usbEp8Map
mpUsbEp8Map		equ mpUsbRange + usbEp8Map
bUsbEpMapIn		equ 0
bmUsbEpMapIn		equ 0Fh << bUsbEpMapIn
bUsbEpMapOut		equ 4
bmUsbEpMapOut		equ 0Fh << bUsbEpMapOut

usbFifo0Map		equ 01A8h
pUsbFifo0Map		equ pUsbRange + usbFifo0Map
mpUsbFifo0Map		equ mpUsbRange + usbFifo0Map
usbFifo1Map		equ 01A9h
pUsbFifo1Map		equ pUsbRange + usbFifo1Map
mpUsbFifo1Map		equ mpUsbRange + usbFifo1Map
usbFifo2Map		equ 01AAh
pUsbFifo2Map		equ pUsbRange + usbFifo2Map
mpUsbFifo2Map		equ mpUsbRange + usbFifo2Map
usbFifo3Map		equ 01ABh
pUsbFifo3Map		equ pUsbRange + usbFifo3Map
mpUsbFifo3Map		equ mpUsbRange + usbFifo3Map
bUsbFifoEp		equ 0
bmUsbFifoEp		equ 0Fh << bUsbFifoEp
bUsbFifoDir		equ 4
usbFifoOut		equ 0 << bUsbFifoDir
usbFifoIn		equ 1 << bUsbFifoDir
usbFifoBi		equ 2 << bUsbFifoDir
bmUsbFifoDir		equ 3 << bUsbFifoDir

usbFifo0Cfg		equ 01ACh
pUsbFifo0Cfg		equ pUsbRange + usbFifo0Cfg
mpUsbFifo0Cfg		equ mpUsbRange + usbFifo0Cfg
usbFifo1Cfg		equ 01ADh
pUsbFifo1Cfg		equ pUsbRange + usbFifo1Cfg
mpUsbFifo1Cfg		equ mpUsbRange + usbFifo1Cfg
usbFifo2Cfg		equ 01AEh
pUsbFifo2Cfg		equ pUsbRange + usbFifo2Cfg
mpUsbFifo2Cfg		equ mpUsbRange + usbFifo2Cfg
usbFifo3Cfg		equ 01AFh
pUsbFifo3Cfg		equ pUsbRange + usbFifo3Cfg
mpUsbFifo3Cfg		equ mpUsbRange + usbFifo3Cfg
bUsbFifoType		equ 0
usbFifoIsoc		equ 1 << bUsbFifoType
usbFifoBulk		equ 2 << bUsbFifoType
usbFifoIntr		equ 3 << bUsbFifoType
bmUsbFifoType		equ 3 << bUsbFifoType
bUsbFifoNumBlks		equ 2
usbFifo1Blk		equ 0 << bUsbFifoNumBlks
usbFifo2Blks		equ 1 << bUsbFifoNumBlks
usbFifo3Blks		equ 2 << bUsbFifoNumBlks
bmUsbFifoNumBlks	equ 3 << bUsbFifoNumBlks
bUsbFifoBlkSz		equ 4
usbFifoBlkSz512		equ 0 << bUsbFifoBlkSz
usbFifoBlkSz1024	equ 1 << bUsbFifoBlkSz
bmUsbFifoBlkSz		equ 1 << bUsbFifoBlkSz
bUsbFifoEn		equ 5
bmUsbFifoEn		equ 1 << bUsbFifoEn

usbFifo0Csr		equ 01B0h
pUsbFifo0Csr		equ pUsbRange + usbFifo0Csr
mpUsbFifo0Csr		equ mpUsbRange + usbFifo0Csr
usbFifo1Csr		equ 01B4h
pUsbFifo1Csr		equ pUsbRange + usbFifo1Csr
mpUsbFifo1Csr		equ mpUsbRange + usbFifo1Csr
usbFifo2Csr		equ 01B8h
pUsbFifo2Csr		equ pUsbRange + usbFifo2Csr
mpUsbFifo2Csr		equ mpUsbRange + usbFifo2Csr
usbFifo3Csr		equ 01BCh
pUsbFifo3Csr		equ pUsbRange + usbFifo3Csr
mpUsbFifo3Csr		equ mpUsbRange + usbFifo3Csr
bUsbFifoLen		equ 0
bmUsbFifoLen		equ 07FFh << bUsbFifoLen
bUsbFifoReset		equ 12
bmUsbFifoReset		equ 1 << bUsbFifoReset

usbDmaFifo		equ 01C0h
pUsbDmaFifo		equ pUsbRange + usbDmaFifo
mpUsbDmaFifo		equ mpUsbRange + usbDmaFifo
bUsbDmaFifo0		equ 0
bmUsbDmaFifo0		equ 1 << bUsbDmaFifo0
bUsbDmaFifo1		equ 1
bmUsbDmaFifo1		equ 1 << bUsbDmaFifo1
bUsbDmaFifo2		equ 2
bmUsbDmaFifo2		equ 1 << bUsbDmaFifo2
bUsbDmaFifo3		equ 3
bmUsbDmaFifo3		equ 1 << bUsbDmaFifo3
bUsbDmaCxFifo		equ 4
bmUsbDmaCxFifo		equ 1 << bUsbDmaCxFifo
bUsbDmaFifo		equ 0
bmUsbDmaNoFifo		equ 0 << bUsbDmaFifo
bmUsbDmaFifo		equ 01Fh << bUsbDmaFifo

usbDmaCtrl		equ 01C8h
pUsbDmaCtrl		equ pUsbRange + usbDmaCtrl
mpUsbDmaCtrl		equ mpUsbRange + usbDmaCtrl
bUsbDmaStart		equ 0
bmUsbDmaStart		equ 1 << bUsbDmaStart
bUsbDmaDir		equ 1
usbDmaFifo2Mem		equ 0 << bUsbDmaDir
usbDmaMem2Fifo		equ 1 << bUsbDmaDir
usbDmaFifo2Fifo		equ 2 << bUsbDmaDir
bmUsbDmaDir		equ 3 << bUsbDmaDir
bUsbDmaAbort		equ 3
bmUsbDmaAbort		equ 1 << bUsbDmaAbort
bUsbDmaClrFifo		equ 4
bmUsbDmaClrFifo		equ 1 << bUsbDmaClrFifo

usbDmaLen		equ 01C9h
pUsbDmaLen		equ pUsbRange + usbDmaLen
mpUsbDmaLen		equ mpUsbRange + usbDmaLen
bUsbDmaLen		equ 0
bmUsbDmaLen		equ 01FFFFh << bUsbDmaLen

usbDmaAddr		equ 01CCh
pUsbDmaAddr		equ pUsbRange + usbDmaAddr
mpUsbDmaAddr		equ mpUsbRange + usbDmaAddr
bUsbDmaAddr		equ 0
bmUsbDmaAddr		equ 07FFFFh << bUsbDmaAddr

usbEp0Data		equ 01D0h
pUsbEp0Data		equ pUsbRange + usbEp0Data
mpUsbEp0Data		equ mpUsbRange + usbEp0Data
bUsbEp0Data		equ 0
bmUsbEp0Data		equ 0FFFFFFFFh << bUsbEp0Data

;LCD Ports
;--------------------------------
pLcdRange		equ 04000h
mpLcdRange		equ 0E30000h

lcdTiming0		equ 0000h
pLcdTiming0		equ pLcdRange + lcdTiming0
mpLcdTiming0		equ mpLcdRange + lcdTiming0
lcdTiming1		equ 0004h
pLcdTiming1		equ pLcdRange + lcdTiming1
mpLcdTiming1		equ mpLcdRange + lcdTiming1
lcdTiming2		equ 0008h
pLcdTiming2		equ pLcdRange + lcdTiming2
mpLcdTiming2		equ mpLcdRange + lcdTiming2
lcdTiming3		equ 000Ch
pLcdTiming3		equ pLcdRange + lcdTiming3
mpLcdTiming3		equ mpLcdRange + lcdTiming3

lcdBase			equ 0010h
pLcdBase		equ pLcdRange + lcdBase
mpLcdBase		equ mpLcdRange + lcdBase
lcdUpbase		equ 0010h
pLcdUpbase		equ pLcdRange + lcdUpbase
mpLcdUpbase		equ mpLcdRange + lcdUpbase
lcdLpbase		equ 0014h
pLcdLpbase		equ pLcdRange + lcdLpbase
mpLcdLpbase		equ mpLcdRange + lcdLpbase

lcdCtrl			equ 0018h
pLcdCtrl		equ pLcdRange + lcdCtrl
mpLcdCtrl		equ mpLcdRange + lcdCtrl
lcdEn			equ 01h
lcdTft			equ 20h
lcdBpp1			equ 0000b | lcdTft | lcdEn
lcdBpp2			equ 0010b | lcdTft | lcdEn
lcdBpp4			equ 0100b | lcdTft | lcdEn
lcdBpp8			equ 0110b | lcdTft | lcdEn
lcdBpp16Alt		equ 1000b | lcdTft | lcdEn
lcdBpp24		equ 1010b | lcdTft | lcdEn
lcdBpp16		equ 1100b | lcdTft | lcdEn ; Default LCD mode
lcdBpp12		equ 1110b | lcdTft | lcdEn
lcdBgr			equ 100h
lcdBigEndian		equ 200h
lcdBigEndianPixels	equ 400h
lcdPwr			equ 800h
lcdIntVSync		equ 0000h
lcdIntBack		equ 1000h
lcdIntActiveVideo	equ 2000h
lcdIntFront		equ 3000h
lcdWatermark		equ 10000h
lcdNormalMode		equ lcdPwr | lcdBgr | lcdBpp16

lcdImsc			equ 001Ch
pLcdImsc		equ pLcdRange + lcdImsc
mpLcdImsc		equ mpLcdRange + lcdImsc
lcdRis			equ 0020h
pLcdRis			equ pLcdRange + lcdRis
mpLcdRis		equ mpLcdRange + lcdRis
lcdMis			equ 0024h
pLcdMis			equ pLcdRange + lcdMis
mpLcdMis		equ mpLcdRange + lcdMis
lcdIcr			equ 0028h
pLcdIcr			equ pLcdRange + lcdIcr
mpLcdIcr		equ mpLcdRange + lcdIcr

bLcdIntFuf		equ 1
lcdIntFuf		equ 1 << bLcdIntFuf
bLcdIntLNBU		equ 2
lcdIntLNBU		equ 1 << bLcdIntLNBU
bLcdIntVcomp		equ 3
lcdIntVcomp		equ 1 << bLcdIntVcomp
bLcdIntMbErr		equ 4
lcdIntMbErr		equ 1 << bLcdIntMbErr

lcdCurr			equ 002Ch
pLcdCurr		equ pLcdRange + lcdCurr
mpLcdCurr		equ mpLcdRange + lcdCurr
lcdUpcurr		equ 002Ch
pLcdUpcurr		equ pLcdRange + lcdUpcurr
mpLcdUpcurr		equ mpLcdRange + lcdUpcurr
lcdLpcurr		equ 0030h
pLcdLpcurr		equ pLcdRange + lcdLpcurr
mpLcdLpcurr		equ mpLcdRange + lcdLpcurr
lcdPalette		equ 0200h
pLcdPalette		equ pLcdRange + lcdPalette
mpLcdPalette		equ mpLcdRange + lcdPalette

lcdCrsrImage		equ 0800h
pLcdCrsrImage		equ pLcdRange + lcdCrsrImage
mpLcdCrsrImage		equ mpLcdRange + lcdCrsrImage
lcdCrsrCtrl		equ 0C00h
pLcdCrsrCtrl		equ pLcdRange + lcdCrsrCtrl
mpLcdCrsrCtrl		equ mpLcdRange + lcdCrsrCtrl
lcdCrsrConfig		equ 0C04h
pLcdCrsrConfig		equ pLcdRange + lcdCrsrConfig
mpLcdCrsrConfig		equ mpLcdRange + lcdCrsrConfig
lcdCrsrPalette0		equ 0C08h
pLcdCrsrPalette0	equ pLcdRange + lcdCrsrPalette0
mpLcdCrsrPalette0	equ mpLcdRange + lcdCrsrPalette0
lcdCrsrPalette1		equ 0C0Ch
pLcdCrsrPalette1	equ pLcdRange + lcdCrsrPalette1
mpLcdCrsrPalette1	equ mpLcdRange + lcdCrsrPalette1
lcdCrsrXY		equ 0C10h
pLcdCrsrXY		equ pLcdRange + lcdCrsrXY
mpLcdCrsrXY		equ mpLcdRange + lcdCrsrXY
lcdCrsrClip		equ 0C14h
pLcdCrsrClip		equ pLcdRange + lcdCrsrClip
mpLcdCrsrClip		equ mpLcdRange + lcdCrsrClip
lcdCrsrImsc		equ 0C20h
pLcdCrsrImsc		equ pLcdRange + lcdCrsrImsc
mpLcdCrsrImsc		equ mpLcdRange + lcdCrsrImsc
lcdCrsrIcr		equ 0C24h
pLcdCrsrIcr		equ pLcdRange + lcdCrsrIcr
mpLcdCrsrIcr		equ mpLcdRange + lcdCrsrIcr
lcdCrsrRis		equ 0C28h
pLcdCrsrRis		equ pLcdRange + lcdCrsrRis
mpLcdCrsrRis		equ mpLcdRange + lcdCrsrRis
lcdCrsrMis		equ 0C2Ch
pLcdCrsrMis		equ pLcdRange + lcdCrsrMis
mpLcdCrsrMis		equ mpLcdRange + lcdCrsrMis

;Interrupt Ports
;-----------------------------------
pIntRange		equ 05000h
mpIntRange		equ 0F00000h

intStat			equ 0
pIntStat		equ pIntRange + intStat
mpIntStat		equ mpIntRange + intStat
intMask			equ 4
pIntMask		equ pIntRange + intMask
mpIntMask		equ mpIntRange + intMask
intAck			equ 8
pIntAck			equ pIntRange + intAck
mpIntAck		equ mpIntRange + intAck
intLatch		equ 12
pIntLatch		equ pIntRange + intLatch
mpIntLatch		equ mpIntRange + intLatch
intInvert		equ 16
pIntInvert		equ pIntRange + intInvert
mpIntInvert		equ mpIntRange + intInvert
intMasked		equ 20
pIntMasked		equ pIntRange + intMasked
mpIntMasked		equ mpIntRange + intMasked

bIntOn			equ 0
intOn			equ 1 << bIntOn
bIntTmr1		equ 1
intTmr1			equ 1 << bIntTmr1
bIntTmr2		equ 2
intTmr2			equ 1 << bIntTmr2
bIntTmr3		equ 3
intTmr3			equ 1 << bIntTmr3
bIntOSTmr		equ 4
intOSTmr		equ 1 << bIntOSTmr
bIntKey			equ 10
intKey			equ 1 << bIntKey
bIntLcd			equ 11
intLcd			equ 1 << bIntLcd
bIntRtc			equ 12
intRtc			equ 1 << bIntRtc
bIntUsb			equ 13
intUsb			equ 1 << bIntUsb
intDefaultMask		equ intOn | intTmr3 | intOSTmr | intRtc | intUsb

;Timer Ports
;-----------------------------------
tmrRange		equ 00h
pTmrRange		equ 7000h
mpTmrRange		equ 0F20000h

tmr1Counter		equ 00h
pTmr1Counter		equ 7000h
mpTmr1Counter		equ 0F20000h
tmr1Load		equ 04h
pTmr1Load		equ 7004h
mpTmr1Load		equ 0F20004h
tmr1Match1		equ 08h
pTmr1Match1		equ 7008h
mpTmr1Match1		equ 0F20008h
tmr1Match2		equ 0Ch
pTmr1Match2		equ 700Ch
mpTmr1Match2		equ 0F2000Ch

tmr2Counter		equ 10h
pTmr2Counter		equ 7010h
mpTmr2Counter		equ 0F20010h
tmr2Load		equ 14h
pTmr2Load		equ 7014h
mpTmr2Load		equ 0F20014h
tmr2Match1		equ 18h
pTmr2Match1		equ 7018h
mpTmr2Match1		equ 0F20018h
tmr2Match2		equ 1Ch
pTmr2Match2		equ 701Ch
mpTmr2Match2		equ 0F2001Ch

tmr3Counter		equ 20h
pTmr3Counter		equ 7020h
mpTmr3Counter		equ 0F20020h
tmr3Load		equ 24h
pTmr3Load		equ 7024h
mpTmr3Load		equ 0F20024h
tmr3Match1		equ 28h
pTmr3Match1		equ 7028h
mpTmr3Match1		equ 0F20028h
tmr3Match2		equ 2Ch
pTmr3Match2		equ 702Ch
mpTmr3Match2		equ 0F2002Ch

tmrCtrl			equ 30h
pTmrCtrl		equ 7030h
mpTmrCtrl		equ 0F20030h

bTmr1Enable		equ 0
tmr1Enable		equ 1<<bTmr1Enable
bTmr1Crystal		equ 1
tmr1Crystal		equ 1<<bTmr1Crystal
bTmr1Overflow		equ 2
tmr1Overflow		equ 1<<bTmr1Overflow
bTmr2Enable		equ 3
tmr2Enable		equ 1<<bTmr2Enable
bTmr2Crystal		equ 4
tmr2Crystal		equ 1<<bTmr2Crystal
bTmr2Overflow		equ 5
tmr2Overflow		equ 1<<bTmr2Overflow
bTmr3Enable		equ 6
tmr3Enable		equ 1<<bTmr3Enable
bTmr3Crystal		equ 7
tmr3Crystal		equ 1<<bTmr3Crystal
bTmr3Overflow		equ 8
tmr3Overflow		equ 1<<bTmr3Overflow
bTmr1CountUp		equ 9
tmr1CountUp		equ 1<<bTmr1CountUp
bTmr2CountUp		equ 10
tmr2CountUp		equ 1<<bTmr2CountUp
bTmr3CountUp		equ 11
tmr3CountUp		equ 1<<bTmr3CountUp

tmrIntStatus		equ 34h
pTmrIntStatus		equ 7034h
mpTmrIntStatus		equ 0F20034h

bTmr1IntMatch1		equ 0
tmr1IntMatch1		equ 1<<bTmr1IntMatch1
bTmr1IntMatch2		equ 1
tmr1IntMatch2		equ 1<<bTmr1IntMatch2
bTmr1IntOverflow	equ 2
tmr1IntOverflow		equ 1<<bTmr1IntOverflow
bTmr2IntMatch1		equ 3
tmr2IntMatch1		equ 1<<bTmr2IntMatch1
bTmr2IntMatch2		equ 4
tmr2IntMatch2		equ 1<<bTmr2IntMatch2
bTmr2IntOverflow	equ 5
tmr2IntOverflow		equ 1<<bTmr2IntOverflow
bTmr3IntMatch1		equ 6
tmr3IntMatch1		equ 1<<bTmr3IntMatch1
bTmr3IntMatch2		equ 7
tmr3IntMatch2		equ 1<<bTmr3IntMatch2
bTmr3IntOverflow	equ 8
tmr3IntOverflow		equ 1<<bTmr3IntOverflow

tmrIntMask		equ 38h
pTmrIntMask		equ 7038h
mpTmrIntMask		equ 0F20038h

tmrRevision		equ 3Ch
pTmrRevision		equ 703Ch
mpTmrRevision		equ 0F2003Ch

;RTC Ports
;-----------------------------------
pRtcRange		equ 8000h
mpRtcRange		equ 0F30000h

;Keypad Ports
;-----------------------------------
pKeyRange		equ 0A000h
mpKeyRange		equ 0F50000h

keyMode			equ 0
pKeyMode		equ pKeyRange + keyMode
mpKeyMode		equ mpKeyRange + keyMode
keyRows			equ 4
pKeyRows		equ pKeyRange + keyRows
mpKeyRows		equ mpKeyRange + keyRows
keyCols			equ 5
pKeyCols		equ pKeyRange + keyCols
mpKeyCols		equ mpKeyRange + keyCols
keyIntStat		equ 8
pKeyIntStat		equ pKeyRange + keyIntStat
mpKeyIntStat		equ mpKeyRange + keyIntStat
keyIntAck		equ 8
pKeyIntAck		equ pKeyRange + keyIntAck
mpKeyIntAck		equ mpKeyRange + keyIntAck
keyIntMask		equ 12
pKeyIntMask		equ pKeyRange + keyIntMask
mpKeyIntMask		equ mpKeyRange + keyIntMask
keyData			equ 16
pKeyData		equ pKeyRange + keyData
mpKeyData		equ mpKeyRange + keyData
keyGpio			equ 48
pKeyGpio		equ pKeyRange + keyGpio
mpKeyGpio		equ mpKeyRange + keyGpio

bKeyIntScanDone		equ 0
keyIntScanDone		equ 1 << bKeyIntScanDone
bKeyIntKeyChange	equ 1
keyIntKeyChange		equ 1 << bKeyIntKeyChange
bKeyIntKeyPress		equ 2
keyIntKeyPress		equ 1 << bKeyIntKeyPress

keyModeIdle		equ 0
keyModeAny		equ 1
keyModeScanOnce		equ 2
keyModeScan		equ 3

;Backlight Ports
;-----------------------------------
pBlLevel		equ 0B024h
mpBlLevel		equ 0F60024h

;Character Font Equates
;-------------------------------------
LrecurN			equ 001h
LrecurU			equ 002h
LrecurV			equ 003h
LrecurW			equ 004h
Lconvert		equ 005h
LsqUp			equ 006h
LsqDown			equ 007h
Lintegral		equ 008h
Lcross			equ 009h
LboxIcon 		equ 00Ah
LcrossIcon 		equ 00Bh
LdotIcon 		equ 00Ch
LsubT   		equ 00Dh ;small capital T for parametric mode.
LcubeR  		equ 00Eh ;slightly different 3 for cubed root.
LhexF			equ 00Fh
Lroot			equ 010h
Linverse		equ 011h
Lsquare			equ 012h
Langle			equ 013h
Ldegree			equ 014h
Lradian			equ 015h
Ltranspose		equ 016h
LLE			equ 017h
LNE			equ 018h
LGE			equ 019h
Lneg			equ 01Ah
Lexponent		equ 01Bh
Lstore			equ 01Ch
Lten			equ 01Dh
LupArrow		equ 01Eh
LdownArrow		equ 01Fh
Lspace			equ 020h
Lexclam			equ 021h
Lquote			equ 022h
Lpound			equ 023h
Lfourth			equ 024h
Lpercent		equ 025h
Lampersand		equ 026h
Lapostrophe		equ 027h
LlParen			equ 028h
LrParen			equ 029h
Lasterisk		equ 02Ah
LplusSign		equ 02Bh
Lcomma			equ 02Ch
Ldash			equ 02Dh
Lperiod			equ 02Eh
Lslash			equ 02Fh
L0			equ 030h
L1			equ 031h
L2			equ 032h
L3			equ 033h
L4			equ 034h
L5			equ 035h
L6			equ 036h
L7			equ 037h
L8			equ 038h
L9			equ 039h
Lcolon			equ 03Ah
Lsemicolon		equ 03Bh
LLT			equ 03Ch
LEQ			equ 03Dh
LGT			equ 03Eh
Lquestion		equ 03Fh
LatSign			equ 040h
LcapA			equ 041h
LcapB			equ 042h
LcapC			equ 043h
LcapD			equ 044h
LcapE			equ 045h
LcapF			equ 046h
LcapG			equ 047h
LcapH			equ 048h
LcapI			equ 049h
LcapJ			equ 04Ah
LcapK			equ 04Bh
LcapL			equ 04Ch
LcapM			equ 04Dh
LcapN			equ 04Eh
LcapO			equ 04Fh
LcapP			equ 050h
LcapQ			equ 051h
LcapR			equ 052h
LcapS			equ 053h
LcapT			equ 054h
LcapU			equ 055h
LcapV			equ 056h
LcapW			equ 057h
LcapX			equ 058h
LcapY			equ 059h
LcapZ			equ 05Ah
Ltheta			equ 05Bh
Lbackslash		equ 05Ch
LrBrack			equ 05Dh
Lcaret			equ 05Eh
Lunderscore		equ 05Fh
Lbackquote		equ 060h
La			equ 061h
Lb			equ 062h
Lc			equ 063h
Ld			equ 064h
Le			equ 065h
Lf			equ 066h
Lg			equ 067h
Lh			equ 068h
Li			equ 069h
Lj			equ 06Ah
Lk			equ 06Bh
Ll			equ 06Ch
Lm			equ 06Dh
Ln			equ 06Eh
Lo			equ 06Fh
Lp			equ 070h
Lq			equ 071h
Lr			equ 072h
Ls			equ 073h
Lt			equ 074h
Lu			equ 075h
Lv			equ 076h
Lw			equ 077h
Lx			equ 078h
Ly			equ 079h
Lz			equ 07Ah
LlBrace			equ 07Bh
Lbar			equ 07Ch
LrBrace			equ 07Dh
Ltilde			equ 07Eh
LinvEQ			equ 07Fh
Lsub0			equ 080h
Lsub1			equ 081h
Lsub2			equ 082h
Lsub3			equ 083h
Lsub4			equ 084h
Lsub5			equ 085h
Lsub6			equ 086h
Lsub7			equ 087h
Lsub8			equ 088h
Lsub9			equ 089h
LcapAAcute		equ 08Ah
LcapAGrave		equ 08Bh
LcapACaret		equ 08Ch
LcapADier		equ 08Dh
LaAcute			equ 08Eh
LaGrave			equ 08Fh
LaCaret			equ 090h
LaDier			equ 091h
LcapEAcute		equ 092h
LcapEGrave		equ 093h
LcapECaret		equ 094h
LcapEDier		equ 095h
LeAcute			equ 096h
LeGrave			equ 097h
LeCaret			equ 098h
LeDier			equ 099h
LcapIAcute		equ 09Ah
LcapIGrave		equ 09Bh
LcapICaret		equ 09Ch
LcapIDier		equ 09Dh
LiAcute			equ 09Eh
LiGrave			equ 09Fh
LiCaret			equ 0A0h
LiDier			equ 0A1h
LcapOAcute		equ 0A2h
LcapOGrave		equ 0A3h
LcapOCaret		equ 0A4h
LcapODier		equ 0A5h
LoAcute			equ 0A6h
LoGrave			equ 0A7h
LoCaret			equ 0A8h
LoDier			equ 0A9h
LcapUAcute		equ 0AAh
LcapUGrave		equ 0ABh
LcapUCaret		equ 0ACh
LcapUDier		equ 0ADh
LuAcute			equ 0AEh
LuGrave			equ 0AFh
LuCaret			equ 0B0h
LuDier			equ 0B1h
LcapCCed		equ 0B2h
LcCed			equ 0B3h
LcapNTilde		equ 0B4h
LnTilde			equ 0B5h
Laccent			equ 0B6h
Lgrave			equ 0B7h
Ldieresis		equ 0B8h
LquesDown		equ 0B9h
LexclamDown		equ 0BAh
Lalpha			equ 0BBh
Lbeta			equ 0BCh
Lgamma			equ 0BDh
LcapDelta		equ 0BEh
Ldelta			equ 0BFh
Lepsilon		equ 0C0h
LlBrack 		equ 0C1h
Llambda			equ 0C2h
Lmu			equ 0C3h
Lpi			equ 0C4h
Lrho			equ 0C5h
LcapSigma		equ 0C6h
Lsigma			equ 0C7h
Ltau			equ 0C8h
Lphi			equ 0C9h
LcapOmega		equ 0CAh
LxMean			equ 0CBh
LyMean			equ 0CCh
LsupX			equ 0CDh
Lellipsis		equ 0CEh
Lleft			equ 0CFh
Lblock			equ 0D0h
Lper			equ 0D1h
Lhyphen			equ 0D2h
Larea			equ 0D3h
Ltemp			equ 0D4h
Lcube			equ 0D5h
Lenter			equ 0D6h
LimagI			equ 0D7h
Lphat			equ 0D8h
Lchi			equ 0D9h
LstatF			equ 0DAh
Llne			equ 0DBh
LlistL			equ 0DCh
LfinanN 		equ 0DDh
L2_r_paren 		equ 0DEh
LblockArrow		equ 0DFh
LcurO   		equ 0E0h
LcurO2  		equ 0E1h
LcurOcapA		equ 0E2h
LcurOa  		equ 0E3h
LcurI   		equ 0E4h
LcurI2  		equ 0E5h
LcurIcapA		equ 0E6h
LcurIa  		equ 0E7h
LGline			equ 0E8h ; = 0
LGthick			equ 0E9h ; = 1
LGabove			equ 0EAh ; = 2
LGbelow			equ 0EBh ; = 3
LGpath			equ 0ECh ; = 4
LGanimate		equ 0EDh ; = 5
LGdot			equ 0EEh ; = 6
LUpBlk			equ 0EFh ;Up arrow and Block in solver
LDnBlk			equ 0F0h ;Down arrow and Block in solver
LcurFull		equ 0F1h ;note: must be last char (PutMap checks)

;(MenuCurrent) Values
;-----------------------------------
mConfirmation		equ 01h
mApps			equ 02h
mProgramHome		equ 03h
mPrgm_Run		 equ 00h
mPrgm_Edit		 equ 01h
mPrgm_New		 equ 02h
mZoom			equ 04h
mZoom_Zoom		 equ 00h
mZoom_Memory		 equ 01h
mDraw			equ 05h
mDraw_Draw		 equ 00h
mDraw_Points		 equ 01h
mDraw_Store		 equ 02h
mDraw_Background	equ 03h
mStatPlots		equ 06h
mStat			equ 07h
mStat_Edit		 equ 00h
mStat_Calc		 equ 01h
mStat_Tests		 equ 02h
mMath			equ 08h
mMath_Math		 equ 00h
mMath_Number		 equ 01h
mMath_Complex		 equ 02h
mMath_Prob		 equ 03h
mMath_Frac		 equ 04h
mTest			equ 09h
mTest_Test		 equ 00h
mTest_Logic		 equ 01h

mVars			equ 0Bh
mVars_Vars		 equ 00h
mVars_YVars		 equ 01h
mVars_Colors	 equ 02h
mMemory			equ 0Ch
mMatrix			equ 0Dh
mMatrix_Name		 equ 00h
mMatrix_Math		 equ 01h
mMatrix_Edit		 equ 02h
mDistr			equ 0Eh
mDistr_Distr		 equ 00h
mDistr_Draw		 equ 01h
mAngle			equ 0Fh
mList			equ 10h
mList_Names		 equ 00h
mList_Ops		 equ 01h
mList_Math		 equ 02h
mCalculate		equ 11h
mVarsWin		equ 15h
mVarsWin_XY		 equ 00h
mVarsWin_TTh		 equ 01h
mVarsWin_UVW		 equ 02h
mVarsZoom		equ 16h
mVarsZoom_ZXY		 equ 00h
mVarsZoom_ZT		 equ 01h
mVarsZoom_UVW		 equ 02h
mVarsGDB		equ 17h
mVarsPics		equ 18h
mVarsPics_Pics		 equ 01h
mVarsPics_Bckgrnds		 equ 01h
mVarsStrings		equ 19h
mVarsStat		equ 1Ah
mVarsStat_XY		 equ 00h
mVarsStat_Sigma		 equ 01h
mVarsStat_EQ		 equ 02h
mVarsStat_Test		 equ 03h
mVarsStat_Pts		 equ 04h
mVarsTable		equ 1Bh
mVarsYequ 		equ 1Ch
mVarsParametric		equ 1Dh
mVarsPolar		equ 1Eh
mVarsFnOnOff		equ 1Fh
mMemReset		equ 20h
mMemReset_RAM		 equ 00h
mMemReset_ROM		 equ 01h
mMemReset_All		 equ 02h
mMemMgmtDel		equ 21h
mMemResetDefaults	equ 22h
mMemResetRAMAll		equ 24h
mMemResetROMVars	equ 25h
mMemResetROMApps	equ 26h
mMemResetROMAll		equ 27h
mMemResetAll		equ 28h
mGroup			equ 29h
mGroup_New		 equ 00h
mGroup_Ungroup		 equ 01h
mGroupVars		equ 2Ah
mProgramEdit		equ 2Bh
mPrgmEd_Ctrl		 equ 00h
mPrgmEd_IO		 equ 01h
mPrgmEd_Color		 equ 02h
mPrgmEd_Exec		 equ 03h
mPrgmZoom		equ 2Ch
mPrgmZoom_Zoom		 equ 00h
mPrgmZoom_Mem		 equ 01h
mPrgmDraw		equ 2Dh
mPrgmDraw_Draw		 equ 00h
mPrgmDraw_Pt		 equ 01h
mPrgmDraw_Store		 equ 02h
mPrgmDraw_Bckgrnd	 equ 03h
mPrgmStatPlot		equ 2Eh
mPrgmSP_Plots		 equ 00h
mPrgmSP_Type		 equ 01h
mPrgmSP_Mark		 equ 02h
mPrgmStat		equ 2Fh
mPrgmStat_Edit		 equ 00h
mPrgmStat_Calc		 equ 01h
mPrgmStat_Tests		 equ 02h
mPrgmMath		equ 30h
mPrgmMath_Math		 equ 00h
mPrgmMath_Num		 equ 01h
mPrgmMath_Cplx		 equ 02h
mPrgmMath_Prob		 equ 03h
mPrgmMath_Frac		 equ 04h
mLink			equ 31h
mLink_Send		 equ 00h
mLink_Recieve		 equ 01h
mLinkTrasmit		equ 32h
mLinkXmit_Xmit		 equ 01h
mGarbageCollect		equ 40h
mSelectGroupVars	equ 41h
mSelGrpVars_Sel		 equ 00h
mSelGrpVars_Grp		 equ 01h
mDuplicateName		equ 43h
mCatalog		equ 46h
mFinance		equ 22h
mFinance_Calc		 equ 00h
mFinance_Vars		 equ 01h

;Keypress Equates
;-----------------------------------
kRight			equ 001h
kLeft			equ 002h
kUp			equ 003h
kDown			equ 004h
kEnter			equ 005h
kAlphaEnter		equ 006h
kAlphaUp		equ 007h
kAlphaDown		equ 008h
kClear			equ 009h
kDel			equ 00Ah
kIns			equ 00Bh
kRecall			equ 00Ch
kLastEnt		equ 00Dh
kBOL			equ 00Eh
kEOL			equ 00Fh

kSelAll			equ 010h
kUnselAll		equ 011h
kLtoTI82		equ 012h
kBackup			equ 013h
kRecieve		equ 014h
kLnkQuit		equ 015h
kTrans			equ 016h
kRename			equ 017h
kOverw			equ 018h
kOmit			equ 019h
kCont			equ 01Ah
kSendID			equ 01Bh
kSendSW			equ 01Ch
kYes			equ 01Dh
kNoWay			equ 01Eh
kvSendType		equ 01Fh
kOverWAll		equ 020h
kNo			equ 025h
kKReset			equ 026h
kApp			equ 027h
kDoug			equ 028h
kListflag		equ 029h
menuStart		equ 02Bh
kAreYouSure		equ 02Bh
kAppsMenu		equ 02Ch
kPrgm			equ 02Dh
kZoom			equ 02Eh
kDraw			equ 02Fh
kSPlot			equ 030h
kStat			equ 031h
kMath			equ 032h
kTest			equ 033h
kChar			equ 034h
kVars			equ 035h
kMem			equ 036h
kMatrix			equ 037h
kDist			equ 038h
kAngle			equ 039h
kList			equ 03Ah
kCalc			equ 03Bh
kFin			equ 03Ch
menuEnd			equ kFin
kCatalog		equ 03Eh
kInputDone		equ 03Fh
kOff			equ kInputDone
kQuit			equ 040h
appStart		equ kQuit
kLinkIO			equ 041h
kMatrixEd		equ 042h
kStatEd			equ 043h
kGraph			equ 044h
kMode			equ 045h
kPrgmEd			equ 046h ;PROGRAM EDIT
kPrgmCr			equ 047h ;PROGRAM CREATE
kWindow			equ 048h ;RANGE EDITOR
kYequ 			equ 049h ;EQUATION EDITOR
kTable			equ 04Ah ;TABLE EDITOR
kTblSet			equ 04Bh ;TABLE SET
kChkRAM			equ 04Ch ;CHECK RAM (About screen)
kDelMem			equ 04Dh ;DELETE MEM
kResetMem		equ 04Eh ;RESET MEM
kResetDef		equ 04Fh ;RESET DEFAULT
kPrgmInput		equ 050h ;PROGRAM INPUT
kZFactEd		equ 051h ;ZOOM FACTOR EDITOR
kError			equ 052h ;ERROR
kSolveTVM		equ 053h ;TVM SOLVER
kSolveRoot		equ 054h ;SOLVE EDITOR
kStatP			equ 055h ;stat plot
kInfStat		equ 056h ;Inferential Statistic
kFormat			equ 057h ;FORMAT
kExtApps		equ 058h ;External Applications.		NEW
kNewApps		equ 059h ;New Apps for Cerberus.
append			equ kNewApps
echoStart1		equ 05Ah
kTrace			equ 05Ah
kZFit			equ 05Bh
kZIn			equ 05Ch
kZOut			equ 05Dh
kZPrev			equ 05Eh
kBox			equ 05Fh
kDecml			equ 060h
kSetZm			equ 061h
kSquar			equ 062h
kStd			equ 063h
kTrig			equ 064h
kUsrZm			equ 065h
kZSto			equ 066h
kZInt			equ 067h
kZStat			equ 068h
echoStart2		equ 069h
kSelect			equ 069h
kCircl			equ 06Ah
kClDrw			equ 06Bh
kLine			equ 06Ch
kPen			equ 06Dh
kPtChg			equ 06Eh
kPtOff			equ 06Fh
kPtOn			equ 070h
kVert			equ 071h
kHoriz			equ 072h
kText			equ 073h
kTanLn			equ 074h
kEval			equ 075h
kInters			equ 076h
kDYDX			equ 077h
kFnIntg			equ 078h
kRootG			equ 079h
kDYDT			equ 07Ah
kDXDT			equ 07Bh
kDRDo			equ 07Ch
KGFMin			equ 07Dh
KGFMax			equ 07Eh
EchoStart		equ 07Fh
kListName		equ 07Fh
kAdd			equ 080h
kSub			equ 081h
kMul			equ 082h
kDiv			equ 083h
kExpon			equ 084h
kLParen			equ 085h
kRParen			equ 086h
kLBrack			equ 087h
kRBrack			equ 088h
kShade			equ 089h
kStore			equ 08Ah
kComma			equ 08Bh
kChs			equ 08Ch
kDecPnt			equ 08Dh
k0			equ 08Eh
k1			equ 08Fh
k2			equ 090h
k3			equ 091h
k4			equ 092h
k5			equ 093h
k6			equ 094h
k7			equ 095h
k8			equ 096h
k9			equ 097h
kEE			equ 098h
kSpace			equ 099h
kCapA			equ 09Ah
kCapB			equ 09Bh
kCapC			equ 09Ch
kCapD			equ 09Dh
kCapE			equ 09Eh
kCapF			equ 09Fh
kCapG			equ 0A0h
kCapH			equ 0A1h
kCapI			equ 0A2h
kCapJ			equ 0A3h
kCapK			equ 0A4h
kCapL			equ 0A5h
kCapM			equ 0A6h
kCapN			equ 0A7h
kCapO			equ 0A8h
kCapP			equ 0A9h
kCapQ			equ 0AAh
kCapR			equ 0ABh
kCapS			equ 0ACh
kCapT			equ 0ADh
kCapU			equ 0AEh
kCapV			equ 0AFh
kCapW			equ 0B0h
kCapX			equ 0B1h
kCapY			equ 0B2h
kCapZ			equ 0B3h
kVarx			equ 0B4h
kPi			equ 0B5h
kInv			equ 0B6h
kSin			equ 0B7h
kASin			equ 0B8h
kCos			equ 0B9h
kACos			equ 0BAh
kTan			equ 0BBh
kATan			equ 0BCh
kSquare			equ 0BDh
kSqrt			equ 0BEh
kLn			equ 0BFh
kExp			equ 0C0h
kLog			equ 0C1h
kALog			equ 0C2h
kToABC			equ 0C3h
kClrTbl			equ 0C4h
kAns			equ 0C5h
kColon			equ 0C6h
kNDeriv			equ 0C7h
kFnInt			equ 0C8h
kRoot			equ 0C9h
kQuest			equ 0CAh
kQuote			equ 0CBh
kTheta			equ 0CCh
kIf			equ 0CDh
kThen			equ 0CEh
kElse			equ 0CFh
kFor			equ 0D0h
kWhile			equ 0D1h
kRepeat			equ 0D2h
kEnd			equ 0D3h
kPause			equ 0D4h
kLbl			equ 0D5h
kGoto			equ 0D6h
kISG			equ 0D7h
kDSL			equ 0D8h
kMenu			equ 0D9h
kExec			equ 0DAh
kReturn			equ 0DBh
kStop			equ 0DCh
kInput			equ 0DDh
kPrompt			equ 0DEh
kDisp			equ 0DFh
kDispG			equ 0E0h
kDispT			equ 0E1h
kOutput			equ 0E2h
kGetKey			equ 0E3h
kClrHome		equ 0E4h
kPrtScr			equ 0E5h
kSinH			equ 0E6h
kCosH			equ 0E7h
kTanH			equ 0E8h
kASinH			equ 0E9h
kACosH			equ 0EAh
kATanH			equ 0EBh
kLBrace			equ 0ECh
kRBrace			equ 0EDh
kI			equ 0EEh
kCONSTeA		equ 0EFh
kPlot3			equ 0F0h
kFMin			equ 0F1h
kFMax			equ 0F2h
kL1A			equ 0F3h
kL2A			equ 0F4h
kL3A			equ 0F5h
kL4A			equ 0F6h
kL5A			equ 0F7h
kL6A			equ 0F8h
kunA			equ 0F9h
kvnA			equ 0FAh
kwnA			equ 0FBh

; THIS KEY MEANS THAT IT IS A 2 BYTE KEYCODE
; THERE ARE 2 OF THESE KEYS; BE CAREFUL WITH USAGE
;--------------------------------------------------------
kExtendEcho2		equ 0FCh

; THIS KEY MEANS THAT THE KEY PRESS IS ONE THAT ECHOS
; INTO A BUFFER, AND IT IS A 2 BYTE KEY CODE, GO LOOK AT
; (EXTECHO) FOR THE KEY VALUE
;--------------------------------------------------------
kExtendEcho		equ 0FEh

kE1BT			equ 0
kDrawInv		equ kE1BT
kDrawF			equ kE1BT+1
kPixelOn		equ kE1BT+2
kPixelOff		equ kE1BT+3
kPxlTest		equ kE1BT+4
kRCGDB			equ kE1BT+5
kRCPic			equ kE1BT+6
kSTGDB			equ kE1BT+7
kSTPic			equ kE1BT+8
kAbs			equ kE1BT+9
kTequ 		equ kE1BT+10 ;==
kTNoteQ			equ kE1BT+11 ;<>
kTGT			equ kE1BT+12 ;>
kTGTE			equ kE1BT+13 ;>=
kTLT			equ kE1BT+14 ;<
kTLTE			equ kE1BT+15 ;<=
kAnd			equ kE1BT+16
kOr			equ kE1BT+17
kXor			equ kE1BT+18
kNot			equ kE1BT+19
kLR1			equ kE1BT+20
kXRoot			equ kE1BT+21
kCube			equ kE1BT+22
kCbRt			equ kE1BT+23 ;Cube ROOT
kToDec			equ kE1BT+24
kCubicR			equ kE1BT+25
kQuartR			equ kE1BT+26
kPlot1			equ kE1BT+27
kPlot2			equ kE1BT+28
kRound			equ kE1BT+29
kIPart			equ kE1BT+30
kFPart			equ kE1BT+31
kInt			equ kE1BT+32
kRand			equ kE1BT+33
kNPR			equ kE1BT+34
kNCR			equ kE1BT+35
kXFactorial		equ kE1BT+36
kRad			equ kE1BT+37
kDegr			equ kE1BT+38 ;DEGREES CONV
kAPost			equ kE1BT+39
kToDMS			equ kE1BT+40
kRToPo			equ kE1BT+41 ;R
kRToPr			equ kE1BT+42
kPToRx			equ kE1BT+43
kPToRy			equ kE1BT+44
kRowSwap		equ kE1BT+45
kRowPlus		equ kE1BT+46
kTimRow			equ kE1BT+47
kTRowP			equ kE1BT+48
kSortA			equ kE1BT+49
kSortD			equ kE1BT+50
kSeq			equ kE1BT+51
kMin			equ kE1BT+52
kMax			equ kE1BT+53
kMean			equ kE1BT+54
kMedian			equ kE1BT+55
kSum			equ kE1BT+56
kProd			equ kE1BT+57
kDet			equ kE1BT+58
kTransp			equ kE1BT+59
kDim			equ kE1BT+60
kFill			equ kE1BT+61
kIdent			equ kE1BT+62
kRandm			equ kE1BT+63
kAug			equ kE1BT+64
kOneVar			equ kE1BT+65
kTwoVar			equ kE1BT+66
kLR			equ kE1BT+67
kLRExp			equ kE1BT+68
kLRLn			equ kE1BT+69
kLRPwr			equ kE1BT+70
kMedMed			equ kE1BT+71
kQuad			equ kE1BT+72
kClrLst			equ kE1BT+73
kHist			equ kE1BT+74
kxyLine			equ kE1BT+75
kScatter		equ kE1BT+76
kmRad			equ kE1BT+77
kmDeg			equ kE1BT+78
kmNormF			equ kE1BT+79
kmSci			equ kE1BT+80
kmEng			equ kE1BT+81
kmFloat			equ kE1BT+82
kFix			equ kE1BT+83
kSplitOn		equ kE1BT+84
kFullScreen		equ kE1BT+85
kStndrd			equ kE1BT+86
kParam			equ kE1BT+87
kPolar			equ kE1BT+88
kSeqG			equ kE1BT+89
kAFillOn		equ kE1BT+90
kAFillOff		equ kE1BT+91
kACalcOn		equ kE1BT+92
kACalcOff		equ kE1BT+93
kFNOn			equ kE1BT+94
kFNOff			equ kE1BT+95
kPlotsOn		equ kE1BT+96
kPlotsOff		equ kE1BT+97
kPixelChg		equ kE1BT+98
kSendMBL		equ kE1BT+99
kRecvMBL		equ kE1BT+100
kBoxPlot		equ kE1BT+101
kBoxIcon		equ kE1BT+102
kCrossIcon		equ kE1BT+103
kDotIcon		equ kE1BT+104
kE2BT			equ kE1BT+105
kSeqential		equ kE2BT
kSimulG			equ kE2BT+1
kPolarG			equ kE2BT+2
kRectG			equ kE2BT+3
kCoordOn		equ kE2BT+4
kCoordOff		equ kE2BT+5
kDrawLine		equ kE2BT+6
kDrawDot		equ kE2BT+7
kAxisOn			equ kE2BT+8
kAxisOff		equ kE2BT+9
kGridOn			equ kE2BT+10
kGridOff		equ kE2BT+11
kLblOn			equ kE2BT+12
kLblOff			equ kE2BT+13
kL1			equ kE2BT+14
kL2			equ kE2BT+15
kL3			equ kE2BT+16
kL4			equ kE2BT+17
kL5			equ kE2BT+18
kL6			equ kE2BT+19

;These keys are laid on top of existing keys to
;enable localization in the inferential stats editor.
;----------------------------------------------------
kinfData		equ kL1
kinfStats		equ kL1+1
kinfYes			equ kL1+2
kinfNo			equ kL1+3
kinfCalc		equ kL1+4
kinfDraw		equ kL1+5
kinfAlt1ne		equ kL1+6
kinfAlt1lt		equ kL1+7
kinfAlt1gt		equ kL1+8
kinfAlt2ne		equ kL1+9
kinfAlt2lt		equ kL1+10
kinfAlt2gt		equ kL1+11
kinfAlt3ne		equ kL1+12
kinfAlt3lt		equ kL1+13
kinfAlt3gt		equ kL1+14
kinfAlt4ne		equ kL1+15
kinfAlt4lt		equ kL1+16
kinfAlt4gt		equ kL1+17
kinfAlt5ne		equ kL1+18
kinfAlt5lt		equ kL1+19
kinfAlt5gt		equ kL1+20
kinfAlt6ne		equ kL1+21
kinfAlt6lt		equ kL1+22
kinfAlt6gt		equ kL1+23
kMatA			equ kE2BT+20
kMatB			equ kE2BT+21
kMatC			equ kE2BT+22
kMatD			equ kE2BT+23
kMatE			equ kE2BT+24
kXmin			equ kE2BT+25
kXmax			equ kE2BT+26
kXscl			equ kE2BT+27
kYmin			equ kE2BT+28
kYmax			equ kE2BT+29
kYscl			equ kE2BT+30
kTmin			equ kE2BT+31
kTmax			equ kE2BT+32
kTStep			equ kE2BT+33
kOmin			equ kE2BT+34
kOmax			equ kE2BT+35
kOStep			equ kE2BT+36
ku0			equ kE2BT+37
kv0			equ kE2BT+38
knMin			equ kE2BT+39
knMax			equ kE2BT+40
kDeltaY			equ kE2BT+41
kDeltaX			equ kE2BT+42
kZXmin			equ kE2BT+43
kZXmax			equ kE2BT+44
kZXscl			equ kE2BT+45
kZYmin			equ kE2BT+46
kZYmax			equ kE2BT+47
kZYscl			equ kE2BT+48
kZTmin			equ kE2BT+49
kZTmax			equ kE2BT+50
kZTStep			equ kE2BT+51
kZOmin			equ kE2BT+52
kZOmax			equ kE2BT+53
kZOStep			equ kE2BT+54
kZu0			equ kE2BT+55
kZv0			equ kE2BT+56
kZnMin			equ kE2BT+57
kZnMax			equ kE2BT+58
kDelLast		equ kE2BT+59
kSinReg			equ kE2BT+60
kConstE			equ kE2BT+61
kPic1			equ kE2BT+62
kPic2			equ kE2BT+63
kPic3			equ kE2BT+64
kDelVar			equ kE2BT+65
kGetCalc		equ kE2BT+66
kRealM			equ kE2BT+67
kPolarM			equ kE2BT+68
kRectM			equ kE2BT+69
kuv			equ kE2BT+70 ;U vs V
kvw			equ kE2BT+71 ;V vs W
kuw			equ kE2BT+72 ;U vs W
kFinPMTend		equ kE2BT+73
kFinPMTbeg		equ kE2BT+74
kGraphStyle		equ kE2BT+75
kExprOn			equ kE2BT+76
kExprOff		equ kE2BT+77
kStatA			equ kE2BT+78
kStatB			equ kE2BT+79
kStatC			equ kE2BT+80
kCorr			equ kE2BT+81
kStatD			equ kE2BT+82
kStatE			equ kE2BT+83
kRegEq			equ kE2BT+84
kMinX			equ kE2BT+85
kQ1			equ kE2BT+86
kMD			equ kE2BT+87
kQ3			equ kE2BT+88
kMaxX			equ kE2BT+89
kStatX1			equ kE2BT+90
kStatY1			equ kE2BT+91
kStatX2			equ kE2BT+92
kStatY2			equ kE2BT+93
kStatX3			equ kE2BT+94
kStatY3			equ kE2BT+95
kTblMin			equ kE2BT+96
kTblStep		equ kE2BT+97
kSetupLst		equ kE2BT+98
kClrAllLst		equ kE2BT+99
kLogistic		equ kE2BT+100
kZTest			equ kE2BT+101
kTTest			equ kE2BT+102
k2SampZTest		equ kE2BT+103
k2SampTTest		equ kE2BT+104
k1PropZTest		equ kE2BT+105
k2PropZTest		equ kE2BT+106
kChiTest		equ kE2BT+107
k2SampFTest		equ kE2BT+108
kZIntVal		equ kE2BT+109
kTIntVal		equ kE2BT+110
k2SampTInt		equ kE2BT+111
k2SampZInt		equ kE2BT+112
k1PropZInt		equ kE2BT+113
k2PropZInt		equ kE2BT+114
kDNormal		equ kE2BT+115
kInvNorm		equ kE2BT+116
kDT			equ kE2BT+117
kChi			equ kE2BT+118
kDF			equ kE2BT+119
kBinPDF			equ kE2BT+120
kBinCDF			equ kE2BT+121
kPoiPDF			equ kE2BT+122
kPoiCDF			equ kE2BT+123
kun			equ kE2BT+124
kvn			equ kE2BT+125
kwn			equ kE2BT+126
kRecn			equ kE2BT+127
kPlotStart		equ kE2BT+128
kZPlotStart		equ kE2BT+129 ;recursion n
kXFact			equ kE2BT+130 ;PlotStart
kYFact			equ kE2BT+131 ;ZPlotStart
kANOVA			equ kE2BT+132 ;XFact
kMaxY			equ kE2BT+133 ;YFact
kWebOn			equ kE2BT+134 ;MinY
kWebOff			equ kE2BT+135 ;MaxY
kTblInput		equ kE2BT+136 ;WEB ON
kGeoPDF			equ kE2BT+137 ;WEB OFF
kGeoCDF			equ kE2BT+138 ;WEB OFF
kShadeNorm		equ kE2BT+139
kShadeT			equ kE2BT+140
kShadeChi		equ kE2BT+141
kShadeF			equ kE2BT+142
kPlotStep		equ kE2BT+143
kZPlotStep		equ kE2BT+144
kLinRegtTest		equ kE2BT+145
KMGT			equ kE2BT+146 ;VERT SPLIT
kSelectA		equ kE2BT+147
kZFitA			equ kE2BT+148
kE2BT_End		equ kZFitA

;More 2 Byte Keys
;-------------------------------------
kE2BT2			equ 00h
kGDB1			equ kE2BT2
kGDB2			equ kE2BT2+1
kGDB3			equ kE2BT2+2
kY1			equ kE2BT2+3
kY2			equ kE2BT2+4
kY3			equ kE2BT2+5
kY4			equ kE2BT2+6
kY5			equ kE2BT2+7
kY6			equ kE2BT2+8
kY7			equ kE2BT2+9
kY8			equ kE2BT2+10
kY9			equ kE2BT2+11
kY0			equ kE2BT2+12
kX1T			equ kE2BT2+13
kY1T			equ kE2BT2+14
kX2T			equ kE2BT2+15
kY2T			equ kE2BT2+16
kX3T			equ kE2BT2+17
kY3T			equ kE2BT2+18
kX4T			equ kE2BT2+19
kY4T			equ kE2BT2+20
kX5T			equ kE2BT2+21
kY5T			equ kE2BT2+22
kX6T			equ kE2BT2+23
kY6T			equ kE2BT2+24
kR1			equ kE2BT2+25
kR2			equ kE2BT2+26
kR3			equ kE2BT2+27
kR4			equ kE2BT2+28
kR5			equ kE2BT2+29
kR6			equ kE2BT2+30
kGDB4			equ kE2BT2+31
kGDB5			equ kE2BT2+32
kGDB6			equ kE2BT2+33
kPic4			equ kE2BT2+34
kPic5			equ kE2BT2+35
kPic6			equ kE2BT2+36
kGDB7			equ kE2BT2+37
kGDB8			equ kE2BT2+38
kGDB9			equ kE2BT2+39
kGDB0			equ kE2BT2+40
kPic7			equ kE2BT2+41
kPic8			equ kE2BT2+42
kPic9			equ kE2BT2+43
kPic0			equ kE2BT2+44
kStatN			equ kE2BT2+45
kXMean			equ kE2BT2+46
kConj			equ kE2BT2+47
kReal			equ kE2BT2+48
kFAngle			equ kE2BT2+49
kLCM			equ kE2BT2+50
kGCD			equ kE2BT2+51
kRandInt		equ kE2BT2+52
kRandNorm		equ kE2BT2+53
kToPolar		equ kE2BT2+54
kToRect			equ kE2BT2+55
kYMean			equ kE2BT2+56
kStdX			equ kE2BT2+57
kStdX1			equ kE2BT2+58
kw0			equ kE2BT2+59
kMatF			equ kE2BT2+60
kMatG			equ kE2BT2+61
kMatRH			equ kE2BT2+62
kMatI			equ kE2BT2+63
kMatJ			equ kE2BT2+64
kYMean1			equ kE2BT2+65
kStdY			equ kE2BT2+66
kStdY1			equ kE2BT2+67
kMatToLst		equ kE2BT2+68
kLstToMat		equ kE2BT2+69
kCumSum			equ kE2BT2+70
kDeltaLst		equ kE2BT2+71
kStdDev			equ kE2BT2+72
kVariance		equ kE2BT2+73
kLength			equ kE2BT2+74
kEquToStrng		equ kE2BT2+75
kStrngToequ 		equ kE2BT2+76
kExpr			equ kE2BT2+77
kSubStrng		equ kE2BT2+78
kInStrng		equ kE2BT2+79
kStr1			equ kE2BT2+80
kStr2			equ kE2BT2+81
kStr3			equ kE2BT2+82
kStr4		 	equ kE2BT2+83
kStr5		 	equ kE2BT2+84
kStr6		 	equ kE2BT2+85
kStr7		 	equ kE2BT2+86
kStr8		 	equ kE2BT2+87
kStr9		 	equ kE2BT2+88
kStr0		 	equ kE2BT2+89
kFinN		 	equ kE2BT2+90
kFinI		 	equ kE2BT2+91
kFinPV			equ kE2BT2+92
kFinPMT			equ kE2BT2+93
kFinFV			equ kE2BT2+94
kFinPY			equ kE2BT2+95
kFinCY			equ kE2BT2+96
kFinFPMT		equ kE2BT2+97
kFinFI			equ kE2BT2+98
kFinFPV			equ kE2BT2+99
kFinFN			equ kE2BT2+100
kFinFFV			equ kE2BT2+101
kFinNPV			equ kE2BT2+102
kFinIRR			equ kE2BT2+103
kFinBAL			equ kE2BT2+104
kFinPRN			equ kE2BT2+105
kFinINT			equ kE2BT2+106
kSumX		 	equ kE2BT2+107
kSumX2			equ kE2BT2+108
kFinToNom		equ kE2BT2+109
kFinToEff		equ kE2BT2+110
kFinDBD			equ kE2BT2+111
kStatVP			equ kE2BT2+112
kStatZ			equ kE2BT2+113
kStatT			equ kE2BT2+114
kStatChi		equ kE2BT2+115
kStatF			equ kE2BT2+116
kStatDF			equ kE2BT2+117
kStatPhat		equ kE2BT2+118
kStatPhat1		equ kE2BT2+119
kStatPhat2		equ kE2BT2+120
kStatMeanX1		equ kE2BT2+121
kStatMeanX2		equ kE2BT2+122
kStatStdX1		equ kE2BT2+123
kStatStdX2		equ kE2BT2+124
kStatStdXP		equ kE2BT2+125
kStatN1			equ kE2BT2+126
kStatN2			equ kE2BT2+127
kStatLower		equ kE2BT2+128
kStatUpper		equ kE2BT2+129
kuw0			equ kE2BT2+130
kImag			equ kE2BT2+131
kSumY			equ kE2BT2+132
kXres			equ kE2BT2+133
kStat_s			equ kE2BT2+134
kSumY2			equ kE2BT2+135
kSumXY			equ kE2BT2+136
kuXres			equ kE2BT2+137
kModBox			equ kE2BT2+138
kNormProb		equ kE2BT2+139
kNormalPDF		equ kE2BT2+140
kTPDF			equ kE2BT2+141
kChiPDF			equ kE2BT2+142
kFPDF			equ kE2BT2+143
kMinY			equ kE2BT2+144 ;MinY
kRandBin		equ kE2BT2+145
kRef			equ kE2BT2+146
kRRef			equ kE2BT2+147
kLRSqr			equ kE2BT2+148
kBRSqr			equ kE2BT2+149
kDiagOn			equ kE2BT2+150
kDiagOff		equ kE2BT2+151
kun1			equ kE2BT2+152 ;FOR RCL USE WHEN GOTTEN FROM 82
kvn1			equ kE2BT2+153 ;FOR RCL USE WHEN GOTTEN FROM 82
k83_00End		equ kvn1 ;end of original keys...
kArchive		equ k83_00End + 1
kUnarchive		equ k83_00End + 2
kAsm			equ k83_00End + 3 ;Asm(
kAsmPrgm		equ k83_00End + 4 ;AsmPrgm
kAsmComp		equ k83_00End + 5 ;AsmComp(
kcapAAcute		equ k83_00End + 6
kcapAGrave		equ k83_00End + 7
kcapACaret		equ k83_00End + 8
kcapADier		equ k83_00End + 9
kaAcute			equ k83_00End + 10
kaGrave			equ k83_00End + 11
kaCaret			equ k83_00End + 12
kaDier			equ k83_00End + 13
kcapEAcute		equ k83_00End + 14
kcapEGrave		equ k83_00End + 15
kcapECaret		equ k83_00End + 16
kcapEDier		equ k83_00End + 17
keAcute			equ k83_00End + 18
keGrave			equ k83_00End + 19
keCaret			equ k83_00End + 20
keDier			equ k83_00End + 21
kcapIAcute		equ k83_00End + 22
kcapIGrave		equ k83_00End + 23
kcapICaret		equ k83_00End + 24
kcapIDier		equ k83_00End + 25
kiAcute			equ k83_00End + 26
kiGrave			equ k83_00End + 27
kiCaret			equ k83_00End + 28
kiDier			equ k83_00End + 29
kcapOAcute		equ k83_00End + 30
kcapOGrave		equ k83_00End + 31
kcapOCaret		equ k83_00End + 32
kcapODier		equ k83_00End + 33
koAcute			equ k83_00End + 34
koGrave			equ k83_00End + 35
koCaret			equ k83_00End + 36
koDier			equ k83_00End + 37
kcapUAcute		equ k83_00End + 38
kcapUGrave		equ k83_00End + 39
kcapUCaret		equ k83_00End + 40
kcapUDier		equ k83_00End + 41
kuAcute			equ k83_00End + 42
kuGrave			equ k83_00End + 43
kuCaret			equ k83_00End + 44
kuDier			equ k83_00End + 45
kcapCCed		equ k83_00End + 46
kcCed			equ k83_00End + 47
kcapNTilde		equ k83_00End + 48
knTilde			equ k83_00End + 49
kaccent			equ k83_00End + 50
kgrave			equ k83_00End + 51
kdieresis		equ k83_00End + 52
kquesDown		equ k83_00End + 53
kexclamDown		equ k83_00End + 54
kalpha			equ k83_00End + 55
kbeta		 	equ k83_00End + 56
kgamma			equ k83_00End + 57
kcapDelta		equ k83_00End + 58
kdelta			equ k83_00End + 59
kepsilon		equ k83_00End + 60
klambda			equ k83_00End + 61
kmu			equ k83_00End + 62
kpi2			equ k83_00End + 63
krho			equ k83_00End + 64
kcapSigma		equ k83_00End + 65
ksigma			equ k83_00End + 66
ktau			equ k83_00End + 67
kphi			equ k83_00End + 68
kcapOmega		equ k83_00End + 69
kphat			equ k83_00End + 70
kchi2			equ k83_00End + 71
kstatF2			equ k83_00End + 72
kLa			equ k83_00End + 73
kLb			equ k83_00End + 74
kLc			equ k83_00End + 75
kLd			equ k83_00End + 76
kLe			equ k83_00End + 77
kLf			equ k83_00End + 78
kLg			equ k83_00End + 79
kLh			equ k83_00End + 80
kLi			equ k83_00End + 81
kLj			equ k83_00End + 82
kLk			equ k83_00End + 83
kLl			equ k83_00End + 84
kLm			equ k83_00End + 85
kLsmalln		equ k83_00End + 86
kLo			equ k83_00End + 87
kLp			equ k83_00End + 88
kLq			equ k83_00End + 89
kLsmallr		equ k83_00End + 90
kLs			equ k83_00End + 91
kLt			equ k83_00End + 92
kLu			equ k83_00End + 93
kLv			equ k83_00End + 94
kLw			equ k83_00End + 95
kLx			equ k83_00End + 96
kLy			equ k83_00End + 97
kLz			equ k83_00End + 98
kGarbageC		equ k83_00End + 99 ;GarbageCollect
kE2BT2_End		equ kGarbageC

;TI-83 Plus Context Equates
;--------------------------------------------------------------
cxCmd			equ kQuit ;home screen
cxMatEdit		equ kMatrixEd ;matrix editor
cxPrgmEdit		equ kPrgmEd ;program editor
cxEquEdit		equ kYequ ;equation editor
cxGrRange		equ kWindow ;graph range editor
cxGrZfact		equ kZFactEd ;graph zoom factors editor
cxGraph			equ kGraph ;graph mode
cxStatEdit		equ kStatEd ;statistics list editor
cxPrgmInput		equ kPrgmInput ;programmed input
cxError			equ kError ;error handler
cxLinkIO		equ kLinkIO ;LINK I/O interface
cxMem			equ kResetMem ;reset memory
cxDefMem		equ kResetDef ;reset default
cxRAMApp		equ kChkRAM ;RAM usage screen
cxMode			equ kMode ;mode settings screen
cxErase			equ kDelMem ;memory erase
cxPrgmCreate		equ kPrgmCr ;PROGRAM CREATE
cxTableEditor		equ kTable ;TABLE EDITOR
cxTableSet		equ kTblSet ;TABLE SET UP
cxStatPlot		equ kStatP ;STAT PLOTS
cxInfStat		equ kInfStat ;Inferential Statistic
cxFormat		equ kFormat ;FORMAT CONTEXT
cxSolveTVM		equ kSolveTVM ;Solve TVM
cxSolveRoot		equ kSolveRoot ;Solve Root
lastOldApp		equ kExtApps ;external applications
cxextapps		equ kExtApps
cxNewApps		equ kNewApps ;new cerberus applications
cxGroup			equ cxNewApps+0 ;1st new app.
cxUnGroup		equ cxNewApps+1 ;2nd new app.
lastNewApp		equ cxUnGroup ;last new app for this ver

;Scan Code Equates
;------------------------------
skDown			equ 01h
skLeft			equ 02h
skRight			equ 03h
skUp			equ 04h
skEnter			equ 09h
skAdd			equ 0Ah
skSub			equ 0Bh
skMul			equ 0Ch
skDiv			equ 0Dh
skPower			equ 0Eh
skClear			equ 0Fh
skChs			equ 11h
sk3			equ 12h
sk6			equ 13h
sk9			equ 14h
skRParen		equ 15h
skTan			equ 16h
skVars			equ 17h
skDecPnt		equ 19h
sk2			equ 1Ah
sk5			equ 1Bh
sk8			equ 1Ch
skLParen		equ 1Dh
skCos			equ 1Eh
skPrgm			equ 1Fh
skStat			equ 20h
sk0			equ 21h
sk1			equ 22h
sk4			equ 23h
sk7			equ 24h
skComma			equ 25h
skSin			equ 26h
skMatrix		equ 27h
skGraphvar		equ 28h
skStore			equ 2Ah
skLn			equ 2Bh
skLog			equ 2Ch
skSquare		equ 2Dh
skRecip			equ 2Eh
skMath			equ 2Fh
skAlpha			equ 30h
skGraph			equ 31h
skTrace			equ 32h
skZoom			equ 33h
skWindow		equ 34h
skYequ 			equ 35h
sk2nd			equ 36h
skMode			equ 37h
skDel			equ 38h

; DI Keyboard Equates
;---------------------------
DI_Mode		equ 0F50000h
DI_Cntrl	equ 0F50004h
DI_Int		equ 0F50008h
DI_IntMask	equ 0F5000Ch

kbdG1		equ 0F50012h
;----------------------------
kbdGraph	equ 00000001b
kbdTrace	equ 00000010b
kbdZoom		equ 00000100b
kbdWindow	equ 00001000b
kbdYequ 	equ 00010000b
kbd2nd		equ 00100000b
kbdMode		equ 01000000b
kbdDel		equ 10000000b

kbitGraph	equ 00h
kbitTrace	equ 01h
kbitZoom	equ 02h
kbitWindow	equ 03h
kbitYequ equ 04h
kbit2nd		equ 05h
kbitMode	equ 06h
kbitDel		equ 07h

kbdG2		equ 0F50014h
;----------------------------
kbdStore	equ 00000010b
kbdLn		equ 00000100b
kbdLog		equ 00001000b
kbdSquare	equ 00010000b
kbdRecip	equ 00100000b
kbdMath		equ 01000000b
kbdAlpha	equ 10000000b

kbitStore	equ 01h
kbitLn		equ 02h
kbitLog		equ 03h
kbitSquare	equ 04h
kbitRecip	equ 05h
kbitMath	equ 06h
kbitAlpha	equ 07h

kbdG3		equ 0F50016h
;----------------------------
kbd0		equ 00000001b
kbd1		equ 00000010b
kbd4		equ 00000100b
kbd7		equ 00001000b
kbdComma	equ 00010000b
kbdSin		equ 00100000b
kbdApps		equ 01000000b
kbdGraphVar	equ 10000000b

kbit0		equ 00h
kbit1		equ 01h
kbit4		equ 02h
kbit7		equ 03h
kbitComma	equ 04h
kbitSin		equ 05h
kbitApps	equ 06h
kbitGraphVar	equ 07h

kbdG4		equ 0F50018h
;----------------------------
kbdDecPnt	equ 00000001b
kbd2		equ 00000010b
kbd5		equ 00000100b
kbd8		equ 00001000b
kbdLParen	equ 00010000b
kbdCos		equ 00100000b
kbdPgrm		equ 01000000b
kbdStat		equ 10000000b

kbitDecPnt	equ 00h
kbit2		equ 01h
kbit5		equ 02h
kbit8		equ 03h
kbitLParen	equ 04h
kbitCos		equ 05h
kbitPgrm	equ 06h
kbitStat	equ 07h

kbdG5		equ 0F5001Ah
;----------------------------
kbdChs		equ 00000001b
kbd3		equ 00000010b
kbd6		equ 00000100b
kbd9		equ 00001000b
kbdRParen	equ 00010000b
kbdTan		equ 00100000b
kbdVars		equ 01000000b

kbitChs		equ 00h
kbit3		equ 01h
kbit6		equ 02h
kbit9		equ 03h
kbitRParen	equ 04h
kbitTan		equ 05h
kbitVars	equ 06h

kbdG6		equ 0F5001Ch
;----------------------------
kbdEnter	equ 00000001b
kbdAdd		equ 00000010b
kbdSub		equ 00000100b
kbdMul		equ 00001000b
kbdDiv		equ 00010000b
kbdPower	equ 00100000b
kbdClear	equ 01000000b

kbitEnter	equ 00h
kbitAdd		equ 01h
kbitSub		equ 02h
kbitMul		equ 03h
kbitDiv		equ 04h
kbitPower	equ 05h
kbitClear	equ 06h

kbdG7		equ 0F5001Eh
;----------------------------
kbdDown		equ 00000001b
kbdLeft		equ 00000010b
kbdRight	equ 00000100b
kbdUp		equ 00001000b

kbitDown	equ 00h
kbitLeft	equ 01h
kbitRight	equ 02h
kbitUp		equ 03h

;Tokens
;-----------------------------------------------------
EOSSTART		equ 00h

;DISPLAY CONVERSIONS COME IMMEDIATELY BEFORE 'TSTORE'
;
DCONV			equ 01h
;
tToDMS			equ DCONV ;01h
tToDEC			equ DCONV+1 ;02h
tToAbc			equ DCONV+2 ;03h > A b/c
;
tStore			equ DCONV+3 ;04h Lstore 01
;
tBoxPlot		equ 05h
;
BRACKS			equ 06h
;
tLBrack			equ BRACKS ;06h '['
tRBrack			equ BRACKS+1 ;07h ']'
tLBrace			equ BRACKS+2 ;08h '{'
tRBrace			equ BRACKS+3 ;09h '}'
;
tPOST1			equ BRACKS+4
;
tFromRad		equ tPOST1 ;0Ah Lradian
tFromDeg		equ tPOST1+1 ;0Bh Ldegree
tRecip			equ tPOST1+2 ;0Ch Linverse
tSqr			equ tPOST1+3 ;0Dh Lsquare
tTrnspos		equ tPOST1+4 ;0Eh Ltranspose
tCube			equ tPOST1+5 ;0Fh '^3'
;
tLParen			equ 10h ;10h '('
tRParen			equ 11h ;11h ')'
;
IMUN			equ 12h
;
tRound			equ IMUN ;12h 'round'
tPxTst			equ IMUN+1 ;13h 'PXL-TEST'
tAug			equ IMUN+2 ;14h 'aug'
tRowSwap		equ IMUN+3 ;15h 'rSwap'
tRowPlus		equ IMUN+4 ;16h 'rAdd'
tmRow			equ IMUN+5 ;17h 'multR'
tmRowPlus		equ IMUN+6 ;18h 'mRAdd'
tMax			equ IMUN+7 ;19h 'max'
tMin			equ IMUN+8 ;1Ah 'min'
tRToPr			equ IMUN+9 ;1Bh 'R>Pr
tRToPo			equ IMUN+10 ;1Ch 'R>Po
tPToRx			equ IMUN+11 ;1Dh 'P>Rx
tPToRy			equ IMUN+12 ;1Eh 'P>Ry
tMedian			equ IMUN+13 ;1Fh 'MEDIAN
tRandM			equ IMUN+14 ;20h 'randM'
tMean			equ IMUN+15 ;21h
tRoot			equ IMUN+16 ;22h 'ROOT'
tSeries			equ IMUN+17 ;23h 'seq'
tFnInt			equ IMUN+18 ;24h 'fnInt'
tNDeriv			equ IMUN+19 ;25h 'fnIr'
tEvalF			equ IMUN+20 ;26h
tFmin			equ IMUN+21 ;27h
tFmax			equ IMUN+22 ;28h
;
tEOSEL			equ IMUN+23
;
tSpace			equ tEOSEL ;29h ' '
tString			equ tEOSEL+1 ;2Ah '"'
tComma			equ tEOSEL+2 ;2Bh ','
;
tii			equ 2Ch ;i

;Postfix Functions
;-----------------------------------------
tPost			equ 2Dh
;
tFact			equ tPost ;2Dh '!'
;
tCubicR			equ 2Eh
tQuartR			equ 2Fh

;Number Tokens 
;---------------------------------------
NUMS			equ 30h
;
t0			equ NUMS ;30h
t1			equ NUMS+1 ;31h
t2			equ NUMS+2 ;32h
t3			equ NUMS+3 ;33h
t4			equ NUMS+4 ;34h
t5			equ NUMS+5 ;35h
t6			equ NUMS+6 ;36h
t7			equ NUMS+7 ;37h
t8			equ NUMS+8 ;38h
t9			equ NUMS+9 ;39h
tDecPt			equ NUMS+10 ;3Ah
tee			equ NUMS+11 ;3Bh

;Binary OP
;-------------------------------------------
tOr			equ 3Ch ;3Ch '_or_'
tXor			equ 3Dh ;3Dh
;
tColon			equ 3Eh ;3Eh ':'
tEnter			equ 3Fh ;3Fh Lenter
;
tAnd			equ 40h ;40h '_and_'

;Letter Tokens
;--------------------------------------
LET			equ 41h
tA			equ LET ;41h
tB			equ LET+1 ;42h
tC			equ LET+2 ;43h
tD			equ LET+3 ;44h
tE			equ LET+4 ;45h
tF			equ LET+5 ;46h
tG			equ LET+6 ;47h
tH			equ LET+7 ;48h
tI			equ LET+8 ;49h
tJ			equ LET+9 ;4Ah
tK			equ LET+10 ;4Bh
tL			equ LET+11 ;4Ch
tM			equ LET+12 ;4Dh
tN			equ LET+13 ;4Eh
tO			equ LET+14 ;4Fh
tP			equ LET+15 ;50h
tQ			equ LET+16 ;51h
tR			equ LET+17 ;52h
tS			equ LET+18 ;53h
tT			equ LET+19 ;54h
tU			equ LET+20 ;55h
tV			equ LET+21 ;56h
tW			equ LET+22 ;57h
tX			equ LET+23 ;58h
tY			equ LET+24 ;59h
tZ			equ LET+25 ;5Ah
tTheta			equ LET+26 ;5Bh

; Extended Tokens
;---------------------------
tExtTok		equ	0EFh

tSetDate	equ	00h
tSetTime	equ	01h
tCheckTmr	equ	02h
tSetDtFmt	equ	03h
tSetTmFmt	equ	04h
tTimeCnv	equ	05h
tDayOfWk	equ	06h
tGetDtStr	equ	07h
tGetTmStr	equ	08h
tGetDate	equ	09h
tGetTime	equ	0Ah
tStartTmr	equ	0Bh
tGtDtFmt	equ	0Ch
tGetTmFmt	equ	0Dh
tIsClockOn	equ	0Eh
tClockOff	equ	0Fh
tClockOn	equ	10h
tOpenLib	equ	11h
tExecLib	equ	12h
tInvT		equ	13h
tChiSquaredGofTest	equ	14h
tLinRegTInt	equ	15h
tManualFit	equ	16h

; MathPrint
tZQuadrant	equ	17h
tZFracHalf	equ	18h
tZFracThird	equ	19h
tZFracFourth	equ	1Ah
tZFracFifth	equ	1Bh
tZFracEighth	equ	1Ch
tZFracTenth	equ	1Dh
tFracSlash	equ	2Eh
tFracMixedNum	equ	2Fh
tSwapImProper	equ	30h
tSwapFracDec	equ	31h
tRemainder	equ	32h
tSummationSigma	equ	33h
tLogBase	equ	34h
tRandIntNoRep	equ	35h
tMathPrint	equ	37h
tClassic	equ	38h
tAutoAnswer	equ	3Bh
tDecAnswer	equ	3Ch
tFracAnswer	equ	3Dh

; TI-84+CSE/CE
tBlue		equ	41h
tRed		equ	42h
tBlack 		equ	43h
tMagenta	equ	44h
tGreen		equ	45h
tOrange		equ	46h
tBrown		equ	47h
tNavy		equ	48h
tLtBlue		equ	49h
tYellow		equ	4Ah
tWhite		equ	4Bh
tLtGray		equ	4Ch
tMedGray	equ	4Dh
tGray		equ	4Eh
tDarkGray	equ	4Fh

tGraphColor	equ	65h
tTextColor	equ	67h
tBackgroundOn	equ	5Bh
tBackgroundOff	equ	64h

tThin		equ	74h
;tThick - 0x7E 0x06 (was "Connected"?)
tAsm84CPrgm	equ	68h
tAsm84CCmp	equ	69h
tBorderColor	equ	6Ch

tAsm84CeCmp	equ	07Bh
tAsm84CePrgm	equ	07Ah

; OS 5.2+ only
tLEFT           equ     92h
tCENTER         equ     93h
tRIGHT          equ     94h
tInvBinom       equ     95h
tWait           equ     96h
tToString       equ     97h
tEval           equ     98h

;These Var Tokens Are 1st Of A Double Token
;-----------------------------------------------

vToks			equ LET+27

;User Matrix Token, 2nd Token Needed For Name
;
tVarMat			equ vToks ;5Ch
;
;User List Token, 2nd Token Needed For Name
;
tVarLst			equ vToks+1 ;5Dh
;
;User Equation Token, 2nd Token Needed For Name
;
tVarequ 		equ vToks+2 ;5Eh
tProg			equ vToks+3 ;5Fh
;
;User Pict Token, 2nd Token Needed For Name
;
tVarPict		equ vToks+4 ;60h
;
;User GDB Token, 2nd Token Needed For Name
;
tVarGDB			equ vToks+5 ;61h
tVarOut			equ vToks+6 ;62h
tVarSys			equ vToks+7 ;63h

;Mode Setting Commands
;-------------------------------------------------
MODESA			equ vToks+8 ;64h
tRad			equ MODESA ;64h 'Radian'
tDeg			equ MODESA+1 ;65h 'Degree'
tNormF			equ MODESA+2 ;66h 'Normal'
tSci			equ MODESA+3 ;67h 'Sci'
tEng			equ MODESA+4 ;68h 'Eng'
tFloat			equ MODESA+5 ;69h 'Float'
CMPS			equ 6Ah
tEQ			equ CMPS ;6Ah '=='
tLT			equ CMPS+1 ;6Bh '<'
tGT			equ CMPS+2 ;6Ch '>'
tLE			equ CMPS+3 ;6Dh LLE
tGE			equ CMPS+4 ;6Eh LGE
tNE			equ CMPS+5 ;6Fh LNE

;Binary OP
;---------------------------------------
tAdd			equ 70h ;70h '+'
tSub			equ 71h ;71h '-'
tAns			equ 72h ;72h

;Mode Setting Commands
;------------------------------------------------------
MODES			equ 73h
tFix			equ MODES ;73h 'Fix_'
tSplitOn		equ MODES+1 ;74h
tFullScreen		equ MODES+2 ;75h
tStndrd			equ MODES+3 ;76h 'Func'
tParam			equ MODES+4 ;77h 'Param'
tPolar			equ MODES+5 ;78h 'Pol'
tSeqG			equ MODES+6 ;79h
tAFillOn		equ MODES+7 ;7Ah 'AUTO FILL ON'
tAFillOff		equ MODES+8 ;7Bh
tACalcOn		equ MODES+9 ;7Ch
tACalcOff		equ MODES+10 ;7Dh 'AutoFill OFF'

;Graph Format Tokens Are 2 Byte Tokens
;----------------------------------------
tGFormat		equ MODES+11 ;7Eh
tBoxIcon		equ 7Fh
tCrossIcon		equ 80h
tDotIcon		equ 81h

;(More) Binary OP
;---------------------------------------
tMul			equ 82h ;82h '*'
tDiv			equ 83h ;83h '/'

;Some Graph Commands
;-----------------------------------------------------
GRCMDS			equ 84h
tTrace			equ GRCMDS ; 84h 'Trace'
tClDrw			equ GRCMDS+1 ; 85h 'ClDrw'
tZoomStd		equ GRCMDS+2 ; 86h 'ZStd'
tZoomtrg		equ GRCMDS+3 ; 87h 'Ztrg'
tZoomBox		equ GRCMDS+4 ; 88h 'ZBOX'
tZoomIn			equ GRCMDS+5 ; 89h 'ZIn'
tZoomOut		equ GRCMDS+6 ; 8Ah 'ZOut'
tZoomSqr		equ GRCMDS+7 ; 8Bh 'ZSqr'
tZoomInt		equ GRCMDS+8 ; 8Ch 'ZInt'
tZoomPrev		equ GRCMDS+9 ; 8Dh 'ZPrev'
tZoomDec		equ GRCMDS+10 ; 8Eh 'ZDecm'
tZoomStat		equ GRCMDS+11 ; 8Fh 'ZStat
tUsrZm			equ GRCMDS+12 ; 90h 'ZRcl'
tPrtScrn		equ GRCMDS+13 ; 91h 'PrtScrn'
tZoomSto		equ GRCMDS+14 ; 92h  ZOOM STORE
tText			equ GRCMDS+15 ; 93h

;Binary OP (Combination & Permutation)
;-------------------------------------------------
tnPr			equ GRCMDS+16 ;94h '_nPr_'
tnCr			equ GRCMDS+17 ;95h '_nCr_'

;More Graph Commands
;--------------------------------------------------
tYOn			equ GRCMDS+18 ;96h 'FnOn_'
tYOff			equ GRCMDS+19 ;97h 'FnOff_'
tStPic			equ GRCMDS+20 ;98h 'StPic_'
tRcPic			equ GRCMDS+21 ;99h 'RcPic_'
tStoDB			equ GRCMDS+22 ;9Ah 'StGDB_'
tRclDB			equ GRCMDS+23 ;9Bh 'RcGDB_'
tLine			equ GRCMDS+24 ;9Ch 'Line'
tVert			equ GRCMDS+25 ;9Dh 'Vert_'
tPtOn			equ GRCMDS+26 ;9Eh 'PtOn'
tPtOff			equ GRCMDS+27 ;9Fh 'PtOff'

;Token A0 Cannot Be An EOS Function Since Low MULT=A0 Already
;-----------------------------------------------------
tPtChg			equ GRCMDS+28 ;A0h 'PtChg'
tPXOn			equ GRCMDS+29 ;A1h
tPXOff			equ GRCMDS+30 ;A2h
tPXChg			equ GRCMDS+31 ;A3h
tShade			equ GRCMDS+32 ;A4h 'Shade'
tCircl			equ GRCMDS+33 ;A5h 'Circl'
tHorz			equ GRCMDS+34 ;A6h 'HORIZONTAL'
tTanLn			equ GRCMDS+35 ;A7h 'TanLn'
tDrInv			equ GRCMDS+36 ;A8h 'DrInv_'
tDrawF			equ GRCMDS+37 ;A9h 'DrawF_'
tVarStrng		equ 0AAh

;Functions with No Arguments
;--------------------------------------------------
NOARG			equ 0ABh
tRand			equ NOARG ;ABh 'rand'
tPi			equ NOARG+1 ;ACh  Lpi
tGetKey			equ NOARG+2 ;ADh 'getKy'
tAPost			equ tGetKey+1 ;APOSTROPHY
tQuest			equ tAPost+1 ;QUESTION MARK
UNARY			equ tQuest+1 ;B0h
tChs			equ UNARY ;B0h
tInt			equ UNARY+1 ;B1h
tAbs			equ UNARY+2 ;B2h
tDet			equ UNARY+3 ;B3h
tIdent			equ UNARY+4 ;B4h
tDim			equ UNARY+5 ;B5h
tSum			equ UNARY+6 ;B6h
tProd			equ UNARY+7 ;B7h
tNot			equ UNARY+8 ;B8h
tIPart			equ UNARY+9 ;B9h
tFPart			equ UNARY+10 ;BAh

;New 2 Byte Tokens
;------------------------------------------
t2ByteTok		equ 0BBh
UNARYLR			equ UNARY+12
tSqrt			equ UNARYLR ;BCh
tCubRt			equ UNARYLR+1 ;BDh
tLn			equ UNARYLR+2 ;BEh
tExp			equ UNARYLR+3 ;BFh
tLog			equ UNARYLR+4 ;C0h
tALog			equ UNARYLR+5 ;C1h
tSin			equ UNARYLR+6 ;C2h
tASin			equ UNARYLR+7 ;C3h
tCos			equ UNARYLR+8 ;C4h
tACos			equ UNARYLR+9 ;C5h
tTan			equ UNARYLR+10 ;C6h
tATan			equ UNARYLR+11 ;C7h
tSinH			equ UNARYLR+12 ;C8h
tASinH			equ UNARYLR+13 ;C9h
tCoshH			equ UNARYLR+14 ;CAh
tACosH			equ UNARYLR+15 ;CBh
tTanH			equ UNARYLR+16 ;CCh
tATanH			equ UNARYLR+17 ;CDh

;Some Programming Commands
;---------------------------------------------------
PROGTOK			equ UNARYLR+18
tIf			equ PROGTOK ;CEh
tThen			equ PROGTOK+1 ;CFh
tElse			equ PROGTOK+2 ;D0h
tWhile			equ PROGTOK+3 ;D1h
tRepeat			equ PROGTOK+4 ;D2h
tFor			equ PROGTOK+5 ;D3h
tEnd			equ PROGTOK+6 ;D4h
tReturn			equ PROGTOK+7 ;D5h
tLbl			equ PROGTOK+8 ;D6h 'Lbl_'
tGoto			equ PROGTOK+9 ;D7h 'Goto_'
tPause			equ PROGTOK+10 ;D8h 'Pause_'
tStop			equ PROGTOK+11 ;D9h 'Stop'
tISG			equ PROGTOK+12 ;DAh 'IS>'
tDSL			equ PROGTOK+13 ;DBh 'DS<'
tInput			equ PROGTOK+14 ;DCh 'Input_'
tPrompt			equ PROGTOK+15 ;DDh 'Prompt_'
tDisp			equ PROGTOK+16 ;DEh 'Disp_'
tDispG			equ PROGTOK+17 ;DFh 'DispG'
tOutput			equ PROGTOK+18 ;E0h 'Outpt'
tClLCD			equ PROGTOK+19 ;E1h 'ClLCD'
tConst			equ PROGTOK+20 ;E2h 'Fill'
tSortA			equ PROGTOK+21 ;E3h 'sortA_'
tSortD			equ PROGTOK+22 ;E4h 'sortD_'
tDispTab		equ PROGTOK+23 ;E5h 'Disp Table
tMenu			equ PROGTOK+24 ;E6h 'Menu'
tSendMBL		equ PROGTOK+25 ;E7h 'SEND'
tGetMBL			equ PROGTOK+26 ;E8h 'GET'

;Stat Plot Commands
;-----------------------------------------------------
statPCmd		equ PROGTOK+27
tPlotOn			equ statPCmd ;E9h ' PLOTSON'
tPlotOff		equ statPCmd+1 ;EAh ' PLOTSOFF
tListName		equ 0EBh ;LIST DESignATOR
tPlot1			equ 0ECh
tPlot2			equ 0EDh
tPlot3			equ 0EEh
tUnused01		equ 0EFh ;available?
tPower			equ 0F0h ;'^'
tXRoot			equ 0F1h ;LsupX,Lroot
STATCMD			equ 0F2h
tOneVar			equ STATCMD ;F2h 'OneVar_'
tTwoVar			equ STATCMD+1 ;F3h
tLR			equ STATCMD+2 ;F4h 'LinR(A+BX
tLRExp			equ STATCMD+3 ;F5h 'ExpR_'
tLRLn			equ STATCMD+4 ;F6h 'LnR_'
tLRPwr			equ STATCMD+5 ;F7h 'PwrR_'
tMedMed			equ STATCMD+6 ;F8h
tQuad			equ STATCMD+7 ;F9h
tClrLst			equ STATCMD+8 ;FAh 'CLEAR LIST
tClrTbl			equ STATCMD+9 ;FBh CLEAR TABLE
tHist			equ STATCMD+10 ;FCh 'Hist_'
txyLine			equ STATCMD+11 ;FDh 'xyline_'
tScatter		equ STATCMD+12 ;FEh 'Scatter_'
tLR1			equ STATCMD+13 ;FFh 'LINR(AX+B

;2nd Half Of Graph Format Tokens
;Format settings commands
;---------------------------------------------
GFMT			equ 00h
tSeq			equ GFMT ; 'SeqG'
tSimulG			equ GFMT+1 ; 'SimulG'
tPolarG			equ GFMT+2 ; 'PolarGC'
tRectG			equ GFMT+3 ; 'RectGC'
tCoordOn		equ GFMT+4 ; 'CoordOn'
tCoordOff		equ GFMT+5 ; 'CoordOff'
tDrawLine		equ GFMT+6 ; 'DrawLine'
tDrawDot		equ GFMT+7 ; 'DrawDot'
tAxisOn			equ GFMT+8 ; 'AxesOn'
tAxisOff		equ GFMT+9 ; 'AxesOff'
tGridOn			equ GFMT+10 ; 'GridOn'
tGridOff		equ GFMT+11 ; 'GridOff'
tLblOn			equ GFMT+12 ; 'LabelOn'
tLblOff			equ GFMT+13 ; 'LabelOff'
tWebOn			equ GFMT+14 ; 'WebOn'
tWebOff			equ GFMT+15 ; 'WebOFF'
tuv			equ GFMT+16 ; U vs V
tvw			equ GFMT+17 ; V vs W
tuw			equ GFMT+18 ; U vs W

;2nd Half Of User Matrix Tokens
;-------------------------------------
tMatA			equ 00h ;MAT A
tMatB			equ 01h ;MAT B
tMatC			equ 02h ;MAT C
tMatD			equ 03h ;MAT D
tMatE			equ 04h ;MAT E
tMatF			equ 05h ;MAT F
tMatG			equ 06h ;MAT G
tMatH			equ 07h ;MAT H
tMatI			equ 08h ;MAT I
tMatJ			equ 09h ;MAT J

;2nd Half Of User List Tokens
;--------------------------------------
tL1			equ 00h ;LIST 1
tL2			equ 01h ;LIST 2
tL3			equ 02h ;LIST 3
tL4			equ 03h ;LIST 4
tL5			equ 04h ;LIST 5
tL6			equ 05h ;LIST 6

;2nd Half Of User Equation Tokens
;----------------------------------
;  "Y" EQUATIONS HAVE BIT 4 SET
;
tY1			equ 10h ;Y1
tY2			equ 11h ;Y2
tY3			equ 12h ;Y3
tY4			equ 13h ;Y4
tY5			equ 14h ;Y5
tY6			equ 15h ;Y6
tY7			equ 16h ;Y7
tY8			equ 17h ;Y8
tY9			equ 18h ;Y9
tY0			equ 19h ;Y0

;Param Equations Have Bit 5 Set
;-----------------------------------
tX1T			equ 20h ;X1t
tY1T			equ 21h ;Y1t
tX2T			equ 22h ;X2t
tY2T			equ 23h ;Y2t
tX3T			equ 24h ;X3t
tY3T			equ 25h ;Y3t
tX4T			equ 26h ;X4t
tY4T			equ 27h ;Y4t
tX5T			equ 28h ;X5t
tY5T			equ 29h ;Y5t
tX6T			equ 2Ah ;X6t
tY6T			equ 2Bh ;Y6t

;Polar Equations Have Bit 6 Set
;----------------------------------
tR1			equ 40h ;R1
tR2			equ 41h ;R2
tR3			equ 42h ;R3
tR4			equ 43h ;R4
tR5			equ 44h ;R5
tR6			equ 45h ;R6

;Recursion Equations Have Bit 7 Set
;----------------------------------
tun			equ 80h ;Un
tvn			equ 81h ;Vn
twn			equ 82h ;Wn

;2nd Half User Picture Tokens
;------------------------------------
tPic1			equ 00h ;PIC1
tPic2			equ 01h ;PIC2
tPic3			equ 02h ;PIC3
tPic4			equ 03h ;PIC4
tPic5			equ 04h ;PIC5
tPic6			equ 05h ;PIC6
tPic7			equ 06h ;PIC7
tPic8			equ 07h ;PIC8
tPic9			equ 08h ;PIC9
tPic0			equ 09h ;PIC0

;2nd Half User Graph Database Tokens
;------------------------------------
tGDB1			equ 00h ;GDB1
tGDB2			equ 01h ;GDB2
tGDB3			equ 02h ;GDB3
tGDB4			equ 03h ;GDB4
tGDB5			equ 04h ;GDB5
tGDB6			equ 05h ;GDB6
tGDB7			equ 06h ;GDB7
tGDB8			equ 07h ;GDB8
tGDB9			equ 08h ;GDB9
tGDB0			equ 09h ;GDB0

;2nd Half Of String Vars
;------------------------------
tStr1			equ 00h
tStr2			equ 01h
tStr3			equ 02h
tStr4			equ 03h
tStr5			equ 04h
tStr6			equ 05h
tStr7			equ 06h
tStr8			equ 07h
tStr9			equ 08h
tStr0			equ 09h

;2nd Half Of System Output Only Variables
;----------------------------------------------------------------
;OPEN			equ 00h
tRegEq			equ 01h ;REGRESSION EQUATION
tStatN			equ 02h ;STATISTICS N
tXMean			equ 03h ;X MEAN
tSumX			equ 04h ;SUM(X)
tSumXSqr		equ 05h ;SUM(X^2)
tStdX			equ 06h ;STANDARD DEV X
tStdPX			equ 07h ;STANDARD DEV POP X
tMinX			equ 08h ;Min X VALUE
tMaxX			equ 09h ;Max X VALUE
tMinY			equ 0Ah ;Min Y VALUE
tMaxY			equ 0Bh ;Max Y VALUE
tYmean			equ 0Ch ;Y MEAN
tSumY			equ 0Dh ;SUM(Y)
tSumYSqr		equ 0Eh ;SUM(Y^2)
tStdY			equ 0Fh ;STANDARD DEV Y
tStdPY			equ 10h ;STANDARD DEV POP Y
tSumXY			equ 11h ;SUM(XY)
tCorr			equ 12h ;CORRELATION
tMedX			equ 13h ;MED(X)
tQ1			equ 14h ;1ST QUADRANT OF X
tQ3			equ 15h ;3RD QUADRANT OF X
tQuadA			equ 16h ;1ST TERM OF QUAD POLY REG/ Y-INT
tQuadB			equ 17h ;2ND TERM OF QUAD POLY REG/ SLOPE
tQuadC			equ 18h ;3RD TERM OF QUAD POLY REG
tCubeD			equ 19h ;4TH TERM OF CUBIC POLY REG
tQuartE			equ 1Ah ;5TH TERM OF QUART POLY REG
tMedX1			equ 1Bh ;x1 FOR MED-MED
tMedX2			equ 1Ch ;x2 FOR MED-MED
tMedX3			equ 1Dh ;x3 FOR MED-MED
tMedY1			equ 1Eh ;y1 FOR MED-MED
tMedY2			equ 1Fh ;y2 FOR MED-MED
tMedY3			equ 20h ;y3 FOR MED-MED
tRecurn			equ 21h	;RECURSION N
tStatP			equ 22h
tStatZ			equ 23h
tStatT			equ 24h
tStatChi		equ 25h
tStatF			equ 26h
tStatDF			equ 27h
tStatPhat		equ 28h
tStatPhat1		equ 29h
tStatPhat2		equ 2Ah
tStatMeanX1		equ 2Bh
tStatStdX1		equ 2Ch
tStatN1			equ 2Dh
tStatMeanX2		equ 2Eh
tStatStdX2		equ 2Fh
tStatN2			equ 30h
tStatStdXP		equ 31h
tStatLower		equ 32h
tStatUpper		equ 33h
tStat_s			equ 34h
tLRSqr			equ 35h ;r^2
tBRSqr			equ 36h ;R^2

;These next tokens are only used to access the data
;they are display only and the user cannot access them at all
;------------------------------------------------------------
tF_DF			equ 37h ;ANOFAV FACTOR DF
tF_SS			equ 38h ;ANOFAV FACTOR SS
tF_MS			equ 39h ;ANOFAV FACTOR MS
tE_DF			equ 3Ah ;ANOFAV ERROR DF
tE_SS			equ 3Bh ;ANOFAV ERROR SS
tE_MS			equ 3Ch ;ANOFAV ERROR MS

;2nd Half Of System Input/Output Variables
;------------------------------------------------
;		SYSTEM VARIABLE EQUATES
;
tuXscl			equ 0
tuYscl			equ 1
tXscl			equ 2
tYscl			equ 3
tRecuru0		equ 4 ;U 1ST INITIAL COND
tRecurv0		equ 5 ;V 1ST INITIAL COND
tun1			equ 6 ;U(N-1); NOT USED
tvn1			equ 7 ;V(N-1); NOT USED
tuRecuru0		equ 8 ;
tuRecurv0		equ 9 ;
tXmin			equ 0Ah
tXmax			equ 0Bh
tYmin			equ 0Ch
tYmax			equ 0Dh
tTmin			equ 0Eh
tTmax			equ 0Fh
tThetaMin		equ 10h
tThetaMax		equ 11h
tuXmin			equ 12h
tuXmax			equ 13h
tuYmin			equ 14h
tuYmax			equ 15h
tuThetMin		equ 16h
tuThetMax		equ 17h
tuTmin			equ 18h
tuTmax			equ 19h
tTblMin			equ 1Ah
tPlotStart		equ 1Bh
tuPlotStart		equ 1Ch
tnMax			equ 1Dh
tunMax			equ 1Eh
tnMin			equ 1Fh
tunMin			equ 20h
tTblStep		equ 21h
tTStep			equ 22h
tThetaStep		equ 23h
tuTStep			equ 24h
tuThetStep		equ 25h
tDeltaX			equ 26h
tDeltaY			equ 27h
tXFact			equ 28h
tYFact			equ 29h
tTblInput		equ 2Ah
tFinN			equ 2Bh
tFinI			equ 2Ch
tFinPV			equ 2Dh
tFinPMT			equ 2Eh
tFinFV			equ 2Fh
tFinPY			equ 30h
tFinCY			equ 31h
tRecurw0		equ 32h ;w0(1)
tuRecurw0		equ 33h
tPlotStep		equ 34h
tuPlotStep		equ 35h
tXres			equ 36h
tuXres			equ 37h
tRecuru02		equ 38h ;u0(2)
tuRecuru02		equ 39h
tRecurv02		equ 3Ch ;v0(2)
tuRecurv02		equ 3Dh
tRecurw02		equ 3Eh ;w0(2)
tuRecurw02		equ 3Fh

;2nd Byte Of t2ByteTok Tokens
;------------------------------
tFinNPV			equ 00h
tFinIRR			equ 01h
tFinBAL			equ 02h
tFinPRN			equ 03h
tFinINT			equ 04h
tFinToNom		equ 05h
tFinToEff		equ 06h
tFinDBD			equ 07h
tLCM			equ 08h
tGCD			equ 09h
tRandInt		equ 0Ah
tRandBin		equ 0Bh
tSubStrng		equ 0Ch
tStdDev			equ 0Dh
tVariance		equ 0Eh
tInStrng		equ 0Fh
tDNormal		equ 10h
tInvNorm		equ 11h
tDT			equ 12h
tChI			equ 13h
tDF			equ 14h
tBINPDF			equ 15h
tBINCDF			equ 16h
tPOIPDF			equ 17h
tPOICDF			equ 18h
tGEOPDF			equ 19h
tGEOCDF			equ 1Ah
tNormalPDF		equ 1Bh
tTPDF			equ 1Ch
tChiPDF			equ 1Dh
tFPDF			equ 1Eh
tRandNorm		equ 1Fh
tFinFPMT		equ 20h
tFinFI			equ 21h
tFinFPV			equ 22h
tFinFN			equ 23h
tFinFFV			equ 24h
tConj			equ 25h
tReal			equ 26h
tImag			equ 27h
tAngle			equ 28h
tCumSum			equ 29h
tExpr			equ 2Ah
tLength			equ 2Bh
tDeltaLst		equ 2Ch
tRef			equ 2Dh
tRRef			equ 2Eh
tToRect			equ 2Fh
tToPolar		equ 30h
tConste			equ 31h
tSinReg			equ 32h
tLogistic		equ 33h
tLinRegTTest		equ 34h
tShadeNorm		equ 35h
tShadeT			equ 36h
tShadeChi		equ 37h
tShadeF			equ 38h
tMatToLst		equ 39h
tLstToMat		equ 3Ah
tZTest			equ 3Bh
tTTest			equ 3Ch
t2SampZTest		equ 3Dh
t1PropZTest		equ 3Eh
t2PropZTest		equ 3Fh
tChiTest		equ 40h
tZIntVal		equ 41h
t2SampZInt		equ 42h
t1PropZInt		equ 43h
t2PropZInt		equ 44h
tGraphStyle		equ 45h
t2SampTTest		equ 46h
t2SampFTest		equ 47h
tTIntVal		equ 48h
t2SampTInt		equ 49h
tSetupLst		equ 4Ah
tFinPMTend		equ 4Bh
tFinPMTbeg		equ 4Ch
tRealM			equ 4Dh
tPolarM			equ 4Eh
tRectM			equ 4Fh
tExprOn			equ 50h
tExprOff		equ 51h
tClrAllLst		equ 52h
tGetCalc		equ 53h
tDelVar			equ 54h
tEquToStrng		equ 55h
tStrngToequ 		equ 56h
tDelLast		equ 57h
tSelect			equ 58h
tANOVA			equ 59h
tModBox			equ 5Ah
tNormProb		equ 5Bh
tMGT			equ 64h ;VERTICAL SPLIT
tZFit			equ 65h ;ZOOM FIT
tDiag_on		equ 66h ;DIANOSTIC DISPLAY ON
tDiag_off		equ 67h ;DIANOSTIC DISPLAY OFF
tOkEnd2v0		equ 67h ;end of 2byte tokens for version 0.
tArchive		equ 68h ;archive
tUnarchive		equ 69h ;unarchive
tasm			equ 6Ah
tasmComp		equ 6Bh	;asm compile
tasmPrgm		equ 6Ch	;Signifies a program is asm
tasmCmp			equ 6Dh	;asm program is compiled
tLcapAAcute		equ 6Eh
tLcapAGrave		equ 6Fh
tLcapACaret		equ 70h
tLcapADier		equ 71h
tLaAcute		equ 72h
tLaGrave		equ 73h
tLaCaret		equ 74h
tLaDier			equ 75h
tLcapEAcute		equ 76h
tLcapEGrave		equ 77h
tLcapECaret		equ 78h
tLcapEDier		equ 79h
tLeAcute		equ 7Ah
tLeGrave		equ 7Bh
tLeCaret		equ 7Ch
tLeDier			equ 7Dh
tLcapIGrave		equ 7Fh
tLcapICaret		equ 80h
tLcapIDier		equ 81h
tLiAcute		equ 82h
tLiGrave		equ 83h
tLiCaret		equ 84h
tLiDier			equ 85h
tLcapOAcute		equ 86h
tLcapOGrave		equ 87h
tLcapOCaret		equ 88h
tLcapODier		equ 89h
tLoAcute		equ 8Ah
tLoGrave		equ 8Bh
tLoCaret		equ 8Ch
tLoDier			equ 8Dh
tLcapUAcute		equ 8Eh
tLcapUGrave		equ 8Fh
tLcapUCaret		equ 90h
tLcapUDier		equ 91h
tLuAcute		equ 92h
tLuGrave		equ 93h
tLuCaret		equ 94h
tLuDier			equ 95h
tLcapCCed		equ 96h
tLcCed			equ 97h
tLcapNTilde		equ 98h
tLnTilde		equ 99h
tLaccent		equ 9Ah
tLgrave			equ 9Bh
tLdieresis		equ 9Ch
tLquesDown		equ 9Dh
tLexclamDown		equ 9Eh
tLalpha			equ 9Fh
tLbeta			equ 0A0h
tLgamma			equ 0A1h
tLcapDelta		equ 0A2h
tLdelta			equ 0A3h
tLepsilon		equ 0A4h
tLlambda		equ 0A5h
tLmu			equ 0A6h
tLpi			equ 0A7h
tLrho			equ 0A8h
tLcapSigma		equ 0A9h
tLphi			equ 0ABh
tLcapOmega		equ 0ACh
tLphat			equ 0ADh
tLchi			equ 0AEh
tLstatF			equ 0AFh
tLa			equ 0B0h
tLb			equ 0B1h
tLc			equ 0B2h
tLd			equ 0B3h
tLsmalle		equ 0B4h
tLf			equ 0B5h
tLsmallg		equ 0B6h
tLh			equ 0B7h
tLi			equ 0B8h
tLj			equ 0B9h
tLk			equ 0BAh
tLl			equ 0BCh
tLm			equ 0BDh
tLsmalln		equ 0BEh
tLo			equ 0BFh
tLp			equ 0C0h
tLq			equ 0C1h
tLsmallr		equ 0C2h
tLs			equ 0C3h
tLsmallt		equ 0C4h
tLu			equ 0C5h
tLv			equ 0C6h
tLw			equ 0C7h
tLx			equ 0C8h
tLy			equ 0C9h
tLz			equ 0CAh
tLsigma			equ 0CBh
tLtau			equ 0CCh
tLcapIAcute		equ 0CDh
tGarbagec		equ 0CEh
LastToken		equ 0CEh ;tLAST TOKEN IN THIS VERSION...

;Data Type Equates
;---------------------------------------------------------------------
RealObj			equ 0
ListObj			equ 1
MatObj			equ 2
EquObj			equ 3
StrngObj		equ 4
ProgObj			equ 5
ProtProgObj		equ 6
PictObj			equ 7
GDBObj			equ 8
UnknownObj		equ 9
UnknownEquObj		equ 0Ah
NewEquObj		equ 0Bh
CplxObj			equ 0Ch
CListObj		equ 0Dh
UndefObj		equ 0Eh
WindowObj		equ 0Fh
ZStoObj			equ 10h
TblRngObj		equ 11h
LCDObj			equ 12h
BackupObj		equ 13h
AppObj			equ 14h	;application, only used in menus/link
AppVarObj		equ 15h	;application variable
TempProgObj		equ 16h ;program, home deletes when finished
GroupObj		equ 17h ;group.

;System Error Codes
;-----------------------------------------------------------
E_EDITF			equ 7 ;allow re-entering application
E_EDIT			equ 1<<E_EDITF
E_Mask			equ 7Fh
E_Overflow		equ 1+E_EDIT
E_DivBy0		equ 2+E_EDIT
E_SingularMat		equ 3+E_EDIT
E_Domain		equ 4+E_EDIT
E_Increment		equ 5+E_EDIT
E_Break			equ 6+E_EDIT
E_NonReal		equ 7+E_EDIT
E_Syntax		equ 8+E_EDIT
E_DataType		equ 9+E_EDIT
E_Argument		equ 10+E_EDIT
E_DimMismatch		equ 11+E_EDIT
E_Dimension		equ 12+E_EDIT
E_Undefined		equ 13+E_EDIT
E_Memory		equ 14+E_EDIT		; 142
E_Invalid		equ 15+E_EDIT		; 143
E_IllegalNest		equ 16+E_EDIT		; 144
E_Bound			equ 17+E_EDIT		; 145
E_GraphRange		equ 18+E_EDIT		; 146
E_Zoom			equ 19+E_EDIT		; 147
E_Label			equ 20			; 148
E_Stat			equ 21			; 149
E_Solver		equ 22+E_EDIT
E_Singularity		equ 23+E_EDIT
E_SignChange		equ 24+E_EDIT
E_Iterations		equ 25+E_EDIT
E_BadGuess		equ 26+E_EDIT
E_StatPlo		equ 27
E_TolTooSmall		equ 28+E_EDIT
E_Reserved		equ 29+E_EDIT
E_Mode			equ 30+E_EDIT
E_LnkErr		equ 31+E_EDIT
E_LnkMemErr		equ 32+E_EDIT
E_LnkTransErr		equ 33+E_EDIT
E_LnkDupErr		equ 34+E_EDIT
E_LnkMemFull		equ 35+E_EDIT
E_Unknown		equ 36+E_EDIT
E_Scale			equ 37+E_EDIT
E_IdNotFound		equ 38
E_NoMode		equ 39+E_EDIT
E_Validation		equ 40
E_Length		equ 41+E_EDIT
E_Application		equ 42+E_EDIT
E_AppErr1		equ 43+E_EDIT
E_AppErr2		equ 44+E_EDIT
E_ExpiredApp		equ 45
E_BadAdd		equ 46
E_Archived		equ 47+E_EDIT
E_Version		equ 48
E_ArchFull		equ 49
E_Variable		equ 50+E_EDIT
E_Duplicate		equ 51+E_EDIT

;System Variable Equates
;------------------------------
XSCLt			equ 02h
YSCLt			equ 03h
XMINt			equ 0Ah
XMAXt			equ 0Bh
YMINt			equ 0Ch
YMAXt			equ 0Dh
TMINt			equ 0Eh
TMAXt			equ 0Fh
THETMINt		equ 10h
THETMAXt		equ 11h
TBLMINt			equ 1Ah
PLOTSTARTt		equ 1Bh
NMAXt			equ 1Dh
NMINt			equ 1Fh
TBLSTEPt		equ 21h
TSTEPt			equ 22h
THETSTEPt		equ 23h
DELTAXt			equ 26h
DELTAYt			equ 27h
XFACTt			equ 28h
YFACTt			equ 29h
FINNt			equ 2Bh
FINIt			equ 2Ch
FINPVt			equ 2Dh
FINPMTt			equ 2Eh
FINFVt			equ 2Fh
FINPYt			equ 30h
FINCYt			equ 31h
PLOTSTEPt		equ 34h
XRESt			equ 36h

;Equates To RAM Locations For Stat Vars
;----------------------------------------------------------------
FPLEN			equ 9 ;Length of a floating-point number.
StatN			equ statVars
XMean			equ StatN + FPLEN
SumX			equ XMean + FPLEN
SumXSqr			equ SumX + FPLEN
StdX			equ SumXSqr + FPLEN
StdPX			equ StdX + FPLEN
MinX			equ StdPX + FPLEN
MaxX			equ MinX + FPLEN
MinY			equ MaxX + FPLEN
MaxY			equ MinY + FPLEN
YMean			equ MaxY + FPLEN
SumY			equ YMean + FPLEN
SumYSqr			equ SumY + FPLEN
StdY			equ SumYSqr + FPLEN
StdPY			equ StdY + FPLEN
SumXY			equ StdPY + FPLEN
Corr			equ SumXY + FPLEN
MedX			equ Corr + FPLEN
Q1			equ MedX + FPLEN
Q3			equ Q1 + FPLEN
QuadA			equ Q3 + FPLEN
QuadB			equ QuadA + FPLEN
QuadC			equ QuadB + FPLEN
CubeD			equ QuadC + FPLEN
QuartE			equ CubeD + FPLEN
MedX1			equ QuartE + FPLEN
MedX2			equ MedX1 + FPLEN
MedX3			equ MedX2 + FPLEN
MedY1			equ MedX3 + FPLEN
MedY2			equ MedY1 + FPLEN
MedY3			equ MedY2 + FPLEN
PStat			equ MedY3 + (2*FPLEN)
ZStat			equ PStat + FPLEN
TStat			equ ZStat + FPLEN
ChiStat			equ TStat + FPLEN
FStat			equ ChiStat + FPLEN
DF			equ FStat + FPLEN
Phat			equ DF + FPLEN
Phat1			equ Phat + FPLEN
Phat2			equ Phat1 + FPLEN
MeanX1			equ Phat2 + FPLEN
StdX1			equ MeanX1 + FPLEN
StatN1			equ StdX1 + FPLEN
MeanX2			equ StatN1 + FPLEN
StdX2			equ MeanX2 + FPLEN
StatN2			equ StdX2 + FPLEN
StdXP2			equ StatN2 + FPLEN
SLower			equ StdXP2 + FPLEN
SUpper			equ SLower + FPLEN
SStat			equ SUpper + FPLEN
F_DF			equ anovaf_vars
F_SS			equ F_DF + FPLEN
F_MS			equ F_SS + FPLEN
E_DF			equ F_MS + FPLEN
E_SS			equ E_DF + FPLEN
E_MS			equ E_SS + FPLEN

;System Flags
;----------------------------------------------------------------------
ioDelFlag		equ 0h
inDelete		equ 0		;1 = DELETE SCREEN

trigFlags		equ 0h		;Trigonometry mode settings
trigDeg			equ 2		;1 = degrees, 0=radians

kbdFlags		equ 0h		;Keyboard scan
kbdSCR			equ 3		;1=scan code ready
kbdKeyPress		equ 4		;1=key has been pressed

doneFlags		equ 0h		;display "Done"
donePrgm		equ 5		;1=display "Done" after prgm
;----------------------------------------------------------------------
editFlags		equ 1h
editOpen		equ 2		;1=edit buffer is open

ansFlags		equ 1
AnsScroll		equ 3		;1=answer can scroll, seems must be reset in order to move about edit buffer

monFlags		equ 1h	 	;monitor flags
monAbandon		equ 4		;1=don't start any long process in put away (#715)
;----------------------------------------------------------------------
plotFlags		equ 2h		;plot generation flags
plotLoc 		equ 1		;0=bkup & display, 1=display only
plotDisp		equ 2		;1=plot is in display, 0=text in display, this also indicates whether graph is being shown or not

grfModeFlags		equ 2h		;graph mode settings
grfFuncM		equ 4		;1=function graph
grfPolarM		equ 5		;1=polar graph
grfParamM		equ 6		;1=parametric graph
grfRecurM		equ 7		;1=RECURSION graph
;----------------------------------------------------------------------
graphFlags		equ 3h
graphDraw		equ 0		;0=graph is valid, 1=redraw graph(dirty)
graphCursor		equ 2
;----------------------------------------------------------------------
grfDBFlags		equ 4h
grfDot			equ 0		;0=line, 1=dot
grfSimul		equ 1		;0=sequential, 1=simultaneous
grfGrid 		equ 2		;0=no grid, 1=grid
grfPolar		equ 3		;0=rectangular, 1=polar coordinates
grfNoCoord		equ 4		;0=display coordinates, 1=off
grfNoAxis		equ 5		;0=axis, 1=no axis
grfLabel		equ 6		;0=off, 1=axis label
;----------------------------------------------------------------------
textFlags		equ 5h		;Text output flags
textEraseBelow		equ 1		;1=erase line below small char
textScrolled		equ 2		;1=screen scrolled
textInverse		equ 3		;1=display inverse bit-map
textInsMode		equ 4		;0=overstrike, 1=insert mode
;----------------------------------------------------------------------
ParsFlag		equ 6h		;PARSER flags
listOpen		equ 5		; {...}
matrixOpen1		equ 6		; [[...]]
matrixOpen2		equ 7		; [...]
;----------------------------------------------------------------------
ParsFlag2		equ 7h		;PARSER flags
numOP1			equ 0		;1=RESULT IN OP1, 0=NO RESULT
;----------------------------------------------------------------------
newDispF		equ 8h		;Derivative mode flags
preClrForMode		equ 0		;1=HELP BLINK ON MODE SCREEN
allowProgTokens		equ 1		;1=allow programming tokens to be parsed in BASIC programs
progExecuting		equ 1

apdFlags		equ 8h		;Automatic power-down
apdAble 		equ 2		;1=APD enabled
apdRunning		equ 3		;1=APD clock running
apdWarmStart		equ 4		;1=calculator is turning on from APD or power loss
;----------------------------------------------------------------------
web_err_mask		equ 60h
;----------------------------------------------------------------------
onFlags 		equ 9h		;on key flags
parseInput		equ 1		;1=parse input when done
onRunning		equ 3		;1=calculator is running
onInterrupt		equ 4		;1=on key interrupt request

statFlags		equ 9h		;statistics flags
;unknown		equ 5		;unknown
statsValid		equ 6		;1=stats are valid
;unknown		equ 7		;unknown
;----------------------------------------------------------------------
fmtFlags		equ 0Ah		;numeric format flags
fmtExponent		equ 0	 	;1=show exponent, 0=no exponent
fmtEng			equ 1	 	;1=engineering notion, 0=scientific

numMode			equ 0Ah
fmtReal			equ 5
fmtRect			equ 6
fmtPolar		equ 7

realMode		equ 5
rectMode		equ 6
polarMode		equ 7

fmtBaseMask		equ  00011100b	; mask to base flags
fmtBaseShift		equ  2		; offset to base flags
;----------------------------------------------------------------------
fmtOverride		equ 0Bh		;copy of fmtFlags with conversion override
;----------------------------------------------------------------------
fmtEditFlags		equ 0Ch		;numeric editing flags
fmtEdit			equ 0		;1=format number for editing

curFlags		equ 0Ch		;Cursor
curAble 		equ 2		;1=cursor flash is enabled
curOn			equ 3		;1=cursor is showing
curLock 		equ 4		;1=cursor is locked off

cmdFlags		equ 0Ch		;command editor flags
cmdVirgin		equ 5		;1=nothing has been typed in cmd bfr
cmdExec			equ 6           ;1=need to execute a command
;----------------------------------------------------------------------
appFlags		equ 0Dh		;application flags
appWantIntrpt		equ 0		;1=want ON key interrupts
appTextSave		equ 1		;1=save characters in textShadow
appAutoScroll		equ 2		;1=auto-scroll text on last line
appMenus		equ 3		;1=process keys that bring up menus, 0=check Lock menu flag
appLockMenus		equ 4		;1=ignore menu keys, 0=switch to home screen and bring up menu
appCurGraphic		equ 5		;1=graphic cursor
appCurWord		equ 6		;1=text cursor covers entire word
appExit 		equ 7		;1=application handles [EXIT] key itself

appWantIntrptF		equ 1<<appWantIntrpt
appTextSaveF		equ 1<<appTextSave
appAutoScrollF		equ 1<<appAutoScroll
appMenusF		equ 1<<appMenus
appLockMenusF		equ 1<<appLockMenus
appCurGraphicF		equ 1<<appCurGraphic
appCurWordF		equ 1<<appCurWord
appExitF		equ 1<<appExit
;----------------------------------------------------------------------
rclFlag			equ 0Eh		;OS recall queue flags
enableQueue		equ 7		;1 = enable recall queue
;----------------------------------------------------------------------
seqFlags		equ 0Fh		;Sequential Graph flags
webMode			equ 0		;0 = NORMAL SEQ MODE, 1 = WEB MODE
webVert			equ 1
sequv			equ 2		;U vs V
seqvw			equ 3		;V vs W
sequw			equ 4		;U vs W
;----------------------------------------------------------------------
promptFlags		equ 11h		;prompt line flags
promptEdit		equ 0		;1=editing in prompt buffer
;unknown		equ 7		;unknown
;----------------------------------------------------------------------
indicFlags		equ 12h		;Indicator flags
indicRun		equ 0		;1=run indicator ON
indicInUse		equ 1		;indicator save area in use=1, free=0 ;resetting will disable 2nd while in _getkey

shiftFlags		equ 12h		;[2nd] and [ALPHA] flags
shift2nd		equ 3		;1=[2nd] has been pressed
shiftAlpha		equ 4		;1=[ALPHA] has been pressed
shiftLwrAlph		equ 5		;1=lower case, 0=upper case
shiftALock		equ 6		;1=alpha lock has been pressed
shiftKeepAlph		equ 7		;1=cannot cancel alpha shift
;----------------------------------------------------------------------
tblFlags		equ 13h		;table flags.
autoFill		equ 4		;1=prompt, 0=fillAuto
autoCalc		equ 5		;1=prompt, 0=CalcAuto
reTable			equ 6		;0=table is okay, 1=must recompute table.
;----------------------------------------------------------------------
sGrFlags		equ 14h
grfSplit		equ 0		;1=Split Graph, 0=Normal
vertSplit		equ 1		;1=Vertical (left-right) Split
grfSChanged		equ 2		;1=Graph just changed Split <-> normal
grfSplitOverride	equ 3		;1 = ignore graph split flag if set
write_on_graph		equ 4		;1 = TEXT OR EQU WRITING TO GRAPH SCREEN
g_style_active		equ 5		;1 = GRAPH STYLES ARE ENABLED, USE THEM
cmp_mod_box		equ 6		;1 = DOING MOD BOX PLOT COMPUTATION
textWrite		equ 7
;----------------------------------------------------------------------
newIndicFlags		equ 15h
extraIndic		equ 0
saIndic			equ 1
;3 has something to do with stat/list editor
;----------------------------------------------------------------------
interruptFlags		equ 16h
secondTimerEnabled	equ 0		;1 = second hardware timer enabled
;----------------------------------------------------------------------
smartFlags		equ 17h
smarter_mask		equ 3
smarter_test		equ 1
smartGraph		equ 0
smartGraph_inv		equ 1
;----------------------------------------------------------------------
traceFlags		equ 18h
grfExpr			equ 0		;set to hide expression while tracing
;----------------------------------------------------------------------
;There is a flag 19h.
;----------------------------------------------------------------------
statFlags2		equ 1Ah
statDiagnosticsOn	equ 0		;1 = stat diagnostics on
noDelStat		equ 2		;1 = don't delete stats
;----------------------------------------------------------------------
apdFlags2		equ 1Bh
warmStartInt		equ 6           ;1 = a warm start is occurning before the next interrupt
;----------------------------------------------------------------------
;There is a flag 1Ch (stats-related).
;----------------------------------------------------------------------
;There is a flag 1Dh.
;----------------------------------------------------------------------
;There is a flag 1Eh.
;----------------------------------------------------------------------
varTypeMask		equ 1Fh		;is this a flag byte? yes
varGraphRef		equ 6
;----------------------------------------------------------------------
graphFlags2		equ 1Fh
splitOverride		equ 3		;0 = force full screen with ParseInp, or something
;----------------------------------------------------------------------
asm_Flag1		equ 21h		;ASM CODING
asm_Flag2		equ 22h		;ASM CODING
asm_Flag3		equ 23h		;NO LONGER AVAILABLE
;----------------------------------------------------------------------
arcFlag			equ 24h
checkBatteryLevelFirst	equ 0		;1 = check battery levels in Arc_Unarc first and throw error if low

getSendFlg		equ 24h
comFailed		equ 1		;1 = Get/Send Communication Failed

selfTestFlag		equ 24h
resetOnPowerOn		equ 2		;1 = Force RAM reset when APD disabled on next power on

appLwrCaseFlag		equ 24h
lwrCaseActive		equ 3
;----------------------------------------------------------------------
contextFlags		equ 25h
nocxPutAway		equ 5		;1 = do not call cxPutAway routine
;----------------------------------------------------------------------
groupFlags		equ 26h		;used temporarily in Arc_Unarc
inGroup			equ 1		;1 = IN GROUP CONTEXT
noCompletionByte	equ 2		;1 = do not write 0FCh when calling Arc_Unarc, leave as 0FEh
noDataWrite		equ 3		;1 = do not write data when calling Arc_Unarc, nor size bytes
writeSizeBytesOnly	equ 5		;1 = only write size bytes when calling Arc_Unarc
;----------------------------------------------------------------------
statusBarFlags		equ 27h
noStatusBarMode		equ 7		; 1 = abort drawing of statusbar mode, like "TEST MODE ENABLED"
;----------------------------------------------------------------------
APIFlg			equ 28h
appAllowContext		equ 0           ;app wants context changes to happen

appRunning		equ 4		;app is currently running
appRetKeyOff		equ 7		;1 = GetKey returns kOff when [2nd]+[ON] pressed
;----------------------------------------------------------------------
apiFlg2			equ 29h
;----------------------------------------------------------------------
apiFlg3			equ 2Ah
;----------------------------------------------------------------------
apiFlg4			equ 2Bh
cellOverride		equ 1		;use cell override
fullScrnDraw		equ 2		;DRAW INTO LAST ROW/COL OF SCREEN
;----------------------------------------------------------------------
xapFlag0		equ 2Eh		;external app flags, do not use 0,(iy+2Eh) (used by mouse routines)
xapFlag1		equ 2Fh
xapFlag2		equ 30h
xapFlag3		equ 31h
;----------------------------------------------------------------------
fontFlags		equ 32h
fracDrawLFont		equ 2
fracTallLFont		equ 3
customFont		equ 7
;----------------------------------------------------------------------
hookflags1		equ 33h		;also scriptFlag, rclFlag2, backGroundLink
alt_On			equ 0		;run ONSCRPT at startup
alt_Off			equ 1		;run OFFSCRPT at shutdown
useRclQueueEnd		equ 2		;1 = external mode
ignoreBPLink		equ 3		;1 = override flag for link activity hook
bPLinkOn		equ 4		;1 = link activity hook active
enableKeyEcho		equ 5		;1 = sends keypresses back to connected calc as remote control packets (with GetCSC vs. GetKey codes...really dumb, TI)
noTempDelete		equ 6		;1 = do not delete temporary programs at homescreen
;----------------------------------------------------------------------
hookflags2		equ 34h		;also sysHookFlg
getCSCHookActive	equ 0		;1 = GetCSC hook active
libraryHookActive	equ 1		;1 = library hook active
noHookActive		equ 2		;1 = same as 0; never used by OS
homescreenHookActive	equ 4		;1 = homescreen hook active
rawKeyHookActive	equ 5		;1 = raw key hook active
catalog2HookActive	equ 6		;1 = catalog 2 hook active
cursorHookActive	equ 7		;1 = cursor hook active
;----------------------------------------------------------------------
hookflags3		equ 35h		;also sysHookFlg1
tokenHookActive		equ 0		;1 = token hook active
localizeHookActive	equ 1		;1 = localize hook active
windowHookActive	equ 2		;1 = window hook active
graphHookActive		equ 3		;1 = graph hook active
yEquHookActive		equ 4		;1 = Y= hook active
fontHookActive		equ 5		;1 = font hook active
regraphHookActive	equ 6		;1 = regraph hook active
drawingHookActive	equ 7		;1 = drawing hook active
;----------------------------------------------------------------------
hookflags4		equ 36h		;also sysHookFlag2
traceHookActive		equ 0		;1 = trace hook active
parserHookActive	equ 1		;1 = parser hook active
appChangeHookActive	equ 2		;1 = app change hook active
catalog1HookActive	equ 3		;1 = catalog 1 hook active
helpHookActive		equ 4		;1 = help hook active
cxRedispHookActive	equ 5		;1 = cxRedisp hook active
menuHookActive		equ 6		;1 = menu hook active
silentLinkHookActive	equ 7		;1 = silent link hook active
;----------------------------------------------------------------------
;hookflags2Override	equ 37h		;set corresponding bit to kill iy+35h hook when executing app
;----------------------------------------------------------------------
;hookflags3Override	equ 38h		;set corresponding bit to kill iy+36h hook when executing app
;----------------------------------------------------------------------
;hookflags4Override	equ 39h		;set corresponding bit to kill iy+37h hook when executing app
;----------------------------------------------------------------------
hookflags5		equ 3Ah
usbActivityHookActive	equ 0		;1 = USB activity hook active
;----------------------------------------------------------------------
plotFlag3		equ 3Ch
bufferOnly		equ 0
useFastCirc		equ 4
;----------------------------------------------------------------------
dBKeyFlags		equ 3Dh
keyDefaultsF		equ 6		;1 = GetKey returns extended keycodes with TI-Keyboard
;----------------------------------------------------------------------
silentLinkFlags		equ 3Eh
silentLinkActive	equ 0		;1 = SE/84+ silent link is active

extraHookFlags		equ 3Eh
checkCatalog2HookVer	equ 3		;1 = check catalog 2 hook's version before executing it (and error or take other action if so)
openLibActive		equ 4		;1 = OpenLib( was successfully called on a Flash application (ExecLib will error if zero)
;----------------------------------------------------------------------
clockFlags		equ 3Fh
notMDYMode		equ 0		;0 = M/D/Y format
isYMDMode		equ 1		;1 = Y/M/D format
is24Hour		equ 2		;1 = clock in 24 hour mode
inAfternoon		equ 3		;1 = current time is in afternoon (PM) (I think)
useTokensInString	equ 4		;1 = use tokens instead of characters when displaying clock as string (for getTmStr and getDtStr vs. MODE screen) (keep this reset)
displayClock		equ 5		;1 = display clock (this is set every second, reset otherwise)
clockOn			equ 6		;1 = clock on
;----------------------------------------------------------------------
mathprintFlags		equ 44h
mathprintEnabled	equ 5		;1 = use mathprint styling
;----------------------------------------------------------------------
InitialBootMenuFlags	equ 45h
dispinitialBootMenu	equ 4		; 1 = don't display the initial boot menu
;----------------------------------------------------------------------
backlightFlags		equ 46h
restoreBrightness	equ 0		;1 = restore lcd brightness when needed
;----------------------------------------------------------------------
grFlags			equ 4Ah
drawGrLbls		equ 0		;1 = don't draw Graph Labels (this is usually reset anyway)

putMapFlags		equ 4Ah
usePixelShadow2		equ 3		;1 = use pixelshadow2, not pixelshadow
putMapUseColor		equ 4		;1 = use custom color
;----------------------------------------------------------------------
graphDispFlags		equ 4Bh
backgroundValid		equ 4		;1 = items in graph background are still valid
;----------------------------------------------------------------------
#endif
.list
