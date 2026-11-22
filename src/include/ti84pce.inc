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
.equ ti.lcdWidth,               320
.equ ti.lcdHeight,              240

; System Calls
; Jump Table located at 020104h
;--------------------------------
.equ ti.OSSize,                    0x0020104 ; not a routine; jump location is end of OS
.equ ti.BootOS,                    0x0020108
.equ ti.InterruptHandler,          0x002010C
.equ ti.Rst10Handler,              0x0020110
.equ ti.Rst18Handler,              0x0020114
.equ ti.Rst20Handler,              0x0020118
.equ ti.Rst28Handler,              0x002011C
.equ ti.Rst30Handler,              0x0020120
;                          equ     0020124h
;                          equ     0020128h
.equ ti.JErrorNo,                  0x002012C
.equ ti.CallFontHook,              0x0020130
.equ ti.CallLocalizeHook,          0x0020134
.equ ti.LoadHLInd_s,               0x0020138
.equ ti.CpHLDE,                    0x002013C
.equ ti.DivHLBy10_s,               0x0020140
.equ ti.DivHLByA_s,                0x0020144
.equ ti.KbdScan,                   0x0020148
.equ ti.GetCSC,                    0x002014C
.equ ti.CoorMon,                   0x0020150
.equ ti.Mon,                       0x0020154
.equ ti.MonForceKey,               0x0020158
.equ ti.SendKPress,                0x002015C
.equ ti.JForceCmdNoChar,           0x0020160
.equ ti.JForceCmd,                 0x0020164
.equ ti.SysErrHandler,             0x0020168
.equ ti.NewContext,                0x002016C
.equ ti.NewContext0,               0x0020170
.equ ti.PPutawayPrompt,            0x0020174
.equ ti.PPutAway,                  0x0020178
.equ ti.PutAway,                   0x002017C
.equ ti.SizeWind,                  0x0020180
.equ ti.ErrorEP,                   0x0020184
.equ ti.CallMain,                  0x0020188
.equ ti.MonErrHand,                0x002018C
.equ ti.AppInit,                   0x0020190
.equ ti.Initialize,                0x0020194
.equ ti.Min,                       0x0020198
.equ ti.Max,                       0x002019C
.equ ti.AbsO1PAbsO2,               0x00201A0
.equ ti.Intgr,                     0x00201A4
.equ ti.TRunc,                     0x00201A8
.equ ti.InvSub,                    0x00201AC
.equ ti.Times2,                    0x00201B0
.equ ti.Plus1,                     0x00201B4
.equ ti.Minus1,                    0x00201B8
.equ ti.FPSub,                     0x00201BC
.equ ti.FPAdd,                     0x00201C0
.equ ti.DToR,                      0x00201C4
.equ ti.RToD,                      0x00201C8
.equ ti.Cube,                      0x00201CC
.equ ti.TimesPT5,                  0x00201D0
.equ ti.FPSquare,                  0x00201D4
.equ ti.FPMult,                    0x00201D8
.equ ti.LJRnd,                     0x00201DC
.equ ti.InvOP1Sc,                  0x00201E0
.equ ti.InvOP1S,                   0x00201E4
.equ ti.InvOP2S,                   0x00201E8
.equ ti.Frac,                      0x00201EC
.equ ti.FPRecip,                   0x00201F0
.equ ti.FPDiv,                     0x00201F4
.equ ti.SqRoot,                    0x00201F8
.equ ti.RndGuard,                  0x00201FC
.equ ti.Rnfx,                      0x0020200
.equ ti.Int,                       0x0020204
.equ ti.Round,                     0x0020208
.equ ti.LnX,                       0x002020C
.equ ti.LogX,                      0x0020210
.equ ti.LJNoRnd,                   0x0020214
.equ ti.EToX,                      0x0020218
.equ ti.TenX,                      0x002021C
.equ ti.SinCosRad,                 0x0020220
.equ ti.Sin,                       0x0020224
.equ ti.Cos,                       0x0020228
.equ ti.Tan,                       0x002022C
.equ ti.SinhCosh,                  0x0020230
.equ ti.Tanh,                      0x0020234
.equ ti.Cosh,                      0x0020238
.equ ti.Sinh,                      0x002023C
.equ ti.ACosRad,                   0x0020240
.equ ti.ATanRad,                   0x0020244
.equ ti.ATan2Rad,                  0x0020248
.equ ti.ASinRad,                   0x002024C
.equ ti.ACos,                      0x0020250
.equ ti.ATan,                      0x0020254
.equ ti.ASin,                      0x0020258
.equ ti.ATan2,                     0x002025C
.equ ti.ATanh,                     0x0020260
.equ ti.ASinh,                     0x0020264
.equ ti.ACosh,                     0x0020268
.equ ti.PToR,                      0x002026C
.equ ti.RToP,                      0x0020270
.equ ti.HLTimes9,                  0x0020274
.equ ti.CkOP1Cplx,                 0x0020278
.equ ti.CkOP1Real,                 0x002027C
.equ ti.Angle,                     0x0020280
.equ ti.COP1Set0,                  0x0020284
.equ ti.Cpop4OP3,                  0x0020288
.equ ti.Mov9OP2Cp,                 0x002028C
.equ ti.AbsO1O2Cp,                 0x0020290
.equ ti.CpOP1OP2,                  0x0020294
.equ ti.OP3ToOP4,                  0x0020298
.equ ti.OP1ToOP4,                  0x002029C
.equ ti.OP2ToOP4,                  0x00202A0
.equ ti.OP4ToOP2,                  0x00202A4
.equ ti.OP3ToOP2,                  0x00202A8
.equ ti.OP1ToOP3,                  0x00202AC
.equ ti.OP5ToOP2,                  0x00202B0
.equ ti.OP5ToOP6,                  0x00202B4
.equ ti.OP5ToOP4,                  0x00202B8
.equ ti.OP1ToOP2,                  0x00202BC
.equ ti.OP6ToOP2,                  0x00202C0
.equ ti.OP6ToOP1,                  0x00202C4
.equ ti.OP4ToOP1,                  0x00202C8
.equ ti.OP5ToOP1,                  0x00202CC
.equ ti.OP3ToOP1,                  0x00202D0
.equ ti.OP6ToOP5,                  0x00202D4
.equ ti.OP4ToOP5,                  0x00202D8
.equ ti.OP3ToOP5,                  0x00202DC
.equ ti.OP2ToOP5,                  0x00202E0
.equ ti.OP2ToOP6,                  0x00202E4
.equ ti.OP1ToOP6,                  0x00202E8
.equ ti.OP1ToOP5,                  0x00202EC
.equ ti.OP2ToOP1,                  0x00202F0
.equ ti.Mov11b,                    0x00202F4
.equ ti.Mov10b,                    0x00202F8
.equ ti.Mov9b,                     0x00202FC
.equ ti.Mov9b_,                    0x0020300
.equ ti.Mov8b,                     0x0020304
.equ ti.Mov7b,                     0x0020308
.equ ti.Mov7b_,                    0x002030C
.equ ti.OP2ToOP3,                  0x0020310
.equ ti.OP4ToOP3,                  0x0020314
.equ ti.OP5ToOP3,                  0x0020318
.equ ti.OP4ToOP6,                  0x002031C
.equ ti.Mov9ToOP1,                 0x0020320
.equ ti.Mov9OP1OP2,                0x0020324
.equ ti.Mov9ToOP2,                 0x0020328
.equ ti.MovFrOP1,                  0x002032C
.equ ti.OP4Set1,                   0x0020330
.equ ti.OP3Set1,                   0x0020334
.equ ti.OP2Set8,                   0x0020338
.equ ti.OP2Set5,                   0x002033C
.equ ti.OP2SetA,                   0x0020340
.equ ti.OP2Set4,                   0x0020344
.equ ti.OP2Set3,                   0x0020348
.equ ti.OP1Set1,                   0x002034C
.equ ti.OP1Set4,                   0x0020350
.equ ti.OP1Set3,                   0x0020354
.equ ti.OP3Set2,                   0x0020358
.equ ti.OP1Set2,                   0x002035C
.equ ti.OP2Set2,                   0x0020360
.equ ti.OP2Set1,                   0x0020364
.equ ti.Zero16D,                   0x0020368
.equ ti.OP5Set0,                   0x002036C
.equ ti.OP4Set0,                   0x0020370
.equ ti.OP3Set0,                   0x0020374
.equ ti.OP2Set0,                   0x0020378
.equ ti.OP1Set0,                   0x002037C
.equ ti.SetNum0,                   0x0020380
.equ ti.ZeroOP1,                   0x0020384
.equ ti.ZeroOP2,                   0x0020388
.equ ti.ZeroOP3,                   0x002038C
.equ ti.ZeroOP,                    0x0020390
.equ ti.ClrLP,                     0x0020394
.equ ti.ShrACC,                    0x0020398
.equ ti.ShlACC,                    0x002039C
.equ ti.Shr18,                     0x00203A0
.equ ti.Shr18a,                    0x00203A4
.equ ti.Shr16,                     0x00203A8
.equ ti.Shr14,                     0x00203AC
.equ ti.Shl16,                     0x00203B0
.equ ti.Shl14,                     0x00203B4
.equ ti.Srdo1,                     0x00203B8
.equ ti.ShrdRnd,                   0x00203BC
.equ ti.MantPa,                    0x00203C0
.equ ti.AddPrOP,                   0x00203C4
.equ ti.AddPrOPlP,                 0x00203C8
;                          equ     00203CCh
;                          equ     00203D0h
.equ ti.Sub16d,                    0x00203D4
.equ ti.Sub14d,                    0x00203D8
.equ ti.OP2ExOP6,                  0x00203DC
.equ ti.OP5ExOP6,                  0x00203E0
.equ ti.OP1ExOP5,                  0x00203E4
.equ ti.OP1ExOP6,                  0x00203E8
.equ ti.OP2ExOP4,                  0x00203EC
.equ ti.OP2ExOP5,                  0x00203F0
.equ ti.OP1ExOP3,                  0x00203F4
.equ ti.OP1ExOP4,                  0x00203F8
.equ ti.OP1ExOP2,                  0x00203FC
.equ ti.ExLP,                      0x0020400
.equ ti.CkOP10,                    0x0020404
.equ ti.CkOP1FP0,                  0x0020408
.equ ti.CkOP2FP0,                  0x002040C
.equ ti.PosNo0Int,                 0x0020410
.equ ti.CkPosInt,                  0x0020414
.equ ti.CkInt,                     0x0020418
.equ ti.CkOdd,                     0x002041C
.equ ti.CkOP1EX,                   0x0020420
.equ ti.GetCon1,                   0x0020424
.equ ti.GetCon,                    0x0020428
.equ ti.PiDiv2,                    0x002042C
.equ ti.PiDiv4,                    0x0020430
.equ ti.TwoPi,                     0x0020434
.equ ti.PiCon,                     0x0020438
.equ ti.ExpToHex,                  0x002043C
.equ ti.OP1ExpToDec,               0x0020440
.equ ti.CkOP2Pos,                  0x0020444
.equ ti.CkOP1Pos,                  0x0020448
.equ ti.ClrOP2S,                   0x002044C
.equ ti.ClrOP1S,                   0x0020450
.equ ti.FDiv100,                   0x0020454
.equ ti.FDiv10,                    0x0020458
.equ ti.DecO1Exp,                  0x002045C
.equ ti.IncO1exp,                  0x0020460
.equ ti.IncExp,                    0x0020464
.equ ti.CkValidNum,                0x0020468
.equ ti.GetExp,                    0x002046C
.equ ti.HtimesL,                   0x0020470
.equ ti.EOP1NotReal,               0x0020474
.equ ti.ThetaName,                 0x0020478
.equ ti.RName,                     0x002047C
.equ ti.RegEqName,                 0x0020480
.equ ti.RecurNName,                0x0020484
.equ ti.XName,                     0x0020488
.equ ti.YName,                     0x002048C
.equ ti.TName,                     0x0020490
.equ ti.RealName,                  0x0020494
.equ ti.SetEStoFPS,                0x0020498
.equ ti.ChkTempDirt,               0x002049C
.equ ti.OP1ExOP2Exp,               0x00204A0
.equ ti.OP1ExpMinusE,              0x00204A4
.equ ti.ChkErrBreak,               0x00204A8
.equ ti.Isa2ByteTok,               0x00204AC
.equ ti.GetLastEntry,              0x00204B0
.equ ti.GetLastEntryPtr,           0x00204B4
.equ ti.RegRclrChng,               0x00204B8
.equ ti.ResetWinTop,               0x00204BC
.equ ti.IsO1NonTLstOrProg,         0x00204C0
.equ ti.IsO1NonTempLst,            0x00204C4
.equ ti.Is_A_LstOrCLst,            0x00204C8
.equ ti.Chk_HL_999,                0x00204CC
.equ ti.Equ_Or_NewEqu,             0x00204D0
.equ ti.Errd_OP1NotPos,            0x00204D4
.equ ti.Errd_OP1Not_R,             0x00204D8
.equ ti.Errd_OP1NotPosInt,         0x00204DC
.equ ti.Errd_OP1_le_0,             0x00204E0
.equ ti.Errd_OP1_0,                0x00204E4
.equ ti.ChkFindSym_Get_Size,       0x00204E8
.equ ti.Sto_StatVar,               0x00204EC
.equ ti.Rcl_StatVar,               0x00204F0
.equ ti.CkOP2Real,                 0x00204F4
.equ ti.Get_X_Indirect,            0x00204F8
.equ ti.MemChk,                    0x00204FC
.equ ti.CmpPrgNamLen1,             0x0020500
.equ ti.CmpPrgNamLen,              0x0020504
.equ ti.FindProgSym,               0x0020508
.equ ti.ChkFindSym,                0x002050C
.equ ti.FindSym,                   0x0020510
.equ ti.InsertMem,                 0x0020514
.equ ti.InsertMemA,                0x0020518
.equ ti.EnoughMem,                 0x002051C
.equ ti.CmpMemNeed,                0x0020520
.equ ti.CreatePVar4,               0x0020524
.equ ti.CreatePVar3,               0x0020528
.equ ti.CreateVar3,                0x002052C
.equ ti.CreateCplx,                0x0020530
.equ ti.CreateReal,                0x0020534
.equ ti.CreateTRList,              0x0020538
.equ ti.CreateRList,               0x002053C
.equ ti.CreateTCList,              0x0020540
.equ ti.CreateCList,               0x0020544
.equ ti.CreateTRMat,               0x0020548
.equ ti.CreateRMat,                0x002054C
.equ ti.CreateTStrng,              0x0020550
.equ ti.CreateStrng,               0x0020554
.equ ti.Create0Equ,                0x0020558
.equ ti.CreatetEqu,                0x002055C
.equ ti.CreateEqu,                 0x0020560
.equ ti.CreateGDB,                 0x0020564
.equ ti.CreateProg,                0x0020568
.equ ti.ChkDel,                    0x002056C
.equ ti.ChkDelA,                   0x0020570
.equ ti.AdjParser,                 0x0020574
.equ ti.AdjMath,                   0x0020578
.equ ti.AdjM7,                     0x002057C
.equ ti.DelMemA,                   0x0020580
.equ ti.Get_Form_Num,              0x0020584
.equ ti.DelVar,                    0x0020588
.equ ti.DelVarIO,                  0x002058C
.equ ti.DelMem,                    0x0020590
.equ ti.DelVar3D,                  0x0020594
.equ ti.DelVar3C,                  0x0020598
.equ ti.DelVar3DC,                 0x002059C
.equ ti.Sym_Prog_non_t_Lst,        0x00205A0
.equ ti.AdjSymPtrs,                0x00205A4
.equ ti.DataSizeA,                 0x00205A8
.equ ti.DataSize,                  0x00205AC
.equ ti.PopMCplxO1,                0x00205B0
.equ ti.PopMCplx,                  0x00205B4
.equ ti.MovCplx,                   0x00205B8
.equ ti.PopOP5,                    0x00205BC
.equ ti.PopOP3,                    0x00205C0
.equ ti.PopOP1,                    0x00205C4
.equ ti.PopRealO6,                 0x00205C8
.equ ti.PopRealO5,                 0x00205CC
.equ ti.PopRealO4,                 0x00205D0
.equ ti.PopRealO3,                 0x00205D4
.equ ti.PopRealO2,                 0x00205D8
.equ ti.PopRealO1,                 0x00205DC
.equ ti.PopReal,                   0x00205E0
.equ ti.FPopCplx,                  0x00205E4
.equ ti.FPopReal,                  0x00205E8
.equ ti.FPopFPS,                   0x00205EC
.equ ti.DeallocFPS,                0x00205F0
.equ ti.DeallocFPS1,               0x00205F4
.equ ti.AllocFPS,                  0x00205F8
.equ ti.AllocFPS1,                 0x00205FC
.equ ti.PushRealO6,                0x0020600
.equ ti.PushRealO5,                0x0020604
.equ ti.PushRealO4,                0x0020608
.equ ti.PushRealO3,                0x002060C
.equ ti.PushRealO2,                0x0020610
.equ ti.PushRealO1,                0x0020614
.equ ti.PushReal,                  0x0020618
.equ ti.PushOP5,                   0x002061C
.equ ti.PushOP3,                   0x0020620
.equ ti.PushMCplxO3,               0x0020624
.equ ti.PushOP1,                   0x0020628
.equ ti.PushMCplxO1,               0x002062C
.equ ti.PushMCplx,                 0x0020630
.equ ti.ExMCplxO1,                 0x0020634
.equ ti.Exch9,                     0x0020638
.equ ti.CpyTo1FPS11,               0x002063C
.equ ti.CpyTo2FPS5,                0x0020640
.equ ti.CpyTo1FPS5,                0x0020644
.equ ti.CpyTo2FPS6,                0x0020648
.equ ti.CpyTo1FPS6,                0x002064C
.equ ti.CpyTo2FPS7,                0x0020650
.equ ti.CpyTo1FPS7,                0x0020654
.equ ti.CpyTo1FPS8,                0x0020658
.equ ti.CpyTo2FPS8,                0x002065C
.equ ti.CpyTo1FPS10,               0x0020660
.equ ti.CpyTo1FPS9,                0x0020664
.equ ti.CpyTo2FPS4,                0x0020668
.equ ti.CpyTo6FPS3,                0x002066C
.equ ti.CpyTo6FPS2,                0x0020670
.equ ti.CpyTo2FPS3,                0x0020674
.equ ti.Cpycto1FPS3,               0x0020678
.equ ti.CpyTo1FPS3,                0x002067C
.equ ti.CpyFPS3,                   0x0020680
.equ ti.CpyTo1FPS4,                0x0020684
.equ ti.CpyTo3FPS2,                0x0020688
.equ ti.CpyTo5FPST,                0x002068C
.equ ti.CpyTo6FPST,                0x0020690
.equ ti.CpyTo4FPST,                0x0020694
.equ ti.CpyTo3FPST,                0x0020698
.equ ti.CpyTo2FPST,                0x002069C
.equ ti.CpyTo1FPST,                0x00206A0
.equ ti.CpyFPST,                   0x00206A4
.equ ti.CpyStack,                  0x00206A8
.equ ti.CpyTo3FPS1,                0x00206AC
.equ ti.CpyTo2FPS1,                0x00206B0
.equ ti.CpyTo1FPS1,                0x00206B4
.equ ti.CpyFPS1,                   0x00206B8
.equ ti.CpyTo2FPS2,                0x00206BC
.equ ti.CpyTo1FPS2,                0x00206C0
.equ ti.CpyFPS2,                   0x00206C4
.equ ti.CpyO3ToFPST,               0x00206C8
.equ ti.CpyO2ToFPST,               0x00206CC
.equ ti.CpyO6ToFPST,               0x00206D0
.equ ti.CpyO1ToFPST,               0x00206D4
.equ ti.CpyToFPST,                 0x00206D8
.equ ti.CpyToStack,                0x00206DC
.equ ti.CpyO3ToFPS1,               0x00206E0
.equ ti.CpyO5ToFPS1,               0x00206E4
.equ ti.CpyO2ToFPS1,               0x00206E8
.equ ti.CpyO1ToFPS1,               0x00206EC
.equ ti.CpyToFPS1,                 0x00206F0
.equ ti.CpyO2ToFPS2,               0x00206F4
.equ ti.CpyO3ToFPS2,               0x00206F8
.equ ti.CpyO6ToFPS2,               0x00206FC
.equ ti.CpyO1ToFPS2,               0x0020700
.equ ti.CpyToFPS2,                 0x0020704
.equ ti.CpyO5ToFPS3,               0x0020708
.equ ti.CpyO2ToFPS3,               0x002070C
.equ ti.CpyO1ToFPS3,               0x0020710
.equ ti.CpyToFPS3,                 0x0020714
.equ ti.CpyO1ToFPS6,               0x0020718
.equ ti.CpyO1ToFPS7,               0x002071C
.equ ti.CpyO1ToFPS5,               0x0020720
.equ ti.CpyO2ToFPS4,               0x0020724
.equ ti.CpyO1ToFPS4,               0x0020728
.equ ti.ErrNotEnoughMem,           0x002072C
.equ ti.FPSMinus9,                 0x0020730
.equ ti.HLMinus9,                  0x0020734
.equ ti.ErrOverflow,               0x0020738
.equ ti.ErrDivBy0,                 0x002073C
.equ ti.ErrSingularMat,            0x0020740
.equ ti.ErrDomain,                 0x0020744
.equ ti.ErrIncrement,              0x0020748
.equ ti.ErrNon_Real,               0x002074C
.equ ti.ErrSyntax,                 0x0020750
.equ ti.ErrDataType,               0x0020754
.equ ti.ErrArgument,               0x0020758
.equ ti.ErrDimMismatch,            0x002075C
.equ ti.ErrDimension,              0x0020760
.equ ti.ErrUndefined,              0x0020764
.equ ti.ErrMemory,                 0x0020768
.equ ti.ErrInvalid,                0x002076C
.equ ti.ErrBreak,                  0x0020770
.equ ti.ErrStat,                   0x0020774
.equ ti.ErrSignChange,             0x0020778
.equ ti.ErrIterations,             0x002077C
.equ ti.ErrBadGuess,               0x0020780
.equ ti.ErrTolTooSmall,            0x0020784
.equ ti.ErrStatPlot,               0x0020788
.equ ti.ErrLinkXmit,               0x002078C
.equ ti.JError,                    0x0020790
.equ ti.NoErrorEntry,              0x0020794
.equ ti.PushErrorHandler,          0x0020798
.equ ti.PopErrorHandler,           0x002079C
.equ ti.StrCopy,                   0x00207A0
.equ ti.StrngCat,                  0x00207A4
.equ ti.IsInSet,                   0x00207A8
.equ ti.GEQNameA,                  0x00207AC
.equ ti.RecName,                   0x00207B0
.equ ti.PutMap,                    0x00207B4
.equ ti.PutC,                      0x00207B8
.equ ti.DispHL_s,                  0x00207BC
.equ ti.PutS,                      0x00207C0
.equ ti.PutPSB,                    0x00207C4
.equ ti.PutPS,                     0x00207C8
.equ ti.WPutPS,                    0x00207CC
.equ ti.PutBuf,                    0x00207D0
.equ ti.PutBuf1,                   0x00207D4
.equ ti.WPutC,                     0x00207D8
.equ ti.WPutS,                     0x00207DC
.equ ti.WPutSEOL,                  0x00207E0
.equ ti.WDispEOL,                  0x00207E4
.equ ti.WHomeUp,                   0x00207E8
.equ ti.SetNumWindow,              0x00207EC
.equ ti.NewLine,                   0x00207F0
.equ ti.MoveDown,                  0x00207F4
.equ ti.ScrollUp,                  0x00207F8
.equ ti.ShrinkWindow,              0x00207FC
.equ ti.MoveUp,                    0x0020800
.equ ti.ScrollDown,                0x0020804
.equ ti.ClrLCDFull,                0x0020808
.equ ti.ClrLCD,                    0x002080C
.equ ti.ClrScrnFull,               0x0020810
.equ ti.ClrScrn,                   0x0020814
.equ ti.ClrTxtShd,                 0x0020818
.equ ti.ClrWindow,                 0x002081C
.equ ti.EraseEOL,                  0x0020820
.equ ti.EraseEOW,                  0x0020824
.equ ti.HomeUp,                    0x0020828
.equ ti.GetCurloc,                 0x002082C
.equ ti.VPutMap,                   0x0020830
.equ ti.VPutS,                     0x0020834
.equ ti.VPutSN,                    0x0020838
.equ ti.VPutSNG,                   0x002083C
.equ ti.VPutSNT,                   0x0020840
.equ ti.RunIndicOn,                0x0020844
.equ ti.RunIndicOff,               0x0020848
.equ ti.SaveCmdShadow,             0x002084C
.equ ti.SaveShadow,                0x0020850
.equ ti.RStrShadow,                0x0020854
.equ ti.RStrPartial,               0x0020858
.equ ti.RStrCurRow,                0x002085C
.equ ti.RStrUnderMenu,             0x0020860
.equ ti.RStrbotRow,                0x0020864
.equ ti.GetKeypress,               0x0020868
.equ ti.GetTokLen,                 0x002086C
.equ ti.Get_Tok_Strng,             0x0020870
.equ ti.GetTokString,              0x0020874
.equ ti.PutBPatBuf2,               0x0020878
.equ ti.PutBPatBuf,                0x002087C
.equ ti.PutBPat,                   0x0020880
.equ ti.PutcChkScroll,             0x0020884
.equ ti.DispEOL,                   0x0020888
.equ ti.FDispEOL,                  0x002088C
.equ ti.MakeRowCmd,                0x0020890
.equ ti.ToToStrp,                  0x0020894
.equ ti.SetVarName,                0x0020898
.equ ti.DispDone,                  0x002089C
.equ ti.FinishOutput,              0x00208A0
.equ ti.CurBlink,                  0x00208A4
.equ ti.CursorOff,                 0x00208A8
.equ ti.HideCursor,                0x00208AC
.equ ti.CursorOn,                  0x00208B0
.equ ti.ShowCursor,                0x00208B4
.equ ti.KeyToString,               0x00208B8
.equ ti.PullDownChk,               0x00208BC
.equ ti.MenuCatCommon,             0x00208C0
.equ ti.LoadCurCat,                0x00208C4
.equ ti.NCIFPrgmedMode,            0x00208C8
.equ ti.LoadMenuNum,               0x00208CC
.equ ti.LoadMenuNuml,              0x00208D0
.equ ti.MenuEdKey,                 0x00208D4
.equ ti.MenCatRet,                 0x00208D8
.equ ti.NotAlphNum,                0x00208DC
.equ ti.SetMenuFlags,              0x00208E0
.equ ti.ResetSomeFlags,            0x00208E4
;                          equ     00208E8h
;                          equ     00208ECh
.equ ti.DispListName,              0x00208F0
.equ ti.DispLAlphaName,            0x00208F4
.equ ti.AbortPrgmode,              0x00208F8
.equ ti.IsFullCntx,                0x00208FC
.equ ti.AdrMRow,                   0x0020900
.equ ti.AdrmeLE,                   0x0020904
.equ ti.GetmatOP1A,                0x0020908
.equ ti.Getm1toOP1,                0x002090C
.equ ti.Getm1tOP1A,                0x0020910
.equ ti.GetMToOP1,                 0x0020914
.equ ti.PutToM1A,                  0x0020918
.equ ti.PutToMA1,                  0x002091C
.equ ti.PutToMat,                  0x0020920
.equ ti.MatELDiv,                  0x0020924
.equ ti.CMatFun,                   0x0020928
.equ ti.RowEchPoly,                0x002092C
.equ ti.RowEchelon,                0x0020930
.equ ti.AdrLELE,                   0x0020934
.equ ti.Getl1ToOP1,                0x0020938
.equ ti.Getl1TOP1A,                0x002093C
.equ ti.GetlToOP1,                 0x0020940
.equ ti.Getl1ToOP2,                0x0020944
.equ ti.Getl1TOP2A,                0x0020948
.equ ti.Getl2TOP1A,                0x002094C
.equ ti.PutTola1,                  0x0020950
.equ ti.PutToL,                    0x0020954
.equ ti.MaxMinLst,                 0x0020958
.equ ti.LLow,                      0x002095C
.equ ti.LHigh,                     0x0020960
.equ ti.LSum,                      0x0020964
.equ ti.CumSum,                    0x0020968
.equ ti.ToFrac,                    0x002096C
.equ ti.SeqSet,                    0x0020970
.equ ti.SeqSolve,                  0x0020974
.equ ti.CmpNumInit,                0x0020978
.equ ti.BinopExec,                 0x002097C
.equ ti.ExMeanL,                   0x0020980
.equ ti.Set2MVLPtrs,               0x0020984
.equ ti.SetMat1,                   0x0020988
.equ ti.CreateTLIst,               0x002098C
.equ ti.UnopExec,                  0x0020990
.equ ti.ThreeExec,                 0x0020994
.equ ti.RestoreErrNo,              0x0020998
.equ ti.FourExec,                  0x002099C
.equ ti.FiveExec,                  0x00209A0
.equ ti.CpyTo2ES1,                 0x00209A4
.equ ti.CpyTo6ES1,                 0x00209A8
.equ ti.CpyTo1ES1,                 0x00209AC
.equ ti.CpyTo3ES1,                 0x00209B0
.equ ti.CpyTo3ES2,                 0x00209B4
.equ ti.CpyTo2ES2,                 0x00209B8
.equ ti.CpyTo1ES2,                 0x00209BC
.equ ti.CpyTo2ES3,                 0x00209C0
.equ ti.CpyTo1ES3,                 0x00209C4
.equ ti.CpyTo3ES4,                 0x00209C8
.equ ti.CpyTo6ES3,                 0x00209CC
.equ ti.CpyTo2ES4,                 0x00209D0
.equ ti.CpyTo1ES4,                 0x00209D4
.equ ti.CpyTo2ES5,                 0x00209D8
.equ ti.CpyTo1ES5,                 0x00209DC
.equ ti.CpyTo4ESt,                 0x00209E0
.equ ti.CpyTo2ESt,                 0x00209E4
.equ ti.CpyTo1ESt,                 0x00209E8
.equ ti.CpyTo2ES6,                 0x00209EC
.equ ti.CpyTo1ES6,                 0x00209F0
.equ ti.CpyTo2ES7,                 0x00209F4
.equ ti.CpyTo1ES7,                 0x00209F8
.equ ti.CpyTo2ES8,                 0x00209FC
.equ ti.CpyTo1ES8,                 0x0020A00
.equ ti.CpyTo1ES9,                 0x0020A04
.equ ti.CpyTo2ES9,                 0x0020A08
.equ ti.CpyTo2ES10,                0x0020A0C
.equ ti.CpyTo1ES10,                0x0020A10
.equ ti.CpyTo2ES11,                0x0020A14
.equ ti.CpyTo1ES11,                0x0020A18
.equ ti.CpyTo2ES12,                0x0020A1C
.equ ti.CpyTo1ES12,                0x0020A20
.equ ti.CpyTo2ES13,                0x0020A24
.equ ti.CpyTo1ES13,                0x0020A28
.equ ti.CpyTo1ES14,                0x0020A2C
.equ ti.CpyTo1ES16,                0x0020A30
.equ ti.CpyTo1ES17,                0x0020A34
.equ ti.CpyTo1ES18,                0x0020A38
.equ ti.CpyTo1ES15,                0x0020A3C
.equ ti.CpyTo2ES15,                0x0020A40
.equ ti.CpyO1ToESt,                0x0020A44
.equ ti.CpyO1ToES1,                0x0020A48
.equ ti.CpyO6ToES1,                0x0020A4C
.equ ti.CpyO6ToES3,                0x0020A50
.equ ti.CpyO1ToES2,                0x0020A54
.equ ti.CpyO2ToES2,                0x0020A58
.equ ti.CpyO1ToES3,                0x0020A5C
.equ ti.CpyO1ToES4,                0x0020A60
.equ ti.CpyO1ToES5,                0x0020A64
.equ ti.CpyO1ToES6,                0x0020A68
.equ ti.CpyO1ToES7,                0x0020A6C
.equ ti.CpyO2ToES4,                0x0020A70
.equ ti.CpyO2ToES5,                0x0020A74
.equ ti.CpyO2ToES6,                0x0020A78
.equ ti.CpyO2ToES7,                0x0020A7C
.equ ti.CpyO2ToES8,                0x0020A80
.equ ti.CpyO2ToES9,                0x0020A84
.equ ti.CpyO1ToES8,                0x0020A88
.equ ti.CpyO1ToES9,                0x0020A8C
.equ ti.CpyO1ToES10,               0x0020A90
.equ ti.CpyO1ToES11,               0x0020A94
.equ ti.CpyO1ToES12,               0x0020A98
.equ ti.CpyO1ToES13,               0x0020A9C
.equ ti.CpyO1ToES14,               0x0020AA0
.equ ti.EvalF3A,                   0x0020AA4
.equ ti.GetK,                      0x0020AA8
.equ ti.SetTitle,                  0x0020AAC
.equ ti.DispVarVal,                0x0020AB0
.equ ti.RecallEd,                  0x0020AB4
.equ ti.SetUpBuffer,               0x0020AB8
.equ ti.CreateNumEditBuf,          0x0020ABC
.equ ti.CallCommon,                0x0020AC0
.equ ti.CommonKeys,                0x0020AC4
.equ ti.LeftMore,                  0x0020AC8
.equ ti.FDel,                      0x0020ACC
.equ ti.FClear,                    0x0020AD0
.equ ti.FInsDisp,                  0x0020AD4
.equ ti.FInsDispNoConv,            0x0020AD8
.equ ti.SetIndicator,              0x0020ADC
.equ ti.CloseEditBufNoR,           0x0020AE0
.equ ti.ReleaseBuffer,             0x0020AE4
.equ ti.VarNameToOP1HL,            0x0020AE8
.equ ti.NameToOP1,                 0x0020AEC
.equ ti.NumpPutAway,               0x0020AF0
.equ ti.NumReDisp,                 0x0020AF4
.equ ti.NumError02,                0x0020AF8
.equ ti.Load_Sfont,                0x0020AFC
.equ ti.Sfont_Len,                 0x0020B00
.equ ti.InitNumVec,                0x0020B04
.equ ti.SetxxOP1,                  0x0020B08
.equ ti.SetxxOP2,                  0x0020B0C
.equ ti.SetxxxxOP2,                0x0020B10
.equ ti.UCLines,                   0x0020B14
.equ ti.CLine,                     0x0020B18
.equ ti.CLines,                    0x0020B1C
.equ ti.XrootY,                    0x0020B20
.equ ti.YtoX,                      0x0020B24
.equ ti.ZmStats,                   0x0020B28
.equ ti.PointStatHelp,             0x0020B2C
.equ ti.DrawSPlot,                 0x0020B30
.equ ti.InitNewTraceP,             0x0020B34
.equ ti.SPlotCoord,                0x0020B38
.equ ti.SPlotRight,                0x0020B3C
.equ ti.SPlotLeft,                 0x0020B40
.equ ti.CmpBoxInfo,                0x0020B44
.equ ti.NextPlot,                  0x0020B48
.equ ti.PrevPlot,                  0x0020B4C
.equ ti.ClrPrevPlot,               0x0020B50
.equ ti.PutIndexList,              0x0020B54
.equ ti.GetIndexList,              0x0020B58
.equ ti.HeapSort,                  0x0020B5C
.equ ti.StoGDB2,                   0x0020B60
.equ ti.RclGDB2,                   0x0020B64
.equ ti.CircCmd,                   0x0020B68
.equ ti.GrphCirc,                  0x0020B6C
.equ ti.Mov18b,                    0x0020B70
.equ ti.DarkLine,                  0x0020B74
.equ ti.ILine,                     0x0020B78
.equ ti.IPoint,                    0x0020B7C
.equ ti.XYRndBoth,                 0x0020B80
.equ ti.XYRnd,                     0x0020B84
.equ ti.CheckTOP,                  0x0020B88
.equ ti.CheckXY,                   0x0020B8C
.equ ti.DarkPnt,                   0x0020B90
.equ ti.CPointS,                   0x0020B94
.equ ti.WToV,                      0x0020B98
.equ ti.VtoWHLDE,                  0x0020B9C
.equ ti.Xitof,                     0x0020BA0
.equ ti.YftoI,                     0x0020BA4
.equ ti.XftoI,                     0x0020BA8
.equ ti.TraceOff,                  0x0020BAC
.equ ti.GrRedisp,                  0x0020BB0
.equ ti.GDispToken,                0x0020BB4
.equ ti.GrdeCoda,                  0x0020BB8
.equ ti.LabCoor,                   0x0020BBC
.equ ti.CoorDisp,                  0x0020BC0
.equ ti.TmpEquNoSrc,               0x0020BC4
.equ ti.GrLabels,                  0x0020BC8
.equ ti.YPixSet,                   0x0020BCC
.equ ti.XPixSet,                   0x0020BD0
.equ ti.CopyRng,                   0x0020BD4
.equ ti.ValCur,                    0x0020BD8
.equ ti.GrPutAway,                 0x0020BDC
.equ ti.RstGFlags,                 0x0020BE0
.equ ti.GrReset,                   0x0020BE4
.equ ti.XYCent,                    0x0020BE8
.equ ti.ZoomXYCmd,                 0x0020BEC
.equ ti.CptDelY,                   0x0020BF0
.equ ti.CptDelX,                   0x0020BF4
.equ ti.SetFuncM,                  0x0020BF8
.equ ti.SetSeqM,                   0x0020BFC
.equ ti.SetPolM,                   0x0020C00
.equ ti.SetParM,                   0x0020C04
.equ ti.ZmInt,                     0x0020C08
.equ ti.ZmDecml,                   0x0020C0C
.equ ti.ZmPrev,                    0x0020C10
.equ ti.ZmUsr,                     0x0020C14
.equ ti.SetUZM,                    0x0020C18
.equ ti.ZmFit,                     0x0020C1C
.equ ti.ZmSquare,                  0x0020C20
.equ ti.ZmTrig,                    0x0020C24
.equ ti.SetXMinMax,                0x0020C28
.equ ti.ZooDefault,                0x0020C2C
.equ ti.GrBufCpy,                  0x0020C30
.equ ti.DrawSplitLine,             0x0020C34
;                          equ     0020C38h
;                          equ     0020C3Ch
;                          equ     0020C40h
;                          equ     0020C44h
;                          equ     0020C48h
;                          equ     0020C4Ch
;                          equ     0020C50h
;                          equ     0020C54h
.equ ti.ChkTextCurs,               0x0020C58
.equ ti.Regraph,                   0x0020C5C
.equ ti.DoRefFlags02,              0x0020C60
.equ ti.InitNSeq,                  0x0020C64
.equ ti.YRes,                      0x0020C68
.equ ti.Ceiling,                   0x0020C6C
.equ ti.PutXY,                     0x0020C70
.equ ti.PutEquNo,                  0x0020C74
.equ ti.PDspGrph,                  0x0020C78
.equ ti.HorizCmd,                  0x0020C7C
.equ ti.VertCmd,                   0x0020C80
.equ ti.LineCmd,                   0x0020C84
.equ ti.UnLineCmd,                 0x0020C88
.equ ti.PointCmd,                  0x0020C8C
.equ ti.PixelTest,                 0x0020C90
.equ ti.PixelCmd,                  0x0020C94
.equ ti.TanLnF,                    0x0020C98
.equ ti.DrawCmdInit,               0x0020C9C
.equ ti.DrawCmd,                   0x0020CA0
.equ ti.ShadeCmd,                  0x0020CA4
.equ ti.InvCmd,                    0x0020CA8
.equ ti.StatShade,                 0x0020CAC
.equ ti.DspMatTable,               0x0020CB0
.equ ti.DspLsts,                   0x0020CB4
.equ ti.CloseEditBuf,              0x0020CB8
.equ ti.ParseEditBuf,              0x0020CBC
.equ ti.PutSM,                     0x0020CC0
.equ ti.DspCurTbl,                 0x0020CC4
.equ ti.DspGrTbl,                  0x0020CC8
.equ ti.ZeroTemplate,              0x0020CCC
.equ ti.SetTblRefs,                0x0020CD0
.equ ti.DispTblBot,                0x0020CD4
.equ ti.DispTblTop,                0x0020CD8
.equ ti.DispTblBody,               0x0020CDC
.equ ti.VPutBlank,                 0x0020CE0
.equ ti.TblTrace,                  0x0020CE4
.equ ti.DispListNameY,             0x0020CE8
.equ ti.CurNameLength,             0x0020CEC
.equ ti.NameToBuf,                 0x0020CF0
.equ ti.JPromptCursor,             0x0020CF4
.equ ti.BufLeft,                   0x0020CF8
.equ ti.BufRight,                  0x0020CFC
.equ ti.BufInsert,                 0x0020D00
.equ ti.BufQueueChar,              0x0020D04
.equ ti.BufReplace,                0x0020D08
.equ ti.BufDelete,                 0x0020D0C
.equ ti.BufPeek,                   0x0020D10
.equ ti.BufPeek1,                  0x0020D14
.equ ti.BufPeek2,                  0x0020D18
.equ ti.BufPeek3,                  0x0020D1C
.equ ti.BufToBtm,                  0x0020D20
.equ ti.SetupEditEqu,              0x0020D24
.equ ti.BufToTop,                  0x0020D28
.equ ti.IsEditFull,                0x0020D2C
.equ ti.IsEditEmpty,               0x0020D30
.equ ti.IsAtTop,                   0x0020D34
.equ ti.IsAtBtm,                   0x0020D38
.equ ti.BufClear,                  0x0020D3C
.equ ti.JCursorFirst,              0x0020D40
.equ ti.JCursorLast,               0x0020D44
.equ ti.CursorLeft,                0x0020D48
.equ ti.CursorRight,               0x0020D4C
.equ ti.CursorUp,                  0x0020D50
.equ ti.CursorDown,                0x0020D54
.equ ti.CursorToOffset,            0x0020D58
.equ ti.InsDisp,                   0x0020D5C
.equ ti.FDispBOL1,                 0x0020D60
.equ ti.FDispBOL,                  0x0020D64
.equ ti.DispEOW,                   0x0020D68
.equ ti.DispHead,                  0x0020D6C
.equ ti.DispTail,                  0x0020D70
.equ ti.PutTokString,              0x0020D74
.equ ti.SetUpEditCmd,              0x0020D78
.equ ti.SetEmptyeditEqu,           0x0020D7C
.equ ti.SetEmptyEditPtr,           0x0020D80
.equ ti.CloseEditEqu,              0x0020D84
.equ ti.GetPrevTok,                0x0020D88
.equ ti.GetKey,                    0x0020D8C
.equ ti.CanIndic,                  0x0020D90
.equ ti.DFMin,                     0x0020D94
.equ ti.FormDisp,                  0x0020D98
.equ ti.FormMatrix,                0x0020D9C
.equ ti.WScrollLeft,               0x0020DA0
.equ ti.WScrollUp,                 0x0020DA4
.equ ti.WScrollDown,               0x0020DA8
.equ ti.WScrollRight,              0x0020DAC
.equ ti.FormEReal,                 0x0020DB0
.equ ti.FormERealTok,              0x0020DB4
.equ ti.FormDCplx,                 0x0020DB8
.equ ti.FormReal,                  0x0020DBC
.equ ti.SetWinAbove,               0x0020DC0
.equ ti.DisarmScroll,              0x0020DC4
.equ ti.MinToEdit,                 0x0020DC8
.equ ti.RclVarToEdit,              0x0020DCC
.equ ti.RclVarToEditPtr,           0x0020DD0
.equ ti.RclEntryToEdit,            0x0020DD4
.equ ti.RclToQueue,                0x0020DD8
.equ ti.FormToTok,                 0x0020DDC
.equ ti.DispInterval,              0x0020DE0
.equ ti.DispLstName,               0x0020DE4
.equ ti.DispSLstNameHL,            0x0020DE8
.equ ti.EditEqu,                   0x0020DEC
.equ ti.CloseEquField,             0x0020DF0
.equ ti.AutoSelect,                0x0020DF4
.equ ti.DispYEOS,                  0x0020DF8
.equ ti.DispNumEOS,                0x0020DFC
.equ ti.SetupDispEq,               0x0020E00
.equ ti.DispForward,               0x0020E04
.equ ti.DispYPrompt2,              0x0020E08
.equ ti.StringWidth,               0x0020E0C
.equ ti.DispErrorScreen,           0x0020E10
.equ ti.PopCX,                     0x0020E14
.equ ti.LoadNoEEntry,              0x0020E18
.equ ti.SaveScreen,                0x0020E1C
.equ ti.RetScreen,                 0x0020E20
.equ ti.RetScreenErr,              0x0020E24
.equ ti.CheckSplitFlag,            0x0020E28
.equ ti.SolveRedisp,               0x0020E2C
.equ ti.SolveDisp,                 0x0020E30
.equ ti.ItemName,                  0x0020E34
.equ ti.SetNorm_Vals,              0x0020E38
.equ ti.SetYOffset,                0x0020E3C
.equ ti.ConvKeyToTok,              0x0020E40
.equ ti.ConvFCKeyToTok,            0x0020E44
.equ ti.ConvFEKeyToTok,            0x0020E48
.equ ti.TokToKey,                  0x0020E4C
.equ ti.GetVarCmdUSB,              0x0020E50
;                          equ     0020E54h
.equ ti.DeselectAllVars,           0x0020E58
.equ ti.DelRes,                    0x0020E5C
.equ ti.ConvLcToLr,                0x0020E60
.equ ti.RedimMat,                  0x0020E64
.equ ti.IncLstSize,                0x0020E68
.equ ti.InsertList,                0x0020E6C
.equ ti.DelListEl,                 0x0020E70
.equ ti.EditProg,                  0x0020E74
.equ ti.CloseProg,                 0x0020E78
.equ ti.ClrGraphRef,               0x0020E7C
.equ ti.FixTempCnt,                0x0020E80
.equ ti.SaveData,                  0x0020E84
.equ ti.RestoreData,               0x0020E88
.equ ti.FindAlphaUp,               0x0020E8C
.equ ti.FindAlphaDn,               0x0020E90
.equ ti.CmpSyms,                   0x0020E94
.equ ti.CreateTemp,                0x0020E98
.equ ti.CleanAll,                  0x0020E9C
.equ ti.MoveToNextSym,             0x0020EA0
.equ ti.ConvLrToLc,                0x0020EA4
.equ ti.TblScreenDown,             0x0020EA8
.equ ti.TblScreenUp,               0x0020EAC
.equ ti.ScreenScrollPixelsUp,      0x0020EB0
;;_ret                     equ 0020EB4h
.equ ti.ZIfRclHandler,             0x0020EB8
.equ ti.ZIfRclKApp,                0x0020EBC
;                          equ     0020EC0h
;                          equ     0020EC4h
.equ ti.InitNamePrompt,            0x0020EC8
.equ ti.InitNamePrompt_,           0x0020ECC
.equ ti.CatalogChk,                0x0020ED0
.equ ti.ClrTR,                     0x0020ED4
;                          equ     0020ED8h
;                          equ     0020EDCh
;                          equ     0020EE0h
;                          equ     0020EE4h
.equ ti.ErrNonReal_FPST_FPS1,      0x0020EE8
.equ ti.ErrNonReal,                0x0020EEC
.equ ti.WriteText,                 0x0020EF0
;                          equ     0020EF4h
.equ ti.GraphPars,                 0x0020EF8
.equ ti.PlotPars,                  0x0020EFC
.equ ti.ParseInp,                  0x0020F00
.equ ti.ParseOn,                   0x0020F04
.equ ti.ParseScan,                 0x0020F08
.equ ti.GetParse,                  0x0020F0C
.equ ti.SaveParse,                 0x0020F10
.equ ti.InitPFlgs,                 0x0020F14
.equ ti.CkEndLineRR,               0x0020F18
.equ ti.OP2Set60,                  0x0020F1C
.equ ti.GetStatPtr,                0x0020F20
.equ ti.CmpStatPtr,                0x0020F24
.equ ti.VarSysAdr,                 0x0020F28
.equ ti.StoSysTok,                 0x0020F2C
.equ ti.StoAns,                    0x0020F30
.equ ti.StoTheta,                  0x0020F34
.equ ti.StoR,                      0x0020F38
.equ ti.StoY,                      0x0020F3C
.equ ti.StoN,                      0x0020F40
.equ ti.StoT,                      0x0020F44
.equ ti.StoX,                      0x0020F48
.equ ti.StoOther,                  0x0020F4C
.equ ti.RclAns,                    0x0020F50
.equ ti.RclY,                      0x0020F54
.equ ti.RclN,                      0x0020F58
.equ ti.RclX,                      0x0020F5C
.equ ti.RclVarSym,                 0x0020F60
.equ ti.RclsyStok,                 0x0020F64
.equ ti.StMatel,                   0x0020F68
.equ ti.StLstvecel,                0x0020F6C
.equ ti.ConvOP1,                   0x0020F70
.equ ti.FindParseFormula,          0x0020F74
.equ ti.ParseFormula,              0x0020F78
.equ ti.StrngEnt1,                 0x0020F7C
.equ ti.Prgrdlp,                   0x0020F80
.equ ti.VarEnt,                    0x0020F84
.equ ti.ParseOnC,                  0x0020F88
.equ ti.ParseOn_,                  0x0020F8C
.equ ti.ParseCmd,                  0x0020F90
.equ ti.StoType,                   0x0020F94
.equ ti.CreatePair,                0x0020F98
.equ ti.PushNum,                   0x0020F9C
.equ ti.IncCurPCErrEnd,            0x0020FA0
.equ ti.ErrEnd,                    0x0020FA4
.equ ti.CommaErrF,                 0x0020FA8
.equ ti.CommaErr,                  0x0020FAC
.equ ti.StEQArg2,                  0x0020FB0
.equ ti.StEQArg,                   0x0020FB4
.equ ti.InpArg,                    0x0020FB8
.equ ti.StEQArg3,                  0x0020FBC
.equ ti.NxtFetch,                  0x0020FC0
.equ ti.CkFetchVar,                0x0020FC4
.equ ti.FetchVarA,                 0x0020FC8
.equ ti.FetchVar,                  0x0020FCC
.equ ti.CkEndLin,                  0x0020FD0
.equ ti.CkEndExp,                  0x0020FD4
.equ ti.CkParsEnd,                 0x0020FD8
.equ ti.StoTypeArg,                0x0020FDC
.equ ti.ConvDim,                   0x0020FE0
.equ ti.ConvDim00,                 0x0020FE4
.equ ti.AheadEqual,                0x0020FE8
.equ ti.ParseHeads,                0x0020FEC
.equ ti.ParseHead,                 0x0020FF0
.equ ti.AnsName,                   0x0020FF4
.equ ti.StoCmpReals,               0x0020FF8
.equ ti.GetDEPtr,                  0x0020FFC
.equ ti.Push2BOper,                0x0021000
.equ ti.Push3BOper,                0x0021004
.equ ti.Pop2BOper,                 0x0021008
.equ ti.Pop3BOper,                 0x002100C
.equ ti.PushOper,                  0x0021010
.equ ti.PopOper,                   0x0021014
.equ ti.FindEUndef,                0x0021018
.equ ti.SttmpEQ,                   0x002101C
.equ ti.FindEOL,                   0x0021020
.equ ti.BrkInc,                    0x0021024
.equ ti.IncFetch,                  0x0021028
.equ ti.CurFetch,                  0x002102C
.equ ti.Random,                    0x0021030
.equ ti.StoRand,                   0x0021034
.equ ti.RandInit,                  0x0021038
.equ ti.ResetStacks,               0x002103C
.equ ti.Factorial,                 0x0021040
.equ ti.YEquOnOff,                 0x0021044
.equ ti.EquSelUnsel,               0x0021048
.equ ti.ITSolver,                  0x002104C
.equ ti.GRITSolver,                0x0021050
.equ ti.ITSolverB,                 0x0021054
.equ ti.ITSolverNB,                0x0021058
.equ ti.ExTestInt,                 0x002105C
.equ ti.DistFun,                   0x0021060
.equ ti.LogGamma,                  0x0021064
.equ ti.OneVar,                    0x0021068
.equ ti.OneVars0,                  0x002106C
.equ ti.OrdStat,                   0x0021070
.equ ti.InitStatAns,               0x0021074
.equ ti.AnovaSpec,                 0x0021078
.equ ti.OutputExpr,                0x002107C
.equ ti.CentCursor,                0x0021080
;                          equ     0021084h
;                          equ     0021088h
;                          equ     002108Ch
;                          equ     0021090h
.equ ti.CkValDeltaX,               0x0021094
.equ ti.CkValDelta,                0x0021098
.equ ti.GrBufClr,                  0x002109C
.equ ti.GrBufCpyV,                 0x00210A0
.equ ti.FndSelEQ,                  0x00210A4
.equ ti.ClrGraphXY,                0x00210A8
.equ ti.NEDXTYStyle,               0x00210AC
.equ ti.PlotPt,                    0x00210B0
.equ ti.NewWindEP,                 0x00210B4
.equ ti.DrawAxes,                  0x00210B8
.equ ti.SetPenX,                   0x00210BC
.equ ti.SetPenY,                   0x00210C0
.equ ti.SetPenT,                   0x00210C4
.equ ti.TanEquDisp,                0x00210C8
.equ ti.PutAns,                    0x00210CC
.equ ti.DispOP1A,                  0x00210D0
;                          equ     00210D4h
.equ ti.SetTblGraphDraw,           0x00210D8
.equ ti.MemClear,                  0x00210DC
.equ ti.MemSet,                    0x00210E0
.equ ti.PointOn,                   0x00210E4
.equ ti.ExecuteNewPrgm,            0x00210E8
.equ ti.StrLength,                 0x00210EC
.equ ti.VPutMapRec,                0x00210F0
.equ ti.FindAppUp,                 0x00210F4
.equ ti.FindAppDown,               0x00210F8
.equ ti.FindApp,                   0x00210FC
.equ ti.os.FindAppStart,           0x0021100
.equ ti.SkipAppHeader,             0x0021104
.equ ti.FindAppStart,              0x0021108
.equ ti.IBounds,                   0x002110C
.equ ti.IOffset,                   0x0021110
.equ ti.DrawCirc,                  0x0021114
.equ ti.CanAlphIns,                0x0021118
.equ ti.CxReDisp,                  0x002111C
.equ ti.GetBaseVer,                0x0021120
.equ ti.OPSet0,                    0x0021124
.equ ti.AppGetCBLUSB,              0x0021128
.equ ti.SetIgnoreKey,              0x002112C
.equ ti.SetSendThisKeyBack,        0x0021130
.equ ti.DisableAPD,                0x0021134
.equ ti.EnableAPD,                 0x0021138
.equ ti.Set2IY34,                  0x002113C
.equ ti.ForceCmd,                  0x0021140
.equ ti.ApdSetup,                  0x0021144
.equ ti.AppSetup,                  0x0021148
;                          equ     002114Ch
.equ ti.ReleaseSedit,              0x0021150
.equ ti.InitSmallEditLine,         0x0021154
.equ ti.StartSmallEdit,            0x0021158
;                          equ     002115Ch
.equ ti.SGetTokString,             0x0021160
.equ ti.LoadPattern,               0x0021164
.equ ti.SStringLength,             0x0021168
.equ ti.RestorePenCol,             0x002116C
;                          equ     0021170h
.equ ti.EmptyHook,                 0x0021174
.equ ti.ForceSmallEditReturn,      0x0021178
.equ ti.SaveContext,               0x002117C
;                          equ     0021180h
.equ ti.ClearRow,                  0x0021184
;                          equ     0021188h
;                          equ     002118Ch
;                          equ     0021190h
;                          equ     0021194h
;                          equ     0021198h
;                          equ     002119Ch
;                          equ     00211A0h
;                          equ     00211A4h
;                          equ     00211A8h
;                          equ     00211ACh
;                          equ     00211B0h
;                          equ     00211B4h
;                          equ     00211B8h
;                          equ     00211BCh
;                          equ     00211C0h
;                          equ     00211C4h
;                          equ     00211C8h
;                          equ     00211CCh
;                          equ     00211D0h
;                          equ     00211D4h
;                          equ     00211D8h
;                          equ     00211DCh
;                          equ     00211E0h
;                          equ     00211E4h
;                          equ     00211E8h
;                          equ     00211ECh
;;_ret                     equ 00211F0h
;                          equ     00211F4h
.equ ti.InitSmallEditLineVar,      0x00211F8
.equ ti.InitSmallEditLineOP1,      0x00211FC
.equ ti.InitSmallEditBoxVar,       0x0021200
.equ ti.InitSmallEditBoxOP1,       0x0021204
.equ ti.RclEntryToEditA,           0x0021208
.equ ti.ErrCustom1,                0x002120C
.equ ti.ErrCustom2,                0x0021210
;;_ret                     equ 0021214h
.equ ti.ClearRect,                 0x0021218
.equ ti.InvertRect,                0x002121C
.equ ti.FillRect,                  0x0021220
.equ ti.RestoreTextFlags,          0x0021224
.equ ti.InitCellBox,               0x0021228
.equ ti.DrawCell,                  0x002122C
;                          equ     0021230h
.equ ti.InvertCell,                0x0021234
.equ ti.SetCellOverride,           0x0021238
.equ ti.DrawRectBorder,            0x002123C
.equ ti.ClearCell,                 0x0021240
.equ ti.CoverCell,                 0x0021244
.equ ti.EraseRectBorder,           0x0021248
.equ ti.FillRectPattern,           0x002124C
.equ ti.DrawRectBorderClear,       0x0021250
;                          equ     0021254h
.equ ti.VerticalLine,              0x0021258
.equ ti.IBoundsFull,               0x002125C
;                          equ     0021260h
;                          equ     0021264h
.equ ti.CPoint,                    0x0021268
.equ ti.DeleteApp,                 0x002126C
.equ ti.GetModeCellFlagOR,         0x0021270
.equ ti.ResetModeCellFlag,         0x0021274
.equ ti.IsModeCellSet,             0x0021278
.equ ti.GetModeCellFlag,           0x002127C
;                          equ     0021280h
.equ ti.SetCurCellBoxManager,      0x0021284
;                          equ     0021288h
.equ ti.CellBoxManager,            0x002128C
.equ ti.StartNewCell,              0x0021290
.equ ti.RunInCellOveride,          0x0021294
.equ ti.RunCellOveride,            0x0021298
.equ ti.ClearCurCell,              0x002129C
.equ ti.DrawCurCell,               0x00212A0
.equ ti.InvertCurCell,             0x00212A4
.equ ti.CoverCurCell,              0x00212A8
.equ ti.BlinkCell,                 0x00212AC
.equ ti.BlinkCellNoLookUp,         0x00212B0
.equ ti.BlinkCurCell,              0x00212B4
.equ ti.BlinkCellToOn,             0x00212B8
.equ ti.BlinkCellToOnNoLookUp,     0x00212BC
.equ ti.BlinkCurCellToOn,          0x00212C0
.equ ti.BlinkCellToOff,            0x00212C4
.equ ti.BlinkCellToOffNoLookUp,    0x00212C8
.equ ti.BlinkCurCellToOff,         0x00212CC
.equ ti.GetCurModeCellFlag,        0x00212D0
;                          equ     00212D4h
.equ ti.StartSmallEditReturn,      0x00212D8
;                          equ     00212DCh
;                          equ     00212E0h
.equ ti.CellKeyHandle,             0x00212E4
;                          equ     00212E8h
;                          equ     00212ECh
;                          equ     00212F0h
;                          equ     00212F4h
;                          equ     00212F8h
.equ ti.EraseAllCells,             0x00212FC
.equ ti.IsCurModeCellSet,          0x0021300
;                          equ     0021304h
;                          equ     0021308h
;                          equ     002130Ch
;                          equ     0021310h
.equ ti.DrawBlnkCell,              0x0021314
.equ ti.ClearBlnkCell,             0x0021318
.equ ti.InvertBlnkCell,            0x002131C
.equ ti.GetStringInput,            0x0021320
.equ ti.GetStringInput2,           0x0021324
.equ ti.WaitEnterKeyValue,         0x0021328
.equ ti.HorizontalLine,            0x002132C
.equ ti.CreateAppVar,              0x0021330
.equ ti.CreateProtProg,            0x0021334
.equ ti.CreateVar,                 0x0021338
.equ ti.AsmComp,                   0x002133C
.equ ti.GetAsmSize,                0x0021340
.equ ti.SquishPrgm,                0x0021344
.equ ti.ExecutePrgm,               0x0021348
.equ ti.ChkFindSymAsm,             0x002134C
.equ ti.ParsePrgmName,             0x0021350
.equ ti.CSub,                      0x0021354
.equ ti.CAdd,                      0x0021358
.equ ti.CSquare,                   0x002135C
.equ ti.CMult,                     0x0021360
.equ ti.CRecip,                    0x0021364
.equ ti.CDiv,                      0x0021368
.equ ti.CAbs,                      0x002136C
.equ ti.AddSquares,                0x0021370
.equ ti.CSqRoot,                   0x0021374
.equ ti.CLN,                       0x0021378
.equ ti.CLog,                      0x002137C
.equ ti.CTenX,                     0x0021380
.equ ti.CEtoX,                     0x0021384
.equ ti.CXrootY,                   0x0021388
;                          equ     002138Ch
.equ ti.CYtoX,                     0x0021390
.equ ti.InvertNonReal,             0x0021394
.equ ti.CTrunc,                    0x0021398
.equ ti.CFrac,                     0x002139C
.equ ti.CFloor,                    0x00213A0
.equ ti.SrchVLstUp,                0x00213A4
.equ ti.SrchVLstDn,                0x00213A8
.equ ti.FlashWriteDisable,         0x00213AC
.equ ti.Disp,                      0x00213B0
.equ ti.GetBytePaged,              0x00213B4
.equ ti.RunCursorHook,             0x00213B8
.equ ti.RunLibraryHook,            0x00213BC
.equ ti.RunRawKeyHook,             0x00213C0
.equ ti.SetCursorHook,             0x00213C4
.equ ti.SetLibraryHook,            0x00213C8
.equ ti.SetGetKeyHook,             0x00213CC
.equ ti.ClrCursorHook,             0x00213D0
.equ ti.ClrLibraryHook,            0x00213D4
.equ ti.ClrRawKeyHook,             0x00213D8
.equ ti.GetKeyHook,                0x00213DC
.equ ti.SetGetCSCHook,             0x00213E0
.equ ti.ClrGetKeyHook,             0x00213E4
.equ ti.SetCatalog2Hook,           0x00213E8
.equ ti.ClrCatalog2Hook,           0x00213EC
.equ ti.SetLocalizeHook,           0x00213F0
.equ ti.ClrLocalizeHook,           0x00213F4
.equ ti.SetTokenHook,              0x00213F8
.equ ti.ClrTokenHook,              0x00213FC
;                          equ     0021400h
;                          equ     0021404h
.equ ti.DispListElementOffLA,      0x0021408
.equ ti.BitVertSplit,              0x002140C
.equ ti.SetHomescreenHook,         0x0021410
.equ ti.ClrHomescreenHook,         0x0021414
.equ ti.SetWindowHook,             0x0021418
.equ ti.ClrWindowHook,             0x002141C
.equ ti.SetGraphModeHook,          0x0021420
.equ ti.ClrGraphModeHook,          0x0021424
.equ ti.ParseAndStoreSysVar,       0x0021428
.equ ti.DisplayEditSysVar,         0x002142C
.equ ti.JForceWIndowSettings,      0x0021430
.equ ti.DelVarArc,                 0x0021434
.equ ti.DelVarNoArc,               0x0021438
.equ ti.SetAllPlots,               0x002143C
.equ ti.SetYeditHook,              0x0021440
.equ ti.ClrYeditHook,              0x0021444
.equ ti.Arc_Unarc,                 0x0021448
.equ ti.ArchiveVar,                0x002144C
.equ ti.UnarchiveVar,              0x0021450
.equ ti.SetFontHook,               0x0021454
.equ ti.ClrFontHook,               0x0021458
.equ ti.SetRegraphHook,            0x002145C
.equ ti.ClrRegraphHook,            0x0021460
.equ ti.RunGraphingHook,           0x0021464
.equ ti.SetTraceHook,              0x0021468
.equ ti.ClrTraceHook,              0x002146C
.equ ti.RunTraceHook,              0x0021470
.equ ti.NDeriv,                    0x0021474
.equ ti.PolarDerivative,           0x0021478
.equ ti.JForceGraphNoKey,          0x002147C
.equ ti.JForceGraphKey,            0x0021480
.equ ti.PowerOff,                  0x0021484
.equ ti.GetKeyRetOff,              0x0021488
.equ ti.FindGroupSym,              0x002148C
.equ ti.LoadDEIndPaged,            0x0021490
.equ ti.SetUpPagedPtr,             0x0021494
.equ ti.PagedGet,                  0x0021498
.equ ti.SetParserHook,             0x002149C
.equ ti.ClrParserHook,             0x00214A0
.equ ti.SetAppChangeHook,          0x00214A4
.equ ti.ClrAppChangeHook,          0x00214A8
.equ ti.SetGraphicsHook,           0x00214AC
.equ ti.ClrGraphicsHook,           0x00214B0
.equ ti.ILineNoGraphicsHook,       0x00214B4
.equ ti.ILineNoHook,               0x00214B8
;                          equ     00214BCh
.equ ti.DeleteTempPrograms,        0x00214C0
.equ ti.SetCatalog1Hook,           0x00214C4
.equ ti.ClrCatalog1Hook,           0x00214C8
.equ ti.SetHelpHook,               0x00214CC
.equ ti.ClrHelpHook,               0x00214D0
.equ ti.DispCatalogEnd,            0x00214D4
.equ ti.GetMenuKeypress,           0x00214D8
.equ ti.GetCatalogItem,            0x00214DC
.equ ti.RunCatalog2Hook,           0x00214E0
.equ ti.RunCatalog1Hook,           0x00214E4
;                          equ     00214E8h
;                          equ     00214ECh
.equ ti.DispMenuTitle,             0x00214F0
;                          equ     00214F4h
.equ ti.SetCxReDispHook,           0x00214F8
.equ ti.ClrCxReDispHook,           0x00214FC
.equ ti.DrawStatusBarMode,         0x0021500
.equ ti.BufClr,                    0x0021504
.equ ti.UnOPExec2,                 0x0021508
.equ ti.BinOPExec2,                0x002150C
.equ ti.LoadMenuB,                 0x0021510
.equ ti.DisplayVarInfo,            0x0021514
.equ ti.SetMenuHook,               0x0021518
.equ ti.ClrMenuHook,               0x002151C
.equ ti.GetBCOffSetIX,             0x0021520
.equ ti.GetBCOffSetIX_,            0x0021524
.equ ti.ForceFullScreen,           0x0021528
.equ ti.HLMinus5,                  0x002152C
;;_ret                     equ 0021530h
;                          equ     0021534h
;                          equ     0021538h
.equ ti.Arc_Unarc_,                0x002153C
.equ ti.RclExit,                   0x0021540
.equ ti.SetSilentLinkHook,         0x0021544
.equ ti.ClrSilentLinkHook,         0x0021548
.equ ti.TwoVarSet,                 0x002154C
.equ ti.ExecClassCToken,           0x0021550
.equ ti.ExecClass3Token,           0x0021554
.equ ti.GetSysInfo,                0x0021558
.equ ti.RunChkCTenX,               0x002155C
.equ ti.TenXNoClr,                 0x0021560
;                          equ     0021564h
;                          equ     0021568h
.equ ti.GetVarVersion,             0x002156C
.equ ti.ParseGraphCmdToken,        0x0021570
;                          equ     0021574h
.equ ti.DeleteTempEditEqu,         0x0021578
.equ ti.PromptMoveBackLeft,        0x002157C
.equ ti.WPutSEOLRes10E,            0x0021580
.equ ti.InvertTextInsMode,         0x0021584
;                          equ     0021588h
.equ ti.ResetDefaults,             0x002158C
.equ ti.ZeroFinanceVars,           0x0021590
.equ ti.DispHeader,                0x0021594
.equ ti.JForceGroup,               0x0021598
;                          equ     002159Ch
;                          equ     00215A0h
.equ ti.DispCoords,                0x00215A4
;                          equ     00215A8h
;                          equ     00215ACh
.equ ti.ChkTmr,                    0x00215B0
.equ ti.ClockOff,                  0x00215B4
.equ ti.ClockOn,                   0x00215B8
;                          equ     00215BCh
.equ ti.GetDate,                   0x00215C0
.equ ti.GetDateString,             0x00215C4
.equ ti.GetDtFmt,                  0x00215C8
.equ ti.GetDtStr,                  0x00215CC
.equ ti.GetTime,                   0x00215D0
.equ ti.FormTime,                  0x00215D4
.equ ti.GetTmFmt,                  0x00215D8
.equ ti.GetTmStr,                  0x00215DC
.equ ti.SetZeroOne,                0x00215E0
.equ ti.SetDate,                   0x00215E4
.equ ti.IsOneTwoThree,             0x00215E8
.equ ti.SetTime,                   0x00215EC
.equ ti.IsOP112or24,               0x00215F0
.equ ti.ChkTimer0,                 0x00215F4
.equ ti.TimeCnv,                   0x00215F8
.equ ti.ClrWindowAndFlags,         0x00215FC
.equ ti.ResetAllLists,             0x0021600
.equ ti.DispValue,                 0x0021604
;                          equ     0021608h
;                          equ     002160Ch
;                          equ     0021610h
.equ ti.CpOP1OP2Rounded,           0x0021614
.equ ti.CpOP1OP2Rounded2,          0x0021618
;                          equ     002161Ch
;                          equ     0021620h
.equ ti.ResetIOPrompt,             0x0021624
;                          equ     0021628h
.equ ti.SetUpEditor,               0x002162C
.equ ti.SortA,                     0x0021630
.equ ti.SortD,                     0x0021634
;                          equ     0021638h
.equ ti.IsOP1ResID,                0x002163C
;                          equ     0021640h
;                          equ     0021644h
;                          equ     0021648h
.equ ti.ForceModeKeypress,         0x002164C
.equ ti.DispAboutScreen,           0x0021650
.equ ti.ChkHelpHookVer,            0x0021654
.equ ti.Draw32,                    0x0021658
;                          equ     002165Ch
;                          equ     0021660h
;                          equ     0021664h
.equ ti.DrawPlotStatus,            0x0021668
.equ ti.DrawTableEditor,           0x002166C
.equ ti.DisplayListNameEquals,     0x0021670
.equ ti.DisplayListHeader,         0x0021674
.equ ti.DispMatrixDimensions,      0x0021678
.equ ti.HighlightListEdItem,       0x002167C
;                          equ     0021680h
;                          equ     0021684h
.equ ti.MatrixName,                0x0021688
;                          equ     002168Ch
;                          equ     0021690h
;                          equ     0021694h
;                          equ     0021698h
;                          equ     002169Ch
.equ ti.ChkCxMainPtr,              0x00216A0
.equ ti.NumError02_,               0x00216A4
;                          equ     00216A8h
.equ ti.SetupEmptyEditTempEqu,     0x00216AC
.equ ti.Res1IY0E,                  0x00216B0
.equ ti.RestoreBuffer,             0x00216B4
;                          equ     00216B8h
;                          equ     00216BCh
;                          equ     00216C0h
;                          equ     00216C4h
;                          equ     00216C8h
;                          equ     00216CCh
.equ ti.DisplayListEquals,         0x00216D0
.equ ti.GetCurPlotListOffset,      0x00216D4
.equ ti.GoToLastRow,               0x00216D8
.equ ti.DrawRectBorder_,           0x00216DC
;                          equ     00216E0h
;                          equ     00216E4h
;                          equ     00216E8h
;                          equ     00216ECh
.equ ti.NamedListToOP1,            0x00216F0
;                          equ     00216F4h
;                          equ     00216F8h
;                          equ     00216FCh
.equ ti.InitUSBDeviceCallback,     0x0021700
.equ ti.KillUSBDevice,             0x0021704
.equ ti.SetUSBConfiguration,       0x0021708
.equ ti.RequestUSBData,            0x002170C
.equ ti.StopReceivingUSBData,      0x0021710
.equ ti.SetVertGraphActive,        0x0021714
.equ ti.ClrVertGraphActive,        0x0021718
.equ ti.SetUSBActivityHook,        0x002171C
.equ ti.ClrUSBActivityHook,        0x0021720
;;_ret                     equ 0021724h
.equ ti.GetCurPlotOffsetPrev,      0x0021728
.equ ti.SplitUpdateStatPlotLists,  0x002172C
.equ ti.GraphLine,                 0x0021730
;                          equ     0021734h
;                          equ     0021738h
;                          equ     002173Ch
;                          equ     0021740h
;                          equ     0021744h
;                          equ     0021748h
.equ ti.ZIfInTblEditor,            0x002174C
;                          equ     0021750h
.equ ti.GetCurPlotOffset,          0x0021754
;                          equ     0021758h
;                          equ     002175Ch
;                          equ     0021760h
;                          equ     0021764h
;                          equ     0021768h
.equ ti.UpdateStatPlotLists,       0x002176C
.equ ti.ChkSomethingElseFPS5,      0x0021770
.equ ti.ChkSomethingFPS5,          0x0021774
.equ ti.VDispRealOP1,              0x0021778
.equ ti.DispXEqualsNum,            0x002177C
.equ ti.ResetGraphSettings,        0x0021780
.equ ti.InitializeVariables,       0x0021784
;;_ret                     equ 0021788h
.equ ti.DelVarSym,                 0x002178C
.equ ti.FindAppUpNoCase,           0x0021790
.equ ti.FindAppDnNoCase,           0x0021794
.equ ti.SetupHome,                 0x0021798
.equ ti.GrPutawayFull,             0x002179C
;;_ret                     equ 00217A0h
.equ ti.ToggleUSBSmartPadInput,    0x00217A4
.equ ti.IsUSBDeviceConnected,      0x00217A8
.equ ti.PolarEquToOP1,             0x00217AC
.equ ti.ParamXEquToOP1,            0x00217B0
.equ ti.ParamYEquToOP1,            0x00217B4
.equ ti.DispTestModeResetComplete, 0x00217B8
.equ ti.PTTReset,                  0x00217BC
.equ ti.FindAppCustom,             0x00217C0
.equ ti.ClearGraphStyles,          0x00217C4
.equ ti.BufToNextBASICSeparator,   0x00217C8
;                          equ     00217CCh
;                          equ     00217D0h
.equ ti.ZooStandard,               0x00217D4
;                          equ     00217D8h
;                          equ     00217DCh
;                          equ     00217E0h
;                          equ     00217E4h
;                          equ     00217E8h
;                          equ     00217ECh
;                          equ     00217F0h
;                          equ     00217F4h
;                          equ     00217F8h
;                          equ     00217FCh
;                          equ     0021800h
;                          equ     0021804h
;                          equ     0021808h
;                          equ     002180Ch
.equ ti.AddHistoryEntryString,     0x0021810
.equ ti.CurrEntryToPrevEntry,      0x0021814
;                          equ     0021818h
;                          equ     002181Ch
;                          equ     0021820h
;                          equ     0021824h
;                          equ     0021828h
;                          equ     002182Ch
;                          equ     0021830h
;                          equ     0021834h
;                          equ     0021838h
;                          equ     002183Ch
;                          equ     0021840h
;                          equ     0021844h
;                          equ     0021848h
;                          equ     002184Ch
;                          equ     0021850h
;                          equ     0021854h
;                          equ     0021858h
;                          equ     002185Ch
;                          equ     0021860h
;                          equ     0021864h
;                          equ     0021868h
;                          equ     002186Ch
;                          equ     0021870h
;                          equ     0021874h
;                          equ     0021878h
;                          equ     002187Ch
;                          equ     0021880h
;                          equ     0021884h
;                          equ     0021888h
;                          equ     002188Ch
;                          equ     0021890h
;                          equ     0021894h
;                          equ     0021898h
;                          equ     002189Ch
;                          equ     00218A0h
;                          equ     00218A4h
;                          equ     00218A8h
;                          equ     00218ACh
;                          equ     00218B0h
;                          equ     00218B4h
;                          equ     00218B8h
;                          equ     00218BCh
;                          equ     00218C0h
;                          equ     00218C4h
;                          equ     00218C8h
;                          equ     00218CCh
;                          equ     00218D0h
;                          equ     00218D4h
;                          equ     00218D8h
;                          equ     00218DCh
;                          equ     00218E0h
;                          equ     00218E4h
;                          equ     00218E8h
;                          equ     00218ECh
.equ ti.RunInitialBootMenu,        0x00218F0
;                          equ     00218F4h
;                          equ     00218F8h
;                          equ     00218FCh
.equ ti.Clr05RclFlags,             0x0021900
;                          equ     0021904h
;                          equ     0021908h
;                          equ     002190Ch
;                          equ     0021910h
.equ ti.DeleteHistoryEntry,        0x0021914
;                          equ     0021918h
;                          equ     002191Ch
;                          equ     0021920h
;                          equ     0021924h
;                          equ     0021928h
;                          equ     002192Ch
;                          equ     0021930h
;                          equ     0021934h
;                          equ     0021938h
;                          equ     002193Ch
.equ ti.CommonKeys_,               0x0021940
;                          equ     0021944h
;                          equ     0021948h
;                          equ     002194Ch
;                          equ     0021950h
;                          equ     0021954h
;                          equ     0021958h
;                          equ     002195Ch
;                          equ     0021960h
;                          equ     0021964h
;                          equ     0021968h
;                          equ     002196Ch
;                          equ     0021970h
;                          equ     0021974h
;                          equ     0021978h
;                          equ     002197Ch
;                          equ     0021980h
;                          equ     0021984h
;                          equ     0021988h
;                          equ     002198Ch
;                          equ     0021990h
;                          equ     0021994h
.equ ti.ResetLastEntryStack,       0x0021998
;                          equ     002199Ch
;                          equ     00219A0h
.equ ti.jp_JForceCmdNoChar,        0x00219A4
.equ ti.Load_LFont,                0x00219A8
;                          equ     00219ACh
;                          equ     00219B0h
;                          equ     00219B4h
;                          equ     00219B8h
;                          equ     00219BCh
;                          equ     00219C0h
;                          equ     00219C4h
;                          equ     00219C8h
;                          equ     00219CCh
;                          equ     00219D0h
;                          equ     00219D4h
;                          equ     00219D8h
.equ ti.EnterSelfTest,             0x00219DC
.equ ti.DrawEntrySepLine,          0x00219E0
;                          equ     00219E4h
.equ ti.GetGraphModeProperties,    0x00219E8
;                          equ     00219ECh
;                          equ     00219F0h
;                          equ     00219F4h
;                          equ     00219F8h
;                          equ     00219FCh
;                          equ     0021A00h
;                          equ     0021A04h
;                          equ     0021A08h
;                          equ     0021A0Ch
.equ ti.ClrLCDAll,                 0x0021A10
.equ ti.BufIPoint,                 0x0021A14
;                          equ     0021A18h
;                          equ     0021A1Ch
;                          equ     0021A20h
;                          equ     0021A24h
.equ ti.SetDrawFGColorA,           0x0021A28
;                          equ     0021A2Ch
;                          equ     0021A30h
;                          equ     0021A34h
.equ ti.DrawGraphBackground,       0x0021A38
.equ ti.DrawStatusBar,             0x0021A3C
;                          equ     0021A40h
;                          equ     0021A44h
;                          equ     0021A48h
;                          equ     0021A4Ch
.equ ti.DrawBatteryIndicator,      0x0021A50
.equ ti.DrawBatteryStatus,         0x0021A54
.equ ti.VDispHL,                   0x0021A58
.equ ti.PDspGrphNoColorReload,     0x0021A5C
;                          equ     0021A60h
;                          equ     0021A64h
;                          equ     0021A68h
;                          equ     0021A6Ch
;                          equ     0021A70h
;                          equ     0021A74h
;                          equ     0021A78h
;                          equ     0021A7Ch
;                          equ     0021A80h
;                          equ     0021A84h
;                          equ     0021A88h
;                          equ     0021A8Ch
;                          equ     0021A90h
;                          equ     0021A94h
;                          equ     0021A98h
;                          equ     0021A9Ch
;                          equ     0021AA0h
;                          equ     0021AA4h
;                          equ     0021AA8h
;                          equ     0021AACh
;                          equ     0021AB0h
.equ ti.DrawStatusBarInfo,         0x0021AB4
.equ ti.RestoreLCDBrightness,      0x0021AB8
.equ ti.RestoreLCDBrightness_,     0x0021ABC
.equ ti.DimLCDSlow,                0x0021AC0
;                          equ     0021AC4h
;                          equ     0021AC8h
;                          equ     0021ACCh
;                          equ     0021AD0h
;                          equ     0021AD4h
;                          equ     0021AD8h
;                          equ     0021ADCh
.equ ti.SetTextFGBGcolors,         0x0021AE0
.equ ti.SetTextFGBGcolors_,        0x0021AE4
.equ ti.SetTextBGcolor,            0x0021AE8
.equ ti.VPutPS,                    0x0021AEC
;                          equ     0021AF0h
;                          equ     0021AF4h
;                          equ     0021AF8h
;                          equ     0021AFCh
.equ ti.DrawTILogo,                0x0021B00
.equ ti.DrawThickRectBorder,       0x0021B04
;                          equ     0021B08h
.equ ti.DrawStatusBarTextClr,      0x0021B0C
;                          equ     0021B10h
;                          equ     0021B14h
;                          equ     0021B18h
;                          equ     0021B1Ch
.equ ti.VPutPSN,                   0x0021B20
;                          equ     0021B24h
;                          equ     0021B28h
;                          equ     0021B2Ch
;                          equ     0021B30h
.equ ti.RStrGraphFlags,            0x0021B34
;                          equ     0021B38h
;                          equ     0021B3Ch
.equ ti.VPutMapSpecial,            0x0021B40
;                          equ     0021B44h
;                          equ     0021B48h
;                          equ     0021B4Ch
;                          equ     0021B50h
;                          equ     0021B54h
;                          equ     0021B58h
;                          equ     0021B5Ch
;                          equ     0021B60h
.equ ti.DrawSprite16bpp,           0x0021B64
;                          equ     0021B68h
;                          equ     0021B6Ch
;                          equ     0021B70h
;                          equ     0021B74h
;                          equ     0021B78h
;                          equ     0021B7Ch
;                          equ     0021B80h
;                          equ     0021B84h
;                          equ     0021B88h
;                          equ     0021B8Ch
;                          equ     0021B90h
;                          equ     0021B94h
;                          equ     0021B98h
;                          equ     0021B9Ch
;                          equ     0021BA0h
;                          equ     0021BA4h
;                          equ     0021BA8h
.equ ti.GetColorValue,             0x0021BAC
;                          equ     0021BB0h
;                          equ     0021BB4h
;                          equ     0021BB8h
;                          equ     0021BBCh
;                          equ     0021BC0h
.equ ti.GraphBGColorToDrawBGColor, 0x0021BC4
.equ ti.SetWhiteDrawBGColor,       0x0021BC8
;                          equ     0021BCCh
.equ ti.ChkResAppTextSave,         0x0021BD0
.equ ti.ChkCxMain,                 0x0021BD4
;                          equ     0021BD8h
;                          equ     0021BDCh
.equ ti.DrawRectBorder__,          0x0021BE0
;                          equ     0021BE4h
;                          equ     0021BE8h
;                          equ     0021BECh
;                          equ     0021BF0h
;                          equ     0021BF4h
;                          equ     0021BF8h
;                          equ     0021BFCh
;                          equ     0021C00h
;                          equ     0021C04h
;                          equ     0021C08h
;                          equ     0021C0Ch
;                          equ     0021C10h
;                          equ     0021C14h
;                          equ     0021C18h
;                          equ     0021C1Ch
;                          equ     0021C20h
;                          equ     0021C24h
;                          equ     0021C28h
;                          equ     0021C2Ch
;                          equ     0021C30h
;                          equ     0021C34h
;                          equ     0021C38h
;                          equ     0021C3Ch
;                          equ     0021C40h
;                          equ     0021C44h
.equ ti.DrawLineEndEntry,          0x0021C48
;                          equ     0021C4Ch
;                          equ     0021C50h
;;_ret                     equ 0021C54h
;                          equ     0021C58h
;                          equ     0021C5Ch
;                          equ     0021C60h
;                          equ     0021C64h
;                          equ     0021C68h
.equ ti.BitGrfFuncM,               0x0021C6C
;;_ret                     equ 0021C70h
.equ ti.GetScrollPxlAmount,        0x0021C74
.equ ti.os.PushErrorHandler,       0x0021C78
.equ ti.os.PopErrorHandler,        0x0021C7C
.equ ti.os.ThrowError,             0x0021C80
.equ ti.os.RealCopy,               0x0021C84
.equ ti.os.RealAcosRad,            0x0021C88
.equ ti.os.RealAsinRad,            0x0021C8C
.equ ti.os.RealAtanRad,            0x0021C90
.equ ti.os.RealAdd,                0x0021C94
.equ ti.os.CplxAdd,                0x0021C98
.equ ti.os.RealCompare,            0x0021C9C
.equ ti.os.RealCosRad,             0x0021CA0
.equ ti.os.RealRadToDeg,           0x0021CA4
.equ ti.os.RealDiv,                0x0021CA8
.equ ti.os.RealExp,                0x0021CAC
.equ ti.os.RealFloor,              0x0021CB0
.equ ti.os.RealToStr,              0x0021CB4
.equ ti.os.RealFrac,               0x0021CB8
.equ ti.os.RealGcd,                0x0021CBC
.equ ti.os.RealRoundInt,           0x0021CC0
.equ ti.os.RealLcm,                0x0021CC4
.equ ti.os.RealLog,                0x0021CC8
.equ ti.os.RealMax,                0x0021CCC
.equ ti.os.RealMin,                0x0021CD0
.equ ti.os.RealMul,                0x0021CD4
.equ ti.os.RealNcr,                0x0021CD8
.equ ti.os.RealNeg,                0x0021CDC
.equ ti.os.RealNpr,                0x0021CE0
.equ ti.os.RealPow,                0x0021CE4
.equ ti.os.RealDegToRad,           0x0021CE8
.equ ti.os.RealRandInt,            0x0021CEC
.equ ti.os.RealInv,                0x0021CF0
.equ ti.os.RealMod,                0x0021CF4
.equ ti.os.RealRound,              0x0021CF8
.equ ti.os.RealSinRad,             0x0021CFC
.equ ti.os.RealSqrt,               0x0021D00
.equ ti.os.RealSub,                0x0021D04
.equ ti.os.RealTanRad,             0x0021D08
.equ ti.os.StrToReal,              0x0021D0C
.equ ti.os.RealTrunc,              0x0021D10
.equ ti.os.SetFlagBits,            0x0021D14
.equ ti.os.ResetFlagBits,          0x0021D18
.equ ti.os.TestFlagBits,           0x0021D1C
.equ ti.os.SetFlagByte,            0x0021D20
.equ ti.os.GetFlagByte,            0x0021D24
.equ ti.os.GetCursorPos,           0x0021D28
.equ ti.os.PutStrFull,             0x0021D2C
.equ ti.os.PutStrLine,             0x0021D30
.equ ti.os.SetCursorPos,           0x0021D34
.equ ti.os.GetKey,                 0x0021D38
.equ ti.os.GetCSC,                 0x0021D3C
.equ ti.os.AppInit,                0x0021D40
;                          equ     0021D44h
.equ ti.ChkBCIs0,                  0x0021D48
.equ ti.ChkDEIs0,                  0x0021D4C
.equ ti.ChkHLIs0,                  0x0021D50
.equ ti.SetAToBCU,                 0x0021D54
.equ ti.SetAToDEU,                 0x0021D58
.equ ti.SetAToHLU,                 0x0021D5C
.equ ti.SetBCUToA,                 0x0021D60
.equ ti.SetBCUToB,                 0x0021D64
.equ ti.SetDEUToA,                 0x0021D68
.equ ti.SetDEUToB,                 0x0021D6C
.equ ti.SetHLUToA,                 0x0021D70
.equ ti.SetHLUToB,                 0x0021D74
.equ ti.SignExtendBC,              0x0021D78
.equ ti.SignExtendDE,              0x0021D7C
.equ ti.SignExtendHL,              0x0021D80
.equ ti.SetBCUTo0,                 0x0021D84
.equ ti.SetDEUTo0,                 0x0021D88
.equ ti.SetHLUTo0,                 0x0021D8C
.equ ti.DivHLByA,                  0x0021D90
.equ ti.CpHLDE_s,                  0x0021D94
.equ ti.CpHLDE_,                   0x0021D98
.equ ti.LoadDEInd_s,               0x0021D9C
.equ ti.LoadDEInd,                 0x0021DA0
.equ ti.CpHLDEBC,                  0x0021DA4
.equ ti.NegBC,                     0x0021DA8
.equ ti.NegDE,                     0x0021DAC
.equ ti.StrCmpre,                  0x0021DB0
.equ ti.AddHLAndA,                 0x0021DB4
.equ ti.NextFlashPage,             0x0021DB8
.equ ti.PrevFlashPage,             0x0021DBC
.equ ti.SwapEndianHL_s,            0x0021DC0
.equ ti.ReloadAppEntryVecs,        0x0021DC4
;                          equ     0021DC8h
;                          equ     0021DCCh
;                          equ     0021DD0h
;                          equ     0021DD4h
;                          equ     0021DD8h
;                          equ     0021DDCh
.equ ti.os.ClearVRAMLines,         0x0021DE0
.equ ti.os.DisableCursor,          0x0021DE4
.equ ti.os.EnableCursor,           0x0021DE8
;                          equ     0021DECh
;                          equ     0021DF0h
;                          equ     0021DF4h
;                          equ     0021DF8h
;                          equ     0021DFCh
.equ ti.os.FontDrawText,           0x0021E00
;                          equ     0021E04h
;                          equ     0021E08h
;                          equ     0021E0Ch
;                          equ     0021E10h
.equ ti.os.FontGetHeight,          0x0021E14
.equ ti.os.FontGetWidth,           0x0021E18
.equ ti.os.InitDrawing,            0x0021E1C
.equ ti.os.SetDrawBGColor,         0x0021E20
.equ ti.os.SetDrawFGColor,         0x0021E24
.equ ti.os.FontSelect,             0x0021E28
;                          equ     0021E2Ch
;                          equ     0021E30h
.equ ti.tolower,                   0x0021E34
.equ ti.toupper,                   0x0021E38
;                          equ     0021E3Ch
;                          equ     0021E40h
;                          equ     0021E44h
;                          equ     0021E48h
;                          equ     0021E4Ch
;                          equ     0021E50h
;                          equ     0021E54h
;                          equ     0021E58h
;                          equ     0021E5Ch
;                          equ     0021E60h
;                          equ     0021E64h
.equ ti.ChkACplx,                  0x0021E68
;                          equ     0021E6Ch
.equ ti.os.RclAns,                 0x0021E70
;                          equ     0021E74h
;                          equ     0021E78h
;                          equ     0021E7Ch
;                          equ     0021E80h
;                          equ     0021E84h
;                          equ     0021E88h
.equ ti.SetPolarEquToOP1,          0x0021E8C
;                          equ     0021E90h
;                          equ     0021E94h
;                          equ     0021E98h
;                          equ     0021E9Ch
;                          equ     0021EA0h
;                          equ     0021EA4h
;                          equ     0021EA8h
;                          equ     0021EACh
;                          equ     0021EB0h
;                          equ     0021EB4h
;                          equ     0021EB8h
;                          equ     0021EBCh
;                          equ     0021EC0h
;                          equ     0021EC4h
.equ ti.os.SetTimer1,              0x0021EC8
.equ ti.os.DisableTimer1,          0x0021ECC
.equ ti.os.SetKbdKey,              0x0021ED0
.equ ti.os.GetSystemInfo,          0x0021ED4
;                          equ     0021ED8h
;                          equ     0021EDCh
.equ ti.DispHL,                    0x0021EE0
.equ ti.os.GetDrawBGColor_BROKEN,  0x0021EE4         ; fixed in OS 5.2
.equ ti.os.GetDrawFGColor,         0x0021EE8
.equ ti.os.FontGetID,              0x0021EEC
;                          equ     0021EF0h
.equ ti.os.RealToInt24,            0x0021EF4
.equ ti.os.Int24ToReal,            0x0021EF8
.equ ti.GetOpenLibPtr,             0x0021EFC
.equ ti.RestoreColCoordinates,     0x0021F00
;                          equ     0021F04h
;                          equ     0021F08h
;                          equ     0021F0Ch
;                          equ     0021F10h
;                          equ     0021F14h
;                          equ     0021F18h
;                          equ     0021F1Ch
;                          equ     0021F20h
;                          equ     0021F24h
;                          equ     0021F28h
;                          equ     0021F2Ch
;                          equ     0021F30h
;                          equ     0021F34h
;                          equ     0021F38h
;                          equ     0021F3Ch
;                          equ     0021F40h
.equ ti.VPutMapNoReset0IY23,       0x0021F44
;                          equ     0021F48h
;                          equ     0021F4Ch
.equ ti.BufCpy,                    0x0021F50
;                          equ     0021F54h
;                          equ     0021F58h
;                          equ     0021F5Ch
.equ ti.DrawStandardEntrySepLine,  0x0021F60
.equ ti.DrawHomeNewSepLine,        0x0021F64
.equ ti.DrawStatusBarText,         0x0021F68
;                          equ     0021F6Ch
;                          equ     0021F70h
;                          equ     0021F74h
;                          equ     0021F78h
;                          equ     0021F7Ch
.equ ti.MovFrOP1OP2,               0x0021F80
;                          equ     0021F84h
;                          equ     0021F88h
;                          equ     0021F8Ch
;                          equ     0021F90h
;                          equ     0021F94h
.equ ti.ChkInRam,                  0x0021F98
;                          equ     0021F9Ch
;                          equ     0021FA0h
.equ ti.FontGetWidth,              0x0021FA4
.equ ti.os.ForceCmdNoChar,         0x0021FA8
.equ ti.os.DelVarEntry,            0x0021FAC
.equ ti.os.GetSymTablePtr,         0x0021FB0
.equ ti.os.NextSymEntry,           0x0021FB4
.equ ti.os.ChkFindSym,             0x0021FB8
.equ ti.os.GetVarSize,             0x0021FBC
.equ ti.os.GetVarSizeBytes,        0x0021FC0
;                          equ     0021FC4h
.equ ti.os.GetRealListElement,     0x0021FC8
.equ ti.os.GetRealVar,             0x0021FCC
.equ ti.os.ResizeList,             0x0021FD0
.equ ti.os.ResizeMatrix,           0x0021FD4
;                          equ     0021FD8h
.equ ti.os.SetRealListElement,     0x0021FDC
.equ ti.os.SetRealVar,             0x0021FE0
.equ ti.os.GetAppVersionString,    0x0021FE4
;                          equ     0021FE8h
;                          equ     0021FECh
.equ ti.os.MemChk,                 0x0021FF0
;                          equ     0021FF4h
;                          equ     0021FF8h
;                          equ     0021FFCh
;                          equ     0022000h
;                          equ     0022004h
;                          equ     0022008h
;                          equ     002200Ch
;                          equ     0022010h
;                          equ     0022014h
;                          equ     0022018h
;                          equ     002201Ch
;                          equ     0022020h
;                          equ     0022024h
;                          equ     0022028h
;                          equ     002202Ch
;                          equ     0022030h
;                          equ     0022034h
;                          equ     0022038h
;                          equ     002203Ch
.equ ti.ArcChk,                    0x0022040
.equ ti.LoadDEIndFlash,            0x0022044
.equ ti.ChkInRamB,                 0x0022048
;                          equ     002204Ch
;                          equ     0022050h
;                          equ     0022054h
.equ ti.os.InitUSBDeviceCallback,  0x0022058
.equ ti.os.KillUSBDevice,          0x002205C
.equ ti.os.SetUSBConfiguration,    0x0022060
.equ ti.os.RequestUSBData,         0x0022064
.equ ti.os.StopReceivingUSBData,   0x0022068
;                          equ     002206Ch
;                          equ     0022070h
.equ ti.Mov11ToOP1,                0x0022074
.equ ti.FindFreeArcSpot,           0x0022078
;                          equ     002207Ch
.equ ti.os.SetTimer2,              0x0022080
.equ ti.os.DisableTimer2,          0x0022084
;                          equ     0022088h
;;_ret                     equ 002208Ch
.equ ti.os.GetYDrawLocation,       0x0022090
.equ ti.os.SetYDrawLocation,       0x0022094
.equ ti.RunLocalizeHook,           0x0022098
.equ ti.os.IntSize,                0x002209C
.equ ti.os.ClearStatusBarLow,      0x00220A0
;                          equ     00220A4h
.equ ti.NMIHandler,                0x00220A8
;                          equ     00220ACh
;                          equ     00220B0h
;                          equ     00220B4h
;                          equ     00220B8h
;                          equ     00220BCh
;                          equ     00220C0h
;                          equ     00220C4h
;                          equ     00220C8h
;                          equ     00220CCh
;                          equ     00220D0h
;                          equ     00220D4h
;                          equ     00220D8h
;                          equ     00220DCh
;                          equ     00220E0h
;                          equ     00220E4h
;                          equ     00220E8h
;                          equ     00220ECh
;                          equ     00220F0h
;                          equ     00220F4h
;                          equ     00220F8h
;                          equ     00220FCh
;                          equ     0022100h
;                          equ     0022104h
;                          equ     0022108h
;                          equ     002210Ch
;                          equ     0022110h
;                          equ     0022114h
;                          equ     0022118h
;                          equ     002211Ch
;                          equ     0022120h
;                          equ     0022124h
;                          equ     0022128h
;                          equ     002212Ch
;                          equ     0022130h
;                          equ     0022134h
;                          equ     0022138h
;                          equ     002213Ch
;                          equ     0022140h
;                          equ     0022144h
;                          equ     0022148h
;                          equ     002214Ch
;                          equ     0022150h
;                          equ     0022154h
;                          equ     0022158h
;                          equ     002215Ch
;                          equ     0022160h
.equ ti.os.RToP,                   0x0022164
.equ ti.os.PToR,                   0x0022168
.equ ti.os.ResetEditOpen,          0x002216C
.equ ti.os.FloatToReal,            0x0022170
.equ ti.os.RealToFloat,            0x0022174
.equ ti.os.FontDrawTransText,      0x0022178
.equ ti.os.DelAppVar,              0x002217C
.equ ti.os.GetAppVarData,          0x0022180
.equ ti.os.CreateAppVar,           0x0022184
;                          equ     0022188h
;                          equ     002218Ch
;                          equ     0022190h
;                          equ     0022194h
.equ ti.os.CreateString,           0x0022198
.equ ti.os.GetStringData,          0x002219C
;                          equ     00221A0h
;                          equ     00221A4h
;                          equ     00221A8h
;                          equ     00221ACh
;                          equ     00221B0h
;                          equ     00221B4h
;                          equ     00221B8h
;                          equ     00221BCh
;                          equ     00221C0h
;                          equ     00221C4h
;                          equ     00221C8h
;                          equ     00221CCh
;                          equ     00221D0h
;                          equ     00221D4h
;                          equ     00221D8h
;                          equ     00221DCh
;                          equ     00221E0h
;                          equ     00221E4h
;                          equ     00221E8h
;                          equ     00221ECh
;                          equ     00221F0h
;                          equ     00221F4h
;                          equ     00221F8h
;                          equ     00221FCh
;                          equ     0022200h
;                          equ     0022204h
;                          equ     0022208h
;                          equ     002220Ch
;                          equ     0022210h
;                          equ     0022214h
;                          equ     0022218h
;                          equ     002221Ch
;                          equ     0022220h
;                          equ     0022224h
;                          equ     0022228h
;                          equ     002222Ch
;                          equ     0022230h
;                          equ     0022234h
;                          equ     0022238h
;                          equ     002223Ch
.equ ti.os.CreateEquation,         0x0022240
.equ ti.os.GetEquationData,        0x0022244

; Boot Calls
;-----------------------------------
.equ ti.boot.GetHardwareVers,      0x0000084
.equ ti.boot.GetKeyID,             0x0000088
.equ ti.boot.GetBootVerMinor,      0x000008C
.equ ti.boot.GetBootVerBuild,      0x0000090
.equ ti.dbgout,                    0x0000094
.equ ti._longjmp,                  0x0000098
.equ ti._memchr,                   0x000009C
.equ ti._memcmp,                   0x00000A0
.equ ti._memcpy,                   0x00000A4
.equ ti._memmove,                  0x00000A8
.equ ti._memset,                   0x00000AC
.equ ti._memclear,                 0x00000B0
.equ ti.printf,                    0x00000B4
.equ ti._setjmp,                   0x00000B8
.equ ti.sprintf,                   0x00000BC
.equ ti._strcat,                   0x00000C0
.equ ti._strchr,                   0x00000C4
.equ ti._strcmp,                   0x00000C8
.equ ti._strcpy,                   0x00000CC
.equ ti._strcspn,                  0x00000D0
.equ ti._strlen,                   0x00000D4
.equ ti._strncat,                  0x00000D8
.equ ti._strncmp,                  0x00000DC
.equ ti._strncpy,                  0x00000E0
.equ ti._strpbrk,                  0x00000E4
.equ ti._strrchr,                  0x00000E8
.equ ti._strspn,                   0x00000EC
.equ ti._strstr,                   0x00000F0
.equ ti.strtok,                    0x00000F4
.equ ti.ret,                       0x00000F8
.equ ti._bldiy,                    0x00000FC
.equ ti._bshl,                     0x0000100
.equ ti._bshru,                    0x0000104
.equ ti._bstiy,                    0x0000108
.equ ti._bstix,                    0x000010C
.equ ti._case,                     0x0000110
.equ ti._case16,                   0x0000114
.equ ti._case16D,                  0x0000118
.equ ti._case24,                   0x000011C
.equ ti._case24D,                  0x0000120
.equ ti._case8,                    0x0000124
.equ ti._case8D,                   0x0000128
.equ ti._frameset,                 0x000012C
.equ ti._frameset0,                0x0000130
.equ ti._iand,                     0x0000134
.equ ti._icmpzero,                 0x0000138
.equ ti._idivs,                    0x000013C
.equ ti._idivu,                    0x0000140
.equ ti._idvrmu,                   0x0000144
.equ ti._ildix,                    0x0000148
.equ ti._ildiy,                    0x000014C
.equ ti._imul_b,                   0x0000150
.equ ti._imulu,                    0x0000154
.equ ti._imuls,                    0x0000158
.equ ti._indcall,                  0x000015C
.equ ti._ineg,                     0x0000160
.equ ti._inot,                     0x0000164
.equ ti._ior,                      0x0000168
.equ ti._irems,                    0x000016C
.equ ti._iremu,                    0x0000170
.equ ti._ishl,                     0x0000174
.equ ti._ishl_b,                   0x0000178
.equ ti._ishrs,                    0x000017C
.equ ti._ishrs_b,                  0x0000180
.equ ti._ishru,                    0x0000184
.equ ti._ishru_b,                  0x0000188
.equ ti._istix,                    0x000018C
.equ ti._istiy,                    0x0000190
.equ ti._itol,                     0x0000194
.equ ti._ixor,                     0x0000198
.equ ti._ladd,                     0x000019C
.equ ti._ladd_b,                   0x00001A0
.equ ti._land,                     0x00001A4
.equ ti._lcmps,                    0x00001A8
.equ ti._lcmpu,                    0x00001AC
.equ ti._lcmpzero,                 0x00001B0
.equ ti._ldivs,                    0x00001B4
.equ ti._ldivu,                    0x00001B8
.equ ti._ldvrmu,                   0x00001BC
.equ ti._lldix,                    0x00001C0
.equ ti._lldiy,                    0x00001C4
.equ ti._lmuls,                    0x00001C8
.equ ti._lmulu,                    0x00001CC
.equ ti._lneg,                     0x00001D0
.equ ti._lnot,                     0x00001D4
.equ ti._lor,                      0x00001D8
.equ ti._lrems,                    0x00001DC
.equ ti._lremu,                    0x00001E0
.equ ti._lshl,                     0x00001E4
.equ ti._lshrs,                    0x00001E8
.equ ti._lshru,                    0x00001EC
.equ ti._lstix,                    0x00001F0
.equ ti._lstiy,                    0x00001F4
.equ ti._lsub,                     0x00001F8
.equ ti._lxor,                     0x00001FC
.equ ti._sand,                     0x0000200
.equ ti._scmpzero,                 0x0000204
.equ ti._sdivs,                    0x0000208
.equ ti._sdivu,                    0x000020C
.equ ti._seqcase,                  0x0000210
.equ ti._seqcaseD,                 0x0000214
.equ ti._setflag,                  0x0000218
.equ ti._sldix,                    0x000021C
.equ ti._sldiy,                    0x0000220
.equ ti._smuls,                    0x0000224
.equ ti._smulu,                    0x0000228
.equ ti._sneg,                     0x000022C
.equ ti._snot,                     0x0000230
.equ ti._sor,                      0x0000234
.equ ti._srems,                    0x0000238
.equ ti._sremu,                    0x000023C
.equ ti._sshl,                     0x0000240
.equ ti._sshl_b,                   0x0000244
.equ ti._sshrs,                    0x0000248
.equ ti._sshrs_b,                  0x000024C
.equ ti._sshru,                    0x0000250
.equ ti._sshru_b,                  0x0000254
.equ ti._sstix,                    0x0000258
.equ ti._sstiy,                    0x000025C
.equ ti._stoi,                     0x0000260
.equ ti._stoiu,                    0x0000264
.equ ti._sxor,                     0x0000268
.equ ti._fppack,                   0x000026C
.equ ti._fadd,                     0x0000270
.equ ti._fcmp,                     0x0000274
.equ ti._fdiv,                     0x0000278
.equ ti._ftol,                     0x000027C
;?_ultof                    := 0000280h
.equ ti._ltof,                     0x0000284
.equ ti._fmul,                     0x0000288
.equ ti._fneg,                     0x000028C
.equ ti._fsub,                     0x0000290
.equ ti.FLTMAX,                    0x0000294
.equ ti.sqrtf,                     0x0000298
.equ ti._frbtof,                   0x000029C
.equ ti._frftob,                   0x00002A0
.equ ti._frftoub,                  0x00002A4
.equ ti._frftoi,                   0x00002A8
.equ ti._frftoui,                  0x00002AC
.equ ti._frftos,                   0x00002B0
.equ ti._frftous,                  0x00002B4
.equ ti._fritof,                   0x00002B8
.equ ti._fruitof,                  0x00002BC
.equ ti._frstof,                   0x00002C0
.equ ti._frubtof,                  0x00002C4
.equ ti._frustof,                  0x00002C8
.equ ti.ResetPorts,                0x00002CC
.equ ti.ChkIfOSInterruptAvailable, 0x00002D0
.equ ti.WriteFlashByte,            0x00002D4
.equ ti.EraseFlash,                0x00002D8
.equ ti.EraseFlashSector,          0x00002DC
.equ ti.WriteFlash,                0x00002E0
.equ ti.WriteFlashByteDuplicate,   0x00002E4
.equ ti.WriteFlashA,               0x00002E8
.equ ti.CleanupCertificate,        0x00002EC
.equ ti.ClrHeap,                   0x00002F0
.equ ti.CpyToHeap,                 0x00002F4
.equ ti.ChkHeapTop,                0x00002F8
.equ ti.ExecuteInRAM,              0x00002FC
.equ ti.ExecuteInRAMDup,           0x0000300
.equ ti.ExecuteInRAMDup2,          0x0000304
.equ ti.ChkCertSpace,              0x0000308
.equ ti.GetFieldSizeFromType,      0x000030C
.equ ti.FindFirstCertField,        0x0000310
.equ ti.FindField,                 0x0000314
.equ ti.FindNextField,             0x0000318
.equ ti.GetCertificateEnd,         0x000031C
.equ ti.GetFieldSizeFromType_,     0x0000320
.equ ti.GetFieldFromSize,          0x0000324
.equ ti.NextFieldFromSize,         0x0000328
.equ ti.NextFieldFromType,         0x000032C
.equ ti.GetOffsetToNextField,      0x0000330
.equ ti.WriteFlashUnsafe,          0x0000334
.equ ti.boot.GetCertCalcString,    0x0000338
.equ ti.boot.GetCertCalcID,        0x000033C
.equ ti.GetSerial,                 0x0000340
;                          equ     0000344h
.equ ti.Mult16By8,                 0x0000348
.equ ti.Div16By8,                  0x000034C
.equ ti.Div16By16,                 0x0000350
.equ ti.Div32By16,                 0x0000354
.equ ti.CmpStr,                    0x0000358
.equ ti.boot.Sha256Init,           0x000035C
.equ ti.boot.Sha256Part,           0x0000360
.equ ti.boot.Sha256Hash,           0x0000364
.equ ti.FindAppHeaderSubField,     0x0000368
;                          equ     000036Ch
.equ ti.FindAppHeaderTimestamp,    0x0000370
.equ ti.boot.ClearVRAM,            0x0000374
.equ ti.boot.PutS,                 0x0000378
.equ ti.PutSpinner,                0x000037C
.equ ti.boot.GetLFontPtr,          0x0000380
.equ ti.boot.InitializeHardware,   0x0000384
.equ ti.boot.TurnOffHardware,      0x0000388
.equ ti.MakeColCmd,                0x000038C
.equ ti.boot.NewLine,              0x0000390
.equ ti.PutBootVersion,            0x0000394
.equ ti.DrawSectorProtectionTable, 0x0000398
.equ ti.boot.Set6MHzMode,          0x000039C
.equ ti.boot.Set48MHzMode,         0x00003A0
.equ ti.boot.Set6MHzModeI,         0x00003A4
.equ ti.boot.Set48MHzModeI,        0x00003A8
.equ ti.CheckHardware,             0x00003AC
.equ ti.GetBatteryStatus,          0x00003B0
.equ ti.Delay10ms,                 0x00003B4
.equ ti.DelayTenTimesAms,          0x00003B8
;                          equ     00003BCh
;                          equ     00003C0h
;                          equ     00003C4h
;                          equ     00003C8h
.equ ti.usb_IsBusPowered,          0x00003CC
.equ ti.KeypadScan,                0x00003D0
.equ ti.KeypadScanFull,            0x00003D4
;_ret                      equ 00003D8h
;_ret                      equ 00003DCh
.equ ti.MarkOSInvalid,             0x00003E0
.equ ti.usb_BusPowered,            0x00003E4
.equ ti.usb_SelfPowered,           0x00003E8
;                          equ     00003ECh
;                          equ     00003F0h
;                          equ     00003F4h
;                          equ     00003F8h
.equ ti.usb_SetDeviceB,            0x00003FC
;                          equ     0000400h
.equ ti.usb_DMACXReadNext,         0x0000404
.equ ti.usb_DMACXWrite,            0x0000408
.equ ti.usb_DMACXRead,             0x000040C
.equ ti.usb_DMACXWriteNext,        0x0000410
.equ ti.usb_DMACXWriteCheck,       0x0000414
;                          equ     0000418h
;                          equ     000041Ch
;                          equ     0000420h
;                          equ     0000424h
;                          equ     0000428h
;                          equ     000042Ch
;                          equ     0000430h
;                          equ     0000434h
;                          equ     0000438h
;                          equ     000043Ch
;                          equ     0000440h
;                          equ     0000444h
;                          equ     0000448h
;                          equ     000044Ch
;                          equ     0000450h
;                          equ     0000454h
;                          equ     0000458h
;                          equ     000045Ch
.equ ti.MarkOSValid,               0x0000460
;                          equ     0000464h
;                          equ     0000468h
;                          equ     000046Ch
;                          equ     0000470h
;                          equ     0000474h
;                          equ     0000478h
;                          equ     000047Ch
;                          equ     0000480h
;                          equ     0000484h
;                          equ     0000488h
;                          equ     000048Ch
;                          equ     0000490h
;                          equ     0000494h
;                          equ     0000498h
;                          equ     000049Ch
;                          equ     00004A0h
;                          equ     00004A4h
.equ ti.usb_SetDMAState,           0x00004A8
.equ ti.usb_DMATransfer,           0x00004AC
.equ ti.usb_DMACXTransferWait,     0x00004B0
;                          equ     00004B4h
;                          equ     00004B8h
.equ ti.usb_ResetFIFOS,            0x00004BC
;                          equ     00004C0h
;                          equ     00004C4h
;                          equ     00004C8h
;                          equ     00004CCh
;                          equ     00004D0h
;                          equ     00004D4h
;                          equ     00004D8h
;                          equ     00004DCh
;                          equ     00004E0h
;                          equ     00004E4h
;                          equ     00004E8h
;                          equ     00004ECh
.equ ti.usb_ResetTimer,            0x00004F0
.equ ti.usb_DisableTimer,          0x00004F4
.equ ti.usb_EnableTimer,           0x00004F8
;                          equ     00004FCh
;                          equ     0000500h
;                          equ     0000504h
;                          equ     0000508h
;                          equ     000050Ch
;                          equ     0000510h
;                          equ     0000514h
;                          equ     0000518h
;                          equ     000051Ch
.equ ti.boot.SetTimersControl,     0x0000520
.equ ti.boot.GetTimersControl,     0x0000524
.equ ti.boot.SetTimersInterrupt,   0x0000528
.equ ti.boot.GetTimersInterrupt,   0x000052C
.equ ti.boot.SetTimersInterruptM,  0x0000530
.equ ti.boot.GetTimersInterruptM,  0x0000534
.equ ti.boot.SetTimer1Counter,     0x0000538
.equ ti.boot.GetTimer1Counter,     0x000053C
.equ ti.boot.SetTimer1ReloadValue, 0x0000540
.equ ti.boot.GetTimer1ReloadValue, 0x0000544
.equ ti.boot.SetTimer1MatchValue1, 0x0000548
.equ ti.boot.GetTimer1MatchValue1, 0x000054C
.equ ti.boot.SetTimer1MatchValue2, 0x0000550
.equ ti.boot.GetTimer1MatchValue2, 0x0000554
.equ ti.boot.SetTimer2Counter,     0x0000558
.equ ti.boot.GetTimer2Counter,     0x000055C
.equ ti.boot.SetTimer2ReloadValue, 0x0000560
.equ ti.boot.GetTimer2ReloadValue, 0x0000564
.equ ti.boot.SetTimer2MatchValue1, 0x0000568
.equ ti.boot.GetTimer2MatchValue1, 0x000056C
.equ ti.boot.SetTimer2MatchValue2, 0x0000570
.equ ti.boot.GetTimer2MatchValue2, 0x0000574
.equ ti.CheckIfEmulated,           0x0000578
.equ ti.boot.GetOnInt,             0x000057C
.equ ti.boot.RTCIntHandler,        0x0000580
.equ ti.boot.RTCInitialize,        0x0000584
.equ ti.boot.RTCGetInitStatus,     0x0000588
.equ ti.boot.RTCEnable,            0x000058C
.equ ti.boot.RTCDisable,           0x0000590
.equ ti.boot.RTCSet24Hours,        0x0000594
;                          equ     0000598h
;                          equ     000059Ch
.equ ti.boot.RTCAckAlarmInt,       0x00005A0
;                          equ     00005A4h
.equ ti.boot.RTCWriteTime,         0x00005A8
.equ ti.boot.RTCGetTime12Hour,     0x00005AC
.equ ti.boot.RTCGetTime,           0x00005B0
.equ ti.boot.RTCSetTime,           0x00005B4
.equ ti.boot.RTCGetAlarm,          0x00005B8
.equ ti.boot.RTCSetAlarmSafe,      0x00005BC
.equ ti.boot.RTCCheckAlarmInt,     0x00005C0
.equ ti.boot.RTCSetAlarmInt,       0x00005C4
.equ ti.boot.RTCIsAfternoon,       0x00005C8
.equ ti.boot.RTCGetDay,            0x00005CC
.equ ti.boot.RTCSetAlarmIntSafe,   0x00005D0
.equ ti.boot.RTCSetAlarm,          0x00005D4
.equ ti.boot.RTCEnableInt,         0x00005D8
.equ ti.boot.RTCDisableInt,        0x00005DC
.equ ti.boot.RTCSetCallback,       0x00005E0
.equ ti.boot.RTCResetTimeStruct,   0x00005E4
;                          equ     00005E8h
.equ ti.boot.RTCSetFlags,          0x00005EC
;                          equ     00005F0h
.equ ti.CheckEmulationBit,         0x00005F4
.equ ti.usb_SetDMAAddress,         0x00005F8
;                          equ     00005FCh
.equ ti.boot.SectorsBegin,         0x0000600
;                          equ     0000604h
.equ ti.usb_InEndpointClrStall,    0x0000608
.equ ti.usb_InEndpointSetStall,    0x000060C
.equ ti.usb_InEndpointClrReset,    0x0000610
.equ ti.usb_InEndpointSetReset,    0x0000614
.equ ti.usb_InEndpointSendZlp,     0x0000618
.equ ti.usb_OutEndpointClrStall,   0x000061C
.equ ti.usb_OutEndpointSetStall,   0x0000620
.equ ti.usb_OutEndpointClrReset,   0x0000624
.equ ti.usb_OutEndpointSetReset,   0x0000628
.equ ti.usb_SetFifoMap,            0x000062C
.equ ti.usb_SetEndpointConfig,     0x0000630
.equ ti.usb_ClrEndpointConfig,     0x0000634
.equ ti.usb_SetFifoConfig,         0x0000638
;                          equ     000063Ch

;RAM Equates
;--------------------------------
.equ ti.ramStart,               0x0D00000
.equ ti.flags,                  0x0D00080            ; location of OS Flags (+-80h)
.equ ti.textFlagsLoc,           0x0D00085           ; location of Text Flags
.equ ti.apdFlagsLoc,            0x0D00088            ; location of APD Flags
.equ ti.appFlagsLoc,            0x0D0008D            ; location of App Flags
.equ ti.rclFlagsLoc,            0x0D0008E           ; location of RCLQueue Flags
.equ ti.shiftFlagsLoc,          0x0D00092           ; location of Shifting Flags
.equ ti.mathprintFlagsLoc,      0x0D000C4            ; location of MathPrint Flags

.equ ti.strtokPtr,              0x0D000FF           ; location of pointer used by C strtok
.equ ti.printRoutine,           0x0D00108           ; stores pointer to printing routines (3 scrap)

.equ ti.flashByte,              0x0D00125            ; used for writing to flash

.equ ti.cellOverrideAddr,       0x0D00166
.equ ti.curCell,                        0x0D0016E           ; selected list cell

.equ ti.SmallEditCancelParse,   0x0D001A4

.equ ti.curRowBackup,           0x0D0033C            ; backup of curRow
.equ ti.shiftFlagsLocBackup,    0x0D00358            ; backup of shiftFlagsLoc
.equ ti.appFlagsLocBackup,      0x0D00366            ; backup of appFlagsLoc
.equ ti.penRowBackup,           0x0D003E3            ; backup of penRow
.equ ti.mathprintBackup,                0x0D003E6            ; backup of mathprint flags
.equ ti.winLeftEdgeBackup,      0x0D003D2            ; backup of winLeftEdge
.equ ti.catalogCurrentBackup,   0x0D003D3            ; backup of catalogCurrent
.equ ti.menuCurrentSubBackup,   0x0D003D6            ; backup of menuCurrentSub
.equ ti.menuNumMenusBackup,     0x0D003D8            ; backup of menuNumMenus
.equ ti.menuCurrentBackup,      0x0D003DA            ; backup of menuCurrent
.equ ti.cxCurAppBackup,         0x0D003DD            ; backup of cxCurApp

.equ ti.curUnderBackup,         0x0D003E8            ; backup of curUnder

.equ ti.appData,                        0x0D00429            ; formerly used for OFFSCRPT and ONSCRPT

.equ ti.arcPtrEnd,              0x0D0052F

.equ ti.tempSP,                 0x0D0053F            ; 3 byte scrap

.equ ti.arcInfo,                        0x0D00543
.equ ti.savedArcInfo,           0x0D0055B
.equ ti.appBank_jump,           0x0D00584

.equ ti.kbdScanCode,            0x0D00587            ; scancode returned by GetCSC
.equ ti.kbdLGSC,                        0x0D00588
.equ ti.kbdPSC,                 0x0D00589
.equ ti.kbdWUR,                 0x0D0058A
.equ ti.kbdDebncCnt,            0x0D0058B
.equ ti.kbdKey,                 0x0D0058C
.equ ti.kbdGetKy,               0x0D0058D
.equ ti.keyExtend,              0x0D0058E
.equ ti.brightness,             0x0D0058F
.equ ti.apdSubTimer,            0x0D00590
.equ ti.apdTimer,               0x0D00591
.equ ti.curTime,                        0x0D00594
.equ ti.curRow,                 0x0D00595
.equ ti.curCol,                 0x0D00596
.equ ti.curOffset,              0x0D00598
.equ ti.curUnder,               0x0D00599
.equ ti.curYCol,                        0x0D0059C
.equ ti.curType,                        0x0D0059F
.equ ti.curXRow,                        0x0D005A0
.equ ti.prevDData,              0x0D005A1
.equ ti.lFont_record,           0x0D005A4
.equ ti.sFont_record,           0x0D005C5
.equ ti.tokVarPtr,              0x0D005E9
.equ ti.tokLen,                 0x0D005EC

.equ ti.indicCounter,           0x0D005F6

.equ ti.OP1,                    0x0D005F8
.equ ti.OP1M,                   0x0D005FA
.equ ti.OP2,                    0x0D00603
.equ ti.OP2M,                   0x0D00605
.equ ti.OP2EXT,                 0x0D0060C
.equ ti.OP3,                    0x0D0060E
.equ ti.OP3M,                   0x0D00610
.equ ti.OP4,                    0x0D00619
.equ ti.OP4M,                   0x0D0061B
.equ ti.OP5,                    0x0D00624
.equ ti.OP5M,                   0x0D00626
.equ ti.OP6,                    0x0D0062F
.equ ti.OP6M,                   0x0D00631
.equ ti.OP6EXT,                 0x0D00638

.equ ti.progToEdit,             0x0D0065B
.equ ti.nameBuff,               0x0D00663

.equ ti.equ_edit_save,          0x0D0066E
.equ ti.iMathPtr1,              0x0D0066F
.equ ti.iMathPtr2,              0x0D00672
.equ ti.iMathPtr3,              0x0D00675
.equ ti.iMathPtr4,              0x0D00678
.equ ti.iMathPtr5,              0x0D0067B
.equ ti.asm_data_ptr1,          0x0D0067E
.equ ti.asm_data_ptr2,          0x0D00681

.equ ti.asm_ram,                        0x0D00687

.equ ti.textShadow,             0x0D006C0
.equ ti.textShadCur,            0x0D007C4
.equ ti.textShadTop,            0x0D007C7
.equ ti.textShadAlph,           0x0D007C8
.equ ti.textShadIns,            0x0D007C9
.equ ti.cxMain,                 0x0D007CA
.equ ti.cxPPutAway,             0x0D007CD
.equ ti.cxPutAway,              0x0D007D0
.equ ti.cxReDisp,               0x0D007D3
.equ ti.cxErrorEP,              0x0D007D6
.equ ti.cxSizeWind,             0x0D007D9
.equ ti.cxPage,                 0x0D007DC
.equ ti.cxCurApp,               0x0D007E0
.equ ti.cxPrev,                 0x0D007E2 ; 23 bytes are shadows of cxMain through cxCurApp and appFlags
.equ ti.cxAppReturn,            0x0D007EB

.equ ti.onSP,                   0x0D007FA

.equ ti.promptRow,              0x0D00800
.equ ti.promptCol,              0x0D00801
.equ ti.promptIns,              0x0D00802
.equ ti.promptShift,            0x0D00803
.equ ti.promptRet,              0x0D00804
.equ ti.promptValid,            0x0D00807

.equ ti.varType,                        0x0D00813
.equ ti.varCurrent,             0x0D00814
.equ ti.varClass,               0x0D0081C

.equ ti.catalogCurrent,         0x0D0081D ; word at this location starting with 6007h corresponds to what is highlighted in catalog
.equ ti.catalogCurrentBackupM,  0x0D00820 ; backup of catalogCurrent for menus
.equ ti.menuAppDepth,           0x0D00823
.equ ti.menuCurrent,            0x0D00824
.equ ti.menuCurrentSub,         0x0D00825 ; holds current submenu index
.equ ti.menuSelected,           0x0D00826 ; holds currently selected item in current submenu
.equ ti.menuNumMenus,           0x0D00827 ; holds number of submenus for this menu
.equ ti.menuNumItems,           0x0D00828 ; holds number of items in this submenu
.equ ti.appFlagsBackup,         0x0D00829 ; iy+appFlags backup for menu stuff
.equ ti.cursorFlagsBackup,      0x0D0082A ; iy+cursorFlags backup for menu stuff
.equ ti.curGStyleBackup,                0x0D0082B ; curGStyle backup for menu stuff
.equ ti.graphFlagsBackup,       0x0D0082C ; iy+graphFlags backup for menu stuff

.equ ti.progCurrent,            0x0D0082D
;D0082E	; something used to execute apps with _NewContext0
.equ ti.userMenuSA,             0x0D00838

.equ ti.tempErrorMessage,       0x0D00842

.equ ti.ioPrompt,               0x0D00879
.equ ti.ioFlag,                 0x0D00894
.equ ti.sndRecState,            0x0D00896
.equ ti.ioErrState,             0x0D00897
.equ ti.ioData,                 0x0D008A1

.equ ti.penCol,                 0x0D008D2
.equ ti.penRow,                 0x0D008D5
.equ ti.rclQueue,               0x0D008D6
.equ ti.rclQueueEnd,            0x0D008D9
.equ ti.errNo,                  0x0D008DF
.equ ti.errSP,                  0x0D008E0
.equ ti.errOffset,              0x0D008E3

.equ ti.entryString,            0x0D008E6
.equ ti.entryResult,            0x0D008EA

.equ ti.statVarsOffset,         0x0D0117F
.equ ti.asm_prgm_size,          0x0D0118C
.equ ti.bstCounter,             0x0D0118F
.equ ti.statVars,               0x0D01191
.equ ti.infVars,                        0x0D013A4
.equ ti.infVar1,                        0x0D013AD
.equ ti.infVar2,                        0x0D013B6
.equ ti.infVar3,                        0x0D013BF
.equ ti.infVar4,                        0x0D013C8
.equ ti.infVar5,                        0x0D013D1
.equ ti.infVar6,                        0x0D013DA
.equ ti.infVar7,                        0x0D013E3
.equ ti.infVar8,                        0x0D013EC
.equ ti.infVar9,                        0x0D013F5
.equ ti.infVar10,               0x0D013FE
.equ ti.infVar11,               0x0D01407
.equ ti.infVar12,               0x0D01410
.equ ti.infVar13,               0x0D01419
.equ ti.infVar14,               0x0D01422
.equ ti.infVar15,               0x0D0142B
.equ ti.infVar16,               0x0D01434
.equ ti.infVar17,               0x0D0143D
.equ ti.infVar18,               0x0D01446
.equ ti.infVar19,               0x0D0144F
.equ ti.infVar20,               0x0D01458

.equ ti.curGStyle,              0x0D0146D
.equ ti.curGY,                  0x0D0146E
.equ ti.curGY2,                 0x0D01470
.equ ti.curGX2,                 0x0D01471 ; currently selected equation while graphing
.equ ti.freeSaveY,              0x0D01472
.equ ti.freeSaveX,              0x0D01474

.equ ti.XOffset,                        0x0D014FA
.equ ti.YOffset,                        0x0D014FC
.equ ti.lcdTallP,               0x0D014FD
.equ ti.pixWideP,               0x0D014FE
.equ ti.pixWide_m_1,            0x0D014FF
.equ ti.pixWide_m_2,            0x0D01501
.equ ti.lastEntryStkPtr,                0x0D01508
.equ ti.lastEntryStk,           0x0D0150B
.equ ti.numLastEntries,         0x0D01D0B
.equ ti.currLastEntry,          0x0D01D0C

.equ ti.curPlotNumber,          0x0D01D45

.equ ti.curInc,                 0x0D01D49

.equ ti.uXmin,                  0x0D01D61
.equ ti.uXmax,                  0x0D01D6A
.equ ti.uXscl,                  0x0D01D73
.equ ti.uYmin,                  0x0D01D7C
.equ ti.uYmax,                  0x0D01D85
.equ ti.uYscl,                  0x0D01D8E
.equ ti.uThetMin,               0x0D01D97
.equ ti.uThetMax,               0x0D01DA0
.equ ti.uThetStep,              0x0D01DA9
.equ ti.uTmin,                  0x0D01DB2
.equ ti.uTmax,                  0x0D01DBB
.equ ti.uTStep,                 0x0D01DC4
.equ ti.uPlotStart,             0x0D01DCD
.equ ti.unMax,                  0x0D01DD6
.equ ti.uu0,                    0x0D01DDF
.equ ti.uv0,                    0x0D01DE8
.equ ti.unMin,                  0x0D01DF1
.equ ti.uu02,                   0x0D01DFA
.equ ti.uv02,                   0x0D01E03
.equ ti.uw0,                    0x0D01E0C
.equ ti.uPlotStep,              0x0D01E15
.equ ti.uXres,                  0x0D01E1E
.equ ti.uw02,                   0x0D01E27
.equ ti.Xmin,                   0x0D01E33
.equ ti.Xmax,                   0x0D01E3C
.equ ti.Xscl,                   0x0D01E45
.equ ti.Ymin,                   0x0D01E4E
.equ ti.Ymax,                   0x0D01E57
.equ ti.Yscl,                   0x0D01E60
.equ ti.ThetaMin,               0x0D01E69
.equ ti.ThetaMax,               0x0D01E72
.equ ti.ThetaStep,              0x0D01E7B
.equ ti.TminPar,                        0x0D01E84
.equ ti.TmaxPar,                        0x0D01E8D
.equ ti.Tstep,                  0x0D01E96
.equ ti.PlotStart,              0x0D01E9F
.equ ti.nMax,                   0x0D01EA8
.equ ti.u0,                     0x0D01EB1
.equ ti.v0,                     0x0D01EBA
.equ ti.nMin,                   0x0D01EC3
.equ ti.u02,                    0x0D01ECC
.equ ti.v02,                    0x0D01ED5
.equ ti.w0,                     0x0D01EDE
.equ ti.PlotStep,               0x0D01EE7
.equ ti.XresO,                  0x0D01EF0
.equ ti.w02,                    0x0D01EF9
.equ ti.un1,                    0x0D01F02
.equ ti.un2,                    0x0D01F0B
.equ ti.vn1,                    0x0D01F14
.equ ti.vn2,                    0x0D01F1D
.equ ti.wn1,                    0x0D01F26
.equ ti.wn2,                    0x0D01F2F
.equ ti.fin_N,                  0x0D01F38
.equ ti.fin_I,                  0x0D01F41
.equ ti.fin_PV,                 0x0D01F4A
.equ ti.fin_PMT,                        0x0D01F53
.equ ti.fin_FV,                 0x0D01F5C
.equ ti.fin_PY,                 0x0D01F65
.equ ti.fin_CY,                 0x0D01F6E
.equ ti.cal_N,                  0x0D01F77
.equ ti.cal_I,                  0x0D01F80
.equ ti.cal_PV,                 0x0D01F89
.equ ti.cal_PMT,                        0x0D01F92
.equ ti.cal_FV,                 0x0D01F9B
.equ ti.cal_PY,                 0x0D01FA4
.equ ti.DeltaX,                 0x0D01FAE
.equ ti.DeltaY,                 0x0D01FB7
.equ ti.TraceStep,              0x0D0203D

.equ ti.TblStart,               0x0D02267
.equ ti.DeltaTbl,               0x0D02270
.equ ti.Plot1MarkType,          0x0D0227E
.equ ti.Plot1List1,             0x0D0227F
.equ ti.Plot1List2,             0x0D02284
.equ ti.Plot1FreqList,          0x0D02289
.equ ti.Plot1XYOnOff,           0x0D0228E
.equ ti.Plot1Color,             0x0D0228F

.equ ti.Plot2MarkType,          0x0D02290
.equ ti.Plot2List1,             0x0D02291
.equ ti.Plot2List2,             0x0D02296
.equ ti.Plot2FreqList,          0x0D0229B
.equ ti.Plot2XYOnOff,           0x0D022A0
.equ ti.Plot2Color,             0x0D022A1

.equ ti.Plot3MarkType,          0x0D022A2
.equ ti.Plot3List1,             0x0D022A3
.equ ti.Plot3List2,             0x0D022A8
.equ ti.Plot3FreqList,          0x0D022AD
.equ ti.Plot3XYOnOff,           0x0D022B2
.equ ti.Plot3Color,             0x0D022B3

.equ ti.ES,                     0x0D022BA

.equ ti.seed1,                  0x0D022FC
.equ ti.seed2,                  0x0D02305
.equ ti.basic_prog,             0x0D0230E
.equ ti.begPC,                  0x0D02317
.equ ti.curPC,                  0x0D0231A
.equ ti.endPC,                  0x0D0231D
.equ ti.numArguments,           0x0D02320

.equ ti.cmdShadow,              0x0D0232D
.equ ti.cmdShadCur,             0x0D02431
.equ ti.cmdShadAlph,            0x0D02433
.equ ti.cmdShadIns,             0x0D02435
.equ ti.cmdCursor,              0x0D02434
.equ ti.editTop,                        0x0D02437
.equ ti.editCursor,             0x0D0243A
.equ ti.editTail,               0x0D0243D
.equ ti.editBtm,                        0x0D02440

.equ ti.currListHighlight,      0x0D0244B ; word, this is offset into list for currently-highlighted element in list editor
.equ ti.editSym,                        0x0D0244E ; pointer to vat of variable being edited
.equ ti.editDat,                        0x0D02451 ; pointer to data of variable being edited

.equ ti.currListPageOffset,     0x0D02457
.equ ti.currList,               0x0D02458
.equ ti.listName1,              0x0D02459
.equ ti.listName2,              0x0D0245E
.equ ti.listName3,              0x0D02463
.equ ti.listName4,              0x0D02468
.equ ti.listName5,              0x0D0246D
.equ ti.listName6,              0x0D02472
.equ ti.listName7,              0x0D02477
.equ ti.listName8,              0x0D0247C
.equ ti.listName9,              0x0D02481
.equ ti.listName10,             0x0D02486
.equ ti.listName11,             0x0D0248B
.equ ti.listName12,             0x0D02490
.equ ti.listName13,             0x0D02495
.equ ti.listName14,             0x0D0249A
.equ ti.listName15,             0x0D0249F
.equ ti.listName16,             0x0D024A4
.equ ti.listName17,             0x0D024A9
.equ ti.listName18,             0x0D024AE
.equ ti.listName19,             0x0D024B3
.equ ti.listName20,             0x0D024B8
.equ ti.currGrphStyle,          0x0D024BE
.equ ti.y1LineType,             0x0D024BF
.equ ti.y2LineType,             0x0D024C0
.equ ti.y3LineType,             0x0D024C1
.equ ti.y4LineType,             0x0D024C2
.equ ti.y5LineType,             0x0D024C3
.equ ti.y6LineType,             0x0D024C4
.equ ti.y7LineType,             0x0D024C5
.equ ti.y8LineType,             0x0D024C6
.equ ti.y9LineType,             0x0D024C7
.equ ti.y0LineType,             0x0D024C8
.equ ti.para1LineType,          0x0D024C9
.equ ti.para2LineType,          0x0D024CA
.equ ti.para3LineType,          0x0D024CB
.equ ti.para4LineType,          0x0D024CC
.equ ti.para5LineType,          0x0D024CD
.equ ti.para6LineType,          0x0D024CE
.equ ti.polar1LineType,         0x0D024CF
.equ ti.polar2LineType,         0x0D024D0
.equ ti.polar3LineType,         0x0D024D1
.equ ti.polar4LineType,         0x0D024D2
.equ ti.polar5LineType,         0x0D024D3
.equ ti.polar6LineType,         0x0D024D4
.equ ti.secULineType,           0x0D024D5
.equ ti.secVLineType,           0x0D024D6
.equ ti.secWLineType,           0x0D024D7
.equ ti.y1LineColor,            0x0D024D8
.equ ti.y2LineColor,            0x0D024D9
.equ ti.y3LineColor,            0x0D024DA
.equ ti.y4LineColor,            0x0D024DB
.equ ti.y5LineColor,            0x0D024DC
.equ ti.y6LineColor,            0x0D024DD
.equ ti.y7LineColor,            0x0D024DE
.equ ti.y8LineColor,            0x0D024DF
.equ ti.y9LineColor,            0x0D024E0
.equ ti.y0LineColor,            0x0D024E1
.equ ti.para1LineColor,         0x0D024E2
.equ ti.para2LineColor,         0x0D024E3
.equ ti.para3LineColor,         0x0D024E4
.equ ti.para4LineColor,         0x0D024E5
.equ ti.para5LineColor,         0x0D024E6
.equ ti.para6LineColor,         0x0D024E7
.equ ti.polar1LineColor,                0x0D024E8
.equ ti.polar2LineColor,                0x0D024E9
.equ ti.polar3LineColor,                0x0D024EA
.equ ti.polar4LineColor,                0x0D024EB
.equ ti.polar5LineColor,                0x0D024EC
.equ ti.polar6LineColor,                0x0D024ED
.equ ti.secULineColor,          0x0D024EE
.equ ti.secVLineColor,          0x0D024EF
.equ ti.secWLineColor,          0x0D024F0

.equ ti.winTop,                 0x0D02504
.equ ti.winBtm,                 0x0D02505
.equ ti.winLeftEdge,            0x0D02506
.equ ti.winLeft,                        0x0D02507
.equ ti.winAbove,               0x0D02509
.equ ti.winRow,                 0x0D0250B
.equ ti.winCol,                 0x0D0250D
.equ ti.fmtDigits,              0x0D0250F
.equ ti.fmtString,              0x0D02510
.equ ti.fmtLeft,                        0x0D02561
.equ ti.fmtIndex,               0x0D02564
.equ ti.fmtMatSym,              0x0D02567
.equ ti.fmtMatMem,              0x0D0256A

.equ ti.tSymPtr1,               0x0D0257B
.equ ti.tSymPtr2,               0x0D0257E
.equ ti.chkDelPtr3,             0x0D02581
.equ ti.chkDelPtr4,             0x0D02584

.equ ti.tempMem,                        0x0D02587
.equ ti.FPSbase,                        0x0D0258A
.equ ti.FPS,                    0x0D0258D
.equ ti.OPBase,                 0x0D02590
.equ ti.OPS,                    0x0D02593
.equ ti.pTempCnt,               0x0D02596
.equ ti.cleanTmp,               0x0D02598
.equ ti.pTemp,                  0x0D0259A
.equ ti.progPtr,                        0x0D0259D
.equ ti.newDataPtr,             0x0D025A0
.equ ti.pagedGetPtr,            0x0D025A3 ; 3 byte scrap (unstable)
.equ ti.pagedPutPtr,            0x0D025A6

.equ ti.appErr1,                        0x0D025A9 ; use with _ErrCustom1
.equ ti.appErr2,                        0x0D025B6 ; use with _ErrCustom2

.equ ti.arcPtr,                 0x0D025C8
.equ ti.appRawKeyHandle,                0x0D025CB
.equ ti.customHeight,           0x0D025CE
.equ ti.localLanguage,          0x0D025CF
.equ ti.hookExecTemp,           0x0D025D2
.equ ti.cursorHookPtr,          0x0D025D5
.equ ti.libraryHookPtr,         0x0D025D8
.equ ti.rawKeyHookPtr,          0x0D025DB
.equ ti.getKeyHookPtr,          0x0D025DE
.equ ti.homescreenHookPtr,      0x0D025E1
.equ ti.windowHookPtr,          0x0D025E4
.equ ti.graphHookPtr,           0x0D025E7
.equ ti.yEqualsHookPtr,         0x0D025EA
.equ ti.fontHookPtr,            0x0D025ED
.equ ti.regraphHookPtr,         0x0D025F0
.equ ti.graphicsHookPtr,                0x0D025F3
.equ ti.traceHookPtr,           0x0D025F6
.equ ti.parserHookPtr,          0x0D025F9
.equ ti.appChangeHookPtr,       0x0D025FC
.equ ti.catalog1HookPtr,                0x0D025FF
.equ ti.helpHookPtr,            0x0D02602
.equ ti.cxRedispHookPtr,                0x0D02605
.equ ti.menuHookPtr,            0x0D02608
.equ ti.catalog2HookPtr,                0x0D0260B
.equ ti.tokenHookPtr,           0x0D0260E
.equ ti.localizeHookPtr,                0x0D02611
.equ ti.silentLinkHookPtr,      0x0D02614
.equ ti.USBActivityHookPtr,     0x0D0261A

.equ ti.tempFreeArc,            0x0D02655 ; set after _ArcChk call

.equ ti.textFGColor,            0x0D02688
.equ ti.textBGColor,            0x0D0268A

.equ ti.drawBGColor,            0x0D026AA
.equ ti.drawFGColor,            0x0D026AC
.equ ti.drawColorCode,          0x0D026AE

.equ ti.keyToStrRam,            0x0D026EA

.equ ti.sEditMonSp,             0x0D02706
.equ ti.bpSave,                 0x0D02709

.equ ti.batteryStatus,          0x0D02A86

.equ ti.graphBGColor,           0x0D02A98

.equ ti.errorLineY,             0x0D02A1B
.equ ti.errorLineX,             0x0D02A23

.equ ti.fillRectColor,          0x0D02AC0
.equ ti.statusBarBGColor,       0x0D02ACC

.equ ti.scrapMem,               0x0D02AD7 ; 3 byte scrap (unstable)

.equ ti.TempOP2ToOP6,           0x0D02B39 ; 55 bytes where OP2 to OP6 are temporary saved

.equ ti.gCurYLoc,               0x0D02FD6 ; current y pixel location for C functions

;safeRAM Locations
;---------------------------------------------
;appData		equ 0D00429h ; 256 bytes
;textShadow		equ 0D006C0h ; 260 bytes	; Call _ClrTxtShdw to put spaces in here
;cmdShadow		equ 0D0232Dh ; 260 bytes
.equ ti.pixelShadow,            0x0D031F6 ; 8400 bytes
.equ ti.pixelShadow2,           0x0D052C6 ; 8400 bytes
.equ ti.cmdPixelShadow,         0x0D07396 ; 8400 bytes
.equ ti.plotSScreen,            0x0D09466 ; 21945 bytes	; Set GraphDraw Flag to redraw graph if used
.equ ti.saveSScreen,            0x0D0EA1F ; 21945 bytes	; Set GraphDraw Flag to redraw graph if used
.equ ti.cursorImage,            0x0E30800 ; 1020 bytes

;semiSafeRAM Locations
;---------------------------------------------
.equ ti.usbArea,                        0x0D13FD8 ; 14306 bytes used for usb, probably need to disable timer3/usb interrupts to use
.equ ti.usbHandleKeys,          0x0D14091 ; zero this byte while using usbArea to keep GetCSC from affecting other parts of usbArea
.equ ti.usbInited,              0x0D177B7 ; zero this byte while using usbArea and to reset the usb stack when interrupts are re-enabled
.equ ti.heapBot,                        0x0D1887C ; 1024 bytes used for flash ram routines, rest used rarely
.equ ti.ramCodeTop,             0x0D18C7C
.equ ti.heapTop,                        0x0D1987C
.equ ti.stackBot,               0x0D1987E
.equ ti.stackTop,               0x0D1A87E

;RAM Equates Continued
;---------------------------------------------
.equ ti.userMem,                        0x0D1A881
.equ ti.symTable,               0x0D3FFFF
.equ ti.vRam,                   0x0D40000
.equ ti.vRamEnd,                        0x0D65800

;Ports
;--------------------------------
.equ ti.pCpuSpeed,              0x0001
.equ ti.pHardwareId,            0x0003

;SHA256 Ports
;--------------------------------
.equ ti.pShaRange,              0x02000
.equ ti.mpShaRange,             0x0E10000

.equ ti.shaCtrl,                        0x00 ; 1 byte
.equ ti.pShaCtrl,               ti.pShaRange + ti.shaCtrl
.equ ti.mpShaCtrl,              ti.mpShaRange + ti.shaCtrl

.equ ti.shaData,                        0x10 ; 40h bytes
.equ ti.pShaData,               ti.pShaRange + ti.shaData
.equ ti.mpShaData,              ti.mpShaRange + ti.shaData

.equ ti.shaState,               0x60 ; 20h bytes
.equ ti.pShaState,              ti.pShaRange + ti.shaState
.equ ti.mpShaState,             ti.mpShaRange + ti.shaState

;USB Ports
;--------------------------------
.equ ti.pUsbRange,              0x03000
.equ ti.mpUsbRange,             0x0E20000

.equ ti.usbCapLen,              0x0000
.equ ti.pUsbCapLen,             ti.pUsbRange + ti.usbCapLen
.equ ti.mpUsbCapLen,            ti.mpUsbRange + ti.usbCapLen

.equ ti.usbHciVer,              0x0002
.equ ti.pUsbHciVer,             ti.pUsbRange + ti.usbHciVer
.equ ti.mpUsbHciVer,            ti.mpUsbRange + ti.usbHciVer

.equ ti.usbHcsParams,           0x0004
.equ ti.pUsbHcsParams,          ti.pUsbRange + ti.usbHcsParams
.equ ti.mpUsbHcsParams,         ti.mpUsbRange + ti.usbHcsParams
.equ ti.bUsbNumPorts,           0
.equ ti.bmUsbNumPorts,          0x0F << ti.bUsbNumPorts
.equ ti.bUsbPortPwrCtrl,                4
.equ ti.bmUsbPortPwrCtrl,       1 << ti.bUsbPortPwrCtrl
.equ ti.bUsbPortRoutRules,      7
.equ ti.bmUsbPortRoutRules,     1 << ti.bUsbPortRoutRules
.equ ti.bUsbNumPortsPerCC,      8
.equ ti.bmUsbNumPortsPerCC,     0x0F << ti.bUsbNumPortsPerCC
.equ ti.bUsbNumCC,              12
.equ ti.bmUsbNumCC,             0x0F << ti.bUsbNumCC
.equ ti.bUsbPortIndics,         16
.equ ti.bmUsbPortIndics,                1 << ti.bUsbPortIndics
.equ ti.bUsbDebugPortNum,       20
.equ ti.bmUsbDebugPortNum,      0x0F << ti.bUsbDebugPortNum

.equ ti.usbHccParams,           0x0008
.equ ti.pUsbHccParams,          ti.pUsbRange + ti.usbHccParams
.equ ti.mpUsbHccParams,         ti.mpUsbRange + ti.usbHccParams
.equ ti.bUsb64Bit,              0
.equ ti.bmUsb64Bit,             1 << ti.bUsb64Bit
.equ ti.bUsbProgFrameList,      1
.equ ti.bmUsbProgFrameList,     1 << ti.bUsbProgFrameList
.equ ti.bUsbAsyncSchedParkCap,  2
.equ ti.bmUsbAsyncSchedParkCap, 1 << ti.bUsbAsyncSchedParkCap
.equ ti.bUsbIsochSchedThresh,   4
.equ ti.bmUsbIsochSchedThresh,  0x0F << ti.bUsbIsochSchedThresh
.equ ti.bUsbEhciExtendCap,      8
.equ ti.bmUsbEhciExtendCap,     0x0FF << ti.bUsbEhciExtendCap

.equ ti.usbHcspPortRout,                0x000C
.equ ti.pUsbHcspPortRout,       ti.pUsbRange + ti.usbHcspPortRout
.equ ti.mpUsbHcspPortRout,      ti.mpUsbRange + ti.usbHcspPortRout

.equ ti.usbCmd,                 0x0010
.equ ti.pUsbCmd,                        ti.pUsbRange + ti.usbCmd
.equ ti.mpUsbCmd,               ti.mpUsbRange + ti.usbCmd
.equ ti.bUsbRunStop,            0
.equ ti.bmUsbRunStop,           1 << ti.bUsbRunStop
.equ ti.bUsbHcReset,            1
.equ ti.bmUsbHcReset,           1 << ti.bUsbHcReset
.equ ti.bUsbFrameListSize,      2
.equ ti.bmUsbFrameListSize,     3 << ti.bUsbFrameListSize
.equ ti.bUsbPeriodicSchedEn,    4
.equ ti.bmUsbPeriodicSchedEn,   1 << ti.bUsbPeriodicSchedEn
.equ ti.bUsbAsyncSchedEn,       5
.equ ti.bmUsbAsyncSchedEn,      1 << ti.bUsbAsyncSchedEn
.equ ti.bUsbIntAsyncAdvDrbl,    6
.equ ti.bmUsbIntAsyncAdvDrbl,   1 << ti.bUsbIntAsyncAdvDrbl
.equ ti.bUsbLightHcReset,       7
.equ ti.bmUsbLightHcReset,      1 << ti.bUsbLightHcReset
.equ ti.bUsbAsyncSchedParkCnt,  8
.equ ti.bmUsbAsyncSchedParkCnt, 3 << ti.bUsbAsyncSchedParkCnt
.equ ti.bUsbAsyncSchedParkEn,   11
.equ ti.bmUsbAsyncSchedParkEn,  1 << ti.bUsbAsyncSchedParkEn
.equ ti.bUsbIntThreshCtrl,      16
.equ ti.bmUsbIntThreshCtrl,     0x0FF << ti.bUsbIntThreshCtrl

.equ ti.usbSts,                 0x0014
.equ ti.pUsbSts,                        ti.pUsbRange + ti.usbSts
.equ ti.mpUsbSts,               ti.mpUsbRange + ti.usbSts
.equ ti.usbIntEn,               0x0018
.equ ti.pUsbIntEn,              ti.pUsbRange + ti.usbIntEn
.equ ti.mpUsbIntEn,             ti.mpUsbRange + ti.usbIntEn
.equ ti.bUsbInt,                        0
.equ ti.bmUsbInt,               1 << ti.bUsbInt
.equ ti.bUsbIntErr,             1
.equ ti.bmUsbIntErr,            1 << ti.bUsbIntErr
.equ ti.bUsbIntPortChgDetect,   2
.equ ti.bmUsbIntPortChgDetect,  1 << ti.bUsbIntPortChgDetect
.equ ti.bUsbIntFrameListOver,   3
.equ ti.bmUsbIntFrameListOver,  1 << ti.bUsbIntFrameListOver
.equ ti.bUsbIntHostSysErr,      4
.equ ti.bmUsbIntHostSysErr,     1 << ti.bUsbIntHostSysErr
.equ ti.bUsbIntAsyncAdv,                5
.equ ti.bmUsbIntAsyncAdv,       1 << ti.bUsbIntAsyncAdv
.equ ti.bUsbHcHalted,           12
.equ ti.bmUsbHcHalted,          1 << ti.bUsbHcHalted
.equ ti.bUsbReclamation,                13
.equ ti.bmUsbReclamation,       1 << ti.bUsbReclamation
.equ ti.bUsbPeriodicSchedSts,   14
.equ ti.bmUsbPeriodicSchedSts,  1 << ti.bUsbPeriodicSchedSts
.equ ti.bUsbAsyncSchedSts,      15
.equ ti.bmUsbAsyncSchedSts,     1 << ti.bUsbAsyncSchedSts

.equ ti.usbFrameIdx,            0x001C
.equ ti.pUsbFrameIdx,           ti.pUsbRange + ti.usbFrameIdx
.equ ti.mpUsbFrameIdx,          ti.mpUsbRange + ti.usbFrameIdx
.equ ti.bUsbFrameIdx,           0
.equ ti.bmUsbFrameIdx,          0x03FFF << ti.bUsbFrameIdx

.equ ti.usbCtrlDsSeg,           0x0020
.equ ti.pUsbCtrlDsSeg,          ti.pUsbRange + ti.usbCtrlDsSeg
.equ ti.mpUsbCtrlDsSeg,         ti.mpUsbRange + ti.usbCtrlDsSeg

.equ ti.usbPeriodicListBase,    0x0024
.equ ti.pUsbPeriodicListBase,   ti.pUsbRange + ti.usbPeriodicListBase
.equ ti.mpUsbPeriodicListBase,  ti.mpUsbRange + ti.usbPeriodicListBase
.equ ti.bUsbPeriodicListBase,   12
.equ ti.bmUsbPeriodicListBase,  0x0FFFFF << ti.bUsbPeriodicListBase

.equ ti.usbAsyncListAddr,       0x0028
.equ ti.pUsbAsyncListAddr,      ti.pUsbRange + ti.usbAsyncListAddr
.equ ti.mpUsbAsyncListAddr,     ti.mpUsbRange + ti.usbAsyncListAddr
.equ ti.bUsbAsyncListAddr,      5
.equ ti.bmUsbAsyncListAddr,     0x07FFFFFF << ti.bUsbAsyncListAddr

.equ ti.usbPortStsCtrl,         0x0030
.equ ti.pUsbPortStsCtrl,                ti.pUsbRange + ti.usbPortStsCtrl
.equ ti.mpUsbPortStsCtrl,       ti.mpUsbRange + ti.usbPortStsCtrl
.equ ti.bUsbCurConnSts,         0
.equ ti.bmUsbCurConnSts,                1 << ti.bUsbCurConnSts
.equ ti.bUsbConnStsChg,         1
.equ ti.bmUsbConnStsChg,                1 << ti.bUsbConnStsChg
.equ ti.bUsbPortEn,             2
.equ ti.bmUsbPortEn,            1 << ti.bUsbPortEn
.equ ti.bUsbPortEnChg,          3
.equ ti.bmUsbPortEnChg,         1 << ti.bUsbPortEnChg
.equ ti.bUsbOvercurrActive,     4
.equ ti.bmUsbOvercurrActive,    1 << ti.bUsbOvercurrActive
.equ ti.bUsbOvercurrChg,                5
.equ ti.bmUsbOvercurrChg,       1 << ti.bUsbOvercurrChg
.equ ti.bUsbForcePortResume,    6
.equ ti.bmUsbForcePortResume,   1 << ti.bUsbForcePortResume
.equ ti.bUsbPortSuspended,      7
.equ ti.bmUsbPortSuspended,     1 << ti.bUsbPortSuspended
.equ ti.bUsbPortReset,          8
.equ ti.bmUsbPortReset,         1 << ti.bUsbPortReset
.equ ti.bUsbLineSts,            10
.equ ti.bmUsbLineSts,           3 << ti.bUsbLineSts
.equ ti.bUsbPortPwr,            12
.equ ti.bmUsbPortPwr,           1 << ti.bUsbPortPwr
.equ ti.bUsbPortOwner,          13
.equ ti.bmUsbPortOwner,         1 << ti.bUsbPortOwner
.equ ti.bUsbPortIndicCtrl,      14
.equ ti.bmUsbPortIndicCtrl,     3 << ti.bUsbPortIndicCtrl
.equ ti.bUsbPortTestCtrl,       16
.equ ti.bmUsbPortTestCtrl,      0x0F << ti.bUsbPortTestCtrl
.equ ti.bUsbWakeConnEn,         20
.equ ti.bmUsbWakeConnEn,                1 << ti.bUsbWakeConnEn
.equ ti.bUsbWakeDiscEn,         21
.equ ti.bmUsbWakeDiscEn,                1 << ti.bUsbWakeDiscEn
.equ ti.bUsbWakeOvercurrEn,     22
.equ ti.bmUsbWakeOvercurrEn,    1 << ti.bUsbWakeOvercurrEn

.equ ti.usbMisc,                        0x0040
.equ ti.pUsbMisc,               ti.pUsbRange + ti.usbMisc
.equ ti.mpUsbMisc,              ti.mpUsbRange + ti.usbMisc
.equ ti.bUsbAsyncSchedSleepTmr, 0
.equ ti.bmUsbAsyncSchedSleepTmr,        3 << ti.bUsbAsyncSchedSleepTmr
.equ ti.bUsbEof1Timing,         2
.equ ti.bmUsbEof1Timing,                3 << ti.bUsbEof1Timing
.equ ti.bUsbEof2Timing,         4
.equ ti.bmUsbEof2Timing,                3 << ti.bUsbEof2Timing
.equ ti.bUsbHostSuspend,                6
.equ ti.bmUsbHostSuspend,       1 << ti.bUsbHostSuspend

.equ ti.usbOtgCsr,              0x0080
.equ ti.pUsbOtgCsr,             ti.pUsbRange + ti.usbOtgCsr
.equ ti.mpUsbOtgCsr,            ti.mpUsbRange + ti.usbOtgCsr
.equ ti.bUsbBBusReq,            0
.equ ti.bmUsbBBusReq,           1 << ti.bUsbBBusReq
.equ ti.bUsbBHnp,               1
.equ ti.bmUsbBHnp,              1 << ti.bUsbBHnp
.equ ti.bUsbBVbusDisc,          2
.equ ti.bmUsbBVbusDisc,         1 << ti.bUsbBVbusDisc
.equ ti.bUsbABusReq,            4
.equ ti.bmUsbABusReq,           1 << ti.bUsbABusReq
.equ ti.bUsbABusDrop,           5
.equ ti.bmUsbABusDrop,          1 << ti.bUsbABusDrop
.equ ti.bUsbAHnp,               6
.equ ti.bmUsbAHnp,              1 << ti.bUsbAHnp
.equ ti.bUsbASrpEn,             7
.equ ti.bmUsbASrpEn,            1 << ti.bUsbASrpEn
.equ ti.bUsbASrpMode,           8
.equ ti.usbASrpModeVbus,                0 << ti.bUsbASrpMode
.equ ti.usbASrpModeData,                1 << ti.bUsbASrpMode
.equ ti.bmUsbASrpMode,          1 << ti.bUsbASrpMode
.equ ti.bUsbIdFilt,             9
.equ ti.usbIdFiltShort,         0 << ti.bUsbIdFilt
.equ ti.usbIdFiltLong,          1 << ti.bUsbIdFilt
.equ ti.bmUsbIdFilt,            1 << ti.bUsbIdFilt
.equ ti.bUsbVbusFilt,           10
.equ ti.usbVbusFiltShort,       0 << ti.bUsbVbusFilt
.equ ti.usbVbusFiltLong,                1 << ti.bUsbVbusFilt
.equ ti.bmUsbVbusFilt,          1 << ti.bUsbVbusFilt
.equ ti.bUsbHdiscFilt,          11
.equ ti.usbHdiscFiltShort,      0 << ti.bUsbHdiscFilt
.equ ti.usbHdiscFiltLong,       1 << ti.bUsbHdiscFilt
.equ ti.bmUsbHdiscFilt,         1 << ti.bUsbHdiscFilt
.equ ti.bUsbBSessEnd,           16
.equ ti.bmUsbBSessEnd,          1 << ti.bUsbBSessEnd
.equ ti.bUsbBSessVld,           17
.equ ti.bmUsbBSessVld,          1 << ti.bUsbBSessVld
.equ ti.bUsbASessVld,           18
.equ ti.bmUsbASessVld,          1 << ti.bUsbASessVld
.equ ti.bUsbAVbusVld,           19
.equ ti.bmUsbAVbusVld,          1 << ti.bUsbAVbusVld
.equ ti.bUsbRole,               20
.equ ti.usbRoleHost,            0 << ti.bUsbRole
.equ ti.usbRoleDev,             1 << ti.bUsbRole
.equ ti.bmUsbRole,              1 << ti.bUsbRole
.equ ti.bUsbId,                 21
.equ ti.usbIdA,                 0 << ti.bUsbId
.equ ti.usbIdB,                 1 << ti.bUsbId
.equ ti.bmUsbId,                        1 << ti.bUsbId
.equ ti.bUsbSpd,                        22
.equ ti.usbSpdFull,             0 << ti.bUsbSpd
.equ ti.usbSpdLow,              1 << ti.bUsbSpd
.equ ti.usbSpdHigh,             2 << ti.bUsbSpd
.equ ti.bmUsbSpd,               3 << ti.bUsbSpd

.equ ti.usbOtgIsr,              0x0084
.equ ti.pUsbOtgIsr,             ti.pUsbRange + ti.usbOtgIsr
.equ ti.mpUsbOtgIsr,            ti.mpUsbRange + ti.usbOtgIsr
.equ ti.usbOtgIer,              0x0088
.equ ti.pUsbOtgIer,             ti.pUsbRange + ti.usbOtgIer
.equ ti.mpUsbOtgIer,            ti.mpUsbRange + ti.usbOtgIer
.equ ti.bUsbIntBSrpComplete,    0
.equ ti.bmUsbIntBSrpComplete,   1 << ti.bUsbIntBSrpComplete
.equ ti.bUsbIntASrpDetect,      4
.equ ti.bmUsbIntASrpDetect,     1 << ti.bUsbIntASrpDetect
.equ ti.bUsbIntAVbusErr,                5
.equ ti.bmUsbIntAVbusErr,       1 << ti.bUsbIntAVbusErr
.equ ti.bUsbIntBSessEnd,                6
.equ ti.bmUsbIntBSessEnd,       1 << ti.bUsbIntBSessEnd
.equ ti.bUsbIntRoleChg,         8
.equ ti.bmUsbIntRoleChg,                1 << ti.bUsbIntRoleChg
.equ ti.bUsbIntIdChg,           9
.equ ti.bmUsbIntIdChg,          1 << ti.bUsbIntIdChg
.equ ti.bUsbIntOvercurr,                10
.equ ti.bmUsbIntOvercurr,       1 << ti.bUsbIntOvercurr
.equ ti.bUsbIntBPlugRemoved,    11
.equ ti.bmUsbIntBPlugRemoved,   1 << ti.bUsbIntBPlugRemoved
.equ ti.bUsbIntAPlugRemoved,    12
.equ ti.bmUsbIntAPlugRemoved,   1 << ti.bUsbIntAPlugRemoved

.equ ti.usbIsr,                 0x00C0
.equ ti.pUsbIsr,                        ti.pUsbRange + ti.usbIsr
.equ ti.mpUsbIsr,               ti.mpUsbRange + ti.usbIsr
.equ ti.usbImr,                 0x00C4
.equ ti.pUsbImr,                        ti.pUsbRange + ti.usbImr
.equ ti.mpUsbImr,               ti.mpUsbRange + ti.usbImr
.equ ti.bUsbIntDev,             0
.equ ti.bmUsbIntDev,            1 << ti.bUsbIntDev
.equ ti.bUsbIntOtg,             1
.equ ti.bmUsbIntOtg,            1 << ti.bUsbIntOtg
.equ ti.bUsbIntHost,            2
.equ ti.bmUsbIntHost,           1 << ti.bUsbIntHost
.equ ti.bUsbIntLevel,           3
.equ ti.usbIntLevelLow,         0 << ti.bUsbIntLevel
.equ ti.usbIntLevelHigh,                1 << ti.bUsbIntLevel
.equ ti.bmUsbIntLevel,          1 << ti.bUsbIntLevel

.equ ti.usbDevCtrl,             0x0100
.equ ti.pUsbDevCtrl,            ti.pUsbRange + ti.usbDevCtrl
.equ ti.mpUsbDevCtrl,           ti.mpUsbRange + ti.usbDevCtrl
.equ ti.bUsbRemoteWake,         0
.equ ti.bmUsbRemoteWake,                1 << ti.bUsbRemoteWake
.equ ti.bUsbHalfSpd,            1
.equ ti.bmUsbHalfSpd,           1 << ti.bUsbHalfSpd
.equ ti.bUsbGirqEn,             2
.equ ti.bmUsbGirqEn,            1 << ti.bUsbGirqEn
.equ ti.bUsbDevSuspend,         3
.equ ti.bmUsbDevSuspend,                1 << ti.bUsbDevSuspend
.equ ti.bUsbDevReset,           4
.equ ti.bmUsbDevReset,          1 << ti.bUsbDevReset
.equ ti.bUsbDevEn,              5
.equ ti.bmUsbDevEn,             1 << ti.bUsbDevEn
.equ ti.bUsbDevSpd,             6
.equ ti.bmUsbDevSpd,            1 << ti.bUsbDevSpd
.equ ti.bUsbDevForceFullSpd,    9
.equ ti.bmUsbDevForceFullSpd,   1 << ti.bUsbDevForceFullSpd

.equ ti.usbDevAddr,             0x0104
.equ ti.pUsbDevAddr,            ti.pUsbRange + ti.usbDevAddr
.equ ti.mpUsbDevAddr,           ti.mpUsbRange + ti.usbDevAddr
.equ ti.bUsbDevAddr,            0
.equ ti.bmUsbDevAddr,           0x07F << ti.bUsbDevAddr
.equ ti.bUsbDevConf,            7
.equ ti.bmUsbDevConf,           1 << ti.bUsbDevConf

.equ ti.usbDevTest,             0x0108
.equ ti.pUsbDevTest,            ti.pUsbRange + ti.usbDevTest
.equ ti.mpUsbDevTest,           ti.mpUsbRange + ti.usbDevTest
.equ ti.bUsbTstClrFifo,         0
.equ ti.bmUsbTstClrFifo,                1 << ti.bUsbTstClrFifo
.equ ti.bUsbTstCxLp,            1
.equ ti.bmUsbTstCxLp,           1 << ti.bUsbTstCxLp
.equ ti.bUsbTstClrEa,           2
.equ ti.bmUsbTstClrEa,          1 << ti.bUsbTstClrEa
.equ ti.bUsbTstNoCrc,           3
.equ ti.bmUsbTstNoCrc,          1 << ti.bUsbTstNoCrc
.equ ti.bUsbTstNoTs,            4
.equ ti.bmUsbTstNoTs,           1 << ti.bUsbTstNoTs
.equ ti.bUsbTstMode,            5
.equ ti.bmUsbTstMode,           1 << ti.bUsbTstMode
.equ ti.bUsbNoSof,              6
.equ ti.bmUsbNoSof,             1 << ti.bUsbNoSof

.equ ti.usbSofFrNum,            0x010C
.equ ti.pUsbSofFrNum,           ti.pUsbRange + ti.usbSofFrNum
.equ ti.mpUsbSofFrNum,          ti.mpUsbRange + ti.usbSofFrNum
.equ ti.bUsbSofFrNum,           0
.equ ti.bmUsbSofFrNum,          0x07FF << ti.bUsbSofFrNum
.equ ti.bUsbSofUFrNum,          11
.equ ti.bmUsbSofUFrNum,         7 << ti.bUsbSofUFrNum

.equ ti.usbSofMtr,              0x0110
.equ ti.pUsbSofMtr,             ti.pUsbRange + ti.usbSofMtr
.equ ti.mpUsbSofMtr,            ti.mpUsbRange + ti.usbSofMtr
.equ ti.bUsbSofMtrTmr,          0
.equ ti.bmUsbSofMtrTmr,         0x0FFFF << ti.bUsbSofMtrTmr

.equ ti.usbPhyTmsr,             0x0114
.equ ti.pUsbPhyTmsr,            ti.pUsbRange + ti.usbPhyTmsr
.equ ti.mpUsbPhyTmsr,           ti.mpUsbRange + ti.usbPhyTmsr
.equ ti.bUsbUnplug,             0
.equ ti.bmUsbUnplug,            1 << ti.bUsbUnplug
.equ ti.bUsbTstJState,          1
.equ ti.bmUsbTstJState,         1 << ti.bUsbTstJState
.equ ti.bUsbTstKState,          2
.equ ti.bmUsbTstKState,         1 << ti.bUsbTstKState
.equ ti.bUsbTstSe0Nak,          3
.equ ti.bmUsbTstSe0Nak,         1 << ti.bUsbTstSe0Nak
.equ ti.bUsbTstPkt,             4
.equ ti.bmUsbTstPkt,            1 << ti.bUsbTstPkt

.equ ti.usbCxsr,                        0x011C
.equ ti.pUsbCxsr,               ti.pUsbRange + ti.usbCxsr
.equ ti.mpUsbCxsr,              ti.mpUsbRange + ti.usbCxsr

.equ ti.usbCxFifo,              0x0120
.equ ti.pUsbCxFifo,             ti.pUsbRange + ti.usbCxFifo
.equ ti.mpUsbCxFifo,            ti.mpUsbRange + ti.usbCxFifo
.equ ti.bCxFifoFin,             0
.equ ti.bmCxFifoFin,            1 << ti.bCxFifoFin
.equ ti.bTstPktFin,             1
.equ ti.bmTstPktFin,            1 << ti.bTstPktFin
.equ ti.bCxFifoStall,           2
.equ ti.bmCxFifoStall,          1 << ti.bCxFifoStall
.equ ti.bCxFifoClr,             3
.equ ti.bmCxFifoClr,            1 << ti.bCxFifoClr
.equ ti.bCxFifoFull,            4
.equ ti.bmCxFifoFull,           1 << ti.bCxFifoFull
.equ ti.bCxFifoEmpty,           5
.equ ti.bmCxFifoEmpty,          1 << ti.bCxFifoEmpty
.equ ti.bFifo0Empty,            8
.equ ti.bmFifo0Empty,           1 << ti.bFifo0Empty
.equ ti.bFifo1Empty,            9
.equ ti.bmFifo1Empty,           1 << ti.bFifo1Empty
.equ ti.bFifo2Empty,            10
.equ ti.bmFifo2Empty,           1 << ti.bFifo2Empty
.equ ti.bFifo3Empty,            11
.equ ti.bmFifo3Empty,           1 << ti.bFifo3Empty
.equ ti.bFifoEmpty,             8
.equ ti.bmFifoEmpty,            0x0F << ti.bFifoEmpty

.equ ti.usbCxFifoBytes,         0x0123
.equ ti.pUsbCxFifoBytes,                ti.pUsbRange + ti.usbCxFifoBytes
.equ ti.mpUsbCxFifoBytes,       ti.mpUsbRange + ti.usbCxFifoBytes
.equ ti.bUsbCxFifoBytes,                0
.equ ti.bmUsbCxFifoBytes,       0x07F

.equ ti.usbIdle,                        0x0124
.equ ti.pUsbIdle,               ti.pUsbRange + ti.usbIdle
.equ ti.mpUsbIdle,              ti.mpUsbRange + ti.usbIdle
.equ ti.bUsbIdleMs,             0
.equ ti.bmUsbIdleMs,            7 << ti.bUsbIdleMs

.equ ti.usbGimr,                        0x0130
.equ ti.pUsbGimr,               ti.pUsbRange + ti.usbGimr
.equ ti.mpUsbGimr,              ti.mpUsbRange + ti.usbGimr
.equ ti.usbGisr,                        0x0140
.equ ti.pUsbGisr,               ti.pUsbRange + ti.usbGisr
.equ ti.mpUsbGisr,              ti.mpUsbRange + ti.usbGisr
.equ ti.bUsbDevIntCx,           0
.equ ti.bmUsbDevIntCx,          1 << ti.bUsbDevIntCx
.equ ti.bUsbDevIntFifo,         1
.equ ti.bmUsbDevIntFifo,                1 << ti.bUsbDevIntFifo
.equ ti.bUsbDevIntDev,          2
.equ ti.bmUsbDevIntDev,         1 << ti.bUsbDevIntDev

.equ ti.usbCxImr,               0x0134
.equ ti.pUsbCxImr,              ti.pUsbRange + ti.usbCxImr
.equ ti.mpUsbCxImr,             ti.mpUsbRange + ti.usbCxImr
.equ ti.usbCxIsr,               0x0144
.equ ti.pUsbCxIsr,              ti.pUsbRange + ti.usbCxIsr
.equ ti.mpUsbCxIsr,             ti.mpUsbRange + ti.usbCxIsr
.equ ti.bUsbIntCxSetup,         0
.equ ti.bmUsbIntCxSetup,                1 << ti.bUsbIntCxSetup
.equ ti.bUsbIntCxIn,            1
.equ ti.bmUsbIntCxIn,           1 << ti.bUsbIntCxIn
.equ ti.bUsbIntCxOut,           2
.equ ti.bmUsbIntCxOut,          1 << ti.bUsbIntCxOut
.equ ti.bUsbIntCxEnd,           3
.equ ti.bmUsbIntCxEnd,          1 << ti.bUsbIntCxEnd
.equ ti.bUsbIntCxErr,           4
.equ ti.bmUsbIntCxErr,          1 << ti.bUsbIntCxErr
.equ ti.bUsbIntCxAbort,         5
.equ ti.bmUsbIntCxAbort,                1 << ti.bUsbIntCxAbort
.equ ti.bUsbIntCx,              0
.equ ti.bmUsbIntCx,             0x01F << ti.bUsbIntCx

.equ ti.usbFifoRxImr,           0x0138
.equ ti.pUsbFifoRxImr,          ti.pUsbRange + ti.usbFifoRxImr
.equ ti.mpUsbFifoRxImr,         ti.mpUsbRange + ti.usbFifoRxImr
.equ ti.usbFifoRxIsr,           0x0148
.equ ti.pUsbFifoRxIsr,          ti.pUsbRange + ti.usbFifoRxIsr
.equ ti.mpUsbFifoRxIsr,         ti.mpUsbRange + ti.usbFifoRxIsr
.equ ti.bUsbIntFifo0Out,                0
.equ ti.bmUsbIntFifo0Out,       1 << ti.bUsbIntFifo0Out
.equ ti.bUsbIntFifo0Spk,                1
.equ ti.bmUsbIntFifo0Spk,       1 << ti.bUsbIntFifo0Spk
.equ ti.bUsbIntFifo1Out,                2
.equ ti.bmUsbIntFifo1Out,       1 << ti.bUsbIntFifo1Out
.equ ti.bUsbIntFifo1Spk,                3
.equ ti.bmUsbIntFifo1Spk,       1 << ti.bUsbIntFifo1Spk
.equ ti.bUsbIntFifo2Out,                4
.equ ti.bmUsbIntFifo2Out,       1 << ti.bUsbIntFifo2Out
.equ ti.bUsbIntFifo2Spk,                5
.equ ti.bmUsbIntFifo2Spk,       1 << ti.bUsbIntFifo2Spk
.equ ti.bUsbIntFifo3Out,                6
.equ ti.bmUsbIntFifo3Out,       1 << ti.bUsbIntFifo3Out
.equ ti.bUsbIntFifo3Spk,                7
.equ ti.bmUsbIntFifo3Spk,       1 << ti.bUsbIntFifo3Spk
.equ ti.bUsbFifoRxInts,         0
.equ ti.bmUsbFifoRxInts,                0x0FF << ti.bUsbFifoRxInts

.equ ti.usbFifoTxImr,           0x013A
.equ ti.pUsbFifoTxImr,          ti.pUsbRange + ti.usbFifoTxImr
.equ ti.mpUsbFifoTxImr,         ti.mpUsbRange + ti.usbFifoTxImr
.equ ti.usbFifoTxIsr,           0x014A
.equ ti.pUsbFifoTxIsr,          ti.pUsbRange + ti.usbFifoTxIsr
.equ ti.mpUsbFifoTxIsr,         ti.mpUsbRange + ti.usbFifoTxIsr
.equ ti.bUsbIntFifo0In,         0
.equ ti.bmUsbIntFifo0In,                1 << ti.bUsbIntFifo0In
.equ ti.bUsbIntFifo1In,         1
.equ ti.bmUsbIntFifo1In,                1 << ti.bUsbIntFifo1In
.equ ti.bUsbIntFifo2In,         2
.equ ti.bmUsbIntFifo2In,                1 << ti.bUsbIntFifo2In
.equ ti.bUsbIntFifo3In,         3
.equ ti.bmUsbIntFifo3In,                1 << ti.bUsbIntFifo3In
.equ ti.bUsbFifoTxInts,         0
.equ ti.bmUsbFifoTxInts,                0x0F << ti.bUsbFifoTxInts

.equ ti.usbDevImr,              0x013C
.equ ti.pUsbDevImr,             ti.pUsbRange + ti.usbDevImr
.equ ti.mpUsbDevImr,            ti.mpUsbRange + ti.usbDevImr
.equ ti.usbDevIsr,              0x014C
.equ ti.pUsbDevIsr,             ti.pUsbRange + ti.usbDevIsr
.equ ti.mpUsbDevIsr,            ti.mpUsbRange + ti.usbDevIsr
.equ ti.bUsbIntDevReset,                0
.equ ti.bmUsbIntDevReset,       1 << ti.bUsbIntDevReset
.equ ti.bUsbIntDevSuspend,      1
.equ ti.bmUsbIntDevSuspend,     1 << ti.bUsbIntDevSuspend
.equ ti.bUsbIntDevResume,       2
.equ ti.bmUsbIntDevResume,      1 << ti.bUsbIntDevResume
.equ ti.bUsbIntDevIsocErr,      3
.equ ti.bmUsbIntDevIsocErr,     1 << ti.bUsbIntDevIsocErr
.equ ti.bUsbIntDevIsocAbt,      4
.equ ti.bmUsbIntDevIsocAbt,     1 << ti.bUsbIntDevIsocAbt
.equ ti.bUsbIntDevZlpTx,                5
.equ ti.bmUsbIntDevZlpTx,       1 << ti.bUsbIntDevZlpTx
.equ ti.bUsbIntDevZlpRx,                6
.equ ti.bmUsbIntDevZlpRx,       1 << ti.bUsbIntDevZlpRx
.equ ti.bUsbIntDevDmaFin,       7
.equ ti.bmUsbIntDevDmaFin,      1 << ti.bUsbIntDevDmaFin
.equ ti.bUsbIntDevDmaErr,       8
.equ ti.bmUsbIntDevDmaErr,      1 << ti.bUsbIntDevDmaErr
.equ ti.bUsbIntDevIdle,         9
.equ ti.bmUsbIntDevIdle,                1 << ti.bUsbIntDevIdle
.equ ti.bUsbIntDevWakeup,       10
.equ ti.bmUsbIntDevWakeup,      1 << ti.bUsbIntDevWakeup
.equ ti.bUsbDevInts,            0
.equ ti.bmUsbDevInts,           0x07FF << ti.bUsbDevInts

.equ ti.usbRxZlp,               0x0150
.equ ti.pUsbRxZlp,              ti.pUsbRange + ti.usbRxZlp
.equ ti.mpUsbRxZlp,             ti.mpUsbRange + ti.usbRxZlp
.equ ti.usbTxZlp,               0x0154
.equ ti.pUsbTxZlp,              ti.pUsbRange + ti.usbTxZlp
.equ ti.mpUsbTxZlp,             ti.mpUsbRange + ti.usbTxZlp
.equ ti.bUsbEp1Zlp,             0
.equ ti.bmUsbEp1Zlp,            1 << ti.bUsbEp1Zlp
.equ ti.bUsbEp2Zlp,             1
.equ ti.bmUsbEp2Zlp,            1 << ti.bUsbEp2Zlp
.equ ti.bUsbEp3Zlp,             2
.equ ti.bmUsbEp3Zlp,            1 << ti.bUsbEp3Zlp
.equ ti.bUsbEp4Zlp,             3
.equ ti.bmUsbEp4Zlp,            1 << ti.bUsbEp4Zlp
.equ ti.bUsbEp5Zlp,             4
.equ ti.bmUsbEp5Zlp,            1 << ti.bUsbEp5Zlp
.equ ti.bUsbEp6Zlp,             5
.equ ti.bmUsbEp6Zlp,            1 << ti.bUsbEp6Zlp
.equ ti.bUsbEp7Zlp,             6
.equ ti.bmUsbEp7Zlp,            1 << ti.bUsbEp7Zlp
.equ ti.bUsbEp8Zlp,             7
.equ ti.bmUsbEp8Zlp,            1 << ti.bUsbEp8Zlp
.equ ti.bUsbZlp,                        0
.equ ti.bmUsbZlp,               0x0FF << ti.bUsbZlp

.equ ti.usbIsoEasr,             0x0158
.equ ti.pUsbIsoEasr,            ti.pUsbRange + ti.usbIsoEasr
.equ ti.mpUsbIsoEasr,           ti.mpUsbRange + ti.usbIsoEasr
.equ ti.bUsbEp1IsocAbort,       0
.equ ti.bmUsbEp1IsocAbort,      1 << ti.bUsbEp1IsocAbort
.equ ti.bUsbEp2IsocAbort,       1
.equ ti.bmUsbEp2IsocAbort,      1 << ti.bUsbEp2IsocAbort
.equ ti.bUsbEp3IsocAbort,       2
.equ ti.bmUsbEp3IsocAbort,      1 << ti.bUsbEp3IsocAbort
.equ ti.bUsbEp4IsocAbort,       3
.equ ti.bmUsbEp4IsocAbort,      1 << ti.bUsbEp4IsocAbort
.equ ti.bUsbEp5IsocAbort,       4
.equ ti.bmUsbEp5IsocAbort,      1 << ti.bUsbEp5IsocAbort
.equ ti.bUsbEp6IsocAbort,       5
.equ ti.bmUsbEp6IsocAbort,      1 << ti.bUsbEp6IsocAbort
.equ ti.bUsbEp7IsocAbort,       6
.equ ti.bmUsbEp7IsocAbort,      1 << ti.bUsbEp7IsocAbort
.equ ti.bUsbEp8IsocAbort,       7
.equ ti.bmUsbEp8IsocAbort,      1 << ti.bUsbEp8IsocAbort
.equ ti.bUsbEp1IsocErr,         16
.equ ti.bmUsbEp1IsocErr,                1 << ti.bUsbEp1IsocErr
.equ ti.bUsbEp2IsocErr,         17
.equ ti.bmUsbEp2IsocErr,                1 << ti.bUsbEp2IsocErr
.equ ti.bUsbEp3IsocErr,         18
.equ ti.bmUsbEp3IsocErr,                1 << ti.bUsbEp3IsocErr
.equ ti.bUsbEp4IsocErr,         19
.equ ti.bmUsbEp4IsocErr,                1 << ti.bUsbEp4IsocErr
.equ ti.bUsbEp5IsocErr,         20
.equ ti.bmUsbEp5IsocErr,                1 << ti.bUsbEp5IsocErr
.equ ti.bUsbEp6IsocErr,         21
.equ ti.bmUsbEp6IsocErr,                1 << ti.bUsbEp6IsocErr
.equ ti.bUsbEp7IsocErr,         22
.equ ti.bmUsbEp7IsocErr,                1 << ti.bUsbEp7IsocErr
.equ ti.bUsbEp8IsocErr,         23
.equ ti.bmUsbEp8IsocErr,                1 << ti.bUsbEp8IsocErr

.equ ti.usbInEp1,               0x0160
.equ ti.pUsbInEp1,              ti.pUsbRange + ti.usbInEp1
.equ ti.mpUsbInEp1,             ti.mpUsbRange + ti.usbInEp1
.equ ti.usbInEp2,               0x0164
.equ ti.pUsbInEp2,              ti.pUsbRange + ti.usbInEp2
.equ ti.mpUsbInEp2,             ti.mpUsbRange + ti.usbInEp2
.equ ti.usbInEp3,               0x0168
.equ ti.pUsbInEp3,              ti.pUsbRange + ti.usbInEp3
.equ ti.mpUsbInEp3,             ti.mpUsbRange + ti.usbInEp3
.equ ti.usbInEp4,               0x016C
.equ ti.pUsbInEp4,              ti.pUsbRange + ti.usbInEp4
.equ ti.mpUsbInEp4,             ti.mpUsbRange + ti.usbInEp4
.equ ti.usbInEp5,               0x0170
.equ ti.pUsbInEp5,              ti.pUsbRange + ti.usbInEp5
.equ ti.mpUsbInEp5,             ti.mpUsbRange + ti.usbInEp5
.equ ti.usbInEp6,               0x0174
.equ ti.pUsbInEp6,              ti.pUsbRange + ti.usbInEp6
.equ ti.mpUsbInEp6,             ti.mpUsbRange + ti.usbInEp6
.equ ti.usbInEp7,               0x0178
.equ ti.pUsbInEp7,              ti.pUsbRange + ti.usbInEp7
.equ ti.mpUsbInEp7,             ti.mpUsbRange + ti.usbInEp7
.equ ti.usbInEp8,               0x017C
.equ ti.pUsbInEp8,              ti.pUsbRange + ti.usbInEp8
.equ ti.mpUsbInEp8,             ti.mpUsbRange + ti.usbInEp8
.equ ti.usbOutEp1,              0x0180
.equ ti.pUsbOutEp1,             ti.pUsbRange + ti.usbOutEp1
.equ ti.mpUsbOutEp1,            ti.mpUsbRange + ti.usbOutEp1
.equ ti.usbOutEp2,              0x0184
.equ ti.pUsbOutEp2,             ti.pUsbRange + ti.usbOutEp2
.equ ti.mpUsbOutEp2,            ti.mpUsbRange + ti.usbOutEp2
.equ ti.usbOutEp3,              0x0188
.equ ti.pUsbOutEp3,             ti.pUsbRange + ti.usbOutEp3
.equ ti.mpUsbOutEp3,            ti.mpUsbRange + ti.usbOutEp3
.equ ti.usbOutEp4,              0x018C
.equ ti.pUsbOutEp4,             ti.pUsbRange + ti.usbOutEp4
.equ ti.mpUsbOutEp4,            ti.mpUsbRange + ti.usbOutEp4
.equ ti.usbOutEp5,              0x0190
.equ ti.pUsbOutEp5,             ti.pUsbRange + ti.usbOutEp5
.equ ti.mpUsbOutEp5,            ti.mpUsbRange + ti.usbOutEp5
.equ ti.usbOutEp6,              0x0194
.equ ti.pUsbOutEp6,             ti.pUsbRange + ti.usbOutEp6
.equ ti.mpUsbOutEp6,            ti.mpUsbRange + ti.usbOutEp6
.equ ti.usbOutEp7,              0x0198
.equ ti.pUsbOutEp7,             ti.pUsbRange + ti.usbOutEp7
.equ ti.mpUsbOutEp7,            ti.mpUsbRange + ti.usbOutEp7
.equ ti.usbOutEp8,              0x019C
.equ ti.pUsbOutEp8,             ti.pUsbRange + ti.usbOutEp8
.equ ti.mpUsbOutEp8,            ti.mpUsbRange + ti.usbOutEp8
.equ ti.bUsbEpMaxPktSz,         0
.equ ti.bmUsbEpMaxPktSz,                0x07FF << ti.bUsbEpMaxPktSz
.equ ti.bUsbEpStall,            11
.equ ti.bmUsbEpStall,           1 << ti.bUsbEpStall
.equ ti.bUsbEpReset,            12
.equ ti.bmUsbEpReset,           1 << ti.bUsbEpReset
.equ ti.bUsbInEpTxNum,          13
.equ ti.bmUsbInEpTxNum,         3 << ti.bUsbInEpTxNum
.equ ti.bUsbInEpSendZlp,                15
.equ ti.bmUsbInEpSendZlp,       1 << ti.bUsbInEpSendZlp

.equ ti.usbEp1Map,              0x01A0
.equ ti.pUsbEp1Map,             ti.pUsbRange + ti.usbEp1Map
.equ ti.mpUsbEp1Map,            ti.mpUsbRange + ti.usbEp1Map
.equ ti.usbEp2Map,              0x01A1
.equ ti.pUsbEp2Map,             ti.pUsbRange + ti.usbEp2Map
.equ ti.mpUsbEp2Map,            ti.mpUsbRange + ti.usbEp2Map
.equ ti.usbEp3Map,              0x01A2
.equ ti.pUsbEp3Map,             ti.pUsbRange + ti.usbEp3Map
.equ ti.mpUsbEp3Map,            ti.mpUsbRange + ti.usbEp3Map
.equ ti.usbEp4Map,              0x01A3
.equ ti.pUsbEp4Map,             ti.pUsbRange + ti.usbEp4Map
.equ ti.mpUsbEp4Map,            ti.mpUsbRange + ti.usbEp4Map
.equ ti.usbEp5Map,              0x01A4
.equ ti.pUsbEp5Map,             ti.pUsbRange + ti.usbEp5Map
.equ ti.mpUsbEp5Map,            ti.mpUsbRange + ti.usbEp5Map
.equ ti.usbEp6Map,              0x01A5
.equ ti.pUsbEp6Map,             ti.pUsbRange + ti.usbEp6Map
.equ ti.mpUsbEp6Map,            ti.mpUsbRange + ti.usbEp6Map
.equ ti.usbEp7Map,              0x01A6
.equ ti.pUsbEp7Map,             ti.pUsbRange + ti.usbEp7Map
.equ ti.mpUsbEp7Map,            ti.mpUsbRange + ti.usbEp7Map
.equ ti.usbEp8Map,              0x01A7
.equ ti.pUsbEp8Map,             ti.pUsbRange + ti.usbEp8Map
.equ ti.mpUsbEp8Map,            ti.mpUsbRange + ti.usbEp8Map
.equ ti.bUsbEpMapIn,            0
.equ ti.bmUsbEpMapIn,           0x0F << ti.bUsbEpMapIn
.equ ti.bUsbEpMapOut,           4
.equ ti.bmUsbEpMapOut,          0x0F << ti.bUsbEpMapOut

.equ ti.usbFifo0Map,            0x01A8
.equ ti.pUsbFifo0Map,           ti.pUsbRange + ti.usbFifo0Map
.equ ti.mpUsbFifo0Map,          ti.mpUsbRange + ti.usbFifo0Map
.equ ti.usbFifo1Map,            0x01A9
.equ ti.pUsbFifo1Map,           ti.pUsbRange + ti.usbFifo1Map
.equ ti.mpUsbFifo1Map,          ti.mpUsbRange + ti.usbFifo1Map
.equ ti.usbFifo2Map,            0x01AA
.equ ti.pUsbFifo2Map,           ti.pUsbRange + ti.usbFifo2Map
.equ ti.mpUsbFifo2Map,          ti.mpUsbRange + ti.usbFifo2Map
.equ ti.usbFifo3Map,            0x01AB
.equ ti.pUsbFifo3Map,           ti.pUsbRange + ti.usbFifo3Map
.equ ti.mpUsbFifo3Map,          ti.mpUsbRange + ti.usbFifo3Map
.equ ti.bUsbFifoEp,             0
.equ ti.bmUsbFifoEp,            0x0F << ti.bUsbFifoEp
.equ ti.bUsbFifoDir,            4
.equ ti.usbFifoOut,             0 << ti.bUsbFifoDir
.equ ti.usbFifoIn,              1 << ti.bUsbFifoDir
.equ ti.usbFifoBi,              2 << ti.bUsbFifoDir
.equ ti.bmUsbFifoDir,           3 << ti.bUsbFifoDir

.equ ti.usbFifo0Cfg,            0x01AC
.equ ti.pUsbFifo0Cfg,           ti.pUsbRange + ti.usbFifo0Cfg
.equ ti.mpUsbFifo0Cfg,          ti.mpUsbRange + ti.usbFifo0Cfg
.equ ti.usbFifo1Cfg,            0x01AD
.equ ti.pUsbFifo1Cfg,           ti.pUsbRange + ti.usbFifo1Cfg
.equ ti.mpUsbFifo1Cfg,          ti.mpUsbRange + ti.usbFifo1Cfg
.equ ti.usbFifo2Cfg,            0x01AE
.equ ti.pUsbFifo2Cfg,           ti.pUsbRange + ti.usbFifo2Cfg
.equ ti.mpUsbFifo2Cfg,          ti.mpUsbRange + ti.usbFifo2Cfg
.equ ti.usbFifo3Cfg,            0x01AF
.equ ti.pUsbFifo3Cfg,           ti.pUsbRange + ti.usbFifo3Cfg
.equ ti.mpUsbFifo3Cfg,          ti.mpUsbRange + ti.usbFifo3Cfg
.equ ti.bUsbFifoType,           0
.equ ti.usbFifoIsoc,            1 << ti.bUsbFifoType
.equ ti.usbFifoBulk,            2 << ti.bUsbFifoType
.equ ti.usbFifoIntr,            3 << ti.bUsbFifoType
.equ ti.bmUsbFifoType,          3 << ti.bUsbFifoType
.equ ti.bUsbFifoNumBlks,                2
.equ ti.usbFifo1Blk,            0 << ti.bUsbFifoNumBlks
.equ ti.usbFifo2Blks,           1 << ti.bUsbFifoNumBlks
.equ ti.usbFifo3Blks,           2 << ti.bUsbFifoNumBlks
.equ ti.bmUsbFifoNumBlks,       3 << ti.bUsbFifoNumBlks
.equ ti.bUsbFifoBlkSz,          4
.equ ti.usbFifoBlkSz512,                0 << ti.bUsbFifoBlkSz
.equ ti.usbFifoBlkSz1024,       1 << ti.bUsbFifoBlkSz
.equ ti.bmUsbFifoBlkSz,         1 << ti.bUsbFifoBlkSz
.equ ti.bUsbFifoEn,             5
.equ ti.bmUsbFifoEn,            1 << ti.bUsbFifoEn

.equ ti.usbFifo0Csr,            0x01B0
.equ ti.pUsbFifo0Csr,           ti.pUsbRange + ti.usbFifo0Csr
.equ ti.mpUsbFifo0Csr,          ti.mpUsbRange + ti.usbFifo0Csr
.equ ti.usbFifo1Csr,            0x01B4
.equ ti.pUsbFifo1Csr,           ti.pUsbRange + ti.usbFifo1Csr
.equ ti.mpUsbFifo1Csr,          ti.mpUsbRange + ti.usbFifo1Csr
.equ ti.usbFifo2Csr,            0x01B8
.equ ti.pUsbFifo2Csr,           ti.pUsbRange + ti.usbFifo2Csr
.equ ti.mpUsbFifo2Csr,          ti.mpUsbRange + ti.usbFifo2Csr
.equ ti.usbFifo3Csr,            0x01BC
.equ ti.pUsbFifo3Csr,           ti.pUsbRange + ti.usbFifo3Csr
.equ ti.mpUsbFifo3Csr,          ti.mpUsbRange + ti.usbFifo3Csr
.equ ti.bUsbFifoLen,            0
.equ ti.bmUsbFifoLen,           0x07FF << ti.bUsbFifoLen
.equ ti.bUsbFifoReset,          12
.equ ti.bmUsbFifoReset,         1 << ti.bUsbFifoReset

.equ ti.usbDmaFifo,             0x01C0
.equ ti.pUsbDmaFifo,            ti.pUsbRange + ti.usbDmaFifo
.equ ti.mpUsbDmaFifo,           ti.mpUsbRange + ti.usbDmaFifo
.equ ti.bUsbDmaFifo0,           0
.equ ti.bmUsbDmaFifo0,          1 << ti.bUsbDmaFifo0
.equ ti.bUsbDmaFifo1,           1
.equ ti.bmUsbDmaFifo1,          1 << ti.bUsbDmaFifo1
.equ ti.bUsbDmaFifo2,           2
.equ ti.bmUsbDmaFifo2,          1 << ti.bUsbDmaFifo2
.equ ti.bUsbDmaFifo3,           3
.equ ti.bmUsbDmaFifo3,          1 << ti.bUsbDmaFifo3
.equ ti.bUsbDmaCxFifo,          4
.equ ti.bmUsbDmaCxFifo,         1 << ti.bUsbDmaCxFifo
.equ ti.bUsbDmaFifo,            0
.equ ti.bmUsbDmaNoFifo,         0 << ti.bUsbDmaFifo
.equ ti.bmUsbDmaFifo,           0x01F << ti.bUsbDmaFifo

.equ ti.usbDmaCtrl,             0x01C8
.equ ti.pUsbDmaCtrl,            ti.pUsbRange + ti.usbDmaCtrl
.equ ti.mpUsbDmaCtrl,           ti.mpUsbRange + ti.usbDmaCtrl
.equ ti.bUsbDmaStart,           0
.equ ti.bmUsbDmaStart,          1 << ti.bUsbDmaStart
.equ ti.bUsbDmaDir,             1
.equ ti.usbDmaFifo2Mem,         0 << ti.bUsbDmaDir
.equ ti.usbDmaMem2Fifo,         1 << ti.bUsbDmaDir
.equ ti.usbDmaFifo2Fifo,                2 << ti.bUsbDmaDir
.equ ti.bmUsbDmaDir,            3 << ti.bUsbDmaDir
.equ ti.bUsbDmaAbort,           3
.equ ti.bmUsbDmaAbort,          1 << ti.bUsbDmaAbort
.equ ti.bUsbDmaClrFifo,         4
.equ ti.bmUsbDmaClrFifo,                1 << ti.bUsbDmaClrFifo

.equ ti.usbDmaLen,              0x01C9
.equ ti.pUsbDmaLen,             ti.pUsbRange + ti.usbDmaLen
.equ ti.mpUsbDmaLen,            ti.mpUsbRange + ti.usbDmaLen
.equ ti.bUsbDmaLen,             0
.equ ti.bmUsbDmaLen,            0x01FFFF << ti.bUsbDmaLen

.equ ti.usbDmaAddr,             0x01CC
.equ ti.pUsbDmaAddr,            ti.pUsbRange + ti.usbDmaAddr
.equ ti.mpUsbDmaAddr,           ti.mpUsbRange + ti.usbDmaAddr
.equ ti.bUsbDmaAddr,            0
.equ ti.bmUsbDmaAddr,           0x07FFFF << ti.bUsbDmaAddr

.equ ti.usbEp0Data,             0x01D0
.equ ti.pUsbEp0Data,            ti.pUsbRange + ti.usbEp0Data
.equ ti.mpUsbEp0Data,           ti.mpUsbRange + ti.usbEp0Data
.equ ti.bUsbEp0Data,            0
.equ ti.bmUsbEp0Data,           0x0FFFFFFFF << ti.bUsbEp0Data

;LCD Ports
;--------------------------------
.equ ti.pLcdRange,              0x04000
.equ ti.mpLcdRange,             0x0E30000

.equ ti.lcdTiming0,             0x0000
.equ ti.pLcdTiming0,            ti.pLcdRange + ti.lcdTiming0
.equ ti.mpLcdTiming0,           ti.mpLcdRange + ti.lcdTiming0
.equ ti.lcdTiming1,             0x0004
.equ ti.pLcdTiming1,            ti.pLcdRange + ti.lcdTiming1
.equ ti.mpLcdTiming1,           ti.mpLcdRange + ti.lcdTiming1
.equ ti.lcdTiming2,             0x0008
.equ ti.pLcdTiming2,            ti.pLcdRange + ti.lcdTiming2
.equ ti.mpLcdTiming2,           ti.mpLcdRange + ti.lcdTiming2
.equ ti.lcdTiming3,             0x000C
.equ ti.pLcdTiming3,            ti.pLcdRange + ti.lcdTiming3
.equ ti.mpLcdTiming3,           ti.mpLcdRange + ti.lcdTiming3

.equ ti.lcdBase,                        0x0010
.equ ti.pLcdBase,               ti.pLcdRange + ti.lcdBase
.equ ti.mpLcdBase,              ti.mpLcdRange + ti.lcdBase
.equ ti.lcdUpbase,              0x0010
.equ ti.pLcdUpbase,             ti.pLcdRange + ti.lcdUpbase
.equ ti.mpLcdUpbase,            ti.mpLcdRange + ti.lcdUpbase
.equ ti.lcdLpbase,              0x0014
.equ ti.pLcdLpbase,             ti.pLcdRange + ti.lcdLpbase
.equ ti.mpLcdLpbase,            ti.mpLcdRange + ti.lcdLpbase

.equ ti.lcdCtrl,                        0x0018
.equ ti.pLcdCtrl,               ti.pLcdRange + ti.lcdCtrl
.equ ti.mpLcdCtrl,              ti.mpLcdRange + ti.lcdCtrl
.equ ti.lcdEn,                  0x01
.equ ti.lcdTft,                 0x20
.equ ti.lcdBpp1,                        0b0000 | ti.lcdTft | ti.lcdEn
.equ ti.lcdBpp2,                        0b0010 | ti.lcdTft | ti.lcdEn
.equ ti.lcdBpp4,                        0b0100 | ti.lcdTft | ti.lcdEn
.equ ti.lcdBpp8,                        0b0110 | ti.lcdTft | ti.lcdEn
.equ ti.lcdBpp16Alt,            0b1000 | ti.lcdTft | ti.lcdEn
.equ ti.lcdBpp24,               0b1010 | ti.lcdTft | ti.lcdEn
.equ ti.lcdBpp16,               0b1100 | ti.lcdTft | ti.lcdEn ; Default LCD mode
.equ ti.lcdBpp12,               0b1110 | ti.lcdTft | ti.lcdEn
.equ ti.lcdBgr,                 0x100
.equ ti.lcdBigEndian,           0x200
.equ ti.lcdBigEndianPixels,     0x400
.equ ti.lcdPwr,                 0x800
.equ ti.lcdIntVSync,            0x0000
.equ ti.lcdIntBack,             0x1000
.equ ti.lcdIntActiveVideo,      0x2000
.equ ti.lcdIntFront,            0x3000
.equ ti.lcdWatermark,           0x10000
.equ ti.lcdNormalMode,          ti.lcdPwr | ti.lcdBgr | ti.lcdBpp16

.equ ti.lcdImsc,                        0x001C
.equ ti.pLcdImsc,               ti.pLcdRange + ti.lcdImsc
.equ ti.mpLcdImsc,              ti.mpLcdRange + ti.lcdImsc
.equ ti.lcdRis,                 0x0020
.equ ti.pLcdRis,                        ti.pLcdRange + ti.lcdRis
.equ ti.mpLcdRis,               ti.mpLcdRange + ti.lcdRis
.equ ti.lcdMis,                 0x0024
.equ ti.pLcdMis,                        ti.pLcdRange + ti.lcdMis
.equ ti.mpLcdMis,               ti.mpLcdRange + ti.lcdMis
.equ ti.lcdIcr,                 0x0028
.equ ti.pLcdIcr,                        ti.pLcdRange + ti.lcdIcr
.equ ti.mpLcdIcr,               ti.mpLcdRange + ti.lcdIcr

.equ ti.bLcdIntFuf,             1
.equ ti.lcdIntFuf,              1 << ti.bLcdIntFuf
.equ ti.bLcdIntLNBU,            2
.equ ti.lcdIntLNBU,             1 << ti.bLcdIntLNBU
.equ ti.bLcdIntVcomp,           3
.equ ti.lcdIntVcomp,            1 << ti.bLcdIntVcomp
.equ ti.bLcdIntMbErr,           4
.equ ti.lcdIntMbErr,            1 << ti.bLcdIntMbErr

.equ ti.lcdCurr,                        0x002C
.equ ti.pLcdCurr,               ti.pLcdRange + ti.lcdCurr
.equ ti.mpLcdCurr,              ti.mpLcdRange + ti.lcdCurr
.equ ti.lcdUpcurr,              0x002C
.equ ti.pLcdUpcurr,             ti.pLcdRange + ti.lcdUpcurr
.equ ti.mpLcdUpcurr,            ti.mpLcdRange + ti.lcdUpcurr
.equ ti.lcdLpcurr,              0x0030
.equ ti.pLcdLpcurr,             ti.pLcdRange + ti.lcdLpcurr
.equ ti.mpLcdLpcurr,            ti.mpLcdRange + ti.lcdLpcurr
.equ ti.lcdPalette,             0x0200
.equ ti.pLcdPalette,            ti.pLcdRange + ti.lcdPalette
.equ ti.mpLcdPalette,           ti.mpLcdRange + ti.lcdPalette

.equ ti.lcdCrsrImage,           0x0800
.equ ti.pLcdCrsrImage,          ti.pLcdRange + ti.lcdCrsrImage
.equ ti.mpLcdCrsrImage,         ti.mpLcdRange + ti.lcdCrsrImage
.equ ti.lcdCrsrCtrl,            0x0C00
.equ ti.pLcdCrsrCtrl,           ti.pLcdRange + ti.lcdCrsrCtrl
.equ ti.mpLcdCrsrCtrl,          ti.mpLcdRange + ti.lcdCrsrCtrl
.equ ti.lcdCrsrConfig,          0x0C04
.equ ti.pLcdCrsrConfig,         ti.pLcdRange + ti.lcdCrsrConfig
.equ ti.mpLcdCrsrConfig,                ti.mpLcdRange + ti.lcdCrsrConfig
.equ ti.lcdCrsrPalette0,                0x0C08
.equ ti.pLcdCrsrPalette0,       ti.pLcdRange + ti.lcdCrsrPalette0
.equ ti.mpLcdCrsrPalette0,      ti.mpLcdRange + ti.lcdCrsrPalette0
.equ ti.lcdCrsrPalette1,                0x0C0C
.equ ti.pLcdCrsrPalette1,       ti.pLcdRange + ti.lcdCrsrPalette1
.equ ti.mpLcdCrsrPalette1,      ti.mpLcdRange + ti.lcdCrsrPalette1
.equ ti.lcdCrsrXY,              0x0C10
.equ ti.pLcdCrsrXY,             ti.pLcdRange + ti.lcdCrsrXY
.equ ti.mpLcdCrsrXY,            ti.mpLcdRange + ti.lcdCrsrXY
.equ ti.lcdCrsrClip,            0x0C14
.equ ti.pLcdCrsrClip,           ti.pLcdRange + ti.lcdCrsrClip
.equ ti.mpLcdCrsrClip,          ti.mpLcdRange + ti.lcdCrsrClip
.equ ti.lcdCrsrImsc,            0x0C20
.equ ti.pLcdCrsrImsc,           ti.pLcdRange + ti.lcdCrsrImsc
.equ ti.mpLcdCrsrImsc,          ti.mpLcdRange + ti.lcdCrsrImsc
.equ ti.lcdCrsrIcr,             0x0C24
.equ ti.pLcdCrsrIcr,            ti.pLcdRange + ti.lcdCrsrIcr
.equ ti.mpLcdCrsrIcr,           ti.mpLcdRange + ti.lcdCrsrIcr
.equ ti.lcdCrsrRis,             0x0C28
.equ ti.pLcdCrsrRis,            ti.pLcdRange + ti.lcdCrsrRis
.equ ti.mpLcdCrsrRis,           ti.mpLcdRange + ti.lcdCrsrRis
.equ ti.lcdCrsrMis,             0x0C2C
.equ ti.pLcdCrsrMis,            ti.pLcdRange + ti.lcdCrsrMis
.equ ti.mpLcdCrsrMis,           ti.mpLcdRange + ti.lcdCrsrMis

;Interrupt Ports
;-----------------------------------
.equ ti.pIntRange,              0x05000
.equ ti.mpIntRange,             0x0F00000

.equ ti.intStat,                        0
.equ ti.pIntStat,               ti.pIntRange + ti.intStat
.equ ti.mpIntStat,              ti.mpIntRange + ti.intStat
.equ ti.intMask,                        4
.equ ti.pIntMask,               ti.pIntRange + ti.intMask
.equ ti.mpIntMask,              ti.mpIntRange + ti.intMask
.equ ti.intAck,                 8
.equ ti.pIntAck,                        ti.pIntRange + ti.intAck
.equ ti.mpIntAck,               ti.mpIntRange + ti.intAck
.equ ti.intLatch,               12
.equ ti.pIntLatch,              ti.pIntRange + ti.intLatch
.equ ti.mpIntLatch,             ti.mpIntRange + ti.intLatch
.equ ti.intInvert,              16
.equ ti.pIntInvert,             ti.pIntRange + ti.intInvert
.equ ti.mpIntInvert,            ti.mpIntRange + ti.intInvert
.equ ti.intMasked,              20
.equ ti.pIntMasked,             ti.pIntRange + ti.intMasked
.equ ti.mpIntMasked,            ti.mpIntRange + ti.intMasked

.equ ti.bIntOn,                 0
.equ ti.intOn,                  1 << ti.bIntOn
.equ ti.bIntTmr1,               1
.equ ti.intTmr1,                        1 << ti.bIntTmr1
.equ ti.bIntTmr2,               2
.equ ti.intTmr2,                        1 << ti.bIntTmr2
.equ ti.bIntTmr3,               3
.equ ti.intTmr3,                        1 << ti.bIntTmr3
.equ ti.bIntOSTmr,              4
.equ ti.intOSTmr,               1 << ti.bIntOSTmr
.equ ti.bIntKey,                        10
.equ ti.intKey,                 1 << ti.bIntKey
.equ ti.bIntLcd,                        11
.equ ti.intLcd,                 1 << ti.bIntLcd
.equ ti.bIntRtc,                        12
.equ ti.intRtc,                 1 << ti.bIntRtc
.equ ti.bIntUsb,                        13
.equ ti.intUsb,                 1 << ti.bIntUsb
.equ ti.intDefaultMask,         ti.intOn | ti.intTmr3 | ti.intOSTmr | ti.intRtc | ti.intUsb

;Timer Ports
;-----------------------------------
.equ ti.tmrRange,               0x00
.equ ti.pTmrRange,              0x7000
.equ ti.mpTmrRange,             0x0F20000

.equ ti.tmr1Counter,            0x00
.equ ti.pTmr1Counter,           0x7000
.equ ti.mpTmr1Counter,          0x0F20000
.equ ti.tmr1Load,               0x04
.equ ti.pTmr1Load,              0x7004
.equ ti.mpTmr1Load,             0x0F20004
.equ ti.tmr1Match1,             0x08
.equ ti.pTmr1Match1,            0x7008
.equ ti.mpTmr1Match1,           0x0F20008
.equ ti.tmr1Match2,             0x0C
.equ ti.pTmr1Match2,            0x700C
.equ ti.mpTmr1Match2,           0x0F2000C

.equ ti.tmr2Counter,            0x10
.equ ti.pTmr2Counter,           0x7010
.equ ti.mpTmr2Counter,          0x0F20010
.equ ti.tmr2Load,               0x14
.equ ti.pTmr2Load,              0x7014
.equ ti.mpTmr2Load,             0x0F20014
.equ ti.tmr2Match1,             0x18
.equ ti.pTmr2Match1,            0x7018
.equ ti.mpTmr2Match1,           0x0F20018
.equ ti.tmr2Match2,             0x1C
.equ ti.pTmr2Match2,            0x701C
.equ ti.mpTmr2Match2,           0x0F2001C

.equ ti.tmr3Counter,            0x20
.equ ti.pTmr3Counter,           0x7020
.equ ti.mpTmr3Counter,          0x0F20020
.equ ti.tmr3Load,               0x24
.equ ti.pTmr3Load,              0x7024
.equ ti.mpTmr3Load,             0x0F20024
.equ ti.tmr3Match1,             0x28
.equ ti.pTmr3Match1,            0x7028
.equ ti.mpTmr3Match1,           0x0F20028
.equ ti.tmr3Match2,             0x2C
.equ ti.pTmr3Match2,            0x702C
.equ ti.mpTmr3Match2,           0x0F2002C

.equ ti.tmrCtrl,                        0x30
.equ ti.pTmrCtrl,               0x7030
.equ ti.mpTmrCtrl,              0x0F20030

.equ ti.bTmr1Enable,            0
.equ ti.tmr1Enable,             1 << ti.bTmr1Enable
.equ ti.bTmr1Crystal,           1
.equ ti.tmr1Crystal,            1 << ti.bTmr1Crystal
.equ ti.bTmr1Overflow,          2
.equ ti.tmr1Overflow,           1 << ti.bTmr1Overflow
.equ ti.bTmr2Enable,            3
.equ ti.tmr2Enable,             1 << ti.bTmr2Enable
.equ ti.bTmr2Crystal,           4
.equ ti.tmr2Crystal,            1 << ti.bTmr2Crystal
.equ ti.bTmr2Overflow,          5
.equ ti.tmr2Overflow,           1 << ti.bTmr2Overflow
.equ ti.bTmr3Enable,            6
.equ ti.tmr3Enable,             1 << ti.bTmr3Enable
.equ ti.bTmr3Crystal,           7
.equ ti.tmr3Crystal,            1 << ti.bTmr3Crystal
.equ ti.bTmr3Overflow,          8
.equ ti.tmr3Overflow,           1 << ti.bTmr3Overflow
.equ ti.bTmr1CountUp,           9
.equ ti.tmr1CountUp,            1 << ti.bTmr1CountUp
.equ ti.bTmr2CountUp,           10
.equ ti.tmr2CountUp,            1 << ti.bTmr2CountUp
.equ ti.bTmr3CountUp,           11
.equ ti.tmr3CountUp,            1 << ti.bTmr3CountUp

.equ ti.tmrIntStatus,           0x34
.equ ti.pTmrIntStatus,          0x7034
.equ ti.mpTmrIntStatus,         0x0F20034

.equ ti.bTmr1IntMatch1,         0
.equ ti.tmr1IntMatch1,          1 << ti.bTmr1IntMatch1
.equ ti.bTmr1IntMatch2,         1
.equ ti.tmr1IntMatch2,          1 << ti.bTmr1IntMatch2
.equ ti.bTmr1IntOverflow,       2
.equ ti.tmr1IntOverflow,                1 << ti.bTmr1IntOverflow
.equ ti.bTmr2IntMatch1,         3
.equ ti.tmr2IntMatch1,          1 << ti.bTmr2IntMatch1
.equ ti.bTmr2IntMatch2,         4
.equ ti.tmr2IntMatch2,          1 << ti.bTmr2IntMatch2
.equ ti.bTmr2IntOverflow,       5
.equ ti.tmr2IntOverflow,                1 << ti.bTmr2IntOverflow
.equ ti.bTmr3IntMatch1,         6
.equ ti.tmr3IntMatch1,          1 << ti.bTmr3IntMatch1
.equ ti.bTmr3IntMatch2,         7
.equ ti.tmr3IntMatch2,          1 << ti.bTmr3IntMatch2
.equ ti.bTmr3IntOverflow,       8
.equ ti.tmr3IntOverflow,                1 << ti.bTmr3IntOverflow

.equ ti.tmrIntMask,             0x38
.equ ti.pTmrIntMask,            0x7038
.equ ti.mpTmrIntMask,           0x0F20038

.equ ti.tmrRevision,            0x3C
.equ ti.pTmrRevision,           0x703C
.equ ti.mpTmrRevision,          0x0F2003C

;RTC Ports
;-----------------------------------
.equ ti.pRtcRange,              0x8000
.equ ti.mpRtcRange,             0x0F30000

;Keypad Ports
;-----------------------------------
.equ ti.pKeyRange,              0x0A000
.equ ti.mpKeyRange,             0x0F50000

.equ ti.keyMode,                        0
.equ ti.pKeyMode,               ti.pKeyRange + ti.keyMode
.equ ti.mpKeyMode,              ti.mpKeyRange + ti.keyMode
.equ ti.keyRows,                        4
.equ ti.pKeyRows,               ti.pKeyRange + ti.keyRows
.equ ti.mpKeyRows,              ti.mpKeyRange + ti.keyRows
.equ ti.keyCols,                        5
.equ ti.pKeyCols,               ti.pKeyRange + ti.keyCols
.equ ti.mpKeyCols,              ti.mpKeyRange + ti.keyCols
.equ ti.keyIntStat,             8
.equ ti.pKeyIntStat,            ti.pKeyRange + ti.keyIntStat
.equ ti.mpKeyIntStat,           ti.mpKeyRange + ti.keyIntStat
.equ ti.keyIntAck,              8
.equ ti.pKeyIntAck,             ti.pKeyRange + ti.keyIntAck
.equ ti.mpKeyIntAck,            ti.mpKeyRange + ti.keyIntAck
.equ ti.keyIntMask,             12
.equ ti.pKeyIntMask,            ti.pKeyRange + ti.keyIntMask
.equ ti.mpKeyIntMask,           ti.mpKeyRange + ti.keyIntMask
.equ ti.keyData,                        16
.equ ti.pKeyData,               ti.pKeyRange + ti.keyData
.equ ti.mpKeyData,              ti.mpKeyRange + ti.keyData
.equ ti.keyGpio,                        48
.equ ti.pKeyGpio,               ti.pKeyRange + ti.keyGpio
.equ ti.mpKeyGpio,              ti.mpKeyRange + ti.keyGpio

.equ ti.bKeyIntScanDone,                0
.equ ti.keyIntScanDone,         1 << ti.bKeyIntScanDone
.equ ti.bKeyIntKeyChange,       1
.equ ti.keyIntKeyChange,                1 << ti.bKeyIntKeyChange
.equ ti.bKeyIntKeyPress,                2
.equ ti.keyIntKeyPress,         1 << ti.bKeyIntKeyPress

.equ ti.keyModeIdle,            0
.equ ti.keyModeAny,             1
.equ ti.keyModeScanOnce,                2
.equ ti.keyModeScan,            3

;Backlight Ports
;-----------------------------------
.equ ti.pBlLevel,               0x0B024
.equ ti.mpBlLevel,              0x0F60024

;SPI Ports
;-----------------------------------
.equ ti.pSpiRange,              0x0D000
.equ ti.mpSpiRange,             0x0F80000

.equ ti.spiCtrl0,               0x000
.equ ti.pSpiCtrl0,              ti.pSpiRange + ti.spiCtrl0
.equ ti.mpSpiCtrl0,             ti.mpSpiRange + ti.spiCtrl0
.equ ti.bSpiClkPolarity,                0
.equ ti.bmSpiClkPolarity,       1 << ti.bSpiClkPolarity
.equ ti.bSpiClkPhase,           1
.equ ti.bmSpiClkPhase,          1 << ti.bSpiClkPhase
.equ ti.bSpiOpMode,             2
.equ ti.bmSpiSlave,             0 << ti.bSpiOpMode
.equ ti.bmSpiMaster,            3 << ti.bSpiOpMode
.equ ti.bmSpiSlaveMono,         0 << ti.bSpiOpMode
.equ ti.bmSpiSlaveStereo,       1 << ti.bSpiOpMode
.equ ti.bmSpiMasterMono,                2 << ti.bSpiOpMode
.equ ti.bmSpiMasterStereo,      3 << ti.bSpiOpMode
.equ ti.bmSpiOpMode,            3 << ti.bSpiOpMode
.equ ti.bSpiFsJustify,          4
.equ ti.bmSpiFsJustify,         1 << ti.bSpiFsJustify
.equ ti.bSpiFsPolarity,         5
.equ ti.bmSpiFsPolarity,                1 << ti.bSpiFsPolarity
.equ ti.bSpiLsb,                        6
.equ ti.bmSpiLsb,               1 << ti.bSpiLsb
.equ ti.bSpiLoopback,           7
.equ ti.bmSpiLoopback,          1 << ti.bSpiLoopback
.equ ti.bSpiFsDist,             8
.equ ti.bmSpiFsDist,            3 << ti.bSpiFsDist
.equ ti.bSpiFlash,              11
.equ ti.bmSpiFlash,             1 << ti.bSpiFlash
.equ ti.bSpiFrFmt,              12
.equ ti.spiSspFrFmt,            0 << ti.bSpiFrFmt
.equ ti.spiSpiFrFmt,            1 << ti.bSpiFrFmt
.equ ti.spiMicrowaveFrFmt,      2 << ti.bSpiFrFmt
.equ ti.spiI2sFrFmt,            3 << ti.bSpiFrFmt
.equ ti.bmSpiFrFmt,             3 << ti.bSpiFrFmt

.equ ti.spiCtrl1,               0x004
.equ ti.pSpiCtrl1,              ti.pSpiRange + ti.spiCtrl1
.equ ti.mpSpiCtrl1,             ti.mpSpiRange + ti.spiCtrl1
.equ ti.spiClkDiv,              ti.spiCtrl1 + 0
.equ ti.pSpiClkDiv,             ti.pSpiRange + ti.spiClkDiv
.equ ti.mpSpiClkDiv,            ti.mpSpiRange + ti.spiClkDiv
.equ ti.bSpiClkDiv,             0
.equ ti.bmSpiClkDiv,            0x0FFFF << ti.bSpiClkDiv
.equ ti.spiDataWidth,           ti.spiCtrl1 + 2
.equ ti.pSpiDataWidth,          ti.pSpiRange + ti.spiDataWidth
.equ ti.mpSpiDataWidth,         ti.mpSpiRange + ti.spiDataWidth
.equ ti.bSpiDataWidth,          0
.equ ti.bmSpiDataWidth,         0x01F << ti.bSpiDataWidth
.equ ti.spiPadWidth,            ti.spiCtrl1 + 3
.equ ti.pSpiPadWidth,           ti.pSpiRange + ti.spiPadWidth
.equ ti.mpSpiPadWidth,          ti.mpSpiRange + ti.spiPadWidth
.equ ti.bSpiPadWidth,           0
.equ ti.bmSpiPadWidth,          0x0FF << ti.bSpiPadWidth

.equ ti.spiCtrl2,               0x008
.equ ti.pSpiCtrl2,              ti.pSpiRange + ti.spiCtrl2
.equ ti.mpSpiCtrl2,             ti.mpSpiRange + ti.spiCtrl2
.equ ti.bSpiChipEn,             0
.equ ti.bmSpiChipEn,            1 << ti.bSpiChipEn
.equ ti.bSpiTxDataOutEn,                1
.equ ti.bmSpiTxDataOutEn,       1 << ti.bSpiTxDataOutEn
.equ ti.bSpiRxClr,              2
.equ ti.bmSpiRxClr,             1 << ti.bSpiRxClr
.equ ti.bSpiTxClr,              3
.equ ti.bmSpiTxClr,             1 << ti.bSpiTxClr
.equ ti.bSpiChipReset,          6
.equ ti.bmSpiChipReset,         1 << ti.bSpiChipReset
.equ ti.bSpiRxEn,               7
.equ ti.bmSpiRxEn,              1 << ti.bSpiRxEn
.equ ti.bSpiTxEn,               8
.equ ti.bmSpiTxEn,              1 << ti.bSpiTxEn
.equ ti.bSpiFs,                 9
.equ ti.bmSpiFs,                        1 << ti.bSpiFs
.equ ti.bSpiCs,                 10
.equ ti.bmSpiCs,                        3 << ti.bSpiCs

.equ ti.spiStatus,              0x00C
.equ ti.pSpiStatus,             ti.pSpiRange + ti.spiStatus
.equ ti.mpSpiStatus,            ti.mpSpiRange + ti.spiStatus
.equ ti.bSpiRxFifoFull,         0
.equ ti.bmSpiRxFifoFull,                1 << ti.bSpiRxFifoFull
.equ ti.bSpiTxFifoNotFull,      1
.equ ti.bmSpiTxFifoNotFull,     1 << ti.bSpiTxFifoNotFull
.equ ti.bSpiChipBusy,           2
.equ ti.bmSpiChipBusy,          1 << ti.bSpiChipBusy
.equ ti.bSpiRxFifoBytes,                4
.equ ti.bmSpiRxFifoBytes,       0x01F << ti.bSpiRxFifoBytes
.equ ti.bSpiTxFifoBytes,                12
.equ ti.bmSpiTxFifoBytes,       0x01F << ti.bSpiTxFifoBytes

.equ ti.spiIntCtrl,             0x010
.equ ti.pSpiIntCtrl,            ti.pSpiRange + ti.spiIntCtrl
.equ ti.mpSpiIntCtrl,           ti.mpSpiRange + ti.spiIntCtrl

.equ ti.spiIntStatus,           0x014
.equ ti.pSpiIntStatus,          ti.pSpiRange + ti.spiIntStatus
.equ ti.mpSpiIntStatus,         ti.mpSpiRange + ti.spiIntStatus

.equ ti.spiData,                        0x018
.equ ti.pSpiData,               ti.pSpiRange + ti.spiData
.equ ti.mpSpiData,              ti.mpSpiRange + ti.spiData
.equ ti.bSpiData,               0
.equ ti.bmSpiData,              0x0FFFFFFFF

;Character Font Equates
;-------------------------------------
.equ ti.LrecurN,                        0x001
.equ ti.LrecurU,                        0x002
.equ ti.LrecurV,                        0x003
.equ ti.LrecurW,                        0x004
.equ ti.Lconvert,               0x005
.equ ti.LsqUp,                  0x006
.equ ti.LsqDown,                        0x007
.equ ti.Lintegral,              0x008
.equ ti.Lcross,                 0x009
.equ ti.LboxIcon,               0x00A
.equ ti.LcrossIcon,             0x00B
.equ ti.LdotIcon,               0x00C
.equ ti.LsubT,                  0x00D ;small capital T for parametric mode.
.equ ti.LcubeR,                 0x00E ;slightly different 3 for cubed root.
.equ ti.LhexF,                  0x00F
.equ ti.Lroot,                  0x010
.equ ti.Linverse,               0x011
.equ ti.Lsquare,                        0x012
.equ ti.Langle,                 0x013
.equ ti.Ldegree,                        0x014
.equ ti.Lradian,                        0x015
.equ ti.Ltranspose,             0x016
.equ ti.LLE,                    0x017
.equ ti.LNE,                    0x018
.equ ti.LGE,                    0x019
.equ ti.Lneg,                   0x01A
.equ ti.Lexponent,              0x01B
.equ ti.Lstore,                 0x01C
.equ ti.Lten,                   0x01D
.equ ti.LupArrow,               0x01E
.equ ti.LdownArrow,             0x01F
.equ ti.Lspace,                 0x020
.equ ti.Lexclam,                        0x021
.equ ti.Lquote,                 0x022
.equ ti.Lpound,                 0x023
.equ ti.Lfourth,                        0x024
.equ ti.Lpercent,               0x025
.equ ti.Lampersand,             0x026
.equ ti.Lapostrophe,            0x027
.equ ti.LlParen,                        0x028
.equ ti.LrParen,                        0x029
.equ ti.Lasterisk,              0x02A
.equ ti.LplusSign,              0x02B
.equ ti.Lcomma,                 0x02C
.equ ti.Ldash,                  0x02D
.equ ti.Lperiod,                        0x02E
.equ ti.Lslash,                 0x02F
.equ ti.L0,                     0x030
.equ ti.L1,                     0x031
.equ ti.L2,                     0x032
.equ ti.L3,                     0x033
.equ ti.L4,                     0x034
.equ ti.L5,                     0x035
.equ ti.L6,                     0x036
.equ ti.L7,                     0x037
.equ ti.L8,                     0x038
.equ ti.L9,                     0x039
.equ ti.Lcolon,                 0x03A
.equ ti.Lsemicolon,             0x03B
.equ ti.LLT,                    0x03C
.equ ti.LEQ,                    0x03D
.equ ti.LGT,                    0x03E
.equ ti.Lquestion,              0x03F
.equ ti.LatSign,                        0x040
.equ ti.LcapA,                  0x041
.equ ti.LcapB,                  0x042
.equ ti.LcapC,                  0x043
.equ ti.LcapD,                  0x044
.equ ti.LcapE,                  0x045
.equ ti.LcapF,                  0x046
.equ ti.LcapG,                  0x047
.equ ti.LcapH,                  0x048
.equ ti.LcapI,                  0x049
.equ ti.LcapJ,                  0x04A
.equ ti.LcapK,                  0x04B
.equ ti.LcapL,                  0x04C
.equ ti.LcapM,                  0x04D
.equ ti.LcapN,                  0x04E
.equ ti.LcapO,                  0x04F
.equ ti.LcapP,                  0x050
.equ ti.LcapQ,                  0x051
.equ ti.LcapR,                  0x052
.equ ti.LcapS,                  0x053
.equ ti.LcapT,                  0x054
.equ ti.LcapU,                  0x055
.equ ti.LcapV,                  0x056
.equ ti.LcapW,                  0x057
.equ ti.LcapX,                  0x058
.equ ti.LcapY,                  0x059
.equ ti.LcapZ,                  0x05A
.equ ti.Ltheta,                 0x05B
.equ ti.Lbackslash,             0x05C
.equ ti.LrBrack,                        0x05D
.equ ti.Lcaret,                 0x05E
.equ ti.Lunderscore,            0x05F
.equ ti.Lbackquote,             0x060
.equ ti.La,                     0x061
.equ ti.Lb,                     0x062
.equ ti.Lc,                     0x063
.equ ti.Ld,                     0x064
.equ ti.Le,                     0x065
.equ ti.Lf,                     0x066
.equ ti.Lg,                     0x067
.equ ti.Lh,                     0x068
.equ ti.Li,                     0x069
.equ ti.Lj,                     0x06A
.equ ti.Lk,                     0x06B
.equ ti.Ll,                     0x06C
.equ ti.Lm,                     0x06D
.equ ti.Ln,                     0x06E
.equ ti.Lo,                     0x06F
.equ ti.Lp,                     0x070
.equ ti.Lq,                     0x071
.equ ti.Lr,                     0x072
.equ ti.Ls,                     0x073
.equ ti.Lt,                     0x074
.equ ti.Lu,                     0x075
.equ ti.Lv,                     0x076
.equ ti.Lw,                     0x077
.equ ti.Lx,                     0x078
.equ ti.Ly,                     0x079
.equ ti.Lz,                     0x07A
.equ ti.LlBrace,                        0x07B
.equ ti.Lbar,                   0x07C
.equ ti.LrBrace,                        0x07D
.equ ti.Ltilde,                 0x07E
.equ ti.LinvEQ,                 0x07F
.equ ti.Lsub0,                  0x080
.equ ti.Lsub1,                  0x081
.equ ti.Lsub2,                  0x082
.equ ti.Lsub3,                  0x083
.equ ti.Lsub4,                  0x084
.equ ti.Lsub5,                  0x085
.equ ti.Lsub6,                  0x086
.equ ti.Lsub7,                  0x087
.equ ti.Lsub8,                  0x088
.equ ti.Lsub9,                  0x089
.equ ti.LcapAAcute,             0x08A
.equ ti.LcapAGrave,             0x08B
.equ ti.LcapACaret,             0x08C
.equ ti.LcapADier,              0x08D
.equ ti.LaAcute,                        0x08E
.equ ti.LaGrave,                        0x08F
.equ ti.LaCaret,                        0x090
.equ ti.LaDier,                 0x091
.equ ti.LcapEAcute,             0x092
.equ ti.LcapEGrave,             0x093
.equ ti.LcapECaret,             0x094
.equ ti.LcapEDier,              0x095
.equ ti.LeAcute,                        0x096
.equ ti.LeGrave,                        0x097
.equ ti.LeCaret,                        0x098
.equ ti.LeDier,                 0x099
.equ ti.LcapIAcute,             0x09A
.equ ti.LcapIGrave,             0x09B
.equ ti.LcapICaret,             0x09C
.equ ti.LcapIDier,              0x09D
.equ ti.LiAcute,                        0x09E
.equ ti.LiGrave,                        0x09F
.equ ti.LiCaret,                        0x0A0
.equ ti.LiDier,                 0x0A1
.equ ti.LcapOAcute,             0x0A2
.equ ti.LcapOGrave,             0x0A3
.equ ti.LcapOCaret,             0x0A4
.equ ti.LcapODier,              0x0A5
.equ ti.LoAcute,                        0x0A6
.equ ti.LoGrave,                        0x0A7
.equ ti.LoCaret,                        0x0A8
.equ ti.LoDier,                 0x0A9
.equ ti.LcapUAcute,             0x0AA
.equ ti.LcapUGrave,             0x0AB
.equ ti.LcapUCaret,             0x0AC
.equ ti.LcapUDier,              0x0AD
.equ ti.LuAcute,                        0x0AE
.equ ti.LuGrave,                        0x0AF
.equ ti.LuCaret,                        0x0B0
.equ ti.LuDier,                 0x0B1
.equ ti.LcapCCed,               0x0B2
.equ ti.LcCed,                  0x0B3
.equ ti.LcapNTilde,             0x0B4
.equ ti.LnTilde,                        0x0B5
.equ ti.Laccent,                        0x0B6
.equ ti.Lgrave,                 0x0B7
.equ ti.Ldieresis,              0x0B8
.equ ti.LquesDown,              0x0B9
.equ ti.LexclamDown,            0x0BA
.equ ti.Lalpha,                 0x0BB
.equ ti.Lbeta,                  0x0BC
.equ ti.Lgamma,                 0x0BD
.equ ti.LcapDelta,              0x0BE
.equ ti.Ldelta,                 0x0BF
.equ ti.Lepsilon,               0x0C0
.equ ti.LlBrack,                0x0C1
.equ ti.Llambda,                        0x0C2
.equ ti.Lmu,                    0x0C3
.equ ti.Lpi,                    0x0C4
.equ ti.Lrho,                   0x0C5
.equ ti.LcapSigma,              0x0C6
.equ ti.Lsigma,                 0x0C7
.equ ti.Ltau,                   0x0C8
.equ ti.Lphi,                   0x0C9
.equ ti.LcapOmega,              0x0CA
.equ ti.LxMean,                 0x0CB
.equ ti.LyMean,                 0x0CC
.equ ti.LsupX,                  0x0CD
.equ ti.Lellipsis,              0x0CE
.equ ti.Lleft,                  0x0CF
.equ ti.Lblock,                 0x0D0
.equ ti.Lper,                   0x0D1
.equ ti.Lhyphen,                        0x0D2
.equ ti.Larea,                  0x0D3
.equ ti.Ltemp,                  0x0D4
.equ ti.Lcube,                  0x0D5
.equ ti.Lenter,                 0x0D6
.equ ti.LimagI,                 0x0D7
.equ ti.Lphat,                  0x0D8
.equ ti.Lchi,                   0x0D9
.equ ti.LstatF,                 0x0DA
.equ ti.Llne,                   0x0DB
.equ ti.LlistL,                 0x0DC
.equ ti.LfinanN,                0x0DD
.equ ti.L2_r_paren,             0x0DE
.equ ti.LblockArrow,            0x0DF
.equ ti.LcurO,                  0x0E0
.equ ti.LcurO2,                 0x0E1
.equ ti.LcurOcapA,              0x0E2
.equ ti.LcurOa,                 0x0E3
.equ ti.LcurI,                  0x0E4
.equ ti.LcurI2,                 0x0E5
.equ ti.LcurIcapA,              0x0E6
.equ ti.LcurIa,                 0x0E7
.equ ti.LGline,                 0x0E8 ; = 0
.equ ti.LGthick,                        0x0E9 ; = 1
.equ ti.LGabove,                        0x0EA ; = 2
.equ ti.LGbelow,                        0x0EB ; = 3
.equ ti.LGpath,                 0x0EC ; = 4
.equ ti.LGanimate,              0x0ED ; = 5
.equ ti.LGdot,                  0x0EE ; = 6
.equ ti.LUpBlk,                 0x0EF ;Up arrow and Block in solver
.equ ti.LDnBlk,                 0x0F0 ;Down arrow and Block in solver
.equ ti.LcurFull,               0x0F1 ;note: must be last char (PutMap checks)

;(MenuCurrent) Values
;-----------------------------------
.equ ti.mConfirmation,          0x01
.equ ti.mApps,                  0x02
.equ ti.mProgramHome,           0x03
.equ ti.mPrgm_Run,               0x00
.equ ti.mPrgm_Edit,              0x01
.equ ti.mPrgm_New,               0x02
.equ ti.mZoom,                  0x04
.equ ti.mZoom_Zoom,              0x00
.equ ti.mZoom_Memory,            0x01
.equ ti.mDraw,                  0x05
.equ ti.mDraw_Draw,              0x00
.equ ti.mDraw_Points,            0x01
.equ ti.mDraw_Store,             0x02
.equ ti.mDraw_Background,       0x03
.equ ti.mStatPlots,             0x06
.equ ti.mStat,                  0x07
.equ ti.mStat_Edit,              0x00
.equ ti.mStat_Calc,              0x01
.equ ti.mStat_Tests,             0x02
.equ ti.mMath,                  0x08
.equ ti.mMath_Math,              0x00
.equ ti.mMath_Number,            0x01
.equ ti.mMath_Complex,           0x02
.equ ti.mMath_Prob,              0x03
.equ ti.mMath_Frac,              0x04
.equ ti.mTest,                  0x09
.equ ti.mTest_Test,              0x00
.equ ti.mTest_Logic,             0x01

.equ ti.mVars,                  0x0B
.equ ti.mVars_Vars,              0x00
.equ ti.mVars_YVars,             0x01
.equ ti.mVars_Colors,    0x02
.equ ti.mMemory,                        0x0C
.equ ti.mMatrix,                        0x0D
.equ ti.mMatrix_Name,            0x00
.equ ti.mMatrix_Math,            0x01
.equ ti.mMatrix_Edit,            0x02
.equ ti.mDistr,                 0x0E
.equ ti.mDistr_Distr,            0x00
.equ ti.mDistr_Draw,             0x01
.equ ti.mAngle,                 0x0F
.equ ti.mList,                  0x10
.equ ti.mList_Names,             0x00
.equ ti.mList_Ops,               0x01
.equ ti.mList_Math,              0x02
.equ ti.mCalculate,             0x11
.equ ti.mVarsWin,               0x15
.equ ti.mVarsWin_XY,             0x00
.equ ti.mVarsWin_TTh,            0x01
.equ ti.mVarsWin_UVW,            0x02
.equ ti.mVarsZoom,              0x16
.equ ti.mVarsZoom_ZXY,           0x00
.equ ti.mVarsZoom_ZT,            0x01
.equ ti.mVarsZoom_UVW,           0x02
.equ ti.mVarsGDB,               0x17
.equ ti.mVarsPics,              0x18
.equ ti.mVarsPics_Pics,          0x01
.equ ti.mVarsPics_Bckgrnds,              0x01
.equ ti.mVarsStrings,           0x19
.equ ti.mVarsStat,              0x1A
.equ ti.mVarsStat_XY,            0x00
.equ ti.mVarsStat_Sigma,                 0x01
.equ ti.mVarsStat_EQ,            0x02
.equ ti.mVarsStat_Test,          0x03
.equ ti.mVarsStat_Pts,           0x04
.equ ti.mVarsTable,             0x1B
.equ ti.mVarsYequ,              0x1C
.equ ti.mVarsParametric,                0x1D
.equ ti.mVarsPolar,             0x1E
.equ ti.mVarsFnOnOff,           0x1F
.equ ti.mMemReset,              0x20
.equ ti.mMemReset_RAM,           0x00
.equ ti.mMemReset_ROM,           0x01
.equ ti.mMemReset_All,           0x02
.equ ti.mMemMgmtDel,            0x21
.equ ti.mMemResetDefaults,      0x22
.equ ti.mMemResetRAMAll,                0x24
.equ ti.mMemResetROMVars,       0x25
.equ ti.mMemResetROMApps,       0x26
.equ ti.mMemResetROMAll,                0x27
.equ ti.mMemResetAll,           0x28
.equ ti.mGroup,                 0x29
.equ ti.mGroup_New,              0x00
.equ ti.mGroup_Ungroup,          0x01
.equ ti.mGroupVars,             0x2A
.equ ti.mProgramEdit,           0x2B
.equ ti.mPrgmEd_Ctrl,            0x00
.equ ti.mPrgmEd_IO,              0x01
.equ ti.mPrgmEd_Color,           0x02
.equ ti.mPrgmEd_Exec,            0x03
.equ ti.mPrgmZoom,              0x2C
.equ ti.mPrgmZoom_Zoom,          0x00
.equ ti.mPrgmZoom_Mem,           0x01
.equ ti.mPrgmDraw,              0x2D
.equ ti.mPrgmDraw_Draw,          0x00
.equ ti.mPrgmDraw_Pt,            0x01
.equ ti.mPrgmDraw_Store,                 0x02
.equ ti.mPrgmDraw_Bckgrnd,       0x03
.equ ti.mPrgmStatPlot,          0x2E
.equ ti.mPrgmSP_Plots,           0x00
.equ ti.mPrgmSP_Type,            0x01
.equ ti.mPrgmSP_Mark,            0x02
.equ ti.mPrgmStat,              0x2F
.equ ti.mPrgmStat_Edit,          0x00
.equ ti.mPrgmStat_Calc,          0x01
.equ ti.mPrgmStat_Tests,                 0x02
.equ ti.mPrgmMath,              0x30
.equ ti.mPrgmMath_Math,          0x00
.equ ti.mPrgmMath_Num,           0x01
.equ ti.mPrgmMath_Cplx,          0x02
.equ ti.mPrgmMath_Prob,          0x03
.equ ti.mPrgmMath_Frac,          0x04
.equ ti.mLink,                  0x31
.equ ti.mLink_Send,              0x00
.equ ti.mLink_Recieve,           0x01
.equ ti.mLinkTrasmit,           0x32
.equ ti.mLinkXmit_Xmit,          0x01
.equ ti.mGarbageCollect,                0x40
.equ ti.mSelectGroupVars,       0x41
.equ ti.mSelGrpVars_Sel,                 0x00
.equ ti.mSelGrpVars_Grp,                 0x01
.equ ti.mDuplicateName,         0x43
.equ ti.mCatalog,               0x46
.equ ti.mFinance,               0x22
.equ ti.mFinance_Calc,           0x00
.equ ti.mFinance_Vars,           0x01

;Keypress Equates
;-----------------------------------
.equ ti.kRight,                 0x001
.equ ti.kLeft,                  0x002
.equ ti.kUp,                    0x003
.equ ti.kDown,                  0x004
.equ ti.kEnter,                 0x005
.equ ti.kAlphaEnter,            0x006
.equ ti.kAlphaUp,               0x007
.equ ti.kAlphaDown,             0x008
.equ ti.kClear,                 0x009
.equ ti.kDel,                   0x00A
.equ ti.kIns,                   0x00B
.equ ti.kRecall,                        0x00C
.equ ti.kLastEnt,               0x00D
.equ ti.kBOL,                   0x00E
.equ ti.kEOL,                   0x00F

.equ ti.kSelAll,                        0x010
.equ ti.kUnselAll,              0x011
.equ ti.kLtoTI82,               0x012
.equ ti.kBackup,                        0x013
.equ ti.kRecieve,               0x014
.equ ti.kLnkQuit,               0x015
.equ ti.kTrans,                 0x016
.equ ti.kRename,                        0x017
.equ ti.kOverw,                 0x018
.equ ti.kOmit,                  0x019
.equ ti.kCont,                  0x01A
.equ ti.kSendID,                        0x01B
.equ ti.kSendSW,                        0x01C
.equ ti.kYes,                   0x01D
.equ ti.kNoWay,                 0x01E
.equ ti.kvSendType,             0x01F
.equ ti.kOverWAll,              0x020
.equ ti.kNo,                    0x025
.equ ti.kKReset,                        0x026
.equ ti.kApp,                   0x027
.equ ti.kDoug,                  0x028
.equ ti.kListflag,              0x029
.equ ti.menuStart,              0x02B
.equ ti.kAreYouSure,            0x02B
.equ ti.kAppsMenu,              0x02C
.equ ti.kPrgm,                  0x02D
.equ ti.kZoom,                  0x02E
.equ ti.kDraw,                  0x02F
.equ ti.kSPlot,                 0x030
.equ ti.kStat,                  0x031
.equ ti.kMath,                  0x032
.equ ti.kTest,                  0x033
.equ ti.kChar,                  0x034
.equ ti.kVars,                  0x035
.equ ti.kMem,                   0x036
.equ ti.kMatrix,                        0x037
.equ ti.kDist,                  0x038
.equ ti.kAngle,                 0x039
.equ ti.kList,                  0x03A
.equ ti.kCalc,                  0x03B
.equ ti.kFin,                   0x03C
.equ ti.menuEnd,                        ti.kFin
.equ ti.kCatalog,               0x03E
.equ ti.kInputDone,             0x03F
.equ ti.kOff,                   ti.kInputDone
.equ ti.kQuit,                  0x040
.equ ti.appStart,               ti.kQuit
.equ ti.kLinkIO,                        0x041
.equ ti.kMatrixEd,              0x042
.equ ti.kStatEd,                        0x043
.equ ti.kGraph,                 0x044
.equ ti.kMode,                  0x045
.equ ti.kPrgmEd,                        0x046 ;PROGRAM EDIT
.equ ti.kPrgmCr,                        0x047 ;PROGRAM CREATE
.equ ti.kWindow,                        0x048 ;RANGE EDITOR
.equ ti.kYequ,                  0x049 ;EQUATION EDITOR
.equ ti.kTable,                 0x04A ;TABLE EDITOR
.equ ti.kTblSet,                        0x04B ;TABLE SET
.equ ti.kChkRAM,                        0x04C ;CHECK RAM (About screen)
.equ ti.kDelMem,                        0x04D ;DELETE MEM
.equ ti.kResetMem,              0x04E ;RESET MEM
.equ ti.kResetDef,              0x04F ;RESET DEFAULT
.equ ti.kPrgmInput,             0x050 ;PROGRAM INPUT
.equ ti.kZFactEd,               0x051 ;ZOOM FACTOR EDITOR
.equ ti.kError,                 0x052 ;ERROR
.equ ti.kSolveTVM,              0x053 ;TVM SOLVER
.equ ti.kSolveRoot,             0x054 ;SOLVE EDITOR
.equ ti.kStatP,                 0x055 ;stat plot
.equ ti.kInfStat,               0x056 ;Inferential Statistic
.equ ti.kFormat,                        0x057 ;FORMAT
.equ ti.kExtApps,               0x058 ;External Applications.		NEW
.equ ti.kNewApps,               0x059 ;New Apps for Cerberus.
.equ ti.append,                 ti.kNewApps
.equ ti.echoStart1,             0x05A
.equ ti.kTrace,                 0x05A
.equ ti.kZFit,                  0x05B
.equ ti.kZIn,                   0x05C
.equ ti.kZOut,                  0x05D
.equ ti.kZPrev,                 0x05E
.equ ti.kBox,                   0x05F
.equ ti.kDecml,                 0x060
.equ ti.kSetZm,                 0x061
.equ ti.kSquar,                 0x062
.equ ti.kStd,                   0x063
.equ ti.kTrig,                  0x064
.equ ti.kUsrZm,                 0x065
.equ ti.kZSto,                  0x066
.equ ti.kZInt,                  0x067
.equ ti.kZStat,                 0x068
.equ ti.echoStart2,             0x069
.equ ti.kSelect,                        0x069
.equ ti.kCircl,                 0x06A
.equ ti.kClDrw,                 0x06B
.equ ti.kLine,                  0x06C
.equ ti.kPen,                   0x06D
.equ ti.kPtChg,                 0x06E
.equ ti.kPtOff,                 0x06F
.equ ti.kPtOn,                  0x070
.equ ti.kVert,                  0x071
.equ ti.kHoriz,                 0x072
.equ ti.kText,                  0x073
.equ ti.kTanLn,                 0x074
.equ ti.kEval,                  0x075
.equ ti.kInters,                        0x076
.equ ti.kDYDX,                  0x077
.equ ti.kFnIntg,                        0x078
.equ ti.kRootG,                 0x079
.equ ti.kDYDT,                  0x07A
.equ ti.kDXDT,                  0x07B
.equ ti.kDRDo,                  0x07C
.equ ti.KGFMin,                 0x07D
.equ ti.KGFMax,                 0x07E
.equ ti.EchoStart,              0x07F
.equ ti.kListName,              0x07F
.equ ti.kAdd,                   0x080
.equ ti.kSub,                   0x081
.equ ti.kMul,                   0x082
.equ ti.kDiv,                   0x083
.equ ti.kExpon,                 0x084
.equ ti.kLParen,                        0x085
.equ ti.kRParen,                        0x086
.equ ti.kLBrack,                        0x087
.equ ti.kRBrack,                        0x088
.equ ti.kShade,                 0x089
.equ ti.kStore,                 0x08A
.equ ti.kComma,                 0x08B
.equ ti.kChs,                   0x08C
.equ ti.kDecPnt,                        0x08D
.equ ti.k0,                     0x08E
.equ ti.k1,                     0x08F
.equ ti.k2,                     0x090
.equ ti.k3,                     0x091
.equ ti.k4,                     0x092
.equ ti.k5,                     0x093
.equ ti.k6,                     0x094
.equ ti.k7,                     0x095
.equ ti.k8,                     0x096
.equ ti.k9,                     0x097
.equ ti.kEE,                    0x098
.equ ti.kSpace,                 0x099
.equ ti.kCapA,                  0x09A
.equ ti.kCapB,                  0x09B
.equ ti.kCapC,                  0x09C
.equ ti.kCapD,                  0x09D
.equ ti.kCapE,                  0x09E
.equ ti.kCapF,                  0x09F
.equ ti.kCapG,                  0x0A0
.equ ti.kCapH,                  0x0A1
.equ ti.kCapI,                  0x0A2
.equ ti.kCapJ,                  0x0A3
.equ ti.kCapK,                  0x0A4
.equ ti.kCapL,                  0x0A5
.equ ti.kCapM,                  0x0A6
.equ ti.kCapN,                  0x0A7
.equ ti.kCapO,                  0x0A8
.equ ti.kCapP,                  0x0A9
.equ ti.kCapQ,                  0x0AA
.equ ti.kCapR,                  0x0AB
.equ ti.kCapS,                  0x0AC
.equ ti.kCapT,                  0x0AD
.equ ti.kCapU,                  0x0AE
.equ ti.kCapV,                  0x0AF
.equ ti.kCapW,                  0x0B0
.equ ti.kCapX,                  0x0B1
.equ ti.kCapY,                  0x0B2
.equ ti.kCapZ,                  0x0B3
.equ ti.kVarx,                  0x0B4
.equ ti.kPi,                    0x0B5
.equ ti.kInv,                   0x0B6
.equ ti.kSin,                   0x0B7
.equ ti.kASin,                  0x0B8
.equ ti.kCos,                   0x0B9
.equ ti.kACos,                  0x0BA
.equ ti.kTan,                   0x0BB
.equ ti.kATan,                  0x0BC
.equ ti.kSquare,                        0x0BD
.equ ti.kSqrt,                  0x0BE
.equ ti.kLn,                    0x0BF
.equ ti.kExp,                   0x0C0
.equ ti.kLog,                   0x0C1
.equ ti.kALog,                  0x0C2
.equ ti.kToABC,                 0x0C3
.equ ti.kClrTbl,                        0x0C4
.equ ti.kAns,                   0x0C5
.equ ti.kColon,                 0x0C6
.equ ti.kNDeriv,                        0x0C7
.equ ti.kFnInt,                 0x0C8
.equ ti.kRoot,                  0x0C9
.equ ti.kQuest,                 0x0CA
.equ ti.kQuote,                 0x0CB
.equ ti.kTheta,                 0x0CC
.equ ti.kIf,                    0x0CD
.equ ti.kThen,                  0x0CE
.equ ti.kElse,                  0x0CF
.equ ti.kFor,                   0x0D0
.equ ti.kWhile,                 0x0D1
.equ ti.kRepeat,                        0x0D2
.equ ti.kEnd,                   0x0D3
.equ ti.kPause,                 0x0D4
.equ ti.kLbl,                   0x0D5
.equ ti.kGoto,                  0x0D6
.equ ti.kISG,                   0x0D7
.equ ti.kDSL,                   0x0D8
.equ ti.kMenu,                  0x0D9
.equ ti.kExec,                  0x0DA
.equ ti.kReturn,                        0x0DB
.equ ti.kStop,                  0x0DC
.equ ti.kInput,                 0x0DD
.equ ti.kPrompt,                        0x0DE
.equ ti.kDisp,                  0x0DF
.equ ti.kDispG,                 0x0E0
.equ ti.kDispT,                 0x0E1
.equ ti.kOutput,                        0x0E2
.equ ti.kGetKey,                        0x0E3
.equ ti.kClrHome,               0x0E4
.equ ti.kPrtScr,                        0x0E5
.equ ti.kSinH,                  0x0E6
.equ ti.kCosH,                  0x0E7
.equ ti.kTanH,                  0x0E8
.equ ti.kASinH,                 0x0E9
.equ ti.kACosH,                 0x0EA
.equ ti.kATanH,                 0x0EB
.equ ti.kLBrace,                        0x0EC
.equ ti.kRBrace,                        0x0ED
.equ ti.kI,                     0x0EE
.equ ti.kCONSTeA,               0x0EF
.equ ti.kPlot3,                 0x0F0
.equ ti.kFMin,                  0x0F1
.equ ti.kFMax,                  0x0F2
.equ ti.kL1A,                   0x0F3
.equ ti.kL2A,                   0x0F4
.equ ti.kL3A,                   0x0F5
.equ ti.kL4A,                   0x0F6
.equ ti.kL5A,                   0x0F7
.equ ti.kL6A,                   0x0F8
.equ ti.kunA,                   0x0F9
.equ ti.kvnA,                   0x0FA
.equ ti.kwnA,                   0x0FB

; THIS KEY MEANS THAT THE KEY PRESS IS ONE THAT ECHOS
; INTO A BUFFER, AND IT IS A 2 BYTE KEY CODE, GO LOOK AT
; (EXTECHO) FOR THE KEY VALUE
;--------------------------------------------------------
.equ ti.kExtendEcho,            0x0FE

.equ ti.kE1BT,                  0
.equ ti.kDrawInv,               ti.kE1BT
.equ ti.kDrawF,                 ti.kE1BT+1
.equ ti.kPixelOn,               ti.kE1BT+2
.equ ti.kPixelOff,              ti.kE1BT+3
.equ ti.kPxlTest,               ti.kE1BT+4
.equ ti.kRCGDB,                 ti.kE1BT+5
.equ ti.kRCPic,                 ti.kE1BT+6
.equ ti.kSTGDB,                 ti.kE1BT+7
.equ ti.kSTPic,                 ti.kE1BT+8
.equ ti.kAbs,                   ti.kE1BT+9
.equ ti.kTequ,          ti.kE1BT+10 ;==
.equ ti.kTNoteQ,                        ti.kE1BT+11 ;<>
.equ ti.kTGT,                   ti.kE1BT+12 ;>
.equ ti.kTGTE,                  ti.kE1BT+13 ;>=
.equ ti.kTLT,                   ti.kE1BT+14 ;<
.equ ti.kTLTE,                  ti.kE1BT+15 ;<=
.equ ti.kAnd,                   ti.kE1BT+16
.equ ti.kOr,                    ti.kE1BT+17
.equ ti.kXor,                   ti.kE1BT+18
.equ ti.kNot,                   ti.kE1BT+19
.equ ti.kLR1,                   ti.kE1BT+20
.equ ti.kXRoot,                 ti.kE1BT+21
.equ ti.kCube,                  ti.kE1BT+22
.equ ti.kCbRt,                  ti.kE1BT+23 ;Cube ROOT
.equ ti.kToDec,                 ti.kE1BT+24
.equ ti.kCubicR,                        ti.kE1BT+25
.equ ti.kQuartR,                        ti.kE1BT+26
.equ ti.kPlot1,                 ti.kE1BT+27
.equ ti.kPlot2,                 ti.kE1BT+28
.equ ti.kRound,                 ti.kE1BT+29
.equ ti.kIPart,                 ti.kE1BT+30
.equ ti.kFPart,                 ti.kE1BT+31
.equ ti.kInt,                   ti.kE1BT+32
.equ ti.kRand,                  ti.kE1BT+33
.equ ti.kNPR,                   ti.kE1BT+34
.equ ti.kNCR,                   ti.kE1BT+35
.equ ti.kXFactorial,            ti.kE1BT+36
.equ ti.kRad,                   ti.kE1BT+37
.equ ti.kDegr,                  ti.kE1BT+38 ;DEGREES CONV
.equ ti.kAPost,                 ti.kE1BT+39
.equ ti.kToDMS,                 ti.kE1BT+40
.equ ti.kRToPo,                 ti.kE1BT+41 ;R
.equ ti.kRToPr,                 ti.kE1BT+42
.equ ti.kPToRx,                 ti.kE1BT+43
.equ ti.kPToRy,                 ti.kE1BT+44
.equ ti.kRowSwap,               ti.kE1BT+45
.equ ti.kRowPlus,               ti.kE1BT+46
.equ ti.kTimRow,                        ti.kE1BT+47
.equ ti.kTRowP,                 ti.kE1BT+48
.equ ti.kSortA,                 ti.kE1BT+49
.equ ti.kSortD,                 ti.kE1BT+50
.equ ti.kSeq,                   ti.kE1BT+51
.equ ti.kMin,                   ti.kE1BT+52
.equ ti.kMax,                   ti.kE1BT+53
.equ ti.kMean,                  ti.kE1BT+54
.equ ti.kMedian,                        ti.kE1BT+55
.equ ti.kSum,                   ti.kE1BT+56
.equ ti.kProd,                  ti.kE1BT+57
.equ ti.kDet,                   ti.kE1BT+58
.equ ti.kTransp,                        ti.kE1BT+59
.equ ti.kDim,                   ti.kE1BT+60
.equ ti.kFill,                  ti.kE1BT+61
.equ ti.kIdent,                 ti.kE1BT+62
.equ ti.kRandm,                 ti.kE1BT+63
.equ ti.kAug,                   ti.kE1BT+64
.equ ti.kOneVar,                        ti.kE1BT+65
.equ ti.kTwoVar,                        ti.kE1BT+66
.equ ti.kLR,                    ti.kE1BT+67
.equ ti.kLRExp,                 ti.kE1BT+68
.equ ti.kLRLn,                  ti.kE1BT+69
.equ ti.kLRPwr,                 ti.kE1BT+70
.equ ti.kMedMed,                        ti.kE1BT+71
.equ ti.kQuad,                  ti.kE1BT+72
.equ ti.kClrLst,                        ti.kE1BT+73
.equ ti.kHist,                  ti.kE1BT+74
.equ ti.kxyLine,                        ti.kE1BT+75
.equ ti.kScatter,               ti.kE1BT+76
.equ ti.kmRad,                  ti.kE1BT+77
.equ ti.kmDeg,                  ti.kE1BT+78
.equ ti.kmNormF,                        ti.kE1BT+79
.equ ti.kmSci,                  ti.kE1BT+80
.equ ti.kmEng,                  ti.kE1BT+81
.equ ti.kmFloat,                        ti.kE1BT+82
.equ ti.kFix,                   ti.kE1BT+83
.equ ti.kSplitOn,               ti.kE1BT+84
.equ ti.kFullScreen,            ti.kE1BT+85
.equ ti.kStndrd,                        ti.kE1BT+86
.equ ti.kParam,                 ti.kE1BT+87
.equ ti.kPolar,                 ti.kE1BT+88
.equ ti.kSeqG,                  ti.kE1BT+89
.equ ti.kAFillOn,               ti.kE1BT+90
.equ ti.kAFillOff,              ti.kE1BT+91
.equ ti.kACalcOn,               ti.kE1BT+92
.equ ti.kACalcOff,              ti.kE1BT+93
.equ ti.kFNOn,                  ti.kE1BT+94
.equ ti.kFNOff,                 ti.kE1BT+95
.equ ti.kPlotsOn,               ti.kE1BT+96
.equ ti.kPlotsOff,              ti.kE1BT+97
.equ ti.kPixelChg,              ti.kE1BT+98
.equ ti.kSendMBL,               ti.kE1BT+99
.equ ti.kRecvMBL,               ti.kE1BT+100
.equ ti.kBoxPlot,               ti.kE1BT+101
.equ ti.kBoxIcon,               ti.kE1BT+102
.equ ti.kCrossIcon,             ti.kE1BT+103
.equ ti.kDotIcon,               ti.kE1BT+104
.equ ti.kE2BT,                  ti.kE1BT+105
.equ ti.kSeqential,             ti.kE2BT
.equ ti.kSimulG,                        ti.kE2BT+1
.equ ti.kPolarG,                        ti.kE2BT+2
.equ ti.kRectG,                 ti.kE2BT+3
.equ ti.kCoordOn,               ti.kE2BT+4
.equ ti.kCoordOff,              ti.kE2BT+5
.equ ti.kDrawLine,              ti.kE2BT+6
.equ ti.kDrawDot,               ti.kE2BT+7
.equ ti.kAxisOn,                        ti.kE2BT+8
.equ ti.kAxisOff,               ti.kE2BT+9
.equ ti.kGridOn,                        ti.kE2BT+10
.equ ti.kGridOff,               ti.kE2BT+11
.equ ti.kLblOn,                 ti.kE2BT+12
.equ ti.kLblOff,                        ti.kE2BT+13
.equ ti.kL1,                    ti.kE2BT+14
.equ ti.kL2,                    ti.kE2BT+15
.equ ti.kL3,                    ti.kE2BT+16
.equ ti.kL4,                    ti.kE2BT+17
.equ ti.kL5,                    ti.kE2BT+18
.equ ti.kL6,                    ti.kE2BT+19

;These keys are laid on top of existing keys to
;enable localization in the inferential stats editor.
;----------------------------------------------------
.equ ti.kinfData,               ti.kL1
.equ ti.kinfStats,              ti.kL1+1
.equ ti.kinfYes,                        ti.kL1+2
.equ ti.kinfNo,                 ti.kL1+3
.equ ti.kinfCalc,               ti.kL1+4
.equ ti.kinfDraw,               ti.kL1+5
.equ ti.kinfAlt1ne,             ti.kL1+6
.equ ti.kinfAlt1lt,             ti.kL1+7
.equ ti.kinfAlt1gt,             ti.kL1+8
.equ ti.kinfAlt2ne,             ti.kL1+9
.equ ti.kinfAlt2lt,             ti.kL1+10
.equ ti.kinfAlt2gt,             ti.kL1+11
.equ ti.kinfAlt3ne,             ti.kL1+12
.equ ti.kinfAlt3lt,             ti.kL1+13
.equ ti.kinfAlt3gt,             ti.kL1+14
.equ ti.kinfAlt4ne,             ti.kL1+15
.equ ti.kinfAlt4lt,             ti.kL1+16
.equ ti.kinfAlt4gt,             ti.kL1+17
.equ ti.kinfAlt5ne,             ti.kL1+18
.equ ti.kinfAlt5lt,             ti.kL1+19
.equ ti.kinfAlt5gt,             ti.kL1+20
.equ ti.kinfAlt6ne,             ti.kL1+21
.equ ti.kinfAlt6lt,             ti.kL1+22
.equ ti.kinfAlt6gt,             ti.kL1+23
.equ ti.kMatA,                  ti.kE2BT+20
.equ ti.kMatB,                  ti.kE2BT+21
.equ ti.kMatC,                  ti.kE2BT+22
.equ ti.kMatD,                  ti.kE2BT+23
.equ ti.kMatE,                  ti.kE2BT+24
.equ ti.kXmin,                  ti.kE2BT+25
.equ ti.kXmax,                  ti.kE2BT+26
.equ ti.kXscl,                  ti.kE2BT+27
.equ ti.kYmin,                  ti.kE2BT+28
.equ ti.kYmax,                  ti.kE2BT+29
.equ ti.kYscl,                  ti.kE2BT+30
.equ ti.kTmin,                  ti.kE2BT+31
.equ ti.kTmax,                  ti.kE2BT+32
.equ ti.kTStep,                 ti.kE2BT+33
.equ ti.kOmin,                  ti.kE2BT+34
.equ ti.kOmax,                  ti.kE2BT+35
.equ ti.kOStep,                 ti.kE2BT+36
.equ ti.ku0,                    ti.kE2BT+37
.equ ti.kv0,                    ti.kE2BT+38
.equ ti.knMin,                  ti.kE2BT+39
.equ ti.knMax,                  ti.kE2BT+40
.equ ti.kDeltaY,                        ti.kE2BT+41
.equ ti.kDeltaX,                        ti.kE2BT+42
.equ ti.kZXmin,                 ti.kE2BT+43
.equ ti.kZXmax,                 ti.kE2BT+44
.equ ti.kZXscl,                 ti.kE2BT+45
.equ ti.kZYmin,                 ti.kE2BT+46
.equ ti.kZYmax,                 ti.kE2BT+47
.equ ti.kZYscl,                 ti.kE2BT+48
.equ ti.kZTmin,                 ti.kE2BT+49
.equ ti.kZTmax,                 ti.kE2BT+50
.equ ti.kZTStep,                        ti.kE2BT+51
.equ ti.kZOmin,                 ti.kE2BT+52
.equ ti.kZOmax,                 ti.kE2BT+53
.equ ti.kZOStep,                        ti.kE2BT+54
.equ ti.kZu0,                   ti.kE2BT+55
.equ ti.kZv0,                   ti.kE2BT+56
.equ ti.kZnMin,                 ti.kE2BT+57
.equ ti.kZnMax,                 ti.kE2BT+58
.equ ti.kDelLast,               ti.kE2BT+59
.equ ti.kSinReg,                        ti.kE2BT+60
.equ ti.kConstE,                        ti.kE2BT+61
.equ ti.kPic1,                  ti.kE2BT+62
.equ ti.kPic2,                  ti.kE2BT+63
.equ ti.kPic3,                  ti.kE2BT+64
.equ ti.kDelVar,                        ti.kE2BT+65
.equ ti.kGetCalc,               ti.kE2BT+66
.equ ti.kRealM,                 ti.kE2BT+67
.equ ti.kPolarM,                        ti.kE2BT+68
.equ ti.kRectM,                 ti.kE2BT+69
.equ ti.kuv,                    ti.kE2BT+70 ;U vs V
.equ ti.kvw,                    ti.kE2BT+71 ;V vs W
.equ ti.kuw,                    ti.kE2BT+72 ;U vs W
.equ ti.kFinPMTend,             ti.kE2BT+73
.equ ti.kFinPMTbeg,             ti.kE2BT+74
.equ ti.kGraphStyle,            ti.kE2BT+75
.equ ti.kExprOn,                        ti.kE2BT+76
.equ ti.kExprOff,               ti.kE2BT+77
.equ ti.kStatA,                 ti.kE2BT+78
.equ ti.kStatB,                 ti.kE2BT+79
.equ ti.kStatC,                 ti.kE2BT+80
.equ ti.kCorr,                  ti.kE2BT+81
.equ ti.kStatD,                 ti.kE2BT+82
.equ ti.kStatE,                 ti.kE2BT+83
.equ ti.kRegEq,                 ti.kE2BT+84
.equ ti.kMinX,                  ti.kE2BT+85
.equ ti.kQ1,                    ti.kE2BT+86
.equ ti.kMD,                    ti.kE2BT+87
.equ ti.kQ3,                    ti.kE2BT+88
.equ ti.kMaxX,                  ti.kE2BT+89
.equ ti.kStatX1,                        ti.kE2BT+90
.equ ti.kStatY1,                        ti.kE2BT+91
.equ ti.kStatX2,                        ti.kE2BT+92
.equ ti.kStatY2,                        ti.kE2BT+93
.equ ti.kStatX3,                        ti.kE2BT+94
.equ ti.kStatY3,                        ti.kE2BT+95
.equ ti.kTblMin,                        ti.kE2BT+96
.equ ti.kTblStep,               ti.kE2BT+97
.equ ti.kSetupLst,              ti.kE2BT+98
.equ ti.kClrAllLst,             ti.kE2BT+99
.equ ti.kLogistic,              ti.kE2BT+100
.equ ti.kZTest,                 ti.kE2BT+101
.equ ti.kTTest,                 ti.kE2BT+102
.equ ti.k2SampZTest,            ti.kE2BT+103
.equ ti.k2SampTTest,            ti.kE2BT+104
.equ ti.k1PropZTest,            ti.kE2BT+105
.equ ti.k2PropZTest,            ti.kE2BT+106
.equ ti.kChiTest,               ti.kE2BT+107
.equ ti.k2SampFTest,            ti.kE2BT+108
.equ ti.kZIntVal,               ti.kE2BT+109
.equ ti.kTIntVal,               ti.kE2BT+110
.equ ti.k2SampTInt,             ti.kE2BT+111
.equ ti.k2SampZInt,             ti.kE2BT+112
.equ ti.k1PropZInt,             ti.kE2BT+113
.equ ti.k2PropZInt,             ti.kE2BT+114
.equ ti.kDNormal,               ti.kE2BT+115
.equ ti.kInvNorm,               ti.kE2BT+116
.equ ti.kDT,                    ti.kE2BT+117
.equ ti.kChi,                   ti.kE2BT+118
.equ ti.kDF,                    ti.kE2BT+119
.equ ti.kBinPDF,                        ti.kE2BT+120
.equ ti.kBinCDF,                        ti.kE2BT+121
.equ ti.kPoiPDF,                        ti.kE2BT+122
.equ ti.kPoiCDF,                        ti.kE2BT+123
.equ ti.kun,                    ti.kE2BT+124
.equ ti.kvn,                    ti.kE2BT+125
.equ ti.kwn,                    ti.kE2BT+126
.equ ti.kRecn,                  ti.kE2BT+127
.equ ti.kPlotStart,             ti.kE2BT+128
.equ ti.kZPlotStart,            ti.kE2BT+129 ;recursion n
.equ ti.kXFact,                 ti.kE2BT+130 ;PlotStart
.equ ti.kYFact,                 ti.kE2BT+131 ;ZPlotStart
.equ ti.kANOVA,                 ti.kE2BT+132 ;XFact
.equ ti.kMaxY,                  ti.kE2BT+133 ;YFact
.equ ti.kWebOn,                 ti.kE2BT+134 ;MinY
.equ ti.kWebOff,                        ti.kE2BT+135 ;MaxY
.equ ti.kTblInput,              ti.kE2BT+136 ;WEB ON
.equ ti.kGeoPDF,                        ti.kE2BT+137 ;WEB OFF
.equ ti.kGeoCDF,                        ti.kE2BT+138 ;WEB OFF
.equ ti.kShadeNorm,             ti.kE2BT+139
.equ ti.kShadeT,                        ti.kE2BT+140
.equ ti.kShadeChi,              ti.kE2BT+141
.equ ti.kShadeF,                        ti.kE2BT+142
.equ ti.kPlotStep,              ti.kE2BT+143
.equ ti.kZPlotStep,             ti.kE2BT+144
.equ ti.kLinRegtTest,           ti.kE2BT+145
.equ ti.KMGT,                   ti.kE2BT+146 ;VERT SPLIT
.equ ti.kSelectA,               ti.kE2BT+147
.equ ti.kZFitA,                 ti.kE2BT+148
.equ ti.kE2BT_End,              ti.kZFitA

; THIS KEY MEANS THAT IT IS A 2 BYTE KEYCODE
; THERE ARE 3 OF THESE KEYS; BE CAREFUL WITH USAGE
;--------------------------------------------------------
.equ ti.kExtendEcho2,           0x0FC

;More 2 Byte Keys
;-------------------------------------
.equ ti.kE2BT2,                 0x00
.equ ti.kGDB1,                  ti.kE2BT2
.equ ti.kGDB2,                  ti.kE2BT2+1
.equ ti.kGDB3,                  ti.kE2BT2+2
.equ ti.kY1,                    ti.kE2BT2+3
.equ ti.kY2,                    ti.kE2BT2+4
.equ ti.kY3,                    ti.kE2BT2+5
.equ ti.kY4,                    ti.kE2BT2+6
.equ ti.kY5,                    ti.kE2BT2+7
.equ ti.kY6,                    ti.kE2BT2+8
.equ ti.kY7,                    ti.kE2BT2+9
.equ ti.kY8,                    ti.kE2BT2+10
.equ ti.kY9,                    ti.kE2BT2+11
.equ ti.kY0,                    ti.kE2BT2+12
.equ ti.kX1T,                   ti.kE2BT2+13
.equ ti.kY1T,                   ti.kE2BT2+14
.equ ti.kX2T,                   ti.kE2BT2+15
.equ ti.kY2T,                   ti.kE2BT2+16
.equ ti.kX3T,                   ti.kE2BT2+17
.equ ti.kY3T,                   ti.kE2BT2+18
.equ ti.kX4T,                   ti.kE2BT2+19
.equ ti.kY4T,                   ti.kE2BT2+20
.equ ti.kX5T,                   ti.kE2BT2+21
.equ ti.kY5T,                   ti.kE2BT2+22
.equ ti.kX6T,                   ti.kE2BT2+23
.equ ti.kY6T,                   ti.kE2BT2+24
.equ ti.kR1,                    ti.kE2BT2+25
.equ ti.kR2,                    ti.kE2BT2+26
.equ ti.kR3,                    ti.kE2BT2+27
.equ ti.kR4,                    ti.kE2BT2+28
.equ ti.kR5,                    ti.kE2BT2+29
.equ ti.kR6,                    ti.kE2BT2+30
.equ ti.kGDB4,                  ti.kE2BT2+31
.equ ti.kGDB5,                  ti.kE2BT2+32
.equ ti.kGDB6,                  ti.kE2BT2+33
.equ ti.kPic4,                  ti.kE2BT2+34
.equ ti.kPic5,                  ti.kE2BT2+35
.equ ti.kPic6,                  ti.kE2BT2+36
.equ ti.kGDB7,                  ti.kE2BT2+37
.equ ti.kGDB8,                  ti.kE2BT2+38
.equ ti.kGDB9,                  ti.kE2BT2+39
.equ ti.kGDB0,                  ti.kE2BT2+40
.equ ti.kPic7,                  ti.kE2BT2+41
.equ ti.kPic8,                  ti.kE2BT2+42
.equ ti.kPic9,                  ti.kE2BT2+43
.equ ti.kPic0,                  ti.kE2BT2+44
.equ ti.kStatN,                 ti.kE2BT2+45
.equ ti.kXMean,                 ti.kE2BT2+46
.equ ti.kConj,                  ti.kE2BT2+47
.equ ti.kReal,                  ti.kE2BT2+48
.equ ti.kFAngle,                        ti.kE2BT2+49
.equ ti.kLCM,                   ti.kE2BT2+50
.equ ti.kGCD,                   ti.kE2BT2+51
.equ ti.kRandInt,               ti.kE2BT2+52
.equ ti.kRandNorm,              ti.kE2BT2+53
.equ ti.kToPolar,               ti.kE2BT2+54
.equ ti.kToRect,                        ti.kE2BT2+55
.equ ti.kYMean,                 ti.kE2BT2+56
.equ ti.kStdX,                  ti.kE2BT2+57
.equ ti.kStdX1,                 ti.kE2BT2+58
.equ ti.kw0,                    ti.kE2BT2+59
.equ ti.kMatF,                  ti.kE2BT2+60
.equ ti.kMatG,                  ti.kE2BT2+61
.equ ti.kMatRH,                 ti.kE2BT2+62
.equ ti.kMatI,                  ti.kE2BT2+63
.equ ti.kMatJ,                  ti.kE2BT2+64
.equ ti.kYMean1,                        ti.kE2BT2+65
.equ ti.kStdY,                  ti.kE2BT2+66
.equ ti.kStdY1,                 ti.kE2BT2+67
.equ ti.kMatToLst,              ti.kE2BT2+68
.equ ti.kLstToMat,              ti.kE2BT2+69
.equ ti.kCumSum,                        ti.kE2BT2+70
.equ ti.kDeltaLst,              ti.kE2BT2+71
.equ ti.kStdDev,                        ti.kE2BT2+72
.equ ti.kVariance,              ti.kE2BT2+73
.equ ti.kLength,                        ti.kE2BT2+74
.equ ti.kEquToStrng,            ti.kE2BT2+75
.equ ti.kStrngToequ,            ti.kE2BT2+76
.equ ti.kExpr,                  ti.kE2BT2+77
.equ ti.kSubStrng,              ti.kE2BT2+78
.equ ti.kInStrng,               ti.kE2BT2+79
.equ ti.kStr1,                  ti.kE2BT2+80
.equ ti.kStr2,                  ti.kE2BT2+81
.equ ti.kStr3,                  ti.kE2BT2+82
.equ ti.kStr4,                  ti.kE2BT2+83
.equ ti.kStr5,                  ti.kE2BT2+84
.equ ti.kStr6,                  ti.kE2BT2+85
.equ ti.kStr7,                  ti.kE2BT2+86
.equ ti.kStr8,                  ti.kE2BT2+87
.equ ti.kStr9,                  ti.kE2BT2+88
.equ ti.kStr0,                  ti.kE2BT2+89
.equ ti.kFinN,                  ti.kE2BT2+90
.equ ti.kFinI,                  ti.kE2BT2+91
.equ ti.kFinPV,                 ti.kE2BT2+92
.equ ti.kFinPMT,                        ti.kE2BT2+93
.equ ti.kFinFV,                 ti.kE2BT2+94
.equ ti.kFinPY,                 ti.kE2BT2+95
.equ ti.kFinCY,                 ti.kE2BT2+96
.equ ti.kFinFPMT,               ti.kE2BT2+97
.equ ti.kFinFI,                 ti.kE2BT2+98
.equ ti.kFinFPV,                        ti.kE2BT2+99
.equ ti.kFinFN,                 ti.kE2BT2+100
.equ ti.kFinFFV,                        ti.kE2BT2+101
.equ ti.kFinNPV,                        ti.kE2BT2+102
.equ ti.kFinIRR,                        ti.kE2BT2+103
.equ ti.kFinBAL,                        ti.kE2BT2+104
.equ ti.kFinPRN,                        ti.kE2BT2+105
.equ ti.kFinINT,                        ti.kE2BT2+106
.equ ti.kSumX,                  ti.kE2BT2+107
.equ ti.kSumX2,                 ti.kE2BT2+108
.equ ti.kFinToNom,              ti.kE2BT2+109
.equ ti.kFinToEff,              ti.kE2BT2+110
.equ ti.kFinDBD,                        ti.kE2BT2+111
.equ ti.kStatVP,                        ti.kE2BT2+112
.equ ti.kStatZ,                 ti.kE2BT2+113
.equ ti.kStatT,                 ti.kE2BT2+114
.equ ti.kStatChi,               ti.kE2BT2+115
.equ ti.kStatF,                 ti.kE2BT2+116
.equ ti.kStatDF,                        ti.kE2BT2+117
.equ ti.kStatPhat,              ti.kE2BT2+118
.equ ti.kStatPhat1,             ti.kE2BT2+119
.equ ti.kStatPhat2,             ti.kE2BT2+120
.equ ti.kStatMeanX1,            ti.kE2BT2+121
.equ ti.kStatMeanX2,            ti.kE2BT2+122
.equ ti.kStatStdX1,             ti.kE2BT2+123
.equ ti.kStatStdX2,             ti.kE2BT2+124
.equ ti.kStatStdXP,             ti.kE2BT2+125
.equ ti.kStatN1,                        ti.kE2BT2+126
.equ ti.kStatN2,                        ti.kE2BT2+127
.equ ti.kStatLower,             ti.kE2BT2+128
.equ ti.kStatUpper,             ti.kE2BT2+129
.equ ti.kuw0,                   ti.kE2BT2+130
.equ ti.kImag,                  ti.kE2BT2+131
.equ ti.kSumY,                  ti.kE2BT2+132
.equ ti.kXres,                  ti.kE2BT2+133
.equ ti.kStat_s,                        ti.kE2BT2+134
.equ ti.kSumY2,                 ti.kE2BT2+135
.equ ti.kSumXY,                 ti.kE2BT2+136
.equ ti.kuXres,                 ti.kE2BT2+137
.equ ti.kModBox,                        ti.kE2BT2+138
.equ ti.kNormProb,              ti.kE2BT2+139
.equ ti.kNormalPDF,             ti.kE2BT2+140
.equ ti.kTPDF,                  ti.kE2BT2+141
.equ ti.kChiPDF,                        ti.kE2BT2+142
.equ ti.kFPDF,                  ti.kE2BT2+143
.equ ti.kMinY,                  ti.kE2BT2+144 ;MinY
.equ ti.kRandBin,               ti.kE2BT2+145
.equ ti.kRef,                   ti.kE2BT2+146
.equ ti.kRRef,                  ti.kE2BT2+147
.equ ti.kLRSqr,                 ti.kE2BT2+148
.equ ti.kBRSqr,                 ti.kE2BT2+149
.equ ti.kDiagOn,                        ti.kE2BT2+150
.equ ti.kDiagOff,               ti.kE2BT2+151
.equ ti.kun1,                   ti.kE2BT2+152 ;FOR RCL USE WHEN GOTTEN FROM 82
.equ ti.kvn1,                   ti.kE2BT2+153 ;FOR RCL USE WHEN GOTTEN FROM 82
.equ ti.k83_00End,              ti.kvn1 ;end of original keys...
.equ ti.kArchive,               ti.k83_00End + 1
.equ ti.kUnarchive,             ti.k83_00End + 2
.equ ti.kAsm,                   ti.k83_00End + 3 ;Asm(
.equ ti.kAsmPrgm,               ti.k83_00End + 4 ;AsmPrgm
.equ ti.kAsmComp,               ti.k83_00End + 5 ;AsmComp(
.equ ti.kcapAAcute,             ti.k83_00End + 6
.equ ti.kcapAGrave,             ti.k83_00End + 7
.equ ti.kcapACaret,             ti.k83_00End + 8
.equ ti.kcapADier,              ti.k83_00End + 9
.equ ti.kaAcute,                        ti.k83_00End + 10
.equ ti.kaGrave,                        ti.k83_00End + 11
.equ ti.kaCaret,                        ti.k83_00End + 12
.equ ti.kaDier,                 ti.k83_00End + 13
.equ ti.kcapEAcute,             ti.k83_00End + 14
.equ ti.kcapEGrave,             ti.k83_00End + 15
.equ ti.kcapECaret,             ti.k83_00End + 16
.equ ti.kcapEDier,              ti.k83_00End + 17
.equ ti.keAcute,                        ti.k83_00End + 18
.equ ti.keGrave,                        ti.k83_00End + 19
.equ ti.keCaret,                        ti.k83_00End + 20
.equ ti.keDier,                 ti.k83_00End + 21
.equ ti.kcapIAcute,             ti.k83_00End + 22
.equ ti.kcapIGrave,             ti.k83_00End + 23
.equ ti.kcapICaret,             ti.k83_00End + 24
.equ ti.kcapIDier,              ti.k83_00End + 25
.equ ti.kiAcute,                        ti.k83_00End + 26
.equ ti.kiGrave,                        ti.k83_00End + 27
.equ ti.kiCaret,                        ti.k83_00End + 28
.equ ti.kiDier,                 ti.k83_00End + 29
.equ ti.kcapOAcute,             ti.k83_00End + 30
.equ ti.kcapOGrave,             ti.k83_00End + 31
.equ ti.kcapOCaret,             ti.k83_00End + 32
.equ ti.kcapODier,              ti.k83_00End + 33
.equ ti.koAcute,                        ti.k83_00End + 34
.equ ti.koGrave,                        ti.k83_00End + 35
.equ ti.koCaret,                        ti.k83_00End + 36
.equ ti.koDier,                 ti.k83_00End + 37
.equ ti.kcapUAcute,             ti.k83_00End + 38
.equ ti.kcapUGrave,             ti.k83_00End + 39
.equ ti.kcapUCaret,             ti.k83_00End + 40
.equ ti.kcapUDier,              ti.k83_00End + 41
.equ ti.kuAcute,                        ti.k83_00End + 42
.equ ti.kuGrave,                        ti.k83_00End + 43
.equ ti.kuCaret,                        ti.k83_00End + 44
.equ ti.kuDier,                 ti.k83_00End + 45
.equ ti.kcapCCed,               ti.k83_00End + 46
.equ ti.kcCed,                  ti.k83_00End + 47
.equ ti.kcapNTilde,             ti.k83_00End + 48
.equ ti.knTilde,                        ti.k83_00End + 49
.equ ti.kaccent,                        ti.k83_00End + 50
.equ ti.kgrave,                 ti.k83_00End + 51
.equ ti.kdieresis,              ti.k83_00End + 52
.equ ti.kquesDown,              ti.k83_00End + 53
.equ ti.kexclamDown,            ti.k83_00End + 54
.equ ti.kalpha,                 ti.k83_00End + 55
.equ ti.kbeta,                  ti.k83_00End + 56
.equ ti.kgamma,                 ti.k83_00End + 57
.equ ti.kcapDelta,              ti.k83_00End + 58
.equ ti.kdelta,                 ti.k83_00End + 59
.equ ti.kepsilon,               ti.k83_00End + 60
.equ ti.klambda,                        ti.k83_00End + 61
.equ ti.kmu,                    ti.k83_00End + 62
.equ ti.kpi2,                   ti.k83_00End + 63
.equ ti.krho,                   ti.k83_00End + 64
.equ ti.kcapSigma,              ti.k83_00End + 65
.equ ti.ksigma,                 ti.k83_00End + 66
.equ ti.ktau,                   ti.k83_00End + 67
.equ ti.kphi,                   ti.k83_00End + 68
.equ ti.kcapOmega,              ti.k83_00End + 69
.equ ti.kphat,                  ti.k83_00End + 70
.equ ti.kchi2,                  ti.k83_00End + 71
.equ ti.kstatF2,                        ti.k83_00End + 72
.equ ti.kLa,                    ti.k83_00End + 73
.equ ti.kLb,                    ti.k83_00End + 74
.equ ti.kLc,                    ti.k83_00End + 75
.equ ti.kLd,                    ti.k83_00End + 76
.equ ti.kLe,                    ti.k83_00End + 77
.equ ti.kLf,                    ti.k83_00End + 78
.equ ti.kLg,                    ti.k83_00End + 79
.equ ti.kLh,                    ti.k83_00End + 80
.equ ti.kLi,                    ti.k83_00End + 81
.equ ti.kLj,                    ti.k83_00End + 82
.equ ti.kLk,                    ti.k83_00End + 83
.equ ti.kLl,                    ti.k83_00End + 84
.equ ti.kLm,                    ti.k83_00End + 85
.equ ti.kLsmalln,               ti.k83_00End + 86
.equ ti.kLo,                    ti.k83_00End + 87
.equ ti.kLp,                    ti.k83_00End + 88
.equ ti.kLq,                    ti.k83_00End + 89
.equ ti.kLsmallr,               ti.k83_00End + 90
.equ ti.kLs,                    ti.k83_00End + 91
.equ ti.kLt,                    ti.k83_00End + 92
.equ ti.kLu,                    ti.k83_00End + 93
.equ ti.kLv,                    ti.k83_00End + 94
.equ ti.kLw,                    ti.k83_00End + 95
.equ ti.kLx,                    ti.k83_00End + 96
.equ ti.kLy,                    ti.k83_00End + 97
.equ ti.kLz,                    ti.k83_00End + 98
.equ ti.kGarbageC,              ti.k83_00End + 99 ;GarbageCollect
.equ ti.kE2BT2_End,             ti.kGarbageC

; THIS KEY MEANS THAT IT IS A 2 BYTE KEYCODE
; UNLESS (EXTECHO) IS 0 THEN IT IS AN OLD 1 BYTE KEYCODE
; THERE ARE 3 OF THESE KEYS; BE CAREFUL WITH USAGE
;--------------------------------------------------------
.equ ti.kExtendEcho3,           0x0FB

;Even More 2 Byte Keys
;-------------------------------------
.equ ti.kE2BT3,                 0x00
.equ ti.kSingleQuote,           ti.kE2BT3+1
.equ ti.kAt,                    ti.kE2BT3+2
.equ ti.kHash,                  ti.kE2BT3+3
.equ ti.kDollar,                        ti.kE2BT3+4
.equ ti.kAmp,                   ti.kE2BT3+5
.equ ti.kBackquote,             ti.kE2BT3+6
.equ ti.kSemicolon,             ti.kE2BT3+7
.equ ti.kBackslash,             ti.kE2BT3+8
.equ ti.kBar,                   ti.kE2BT3+9
.equ ti.kUnderscore,            ti.kE2BT3+10
.equ ti.kTilde,                 ti.kE2BT3+11
.equ ti.kPercent,               ti.kE2BT3+12
.equ ti.kEllipsis,              ti.kE2BT3+140
.equ ti.kAng,                   ti.kE2BT3+141
.equ ti.kSS,                    ti.kE2BT3+142
.equ ti.kSupX,                  ti.kE2BT3+143
.equ ti.kSubT,                  ti.kE2BT3+144
.equ ti.kSub0,                  ti.kE2BT3+145
.equ ti.kSub1,                  ti.kE2BT3+146
.equ ti.kSub2,                  ti.kE2BT3+147
.equ ti.kSub3,                  ti.kE2BT3+148
.equ ti.kSub4,                  ti.kE2BT3+149
.equ ti.kSub5,                  ti.kE2BT3+150
.equ ti.kSub6,                  ti.kE2BT3+151
.equ ti.kSub7,                  ti.kE2BT3+152
.equ ti.kSub8,                  ti.kE2BT3+153
.equ ti.kSub9,                  ti.kE2BT3+154
.equ ti.kSub10,                 ti.kE2BT3+155

;TI-83 Plus Context Equates
;--------------------------------------------------------------
.equ ti.cxCmd,                  ti.kQuit ;home screen
.equ ti.cxMatEdit,              ti.kMatrixEd ;matrix editor
.equ ti.cxPrgmEdit,             ti.kPrgmEd ;program editor
.equ ti.cxEquEdit,              ti.kYequ ;equation editor
.equ ti.cxGrRange,              ti.kWindow ;graph range editor
.equ ti.cxGrZfact,              ti.kZFactEd ;graph zoom factors editor
.equ ti.cxGraph,                        ti.kGraph ;graph mode
.equ ti.cxStatEdit,             ti.kStatEd ;statistics list editor
.equ ti.cxPrgmInput,            ti.kPrgmInput ;programmed input
.equ ti.cxError,                        ti.kError ;error handler
.equ ti.cxLinkIO,               ti.kLinkIO ;LINK I/O interface
.equ ti.cxMem,                  ti.kResetMem ;reset memory
.equ ti.cxDefMem,               ti.kResetDef ;reset default
.equ ti.cxRAMApp,               ti.kChkRAM ;RAM usage screen
.equ ti.cxMode,                 ti.kMode ;mode settings screen
.equ ti.cxErase,                        ti.kDelMem ;memory erase
.equ ti.cxPrgmCreate,           ti.kPrgmCr ;PROGRAM CREATE
.equ ti.cxTableEditor,          ti.kTable ;TABLE EDITOR
.equ ti.cxTableSet,             ti.kTblSet ;TABLE SET UP
.equ ti.cxStatPlot,             ti.kStatP ;STAT PLOTS
.equ ti.cxInfStat,              ti.kInfStat ;Inferential Statistic
.equ ti.cxFormat,               ti.kFormat ;FORMAT CONTEXT
.equ ti.cxSolveTVM,             ti.kSolveTVM ;Solve TVM
.equ ti.cxSolveRoot,            ti.kSolveRoot ;Solve Root
.equ ti.lastOldApp,             ti.kExtApps ;external applications
.equ ti.cxextapps,              ti.kExtApps
.equ ti.cxNewApps,              ti.kNewApps ;new cerberus applications
.equ ti.cxGroup,                        ti.cxNewApps+0 ;1st new app.
.equ ti.cxUnGroup,              ti.cxNewApps+1 ;2nd new app.
.equ ti.lastNewApp,             ti.cxUnGroup ;last new app for this ver

;Scan Code Equates
;------------------------------
.equ ti.skDown,                 0x01
.equ ti.skLeft,                 0x02
.equ ti.skRight,                        0x03
.equ ti.skUp,                   0x04
.equ ti.skEnter,                        0x09
.equ ti.skAdd,                  0x0A
.equ ti.skSub,                  0x0B
.equ ti.skMul,                  0x0C
.equ ti.skDiv,                  0x0D
.equ ti.skPower,                        0x0E
.equ ti.skClear,                        0x0F
.equ ti.skChs,                  0x11
.equ ti.sk3,                    0x12
.equ ti.sk6,                    0x13
.equ ti.sk9,                    0x14
.equ ti.skRParen,               0x15
.equ ti.skTan,                  0x16
.equ ti.skVars,                 0x17
.equ ti.skDecPnt,               0x19
.equ ti.sk2,                    0x1A
.equ ti.sk5,                    0x1B
.equ ti.sk8,                    0x1C
.equ ti.skLParen,               0x1D
.equ ti.skCos,                  0x1E
.equ ti.skPrgm,                 0x1F
.equ ti.skStat,                 0x20
.equ ti.sk0,                    0x21
.equ ti.sk1,                    0x22
.equ ti.sk4,                    0x23
.equ ti.sk7,                    0x24
.equ ti.skComma,                        0x25
.equ ti.skSin,                  0x26
.equ ti.skMatrix,               0x27
.equ ti.skGraphvar,             0x28
.equ ti.skStore,                        0x2A
.equ ti.skLn,                   0x2B
.equ ti.skLog,                  0x2C
.equ ti.skSquare,               0x2D
.equ ti.skRecip,                        0x2E
.equ ti.skMath,                 0x2F
.equ ti.skAlpha,                        0x30
.equ ti.skGraph,                        0x31
.equ ti.skTrace,                        0x32
.equ ti.skZoom,                 0x33
.equ ti.skWindow,               0x34
.equ ti.skYequ,                         0x35
.equ ti.sk2nd,                  0x36
.equ ti.skMode,                 0x37
.equ ti.skDel,                  0x38

; DI Keyboard Equates
;---------------------------
.equ ti.DI_Mode,                0x0F50000
.equ ti.DI_Cntrl,       0x0F50004
.equ ti.DI_Int,         0x0F50008
.equ ti.DI_IntMask,     0x0F5000C

.equ ti.kbdG1,          0x0F50012
;----------------------------
.equ ti.kbdGraph,       0b00000001
.equ ti.kbdTrace,       0b00000010
.equ ti.kbdZoom,                0b00000100
.equ ti.kbdWindow,      0b00001000
.equ ti.kbdYequ,        0b00010000
.equ ti.kbd2nd,         0b00100000
.equ ti.kbdMode,                0b01000000
.equ ti.kbdDel,         0b10000000

.equ ti.kbitGraph,      0x00
.equ ti.kbitTrace,      0x01
.equ ti.kbitZoom,       0x02
.equ ti.kbitWindow,     0x03
.equ ti.kbitYequ, 0x04
.equ ti.kbit2nd,                0x05
.equ ti.kbitMode,       0x06
.equ ti.kbitDel,                0x07

.equ ti.kbdG2,          0x0F50014
;----------------------------
.equ ti.kbdStore,       0b00000010
.equ ti.kbdLn,          0b00000100
.equ ti.kbdLog,         0b00001000
.equ ti.kbdSquare,      0b00010000
.equ ti.kbdRecip,       0b00100000
.equ ti.kbdMath,                0b01000000
.equ ti.kbdAlpha,       0b10000000

.equ ti.kbitStore,      0x01
.equ ti.kbitLn,         0x02
.equ ti.kbitLog,                0x03
.equ ti.kbitSquare,     0x04
.equ ti.kbitRecip,      0x05
.equ ti.kbitMath,       0x06
.equ ti.kbitAlpha,      0x07

.equ ti.kbdG3,          0x0F50016
;----------------------------
.equ ti.kbd0,           0b00000001
.equ ti.kbd1,           0b00000010
.equ ti.kbd4,           0b00000100
.equ ti.kbd7,           0b00001000
.equ ti.kbdComma,       0b00010000
.equ ti.kbdSin,         0b00100000
.equ ti.kbdApps,                0b01000000
.equ ti.kbdGraphVar,    0b10000000

.equ ti.kbit0,          0x00
.equ ti.kbit1,          0x01
.equ ti.kbit4,          0x02
.equ ti.kbit7,          0x03
.equ ti.kbitComma,      0x04
.equ ti.kbitSin,                0x05
.equ ti.kbitApps,       0x06
.equ ti.kbitGraphVar,   0x07

.equ ti.kbdG4,          0x0F50018
;----------------------------
.equ ti.kbdDecPnt,      0b00000001
.equ ti.kbd2,           0b00000010
.equ ti.kbd5,           0b00000100
.equ ti.kbd8,           0b00001000
.equ ti.kbdLParen,      0b00010000
.equ ti.kbdCos,         0b00100000
.equ ti.kbdPgrm,                0b01000000
.equ ti.kbdStat,                0b10000000

.equ ti.kbitDecPnt,     0x00
.equ ti.kbit2,          0x01
.equ ti.kbit5,          0x02
.equ ti.kbit8,          0x03
.equ ti.kbitLParen,     0x04
.equ ti.kbitCos,                0x05
.equ ti.kbitPgrm,       0x06
.equ ti.kbitStat,       0x07

.equ ti.kbdG5,          0x0F5001A
;----------------------------
.equ ti.kbdChs,         0b00000001
.equ ti.kbd3,           0b00000010
.equ ti.kbd6,           0b00000100
.equ ti.kbd9,           0b00001000
.equ ti.kbdRParen,      0b00010000
.equ ti.kbdTan,         0b00100000
.equ ti.kbdVars,                0b01000000

.equ ti.kbitChs,                0x00
.equ ti.kbit3,          0x01
.equ ti.kbit6,          0x02
.equ ti.kbit9,          0x03
.equ ti.kbitRParen,     0x04
.equ ti.kbitTan,                0x05
.equ ti.kbitVars,       0x06

.equ ti.kbdG6,          0x0F5001C
;----------------------------
.equ ti.kbdEnter,       0b00000001
.equ ti.kbdAdd,         0b00000010
.equ ti.kbdSub,         0b00000100
.equ ti.kbdMul,         0b00001000
.equ ti.kbdDiv,         0b00010000
.equ ti.kbdPower,       0b00100000
.equ ti.kbdClear,       0b01000000

.equ ti.kbitEnter,      0x00
.equ ti.kbitAdd,                0x01
.equ ti.kbitSub,                0x02
.equ ti.kbitMul,                0x03
.equ ti.kbitDiv,                0x04
.equ ti.kbitPower,      0x05
.equ ti.kbitClear,      0x06

.equ ti.kbdG7,          0x0F5001E
;----------------------------
.equ ti.kbdDown,                0b00000001
.equ ti.kbdLeft,                0b00000010
.equ ti.kbdRight,       0b00000100
.equ ti.kbdUp,          0b00001000

.equ ti.kbitDown,       0x00
.equ ti.kbitLeft,       0x01
.equ ti.kbitRight,      0x02
.equ ti.kbitUp,         0x03

;Tokens
;-----------------------------------------------------
.equ ti.EOSSTART,               0x00

;DISPLAY CONVERSIONS COME IMMEDIATELY BEFORE 'TSTORE'
;
.equ ti.DCONV,                  0x01
;
.equ ti.tToDMS,                 ti.DCONV ;01h
.equ ti.tToDEC,                 ti.DCONV+1 ;02h
.equ ti.tToAbc,                 ti.DCONV+2 ;03h > A b/c
;
.equ ti.tStore,                 ti.DCONV+3 ;04h Lstore 01
;
.equ ti.tBoxPlot,               0x05
;
.equ ti.BRACKS,                 0x06
;
.equ ti.tLBrack,                        ti.BRACKS ;06h '['
.equ ti.tRBrack,                        ti.BRACKS+1 ;07h ']'
.equ ti.tLBrace,                        ti.BRACKS+2 ;08h '{'
.equ ti.tRBrace,                        ti.BRACKS+3 ;09h '}'
;
.equ ti.tPOST1,                 ti.BRACKS+4
;
.equ ti.tFromRad,               ti.tPOST1 ;0Ah Lradian
.equ ti.tFromDeg,               ti.tPOST1+1 ;0Bh Ldegree
.equ ti.tRecip,                 ti.tPOST1+2 ;0Ch Linverse
.equ ti.tSqr,                   ti.tPOST1+3 ;0Dh Lsquare
.equ ti.tTrnspos,               ti.tPOST1+4 ;0Eh Ltranspose
.equ ti.tCube,                  ti.tPOST1+5 ;0Fh ' xor 3'
;
.equ ti.tLParen,                        0x10 ;10h '('
.equ ti.tRParen,                        0x11 ;11h ')'
;
.equ ti.IMUN,                   0x12
;
.equ ti.tRound,                 ti.IMUN ;12h 'round'
.equ ti.tPxTst,                 ti.IMUN+1 ;13h 'PXL-TEST'
.equ ti.tAug,                   ti.IMUN+2 ;14h 'aug'
.equ ti.tRowSwap,               ti.IMUN+3 ;15h 'rSwap'
.equ ti.tRowPlus,               ti.IMUN+4 ;16h 'rAdd'
.equ ti.tmRow,                  ti.IMUN+5 ;17h 'multR'
.equ ti.tmRowPlus,              ti.IMUN+6 ;18h 'mRAdd'
.equ ti.tMax,                   ti.IMUN+7 ;19h 'max'
.equ ti.tMin,                   ti.IMUN+8 ;1Ah 'min'
.equ ti.tRToPr,                 ti.IMUN+9 ;1Bh 'R>Pr
.equ ti.tRToPo,                 ti.IMUN+10 ;1Ch 'R>Po
.equ ti.tPToRx,                 ti.IMUN+11 ;1Dh 'P>Rx
.equ ti.tPToRy,                 ti.IMUN+12 ;1Eh 'P>Ry
.equ ti.tMedian,                        ti.IMUN+13 ;1Fh 'MEDIAN
.equ ti.tRandM,                 ti.IMUN+14 ;20h 'randM'
.equ ti.tMean,                  ti.IMUN+15 ;21h
.equ ti.tRoot,                  ti.IMUN+16 ;22h 'ROOT'
.equ ti.tSeries,                        ti.IMUN+17 ;23h 'seq'
.equ ti.tFnInt,                 ti.IMUN+18 ;24h 'fnInt'
.equ ti.tNDeriv,                        ti.IMUN+19 ;25h 'fnIr'
.equ ti.tEvalF,                 ti.IMUN+20 ;26h
.equ ti.tFmin,                  ti.IMUN+21 ;27h
.equ ti.tFmax,                  ti.IMUN+22 ;28h
;
.equ ti.tEOSEL,                 ti.IMUN+23
;
.equ ti.tSpace,                 ti.tEOSEL ;29h ' '
.equ ti.tString,                        ti.tEOSEL+1 ;2Ah '"'
.equ ti.tComma,                 ti.tEOSEL+2 ;2Bh ','
;
.equ ti.tii,                    0x2C ;i

;Postfix Functions
;-----------------------------------------
.equ ti.tPost,                  0x2D
;
.equ ti.tFact,                  ti.tPost ;2Dh '!'
;
.equ ti.tCubicR,                        0x2E
.equ ti.tQuartR,                        0x2F

;Number Tokens
;---------------------------------------
.equ ti.NUMS,                   0x30
;
.equ ti.t0,                     ti.NUMS ;30h
.equ ti.t1,                     ti.NUMS+1 ;31h
.equ ti.t2,                     ti.NUMS+2 ;32h
.equ ti.t3,                     ti.NUMS+3 ;33h
.equ ti.t4,                     ti.NUMS+4 ;34h
.equ ti.t5,                     ti.NUMS+5 ;35h
.equ ti.t6,                     ti.NUMS+6 ;36h
.equ ti.t7,                     ti.NUMS+7 ;37h
.equ ti.t8,                     ti.NUMS+8 ;38h
.equ ti.t9,                     ti.NUMS+9 ;39h
.equ ti.tDecPt,                 ti.NUMS+10 ;3Ah
.equ ti.tee,                    ti.NUMS+11 ;3Bh

;Binary OP
;-------------------------------------------
.equ ti.tOr,                    0x3C ;3Ch '_or_'
.equ ti.tXor,                   0x3D ;3Dh
;
.equ ti.tColon,                 0x3E ;3Eh ':'
.equ ti.tEnter,                 0x3F ;3Fh Lenter
;
.equ ti.tAnd,                   0x40 ;40h '_and_'

;Letter Tokens
;--------------------------------------
.equ ti.LET,                    0x41
.equ ti.tA,                     ti.LET ;41h
.equ ti.tB,                     ti.LET+1 ;42h
.equ ti.tC,                     ti.LET+2 ;43h
.equ ti.tD,                     ti.LET+3 ;44h
.equ ti.tE,                     ti.LET+4 ;45h
.equ ti.tF,                     ti.LET+5 ;46h
.equ ti.tG,                     ti.LET+6 ;47h
.equ ti.tH,                     ti.LET+7 ;48h
.equ ti.tI,                     ti.LET+8 ;49h
.equ ti.tJ,                     ti.LET+9 ;4Ah
.equ ti.tK,                     ti.LET+10 ;4Bh
.equ ti.tL,                     ti.LET+11 ;4Ch
.equ ti.tM,                     ti.LET+12 ;4Dh
.equ ti.tN,                     ti.LET+13 ;4Eh
.equ ti.tO,                     ti.LET+14 ;4Fh
.equ ti.tP,                     ti.LET+15 ;50h
.equ ti.tQ,                     ti.LET+16 ;51h
.equ ti.tR,                     ti.LET+17 ;52h
.equ ti.tS,                     ti.LET+18 ;53h
.equ ti.tT,                     ti.LET+19 ;54h
.equ ti.tU,                     ti.LET+20 ;55h
.equ ti.tV,                     ti.LET+21 ;56h
.equ ti.tW,                     ti.LET+22 ;57h
.equ ti.tX,                     ti.LET+23 ;58h
.equ ti.tY,                     ti.LET+24 ;59h
.equ ti.tZ,                     ti.LET+25 ;5Ah
.equ ti.tTheta,                 ti.LET+26 ;5Bh

; Extended Tokens
;---------------------------
.equ ti.tExtTok,                     0x0EF

.equ ti.tSetDate,            0x00
.equ ti.tSetTime,            0x01
.equ ti.tCheckTmr,           0x02
.equ ti.tSetDtFmt,           0x03
.equ ti.tSetTmFmt,           0x04
.equ ti.tTimeCnv,            0x05
.equ ti.tDayOfWk,            0x06
.equ ti.tGetDtStr,           0x07
.equ ti.tGetTmStr,           0x08
.equ ti.tGetDate,            0x09
.equ ti.tGetTime,            0x0A
.equ ti.tStartTmr,           0x0B
.equ ti.tGtDtFmt,            0x0C
.equ ti.tGetTmFmt,           0x0D
.equ ti.tIsClockOn,          0x0E
.equ ti.tClockOff,           0x0F
.equ ti.tClockOn,            0x10
.equ ti.tOpenLib,            0x11
.equ ti.tExecLib,            0x12
.equ ti.tInvT,               0x13
.equ ti.tChiSquaredGofTest,          0x14
.equ ti.tLinRegTInt,         0x15
.equ ti.tManualFit,          0x16

; MathPrint
.equ ti.tZQuadrant,          0x17
.equ ti.tZFracHalf,          0x18
.equ ti.tZFracThird,         0x19
.equ ti.tZFracFourth,        0x1A
.equ ti.tZFracFifth,         0x1B
.equ ti.tZFracEighth,        0x1C
.equ ti.tZFracTenth,         0x1D
.equ ti.tFracSlash,          0x2E
.equ ti.tFracMixedNum,       0x2F
.equ ti.tSwapImProper,       0x30
.equ ti.tSwapFracDec,        0x31
.equ ti.tRemainder,          0x32
.equ ti.tSummationSigma,             0x33
.equ ti.tLogBase,            0x34
.equ ti.tRandIntNoRep,       0x35
.equ ti.tMathPrint,          0x37
.equ ti.tClassic,            0x38
.equ ti.tAutoAnswer,         0x3B
.equ ti.tDecAnswer,          0x3C
.equ ti.tFracAnswer,         0x3D

; TI-84+CSE/CE
.equ ti.tBlue,               0x41
.equ ti.tRed,                0x42
.equ ti.tBlack,                      0x43
.equ ti.tMagenta,            0x44
.equ ti.tGreen,              0x45
.equ ti.tOrange,                     0x46
.equ ti.tBrown,              0x47
.equ ti.tNavy,               0x48
.equ ti.tLtBlue,                     0x49
.equ ti.tYellow,                     0x4A
.equ ti.tWhite,              0x4B
.equ ti.tLtGray,                     0x4C
.equ ti.tMedGray,            0x4D
.equ ti.tGray,               0x4E
.equ ti.tDarkGray,           0x4F

.equ ti.tGraphColor,         0x65
.equ ti.tTextColor,          0x67
.equ ti.tBackgroundOn,       0x5B
.equ ti.tBackgroundOff,      0x64

.equ ti.tThin,               0x74
;tThick - 0x7E 0x06 (was "Connected"?)
.equ ti.tAsm84CPrgm,         0x68
.equ ti.tAsm84CCmp,          0x69
.equ ti.tBorderColor,        0x6C

.equ ti.tAsm84CeCmp,         0x07B
.equ ti.tAsm84CePrgm,        0x07A

; OS 5.2+ only
.equ ti.tLEFT,               0x92
.equ ti.tCENTER,             0x93
.equ ti.tRIGHT,              0x94
.equ ti.tInvBinom,           0x95
.equ ti.tWait,               0x96
.equ ti.tToString,           0x97
.equ ti.tEval,               0x98

;These Var Tokens Are 1st Of A Double Token
;-----------------------------------------------

.equ ti.vToks,                  ti.LET+27

;User Matrix Token, 2nd Token Needed For Name
;
.equ ti.tVarMat,                        ti.vToks ;5Ch
;
;User List Token, 2nd Token Needed For Name
;
.equ ti.tVarLst,                        ti.vToks+1 ;5Dh
;
;User Equation Token, 2nd Token Needed For Name
;
.equ ti.tVarequ,                ti.vToks+2 ;5Eh
.equ ti.tProg,                  ti.vToks+3 ;5Fh
;
;User Pict Token, 2nd Token Needed For Name
;
.equ ti.tVarPict,               ti.vToks+4 ;60h
;
;User GDB Token, 2nd Token Needed For Name
;
.equ ti.tVarGDB,                        ti.vToks+5 ;61h
.equ ti.tVarOut,                        ti.vToks+6 ;62h
.equ ti.tVarSys,                        ti.vToks+7 ;63h

;Mode Setting Commands
;-------------------------------------------------
.equ ti.MODESA,                 ti.vToks+8 ;64h
.equ ti.tRad,                   ti.MODESA ;64h 'Radian'
.equ ti.tDeg,                   ti.MODESA+1 ;65h 'Degree'
.equ ti.tNormF,                 ti.MODESA+2 ;66h 'Normal'
.equ ti.tSci,                   ti.MODESA+3 ;67h 'Sci'
.equ ti.tEng,                   ti.MODESA+4 ;68h 'Eng'
.equ ti.tFloat,                 ti.MODESA+5 ;69h 'Float'
.equ ti.CMPS,                   0x6A
.equ ti.tEQ,                    ti.CMPS ;6Ah '=='
.equ ti.tLT,                    ti.CMPS+1 ;6Bh '<'
.equ ti.tGT,                    ti.CMPS+2 ;6Ch '>'
.equ ti.tLE,                    ti.CMPS+3 ;6Dh LLE
.equ ti.tGE,                    ti.CMPS+4 ;6Eh LGE
.equ ti.tNE,                    ti.CMPS+5 ;6Fh LNE

;Binary OP
;---------------------------------------
.equ ti.tAdd,                   0x70 ;70h '+'
.equ ti.tSub,                   0x71 ;71h '-'
.equ ti.tAns,                   0x72 ;72h

;Mode Setting Commands
;------------------------------------------------------
.equ ti.MODES,                  0x73
.equ ti.tFix,                   ti.MODES ;73h 'Fix_'
.equ ti.tSplitOn,               ti.MODES+1 ;74h
.equ ti.tFullScreen,            ti.MODES+2 ;75h
.equ ti.tStndrd,                        ti.MODES+3 ;76h 'Func'
.equ ti.tParam,                 ti.MODES+4 ;77h 'Param'
.equ ti.tPolar,                 ti.MODES+5 ;78h 'Pol'
.equ ti.tSeqG,                  ti.MODES+6 ;79h
.equ ti.tAFillOn,               ti.MODES+7 ;7Ah 'AUTO FILL ON'
.equ ti.tAFillOff,              ti.MODES+8 ;7Bh
.equ ti.tACalcOn,               ti.MODES+9 ;7Ch
.equ ti.tACalcOff,              ti.MODES+10 ;7Dh 'AutoFill OFF'

;Graph Format Tokens Are 2 Byte Tokens
;----------------------------------------
.equ ti.tGFormat,               ti.MODES+11 ;7Eh
.equ ti.tBoxIcon,               0x7F
.equ ti.tCrossIcon,             0x80
.equ ti.tDotIcon,               0x81

;(More) Binary OP
;---------------------------------------
.equ ti.tMul,                   0x82 ;82h '*'
.equ ti.tDiv,                   0x83 ;83h '/'

;Some Graph Commands
;-----------------------------------------------------
.equ ti.GRCMDS,                 0x84
.equ ti.tTrace,                 ti.GRCMDS ; 84h 'Trace'
.equ ti.tClDrw,                 ti.GRCMDS+1 ; 85h 'ClDrw'
.equ ti.tZoomStd,               ti.GRCMDS+2 ; 86h 'ZStd'
.equ ti.tZoomtrg,               ti.GRCMDS+3 ; 87h 'Ztrg'
.equ ti.tZoomBox,               ti.GRCMDS+4 ; 88h 'ZBOX'
.equ ti.tZoomIn,                        ti.GRCMDS+5 ; 89h 'ZIn'
.equ ti.tZoomOut,               ti.GRCMDS+6 ; 8Ah 'ZOut'
.equ ti.tZoomSqr,               ti.GRCMDS+7 ; 8Bh 'ZSqr'
.equ ti.tZoomInt,               ti.GRCMDS+8 ; 8Ch 'ZInt'
.equ ti.tZoomPrev,              ti.GRCMDS+9 ; 8Dh 'ZPrev'
.equ ti.tZoomDec,               ti.GRCMDS+10 ; 8Eh 'ZDecm'
.equ ti.tZoomStat,              ti.GRCMDS+11 ; 8Fh 'ZStat
.equ ti.tUsrZm,                 ti.GRCMDS+12 ; 90h 'ZRcl'
.equ ti.tPrtScrn,               ti.GRCMDS+13 ; 91h 'PrtScrn'
.equ ti.tZoomSto,               ti.GRCMDS+14 ; 92h  ZOOM STORE
.equ ti.tText,                  ti.GRCMDS+15 ; 93h

;Binary OP (Combination and Permutation)
;-------------------------------------------------
.equ ti.tnPr,                   ti.GRCMDS+16 ;94h '_nPr_'
.equ ti.tnCr,                   ti.GRCMDS+17 ;95h '_nCr_'

;More Graph Commands
;--------------------------------------------------
.equ ti.tYOn,                   ti.GRCMDS+18 ;96h 'FnOn_'
.equ ti.tYOff,                  ti.GRCMDS+19 ;97h 'FnOff_'
.equ ti.tStPic,                 ti.GRCMDS+20 ;98h 'StPic_'
.equ ti.tRcPic,                 ti.GRCMDS+21 ;99h 'RcPic_'
.equ ti.tStoDB,                 ti.GRCMDS+22 ;9Ah 'StGDB_'
.equ ti.tRclDB,                 ti.GRCMDS+23 ;9Bh 'RcGDB_'
.equ ti.tLine,                  ti.GRCMDS+24 ;9Ch 'Line'
.equ ti.tVert,                  ti.GRCMDS+25 ;9Dh 'Vert_'
.equ ti.tPtOn,                  ti.GRCMDS+26 ;9Eh 'PtOn'
.equ ti.tPtOff,                 ti.GRCMDS+27 ;9Fh 'PtOff'

;Token A0 Cannot Be An EOS Function Since Low MULT=A0 Already
;-----------------------------------------------------
.equ ti.tPtChg,                 ti.GRCMDS+28 ;A0h 'PtChg'
.equ ti.tPXOn,                  ti.GRCMDS+29 ;A1h
.equ ti.tPXOff,                 ti.GRCMDS+30 ;A2h
.equ ti.tPXChg,                 ti.GRCMDS+31 ;A3h
.equ ti.tShade,                 ti.GRCMDS+32 ;A4h 'Shade'
.equ ti.tCircl,                 ti.GRCMDS+33 ;A5h 'Circl'
.equ ti.tHorz,                  ti.GRCMDS+34 ;A6h 'HORIZONTAL'
.equ ti.tTanLn,                 ti.GRCMDS+35 ;A7h 'TanLn'
.equ ti.tDrInv,                 ti.GRCMDS+36 ;A8h 'DrInv_'
.equ ti.tDrawF,                 ti.GRCMDS+37 ;A9h 'DrawF_'
.equ ti.tVarStrng,              0x0AA

;Functions with No Arguments
;--------------------------------------------------
.equ ti.NOARG,                  0x0AB
.equ ti.tRand,                  ti.NOARG ;ABh 'rand'
.equ ti.tPi,                    ti.NOARG+1 ;ACh  Lpi
.equ ti.tGetKey,                        ti.NOARG+2 ;ADh 'getKy'
.equ ti.tAPost,                 ti.tGetKey+1 ;APOSTROPHY
.equ ti.tQuest,                 ti.tAPost+1 ;QUESTION MARK
.equ ti.UNARY,                  ti.tQuest+1 ;B0h
.equ ti.tChs,                   ti.UNARY ;B0h
.equ ti.tInt,                   ti.UNARY+1 ;B1h
.equ ti.tAbs,                   ti.UNARY+2 ;B2h
.equ ti.tDet,                   ti.UNARY+3 ;B3h
.equ ti.tIdent,                 ti.UNARY+4 ;B4h
.equ ti.tDim,                   ti.UNARY+5 ;B5h
.equ ti.tSum,                   ti.UNARY+6 ;B6h
.equ ti.tProd,                  ti.UNARY+7 ;B7h
.equ ti.tNot,                   ti.UNARY+8 ;B8h
.equ ti.tIPart,                 ti.UNARY+9 ;B9h
.equ ti.tFPart,                 ti.UNARY+10 ;BAh

;New 2 Byte Tokens
;------------------------------------------
.equ ti.t2ByteTok,              0x0BB
.equ ti.UNARYLR,                        ti.UNARY+12
.equ ti.tSqrt,                  ti.UNARYLR ;BCh
.equ ti.tCubRt,                 ti.UNARYLR+1 ;BDh
.equ ti.tLn,                    ti.UNARYLR+2 ;BEh
.equ ti.tExp,                   ti.UNARYLR+3 ;BFh
.equ ti.tLog,                   ti.UNARYLR+4 ;C0h
.equ ti.tALog,                  ti.UNARYLR+5 ;C1h
.equ ti.tSin,                   ti.UNARYLR+6 ;C2h
.equ ti.tASin,                  ti.UNARYLR+7 ;C3h
.equ ti.tCos,                   ti.UNARYLR+8 ;C4h
.equ ti.tACos,                  ti.UNARYLR+9 ;C5h
.equ ti.tTan,                   ti.UNARYLR+10 ;C6h
.equ ti.tATan,                  ti.UNARYLR+11 ;C7h
.equ ti.tSinH,                  ti.UNARYLR+12 ;C8h
.equ ti.tASinH,                 ti.UNARYLR+13 ;C9h
.equ ti.tCoshH,                 ti.UNARYLR+14 ;CAh
.equ ti.tACosH,                 ti.UNARYLR+15 ;CBh
.equ ti.tTanH,                  ti.UNARYLR+16 ;CCh
.equ ti.tATanH,                 ti.UNARYLR+17 ;CDh

;Some Programming Commands
;---------------------------------------------------
.equ ti.PROGTOK,                        ti.UNARYLR+18
.equ ti.tIf,                    ti.PROGTOK ;CEh
.equ ti.tThen,                  ti.PROGTOK+1 ;CFh
.equ ti.tElse,                  ti.PROGTOK+2 ;D0h
.equ ti.tWhile,                 ti.PROGTOK+3 ;D1h
.equ ti.tRepeat,                        ti.PROGTOK+4 ;D2h
.equ ti.tFor,                   ti.PROGTOK+5 ;D3h
.equ ti.tEnd,                   ti.PROGTOK+6 ;D4h
.equ ti.tReturn,                        ti.PROGTOK+7 ;D5h
.equ ti.tLbl,                   ti.PROGTOK+8 ;D6h 'Lbl_'
.equ ti.tGoto,                  ti.PROGTOK+9 ;D7h 'Goto_'
.equ ti.tPause,                 ti.PROGTOK+10 ;D8h 'Pause_'
.equ ti.tStop,                  ti.PROGTOK+11 ;D9h 'Stop'
.equ ti.tISG,                   ti.PROGTOK+12 ;DAh 'IS>'
.equ ti.tDSL,                   ti.PROGTOK+13 ;DBh 'DS<'
.equ ti.tInput,                 ti.PROGTOK+14 ;DCh 'Input_'
.equ ti.tPrompt,                        ti.PROGTOK+15 ;DDh 'Prompt_'
.equ ti.tDisp,                  ti.PROGTOK+16 ;DEh 'Disp_'
.equ ti.tDispG,                 ti.PROGTOK+17 ;DFh 'DispG'
.equ ti.tOutput,                        ti.PROGTOK+18 ;E0h 'Outpt'
.equ ti.tClLCD,                 ti.PROGTOK+19 ;E1h 'ClLCD'
.equ ti.tConst,                 ti.PROGTOK+20 ;E2h 'Fill'
.equ ti.tSortA,                 ti.PROGTOK+21 ;E3h 'sortA_'
.equ ti.tSortD,                 ti.PROGTOK+22 ;E4h 'sortD_'
.equ ti.tDispTab,               ti.PROGTOK+23 ;E5h 'Disp Table
.equ ti.tMenu,                  ti.PROGTOK+24 ;E6h 'Menu'
.equ ti.tSendMBL,               ti.PROGTOK+25 ;E7h 'SEND'
.equ ti.tGetMBL,                        ti.PROGTOK+26 ;E8h 'GET'

;Stat Plot Commands
;-----------------------------------------------------
.equ ti.statPCmd,               ti.PROGTOK+27
.equ ti.tPlotOn,                        ti.statPCmd ;E9h ' PLOTSON'
.equ ti.tPlotOff,               ti.statPCmd+1 ;EAh ' PLOTSOFF
.equ ti.tListName,              0x0EB ;LIST DESignATOR
.equ ti.tPlot1,                 0x0EC
.equ ti.tPlot2,                 0x0ED
.equ ti.tPlot3,                 0x0EE
.equ ti.tUnused01,              0x0EF ;available?
.equ ti.tPower,                 0x0F0 ;' xor '
.equ ti.tXRoot,                 0x0F1 ;LsupX,Lroot
.equ ti.STATCMD,                        0x0F2
.equ ti.tOneVar,                        ti.STATCMD ;F2h 'OneVar_'
.equ ti.tTwoVar,                        ti.STATCMD+1 ;F3h
.equ ti.tLR,                    ti.STATCMD+2 ;F4h 'LinR(A+BX
.equ ti.tLRExp,                 ti.STATCMD+3 ;F5h 'ExpR_'
.equ ti.tLRLn,                  ti.STATCMD+4 ;F6h 'LnR_'
.equ ti.tLRPwr,                 ti.STATCMD+5 ;F7h 'PwrR_'
.equ ti.tMedMed,                        ti.STATCMD+6 ;F8h
.equ ti.tQuad,                  ti.STATCMD+7 ;F9h
.equ ti.tClrLst,                        ti.STATCMD+8 ;FAh 'CLEAR LIST
.equ ti.tClrTbl,                        ti.STATCMD+9 ;FBh CLEAR TABLE
.equ ti.tHist,                  ti.STATCMD+10 ;FCh 'Hist_'
.equ ti.txyLine,                        ti.STATCMD+11 ;FDh 'xyline_'
.equ ti.tScatter,               ti.STATCMD+12 ;FEh 'Scatter_'
.equ ti.tLR1,                   ti.STATCMD+13 ;FFh 'LINR(AX+B

;2nd Half Of Graph Format Tokens
;Format settings commands
;---------------------------------------------
.equ ti.GFMT,                   0x00
.equ ti.tSeq,                   ti.GFMT ; 'SeqG'
.equ ti.tSimulG,                        ti.GFMT+1 ; 'SimulG'
.equ ti.tPolarG,                        ti.GFMT+2 ; 'PolarGC'
.equ ti.tRectG,                 ti.GFMT+3 ; 'RectGC'
.equ ti.tCoordOn,               ti.GFMT+4 ; 'CoordOn'
.equ ti.tCoordOff,              ti.GFMT+5 ; 'CoordOff'
.equ ti.tDrawLine,              ti.GFMT+6 ; 'DrawLine'
.equ ti.tDrawDot,               ti.GFMT+7 ; 'DrawDot'
.equ ti.tAxisOn,                        ti.GFMT+8 ; 'AxesOn'
.equ ti.tAxisOff,               ti.GFMT+9 ; 'AxesOff'
.equ ti.tGridOn,                        ti.GFMT+10 ; 'GridOn'
.equ ti.tGridOff,               ti.GFMT+11 ; 'GridOff'
.equ ti.tLblOn,                 ti.GFMT+12 ; 'LabelOn'
.equ ti.tLblOff,                        ti.GFMT+13 ; 'LabelOff'
.equ ti.tWebOn,                 ti.GFMT+14 ; 'WebOn'
.equ ti.tWebOff,                        ti.GFMT+15 ; 'WebOFF'
.equ ti.tuv,                    ti.GFMT+16 ; U vs V
.equ ti.tvw,                    ti.GFMT+17 ; V vs W
.equ ti.tuw,                    ti.GFMT+18 ; U vs W

;2nd Half Of User Matrix Tokens
;-------------------------------------
.equ ti.tMatA,                  0x00 ;MAT A
.equ ti.tMatB,                  0x01 ;MAT B
.equ ti.tMatC,                  0x02 ;MAT C
.equ ti.tMatD,                  0x03 ;MAT D
.equ ti.tMatE,                  0x04 ;MAT E
.equ ti.tMatF,                  0x05 ;MAT F
.equ ti.tMatG,                  0x06 ;MAT G
.equ ti.tMatH,                  0x07 ;MAT H
.equ ti.tMatI,                  0x08 ;MAT I
.equ ti.tMatJ,                  0x09 ;MAT J

;2nd Half Of User List Tokens
;--------------------------------------
.equ ti.tL1,                    0x00 ;LIST 1
.equ ti.tL2,                    0x01 ;LIST 2
.equ ti.tL3,                    0x02 ;LIST 3
.equ ti.tL4,                    0x03 ;LIST 4
.equ ti.tL5,                    0x04 ;LIST 5
.equ ti.tL6,                    0x05 ;LIST 6

;2nd Half Of User Equation Tokens
;----------------------------------
;  "Y" EQUATIONS HAVE BIT 4 SET
;
.equ ti.tY1,                    0x10 ;Y1
.equ ti.tY2,                    0x11 ;Y2
.equ ti.tY3,                    0x12 ;Y3
.equ ti.tY4,                    0x13 ;Y4
.equ ti.tY5,                    0x14 ;Y5
.equ ti.tY6,                    0x15 ;Y6
.equ ti.tY7,                    0x16 ;Y7
.equ ti.tY8,                    0x17 ;Y8
.equ ti.tY9,                    0x18 ;Y9
.equ ti.tY0,                    0x19 ;Y0

;Param Equations Have Bit 5 Set
;-----------------------------------
.equ ti.tX1T,                   0x20 ;X1t
.equ ti.tY1T,                   0x21 ;Y1t
.equ ti.tX2T,                   0x22 ;X2t
.equ ti.tY2T,                   0x23 ;Y2t
.equ ti.tX3T,                   0x24 ;X3t
.equ ti.tY3T,                   0x25 ;Y3t
.equ ti.tX4T,                   0x26 ;X4t
.equ ti.tY4T,                   0x27 ;Y4t
.equ ti.tX5T,                   0x28 ;X5t
.equ ti.tY5T,                   0x29 ;Y5t
.equ ti.tX6T,                   0x2A ;X6t
.equ ti.tY6T,                   0x2B ;Y6t

;Polar Equations Have Bit 6 Set
;----------------------------------
.equ ti.tR1,                    0x40 ;R1
.equ ti.tR2,                    0x41 ;R2
.equ ti.tR3,                    0x42 ;R3
.equ ti.tR4,                    0x43 ;R4
.equ ti.tR5,                    0x44 ;R5
.equ ti.tR6,                    0x45 ;R6

;Recursion Equations Have Bit 7 Set
;----------------------------------
.equ ti.tun,                    0x80 ;Un
.equ ti.tvn,                    0x81 ;Vn
.equ ti.twn,                    0x82 ;Wn

;2nd Half User Picture Tokens
;------------------------------------
.equ ti.tPic1,                  0x00 ;PIC1
.equ ti.tPic2,                  0x01 ;PIC2
.equ ti.tPic3,                  0x02 ;PIC3
.equ ti.tPic4,                  0x03 ;PIC4
.equ ti.tPic5,                  0x04 ;PIC5
.equ ti.tPic6,                  0x05 ;PIC6
.equ ti.tPic7,                  0x06 ;PIC7
.equ ti.tPic8,                  0x07 ;PIC8
.equ ti.tPic9,                  0x08 ;PIC9
.equ ti.tPic0,                  0x09 ;PIC0

;2nd Half User Graph Database Tokens
;------------------------------------
.equ ti.tGDB1,                  0x00 ;GDB1
.equ ti.tGDB2,                  0x01 ;GDB2
.equ ti.tGDB3,                  0x02 ;GDB3
.equ ti.tGDB4,                  0x03 ;GDB4
.equ ti.tGDB5,                  0x04 ;GDB5
.equ ti.tGDB6,                  0x05 ;GDB6
.equ ti.tGDB7,                  0x06 ;GDB7
.equ ti.tGDB8,                  0x07 ;GDB8
.equ ti.tGDB9,                  0x08 ;GDB9
.equ ti.tGDB0,                  0x09 ;GDB0

;2nd Half Of String Vars
;------------------------------
.equ ti.tStr1,                  0x00
.equ ti.tStr2,                  0x01
.equ ti.tStr3,                  0x02
.equ ti.tStr4,                  0x03
.equ ti.tStr5,                  0x04
.equ ti.tStr6,                  0x05
.equ ti.tStr7,                  0x06
.equ ti.tStr8,                  0x07
.equ ti.tStr9,                  0x08
.equ ti.tStr0,                  0x09

;2nd Half Of System Output Only Variables
;----------------------------------------------------------------
;OPEN			equ 00h
.equ ti.tRegEq,                 0x01 ;REGRESSION EQUATION
.equ ti.tStatN,                 0x02 ;STATISTICS N
.equ ti.tXMean,                 0x03 ;X MEAN
.equ ti.tSumX,                  0x04 ;SUM(X)
.equ ti.tSumXSqr,               0x05 ;SUM(X xor 2)
.equ ti.tStdX,                  0x06 ;STANDARD DEV X
.equ ti.tStdPX,                 0x07 ;STANDARD DEV POP X
.equ ti.tMinX,                  0x08 ;Min X VALUE
.equ ti.tMaxX,                  0x09 ;Max X VALUE
.equ ti.tMinY,                  0x0A ;Min Y VALUE
.equ ti.tMaxY,                  0x0B ;Max Y VALUE
.equ ti.tYmean,                 0x0C ;Y MEAN
.equ ti.tSumY,                  0x0D ;SUM(Y)
.equ ti.tSumYSqr,               0x0E ;SUM(Y xor 2)
.equ ti.tStdY,                  0x0F ;STANDARD DEV Y
.equ ti.tStdPY,                 0x10 ;STANDARD DEV POP Y
.equ ti.tSumXY,                 0x11 ;SUM(XY)
.equ ti.tCorr,                  0x12 ;CORRELATION
.equ ti.tMedX,                  0x13 ;MED(X)
.equ ti.tQ1,                    0x14 ;1ST QUADRANT OF X
.equ ti.tQ3,                    0x15 ;3RD QUADRANT OF X
.equ ti.tQuadA,                 0x16 ;1ST TERM OF QUAD POLY REG/ Y-INT
.equ ti.tQuadB,                 0x17 ;2ND TERM OF QUAD POLY REG/ SLOPE
.equ ti.tQuadC,                 0x18 ;3RD TERM OF QUAD POLY REG
.equ ti.tCubeD,                 0x19 ;4TH TERM OF CUBIC POLY REG
.equ ti.tQuartE,                        0x1A ;5TH TERM OF QUART POLY REG
.equ ti.tMedX1,                 0x1B ;x1 FOR MED-MED
.equ ti.tMedX2,                 0x1C ;x2 FOR MED-MED
.equ ti.tMedX3,                 0x1D ;x3 FOR MED-MED
.equ ti.tMedY1,                 0x1E ;y1 FOR MED-MED
.equ ti.tMedY2,                 0x1F ;y2 FOR MED-MED
.equ ti.tMedY3,                 0x20 ;y3 FOR MED-MED
.equ ti.tRecurn,                        0x21 ;RECURSION N
.equ ti.tStatP,                 0x22
.equ ti.tStatZ,                 0x23
.equ ti.tStatT,                 0x24
.equ ti.tStatChi,               0x25
.equ ti.tStatF,                 0x26
.equ ti.tStatDF,                        0x27
.equ ti.tStatPhat,              0x28
.equ ti.tStatPhat1,             0x29
.equ ti.tStatPhat2,             0x2A
.equ ti.tStatMeanX1,            0x2B
.equ ti.tStatStdX1,             0x2C
.equ ti.tStatN1,                        0x2D
.equ ti.tStatMeanX2,            0x2E
.equ ti.tStatStdX2,             0x2F
.equ ti.tStatN2,                        0x30
.equ ti.tStatStdXP,             0x31
.equ ti.tStatLower,             0x32
.equ ti.tStatUpper,             0x33
.equ ti.tStat_s,                        0x34
.equ ti.tLRSqr,                 0x35 ;r xor 2
.equ ti.tBRSqr,                 0x36 ;R xor 2

;These next tokens are only used to access the data
;they are display only and the user cannot access them at all
;------------------------------------------------------------
.equ ti.tF_DF,                  0x37 ;ANOFAV FACTOR DF
.equ ti.tF_SS,                  0x38 ;ANOFAV FACTOR SS
.equ ti.tF_MS,                  0x39 ;ANOFAV FACTOR MS
.equ ti.tE_DF,                  0x3A ;ANOFAV ERROR DF
.equ ti.tE_SS,                  0x3B ;ANOFAV ERROR SS
.equ ti.tE_MS,                  0x3C ;ANOFAV ERROR MS

;2nd Half Of System Input/Output Variables
;------------------------------------------------
;		SYSTEM VARIABLE EQUATES
;
.equ ti.tuXscl,                 0
.equ ti.tuYscl,                 1
.equ ti.tXscl,                  2
.equ ti.tYscl,                  3
.equ ti.tRecuru0,               4 ;U 1ST INITIAL COND
.equ ti.tRecurv0,               5 ;V 1ST INITIAL COND
.equ ti.tun1,                   6 ;U(N-1); NOT USED
.equ ti.tvn1,                   7 ;V(N-1); NOT USED
.equ ti.tuRecuru0,              8 ;
.equ ti.tuRecurv0,              9 ;
.equ ti.tXmin,                  0x0A
.equ ti.tXmax,                  0x0B
.equ ti.tYmin,                  0x0C
.equ ti.tYmax,                  0x0D
.equ ti.tTmin,                  0x0E
.equ ti.tTmax,                  0x0F
.equ ti.tThetaMin,              0x10
.equ ti.tThetaMax,              0x11
.equ ti.tuXmin,                 0x12
.equ ti.tuXmax,                 0x13
.equ ti.tuYmin,                 0x14
.equ ti.tuYmax,                 0x15
.equ ti.tuThetMin,              0x16
.equ ti.tuThetMax,              0x17
.equ ti.tuTmin,                 0x18
.equ ti.tuTmax,                 0x19
.equ ti.tTblMin,                        0x1A
.equ ti.tPlotStart,             0x1B
.equ ti.tuPlotStart,            0x1C
.equ ti.tnMax,                  0x1D
.equ ti.tunMax,                 0x1E
.equ ti.tnMin,                  0x1F
.equ ti.tunMin,                 0x20
.equ ti.tTblStep,               0x21
.equ ti.tTStep,                 0x22
.equ ti.tThetaStep,             0x23
.equ ti.tuTStep,                        0x24
.equ ti.tuThetStep,             0x25
.equ ti.tDeltaX,                        0x26
.equ ti.tDeltaY,                        0x27
.equ ti.tXFact,                 0x28
.equ ti.tYFact,                 0x29
.equ ti.tTblInput,              0x2A
.equ ti.tFinN,                  0x2B
.equ ti.tFinI,                  0x2C
.equ ti.tFinPV,                 0x2D
.equ ti.tFinPMT,                        0x2E
.equ ti.tFinFV,                 0x2F
.equ ti.tFinPY,                 0x30
.equ ti.tFinCY,                 0x31
.equ ti.tRecurw0,               0x32 ;w0(1)
.equ ti.tuRecurw0,              0x33
.equ ti.tPlotStep,              0x34
.equ ti.tuPlotStep,             0x35
.equ ti.tXres,                  0x36
.equ ti.tuXres,                 0x37
.equ ti.tRecuru02,              0x38 ;u0(2)
.equ ti.tuRecuru02,             0x39
.equ ti.tRecurv02,              0x3C ;v0(2)
.equ ti.tuRecurv02,             0x3D
.equ ti.tRecurw02,              0x3E ;w0(2)
.equ ti.tuRecurw02,             0x3F

;2nd Byte Of t2ByteTok Tokens
;------------------------------
.equ ti.tFinNPV,                        0x00
.equ ti.tFinIRR,                        0x01
.equ ti.tFinBAL,                        0x02
.equ ti.tFinPRN,                        0x03
.equ ti.tFinINT,                        0x04
.equ ti.tFinToNom,              0x05
.equ ti.tFinToEff,              0x06
.equ ti.tFinDBD,                        0x07
.equ ti.tLCM,                   0x08
.equ ti.tGCD,                   0x09
.equ ti.tRandInt,               0x0A
.equ ti.tRandBin,               0x0B
.equ ti.tSubStrng,              0x0C
.equ ti.tStdDev,                        0x0D
.equ ti.tVariance,              0x0E
.equ ti.tInStrng,               0x0F
.equ ti.tDNormal,               0x10
.equ ti.tInvNorm,               0x11
.equ ti.tDT,                    0x12
.equ ti.tChI,                   0x13
.equ ti.tDF,                    0x14
.equ ti.tBINPDF,                        0x15
.equ ti.tBINCDF,                        0x16
.equ ti.tPOIPDF,                        0x17
.equ ti.tPOICDF,                        0x18
.equ ti.tGEOPDF,                        0x19
.equ ti.tGEOCDF,                        0x1A
.equ ti.tNormalPDF,             0x1B
.equ ti.tTPDF,                  0x1C
.equ ti.tChiPDF,                        0x1D
.equ ti.tFPDF,                  0x1E
.equ ti.tRandNorm,              0x1F
.equ ti.tFinFPMT,               0x20
.equ ti.tFinFI,                 0x21
.equ ti.tFinFPV,                        0x22
.equ ti.tFinFN,                 0x23
.equ ti.tFinFFV,                        0x24
.equ ti.tConj,                  0x25
.equ ti.tReal,                  0x26
.equ ti.tImag,                  0x27
.equ ti.tAngle,                 0x28
.equ ti.tCumSum,                        0x29
.equ ti.tExpr,                  0x2A
.equ ti.tLength,                        0x2B
.equ ti.tDeltaLst,              0x2C
.equ ti.tRef,                   0x2D
.equ ti.tRRef,                  0x2E
.equ ti.tToRect,                        0x2F
.equ ti.tToPolar,               0x30
.equ ti.tConste,                        0x31
.equ ti.tSinReg,                        0x32
.equ ti.tLogistic,              0x33
.equ ti.tLinRegTTest,           0x34
.equ ti.tShadeNorm,             0x35
.equ ti.tShadeT,                        0x36
.equ ti.tShadeChi,              0x37
.equ ti.tShadeF,                        0x38
.equ ti.tMatToLst,              0x39
.equ ti.tLstToMat,              0x3A
.equ ti.tZTest,                 0x3B
.equ ti.tTTest,                 0x3C
.equ ti.t2SampZTest,            0x3D
.equ ti.t1PropZTest,            0x3E
.equ ti.t2PropZTest,            0x3F
.equ ti.tChiTest,               0x40
.equ ti.tZIntVal,               0x41
.equ ti.t2SampZInt,             0x42
.equ ti.t1PropZInt,             0x43
.equ ti.t2PropZInt,             0x44
.equ ti.tGraphStyle,            0x45
.equ ti.t2SampTTest,            0x46
.equ ti.t2SampFTest,            0x47
.equ ti.tTIntVal,               0x48
.equ ti.t2SampTInt,             0x49
.equ ti.tSetupLst,              0x4A
.equ ti.tFinPMTend,             0x4B
.equ ti.tFinPMTbeg,             0x4C
.equ ti.tRealM,                 0x4D
.equ ti.tPolarM,                        0x4E
.equ ti.tRectM,                 0x4F
.equ ti.tExprOn,                        0x50
.equ ti.tExprOff,               0x51
.equ ti.tClrAllLst,             0x52
.equ ti.tGetCalc,               0x53
.equ ti.tDelVar,                        0x54
.equ ti.tEquToStrng,            0x55
.equ ti.tStrngToequ,            0x56
.equ ti.tDelLast,               0x57
.equ ti.tSelect,                        0x58
.equ ti.tANOVA,                 0x59
.equ ti.tModBox,                        0x5A
.equ ti.tNormProb,              0x5B
.equ ti.tMGT,                   0x64 ;VERTICAL SPLIT
.equ ti.tZFit,                  0x65 ;ZOOM FIT
.equ ti.tDiag_on,               0x66 ;DIANOSTIC DISPLAY ON
.equ ti.tDiag_off,              0x67 ;DIANOSTIC DISPLAY OFF
.equ ti.tOkEnd2v0,              0x67 ;end of 2byte tokens for version 0.
.equ ti.tArchive,               0x68 ;archive
.equ ti.tUnarchive,             0x69 ;unarchive
.equ ti.tasm,                   0x6A
.equ ti.tasmComp,               0x6B ;asm compile
.equ ti.tasmPrgm,               0x6C ;Signifies a program is asm
.equ ti.tasmCmp,                        0x6D ;asm program is compiled
.equ ti.tLcapAAcute,            0x6E
.equ ti.tLcapAGrave,            0x6F
.equ ti.tLcapACaret,            0x70
.equ ti.tLcapADier,             0x71
.equ ti.tLaAcute,               0x72
.equ ti.tLaGrave,               0x73
.equ ti.tLaCaret,               0x74
.equ ti.tLaDier,                        0x75
.equ ti.tLcapEAcute,            0x76
.equ ti.tLcapEGrave,            0x77
.equ ti.tLcapECaret,            0x78
.equ ti.tLcapEDier,             0x79
.equ ti.tLeAcute,               0x7A
.equ ti.tLeGrave,               0x7B
.equ ti.tLeCaret,               0x7C
.equ ti.tLeDier,                        0x7D
.equ ti.tLcapIGrave,            0x7F
.equ ti.tLcapICaret,            0x80
.equ ti.tLcapIDier,             0x81
.equ ti.tLiAcute,               0x82
.equ ti.tLiGrave,               0x83
.equ ti.tLiCaret,               0x84
.equ ti.tLiDier,                        0x85
.equ ti.tLcapOAcute,            0x86
.equ ti.tLcapOGrave,            0x87
.equ ti.tLcapOCaret,            0x88
.equ ti.tLcapODier,             0x89
.equ ti.tLoAcute,               0x8A
.equ ti.tLoGrave,               0x8B
.equ ti.tLoCaret,               0x8C
.equ ti.tLoDier,                        0x8D
.equ ti.tLcapUAcute,            0x8E
.equ ti.tLcapUGrave,            0x8F
.equ ti.tLcapUCaret,            0x90
.equ ti.tLcapUDier,             0x91
.equ ti.tLuAcute,               0x92
.equ ti.tLuGrave,               0x93
.equ ti.tLuCaret,               0x94
.equ ti.tLuDier,                        0x95
.equ ti.tLcapCCed,              0x96
.equ ti.tLcCed,                 0x97
.equ ti.tLcapNTilde,            0x98
.equ ti.tLnTilde,               0x99
.equ ti.tLaccent,               0x9A
.equ ti.tLgrave,                        0x9B
.equ ti.tLdieresis,             0x9C
.equ ti.tLquesDown,             0x9D
.equ ti.tLexclamDown,           0x9E
.equ ti.tLalpha,                        0x9F
.equ ti.tLbeta,                 0x0A0
.equ ti.tLgamma,                        0x0A1
.equ ti.tLcapDelta,             0x0A2
.equ ti.tLdelta,                        0x0A3
.equ ti.tLepsilon,              0x0A4
.equ ti.tLlambda,               0x0A5
.equ ti.tLmu,                   0x0A6
.equ ti.tLpi,                   0x0A7
.equ ti.tLrho,                  0x0A8
.equ ti.tLcapSigma,             0x0A9
.equ ti.tLphi,                  0x0AB
.equ ti.tLcapOmega,             0x0AC
.equ ti.tLphat,                 0x0AD
.equ ti.tLchi,                  0x0AE
.equ ti.tLstatF,                        0x0AF
.equ ti.tLa,                    0x0B0
.equ ti.tLb,                    0x0B1
.equ ti.tLc,                    0x0B2
.equ ti.tLd,                    0x0B3
.equ ti.tLsmalle,               0x0B4
.equ ti.tLf,                    0x0B5
.equ ti.tLsmallg,               0x0B6
.equ ti.tLh,                    0x0B7
.equ ti.tLi,                    0x0B8
.equ ti.tLj,                    0x0B9
.equ ti.tLk,                    0x0BA
.equ ti.tLl,                    0x0BC
.equ ti.tLm,                    0x0BD
.equ ti.tLsmalln,               0x0BE
.equ ti.tLo,                    0x0BF
.equ ti.tLp,                    0x0C0
.equ ti.tLq,                    0x0C1
.equ ti.tLsmallr,               0x0C2
.equ ti.tLs,                    0x0C3
.equ ti.tLsmallt,               0x0C4
.equ ti.tLu,                    0x0C5
.equ ti.tLv,                    0x0C6
.equ ti.tLw,                    0x0C7
.equ ti.tLx,                    0x0C8
.equ ti.tLy,                    0x0C9
.equ ti.tLz,                    0x0CA
.equ ti.tLsigma,                        0x0CB
.equ ti.tLtau,                  0x0CC
.equ ti.tLcapIAcute,            0x0CD
.equ ti.tGarbagec,              0x0CE
.equ ti.LastToken,              0x0CE ;tLAST TOKEN IN THIS VERSION...

;Data Type Equates
;---------------------------------------------------------------------
.equ ti.RealObj,                        0
.equ ti.ListObj,                        1
.equ ti.MatObj,                 2
.equ ti.EquObj,                 3
.equ ti.StrngObj,               4
.equ ti.ProgObj,                        5
.equ ti.ProtProgObj,            6
.equ ti.PictObj,                        7
.equ ti.GDBObj,                 8
.equ ti.UnknownObj,             9
.equ ti.UnknownEquObj,          0x0A
.equ ti.NewEquObj,              0x0B
.equ ti.CplxObj,                        0x0C
.equ ti.CListObj,               0x0D
.equ ti.UndefObj,               0x0E
.equ ti.WindowObj,              0x0F
.equ ti.ZStoObj,                        0x10
.equ ti.TblRngObj,              0x11
.equ ti.LCDObj,                 0x12
.equ ti.BackupObj,              0x13
.equ ti.AppObj,                 0x14 ;application, only used in menus/link
.equ ti.AppVarObj,              0x15 ;application variable
.equ ti.TempProgObj,            0x16 ;program, home deletes when finished
.equ ti.GroupObj,               0x17 ;group.

;System Error Codes
;-----------------------------------------------------------
.equ ti.E_EDITF,                        7 ;allow re-entering application
.equ ti.E_EDIT,                 1 << ti.E_EDITF
.equ ti.E_Mask,                 0x7F
.equ ti.E_Overflow,             1+ti.E_EDIT
.equ ti.E_DivBy0,               2+ti.E_EDIT
.equ ti.E_SingularMat,          3+ti.E_EDIT
.equ ti.E_Domain,               4+ti.E_EDIT
.equ ti.E_Increment,            5+ti.E_EDIT
.equ ti.E_Break,                        6+ti.E_EDIT
.equ ti.E_NonReal,              7+ti.E_EDIT
.equ ti.E_Syntax,               8+ti.E_EDIT
.equ ti.E_DataType,             9+ti.E_EDIT
.equ ti.E_Argument,             10+ti.E_EDIT
.equ ti.E_DimMismatch,          11+ti.E_EDIT
.equ ti.E_Dimension,            12+ti.E_EDIT
.equ ti.E_Undefined,            13+ti.E_EDIT
.equ ti.E_Memory,               14+ti.E_EDIT         ; 142
.equ ti.E_Invalid,              15+ti.E_EDIT         ; 143
.equ ti.E_IllegalNest,          16+ti.E_EDIT         ; 144
.equ ti.E_Bound,                        17+ti.E_EDIT         ; 145
.equ ti.E_GraphRange,           18+ti.E_EDIT         ; 146
.equ ti.E_Zoom,                 19+ti.E_EDIT         ; 147
.equ ti.E_Label,                        20                   ; 148
.equ ti.E_Stat,                 21                   ; 149
.equ ti.E_Solver,               22+ti.E_EDIT
.equ ti.E_Singularity,          23+ti.E_EDIT
.equ ti.E_SignChange,           24+ti.E_EDIT
.equ ti.E_Iterations,           25+ti.E_EDIT
.equ ti.E_BadGuess,             26+ti.E_EDIT
.equ ti.E_StatPlo,              27
.equ ti.E_TolTooSmall,          28+ti.E_EDIT
.equ ti.E_Reserved,             29+ti.E_EDIT
.equ ti.E_Mode,                 30+ti.E_EDIT
.equ ti.E_LnkErr,               31+ti.E_EDIT
.equ ti.E_LnkMemErr,            32+ti.E_EDIT
.equ ti.E_LnkTransErr,          33+ti.E_EDIT
.equ ti.E_LnkDupErr,            34+ti.E_EDIT
.equ ti.E_LnkMemFull,           35+ti.E_EDIT
.equ ti.E_Unknown,              36+ti.E_EDIT
.equ ti.E_Scale,                        37+ti.E_EDIT
.equ ti.E_IdNotFound,           38
.equ ti.E_NoMode,               39+ti.E_EDIT
.equ ti.E_Validation,           40
.equ ti.E_Length,               41+ti.E_EDIT
.equ ti.E_Application,          42+ti.E_EDIT
.equ ti.E_AppErr1,              43+ti.E_EDIT
.equ ti.E_AppErr2,              44+ti.E_EDIT
.equ ti.E_ExpiredApp,           45
.equ ti.E_BadAdd,               46
.equ ti.E_Archived,             47+ti.E_EDIT
.equ ti.E_Version,              48
.equ ti.E_ArchFull,             49
.equ ti.E_Variable,             50+ti.E_EDIT
.equ ti.E_Duplicate,            51+ti.E_EDIT

;System Variable Equates
;------------------------------
.equ ti.XSCLt,                  0x02
.equ ti.YSCLt,                  0x03
.equ ti.XMINt,                  0x0A
.equ ti.XMAXt,                  0x0B
.equ ti.YMINt,                  0x0C
.equ ti.YMAXt,                  0x0D
.equ ti.TMINt,                  0x0E
.equ ti.TMAXt,                  0x0F
.equ ti.THETMINt,               0x10
.equ ti.THETMAXt,               0x11
.equ ti.TBLMINt,                        0x1A
.equ ti.PLOTSTARTt,             0x1B
.equ ti.NMAXt,                  0x1D
.equ ti.NMINt,                  0x1F
.equ ti.TBLSTEPt,               0x21
.equ ti.TSTEPt,                 0x22
.equ ti.THETSTEPt,              0x23
.equ ti.DELTAXt,                        0x26
.equ ti.DELTAYt,                        0x27
.equ ti.XFACTt,                 0x28
.equ ti.YFACTt,                 0x29
.equ ti.FINNt,                  0x2B
.equ ti.FINIt,                  0x2C
.equ ti.FINPVt,                 0x2D
.equ ti.FINPMTt,                        0x2E
.equ ti.FINFVt,                 0x2F
.equ ti.FINPYt,                 0x30
.equ ti.FINCYt,                 0x31
.equ ti.PLOTSTEPt,              0x34
.equ ti.XRESt,                  0x36

;Equates To RAM Locations For Stat Vars
;----------------------------------------------------------------
.equ ti.FPLEN,                  9 ;Length of a floating-point number.
.equ ti.StatN,                  ti.statVars
.equ ti.XMean,                  ti.StatN + ti.FPLEN
.equ ti.SumX,                   ti.XMean + ti.FPLEN
.equ ti.SumXSqr,                        ti.SumX + ti.FPLEN
.equ ti.StdX,                   ti.SumXSqr + ti.FPLEN
.equ ti.StdPX,                  ti.StdX + ti.FPLEN
.equ ti.MinX,                   ti.StdPX + ti.FPLEN
.equ ti.MaxX,                   ti.MinX + ti.FPLEN
.equ ti.MinY,                   ti.MaxX + ti.FPLEN
.equ ti.MaxY,                   ti.MinY + ti.FPLEN
.equ ti.YMean,                  ti.MaxY + ti.FPLEN
.equ ti.SumY,                   ti.YMean + ti.FPLEN
.equ ti.SumYSqr,                        ti.SumY + ti.FPLEN
.equ ti.StdY,                   ti.SumYSqr + ti.FPLEN
.equ ti.StdPY,                  ti.StdY + ti.FPLEN
.equ ti.SumXY,                  ti.StdPY + ti.FPLEN
.equ ti.Corr,                   ti.SumXY + ti.FPLEN
.equ ti.MedX,                   ti.Corr + ti.FPLEN
.equ ti.Q1,                     ti.MedX + ti.FPLEN
.equ ti.Q3,                     ti.Q1 + ti.FPLEN
.equ ti.QuadA,                  ti.Q3 + ti.FPLEN
.equ ti.QuadB,                  ti.QuadA + ti.FPLEN
.equ ti.QuadC,                  ti.QuadB + ti.FPLEN
.equ ti.CubeD,                  ti.QuadC + ti.FPLEN
.equ ti.QuartE,                 ti.CubeD + ti.FPLEN
.equ ti.MedX1,                  ti.QuartE + ti.FPLEN
.equ ti.MedX2,                  ti.MedX1 + ti.FPLEN
.equ ti.MedX3,                  ti.MedX2 + ti.FPLEN
.equ ti.MedY1,                  ti.MedX3 + ti.FPLEN
.equ ti.MedY2,                  ti.MedY1 + ti.FPLEN
.equ ti.MedY3,                  ti.MedY2 + ti.FPLEN
.equ ti.PStat,                  ti.MedY3 + (2*ti.FPLEN)
.equ ti.ZStat,                  ti.PStat + ti.FPLEN
.equ ti.TStat,                  ti.ZStat + ti.FPLEN
.equ ti.ChiStat,                        ti.TStat + ti.FPLEN
.equ ti.FStat,                  ti.ChiStat + ti.FPLEN
.equ ti.DF,                     ti.FStat + ti.FPLEN
.equ ti.Phat,                   ti.DF + ti.FPLEN
.equ ti.Phat1,                  ti.Phat + ti.FPLEN
.equ ti.Phat2,                  ti.Phat1 + ti.FPLEN
.equ ti.MeanX1,                 ti.Phat2 + ti.FPLEN
.equ ti.StdX1,                  ti.MeanX1 + ti.FPLEN
.equ ti.StatN1,                 ti.StdX1 + ti.FPLEN
.equ ti.MeanX2,                 ti.StatN1 + ti.FPLEN
.equ ti.StdX2,                  ti.MeanX2 + ti.FPLEN
.equ ti.StatN2,                 ti.StdX2 + ti.FPLEN
.equ ti.StdXP2,                 ti.StatN2 + ti.FPLEN
.equ ti.SLower,                 ti.StdXP2 + ti.FPLEN
.equ ti.SUpper,                 ti.SLower + ti.FPLEN
.equ ti.SStat,                  ti.SUpper + ti.FPLEN
.equ ti.anovaf_vars,            ti.SStat + ti.FPLEN
.equ ti.F_DF,                   ti.anovaf_vars
.equ ti.F_SS,                   ti.F_DF + ti.FPLEN
.equ ti.F_MS,                   ti.F_SS + ti.FPLEN
.equ ti.E_DF,                   ti.F_MS + ti.FPLEN
.equ ti.E_SS,                   ti.E_DF + ti.FPLEN
.equ ti.E_MS,                   ti.E_SS + ti.FPLEN

;System Flags
;----------------------------------------------------------------------
.equ ti.ioDelFlag,              0x0
.equ ti.inDelete,               0            ;1 = DELETE SCREEN

.equ ti.trigFlags,              0x0          ;Trigonometry mode settings
.equ ti.trigDeg,                        2            ;1 = degrees, 0=radians

.equ ti.kbdFlags,               0x0          ;Keyboard scan
.equ ti.kbdSCR,                 3            ;1=scan code ready
.equ ti.kbdKeyPress,            4            ;1=key has been pressed

.equ ti.doneFlags,              0x0          ;display "Done"
.equ ti.donePrgm,               5            ;1=display "Done" after prgm
;----------------------------------------------------------------------
.equ ti.editFlags,              0x1
.equ ti.editOpen,               2            ;1=edit buffer is open

.equ ti.ansFlags,               1
.equ ti.AnsScroll,              3            ;1=answer can scroll, seems must be reset in order to move about edit buffer

.equ ti.monFlags,               0x1          ;monitor flags
.equ ti.monAbandon,             4            ;1=don't start any long process in put away (#715)
;----------------------------------------------------------------------
.equ ti.plotFlags,              0x2          ;plot generation flags
.equ ti.plotLoc,                1            ;0=bkup and display, 1=display only
.equ ti.plotDisp,               2            ;1=plot is in display, 0=text in display, this also indicates whether graph is being shown or not

.equ ti.grfModeFlags,           0x2          ;graph mode settings
.equ ti.grfFuncM,               4            ;1=function graph
.equ ti.grfPolarM,              5            ;1=polar graph
.equ ti.grfParamM,              6            ;1=parametric graph
.equ ti.grfRecurM,              7            ;1=RECURSION graph
;----------------------------------------------------------------------
.equ ti.graphFlags,             0x3
.equ ti.graphDraw,              0            ;0=graph is valid, 1=redraw graph(dirty)
.equ ti.graphCursor,            2
;----------------------------------------------------------------------
.equ ti.grfDBFlags,             0x4
.equ ti.grfDot,                 0            ;0=line, 1=dot
.equ ti.grfSimul,               1            ;0=sequential, 1=simultaneous
.equ ti.grfGrid,                2            ;0=no grid, 1=grid
.equ ti.grfPolar,               3            ;0=rectangular, 1=polar coordinates
.equ ti.grfNoCoord,             4            ;0=display coordinates, 1=off
.equ ti.grfNoAxis,              5            ;0=axis, 1=no axis
.equ ti.grfLabel,               6            ;0=off, 1=axis label
;----------------------------------------------------------------------
.equ ti.textFlags,              0x5          ;Text output flags
.equ ti.textEraseBelow,         1            ;1=erase line below small char
.equ ti.textScrolled,           2            ;1=screen scrolled
.equ ti.textInverse,            3            ;1=display inverse bit-map
.equ ti.textInsMode,            4            ;0=overstrike, 1=insert mode
;----------------------------------------------------------------------
.equ ti.ParsFlag,               0x6          ;PARSER flags
.equ ti.listOpen,               5            ; {...}
.equ ti.matrixOpen1,            6            ; [[...]]
.equ ti.matrixOpen2,            7            ; [...]
;----------------------------------------------------------------------
.equ ti.ParsFlag2,              0x7          ;PARSER flags
.equ ti.numOP1,                 0            ;1=RESULT IN OP1, 0=NO RESULT
;----------------------------------------------------------------------
.equ ti.newDispF,               0x8          ;Derivative mode flags
.equ ti.preClrForMode,          0            ;1=HELP BLINK ON MODE SCREEN
.equ ti.allowProgTokens,                1            ;1=allow programming tokens to be parsed in BASIC programs
.equ ti.progExecuting,          1

.equ ti.apdFlags,               0x8          ;Automatic power-down
.equ ti.apdAble,                2            ;1=APD enabled
.equ ti.apdRunning,             3            ;1=APD clock running
.equ ti.apdWarmStart,           4            ;1=calculator is turning on from APD or power loss
;----------------------------------------------------------------------
.equ ti.web_err_mask,           0x60
;----------------------------------------------------------------------
.equ ti.onFlags,                0x9          ;on key flags
.equ ti.parseInput,             1            ;1=parse input when done
.equ ti.onRunning,              3            ;1=calculator is running
.equ ti.onInterrupt,            4            ;1=on key interrupt request

.equ ti.statFlags,              0x9          ;statistics flags
;unknown		equ 5		;unknown
.equ ti.statsValid,             6            ;1=stats are valid
;unknown		equ 7		;unknown
;----------------------------------------------------------------------
.equ ti.fmtFlags,               0x0A         ;numeric format flags
.equ ti.fmtExponent,            0            ;1=show exponent, 0=no exponent
.equ ti.fmtEng,                 1            ;1=engineering notion, 0=scientific

.equ ti.numMode,                        0x0A
.equ ti.fmtReal,                        5
.equ ti.fmtRect,                        6
.equ ti.fmtPolar,               7

.equ ti.realMode,               5
.equ ti.rectMode,               6
.equ ti.polarMode,              7

.equ ti.fmtBaseMask,             0b00011100  ; mask to base flags
.equ ti.fmtBaseShift,            2           ; offset to base flags
;----------------------------------------------------------------------
.equ ti.fmtOverride,            0x0B         ;copy of fmtFlags with conversion override
;----------------------------------------------------------------------
.equ ti.fmtEditFlags,           0x0C         ;numeric editing flags
.equ ti.fmtEdit,                        0            ;1=format number for editing

.equ ti.curFlags,               0x0C         ;Cursor
.equ ti.curAble,                2            ;1=cursor flash is enabled
.equ ti.curOn,                  3            ;1=cursor is showing
.equ ti.curLock,                4            ;1=cursor is locked off

.equ ti.cmdFlags,               0x0C         ;command editor flags
.equ ti.cmdVirgin,              5            ;1=nothing has been typed in cmd bfr
.equ ti.cmdExec,                        6           ;1=need to execute a command
;----------------------------------------------------------------------
.equ ti.appFlags,               0x0D         ;application flags
.equ ti.appWantIntrpt,          0            ;1=want ON key interrupts
.equ ti.appTextSave,            1            ;1=save characters in textShadow
.equ ti.appAutoScroll,          2            ;1=auto-scroll text on last line
.equ ti.appMenus,               3            ;1=process keys that bring up menus, 0=check Lock menu flag
.equ ti.appLockMenus,           4            ;1=ignore menu keys, 0=switch to home screen and bring up menu
.equ ti.appCurGraphic,          5            ;1=graphic cursor
.equ ti.appCurWord,             6            ;1=text cursor covers entire word
.equ ti.appExit,                7            ;1=application handles [EXIT] key itself

.equ ti.appWantIntrptF,         1 << ti.appWantIntrpt
.equ ti.appTextSaveF,           1 << ti.appTextSave
.equ ti.appAutoScrollF,         1 << ti.appAutoScroll
.equ ti.appMenusF,              1 << ti.appMenus
.equ ti.appLockMenusF,          1 << ti.appLockMenus
.equ ti.appCurGraphicF,         1 << ti.appCurGraphic
.equ ti.appCurWordF,            1 << ti.appCurWord
.equ ti.appExitF,               1 << ti.appExit
;----------------------------------------------------------------------
.equ ti.rclFlag,                        0x0E         ;OS recall queue flags
.equ ti.enableQueue,            7            ;1 = enable recall queue
;----------------------------------------------------------------------
.equ ti.seqFlags,               0x0F         ;Sequential Graph flags
.equ ti.webMode,                        0            ;0 = NORMAL SEQ MODE, 1 = WEB MODE
.equ ti.webVert,                        1
.equ ti.sequv,                  2            ;U vs V
.equ ti.seqvw,                  3            ;V vs W
.equ ti.sequw,                  4            ;U vs W
;----------------------------------------------------------------------
.equ ti.promptFlags,            0x11         ;prompt line flags
.equ ti.promptEdit,             0            ;1=editing in prompt buffer
;unknown		equ 7		;unknown
;----------------------------------------------------------------------
.equ ti.indicFlags,             0x12         ;Indicator flags
.equ ti.indicRun,               0            ;1=run indicator ON
.equ ti.indicInUse,             1            ;indicator save area in use=1, free=0 ;resetting will disable 2nd while in _getkey

.equ ti.shiftFlags,             0x12         ;[2nd] and [ALPHA] flags
.equ ti.shift2nd,               3            ;1=[2nd] has been pressed
.equ ti.shiftAlpha,             4            ;1=[ALPHA] has been pressed
.equ ti.shiftLwrAlph,           5            ;1=lower case, 0=upper case
.equ ti.shiftALock,             6            ;1=alpha lock has been pressed
.equ ti.shiftKeepAlph,          7            ;1=cannot cancel alpha shift
;----------------------------------------------------------------------
.equ ti.tblFlags,               0x13         ;table flags.
.equ ti.autoFill,               4            ;1=prompt, 0=fillAuto
.equ ti.autoCalc,               5            ;1=prompt, 0=CalcAuto
.equ ti.reTable,                        6            ;0=table is okay, 1=must recompute table.
;----------------------------------------------------------------------
.equ ti.sGrFlags,               0x14
.equ ti.grfSplit,               0            ;1=Split Graph, 0=Normal
.equ ti.vertSplit,              1            ;1=Vertical (left-right) Split
.equ ti.grfSChanged,            2            ;1=Graph just changed Split <-> normal
.equ ti.grfSplitOverride,       3            ;1 = ignore graph split flag if set
.equ ti.write_on_graph,         4            ;1 = TEXT OR EQU WRITING TO GRAPH SCREEN
.equ ti.g_style_active,         5            ;1 = GRAPH STYLES ARE ENABLED, USE THEM
.equ ti.cmp_mod_box,            6            ;1 = DOING MOD BOX PLOT COMPUTATION
.equ ti.textWrite,              7
;----------------------------------------------------------------------
.equ ti.newIndicFlags,          0x15
.equ ti.extraIndic,             0
.equ ti.saIndic,                        1
;3 has something to do with stat/list editor
;----------------------------------------------------------------------
.equ ti.interruptFlags,         0x16
.equ ti.secondTimerEnabled,     0            ;1 = second hardware timer enabled
;----------------------------------------------------------------------
.equ ti.smartFlags,             0x17
.equ ti.smarter_mask,           3
.equ ti.smarter_test,           1
.equ ti.smartGraph,             0
.equ ti.smartGraph_inv,         1
;----------------------------------------------------------------------
.equ ti.traceFlags,             0x18
.equ ti.grfExpr,                        0            ;set to hide expression while tracing
;----------------------------------------------------------------------
;There is a flag 19h.
;----------------------------------------------------------------------
.equ ti.statFlags2,             0x1A
.equ ti.statDiagnosticsOn,      0            ;1 = stat diagnostics on
.equ ti.noDelStat,              2            ;1 = don't delete stats
;----------------------------------------------------------------------
.equ ti.apdFlags2,              0x1B
.equ ti.warmStartInt,           6           ;1 = a warm start is occurning before the next interrupt
;----------------------------------------------------------------------
;There is a flag 1Ch (stats-related).
;----------------------------------------------------------------------
;There is a flag 1Dh.
;----------------------------------------------------------------------
;There is a flag 1Eh.
;----------------------------------------------------------------------
.equ ti.varTypeMask,            0x1F         ;is this a flag byte? yes
.equ ti.varGraphRef,            6
;----------------------------------------------------------------------
.equ ti.graphFlags2,            0x1F
.equ ti.splitOverride,          3            ;0 = force full screen with ParseInp, or something
;----------------------------------------------------------------------
.equ ti.asm_Flag1,              0x21         ;ASM CODING
.equ ti.asm_Flag2,              0x22         ;ASM CODING
.equ ti.asm_Flag3,              0x23         ;NO LONGER AVAILABLE
;----------------------------------------------------------------------
.equ ti.arcFlag,                        0x24
.equ ti.checkBatteryLevelFirst, 0            ;1 = check battery levels in Arc_Unarc first and throw error if low

.equ ti.getSendFlg,             0x24
.equ ti.comFailed,              1            ;1 = Get/Send Communication Failed

.equ ti.selfTestFlag,           0x24
.equ ti.resetOnPowerOn,         2            ;1 = Force RAM reset when APD disabled on next power on

.equ ti.appLwrCaseFlag,         0x24
.equ ti.lwrCaseActive,          3
;----------------------------------------------------------------------
.equ ti.contextFlags,           0x25
.equ ti.nocxPutAway,            5            ;1 = do not call cxPutAway routine
;----------------------------------------------------------------------
.equ ti.groupFlags,             0x26         ;used temporarily in Arc_Unarc
.equ ti.inGroup,                        1            ;1 = IN GROUP CONTEXT
.equ ti.noCompletionByte,       2            ;1 = do not write 0FCh when calling Arc_Unarc, leave as 0FEh
.equ ti.noDataWrite,            3            ;1 = do not write data when calling Arc_Unarc, nor size bytes
.equ ti.writeSizeBytesOnly,     5            ;1 = only write size bytes when calling Arc_Unarc
;----------------------------------------------------------------------
.equ ti.statusBarFlags,         0x27
.equ ti.noStatusBarMode,                7            ; 1 = abort drawing of statusbar mode, like "TEST MODE ENABLED"
;----------------------------------------------------------------------
.equ ti.APIFlg,                 0x28
.equ ti.appAllowContext,                0           ;app wants context changes to happen

.equ ti.appRunning,             4            ;app is currently running
.equ ti.appRetKeyOff,           7            ;1 = GetKey returns kOff when [2nd]+[ON] pressed
;----------------------------------------------------------------------
.equ ti.apiFlg2,                        0x29
;----------------------------------------------------------------------
.equ ti.apiFlg3,                        0x2A
;----------------------------------------------------------------------
.equ ti.apiFlg4,                        0x2B
.equ ti.cellOverride,           1            ;use cell override
.equ ti.fullScrnDraw,           2            ;DRAW INTO LAST ROW/COL OF SCREEN
;----------------------------------------------------------------------
.equ ti.xapFlag0,               0x2E         ;external app flags, do not use 0,(iy+2Eh) (used by mouse routines)
.equ ti.xapFlag1,               0x2F
.equ ti.xapFlag2,               0x30
.equ ti.xapFlag3,               0x31
;----------------------------------------------------------------------
.equ ti.fontFlags,              0x32
.equ ti.fracDrawLFont,          2
.equ ti.fracTallLFont,          3
.equ ti.customFont,             7
;----------------------------------------------------------------------
.equ ti.hookflags1,             0x33         ;also scriptFlag, rclFlag2, backGroundLink
.equ ti.alt_On,                 0            ;run ONSCRPT at startup
.equ ti.alt_Off,                        1            ;run OFFSCRPT at shutdown
.equ ti.useRclQueueEnd,         2            ;1 = external mode
.equ ti.ignoreBPLink,           3            ;1 = override flag for link activity hook
.equ ti.bPLinkOn,               4            ;1 = link activity hook active
.equ ti.enableKeyEcho,          5            ;1 = sends keypresses back to connected calc as remote control packets (with GetCSC vs. GetKey codes...really dumb, TI)
.equ ti.noTempDelete,           6            ;1 = do not delete temporary programs at homescreen
;----------------------------------------------------------------------
.equ ti.hookflags2,             0x34         ;also sysHookFlg
.equ ti.getCSCHookActive,       0            ;1 = GetCSC hook active
.equ ti.libraryHookActive,      1            ;1 = library hook active
.equ ti.noHookActive,           2            ;1 = same as 0; never used by OS
.equ ti.homescreenHookActive,   4            ;1 = homescreen hook active
.equ ti.rawKeyHookActive,       5            ;1 = raw key hook active
.equ ti.catalog2HookActive,     6            ;1 = catalog 2 hook active
.equ ti.cursorHookActive,       7            ;1 = cursor hook active
;----------------------------------------------------------------------
.equ ti.hookflags3,             0x35         ;also sysHookFlg1
.equ ti.tokenHookActive,                0            ;1 = token hook active
.equ ti.localizeHookActive,     1            ;1 = localize hook active
.equ ti.windowHookActive,       2            ;1 = window hook active
.equ ti.graphHookActive,                3            ;1 = graph hook active
.equ ti.yEquHookActive,         4            ;1 = Y= hook active
.equ ti.fontHookActive,         5            ;1 = font hook active
.equ ti.regraphHookActive,      6            ;1 = regraph hook active
.equ ti.drawingHookActive,      7            ;1 = drawing hook active
;----------------------------------------------------------------------
.equ ti.hookflags4,             0x36         ;also sysHookFlag2
.equ ti.traceHookActive,                0            ;1 = trace hook active
.equ ti.parserHookActive,       1            ;1 = parser hook active
.equ ti.appChangeHookActive,    2            ;1 = app change hook active
.equ ti.catalog1HookActive,     3            ;1 = catalog 1 hook active
.equ ti.helpHookActive,         4            ;1 = help hook active
.equ ti.cxRedispHookActive,     5            ;1 = cxRedisp hook active
.equ ti.menuHookActive,         6            ;1 = menu hook active
.equ ti.silentLinkHookActive,   7            ;1 = silent link hook active
;----------------------------------------------------------------------
;hookflags2Override	equ 37h		;set corresponding bit to kill iy+35h hook when executing app
;----------------------------------------------------------------------
;hookflags3Override	equ 38h		;set corresponding bit to kill iy+36h hook when executing app
;----------------------------------------------------------------------
;hookflags4Override	equ 39h		;set corresponding bit to kill iy+37h hook when executing app
;----------------------------------------------------------------------
.equ ti.hookflags5,             0x3A
.equ ti.usbActivityHookActive,  0            ;1 = USB activity hook active
;----------------------------------------------------------------------
.equ ti.plotFlag3,              0x3C
.equ ti.bufferOnly,             0
.equ ti.useFastCirc,            4
;----------------------------------------------------------------------
.equ ti.dBKeyFlags,             0x3D
.equ ti.keyDefaultsF,           6            ;1 = GetKey returns extended keycodes with TI-Keyboard
;----------------------------------------------------------------------
.equ ti.silentLinkFlags,                0x3E
.equ ti.silentLinkActive,       0            ;1 = SE/84+ silent link is active

.equ ti.extraHookFlags,         0x3E
.equ ti.checkCatalog2HookVer,   3            ;1 = check catalog 2 hook's version before executing it (and error or take other action if so)
.equ ti.openLibActive,          4            ;1 = OpenLib( was successfully called on a Flash application (ExecLib will error if zero)
;----------------------------------------------------------------------
.equ ti.clockFlags,             0x3F
.equ ti.notMDYMode,             0            ;0 = M/D/Y format
.equ ti.isYMDMode,              1            ;1 = Y/M/D format
.equ ti.is24Hour,               2            ;1 = clock in 24 hour mode
.equ ti.inAfternoon,            3            ;1 = current time is in afternoon (PM) (I think)
.equ ti.useTokensInString,      4            ;1 = use tokens instead of characters when displaying clock as string (for getTmStr and getDtStr vs. MODE screen) (keep this reset)
.equ ti.displayClock,           5            ;1 = display clock (this is set every second, reset otherwise)
.equ ti.clockOn,                        6            ;1 = clock on
;----------------------------------------------------------------------
.equ ti.mathprintFlags,         0x44
.equ ti.mathprintEnabled,       5            ;1 = use mathprint styling
;----------------------------------------------------------------------
.equ ti.InitialBootMenuFlags,   0x45
.equ ti.dispinitialBootMenu,    4            ; 1 = don't display the initial boot menu
;----------------------------------------------------------------------
.equ ti.backlightFlags,         0x46
.equ ti.restoreBrightness,      0            ;1 = restore lcd brightness when needed
;----------------------------------------------------------------------
.equ ti.grFlags,                        0x4A
.equ ti.drawGrLbls,             0            ;1 = don't draw Graph Labels (this is usually reset anyway)

.equ ti.putMapFlags,            0x4A
.equ ti.usePixelShadow2,                3            ;1 = use pixelshadow2, not pixelshadow
.equ ti.putMapUseColor,         4            ;1 = use custom color
;----------------------------------------------------------------------
.equ ti.graphDispFlags,         0x4B
.equ ti.backgroundValid,                4            ;1 = items in graph background are still valid
;----------------------------------------------------------------------
