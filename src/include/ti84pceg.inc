define ti? ti
namespace ti?
;TI-84 Plus CE Include File

;Various Parts Contributed by
;- BrandonW
;- calc84
;- MateoConLechuga
;- Runer112
;- tr1p1ea
;- Kerm Martian
;- Texas Instruments (ti83plus.inc)





; Included for Assembler Compatibility
;------------------------------------





; Hardware Defines
;------------------------------
?lcdWidth		:= 320
?lcdHeight		:= 240

; System Calls
; Jump Table located at 020104h
;--------------------------------
?OSSize                    := 0020104h ; not a routine; jump location is end of OS
?BootOS	                   := 0020108h
?InterruptHandler          := 002010Ch
?Rst10Handler              := 0020110h
?Rst18Handler              := 0020114h
?Rst20Handler              := 0020118h
?Rst28Handler              := 002011Ch
?Rst30Handler              := 0020120h
;                          equ 0020124h
;                          equ 0020128h
?JErrorNo                  := 002012Ch
?CallFontHook              := 0020130h
?CallLocalizeHook          := 0020134h
?LoadHLInd_s               := 0020138h
?CpHLDE                    := 002013Ch
?DivHLBy10_s               := 0020140h
?DivHLByA_s                := 0020144h
?KbdScan                   := 0020148h
?GetCSC                    := 002014Ch
?CoorMon                   := 0020150h
?Mon                       := 0020154h
?MonForceKey               := 0020158h
?SendKPress                := 002015Ch
?JForceCmdNoChar           := 0020160h
?JForceCmd                 := 0020164h
?SysErrHandler             := 0020168h
?NewContext                := 002016Ch
?NewContext0               := 0020170h
?PPutawayPrompt            := 0020174h
?PPutAway                  := 0020178h
?PutAway                   := 002017Ch
?SizeWind                  := 0020180h
?ErrorEP                   := 0020184h
?CallMain                  := 0020188h
?MonErrHand                := 002018Ch
?AppInit                   := 0020190h
?Initialize                := 0020194h
?Min                       := 0020198h
?Max                       := 002019Ch
?AbsO1PAbsO2               := 00201A0h
?Intgr                     := 00201A4h
?TRunc                     := 00201A8h
?InvSub                    := 00201ACh
?Times2                    := 00201B0h
?Plus1                     := 00201B4h
?Minus1                    := 00201B8h
?FPSub                     := 00201BCh
?FPAdd                     := 00201C0h
?DToR                      := 00201C4h
?RToD                      := 00201C8h
?Cube                      := 00201CCh
?TimesPT5                  := 00201D0h
?FPSquare                  := 00201D4h
?FPMult                    := 00201D8h
?LJRnd                     := 00201DCh
?InvOP1Sc                  := 00201E0h
?InvOP1S                   := 00201E4h
?InvOP2S                   := 00201E8h
?Frac                      := 00201ECh
?FPRecip                   := 00201F0h
?FPDiv                     := 00201F4h
?SqRoot                    := 00201F8h
?RndGuard                  := 00201FCh
?Rnfx                      := 0020200h
?Int                       := 0020204h
?Round                     := 0020208h
?LnX                       := 002020Ch
?LogX                      := 0020210h
?LJNoRnd                   := 0020214h
?EToX                      := 0020218h
?TenX                      := 002021Ch
?SinCosRad                 := 0020220h
?Sin                       := 0020224h
?Cos                       := 0020228h
?Tan                       := 002022Ch
?SinhCosh                  := 0020230h
?Tanh                      := 0020234h
?Cosh                      := 0020238h
?Sinh                      := 002023Ch
?ACosRad                   := 0020240h
?ATanRad                   := 0020244h
?ATan2Rad                  := 0020248h
?ASinRad                   := 002024Ch
?ACos                      := 0020250h
?ATan                      := 0020254h
?ASin                      := 0020258h
?ATan2                     := 002025Ch
?ATanh                     := 0020260h
?ASinh                     := 0020264h
?ACosh                     := 0020268h
?PToR                      := 002026Ch
?RToP                      := 0020270h
?HLTimes9                  := 0020274h
?CkOP1Cplx                 := 0020278h
?CkOP1Real                 := 002027Ch
?Angle                     := 0020280h
?COP1Set0                  := 0020284h
?Cpop4OP3                  := 0020288h
?Mov9OP2Cp                 := 002028Ch
?AbsO1O2Cp                 := 0020290h
?CpOP1OP2                  := 0020294h
?OP3ToOP4                  := 0020298h
?OP1ToOP4                  := 002029Ch
?OP2ToOP4                  := 00202A0h
?OP4ToOP2                  := 00202A4h
?OP3ToOP2                  := 00202A8h
?OP1ToOP3                  := 00202ACh
?OP5ToOP2                  := 00202B0h
?OP5ToOP6                  := 00202B4h
?OP5ToOP4                  := 00202B8h
?OP1ToOP2                  := 00202BCh
?OP6ToOP2                  := 00202C0h
?OP6ToOP1                  := 00202C4h
?OP4ToOP1                  := 00202C8h
?OP5ToOP1                  := 00202CCh
?OP3ToOP1                  := 00202D0h
?OP6ToOP5                  := 00202D4h
?OP4ToOP5                  := 00202D8h
?OP3ToOP5                  := 00202DCh
?OP2ToOP5                  := 00202E0h
?OP2ToOP6                  := 00202E4h
?OP1ToOP6                  := 00202E8h
?OP1ToOP5                  := 00202ECh
?OP2ToOP1                  := 00202F0h
?Mov11b                    := 00202F4h
?Mov10b                    := 00202F8h
?Mov9b                     := 00202FCh
?Mov9b_                    := 0020300h
?Mov8b                     := 0020304h
?Mov7b                     := 0020308h
?Mov7b_                    := 002030Ch
?OP2ToOP3                  := 0020310h
?OP4ToOP3                  := 0020314h
?OP5ToOP3                  := 0020318h
?OP4ToOP6                  := 002031Ch
?Mov9ToOP1                 := 0020320h
?Mov9OP1OP2                := 0020324h
?Mov9ToOP2                 := 0020328h
?MovFROP1                  := 002032Ch
?OP4Set1                   := 0020330h
?OP3Set1                   := 0020334h
?OP2Set8                   := 0020338h
?OP2Set5                   := 002033Ch
?OP2SetA                   := 0020340h
?OP2Set4                   := 0020344h
?OP2Set3                   := 0020348h
?OP1Set1                   := 002034Ch
?OP1Set4                   := 0020350h
?OP1Set3                   := 0020354h
?OP3Set2                   := 0020358h
?OP1Set2                   := 002035Ch
?OP2Set2                   := 0020360h
?OP2Set1                   := 0020364h
?Zero16D                   := 0020368h
?OP5Set0                   := 002036Ch
?OP4Set0                   := 0020370h
?OP3Set0                   := 0020374h
?OP2Set0                   := 0020378h
?OP1Set0                   := 002037Ch
?SetNum0                   := 0020380h
?ZeroOP1                   := 0020384h
?ZeroOP2                   := 0020388h
?ZeroOP3                   := 002038Ch
?ZeroOP                    := 0020390h
?ClrLP                     := 0020394h
?ShrACC                    := 0020398h
?ShlACC                    := 002039Ch
?Shr18                     := 00203A0h
?Shr18a                    := 00203A4h
?Shr16                     := 00203A8h
?Shr14                     := 00203ACh
?Shl16                     := 00203B0h
?Shl14                     := 00203B4h
?Srdo1                     := 00203B8h
?ShrdRnd                   := 00203BCh
?MantPa                    := 00203C0h
?AddPrOP                   := 00203C4h
?AddPrOPlP                 := 00203C8h
;                          equ 00203CCh
;                          equ 00203D0h
?Sub16d                    := 00203D4h
?Sub14d                    := 00203D8h
?OP2ExOP6                  := 00203DCh
?OP5ExOP6                  := 00203E0h
?OP1ExOP5                  := 00203E4h
?OP1ExOP6                  := 00203E8h
?OP2ExOP4                  := 00203ECh
?OP2ExOP5                  := 00203F0h
?OP1ExOP3                  := 00203F4h
?OP1ExOP4                  := 00203F8h
?OP1ExOP2                  := 00203FCh
?ExLP                      := 0020400h
?CkOP10                    := 0020404h
?CkOP1FP0                  := 0020408h
?CkOP2FP0                  := 002040Ch
?PosNo0Int                 := 0020410h
?CkPosInt                  := 0020414h
?CkInt                     := 0020418h
?CkOdd                     := 002041Ch
?CkOP1EX                   := 0020420h
?GetCon1                   := 0020424h
?GetCon                    := 0020428h
?PiDiv2                    := 002042Ch
?PiDiv4                    := 0020430h
?TwoPi                     := 0020434h
?PiCon                     := 0020438h
?ExpToHex                  := 002043Ch
?OP1ExpToDec               := 0020440h
?CkOP2Pos                  := 0020444h
?CkOP1Pos                  := 0020448h
?ClrOP2S                   := 002044Ch
?ClrOP1S                   := 0020450h
?FDiv100                   := 0020454h
?FDiv10                    := 0020458h
?DecO1Exp                  := 002045Ch
?IncO1exp                  := 0020460h
?IncExp                    := 0020464h
?CkValidNum                := 0020468h
?GetExp                    := 002046Ch
?HtimesL                   := 0020470h
?EOP1NotReal               := 0020474h
?ThetaName                 := 0020478h
?RName                     := 002047Ch
?RegEqName                 := 0020480h
?RecurNName                := 0020484h
?XName                     := 0020488h
?YName                     := 002048Ch
?TName                     := 0020490h
?RealName                  := 0020494h
?SetEStoFPS                := 0020498h
?ChkTempDirt               := 002049Ch
?OP1ExOP2Exp               := 00204A0h
?OP1ExpMinusE              := 00204A4h
?ChkErrBreak               := 00204A8h
?Isa2ByteTok               := 00204ACh
?GetLastEntry              := 00204B0h
?GetLastEntryPtr           := 00204B4h
?RegRclrChng               := 00204B8h
?ResetWinTop               := 00204BCh
?IsO1NonTLstOrProg         := 00204C0h
?IsO1NonTempLst            := 00204C4h
?Is_A_LstOrCLst            := 00204C8h
?Chk_HL_999                := 00204CCh
?Equ_Or_NewEqu             := 00204D0h
?Errd_OP1NotPos            := 00204D4h
?Errd_OP1Not_R             := 00204D8h
?Errd_OP1NotPosInt         := 00204DCh
?Errd_OP1_le_0             := 00204E0h
?Errd_OP1_0                := 00204E4h
?ChkFindSym_Get_Size       := 00204E8h
?Sto_StatVar               := 00204ECh
?Rcl_StatVar               := 00204F0h
?CkOP2Real                 := 00204F4h
?Get_X_Indirect            := 00204F8h
?MemChk                    := 00204FCh
?CmpPrgNamLen1             := 0020500h
?CmpPrgNamLen              := 0020504h
?FindProgSym               := 0020508h
?ChkFindSym                := 002050Ch
?FindSym                   := 0020510h
?InsertMem                 := 0020514h
?InsertMemA                := 0020518h
?EnoughMem                 := 002051Ch
?CmpMemNeed                := 0020520h
?CreatePVar4               := 0020524h
?CreatePVar3               := 0020528h
?CreateVar3                := 002052Ch
?CreateCplx                := 0020530h
?CreateReal                := 0020534h
?CreateTRList              := 0020538h
?CreateRList               := 002053Ch
?CreateTCList              := 0020540h
?CreateCList               := 0020544h
?CreateTRMat               := 0020548h
?CreateRMat                := 002054Ch
?CreateTStrng              := 0020550h
?CreateStrng               := 0020554h
?Create0Equ                := 0020558h
?CreatetEqu                := 002055Ch
?CreateEqu                 := 0020560h
?CreateGDB                 := 0020564h
?CreateProg                := 0020568h
?ChkDel                    := 002056Ch
?ChkDelA                   := 0020570h
?AdjParser                 := 0020574h
?AdjMath                   := 0020578h
?AdjM7                     := 002057Ch
?DelMemA                   := 0020580h
?Get_Form_Num              := 0020584h
?DelVar                    := 0020588h
?DelVarIO                  := 002058Ch
?DelMem                    := 0020590h
?DelVar3D                  := 0020594h
?DelVar3C                  := 0020598h
?DelVar3DC                 := 002059Ch
?Sym_Prog_non_t_Lst        := 00205A0h
?AdjSymPtrs                := 00205A4h
?DataSizeA                 := 00205A8h
?DataSize                  := 00205ACh
?PopMCplxO1                := 00205B0h
?PopMCplx                  := 00205B4h
?MovCplx                   := 00205B8h
?PopOP5                    := 00205BCh
?PopOP3                    := 00205C0h
?PopOP1                    := 00205C4h
?PopRealO6                 := 00205C8h
?PopRealO5                 := 00205CCh
?PopRealO4                 := 00205D0h
?PopRealO3                 := 00205D4h
?PopRealO2                 := 00205D8h
?PopRealO1                 := 00205DCh
?PopReal                   := 00205E0h
?FPopCplx                  := 00205E4h
?FPopReal                  := 00205E8h
?FPopFPS                   := 00205ECh
?DeallocFPS                := 00205F0h
?DeallocFPS1               := 00205F4h
?AllocFPS                  := 00205F8h
?AllocFPS1                 := 00205FCh
?PushRealO6                := 0020600h
?PushRealO5                := 0020604h
?PushRealO4                := 0020608h
?PushRealO3                := 002060Ch
?PushRealO2                := 0020610h
?PushRealO1                := 0020614h
?PushReal                  := 0020618h
?PushOP5                   := 002061Ch
?PushOP3                   := 0020620h
?PushMCplxO3               := 0020624h
?PushOP1                   := 0020628h
?PushMCplxO1               := 002062Ch
?PushMCplx                 := 0020630h
?ExMCplxO1                 := 0020634h
?Exch9                     := 0020638h
?CpyTo1FPS11               := 002063Ch
?CpyTo2FPS5                := 0020640h
?CpyTo1FPS5                := 0020644h
?CpyTo2FPS6                := 0020648h
?CpyTo1FPS6                := 002064Ch
?CpyTo2FPS7                := 0020650h
?CpyTo1FPS7                := 0020654h
?CpyTo1FPS8                := 0020658h
?CpyTo2FPS8                := 002065Ch
?CpyTo1FPS10               := 0020660h
?CpyTo1FPS9                := 0020664h
?CpyTo2FPS4                := 0020668h
?CpyTo6FPS3                := 002066Ch
?CpyTo6FPS2                := 0020670h
?CpyTo2FPS3                := 0020674h
?Cpycto1FPS3               := 0020678h
?CpyTo1FPS3                := 002067Ch
?CpyFPS3                   := 0020680h
?CpyTo1FPS4                := 0020684h
?CpyTo3FPS2                := 0020688h
?CpyTo5FPST                := 002068Ch
?CpyTo6FPST                := 0020690h
?CpyTo4FPST                := 0020694h
?CpyTo3FPST                := 0020698h
?CpyTo2FPST                := 002069Ch
?CpyTo1FPST                := 00206A0h
?CpyFPST                   := 00206A4h
?CpyStack                  := 00206A8h
?CpyTo3FPS1                := 00206ACh
?CpyTo2FPS1                := 00206B0h
?CpyTo1FPS1                := 00206B4h
?CpyFPS1                   := 00206B8h
?CpyTo2FPS2                := 00206BCh
?CpyTo1FPS2                := 00206C0h
?CpyFPS2                   := 00206C4h
?CpyO3ToFPST               := 00206C8h
?CpyO2ToFPST               := 00206CCh
?CpyO6ToFPST               := 00206D0h
?CpyO1ToFPST               := 00206D4h
?CpyToFPST                 := 00206D8h
?CpyToStack                := 00206DCh
?CpyO3ToFPS1               := 00206E0h
?CpyO5ToFPS1               := 00206E4h
?CpyO2ToFPS1               := 00206E8h
?CpyO1ToFPS1               := 00206ECh
?CpyToFPS1                 := 00206F0h
?CpyO2ToFPS2               := 00206F4h
?CpyO3ToFPS2               := 00206F8h
?CpyO6ToFPS2               := 00206FCh
?CpyO1ToFPS2               := 0020700h
?CpyToFPS2                 := 0020704h
?CpyO5ToFPS3               := 0020708h
?CpyO2ToFPS3               := 002070Ch
?CpyO1ToFPS3               := 0020710h
?CpyToFPS3                 := 0020714h
?CpyO1ToFPS6               := 0020718h
?CpyO1ToFPS7               := 002071Ch
?CpyO1ToFPS5               := 0020720h
?CpyO2ToFPS4               := 0020724h
?CpyO1ToFPS4               := 0020728h
?ErrNotEnoughMem           := 002072Ch
?FPSMinus9                 := 0020730h
?HLMinus9                  := 0020734h
?ErrOverflow               := 0020738h
?ErrDivBy0                 := 002073Ch
?ErrSingularMat            := 0020740h
?ErrDomain                 := 0020744h
?ErrIncrement              := 0020748h
?ErrNon_Real               := 002074Ch
?ErrSyntax                 := 0020750h
?ErrDataType               := 0020754h
?ErrArgument               := 0020758h
?ErrDimMismatch            := 002075Ch
?ErrDimension              := 0020760h
?ErrUndefined              := 0020764h
?ErrMemory                 := 0020768h
?ErrInvalid                := 002076Ch
?ErrBreak                  := 0020770h
?ErrStat                   := 0020774h
?ErrSignChange             := 0020778h
?ErrIterations             := 002077Ch
?ErrBadGuess               := 0020780h
?ErrTolTooSmall            := 0020784h
?ErrStatPlot               := 0020788h
?ErrLinkXmit               := 002078Ch
?JError                    := 0020790h
?NoErrorEntry              := 0020794h
?PushErrorHandler          := 0020798h
?PopErrorHandler           := 002079Ch
?StrCopy                   := 00207A0h
?StrngCat                  := 00207A4h
?IsInSet                   := 00207A8h
?GEQNameA                  := 00207ACh
?RecName                   := 00207B0h
?PutMap                    := 00207B4h
?PutC                      := 00207B8h
?DispHL_s                  := 00207BCh
?PutS                      := 00207C0h
?PutPSB                    := 00207C4h
?PutPS                     := 00207C8h
?WPutPS                    := 00207CCh
?PutBuf                    := 00207D0h
?PutBuf1                   := 00207D4h
?WPutC                     := 00207D8h
?WPutS                     := 00207DCh
?WPutSEOL                  := 00207E0h
?WDispEOL                  := 00207E4h
?WHomeUp                   := 00207E8h
?SetNumWindow              := 00207ECh
?NewLine                   := 00207F0h
?MoveDown                  := 00207F4h
?ScrollUp                  := 00207F8h
?ShrinkWindow              := 00207FCh
?MoveUp                    := 0020800h
?ScrollDown                := 0020804h
?ClrLCDFull                := 0020808h
?ClrLCD                    := 002080Ch
?ClrScrnFull               := 0020810h
?ClrScrn                   := 0020814h
?ClrTxtShd                 := 0020818h
?ClrWindow                 := 002081Ch
?EraseEOL                  := 0020820h
?EraseEOW                  := 0020824h
?HomeUp                    := 0020828h
?GetCurloc                 := 002082Ch
?VPutMap                   := 0020830h
?VPutS                     := 0020834h
?VPutSN                    := 0020838h
?VPutSNG                   := 002083Ch
?VPutSNT                   := 0020840h
?RunIndicOn                := 0020844h
?RunIndicOff               := 0020848h
?SaveCmdShadow             := 002084Ch
?SaveShadow                := 0020850h
?RStrShadow                := 0020854h
?RStrPartial               := 0020858h
?RStrCurRow                := 002085Ch
?RStrUnderMenu             := 0020860h
?RStrbotRow                := 0020864h
?GetKeypress               := 0020868h
?GetTokLen                 := 002086Ch
?Get_Tok_Strng             := 0020870h
?GetTokString              := 0020874h
?PutBPatBuf2               := 0020878h
?PutBPatBuf                := 002087Ch
?PutBPat                   := 0020880h
?PutcChkScroll             := 0020884h
?DispEOL                   := 0020888h
?FDispEOL                  := 002088Ch
?MakeRowCmd                := 0020890h
?ToToStrp                  := 0020894h
?SetVarName                := 0020898h
?DispDone                  := 002089Ch
?FinishOutput              := 00208A0h
?CurBlink                  := 00208A4h
?CursorOff                 := 00208A8h
?HideCursor                := 00208ACh
?CursorOn                  := 00208B0h
?ShowCursor                := 00208B4h
?KeyToString               := 00208B8h
?PullDownChk               := 00208BCh
?MenuCatCommon             := 00208C0h
?LoadCurCat                := 00208C4h
?NCIFPrgmedMode            := 00208C8h
?LoadMenuNum               := 00208CCh
?LoadMenuNuml              := 00208D0h
?MenuEdKey                 := 00208D4h
?MenCatRet                 := 00208D8h
?NotAlphNum                := 00208DCh
?SetMenuFlags              := 00208E0h
?ResetSomeFlags            := 00208E4h
;                          equ 00208E8h
;                          equ 00208ECh
?DispListName              := 00208F0h
?DispLAlphaName            := 00208F4h
?AbortPrgmode              := 00208F8h
?IsFullCntx                := 00208FCh
?AdrMRow                   := 0020900h
?AdrmeLE                   := 0020904h
?GetmatOP1A                := 0020908h
?Getm1toOP1                := 002090Ch
?Getm1tOP1A                := 0020910h
?GetMToOP1                 := 0020914h
?PutToM1A                  := 0020918h
?PutToMA1                  := 002091Ch
?PutToMat                  := 0020920h
?MatELDiv                  := 0020924h
?CMatFun                   := 0020928h
?RowEchPoly                := 002092Ch
?RowEchelon                := 0020930h
?AdrLELE                   := 0020934h
?Getl1ToOP1                := 0020938h
?Getl1TOP1A                := 002093Ch
?GetlToOP1                 := 0020940h
?Getl1ToOP2                := 0020944h
?Getl1TOP2A                := 0020948h
?Getl2TOP1A                := 002094Ch
?PutTola1                  := 0020950h
?PutToL                    := 0020954h
?MaxMinLst                 := 0020958h
?LLow                      := 002095Ch
?LHigh                     := 0020960h
?LSum                      := 0020964h
?CumSum                    := 0020968h
?ToFrac                    := 002096Ch
?SeqSet                    := 0020970h
?SeqSolve                  := 0020974h
?CmpNumInit                := 0020978h
?BinopExec                 := 002097Ch
?ExMeanL                   := 0020980h
?Set2MVLPtrs               := 0020984h
?SetMat1                   := 0020988h
?CreateTLIst               := 002098Ch
?UnopExec                  := 0020990h
?ThreeExec                 := 0020994h
?RestoreErrNo              := 0020998h
?FourExec                  := 002099Ch
?FiveExec                  := 00209A0h
?CpyTo2ES1                 := 00209A4h
?CpyTo6ES1                 := 00209A8h
?CpyTo1ES1                 := 00209ACh
?CpyTo3ES1                 := 00209B0h
?CpyTo3ES2                 := 00209B4h
?CpyTo2ES2                 := 00209B8h
?CpyTo1ES2                 := 00209BCh
?CpyTo2ES3                 := 00209C0h
?CpyTo1ES3                 := 00209C4h
?CpyTo3ES4                 := 00209C8h
?CpyTo6ES3                 := 00209CCh
?CpyTo2ES4                 := 00209D0h
?CpyTo1ES4                 := 00209D4h
?CpyTo2ES5                 := 00209D8h
?CpyTo1ES5                 := 00209DCh
?CpyTo4ESt                 := 00209E0h
?CpyTo2ESt                 := 00209E4h
?CpyTo1ESt                 := 00209E8h
?CpyTo2ES6                 := 00209ECh
?CpyTo1ES6                 := 00209F0h
?CpyTo2ES7                 := 00209F4h
?CpyTo1ES7                 := 00209F8h
?CpyTo2ES8                 := 00209FCh
?CpyTo1ES8                 := 0020A00h
?CpyTo1ES9                 := 0020A04h
?CpyTo2ES9                 := 0020A08h
?CpyTo2ES10                := 0020A0Ch
?CpyTo1ES10                := 0020A10h
?CpyTo2ES11                := 0020A14h
?CpyTo1ES11                := 0020A18h
?CpyTo2ES12                := 0020A1Ch
?CpyTo1ES12                := 0020A20h
?CpyTo2ES13                := 0020A24h
?CpyTo1ES13                := 0020A28h
?CpyTo1ES14                := 0020A2Ch
?CpyTo1ES16                := 0020A30h
?CpyTo1ES17                := 0020A34h
?CpyTo1ES18                := 0020A38h
?CpyTo1ES15                := 0020A3Ch
?CpyTo2ES15                := 0020A40h
?CpyO1ToESt                := 0020A44h
?CpyO1ToES1                := 0020A48h
?CpyO6ToES1                := 0020A4Ch
?CpyO6ToES3                := 0020A50h
?CpyO1ToES2                := 0020A54h
?CpyO2ToES2                := 0020A58h
?CpyO1ToES3                := 0020A5Ch
?CpyO1ToES4                := 0020A60h
?CpyO1ToES5                := 0020A64h
?CpyO1ToES6                := 0020A68h
?CpyO1ToES7                := 0020A6Ch
?CpyO2ToES4                := 0020A70h
?CpyO2ToES5                := 0020A74h
?CpyO2ToES6                := 0020A78h
?CpyO2ToES7                := 0020A7Ch
?CpyO2ToES8                := 0020A80h
?CpyO2ToES9                := 0020A84h
?CpyO1ToES8                := 0020A88h
?CpyO1ToES9                := 0020A8Ch
?CpyO1ToES10               := 0020A90h
?CpyO1ToES11               := 0020A94h
?CpyO1ToES12               := 0020A98h
?CpyO1ToES13               := 0020A9Ch
?CpyO1ToES14               := 0020AA0h
?EvalF3A                   := 0020AA4h
?GetK                      := 0020AA8h
?SetTitle                  := 0020AACh
?DispVarVal                := 0020AB0h
?RecallEd                  := 0020AB4h
?SetUpBuffer               := 0020AB8h
?CreateNumEditBuf          := 0020ABCh
?CallCommon                := 0020AC0h
?CommonKeys                := 0020AC4h
?LeftMore                  := 0020AC8h
?FDel                      := 0020ACCh
?FClear                    := 0020AD0h
?FInsDisp                  := 0020AD4h
?FInsDispNoConv            := 0020AD8h
?SetIndicator              := 0020ADCh
?CloseEditBufNoR           := 0020AE0h
?ReleaseBuffer             := 0020AE4h
?VarNameToOP1HL            := 0020AE8h
?NameToOP1                 := 0020AECh
?NumpPutAway               := 0020AF0h
?NumReDisp                 := 0020AF4h
?NumError02                := 0020AF8h
?Load_Sfont                := 0020AFCh
?Sfont_Len                 := 0020B00h
?InitNumVec                := 0020B04h
?SetxxOP1                  := 0020B08h
?SetxxOP2                  := 0020B0Ch
?SetxxxxOP2                := 0020B10h
?UCLines                   := 0020B14h
?CLine                     := 0020B18h
?CLines                    := 0020B1Ch
?XrootY                    := 0020B20h
?YtoX                      := 0020B24h
?ZmStats                   := 0020B28h
?PointStatHelp             := 0020B2Ch
?DrawSPlot                 := 0020B30h
?InitNewTraceP             := 0020B34h
?SPlotCoord                := 0020B38h
?SPlotRight                := 0020B3Ch
?SPlotLeft                 := 0020B40h
?CmpBoxInfo                := 0020B44h
?NextPlot                  := 0020B48h
?PrevPlot                  := 0020B4Ch
?ClrPrevPlot               := 0020B50h
?PutIndexList              := 0020B54h
?GetIndexList              := 0020B58h
?HeapSort                  := 0020B5Ch
?StoGDB2                   := 0020B60h
?RclGDB2                   := 0020B64h
?CircCmd                   := 0020B68h
?GrphCirc                  := 0020B6Ch
?Mov18b                    := 0020B70h
?DarkLine                  := 0020B74h
?ILine                     := 0020B78h
?IPoint                    := 0020B7Ch
?XYRndBoth                 := 0020B80h
?XYRnd                     := 0020B84h
?CheckTOP                  := 0020B88h
?CheckXY                   := 0020B8Ch
?DarkPnt                   := 0020B90h
?CPointS                   := 0020B94h
?WToV                      := 0020B98h
?VtoWHLDE                  := 0020B9Ch
?Xitof                     := 0020BA0h
?YftoI                     := 0020BA4h
?XftoI                     := 0020BA8h
?TraceOff                  := 0020BACh
?GrRedisp                  := 0020BB0h
?GDispToken                := 0020BB4h
?GrdeCoda                  := 0020BB8h
?LabCoor                   := 0020BBCh
?CoorDisp                  := 0020BC0h
?TmpEquNoSrc               := 0020BC4h
?GrLabels                  := 0020BC8h
?YPixSet                   := 0020BCCh
?XPixSet                   := 0020BD0h
?CopyRng                   := 0020BD4h
?ValCur                    := 0020BD8h
?GrPutAway                 := 0020BDCh
?RstGFlags                 := 0020BE0h
?GrReset                   := 0020BE4h
?XYCent                    := 0020BE8h
?ZoomXYCmd                 := 0020BECh
?CptDelY                   := 0020BF0h
?CptDelX                   := 0020BF4h
?SetFuncM                  := 0020BF8h
?SetSeqM                   := 0020BFCh
?SetPolM                   := 0020C00h
?SetParM                   := 0020C04h
?ZmInt                     := 0020C08h
?ZmDecml                   := 0020C0Ch
?ZmPrev                    := 0020C10h
?ZmUsr                     := 0020C14h
?SetUZM                    := 0020C18h
?ZmFit                     := 0020C1Ch
?ZmSquare                  := 0020C20h
?ZmTrig                    := 0020C24h
?SetXMinMax                := 0020C28h
?ZooDefault                := 0020C2Ch
?GrBufCpy                  := 0020C30h
?DrawSplitLine             := 0020C34h
;                          equ 0020C38h
;                          equ 0020C3Ch
;                          equ 0020C40h
;                          equ 0020C44h
;                          equ 0020C48h
;                          equ 0020C4Ch
;                          equ 0020C50h
;                          equ 0020C54h
?ChkTextCurs               := 0020C58h
?Regraph                   := 0020C5Ch
?DoRefFlags02              := 0020C60h
?InitNSeq                  := 0020C64h
?YRes                      := 0020C68h
?Ceiling                   := 0020C6Ch
?PutXY                     := 0020C70h
?PutEquNo                  := 0020C74h
?PDspGrph                  := 0020C78h
?HorizCmd                  := 0020C7Ch
?VertCmd                   := 0020C80h
?LineCmd                   := 0020C84h
?UnLineCmd                 := 0020C88h
?PointCmd                  := 0020C8Ch
?PixelTest                 := 0020C90h
?PixelCmd                  := 0020C94h
?TanLnF                    := 0020C98h
?DrawCmdInit               := 0020C9Ch
?DrawCmd                   := 0020CA0h
?ShadeCmd                  := 0020CA4h
?InvCmd                    := 0020CA8h
?StatShade                 := 0020CACh
?DspMatTable               := 0020CB0h
?DspLsts                   := 0020CB4h
?CloseEditBuf              := 0020CB8h
?ParseEditBuf              := 0020CBCh
?PutSM                     := 0020CC0h
?DspCurTbl                 := 0020CC4h
?DspGrTbl                  := 0020CC8h
?ZeroTemplate              := 0020CCCh
?SetTblRefs                := 0020CD0h
?DispTblBot                := 0020CD4h
?DispTblTop                := 0020CD8h
?DispTblBody               := 0020CDCh
?VPutBlank                 := 0020CE0h
?TblTrace                  := 0020CE4h
?DispListNameY             := 0020CE8h
?CurNameLength             := 0020CECh
?NameToBuf                 := 0020CF0h
?JPromptCursor             := 0020CF4h
?BufLeft                   := 0020CF8h
?BufRight                  := 0020CFCh
?BufInsert                 := 0020D00h
?BufQueueChar              := 0020D04h
?BufReplace                := 0020D08h
?BufDelete                 := 0020D0Ch
?BufPeek                   := 0020D10h
?BufPeek1                  := 0020D14h
?BufPeek2                  := 0020D18h
?BufPeek3                  := 0020D1Ch
?BufToBtm                  := 0020D20h
?SetupEditEqu              := 0020D24h
?BufToTop                  := 0020D28h
?IsEditFull                := 0020D2Ch
?IsEditEmpty               := 0020D30h
?IsAtTop                   := 0020D34h
?IsAtBtm                   := 0020D38h
?BufClear                  := 0020D3Ch
?JCursorFirst              := 0020D40h
?JCursorLast               := 0020D44h
?CursorLeft                := 0020D48h
?CursorRight               := 0020D4Ch
?CursorUp                  := 0020D50h
?CursorDown                := 0020D54h
?CursorToOffset            := 0020D58h
?InsDisp                   := 0020D5Ch
?FDispBOL1                 := 0020D60h
?FDispBOL                  := 0020D64h
?DispEOW                   := 0020D68h
?DispHead                  := 0020D6Ch
?DispTail                  := 0020D70h
?PutTokString              := 0020D74h
?SetUpEditCmd              := 0020D78h
?SetEmptyeditEqu           := 0020D7Ch
?SetEmptyEditPtr           := 0020D80h
?CloseEditEqu              := 0020D84h
?GetPrevTok                := 0020D88h
?GetKey                    := 0020D8Ch
?CanIndic                  := 0020D90h
?DFMin                     := 0020D94h
?FormDisp                  := 0020D98h
?FormMatrix                := 0020D9Ch
?WScrollLeft               := 0020DA0h
?WScrollUp                 := 0020DA4h
?WScrollDown               := 0020DA8h
?WScrollRight              := 0020DACh
?FormEReal                 := 0020DB0h
?FormERealTok              := 0020DB4h
?FormDCplx                 := 0020DB8h
?FormReal                  := 0020DBCh
?SetWinAbove               := 0020DC0h
?DisarmScroll              := 0020DC4h
?MinToEdit                 := 0020DC8h
?RclVarToEdit              := 0020DCCh
?RclVarToEditPtr           := 0020DD0h
?RclEntryToEdit            := 0020DD4h
?RclToQueue                := 0020DD8h
?FormToTok                 := 0020DDCh
?DispInterval              := 0020DE0h
?DispLstName               := 0020DE4h
?DispSLstNameHL            := 0020DE8h
?EditEqu                   := 0020DECh
?CloseEquField             := 0020DF0h
?AutoSelect                := 0020DF4h
?DispYEOS                  := 0020DF8h
?DispNumEOS                := 0020DFCh
?SetupDispEq               := 0020E00h
?DispForward               := 0020E04h
?DispYPrompt2              := 0020E08h
?StringWidth               := 0020E0Ch
?DispErrorScreen           := 0020E10h
?PopCX                     := 0020E14h
?LoadNoEEntry              := 0020E18h
?SaveScreen                := 0020E1Ch
?RetScreen                 := 0020E20h
?RetScreenErr              := 0020E24h
?CheckSplitFlag            := 0020E28h
?SolveRedisp               := 0020E2Ch
?SolveDisp                 := 0020E30h
?ItemName                  := 0020E34h
?SetNorm_Vals              := 0020E38h
?SetYOffset                := 0020E3Ch
?ConvKeyToTok              := 0020E40h
?ConvFCKeyToTok            := 0020E44h
?ConvFEKeyToTok            := 0020E48h
?TokToKey                  := 0020E4Ch
?GetVarCmdUSB              := 0020E50h
;                          equ 0020E54h
?DeselectAllVars           := 0020E58h
?DelRes                    := 0020E5Ch
?ConvLcToLr                := 0020E60h
?RedimMat                  := 0020E64h
?IncLstSize                := 0020E68h
?InsertList                := 0020E6Ch
?DelListEl                 := 0020E70h
?EditProg                  := 0020E74h
?CloseProg                 := 0020E78h
?ClrGraphRef               := 0020E7Ch
?FixTempCnt                := 0020E80h
?SaveData                  := 0020E84h
?RestoreData               := 0020E88h
?FindAlphaUp               := 0020E8Ch
?FindAlphaDn               := 0020E90h
?CmpSyms                   := 0020E94h
?CreateTemp                := 0020E98h
?CleanAll                  := 0020E9Ch
?MoveToNextSym             := 0020EA0h
?ConvLrToLc                := 0020EA4h
?TblScreenDown             := 0020EA8h
?TblScreenUp               := 0020EACh
?ScreenScrollPixelsUp      := 0020EB0h
;;_ret                     equ 0020EB4h
?ZIfRclHandler             := 0020EB8h
?ZIfRclKApp                := 0020EBCh
;                          equ 0020EC0h
;                          equ 0020EC4h
?InitNamePrompt            := 0020EC8h
?InitNamePrompt_           := 0020ECCh
?CatalogChk                := 0020ED0h
?ClrTR                     := 0020ED4h
;                          equ 0020ED8h
;                          equ 0020EDCh
;                          equ 0020EE0h
;                          equ 0020EE4h
?ErrNonReal_FPST_FPS1      := 0020EE8h
?ErrNonReal                := 0020EECh
?WriteText                 := 0020EF0h
;                          equ 0020EF4h
?GraphPars                 := 0020EF8h
?PlotPars                  := 0020EFCh
?ParseInp                  := 0020F00h
?ParseOn                   := 0020F04h
?ParseScan                 := 0020F08h
?GetParse                  := 0020F0Ch
?SaveParse                 := 0020F10h
?InitPFlgs                 := 0020F14h
?CkEndLineRR               := 0020F18h
?OP2Set60                  := 0020F1Ch
?GetStatPtr                := 0020F20h
?CmpStatPtr                := 0020F24h
?VarSysAdr                 := 0020F28h
?StoSysTok                 := 0020F2Ch
?StoAns                    := 0020F30h
?StoTheta                  := 0020F34h
?StoR                      := 0020F38h
?StoY                      := 0020F3Ch
?StoN                      := 0020F40h
?StoT                      := 0020F44h
?StoX                      := 0020F48h
?StoOther                  := 0020F4Ch
?RclAns                    := 0020F50h
?RclY                      := 0020F54h
?RclN                      := 0020F58h
?RclX                      := 0020F5Ch
?RclVarSym                 := 0020F60h
?RclsyStok                 := 0020F64h
?StMatel                   := 0020F68h
?StLstvecel                := 0020F6Ch
?ConvOP1                   := 0020F70h
?FindParseFormula          := 0020F74h
?ParseFormula              := 0020F78h
?StrngEnt1                 := 0020F7Ch
?Prgrdlp                   := 0020F80h
?VarEnt                    := 0020F84h
?ParseOnC                  := 0020F88h
?ParseOn_                  := 0020F8Ch
?ParseCmd                  := 0020F90h
?StoType                   := 0020F94h
?CreatePair                := 0020F98h
?PushNum                   := 0020F9Ch
?IncCurPCErrEnd            := 0020FA0h
?ErrEnd                    := 0020FA4h
?CommaErrF                 := 0020FA8h
?CommaErr                  := 0020FACh
?StEQArg2                  := 0020FB0h
?StEQArg                   := 0020FB4h
?InpArg                    := 0020FB8h
?StEQArg3                  := 0020FBCh
?NxtFetch                  := 0020FC0h
?CkFetchVar                := 0020FC4h
?FetchVarA                 := 0020FC8h
?FetchVar                  := 0020FCCh
?CkEndLin                  := 0020FD0h
?CkEndExp                  := 0020FD4h
?CkParsEnd                 := 0020FD8h
?StoTypeArg                := 0020FDCh
?ConvDim                   := 0020FE0h
?ConvDim00                 := 0020FE4h
?AheadEqual                := 0020FE8h
?ParseHeads                := 0020FECh
?ParseHead                 := 0020FF0h
?AnsName                   := 0020FF4h
?StoCmpReals               := 0020FF8h
?GetDEPtr                  := 0020FFCh
?Push2BOper                := 0021000h
?Push3BOper                := 0021004h
?Pop2BOper                 := 0021008h
?Pop3BOper                 := 002100Ch
?PushOper                  := 0021010h
?PopOper                   := 0021014h
?FindEUndef                := 0021018h
?SttmpEQ                   := 002101Ch
?FindEOL                   := 0021020h
?BrkInc                    := 0021024h
?IncFetch                  := 0021028h
?CurFetch                  := 002102Ch
?Random                    := 0021030h
?StoRand                   := 0021034h
?RandInit                  := 0021038h
?ResetStacks               := 002103Ch
?Factorial                 := 0021040h
?YEquOnOff                 := 0021044h
?EquSelUnsel               := 0021048h
?ITSolver                  := 002104Ch
?GRITSolver                := 0021050h
?ITSolverB                 := 0021054h
?ITSolverNB                := 0021058h
?ExTestInt                 := 002105Ch
?DistFun                   := 0021060h
?LogGamma                  := 0021064h
?OneVar                    := 0021068h
?OneVars0                  := 002106Ch
?OrdStat                   := 0021070h
?InitStatAns               := 0021074h
?AnovaSpec                 := 0021078h
?OutputExpr                := 002107Ch
?CentCursor                := 0021080h
;                          equ 0021084h
;                          equ 0021088h
;                          equ 002108Ch
;                          equ 0021090h
?CkValDeltaX               := 0021094h
?CkValDelta                := 0021098h
?GrBufClr                  := 002109Ch
?GrBufCpyV                 := 00210A0h
?FndSelEQ                  := 00210A4h
?ClrGraphXY                := 00210A8h
?NEDXTYStyle               := 00210ACh
?PlotPt                    := 00210B0h
?NewWindEP                 := 00210B4h
?DrawAxes                  := 00210B8h
?SetPenX                   := 00210BCh
?SetPenY                   := 00210C0h
?SetPenT                   := 00210C4h
?TanEquDisp                := 00210C8h
?PutAns                    := 00210CCh
?DispOP1A                  := 00210D0h
;                          equ 00210D4h
?SetTblGraphDraw           := 00210D8h
?MemClear                  := 00210DCh
?MemSet                    := 00210E0h
?PointOn                   := 00210E4h
?ExecuteNewPrgm            := 00210E8h
?StrLength                 := 00210ECh
?VPutMapRec                := 00210F0h
?FindAppUp                 := 00210F4h
?FindAppDown               := 00210F8h
?FindApp                   := 00210FCh
?os.FindAppStart           := 0021100h
?SkipAppHeader             := 0021104h
?FindAppStart              := 0021108h
?IBounds                   := 002110Ch
?IOffset                   := 0021110h
?DrawCirc                  := 0021114h
?CanAlphIns                := 0021118h
?CxReDisp                  := 002111Ch
?GetBaseVer                := 0021120h
?OPSet0                    := 0021124h
?AppGetCBLUSB              := 0021128h
?SetIgnoreKey              := 002112Ch
?SetSendThisKeyBack        := 0021130h
?DisableAPD                := 0021134h
?EnableAPD                 := 0021138h
?Set2IY34                  := 002113Ch
?ForceCmd                  := 0021140h
?ApdSetup                  := 0021144h
?AppSetup                  := 0021148h
;                          equ 002114Ch
?ReleaseSedit              := 0021150h
?InitSmallEditLine         := 0021154h
?StartSmallEdit            := 0021158h
;                          equ 002115Ch
?SGetTokString             := 0021160h
?LoadPattern               := 0021164h
?SStringLength             := 0021168h
?RestorePenCol             := 002116Ch
;                          equ 0021170h
?EmptyHook                 := 0021174h
?ForceSmallEditReturn      := 0021178h
?SaveContext               := 002117Ch
;                          equ 0021180h
?ClearRow                  := 0021184h
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
?InitSmallEditLineVar      := 00211F8h
?InitSmallEditLineOP1      := 00211FCh
?InitSmallEditBoxVar       := 0021200h
?InitSmallEditBoxOP1       := 0021204h
?RclEntryToEditA           := 0021208h
?ErrCustom1                := 002120Ch
?ErrCustom2                := 0021210h
;;_ret                     equ 0021214h
?ClearRect                 := 0021218h
?InvertRect                := 002121Ch
?FillRect                  := 0021220h
?RestoreTextFlags          := 0021224h
?InitCellBox               := 0021228h
?DrawCell                  := 002122Ch
;                          equ 0021230h
?InvertCell                := 0021234h
?SetCellOverride           := 0021238h
?DrawRectBorder            := 002123Ch
?ClearCell                 := 0021240h
?CoverCell                 := 0021244h
?EraseRectBorder           := 0021248h
?FillRectPattern           := 002124Ch
?DrawRectBorderClear       := 0021250h
;                          equ 0021254h
?VerticalLine              := 0021258h
?IBoundsFull               := 002125Ch
;                          equ 0021260h
;                          equ 0021264h
?CPoint                    := 0021268h
?DeleteApp                 := 002126Ch
?GetModeCellFlagOR         := 0021270h
?ResetModeCellFlag         := 0021274h
?IsModeCellSet             := 0021278h
?GetModeCellFlag           := 002127Ch
;                          equ 0021280h
?SetCurCellBoxManager      := 0021284h
;                          equ 0021288h
?CellBoxManager            := 002128Ch
?StartNewCell              := 0021290h
?RunInCellOveride          := 0021294h
?RunCellOveride            := 0021298h
?ClearCurCell              := 002129Ch
?DrawCurCell               := 00212A0h
?InvertCurCell             := 00212A4h
?CoverCurCell              := 00212A8h
?BlinkCell                 := 00212ACh
?BlinkCellNoLookUp         := 00212B0h
?BlinkCurCell              := 00212B4h
?BlinkCellToOn             := 00212B8h
?BlinkCellToOnNoLookUp     := 00212BCh
?BlinkCurCellToOn          := 00212C0h
?BlinkCellToOff            := 00212C4h
?BlinkCellToOffNoLookUp    := 00212C8h
?BlinkCurCellToOff         := 00212CCh
?GetCurModeCellFlag        := 00212D0h
;                          equ 00212D4h
?StartSmallEditReturn      := 00212D8h
;                          equ 00212DCh
;                          equ 00212E0h
?CellKeyHandle             := 00212E4h
;                          equ 00212E8h
;                          equ 00212ECh
;                          equ 00212F0h
;                          equ 00212F4h
;                          equ 00212F8h
?EraseAllCells             := 00212FCh
?IsCurModeCellSet          := 0021300h
;                          equ 0021304h
;                          equ 0021308h
;                          equ 002130Ch
;                          equ 0021310h
?DrawBlnkCell              := 0021314h
?ClearBlnkCell             := 0021318h
?InvertBlnkCell            := 002131Ch
?GetStringInput            := 0021320h
?GetStringInput2           := 0021324h
?WaitEnterKeyValue         := 0021328h
?HorizontalLine            := 002132Ch
?CreateAppVar              := 0021330h
?CreateProtProg            := 0021334h
?CreateVar                 := 0021338h
?AsmComp                   := 002133Ch
?GetAsmSize                := 0021340h
?SquishPrgm                := 0021344h
?ExecutePrgm               := 0021348h
?ChkFindSymAsm             := 002134Ch
?ParsePrgmName             := 0021350h
?CSub                      := 0021354h
?CAdd                      := 0021358h
?CSquare                   := 002135Ch
?CMult                     := 0021360h
?CRecip                    := 0021364h
?CDiv                      := 0021368h
?CAbs                      := 002136Ch
?AddSquares                := 0021370h
?CSqRoot                   := 0021374h
?CLN                       := 0021378h
?CLog                      := 002137Ch
?CTenX                     := 0021380h
?CEtoX                     := 0021384h
?CXrootY                   := 0021388h
;                          equ 002138Ch
?CYtoX                     := 0021390h
?InvertNonReal             := 0021394h
?CTrunc                    := 0021398h
?CFrac                     := 002139Ch
?CFloor                    := 00213A0h
?SrchVLstUp                := 00213A4h
?SrchVLstDn                := 00213A8h
?FlashWriteDisable         := 00213ACh
?Disp                      := 00213B0h
?GetBytePaged              := 00213B4h
?RunCursorHook             := 00213B8h
?RunLibraryHook            := 00213BCh
?RunRawKeyHook             := 00213C0h
?SetCursorHook             := 00213C4h
?SetLibraryHook            := 00213C8h
?SetGetKeyHook             := 00213CCh
?ClrCursorHook             := 00213D0h
?ClrLibraryHook            := 00213D4h
?ClrRawKeyHook             := 00213D8h
?GetKeyHook                := 00213DCh
?SetGetCSCHook             := 00213E0h
?ClrGetKeyHook             := 00213E4h
?SetCatalog2Hook           := 00213E8h
?ClrCatalog2Hook           := 00213ECh
?SetLocalizeHook           := 00213F0h
?ClrLocalizeHook           := 00213F4h
?SetTokenHook              := 00213F8h
?ClrTokenHook              := 00213FCh
;                          equ 0021400h
;                          equ 0021404h
?DispListElementOffLA      := 0021408h
?BitVertSplit              := 002140Ch
?SetHomescreenHook         := 0021410h
?ClrHomescreenHook         := 0021414h
?SetWindowHook             := 0021418h
?ClrWindowHook             := 002141Ch
?SetGraphModeHook          := 0021420h
?ClrGraphModeHook          := 0021424h
?ParseAndStoreSysVar       := 0021428h
?DisplayEditSysVar         := 002142Ch
?JForceWIndowSettings      := 0021430h
?DelVarArc                 := 0021434h
?DelVarNoArc               := 0021438h
?SetAllPlots               := 002143Ch
?SetYeditHook              := 0021440h
?ClrYeditHook              := 0021444h
?Arc_Unarc                 := 0021448h
?ArchiveVar                := 002144Ch
?UnarchiveVar              := 0021450h
?SetFontHook               := 0021454h
?ClrFontHook               := 0021458h
?SetRegraphHook            := 002145Ch
?ClrRegraphHook            := 0021460h
?RunGraphingHook           := 0021464h
?SetTraceHook              := 0021468h
?ClrTraceHook              := 002146Ch
?RunTraceHook              := 0021470h
?NDeriv                    := 0021474h
?PolarDerivative           := 0021478h
?JForceGraphNoKey          := 002147Ch
?JForceGraphKey            := 0021480h
?PowerOff                  := 0021484h
?GetKeyRetOff              := 0021488h
?FindGroupSym              := 002148Ch
?LoadDEIndPaged            := 0021490h
?SetUpPagedPtr             := 0021494h
?PagedGet                  := 0021498h
?SetParserHook             := 002149Ch
?ClrParserHook             := 00214A0h
?SetAppChangeHook          := 00214A4h
?ClrAppChangeHook          := 00214A8h
?SetGraphicsHook           := 00214ACh
?ClrGraphicsHook           := 00214B0h
?ILineNoGraphicsHook       := 00214B4h
?ILineNoHook               := 00214B8h
;                          equ 00214BCh
?DeleteTempPrograms        := 00214C0h
?SetCatalog1Hook           := 00214C4h
?ClrCatalog1Hook           := 00214C8h
?SetHelpHook               := 00214CCh
?ClrHelpHook               := 00214D0h
?DispCatalogEnd            := 00214D4h
?GetMenuKeypress           := 00214D8h
?GetCatalogItem            := 00214DCh
?RunCatalog2Hook           := 00214E0h
?RunCatalog1Hook           := 00214E4h
;                          equ 00214E8h
;                          equ 00214ECh
?DispMenuTitle             := 00214F0h
;                          equ 00214F4h
?SetCxReDispHook           := 00214F8h
?ClrCxReDispHook           := 00214FCh
?DrawStatusBarMode         := 0021500h
?BufClr                    := 0021504h
?UnOPExec2                 := 0021508h
?BinOPExec2                := 002150Ch
?LoadMenuB                 := 0021510h
?DisplayVarInfo            := 0021514h
?SetMenuHook               := 0021518h
?ClrMenuHook               := 002151Ch
?GetBCOffSetIX             := 0021520h
?GetBCOffSetIX_            := 0021524h
?ForceFullScreen           := 0021528h
?HLMinus5                  := 002152Ch
;;_ret                     equ 0021530h
;                          equ 0021534h
;                          equ 0021538h
?Arc_Unarc_                := 002153Ch
?RclExit                   := 0021540h
?SetSilentLinkHook         := 0021544h
?ClrSilentLinkHook         := 0021548h
?TwoVarSet                 := 002154Ch
?ExecClassCToken           := 0021550h
?ExecClass3Token           := 0021554h
?GetSysInfo                := 0021558h
?RunChkCTenX               := 002155Ch
?TenXNoClr                 := 0021560h
;                          equ 0021564h
;                          equ 0021568h
?GetVarVersion             := 002156Ch
?ParseGraphCmdToken        := 0021570h
;                          equ 0021574h
?DeleteTempEditEqu         := 0021578h
?PromptMoveBackLeft        := 002157Ch
?WPutSEOLRes10E            := 0021580h
?InvertTextInsMode         := 0021584h
;                          equ 0021588h
?ResetDefaults             := 002158Ch
?ZeroFinanceVars           := 0021590h
?DispHeader                := 0021594h
?JForceGroup               := 0021598h
;                          equ 002159Ch
;                          equ 00215A0h
?DispCoords                := 00215A4h
;                          equ 00215A8h
;                          equ 00215ACh
?ChkTmr                    := 00215B0h
?ClockOff                  := 00215B4h
?ClockOn                   := 00215B8h
;                          equ 00215BCh
?GetDate                   := 00215C0h
?GetDateString             := 00215C4h
?GetDtFmt                  := 00215C8h
?GetDtStr                  := 00215CCh
?GetTime                   := 00215D0h
?FormTime                  := 00215D4h
?GetTmFmt                  := 00215D8h
?GetTmStr                  := 00215DCh
?SetZeroOne                := 00215E0h
?SetDate                   := 00215E4h
?IsOneTwoThree             := 00215E8h
?SetTime                   := 00215ECh
?IsOP112or24               := 00215F0h
?ChkTimer0                 := 00215F4h
?TimeCnv                   := 00215F8h
?ClrWindowAndFlags         := 00215FCh
?ResetAllLists             := 0021600h
?DispValue                 := 0021604h
;                          equ 0021608h
;                          equ 002160Ch
;                          equ 0021610h
?CpOP1OP2Rounded           := 0021614h
?CpOP1OP2Rounded2          := 0021618h
;                          equ 002161Ch
;                          equ 0021620h
?ResetIOPrompt             := 0021624h
;                          equ 0021628h
?SetUpEditor               := 002162Ch
?SortA                     := 0021630h
?SortD                     := 0021634h
;                          equ 0021638h
?IsOP1ResID                := 002163Ch
;                          equ 0021640h
;                          equ 0021644h
;                          equ 0021648h
?ForceModeKeypress         := 002164Ch
?DispAboutScreen           := 0021650h
?ChkHelpHookVer            := 0021654h
?Draw32                    := 0021658h
;                          equ 002165Ch
;                          equ 0021660h
;                          equ 0021664h
?DrawPlotStatus            := 0021668h
?DrawTableEditor           := 002166Ch
?DisplayListNameEquals     := 0021670h
?DisplayListHeader         := 0021674h
?DispMatrixDimensions      := 0021678h
?HighlightListEdItem       := 002167Ch
;                          equ 0021680h
;                          equ 0021684h
?MatrixName                := 0021688h
;                          equ 002168Ch
;                          equ 0021690h
;                          equ 0021694h
;                          equ 0021698h
;                          equ 002169Ch
?ChkCxMainPtr              := 00216A0h
?NumError02_               := 00216A4h
;                          equ 00216A8h
?SetupEmptyEditTempEqu     := 00216ACh
?Res1IY0E                  := 00216B0h
?RestoreBuffer             := 00216B4h
;                          equ 00216B8h
;                          equ 00216BCh
;                          equ 00216C0h
;                          equ 00216C4h
;                          equ 00216C8h
;                          equ 00216CCh
?DisplayListEquals         := 00216D0h
?GetCurPlotListOffset      := 00216D4h
?GoToLastRow               := 00216D8h
?DrawRectBorder_           := 00216DCh
;                          equ 00216E0h
;                          equ 00216E4h
;                          equ 00216E8h
;                          equ 00216ECh
?NamedListToOP1            := 00216F0h
;                          equ 00216F4h
;                          equ 00216F8h
;                          equ 00216FCh
?InitUSBDeviceCallback     := 0021700h
?KillUSBDevice             := 0021704h
?SetUSBConfiguration       := 0021708h
?RequestUSBData            := 002170Ch
?StopReceivingUSBData      := 0021710h
?SetVertGraphActive        := 0021714h
?ClrVertGraphActive        := 0021718h
?SetUSBActivityHook        := 002171Ch
?ClrUSBActivityHook        := 0021720h
;;_ret                     equ 0021724h
?GetCurPlotOffsetPrev      := 0021728h
?SplitUpdateStatPlotLists  := 002172Ch
?GraphLine                 := 0021730h
;                          equ 0021734h
;                          equ 0021738h
;                          equ 002173Ch
;                          equ 0021740h
;                          equ 0021744h
;                          equ 0021748h
?ZIfInTblEditor            := 002174Ch
;                          equ 0021750h
?GetCurPlotOffset          := 0021754h
;                          equ 0021758h
;                          equ 002175Ch
;                          equ 0021760h
;                          equ 0021764h
;                          equ 0021768h
?UpdateStatPlotLists       := 002176Ch
?ChkSomethingElseFPS5      := 0021770h
?ChkSomethingFPS5          := 0021774h
?VDispRealOP1              := 0021778h
?DispXEqualsNum            := 002177Ch
?ResetGraphSettings        := 0021780h
?InitializeVariables       := 0021784h
;;_ret                     equ 0021788h
?DelVarSym                 := 002178Ch
?FindAppUpNoCase           := 0021790h
?FindAppDnNoCase           := 0021794h
?SetupHome                 := 0021798h
?GrPutawayFull             := 002179Ch
;;_ret                     equ 00217A0h
?ToggleUSBSmartPadInput    := 00217A4h
?IsUSBDeviceConnected      := 00217A8h
?PolarEquToOP1             := 00217ACh
?ParamXEquToOP1            := 00217B0h
?ParamYEquToOP1            := 00217B4h
?DispTestModeResetComplete := 00217B8h
?PTTReset                  := 00217BCh
?FindAppCustom             := 00217C0h
?ClearGraphStyles          := 00217C4h
?BufToNextBASICSeparator   := 00217C8h
;                          equ 00217CCh
;                          equ 00217D0h
?ZooStandard               := 00217D4h
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
?AddHistoryEntryString     := 0021810h
?CurrEntryToPrevEntry      := 0021814h
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
?RunInitialBootMenu        := 00218F0h
;                          equ 00218F4h
;                          equ 00218F8h
;                          equ 00218FCh
?Clr05RclFlags             := 0021900h
;                          equ 0021904h
;                          equ 0021908h
;                          equ 002190Ch
;                          equ 0021910h
?DeleteHistoryEntry        := 0021914h
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
?CommonKeys_               := 0021940h
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
?ResetLastEntryStack       := 0021998h
;                          equ 002199Ch
;                          equ 00219A0h
?jp_JForceCmdNoChar        := 00219A4h
?Load_LFont                := 00219A8h
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
?EnterSelfTest             := 00219DCh
?DrawEntrySepLine          := 00219E0h
;                          equ 00219E4h
?GetGraphModeProperties    := 00219E8h
;                          equ 00219ECh
;                          equ 00219F0h
;                          equ 00219F4h
;                          equ 00219F8h
;                          equ 00219FCh
;                          equ 0021A00h
;                          equ 0021A04h
;                          equ 0021A08h
;                          equ 0021A0Ch
?ClrLCDAll                 := 0021A10h
?BufIPoint                 := 0021A14h
;                          equ 0021A18h
;                          equ 0021A1Ch
;                          equ 0021A20h
;                          equ 0021A24h
?SetDrawFGColorA           := 0021A28h
;                          equ 0021A2Ch
;                          equ 0021A30h
;                          equ 0021A34h
?DrawGraphBackground       := 0021A38h
?DrawStatusBar             := 0021A3Ch
;                          equ 0021A40h
;                          equ 0021A44h
;                          equ 0021A48h
;                          equ 0021A4Ch
?DrawBatteryIndicator      := 0021A50h
?DrawBatteryStatus         := 0021A54h
?VDispHL                   := 0021A58h
?PDspGrphNoColorReload     := 0021A5Ch
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
?DrawStatusBarInfo         := 0021AB4h
?RestoreLCDBrightness      := 0021AB8h
?RestoreLCDBrightness_     := 0021ABCh
?DimLCDSlow                := 0021AC0h
;                          equ 0021AC4h
;                          equ 0021AC8h
;                          equ 0021ACCh
;                          equ 0021AD0h
;                          equ 0021AD4h
;                          equ 0021AD8h
;                          equ 0021ADCh
?SetTextFGBGcolors         := 0021AE0h
?SetTextFGBGcolors_        := 0021AE4h
?SetTextBGcolor            := 0021AE8h
?VPutPS                    := 0021AECh
;                          equ 0021AF0h
;                          equ 0021AF4h
;                          equ 0021AF8h
;                          equ 0021AFCh
?DrawTILogo                := 0021B00h
?DrawThickRectBorder       := 0021B04h
;                          equ 0021B08h
?DrawStatusBarTextClr      := 0021B0Ch
;                          equ 0021B10h
;                          equ 0021B14h
;                          equ 0021B18h
;                          equ 0021B1Ch
?VPutPSN                   := 0021B20h
;                          equ 0021B24h
;                          equ 0021B28h
;                          equ 0021B2Ch
;                          equ 0021B30h
?RStrGraphFlags            := 0021B34h
;                          equ 0021B38h
;                          equ 0021B3Ch
?VPutMapSpecial            := 0021B40h
;                          equ 0021B44h
;                          equ 0021B48h
;                          equ 0021B4Ch
;                          equ 0021B50h
;                          equ 0021B54h
;                          equ 0021B58h
;                          equ 0021B5Ch
;                          equ 0021B60h
?DrawSprite16bpp           := 0021B64h
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
?GetColorValue             := 0021BACh
;                          equ 0021BB0h
;                          equ 0021BB4h
;                          equ 0021BB8h
;                          equ 0021BBCh
;                          equ 0021BC0h
?GraphBGColorToDrawBGColor := 0021BC4h
?SetWhiteDrawBGColor       := 0021BC8h
;                          equ 0021BCCh
?ChkResAppTextSave         := 0021BD0h
?ChkCxMain                 := 0021BD4h
;                          equ 0021BD8h
;                          equ 0021BDCh
?DrawRectBorder__          := 0021BE0h
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
?DrawLineEndEntry          := 0021C48h
;                          equ 0021C4Ch
;                          equ 0021C50h
;;_ret                     equ 0021C54h
;                          equ 0021C58h
;                          equ 0021C5Ch
;                          equ 0021C60h
;                          equ 0021C64h
;                          equ 0021C68h
?BitGrfFuncM               := 0021C6Ch
;;_ret                     equ 0021C70h
?GetScrollPxlAmount        := 0021C74h
?os.PushErrorHandler       := 0021C78h
?os.PopErrorHandler        := 0021C7Ch
?os.ThrowError             := 0021C80h
?os.RealCopy               := 0021C84h
?os.RealAsinRad            := 0021C88h
?os.RealAcosRad            := 0021C8Ch
?os.RealAtanRad            := 0021C90h
?os.RealAdd                := 0021C94h
?os.CplxAdd                := 0021C98h
?os.RealCompare            := 0021C9Ch
?os.RealCosRad             := 0021CA0h
?os.RealRadToDeg           := 0021CA4h
?os.RealDiv                := 0021CA8h
?os.RealExp                := 0021CACh
?os.RealFloor              := 0021CB0h
?os.RealToStr              := 0021CB4h
?os.RealFrac               := 0021CB8h
?os.RealGcd                := 0021CBCh
?os.RealRoundInt           := 0021CC0h
?os.RealLcm                := 0021CC4h
?os.RealLog                := 0021CC8h
?os.RealMax                := 0021CCCh
?os.RealMin                := 0021CD0h
?os.RealMul                := 0021CD4h
?os.RealNcr                := 0021CD8h
?os.RealNeg                := 0021CDCh
?os.RealNpr                := 0021CE0h
?os.RealPow                := 0021CE4h
?os.RealDegToRad           := 0021CE8h
?os.RealRandInt            := 0021CECh
?os.RealInv                := 0021CF0h
?os.RealMod                := 0021CF4h
?os.RealRound              := 0021CF8h
?os.RealSinRad             := 0021CFCh
?os.RealSqrt               := 0021D00h
?os.RealSub                := 0021D04h
?os.RealTanRad             := 0021D08h
?os.StrToReal              := 0021D0Ch
?os.RealTrunc              := 0021D10h
?os.SetFlagBits            := 0021D14h
?os.ResetFlagBits          := 0021D18h
?os.TestFlagBits           := 0021D1Ch
?os.SetFlagByte            := 0021D20h
?os.GetFlagByte            := 0021D24h
?os.GetCursorPos           := 0021D28h
?os.PutStrFull             := 0021D2Ch
?os.PutStrLine             := 0021D30h
?os.SetCursorPos           := 0021D34h
?os.GetKey                 := 0021D38h
?os.GetCSC                 := 0021D3Ch
?os.AppInit                := 0021D40h
;                          equ 0021D44h
?ChkBCIs0                  := 0021D48h
?ChkDEIs0                  := 0021D4Ch
?ChkHLIs0                  := 0021D50h
?SetAToBCU                 := 0021D54h
?SetAToDEU                 := 0021D58h
?SetAToHLU                 := 0021D5Ch
?SetBCUToA                 := 0021D60h
?SetBCUToB                 := 0021D64h
?SetDEUToA                 := 0021D68h
?SetDEUToB                 := 0021D6Ch
?SetHLUToA                 := 0021D70h
?SetHLUToB                 := 0021D74h
?SignExtendBC              := 0021D78h
?SignExtendDE              := 0021D7Ch
?SignExtendHL              := 0021D80h
?SetBCUTo0                 := 0021D84h
?SetDEUTo0                 := 0021D88h
?SetHLUTo0                 := 0021D8Ch
?DivHLByA                  := 0021D90h
?CpHLDE_s                  := 0021D94h
?CpHLDE_                   := 0021D98h
?LoadDEInd_s               := 0021D9Ch
?LoadDEInd                 := 0021DA0h
?CpHLDEBC                  := 0021DA4h
?NegBC                     := 0021DA8h
?NegDE                     := 0021DACh
?StrCmpre                  := 0021DB0h
?AddHLAndA                 := 0021DB4h
?NextFlashPage             := 0021DB8h
?PrevFlashPage             := 0021DBCh
?SwapEndianHL_s            := 0021DC0h
?ReloadAppEntryVecs        := 0021DC4h
;                          equ 0021DC8h
;                          equ 0021DCCh
;                          equ 0021DD0h
;                          equ 0021DD4h
;                          equ 0021DD8h
;                          equ 0021DDCh
?os.ClearVRAMLines         := 0021DE0h
?os.DisableCursor          := 0021DE4h
?os.EnableCursor           := 0021DE8h
;                          equ 0021DECh
;                          equ 0021DF0h
;                          equ 0021DF4h
;                          equ 0021DF8h
;                          equ 0021DFCh
?os.FontDrawText           := 0021E00h
;                          equ 0021E04h
;                          equ 0021E08h
;                          equ 0021E0Ch
;                          equ 0021E10h
?os.FontGetHeight          := 0021E14h
?os.FontGetWidth           := 0021E18h
?os.InitDrawing            := 0021E1Ch
?os.SetDrawBGColor         := 0021E20h
?os.SetDrawFGColor         := 0021E24h
?os.FontSelect             := 0021E28h
;                          equ 0021E2Ch
;                          equ 0021E30h
?os.ReturnByte             := 0021E34h
?os.ReturnByteEvenBetter   := 0021E38h
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
?ChkACplx                  := 0021E68h
;                          equ 0021E6Ch
?os.RclAns                 := 0021E70h
;                          equ 0021E74h
;                          equ 0021E78h
;                          equ 0021E7Ch
;                          equ 0021E80h
;                          equ 0021E84h
;                          equ 0021E88h
?SetPolarEquToOP1          := 0021E8Ch
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
?os.SetTimer1              := 0021EC8h
?os.DisableTimer1          := 0021ECCh
?os.SetKbdKey              := 0021ED0h
?os.GetSystemStats         := 0021ED4h
;                          equ 0021ED8h
;                          equ 0021EDCh
?DispHL                    := 0021EE0h
?os.GetDrawBGColor_BROKEN  := 0021EE4h		; fixed in OS 5.2
?os.GetDrawFGColor         := 0021EE8h
?os.FontGetID              := 0021EECh
;                          equ 0021EF0h
?os.RealToInt24            := 0021EF4h
?os.Int24ToReal            := 0021EF8h
?GetOpenLibPtr             := 0021EFCh
?RestoreColCoordinates     := 0021F00h
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
?VPutMapNoReset0IY23       := 0021F44h
;                          equ 0021F48h
;                          equ 0021F4Ch
?BufCpy                    := 0021F50h
;                          equ 0021F54h
;                          equ 0021F58h
;                          equ 0021F5Ch
?DrawStandardEntrySepLine  := 0021F60h
?DrawHomeNewSepLine        := 0021F64h
?DrawStatusBarText         := 0021F68h
;                          equ 0021F6Ch
;                          equ 0021F70h
;                          equ 0021F74h
;                          equ 0021F78h
;                          equ 0021F7Ch
?MovFrOP1OP2               := 0021F80h
;                          equ 0021F84h
;                          equ 0021F88h
;                          equ 0021F8Ch
;                          equ 0021F90h
;                          equ 0021F94h
?ChkInRam                  := 0021F98h
;                          equ 0021F9Ch
;                          equ 0021FA0h
?FontGetWidth              := 0021FA4h
?os.ForceCmdNoChar         := 0021FA8h
?os.DelVarEntry            := 0021FACh
?os.GetSymTablePtr         := 0021FB0h
?os.NextSymEntry           := 0021FB4h
?os.ChkFindSym             := 0021FB8h
?os.GetVarSize             := 0021FBCh
?os.GetVarSizeBytes        := 0021FC0h
;                          equ 0021FC4h
?os.GetRealListElement     := 0021FC8h
?os.GetRealVar             := 0021FCCh
?os.ResizeList             := 0021FD0h
?os.ResizeMatrix           := 0021FD4h
;                          equ 0021FD8h
?os.SetRealListElement     := 0021FDCh
?os.SetRealVar             := 0021FE0h
?os.GetAppVersionString    := 0021FE4h
;                          equ 0021FE8h
;                          equ 0021FECh
?os.MemChk                 := 0021FF0h
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
?ArcChk                    := 0022040h
?LoadDEIndFlash            := 0022044h
?ChkInRamB                 := 0022048h
;                          equ 002204Ch
;                          equ 0022050h
;                          equ 0022054h
?os.InitUSBDeviceCallback  := 0022058h
?os.KillUSBDevice          := 002205Ch
?os.SetUSBConfiguration    := 0022060h
?os.RequestUSBData         := 0022064h
?os.StopReceivingUSBData   := 0022068h
;                          equ 002206Ch
;                          equ 0022070h
?Mov11ToOP1                := 0022074h
?FindFreeArcSpot           := 0022078h
;                          equ 002207Ch
?os.SetTimer2              := 0022080h
?os.DisableTimer2          := 0022084h
;                          equ 0022088h
;;_ret                     equ 002208Ch
?os.GetYDrawLocation       := 0022090h
?os.SetYDrawLocation       := 0022094h
?RunLocalizeHook           := 0022098h
?os.IntSize                := 002209Ch
?os.ClearStatusBarLow      := 00220A0h
;                          equ 00220A4h
?NMIHandler                := 00220A8h
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
?os.RToP                   := 0022164h
?os.PToR                   := 0022168h
?os.ResetEditOpen          := 002216Ch
?os.FloatToReal            := 0022170h
?os.RealToFloat            := 0022174h
?os.FontDrawTransText      := 0022178h
?os.DelAppVar              := 002217Ch
?os.GetAppVarDataPtr       := 0022180h
?os.CreateAppVar           := 0022184h
;                          equ 0022188h
;                          equ 002218Ch
;                          equ 0022190h
;                          equ 0022194h
?os.CreateString           := 0022198h
?os.GetStringDataPtr       := 002219Ch
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
?boot.GetHardwareVers      := 0000084h
?boot.GetKeyID             := 0000088h
?boot.GetBootVerMinor      := 000008Ch
?boot.GetBootVerBuild      := 0000090h
?dbgout                    := 0000094h
?_longjmp                  := 0000098h
?_memchr                   := 000009Ch
?_memcmp                   := 00000A0h
?_memcpy                   := 00000A4h
?_memmove                  := 00000A8h
?_memset                   := 00000ACh
?_memclear                 := 00000B0h
?printf                    := 00000B4h
?_setjmp                   := 00000B8h
?sprintf                   := 00000BCh
?_strcat                   := 00000C0h
?_strchr                   := 00000C4h
?_strcmp                   := 00000C8h
?_strcpy                   := 00000CCh
?_strcspn                  := 00000D0h
?_strlen                   := 00000D4h
?_strncat                  := 00000D8h
?_strncmp                  := 00000DCh
?_strncpy                  := 00000E0h
?_strpbrk                  := 00000E4h
?_strrchr                  := 00000E8h
?_strspn                   := 00000ECh
?_strstr                   := 00000F0h
?strtok                    := 00000F4h
?ret                       := 00000F8h
?_bldiy                    := 00000FCh
?_bshl                     := 0000100h
?_bshru                    := 0000104h
?_bstiy                    := 0000108h
?_bstix                    := 000010Ch
?_case                     := 0000110h
?_case16                   := 0000114h
?_case16D                  := 0000118h
?_case24                   := 000011Ch
?_case24D                  := 0000120h
?_case8                    := 0000124h
?_case8D                   := 0000128h
?_frameset                 := 000012Ch
?_frameset0                := 0000130h
?_iand                     := 0000134h
?_icmpzero                 := 0000138h
?_idivs                    := 000013Ch
?_idivu                    := 0000140h
?_idvrmu                   := 0000144h
?_ildix                    := 0000148h
?_ildiy                    := 000014Ch
?_imul_b                   := 0000150h
?_imulu                    := 0000154h
?_imuls                    := 0000158h
?_indcall                  := 000015Ch
?_ineg                     := 0000160h
?_inot                     := 0000164h
?_ior                      := 0000168h
?_irems                    := 000016Ch
?_iremu                    := 0000170h
?_ishl                     := 0000174h
?_ishl_b                   := 0000178h
?_ishrs                    := 000017Ch
?_ishrs_b                  := 0000180h
?_ishru                    := 0000184h
?_ishru_b                  := 0000188h
?_istix                    := 000018Ch
?_istiy                    := 0000190h
?_itol                     := 0000194h
?_ixor                     := 0000198h
?_ladd                     := 000019Ch
?_ladd_b                   := 00001A0h
?_land                     := 00001A4h
?_lcmps                    := 00001A8h
?_lcmpu                    := 00001ACh
?_lcmpzero                 := 00001B0h
?_ldivs                    := 00001B4h
?_ldivu                    := 00001B8h
?_ldvrmu                   := 00001BCh
?_lldix                    := 00001C0h
?_lldiy                    := 00001C4h
?_lmuls                    := 00001C8h
?_lmulu                    := 00001CCh
?_lneg                     := 00001D0h
?_lnot                     := 00001D4h
?_lor                      := 00001D8h
?_lrems                    := 00001DCh
?_lremu                    := 00001E0h
?_lshl                     := 00001E4h
?_lshrs                    := 00001E8h
?_lshru                    := 00001ECh
?_lstix                    := 00001F0h
?_lstiy                    := 00001F4h
?_lsub                     := 00001F8h
?_lxor                     := 00001FCh
?_sand                     := 0000200h
?_scmpzero                 := 0000204h
?_sdivs                    := 0000208h
?_sdivu                    := 000020Ch
?_seqcase                  := 0000210h
?_seqcaseD                 := 0000214h
?_setflag                  := 0000218h
?_sldix                    := 000021Ch
?_sldiy                    := 0000220h
?_smuls                    := 0000224h
?_smulu                    := 0000228h
?_sneg                     := 000022Ch
?_snot                     := 0000230h
?_sor                      := 0000234h
?_srems                    := 0000238h
?_sremu                    := 000023Ch
?_sshl                     := 0000240h
?_sshl_b                   := 0000244h
?_sshrs                    := 0000248h
?_sshrs_b                  := 000024Ch
?_sshru                    := 0000250h
?_sshru_b                  := 0000254h
?_sstix                    := 0000258h
?_sstiy                    := 000025Ch
?_stoi                     := 0000260h
?_stoiu                    := 0000264h
?_sxor                     := 0000268h
?_fppack                   := 000026Ch
?_fadd                     := 0000270h
?_fcmp                     := 0000274h
?_fdiv                     := 0000278h
?_ftol                     := 000027Ch
?_ultof                    := 0000280h
?_ltof                     := 0000284h
?_fmul                     := 0000288h
?_fneg                     := 000028Ch
?_fsub                     := 0000290h
?FLTMAX                    := 0000294h
?sqrtf                     := 0000298h
?_frbtof                   := 000029Ch
?_frftob                   := 00002A0h
?_frftoub                  := 00002A4h
?_frftoi                   := 00002A8h
?_frftoui                  := 00002ACh
?_frftos                   := 00002B0h
?_frftous                  := 00002B4h
?_fritof                   := 00002B8h
?_fruitof                  := 00002BCh
?_frstof                   := 00002C0h
?_frubtof                  := 00002C4h
?_frustof                  := 00002C8h
?ResetPorts                := 00002CCh
?ChkIfOSInterruptAvailable := 00002D0h
?WriteFlashByte            := 00002D4h
?EraseFlash                := 00002D8h
?EraseFlashSector          := 00002DCh
?WriteFlash                := 00002E0h
?WriteFlashByteDuplicate   := 00002E4h
?WriteFlashA               := 00002E8h
?CleanupCertificate        := 00002ECh
?ClrHeap                   := 00002F0h
?CpyToHeap                 := 00002F4h
?ChkHeapTop                := 00002F8h
?ExecuteInRAM              := 00002FCh
?ExecuteInRAMDup           := 0000300h
?ExecuteInRAMDup2          := 0000304h
?ChkCertSpace              := 0000308h
?GetFieldSizeFromType      := 000030Ch
?FindFirstCertField        := 0000310h
?FindField                 := 0000314h
?FindNextField             := 0000318h
?GetCertificateEnd         := 000031Ch
?GetFieldSizeFromType_     := 0000320h
?GetFieldFromSize          := 0000324h
?NextFieldFromSize         := 0000328h
?NextFieldFromType         := 000032Ch
?GetOffsetToNextField      := 0000330h
?WriteFlashUnsafe          := 0000334h
?boot.GetCertCalcString    := 0000338h
?boot.GetCertCalcID        := 000033Ch
?GetSerial                 := 0000340h
;                          equ 0000344h
?Mult16By8                 := 0000348h
?Div16By8                  := 000034Ch
?Div16By16                 := 0000350h
?Div32By16                 := 0000354h
?CmpStr                    := 0000358h
?boot.Sha256Init           := 000035Ch
?boot.Sha256Part           := 0000360h
?boot.Sha256Hash           := 0000364h
?FindAppHeaderSubField     := 0000368h
;                          equ 000036Ch
?FindAppHeaderTimestamp    := 0000370h
?boot.ClearVRAM            := 0000374h
?boot.PutS                 := 0000378h
?PutSpinner                := 000037Ch
?boot.GetLFontPtr          := 0000380h
?boot.InitializeHardware   := 0000384h
?boot.TurnOffHardware      := 0000388h
?MakeColCmd                := 000038Ch
?boot.NewLine              := 0000390h
?PutBootVersion            := 0000394h
?DrawSectorProtectionTable := 0000398h
?boot.Set6MHzMode          := 000039Ch
?boot.Set48MHzMode         := 00003A0h
?boot.Set6MHzModeI         := 00003A4h
?boot.Set48MHzModeI        := 00003A8h
?CheckHardware             := 00003ACh
?GetBatteryStatus          := 00003B0h
?Delay10ms                 := 00003B4h
?DelayTenTimesAms          := 00003B8h
;                          equ 00003BCh
;                          equ 00003C0h
;                          equ 00003C4h
;                          equ 00003C8h
?usb_IsBusPowered          := 00003CCh
?KeypadScan                := 00003D0h
?KeypadScanFull            := 00003D4h
;_ret                      equ 00003D8h
;_ret                      equ 00003DCh
?MarkOSInvalid             := 00003E0h
?usb_BusPowered            := 00003E4h
?usb_SelfPowered           := 00003E8h
;                          equ 00003ECh
;                          equ 00003F0h
;                          equ 00003F4h
;                          equ 00003F8h
?usb_SetDeviceB            := 00003FCh
;                          equ 0000400h
?usb_DMACXReadNext         := 0000404h
?usb_DMACXWrite            := 0000408h
?usb_DMACXRead             := 000040Ch
?usb_DMACXWriteNext        := 0000410h
?usb_DMACXWriteCheck       := 0000414h
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
?MarkOSValid               := 0000460h
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
?usb_SetDMAState           := 00004A8h
?usb_DMATransfer           := 00004ACh
?usb_DMACXTransferWait     := 00004B0h
;                          equ 00004B4h
;                          equ 00004B8h
?usb_ResetFIFOS            := 00004BCh
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
?usb_ResetTimer            := 00004F0h
?usb_DisableTimer          := 00004F4h
?usb_EnableTimer           := 00004F8h
;                          equ 00004FCh
;                          equ 0000500h
;                          equ 0000504h
;                          equ 0000508h
;                          equ 000050Ch
;                          equ 0000510h
;                          equ 0000514h
;                          equ 0000518h
;                          equ 000051Ch
?boot.SetTimersControl     := 0000520h
?boot.GetTimersControl     := 0000524h
?boot.SetTimersInterrupt   := 0000528h
?boot.GetTimersInterrupt   := 000052Ch
?boot.SetTimersInterruptM  := 0000530h
?boot.GetTimersInterruptM  := 0000534h
?boot.SetTimer1Counter     := 0000538h
?boot.GetTimer1Counter     := 000053Ch
?boot.SetTimer1ReloadValue := 0000540h
?boot.GetTimer1ReloadValue := 0000544h
?boot.SetTimer1MatchValue1 := 0000548h
?boot.GetTimer1MatchValue1 := 000054Ch
?boot.SetTimer1MatchValue2 := 0000550h
?boot.GetTimer1MatchValue2 := 0000554h
?boot.SetTimer2Counter     := 0000558h
?boot.GetTimer2Counter     := 000055Ch
?boot.SetTimer2ReloadValue := 0000560h
?boot.GetTimer2ReloadValue := 0000564h
?boot.SetTimer2MatchValue1 := 0000568h
?boot.GetTimer2MatchValue1 := 000056Ch
?boot.SetTimer2MatchValue2 := 0000570h
?boot.GetTimer2MatchValue2 := 0000574h
?CheckIfEmulated           := 0000578h
?boot.GetOnInt             := 000057Ch
?boot.RTCIntHandler        := 0000580h
?boot.RTCInitialize        := 0000584h
?boot.RTCGetInitStatus     := 0000588h
?boot.RTCEnable            := 000058Ch
?boot.RTCDisable           := 0000590h
?boot.RTCSet24Hours        := 0000594h
;                          equ 0000598h
;                          equ 000059Ch
?boot.RTCAckAlarmInt       := 00005A0h
;                          equ 00005A4h
?boot.RTCWriteTime         := 00005A8h
?boot.RTCGetTime12Hour     := 00005ACh
?boot.RTCGetTime           := 00005B0h
?boot.RTCSetTime           := 00005B4h
?boot.RTCGetAlarm          := 00005B8h
?boot.RTCSetAlarmSafe      := 00005BCh
?boot.RTCCheckAlarmInt     := 00005C0h
?boot.RTCSetAlarmInt       := 00005C4h
?boot.RTCIsAfternoon       := 00005C8h
?boot.RTCGetDay            := 00005CCh
?boot.RTCSetAlarmIntSafe   := 00005D0h
?boot.RTCSetAlarm          := 00005D4h
?boot.RTCEnableInt         := 00005D8h
?boot.RTCDisableInt        := 00005DCh
?boot.RTCSetCallback       := 00005E0h
?boot.RTCResetTimeStruct   := 00005E4h
;                          equ 00005E8h
?boot.RTCSetFlags          := 00005ECh
;                          equ 00005F0h
?CheckEmulationBit         := 00005F4h
?usb_SetDMAAddress         := 00005F8h
;                          equ 00005FCh
?boot.SectorsBegin         := 0000600h
;                          equ 0000604h
?usb_InEndpointClrStall    := 0000608h
?usb_InEndpointSetStall    := 000060Ch
?usb_InEndpointClrReset    := 0000610h
?usb_InEndpointSetReset    := 0000614h
?usb_InEndpointSendZlp     := 0000618h
?usb_OutEndpointClrStall   := 000061Ch
?usb_OutEndpointSetStall   := 0000620h
?usb_OutEndpointClrReset   := 0000624h
?usb_OutEndpointSetReset   := 0000628h
?usb_SetFifoMap            := 000062Ch
?usb_SetEndpointConfig     := 0000630h
?usb_ClrEndpointConfig     := 0000634h
?usb_SetFifoConfig         := 0000638h
;                          equ 000063Ch

;RAM Equates
;--------------------------------
?ramStart		:= 0D00000h
?flags			:= 0D00080h		; location of OS Flags (+-80h)
?textFlagsLoc		:= 0D00085h            ; location of Text Flags
?apdFlagsLoc		:= 0D00088h		; location of APD Flags
?appFlagsLoc		:= 0D0008Dh		; location of App Flags
?rclFlagsLoc		:= 0D0008Eh            ; location of RCLQueue Flags
?shiftFlagsLoc		:= 0D00092h            ; location of Shifting Flags
?mathprintFlagsLoc	:= 0D000C4h		; location of MathPrint Flags

?strtokPtr		:= 0D000FFh            ; location of pointer used by C strtok
?printRoutine		:= 0D00108h            ; stores pointer to printing routines (3 scrap)

?flashByte		:= 0D00125h		; used for writing to flash

?cellOverrideAddr	:= 0D00166h
?curCell			:= 0D0016Eh            ; selected list cell

?SmallEditCancelParse	:= 0D001A4h

?curRowBackup		:= 0D0033Ch		; backup of curRow
?shiftFlagsLocBackup	:= 0D00358h		; backup of shiftFlagsLoc
?appFlagsLocBackup	:= 0D00366h		; backup of appFlagsLoc
?penRowBackup		:= 0D003E3h		; backup of penRow
?mathprintBackup		:= 0D003E6h		; backup of mathprint flags
?winLeftEdgeBackup	:= 0D003D2h		; backup of winLeftEdge
?catalogCurrentBackup	:= 0D003D3h		; backup of catalogCurrent
?menuCurrentSubBackup	:= 0D003D6h		; backup of menuCurrentSub
?menuNumMenusBackup	:= 0D003D8h		; backup of menuNumMenus
?menuCurrentBackup	:= 0D003DAh		; backup of menuCurrent
?cxCurAppBackup		:= 0D003DDh		; backup of cxCurApp

?curUnderBackup		:= 0D003E8h		; backup of curUnder

?appData			:= 0D00429h		; used for OFFSCRPT and ONSCRPT

?arcPtrEnd		:= 0D0052Fh

?tempSP			:= 0D0053Fh		; 3 byte scrap

?arcInfo			:= 0D00543h
?savedArcInfo		:= 0D0055Bh
?appBank_jump		:= 0D00584h

?kbdScanCode		:= 0D00587h		; scancode returned by GetCSC
?kbdLGSC			:= 0D00588h
?kbdPSC			:= 0D00589h
?kbdWUR			:= 0D0058Ah
?kbdDebncCnt		:= 0D0058Bh
?kbdKey			:= 0D0058Ch
?kbdGetKy		:= 0D0058Dh
?keyExtend		:= 0D0058Eh
?brightness		:= 0D0058Fh
?apdSubTimer		:= 0D00590h
?apdTimer		:= 0D00591h
?curTime			:= 0D00594h
?curRow			:= 0D00595h
?curCol			:= 0D00596h
?curOffset		:= 0D00598h
?curUnder		:= 0D00599h
?curYCol			:= 0D0059Ch
?curType			:= 0D0059Fh
?curXRow			:= 0D005A0h
?prevDData		:= 0D005A1h
?lFont_record		:= 0D005A4h
?sFont_record		:= 0D005C5h
?tokVarPtr		:= 0D005E9h
?tokLen			:= 0D005ECh

?indicCounter		:= 0D005F6h

?OP1			:= 0D005F8h
?OP1M			:= 0D005FAh
?OP2			:= 0D00603h
?OP2M			:= 0D00605h
?OP2EXT			:= 0D0060Ch
?OP3			:= 0D0060Eh
?OP3M			:= 0D00610h
?OP4			:= 0D00619h
?OP4M			:= 0D0061Bh
?OP5			:= 0D00624h
?OP5M			:= 0D00626h
?OP6			:= 0D0062Fh
?OP6M			:= 0D00631h
?OP6EXT			:= 0D00638h

?progToEdit		:= 0D0065Bh
?nameBuff		:= 0D00663h

?equ_edit_save		:= 0D0066Eh
?iMathPtr1		:= 0D0066Fh
?iMathPtr2		:= 0D00672h
?iMathPtr3		:= 0D00675h
?iMathPtr4		:= 0D00678h
?iMathPtr5		:= 0D0067Bh
?asm_data_ptr1		:= 0D0067Eh
?asm_data_ptr2		:= 0D00681h

?asm_ram			:= 0D00687h

?textShadow		:= 0D006C0h
?textShadCur		:= 0D007C4h
?textShadTop		:= 0D007C7h
?textShadAlph		:= 0D007C8h
?textShadIns		:= 0D007C9h
?cxMain			:= 0D007CAh
?cxPPutAway		:= 0D007CDh
?cxPutAway		:= 0D007D0h
?cxReDisp		:= 0D007D3h
?cxErrorEP		:= 0D007D6h
?cxSizeWind		:= 0D007D9h
?cxPage			:= 0D007DCh
?cxCurApp		:= 0D007E0h
?cxPrev			:= 0D007E2h ; 23 bytes are shadows of cxMain through cxCurApp and appFlags
?cxAppReturn		:= 0D007EBh

?onSP			:= 0D007FAh

?promptRow		:= 0D00800h
?promptCol		:= 0D00801h
?promptIns		:= 0D00802h
?promptShift		:= 0D00803h
?promptRet		:= 0D00804h
?promptValid		:= 0D00807h

?varType			:= 0D00813h
?varCurrent		:= 0D00814h
?varClass		:= 0D0081Ch

?catalogCurrent		:= 0D0081Dh ; word at this location starting with 6007h corresponds to what is highlighted in catalog
?catalogCurrentBackupM	:= 0D00820h ; backup of catalogCurrent for menus
?menuAppDepth		:= 0D00823h
?menuCurrent		:= 0D00824h
?menuCurrentSub		:= 0D00825h ; holds current submenu index
?menuSelected		:= 0D00826h ; holds currently selected item in current submenu
?menuNumMenus		:= 0D00827h ; holds number of submenus for this menu
?menuNumItems		:= 0D00828h ; holds number of items in this submenu
?appFlagsBackup		:= 0D00829h ; iy+appFlags backup for menu stuff
?cursorFlagsBackup	:= 0D0082Ah ; iy+cursorFlags backup for menu stuff
?curGStyleBackup		:= 0D0082Bh ; curGStyle backup for menu stuff
?graphFlagsBackup	:= 0D0082Ch ; iy+graphFlags backup for menu stuff

?progCurrent		:= 0D0082Dh
;D0082E	; something used to execute apps with _NewContext0
?userMenuSA		:= 0D00838h

?tempErrorMessage	:= 0D00842h

?ioPrompt		:= 0D00879h
?ioFlag			:= 0D00894h
?sndRecState		:= 0D00896h
?ioErrState		:= 0D00897h
?ioData			:= 0D008A1h

?penCol			:= 0D008D2h
?penRow			:= 0D008D5h
?rclQueue		:= 0D008D6h
?rclQueueEnd		:= 0D008D9h
?errNo			:= 0D008DFh
?errSP			:= 0D008E0h
?errOffset		:= 0D008E3h

?entryString		:= 0D008E6h
?entryResult		:= 0D008EAh

?statVarsOffset		:= 0D0117Fh
?asm_prgm_size		:= 0D0118Ch
?bstCounter		:= 0D0118Fh
?statVars		:= 0D01191h
?infVars			:= 0D013A4h
?infVar1			:= 0D013ADh
?infVar2			:= 0D013B6h
?infVar3			:= 0D013BFh
?infVar4			:= 0D013C8h
?infVar5			:= 0D013D1h
?infVar6			:= 0D013DAh
?infVar7			:= 0D013E3h
?infVar8			:= 0D013ECh
?infVar9			:= 0D013F5h
?infVar10		:= 0D013FEh
?infVar11		:= 0D01407h
?infVar12		:= 0D01410h
?infVar13		:= 0D01419h
?infVar14		:= 0D01422h
?infVar15		:= 0D0142Bh
?infVar16		:= 0D01434h
?infVar17		:= 0D0143Dh
?infVar18		:= 0D01446h
?infVar19		:= 0D0144Fh
?infVar20		:= 0D01458h

?curGStyle		:= 0D0146Dh
?curGY			:= 0D0146Eh
?curGY2			:= 0D01470h
?curGX2			:= 0D01471h ; currently selected equation while graphing
?freeSaveY		:= 0D01472h
?freeSaveX		:= 0D01474h

?XOffset			:= 0D014FAh
?YOffset			:= 0D014FCh
?lcdTallP		:= 0D014FDh
?pixWideP		:= 0D014FEh
?pixWide_m_1		:= 0D014FFh
?pixWide_m_2		:= 0D01501h
?lastEntryStkPtr		:= 0D01508h
?lastEntryStk		:= 0D0150Bh
?numLastEntries		:= 0D01D0Bh
?currLastEntry		:= 0D01D0Ch

?curPlotNumber		:= 0D01D45h

?curInc			:= 0D01D49h

?uXmin			:= 0D01D61h
?uXmax			:= 0D01D6Ah
?uXscl			:= 0D01D73h
?uYmin			:= 0D01D7Ch
?uYmax			:= 0D01D85h
?uYscl			:= 0D01D8Eh
?uThetMin		:= 0D01D97h
?uThetMax		:= 0D01DA0h
?uThetStep		:= 0D01DA9h
?uTmin			:= 0D01DB2h
?uTmax			:= 0D01DBBh
?uTStep			:= 0D01DC4h
?uPlotStart		:= 0D01DCDh
?unMax			:= 0D01DD6h
?uu0			:= 0D01DDFh
?uv0			:= 0D01DE8h
?unMin			:= 0D01DF1h
?uu02			:= 0D01DFAh
?uv02			:= 0D01E03h
?uw0			:= 0D01E0Ch
?uPlotStep		:= 0D01E15h
?uXres			:= 0D01E1Eh
?uw02			:= 0D01E27h
?Xmin			:= 0D01E33h
?Xmax			:= 0D01E3Ch
?Xscl			:= 0D01E45h
?Ymin			:= 0D01E4Eh
?Ymax			:= 0D01E57h
?Yscl			:= 0D01E60h
?ThetaMin		:= 0D01E69h
?ThetaMax		:= 0D01E72h
?ThetaStep		:= 0D01E7Bh
?TminPar			:= 0D01E84h
?TmaxPar			:= 0D01E8Dh
?Tstep			:= 0D01E96h
?PlotStart		:= 0D01E9Fh
?nMax			:= 0D01EA8h
?u0			:= 0D01EB1h
?v0			:= 0D01EBAh
?nMin			:= 0D01EC3h
?u02			:= 0D01ECCh
?v02			:= 0D01ED5h
?w0			:= 0D01EDEh
?PlotStep		:= 0D01EE7h
?XresO			:= 0D01EF0h
?w02			:= 0D01EF9h
?un1			:= 0D01F02h
?un2			:= 0D01F0Bh
?vn1			:= 0D01F14h
?vn2			:= 0D01F1Dh
?wn1			:= 0D01F26h
?wn2			:= 0D01F2Fh
?fin_N			:= 0D01F38h
?fin_I			:= 0D01F41h
?fin_PV			:= 0D01F4Ah
?fin_PMT			:= 0D01F53h
?fin_FV			:= 0D01F5Ch
?fin_PY			:= 0D01F65h
?fin_CY			:= 0D01F6Eh
?cal_N			:= 0D01F77h
?cal_I			:= 0D01F80h
?cal_PV			:= 0D01F89h
?cal_PMT			:= 0D01F92h
?cal_FV			:= 0D01F9Bh
?cal_PY			:= 0D01FA4h
?DeltaX			:= 0D01FAEh
?DeltaY			:= 0D01FB7h
?TraceStep		:= 0D0203Dh

?TblStart		:= 0D02267h
?DeltaTbl		:= 0D02270h
?Plot1MarkType		:= 0D0227Eh
?Plot1List1		:= 0D0227Fh
?Plot1List2		:= 0D02284h
?Plot1FreqList		:= 0D02289h
?Plot1XYOnOff		:= 0D0228Eh
?Plot1Color		:= 0D0228Fh

?Plot2MarkType		:= 0D02290h
?Plot2List1		:= 0D02291h
?Plot2List2		:= 0D02296h
?Plot2FreqList		:= 0D0229Bh
?Plot2XYOnOff		:= 0D022A0h
?Plot2Color		:= 0D022A1h

?Plot3MarkType		:= 0D022A2h
?Plot3List1		:= 0D022A3h
?Plot3List2		:= 0D022A8h
?Plot3FreqList		:= 0D022ADh
?Plot3XYOnOff		:= 0D022B2h
?Plot3Color		:= 0D022B3h

?ES			:= 0D022BAh

?seed1			:= 0D022FCh
?seed2			:= 0D02305h
?basic_prog		:= 0D0230Eh
?begPC			:= 0D02317h
?curPC			:= 0D0231Ah
?endPC			:= 0D0231Dh
?numArguments		:= 0D02320h

?cmdShadow		:= 0D0232Dh
?cmdShadCur		:= 0D02431h
?cmdShadAlph		:= 0D02433h
?cmdShadIns		:= 0D02435h
?cmdCursor		:= 0D02434h
?editTop			:= 0D02437h
?editCursor		:= 0D0243Ah
?editTail		:= 0D0243Dh
?editBtm			:= 0D02440h

?currListHighlight	:= 0D0244Bh ; word, this is offset into list for currently-highlighted element in list editor
?editSym			:= 0D0244Eh ; pointer to vat of variable being edited
?editDat			:= 0D02451h ; pointer to data of variable being edited

?currListPageOffset	:= 0D02457h
?currList		:= 0D02458h
?listName1		:= 0D02459h
?listName2		:= 0D0245Eh
?listName3		:= 0D02463h
?listName4		:= 0D02468h
?listName5		:= 0D0246Dh
?listName6		:= 0D02472h
?listName7		:= 0D02477h
?listName8		:= 0D0247Ch
?listName9		:= 0D02481h
?listName10		:= 0D02486h
?listName11		:= 0D0248Bh
?listName12		:= 0D02490h
?listName13		:= 0D02495h
?listName14		:= 0D0249Ah
?listName15		:= 0D0249Fh
?listName16		:= 0D024A4h
?listName17		:= 0D024A9h
?listName18		:= 0D024AEh
?listName19		:= 0D024B3h
?listName20		:= 0D024B8h
?currGrphStyle		:= 0D024BEh
?y1LineType		:= 0D024BFh
?y2LineType		:= 0D024C0h
?y3LineType		:= 0D024C1h
?y4LineType		:= 0D024C2h
?y5LineType		:= 0D024C3h
?y6LineType		:= 0D024C4h
?y7LineType		:= 0D024C5h
?y8LineType		:= 0D024C6h
?y9LineType		:= 0D024C7h
?y0LineType		:= 0D024C8h
?para1LineType		:= 0D024C9h
?para2LineType		:= 0D024CAh
?para3LineType		:= 0D024CBh
?para4LineType		:= 0D024CCh
?para5LineType		:= 0D024CDh
?para6LineType		:= 0D024CEh
?polar1LineType		:= 0D024CFh
?polar2LineType		:= 0D024D0h
?polar3LineType		:= 0D024D1h
?polar4LineType		:= 0D024D2h
?polar5LineType		:= 0D024D3h
?polar6LineType		:= 0D024D4h
?secULineType		:= 0D024D5h
?secVLineType		:= 0D024D6h
?secWLineType		:= 0D024D7h
?y1LineColor		:= 0D024D8h
?y2LineColor		:= 0D024D9h
?y3LineColor		:= 0D024DAh
?y4LineColor		:= 0D024DBh
?y5LineColor		:= 0D024DCh
?y6LineColor		:= 0D024DDh
?y7LineColor		:= 0D024DEh
?y8LineColor		:= 0D024DFh
?y9LineColor		:= 0D024E0h
?y0LineColor		:= 0D024E1h
?para1LineColor		:= 0D024E2h
?para2LineColor		:= 0D024E3h
?para3LineColor		:= 0D024E4h
?para4LineColor		:= 0D024E5h
?para5LineColor		:= 0D024E6h
?para6LineColor		:= 0D024E7h
?polar1LineColor		:= 0D024E8h
?polar2LineColor		:= 0D024E9h
?polar3LineColor		:= 0D024EAh
?polar4LineColor		:= 0D024EBh
?polar5LineColor		:= 0D024ECh
?polar6LineColor		:= 0D024EDh
?secULineColor		:= 0D024EEh
?secVLineColor		:= 0D024EFh
?secWLineColor		:= 0D024F0h

?winTop			:= 0D02504h
?winBtm			:= 0D02505h
?winLeftEdge		:= 0D02506h
?winLeft			:= 0D02507h
?winAbove		:= 0D02509h
?winRow			:= 0D0250Bh
?winCol			:= 0D0250Dh
?fmtDigits		:= 0D0250Fh
?fmtString		:= 0D02510h
?fmtLeft			:= 0D02561h
?fmtIndex		:= 0D02564h
?fmtMatSym		:= 0D02567h
?fmtMatMem		:= 0D0256Ah

?tSymPtr1		:= 0D0257Bh
?tSymPtr2		:= 0D0257Eh
?chkDelPtr3		:= 0D02581h
?chkDelPtr4		:= 0D02584h

?tempMem			:= 0D02587h
?FPSbase			:= 0D0258Ah
?FPS			:= 0D0258Dh
?OPBase			:= 0D02590h
?OPS			:= 0D02593h
?pTempCnt		:= 0D02596h
?cleanTmp		:= 0D02598h
?pTemp			:= 0D0259Ah
?progPtr			:= 0D0259Dh
?newDataPtr		:= 0D025A0h
?pagedGetPtr		:= 0D025A3h ; 3 byte scrap (unstable)
?pagedPutPtr		:= 0D025A6h

?appErr1			:= 0D025A9h ; use with _ErrCustom1
?appErr2			:= 0D025B6h ; use with _ErrCustom2

?arcPtr			:= 0D025C8h
?appRawKeyHandle		:= 0D025CBh
?customHeight		:= 0D025CEh
?localLanguage		:= 0D025CFh
?hookExecTemp		:= 0D025D2h
?cursorHookPtr		:= 0D025D5h
?libraryHookPtr		:= 0D025D8h
?rawKeyHookPtr		:= 0D025DBh
?getKeyHookPtr		:= 0D025DEh
?homescreenHookPtr	:= 0D025E1h
?windowHookPtr		:= 0D025E4h
?graphHookPtr		:= 0D025E7h
?yEqualsHookPtr		:= 0D025EAh
?fontHookPtr		:= 0D025EDh
?regraphHookPtr		:= 0D025F0h
?graphicsHookPtr		:= 0D025F3h
?traceHookPtr		:= 0D025F6h
?parserHookPtr		:= 0D025F9h
?appChangeHookPtr	:= 0D025FCh
?catalog1HookPtr		:= 0D025FFh
?helpHookPtr		:= 0D02602h
?cxRedispHookPtr		:= 0D02605h
?menuHookPtr		:= 0D02608h
?catalog2HookPtr		:= 0D0260Bh
?tokenHookPtr		:= 0D0260Eh
?localizeHookPtr		:= 0D02611h
?silentLinkHookPtr	:= 0D02614h
?USBActivityHookPtr	:= 0D0261Ah

?tempFreeArc		:= 0D02655h ; set after _ArcChk call

?textBGcolor		:= 0D02688h
?textFGcolor		:= 0D0268Ah

?drawBGColor		:= 0D026AAh
?drawFGColor		:= 0D026ACh
?drawColorCode		:= 0D026AEh

?keyToStrRam		:= 0D026EAh

?sEditMonSp		:= 0D02706h
?bpSave			:= 0D02709h

?batteryStatus		:= 0D02A86h

?graphBGColor		:= 0D02A98h

?errorLineY		:= 0D02A1Bh
?errorLineX		:= 0D02A23h

?fillRectColor		:= 0D02AC0h
?statusBarBGColor	:= 0D02ACCh

?scrapMem		:= 0D02AD7h ; 3 byte scrap (unstable)

?TempOP2ToOP6		:= 0D02B39h ; 55 bytes where OP2 to OP6 are temporary saved

?gCurYLoc		:= 0D02FD6h ; current y pixel location for C functions

;safeRAM Locations
;---------------------------------------------
;appData		equ 0D00429h ; 256 bytes
;textShadow		equ 0D006C0h ; 260 bytes	; Call _ClrTxtShdw to put spaces in here
;cmdShadow		equ 0D0232Dh ; 260 bytes
?pixelShadow		:= 0D031F6h ; 8400 bytes
?pixelShadow2		:= 0D052C6h ; 8400 bytes
?cmdPixelShadow		:= 0D07396h ; 8400 bytes
?plotSScreen		:= 0D09466h ; 21945 bytes	; Set GraphDraw Flag to redraw graph if used
?saveSScreen		:= 0D0EA1Fh ; 21945 bytes	; Set GraphDraw Flag to redraw graph if used
?cursorImage		:= 0E30800h ; 1020 bytes

;semiSafeRAM Locations
;---------------------------------------------
?usbArea			:= 0D13FD8h ; 14306 bytes used for usb, probably need to disable timer3/usb interrupts to use
?usbInited		:= 0D177B7h ; zero this byte while using usbArea and to reset the usb stack when interrupts are re-enabled
?heapBot			:= 0D1887Ch ; 1024 bytes used for flash ram routines, rest used rarely
?ramCodeTop		:= 0D18C7Ch
?heapTop			:= 0D1987Ch
?stackBot		:= 0D1987Eh
?stackTop		:= 0D1A87Eh

;RAM Equates Continued
;---------------------------------------------
?userMem			:= 0D1A881h
?symTable		:= 0D3FFFFh
?vRam			:= 0D40000h
?vRamEnd			:= 0D65800h

;Ports
;--------------------------------
?pCpuSpeed		:= 0001h
?pHardwareId		:= 0003h

;SHA256 Ports
;--------------------------------
?pShaRange		:= 02000h
?mpShaRange		:= 0E10000h

?shaCtrl			:= 00h ; 1 byte
?pShaCtrl		:= pShaRange + shaCtrl
?mpShaCtrl		:= mpShaRange + shaCtrl

?shaData			:= 10h ; 40h bytes
?pShaData		:= pShaRange + shaData
?mpShaData		:= mpShaRange + shaData

?shaState		:= 60h ; 20h bytes
?pShaState		:= pShaRange + shaState
?mpShaState		:= mpShaRange + shaState

;USB Ports
;--------------------------------
?pUsbRange		:= 03000h
?mpUsbRange		:= 0E20000h

?usbCapLen		:= 0000h
?pUsbCapLen		:= pUsbRange + usbCapLen
?mpUsbCapLen		:= mpUsbRange + usbCapLen

?usbHciVer		:= 0002h
?pUsbHciVer		:= pUsbRange + usbHciVer
?mpUsbHciVer		:= mpUsbRange + usbHciVer

?usbHcsParams		:= 0004h
?pUsbHcsParams		:= pUsbRange + usbHcsParams
?mpUsbHcsParams		:= mpUsbRange + usbHcsParams
?bUsbNumPorts		:= 0
?bmUsbNumPorts		:= 0Fh shl bUsbNumPorts
?bUsbPortPwrCtrl		:= 4
?bmUsbPortPwrCtrl	:= 1 shl bUsbPortPwrCtrl
?bUsbPortRoutRules	:= 7
?bmUsbPortRoutRules	:= 1 shl bUsbPortRoutRules
?bUsbNumPortsPerCC	:= 8
?bmUsbNumPortsPerCC	:= 0Fh shl bUsbNumPortsPerCC
?bUsbNumCC		:= 12
?bmUsbNumCC		:= 0Fh shl bUsbNumCC
?bUsbPortIndics		:= 16
?bmUsbPortIndics		:= 1 shl bUsbPortIndics
?bUsbDebugPortNum	:= 20
?bmUsbDebugPortNum	:= 0Fh shl bUsbDebugPortNum

?usbHccParams		:= 0008h
?pUsbHccParams		:= pUsbRange + usbHccParams
?mpUsbHccParams		:= mpUsbRange + usbHccParams
?bUsb64Bit		:= 0
?bmUsb64Bit		:= 1 shl bUsb64Bit
?bUsbProgFrameList	:= 1
?bmUsbProgFrameList	:= 1 shl bUsbProgFrameList
?bUsbAsyncSchedParkCap	:= 2
?bmUsbAsyncSchedParkCap	:= 1 shl bUsbAsyncSchedParkCap
?bUsbIsochSchedThresh	:= 4
?bmUsbIsochSchedThresh	:= 0Fh shl bUsbIsochSchedThresh
?bUsbEhciExtendCap	:= 8
?bmUsbEhciExtendCap	:= 0FFh shl bUsbEhciExtendCap

?usbHcspPortRout		:= 000Ch
?pUsbHcspPortRout	:= pUsbRange + usbHcspPortRout
?mpUsbHcspPortRout	:= mpUsbRange + usbHcspPortRout

?usbCmd			:= 0010h
?pUsbCmd			:= pUsbRange + usbCmd
?mpUsbCmd		:= mpUsbRange + usbCmd
?bUsbRunStop		:= 0
?bmUsbRunStop		:= 1 shl bUsbRunStop
?bUsbHcReset		:= 1
?bmUsbHcReset		:= 1 shl bUsbHcReset
?bUsbFrameListSize	:= 2
?bmUsbFrameListSize	:= 3 shl bUsbFrameListSize
?bUsbPeriodicSchedEn	:= 4
?bmUsbPeriodicSchedEn	:= 1 shl bUsbPeriodicSchedEn
?bUsbAsyncSchedEn	:= 5
?bmUsbAsyncSchedEn	:= 1 shl bUsbAsyncSchedEn
?bUsbIntAsyncAdvDrbl	:= 6
?bmUsbIntAsyncAdvDrbl	:= 1 shl bUsbIntAsyncAdvDrbl
?bUsbLightHcReset	:= 7
?bmUsbLightHcReset	:= 1 shl bUsbLightHcReset
?bUsbAsyncSchedParkCnt	:= 8
?bmUsbAsyncSchedParkCnt	:= 3 shl bUsbAsyncSchedParkCnt
?bUsbAsyncSchedParkEn	:= 11
?bmUsbAsyncSchedParkEn	:= 1 shl bUsbAsyncSchedParkEn
?bUsbIntThreshCtrl	:= 16
?bmUsbIntThreshCtrl	:= 0FFh shl bUsbIntThreshCtrl

?usbSts			:= 0014h
?pUsbSts			:= pUsbRange + usbSts
?mpUsbSts		:= mpUsbRange + usbSts
?usbIntEn		:= 0018h
?pUsbIntEn		:= pUsbRange + usbIntEn
?mpUsbIntEn		:= mpUsbRange + usbIntEn
?bUsbInt			:= 0
?bmUsbInt		:= 1 shl bUsbInt
?bUsbIntErr		:= 1
?bmUsbIntErr		:= 1 shl bUsbIntErr
?bUsbIntPortChgDetect	:= 2
?bmUsbIntPortChgDetect	:= 1 shl bUsbIntPortChgDetect
?bUsbIntFrameListOver	:= 3
?bmUsbIntFrameListOver	:= 1 shl bUsbIntFrameListOver
?bUsbIntHostSysErr	:= 4
?bmUsbIntHostSysErr	:= 1 shl bUsbIntHostSysErr
?bUsbIntAsyncAdv		:= 5
?bmUsbIntAsyncAdv	:= 1 shl bUsbIntAsyncAdv
?bUsbHcHalted		:= 12
?bmUsbHcHalted		:= 1 shl bUsbHcHalted
?bUsbReclamation		:= 13
?bmUsbReclamation	:= 1 shl bUsbReclamation
?bUsbPeriodicSchedSts	:= 14
?bmUsbPeriodicSchedSts	:= 1 shl bUsbPeriodicSchedSts
?bUsbAsyncSchedSts	:= 15
?bmUsbAsyncSchedSts	:= 1 shl bUsbAsyncSchedSts

?usbFrameIdx		:= 001Ch
?pUsbFrameIdx		:= pUsbRange + usbFrameIdx
?mpUsbFrameIdx		:= mpUsbRange + usbFrameIdx
?bUsbFrameIdx		:= 0
?bmUsbFrameIdx		:= 03FFFh shl bUsbFrameIdx

?usbCtrlDsSeg		:= 0020h
?pUsbCtrlDsSeg		:= pUsbRange + usbCtrlDsSeg
?mpUsbCtrlDsSeg		:= mpUsbRange + usbCtrlDsSeg

?usbPeriodicListBase	:= 0024h
?pUsbPeriodicListBase	:= pUsbRange + usbPeriodicListBase
?mpUsbPeriodicListBase	:= mpUsbRange + usbPeriodicListBase
?bUsbPeriodicListBase	:= 12
?bmUsbPeriodicListBase	:= 0FFFFFh shl bUsbPeriodicListBase

?usbAsyncListAddr	:= 0028h
?pUsbAsyncListAddr	:= pUsbRange + usbAsyncListAddr
?mpUsbAsyncListAddr	:= mpUsbRange + usbAsyncListAddr
?bUsbAsyncListAddr	:= 5
?bmUsbAsyncListAddr	:= 07FFFFFFh shl bUsbAsyncListAddr

?usbPortStsCtrl		:= 0030h
?pUsbPortStsCtrl		:= pUsbRange + usbPortStsCtrl
?mpUsbPortStsCtrl	:= mpUsbRange + usbPortStsCtrl
?bUsbCurConnSts		:= 0
?bmUsbCurConnSts		:= 1 shl bUsbCurConnSts
?bUsbConnStsChg		:= 1
?bmUsbConnStsChg		:= 1 shl bUsbConnStsChg
?bUsbPortEn		:= 2
?bmUsbPortEn		:= 1 shl bUsbPortEn
?bUsbPortEnChg		:= 3
?bmUsbPortEnChg		:= 1 shl bUsbPortEnChg
?bUsbOvercurrActive	:= 4
?bmUsbOvercurrActive	:= 1 shl bUsbOvercurrActive
?bUsbOvercurrChg		:= 5
?bmUsbOvercurrChg	:= 1 shl bUsbOvercurrChg
?bUsbForcePortResume	:= 6
?bmUsbForcePortResume	:= 1 shl bUsbForcePortResume
?bUsbPortSuspended	:= 7
?bmUsbPortSuspended	:= 1 shl bUsbPortSuspended
?bUsbPortReset		:= 8
?bmUsbPortReset		:= 1 shl bUsbPortReset
?bUsbLineSts		:= 10
?bmUsbLineSts		:= 3 shl bUsbLineSts
?bUsbPortPwr		:= 12
?bmUsbPortPwr		:= 1 shl bUsbPortPwr
?bUsbPortOwner		:= 13
?bmUsbPortOwner		:= 1 shl bUsbPortOwner
?bUsbPortIndicCtrl	:= 14
?bmUsbPortIndicCtrl	:= 3 shl bUsbPortIndicCtrl
?bUsbPortTestCtrl	:= 16
?bmUsbPortTestCtrl	:= 0Fh shl bUsbPortTestCtrl
?bUsbWakeConnEn		:= 20
?bmUsbWakeConnEn		:= 1 shl bUsbWakeConnEn
?bUsbWakeDiscEn		:= 21
?bmUsbWakeDiscEn		:= 1 shl bUsbWakeDiscEn
?bUsbWakeOvercurrEn	:= 22
?bmUsbWakeOvercurrEn	:= 1 shl bUsbWakeOvercurrEn

?usbMisc			:= 0040h
?pUsbMisc		:= pUsbRange + usbMisc
?mpUsbMisc		:= mpUsbRange + usbMisc
?bUsbAsyncSchedSleepTmr	:= 0
?bmUsbAsyncSchedSleepTmr	:= 3 shl bUsbAsyncSchedSleepTmr
?bUsbEof1Timing		:= 2
?bmUsbEof1Timing		:= 3 shl bUsbEof1Timing
?bUsbEof2Timing		:= 4
?bmUsbEof2Timing		:= 3 shl bUsbEof2Timing
?bUsbHostSuspend		:= 6
?bmUsbHostSuspend	:= 1 shl bUsbHostSuspend

?usbOtgCsr		:= 0080h
?pUsbOtgCsr		:= pUsbRange + usbOtgCsr
?mpUsbOtgCsr		:= mpUsbRange + usbOtgCsr
?bUsbBBusReq		:= 0
?bmUsbBBusReq		:= 1 shl bUsbBBusReq
?bUsbBHnp		:= 1
?bmUsbBHnp		:= 1 shl bUsbBHnp
?bUsbBVbusDisc		:= 2
?bmUsbBVbusDisc		:= 1 shl bUsbBVbusDisc
?bUsbABusReq		:= 4
?bmUsbABusReq		:= 1 shl bUsbABusReq
?bUsbABusDrop		:= 5
?bmUsbABusDrop		:= 1 shl bUsbABusDrop
?bUsbAHnp		:= 6
?bmUsbAHnp		:= 1 shl bUsbAHnp
?bUsbASrpEn		:= 7
?bmUsbASrpEn		:= 1 shl bUsbASrpEn
?bUsbASrpMode		:= 8
?usbASrpModeVbus		:= 0 shl bUsbASrpMode
?usbASrpModeData		:= 1 shl bUsbASrpMode
?bmUsbASrpMode		:= 1 shl bUsbASrpMode
?bUsbIdFilt		:= 9
?usbIdFiltShort		:= 0 shl bUsbIdFilt
?usbIdFiltLong		:= 1 shl bUsbIdFilt
?bmUsbIdFilt		:= 1 shl bUsbIdFilt
?bUsbVbusFilt		:= 10
?usbVbusFiltShort	:= 0 shl bUsbVbusFilt
?usbVbusFiltLong		:= 1 shl bUsbVbusFilt
?bmUsbVbusFilt		:= 1 shl bUsbVbusFilt
?bUsbHdiscFilt		:= 11
?usbHdiscFiltShort	:= 0 shl bUsbHdiscFilt
?usbHdiscFiltLong	:= 1 shl bUsbHdiscFilt
?bmUsbHdiscFilt		:= 1 shl bUsbHdiscFilt
?bUsbBSessEnd		:= 16
?bmUsbBSessEnd		:= 1 shl bUsbBSessEnd
?bUsbBSessVld		:= 17
?bmUsbBSessVld		:= 1 shl bUsbBSessVld
?bUsbASessVld		:= 18
?bmUsbASessVld		:= 1 shl bUsbASessVld
?bUsbAVbusVld		:= 19
?bmUsbAVbusVld		:= 1 shl bUsbAVbusVld
?bUsbRole		:= 20
?usbRoleHost		:= 0 shl bUsbRole
?usbRoleDev		:= 1 shl bUsbRole
?bmUsbRole		:= 1 shl bUsbRole
?bUsbId			:= 21
?usbIdA			:= 0 shl bUsbId
?usbIdB			:= 1 shl bUsbId
?bmUsbId			:= 1 shl bUsbId
?bUsbSpd			:= 22
?usbSpdFull		:= 0 shl bUsbSpd
?usbSpdLow		:= 1 shl bUsbSpd
?usbSpdHigh		:= 2 shl bUsbSpd
?bmUsbSpd		:= 3 shl bUsbSpd

?usbOtgIsr		:= 0084h
?pUsbOtgIsr		:= pUsbRange + usbOtgIsr
?mpUsbOtgIsr		:= mpUsbRange + usbOtgIsr
?usbOtgIer		:= 0088h
?pUsbOtgIer		:= pUsbRange + usbOtgIer
?mpUsbOtgIer		:= mpUsbRange + usbOtgIer
?bUsbIntBSrpComplete	:= 0
?bmUsbIntBSrpComplete	:= 1 shl bUsbIntBSrpComplete
?bUsbIntASrpDetect	:= 4
?bmUsbIntASrpDetect	:= 1 shl bUsbIntASrpDetect
?bUsbIntAVbusErr		:= 5
?bmUsbIntAVbusErr	:= 1 shl bUsbIntAVbusErr
?bUsbIntBSessEnd		:= 6
?bmUsbIntBSessEnd	:= 1 shl bUsbIntBSessEnd
?bUsbIntRoleChg		:= 8
?bmUsbIntRoleChg		:= 1 shl bUsbIntRoleChg
?bUsbIntIdChg		:= 9
?bmUsbIntIdChg		:= 1 shl bUsbIntIdChg
?bUsbIntOvercurr		:= 10
?bmUsbIntOvercurr	:= 1 shl bUsbIntOvercurr
?bUsbIntBPlugRemoved	:= 11
?bmUsbIntBPlugRemoved	:= 1 shl bUsbIntBPlugRemoved
?bUsbIntAPlugRemoved	:= 12
?bmUsbIntAPlugRemoved	:= 1 shl bUsbIntAPlugRemoved

?usbIsr			:= 00C0h
?pUsbIsr			:= pUsbRange + usbIsr
?mpUsbIsr		:= mpUsbRange + usbIsr
?usbImr			:= 00C4h
?pUsbImr			:= pUsbRange + usbImr
?mpUsbImr		:= mpUsbRange + usbImr
?bUsbIntDev		:= 0
?bmUsbIntDev		:= 1 shl bUsbIntDev
?bUsbIntOtg		:= 1
?bmUsbIntOtg		:= 1 shl bUsbIntOtg
?bUsbIntHost		:= 2
?bmUsbIntHost		:= 1 shl bUsbIntHost
?bUsbIntLevel		:= 3
?usbIntLevelLow		:= 0 shl bUsbIntLevel
?usbIntLevelHigh		:= 1 shl bUsbIntLevel
?bmUsbIntLevel		:= 1 shl bUsbIntLevel

?usbDevCtrl		:= 0100h
?pUsbDevCtrl		:= pUsbRange + usbDevCtrl
?mpUsbDevCtrl		:= mpUsbRange + usbDevCtrl
?bUsbRemoteWake		:= 0
?bmUsbRemoteWake		:= 1 shl bUsbRemoteWake
?bUsbHalfSpd		:= 1
?bmUsbHalfSpd		:= 1 shl bUsbHalfSpd
?bUsbGirqEn		:= 2
?bmUsbGirqEn		:= 1 shl bUsbGirqEn
?bUsbDevSuspend		:= 3
?bmUsbDevSuspend		:= 1 shl bUsbDevSuspend
?bUsbDevReset		:= 4
?bmUsbDevReset		:= 1 shl bUsbDevReset
?bUsbDevEn		:= 5
?bmUsbDevEn		:= 1 shl bUsbDevEn
?bUsbDevSpd		:= 6
?bmUsbDevSpd		:= 1 shl bUsbDevSpd
?bUsbDevForceFullSpd	:= 9
?bmUsbDevForceFullSpd	:= 1 shl bUsbDevForceFullSpd

?usbDevAddr		:= 0104h
?pUsbDevAddr		:= pUsbRange + usbDevAddr
?mpUsbDevAddr		:= mpUsbRange + usbDevAddr
?bUsbDevAddr		:= 0
?bmUsbDevAddr		:= 07Fh shl bUsbDevAddr
?bUsbDevConf		:= 7
?bmUsbDevConf		:= 1 shl bUsbDevConf

?usbDevTest		:= 0108h
?pUsbDevTest		:= pUsbRange + usbDevTest
?mpUsbDevTest		:= mpUsbRange + usbDevTest
?bUsbTstClrFifo		:= 0
?bmUsbTstClrFifo		:= 1 shl bUsbTstClrFifo
?bUsbTstCxLp		:= 1
?bmUsbTstCxLp		:= 1 shl bUsbTstCxLp
?bUsbTstClrEa		:= 2
?bmUsbTstClrEa		:= 1 shl bUsbTstClrEa
?bUsbTstNoCrc		:= 3
?bmUsbTstNoCrc		:= 1 shl bUsbTstNoCrc
?bUsbTstNoTs		:= 4
?bmUsbTstNoTs		:= 1 shl bUsbTstNoTs
?bUsbTstMode		:= 5
?bmUsbTstMode		:= 1 shl bUsbTstMode
?bUsbNoSof		:= 6
?bmUsbNoSof		:= 1 shl bUsbNoSof

?usbSofFrNum		:= 010Ch
?pUsbSofFrNum		:= pUsbRange + usbSofFrNum
?mpUsbSofFrNum		:= mpUsbRange + usbSofFrNum
?bUsbSofFrNum		:= 0
?bmUsbSofFrNum		:= 07FFh shl bUsbSofFrNum
?bUsbSofUFrNum		:= 11
?bmUsbSofUFrNum		:= 7 shl bUsbSofUFrNum

?usbSofMtr		:= 0110h
?pUsbSofMtr		:= pUsbRange + usbSofMtr
?mpUsbSofMtr		:= mpUsbRange + usbSofMtr
?bUsbSofMtrTmr		:= 0
?bmUsbSofMtrTmr		:= 0FFFFh shl bUsbSofMtrTmr

?usbPhyTmsr		:= 0114h
?pUsbPhyTmsr		:= pUsbRange + usbPhyTmsr
?mpUsbPhyTmsr		:= mpUsbRange + usbPhyTmsr
?bUsbUnplug		:= 0
?bmUsbUnplug		:= 1 shl bUsbUnplug
?bUsbTstJState		:= 1
?bmUsbTstJState		:= 1 shl bUsbTstJState
?bUsbTstKState		:= 2
?bmUsbTstKState		:= 1 shl bUsbTstKState
?bUsbTstSe0Nak		:= 3
?bmUsbTstSe0Nak		:= 1 shl bUsbTstSe0Nak
?bUsbTstPkt		:= 4
?bmUsbTstPkt		:= 1 shl bUsbTstPkt

?usbCxsr			:= 011Ch
?pUsbCxsr		:= pUsbRange + usbCxsr
?mpUsbCxsr		:= mpUsbRange + usbCxsr

?usbCxFifo		:= 0120h
?pUsbCxFifo		:= pUsbRange + usbCxFifo
?mpUsbCxFifo		:= mpUsbRange + usbCxFifo
?bCxFifoFin		:= 0
?bmCxFifoFin		:= 1 shl bCxFifoFin
?bTstPktFin		:= 1
?bmTstPktFin		:= 1 shl bTstPktFin
?bCxFifoStall		:= 2
?bmCxFifoStall		:= 1 shl bCxFifoStall
?bCxFifoClr		:= 3
?bmCxFifoClr		:= 1 shl bCxFifoClr
?bCxFifoFull		:= 4
?bmCxFifoFull		:= 1 shl bCxFifoFull
?bCxFifoEmpty		:= 5
?bmCxFifoEmpty		:= 1 shl bCxFifoEmpty
?bFifo0Empty		:= 8
?bmFifo0Empty		:= 1 shl bFifo0Empty
?bFifo1Empty		:= 9
?bmFifo1Empty		:= 1 shl bFifo1Empty
?bFifo2Empty		:= 10
?bmFifo2Empty		:= 1 shl bFifo2Empty
?bFifo3Empty		:= 11
?bmFifo3Empty		:= 1 shl bFifo3Empty
?bFifoEmpty		:= 8
?bmFifoEmpty		:= 0Fh shl bFifoEmpty

?usbIdle			:= 0124h
?pUsbIdle		:= pUsbRange + usbIdle
?mpUsbIdle		:= mpUsbRange + usbIdle
?bUsbIdleMs		:= 0
?bmUsbIdleMs		:= 7 shl bUsbIdleMs

?usbGimr			:= 0130h
?pUsbGimr		:= pUsbRange + usbGimr
?mpUsbGimr		:= mpUsbRange + usbGimr
?usbGisr			:= 0140h
?pUsbGisr		:= pUsbRange + usbGisr
?mpUsbGisr		:= mpUsbRange + usbGisr
?bUsbDevIntCx		:= 0
?bmUsbDevIntCx		:= 1 shl bUsbDevIntCx
?bUsbDevIntFifo		:= 1
?bmUsbDevIntFifo		:= 1 shl bUsbDevIntFifo
?bUsbDevIntDev		:= 2
?bmUsbDevIntDev		:= 1 shl bUsbDevIntDev

?usbCxImr		:= 0134h
?pUsbCxImr		:= pUsbRange + usbCxImr
?mpUsbCxImr		:= mpUsbRange + usbCxImr
?usbCxIsr		:= 0144h
?pUsbCxIsr		:= pUsbRange + usbCxIsr
?mpUsbCxIsr		:= mpUsbRange + usbCxIsr
?bUsbIntCxSetup		:= 0
?bmUsbIntCxSetup		:= 1 shl bUsbIntCxSetup
?bUsbIntCxIn		:= 1
?bmUsbIntCxIn		:= 1 shl bUsbIntCxIn
?bUsbIntCxOut		:= 2
?bmUsbIntCxOut		:= 1 shl bUsbIntCxOut
?bUsbIntCxEnd		:= 3
?bmUsbIntCxEnd		:= 1 shl bUsbIntCxEnd
?bUsbIntCxErr		:= 4
?bmUsbIntCxErr		:= 1 shl bUsbIntCxErr
?bUsbIntCxAbort		:= 5
?bmUsbIntCxAbort		:= 1 shl bUsbIntCxAbort
?bUsbIntCx		:= 0
?bmUsbIntCx		:= 01Fh shl bUsbIntCx

?usbFifoRxImr		:= 0138h
?pUsbFifoRxImr		:= pUsbRange + usbFifoRxImr
?mpUsbFifoRxImr		:= mpUsbRange + usbFifoRxImr
?usbFifoRxIsr		:= 0148h
?pUsbFifoRxIsr		:= pUsbRange + usbFifoRxIsr
?mpUsbFifoRxIsr		:= mpUsbRange + usbFifoRxIsr
?bUsbIntFifo0Out		:= 0
?bmUsbIntFifo0Out	:= 1 shl bUsbIntFifo0Out
?bUsbIntFifo0Spk		:= 1
?bmUsbIntFifo0Spk	:= 1 shl bUsbIntFifo0Spk
?bUsbIntFifo1Out		:= 2
?bmUsbIntFifo1Out	:= 1 shl bUsbIntFifo1Out
?bUsbIntFifo1Spk		:= 3
?bmUsbIntFifo1Spk	:= 1 shl bUsbIntFifo1Spk
?bUsbIntFifo2Out		:= 4
?bmUsbIntFifo2Out	:= 1 shl bUsbIntFifo2Out
?bUsbIntFifo2Spk		:= 5
?bmUsbIntFifo2Spk	:= 1 shl bUsbIntFifo2Spk
?bUsbIntFifo3Out		:= 6
?bmUsbIntFifo3Out	:= 1 shl bUsbIntFifo3Out
?bUsbIntFifo3Spk		:= 7
?bmUsbIntFifo3Spk	:= 1 shl bUsbIntFifo3Spk
?bUsbFifoRxInts		:= 0
?bmUsbFifoRxInts		:= 0FFh shl bUsbFifoRxInts

?usbFifoTxImr		:= 013Ah
?pUsbFifoTxImr		:= pUsbRange + usbFifoTxImr
?mpUsbFifoTxImr		:= mpUsbRange + usbFifoTxImr
?usbFifoTxIsr		:= 014Ah
?pUsbFifoTxIsr		:= pUsbRange + usbFifoTxIsr
?mpUsbFifoTxIsr		:= mpUsbRange + usbFifoTxIsr
?bUsbIntFifo0In		:= 0
?bmUsbIntFifo0In		:= 1 shl bUsbIntFifo0In
?bUsbIntFifo1In		:= 1
?bmUsbIntFifo1In		:= 1 shl bUsbIntFifo1In
?bUsbIntFifo2In		:= 2
?bmUsbIntFifo2In		:= 1 shl bUsbIntFifo2In
?bUsbIntFifo3In		:= 3
?bmUsbIntFifo3In		:= 1 shl bUsbIntFifo3In
?bUsbFifoTxInts		:= 0
?bmUsbFifoTxInts		:= 0Fh shl bUsbFifoTxInts

?usbDevImr		:= 013Ch
?pUsbDevImr		:= pUsbRange + usbDevImr
?mpUsbDevImr		:= mpUsbRange + usbDevImr
?usbDevIsr		:= 014Ch
?pUsbDevIsr		:= pUsbRange + usbDevIsr
?mpUsbDevIsr		:= mpUsbRange + usbDevIsr
?bUsbIntDevReset		:= 0
?bmUsbIntDevReset	:= 1 shl bUsbIntDevReset
?bUsbIntDevSuspend	:= 1
?bmUsbIntDevSuspend	:= 1 shl bUsbIntDevSuspend
?bUsbIntDevResume	:= 2
?bmUsbIntDevResume	:= 1 shl bUsbIntDevResume
?bUsbIntDevIsocErr	:= 3
?bmUsbIntDevIsocErr	:= 1 shl bUsbIntDevIsocErr
?bUsbIntDevIsocAbt	:= 4
?bmUsbIntDevIsocAbt	:= 1 shl bUsbIntDevIsocAbt
?bUsbIntDevZlpTx		:= 5
?bmUsbIntDevZlpTx	:= 1 shl bUsbIntDevZlpTx
?bUsbIntDevZlpRx		:= 6
?bmUsbIntDevZlpRx	:= 1 shl bUsbIntDevZlpRx
?bUsbIntDevDmaFin	:= 7
?bmUsbIntDevDmaFin	:= 1 shl bUsbIntDevDmaFin
?bUsbIntDevDmaErr	:= 8
?bmUsbIntDevDmaErr	:= 1 shl bUsbIntDevDmaErr
?bUsbIntDevIdle		:= 9
?bmUsbIntDevIdle		:= 1 shl bUsbIntDevIdle
?bUsbIntDevWakeup	:= 10
?bmUsbIntDevWakeup	:= 1 shl bUsbIntDevWakeup
?bUsbDevInts		:= 0
?bmUsbDevInts		:= 07FFh shl bUsbDevInts

?usbRxZlp		:= 0150h
?pUsbRxZlp		:= pUsbRange + usbRxZlp
?mpUsbRxZlp		:= mpUsbRange + usbRxZlp
?usbTxZlp		:= 0154h
?pUsbTxZlp		:= pUsbRange + usbTxZlp
?mpUsbTxZlp		:= mpUsbRange + usbTxZlp
?bUsbEp1Zlp		:= 0
?bmUsbEp1Zlp		:= 1 shl bUsbEp1Zlp
?bUsbEp2Zlp		:= 1
?bmUsbEp2Zlp		:= 1 shl bUsbEp2Zlp
?bUsbEp3Zlp		:= 2
?bmUsbEp3Zlp		:= 1 shl bUsbEp3Zlp
?bUsbEp4Zlp		:= 3
?bmUsbEp4Zlp		:= 1 shl bUsbEp4Zlp
?bUsbEp5Zlp		:= 4
?bmUsbEp5Zlp		:= 1 shl bUsbEp5Zlp
?bUsbEp6Zlp		:= 5
?bmUsbEp6Zlp		:= 1 shl bUsbEp6Zlp
?bUsbEp7Zlp		:= 6
?bmUsbEp7Zlp		:= 1 shl bUsbEp7Zlp
?bUsbEp8Zlp		:= 7
?bmUsbEp8Zlp		:= 1 shl bUsbEp8Zlp
?bUsbZlp			:= 0
?bmUsbZlp		:= 0FFh shl bUsbZlp

?usbIsoEasr		:= 0158h
?pUsbIsoEasr		:= pUsbRange + usbIsoEasr
?mpUsbIsoEasr		:= mpUsbRange + usbIsoEasr
?bUsbEp1IsocAbort	:= 0
?bmUsbEp1IsocAbort	:= 1 shl bUsbEp1IsocAbort
?bUsbEp2IsocAbort	:= 1
?bmUsbEp2IsocAbort	:= 1 shl bUsbEp2IsocAbort
?bUsbEp3IsocAbort	:= 2
?bmUsbEp3IsocAbort	:= 1 shl bUsbEp3IsocAbort
?bUsbEp4IsocAbort	:= 3
?bmUsbEp4IsocAbort	:= 1 shl bUsbEp4IsocAbort
?bUsbEp5IsocAbort	:= 4
?bmUsbEp5IsocAbort	:= 1 shl bUsbEp5IsocAbort
?bUsbEp6IsocAbort	:= 5
?bmUsbEp6IsocAbort	:= 1 shl bUsbEp6IsocAbort
?bUsbEp7IsocAbort	:= 6
?bmUsbEp7IsocAbort	:= 1 shl bUsbEp7IsocAbort
?bUsbEp8IsocAbort	:= 7
?bmUsbEp8IsocAbort	:= 1 shl bUsbEp8IsocAbort
?bUsbEp1IsocErr		:= 16
?bmUsbEp1IsocErr		:= 1 shl bUsbEp1IsocErr
?bUsbEp2IsocErr		:= 17
?bmUsbEp2IsocErr		:= 1 shl bUsbEp2IsocErr
?bUsbEp3IsocErr		:= 18
?bmUsbEp3IsocErr		:= 1 shl bUsbEp3IsocErr
?bUsbEp4IsocErr		:= 19
?bmUsbEp4IsocErr		:= 1 shl bUsbEp4IsocErr
?bUsbEp5IsocErr		:= 20
?bmUsbEp5IsocErr		:= 1 shl bUsbEp5IsocErr
?bUsbEp6IsocErr		:= 21
?bmUsbEp6IsocErr		:= 1 shl bUsbEp6IsocErr
?bUsbEp7IsocErr		:= 22
?bmUsbEp7IsocErr		:= 1 shl bUsbEp7IsocErr
?bUsbEp8IsocErr		:= 23
?bmUsbEp8IsocErr		:= 1 shl bUsbEp8IsocErr

?usbInEp1		:= 0160h
?pUsbInEp1		:= pUsbRange + usbInEp1
?mpUsbInEp1		:= mpUsbRange + usbInEp1
?usbInEp2		:= 0164h
?pUsbInEp2		:= pUsbRange + usbInEp2
?mpUsbInEp2		:= mpUsbRange + usbInEp2
?usbInEp3		:= 0168h
?pUsbInEp3		:= pUsbRange + usbInEp3
?mpUsbInEp3		:= mpUsbRange + usbInEp3
?usbInEp4		:= 016Ch
?pUsbInEp4		:= pUsbRange + usbInEp4
?mpUsbInEp4		:= mpUsbRange + usbInEp4
?usbInEp5		:= 0170h
?pUsbInEp5		:= pUsbRange + usbInEp5
?mpUsbInEp5		:= mpUsbRange + usbInEp5
?usbInEp6		:= 0174h
?pUsbInEp6		:= pUsbRange + usbInEp6
?mpUsbInEp6		:= mpUsbRange + usbInEp6
?usbInEp7		:= 0178h
?pUsbInEp7		:= pUsbRange + usbInEp7
?mpUsbInEp7		:= mpUsbRange + usbInEp7
?usbInEp8		:= 017Ch
?pUsbInEp8		:= pUsbRange + usbInEp8
?mpUsbInEp8		:= mpUsbRange + usbInEp8
?usbOutEp1		:= 0180h
?pUsbOutEp1		:= pUsbRange + usbOutEp1
?mpUsbOutEp1		:= mpUsbRange + usbOutEp1
?usbOutEp2		:= 0184h
?pUsbOutEp2		:= pUsbRange + usbOutEp2
?mpUsbOutEp2		:= mpUsbRange + usbOutEp2
?usbOutEp3		:= 0188h
?pUsbOutEp3		:= pUsbRange + usbOutEp3
?mpUsbOutEp3		:= mpUsbRange + usbOutEp3
?usbOutEp4		:= 018Ch
?pUsbOutEp4		:= pUsbRange + usbOutEp4
?mpUsbOutEp4		:= mpUsbRange + usbOutEp4
?usbOutEp5		:= 0190h
?pUsbOutEp5		:= pUsbRange + usbOutEp5
?mpUsbOutEp5		:= mpUsbRange + usbOutEp5
?usbOutEp6		:= 0194h
?pUsbOutEp6		:= pUsbRange + usbOutEp6
?mpUsbOutEp6		:= mpUsbRange + usbOutEp6
?usbOutEp7		:= 0198h
?pUsbOutEp7		:= pUsbRange + usbOutEp7
?mpUsbOutEp7		:= mpUsbRange + usbOutEp7
?usbOutEp8		:= 019Ch
?pUsbOutEp8		:= pUsbRange + usbOutEp8
?mpUsbOutEp8		:= mpUsbRange + usbOutEp8
?bUsbEpMaxPktSz		:= 0
?bmUsbEpMaxPktSz		:= 07FFh shl bUsbEpMaxPktSz
?bUsbEpStall		:= 11
?bmUsbEpStall		:= 1 shl bUsbEpStall
?bUsbEpReset		:= 12
?bmUsbEpReset		:= 1 shl bUsbEpReset
?bUsbInEpTxNum		:= 13
?bmUsbInEpTxNum		:= 3 shl bUsbInEpTxNum
?bUsbInEpSendZlp		:= 15
?bmUsbInEpSendZlp	:= 1 shl bUsbInEpSendZlp

?usbEp1Map		:= 01A0h
?pUsbEp1Map		:= pUsbRange + usbEp1Map
?mpUsbEp1Map		:= mpUsbRange + usbEp1Map
?usbEp2Map		:= 01A1h
?pUsbEp2Map		:= pUsbRange + usbEp2Map
?mpUsbEp2Map		:= mpUsbRange + usbEp2Map
?usbEp3Map		:= 01A2h
?pUsbEp3Map		:= pUsbRange + usbEp3Map
?mpUsbEp3Map		:= mpUsbRange + usbEp3Map
?usbEp4Map		:= 01A3h
?pUsbEp4Map		:= pUsbRange + usbEp4Map
?mpUsbEp4Map		:= mpUsbRange + usbEp4Map
?usbEp5Map		:= 01A4h
?pUsbEp5Map		:= pUsbRange + usbEp5Map
?mpUsbEp5Map		:= mpUsbRange + usbEp5Map
?usbEp6Map		:= 01A5h
?pUsbEp6Map		:= pUsbRange + usbEp6Map
?mpUsbEp6Map		:= mpUsbRange + usbEp6Map
?usbEp7Map		:= 01A6h
?pUsbEp7Map		:= pUsbRange + usbEp7Map
?mpUsbEp7Map		:= mpUsbRange + usbEp7Map
?usbEp8Map		:= 01A7h
?pUsbEp8Map		:= pUsbRange + usbEp8Map
?mpUsbEp8Map		:= mpUsbRange + usbEp8Map
?bUsbEpMapIn		:= 0
?bmUsbEpMapIn		:= 0Fh shl bUsbEpMapIn
?bUsbEpMapOut		:= 4
?bmUsbEpMapOut		:= 0Fh shl bUsbEpMapOut

?usbFifo0Map		:= 01A8h
?pUsbFifo0Map		:= pUsbRange + usbFifo0Map
?mpUsbFifo0Map		:= mpUsbRange + usbFifo0Map
?usbFifo1Map		:= 01A9h
?pUsbFifo1Map		:= pUsbRange + usbFifo1Map
?mpUsbFifo1Map		:= mpUsbRange + usbFifo1Map
?usbFifo2Map		:= 01AAh
?pUsbFifo2Map		:= pUsbRange + usbFifo2Map
?mpUsbFifo2Map		:= mpUsbRange + usbFifo2Map
?usbFifo3Map		:= 01ABh
?pUsbFifo3Map		:= pUsbRange + usbFifo3Map
?mpUsbFifo3Map		:= mpUsbRange + usbFifo3Map
?bUsbFifoEp		:= 0
?bmUsbFifoEp		:= 0Fh shl bUsbFifoEp
?bUsbFifoDir		:= 4
?usbFifoOut		:= 0 shl bUsbFifoDir
?usbFifoIn		:= 1 shl bUsbFifoDir
?usbFifoBi		:= 2 shl bUsbFifoDir
?bmUsbFifoDir		:= 3 shl bUsbFifoDir

?usbFifo0Cfg		:= 01ACh
?pUsbFifo0Cfg		:= pUsbRange + usbFifo0Cfg
?mpUsbFifo0Cfg		:= mpUsbRange + usbFifo0Cfg
?usbFifo1Cfg		:= 01ADh
?pUsbFifo1Cfg		:= pUsbRange + usbFifo1Cfg
?mpUsbFifo1Cfg		:= mpUsbRange + usbFifo1Cfg
?usbFifo2Cfg		:= 01AEh
?pUsbFifo2Cfg		:= pUsbRange + usbFifo2Cfg
?mpUsbFifo2Cfg		:= mpUsbRange + usbFifo2Cfg
?usbFifo3Cfg		:= 01AFh
?pUsbFifo3Cfg		:= pUsbRange + usbFifo3Cfg
?mpUsbFifo3Cfg		:= mpUsbRange + usbFifo3Cfg
?bUsbFifoType		:= 0
?usbFifoIsoc		:= 1 shl bUsbFifoType
?usbFifoBulk		:= 2 shl bUsbFifoType
?usbFifoIntr		:= 3 shl bUsbFifoType
?bmUsbFifoType		:= 3 shl bUsbFifoType
?bUsbFifoNumBlks		:= 2
?usbFifo1Blk		:= 0 shl bUsbFifoNumBlks
?usbFifo2Blks		:= 1 shl bUsbFifoNumBlks
?usbFifo3Blks		:= 2 shl bUsbFifoNumBlks
?bmUsbFifoNumBlks	:= 3 shl bUsbFifoNumBlks
?bUsbFifoBlkSz		:= 4
?usbFifoBlkSz512		:= 0 shl bUsbFifoBlkSz
?usbFifoBlkSz1024	:= 1 shl bUsbFifoBlkSz
?bmUsbFifoBlkSz		:= 1 shl bUsbFifoBlkSz
?bUsbFifoEn		:= 5
?bmUsbFifoEn		:= 1 shl bUsbFifoEn

?usbFifo0Csr		:= 01B0h
?pUsbFifo0Csr		:= pUsbRange + usbFifo0Csr
?mpUsbFifo0Csr		:= mpUsbRange + usbFifo0Csr
?usbFifo1Csr		:= 01B4h
?pUsbFifo1Csr		:= pUsbRange + usbFifo1Csr
?mpUsbFifo1Csr		:= mpUsbRange + usbFifo1Csr
?usbFifo2Csr		:= 01B8h
?pUsbFifo2Csr		:= pUsbRange + usbFifo2Csr
?mpUsbFifo2Csr		:= mpUsbRange + usbFifo2Csr
?usbFifo3Csr		:= 01BCh
?pUsbFifo3Csr		:= pUsbRange + usbFifo3Csr
?mpUsbFifo3Csr		:= mpUsbRange + usbFifo3Csr
?bUsbFifoLen		:= 0
?bmUsbFifoLen		:= 07FFh shl bUsbFifoLen
?bUsbFifoReset		:= 12
?bmUsbFifoReset		:= 1 shl bUsbFifoReset

?usbDmaFifo		:= 01C0h
?pUsbDmaFifo		:= pUsbRange + usbDmaFifo
?mpUsbDmaFifo		:= mpUsbRange + usbDmaFifo
?bUsbDmaFifo0		:= 0
?bmUsbDmaFifo0		:= 1 shl bUsbDmaFifo0
?bUsbDmaFifo1		:= 1
?bmUsbDmaFifo1		:= 1 shl bUsbDmaFifo1
?bUsbDmaFifo2		:= 2
?bmUsbDmaFifo2		:= 1 shl bUsbDmaFifo2
?bUsbDmaFifo3		:= 3
?bmUsbDmaFifo3		:= 1 shl bUsbDmaFifo3
?bUsbDmaCxFifo		:= 4
?bmUsbDmaCxFifo		:= 1 shl bUsbDmaCxFifo
?bUsbDmaFifo		:= 0
?bmUsbDmaNoFifo		:= 0 shl bUsbDmaFifo
?bmUsbDmaFifo		:= 01Fh shl bUsbDmaFifo

?usbDmaCtrl		:= 01C8h
?pUsbDmaCtrl		:= pUsbRange + usbDmaCtrl
?mpUsbDmaCtrl		:= mpUsbRange + usbDmaCtrl
?bUsbDmaStart		:= 0
?bmUsbDmaStart		:= 1 shl bUsbDmaStart
?bUsbDmaDir		:= 1
?usbDmaFifo2Mem		:= 0 shl bUsbDmaDir
?usbDmaMem2Fifo		:= 1 shl bUsbDmaDir
?usbDmaFifo2Fifo		:= 2 shl bUsbDmaDir
?bmUsbDmaDir		:= 3 shl bUsbDmaDir
?bUsbDmaAbort		:= 3
?bmUsbDmaAbort		:= 1 shl bUsbDmaAbort
?bUsbDmaClrFifo		:= 4
?bmUsbDmaClrFifo		:= 1 shl bUsbDmaClrFifo

?usbDmaLen		:= 01C9h
?pUsbDmaLen		:= pUsbRange + usbDmaLen
?mpUsbDmaLen		:= mpUsbRange + usbDmaLen
?bUsbDmaLen		:= 0
?bmUsbDmaLen		:= 01FFFFh shl bUsbDmaLen

?usbDmaAddr		:= 01CCh
?pUsbDmaAddr		:= pUsbRange + usbDmaAddr
?mpUsbDmaAddr		:= mpUsbRange + usbDmaAddr
?bUsbDmaAddr		:= 0
?bmUsbDmaAddr		:= 07FFFFh shl bUsbDmaAddr

?usbEp0Data		:= 01D0h
?pUsbEp0Data		:= pUsbRange + usbEp0Data
?mpUsbEp0Data		:= mpUsbRange + usbEp0Data
?bUsbEp0Data		:= 0
?bmUsbEp0Data		:= 0FFFFFFFFh shl bUsbEp0Data

;LCD Ports
;--------------------------------
?pLcdRange		:= 04000h
?mpLcdRange		:= 0E30000h

?lcdTiming0		:= 0000h
?pLcdTiming0		:= pLcdRange + lcdTiming0
?mpLcdTiming0		:= mpLcdRange + lcdTiming0
?lcdTiming1		:= 0004h
?pLcdTiming1		:= pLcdRange + lcdTiming1
?mpLcdTiming1		:= mpLcdRange + lcdTiming1
?lcdTiming2		:= 0008h
?pLcdTiming2		:= pLcdRange + lcdTiming2
?mpLcdTiming2		:= mpLcdRange + lcdTiming2
?lcdTiming3		:= 000Ch
?pLcdTiming3		:= pLcdRange + lcdTiming3
?mpLcdTiming3		:= mpLcdRange + lcdTiming3

?lcdBase			:= 0010h
?pLcdBase		:= pLcdRange + lcdBase
?mpLcdBase		:= mpLcdRange + lcdBase
?lcdUpbase		:= 0010h
?pLcdUpbase		:= pLcdRange + lcdUpbase
?mpLcdUpbase		:= mpLcdRange + lcdUpbase
?lcdLpbase		:= 0014h
?pLcdLpbase		:= pLcdRange + lcdLpbase
?mpLcdLpbase		:= mpLcdRange + lcdLpbase

?lcdCtrl			:= 0018h
?pLcdCtrl		:= pLcdRange + lcdCtrl
?mpLcdCtrl		:= mpLcdRange + lcdCtrl
?lcdEn			:= 01h
?lcdTft			:= 20h
?lcdBpp1			:= 0000b or lcdTft or lcdEn
?lcdBpp2			:= 0010b or lcdTft or lcdEn
?lcdBpp4			:= 0100b or lcdTft or lcdEn
?lcdBpp8			:= 0110b or lcdTft or lcdEn
?lcdBpp16Alt		:= 1000b or lcdTft or lcdEn
?lcdBpp24		:= 1010b or lcdTft or lcdEn
?lcdBpp16		:= 1100b or lcdTft or lcdEn ; Default LCD mode
?lcdBpp12		:= 1110b or lcdTft or lcdEn
?lcdBgr			:= 100h
?lcdBigEndian		:= 200h
?lcdBigEndianPixels	:= 400h
?lcdPwr			:= 800h
?lcdIntVSync		:= 0000h
?lcdIntBack		:= 1000h
?lcdIntActiveVideo	:= 2000h
?lcdIntFront		:= 3000h
?lcdWatermark		:= 10000h
?lcdNormalMode		:= lcdPwr or lcdBgr or lcdBpp16

?lcdImsc			:= 001Ch
?pLcdImsc		:= pLcdRange + lcdImsc
?mpLcdImsc		:= mpLcdRange + lcdImsc
?lcdRis			:= 0020h
?pLcdRis			:= pLcdRange + lcdRis
?mpLcdRis		:= mpLcdRange + lcdRis
?lcdMis			:= 0024h
?pLcdMis			:= pLcdRange + lcdMis
?mpLcdMis		:= mpLcdRange + lcdMis
?lcdIcr			:= 0028h
?pLcdIcr			:= pLcdRange + lcdIcr
?mpLcdIcr		:= mpLcdRange + lcdIcr

?bLcdIntFuf		:= 1
?lcdIntFuf		:= 1 shl bLcdIntFuf
?bLcdIntLNBU		:= 2
?lcdIntLNBU		:= 1 shl bLcdIntLNBU
?bLcdIntVcomp		:= 3
?lcdIntVcomp		:= 1 shl bLcdIntVcomp
?bLcdIntMbErr		:= 4
?lcdIntMbErr		:= 1 shl bLcdIntMbErr

?lcdCurr			:= 002Ch
?pLcdCurr		:= pLcdRange + lcdCurr
?mpLcdCurr		:= mpLcdRange + lcdCurr
?lcdUpcurr		:= 002Ch
?pLcdUpcurr		:= pLcdRange + lcdUpcurr
?mpLcdUpcurr		:= mpLcdRange + lcdUpcurr
?lcdLpcurr		:= 0030h
?pLcdLpcurr		:= pLcdRange + lcdLpcurr
?mpLcdLpcurr		:= mpLcdRange + lcdLpcurr
?lcdPalette		:= 0200h
?pLcdPalette		:= pLcdRange + lcdPalette
?mpLcdPalette		:= mpLcdRange + lcdPalette

?lcdCrsrImage		:= 0800h
?pLcdCrsrImage		:= pLcdRange + lcdCrsrImage
?mpLcdCrsrImage		:= mpLcdRange + lcdCrsrImage
?lcdCrsrCtrl		:= 0C00h
?pLcdCrsrCtrl		:= pLcdRange + lcdCrsrCtrl
?mpLcdCrsrCtrl		:= mpLcdRange + lcdCrsrCtrl
?lcdCrsrConfig		:= 0C04h
?pLcdCrsrConfig		:= pLcdRange + lcdCrsrConfig
?mpLcdCrsrConfig		:= mpLcdRange + lcdCrsrConfig
?lcdCrsrPalette0		:= 0C08h
?pLcdCrsrPalette0	:= pLcdRange + lcdCrsrPalette0
?mpLcdCrsrPalette0	:= mpLcdRange + lcdCrsrPalette0
?lcdCrsrPalette1		:= 0C0Ch
?pLcdCrsrPalette1	:= pLcdRange + lcdCrsrPalette1
?mpLcdCrsrPalette1	:= mpLcdRange + lcdCrsrPalette1
?lcdCrsrXY		:= 0C10h
?pLcdCrsrXY		:= pLcdRange + lcdCrsrXY
?mpLcdCrsrXY		:= mpLcdRange + lcdCrsrXY
?lcdCrsrClip		:= 0C14h
?pLcdCrsrClip		:= pLcdRange + lcdCrsrClip
?mpLcdCrsrClip		:= mpLcdRange + lcdCrsrClip
?lcdCrsrImsc		:= 0C20h
?pLcdCrsrImsc		:= pLcdRange + lcdCrsrImsc
?mpLcdCrsrImsc		:= mpLcdRange + lcdCrsrImsc
?lcdCrsrIcr		:= 0C24h
?pLcdCrsrIcr		:= pLcdRange + lcdCrsrIcr
?mpLcdCrsrIcr		:= mpLcdRange + lcdCrsrIcr
?lcdCrsrRis		:= 0C28h
?pLcdCrsrRis		:= pLcdRange + lcdCrsrRis
?mpLcdCrsrRis		:= mpLcdRange + lcdCrsrRis
?lcdCrsrMis		:= 0C2Ch
?pLcdCrsrMis		:= pLcdRange + lcdCrsrMis
?mpLcdCrsrMis		:= mpLcdRange + lcdCrsrMis

;Interrupt Ports
;-----------------------------------
?pIntRange		:= 05000h
?mpIntRange		:= 0F00000h

?intStat			:= 0
?pIntStat		:= pIntRange + intStat
?mpIntStat		:= mpIntRange + intStat
?intMask			:= 4
?pIntMask		:= pIntRange + intMask
?mpIntMask		:= mpIntRange + intMask
?intAck			:= 8
?pIntAck			:= pIntRange + intAck
?mpIntAck		:= mpIntRange + intAck
?intLatch		:= 12
?pIntLatch		:= pIntRange + intLatch
?mpIntLatch		:= mpIntRange + intLatch
?intInvert		:= 16
?pIntInvert		:= pIntRange + intInvert
?mpIntInvert		:= mpIntRange + intInvert
?intMasked		:= 20
?pIntMasked		:= pIntRange + intMasked
?mpIntMasked		:= mpIntRange + intMasked

?bIntOn			:= 0
?intOn			:= 1 shl bIntOn
?bIntTmr1		:= 1
?intTmr1			:= 1 shl bIntTmr1
?bIntTmr2		:= 2
?intTmr2			:= 1 shl bIntTmr2
?bIntTmr3		:= 3
?intTmr3			:= 1 shl bIntTmr3
?bIntOSTmr		:= 4
?intOSTmr		:= 1 shl bIntOSTmr
?bIntKey			:= 10
?intKey			:= 1 shl bIntKey
?bIntLcd			:= 11
?intLcd			:= 1 shl bIntLcd
?bIntRtc			:= 12
?intRtc			:= 1 shl bIntRtc
?bIntUsb			:= 13
?intUsb			:= 1 shl bIntUsb
?intDefaultMask		:= intOn or intTmr3 or intOSTmr or intRtc or intUsb

;Timer Ports
;-----------------------------------
?tmrRange		:= 00h
?pTmrRange		:= 7000h
?mpTmrRange		:= 0F20000h

?tmr1Counter		:= 00h
?pTmr1Counter		:= 7000h
?mpTmr1Counter		:= 0F20000h
?tmr1Load		:= 04h
?pTmr1Load		:= 7004h
?mpTmr1Load		:= 0F20004h
?tmr1Match1		:= 08h
?pTmr1Match1		:= 7008h
?mpTmr1Match1		:= 0F20008h
?tmr1Match2		:= 0Ch
?pTmr1Match2		:= 700Ch
?mpTmr1Match2		:= 0F2000Ch

?tmr2Counter		:= 10h
?pTmr2Counter		:= 7010h
?mpTmr2Counter		:= 0F20010h
?tmr2Load		:= 14h
?pTmr2Load		:= 7014h
?mpTmr2Load		:= 0F20014h
?tmr2Match1		:= 18h
?pTmr2Match1		:= 7018h
?mpTmr2Match1		:= 0F20018h
?tmr2Match2		:= 1Ch
?pTmr2Match2		:= 701Ch
?mpTmr2Match2		:= 0F2001Ch

?tmr3Counter		:= 20h
?pTmr3Counter		:= 7020h
?mpTmr3Counter		:= 0F20020h
?tmr3Load		:= 24h
?pTmr3Load		:= 7024h
?mpTmr3Load		:= 0F20024h
?tmr3Match1		:= 28h
?pTmr3Match1		:= 7028h
?mpTmr3Match1		:= 0F20028h
?tmr3Match2		:= 2Ch
?pTmr3Match2		:= 702Ch
?mpTmr3Match2		:= 0F2002Ch

?tmrCtrl			:= 30h
?pTmrCtrl		:= 7030h
?mpTmrCtrl		:= 0F20030h

?bTmr1Enable		:= 0
?tmr1Enable		:= 1 shl bTmr1Enable
?bTmr1Crystal		:= 1
?tmr1Crystal		:= 1 shl bTmr1Crystal
?bTmr1Overflow		:= 2
?tmr1Overflow		:= 1 shl bTmr1Overflow
?bTmr2Enable		:= 3
?tmr2Enable		:= 1 shl bTmr2Enable
?bTmr2Crystal		:= 4
?tmr2Crystal		:= 1 shl bTmr2Crystal
?bTmr2Overflow		:= 5
?tmr2Overflow		:= 1 shl bTmr2Overflow
?bTmr3Enable		:= 6
?tmr3Enable		:= 1 shl bTmr3Enable
?bTmr3Crystal		:= 7
?tmr3Crystal		:= 1 shl bTmr3Crystal
?bTmr3Overflow		:= 8
?tmr3Overflow		:= 1 shl bTmr3Overflow
?bTmr1CountUp		:= 9
?tmr1CountUp		:= 1 shl bTmr1CountUp
?bTmr2CountUp		:= 10
?tmr2CountUp		:= 1 shl bTmr2CountUp
?bTmr3CountUp		:= 11
?tmr3CountUp		:= 1 shl bTmr3CountUp

?tmrIntStatus		:= 34h
?pTmrIntStatus		:= 7034h
?mpTmrIntStatus		:= 0F20034h

?bTmr1IntMatch1		:= 0
?tmr1IntMatch1		:= 1 shl bTmr1IntMatch1
?bTmr1IntMatch2		:= 1
?tmr1IntMatch2		:= 1 shl bTmr1IntMatch2
?bTmr1IntOverflow	:= 2
?tmr1IntOverflow		:= 1 shl bTmr1IntOverflow
?bTmr2IntMatch1		:= 3
?tmr2IntMatch1		:= 1 shl bTmr2IntMatch1
?bTmr2IntMatch2		:= 4
?tmr2IntMatch2		:= 1 shl bTmr2IntMatch2
?bTmr2IntOverflow	:= 5
?tmr2IntOverflow		:= 1 shl bTmr2IntOverflow
?bTmr3IntMatch1		:= 6
?tmr3IntMatch1		:= 1 shl bTmr3IntMatch1
?bTmr3IntMatch2		:= 7
?tmr3IntMatch2		:= 1 shl bTmr3IntMatch2
?bTmr3IntOverflow	:= 8
?tmr3IntOverflow		:= 1 shl bTmr3IntOverflow

?tmrIntMask		:= 38h
?pTmrIntMask		:= 7038h
?mpTmrIntMask		:= 0F20038h

?tmrRevision		:= 3Ch
?pTmrRevision		:= 703Ch
?mpTmrRevision		:= 0F2003Ch

;RTC Ports
;-----------------------------------
?pRtcRange		:= 8000h
?mpRtcRange		:= 0F30000h

;Keypad Ports
;-----------------------------------
?pKeyRange		:= 0A000h
?mpKeyRange		:= 0F50000h

?keyMode			:= 0
?pKeyMode		:= pKeyRange + keyMode
?mpKeyMode		:= mpKeyRange + keyMode
?keyRows			:= 4
?pKeyRows		:= pKeyRange + keyRows
?mpKeyRows		:= mpKeyRange + keyRows
?keyCols			:= 5
?pKeyCols		:= pKeyRange + keyCols
?mpKeyCols		:= mpKeyRange + keyCols
?keyIntStat		:= 8
?pKeyIntStat		:= pKeyRange + keyIntStat
?mpKeyIntStat		:= mpKeyRange + keyIntStat
?keyIntAck		:= 8
?pKeyIntAck		:= pKeyRange + keyIntAck
?mpKeyIntAck		:= mpKeyRange + keyIntAck
?keyIntMask		:= 12
?pKeyIntMask		:= pKeyRange + keyIntMask
?mpKeyIntMask		:= mpKeyRange + keyIntMask
?keyData			:= 16
?pKeyData		:= pKeyRange + keyData
?mpKeyData		:= mpKeyRange + keyData
?keyGpio			:= 48
?pKeyGpio		:= pKeyRange + keyGpio
?mpKeyGpio		:= mpKeyRange + keyGpio

?bKeyIntScanDone		:= 0
?keyIntScanDone		:= 1 shl bKeyIntScanDone
?bKeyIntKeyChange	:= 1
?keyIntKeyChange		:= 1 shl bKeyIntKeyChange
?bKeyIntKeyPress		:= 2
?keyIntKeyPress		:= 1 shl bKeyIntKeyPress

?keyModeIdle		:= 0
?keyModeAny		:= 1
?keyModeScanOnce		:= 2
?keyModeScan		:= 3

;Backlight Ports
;-----------------------------------
?pBlLevel		:= 0B024h
?mpBlLevel		:= 0F60024h

;Character Font Equates
;-------------------------------------
?LrecurN			:= 001h
?LrecurU			:= 002h
?LrecurV			:= 003h
?LrecurW			:= 004h
?Lconvert		:= 005h
?LsqUp			:= 006h
?LsqDown			:= 007h
?Lintegral		:= 008h
?Lcross			:= 009h
?LboxIcon 		:= 00Ah
?LcrossIcon 		:= 00Bh
?LdotIcon 		:= 00Ch
?LsubT   		:= 00Dh ;small capital T for parametric mode.
?LcubeR  		:= 00Eh ;slightly different 3 for cubed root.
?LhexF			:= 00Fh
?Lroot			:= 010h
?Linverse		:= 011h
?Lsquare			:= 012h
?Langle			:= 013h
?Ldegree			:= 014h
?Lradian			:= 015h
?Ltranspose		:= 016h
?LLE			:= 017h
?LNE			:= 018h
?LGE			:= 019h
?Lneg			:= 01Ah
?Lexponent		:= 01Bh
?Lstore			:= 01Ch
?Lten			:= 01Dh
?LupArrow		:= 01Eh
?LdownArrow		:= 01Fh
?Lspace			:= 020h
?Lexclam			:= 021h
?Lquote			:= 022h
?Lpound			:= 023h
?Lfourth			:= 024h
?Lpercent		:= 025h
?Lampersand		:= 026h
?Lapostrophe		:= 027h
?LlParen			:= 028h
?LrParen			:= 029h
?Lasterisk		:= 02Ah
?LplusSign		:= 02Bh
?Lcomma			:= 02Ch
?Ldash			:= 02Dh
?Lperiod			:= 02Eh
?Lslash			:= 02Fh
?L0			:= 030h
?L1			:= 031h
?L2			:= 032h
?L3			:= 033h
?L4			:= 034h
?L5			:= 035h
?L6			:= 036h
?L7			:= 037h
?L8			:= 038h
?L9			:= 039h
?Lcolon			:= 03Ah
?Lsemicolon		:= 03Bh
?LLT			:= 03Ch
?LEQ			:= 03Dh
?LGT			:= 03Eh
?Lquestion		:= 03Fh
?LatSign			:= 040h
?LcapA			:= 041h
?LcapB			:= 042h
?LcapC			:= 043h
?LcapD			:= 044h
?LcapE			:= 045h
?LcapF			:= 046h
?LcapG			:= 047h
?LcapH			:= 048h
?LcapI			:= 049h
?LcapJ			:= 04Ah
?LcapK			:= 04Bh
?LcapL			:= 04Ch
?LcapM			:= 04Dh
?LcapN			:= 04Eh
?LcapO			:= 04Fh
?LcapP			:= 050h
?LcapQ			:= 051h
?LcapR			:= 052h
?LcapS			:= 053h
?LcapT			:= 054h
?LcapU			:= 055h
?LcapV			:= 056h
?LcapW			:= 057h
?LcapX			:= 058h
?LcapY			:= 059h
?LcapZ			:= 05Ah
?Ltheta			:= 05Bh
?Lbackslash		:= 05Ch
?LrBrack			:= 05Dh
?Lcaret			:= 05Eh
?Lunderscore		:= 05Fh
?Lbackquote		:= 060h
?La			:= 061h
?Lb			:= 062h
?Lc			:= 063h
?Ld			:= 064h
?Le			:= 065h
?Lf			:= 066h
?Lg			:= 067h
?Lh			:= 068h
?Li			:= 069h
?Lj			:= 06Ah
?Lk			:= 06Bh
?Ll			:= 06Ch
?Lm			:= 06Dh
?Ln			:= 06Eh
?Lo			:= 06Fh
?Lp			:= 070h
?Lq			:= 071h
?Lr			:= 072h
?Ls			:= 073h
?Lt			:= 074h
?Lu			:= 075h
?Lv			:= 076h
?Lw			:= 077h
?Lx			:= 078h
?Ly			:= 079h
?Lz			:= 07Ah
?LlBrace			:= 07Bh
?Lbar			:= 07Ch
?LrBrace			:= 07Dh
?Ltilde			:= 07Eh
?LinvEQ			:= 07Fh
?Lsub0			:= 080h
?Lsub1			:= 081h
?Lsub2			:= 082h
?Lsub3			:= 083h
?Lsub4			:= 084h
?Lsub5			:= 085h
?Lsub6			:= 086h
?Lsub7			:= 087h
?Lsub8			:= 088h
?Lsub9			:= 089h
?LcapAAcute		:= 08Ah
?LcapAGrave		:= 08Bh
?LcapACaret		:= 08Ch
?LcapADier		:= 08Dh
?LaAcute			:= 08Eh
?LaGrave			:= 08Fh
?LaCaret			:= 090h
?LaDier			:= 091h
?LcapEAcute		:= 092h
?LcapEGrave		:= 093h
?LcapECaret		:= 094h
?LcapEDier		:= 095h
?LeAcute			:= 096h
?LeGrave			:= 097h
?LeCaret			:= 098h
?LeDier			:= 099h
?LcapIAcute		:= 09Ah
?LcapIGrave		:= 09Bh
?LcapICaret		:= 09Ch
?LcapIDier		:= 09Dh
?LiAcute			:= 09Eh
?LiGrave			:= 09Fh
?LiCaret			:= 0A0h
?LiDier			:= 0A1h
?LcapOAcute		:= 0A2h
?LcapOGrave		:= 0A3h
?LcapOCaret		:= 0A4h
?LcapODier		:= 0A5h
?LoAcute			:= 0A6h
?LoGrave			:= 0A7h
?LoCaret			:= 0A8h
?LoDier			:= 0A9h
?LcapUAcute		:= 0AAh
?LcapUGrave		:= 0ABh
?LcapUCaret		:= 0ACh
?LcapUDier		:= 0ADh
?LuAcute			:= 0AEh
?LuGrave			:= 0AFh
?LuCaret			:= 0B0h
?LuDier			:= 0B1h
?LcapCCed		:= 0B2h
?LcCed			:= 0B3h
?LcapNTilde		:= 0B4h
?LnTilde			:= 0B5h
?Laccent			:= 0B6h
?Lgrave			:= 0B7h
?Ldieresis		:= 0B8h
?LquesDown		:= 0B9h
?LexclamDown		:= 0BAh
?Lalpha			:= 0BBh
?Lbeta			:= 0BCh
?Lgamma			:= 0BDh
?LcapDelta		:= 0BEh
?Ldelta			:= 0BFh
?Lepsilon		:= 0C0h
?LlBrack 		:= 0C1h
?Llambda			:= 0C2h
?Lmu			:= 0C3h
?Lpi			:= 0C4h
?Lrho			:= 0C5h
?LcapSigma		:= 0C6h
?Lsigma			:= 0C7h
?Ltau			:= 0C8h
?Lphi			:= 0C9h
?LcapOmega		:= 0CAh
?LxMean			:= 0CBh
?LyMean			:= 0CCh
?LsupX			:= 0CDh
?Lellipsis		:= 0CEh
?Lleft			:= 0CFh
?Lblock			:= 0D0h
?Lper			:= 0D1h
?Lhyphen			:= 0D2h
?Larea			:= 0D3h
?Ltemp			:= 0D4h
?Lcube			:= 0D5h
?Lenter			:= 0D6h
?LimagI			:= 0D7h
?Lphat			:= 0D8h
?Lchi			:= 0D9h
?LstatF			:= 0DAh
?Llne			:= 0DBh
?LlistL			:= 0DCh
?LfinanN 		:= 0DDh
?L2_r_paren 		:= 0DEh
?LblockArrow		:= 0DFh
?LcurO   		:= 0E0h
?LcurO2  		:= 0E1h
?LcurOcapA		:= 0E2h
?LcurOa  		:= 0E3h
?LcurI   		:= 0E4h
?LcurI2  		:= 0E5h
?LcurIcapA		:= 0E6h
?LcurIa  		:= 0E7h
?LGline			:= 0E8h ; = 0
?LGthick			:= 0E9h ; = 1
?LGabove			:= 0EAh ; = 2
?LGbelow			:= 0EBh ; = 3
?LGpath			:= 0ECh ; = 4
?LGanimate		:= 0EDh ; = 5
?LGdot			:= 0EEh ; = 6
?LUpBlk			:= 0EFh ;Up arrow and Block in solver
?LDnBlk			:= 0F0h ;Down arrow and Block in solver
?LcurFull		:= 0F1h ;note: must be last char (PutMap checks)

;(MenuCurrent) Values
;-----------------------------------
?mConfirmation		:= 01h
?mApps			:= 02h
?mProgramHome		:= 03h
?mPrgm_Run		 := 00h
?mPrgm_Edit		 := 01h
?mPrgm_New		 := 02h
?mZoom			:= 04h
?mZoom_Zoom		 := 00h
?mZoom_Memory		 := 01h
?mDraw			:= 05h
?mDraw_Draw		 := 00h
?mDraw_Points		 := 01h
?mDraw_Store		 := 02h
?mDraw_Background	:= 03h
?mStatPlots		:= 06h
?mStat			:= 07h
?mStat_Edit		 := 00h
?mStat_Calc		 := 01h
?mStat_Tests		 := 02h
?mMath			:= 08h
?mMath_Math		 := 00h
?mMath_Number		 := 01h
?mMath_Complex		 := 02h
?mMath_Prob		 := 03h
?mMath_Frac		 := 04h
?mTest			:= 09h
?mTest_Test		 := 00h
?mTest_Logic		 := 01h

?mVars			:= 0Bh
?mVars_Vars		 := 00h
?mVars_YVars		 := 01h
?mVars_Colors	 := 02h
?mMemory			:= 0Ch
?mMatrix			:= 0Dh
?mMatrix_Name		 := 00h
?mMatrix_Math		 := 01h
?mMatrix_Edit		 := 02h
?mDistr			:= 0Eh
?mDistr_Distr		 := 00h
?mDistr_Draw		 := 01h
?mAngle			:= 0Fh
?mList			:= 10h
?mList_Names		 := 00h
?mList_Ops		 := 01h
?mList_Math		 := 02h
?mCalculate		:= 11h
?mVarsWin		:= 15h
?mVarsWin_XY		 := 00h
?mVarsWin_TTh		 := 01h
?mVarsWin_UVW		 := 02h
?mVarsZoom		:= 16h
?mVarsZoom_ZXY		 := 00h
?mVarsZoom_ZT		 := 01h
?mVarsZoom_UVW		 := 02h
?mVarsGDB		:= 17h
?mVarsPics		:= 18h
?mVarsPics_Pics		 := 01h
?mVarsPics_Bckgrnds		 := 01h
?mVarsStrings		:= 19h
?mVarsStat		:= 1Ah
?mVarsStat_XY		 := 00h
?mVarsStat_Sigma		 := 01h
?mVarsStat_EQ		 := 02h
?mVarsStat_Test		 := 03h
?mVarsStat_Pts		 := 04h
?mVarsTable		:= 1Bh
?mVarsYequ 		:= 1Ch
?mVarsParametric		:= 1Dh
?mVarsPolar		:= 1Eh
?mVarsFnOnOff		:= 1Fh
?mMemReset		:= 20h
?mMemReset_RAM		 := 00h
?mMemReset_ROM		 := 01h
?mMemReset_All		 := 02h
?mMemMgmtDel		:= 21h
?mMemResetDefaults	:= 22h
?mMemResetRAMAll		:= 24h
?mMemResetROMVars	:= 25h
?mMemResetROMApps	:= 26h
?mMemResetROMAll		:= 27h
?mMemResetAll		:= 28h
?mGroup			:= 29h
?mGroup_New		 := 00h
?mGroup_Ungroup		 := 01h
?mGroupVars		:= 2Ah
?mProgramEdit		:= 2Bh
?mPrgmEd_Ctrl		 := 00h
?mPrgmEd_IO		 := 01h
?mPrgmEd_Color		 := 02h
?mPrgmEd_Exec		 := 03h
?mPrgmZoom		:= 2Ch
?mPrgmZoom_Zoom		 := 00h
?mPrgmZoom_Mem		 := 01h
?mPrgmDraw		:= 2Dh
?mPrgmDraw_Draw		 := 00h
?mPrgmDraw_Pt		 := 01h
?mPrgmDraw_Store		 := 02h
?mPrgmDraw_Bckgrnd	 := 03h
?mPrgmStatPlot		:= 2Eh
?mPrgmSP_Plots		 := 00h
?mPrgmSP_Type		 := 01h
?mPrgmSP_Mark		 := 02h
?mPrgmStat		:= 2Fh
?mPrgmStat_Edit		 := 00h
?mPrgmStat_Calc		 := 01h
?mPrgmStat_Tests		 := 02h
?mPrgmMath		:= 30h
?mPrgmMath_Math		 := 00h
?mPrgmMath_Num		 := 01h
?mPrgmMath_Cplx		 := 02h
?mPrgmMath_Prob		 := 03h
?mPrgmMath_Frac		 := 04h
?mLink			:= 31h
?mLink_Send		 := 00h
?mLink_Recieve		 := 01h
?mLinkTrasmit		:= 32h
?mLinkXmit_Xmit		 := 01h
?mGarbageCollect		:= 40h
?mSelectGroupVars	:= 41h
?mSelGrpVars_Sel		 := 00h
?mSelGrpVars_Grp		 := 01h
?mDuplicateName		:= 43h
?mCatalog		:= 46h
?mFinance		:= 22h
?mFinance_Calc		 := 00h
?mFinance_Vars		 := 01h

;Keypress Equates
;-----------------------------------
?kRight			:= 001h
?kLeft			:= 002h
?kUp			:= 003h
?kDown			:= 004h
?kEnter			:= 005h
?kAlphaEnter		:= 006h
?kAlphaUp		:= 007h
?kAlphaDown		:= 008h
?kClear			:= 009h
?kDel			:= 00Ah
?kIns			:= 00Bh
?kRecall			:= 00Ch
?kLastEnt		:= 00Dh
?kBOL			:= 00Eh
?kEOL			:= 00Fh

?kSelAll			:= 010h
?kUnselAll		:= 011h
?kLtoTI82		:= 012h
?kBackup			:= 013h
?kRecieve		:= 014h
?kLnkQuit		:= 015h
?kTrans			:= 016h
?kRename			:= 017h
?kOverw			:= 018h
?kOmit			:= 019h
?kCont			:= 01Ah
?kSendID			:= 01Bh
?kSendSW			:= 01Ch
?kYes			:= 01Dh
?kNoWay			:= 01Eh
?kvSendType		:= 01Fh
?kOverWAll		:= 020h
?kNo			:= 025h
?kKReset			:= 026h
?kApp			:= 027h
?kDoug			:= 028h
?kListflag		:= 029h
?menuStart		:= 02Bh
?kAreYouSure		:= 02Bh
?kAppsMenu		:= 02Ch
?kPrgm			:= 02Dh
?kZoom			:= 02Eh
?kDraw			:= 02Fh
?kSPlot			:= 030h
?kStat			:= 031h
?kMath			:= 032h
?kTest			:= 033h
?kChar			:= 034h
?kVars			:= 035h
?kMem			:= 036h
?kMatrix			:= 037h
?kDist			:= 038h
?kAngle			:= 039h
?kList			:= 03Ah
?kCalc			:= 03Bh
?kFin			:= 03Ch
?menuEnd			:= kFin
?kCatalog		:= 03Eh
?kInputDone		:= 03Fh
?kOff			:= kInputDone
?kQuit			:= 040h
?appStart		:= kQuit
?kLinkIO			:= 041h
?kMatrixEd		:= 042h
?kStatEd			:= 043h
?kGraph			:= 044h
?kMode			:= 045h
?kPrgmEd			:= 046h ;PROGRAM EDIT
?kPrgmCr			:= 047h ;PROGRAM CREATE
?kWindow			:= 048h ;RANGE EDITOR
?kYequ 			:= 049h ;EQUATION EDITOR
?kTable			:= 04Ah ;TABLE EDITOR
?kTblSet			:= 04Bh ;TABLE SET
?kChkRAM			:= 04Ch ;CHECK RAM (About screen)
?kDelMem			:= 04Dh ;DELETE MEM
?kResetMem		:= 04Eh ;RESET MEM
?kResetDef		:= 04Fh ;RESET DEFAULT
?kPrgmInput		:= 050h ;PROGRAM INPUT
?kZFactEd		:= 051h ;ZOOM FACTOR EDITOR
?kError			:= 052h ;ERROR
?kSolveTVM		:= 053h ;TVM SOLVER
?kSolveRoot		:= 054h ;SOLVE EDITOR
?kStatP			:= 055h ;stat plot
?kInfStat		:= 056h ;Inferential Statistic
?kFormat			:= 057h ;FORMAT
?kExtApps		:= 058h ;External Applications.		NEW
?kNewApps		:= 059h ;New Apps for Cerberus.
?append			:= kNewApps
?echoStart1		:= 05Ah
?kTrace			:= 05Ah
?kZFit			:= 05Bh
?kZIn			:= 05Ch
?kZOut			:= 05Dh
?kZPrev			:= 05Eh
?kBox			:= 05Fh
?kDecml			:= 060h
?kSetZm			:= 061h
?kSquar			:= 062h
?kStd			:= 063h
?kTrig			:= 064h
?kUsrZm			:= 065h
?kZSto			:= 066h
?kZInt			:= 067h
?kZStat			:= 068h
?echoStart2		:= 069h
?kSelect			:= 069h
?kCircl			:= 06Ah
?kClDrw			:= 06Bh
?kLine			:= 06Ch
?kPen			:= 06Dh
?kPtChg			:= 06Eh
?kPtOff			:= 06Fh
?kPtOn			:= 070h
?kVert			:= 071h
?kHoriz			:= 072h
?kText			:= 073h
?kTanLn			:= 074h
?kEval			:= 075h
?kInters			:= 076h
?kDYDX			:= 077h
?kFnIntg			:= 078h
?kRootG			:= 079h
?kDYDT			:= 07Ah
?kDXDT			:= 07Bh
?kDRDo			:= 07Ch
?KGFMin			:= 07Dh
?KGFMax			:= 07Eh
?EchoStart		:= 07Fh
?kListName		:= 07Fh
?kAdd			:= 080h
?kSub			:= 081h
?kMul			:= 082h
?kDiv			:= 083h
?kExpon			:= 084h
?kLParen			:= 085h
?kRParen			:= 086h
?kLBrack			:= 087h
?kRBrack			:= 088h
?kShade			:= 089h
?kStore			:= 08Ah
?kComma			:= 08Bh
?kChs			:= 08Ch
?kDecPnt			:= 08Dh
?k0			:= 08Eh
?k1			:= 08Fh
?k2			:= 090h
?k3			:= 091h
?k4			:= 092h
?k5			:= 093h
?k6			:= 094h
?k7			:= 095h
?k8			:= 096h
?k9			:= 097h
?kEE			:= 098h
?kSpace			:= 099h
?kCapA			:= 09Ah
?kCapB			:= 09Bh
?kCapC			:= 09Ch
?kCapD			:= 09Dh
?kCapE			:= 09Eh
?kCapF			:= 09Fh
?kCapG			:= 0A0h
?kCapH			:= 0A1h
?kCapI			:= 0A2h
?kCapJ			:= 0A3h
?kCapK			:= 0A4h
?kCapL			:= 0A5h
?kCapM			:= 0A6h
?kCapN			:= 0A7h
?kCapO			:= 0A8h
?kCapP			:= 0A9h
?kCapQ			:= 0AAh
?kCapR			:= 0ABh
?kCapS			:= 0ACh
?kCapT			:= 0ADh
?kCapU			:= 0AEh
?kCapV			:= 0AFh
?kCapW			:= 0B0h
?kCapX			:= 0B1h
?kCapY			:= 0B2h
?kCapZ			:= 0B3h
?kVarx			:= 0B4h
?kPi			:= 0B5h
?kInv			:= 0B6h
?kSin			:= 0B7h
?kASin			:= 0B8h
?kCos			:= 0B9h
?kACos			:= 0BAh
?kTan			:= 0BBh
?kATan			:= 0BCh
?kSquare			:= 0BDh
?kSqrt			:= 0BEh
?kLn			:= 0BFh
?kExp			:= 0C0h
?kLog			:= 0C1h
?kALog			:= 0C2h
?kToABC			:= 0C3h
?kClrTbl			:= 0C4h
?kAns			:= 0C5h
?kColon			:= 0C6h
?kNDeriv			:= 0C7h
?kFnInt			:= 0C8h
?kRoot			:= 0C9h
?kQuest			:= 0CAh
?kQuote			:= 0CBh
?kTheta			:= 0CCh
?kIf			:= 0CDh
?kThen			:= 0CEh
?kElse			:= 0CFh
?kFor			:= 0D0h
?kWhile			:= 0D1h
?kRepeat			:= 0D2h
?kEnd			:= 0D3h
?kPause			:= 0D4h
?kLbl			:= 0D5h
?kGoto			:= 0D6h
?kISG			:= 0D7h
?kDSL			:= 0D8h
?kMenu			:= 0D9h
?kExec			:= 0DAh
?kReturn			:= 0DBh
?kStop			:= 0DCh
?kInput			:= 0DDh
?kPrompt			:= 0DEh
?kDisp			:= 0DFh
?kDispG			:= 0E0h
?kDispT			:= 0E1h
?kOutput			:= 0E2h
?kGetKey			:= 0E3h
?kClrHome		:= 0E4h
?kPrtScr			:= 0E5h
?kSinH			:= 0E6h
?kCosH			:= 0E7h
?kTanH			:= 0E8h
?kASinH			:= 0E9h
?kACosH			:= 0EAh
?kATanH			:= 0EBh
?kLBrace			:= 0ECh
?kRBrace			:= 0EDh
?kI			:= 0EEh
?kCONSTeA		:= 0EFh
?kPlot3			:= 0F0h
?kFMin			:= 0F1h
?kFMax			:= 0F2h
?kL1A			:= 0F3h
?kL2A			:= 0F4h
?kL3A			:= 0F5h
?kL4A			:= 0F6h
?kL5A			:= 0F7h
?kL6A			:= 0F8h
?kunA			:= 0F9h
?kvnA			:= 0FAh
?kwnA			:= 0FBh

; THIS KEY MEANS THAT IT IS A 2 BYTE KEYCODE
; THERE ARE 2 OF THESE KEYS; BE CAREFUL WITH USAGE
;--------------------------------------------------------
?kExtendEcho2		:= 0FCh

; THIS KEY MEANS THAT THE KEY PRESS IS ONE THAT ECHOS
; INTO A BUFFER, AND IT IS A 2 BYTE KEY CODE, GO LOOK AT
; (EXTECHO) FOR THE KEY VALUE
;--------------------------------------------------------
?kExtendEcho		:= 0FEh

?kE1BT			:= 0
?kDrawInv		:= kE1BT
?kDrawF			:= kE1BT+1
?kPixelOn		:= kE1BT+2
?kPixelOff		:= kE1BT+3
?kPxlTest		:= kE1BT+4
?kRCGDB			:= kE1BT+5
?kRCPic			:= kE1BT+6
?kSTGDB			:= kE1BT+7
?kSTPic			:= kE1BT+8
?kAbs			:= kE1BT+9
?kTequ 		:= kE1BT+10 ;==
?kTNoteQ			:= kE1BT+11 ;<>
?kTGT			:= kE1BT+12 ;>
?kTGTE			:= kE1BT+13 ;>=
?kTLT			:= kE1BT+14 ;<
?kTLTE			:= kE1BT+15 ;<=
?kAnd			:= kE1BT+16
?kOr			:= kE1BT+17
?kXor			:= kE1BT+18
?kNot			:= kE1BT+19
?kLR1			:= kE1BT+20
?kXRoot			:= kE1BT+21
?kCube			:= kE1BT+22
?kCbRt			:= kE1BT+23 ;Cube ROOT
?kToDec			:= kE1BT+24
?kCubicR			:= kE1BT+25
?kQuartR			:= kE1BT+26
?kPlot1			:= kE1BT+27
?kPlot2			:= kE1BT+28
?kRound			:= kE1BT+29
?kIPart			:= kE1BT+30
?kFPart			:= kE1BT+31
?kInt			:= kE1BT+32
?kRand			:= kE1BT+33
?kNPR			:= kE1BT+34
?kNCR			:= kE1BT+35
?kXFactorial		:= kE1BT+36
?kRad			:= kE1BT+37
?kDegr			:= kE1BT+38 ;DEGREES CONV
?kAPost			:= kE1BT+39
?kToDMS			:= kE1BT+40
?kRToPo			:= kE1BT+41 ;R
?kRToPr			:= kE1BT+42
?kPToRx			:= kE1BT+43
?kPToRy			:= kE1BT+44
?kRowSwap		:= kE1BT+45
?kRowPlus		:= kE1BT+46
?kTimRow			:= kE1BT+47
?kTRowP			:= kE1BT+48
?kSortA			:= kE1BT+49
?kSortD			:= kE1BT+50
?kSeq			:= kE1BT+51
?kMin			:= kE1BT+52
?kMax			:= kE1BT+53
?kMean			:= kE1BT+54
?kMedian			:= kE1BT+55
?kSum			:= kE1BT+56
?kProd			:= kE1BT+57
?kDet			:= kE1BT+58
?kTransp			:= kE1BT+59
?kDim			:= kE1BT+60
?kFill			:= kE1BT+61
?kIdent			:= kE1BT+62
?kRandm			:= kE1BT+63
?kAug			:= kE1BT+64
?kOneVar			:= kE1BT+65
?kTwoVar			:= kE1BT+66
?kLR			:= kE1BT+67
?kLRExp			:= kE1BT+68
?kLRLn			:= kE1BT+69
?kLRPwr			:= kE1BT+70
?kMedMed			:= kE1BT+71
?kQuad			:= kE1BT+72
?kClrLst			:= kE1BT+73
?kHist			:= kE1BT+74
?kxyLine			:= kE1BT+75
?kScatter		:= kE1BT+76
?kmRad			:= kE1BT+77
?kmDeg			:= kE1BT+78
?kmNormF			:= kE1BT+79
?kmSci			:= kE1BT+80
?kmEng			:= kE1BT+81
?kmFloat			:= kE1BT+82
?kFix			:= kE1BT+83
?kSplitOn		:= kE1BT+84
?kFullScreen		:= kE1BT+85
?kStndrd			:= kE1BT+86
?kParam			:= kE1BT+87
?kPolar			:= kE1BT+88
?kSeqG			:= kE1BT+89
?kAFillOn		:= kE1BT+90
?kAFillOff		:= kE1BT+91
?kACalcOn		:= kE1BT+92
?kACalcOff		:= kE1BT+93
?kFNOn			:= kE1BT+94
?kFNOff			:= kE1BT+95
?kPlotsOn		:= kE1BT+96
?kPlotsOff		:= kE1BT+97
?kPixelChg		:= kE1BT+98
?kSendMBL		:= kE1BT+99
?kRecvMBL		:= kE1BT+100
?kBoxPlot		:= kE1BT+101
?kBoxIcon		:= kE1BT+102
?kCrossIcon		:= kE1BT+103
?kDotIcon		:= kE1BT+104
?kE2BT			:= kE1BT+105
?kSeqential		:= kE2BT
?kSimulG			:= kE2BT+1
?kPolarG			:= kE2BT+2
?kRectG			:= kE2BT+3
?kCoordOn		:= kE2BT+4
?kCoordOff		:= kE2BT+5
?kDrawLine		:= kE2BT+6
?kDrawDot		:= kE2BT+7
?kAxisOn			:= kE2BT+8
?kAxisOff		:= kE2BT+9
?kGridOn			:= kE2BT+10
?kGridOff		:= kE2BT+11
?kLblOn			:= kE2BT+12
?kLblOff			:= kE2BT+13
?kL1			:= kE2BT+14
?kL2			:= kE2BT+15
?kL3			:= kE2BT+16
?kL4			:= kE2BT+17
?kL5			:= kE2BT+18
?kL6			:= kE2BT+19

;These keys are laid on top of existing keys to
;enable localization in the inferential stats editor.
;----------------------------------------------------
?kinfData		:= kL1
?kinfStats		:= kL1+1
?kinfYes			:= kL1+2
?kinfNo			:= kL1+3
?kinfCalc		:= kL1+4
?kinfDraw		:= kL1+5
?kinfAlt1ne		:= kL1+6
?kinfAlt1lt		:= kL1+7
?kinfAlt1gt		:= kL1+8
?kinfAlt2ne		:= kL1+9
?kinfAlt2lt		:= kL1+10
?kinfAlt2gt		:= kL1+11
?kinfAlt3ne		:= kL1+12
?kinfAlt3lt		:= kL1+13
?kinfAlt3gt		:= kL1+14
?kinfAlt4ne		:= kL1+15
?kinfAlt4lt		:= kL1+16
?kinfAlt4gt		:= kL1+17
?kinfAlt5ne		:= kL1+18
?kinfAlt5lt		:= kL1+19
?kinfAlt5gt		:= kL1+20
?kinfAlt6ne		:= kL1+21
?kinfAlt6lt		:= kL1+22
?kinfAlt6gt		:= kL1+23
?kMatA			:= kE2BT+20
?kMatB			:= kE2BT+21
?kMatC			:= kE2BT+22
?kMatD			:= kE2BT+23
?kMatE			:= kE2BT+24
?kXmin			:= kE2BT+25
?kXmax			:= kE2BT+26
?kXscl			:= kE2BT+27
?kYmin			:= kE2BT+28
?kYmax			:= kE2BT+29
?kYscl			:= kE2BT+30
?kTmin			:= kE2BT+31
?kTmax			:= kE2BT+32
?kTStep			:= kE2BT+33
?kOmin			:= kE2BT+34
?kOmax			:= kE2BT+35
?kOStep			:= kE2BT+36
?ku0			:= kE2BT+37
?kv0			:= kE2BT+38
?knMin			:= kE2BT+39
?knMax			:= kE2BT+40
?kDeltaY			:= kE2BT+41
?kDeltaX			:= kE2BT+42
?kZXmin			:= kE2BT+43
?kZXmax			:= kE2BT+44
?kZXscl			:= kE2BT+45
?kZYmin			:= kE2BT+46
?kZYmax			:= kE2BT+47
?kZYscl			:= kE2BT+48
?kZTmin			:= kE2BT+49
?kZTmax			:= kE2BT+50
?kZTStep			:= kE2BT+51
?kZOmin			:= kE2BT+52
?kZOmax			:= kE2BT+53
?kZOStep			:= kE2BT+54
?kZu0			:= kE2BT+55
?kZv0			:= kE2BT+56
?kZnMin			:= kE2BT+57
?kZnMax			:= kE2BT+58
?kDelLast		:= kE2BT+59
?kSinReg			:= kE2BT+60
?kConstE			:= kE2BT+61
?kPic1			:= kE2BT+62
?kPic2			:= kE2BT+63
?kPic3			:= kE2BT+64
?kDelVar			:= kE2BT+65
?kGetCalc		:= kE2BT+66
?kRealM			:= kE2BT+67
?kPolarM			:= kE2BT+68
?kRectM			:= kE2BT+69
?kuv			:= kE2BT+70 ;U vs V
?kvw			:= kE2BT+71 ;V vs W
?kuw			:= kE2BT+72 ;U vs W
?kFinPMTend		:= kE2BT+73
?kFinPMTbeg		:= kE2BT+74
?kGraphStyle		:= kE2BT+75
?kExprOn			:= kE2BT+76
?kExprOff		:= kE2BT+77
?kStatA			:= kE2BT+78
?kStatB			:= kE2BT+79
?kStatC			:= kE2BT+80
?kCorr			:= kE2BT+81
?kStatD			:= kE2BT+82
?kStatE			:= kE2BT+83
?kRegEq			:= kE2BT+84
?kMinX			:= kE2BT+85
?kQ1			:= kE2BT+86
?kMD			:= kE2BT+87
?kQ3			:= kE2BT+88
?kMaxX			:= kE2BT+89
?kStatX1			:= kE2BT+90
?kStatY1			:= kE2BT+91
?kStatX2			:= kE2BT+92
?kStatY2			:= kE2BT+93
?kStatX3			:= kE2BT+94
?kStatY3			:= kE2BT+95
?kTblMin			:= kE2BT+96
?kTblStep		:= kE2BT+97
?kSetupLst		:= kE2BT+98
?kClrAllLst		:= kE2BT+99
?kLogistic		:= kE2BT+100
?kZTest			:= kE2BT+101
?kTTest			:= kE2BT+102
?k2SampZTest		:= kE2BT+103
?k2SampTTest		:= kE2BT+104
?k1PropZTest		:= kE2BT+105
?k2PropZTest		:= kE2BT+106
?kChiTest		:= kE2BT+107
?k2SampFTest		:= kE2BT+108
?kZIntVal		:= kE2BT+109
?kTIntVal		:= kE2BT+110
?k2SampTInt		:= kE2BT+111
?k2SampZInt		:= kE2BT+112
?k1PropZInt		:= kE2BT+113
?k2PropZInt		:= kE2BT+114
?kDNormal		:= kE2BT+115
?kInvNorm		:= kE2BT+116
?kDT			:= kE2BT+117
?kChi			:= kE2BT+118
?kDF			:= kE2BT+119
?kBinPDF			:= kE2BT+120
?kBinCDF			:= kE2BT+121
?kPoiPDF			:= kE2BT+122
?kPoiCDF			:= kE2BT+123
?kun			:= kE2BT+124
?kvn			:= kE2BT+125
?kwn			:= kE2BT+126
?kRecn			:= kE2BT+127
?kPlotStart		:= kE2BT+128
?kZPlotStart		:= kE2BT+129 ;recursion n
?kXFact			:= kE2BT+130 ;PlotStart
?kYFact			:= kE2BT+131 ;ZPlotStart
?kANOVA			:= kE2BT+132 ;XFact
?kMaxY			:= kE2BT+133 ;YFact
?kWebOn			:= kE2BT+134 ;MinY
?kWebOff			:= kE2BT+135 ;MaxY
?kTblInput		:= kE2BT+136 ;WEB ON
?kGeoPDF			:= kE2BT+137 ;WEB OFF
?kGeoCDF			:= kE2BT+138 ;WEB OFF
?kShadeNorm		:= kE2BT+139
?kShadeT			:= kE2BT+140
?kShadeChi		:= kE2BT+141
?kShadeF			:= kE2BT+142
?kPlotStep		:= kE2BT+143
?kZPlotStep		:= kE2BT+144
?kLinRegtTest		:= kE2BT+145
?KMGT			:= kE2BT+146 ;VERT SPLIT
?kSelectA		:= kE2BT+147
?kZFitA			:= kE2BT+148
?kE2BT_End		:= kZFitA

;More 2 Byte Keys
;-------------------------------------
?kE2BT2			:= 00h
?kGDB1			:= kE2BT2
?kGDB2			:= kE2BT2+1
?kGDB3			:= kE2BT2+2
?kY1			:= kE2BT2+3
?kY2			:= kE2BT2+4
?kY3			:= kE2BT2+5
?kY4			:= kE2BT2+6
?kY5			:= kE2BT2+7
?kY6			:= kE2BT2+8
?kY7			:= kE2BT2+9
?kY8			:= kE2BT2+10
?kY9			:= kE2BT2+11
?kY0			:= kE2BT2+12
?kX1T			:= kE2BT2+13
?kY1T			:= kE2BT2+14
?kX2T			:= kE2BT2+15
?kY2T			:= kE2BT2+16
?kX3T			:= kE2BT2+17
?kY3T			:= kE2BT2+18
?kX4T			:= kE2BT2+19
?kY4T			:= kE2BT2+20
?kX5T			:= kE2BT2+21
?kY5T			:= kE2BT2+22
?kX6T			:= kE2BT2+23
?kY6T			:= kE2BT2+24
?kR1			:= kE2BT2+25
?kR2			:= kE2BT2+26
?kR3			:= kE2BT2+27
?kR4			:= kE2BT2+28
?kR5			:= kE2BT2+29
?kR6			:= kE2BT2+30
?kGDB4			:= kE2BT2+31
?kGDB5			:= kE2BT2+32
?kGDB6			:= kE2BT2+33
?kPic4			:= kE2BT2+34
?kPic5			:= kE2BT2+35
?kPic6			:= kE2BT2+36
?kGDB7			:= kE2BT2+37
?kGDB8			:= kE2BT2+38
?kGDB9			:= kE2BT2+39
?kGDB0			:= kE2BT2+40
?kPic7			:= kE2BT2+41
?kPic8			:= kE2BT2+42
?kPic9			:= kE2BT2+43
?kPic0			:= kE2BT2+44
?kStatN			:= kE2BT2+45
?kXMean			:= kE2BT2+46
?kConj			:= kE2BT2+47
?kReal			:= kE2BT2+48
?kFAngle			:= kE2BT2+49
?kLCM			:= kE2BT2+50
?kGCD			:= kE2BT2+51
?kRandInt		:= kE2BT2+52
?kRandNorm		:= kE2BT2+53
?kToPolar		:= kE2BT2+54
?kToRect			:= kE2BT2+55
?kYMean			:= kE2BT2+56
?kStdX			:= kE2BT2+57
?kStdX1			:= kE2BT2+58
?kw0			:= kE2BT2+59
?kMatF			:= kE2BT2+60
?kMatG			:= kE2BT2+61
?kMatRH			:= kE2BT2+62
?kMatI			:= kE2BT2+63
?kMatJ			:= kE2BT2+64
?kYMean1			:= kE2BT2+65
?kStdY			:= kE2BT2+66
?kStdY1			:= kE2BT2+67
?kMatToLst		:= kE2BT2+68
?kLstToMat		:= kE2BT2+69
?kCumSum			:= kE2BT2+70
?kDeltaLst		:= kE2BT2+71
?kStdDev			:= kE2BT2+72
?kVariance		:= kE2BT2+73
?kLength			:= kE2BT2+74
?kEquToStrng		:= kE2BT2+75
?kStrngToequ 		:= kE2BT2+76
?kExpr			:= kE2BT2+77
?kSubStrng		:= kE2BT2+78
?kInStrng		:= kE2BT2+79
?kStr1			:= kE2BT2+80
?kStr2			:= kE2BT2+81
?kStr3			:= kE2BT2+82
?kStr4		 	:= kE2BT2+83
?kStr5		 	:= kE2BT2+84
?kStr6		 	:= kE2BT2+85
?kStr7		 	:= kE2BT2+86
?kStr8		 	:= kE2BT2+87
?kStr9		 	:= kE2BT2+88
?kStr0		 	:= kE2BT2+89
?kFinN		 	:= kE2BT2+90
?kFinI		 	:= kE2BT2+91
?kFinPV			:= kE2BT2+92
?kFinPMT			:= kE2BT2+93
?kFinFV			:= kE2BT2+94
?kFinPY			:= kE2BT2+95
?kFinCY			:= kE2BT2+96
?kFinFPMT		:= kE2BT2+97
?kFinFI			:= kE2BT2+98
?kFinFPV			:= kE2BT2+99
?kFinFN			:= kE2BT2+100
?kFinFFV			:= kE2BT2+101
?kFinNPV			:= kE2BT2+102
?kFinIRR			:= kE2BT2+103
?kFinBAL			:= kE2BT2+104
?kFinPRN			:= kE2BT2+105
?kFinINT			:= kE2BT2+106
?kSumX		 	:= kE2BT2+107
?kSumX2			:= kE2BT2+108
?kFinToNom		:= kE2BT2+109
?kFinToEff		:= kE2BT2+110
?kFinDBD			:= kE2BT2+111
?kStatVP			:= kE2BT2+112
?kStatZ			:= kE2BT2+113
?kStatT			:= kE2BT2+114
?kStatChi		:= kE2BT2+115
?kStatF			:= kE2BT2+116
?kStatDF			:= kE2BT2+117
?kStatPhat		:= kE2BT2+118
?kStatPhat1		:= kE2BT2+119
?kStatPhat2		:= kE2BT2+120
?kStatMeanX1		:= kE2BT2+121
?kStatMeanX2		:= kE2BT2+122
?kStatStdX1		:= kE2BT2+123
?kStatStdX2		:= kE2BT2+124
?kStatStdXP		:= kE2BT2+125
?kStatN1			:= kE2BT2+126
?kStatN2			:= kE2BT2+127
?kStatLower		:= kE2BT2+128
?kStatUpper		:= kE2BT2+129
?kuw0			:= kE2BT2+130
?kImag			:= kE2BT2+131
?kSumY			:= kE2BT2+132
?kXres			:= kE2BT2+133
?kStat_s			:= kE2BT2+134
?kSumY2			:= kE2BT2+135
?kSumXY			:= kE2BT2+136
?kuXres			:= kE2BT2+137
?kModBox			:= kE2BT2+138
?kNormProb		:= kE2BT2+139
?kNormalPDF		:= kE2BT2+140
?kTPDF			:= kE2BT2+141
?kChiPDF			:= kE2BT2+142
?kFPDF			:= kE2BT2+143
?kMinY			:= kE2BT2+144 ;MinY
?kRandBin		:= kE2BT2+145
?kRef			:= kE2BT2+146
?kRRef			:= kE2BT2+147
?kLRSqr			:= kE2BT2+148
?kBRSqr			:= kE2BT2+149
?kDiagOn			:= kE2BT2+150
?kDiagOff		:= kE2BT2+151
?kun1			:= kE2BT2+152 ;FOR RCL USE WHEN GOTTEN FROM 82
?kvn1			:= kE2BT2+153 ;FOR RCL USE WHEN GOTTEN FROM 82
?k83_00End		:= kvn1 ;end of original keys...
?kArchive		:= k83_00End + 1
?kUnarchive		:= k83_00End + 2
?kAsm			:= k83_00End + 3 ;Asm(
?kAsmPrgm		:= k83_00End + 4 ;AsmPrgm
?kAsmComp		:= k83_00End + 5 ;AsmComp(
?kcapAAcute		:= k83_00End + 6
?kcapAGrave		:= k83_00End + 7
?kcapACaret		:= k83_00End + 8
?kcapADier		:= k83_00End + 9
?kaAcute			:= k83_00End + 10
?kaGrave			:= k83_00End + 11
?kaCaret			:= k83_00End + 12
?kaDier			:= k83_00End + 13
?kcapEAcute		:= k83_00End + 14
?kcapEGrave		:= k83_00End + 15
?kcapECaret		:= k83_00End + 16
?kcapEDier		:= k83_00End + 17
?keAcute			:= k83_00End + 18
?keGrave			:= k83_00End + 19
?keCaret			:= k83_00End + 20
?keDier			:= k83_00End + 21
?kcapIAcute		:= k83_00End + 22
?kcapIGrave		:= k83_00End + 23
?kcapICaret		:= k83_00End + 24
?kcapIDier		:= k83_00End + 25
?kiAcute			:= k83_00End + 26
?kiGrave			:= k83_00End + 27
?kiCaret			:= k83_00End + 28
?kiDier			:= k83_00End + 29
?kcapOAcute		:= k83_00End + 30
?kcapOGrave		:= k83_00End + 31
?kcapOCaret		:= k83_00End + 32
?kcapODier		:= k83_00End + 33
?koAcute			:= k83_00End + 34
?koGrave			:= k83_00End + 35
?koCaret			:= k83_00End + 36
?koDier			:= k83_00End + 37
?kcapUAcute		:= k83_00End + 38
?kcapUGrave		:= k83_00End + 39
?kcapUCaret		:= k83_00End + 40
?kcapUDier		:= k83_00End + 41
?kuAcute			:= k83_00End + 42
?kuGrave			:= k83_00End + 43
?kuCaret			:= k83_00End + 44
?kuDier			:= k83_00End + 45
?kcapCCed		:= k83_00End + 46
?kcCed			:= k83_00End + 47
?kcapNTilde		:= k83_00End + 48
?knTilde			:= k83_00End + 49
?kaccent			:= k83_00End + 50
?kgrave			:= k83_00End + 51
?kdieresis		:= k83_00End + 52
?kquesDown		:= k83_00End + 53
?kexclamDown		:= k83_00End + 54
?kalpha			:= k83_00End + 55
?kbeta		 	:= k83_00End + 56
?kgamma			:= k83_00End + 57
?kcapDelta		:= k83_00End + 58
?kdelta			:= k83_00End + 59
?kepsilon		:= k83_00End + 60
?klambda			:= k83_00End + 61
?kmu			:= k83_00End + 62
?kpi2			:= k83_00End + 63
?krho			:= k83_00End + 64
?kcapSigma		:= k83_00End + 65
?ksigma			:= k83_00End + 66
?ktau			:= k83_00End + 67
?kphi			:= k83_00End + 68
?kcapOmega		:= k83_00End + 69
?kphat			:= k83_00End + 70
?kchi2			:= k83_00End + 71
?kstatF2			:= k83_00End + 72
?kLa			:= k83_00End + 73
?kLb			:= k83_00End + 74
?kLc			:= k83_00End + 75
?kLd			:= k83_00End + 76
?kLe			:= k83_00End + 77
?kLf			:= k83_00End + 78
?kLg			:= k83_00End + 79
?kLh			:= k83_00End + 80
?kLi			:= k83_00End + 81
?kLj			:= k83_00End + 82
?kLk			:= k83_00End + 83
?kLl			:= k83_00End + 84
?kLm			:= k83_00End + 85
?kLsmalln		:= k83_00End + 86
?kLo			:= k83_00End + 87
?kLp			:= k83_00End + 88
?kLq			:= k83_00End + 89
?kLsmallr		:= k83_00End + 90
?kLs			:= k83_00End + 91
?kLt			:= k83_00End + 92
?kLu			:= k83_00End + 93
?kLv			:= k83_00End + 94
?kLw			:= k83_00End + 95
?kLx			:= k83_00End + 96
?kLy			:= k83_00End + 97
?kLz			:= k83_00End + 98
?kGarbageC		:= k83_00End + 99 ;GarbageCollect
?kE2BT2_End		:= kGarbageC

;TI-83 Plus Context Equates
;--------------------------------------------------------------
?cxCmd			:= kQuit ;home screen
?cxMatEdit		:= kMatrixEd ;matrix editor
?cxPrgmEdit		:= kPrgmEd ;program editor
?cxEquEdit		:= kYequ ;equation editor
?cxGrRange		:= kWindow ;graph range editor
?cxGrZfact		:= kZFactEd ;graph zoom factors editor
?cxGraph			:= kGraph ;graph mode
?cxStatEdit		:= kStatEd ;statistics list editor
?cxPrgmInput		:= kPrgmInput ;programmed input
?cxError			:= kError ;error handler
?cxLinkIO		:= kLinkIO ;LINK I/O interface
?cxMem			:= kResetMem ;reset memory
?cxDefMem		:= kResetDef ;reset default
?cxRAMApp		:= kChkRAM ;RAM usage screen
?cxMode			:= kMode ;mode settings screen
?cxErase			:= kDelMem ;memory erase
?cxPrgmCreate		:= kPrgmCr ;PROGRAM CREATE
?cxTableEditor		:= kTable ;TABLE EDITOR
?cxTableSet		:= kTblSet ;TABLE SET UP
?cxStatPlot		:= kStatP ;STAT PLOTS
?cxInfStat		:= kInfStat ;Inferential Statistic
?cxFormat		:= kFormat ;FORMAT CONTEXT
?cxSolveTVM		:= kSolveTVM ;Solve TVM
?cxSolveRoot		:= kSolveRoot ;Solve Root
?lastOldApp		:= kExtApps ;external applications
?cxextapps		:= kExtApps
?cxNewApps		:= kNewApps ;new cerberus applications
?cxGroup			:= cxNewApps+0 ;1st new app.
?cxUnGroup		:= cxNewApps+1 ;2nd new app.
?lastNewApp		:= cxUnGroup ;last new app for this ver

;Scan Code Equates
;------------------------------
?skDown			:= 01h
?skLeft			:= 02h
?skRight			:= 03h
?skUp			:= 04h
?skEnter			:= 09h
?skAdd			:= 0Ah
?skSub			:= 0Bh
?skMul			:= 0Ch
?skDiv			:= 0Dh
?skPower			:= 0Eh
?skClear			:= 0Fh
?skChs			:= 11h
?sk3			:= 12h
?sk6			:= 13h
?sk9			:= 14h
?skRParen		:= 15h
?skTan			:= 16h
?skVars			:= 17h
?skDecPnt		:= 19h
?sk2			:= 1Ah
?sk5			:= 1Bh
?sk8			:= 1Ch
?skLParen		:= 1Dh
?skCos			:= 1Eh
?skPrgm			:= 1Fh
?skStat			:= 20h
?sk0			:= 21h
?sk1			:= 22h
?sk4			:= 23h
?sk7			:= 24h
?skComma			:= 25h
?skSin			:= 26h
?skMatrix		:= 27h
?skGraphvar		:= 28h
?skStore			:= 2Ah
?skLn			:= 2Bh
?skLog			:= 2Ch
?skSquare		:= 2Dh
?skRecip			:= 2Eh
?skMath			:= 2Fh
?skAlpha			:= 30h
?skGraph			:= 31h
?skTrace			:= 32h
?skZoom			:= 33h
?skWindow		:= 34h
?skYequ 			:= 35h
?sk2nd			:= 36h
?skMode			:= 37h
?skDel			:= 38h

; DI Keyboard Equates
;---------------------------
?DI_Mode		:= 0F50000h
?DI_Cntrl	:= 0F50004h
?DI_Int		:= 0F50008h
?DI_IntMask	:= 0F5000Ch

?kbdG1		:= 0F50012h
;----------------------------
?kbdGraph	:= 00000001b
?kbdTrace	:= 00000010b
?kbdZoom		:= 00000100b
?kbdWindow	:= 00001000b
?kbdYequ 	:= 00010000b
?kbd2nd		:= 00100000b
?kbdMode		:= 01000000b
?kbdDel		:= 10000000b

?kbitGraph	:= 00h
?kbitTrace	:= 01h
?kbitZoom	:= 02h
?kbitWindow	:= 03h
?kbitYequ := 04h
?kbit2nd		:= 05h
?kbitMode	:= 06h
?kbitDel		:= 07h

?kbdG2		:= 0F50014h
;----------------------------
?kbdStore	:= 00000010b
?kbdLn		:= 00000100b
?kbdLog		:= 00001000b
?kbdSquare	:= 00010000b
?kbdRecip	:= 00100000b
?kbdMath		:= 01000000b
?kbdAlpha	:= 10000000b

?kbitStore	:= 01h
?kbitLn		:= 02h
?kbitLog		:= 03h
?kbitSquare	:= 04h
?kbitRecip	:= 05h
?kbitMath	:= 06h
?kbitAlpha	:= 07h

?kbdG3		:= 0F50016h
;----------------------------
?kbd0		:= 00000001b
?kbd1		:= 00000010b
?kbd4		:= 00000100b
?kbd7		:= 00001000b
?kbdComma	:= 00010000b
?kbdSin		:= 00100000b
?kbdApps		:= 01000000b
?kbdGraphVar	:= 10000000b

?kbit0		:= 00h
?kbit1		:= 01h
?kbit4		:= 02h
?kbit7		:= 03h
?kbitComma	:= 04h
?kbitSin		:= 05h
?kbitApps	:= 06h
?kbitGraphVar	:= 07h

?kbdG4		:= 0F50018h
;----------------------------
?kbdDecPnt	:= 00000001b
?kbd2		:= 00000010b
?kbd5		:= 00000100b
?kbd8		:= 00001000b
?kbdLParen	:= 00010000b
?kbdCos		:= 00100000b
?kbdPgrm		:= 01000000b
?kbdStat		:= 10000000b

?kbitDecPnt	:= 00h
?kbit2		:= 01h
?kbit5		:= 02h
?kbit8		:= 03h
?kbitLParen	:= 04h
?kbitCos		:= 05h
?kbitPgrm	:= 06h
?kbitStat	:= 07h

?kbdG5		:= 0F5001Ah
;----------------------------
?kbdChs		:= 00000001b
?kbd3		:= 00000010b
?kbd6		:= 00000100b
?kbd9		:= 00001000b
?kbdRParen	:= 00010000b
?kbdTan		:= 00100000b
?kbdVars		:= 01000000b

?kbitChs		:= 00h
?kbit3		:= 01h
?kbit6		:= 02h
?kbit9		:= 03h
?kbitRParen	:= 04h
?kbitTan		:= 05h
?kbitVars	:= 06h

?kbdG6		:= 0F5001Ch
;----------------------------
?kbdEnter	:= 00000001b
?kbdAdd		:= 00000010b
?kbdSub		:= 00000100b
?kbdMul		:= 00001000b
?kbdDiv		:= 00010000b
?kbdPower	:= 00100000b
?kbdClear	:= 01000000b

?kbitEnter	:= 00h
?kbitAdd		:= 01h
?kbitSub		:= 02h
?kbitMul		:= 03h
?kbitDiv		:= 04h
?kbitPower	:= 05h
?kbitClear	:= 06h

?kbdG7		:= 0F5001Eh
;----------------------------
?kbdDown		:= 00000001b
?kbdLeft		:= 00000010b
?kbdRight	:= 00000100b
?kbdUp		:= 00001000b

?kbitDown	:= 00h
?kbitLeft	:= 01h
?kbitRight	:= 02h
?kbitUp		:= 03h

;Tokens
;-----------------------------------------------------
?EOSSTART		:= 00h

;DISPLAY CONVERSIONS COME IMMEDIATELY BEFORE 'TSTORE'
;
?DCONV			:= 01h
;
?tToDMS			:= DCONV ;01h
?tToDEC			:= DCONV+1 ;02h
?tToAbc			:= DCONV+2 ;03h > A b/c
;
?tStore			:= DCONV+3 ;04h Lstore 01
;
?tBoxPlot		:= 05h
;
?BRACKS			:= 06h
;
?tLBrack			:= BRACKS ;06h '['
?tRBrack			:= BRACKS+1 ;07h ']'
?tLBrace			:= BRACKS+2 ;08h '{'
?tRBrace			:= BRACKS+3 ;09h '}'
;
?tPOST1			:= BRACKS+4
;
?tFromRad		:= tPOST1 ;0Ah Lradian
?tFromDeg		:= tPOST1+1 ;0Bh Ldegree
?tRecip			:= tPOST1+2 ;0Ch Linverse
?tSqr			:= tPOST1+3 ;0Dh Lsquare
?tTrnspos		:= tPOST1+4 ;0Eh Ltranspose
?tCube			:= tPOST1+5 ;0Fh ' xor 3'
;
?tLParen			:= 10h ;10h '('
?tRParen			:= 11h ;11h ')'
;
?IMUN			:= 12h
;
?tRound			:= IMUN ;12h 'round'
?tPxTst			:= IMUN+1 ;13h 'PXL-TEST'
?tAug			:= IMUN+2 ;14h 'aug'
?tRowSwap		:= IMUN+3 ;15h 'rSwap'
?tRowPlus		:= IMUN+4 ;16h 'rAdd'
?tmRow			:= IMUN+5 ;17h 'multR'
?tmRowPlus		:= IMUN+6 ;18h 'mRAdd'
?tMax			:= IMUN+7 ;19h 'max'
?tMin			:= IMUN+8 ;1Ah 'min'
?tRToPr			:= IMUN+9 ;1Bh 'R>Pr
?tRToPo			:= IMUN+10 ;1Ch 'R>Po
?tPToRx			:= IMUN+11 ;1Dh 'P>Rx
?tPToRy			:= IMUN+12 ;1Eh 'P>Ry
?tMedian			:= IMUN+13 ;1Fh 'MEDIAN
?tRandM			:= IMUN+14 ;20h 'randM'
?tMean			:= IMUN+15 ;21h
?tRoot			:= IMUN+16 ;22h 'ROOT'
?tSeries			:= IMUN+17 ;23h 'seq'
?tFnInt			:= IMUN+18 ;24h 'fnInt'
?tNDeriv			:= IMUN+19 ;25h 'fnIr'
?tEvalF			:= IMUN+20 ;26h
?tFmin			:= IMUN+21 ;27h
?tFmax			:= IMUN+22 ;28h
;
?tEOSEL			:= IMUN+23
;
?tSpace			:= tEOSEL ;29h ' '
?tString			:= tEOSEL+1 ;2Ah '"'
?tComma			:= tEOSEL+2 ;2Bh ','
;
?tii			:= 2Ch ;i

;Postfix Functions
;-----------------------------------------
?tPost			:= 2Dh
;
?tFact			:= tPost ;2Dh '!'
;
?tCubicR			:= 2Eh
?tQuartR			:= 2Fh

;Number Tokens 
;---------------------------------------
?NUMS			:= 30h
;
?t0			:= NUMS ;30h
?t1			:= NUMS+1 ;31h
?t2			:= NUMS+2 ;32h
?t3			:= NUMS+3 ;33h
?t4			:= NUMS+4 ;34h
?t5			:= NUMS+5 ;35h
?t6			:= NUMS+6 ;36h
?t7			:= NUMS+7 ;37h
?t8			:= NUMS+8 ;38h
?t9			:= NUMS+9 ;39h
?tDecPt			:= NUMS+10 ;3Ah
?tee			:= NUMS+11 ;3Bh

;Binary OP
;-------------------------------------------
?tOr			:= 3Ch ;3Ch '_or_'
?tXor			:= 3Dh ;3Dh
;
?tColon			:= 3Eh ;3Eh ':'
?tEnter			:= 3Fh ;3Fh Lenter
;
?tAnd			:= 40h ;40h '_and_'

;Letter Tokens
;--------------------------------------
?LET			:= 41h
?tA			:= LET ;41h
?tB			:= LET+1 ;42h
?tC			:= LET+2 ;43h
?tD			:= LET+3 ;44h
?tE			:= LET+4 ;45h
?tF			:= LET+5 ;46h
?tG			:= LET+6 ;47h
?tH			:= LET+7 ;48h
?tI			:= LET+8 ;49h
?tJ			:= LET+9 ;4Ah
?tK			:= LET+10 ;4Bh
?tL			:= LET+11 ;4Ch
?tM			:= LET+12 ;4Dh
?tN			:= LET+13 ;4Eh
?tO			:= LET+14 ;4Fh
?tP			:= LET+15 ;50h
?tQ			:= LET+16 ;51h
?tR			:= LET+17 ;52h
?tS			:= LET+18 ;53h
?tT			:= LET+19 ;54h
?tU			:= LET+20 ;55h
?tV			:= LET+21 ;56h
?tW			:= LET+22 ;57h
?tX			:= LET+23 ;58h
?tY			:= LET+24 ;59h
?tZ			:= LET+25 ;5Ah
?tTheta			:= LET+26 ;5Bh

; Extended Tokens
;---------------------------
?tExtTok		:=	0EFh

?tSetDate	:=	00h
?tSetTime	:=	01h
?tCheckTmr	:=	02h
?tSetDtFmt	:=	03h
?tSetTmFmt	:=	04h
?tTimeCnv	:=	05h
?tDayOfWk	:=	06h
?tGetDtStr	:=	07h
?tGetTmStr	:=	08h
?tGetDate	:=	09h
?tGetTime	:=	0Ah
?tStartTmr	:=	0Bh
?tGtDtFmt	:=	0Ch
?tGetTmFmt	:=	0Dh
?tIsClockOn	:=	0Eh
?tClockOff	:=	0Fh
?tClockOn	:=	10h
?tOpenLib	:=	11h
?tExecLib	:=	12h
?tInvT		:=	13h
?tChiSquaredGofTest	:=	14h
?tLinRegTInt	:=	15h
?tManualFit	:=	16h

; MathPrint
?tZQuadrant	:=	17h
?tZFracHalf	:=	18h
?tZFracThird	:=	19h
?tZFracFourth	:=	1Ah
?tZFracFifth	:=	1Bh
?tZFracEighth	:=	1Ch
?tZFracTenth	:=	1Dh
?tFracSlash	:=	2Eh
?tFracMixedNum	:=	2Fh
?tSwapImProper	:=	30h
?tSwapFracDec	:=	31h
?tRemainder	:=	32h
?tSummationSigma	:=	33h
?tLogBase	:=	34h
?tRandIntNoRep	:=	35h
?tMathPrint	:=	37h
?tClassic	:=	38h
?tAutoAnswer	:=	3Bh
?tDecAnswer	:=	3Ch
?tFracAnswer	:=	3Dh

; TI-84+CSE/CE
?tBlue		:=	41h
?tRed		:=	42h
?tBlack 		:=	43h
?tMagenta	:=	44h
?tGreen		:=	45h
?tOrange		:=	46h
?tBrown		:=	47h
?tNavy		:=	48h
?tLtBlue		:=	49h
?tYellow		:=	4Ah
?tWhite		:=	4Bh
?tLtGray		:=	4Ch
?tMedGray	:=	4Dh
?tGray		:=	4Eh
?tDarkGray	:=	4Fh

?tGraphColor	:=	65h
?tTextColor	:=	67h
?tBackgroundOn	:=	5Bh
?tBackgroundOff	:=	64h

?tThin		:=	74h
;tThick - 0x7E 0x06 (was "Connected"?)
?tAsm84CPrgm	:=	68h
?tAsm84CCmp	:=	69h
?tBorderColor	:=	6Ch

?tAsm84CeCmp	:=	07Bh
?tAsm84CePrgm	:=	07Ah

; OS 5.2+ only
?tLEFT           :=     92h
?tCENTER         :=     93h
?tRIGHT          :=     94h
?tInvBinom       :=     95h
?tWait           :=     96h
?tToString       :=     97h
?tEval           :=     98h

;These Var Tokens Are 1st Of A Double Token
;-----------------------------------------------

?vToks			:= LET+27

;User Matrix Token, 2nd Token Needed For Name
;
?tVarMat			:= vToks ;5Ch
;
;User List Token, 2nd Token Needed For Name
;
?tVarLst			:= vToks+1 ;5Dh
;
;User Equation Token, 2nd Token Needed For Name
;
?tVarequ 		:= vToks+2 ;5Eh
?tProg			:= vToks+3 ;5Fh
;
;User Pict Token, 2nd Token Needed For Name
;
?tVarPict		:= vToks+4 ;60h
;
;User GDB Token, 2nd Token Needed For Name
;
?tVarGDB			:= vToks+5 ;61h
?tVarOut			:= vToks+6 ;62h
?tVarSys			:= vToks+7 ;63h

;Mode Setting Commands
;-------------------------------------------------
?MODESA			:= vToks+8 ;64h
?tRad			:= MODESA ;64h 'Radian'
?tDeg			:= MODESA+1 ;65h 'Degree'
?tNormF			:= MODESA+2 ;66h 'Normal'
?tSci			:= MODESA+3 ;67h 'Sci'
?tEng			:= MODESA+4 ;68h 'Eng'
?tFloat			:= MODESA+5 ;69h 'Float'
?CMPS			:= 6Ah
?tEQ			:= CMPS ;6Ah '=='
?tLT			:= CMPS+1 ;6Bh '<'
?tGT			:= CMPS+2 ;6Ch '>'
?tLE			:= CMPS+3 ;6Dh LLE
?tGE			:= CMPS+4 ;6Eh LGE
?tNE			:= CMPS+5 ;6Fh LNE

;Binary OP
;---------------------------------------
?tAdd			:= 70h ;70h '+'
?tSub			:= 71h ;71h '-'
?tAns			:= 72h ;72h

;Mode Setting Commands
;------------------------------------------------------
?MODES			:= 73h
?tFix			:= MODES ;73h 'Fix_'
?tSplitOn		:= MODES+1 ;74h
?tFullScreen		:= MODES+2 ;75h
?tStndrd			:= MODES+3 ;76h 'Func'
?tParam			:= MODES+4 ;77h 'Param'
?tPolar			:= MODES+5 ;78h 'Pol'
?tSeqG			:= MODES+6 ;79h
?tAFillOn		:= MODES+7 ;7Ah 'AUTO FILL ON'
?tAFillOff		:= MODES+8 ;7Bh
?tACalcOn		:= MODES+9 ;7Ch
?tACalcOff		:= MODES+10 ;7Dh 'AutoFill OFF'

;Graph Format Tokens Are 2 Byte Tokens
;----------------------------------------
?tGFormat		:= MODES+11 ;7Eh
?tBoxIcon		:= 7Fh
?tCrossIcon		:= 80h
?tDotIcon		:= 81h

;(More) Binary OP
;---------------------------------------
?tMul			:= 82h ;82h '*'
?tDiv			:= 83h ;83h '/'

;Some Graph Commands
;-----------------------------------------------------
?GRCMDS			:= 84h
?tTrace			:= GRCMDS ; 84h 'Trace'
?tClDrw			:= GRCMDS+1 ; 85h 'ClDrw'
?tZoomStd		:= GRCMDS+2 ; 86h 'ZStd'
?tZoomtrg		:= GRCMDS+3 ; 87h 'Ztrg'
?tZoomBox		:= GRCMDS+4 ; 88h 'ZBOX'
?tZoomIn			:= GRCMDS+5 ; 89h 'ZIn'
?tZoomOut		:= GRCMDS+6 ; 8Ah 'ZOut'
?tZoomSqr		:= GRCMDS+7 ; 8Bh 'ZSqr'
?tZoomInt		:= GRCMDS+8 ; 8Ch 'ZInt'
?tZoomPrev		:= GRCMDS+9 ; 8Dh 'ZPrev'
?tZoomDec		:= GRCMDS+10 ; 8Eh 'ZDecm'
?tZoomStat		:= GRCMDS+11 ; 8Fh 'ZStat
?tUsrZm			:= GRCMDS+12 ; 90h 'ZRcl'
?tPrtScrn		:= GRCMDS+13 ; 91h 'PrtScrn'
?tZoomSto		:= GRCMDS+14 ; 92h  ZOOM STORE
?tText			:= GRCMDS+15 ; 93h

;Binary OP (Combination and Permutation)
;-------------------------------------------------
?tnPr			:= GRCMDS+16 ;94h '_nPr_'
?tnCr			:= GRCMDS+17 ;95h '_nCr_'

;More Graph Commands
;--------------------------------------------------
?tYOn			:= GRCMDS+18 ;96h 'FnOn_'
?tYOff			:= GRCMDS+19 ;97h 'FnOff_'
?tStPic			:= GRCMDS+20 ;98h 'StPic_'
?tRcPic			:= GRCMDS+21 ;99h 'RcPic_'
?tStoDB			:= GRCMDS+22 ;9Ah 'StGDB_'
?tRclDB			:= GRCMDS+23 ;9Bh 'RcGDB_'
?tLine			:= GRCMDS+24 ;9Ch 'Line'
?tVert			:= GRCMDS+25 ;9Dh 'Vert_'
?tPtOn			:= GRCMDS+26 ;9Eh 'PtOn'
?tPtOff			:= GRCMDS+27 ;9Fh 'PtOff'

;Token A0 Cannot Be An EOS Function Since Low MULT=A0 Already
;-----------------------------------------------------
?tPtChg			:= GRCMDS+28 ;A0h 'PtChg'
?tPXOn			:= GRCMDS+29 ;A1h
?tPXOff			:= GRCMDS+30 ;A2h
?tPXChg			:= GRCMDS+31 ;A3h
?tShade			:= GRCMDS+32 ;A4h 'Shade'
?tCircl			:= GRCMDS+33 ;A5h 'Circl'
?tHorz			:= GRCMDS+34 ;A6h 'HORIZONTAL'
?tTanLn			:= GRCMDS+35 ;A7h 'TanLn'
?tDrInv			:= GRCMDS+36 ;A8h 'DrInv_'
?tDrawF			:= GRCMDS+37 ;A9h 'DrawF_'
?tVarStrng		:= 0AAh

;Functions with No Arguments
;--------------------------------------------------
?NOARG			:= 0ABh
?tRand			:= NOARG ;ABh 'rand'
?tPi			:= NOARG+1 ;ACh  Lpi
?tGetKey			:= NOARG+2 ;ADh 'getKy'
?tAPost			:= tGetKey+1 ;APOSTROPHY
?tQuest			:= tAPost+1 ;QUESTION MARK
?UNARY			:= tQuest+1 ;B0h
?tChs			:= UNARY ;B0h
?tInt			:= UNARY+1 ;B1h
?tAbs			:= UNARY+2 ;B2h
?tDet			:= UNARY+3 ;B3h
?tIdent			:= UNARY+4 ;B4h
?tDim			:= UNARY+5 ;B5h
?tSum			:= UNARY+6 ;B6h
?tProd			:= UNARY+7 ;B7h
?tNot			:= UNARY+8 ;B8h
?tIPart			:= UNARY+9 ;B9h
?tFPart			:= UNARY+10 ;BAh

;New 2 Byte Tokens
;------------------------------------------
?t2ByteTok		:= 0BBh
?UNARYLR			:= UNARY+12
?tSqrt			:= UNARYLR ;BCh
?tCubRt			:= UNARYLR+1 ;BDh
?tLn			:= UNARYLR+2 ;BEh
?tExp			:= UNARYLR+3 ;BFh
?tLog			:= UNARYLR+4 ;C0h
?tALog			:= UNARYLR+5 ;C1h
?tSin			:= UNARYLR+6 ;C2h
?tASin			:= UNARYLR+7 ;C3h
?tCos			:= UNARYLR+8 ;C4h
?tACos			:= UNARYLR+9 ;C5h
?tTan			:= UNARYLR+10 ;C6h
?tATan			:= UNARYLR+11 ;C7h
?tSinH			:= UNARYLR+12 ;C8h
?tASinH			:= UNARYLR+13 ;C9h
?tCoshH			:= UNARYLR+14 ;CAh
?tACosH			:= UNARYLR+15 ;CBh
?tTanH			:= UNARYLR+16 ;CCh
?tATanH			:= UNARYLR+17 ;CDh

;Some Programming Commands
;---------------------------------------------------
?PROGTOK			:= UNARYLR+18
?tIf			:= PROGTOK ;CEh
?tThen			:= PROGTOK+1 ;CFh
?tElse			:= PROGTOK+2 ;D0h
?tWhile			:= PROGTOK+3 ;D1h
?tRepeat			:= PROGTOK+4 ;D2h
?tFor			:= PROGTOK+5 ;D3h
?tEnd			:= PROGTOK+6 ;D4h
?tReturn			:= PROGTOK+7 ;D5h
?tLbl			:= PROGTOK+8 ;D6h 'Lbl_'
?tGoto			:= PROGTOK+9 ;D7h 'Goto_'
?tPause			:= PROGTOK+10 ;D8h 'Pause_'
?tStop			:= PROGTOK+11 ;D9h 'Stop'
?tISG			:= PROGTOK+12 ;DAh 'IS>'
?tDSL			:= PROGTOK+13 ;DBh 'DS<'
?tInput			:= PROGTOK+14 ;DCh 'Input_'
?tPrompt			:= PROGTOK+15 ;DDh 'Prompt_'
?tDisp			:= PROGTOK+16 ;DEh 'Disp_'
?tDispG			:= PROGTOK+17 ;DFh 'DispG'
?tOutput			:= PROGTOK+18 ;E0h 'Outpt'
?tClLCD			:= PROGTOK+19 ;E1h 'ClLCD'
?tConst			:= PROGTOK+20 ;E2h 'Fill'
?tSortA			:= PROGTOK+21 ;E3h 'sortA_'
?tSortD			:= PROGTOK+22 ;E4h 'sortD_'
?tDispTab		:= PROGTOK+23 ;E5h 'Disp Table
?tMenu			:= PROGTOK+24 ;E6h 'Menu'
?tSendMBL		:= PROGTOK+25 ;E7h 'SEND'
?tGetMBL			:= PROGTOK+26 ;E8h 'GET'

;Stat Plot Commands
;-----------------------------------------------------
?statPCmd		:= PROGTOK+27
?tPlotOn			:= statPCmd ;E9h ' PLOTSON'
?tPlotOff		:= statPCmd+1 ;EAh ' PLOTSOFF
?tListName		:= 0EBh ;LIST DESignATOR
?tPlot1			:= 0ECh
?tPlot2			:= 0EDh
?tPlot3			:= 0EEh
?tUnused01		:= 0EFh ;available?
?tPower			:= 0F0h ;' xor '
?tXRoot			:= 0F1h ;LsupX,Lroot
?STATCMD			:= 0F2h
?tOneVar			:= STATCMD ;F2h 'OneVar_'
?tTwoVar			:= STATCMD+1 ;F3h
?tLR			:= STATCMD+2 ;F4h 'LinR(A+BX
?tLRExp			:= STATCMD+3 ;F5h 'ExpR_'
?tLRLn			:= STATCMD+4 ;F6h 'LnR_'
?tLRPwr			:= STATCMD+5 ;F7h 'PwrR_'
?tMedMed			:= STATCMD+6 ;F8h
?tQuad			:= STATCMD+7 ;F9h
?tClrLst			:= STATCMD+8 ;FAh 'CLEAR LIST
?tClrTbl			:= STATCMD+9 ;FBh CLEAR TABLE
?tHist			:= STATCMD+10 ;FCh 'Hist_'
?txyLine			:= STATCMD+11 ;FDh 'xyline_'
?tScatter		:= STATCMD+12 ;FEh 'Scatter_'
?tLR1			:= STATCMD+13 ;FFh 'LINR(AX+B

;2nd Half Of Graph Format Tokens
;Format settings commands
;---------------------------------------------
?GFMT			:= 00h
?tSeq			:= GFMT ; 'SeqG'
?tSimulG			:= GFMT+1 ; 'SimulG'
?tPolarG			:= GFMT+2 ; 'PolarGC'
?tRectG			:= GFMT+3 ; 'RectGC'
?tCoordOn		:= GFMT+4 ; 'CoordOn'
?tCoordOff		:= GFMT+5 ; 'CoordOff'
?tDrawLine		:= GFMT+6 ; 'DrawLine'
?tDrawDot		:= GFMT+7 ; 'DrawDot'
?tAxisOn			:= GFMT+8 ; 'AxesOn'
?tAxisOff		:= GFMT+9 ; 'AxesOff'
?tGridOn			:= GFMT+10 ; 'GridOn'
?tGridOff		:= GFMT+11 ; 'GridOff'
?tLblOn			:= GFMT+12 ; 'LabelOn'
?tLblOff			:= GFMT+13 ; 'LabelOff'
?tWebOn			:= GFMT+14 ; 'WebOn'
?tWebOff			:= GFMT+15 ; 'WebOFF'
?tuv			:= GFMT+16 ; U vs V
?tvw			:= GFMT+17 ; V vs W
?tuw			:= GFMT+18 ; U vs W

;2nd Half Of User Matrix Tokens
;-------------------------------------
?tMatA			:= 00h ;MAT A
?tMatB			:= 01h ;MAT B
?tMatC			:= 02h ;MAT C
?tMatD			:= 03h ;MAT D
?tMatE			:= 04h ;MAT E
?tMatF			:= 05h ;MAT F
?tMatG			:= 06h ;MAT G
?tMatH			:= 07h ;MAT H
?tMatI			:= 08h ;MAT I
?tMatJ			:= 09h ;MAT J

;2nd Half Of User List Tokens
;--------------------------------------
?tL1			:= 00h ;LIST 1
?tL2			:= 01h ;LIST 2
?tL3			:= 02h ;LIST 3
?tL4			:= 03h ;LIST 4
?tL5			:= 04h ;LIST 5
?tL6			:= 05h ;LIST 6

;2nd Half Of User Equation Tokens
;----------------------------------
;  "Y" EQUATIONS HAVE BIT 4 SET
;
?tY1			:= 10h ;Y1
?tY2			:= 11h ;Y2
?tY3			:= 12h ;Y3
?tY4			:= 13h ;Y4
?tY5			:= 14h ;Y5
?tY6			:= 15h ;Y6
?tY7			:= 16h ;Y7
?tY8			:= 17h ;Y8
?tY9			:= 18h ;Y9
?tY0			:= 19h ;Y0

;Param Equations Have Bit 5 Set
;-----------------------------------
?tX1T			:= 20h ;X1t
?tY1T			:= 21h ;Y1t
?tX2T			:= 22h ;X2t
?tY2T			:= 23h ;Y2t
?tX3T			:= 24h ;X3t
?tY3T			:= 25h ;Y3t
?tX4T			:= 26h ;X4t
?tY4T			:= 27h ;Y4t
?tX5T			:= 28h ;X5t
?tY5T			:= 29h ;Y5t
?tX6T			:= 2Ah ;X6t
?tY6T			:= 2Bh ;Y6t

;Polar Equations Have Bit 6 Set
;----------------------------------
?tR1			:= 40h ;R1
?tR2			:= 41h ;R2
?tR3			:= 42h ;R3
?tR4			:= 43h ;R4
?tR5			:= 44h ;R5
?tR6			:= 45h ;R6

;Recursion Equations Have Bit 7 Set
;----------------------------------
?tun			:= 80h ;Un
?tvn			:= 81h ;Vn
?twn			:= 82h ;Wn

;2nd Half User Picture Tokens
;------------------------------------
?tPic1			:= 00h ;PIC1
?tPic2			:= 01h ;PIC2
?tPic3			:= 02h ;PIC3
?tPic4			:= 03h ;PIC4
?tPic5			:= 04h ;PIC5
?tPic6			:= 05h ;PIC6
?tPic7			:= 06h ;PIC7
?tPic8			:= 07h ;PIC8
?tPic9			:= 08h ;PIC9
?tPic0			:= 09h ;PIC0

;2nd Half User Graph Database Tokens
;------------------------------------
?tGDB1			:= 00h ;GDB1
?tGDB2			:= 01h ;GDB2
?tGDB3			:= 02h ;GDB3
?tGDB4			:= 03h ;GDB4
?tGDB5			:= 04h ;GDB5
?tGDB6			:= 05h ;GDB6
?tGDB7			:= 06h ;GDB7
?tGDB8			:= 07h ;GDB8
?tGDB9			:= 08h ;GDB9
?tGDB0			:= 09h ;GDB0

;2nd Half Of String Vars
;------------------------------
?tStr1			:= 00h
?tStr2			:= 01h
?tStr3			:= 02h
?tStr4			:= 03h
?tStr5			:= 04h
?tStr6			:= 05h
?tStr7			:= 06h
?tStr8			:= 07h
?tStr9			:= 08h
?tStr0			:= 09h

;2nd Half Of System Output Only Variables
;----------------------------------------------------------------
;OPEN			equ 00h
?tRegEq			:= 01h ;REGRESSION EQUATION
?tStatN			:= 02h ;STATISTICS N
?tXMean			:= 03h ;X MEAN
?tSumX			:= 04h ;SUM(X)
?tSumXSqr		:= 05h ;SUM(X xor 2)
?tStdX			:= 06h ;STANDARD DEV X
?tStdPX			:= 07h ;STANDARD DEV POP X
?tMinX			:= 08h ;Min X VALUE
?tMaxX			:= 09h ;Max X VALUE
?tMinY			:= 0Ah ;Min Y VALUE
?tMaxY			:= 0Bh ;Max Y VALUE
?tYmean			:= 0Ch ;Y MEAN
?tSumY			:= 0Dh ;SUM(Y)
?tSumYSqr		:= 0Eh ;SUM(Y xor 2)
?tStdY			:= 0Fh ;STANDARD DEV Y
?tStdPY			:= 10h ;STANDARD DEV POP Y
?tSumXY			:= 11h ;SUM(XY)
?tCorr			:= 12h ;CORRELATION
?tMedX			:= 13h ;MED(X)
?tQ1			:= 14h ;1ST QUADRANT OF X
?tQ3			:= 15h ;3RD QUADRANT OF X
?tQuadA			:= 16h ;1ST TERM OF QUAD POLY REG/ Y-INT
?tQuadB			:= 17h ;2ND TERM OF QUAD POLY REG/ SLOPE
?tQuadC			:= 18h ;3RD TERM OF QUAD POLY REG
?tCubeD			:= 19h ;4TH TERM OF CUBIC POLY REG
?tQuartE			:= 1Ah ;5TH TERM OF QUART POLY REG
?tMedX1			:= 1Bh ;x1 FOR MED-MED
?tMedX2			:= 1Ch ;x2 FOR MED-MED
?tMedX3			:= 1Dh ;x3 FOR MED-MED
?tMedY1			:= 1Eh ;y1 FOR MED-MED
?tMedY2			:= 1Fh ;y2 FOR MED-MED
?tMedY3			:= 20h ;y3 FOR MED-MED
?tRecurn			:= 21h	;RECURSION N
?tStatP			:= 22h
?tStatZ			:= 23h
?tStatT			:= 24h
?tStatChi		:= 25h
?tStatF			:= 26h
?tStatDF			:= 27h
?tStatPhat		:= 28h
?tStatPhat1		:= 29h
?tStatPhat2		:= 2Ah
?tStatMeanX1		:= 2Bh
?tStatStdX1		:= 2Ch
?tStatN1			:= 2Dh
?tStatMeanX2		:= 2Eh
?tStatStdX2		:= 2Fh
?tStatN2			:= 30h
?tStatStdXP		:= 31h
?tStatLower		:= 32h
?tStatUpper		:= 33h
?tStat_s			:= 34h
?tLRSqr			:= 35h ;r xor 2
?tBRSqr			:= 36h ;R xor 2

;These next tokens are only used to access the data
;they are display only and the user cannot access them at all
;------------------------------------------------------------
?tF_DF			:= 37h ;ANOFAV FACTOR DF
?tF_SS			:= 38h ;ANOFAV FACTOR SS
?tF_MS			:= 39h ;ANOFAV FACTOR MS
?tE_DF			:= 3Ah ;ANOFAV ERROR DF
?tE_SS			:= 3Bh ;ANOFAV ERROR SS
?tE_MS			:= 3Ch ;ANOFAV ERROR MS

;2nd Half Of System Input/Output Variables
;------------------------------------------------
;		SYSTEM VARIABLE EQUATES
;
?tuXscl			:= 0
?tuYscl			:= 1
?tXscl			:= 2
?tYscl			:= 3
?tRecuru0		:= 4 ;U 1ST INITIAL COND
?tRecurv0		:= 5 ;V 1ST INITIAL COND
?tun1			:= 6 ;U(N-1); NOT USED
?tvn1			:= 7 ;V(N-1); NOT USED
?tuRecuru0		:= 8 ;
?tuRecurv0		:= 9 ;
?tXmin			:= 0Ah
?tXmax			:= 0Bh
?tYmin			:= 0Ch
?tYmax			:= 0Dh
?tTmin			:= 0Eh
?tTmax			:= 0Fh
?tThetaMin		:= 10h
?tThetaMax		:= 11h
?tuXmin			:= 12h
?tuXmax			:= 13h
?tuYmin			:= 14h
?tuYmax			:= 15h
?tuThetMin		:= 16h
?tuThetMax		:= 17h
?tuTmin			:= 18h
?tuTmax			:= 19h
?tTblMin			:= 1Ah
?tPlotStart		:= 1Bh
?tuPlotStart		:= 1Ch
?tnMax			:= 1Dh
?tunMax			:= 1Eh
?tnMin			:= 1Fh
?tunMin			:= 20h
?tTblStep		:= 21h
?tTStep			:= 22h
?tThetaStep		:= 23h
?tuTStep			:= 24h
?tuThetStep		:= 25h
?tDeltaX			:= 26h
?tDeltaY			:= 27h
?tXFact			:= 28h
?tYFact			:= 29h
?tTblInput		:= 2Ah
?tFinN			:= 2Bh
?tFinI			:= 2Ch
?tFinPV			:= 2Dh
?tFinPMT			:= 2Eh
?tFinFV			:= 2Fh
?tFinPY			:= 30h
?tFinCY			:= 31h
?tRecurw0		:= 32h ;w0(1)
?tuRecurw0		:= 33h
?tPlotStep		:= 34h
?tuPlotStep		:= 35h
?tXres			:= 36h
?tuXres			:= 37h
?tRecuru02		:= 38h ;u0(2)
?tuRecuru02		:= 39h
?tRecurv02		:= 3Ch ;v0(2)
?tuRecurv02		:= 3Dh
?tRecurw02		:= 3Eh ;w0(2)
?tuRecurw02		:= 3Fh

;2nd Byte Of t2ByteTok Tokens
;------------------------------
?tFinNPV			:= 00h
?tFinIRR			:= 01h
?tFinBAL			:= 02h
?tFinPRN			:= 03h
?tFinINT			:= 04h
?tFinToNom		:= 05h
?tFinToEff		:= 06h
?tFinDBD			:= 07h
?tLCM			:= 08h
?tGCD			:= 09h
?tRandInt		:= 0Ah
?tRandBin		:= 0Bh
?tSubStrng		:= 0Ch
?tStdDev			:= 0Dh
?tVariance		:= 0Eh
?tInStrng		:= 0Fh
?tDNormal		:= 10h
?tInvNorm		:= 11h
?tDT			:= 12h
?tChI			:= 13h
?tDF			:= 14h
?tBINPDF			:= 15h
?tBINCDF			:= 16h
?tPOIPDF			:= 17h
?tPOICDF			:= 18h
?tGEOPDF			:= 19h
?tGEOCDF			:= 1Ah
?tNormalPDF		:= 1Bh
?tTPDF			:= 1Ch
?tChiPDF			:= 1Dh
?tFPDF			:= 1Eh
?tRandNorm		:= 1Fh
?tFinFPMT		:= 20h
?tFinFI			:= 21h
?tFinFPV			:= 22h
?tFinFN			:= 23h
?tFinFFV			:= 24h
?tConj			:= 25h
?tReal			:= 26h
?tImag			:= 27h
?tAngle			:= 28h
?tCumSum			:= 29h
?tExpr			:= 2Ah
?tLength			:= 2Bh
?tDeltaLst		:= 2Ch
?tRef			:= 2Dh
?tRRef			:= 2Eh
?tToRect			:= 2Fh
?tToPolar		:= 30h
?tConste			:= 31h
?tSinReg			:= 32h
?tLogistic		:= 33h
?tLinRegTTest		:= 34h
?tShadeNorm		:= 35h
?tShadeT			:= 36h
?tShadeChi		:= 37h
?tShadeF			:= 38h
?tMatToLst		:= 39h
?tLstToMat		:= 3Ah
?tZTest			:= 3Bh
?tTTest			:= 3Ch
?t2SampZTest		:= 3Dh
?t1PropZTest		:= 3Eh
?t2PropZTest		:= 3Fh
?tChiTest		:= 40h
?tZIntVal		:= 41h
?t2SampZInt		:= 42h
?t1PropZInt		:= 43h
?t2PropZInt		:= 44h
?tGraphStyle		:= 45h
?t2SampTTest		:= 46h
?t2SampFTest		:= 47h
?tTIntVal		:= 48h
?t2SampTInt		:= 49h
?tSetupLst		:= 4Ah
?tFinPMTend		:= 4Bh
?tFinPMTbeg		:= 4Ch
?tRealM			:= 4Dh
?tPolarM			:= 4Eh
?tRectM			:= 4Fh
?tExprOn			:= 50h
?tExprOff		:= 51h
?tClrAllLst		:= 52h
?tGetCalc		:= 53h
?tDelVar			:= 54h
?tEquToStrng		:= 55h
?tStrngToequ 		:= 56h
?tDelLast		:= 57h
?tSelect			:= 58h
?tANOVA			:= 59h
?tModBox			:= 5Ah
?tNormProb		:= 5Bh
?tMGT			:= 64h ;VERTICAL SPLIT
?tZFit			:= 65h ;ZOOM FIT
?tDiag_on		:= 66h ;DIANOSTIC DISPLAY ON
?tDiag_off		:= 67h ;DIANOSTIC DISPLAY OFF
?tOkEnd2v0		:= 67h ;end of 2byte tokens for version 0.
?tArchive		:= 68h ;archive
?tUnarchive		:= 69h ;unarchive
?tasm			:= 6Ah
?tasmComp		:= 6Bh	;asm compile
?tasmPrgm		:= 6Ch	;Signifies a program is asm
?tasmCmp			:= 6Dh	;asm program is compiled
?tLcapAAcute		:= 6Eh
?tLcapAGrave		:= 6Fh
?tLcapACaret		:= 70h
?tLcapADier		:= 71h
?tLaAcute		:= 72h
?tLaGrave		:= 73h
?tLaCaret		:= 74h
?tLaDier			:= 75h
?tLcapEAcute		:= 76h
?tLcapEGrave		:= 77h
?tLcapECaret		:= 78h
?tLcapEDier		:= 79h
?tLeAcute		:= 7Ah
?tLeGrave		:= 7Bh
?tLeCaret		:= 7Ch
?tLeDier			:= 7Dh
?tLcapIGrave		:= 7Fh
?tLcapICaret		:= 80h
?tLcapIDier		:= 81h
?tLiAcute		:= 82h
?tLiGrave		:= 83h
?tLiCaret		:= 84h
?tLiDier			:= 85h
?tLcapOAcute		:= 86h
?tLcapOGrave		:= 87h
?tLcapOCaret		:= 88h
?tLcapODier		:= 89h
?tLoAcute		:= 8Ah
?tLoGrave		:= 8Bh
?tLoCaret		:= 8Ch
?tLoDier			:= 8Dh
?tLcapUAcute		:= 8Eh
?tLcapUGrave		:= 8Fh
?tLcapUCaret		:= 90h
?tLcapUDier		:= 91h
?tLuAcute		:= 92h
?tLuGrave		:= 93h
?tLuCaret		:= 94h
?tLuDier			:= 95h
?tLcapCCed		:= 96h
?tLcCed			:= 97h
?tLcapNTilde		:= 98h
?tLnTilde		:= 99h
?tLaccent		:= 9Ah
?tLgrave			:= 9Bh
?tLdieresis		:= 9Ch
?tLquesDown		:= 9Dh
?tLexclamDown		:= 9Eh
?tLalpha			:= 9Fh
?tLbeta			:= 0A0h
?tLgamma			:= 0A1h
?tLcapDelta		:= 0A2h
?tLdelta			:= 0A3h
?tLepsilon		:= 0A4h
?tLlambda		:= 0A5h
?tLmu			:= 0A6h
?tLpi			:= 0A7h
?tLrho			:= 0A8h
?tLcapSigma		:= 0A9h
?tLphi			:= 0ABh
?tLcapOmega		:= 0ACh
?tLphat			:= 0ADh
?tLchi			:= 0AEh
?tLstatF			:= 0AFh
?tLa			:= 0B0h
?tLb			:= 0B1h
?tLc			:= 0B2h
?tLd			:= 0B3h
?tLsmalle		:= 0B4h
?tLf			:= 0B5h
?tLsmallg		:= 0B6h
?tLh			:= 0B7h
?tLi			:= 0B8h
?tLj			:= 0B9h
?tLk			:= 0BAh
?tLl			:= 0BCh
?tLm			:= 0BDh
?tLsmalln		:= 0BEh
?tLo			:= 0BFh
?tLp			:= 0C0h
?tLq			:= 0C1h
?tLsmallr		:= 0C2h
?tLs			:= 0C3h
?tLsmallt		:= 0C4h
?tLu			:= 0C5h
?tLv			:= 0C6h
?tLw			:= 0C7h
?tLx			:= 0C8h
?tLy			:= 0C9h
?tLz			:= 0CAh
?tLsigma			:= 0CBh
?tLtau			:= 0CCh
?tLcapIAcute		:= 0CDh
?tGarbagec		:= 0CEh
?LastToken		:= 0CEh ;tLAST TOKEN IN THIS VERSION...

;Data Type Equates
;---------------------------------------------------------------------
?RealObj			:= 0
?ListObj			:= 1
?MatObj			:= 2
?EquObj			:= 3
?StrngObj		:= 4
?ProgObj			:= 5
?ProtProgObj		:= 6
?PictObj			:= 7
?GDBObj			:= 8
?UnknownObj		:= 9
?UnknownEquObj		:= 0Ah
?NewEquObj		:= 0Bh
?CplxObj			:= 0Ch
?CListObj		:= 0Dh
?UndefObj		:= 0Eh
?WindowObj		:= 0Fh
?ZStoObj			:= 10h
?TblRngObj		:= 11h
?LCDObj			:= 12h
?BackupObj		:= 13h
?AppObj			:= 14h	;application, only used in menus/link
?AppVarObj		:= 15h	;application variable
?TempProgObj		:= 16h ;program, home deletes when finished
?GroupObj		:= 17h ;group.

;System Error Codes
;-----------------------------------------------------------
?E_EDITF			:= 7 ;allow re-entering application
?E_EDIT			:= 1 shl E_EDITF
?E_Mask			:= 7Fh
?E_Overflow		:= 1+E_EDIT
?E_DivBy0		:= 2+E_EDIT
?E_SingularMat		:= 3+E_EDIT
?E_Domain		:= 4+E_EDIT
?E_Increment		:= 5+E_EDIT
?E_Break			:= 6+E_EDIT
?E_NonReal		:= 7+E_EDIT
?E_Syntax		:= 8+E_EDIT
?E_DataType		:= 9+E_EDIT
?E_Argument		:= 10+E_EDIT
?E_DimMismatch		:= 11+E_EDIT
?E_Dimension		:= 12+E_EDIT
?E_Undefined		:= 13+E_EDIT
?E_Memory		:= 14+E_EDIT		; 142
?E_Invalid		:= 15+E_EDIT		; 143
?E_IllegalNest		:= 16+E_EDIT		; 144
?E_Bound			:= 17+E_EDIT		; 145
?E_GraphRange		:= 18+E_EDIT		; 146
?E_Zoom			:= 19+E_EDIT		; 147
?E_Label			:= 20			; 148
?E_Stat			:= 21			; 149
?E_Solver		:= 22+E_EDIT
?E_Singularity		:= 23+E_EDIT
?E_SignChange		:= 24+E_EDIT
?E_Iterations		:= 25+E_EDIT
?E_BadGuess		:= 26+E_EDIT
?E_StatPlo		:= 27
?E_TolTooSmall		:= 28+E_EDIT
?E_Reserved		:= 29+E_EDIT
?E_Mode			:= 30+E_EDIT
?E_LnkErr		:= 31+E_EDIT
?E_LnkMemErr		:= 32+E_EDIT
?E_LnkTransErr		:= 33+E_EDIT
?E_LnkDupErr		:= 34+E_EDIT
?E_LnkMemFull		:= 35+E_EDIT
?E_Unknown		:= 36+E_EDIT
?E_Scale			:= 37+E_EDIT
?E_IdNotFound		:= 38
?E_NoMode		:= 39+E_EDIT
?E_Validation		:= 40
?E_Length		:= 41+E_EDIT
?E_Application		:= 42+E_EDIT
?E_AppErr1		:= 43+E_EDIT
?E_AppErr2		:= 44+E_EDIT
?E_ExpiredApp		:= 45
?E_BadAdd		:= 46
?E_Archived		:= 47+E_EDIT
?E_Version		:= 48
?E_ArchFull		:= 49
?E_Variable		:= 50+E_EDIT
?E_Duplicate		:= 51+E_EDIT

;System Variable Equates
;------------------------------
?XSCLt			:= 02h
?YSCLt			:= 03h
?XMINt			:= 0Ah
?XMAXt			:= 0Bh
?YMINt			:= 0Ch
?YMAXt			:= 0Dh
?TMINt			:= 0Eh
?TMAXt			:= 0Fh
?THETMINt		:= 10h
?THETMAXt		:= 11h
?TBLMINt			:= 1Ah
?PLOTSTARTt		:= 1Bh
?NMAXt			:= 1Dh
?NMINt			:= 1Fh
?TBLSTEPt		:= 21h
?TSTEPt			:= 22h
?THETSTEPt		:= 23h
?DELTAXt			:= 26h
?DELTAYt			:= 27h
?XFACTt			:= 28h
?YFACTt			:= 29h
?FINNt			:= 2Bh
?FINIt			:= 2Ch
?FINPVt			:= 2Dh
?FINPMTt			:= 2Eh
?FINFVt			:= 2Fh
?FINPYt			:= 30h
?FINCYt			:= 31h
?PLOTSTEPt		:= 34h
?XRESt			:= 36h

;Equates To RAM Locations For Stat Vars
;----------------------------------------------------------------
?FPLEN			:= 9 ;Length of a floating-point number.
?StatN			:= statVars
?XMean			:= StatN + FPLEN
?SumX			:= XMean + FPLEN
?SumXSqr			:= SumX + FPLEN
?StdX			:= SumXSqr + FPLEN
?StdPX			:= StdX + FPLEN
?MinX			:= StdPX + FPLEN
?MaxX			:= MinX + FPLEN
?MinY			:= MaxX + FPLEN
?MaxY			:= MinY + FPLEN
?YMean			:= MaxY + FPLEN
?SumY			:= YMean + FPLEN
?SumYSqr			:= SumY + FPLEN
?StdY			:= SumYSqr + FPLEN
?StdPY			:= StdY + FPLEN
?SumXY			:= StdPY + FPLEN
?Corr			:= SumXY + FPLEN
?MedX			:= Corr + FPLEN
?Q1			:= MedX + FPLEN
?Q3			:= Q1 + FPLEN
?QuadA			:= Q3 + FPLEN
?QuadB			:= QuadA + FPLEN
?QuadC			:= QuadB + FPLEN
?CubeD			:= QuadC + FPLEN
?QuartE			:= CubeD + FPLEN
?MedX1			:= QuartE + FPLEN
?MedX2			:= MedX1 + FPLEN
?MedX3			:= MedX2 + FPLEN
?MedY1			:= MedX3 + FPLEN
?MedY2			:= MedY1 + FPLEN
?MedY3			:= MedY2 + FPLEN
?PStat			:= MedY3 + (2*FPLEN)
?ZStat			:= PStat + FPLEN
?TStat			:= ZStat + FPLEN
?ChiStat			:= TStat + FPLEN
?FStat			:= ChiStat + FPLEN
?DF			:= FStat + FPLEN
?Phat			:= DF + FPLEN
?Phat1			:= Phat + FPLEN
?Phat2			:= Phat1 + FPLEN
?MeanX1			:= Phat2 + FPLEN
?StdX1			:= MeanX1 + FPLEN
?StatN1			:= StdX1 + FPLEN
?MeanX2			:= StatN1 + FPLEN
?StdX2			:= MeanX2 + FPLEN
?StatN2			:= StdX2 + FPLEN
?StdXP2			:= StatN2 + FPLEN
?SLower			:= StdXP2 + FPLEN
?SUpper			:= SLower + FPLEN
?SStat			:= SUpper + FPLEN
?anovaf_vars		:= SStat + FPLEN
?F_DF			:= anovaf_vars
?F_SS			:= F_DF + FPLEN
?F_MS			:= F_SS + FPLEN
?E_DF			:= F_MS + FPLEN
?E_SS			:= E_DF + FPLEN
?E_MS			:= E_SS + FPLEN

;System Flags
;----------------------------------------------------------------------
?ioDelFlag		:= 0h
?inDelete		:= 0		;1 = DELETE SCREEN

?trigFlags		:= 0h		;Trigonometry mode settings
?trigDeg			:= 2		;1 = degrees, 0=radians

?kbdFlags		:= 0h		;Keyboard scan
?kbdSCR			:= 3		;1=scan code ready
?kbdKeyPress		:= 4		;1=key has been pressed

?doneFlags		:= 0h		;display "Done"
?donePrgm		:= 5		;1=display "Done" after prgm
;----------------------------------------------------------------------
?editFlags		:= 1h
?editOpen		:= 2		;1=edit buffer is open

?ansFlags		:= 1
?AnsScroll		:= 3		;1=answer can scroll, seems must be reset in order to move about edit buffer

?monFlags		:= 1h	 	;monitor flags
?monAbandon		:= 4		;1=don't start any long process in put away (#715)
;----------------------------------------------------------------------
?plotFlags		:= 2h		;plot generation flags
?plotLoc 		:= 1		;0=bkup and display, 1=display only
?plotDisp		:= 2		;1=plot is in display, 0=text in display, this also indicates whether graph is being shown or not

?grfModeFlags		:= 2h		;graph mode settings
?grfFuncM		:= 4		;1=function graph
?grfPolarM		:= 5		;1=polar graph
?grfParamM		:= 6		;1=parametric graph
?grfRecurM		:= 7		;1=RECURSION graph
;----------------------------------------------------------------------
?graphFlags		:= 3h
?graphDraw		:= 0		;0=graph is valid, 1=redraw graph(dirty)
?graphCursor		:= 2
;----------------------------------------------------------------------
?grfDBFlags		:= 4h
?grfDot			:= 0		;0=line, 1=dot
?grfSimul		:= 1		;0=sequential, 1=simultaneous
?grfGrid 		:= 2		;0=no grid, 1=grid
?grfPolar		:= 3		;0=rectangular, 1=polar coordinates
?grfNoCoord		:= 4		;0=display coordinates, 1=off
?grfNoAxis		:= 5		;0=axis, 1=no axis
?grfLabel		:= 6		;0=off, 1=axis label
;----------------------------------------------------------------------
?textFlags		:= 5h		;Text output flags
?textEraseBelow		:= 1		;1=erase line below small char
?textScrolled		:= 2		;1=screen scrolled
?textInverse		:= 3		;1=display inverse bit-map
?textInsMode		:= 4		;0=overstrike, 1=insert mode
;----------------------------------------------------------------------
?ParsFlag		:= 6h		;PARSER flags
?listOpen		:= 5		; {...}
?matrixOpen1		:= 6		; [[...]]
?matrixOpen2		:= 7		; [...]
;----------------------------------------------------------------------
?ParsFlag2		:= 7h		;PARSER flags
?numOP1			:= 0		;1=RESULT IN OP1, 0=NO RESULT
;----------------------------------------------------------------------
?newDispF		:= 8h		;Derivative mode flags
?preClrForMode		:= 0		;1=HELP BLINK ON MODE SCREEN
?allowProgTokens		:= 1		;1=allow programming tokens to be parsed in BASIC programs
?progExecuting		:= 1

?apdFlags		:= 8h		;Automatic power-down
?apdAble 		:= 2		;1=APD enabled
?apdRunning		:= 3		;1=APD clock running
?apdWarmStart		:= 4		;1=calculator is turning on from APD or power loss
;----------------------------------------------------------------------
?web_err_mask		:= 60h
;----------------------------------------------------------------------
?onFlags 		:= 9h		;on key flags
?parseInput		:= 1		;1=parse input when done
?onRunning		:= 3		;1=calculator is running
?onInterrupt		:= 4		;1=on key interrupt request

?statFlags		:= 9h		;statistics flags
;unknown		equ 5		;unknown
?statsValid		:= 6		;1=stats are valid
;unknown		equ 7		;unknown
;----------------------------------------------------------------------
?fmtFlags		:= 0Ah		;numeric format flags
?fmtExponent		:= 0	 	;1=show exponent, 0=no exponent
?fmtEng			:= 1	 	;1=engineering notion, 0=scientific

?numMode			:= 0Ah
?fmtReal			:= 5
?fmtRect			:= 6
?fmtPolar		:= 7

?realMode		:= 5
?rectMode		:= 6
?polarMode		:= 7

?fmtBaseMask		:=  00011100b	; mask to base flags
?fmtBaseShift		:=  2		; offset to base flags
;----------------------------------------------------------------------
?fmtOverride		:= 0Bh		;copy of fmtFlags with conversion override
;----------------------------------------------------------------------
?fmtEditFlags		:= 0Ch		;numeric editing flags
?fmtEdit			:= 0		;1=format number for editing

?curFlags		:= 0Ch		;Cursor
?curAble 		:= 2		;1=cursor flash is enabled
?curOn			:= 3		;1=cursor is showing
?curLock 		:= 4		;1=cursor is locked off

?cmdFlags		:= 0Ch		;command editor flags
?cmdVirgin		:= 5		;1=nothing has been typed in cmd bfr
?cmdExec			:= 6           ;1=need to execute a command
;----------------------------------------------------------------------
?appFlags		:= 0Dh		;application flags
?appWantIntrpt		:= 0		;1=want ON key interrupts
?appTextSave		:= 1		;1=save characters in textShadow
?appAutoScroll		:= 2		;1=auto-scroll text on last line
?appMenus		:= 3		;1=process keys that bring up menus, 0=check Lock menu flag
?appLockMenus		:= 4		;1=ignore menu keys, 0=switch to home screen and bring up menu
?appCurGraphic		:= 5		;1=graphic cursor
?appCurWord		:= 6		;1=text cursor covers entire word
?appExit 		:= 7		;1=application handles [EXIT] key itself

?appWantIntrptF		:= 1 shl appWantIntrpt
?appTextSaveF		:= 1 shl appTextSave
?appAutoScrollF		:= 1 shl appAutoScroll
?appMenusF		:= 1 shl appMenus
?appLockMenusF		:= 1 shl appLockMenus
?appCurGraphicF		:= 1 shl appCurGraphic
?appCurWordF		:= 1 shl appCurWord
?appExitF		:= 1 shl appExit
;----------------------------------------------------------------------
?rclFlag			:= 0Eh		;OS recall queue flags
?enableQueue		:= 7		;1 = enable recall queue
;----------------------------------------------------------------------
?seqFlags		:= 0Fh		;Sequential Graph flags
?webMode			:= 0		;0 = NORMAL SEQ MODE, 1 = WEB MODE
?webVert			:= 1
?sequv			:= 2		;U vs V
?seqvw			:= 3		;V vs W
?sequw			:= 4		;U vs W
;----------------------------------------------------------------------
?promptFlags		:= 11h		;prompt line flags
?promptEdit		:= 0		;1=editing in prompt buffer
;unknown		equ 7		;unknown
;----------------------------------------------------------------------
?indicFlags		:= 12h		;Indicator flags
?indicRun		:= 0		;1=run indicator ON
?indicInUse		:= 1		;indicator save area in use=1, free=0 ;resetting will disable 2nd while in _getkey

?shiftFlags		:= 12h		;[2nd] and [ALPHA] flags
?shift2nd		:= 3		;1=[2nd] has been pressed
?shiftAlpha		:= 4		;1=[ALPHA] has been pressed
?shiftLwrAlph		:= 5		;1=lower case, 0=upper case
?shiftALock		:= 6		;1=alpha lock has been pressed
?shiftKeepAlph		:= 7		;1=cannot cancel alpha shift
;----------------------------------------------------------------------
?tblFlags		:= 13h		;table flags.
?autoFill		:= 4		;1=prompt, 0=fillAuto
?autoCalc		:= 5		;1=prompt, 0=CalcAuto
?reTable			:= 6		;0=table is okay, 1=must recompute table.
;----------------------------------------------------------------------
?sGrFlags		:= 14h
?grfSplit		:= 0		;1=Split Graph, 0=Normal
?vertSplit		:= 1		;1=Vertical (left-right) Split
?grfSChanged		:= 2		;1=Graph just changed Split <-> normal
?grfSplitOverride	:= 3		;1 = ignore graph split flag if set
?write_on_graph		:= 4		;1 = TEXT OR EQU WRITING TO GRAPH SCREEN
?g_style_active		:= 5		;1 = GRAPH STYLES ARE ENABLED, USE THEM
?cmp_mod_box		:= 6		;1 = DOING MOD BOX PLOT COMPUTATION
?textWrite		:= 7
;----------------------------------------------------------------------
?newIndicFlags		:= 15h
?extraIndic		:= 0
?saIndic			:= 1
;3 has something to do with stat/list editor
;----------------------------------------------------------------------
?interruptFlags		:= 16h
?secondTimerEnabled	:= 0		;1 = second hardware timer enabled
;----------------------------------------------------------------------
?smartFlags		:= 17h
?smarter_mask		:= 3
?smarter_test		:= 1
?smartGraph		:= 0
?smartGraph_inv		:= 1
;----------------------------------------------------------------------
?traceFlags		:= 18h
?grfExpr			:= 0		;set to hide expression while tracing
;----------------------------------------------------------------------
;There is a flag 19h.
;----------------------------------------------------------------------
?statFlags2		:= 1Ah
?statDiagnosticsOn	:= 0		;1 = stat diagnostics on
?noDelStat		:= 2		;1 = don't delete stats
;----------------------------------------------------------------------
?apdFlags2		:= 1Bh
?warmStartInt		:= 6           ;1 = a warm start is occurning before the next interrupt
;----------------------------------------------------------------------
;There is a flag 1Ch (stats-related).
;----------------------------------------------------------------------
;There is a flag 1Dh.
;----------------------------------------------------------------------
;There is a flag 1Eh.
;----------------------------------------------------------------------
?varTypeMask		:= 1Fh		;is this a flag byte? yes
?varGraphRef		:= 6
;----------------------------------------------------------------------
?graphFlags2		:= 1Fh
?splitOverride		:= 3		;0 = force full screen with ParseInp, or something
;----------------------------------------------------------------------
?asm_Flag1		:= 21h		;ASM CODING
?asm_Flag2		:= 22h		;ASM CODING
?asm_Flag3		:= 23h		;NO LONGER AVAILABLE
;----------------------------------------------------------------------
?arcFlag			:= 24h
?checkBatteryLevelFirst	:= 0		;1 = check battery levels in Arc_Unarc first and throw error if low

?getSendFlg		:= 24h
?comFailed		:= 1		;1 = Get/Send Communication Failed

?selfTestFlag		:= 24h
?resetOnPowerOn		:= 2		;1 = Force RAM reset when APD disabled on next power on

?appLwrCaseFlag		:= 24h
?lwrCaseActive		:= 3
;----------------------------------------------------------------------
?contextFlags		:= 25h
?nocxPutAway		:= 5		;1 = do not call cxPutAway routine
;----------------------------------------------------------------------
?groupFlags		:= 26h		;used temporarily in Arc_Unarc
?inGroup			:= 1		;1 = IN GROUP CONTEXT
?noCompletionByte	:= 2		;1 = do not write 0FCh when calling Arc_Unarc, leave as 0FEh
?noDataWrite		:= 3		;1 = do not write data when calling Arc_Unarc, nor size bytes
?writeSizeBytesOnly	:= 5		;1 = only write size bytes when calling Arc_Unarc
;----------------------------------------------------------------------
?statusBarFlags		:= 27h
?noStatusBarMode		:= 7		; 1 = abort drawing of statusbar mode, like "TEST MODE ENABLED"
;----------------------------------------------------------------------
?APIFlg			:= 28h
?appAllowContext		:= 0           ;app wants context changes to happen

?appRunning		:= 4		;app is currently running
?appRetKeyOff		:= 7		;1 = GetKey returns kOff when [2nd]+[ON] pressed
;----------------------------------------------------------------------
?apiFlg2			:= 29h
;----------------------------------------------------------------------
?apiFlg3			:= 2Ah
;----------------------------------------------------------------------
?apiFlg4			:= 2Bh
?cellOverride		:= 1		;use cell override
?fullScrnDraw		:= 2		;DRAW INTO LAST ROW/COL OF SCREEN
;----------------------------------------------------------------------
?xapFlag0		:= 2Eh		;external app flags, do not use 0,(iy+2Eh) (used by mouse routines)
?xapFlag1		:= 2Fh
?xapFlag2		:= 30h
?xapFlag3		:= 31h
;----------------------------------------------------------------------
?fontFlags		:= 32h
?fracDrawLFont		:= 2
?fracTallLFont		:= 3
?customFont		:= 7
;----------------------------------------------------------------------
?hookflags1		:= 33h		;also scriptFlag, rclFlag2, backGroundLink
?alt_On			:= 0		;run ONSCRPT at startup
?alt_Off			:= 1		;run OFFSCRPT at shutdown
?useRclQueueEnd		:= 2		;1 = external mode
?ignoreBPLink		:= 3		;1 = override flag for link activity hook
?bPLinkOn		:= 4		;1 = link activity hook active
?enableKeyEcho		:= 5		;1 = sends keypresses back to connected calc as remote control packets (with GetCSC vs. GetKey codes...really dumb, TI)
?noTempDelete		:= 6		;1 = do not delete temporary programs at homescreen
;----------------------------------------------------------------------
?hookflags2		:= 34h		;also sysHookFlg
?getCSCHookActive	:= 0		;1 = GetCSC hook active
?libraryHookActive	:= 1		;1 = library hook active
?noHookActive		:= 2		;1 = same as 0; never used by OS
?homescreenHookActive	:= 4		;1 = homescreen hook active
?rawKeyHookActive	:= 5		;1 = raw key hook active
?catalog2HookActive	:= 6		;1 = catalog 2 hook active
?cursorHookActive	:= 7		;1 = cursor hook active
;----------------------------------------------------------------------
?hookflags3		:= 35h		;also sysHookFlg1
?tokenHookActive		:= 0		;1 = token hook active
?localizeHookActive	:= 1		;1 = localize hook active
?windowHookActive	:= 2		;1 = window hook active
?graphHookActive		:= 3		;1 = graph hook active
?yEquHookActive		:= 4		;1 = Y= hook active
?fontHookActive		:= 5		;1 = font hook active
?regraphHookActive	:= 6		;1 = regraph hook active
?drawingHookActive	:= 7		;1 = drawing hook active
;----------------------------------------------------------------------
?hookflags4		:= 36h		;also sysHookFlag2
?traceHookActive		:= 0		;1 = trace hook active
?parserHookActive	:= 1		;1 = parser hook active
?appChangeHookActive	:= 2		;1 = app change hook active
?catalog1HookActive	:= 3		;1 = catalog 1 hook active
?helpHookActive		:= 4		;1 = help hook active
?cxRedispHookActive	:= 5		;1 = cxRedisp hook active
?menuHookActive		:= 6		;1 = menu hook active
?silentLinkHookActive	:= 7		;1 = silent link hook active
;----------------------------------------------------------------------
;hookflags2Override	equ 37h		;set corresponding bit to kill iy+35h hook when executing app
;----------------------------------------------------------------------
;hookflags3Override	equ 38h		;set corresponding bit to kill iy+36h hook when executing app
;----------------------------------------------------------------------
;hookflags4Override	equ 39h		;set corresponding bit to kill iy+37h hook when executing app
;----------------------------------------------------------------------
?hookflags5		:= 3Ah
?usbActivityHookActive	:= 0		;1 = USB activity hook active
;----------------------------------------------------------------------
?plotFlag3		:= 3Ch
?bufferOnly		:= 0
?useFastCirc		:= 4
;----------------------------------------------------------------------
?dBKeyFlags		:= 3Dh
?keyDefaultsF		:= 6		;1 = GetKey returns extended keycodes with TI-Keyboard
;----------------------------------------------------------------------
?silentLinkFlags		:= 3Eh
?silentLinkActive	:= 0		;1 = SE/84+ silent link is active

?extraHookFlags		:= 3Eh
?checkCatalog2HookVer	:= 3		;1 = check catalog 2 hook's version before executing it (and error or take other action if so)
?openLibActive		:= 4		;1 = OpenLib( was successfully called on a Flash application (ExecLib will error if zero)
;----------------------------------------------------------------------
?clockFlags		:= 3Fh
?notMDYMode		:= 0		;0 = M/D/Y format
?isYMDMode		:= 1		;1 = Y/M/D format
?is24Hour		:= 2		;1 = clock in 24 hour mode
?inAfternoon		:= 3		;1 = current time is in afternoon (PM) (I think)
?useTokensInString	:= 4		;1 = use tokens instead of characters when displaying clock as string (for getTmStr and getDtStr vs. MODE screen) (keep this reset)
?displayClock		:= 5		;1 = display clock (this is set every second, reset otherwise)
?clockOn			:= 6		;1 = clock on
;----------------------------------------------------------------------
?mathprintFlags		:= 44h
?mathprintEnabled	:= 5		;1 = use mathprint styling
;----------------------------------------------------------------------
?InitialBootMenuFlags	:= 45h
?dispinitialBootMenu	:= 4		; 1 = don't display the initial boot menu
;----------------------------------------------------------------------
?backlightFlags		:= 46h
?restoreBrightness	:= 0		;1 = restore lcd brightness when needed
;----------------------------------------------------------------------
?grFlags			:= 4Ah
?drawGrLbls		:= 0		;1 = don't draw Graph Labels (this is usually reset anyway)

?putMapFlags		:= 4Ah
?usePixelShadow2		:= 3		;1 = use pixelshadow2, not pixelshadow
?putMapUseColor		:= 4		;1 = use custom color
;----------------------------------------------------------------------
?graphDispFlags		:= 4Bh
?backgroundValid		:= 4		;1 = items in graph background are still valid
;----------------------------------------------------------------------


end namespace
