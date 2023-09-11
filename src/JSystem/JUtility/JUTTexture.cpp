//
// Generated by dtk
// Translation Unit: JUTTexture.cpp
//

#include "JSystem/JUtility/JUTTexture.h"
#include "JSystem/JUtility/JUTPalette.h"
#include "dolphin/gx/GX.h"
#include "dolphin/types.h"

/* 802C13FC-802C1470       .text __dt__10JUTTextureFv */
JUTTexture::~JUTTexture() {
    if (getCaptureFlag()) {
        delete[] field_0x3c;
    }
    if (getEmbPaletteDelFlag()) {
        delete mEmbPalette;
    }
}

/* 802C1470-802C15FC       .text storeTIMG__10JUTTextureFPC7ResTIMGUc */
void JUTTexture::storeTIMG(const ResTIMG* pTimg, u8 param_1) {
    _GXTlut tlut;

    if (pTimg && param_1 < 0x10) {
        mTexInfo = pTimg;
        mTexData = (void*)((int)mTexInfo + mTexInfo->imageOffset);

        if (mTexInfo->imageOffset == 0) {
            mTexData = (void*)((int)mTexInfo + 0x20);
        }

        if (getEmbPaletteDelFlag()) {
            delete mEmbPalette;
        }
        mEmbPalette = NULL;
        mAttachedPalette = NULL;
        mTlutName = 0;
        mWrapS = mTexInfo->wrapS;
        mWrapT = mTexInfo->wrapT;
        mMinFilter = mTexInfo->minFilter;
        mMagFilter = mTexInfo->magFilter;
        mMinLOD = (s8)mTexInfo->minLOD;
        mMaxLOD = (s8)mTexInfo->maxLOD;
        mLODBias = mTexInfo->LODBias;

        if (mTexInfo->numColors == 0) {
            initTexObj();
        } else {
            if (mTexInfo->numColors > 0x100) {
                tlut = (_GXTlut)((param_1 % 4) + GX_BIGTLUT0);
            } else {
                tlut = (_GXTlut)param_1;
            }

            mEmbPalette = new JUTPalette(
                tlut, (_GXTlutFmt)mTexInfo->colorFormat, (JUTTransparency)mTexInfo->alphaEnabled,
                mTexInfo->numColors, (void*)(&mTexInfo->format + mTexInfo->paletteOffset));

            mFlags = mFlags & 1 | 2;
            attachPalette(mEmbPalette);
        }
    }
}

/* 802C15FC-802C1654       .text attachPalette__10JUTTextureFP10JUTPalette */
void JUTTexture::attachPalette(JUTPalette* pPalette) {
    if (mTexInfo->indexTexture) {
        if (pPalette == NULL && mEmbPalette != NULL) {
            mAttachedPalette = mEmbPalette;
        } else {
            mAttachedPalette = pPalette;
        }
        _GXTlut name = (_GXTlut)mAttachedPalette->getTlutName();
        initTexObj(name);
    }
}

/* 802C1654-802C1740       .text initTexObj__10JUTTextureFv */
void JUTTexture::initTexObj() {
    GXBool mipmapEnabled;
    if (mTexInfo->mipmapEnabled != 0) {
        mipmapEnabled = 1;
    } else {
        mipmapEnabled = 0;
    }
    u8* image = ((u8*)mTexInfo);
    image += (mTexInfo->imageOffset ? mTexInfo->imageOffset : 0x20);
    GXInitTexObj(&mTexObj, image, mTexInfo->width, mTexInfo->height, (GXTexFmt)mTexInfo->format,
                 (GXTexWrapMode)mWrapS, (GXTexWrapMode)mWrapT, mipmapEnabled);
    GXInitTexObjLOD(&mTexObj, (GXTexFilter)mMinFilter, (GXTexFilter)mMagFilter, mMinLOD / 8.0f,
                    mMaxLOD / 8.0f, mLODBias / 100.0f, mTexInfo->biasClamp, mTexInfo->doEdgeLOD,
                    (GXAnisotropy)mTexInfo->maxAnisotropy);
}

/* 802C1740-802C183C       .text initTexObj__10JUTTextureF7_GXTlut */
void JUTTexture::initTexObj(_GXTlut tlut) {
    GXBool mipmapEnabled;
    if (mTexInfo->mipmapEnabled != 0) {
        mipmapEnabled = 1;
    } else {
        mipmapEnabled = 0;
    }
    mTlutName = tlut;
    u8* image = ((u8*)mTexInfo);
    image += (mTexInfo->imageOffset ? mTexInfo->imageOffset : 0x20);
    GXInitTexObjCI(&mTexObj, image, mTexInfo->width, mTexInfo->height, (GXCITexFmt)mTexInfo->format,
                   (GXTexWrapMode)mWrapS, (GXTexWrapMode)mWrapT, mipmapEnabled, tlut);
    GXInitTexObjLOD(&mTexObj, (GXTexFilter)mMinFilter, (GXTexFilter)mMagFilter, mMinLOD / 8.0f,
                    mMaxLOD / 8.0f, mLODBias / 100.0f, mTexInfo->biasClamp, mTexInfo->doEdgeLOD,
                    (GXAnisotropy)mTexInfo->maxAnisotropy);
}

/* 802C183C-802C188C       .text load__10JUTTextureF11_GXTexMapID */
void JUTTexture::load(_GXTexMapID id) {
    if (mAttachedPalette) {
        mAttachedPalette->load();
    }
    GXLoadTexObj(&mTexObj, id);
}
