//
// Generated by dtk
// Translation Unit: d_a_sea.cpp
//

#include "d/actor/d_a_sea.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_stage.h"
#include "m_Do/m_Do_lib.h"
#include "m_Do/m_Do_graphic.h"
#include "d/actor/d_a_daiocta.h"
#include "SSystem/SComponent/c_m2d_g_box.h"

// There are probably still magic numbers that depend on these,
// so it's not recommended to modify them.
#define GRID_SIZE 800
#define GRID_CELLS 65
#define GRID_INDEX(x, z) (x + GRID_CELLS * z)

daSea_packet_c l_cloth;

f32 daSea_packet_c::BASE_HEIGHT = 1.0f;

daSea_WaveInfoDat wi_prm_ocean[4] = {
    {
        2.5f,           // mHeight
        7.352941E-5f,   // mKm
        0,              // mPhase
        0.98f,          // mScaleX
        0.2f,           // mScaleZ
        200,            // mCounterMax
    },
    {
        2.5f,           // mHeight
        8.928571E-5f,   // mKm
        4000,           // mPhase
        0.2f,           // mScaleX
        0.98f,          // mScaleZ
        190,            // mCounterMax
    },
    {
        2.5f,           // mHeight
        1.13636364E-4f, // mKm
        8000,           // mPhase
        -0.98f,         // mScaleX
        0.2f,           // mScaleZ
        210,            // mCounterMax
    },
    {
        2.5f,           // mHeight
        1.5625E-4f,     // mKm
        12000,          // mPhase
        0.2f,           // mScaleX
        -0.98f,         // mScaleZ
        180,            // mCounterMax
    },
};

s8 pos_around[8][2] = {
    {-1, -1},  { 0, -1},
    { 1, -1},  { 1,  0},
    { 1,  1},  { 0,  1},
    {-1,  1},  {-1,  0},
};

extern void dKy_usonami_set(f32 param_0);

/* 8015B0A4-8015B0FC       .text Pos2Index__25daSea_WaterHeightInfo_MngFfPf */
int daSea_WaterHeightInfo_Mng::Pos2Index(f32 v, f32* dst) {
    f32 f = 450000.0f;
    int idx = (v + f) / 100000.0f;
    if (dst != NULL)
        *dst = (v + f) - idx * 100000.0f;
    return idx;
}

/* 8015B0FC-8015B164       .text GetHeight__25daSea_WaterHeightInfo_MngFff */
int daSea_WaterHeightInfo_Mng::GetHeight(f32 x, f32 z) {
    int xi = Pos2Index(x, NULL);
    int zi = Pos2Index(z, NULL);
    return GetHeight(xi, zi);
}

/* 8015B164-8015B1E8       .text get_wave_max__Fi */
int get_wave_max(int roomNo) {
    dStage_Multi_c * multi = dComIfGp_getStage().getMulti();
    if (multi == NULL)
        return 10;

    dStage_Mult_info* entry = multi->m_entries;
    for (int i = 0; i < multi->num; i++, entry++)
        if (roomNo == entry->mRoomNo)
            return entry->mWaveMax;

    return 10;
}

/* 8015B1E8-8015B288       .text GetHeight__25daSea_WaterHeightInfo_MngFii */
int daSea_WaterHeightInfo_Mng::GetHeight(int x, int z) {
    if (x < 0 || (s32)ARRAY_SIZE(mHeight[0]) <= x || z < 0 || (s32)ARRAY_SIZE(mHeight) <= z)
        return 10;

    if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_SEA_e) {
        return mHeight[z][x];
    } else {
        return get_wave_max(dComIfGp_roomControl_getStayNo());
    }
}

/* 8015B288-8015B2D0       .text calcMinMax__FiPfPf */
void calcMinMax(int v, f32* min, f32* max) {
    *min = v * 100000.0f - 450000.0f;
    *max = *min + 100000.0f;
}

/* 8015B2D0-8015B328       .text GetArea__25daSea_WaterHeightInfo_MngFiiPfPfPfPf */
void daSea_WaterHeightInfo_Mng::GetArea(int x, int z, f32* minX, f32* minZ, f32* maxX, f32* maxZ) {
    calcMinMax(x, minX, maxX);
    calcMinMax(z, minZ, maxZ);
}

/* 8015B328-8015B3FC       .text SetInf__25daSea_WaterHeightInfo_MngFv */
void daSea_WaterHeightInfo_Mng::SetInf() {
    dStage_Multi_c * multi = dComIfGp_getStage().getMulti();

    for (s32 i = 0; i < (s32)ARRAY_SIZE(mHeight); i++)
        for (s32 j = 0; j < (s32)ARRAY_SIZE(mHeight[0]); j++)
            mHeight[i][j] = 10;

    if (multi != NULL) {
        s32 roomNo = 1;
        for (s32 i = 1; i < (s32)ARRAY_SIZE(mHeight) - 1; i++) {
            for (s32 j = 1; j < (s32)ARRAY_SIZE(mHeight[0]) - 1; j++) {
                mHeight[i][j] = get_wave_max(roomNo);
                roomNo++;
            }
        }
    }
}

/* 8015B3FC-8015B43C       .text __ct__14daSea_WaveInfoFv */
daSea_WaveInfo::daSea_WaveInfo() {
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mCounters); i++) {
        m04[i] = 0.0f;
        mCounters[i] = 0;
    }
    mCurScale = 1.0f;
}

/* 8015B43C-8015B484       .text __dt__14daSea_WaveInfoFv */
daSea_WaveInfo::~daSea_WaveInfo() {}

/* 8015B484-8015B4D4       .text AddCounter__14daSea_WaveInfoFv */
void daSea_WaveInfo::AddCounter() {
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mCounters); i++) {
        mCounters[i]++;
        if (mCounters[i] >= mWaveInfoTable[i].mCounterMax)
            mCounters[i] = 0;
    }
}

/* 8015B4D4-8015B530       .text GetRatio__14daSea_WaveInfoFi */
f32 daSea_WaveInfo::GetRatio(int idx) {
    return (f32)mCounters[idx] / (f32)mWaveInfoTable[idx].mCounterMax;
}

/* 8015B530-8015B54C       .text GetKm__14daSea_WaveInfoFi */
f32 daSea_WaveInfo::GetKm(int idx) {
    return mWaveInfoTable[idx].mKm * 6.28f;
}

/* 8015B54C-8015B56C       .text GetScale__14daSea_WaveInfoFf */
f32 daSea_WaveInfo::GetScale(f32 v) {
    mCurScale += (v - mCurScale) / 100.0f;
    return mCurScale;
}

/* 8015B56C-8015B7A0       .text create__14daSea_packet_cFR4cXyz */
bool daSea_packet_c::create(cXyz& pos) {
    BASE_HEIGHT = 1.0f;
    BASE_HEIGHT = pos.y + 1.0f;

    mFlatInter = 0.0f;
    mpHeightTable = new f32[GRID_CELLS * GRID_CELLS];
    if (mpHeightTable == NULL)
        return false;

    mWaterHeightMgr.SetInf();
    mWaveInfo.SetDat(wi_prm_ocean);
    CleanUp();
    mInitFlag = true;
    mRoomNo = -1;
    mFlags = 0;
    mAnimCounter = 0;

    ResTIMG* timg = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_B_SEA_TEX0AND2);
    
    GXBool mipmap = timg->mipmapCount > 1;
    GXInitTexObj(&mTexSea0, (char*)timg + timg->imageOffset, timg->width, timg->height,
        (GXTexFmt)timg->format, (GXTexWrapMode)timg->wrapS, (GXTexWrapMode)timg->wrapT,
        mipmap);
    GXInitTexObjLOD(&mTexSea0, (GXTexFilter)timg->minFilter, (GXTexFilter)timg->magFilter,
        timg->minLOD * 0.125f, timg->maxLOD * 0.125f, -0.9f,
        (GXBool)timg->biasClamp, (GXBool)timg->doEdgeLOD,
        (GXAnisotropy)timg->maxAnisotropy);

    mipmap = timg->mipmapCount > 1;
    GXInitTexObj(&mTexSea1, (char*)timg + timg->imageOffset, timg->width, timg->height,
        (GXTexFmt)timg->format, (GXTexWrapMode)timg->wrapS, (GXTexWrapMode)timg->wrapT,
        mipmap);
    GXInitTexObjLOD(&mTexSea1, (GXTexFilter)timg->minFilter, (GXTexFilter)timg->magFilter,
        timg->minLOD * 0.125f, timg->maxLOD * 0.125f, 1.0f,
        (GXBool)timg->biasClamp, (GXBool)timg->doEdgeLOD,
        (GXAnisotropy)timg->maxAnisotropy);

    timg = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_B_WYURAYURA_TEX1);
    mDoLib_setResTimgObj(timg, &mTexYura, 0, NULL);

    return true;
}

/* 8015B7A0-8015B7E4       .text CleanUp__14daSea_packet_cFv */
void daSea_packet_c::CleanUp() {
    s32 idx = 0;
    for (s32 z = 0; z < GRID_CELLS; z++)
        for (s32 x = 0; x < GRID_CELLS; x++)
            mpHeightTable[idx++] = BASE_HEIGHT;
    mCurPos.zero();
}

/* 8015B7E4-8015B84C       .text __ct__14daSea_packet_cFv */
daSea_packet_c::daSea_packet_c() {}

/* 8015B84C-8015B86C       .text SetFlat__14daSea_packet_cFv */
void daSea_packet_c::SetFlat() {
    mFlags |= 0x01;
    mFlatTarget = 0.0f;
    mFlatInterCounter = 150.0f;
}

/* 8015B86C-8015B884       .text ClrFlat__14daSea_packet_cFv */
void daSea_packet_c::ClrFlat() {
    mFlags &= ~0x01;
    mFlatInterCounter = 150.0f;
}

/* 8015B884-8015BA18       .text CalcFlatInterTarget__14daSea_packet_cFR4cXyz */
f32 daSea_packet_c::CalcFlatInterTarget(cXyz& pos) {
    cM2dGBox box;
    cXy xzPos;
    xzPos.x = pos.x;
    xzPos.y = pos.z;

    if (mWaterHeightMgr.GetHeight(mIdxX, mIdxZ) == 0) {
        return 0.0f;
    }

    f32 result = 1.0f;

    for (int i = 0; i < (int)ARRAY_SIZE(pos_around); i++) {
        int ix = mIdxX + pos_around[i][0];
        int iz = mIdxZ + pos_around[i][1];

        if (mWaterHeightMgr.GetHeight(ix, iz) == 0) {
            cXy min;
            cXy max;

            mWaterHeightMgr.GetArea(ix, iz, &min.x, &min.y, &max.x, &max.y);

            // 12800 = GRID_SIZE * 16?
            min.x -= 12800.0f;
            min.y -= 12800.0f;
            max.x += 12800.0f;
            max.y += 12800.0f;

            box.Set(min, max);

            f32 len = box.GetLen(xzPos);

            if (len > 12800.0f) {
                len = 12800.0f;
            }

            len /= 12800.0f;
            if (result > len) {
                result = len;
            }
        }
    }

    return result;
}

/* 8015BA18-8015BAD8       .text CalcFlatInter__14daSea_packet_cFv */
void daSea_packet_c::CalcFlatInter() {
    if (mFlags & 1) {
        if (mFlatInterCounter != 0.0f) {
            mFlatInter = mFlatInter + (mFlatTarget - mFlatInter) / mFlatInterCounter;
            mFlatInterCounter--;
        } else {
            mFlatInter = mFlatTarget;
        }
    } else {
        f32 target = CalcFlatInterTarget(mPlayerPos);
        if (mFlatInterCounter != 0.0f) {
            mFlatInter = mFlatInter + (target - mFlatInter) / mFlatInterCounter;
            mFlatInterCounter--;
        } else {
            mFlatInter = target;
        }
    }
}

/* 8015BAD8-8015BAF8       .text daSea_Init__Fv */
void daSea_Init() {
    l_cloth.mInitFlag = false;
    l_cloth.mCullStopFlag = true;
    l_cloth.m13A = true;
}

/* 8015BAF8-8015BB60       .text daSea_ChkAreaBeforePos__Fff */
bool daSea_ChkAreaBeforePos(f32 x, f32 z) {
    if (l_cloth.mInitFlag == 0) {
        return false;
    }

    if (l_cloth.mWaterHeightMgr.GetHeight(x, z) == 0 && l_cloth.mCullStopFlag != 0) {
        return false;
    }

    return true;
}

/* 8015BB60-8015BBFC       .text daSea_ChkArea__Fff */
bool daSea_ChkArea(f32 x, f32 z) {
    if (!daSea_ChkAreaBeforePos(x, z)) {
        return false;
    }

    if (l_cloth.getMinX() < x && x < l_cloth.getMaxX() && l_cloth.getMinZ() < z && z < l_cloth.getMaxZ()) {
        return true;
    }

    return false;
}

// Fakematch
#pragma opt_dead_assignments off
/* 8015BBFC-8015BDB0       .text daSea_calcWave__Fff */
f32 daSea_calcWave(f32 x, f32 z) {
    if (!daSea_ChkArea(x, z)) {
        return daSea_packet_c::BASE_HEIGHT;
    }

    f32 frac = 1.0f / GRID_SIZE;

    int x0 = (x - l_cloth.getMinX()) * frac;
    int z0 = (z - l_cloth.getMinZ()) * frac;

    f32* pY = l_cloth.mpHeightTable;
    pY += x0;
    pY += z0 * GRID_CELLS;

    //f32 minX = (x0 * 800) + l_cloth.getMinX();
    //f32 maxX = minX + 800.0f;
    //f32 minZ = (z0 * 800) + l_cloth.getMinZ();
    //f32 maxZ = minZ + 800.0f;
    
    Vec v00, v01, v10, v11;

    v00.x = (x0 * GRID_SIZE) + l_cloth.getMinX();
    v00.y = pY[GRID_INDEX(0, 0)];
    v00.z = (z0 * GRID_SIZE) + l_cloth.getMinZ();

    v01.x = (x0 * GRID_SIZE) + l_cloth.getMinX();
    v01.y = pY[GRID_INDEX(0, 1)];
    v01.z = v00.z + GRID_SIZE;

    v10.x = v01.x + GRID_SIZE;
    v10.y = pY[GRID_INDEX(1, 0)];
    v10.z = (z0 * GRID_SIZE) + l_cloth.getMinZ();

    v11.x = v10.x;
    v11.y = pY[GRID_INDEX(1, 1)];
    v11.z = v01.z;

    Vec norm;
    f32 baseY;

    f32 f0, f1;
    f1 = x - v01.x;
    f0 = z - v10.z;
    f1 *= frac;
    f0 *= frac;

    if (f1 + f0 >= 1.0f) {
        cM3d_CalcPla(&v01, &v10, &v11, &norm, &baseY);
    } else {
        cM3d_CalcPla(&v00, &v01, &v10, &norm, &baseY);
    }

    return -((norm.x * x) + (norm.z * z) + baseY) / norm.y;
}

#pragma opt_dead_assignments reset

/* 8015BDB0-8015C010       .text daSea_GetPoly__FPvPFPvR4cXyzR4cXyzR4cXyz_vRC4cXyzRC4cXyz */
void daSea_GetPoly(void* pUserData, void (*callback)(void*, cXyz&, cXyz&, cXyz&), const cXyz& minPt, const cXyz& maxPt) {
    if (!daSea_ChkArea(minPt.x, minPt.z) || !daSea_ChkArea(maxPt.x, maxPt.z)) return;

    f32 frac = 1.0f / GRID_SIZE;
    int x0 = (minPt.x - l_cloth.getMinX()) * frac;
    int z0 = (minPt.z - l_cloth.getMinZ()) * frac;
    int x1 = (maxPt.x - l_cloth.getMinX()) * frac;
    int z1 = (maxPt.z - l_cloth.getMinZ()) * frac;

    if (!(x0 >= 0 && x0 <= GRID_CELLS - 2 && z0 >= 0 && z0 <= GRID_CELLS - 2 && x1 >= 0 && x1 <= GRID_CELLS - 2 && z1 >= 0 && z1 <= GRID_CELLS - 2)) {
        return;
    }

    for (int z = z0; z < z1 + 1; z++) {
        for (int x = x0; x < x1 + 1; x++) {
            f32* pY = l_cloth.mpHeightTable;
            pY += x;
            pY += z * GRID_CELLS;
            cXyz v00, v01, v10, v11;

            v00.x = (x * GRID_SIZE) + l_cloth.getMinX();
            v00.y = pY[GRID_INDEX(0, 0)];
            v00.z = (z * GRID_SIZE) + l_cloth.getMinZ();

            v01.x = v00.x;
            v01.y = pY[GRID_INDEX(0, 1)];
            v01.z = v00.z + GRID_SIZE;

            v10.x = v00.x + GRID_SIZE;
            v10.y = pY[GRID_INDEX(1, 0)];
            v10.z = v00.z;

            v11.x = v10.x;
            v11.y = pY[GRID_INDEX(1, 1)];
            v11.z = v01.z;

            callback(pUserData, v00, v01, v11);
            callback(pUserData, v00, v11, v10);
        }
    }
}

/* 8015C010-8015C11C       .text SetCullStopFlag__14daSea_packet_cFv */
void daSea_packet_c::SetCullStopFlag() {
    if (strcmp(dComIfGp_getStartStageName(), "A_umikz") == 0) {
        mCullStopFlag = false;
        return;
    }

    if (mWaterHeightMgr.GetHeight(mIdxX, mIdxZ) != 0) {
        mCullStopFlag = false;
        return;
    }

    f32 minX, minZ, maxX, maxZ;
    mWaterHeightMgr.GetArea(mIdxX, mIdxZ, &minX, &minZ, &maxX, &maxZ);

    // 25600 = GRID_SIZE * 32?
    minX += 25600.0f;
    minZ += 25600.0f;
    maxX -= 25600.0f;
    maxZ -= 25600.0f;

    if ((minX < mPlayerPos.x) && (mPlayerPos.x < maxX) && (minZ < mPlayerPos.z) && (mPlayerPos.z < maxZ)) {
        mCullStopFlag = true;
        return;
    }

    mCullStopFlag = false;
}

/* 8015C11C-8015C1DC       .text CheckRoomChange__14daSea_packet_cFv */
void daSea_packet_c::CheckRoomChange() {
    dStage_roomDt_c * room = dComIfGp_roomControl_getStatusRoomDt(dComIfGp_roomControl_getStayNo());
    if (room != NULL) {
        mRoomNo = dComIfGp_roomControl_getStayNo();
        u32 procName = PROC_DAIOCTA;
        daDaiocta_c* octa = (daDaiocta_c *)fopAcM_SearchByName(PROC_DAIOCTA);
        if (octa == NULL) {
            if (mFlags & 0x01) {
                ClrFlat();
            }
        } else {
            if (!dComIfGs_isSwitch(octa->getSw(), fopAcM_GetHomeRoomNo(octa))) {
                SetFlat();
            } else {
                ClrFlat();
            }
        }
    }
}

/* 8015C1DC-8015C214       .text daSea_execute__FR4cXyz */
void daSea_execute(cXyz& pos) {
    if (l_cloth.mInitFlag)
        l_cloth.execute(pos);
}

/* 8015C214-8015C75C       .text execute__14daSea_packet_cFR4cXyz */
void daSea_packet_c::execute(cXyz& pos) {
    mPlayerPos = pos;
    mIdxX = mWaterHeightMgr.Pos2Index(mPlayerPos.x, NULL);
    mIdxZ = mWaterHeightMgr.Pos2Index(mPlayerPos.z, NULL);

    if (strcmp(dComIfGp_getStartStageName(), "ADMumi") == 0) {
        mFlatInter = 0.0f;
    }

    if (mRoomNo != dComIfGp_roomControl_getStayNo() && dComIfGp_roomControl_getStayNo() != 0) {
        CheckRoomChange();
    }

    CalcFlatInter();
    dKy_usonami_set(mFlatInter);
    // 25600 = GRID_SIZE * 32?
    mDrawMinX = pos.x - 25600.0f;
    mDrawMaxX = pos.x + 25600.0f;
    mDrawMinZ = pos.z - 25600.0f;
    mDrawMaxZ = pos.z + 25600.0f;
    SetCullStopFlag();

    if (mCullStopFlag == 1) {
        return;
    }

    int h = mWaterHeightMgr.GetHeight(pos.x, pos.z);

    f32 scale = mFlatInter * mWaveInfo.GetScale(h);

    // Vectorization?
    s16 aOffsAnimTable [4];
    f32 aThetaXTable [4];
    f32 aThetaZTable [4];
    f32 aHeightTable [4];

    for (int i = 0; i < 4; i++) {
        aThetaXTable[i] = mWaveInfo.GetKm(i) * mWaveInfo.GetVx(i);
        aThetaZTable[i] = mWaveInfo.GetKm(i) * mWaveInfo.GetVz(i);

        aOffsAnimTable[i] = 65536.0f * (mWaveInfo.GetRatio(i) - 0.5f);
        aHeightTable[i] = mWaveInfo.GetBaseHeight(i) * scale;
    }

    scale = mDrawMinZ + GRID_SIZE;

    // Unrolled loops?

    s16 theta[4];
    // Split up to prevent integer promotion
    theta[0] = cM_rad2s(aThetaZTable[0] * scale);
    theta[1] = cM_rad2s(aThetaZTable[1] * scale);
    theta[2] = cM_rad2s(aThetaZTable[2] * scale);
    theta[3] = cM_rad2s(aThetaZTable[3] * scale);

    theta[0] -= aOffsAnimTable[0];
    theta[1] -= aOffsAnimTable[1];
    theta[2] -= aOffsAnimTable[2];
    theta[3] -= aOffsAnimTable[3];

    theta[0] += mWaveInfo.GetPhai(0);
    theta[1] += mWaveInfo.GetPhai(1);
    theta[2] += mWaveInfo.GetPhai(2);
    theta[3] += mWaveInfo.GetPhai(3);

    s16 waveTheta_DeltaZ[4];
    waveTheta_DeltaZ[0] = cM_rad2s(aThetaZTable[0] * GRID_SIZE);
    waveTheta_DeltaZ[1] = cM_rad2s(aThetaZTable[1] * GRID_SIZE);
    waveTheta_DeltaZ[2] = cM_rad2s(aThetaZTable[2] * GRID_SIZE);
    waveTheta_DeltaZ[3] = cM_rad2s(aThetaZTable[3] * GRID_SIZE);

    s16 waveTheta_DeltaX[4];
    waveTheta_DeltaX[0] = cM_rad2s(aThetaXTable[0] * GRID_SIZE);
    waveTheta_DeltaX[1] = cM_rad2s(aThetaXTable[1] * GRID_SIZE);
    waveTheta_DeltaX[2] = cM_rad2s(aThetaXTable[2] * GRID_SIZE);
    waveTheta_DeltaX[3] = cM_rad2s(aThetaXTable[3] * GRID_SIZE);

    scale = mDrawMinX + GRID_SIZE;

    s16 waveTheta_Phase[4];
    waveTheta_Phase[0] = cM_rad2s(aThetaXTable[0] * scale);
    waveTheta_Phase[1] = cM_rad2s(aThetaXTable[1] * scale);
    waveTheta_Phase[2] = cM_rad2s(aThetaXTable[2] * scale);
    waveTheta_Phase[3] = cM_rad2s(aThetaXTable[3] * scale);

    f32 aFadeTable [GRID_CELLS];

    for (int fadeZ = 0; fadeZ < GRID_CELLS; fadeZ++) {
        aFadeTable[fadeZ] = 1.0f;
    }

    // Probably unrolled loop
    f32 frac = 1.0f / 6;
    aFadeTable[GRID_CELLS - 1] = frac * 0;
    aFadeTable[0]  = frac * 0;
    aFadeTable[GRID_CELLS - 2] = frac * 1;
    aFadeTable[1]  = frac * 1;
    aFadeTable[GRID_CELLS - 3] = frac * 2;
    aFadeTable[2]  = frac * 2;
    aFadeTable[GRID_CELLS - 4] = frac * 3;
    aFadeTable[3]  = frac * 3;
    aFadeTable[GRID_CELLS - 5] = frac * 4;
    aFadeTable[4]  = frac * 4;
    aFadeTable[GRID_CELLS - 6] = frac * 5;
    aFadeTable[5]  = frac * 5;

    for (int z = 1; z < GRID_CELLS - 1; z++) {
        f32* pHeight = mpHeightTable + GRID_CELLS * z + 1;
        s16 waveTheta0 = waveTheta_Phase[0];
        waveTheta0 += theta[0];
        s16 waveTheta1 = waveTheta_Phase[1];
        waveTheta1 += theta[1];
        s16 waveTheta2 = waveTheta_Phase[2];
        waveTheta2 += theta[2];
        s16 waveTheta3 = waveTheta_Phase[3];
        waveTheta3 += theta[3];

        for (int x = 1; x < GRID_CELLS - 1; x++) {
            *pHeight = aHeightTable[0] * cM_scos(waveTheta0)
                     + aHeightTable[1] * cM_scos(waveTheta1)
                     + aHeightTable[2] * cM_scos(waveTheta2)
                     + aHeightTable[3] * cM_scos(waveTheta3)
                     + BASE_HEIGHT;

            *pHeight *= aFadeTable[z] * aFadeTable[x];
            waveTheta0 += waveTheta_DeltaX[0];
            waveTheta1 += waveTheta_DeltaX[1];
            waveTheta2 += waveTheta_DeltaX[2];
            waveTheta3 += waveTheta_DeltaX[3];

            pHeight++;
        }

        theta[0] += waveTheta_DeltaZ[0];
        theta[1] += waveTheta_DeltaZ[1];
        theta[2] += waveTheta_DeltaZ[2];
        theta[3] += waveTheta_DeltaZ[3];
    }

    mWaveInfo.AddCounter();
    mCurPos = pos;
}

/* 8015C75C-8015D80C       .text draw__14daSea_packet_cFv */
void daSea_packet_c::draw() {
    if (ChkCullStop()) return;

    m_draw_vtx = (cXyz*)mDoGph_gInf_c::alloc(sizeof(cXyz) * GRID_CELLS * GRID_CELLS, 0x20);
    if (m_draw_vtx == NULL) {
        return;
    }

    JUT_ASSERT(VERSION_SELECT(0x519, 0x518, 0x518), m_draw_vtx != NULL); // Redundant assert

#if VERSION != VERSION_JPN
    j3dSys.reinitGX();
#endif

    cXyz* vtx = m_draw_vtx;
    f32* pY = mpHeightTable;

    f32 minZ = getMinZ();
    for (int z = 0; z < GRID_CELLS; z++) {
        f32 minX = getMinX();
        for (int x = 0; x < GRID_CELLS; x++) {
            (*vtx).x = minX;
            (*vtx).y = *pY;
            (*vtx).z = minZ;
            minX += GRID_SIZE;
            vtx++;
            pY++;
        }

        minZ += GRID_SIZE;
    }

#if VERSION == VERSION_JPN
    DCFlushRange(m_draw_vtx, sizeof(cXyz) * GRID_CELLS * GRID_CELLS);
#else
    DCStoreRange(m_draw_vtx, sizeof(cXyz) * GRID_CELLS * GRID_CELLS);
#endif

    ResTIMG* pResTIMG = static_cast<ResTIMG*>(dComIfG_getObjectRes("Always", ALWAYS_BTI_B_SEA_TEX0AND2));

    GXBool mipmap = pResTIMG->mipmapCount > 1;
    GXInitTexObj(&mTexSea0, (&pResTIMG->format + pResTIMG->imageOffset), pResTIMG->width, pResTIMG->height,
                (GXTexFmt)pResTIMG->format, (GXTexWrapMode)pResTIMG->wrapS, (GXTexWrapMode)pResTIMG->wrapT,
                mipmap);

    GXInitTexObjLOD(&mTexSea0, (GXTexFilter)pResTIMG->minFilter, (GXTexFilter)pResTIMG->magFilter,
                    pResTIMG->minLOD * 0.125f, pResTIMG->maxLOD * 0.125f, -0.9f,
                    (GXBool)pResTIMG->biasClamp, (GXBool)pResTIMG->doEdgeLOD,
                    (GXAnisotropy)pResTIMG->maxAnisotropy);

    mipmap = pResTIMG->mipmapCount > 1;
    GXInitTexObj(&mTexSea1, (&pResTIMG->format + pResTIMG->imageOffset), pResTIMG->width, pResTIMG->height,
                (GXTexFmt)pResTIMG->format, (GXTexWrapMode)pResTIMG->wrapS, (GXTexWrapMode)pResTIMG->wrapT,
                mipmap);

    GXInitTexObjLOD(&mTexSea1, (GXTexFilter)pResTIMG->minFilter, (GXTexFilter)pResTIMG->magFilter,
                    pResTIMG->minLOD * 0.125f, pResTIMG->maxLOD * 0.125f, 1.0f,
                    (GXBool)pResTIMG->biasClamp, (GXBool)pResTIMG->doEdgeLOD,
                    (GXAnisotropy)pResTIMG->maxAnisotropy);

    pResTIMG = static_cast<ResTIMG*>(dComIfG_getObjectRes("Always", ALWAYS_BTI_B_WYURAYURA_TEX1));
    mDoLib_setResTimgObj(pResTIMG, &mTexYura, 0, NULL);
    mDoMtx_stack_c::scaleS(1.5f, 1.5f, 1.0f);
    GXLoadTexMtxImm(mDoMtx_stack_c::get(), GX_TEXMTX0, GX_MTX2x4);
    GXLoadTexObj(&mTexSea0, GX_TEXMAP0);

    mAnimCounter += 1;

    if (mAnimCounter > 300) {
        mAnimCounter = 0;
    }

    mDoMtx_stack_c::transS(0.0f, mAnimCounter / 300.0f, 0.0f);
    GXLoadTexMtxImm(mDoMtx_stack_c::get(), GX_TEXMTX1, GX_MTX2x4);
    GXLoadTexObj(&mTexYura, GX_TEXMAP1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);

    static f32 offset[6];

    offset[0] = 0.3f;
    offset[1] = 0.0f;
    offset[2] = 0.0f;
    offset[3] = 0.0f;
    offset[4] = 0.3f;
    offset[5] = 0.0f;

    GXSetIndTexMtx(GX_ITM_0, (f32*) offset, -1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetTevIndWarp(GX_TEVSTAGE1, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    mDoMtx_stack_c::transS(0.2f, -0.2f, 0.0f);
    GXLoadTexMtxImm(mDoMtx_stack_c::get(), GX_TEXMTX2, GX_MTX2x4);
    GXLoadTexObj(&mTexSea1, GX_TEXMAP2);
    
    GXColor colorAmb, colorDif;
    dKy_get_seacolor(&colorAmb, &colorDif);

    f32 tmp = mFlatInter * mFlatInter;

    GXColor color1;
    color1.r = colorDif.r + tmp * ((f32)colorAmb.r - (f32)colorDif.r);
    color1.g = colorDif.g + tmp * ((f32)colorAmb.g - (f32)colorDif.g);
    color1.b = colorDif.b + tmp * ((f32)colorAmb.b - (f32)colorDif.b);
    color1.a = 0xFF;

    f32 f = 1.0f / 10;

    f32 r;
    f32 g;
    f32 b;
    f32 tmp_2;
    tmp_2 = 1.0f - f * tmp;

    r = colorDif.r * tmp_2;
    g = colorDif.g * tmp_2;
    b = colorDif.b * tmp_2;

    if (r > 255.0f) {
        r = 255.0f;
    }

    if (g > 255.0f) {
        g = 255.0f;
    }

    if (b > 255.0f) {
        b = 255.0f;
    }

    GXColor color2;// = {(u8) r, (u8) g, (u8) b};
    color2.r = r;
    color2.g = g;
    color2.b = b;
    color2.a = 0xFF;

    GXSetTevColor(GX_TEVREG0, colorDif);
    GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
    GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K1);

    GXSetTevKColor(GX_KCOLOR0, color1);
    GXSetTevKColor(GX_KCOLOR1, color2);

    GXSetNumIndStages(1);
    GXSetNumChans(0);
    GXSetNumTexGens(3);
    GXSetNumTevStages(3);
    GXSetCullMode(GX_CULL_BACK);
    GXSetCoPlanar(GX_FALSE);

    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1);
    GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX2);

    GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP0, VERSION_SELECT(GX_COLOR_ZERO, GX_COLOR_NULL, GX_COLOR_NULL));
    GXSetTevColorIn(GX_TEVSTAGE0,GX_CC_C0,GX_CC_KONST,GX_CC_TEXC,GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVREG2);
    GXSetTevAlphaIn(GX_TEVSTAGE0,GX_CA_ZERO,GX_CA_KONST,GX_CA_TEXA,GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
    GXSetTevSwapMode(GX_TEVSTAGE0,GX_TEV_SWAP0,GX_TEV_SWAP0);
    GXSetTevOrder(GX_TEVSTAGE1,GX_TEXCOORD2,GX_TEXMAP2, VERSION_SELECT(GX_COLOR_ZERO, GX_COLOR_NULL, GX_COLOR_NULL));
    GXSetTevColorIn(GX_TEVSTAGE1,GX_CC_C0,GX_CC_KONST,GX_CC_TEXC,GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1,GX_CA_APREV,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
    GXSetTevSwapMode(GX_TEVSTAGE1,GX_TEV_SWAP0,GX_TEV_SWAP0);
    GXSetTevOrder(GX_TEVSTAGE2,GX_TEXCOORD_NULL,GX_TEXMAP_NULL, VERSION_SELECT(GX_COLOR_ZERO, GX_COLOR_NULL, GX_COLOR_NULL));
    GXSetTevColorIn(GX_TEVSTAGE2,GX_CC_CPREV,GX_CC_C2,GX_CC_APREV,GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE2,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2,GX_CA_ZERO,GX_CA_KONST,GX_CA_APREV,GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
    GXSetTevSwapMode(GX_TEVSTAGE2,GX_TEV_SWAP0,GX_TEV_SWAP0);
    GXSetAlphaCompare(GX_ALWAYS,0,GX_AOP_OR,GX_ALWAYS,0);
    GXSetZCompLoc(GX_TRUE);
    GXSetPixelFmt(GX_PF_RGBA6_Z24,GX_ZC_LINEAR);
    GXSetZMode(true,GX_LEQUAL,true);
    GXSetBlendMode(GX_BM_NONE,GX_BL_ZERO,GX_BL_ZERO,GX_LO_CLEAR);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetDither(GX_TRUE);

    dKy_GxFog_sea_set();

    GXLoadPosMtxImm(j3dSys.getViewMtx(), 0);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS,GX_INDEX16);
    GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_CLR_RGBA,GX_F32,0);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_CLR_RGBA,GX_F32,0);
    GXSetArray(GX_VA_POS, this->m_draw_vtx, sizeof(cXyz));

    // TODO: Remove magic numbers

    // 1.0f / 2000
    f32 frac = 0.0005000001f;   // Fakematch

    cXyz* pVtx;
    u16 idx2;
    int z;
    u16 idx1;
    idx1 = 0;
    idx2 = GRID_CELLS;

    pVtx = m_draw_vtx;

    f32 prevTexZ;
    f32 texZ = frac * (*pVtx).z;
    for (z = 0; z < GRID_CELLS - 1; z++) {
        prevTexZ = texZ;
        texZ = frac * ((*pVtx).z + GRID_SIZE);

        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, GRID_CELLS * 2);

        for (int x = 0; x < GRID_CELLS; x++) {
            f32 texX = frac * (*pVtx).x;
            GXPosition1x16(idx2);
            GXTexCoord2f32(texX, texZ);
            GXPosition1x16(idx1);
            GXTexCoord2f32(texX, prevTexZ);
            idx1++;
            idx2++;

            pVtx++;
        };

        GXEnd();
    }

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    f32 dVar14;

    f32 posZ;
    if (getMinZ() > -450000.0f) {
        int end = (getMinZ() - (-450000.0f)) / 225000.0f;
        posZ = -450000.0f;
        texZ = posZ * frac;

        for (int z = 0; z < end; z++) {
            prevTexZ = texZ;
            dVar14 = 225000.0f + posZ;
            texZ = frac * dVar14;

            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 10);
            f32 texX;
            f32 posX = -450000.0f;
            for (int x = 0; x < 5; x++) {
                texX = frac * posX;
                GXPosition3f32(posX, BASE_HEIGHT, dVar14);
                GXTexCoord2f32(texX, texZ);

                GXPosition3f32(posX, BASE_HEIGHT, posZ);
                GXTexCoord2f32(texX, prevTexZ);

                posX += 225000.0f;
            }

            GXEnd();

            posZ += 225000.0f;
        }

        if (posZ < getMinZ()) {
            prevTexZ = texZ;
            texZ = getMinZ() * frac;
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 10);
            f32 texX;
            f32 posX = -450000.0f;
            for (int i = 0; i < 5; i++) {
                texX = frac * posX;
                GXPosition3f32(posX, BASE_HEIGHT, getMinZ());
                GXTexCoord2f32(texX, texZ);
                GXPosition3f32(posX, BASE_HEIGHT, posZ);
                GXTexCoord2f32(texX, prevTexZ);

                posX += 225000.0f;
            }

            GXEnd();
        }
    }

    if (getMaxZ() < 450000.0f) {
        posZ = getMaxZ();
        int i;
        int end = (450000.0f - getMaxZ()) / 225000.0f;
        texZ = frac * posZ;

        for (i = 0; i < end; i++) {
            prevTexZ = texZ;
            f32 f30 = posZ + 225000.0f;
            texZ = frac * f30;
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 10);
            f32 texX;
            f32 posX = -450000.0f;
            for (int x = 0; x < 5; x++) {
                texX = frac * posX;
                GXPosition3f32(posX, BASE_HEIGHT, f30);
                GXTexCoord2f32(texX, texZ);

                GXPosition3f32(posX, BASE_HEIGHT, posZ);
                GXTexCoord2f32(texX, prevTexZ);

                posX += 225000.0f;
            }

            GXEnd();

            posZ += 225000.0f;
        }

        if (posZ < 450000.0f) {
            prevTexZ = texZ;
            texZ = 450000.0f * frac;
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 10);
            f32 texX;
            f32 posX = -450000.0f;
            for (int x = 0; x < 5; x++) {
                texX = frac * posX;
                GXPosition3f32(posX, BASE_HEIGHT, 450000.0f);
                GXTexCoord2f32(texX, texZ);
                GXPosition3f32(posX, BASE_HEIGHT, posZ);
                GXTexCoord2f32(texX, prevTexZ);

                posX += 225000.0f;
            }

            GXEnd();
        }
    }

    if (getMaxZ() > getMinZ()) {
        int temp_r26;
        int end = (getMaxZ() - getMinZ()) / 225000.0f;
        posZ = getMinZ();
        if (getMinX() > -450000.0f) {
            f32 temp_f3 = getMinX() - (-450000.0f);
            temp_r26 = temp_f3 / 225000.0f;

            // Check if value gets truncated?
            int trunc = 225000.0f * temp_r26 < temp_f3 ? 1 : 0;

            texZ = frac * posZ;
            int z = 0;

            // Might be equivalent to ceil(temp_f3 / 225000.0f)
            int count = temp_r26 + trunc;

            for (; z < end; z++) {
                prevTexZ = texZ;
                texZ = frac * 450000.0f;
                GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (1+count) * 2);

                f32 texX;
                f32 posX = -450000.0f;

                for (int x = 0; x <= temp_r26; x++) {
                    texX = frac * posX;

                    GXPosition3f32(posX, BASE_HEIGHT, posZ + 225000.0f);
                    GXTexCoord2f32(texX, frac * 450000.0f);
                    GXPosition3f32(posX, BASE_HEIGHT, posZ);
                    GXTexCoord2f32(texX, prevTexZ);
                    posX += 225000.0f;
                }

                if (trunc) {
                    texX = frac * getMinX();
                    GXPosition3f32(getMinX(), BASE_HEIGHT, posZ + 225000.0f);
                    GXTexCoord2f32(texX, frac * 450000.0f);
                    GXPosition3f32(getMinX(), BASE_HEIGHT, posZ);
                    GXTexCoord2f32(texX, prevTexZ);
                }

                GXEnd();

                posZ += 225000.0f;
            }

            if (posZ < getMaxZ()) {
                prevTexZ = texZ;
                texZ = frac * getMaxZ();
                GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (1+count) * 2);

                f32 texX;
                f32 posX = -450000.0f;
                for (int x = 0; x <= temp_r26; x++) {
                    texX = frac * posX;
                    GXPosition3f32(posX, BASE_HEIGHT, getMaxZ());
                    GXTexCoord2f32(texX, texZ);
                    GXPosition3f32(posX, BASE_HEIGHT, posZ);
                    GXTexCoord2f32(texX, prevTexZ);
                    posX += 225000.0f;
                }

                if (trunc != 0) {
                    texX = frac * getMinX();
                    GXPosition3f32(getMinX(), BASE_HEIGHT, getMaxZ());
                    GXTexCoord2f32(texX, texZ);
                    GXPosition3f32(getMinX(), BASE_HEIGHT, posZ);
                    GXTexCoord2f32(texX, prevTexZ);
                }

                GXEnd();
            }
        }

        if (getMaxX() < 450000.0f) {
            int z;
            f32 temp_f3_3 = 450000.0f - getMaxX();
            int temp_r26_2 = temp_f3_3 / 225000.0f;

            // Check if value gets truncated?
            int trunc = 225000.0f * temp_r26_2 < temp_f3_3 ? 1 : 0;

            posZ = getMinZ();
            texZ = frac * posZ;
            z = 0;

            // Might be equivalent to ceil(temp_3_3 / 225000.0f)
            int count = temp_r26_2 + trunc;

            for (; z < end; z++) {

                GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (1+count) * 2);

                f32 texX;
                f32 posX = getMaxX();
                for (int x = 0; x <= temp_r26_2; x++) {
                    texX = frac * posX;
                    GXPosition3f32(posX, BASE_HEIGHT, posZ + 225000.0f);
                    GXTexCoord2f32(texX, texZ);
                    GXPosition3f32(posX, BASE_HEIGHT, posZ);
                    GXTexCoord2f32(texX, prevTexZ);

                    posX += 225000.0f;
                }

                if (trunc != 0) {
                    GXPosition3f32(450000.0f, BASE_HEIGHT, posZ + 225000.0f);
                    GXTexCoord2f32(frac * 450000.0f, texZ);
                    GXPosition3f32(450000.0f, BASE_HEIGHT, posZ);
                    GXTexCoord2f32(frac * 450000.0f, prevTexZ);
                }

                GXEnd();

                posZ += 225000.0f;
            }

            if (posZ < getMaxZ()) {
                prevTexZ = texZ;
                texZ = frac * getMaxZ();

                GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (1+count) * 2);

                f32 texX;
                f32 posX = getMaxX();

                for (int x = 0; x <= temp_r26_2; x++) {
                    texX = frac * posX;
                    GXPosition3f32(posX, BASE_HEIGHT, getMaxZ());
                    GXTexCoord2f32(texX, texZ);
                    GXPosition3f32(posX, BASE_HEIGHT, posZ);
                    GXTexCoord2f32(texX, prevTexZ);

                    posX += 225000.0f;
                }

                if (trunc != 0) {
                    texX = 450000.0f * frac;
                    GXPosition3f32(450000.0f, BASE_HEIGHT, getMaxZ());
                    GXTexCoord2f32(texX, texZ);
                    GXPosition3f32(450000.0f, BASE_HEIGHT, posZ);
                    GXTexCoord2f32(texX, prevTexZ);
                }

                GXEnd();
            }
        }
    }

    GXSetNumIndStages(0);
#if VERSION != VERSION_JPN
    J3DShape::resetVcdVatCache();
#endif
}

/* 8015D80C-8015D87C       .text daSea_Draw__FP9sea_class */
static BOOL daSea_Draw(sea_class* i_this) {
    dComIfGd_setListSky();
    j3dSys.getDrawBuffer(1)->entryImm(&l_cloth, 31);
    dComIfGd_setList();
    return TRUE;
}

/* 8015D87C-8015D8D0       .text daSea_Execute__FP9sea_class */
static BOOL daSea_Execute(sea_class* i_this) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz pos = player->current.pos;
    l_cloth.execute(pos);
    return TRUE;
}

/* 8015D8D0-8015D8E8       .text daSea_IsDelete__FP9sea_class */
static BOOL daSea_IsDelete(sea_class*) {
    l_cloth.mInitFlag = false;
    return TRUE;
}

/* 8015D8E8-8015D8F0       .text daSea_Delete__FP9sea_class */
static BOOL daSea_Delete(sea_class*) {
    return TRUE;
}

/* 8015D8F0-8015D924       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return l_cloth.create(i_this->current.pos);
}

/* 8015D924-8015D99C       .text daSea_Create__FP10fopAc_ac_c */
static s32 daSea_Create(fopAc_ac_c* i_this) {
    fopAcM_SetupActor(i_this, sea_class);
    if (!fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0xA000))
        return cPhs_ERROR_e;
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daSea_Method = {
    (process_method_func)daSea_Create,
    (process_method_func)daSea_Delete,
    (process_method_func)daSea_Execute,
    (process_method_func)daSea_IsDelete,
    (process_method_func)daSea_Draw,
};

actor_process_profile_definition g_profile_SEA = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SEA,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sea_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x009A,
    /* Actor SubMtd */ &l_daSea_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
