//
// Generated by dtk
// Translation Unit: JUTFader.cpp
//

#include "JSystem/JUtility/JUTFader.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"

/* 802C8544-802C85F0       .text __ct__8JUTFaderFiiiiQ28JUtility6TColor */
JUTFader::JUTFader(int x, int y, int width, int height, JUtility::TColor pColor) : mColor(pColor), mBox(x, y, x + width, y + height) {
    mStatus = 0;
    mFadeTime = 0;
    mTimer = 0;
    mDelayStatus = 0;
    mDelayTimer = -1;
}

/* 802C85F0-802C86F0       .text control__8JUTFaderFv */
void JUTFader::control() {
    if (0 <= mDelayTimer && mDelayTimer-- == 0) {
        mStatus = mDelayStatus;
    }

    if (mStatus == WaitIn) {
        return;
    }

    switch (mStatus) {
    case WaitOut:
        mColor.a = 0xFF;
        break;
    case FadeIn:
        mColor.a = 0xFF - ((++mTimer * 0xFF) / mFadeTime);
        if (mTimer >= mFadeTime)
            mStatus = WaitIn;
        break;
    case FadeOut:
        mColor.a = ((++mTimer * 0xFF) / mFadeTime);
        if (mTimer >= mFadeTime)
            mStatus = WaitOut;
        break;
    }
    draw();
}

/* 802C86F0-802C8780       .text draw__8JUTFaderFv */
void JUTFader::draw() {
    if (mColor.a == 0) {
        return;
    }

    J2DOrthoGraph graf;
    graf.setColor(mColor);
    graf.fillBox(mBox);
}

/* 802C8780-802C87B0       .text startFadeIn__8JUTFaderFi */
bool JUTFader::startFadeIn(int fadeTime) {
    bool statusCheck = mStatus == WaitOut;

    if (statusCheck) {
        mStatus = FadeIn;
        mTimer = 0;
        mFadeTime = fadeTime;
    }

    return statusCheck;
}

/* 802C87B0-802C87E4       .text startFadeOut__8JUTFaderFi */
bool JUTFader::startFadeOut(int fadeTime) {
    bool statusCheck = mStatus == WaitIn;

    if (statusCheck) {
        mStatus = FadeOut;
        mTimer = 0;
        mFadeTime = fadeTime;
    }

    return statusCheck;
}
