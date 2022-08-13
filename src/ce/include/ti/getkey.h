/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI's keyboard interface defines
 */

#ifndef TI_GETKEY_H
#define TI_GETKEY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define os_KbdKey            (*(uint8_t*)0xD0058C)
#define os_KbdGetKy          (*(uint8_t*)0xD0058D)
#define os_KeyExtend         (*(uint8_t*)0xD0058E)

/**
 * Gets a key from the OS. This function does block, use os_GetCSC() if you need a non-blocking variant.
 *
 * @returns Key code
 * @returns Extended key code in high byte
 */
uint16_t os_GetKey(void);

/**
 * Keypress Equates
 */
#define k_Right             0x01
#define k_Left              0x02
#define k_Up                0x03
#define k_Down              0x04
#define k_Enter             0x05
#define k_AlphaEnter        0x06
#define k_AlphaUp           0x07
#define k_AlphaDown         0x08
#define k_Clear             0x09
#define k_Del               0x0A
#define k_Ins               0x0B
#define k_Recall            0x0C
#define k_LastEnt           0x0D
#define k_BOL               0x0E
#define k_EOL               0x0F

#define k_SelAll            0x10
#define k_UnselAll          0x11
#define k_LtoTI82           0x12
#define k_Backup            0x13
#define k_Recieve           0x14
#define k_LnkQuit           0x15
#define k_Trans             0x16
#define k_Rename            0x17
#define k_Overw             0x18
#define k_Omit              0x19
#define k_Cont              0x1A
#define k_SendID            0x1B
#define k_SendSW            0x1C
#define k_Yes               0x1D
#define k_NoWay             0x1E
#define k_vSendType         0x1F
#define k_OverWAll          0x20
#define k_No                0x25
#define k_KReset            0x26
#define k_App               0x27
#define k_Doug              0x28
#define k_Listflag          0x29
#define k_menuStart         0x2B /**< Start of menus */
#define k_AreYouSure        0x2B
#define k_AppsMenu          0x2C
#define k_Prgm              0x2D
#define k_Zoom              0x2E
#define k_Draw              0x2F
#define k_SPlot             0x30
#define k_Stat              0x31
#define k_Math              0x32
#define k_Test              0x33
#define k_Char              0x34
#define k_Vars              0x35
#define k_Mem               0x36
#define k_Matrix            0x37
#define k_Dist              0x38
#define k_Angle             0x39
#define k_List              0x3A
#define k_Calc              0x3B
#define k_Fin               0x3C
#define k_menuEnd           k_Fin /**< End of menus */
#define k_Catalog           0x3E
#define k_InputDone         0x3F
#define k_Off               k_InputDone
#define k_Quit              0x40
#define k_appStart          k_Quit /**< Start of group */
#define k_LinkIO            0x41
#define k_MatrixEd          0x42
#define k_StatEd            0x43
#define k_Graph             0x44
#define k_Mode              0x45
#define k_PrgmEd            0x46 /**< PROGRAM EDIT */
#define k_PrgmCr            0x47 /**< PROGRAM CREATE */
#define k_Window            0x48 /**< RANGE EDITOR */
#define k_Yequ              0x49 /**< EQUATION EDITOR */
#define k_Table             0x4A /**< TABLE EDITOR */
#define k_TblSet            0x4B /**< TABLE SET */
#define k_ChkRAM            0x4C /**< CHECK RAM (About screen) */
#define k_DelMem            0x4D /**< DELETE MEM */
#define k_ResetMem          0x4E /**< RESET MEM */
#define k_ResetDef          0x4F /**< RESET DEFAULT */
#define k_PrgmInput         0x50 /**< PROGRAM INPUT */
#define k_ZFactEd           0x51 /**< ZOOM FACTOR EDITOR */
#define k_Error             0x52 /**< ERROR */
#define k_SolveTVM          0x53 /**< TVM SOLVER */
#define k_SolveRoot         0x54 /**< SOLVE EDITOR */
#define k_StatP             0x55 /**< stat plot */
#define k_InfStat           0x56 /**< Inferential Statistic */
#define k_Format            0x57 /**< FORMAT */
#define k_ExtApps           0x58 /**< External Applications. */
#define k_NewApps           0x59 /**< New Apps for Cerberus. */
#define k_append            k_NewApps
#define k_echoStart1        0x5A /**< Start of group */
#define k_Trace             0x5A
#define k_ZFit              0x5B
#define k_ZIn               0x5C
#define k_ZOut              0x5D
#define k_ZPrev             0x5E
#define k_Box               0x5F
#define k_Decml             0x60
#define k_SetZm             0x61
#define k_Squar             0x62
#define k_Std               0x63
#define k_Trig              0x64
#define k_UsrZm             0x65
#define k_ZSto              0x66
#define k_ZInt              0x67
#define k_ZStat             0x68
#define k_echoStart2        0x69 /**< Start of group */
#define k_Select            0x69
#define k_Circl             0x6A
#define k_ClDrw             0x6B
#define k_Line              0x6C
#define k_Pen               0x6D
#define k_PtChg             0x6E
#define k_PtOff             0x6F
#define k_PtOn              0x70
#define k_Vert              0x71
#define k_Horiz             0x72
#define k_Text              0x73
#define k_TanLn             0x74
#define k_Eval              0x75
#define k_Inters            0x76
#define k_DYDX              0x77
#define k_FnIntg            0x78
#define k_RootG             0x79
#define k_DYDT              0x7A
#define k_DXDT              0x7B
#define k_DRDo              0x7C
#define k_GFMin             0x7D
#define k_GFMax             0x7E
#define k_EchoStart         0x7F /**< Start of group */
#define k_ListName          0x7F
#define k_Add               0x80
#define k_Sub               0x81
#define k_Mul               0x82
#define k_Div               0x83
#define k_Expon             0x84
#define k_LParen            0x85
#define k_RParen            0x86
#define k_LBrack            0x87
#define k_RBrack            0x88
#define k_Shade             0x89
#define k_Store             0x8A
#define k_Comma             0x8B
#define k_Chs               0x8C
#define k_DecPnt            0x8D
#define k_0                 0x8E
#define k_1                 0x8F
#define k_2                 0x90
#define k_3                 0x91
#define k_4                 0x92
#define k_5                 0x93
#define k_6                 0x94
#define k_7                 0x95
#define k_8                 0x96
#define k_9                 0x97
#define k_EE                0x98
#define k_Space             0x99
#define k_CapA              0x9A
#define k_CapB              0x9B
#define k_CapC              0x9C
#define k_CapD              0x9D
#define k_CapE              0x9E
#define k_CapF              0x9F
#define k_CapG              0xA0
#define k_CapH              0xA1
#define k_CapI              0xA2
#define k_CapJ              0xA3
#define k_CapK              0xA4
#define k_CapL              0xA5
#define k_CapM              0xA6
#define k_CapN              0xA7
#define k_CapO              0xA8
#define k_CapP              0xA9
#define k_CapQ              0xAA
#define k_CapR              0xAB
#define k_CapS              0xAC
#define k_CapT              0xAD
#define k_CapU              0xAE
#define k_CapV              0xAF
#define k_CapW              0xB0
#define k_CapX              0xB1
#define k_CapY              0xB2
#define k_CapZ              0xB3
#define k_Varx              0xB4
#define k_Pi                0xB5
#define k_Inv               0xB6
#define k_Sin               0xB7
#define k_ASin              0xB8
#define k_Cos               0xB9
#define k_ACos              0xBA
#define k_Tan               0xBB
#define k_ATan              0xBC
#define k_Square            0xBD
#define k_Sqrt              0xBE
#define k_Ln                0xBF
#define k_Exp               0xC0
#define k_Log               0xC1
#define k_ALog              0xC2
#define k_ToABC             0xC3
#define k_ClrTbl            0xC4
#define k_Ans               0xC5
#define k_Colon             0xC6
#define k_NDeriv            0xC7
#define k_FnInt             0xC8
#define k_Root              0xC9
#define k_Quest             0xCA
#define k_Quote             0xCB
#define k_Theta             0xCC
#define k_If                0xCD
#define k_Then              0xCE
#define k_Else              0xCF
#define k_For               0xD0
#define k_While             0xD1
#define k_Repeat            0xD2
#define k_End               0xD3
#define k_Pause             0xD4
#define k_Lbl               0xD5
#define k_Goto              0xD6
#define k_ISG               0xD7
#define k_DSL               0xD8
#define k_Menu              0xD9
#define k_Exec              0xDA
#define k_Return            0xDB
#define k_Stop              0xDC
#define k_Input             0xDD
#define k_Prompt            0xDE
#define k_Disp              0xDF
#define k_DispG             0xE0
#define k_DispT             0xE1
#define k_Output            0xE2
#define k_GetKey            0xE3
#define k_ClrHome           0xE4
#define k_PrtScr            0xE5
#define k_SinH              0xE6
#define k_CosH              0xE7
#define k_TanH              0xE8
#define k_ASinH             0xE9
#define k_ACosH             0xEA
#define k_ATanH             0xEB
#define k_LBrace            0xEC
#define k_RBrace            0xED
#define k_I                 0xEE
#define k_CONSTeA           0xEF
#define k_Plot3             0xF0
#define k_FMin              0xF1
#define k_FMax              0xF2
#define k_L1A               0xF3
#define k_L2A               0xF4
#define k_L3A               0xF5
#define k_L4A               0xF6
#define k_L5A               0xF7
#define k_L6A               0xF8
#define k_unA               0xF9
#define k_vnA               0xFA
#define k_wnA               0xFB

/**
 * THIS KEY MEANS THAT THE KEY PRESS IS ONE THAT ECHOS
 * INTO A BUFFER, AND IT IS A 2 BYTE KEY CODE, GO LOOK AT
 * (EXTECHO) FOR THE KEY VALUE
 */
#define k_ExtendEcho        0xFE
#define k_E1BT              k_ExtendEcho
#define k_DrawInv           (k_E1BT+(0<<8))
#define k_DrawF             (k_E1BT+(1<<8))
#define k_PixelOn           (k_E1BT+(2<<8))
#define k_PixelOff          (k_E1BT+(3<<8))
#define k_PxlTest           (k_E1BT+(4<<8))
#define k_RCGDB             (k_E1BT+(5<<8))
#define k_RCPic             (k_E1BT+(6<<8))
#define k_STGDB             (k_E1BT+(7<<8))
#define k_STPic             (k_E1BT+(8<<8))
#define k_Abs               (k_E1BT+(9<<8))
#define k_Tequ              (k_E1BT+(10<<8)) /**< == */
#define k_TNoteQ            (k_E1BT+(11<<8)) /**< <> */
#define k_TGT               (k_E1BT+(12<<8)) /**< > */
#define k_TGTE              (k_E1BT+(13<<8)) /**< >= */
#define k_TLT               (k_E1BT+(14<<8)) /**< < */
#define k_TLTE              (k_E1BT+(15<<8)) /**< <= */
#define k_And               (k_E1BT+(16<<8))
#define k_Or                (k_E1BT+(17<<8))
#define k_Xor               (k_E1BT+(18<<8))
#define k_Not               (k_E1BT+(19<<8))
#define k_LR1               (k_E1BT+(20<<8))
#define k_XRoot             (k_E1BT+(21<<8))
#define k_Cube              (k_E1BT+(22<<8))
#define k_CbRt              (k_E1BT+(23<<8)) /**< Cube ROOT */
#define k_ToDec             (k_E1BT+(24<<8))
#define k_CubicR            (k_E1BT+(25<<8))
#define k_QuartR            (k_E1BT+(26<<8))
#define k_Plot1             (k_E1BT+(27<<8))
#define k_Plot2             (k_E1BT+(28<<8))
#define k_Round             (k_E1BT+(29<<8))
#define k_IPart             (k_E1BT+(30<<8))
#define k_FPart             (k_E1BT+(31<<8))
#define k_Int               (k_E1BT+(32<<8))
#define k_Rand              (k_E1BT+(33<<8))
#define k_NPR               (k_E1BT+(34<<8))
#define k_NCR               (k_E1BT+(35<<8))
#define k_XFactorial        (k_E1BT+(36<<8))
#define k_Rad               (k_E1BT+(37<<8))
#define k_Degr              (k_E1BT+(38<<8)) /**< DEGREES CONV */
#define k_APost             (k_E1BT+(39<<8))
#define k_ToDMS             (k_E1BT+(40<<8))
#define k_RToPo             (k_E1BT+(41<<8)) /**< R */
#define k_RToPr             (k_E1BT+(42<<8))
#define k_PToRx             (k_E1BT+(43<<8))
#define k_PToRy             (k_E1BT+(44<<8))
#define k_RowSwap           (k_E1BT+(45<<8))
#define k_RowPlus           (k_E1BT+(46<<8))
#define k_TimRow            (k_E1BT+(47<<8))
#define k_TRowP             (k_E1BT+(48<<8))
#define k_SortA             (k_E1BT+(49<<8))
#define k_SortD             (k_E1BT+(50<<8))
#define k_Seq               (k_E1BT+(51<<8))
#define k_Min               (k_E1BT+(52<<8))
#define k_Max               (k_E1BT+(53<<8))
#define k_Mean              (k_E1BT+(54<<8))
#define k_Median            (k_E1BT+(55<<8))
#define k_Sum               (k_E1BT+(56<<8))
#define k_Prod              (k_E1BT+(57<<8))
#define k_Det               (k_E1BT+(58<<8))
#define k_Transp            (k_E1BT+(59<<8))
#define k_Dim               (k_E1BT+(60<<8))
#define k_Fill              (k_E1BT+(61<<8))
#define k_Ident             (k_E1BT+(62<<8))
#define k_Randm             (k_E1BT+(63<<8))
#define k_Aug               (k_E1BT+(64<<8))
#define k_OneVar            (k_E1BT+(65<<8))
#define k_TwoVar            (k_E1BT+(66<<8))
#define k_LR                (k_E1BT+(67<<8))
#define k_LRExp             (k_E1BT+(68<<8))
#define k_LRLn              (k_E1BT+(69<<8))
#define k_LRPwr             (k_E1BT+(70<<8))
#define k_MedMed            (k_E1BT+(71<<8))
#define k_Quad              (k_E1BT+(72<<8))
#define k_ClrLst            (k_E1BT+(73<<8))
#define k_Hist              (k_E1BT+(74<<8))
#define k_xyLine            (k_E1BT+(75<<8))
#define k_Scatter           (k_E1BT+(76<<8))
#define k_mRad              (k_E1BT+(77<<8))
#define k_mDeg              (k_E1BT+(78<<8))
#define k_mNormF            (k_E1BT+(79<<8))
#define k_mSci              (k_E1BT+(80<<8))
#define k_mEng              (k_E1BT+(81<<8))
#define k_mFloat            (k_E1BT+(82<<8))
#define k_Fix               (k_E1BT+(83<<8))
#define k_SplitOn           (k_E1BT+(84<<8))
#define k_FullScreen        (k_E1BT+(85<<8))
#define k_Stndrd            (k_E1BT+(86<<8))
#define k_Param             (k_E1BT+(87<<8))
#define k_Polar             (k_E1BT+(88<<8))
#define k_SeqG              (k_E1BT+(89<<8))
#define k_AFillOn           (k_E1BT+(90<<8))
#define k_AFillOff          (k_E1BT+(91<<8))
#define k_ACalcOn           (k_E1BT+(92<<8))
#define k_ACalcOff          (k_E1BT+(93<<8))
#define k_FNOn              (k_E1BT+(94<<8))
#define k_FNOff             (k_E1BT+(95<<8))
#define k_PlotsOn           (k_E1BT+(96<<8))
#define k_PlotsOff          (k_E1BT+(97<<8))
#define k_PixelChg          (k_E1BT+(98<<8))
#define k_SendMBL           (k_E1BT+(99<<8))
#define k_RecvMBL           (k_E1BT+(100<<8))
#define k_BoxPlot           (k_E1BT+(101<<8))
#define k_BoxIcon           (k_E1BT+(102<<8))
#define k_CrossIcon         (k_E1BT+(103<<8))
#define k_DotIcon           (k_E1BT+(104<<8))
#define k_E2BT              (k_E1BT+(105<<8))
#define k_Seqential         (k_E2BT+(0<<8))
#define k_SimulG            (k_E2BT+(1<<8))
#define k_PolarG            (k_E2BT+(2<<8))
#define k_RectG             (k_E2BT+(3<<8))
#define k_CoordOn           (k_E2BT+(4<<8))
#define k_CoordOff          (k_E2BT+(5<<8))
#define k_DrawLine          (k_E2BT+(6<<8))
#define k_DrawDot           (k_E2BT+(7<<8))
#define k_AxisOn            (k_E2BT+(8<<8))
#define k_AxisOff           (k_E2BT+(9<<8))
#define k_GridOn            (k_E2BT+(10<<8))
#define k_GridOff           (k_E2BT+(11<<8))
#define k_LblOn             (k_E2BT+(12<<8))
#define k_LblOff            (k_E2BT+(13<<8))
#define k_L1                (k_E2BT+(14<<8))
#define k_L2                (k_E2BT+(15<<8))
#define k_L3                (k_E2BT+(16<<8))
#define k_L4                (k_E2BT+(17<<8))
#define k_L5                (k_E2BT+(18<<8))
#define k_L6                (k_E2BT+(19<<8))

/**
 * These keys are laid on top of existing keys to
 * enable localization in the inferential stats editor.
 */
#define k_infData           (k_L1)
#define k_infStats          (k_L1+1)
#define k_infYes            (k_L1+2)
#define k_infNo             (k_L1+3)
#define k_infCalc           (k_L1+4)
#define k_infDraw           (k_L1+5)
#define k_infAlt1ne         (k_L1+6)
#define k_infAlt1lt         (k_L1+7)
#define k_infAlt1gt         (k_L1+8)
#define k_infAlt2ne         (k_L1+9)
#define k_infAlt2lt         (k_L1+10)
#define k_infAlt2gt         (k_L1+11)
#define k_infAlt3ne         (k_L1+12)
#define k_infAlt3lt         (k_L1+13)
#define k_infAlt3gt         (k_L1+14)
#define k_infAlt4ne         (k_L1+15)
#define k_infAlt4lt         (k_L1+16)
#define k_infAlt4gt         (k_L1+17)
#define k_infAlt5ne         (k_L1+18)
#define k_infAlt5lt         (k_L1+19)
#define k_infAlt5gt         (k_L1+20)
#define k_infAlt6ne         (k_L1+21)
#define k_infAlt6lt         (k_L1+22)
#define k_infAlt6gt         (k_L1+23)

#define k_MatA              (k_E2BT+(20<<8))
#define k_MatB              (k_E2BT+(21<<8))
#define k_MatC              (k_E2BT+(22<<8))
#define k_MatD              (k_E2BT+(23<<8))
#define k_MatE              (k_E2BT+(24<<8))
#define k_Xmin              (k_E2BT+(25<<8))
#define k_Xmax              (k_E2BT+(26<<8))
#define k_Xscl              (k_E2BT+(27<<8))
#define k_Ymin              (k_E2BT+(28<<8))
#define k_Ymax              (k_E2BT+(29<<8))
#define k_Yscl              (k_E2BT+(30<<8))
#define k_Tmin              (k_E2BT+(31<<8))
#define k_Tmax              (k_E2BT+(32<<8))
#define k_TStep             (k_E2BT+(33<<8))
#define k_Omin              (k_E2BT+(34<<8))
#define k_Omax              (k_E2BT+(35<<8))
#define k_OStep             (k_E2BT+(36<<8))
#define k_u0                (k_E2BT+(37<<8))
#define k_v0                (k_E2BT+(38<<8))
#define k_nMin              (k_E2BT+(39<<8))
#define k_nMax              (k_E2BT+(40<<8))
#define k_DeltaY            (k_E2BT+(41<<8))
#define k_DeltaX            (k_E2BT+(42<<8))
#define k_ZXmin             (k_E2BT+(43<<8))
#define k_ZXmax             (k_E2BT+(44<<8))
#define k_ZXscl             (k_E2BT+(45<<8))
#define k_ZYmin             (k_E2BT+(46<<8))
#define k_ZYmax             (k_E2BT+(47<<8))
#define k_ZYscl             (k_E2BT+(48<<8))
#define k_ZTmin             (k_E2BT+(49<<8))
#define k_ZTmax             (k_E2BT+(50<<8))
#define k_ZTStep            (k_E2BT+(51<<8))
#define k_ZOmin             (k_E2BT+(52<<8))
#define k_ZOmax             (k_E2BT+(53<<8))
#define k_ZOStep            (k_E2BT+(54<<8))
#define k_Zu0               (k_E2BT+(55<<8))
#define k_Zv0               (k_E2BT+(56<<8))
#define k_ZnMin             (k_E2BT+(57<<8))
#define k_ZnMax             (k_E2BT+(58<<8))
#define k_DelLast           (k_E2BT+(59<<8))
#define k_SinReg            (k_E2BT+(60<<8))
#define k_ConstE            (k_E2BT+(61<<8))
#define k_Pic1              (k_E2BT+(62<<8))
#define k_Pic2              (k_E2BT+(63<<8))
#define k_Pic3              (k_E2BT+(64<<8))
#define k_DelVar            (k_E2BT+(65<<8))
#define k_GetCalc           (k_E2BT+(66<<8))
#define k_RealM             (k_E2BT+(67<<8))
#define k_PolarM            (k_E2BT+(68<<8))
#define k_RectM             (k_E2BT+(69<<8))
#define k_uv                (k_E2BT+(70<<8)) /**< U vs V */
#define k_vw                (k_E2BT+(71<<8)) /**< V vs W */
#define k_uw                (k_E2BT+(72<<8)) /**< U vs W */
#define k_FinPMTend         (k_E2BT+(73<<8))
#define k_FinPMTbeg         (k_E2BT+(74<<8))
#define k_GraphStyle        (k_E2BT+(75<<8))
#define k_ExprOn            (k_E2BT+(76<<8))
#define k_ExprOff           (k_E2BT+(77<<8))
#define k_StatA             (k_E2BT+(78<<8))
#define k_StatB             (k_E2BT+(79<<8))
#define k_StatC             (k_E2BT+(80<<8))
#define k_Corr              (k_E2BT+(81<<8))
#define k_StatD             (k_E2BT+(82<<8))
#define k_StatE             (k_E2BT+(83<<8))
#define k_RegEq             (k_E2BT+(84<<8))
#define k_MinX              (k_E2BT+(85<<8))
#define k_Q1                (k_E2BT+(86<<8))
#define k_MD                (k_E2BT+(87<<8))
#define k_Q3                (k_E2BT+(88<<8))
#define k_MaxX              (k_E2BT+(89<<8))
#define k_StatX1            (k_E2BT+(90<<8))
#define k_StatY1            (k_E2BT+(91<<8))
#define k_StatX2            (k_E2BT+(92<<8))
#define k_StatY2            (k_E2BT+(93<<8))
#define k_StatX3            (k_E2BT+(94<<8))
#define k_StatY3            (k_E2BT+(95<<8))
#define k_TblMin            (k_E2BT+(96<<8))
#define k_TblStep           (k_E2BT+(97<<8))
#define k_SetupLst          (k_E2BT+(98<<8))
#define k_ClrAllLst         (k_E2BT+(99<<8))
#define k_Logistic          (k_E2BT+(100<<8))
#define k_ZTest             (k_E2BT+(101<<8))
#define k_TTest             (k_E2BT+(102<<8))
#define k_2SampZTest        (k_E2BT+(103<<8))
#define k_2SampTTest        (k_E2BT+(104<<8))
#define k_1PropZTest        (k_E2BT+(105<<8))
#define k_2PropZTest        (k_E2BT+(106<<8))
#define k_ChiTest           (k_E2BT+(107<<8))
#define k_2SampFTest        (k_E2BT+(108<<8))
#define k_ZIntVal           (k_E2BT+(109<<8))
#define k_TIntVal           (k_E2BT+(110<<8))
#define k_2SampTInt         (k_E2BT+(111<<8))
#define k_2SampZInt         (k_E2BT+(112<<8))
#define k_1PropZInt         (k_E2BT+(113<<8))
#define k_2PropZInt         (k_E2BT+(114<<8))
#define k_DNormal           (k_E2BT+(115<<8))
#define k_InvNorm           (k_E2BT+(116<<8))
#define k_DT                (k_E2BT+(117<<8))
#define k_Chi               (k_E2BT+(118<<8))
#define k_DF                (k_E2BT+(119<<8))
#define k_BinPDF            (k_E2BT+(120<<8))
#define k_BinCDF            (k_E2BT+(121<<8))
#define k_PoiPDF            (k_E2BT+(122<<8))
#define k_PoiCDF            (k_E2BT+(123<<8))
#define k_un                (k_E2BT+(124<<8))
#define k_vn                (k_E2BT+(125<<8))
#define k_wn                (k_E2BT+(126<<8))
#define k_Recn              (k_E2BT+(127<<8))
#define k_PlotStart         (k_E2BT+(128<<8))
#define k_ZPlotStart        (k_E2BT+(129<<8)) /**< recursion n */
#define k_XFact             (k_E2BT+(130<<8)) /**< PlotStart */
#define k_YFact             (k_E2BT+(131<<8)) /**< ZPlotStart */
#define k_ANOVA             (k_E2BT+(132<<8)) /**< XFact */
#define k_MaxY              (k_E2BT+(133<<8)) /**< YFact */
#define k_WebOn             (k_E2BT+(134<<8)) /**< MinY */
#define k_WebOff            (k_E2BT+(135<<8)) /**< MaxY */
#define k_TblInput          (k_E2BT+(136<<8)) /**< WEB ON */
#define k_GeoPDF            (k_E2BT+(137<<8)) /**< WEB OFF */
#define k_GeoCDF            (k_E2BT+(138<<8)) /**< WEB OFF */
#define k_ShadeNorm         (k_E2BT+(139<<8))
#define k_ShadeT            (k_E2BT+(140<<8))
#define k_ShadeChi          (k_E2BT+(141<<8))
#define k_ShadeF            (k_E2BT+(142<<8))
#define k_PlotStep          (k_E2BT+(143<<8))
#define k_ZPlotStep         (k_E2BT+(144<<8))
#define k_LinRegtTest       (k_E2BT+(145<<8))
#define k_MGT               (k_E2BT+(146<<8)) /**< VERT SPLIT */
#define k_SelectA           (k_E2BT+(147<<8))
#define k_ZFitA             (k_E2BT+(148<<8))
#define k_E2BT_End          (k_ZFitA)

/**
 * THIS KEY MEANS THAT IT IS A 2 BYTE KEYCODE
 * THERE ARE 3 OF THESE KEYS; BE CAREFUL WITH USAGE
 */
#define k_ExtendEcho2       0xFC

/**
 * More 2 Byte Keys
 */
#define k_E2BT2             k_ExtendEcho2
#define k_GDB1              (k_E2BT2+(0<<8))
#define k_GDB2              (k_E2BT2+(1<<8))
#define k_GDB3              (k_E2BT2+(2<<8))
#define k_Y1                (k_E2BT2+(3<<8))
#define k_Y2                (k_E2BT2+(4<<8))
#define k_Y3                (k_E2BT2+(5<<8))
#define k_Y4                (k_E2BT2+(6<<8))
#define k_Y5                (k_E2BT2+(7<<8))
#define k_Y6                (k_E2BT2+(8<<8))
#define k_Y7                (k_E2BT2+(9<<8))
#define k_Y8                (k_E2BT2+(10<<8))
#define k_Y9                (k_E2BT2+(11<<8))
#define k_Y0                (k_E2BT2+(12<<8))
#define k_X1T               (k_E2BT2+(13<<8))
#define k_Y1T               (k_E2BT2+(14<<8))
#define k_X2T               (k_E2BT2+(15<<8))
#define k_Y2T               (k_E2BT2+(16<<8))
#define k_X3T               (k_E2BT2+(17<<8))
#define k_Y3T               (k_E2BT2+(18<<8))
#define k_X4T               (k_E2BT2+(19<<8))
#define k_Y4T               (k_E2BT2+(20<<8))
#define k_X5T               (k_E2BT2+(21<<8))
#define k_Y5T               (k_E2BT2+(22<<8))
#define k_X6T               (k_E2BT2+(23<<8))
#define k_Y6T               (k_E2BT2+(24<<8))
#define k_R1                (k_E2BT2+(25<<8))
#define k_R2                (k_E2BT2+(26<<8))
#define k_R3                (k_E2BT2+(27<<8))
#define k_R4                (k_E2BT2+(28<<8))
#define k_R5                (k_E2BT2+(29<<8))
#define k_R6                (k_E2BT2+(30<<8))
#define k_GDB4              (k_E2BT2+(31<<8))
#define k_GDB5              (k_E2BT2+(32<<8))
#define k_GDB6              (k_E2BT2+(33<<8))
#define k_Pic4              (k_E2BT2+(34<<8))
#define k_Pic5              (k_E2BT2+(35<<8))
#define k_Pic6              (k_E2BT2+(36<<8))
#define k_GDB7              (k_E2BT2+(37<<8))
#define k_GDB8              (k_E2BT2+(38<<8))
#define k_GDB9              (k_E2BT2+(39<<8))
#define k_GDB0              (k_E2BT2+(40<<8))
#define k_Pic7              (k_E2BT2+(41<<8))
#define k_Pic8              (k_E2BT2+(42<<8))
#define k_Pic9              (k_E2BT2+(43<<8))
#define k_Pic0              (k_E2BT2+(44<<8))
#define k_StatN             (k_E2BT2+(45<<8))
#define k_XMean             (k_E2BT2+(46<<8))
#define k_Conj              (k_E2BT2+(47<<8))
#define k_Real              (k_E2BT2+(48<<8))
#define k_FAngle            (k_E2BT2+(49<<8))
#define k_LCM               (k_E2BT2+(50<<8))
#define k_GCD               (k_E2BT2+(51<<8))
#define k_RandInt           (k_E2BT2+(52<<8))
#define k_RandNorm          (k_E2BT2+(53<<8))
#define k_ToPolar           (k_E2BT2+(54<<8))
#define k_ToRect            (k_E2BT2+(55<<8))
#define k_YMean             (k_E2BT2+(56<<8))
#define k_StdX              (k_E2BT2+(57<<8))
#define k_StdX1             (k_E2BT2+(58<<8))
#define k_w0                (k_E2BT2+(59<<8))
#define k_MatF              (k_E2BT2+(60<<8))
#define k_MatG              (k_E2BT2+(61<<8))
#define k_MatRH             (k_E2BT2+(62<<8))
#define k_MatI              (k_E2BT2+(63<<8))
#define k_MatJ              (k_E2BT2+(64<<8))
#define k_YMean1            (k_E2BT2+(65<<8))
#define k_StdY              (k_E2BT2+(66<<8))
#define k_StdY1             (k_E2BT2+(67<<8))
#define k_MatToLst          (k_E2BT2+(68<<8))
#define k_LstToMat          (k_E2BT2+(69<<8))
#define k_CumSum            (k_E2BT2+(70<<8))
#define k_DeltaLst          (k_E2BT2+(71<<8))
#define k_StdDev            (k_E2BT2+(72<<8))
#define k_Variance          (k_E2BT2+(73<<8))
#define k_Length            (k_E2BT2+(74<<8))
#define k_EquToStrng        (k_E2BT2+(75<<8))
#define k_StrngToequ        (k_E2BT2+(76<<8))
#define k_Expr              (k_E2BT2+(77<<8))
#define k_SubStrng          (k_E2BT2+(78<<8))
#define k_InStrng           (k_E2BT2+(79<<8))
#define k_Str1              (k_E2BT2+(80<<8))
#define k_Str2              (k_E2BT2+(81<<8))
#define k_Str3              (k_E2BT2+(82<<8))
#define k_Str4              (k_E2BT2+(83<<8))
#define k_Str5              (k_E2BT2+(84<<8))
#define k_Str6              (k_E2BT2+(85<<8))
#define k_Str7              (k_E2BT2+(86<<8))
#define k_Str8              (k_E2BT2+(87<<8))
#define k_Str9              (k_E2BT2+(88<<8))
#define k_Str0              (k_E2BT2+(89<<8))
#define k_FinN              (k_E2BT2+(90<<8))
#define k_FinI              (k_E2BT2+(91<<8))
#define k_FinPV             (k_E2BT2+(92<<8))
#define k_FinPMT            (k_E2BT2+(93<<8))
#define k_FinFV             (k_E2BT2+(94<<8))
#define k_FinPY             (k_E2BT2+(95<<8))
#define k_FinCY             (k_E2BT2+(96<<8))
#define k_FinFPMT           (k_E2BT2+(97<<8))
#define k_FinFI             (k_E2BT2+(98<<8))
#define k_FinFPV            (k_E2BT2+(99<<8))
#define k_FinFN             (k_E2BT2+(100<<8))
#define k_FinFFV            (k_E2BT2+(101<<8))
#define k_FinNPV            (k_E2BT2+(102<<8))
#define k_FinIRR            (k_E2BT2+(103<<8))
#define k_FinBAL            (k_E2BT2+(104<<8))
#define k_FinPRN            (k_E2BT2+(105<<8))
#define k_FinINT            (k_E2BT2+(106<<8))
#define k_SumX              (k_E2BT2+(107<<8))
#define k_SumX2             (k_E2BT2+(108<<8))
#define k_FinToNom          (k_E2BT2+(109<<8))
#define k_FinToEff          (k_E2BT2+(110<<8))
#define k_FinDBD            (k_E2BT2+(111<<8))
#define k_StatVP            (k_E2BT2+(112<<8))
#define k_StatZ             (k_E2BT2+(113<<8))
#define k_StatT             (k_E2BT2+(114<<8))
#define k_StatChi           (k_E2BT2+(115<<8))
#define k_StatF             (k_E2BT2+(116<<8))
#define k_StatDF            (k_E2BT2+(117<<8))
#define k_StatPhat          (k_E2BT2+(118<<8))
#define k_StatPhat1         (k_E2BT2+(119<<8))
#define k_StatPhat2         (k_E2BT2+(120<<8))
#define k_StatMeanX1        (k_E2BT2+(121<<8))
#define k_StatMeanX2        (k_E2BT2+(122<<8))
#define k_StatStdX1         (k_E2BT2+(123<<8))
#define k_StatStdX2         (k_E2BT2+(124<<8))
#define k_StatStdXP         (k_E2BT2+(125<<8))
#define k_StatN1            (k_E2BT2+(126<<8))
#define k_StatN2            (k_E2BT2+(127<<8))
#define k_StatLower         (k_E2BT2+(128<<8))
#define k_StatUpper         (k_E2BT2+(129<<8))
#define k_uw0               (k_E2BT2+(130<<8))
#define k_Imag              (k_E2BT2+(131<<8))
#define k_SumY              (k_E2BT2+(132<<8))
#define k_Xres              (k_E2BT2+(133<<8))
#define k_Stat_s            (k_E2BT2+(134<<8))
#define k_SumY2             (k_E2BT2+(135<<8))
#define k_SumXY             (k_E2BT2+(136<<8))
#define k_uXres             (k_E2BT2+(137<<8))
#define k_ModBox            (k_E2BT2+(138<<8))
#define k_NormProb          (k_E2BT2+(139<<8))
#define k_NormalPDF         (k_E2BT2+(140<<8))
#define k_TPDF              (k_E2BT2+(141<<8))
#define k_ChiPDF            (k_E2BT2+(142<<8))
#define k_FPDF              (k_E2BT2+(143<<8))
#define k_MinY              (k_E2BT2+(144<<8)) /**< MinY */
#define k_RandBin           (k_E2BT2+(145<<8))
#define k_Ref               (k_E2BT2+(146<<8))
#define k_RRef              (k_E2BT2+(147<<8))
#define k_LRSqr             (k_E2BT2+(148<<8))
#define k_BRSqr             (k_E2BT2+(149<<8))
#define k_DiagOn            (k_E2BT2+(150<<8))
#define k_DiagOff           (k_E2BT2+(151<<8))
#define k_un1               (k_E2BT2+(152<<8)) /**< FOR RCL USE WHEN GOTTEN FROM 82 */
#define k_vn1               (k_E2BT2+(153<<8)) /**< FOR RCL USE WHEN GOTTEN FROM 82 */
#define k_83_00End          (k_vn1)       /**< end of original keys... */
#define k_Archive           (k_83_00End + (1<<8))
#define k_Unarchive         (k_83_00End + (2<<8))
#define k_Asm               (k_83_00End + (3<<8)) /**< Asm( */
#define k_AsmPrgm           (k_83_00End + (4<<8)) /**< AsmPrgm */
#define k_AsmComp           (k_83_00End + (5<<8)) /**< AsmComp( */
#define k_capAAcute         (k_83_00End + (6<<8))
#define k_capAGrave         (k_83_00End + (7<<8))
#define k_capACaret         (k_83_00End + (8<<8))
#define k_capADier          (k_83_00End + (9<<8))
#define k_aAcute            (k_83_00End + (10<<8))
#define k_aGrave            (k_83_00End + (11<<8))
#define k_aCaret            (k_83_00End + (12<<8))
#define k_aDier             (k_83_00End + (13<<8))
#define k_capEAcute         (k_83_00End + (14<<8))
#define k_capEGrave         (k_83_00End + (15<<8))
#define k_capECaret         (k_83_00End + (16<<8))
#define k_capEDier          (k_83_00End + (17<<8))
#define k_eAcute            (k_83_00End + (18<<8))
#define k_eGrave            (k_83_00End + (19<<8))
#define k_eCaret            (k_83_00End + (20<<8))
#define k_eDier             (k_83_00End + (21<<8))
#define k_capIAcute         (k_83_00End + (22<<8))
#define k_capIGrave         (k_83_00End + (23<<8))
#define k_capICaret         (k_83_00End + (24<<8))
#define k_capIDier          (k_83_00End + (25<<8))
#define k_iAcute            (k_83_00End + (26<<8))
#define k_iGrave            (k_83_00End + (27<<8))
#define k_iCaret            (k_83_00End + (28<<8))
#define k_iDier             (k_83_00End + (29<<8))
#define k_capOAcute         (k_83_00End + (30<<8))
#define k_capOGrave         (k_83_00End + (31<<8))
#define k_capOCaret         (k_83_00End + (32<<8))
#define k_capODier          (k_83_00End + (33<<8))
#define k_oAcute            (k_83_00End + (34<<8))
#define k_oGrave            (k_83_00End + (35<<8))
#define k_oCaret            (k_83_00End + (36<<8))
#define k_oDier             (k_83_00End + (37<<8))
#define k_capUAcute         (k_83_00End + (38<<8))
#define k_capUGrave         (k_83_00End + (39<<8))
#define k_capUCaret         (k_83_00End + (40<<8))
#define k_capUDier          (k_83_00End + (41<<8))
#define k_uAcute            (k_83_00End + (42<<8))
#define k_uGrave            (k_83_00End + (43<<8))
#define k_uCaret            (k_83_00End + (44<<8))
#define k_uDier             (k_83_00End + (45<<8))
#define k_capCCed           (k_83_00End + (46<<8))
#define k_cCed              (k_83_00End + (47<<8))
#define k_capNTilde         (k_83_00End + (48<<8))
#define k_nTilde            (k_83_00End + (49<<8))
#define k_accent            (k_83_00End + (50<<8))
#define k_grave             (k_83_00End + (51<<8))
#define k_dieresis          (k_83_00End + (52<<8))
#define k_quesDown          (k_83_00End + (53<<8))
#define k_exclamDown        (k_83_00End + (54<<8))
#define k_alpha             (k_83_00End + (55<<8))
#define k_beta              (k_83_00End + (56<<8))
#define k_gamma             (k_83_00End + (57<<8))
#define k_capDelta          (k_83_00End + (58<<8))
#define k_delta             (k_83_00End + (59<<8))
#define k_epsilon           (k_83_00End + (60<<8))
#define k_lambda            (k_83_00End + (61<<8))
#define k_mu                (k_83_00End + (62<<8))
#define k_pi2               (k_83_00End + (63<<8))
#define k_rho               (k_83_00End + (64<<8))
#define k_capSigma          (k_83_00End + (65<<8))
#define k_sigma             (k_83_00End + (66<<8))
#define k_tau               (k_83_00End + (67<<8))
#define k_phi               (k_83_00End + (68<<8))
#define k_capOmega          (k_83_00End + (69<<8))
#define k_phat              (k_83_00End + (70<<8))
#define k_chi2              (k_83_00End + (71<<8))
#define k_statF2            (k_83_00End + (72<<8))
#define k_La                (k_83_00End + (73<<8))
#define k_Lb                (k_83_00End + (74<<8))
#define k_Lc                (k_83_00End + (75<<8))
#define k_Ld                (k_83_00End + (76<<8))
#define k_Le                (k_83_00End + (77<<8))
#define k_Lf                (k_83_00End + (78<<8))
#define k_Lg                (k_83_00End + (79<<8))
#define k_Lh                (k_83_00End + (80<<8))
#define k_Li                (k_83_00End + (81<<8))
#define k_Lj                (k_83_00End + (82<<8))
#define k_Lk                (k_83_00End + (83<<8))
#define k_Ll                (k_83_00End + (84<<8))
#define k_Lm                (k_83_00End + (85<<8))
#define k_Lsmalln           (k_83_00End + (86<<8))
#define k_Lo                (k_83_00End + (87<<8))
#define k_Lp                (k_83_00End + (88<<8))
#define k_Lq                (k_83_00End + (89<<8))
#define k_Lsmallr           (k_83_00End + (90<<8))
#define k_Ls                (k_83_00End + (91<<8))
#define k_Lt                (k_83_00End + (92<<8))
#define k_Lu                (k_83_00End + (93<<8))
#define k_Lv                (k_83_00End + (94<<8))
#define k_Lw                (k_83_00End + (95<<8))
#define k_Lx                (k_83_00End + (96<<8))
#define k_Ly                (k_83_00End + (97<<8))
#define k_Lz                (k_83_00End + (98<<8))
#define k_GarbageC          (k_83_00End + (99<<8)) /**< GarbageCollect */
#define k_E2BT2_End         k_GarbageC

/**
 * THIS KEY MEANS THAT IT IS A 2 BYTE KEYCODE
 * UNLESS (EXTECHO) IS 0 THEN IT IS AN OLD 1 BYTE KEYCODE
 * THERE ARE 3 OF THESE KEYS; BE CAREFUL WITH USAGE
 */
#define k_ExtendEcho3       0xFB

/**
 * Even More 2 Byte Keys
 */
#define k_E2BT3             k_ExtendEcho3
#define k_SingleQuote       (k_E2BT3+(1<<8))
#define k_At                (k_E2BT3+(2<<8))
#define k_Hash              (k_E2BT3+(3<<8))
#define k_Dollar            (k_E2BT3+(4<<8))
#define k_Amp               (k_E2BT3+(5<<8))
#define k_Backquote         (k_E2BT3+(6<<8))
#define k_Semicolon         (k_E2BT3+(7<<8))
#define k_Backslash         (k_E2BT3+(8<<8))
#define k_Bar               (k_E2BT3+(9<<8))
#define k_Underscore        (k_E2BT3+(10<<8))
#define k_Tilde             (k_E2BT3+(11<<8))
#define k_Percent           (k_E2BT3+(12<<8))
#define k_Ellipsis          (k_E2BT3+(140<<8))
#define k_Ang               (k_E2BT3+(141<<8))
#define k_SS                (k_E2BT3+(142<<8))
#define k_SupX              (k_E2BT3+(143<<8))
#define k_SubT              (k_E2BT3+(144<<8))
#define k_Sub0              (k_E2BT3+(145<<8))
#define k_Sub1              (k_E2BT3+(146<<8))
#define k_Sub2              (k_E2BT3+(147<<8))
#define k_Sub3              (k_E2BT3+(148<<8))
#define k_Sub4              (k_E2BT3+(149<<8))
#define k_Sub5              (k_E2BT3+(150<<8))
#define k_Sub6              (k_E2BT3+(151<<8))
#define k_Sub7              (k_E2BT3+(152<<8))
#define k_Sub8              (k_E2BT3+(153<<8))
#define k_Sub9              (k_E2BT3+(154<<8))
#define k_Sub10             (k_E2BT3+(155<<8))

#ifdef __cplusplus
}
#endif

#endif
