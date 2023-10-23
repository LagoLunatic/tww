//
// Generated by dtk
// Translation Unit: d_a_bomb.cpp
//

#include "d/actor/d_a_bomb.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/actor/d_a_player_link.h"
#include "d/d_kankyo_wether.h"
#include "f_op/f_op_camera_mng.h"
#include "f_op/f_op_kankyo_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_lib.h"

namespace {
    enum AttrSt_e {
        ATTR_STATE_0 = 0x00,
        ATTR_STATE_1 = 0x01,
        ATTR_STATE_2 = 0x02,
        ATTR_STATE_4 = 0x04,
        ATTR_STATE_8 = 0x08,
        ATTR_STATE_10 = 0x10,
        ATTR_STATE_20 = 0x20,
        ATTR_STATE_80 = 0x80,
        ATTR_STATE_100 = 0x100,
        ATTR_STATE_200 = 0x200,

        ATTR_STATE_1C = ATTR_STATE_10 | ATTR_STATE_8 | ATTR_STATE_4,
        ATTR_STATE_21 = ATTR_STATE_20 | ATTR_STATE_1,
        ATTR_STATE_9C = ATTR_STATE_80 | ATTR_STATE_10 | ATTR_STATE_8 | ATTR_STATE_4,
        ATTR_STATE_A1 = ATTR_STATE_80 | ATTR_STATE_20 | ATTR_STATE_1,
        ATTR_STATE_20C = ATTR_STATE_200 | ATTR_STATE_8 | ATTR_STATE_4,
        ATTR_STATE_300 = ATTR_STATE_200 | ATTR_STATE_100
    };

    //game has this with global visibility somehow
    const AttrSt_e L_attrState[] = {
        ATTR_STATE_A1,
        ATTR_STATE_1C,
        ATTR_STATE_9C,
        ATTR_STATE_9C,
        ATTR_STATE_20C,
        ATTR_STATE_300,
        ATTR_STATE_200,
        ATTR_STATE_2,
        ATTR_STATE_21,
        ATTR_STATE_0
    };
    
    bool chk_attrState(const daBomb_c* i_this, AttrSt_e mask) {
        return cLib_checkBit(L_attrState[i_this->prm_get_state()], mask); // register order is wrong in the and
    }
}

const daBomb_c::AttrType daBomb_c::m_attrType[] = {
    {"Link", 0x8E0},
    {"VbakH", 0x800},
    {"Link", 0x8E0},
};

void daBomb_fuseSmokeEcallBack::executeAfter(JPABaseEmitter* emitter) {
    cXyz pos = *mpPos;
    emitter->mGlobalTranslation.set(pos.x, pos.y, pos.z);
    f32 temp = mpPos->abs(*field_0x0C);
    s16 temp2 = (20.0f - temp) * 0.5f + 10.0f;
    if(temp2 < 10) {
        temp2 = 10;
    }

    //probably uses cubic<f>__Q29JGeometry8TVec3<f>FRCQ29JGeometry8TVec3<f>RCQ29JGeometry8TVec3<f>RCQ29JGeometry8TVec3<f>RCQ29JGeometry8TVec3<f>f
    //but I don't know exactly what that would encompass
    emitter->mLifeTime = temp2;
    cXyz temp3 = *field_0x0C - *mpPos;
    cXyz temp4((field_0x0C->x - field_0x10->x) * 0.5f, (field_0x0C->y - field_0x10->y) * 0.5f, (field_0x0C->z - field_0x10->z) * 0.5f);
    f32 temp5 = mpPos->abs(*field_0x0C);

    //this is minimally-fixed ghidra stuff, no idea if its functionality is even similar
    if(temp5 * 0.1f < 1.0f) {
        f32 temp6 = 1.0f / (temp5 * 0.1f);
        s32 temp7 = temp6;
        s32 temp8 = temp2 + temp7;

        f32 step = temp6;
        for(; temp6 < 1.0f; temp6 += step) {
            cXyz temp9;
            temp9.x = temp6 * temp6;
            temp9.y = temp9.x * temp6;
            temp9.z = 1.0f + (2.0f * temp9.y - 3.0f * temp9.x);
            cXyz temp10;
            temp10.x = -2.0f * temp9.y + 3.0f * temp9.x;
            temp10.y = temp6 + (temp9.y - 2.0f * temp9.x);
            temp10.z = temp9.y - temp9.x;
            cXyz temp11;
            temp11.x = temp10.z * temp3.x * 0.5f + temp10.y * temp4.x + temp9.z * field_0x0C->x + temp10.x * mpPos->x;
            temp11.y = temp10.z * temp3.y * 0.5f + temp10.y * temp4.y + temp9.z * field_0x0C->y + temp10.x * mpPos->y;
            temp11.z = temp10.z * temp3.z * 0.5f + temp10.y * temp4.z + temp9.z * field_0x0C->z + temp10.x * mpPos->z;
            
            emitter->mLifeTime = temp8;
            JPABaseParticle* particle = emitter->createParticle();
            if(particle) {
                particle->mGlobalPosition = temp11;
            }

            temp8 += temp7;
        }
    }

    field_0x04 = temp2;
}

void daBomb_fuseSparksEcallBack::execute(JPABaseEmitter* emitter) {
    f32 x = mpPos->x;
    f32 y = mpPos->y;
    f32 z = mpPos->z;
    emitter->mGlobalTranslation.set(x, y, z);
    
    JSUPtrLink* link = emitter->mActiveParticles.getFirstLink();
    while(link != 0) {
        JSUPtrLink* next = link->getNext();

        JPABaseParticle* ptcl = (JPABaseParticle*)link->getObjectPtr();
        ptcl->mGlobalPosition.set(x, y, z);

        link = next;
    }
}

void daBomb_c::draw_norm() {
    J3DAnmTevRegKey* bombBrk = daPy_getPlayerLinkActorClass()->getBombBrk();
    s16 end = bombBrk->getFrameMax();
    f32 frame = end - mRestTime + 2;
    if(frame < 0.0f) {
        frame = 0.0f;
    }
    else if(frame >= end) {
        frame = end - 0.001f;
    }
    bombBrk->setFrame(frame);

    end = mBck0.getBckAnm()->getFrameMax();
    frame = end - mRestTime;
    if(frame < 0.0f) {
        frame = 0.0f;
    }
    else if(frame >= end) {
        frame = end - 0.001f;
    }

    mBck0.entry(mpModel->getModelData(), frame);
    dComIfGd_setListP1();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
}

void daBomb_c::draw_nut() {
    //entry calls are loading params in the wrong order
    if(chk_state(STATE_5) || chk_state(STATE_6)) {
        mBck0.entry(mpModel->getModelData(), mBck0.getFrame());
        mBrk0.entry(mpModel->getModelData(), mBrk0.getFrame());
    }
    else {
        mBck1.entry(mpModel->getModelData(), mBck1.getFrame());
        mBrk1.entry(mpModel->getModelData(), mBrk1.getFrame());
    }

    dComIfGd_setListP1();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
}

BOOL daBomb_c::draw() {
    if(chk_attrState(this, ATTR_STATE_20)) {
        return true;
    }
    if(chk_state(STATE_4) && field_0x77D == 1) {
        return true;
    }

    if(mDoLib_clipper::clip(j3dSys.getViewMtx(), current.pos, 80.0f)) {
        return true;
    }
    if(field_0x7C8 > 0) {
        return true;
    }
    
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &mTevStr);
    g_env_light.setLightTevColorType(mpModel, &mTevStr);

    if(mType == 1) {
        draw_nut();
    }
    else {
        draw_norm();
    }

    if(fopAcM_GetModel(this) == 0 && mAcch.GetGroundH() != -1.0e9f) {
        cM3dGPla* pNormal = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd.GetBgIndex(), mAcch.m_gnd.GetPolyIndex());
        if(pNormal) {
            dComIfGd_setSimpleShadow(&current.pos, mAcch.GetGroundH(), 25.0f, &pNormal->mNormal, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
        }
    }

    return true;
}

BOOL daBomb_Draw(daBomb_c* i_this) {
    return i_this->draw();
}

bool daBomb_c::checkExplodeCc_norm() {
    bool explode = false;

    if(mSph.ChkTgHit()) {
        cCcD_Obj* obj = mSph.GetTgHitObj();
        if(obj) {
            if(obj->ChkAtType(AT_TYPE_BOMB)) {
                explode = true;
            }
            else if(!obj->ChkAtType(AT_TYPE_LEAF_WIND)) {
                explode = true;
            }
        }

        mSph.ClrTgHit();
    }

    if(explode) {
        explode = procExplode_init();
    }
    else {
        explode = false;
    }

    return explode;
}

bool daBomb_c::checkExplodeCc_nut() {
    bool explode = false;
    bool hit = false;

    if(mSph.ChkTgHit()) {
        cCcD_Obj* obj = mSph.GetTgHitObj();
        if(obj) {
            if(obj->ChkAtType(AT_TYPE_BOMB)) {
                explode = true;
            }
            else if(!obj->ChkAtType(AT_TYPE_LEAF_WIND)) {
                hit = true;
            }
        }

        mSph.ClrTgHit();
    }

    if(mSph.ChkCoHit()) {
        if(field_0x780) {
            hit = true;
        }

        mSph.ClrCoHit();
    }

    bool ret = false;
    if(explode) {
        ret = procExplode_init();
    }
    else if(hit) {
        change_state(STATE_1);
        setFuseEffect();
        if(30 < mRestTime) {
            mRestTime = 30;
            mBck1.setFrame(105.0f);
            mBrk1.setFrame(105.0f);
        }
    }

    return ret;
}

bool daBomb_c::checkExplodeCc_cannon() {
    bool explode = false;

    if(mSph.ChkTgHit()) {
        cCcD_Obj* obj = mSph.GetTgHitObj();
        if(obj) {
            if(!obj->ChkAtType(AT_TYPE_LEAF_WIND)) {
                explode = true;
            }
        }

        mSph.ClrTgHit();
    }

    if(mSph.ChkCoHit()) {
        explode = true;
        mSph.ClrCoHit();
    }

    if(explode) {
        explode = procExplode_init();
    }
    else {
        explode = false;
    }

    return explode;
}

bool daBomb_c::checkExplodeCc() {
    if(0 < mRestTime) {
        typedef bool(daBomb_c::*checkFunc)();
        static checkFunc proc[] = {
            &checkExplodeCc_norm,
            &checkExplodeCc_nut,
            &checkExplodeCc_cannon
        };

        return (this->*proc[mType])();
    }

    return false;
}

bool daBomb_c::checkExplodeTimer() {
    bool explode = false;
    if(!chk_attrState(this, ATTR_STATE_200)) {
        if(0 < mRestTime) {
            if(--mRestTime == 0) {
                explode = procExplode_init();
            }
        }
    }

    return explode;
}

bool daBomb_c::checkExplode() {
    return checkExplodeCc() || checkExplodeTimer();
}

bool daBomb_c::checkExplodeBg_norm() {
    bool sink = chk_water_sink();
    bool land = chk_water_land();
    bool burn = chk_lava_hit();

    if(sink) {
        field_0x781 = true;
    }
    if(land) {
        eff_water_splash();
    }
    if(burn) {
        return procExplode_init();
    }

    return false;
}

bool daBomb_c::checkExplodeBg_nut() {
    bool sink = chk_water_in();
    bool burn = chk_lava_hit();

    //these 2 ifs might be an inline?
    bool temp1 = true;
    bool temp2 = false;
    if(mAcch.ChkWallHit() || mAcch.ChkGroundHit()) {
        temp2 = true;
    }

    if(!temp2 && !mAcch.ChkRoofHit()) {
        temp1 = false;
    }

    bool ret = false;
    if(burn) {
        ret = procExplode_init();
    }
    else {
        if(sink) {
            makeWaterEffect();
            field_0x781 = true;
        }
        else if(temp1 && field_0x780) {
            change_state(STATE_1);
            setFuseEffect();
            if(30 < mRestTime) {
                mRestTime = 30;
                mBck1.setFrame(105.0f);
                mBrk1.setFrame(105.0f);
            }
        }
    }

    return ret;
}

bool daBomb_c::checkExplodeBg_cannon() {
    bool sink = chk_water_in();
    bool burn = chk_lava_hit();

    //these 2 ifs might be an inline?
    bool temp1 = true;
    bool temp2 = false;
    if(mAcch.ChkWallHit() || mAcch.ChkGroundHit()) {
        temp2 = true;
    }
    if(!temp2 && !mAcch.ChkRoofHit()) {
        temp1 = false;
    }

    bool dead = chk_dead_zone();
    bool ret = false;
    if(burn || temp1) {
        ret = procExplode_init();
    }
    else {
        if(sink) {
            makeWaterEffect();
            field_0x781 = true;
        }
        else if(dead) {
            field_0x781 = true;
        }
    }
    
    return ret;
}

bool daBomb_c::checkExplodeBg() {
    typedef bool(daBomb_c::*checkFunc)();
    static checkFunc proc[] = {
        &checkExplodeBg_norm,
        &checkExplodeBg_nut,
        &checkExplodeBg_cannon
    };

    return (this->*proc[mType])();
}

void daBomb_c::water_tention() {
    if(chk_water_in()) {
        if(field_0x554.y != -1.0e9f && field_0x554.z != -1.0e9f) {
            f32 temp;
            if(field_0x554.y - field_0x554.z < 0) {
                temp = 0.8f * field_0x554.z;
            } 
            else {
                temp = 0.2f * field_0x554.z;
            }

            current.pos.y += temp;
        }
    }
}

void daBomb_c::posMoveF() {
    u32 temp = mNoGravityTime > 0;
    f32 gravity;
    if(temp) {
        gravity = mGravity;
        mGravity = 0.0f;
    }

    if(mType == 0 && chk_water_in()) {
        speed.y *= 0.9f;
        speedF *= 0.9f;
    }

    if(!chk_state(STATE_5) && !chk_state(STATE_6) && field_0x6F3 != 1) {
        water_tention();
        cM3dGPla* tri = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd.GetBgIndex(), mAcch.m_gnd.GetPolyIndex());

        f32 mag = mWindVec.getSquareMag();
        if(mag > 0.01f) {
            f32 temp2;
            cXyz* norm;
            if(tri) {
                norm = &tri->mNormal;
                mag = 0.06f;
                temp2 = cM_scos(0xA4F);
            }
            else {
                norm = 0;
                mag = 0.0f;
                temp2 = 0.0f;
            }

            daObj::posMoveF_grade(this, mStts.GetCCMoveP(), &mWindVec, 0.002f, 0.0005f, norm, mag, temp2, 0);
        }
        else {
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
    }
    
    if(temp) {
        mGravity = gravity;
        mNoGravityTime--;
    }
}

void daBomb_c::bgCrrPos() {
    mAcch.CrrPos(*dComIfG_Bgsp());
    bgCrrPos_lava();
    bgCrrPos_water();
    setRoomInfo();
}

void daBomb_c::bgCrrPos_lava() {
    cXyz temp(current.pos.x, next.pos.y + 1.0f, current.pos.z);
    mGndChk.SetPos(&temp);

    field_0x554.x = dComIfG_Bgsp()->GroundCross(&mGndChk);
}

/* 800DA5E0-800DA700       .text bgCrrPos_water__8daBomb_cFv */
void daBomb_c::bgCrrPos_water() {
    /* Nonmatching */
}

bool daBomb_c::chk_water_land() {
    return field_0x560;
}

bool daBomb_c::chk_water_in() {
    return mbWaterIn;
}

bool daBomb_c::chk_water_sink() {
    bool water = chk_water_in();

    return water && field_0x554.y - current.pos.y > 30.0f;
}

bool daBomb_c::chk_lava_hit() {
    if(field_0x554.x == -1.0e9f) {
        return false;
    }

    return current.pos.y < field_0x554.x;
}

bool daBomb_c::chk_dead_zone() {
    return mAcch.GetGroundH() == -1.0e9f && field_0x554.y == -1.0e9f && field_0x554.x == -1.0e9f;
}

void daBomb_c::bound(f32 param_1) {
    if(mAcch.ChkWallHit()) {
        speedF *= 0.8f;
        current.angle.y = (mCir.GetWallAngleY() * 2) - (current.angle.y - 0x8000); //+ 0x10000 - 0x8000 generates the addis but seems fake
    }

    if(mAcch.ChkGroundLanding()) {
        daObj::make_land_effect(this, &mAcch.m_gnd, 0.6f);
        param_1 *= -0.6f;
        if(param_1 < 19.5f) {
            field_0x780 = 0;
        }
        else {
            speedF *= 0.9f;
            if(param_1 > 13.0f) {
                speed.y = 13.0f;
            }
            else {
                speed.y = param_1;
            }
        }
    }
    else {
        if(mAcch.ChkGroundHit()) {
            cLib_addCalc(&speedF, 0.0f, 0.5f, 5.5f, 1.0f);
        }
    }
}

/* 800DA8C8-800DA9DC       .text set_real_shadow_flag__8daBomb_cFv */
void daBomb_c::set_real_shadow_flag() {
    /* Nonmatching */
}

void daBomb_c::setRoomInfo() {
    s32 roomNo;
    if(mAcch.GetGroundH() != -1.0e9f) {
        roomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
        mTevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
    }
    else {
        roomNo = dComIfGp_roomControl_getStayNo();
    }

    mTevStr.mRoomNo = roomNo;
    mStts.SetRoomId(roomNo);
    current.roomNo = roomNo;
}

void daBomb_c::makeFireEffect(cXyz& pos, csXyz& rotation) {
    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));

    cXyz scale;
    scale.setall(0.3f);
    csXyz rot;
    rot.x = -cam->mAngle.x;
    rot.y = cam->mAngle.y + 0x8000;
    rot.z = 0;

    rotation.x = rotation.x + 0x4000;
    rotation.z = rotation.z;
    g_dComIfG_gameInfo.play.getParticle()->setBombSmoke(0x200A, &pos, &rotation, &scale, 0xFF);

    dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
}

void daBomb_c::makeWaterEffect() {
    if(field_0x77D == 0) {
        fopAcM_seStart(this, JA_SE_OBJ_BOMB_WATER, 0);
        fopKyM_createWpillar(&current.pos, 1.0f, 1.0f, 1);
        mSph.GetObjTg().OffSPrmBit(cCcD_ObjCommonBase::CO_SPRM_SET);
        mSph.GetObjCo().OffSPrmBit(cCcD_ObjCommonBase::CO_SPRM_SET);
        mSph.GetObjAt().OnSPrmBit(cCcD_ObjCommonBase::CO_SPRM_SET);
        mSph.SetR(200.0f);
        mSph.SetC(current.pos);
        if(mMassCounter != g_Counter.mCounter0) {
            dComIfG_Ccsp()->Set(&mSph);
            //using inline breaks match
            //dComIfG_Ccsp()->SetMass(&mSph, 3);
            g_dComIfG_gameInfo.play.mCcS.SetMass(&mSph, 3);
            mMassCounter = g_Counter.mCounter0;
            field_0x782 = 1;
        }

        field_0x77D = 1;
    }
}

void daBomb_c::setFuseEffect() {
    if(field_0x77E == 0) {
        field_0x77E = 1;
        mFusePos.x = current.pos.x;
        mFusePos.y = current.pos.y + 60.0f;
        mFusePos.z = current.pos.z;
        mFusePos2 = mFusePos;
        mFusePos3 = mFusePos;

        dComIfGp_particle_setP1(0x11, &mFusePos, 0, &mScale, 0xFF, &mSparks, -1, 0, 0, 0);
        dComIfGp_particle_setToonP1(0x2012, &mFusePos, 0, &mScale, 0xDC, &mSmoke, -1, 0, 0, 0);
        mSmoke.field_0x0C = &mFusePos2;
        mSmoke.field_0x10 = &mFusePos3;
        mSmoke.field_0x04 = 0x14;
    }
}

void daBomb_c::eff_explode_normal(const csXyz* rotation) {
    dComIfGp_particle_setP1(0xB, &current.pos, rotation, &mScale, 0xFF, 0, -1, 0, 0, 0);
    g_dComIfG_gameInfo.play.getParticle()->setBombSmoke(0x2009, &current.pos, 0, &mScale, 0xFF);
    g_dComIfG_gameInfo.play.getParticle()->setBombSmoke(0x200A, &current.pos, 0, &mScale, 0xFF);
    dComIfGp_particle_setToonP1(0x2008, &current.pos, 0, &mScale, 0xFF, 0, -1, 0, 0, 0);
}

void daBomb_c::eff_explode_cheap(const csXyz* rotation) {
    JPABaseEmitter* emitter = dComIfGp_particle_setP1(0xB, &current.pos, rotation, &mScale, 0xFF, 0, -1, 0, 0, 0);
    if(emitter) {
        emitter->mLifeTime = 0xC;
        JGeometry::TVec3<f32> vec(0.5f, 0.67f, 1.0f);
        emitter->setGlobalParticleScale(vec);
    }

    g_dComIfG_gameInfo.play.getParticle()->setBombSmoke(0x232A, &current.pos, 0, &mScale, 0xFF);
    emitter = g_dComIfG_gameInfo.play.getParticle()->setBombSmoke(0x200A, &current.pos, 0, &mScale, 0xFF);
    if(emitter) {
        emitter->mLifeTime = 0x46;
    }
    
    emitter = dComIfGp_particle_setToonP1(0x2008, &current.pos, 0, &mScale, 0xFF, 0, -1, 0, 0, 0);
    if(emitter) {
        emitter->mLifeTime = 0x46;
        emitter->mInitialVelAxis = 25.0f;
        emitter->mInitialVelDir = 35.0f;
    }
}

void daBomb_c::eff_explode() {
    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    csXyz rot;
    rot.x = -cam->mAngle.x;
    rot.y = cam->mAngle.y + 0x8000;
    rot.z = 0;

    if(prm_get_cheapEff()) {
        eff_explode_cheap(&rot);
    }
    else {
        eff_explode_normal(&rot);
    }
}

int daBomb_c::procExplode_init() {
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.ForceLockOff(fopAcM_GetID(this));

    s32 temp;
    if(chk_state(STATE_8)) {
        f32 temp2;
        temp = fopAcM_getWaterY(&current.pos, &temp2);
        if(temp) {
            cXyz temp3;
            dBgS_ObjGndChk gndCheck;
            temp3.set(current.pos.x, current.pos.y + 1.0f, current.pos.z);
            gndCheck.SetPos(&temp3);

            if(dComIfG_Bgsp()->GroundCross(&gndCheck) > temp2 || current.pos.y > temp2 + 50.0f) {
                temp = 0;
            }
        }
    }
    else {
        temp = 0;
    }

    if(temp == 0) {
        eff_explode();
    }
    else {
        fopKyM_createWpillar(&current.pos, 1.0f, 1.0f, 1);
    }

    if(mSmoke.mpEmitter) {
        mSmoke.mpEmitter->mpEmitterCallBack = 0;
        mSmoke.mpEmitter->becomeInvalidEmitter();
    }
    mSmoke.mpEmitter = 0;

    if(mSparks.mpEmitter) {
        mSparks.mpEmitter->mpEmitterCallBack = 0;
        mSparks.mpEmitter->becomeInvalidEmitter();
    }
    mSparks.mpEmitter = 0;

    mPntLight.mPos = current.pos;
    mPntLight.mPos.y += 100.0f;
    mPntLight.mColor.r = 200;
    mPntLight.mColor.g = 200;
    mPntLight.mColor.b = 160;
    mPntLight.mPower = 600.0f;
    mPntLight.mFluctuation = 100.0f;
    dKy_efplight_set(&mPntLight);

    mPntWind.mPos = current.pos;
    mPntWind.mDir.x = 0.0f;
    mPntWind.mDir.y = 1.0f;
    mPntWind.mDir.z = 0.0f;
    mPntWind.mRadius = 500.0f;
    mPntWind.field_0x20 = 0.0f;
    mPntWind.mStrength = 0.5f;
    dKyw_pntwind_set(&mPntWind);

    field_0x774 = 0;
    field_0x778 = 0.0f;
    mFunc = &procExplode;
    speedF = 0.0f;
    speed = cXyz::Zero;
    mGravity = 0.0f;

    if(chk_state(STATE_8)) {
        change_state(STATE_0);
    }

    mAttentionInfo.mFlags &= ~fopAc_Attn_ACTION_CARRY_e;

    if(field_0x6F0) {
        if(daPy_getPlayerLinkActorClass()->mActivePlayerBombs != 0) {
            daPy_getPlayerLinkActorClass()->mActivePlayerBombs -= 1;
        }

        field_0x6F0 = 0;
    }

    mSph.GetObjTg().OffSPrmBit(cCcD_ObjCommonBase::CO_SPRM_SET);
    mSph.GetObjCo().OffSPrmBit(cCcD_ObjCommonBase::CO_SPRM_SET);
    mSph.GetObjAt().OnSPrmBit(cCcD_ObjCommonBase::CO_SPRM_SET);
    mSph.SetR(200.0f);
    mSph.SetC(current.pos);
    if(mMassCounter != g_Counter.mCounter0) {
        dComIfG_Ccsp()->Set(&mSph);
        //using inline breaks match
        //dComIfG_Ccsp()->SetMass(&mSph, 3);
        g_dComIfG_gameInfo.play.mCcS.SetMass(&mSph, 3);
        field_0x782 = 1;
        mMassCounter = g_Counter.mCounter0;
    }

    if(temp) {
        fopAcM_seStart(this, JA_SE_OBJ_BOMB_WATER, 0);
    }
    else {
        fopAcM_seStart(this, JA_SE_OBJ_BOMB_EXPLODE, 0);
    }

    fopAcM_cancelCarryNow(this);
    dKy_Sound_set(current.pos, 0xFF, fopAcM_GetID(this), 0xA);

    mRestTime = 0;
    field_0x6FE = 2;
    dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));

    se_cannon_fly_stop();

    return true;
}

/* 800DB630-800DB880       .text procExplode__8daBomb_cFv */
bool daBomb_c::procExplode() {
    camera_class* camera = dComIfGp_getCamera(0);
    f32 temp2 = 0.0f;

    mPntLight.mPower = field_0x778 * 1500.0f;
    mPntWind.mStrength = field_0x778;
    f32 temp = current.pos.abs(camera->mLookat.mEye);

    if(temp < 1500.0f) {
        temp2 = 1.0f - (temp / 1500.0f);
    }

    dKy_actor_addcol_amb_set(200, 180, 100, field_0x778 * temp2);
    dKy_bg_addcol_amb_set(180, 160, 60, field_0x778 * temp2);
    dKy_bg_addcol_dif_set(255, 225, 120, field_0x778 * temp2);

    switch(field_0x774) {
    case 0:
        cLib_addCalc(&field_0x778, 0.0f, 0.05f, 0.04f, 0.001f);
        if(field_0x778 >= 0.01f) {
            field_0x774 += 1;
        }

        break;
    case 1:
        cLib_addCalc(&field_0x778, 0.0f, 0.05f, 0.04f, 0.01f);
        if(field_0x778 <= 0.99f) {
            field_0x774 += 1;
        }

        break;
    }

    if(field_0x6FE) {
        field_0x6FE -= 1;
        mSph.SetC(current.pos);
        if(mMassCounter != g_Counter.mCounter0) {
            dComIfG_Ccsp()->Set(&mSph);
            //using inline breaks match
            //dComIfG_Ccsp()->SetMass(&mSph, 3);
            g_dComIfG_gameInfo.play.mCcS.SetMass(&mSph, 3);
            mMassCounter = g_Counter.mCounter0;
            field_0x782 = 1;
        }
    }
    else {
        if(1 < field_0x774) {
            field_0x781 = 1;
        }
    }

    return true;
}

bool daBomb_c::procCarry_init() {
    if(chk_attrState(this, ATTR_STATE_100)) {
        setFuseEffect();
    }

    mFunc = &procCarry;
    change_state(STATE_2);
    speedF = 0.0f;
    speed.set(cXyz::Zero);
    mAttentionInfo.mFlags &= ~fopAc_Attn_ACTION_CARRY_e;
    mSph.GetObjCo().OffSPrmBit(cCcD_ObjCommonBase::CO_SPRM_SET);

    return true;
}

bool daBomb_c::procCarry() {
    if(!fopAcM_checkCarryNow(this)) {
        if(speedF > 0.0f) {
            field_0x780 = 1;
        }

        procWait_init();
        return procWait();
    }
    else {
        if(checkExplode()) {
            return true;
        }
        else {
            cXyz curPos(current.pos);
            bgCrrPos();
            current.pos.set(curPos);

            return true;
        }
    }
}

bool daBomb_c::procWait_init() {
    mFunc = &procWait;
    if(chk_attrState(this, ATTR_STATE_80)) {
        change_state(STATE_1);
    }

    mSph.GetObjCo().OnSPrmBit(cCcD_ObjCommonBase::CO_SPRM_SET);
    return true;
}

bool daBomb_c::procWait() {
    if(checkExplode()) {
        return true;
    }
    else {
        if(fopAcM_checkCarryNow(this)) {
            return procCarry_init();
        }
        else {
            posMoveF();
            f32 y_vel = speed.y;
            bgCrrPos();
            bool temp = false;
            if(checkExplodeBg()) {
                temp = true;
            }
            else {
                if(chk_state(STATE_4)) {
                    if(waitState_cannon()) {
                        temp = true;
                    }
                }
                else {
                    if(chk_state(STATE_7)) {
                        waitState_bomtyu();
                    }
                }
            }

            if(!temp && !field_0x781) {
                bound(y_vel);
                if((mAcch.ChkGroundHit() || chk_state(STATE_5)) && !mAcch.ChkGroundLanding()) {
                    mAttentionInfo.setFlag(fopAc_Attn_ACTION_CARRY_e);
                }
                else {
                    mAttentionInfo.mFlags &= ~fopAc_Attn_ACTION_CARRY_e;
                }
            }

            return true;
        }
    }
}

bool daBomb_c::waitState_cannon() {
    se_cannon_fly_set();

    return false;
}

void daBomb_c::waitState_bomtyu() {
    cLib_chaseF(&mScale.x, 1.0f, 0.05f);
    cLib_chaseF(&mScale.y, 1.0f, 0.05f);
    cLib_chaseF(&mScale.z, 1.0f, 0.05f);
    if(field_0x6F2) {
        setFuseEffect();
        field_0x6F2 = 0;
        field_0x6F4 = 1;
        change_state(STATE_1);
    }
}

bool daBomb_c::procSink() {
    field_0x781 = 1;

    return true;
}

/* 800DBC5C-800DBF24       .text execute__8daBomb_cFv */
BOOL daBomb_c::execute() {
    static cXyz fuse_offset(0.0f, 60.0f, 5.0f);

    if(chk_state(STATE_4) && !field_0x77C) {
        field_0x77C = 1;
        cXyz pos(current.pos);
        pos.y += 20.0f;
        makeFireEffect(pos, shape_angle);
    }
    
    set_wind_vec();
    if(mFunc) {
        (this->*mFunc)();
    }

    if(field_0x781) {
        fopAcM_delete(this);
    }
    else {
        set_real_shadow_flag();
        if(mType == 1) {
            anm_play_nut();
        }

        mStts.Move();
        mAttentionInfo.mPosition.x = current.pos.x;
        mAttentionInfo.mPosition.y = current.pos.y + 50.0f;
        mAttentionInfo.mPosition.z = current.pos.z;
        mEyePos = mAttentionInfo.mPosition;
        if(!chk_attrState(this, ATTR_STATE_20)) {
            set_mtx();
            mFusePos3 = mFusePos2;
            mFusePos2 = mFusePos;
            mDoMtx_stack_c::multVec(&fuse_offset, &mFusePos);
            cXyz pos;
            pos.x = current.pos.x;
            pos.y = current.pos.y + 30.0f;
            pos.z = current.pos.z;
            mSph.SetC(pos);
            mSph.SetR(mScale.x * 30.0f);
            if(mMassCounter != g_Counter.mCounter0) {
                dComIfG_Ccsp()->Set(&mSph);
                //using inline breaks match
                //dComIfG_Ccsp()->SetMass(&mSph, 3);
                g_dComIfG_gameInfo.play.mCcS.SetMass(&mSph, 3);
                mMassCounter = g_Counter.mCounter0;
            }
        }

        if(chk_attrState(this, ATTR_STATE_10) || field_0x6F4 == 1) {
            fopAcM_seStart(this, JA_SE_OBJ_BOMB_IGNITION, 0);
        }
    }

    if(field_0x782) {
        field_0x784++;
    }

    return true;
}

BOOL daBomb_Execute(daBomb_c* i_this) {
    return i_this->execute();
}

/* 800DBF44-800DC250       .text set_wind_vec__8daBomb_cFv */
void daBomb_c::set_wind_vec() {
    /* Nonmatching */
}

/* 800DC250-800DC2D0       .text anm_play_nut__8daBomb_cFv */
void daBomb_c::anm_play_nut() {
    if(chk_state(STATE_5) || chk_state(STATE_6)) {
        mBck0.play();
        mBrk0.play();
    }
    else {
        if(mRestTime + 2 <= 0x87) {
            mBck1.play();
            mBrk1.play();
        }
    }
}

void daBomb_c::set_mtx() {
    mpModel->setBaseScale(mScale);
    mDoMtx_stack_c::transS(current.pos);
    if(prm_get_angXZero()) {
        mDoMtx_stack_c::ZXYrotM(0, shape_angle.y, shape_angle.z);
    }
    else {
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    }

    MTXCopy(mDoMtx_stack_c::get(), mpModel->mBaseTransformMtx);
}

void daBomb_c::init_mtx() {
    set_mtx();
}

void daBomb_c::se_cannon_fly_set() {
    mDoAud_seStart(JA_SE_LK_SHIP_CANNON_FLY, &current.pos, 0, 0);
    field_0x77F = 1;
}

void daBomb_c::se_cannon_fly_stop() {
    if(field_0x77F) {
        mDoAud_seStopActor(&current.pos, -1);
        field_0x77F = 0;
    }
}

void daBomb_c::eff_water_splash() {
    cXyz pos;
    pos.z = current.pos.z;
    pos.y = field_0x554.y;
    pos.x = current.pos.x;
    fopKyM_createWpillar(&pos, 0.5f, 0.75f, 0);

    //what
    u32 soundId = 0x13;

    fopAcM_seStart(this, JA_SE_OBJ_FALL_WATER_S, soundId);
}

bool daBomb_IsDelete(daBomb_c*) {
    return true;
}

bool daBomb_c::bombDelete() {
    if(mSmoke.mpEmitter) {
        mSmoke.mpEmitter->mpEmitterCallBack = 0;
        mSmoke.mpEmitter->becomeInvalidEmitter();
    }
    mSmoke.mpEmitter = 0;

    if(mSparks.mpEmitter) {
        mSparks.mpEmitter->mpEmitterCallBack = 0;
        mSparks.mpEmitter->becomeInvalidEmitter();
    }
    mSparks.mpEmitter = 0;

    if(field_0x6F0) {
        if(daPy_getPlayerLinkActorClass()->mActivePlayerBombs != 0) {
            daPy_getPlayerLinkActorClass()->mActivePlayerBombs -= 1;
        }
    }

    se_cannon_fly_stop();
    if(mType == 1) {
        dComIfG_resDelete(&mPhs, m_attrType[mType].resName);
    }

    dKy_actor_addcol_set(0, 0, 0, 0.0f);
    dKy_efplight_cut(&mPntLight);
    dKyw_pntwind_cut(&mPntWind);

    return true;
}

BOOL daBomb_Delete(daBomb_c* i_this) {
    i_this->bombDelete();
    return true;
}

#include "d/actor/d_a_bomb3.inc"

int daBomb_createHeap(fopAc_ac_c* i_this) {
    static_cast<daBomb_c*>(i_this)->createHeap();
}

int daBomb_c::create() {
    int state = prm_get_state();
    if(state == 5 || state == 6) {
        mType = 1;
    }
    else if(state == 4) {
        mType = 2;
    }
    else {
        mType = 0;
    }

    fopAcM_SetupActor(this, daBomb_c);

    int status;
    if(mType == 1) {
        status = dComIfG_resLoad(&mPhs, m_attrType[mType].resName);
    }
    else {
        status = cPhs_COMPLEATE_e;
    }

    if(status == cPhs_COMPLEATE_e) {
        if(fopAcM_entrySolidHeap(this, &daBomb_createHeap, m_attrType[mType].heapSize)) {
            create_init();
        }
        else {
            status = cPhs_ERROR_e;
        }
    }

    return status;
}

/* 800DCC0C-800DCEBC       .text __ct__8daBomb_cFv */
daBomb_c::daBomb_c() {
    /* Nonmatching */
}

int daBomb_Create(fopAc_ac_c* i_this) {
    return static_cast<daBomb_c*>(i_this)->create();
}

dCcD_SrcSph l_sph_src = {};

void daBomb_c::create_init() {
    mCir.SetWall(30.0f, 30.0f);
    mAcch.Set(&current.pos, &next.pos, this, true, &mCir, &speed, &current.angle, &shape_angle);
    mAcch.ClrWaterNone();
    mAcch.ClrRoofNone();
    mAcch.m_roof_height = 50.0f;
    mAcch.OnLineCheck();

    field_0x554.setall(-1.0e9f);
    field_0x560 = 0;
    mbWaterIn = 0;
    field_0x562 = 0;
    mCullMtx = mpModel->getBaseTRMtx();
    
    mStts.Init(200, 0xFF, this);
    mSph.Set(l_sph_src);
    mSph.SetStts(&mStts);
    if(chk_state(STATE_8)) {
        mSph.GetObjAt().SetAtp(2);
    }

    mGravity = -2.9f;
    mMaxFallSpeed = -100.0f;
    mRestTime = 0x96;
    mInitialState = prm_get_state();
    if(!chk_state(STATE_4)) {
        mAttentionInfo.setFlag(fopAc_Attn_ACTION_CARRY_e);
    }

    field_0x77C = 0;
    field_0x77D = 0;
    field_0x77E = 0;
    field_0x6F4 = 0;
    field_0x77F = 0;
    field_0x780 = 0;
    field_0x781 = 0;
    field_0x782 = 0;
    field_0x784 = 0;

    mWindVec.set(cXyz::Zero);

    mMassCounter = g_Counter.mCounter0 - 1;
    if(chk_attrState(this, ATTR_STATE_2)) {
        mScale.setall(0.0f);
    }
    if(chk_attrState(this, ATTR_STATE_4)) {
        setFuseEffect();
    }
    if(chk_attrState(this, ATTR_STATE_8)) {
        bgCrrPos();
    }
    
    if(chk_state(STATE_3)) {
        field_0x6F0 = 1;
        field_0x7C8 = 2;
    }
    else {
        field_0x7C8 = 0;
    }
    
    if(chk_attrState(this, ATTR_STATE_1)) {
        procExplode_init();
    }
    else {
        procWait_init();
    }

    mCull.mBox.mMin.x = -36.0f;
    mCull.mBox.mMin.y = 0.0f;
    mCull.mBox.mMin.z = -36.0f;
    mCull.mBox.mMax.x = 36.0f;
    mCull.mBox.mMax.y = 66.0f;
    mCull.mBox.mMax.z = 36.0f;
    mCullSizeFar = 10.0f;

    init_mtx();
}

/* 800DD348-800DD34C       .text draw__26daBomb_fuseSparksEcallBackFP14JPABaseEmitter */
void daBomb_fuseSparksEcallBack::draw(JPABaseEmitter*) {
    /* Nonmatching */
}

void daBomb_fuseSparksEcallBack::setup(JPABaseEmitter* emitter, const cXyz* pos, const csXyz*, signed char) {
    mpPos = pos;
    mpEmitter = emitter;
}

/* 800DD358-800DD35C       .text execute__25daBomb_fuseSmokeEcallBackFP14JPABaseEmitter */
void daBomb_fuseSmokeEcallBack::execute(JPABaseEmitter*) {
    /* Nonmatching */
}

/* 800DD35C-800DD360       .text draw__25daBomb_fuseSmokeEcallBackFP14JPABaseEmitter */
void daBomb_fuseSmokeEcallBack::draw(JPABaseEmitter*) {
    /* Nonmatching */
}

void daBomb_fuseSmokeEcallBack::setup(JPABaseEmitter* emitter, const cXyz* pos, const csXyz*, signed char) {
    mpPos = pos;
    mpEmitter = emitter;
}

actor_method_class l_daBomb_Method = {
    (process_method_func)daBomb_Create,
    (process_method_func)daBomb_Delete,
    (process_method_func)daBomb_Execute,
    (process_method_func)daBomb_IsDelete,
    (process_method_func)daBomb_Draw,
};

actor_process_profile_definition g_profile_BOMB = {
    fpcLy_CURRENT_e,
    7,
    fpcPi_CURRENT_e,
    PROC_BOMB,
    &g_fpcLf_Method.mBase,
    sizeof(daBomb_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x0115,
    &l_daBomb_Method,
    fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_CUSTOM_e,
};
