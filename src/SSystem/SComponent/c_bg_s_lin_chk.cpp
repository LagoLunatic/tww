//
// Generated by dtk
// Translation Unit: c_bg_s_lin_chk.cpp
//

#include "SSystem/SComponent/c_bg_s_lin_chk.h"
#include "dolphin/types.h"

/* 80247418-80247480       .text ct__11cBgS_LinChkFv */
void cBgS_LinChk::ct() {
    mLin.mStart = cXyz::Zero;
    mLin.mEnd = cXyz::Zero;
    field_0x40 = cXyz::Zero ;
    setActorPid(0xFFFFFFFF);
    field_0x4c = 0;
    mFrontFlag = 1;
    mBackFlag = 0;
}

/* 80247480-80247500       .text Set2__11cBgS_LinChkFP4cXyzP4cXyzUi */
void cBgS_LinChk::Set2(cXyz* pStart, cXyz* pEnd, unsigned int actorPid) {
    mLin.SetStartEnd(*pStart, *pEnd);
    field_0x40 = *pEnd;
    setActorPid(actorPid);
    field_0x4c &= ~0x10;
    ClearPi();
}