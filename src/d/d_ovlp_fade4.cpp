//
// Generated by dtk
// Translation Unit: d_ovlp_fade4.cpp
//

#include "d/d_ovlp_fade4.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "f_op/f_op_overlap.h"
#include "m_Do/m_Do_graphic.h"

/* 80224390-80224484       .text init__15dDlst_2DtEff1_cF8_GXColor */
void dDlst_2DtEff1_c::init(GXColor color) {
    /* Nonmatching */
    snap_dlst.init(mDoGph_gInf_c::getFrameBufferTex(), 640, 480);
    redraw_dlst.init(mDoGph_gInf_c::getFrameBufferTimg(), 0.0f, 0.0f, 640.0f, 480.0f, g_whiteColor);
    save_dlst.init(mDoGph_gInf_c::getFrameBufferTex(), 640, 480);
    blur0_dlst.init(mDoGph_gInf_c::getFrameBufferTimg(), 0.0f, 0.0f, 640.0f, 480.0f, g_whiteColor);
    blur0Snap_dlst.init(mDoGph_gInf_c::getFrameBufferTex(), 640, 480);
    composite_dlst.init(mDoGph_gInf_c::getFrameBufferTimg(), 0.0f, 0.0f, 640.0f, 480.0f, color);
}

/* 80224484-802246CC       .text draw__15dDlst_2DtEff1_cFv */
void dDlst_2DtEff1_c::draw() {
    curWidth = 320 + (s16)(timer * 8.0f) * -16;
    curHeight = 240 + (s16)(timer * 8.0f) * -12;
    if (first) {
        snap_dlst.draw();
        redraw_dlst.draw();
        save_dlst.draw();
        blur0_dlst.draw();
        blur0Snap_dlst.draw();
        composite_dlst.draw();
        first = false;
    } else {
        if (dComIfGp_getWindowNum() == 0) {
            s32 w = 320;
            s32 h = 240;

            blur0_dlst.setImagePtr(GXGetTexObjData(mDoGph_gInf_c::getZbufferTexObj()));
            composite_dlst.setImagePtr(GXGetTexObjData(mDoGph_gInf_c::getZbufferTexObj()));

            while (true) {
                s32 dstW = w - 16;
                s32 dstH = h - 12;

                if (dstW < curWidth || dstH < curHeight)
                    break;

                blur0_dlst.setImageWidth(w / 2);
                blur0_dlst.setImageHeight(h / 2);
                blur0_dlst.setWidth(dstW);
                blur0_dlst.setHeight(dstH);
                blur0_dlst.draw();

                blur0Snap_dlst.setWd(dstW);
                blur0Snap_dlst.setHt(dstH);
                blur0Snap_dlst.draw();

                w = dstW;
                h = dstH;

                blur0_dlst.setImagePtr(mDoGph_gInf_c::getFrameBufferTex());
                composite_dlst.setImagePtr(mDoGph_gInf_c::getFrameBufferTex());
            }

            composite_dlst.setImageWidth(w / 2);
            composite_dlst.setImageHeight(h / 2);
            composite_dlst.setPos(0.0f, 0.0f);
            composite_dlst.draw();
        }
    }
}

/* 802246CC-80224748       .text draw__17dDlst_snapShot2_cFv */
void dDlst_snapShot2_c::draw() {
    GXSetCopyFilter(GX_FALSE, NULL, GX_FALSE, NULL);
    GXSetTexCopySrc(0, 0, mWidth, mHeight);
    GXSetTexCopyDst(mWidth / 2, mHeight / 2, GX_TF_RGBA8, GX_TRUE);
    GXCopyTex(mImagePtr, GX_FALSE);
    GXPixModeSync();
}

/* 80224748-80224884       .text dDlst_setResTimgObj__FPC7ResTIMGP9_GXTexObjPvUlUl */
bool dDlst_setResTimgObj(const ResTIMG* timg, GXTexObj* texObj, void* imagePtr, u32 w, u32 h) {
    if (timg->indexTexture) {
        JUT_ASSERT(0xd9, FALSE);
    } else {
        GXInitTexObj(texObj, imagePtr, w, h, (GXTexFmt)timg->format, (GXTexWrapMode)timg->wrapS, (GXTexWrapMode)timg->wrapT, (GXBool)((int)timg->mipmapCount > 1));
    }

    GXInitTexObjLOD(texObj, (GXTexFilter)timg->minFilter, (GXTexFilter)timg->magFilter,
        timg->minLOD * 0.125f, timg->maxLOD * 0.125f, timg->LODBias * 0.01f,
        (GXBool)timg->biasClamp, (GXBool)timg->doEdgeLOD,
        (GXAnisotropy)timg->maxAnisotropy);
    return true;
}

/* 80224884-802249C4       .text cnvAddress__FffPfPf */
void cnvAddress(f32 x1, f32 y1, f32* x2, f32* y2) {
    JUT_ASSERT(0x11a, x2 != NULL);
    JUT_ASSERT(0x11b, y2 != NULL);
    *x2 = 320.0f + (s32)((x1 - 320.0f) * 1.0296875f);
    *y2 = 240.0f + (s32)((y1 - 240.0f) * 1.0926074f);
}

/* 802249C4-80224CC4       .text draw__14dDlst_2Dt_Sp_cFv */
void dDlst_2Dt_Sp_c::draw() {
    dDlst_setResTimgObj(mDoGph_gInf_c::getFrameBufferTimg(), &mTexObj, mImagePtr, mImageWidth, mImageHeight);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_U8, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXLoadTexObj(&mTexObj, GX_TEXMAP0);
    GXSetNumChans(0);
    GXSetTevColor(GX_TEVREG0, mColor);
    u8 i = mPercent * 255.0f;
    GXColor tev1;
    tev1.r = i;
    tev1.g = i;
    tev1.b = i;
    GXSetTevColor(GX_TEVREG1, tev1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_C0, GX_CC_C1, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_1);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
    GXSetCullMode(GX_CULL_NONE);
    GXSetDither(GX_FALSE);
    GXSetClipMode(GX_CLIP_DISABLE);
    GXLoadPosMtxImm(mDoMtx_getIdentity(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    f32 x1, y1;
    f32 x2, y2;
    cnvAddress(mPosX, mPosY, &x1, &y1);

    // lol
    x1 = -9.0f;
    y1 = -21.0f;
    x2 = x1 + (mWidth * 1.0296875f);
    y2 = y1 + (mHeight * 1.0916667f);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2f32(x1, y1);
        GXTexCoord2u8(0, 0);

        GXPosition2f32(x2, y1);
        GXTexCoord2u8(1, 0);

        GXPosition2f32(x2, y2);
        GXTexCoord2u8(1, 1);

        GXPosition2f32(x1, y2);
        GXTexCoord2u8(0, 1);
    GXEnd();
}

/* 80224CC4-80224DBC       .text init__14dDlst_2Dt_Sp_cFP7ResTIMGffff8_GXColor */
void dDlst_2Dt_Sp_c::init(ResTIMG* timg, f32 x, f32 y, f32 w, f32 h, GXColor color) {
    setImageWidth(timg->width);
    setImageHeight(timg->height);
    mTimg = timg;
    setImagePtr((u8*)mTimg + mTimg->imageOffset);
    dDlst_setResTimgObj(mTimg, &mTexObj, mImagePtr, mImageWidth, mImageHeight);
    setPos(x, y);
    setWidth(w);
    setHeight(h);
    mColor = color;
    mPercent = 0.0f;
}

/* 80224DBC-80224F98       .text __ct__10dOvlpFd4_cFv */
dOvlpFd4_c::dOvlpFd4_c() {
    first = true;
    setExecute(&dOvlpFd4_c::execFirstSnap);
    setDraw(&dOvlpFd4_c::drawFadeOut);
    if (base.mProcName == PROC_OVERLAP4) {
        fadeOutComposite_dlst.init(mDoGph_gInf_c::getFrameBufferTimg(), 0.0f, 0.0f, 640.0f, 480.0f, g_saftyWhiteColor);
    } else {
        fadeOutComposite_dlst.init(mDoGph_gInf_c::getFrameBufferTimg(), 0.0f, 0.0f, 640.0f, 480.0f, (GXColor){ 0x00, 0x00, 0x00, 0x00 });
    }
    fadeOutBlur1_dlst.init(mDoGph_gInf_c::getFrameBufferTimg(), 0.0f, 0.0f, 640.0f, 480.0f, g_whiteColor);
    fadeOutBlur0_dlst.init(mDoGph_gInf_c::getFrameBufferTex(), 640, 480);
    fadeOutSnap_dlst.init(mDoGph_gInf_c::getFrameBufferTex(), 640, 480);
    fadeIn_dlst.init(g_saftyWhiteColor);
    dComIfGp_2dShowOff();
    timer = 2;
    totalTime = 39;
    delayPercent = 0.0f;
    fadeOutStatus = 0;
}

/* 80224F98-80225060       .text drawFadeOut__10dOvlpFd4_cFv */
void dOvlpFd4_c::drawFadeOut() {
    if (first) {
        dComIfGd_set2DXlu(&fadeOutSnap_dlst);
        first = false;
    } else if (fadeOutStatus == 1) {
        dComIfGd_set2DXlu(&fadeOutBlur1_dlst);
        dComIfGd_set2DXlu(&fadeOutBlur0_dlst);
    }
    dComIfGd_set2DXlu(&fadeOutComposite_dlst);
}

/* 80225060-8022509C       .text drawFadeIn__10dOvlpFd4_cFv */
void dOvlpFd4_c::drawFadeIn() {
    dComIfGd_set2DXlu(&fadeIn_dlst);
}

/* 8022509C-802251FC       .text execFirstSnap__10dOvlpFd4_cFv */
void dOvlpFd4_c::execFirstSnap() {
    if (!first && cLib_calcTimer(&timer) == 0) {
        setExecute(&dOvlpFd4_c::execFadeOut);
        fopOvlpM_Done(this);
        dComIfGp_setWindowNum(0);
        fadeOutStatus = 1;

        if (totalTime > 79) {
            // this path is never used
            field_0x2bc = (f32)(totalTime - 79) / 79.0f;
            sizeStep = 8;
        } else {
            f32 x = (624.0f / totalTime);
            field_0x2bc = 0.0f;
            sizeStep = (s32)(x / 16) * 16;
        }

        timer = totalTime;
        startTime = totalTime - (s32)(totalTime * delayPercent);
    }
}

/* 802251FC-802253C4       .text execFadeOut__10dOvlpFd4_cFv */
void dOvlpFd4_c::execFadeOut() {
    dComIfGp_setWindowNum(0);
    if (cLib_calcTimer(&timer) == 0 && (fadeOutBlur0_dlst.mWidth <= sizeStep || fadeOutBlur0_dlst.mHeight <= sizeStep) && fopOvlpM_IsOutReq(this)) {
        fopOvlpM_SceneIsStart();
        setExecute(&dOvlpFd4_c::execNextSnap);
        fadeOutStatus = 0;
        timer = 200;
        dComIfGp_2dShowOff();
    } else {
        u16 wd = fadeOutBlur0_dlst.getWd();
        u16 ht = fadeOutBlur0_dlst.getHt();
        fadeOutBlur1_dlst.setImageWidth(wd / 2);
        fadeOutBlur1_dlst.setImageHeight(ht / 2);

        if (wd > sizeStep && ht > sizeStep) {
            wd -= sizeStep;
            ht -= sizeStep;
        }

        f32 percent;
        if (timer > startTime) {
            percent = 0.0f;
        } else if (wd > sizeStep || ht > sizeStep) {
            percent = 1.0f - ((f32)timer / startTime);
            percent *= percent;
        } else {
            percent = 1.0f;
        }

        fadeOutComposite_dlst.setPer(percent);
        fadeOutBlur1_dlst.setWidth(wd);
        fadeOutBlur1_dlst.setHeight(ht);
        fadeOutBlur0_dlst.setWd(wd);
        fadeOutBlur0_dlst.setHt(ht);
        fadeOutComposite_dlst.setImageWidth(wd / 2);
        fadeOutComposite_dlst.setImageHeight(ht / 2);
    }
}

/* 802253C4-80225528       .text execNextSnap__10dOvlpFd4_cFv */
void dOvlpFd4_c::execNextSnap() {
    setExecute(&dOvlpFd4_c::execFadeIn);
    setDraw(&dOvlpFd4_c::drawFadeIn);
    fadeIn_dlst.first = true;
    dComIfGp_setWindowNum(1);

    fadeIn_dlst.snap_dlst.setWd(640);
    fadeIn_dlst.snap_dlst.setHt(480);
    fadeIn_dlst.redraw_dlst.setImageWidth(320);
    fadeIn_dlst.redraw_dlst.setImageHeight(240);
    fadeIn_dlst.redraw_dlst.setWidth(320);
    fadeIn_dlst.redraw_dlst.setHeight(240);

    // saves blurred frame to getZbufferTexObj after the game is finished rendering...
    fadeIn_dlst.save_dlst.init(GXGetTexObjData(mDoGph_gInf_c::getZbufferTexObj()), 320, 240);

    fadeIn_dlst.blur0_dlst.setImagePtr(GXGetTexObjData(mDoGph_gInf_c::getZbufferTexObj()));
    fadeIn_dlst.blur0_dlst.setImageWidth(160);
    fadeIn_dlst.blur0_dlst.setImageHeight(120);
    fadeIn_dlst.blur0_dlst.setWidth(16.0f);
    fadeIn_dlst.blur0_dlst.setHeight(16.0f);
    fadeIn_dlst.blur0Snap_dlst.setWd(16);
    fadeIn_dlst.blur0Snap_dlst.setHt(16);
    fadeIn_dlst.composite_dlst.setPer(1.0f);
    fadeIn_dlst.composite_dlst.setImageWidth(8);
    fadeIn_dlst.composite_dlst.setImageHeight(8);
    fadeIn_dlst.composite_dlst.setWidth(640.0f);
    fadeIn_dlst.composite_dlst.setHeight(480.0f);
    timer = totalTime;
    fadeIn_dlst.timer = 1.0f;
    timerStep = -1.0f / timer;
}

/* 80225528-802255F4       .text execFadeIn__10dOvlpFd4_cFv */
void dOvlpFd4_c::execFadeIn() {
    if (cLib_calcTimer(&timer) == 0 && fadeIn_dlst.timer <= 0.0f) {
        if (!field_0x2cc) {
            fopOvlpM_SceneIsStart();
            field_0x2cc = true;
        } else {
            fopOvlpM_Done(this);
            dComIfGp_setWindowNum(1);
            dComIfGp_2dShowOn();
        }
    } else {
        dComIfGp_setWindowNum(0);
        fopOvlpM_SceneIsStop();
        fadeIn_dlst.composite_dlst.setPer(fadeIn_dlst.timer * fadeIn_dlst.timer);
        fadeIn_dlst.timer += timerStep;
        if (fadeIn_dlst.timer < 0.0f)
            fadeIn_dlst.timer = 0.0f;
    }
}

/* 802255F4-80225658       .text dOvlpFd4_Draw__FP10dOvlpFd4_c */
BOOL dOvlpFd4_Draw(dOvlpFd4_c* i_this) {
    dOvlpFd4_c::DrawFunc func = i_this->mDrawFunc;
    if (func != NULL) {
        (i_this->*i_this->mDrawFunc)();
    }
    return TRUE;
}

/* 80225658-80225684       .text dOvlpFd4_Execute__FP10dOvlpFd4_c */
BOOL dOvlpFd4_Execute(dOvlpFd4_c* i_this) {
    (i_this->*i_this->mExecuteFunc)();
    return TRUE;
}

/* 80225684-8022568C       .text dOvlpFd4_IsDelete__FP10dOvlpFd4_c */
BOOL dOvlpFd4_IsDelete(dOvlpFd4_c*) {
    return TRUE;
}

/* 8022568C-80225694       .text dOvlpFd4_Delete__FP10dOvlpFd4_c */
BOOL dOvlpFd4_Delete(dOvlpFd4_c*) {
    return TRUE;
}

/* 80225694-802256C0       .text dOvlpFd4_Create__FPv */
s32 dOvlpFd4_Create(void* i_this) {
    new (i_this) dOvlpFd4_c();
    return cPhs_COMPLEATE_e;
}

overlap_method_class l_dOvlpFd4_Method = {
    (process_method_func)dOvlpFd4_Create,
    (process_method_func)dOvlpFd4_Delete,
    (process_method_func)dOvlpFd4_Execute,
    (process_method_func)dOvlpFd4_IsDelete,
    (process_method_func)dOvlpFd4_Draw,
};

overlap_process_profile_definition g_profile_OVERLAP4 = {
    fpcLy_ROOT_e,
    2,
    fpcPi_CURRENT_e,
    PROC_OVERLAP4,
    &g_fpcLf_Method.base,
    sizeof(dOvlpFd4_c),
    0,
    0,
    &g_fopOvlp_Method,
    0x1E5,
    &l_dOvlpFd4_Method,
};

overlap_process_profile_definition g_profile_OVERLAP5 = {
    fpcLy_ROOT_e,
    2,
    fpcPi_CURRENT_e,
    PROC_OVERLAP5,
    &g_fpcLf_Method.base,
    sizeof(dOvlpFd4_c),
    0,
    0,
    &g_fopOvlp_Method,
    0x1E6,
    &l_dOvlpFd4_Method,
};
