/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI token defines
 */

#ifndef TI_TOKENS_H
#define TI_TOKENS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * TI-OS Token definitions
 */

#define tToDMS              0x01
#define tToDEC              0x02
#define tToAbc              0x03
#define tStore              0x04
#define tBoxPlot            0x05
#define tLBrack             0x06
#define tRBrack             0x07
#define tLBrace             0x08
#define tRBrace             0x09
#define tFromRad            0x0A
#define tFromDeg            0x0B
#define tRecip              0x0C
#define tSqr                0x0D
#define tTrnspos            0x0E
#define tCube               0x0F
#define tLParen             0x10
#define tRParen             0x11
#define tRound              0x12
#define tPxTst              0x13
#define tAug                0x14
#define tRowSwap            0x15
#define tRowPlu             0x16
#define tmRow               0x17
#define tmRowPlus           0x18
#define tMax                0x19 // 'max'
#define tMin                0x1A // 'min'
#define tRToPr              0x1B // 'R>Pr'
#define tRToPo              0x1C // 'R>Po'
#define tPToRx              0x1D // 'P>Rx'
#define tPToRy              0x1E // 'P>Ry'
#define tMedian             0x1F // 'MEDIAN'
#define tRandM              0x20 // 'randM'
#define tMean               0x21 // 'MEAN'
#define tRoot               0x22 // 'ROOT'
#define tSeries             0x23 // 'seq'
#define tFnInt              0x24 // 'fnInt'
#define tNDeriv             0x25 // 'fnIr'
#define tEvalF              0x26
#define tFmin               0x27
#define tFmax               0x28
#define tSpace              0x29 // ' '
#define tString             0x2A // '"'
#define tComma              0x2B // ','
#define tii                 0x2C // 'i'
#define tFact               0x2D // '!'
#define tCubicR             0x2E
#define tQuartR             0x2F
#define t0                  0x30
#define t1                  0x31
#define t2                  0x32
#define t3                  0x33
#define t4                  0x34
#define t5                  0x35
#define t6                  0x36
#define t7                  0x37
#define t8                  0x38
#define t9                  0x39
#define tDecPt              0x3A // '.'
#define tee                 0x3B // 'e'
#define tOr                 0x3C // '_or_'
#define tXor                0x3D
#define tColon              0x3E // ':'
#define tEnter              0x3F
#define tAnd                0x40 // '_and_'
#define tA                  0x41
#define tB                  0x42
#define tC                  0x43
#define tD                  0x44
#define tE                  0x45
#define tF                  0x46
#define tG                  0x47
#define tH                  0x48
#define tI                  0x49
#define tJ                  0x4A
#define tK                  0x4B
#define tL                  0x4C
#define tM                  0x4D
#define tN                  0x4E
#define tO                  0x4F
#define tP                  0x50
#define tQ                  0x51
#define tR                  0x52
#define tS                  0x53
#define tT                  0x54
#define tU                  0x55
#define tV                  0x56
#define tW                  0x57
#define tX                  0x58
#define tY                  0x59
#define tZ                  0x5A
#define tTheta              0x5B
#define tProg               0x5F

/*
 * Mode settings tokens
 */
#define tRad                0x64 // 'Radian'
#define tDeg                0x65 // 'Degree'
#define tNormF              0x66 // 'Normal'
#define tSci                0x67 // 'Sci'
#define tEng                0x68 // 'Eng'
#define tFloat              0x69 // 'Float'
#define tFix                0x73 // 'Fix_'
#define tSplitOn            0x74
#define tFullScreen         0x75
#define tStndrd             0x76 // 'Func'
#define tParam              0x77 // 'Param'
#define tPolar              0x78 // 'Pol'
#define tSeqG               0x79 // ;79h
#define tAFillOn            0x7A // 'AUTO FILL ON'
#define tAFillOff           0x7B // 'AutoFill OFF'
#define tACalcOn            0x7C
#define tACalcOff           0x7D

#define tEQ                 0x6A // '='
#define tLT                 0x6B // '<'
#define tGT                 0x6C // '>'
#define tLE                 0x6D // LLE
#define tGE                 0x6E // LGE
#define tNE                 0x6F // LNE
#define tAdd                0x70 // '+'
#define tSub                0x71 // '-'
#define tAns                0x72
#define tMul                0x82 // '*'
#define tDiv                0x83 // '/'

#define tBoxIcon            0x7F
#define tCrossIcon          0x80
#define tDotIcon            0x81

#define tTrace              0x84 // 'Trace'
#define tClDrw              0x85 // 'ClrDraw'
#define tZoomStd            0x86 // 'ZStd'
#define tZoomtrg            0x87 // 'Ztrg'
#define tZoomBox            0x88 // 'ZBOX'
#define tZoomIn             0x89 // 'ZIn'
#define tZoomOut            0x8A // 'ZOut'
#define tZoomSqr            0x8B // 'ZSqr'
#define tZoomInt            0x8C // 'ZInt'
#define tZoomPrev           0x8D // 'ZPrev'
#define tZoomDec            0x8E // 'ZDecm'
#define tZoomStat           0x8F // 'ZStat
#define tUsrZm              0x90 // 'ZRcl'
#define tPrtScrn            0x91 // 'PrtScrn'
#define tZoomSto            0x92 //  'ZSto'
#define tText               0x93

#define tnPr                0x94 // '_nPr_'
#define tnCr                0x95 // '_nCr_'

// Graph Commands
#define tYOn                0x96 // 'FnOn_'
#define tYOff               0x97 // 'FnOff_'
#define tStPic              0x98 // 'StPic_'
#define tRcPic              0x99 // 'RcPic_'
#define tStoDB              0x9A // 'StGDB_'
#define tRclDB              0x9B // 'RcGDB_'
#define tLine               0x9C // 'Line'
#define tVert               0x9D // 'Vert_'
#define tPtOn               0x9E // 'PtOn'
#define tPtOff              0x9F // 'PtOff'
#define tPtChg              0xA0 // 'PtChg'
#define tPXOn               0xA1
#define tPXOff              0xA2
#define tPXChg              0xA3
#define tShade              0xA4 // 'Shade'
#define tCircle             0xA5 // 'Circle'
#define tHorz               0xA6 // 'HORIZONTAL'
#define tTanLn              0xA7 // 'TanLn'
#define tDrInv              0xA8 // 'DrInv_'
#define tDrawF              0xA9 // 'DrawF_'

// Functions with no argument
#define tRand               0xAB // 'rand'
#define tPi                 0xAC //  Lpi
#define tGetKey             0xAD // 'getKy'
#define tAPost              0xAE // '''
#define tQuest              0xAF // '?'
#define tChs                0xB0
#define tInt                0xB1
#define tAbs                0xB2
#define tDet                0xB3
#define tIdent              0xB4
#define tDim                0xB5
#define tSum                0xB6
#define tProd               0xB7
#define tNot                0xB8
#define tIPart              0xB9
#define tFPart              0xBA

// New 2 Byte Tokens
#define t2ByteTok           0xBB
#define tSqrt               0xBC
#define tCubRt              0xBD
#define tLn                 0xBE
#define tExp                0xBF
#define tLog                0xC0
#define tALog               0xC1
#define tSin                0xC2
#define tASin               0xC3
#define tCos                0xC4
#define tACos               0xC5
#define tTan                0xC6
#define tATan               0xC7
#define tSinH               0xC8
#define tASinH              0xC9
#define tCoshH              0xCA
#define tACosH              0xCB
#define tTanH               0xCC
#define tATanH              0xCD

// Some Programming Commands
#define tIf                 0xCE // 'If_'
#define tThen               0xCF // 'Then_'
#define tElse               0xD0 // 'Else_'
#define tWhile              0xD1 // 'While_'
#define tRepeat             0xD2 // 'Repeat_'
#define tFor                0xD3 // 'For_'
#define tEnd                0xD4 // 'End'
#define tReturn             0xD5 // 'Return'
#define tLbl                0xD6 // 'Lbl_'
#define tGoto               0xD7 // 'Goto_'
#define tPause              0xD8 // 'Pause_'
#define tStop               0xD9 // 'Stop'
#define tISG                0xDA // 'IS>'
#define tDSL                0xDB // 'DS<'
#define tInput              0xDC // 'Input_'
#define tPrompt             0xDD // 'Prompt_'
#define tDisp               0xDE // 'Disp_'
#define tDispG              0xDF // 'DispG'
#define tOutput             0xE0 // 'Outpt'
#define tClLCD              0xE1 // 'ClLCD'
#define tConst              0xE2 // 'Fill'
#define tSortA              0xE3 // 'sortA_'
#define tSortD              0xE4 // 'sortD_'
#define tDispTab            0xE5 // 'Disp Table
#define tMenu               0xE6 // 'Menu'
#define tSendMBL            0xE7 // 'Send'
#define tGetMBL             0xE8 // 'Get'

// Stat Plot Commands
#define tPlotOn             0xE9 // 'PLOTSON'
#define tPlotOff            0xEA // 'PLOTSOFF
#define tListName           0xEB // List Designator
#define tPlot1              0xEC
#define tPlot2              0xED
#define tPlot3              0xEE
#define tUnused01           0xEF // available?
#define tPower              0xF0 // '^'
#define tXRoot              0xF1 // LsupX,Lroot
#define tOneVar             0xF2 // 'OneVar_'
#define tTwoVar             0xF3
#define tLR                 0xF4 // 'LinR(A+BX)'
#define tLRExp              0xF5 // 'ExpR_'
#define tLRLn               0xF6 // 'LnR_'
#define tLRPwr              0xF7 // 'PwrR_'
#define tMedMed             0xF8
#define tQuad               0xF9
#define tClrLst             0xFA // 'Clear List'
#define tClrTbl             0xFB // 'Clear Table'
#define tHist               0xFC // 'Hist_'
#define txyLine             0xFD // 'xyline_'
#define tScatter            0xFE // 'Scatter_'
#define tLR1                0xFF // 'LINR(AX+B)'

#define tGFormat            0x7E
// 2nd Half Of Graph Format Tokens
#define tSeq                0x00 // 'SeqG'
#define tSimulG             0x01 // 'SimulG'
#define tPolarG             0x02 // 'PolarGC'
#define tRectG              0x03 // 'RectGC'
#define tCoordOn            0x04 // 'CoordOn'
#define tCoordOff           0x05 // 'CoordOff'
#define tDrawLine           0x06 // 'DrawLine'
#define tDrawDot            0x07 // 'DrawDot'
#define tAxisOn             0x08 // 'AxesOn'
#define tAxisOff            0x09 // 'AxesOff'
#define tGridOn             0x0A // 'GridOn'
#define tGridOff            0x0B // 'GridOff'
#define tLblOn              0x0C // 'LabelOn'
#define tLblOff             0x0D // 'LabelOff'
#define tWebOn              0x0E // 'WebOn'
#define tWebOff             0x0F // 'WebOFF'
#define tuv                 0x10 // U vs V
#define tvw                 0x11 // V vs W
#define tuw                 0x12 // U vs W

#define tVarMat             0x5C
// 2nd Half Of User Matrix Tokens
#define tMatA               0x00 // MAT A
#define tMatB               0x01 // MAT B
#define tMatC               0x02 // MAT C
#define tMatD               0x03 // MAT D
#define tMatE               0x04 // MAT E
#define tMatF               0x05 // MAT F
#define tMatG               0x06 // MAT G
#define tMatH               0x07 // MAT H
#define tMatI               0x08 // MAT I
#define tMatJ               0x09 // MAT J

#define tVarLst             0x5D
// 2nd Half Of User List Tokens
#define tL1                 0x00 // LIST 1
#define tL2                 0x01 // LIST 2
#define tL3                 0x02 // LIST 3
#define tL4                 0x03 // LIST 4
#define tL5                 0x04 // LIST 5
#define tL6                 0x05 // LIST 6

#define tVarEqu             0x5E
// 2nd Half Of User Equation Tokens

// Y Equations have bit 4 set
#define tY1                 0x10 // Y1
#define tY2                 0x11 // Y2
#define tY3                 0x12 // Y3
#define tY4                 0x13 // Y4
#define tY5                 0x14 // Y5
#define tY6                 0x15 // Y6
#define tY7                 0x16 // Y7
#define tY8                 0x17 // Y8
#define tY9                 0x18 // Y9
#define tY0                 0x19 // Y0

// Param Equations Have Bit 5 Set
#define tX1T                0x20 // X1t
#define tY1T                0x21 // Y1t
#define tX2T                0x22 // X2t
#define tY2T                0x23 // Y2t
#define tX3T                0x24 // X3t
#define tY3T                0x25 // Y3t
#define tX4T                0x26 // X4t
#define tY4T                0x27 // Y4t
#define tX5T                0x28 // X5t
#define tY5T                0x29 // Y5t
#define tX6T                0x2A // X6t
#define tY6T                0x2B // Y6t

// Polar Equations Have Bit 6 Set
#define tR1                 0x40 // R1
#define tR2                 0x41 // R2
#define tR3                 0x42 // R3
#define tR4                 0x43 // R4
#define tR5                 0x44 // R5
#define tR6                 0x45 // R6

// Recursion Equations Have Bit 7 Set
#define tun                 0x80 // Un
#define tvn                 0x81 // Vn
#define twn                 0x82 // Wn

#define tVarPict            0x60
// 2nd Half User Picture Tokens
#define tPic1               0x00 // PIC1
#define tPic2               0x01 // PIC2
#define tPic3               0x02 // PIC3
#define tPic4               0x03 // PIC4
#define tPic5               0x04 // PIC5
#define tPic6               0x05 // PIC6
#define tPic7               0x06 // PIC7
#define tPic8               0x07 // PIC8
#define tPic9               0x08 // PIC9
#define tPic0               0x09 // PIC0

#define tVarGDB             0x61
// 2nd Half User Graph Database Tokens
#define tGDB1               0x00 // GDB1
#define tGDB2               0x01 // GDB2
#define tGDB3               0x02 // GDB3
#define tGDB4               0x03 // GDB4
#define tGDB5               0x04 // GDB5
#define tGDB6               0x05 // GDB6
#define tGDB7               0x06 // GDB7
#define tGDB8               0x07 // GDB8
#define tGDB9               0x08 // GDB9
#define tGDB0               0x09 // GDB0

#define tVarStrng           0xAA
// 2nd Half Of String Vars
#define tStr1               0x00
#define tStr2               0x01
#define tStr3               0x02
#define tStr4               0x03
#define tStr5               0x04
#define tStr6               0x05
#define tStr7               0x06
#define tStr8               0x07
#define tStr9               0x08
#define tStr0               0x09

#define tVarOut             0x62
// 2nd Half Of System Output Only Variables
#define tRegEq              0x01 // REGRESSION EQUATION
#define tStatN              0x02 // STATISTICS N
#define tXMean              0x03 // X MEAN
#define tSumX               0x04 // SUM(X)
#define tSumXSqr            0x05 // SUM(X^2)
#define tStdX               0x06 // STANDARD DEV X
#define tStdPX              0x07 // STANDARD DEV POP X
#define tMinX               0x08 // Min X VALUE
#define tMaxX               0x09 // Max X VALUE
#define tMinY               0x0A // Min Y VALUE
#define tMaxY               0x0B // Max Y VALUE
#define tYmean              0x0C // Y MEAN
#define tSumY               0x0D // SUM(Y)
#define tSumYSqr            0x0E // SUM(Y^2)
#define tStdY               0x0F // STANDARD DEV Y
#define tStdPY              0x10 // STANDARD DEV POP Y
#define tSumXY              0x11 // SUM(XY)
#define tCorr               0x12 // CORRELATION
#define tMedX               0x13 // MED(X)
#define tQ1                 0x14 // 1ST QUADRANT OF X
#define tQ3                 0x15 // 3RD QUADRANT OF X
#define tQuadA              0x16 // 1ST TERM OF QUAD POLY REG/ Y-INT
#define tQuadB              0x17 // 2ND TERM OF QUAD POLY REG/ SLOPE
#define tQuadC              0x18 // 3RD TERM OF QUAD POLY REG
#define tCubeD              0x19 // 4TH TERM OF CUBIC POLY REG
#define tQuartE             0x1A // 5TH TERM OF QUART POLY REG
#define tMedX1              0x1B // x1 FOR MED-MED
#define tMedX2              0x1C // x2 FOR MED-MED
#define tMedX3              0x1D // x3 FOR MED-MED
#define tMedY1              0x1E // y1 FOR MED-MED
#define tMedY2              0x1F // y2 FOR MED-MED
#define tMedY3              0x20 // y3 FOR MED-MED
#define tRecurn             0x21 // RECURSION N
#define tStatP              0x22
#define tStatZ              0x23
#define tStatT              0x24
#define tStatChi            0x25
#define tStatF              0x26
#define tStatDF             0x27
#define tStatPhat           0x28
#define tStatPhat1          0x29
#define tStatPhat2          0x2A
#define tStatMeanX1         0x2B
#define tStatStdX1          0x2C
#define tStatN1             0x2D
#define tStatMeanX2         0x2E
#define tStatStdX2          0x2F
#define tStatN2             0x30
#define tStatStdXP          0x31
#define tStatLower          0x32
#define tStatUpper          0x33
#define tStat_s             0x34
#define tLRSqr              0x35
#define tBRSqr              0x36

// These next tokens are only used to access the data
// They are display only and the user cannot access them at all
#define tF_DF               0x37
#define tF_SS               0x38
#define tF_MS               0x39
#define tE_DF               0x3A
#define tE_SS               0x3B
#define tE_MS               0x3C

#define tVarSys             0x63
// 2nd Half Of System Input/Output Variables
#define tuXscl              0x00
#define tuYscl              0x01
#define tXscl               0x02
#define tYscl               0x03
#define tRecuru0            0x04
#define tRecurv0            0x05
#define tun1                0x06
#define tvn1                0x07
#define tuRecuru0           0x08
#define tuRecurv0           0x09
#define tXmin               0x0A
#define tXmax               0x0B
#define tYmin               0x0C
#define tYmax               0x0D
#define tTmin               0x0E
#define tTmax               0x0F
#define tThetaMin           0x10
#define tThetaMax           0x11
#define tuXmin              0x12
#define tuXmax              0x13
#define tuYmin              0x14
#define tuYmax              0x15
#define tuThetMin           0x16
#define tuThetMax           0x17
#define tuTmin              0x18
#define tuTmax              0x19
#define tTblMin             0x1A
#define tPlotStart          0x1B
#define tuPlotStart         0x1C
#define tnMax               0x1D
#define tunMax              0x1E
#define tnMin               0x1F
#define tunMin              0x20
#define tTblStep            0x21
#define tTStep              0x22
#define tThetaStep          0x23
#define tuTStep             0x24
#define tuThetStep          0x25
#define tDeltaX             0x26
#define tDeltaY             0x27
#define tXFact              0x28
#define tYFact              0x29
#define tTblInput           0x2A
#define tFinN               0x2B
#define tFinI               0x2C
#define tFinPV              0x2D
#define tFinPMT             0x2E
#define tFinFV              0x2F
#define tFinPY              0x30
#define tFinCY              0x31
#define tRecurw0            0x32
#define tuRecurw0           0x33
#define tPlotStep           0x34
#define tuPlotStep          0x35
#define tXres               0x36
#define tuXres              0x37
#define tRecuru02           0x38
#define tuRecuru02          0x39
#define tRecurv02           0x3C
#define tuRecurv02          0x3D
#define tRecurw02           0x3E
#define tuRecurw02          0x3F

// 2nd Byte Of t2ByteTok Tokens
#define tFinNPV             0x00
#define tFinIRR             0x01
#define tFinBAL             0x02
#define tFinPRN             0x03
#define tFinINT             0x04
#define tFinToNom           0x05
#define tFinToEff           0x06
#define tFinDBD             0x07
#define tLCM                0x08
#define tGCD                0x09
#define tRandInt            0x0A
#define tRandBin            0x0B
#define tSubStrng           0x0C
#define tStdDev             0x0D
#define tVariance           0x0E
#define tInStrng            0x0F
#define tDNormal            0x10
#define tInvNorm            0x11
#define tDT                 0x12
#define tChI                0x13
#define tDF                 0x14
#define tBINPDF             0x15
#define tBINCDF             0x16
#define tPOIPDF             0x17
#define tPOICDF             0x18
#define tGEOPDF             0x19
#define tGEOCDF             0x1A
#define tNormalPDF          0x1B
#define tTPDF               0x1C
#define tChiPDF             0x1D
#define tFPDF               0x1E
#define tRandNorm           0x1F
#define tFinFPMT            0x20
#define tFinFI              0x21
#define tFinFPV             0x22
#define tFinFN              0x23
#define tFinFFV             0x24
#define tConj               0x25
#define tReal               0x26
#define tImag               0x27
#define tAngle              0x28
#define tCumSum             0x29
#define tExpr               0x2A
#define tLength             0x2B
#define tDeltaLst           0x2C
#define tRef                0x2D
#define tRRef               0x2E
#define tToRect             0x2F
#define tToPolar            0x30
#define tConste             0x31
#define tSinReg             0x32
#define tLogistic           0x33
#define tLinRegTTest        0x34
#define tShadeNorm          0x35
#define tShadeT             0x36
#define tShadeChi           0x37
#define tShadeF             0x38
#define tMatToLst           0x39
#define tLstToMat           0x3A
#define tZTest              0x3B
#define tTTest              0x3C
#define t2SampZTest         0x3D
#define t1PropZTest         0x3E
#define t2PropZTest         0x3F
#define tChiTest            0x40
#define tZIntVal            0x41
#define t2SampZInt          0x42
#define t1PropZInt          0x43
#define t2PropZInt          0x44
#define tGraphStyle         0x45
#define t2SampTTest         0x46
#define t2SampFTest         0x47
#define tTIntVal            0x48
#define t2SampTInt          0x49
#define tSetupLst           0x4A
#define tFinPMTend          0x4B
#define tFinPMTbeg          0x4C
#define tRealM              0x4D
#define tPolarM             0x4E
#define tRectM              0x4F
#define tExprOn             0x50
#define tExprOff            0x51
#define tClrAllLst          0x52
#define tGetCalc            0x53
#define tDelVar             0x54
#define tEquToStrng         0x55
#define tStrngToequ         0x56
#define tDelLast            0x57
#define tSelect             0x58
#define tANOVA              0x59
#define tModBox             0x5A
#define tNormProb           0x5B
#define tMGT                0x64
#define tZFit               0x65
#define tDiag_on            0x66
#define tDiag_off           0x67
#define tArchive            0x68
#define tUnarchive          0x69
#define tAsm                0x6A
#define tAsmComp            0x6B
#define tAsmPrgm            0x6C
#define tAsmCmp             0x6D
#define tLcapAAcute         0x6E
#define tLcapAGrave         0x6F
#define tLcapACaret         0x70
#define tLcapADier          0x71
#define tLaAcute            0x72
#define tLaGrave            0x73
#define tLaCaret            0x74
#define tLaDier             0x75
#define tLcapEAcute         0x76
#define tLcapEGrave         0x77
#define tLcapECaret         0x78
#define tLcapEDier          0x79
#define tLeAcute            0x7A
#define tLeGrave            0x7B
#define tLeCaret            0x7C
#define tLeDier             0x7D
#define tLcapIGrave         0x7F
#define tLcapICaret         0x80
#define tLcapIDier          0x81
#define tLiAcute            0x82
#define tLiGrave            0x83
#define tLiCaret            0x84
#define tLiDier             0x85
#define tLcapOAcute         0x86
#define tLcapOGrave         0x87
#define tLcapOCaret         0x88
#define tLcapODier          0x89
#define tLoAcute            0x8A
#define tLoGrave            0x8B
#define tLoCaret            0x8C
#define tLoDier             0x8D
#define tLcapUAcute         0x8E
#define tLcapUGrave         0x8F
#define tLcapUCaret         0x90
#define tLcapUDier          0x91
#define tLuAcute            0x92
#define tLuGrave            0x93
#define tLuCaret            0x94
#define tLuDier             0x95
#define tLcapCCed           0x96
#define tLcCed              0x97
#define tLcapNTilde         0x98
#define tLnTilde            0x99
#define tLaccent            0x9A
#define tLgrave             0x9B
#define tLdieresis          0x9C
#define tLquesDown          0x9D
#define tLexclamDown        0x9E
#define tLalpha             0x9F
#define tLbeta              0xA0
#define tLgamma             0xA1
#define tLcapDelta          0xA2
#define tLdelta             0xA3
#define tLepsilon           0xA4
#define tLlambda            0xA5
#define tLmu                0xA6
#define tLpi                0xA7
#define tLrho               0xA8
#define tLcapSigma          0xA9
#define tLphi               0xAB
#define tLcapOmega          0xAC
#define tLphat              0xAD
#define tLchi               0xAE
#define tLstatF             0xAF
#define tLa                 0xB0
#define tLb                 0xB1
#define tLc                 0xB2
#define tLd                 0xB3
#define tLsmalle            0xB4
#define tLf                 0xB5
#define tLsmallg            0xB6
#define tLh                 0xB7
#define tLi                 0xB8
#define tLj                 0xB9
#define tLk                 0xBA
#define tLl                 0xBC
#define tLm                 0xBD
#define tLsmalln            0xBE
#define tLo                 0xBF
#define tLp                 0xC0
#define tLq                 0xC1
#define tLsmallr            0xC2
#define tLs                 0xC3
#define tLsmallt            0xC4
#define tLu                 0xC5
#define tLv                 0xC6
#define tLw                 0xC7
#define tLx                 0xC8
#define tLy                 0xC9
#define tLz                 0xCA
#define tLsigma             0xCB
#define tLtau               0xCC
#define tLcapIAcute         0xCD
#define tGarbageCollect     0xCE

#define tExtTok             0xEF
// 2nd Byte Of tExtTok Tokens
#define tSetDate            0x00
#define tSetTime            0x01
#define tCheckTmr           0x02
#define tSetDtFmt           0x03
#define tSetTmFmt           0x04
#define tTimeCnv            0x05
#define tDayOfWk            0x06
#define tGetDtStr           0x07
#define tGetTmStr           0x08
#define tGetDate            0x09
#define tGetTime            0x0A
#define tStartTmr           0x0B
#define tGtDtFmt            0x0C
#define tGetTmFmt           0x0D
#define tIsClockOn          0x0E
#define tClockOff           0x0F
#define tClockOn            0x10
#define tOpenLib            0x11
#define tExecLib            0x12
#define tInvT               0x13
#define tChiSquaredTest     0x14
#define tLinRegTInt         0x15
#define tManualFit          0x16
#define tZQuadrant          0x17
#define tZFracHalf          0x18
#define tZFracThird         0x19
#define tZFracFourth        0x1A
#define tZFracFifth         0x1B
#define tZFracEighth        0x1C
#define tZFracTenth         0x1D
#define tFracSlash          0x2E
#define tFracMixedNum       0x2F
#define tSwapImProper       0x30
#define tSwapFracDec        0x31
#define tRemainder          0x32
#define tSummationSigma     0x33
#define tLogBase            0x34
#define tRandIntNoRep       0x35
#define tMathPrint          0x36
#define tClassic            0x38
#define tAutoAnswer         0x3B
#define tDecAnswer          0x3C
#define tFracAnswer         0x3D
#define tBlue               0x41
#define tRed                0x42
#define tBlack              0x43
#define tMagenta            0x44
#define tGreen              0x45
#define tOrange             0x46
#define tBrown              0x47
#define tNavy               0x48
#define tLtBlue             0x49
#define tYellow             0x4A
#define tWhite              0x4B
#define tLtGray             0x4C
#define tMedGray            0x4D
#define tGray               0x4E
#define tDarkGray           0x4F
#define tGraphColor         0x65
#define tTextColor          0x67
#define tBackgroundOn       0x5B
#define tBackgroundOff      0x64
#define tThin               0x74
#define tBorderColor        0x6C
#define tAsm84CPrgm         0x68
#define tAsm84CCmp          0x69
#define tAsm84CeCmp         0x7B
#define tAsm84CePrgm        0x7A

/* 2 byte extended tokens (tExtTok) present in OS 5.2 and above */
#define tSEQn               0x8F /* 'SEQ(n)'     */
#define tSEQn1              0x90 /* 'SEQ(n+1)'   */
#define tSEQn2              0x91 /* 'SEQ(n+2)'   */
#define tLEFT               0x92 /* 'LEFT'       */
#define tCENTER             0x93 /* 'CENTER'     */
#define tRIGHT              0x94 /* 'RIGHT'      */
#define tInvBinom           0x95 /* 'invBinom('  */
#define tWait               0x96 /* 'Wait_'      */
#define tToString           0x97 /* 'toString('  */
#define tEval               0x98 /* 'eval('      */

#ifdef __cplusplus
}
#endif

#endif
