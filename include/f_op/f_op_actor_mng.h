#ifndef F_OP_ACTOR_MNG_H_
#define F_OP_ACTOR_MNG_H_

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_iter.h"
#include "f_pc/f_pc_manager.h"
#include "f_pc/f_pc_searcher.h"
#include "m_Do/m_Do_audio.h"

#define fopAcM_SetupActor(ptr,ClassName) \
    if (!fopAcM_CheckCondition(ptr, fopAcCnd_INIT_e)) { \
        new (ptr) ClassName(); \
        fopAcM_OnCondition(ptr, fopAcCnd_INIT_e); \
    }

class J3DModelData;  // placeholder
class JKRHeap;
class cM3dGPla;

struct fopAcM_prmBase_class {
    /* 0x00 */ u32 field_0x00;
    /* 0x04 */ cXyz field_0x04;
    /* 0x10 */ csXyz field_0x10;
    /* 0x16 */ u16 field_0x16;
};  // Size = 0x18

struct fopAcM_prm_class {
    /* 0x00 */ u32 mParameter;  // single U32 Parameter
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ csXyz mAngle;  // rotation
    /* 0x16 */ u16 mSetId;
    /* 0x18 */ u8 mScale[3];
    /* 0x1B */ u8 mGbaName;
    /* 0x1C */ s32 mParentPcId;  // parent process ID
    /* 0x20 */ s8 mSubtype;
    /* 0x21 */ s8 mRoomNo;
};

struct fopAcM_search4ev_prm {
    fopAcM_search4ev_prm() { clear(); }
    void clear() {
        mName[0] = 0;
        mEventID = -1;
        mProcName = 11;
        mSubType = 0;
    }

    /* 0x00 */ char mName[30];
    /* 0x1E */ s16 mEventID;
    /* 0x20 */ s16 mProcName;
    /* 0x22 */ s8 mSubType;
};

struct fopAcM_search_prm {
    /* 0x00 */ u32 mParam0;
    /* 0x04 */ u32 mParam1;
    /* 0x08 */ s16 mProcName;
    /* 0x0A */ s8 mSubType;
};

class dKy_tevstr_c;
typedef int (*heapCallbackFunc)(fopAc_ac_c*);
typedef int (*createFunc)(void*);

// struct DOUBLE_POS {
//     double x, y, z;
// };

inline s8 fopAcM_GetRoomNo(fopAc_ac_c* pActor) {
    return pActor->current.roomNo;
}

inline u32 fopAcM_GetID(void* pActor) {
    return fpcM_GetID(pActor);
}

inline s16 fopAcM_GetName(void* pActor) {
    return fpcM_GetName(pActor);
}

inline MtxP fopAcM_GetMtx(fopAc_ac_c* pActor) {
    return pActor->mCullMtx;
}

inline bool fopAcM_checkStatus(fopAc_ac_c* pActor, u32 status) {
    return pActor->mStatus & status;
}

inline u32 fopAcM_checkCarryNow(fopAc_ac_c* pActor) {
    return pActor->mStatus & fopAcStts_CARRY_e;
}

enum fopAcM_CARRY {
    /* 0x01 */ fopAcM_CARRY_TYPE_1 = 1,
    /* 0x02 */ fopAcM_CARRY_HEAVY = 2,
    /* 0x04 */ fopAcM_CARRY_SIDE = 4,
    /* 0x08 */ fopAcM_CARRY_TYPE_8 = 8,
    /* 0x10 */ fopAcM_CARRY_LIGHT = 16, // guess based on context
    /* 0x30 */ fopAcM_CARRY_UNK_30 = 0x30,
};

inline u32 fopAcM_checkHookCarryNow(fopAc_ac_c* pActor) {
    return fopAcM_checkStatus(pActor, fopAcStts_HOOK_CARRY_e);
}

inline u32 fopAcM_GetParam(void* pActor) {
    return fpcM_GetParam(pActor);
}

inline u32 fopAcM_GetParamBit(void* ac, u8 shift, u8 bit) {
    return (fopAcM_GetParam(ac) >> shift) & ((1 << bit) - 1);
}

inline void fopAcM_SetParam(void* p_actor, u32 param) {
    fpcM_SetParam(p_actor, param);
}

inline void fopAcM_SetJntHit(fopAc_ac_c* i_actorP, JntHit_c* i_jntHitP) {
    i_actorP->mJntHit = i_jntHitP;
}

inline s16 fopAcM_GetProfName(void* pActor) {
    return fpcM_GetProfName(pActor);
}

inline u8 fopAcM_GetGroup(fopAc_ac_c* p_actor) {
    return p_actor->mGroup;
}

inline void fopAcM_OnStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->mStatus |= flag;
}

inline void fopAcM_OffStatus(fopAc_ac_c* pActor, u32 flag) {
    pActor->mStatus &= ~flag;
}

inline fopAc_ac_c* fopAcM_Search(fopAcIt_JudgeFunc func, void* param) {
    return (fopAc_ac_c*)fopAcIt_Judge(func, param);
}

inline cXyz& fopAcM_GetPosition_p(fopAc_ac_c* pActor) {
    return pActor->current.pos;
}

inline cXyz& fopAcM_GetPosition(fopAc_ac_c* pActor) {
    return pActor->current.pos;
}

inline cXyz& fopAcM_GetOldPosition_p(fopAc_ac_c* pActor) {
    return pActor->next.pos;
}

inline cXyz& fopAcM_GetSpeed_p(fopAc_ac_c* pActor) {
    return pActor->speed;
}

inline csXyz& fopAcM_GetAngle_p(fopAc_ac_c* pActor) {
    return pActor->current.angle;
}

inline csXyz& fopAcM_GetShapeAngle_p(fopAc_ac_c* pActor) {
    return pActor->shape_angle;
}

inline bool fopAcM_CheckCondition(fopAc_ac_c* p_actor, u32 flag) {
    return p_actor->mCondition & flag;
}

inline void fopAcM_OnCondition(fopAc_ac_c* p_actor, u32 flag) {
    p_actor->mCondition |= flag;
}

inline void fopAcM_OffCondition(fopAc_ac_c* p_actor, u32 flag) {
    p_actor->mCondition &= ~flag;
}

inline BOOL fopAcM_IsActor(void* actor) {
    return fopAc_IsActor(actor);
}

inline void fopAcM_SetRoomNo(fopAc_ac_c* actor, s8 roomNo) {
    actor->current.roomNo = roomNo;
}

inline void fopAcM_setHookCarryNow(fopAc_ac_c* actor) {
    fopAcM_OnStatus(actor, fopAcStts_HOOK_CARRY_e);
}

inline void fopAcM_cancelHookCarryNow(fopAc_ac_c* actor) {
    fopAcM_OffStatus(actor, fopAcStts_HOOK_CARRY_e);
}

inline s8 fopAcM_GetHomeRoomNo(fopAc_ac_c* pActor) {
    return pActor->orig.roomNo;
}

inline void fopAcM_SetGravity(fopAc_ac_c* actor, f32 gravity) {
    actor->mGravity = gravity;
}

inline void fopAcM_SetMaxFallSpeed(fopAc_ac_c* actor, f32 speed) {
    actor->mMaxFallSpeed = speed;
}

inline void fopAcM_SetMtx(fopAc_ac_c* actor, MtxP m) {
    actor->mCullMtx = m;
}

inline void fopAcM_SetSpeed(fopAc_ac_c* actor, f32 x, f32 y, f32 z) {
    actor->speed.set(x, y, z);
}

inline void fopAcM_SetSpeedF(fopAc_ac_c* actor, f32 f) {
    actor->speedF = f;
}

inline void fopAcM_SetStatus(fopAc_ac_c* actor, u32 status) {
    actor->mStatus = status;
}

inline void fopAcM_SetModel(fopAc_ac_c* actor, J3DModel* model) {
    actor->model = model;
}

inline J3DModel* fopAcM_GetModel(fopAc_ac_c* actor) {
    return actor->model;
}

inline fopAcM_prm_class* fopAcM_GetAppend(void* actor) {
    return (fopAcM_prm_class*)fpcM_GetAppend(actor);
}

inline BOOL fopAcM_IsExecuting(unsigned int id) {
    return fpcM_IsExecuting(id);
}

inline f32 fopAcM_GetSpeedF(fopAc_ac_c* p_actor) {
    return p_actor->speedF;
}

inline f32 fopAcM_GetGravity(fopAc_ac_c* p_actor) {
    return p_actor->mGravity;
}

inline f32 fopAcM_GetMaxFallSpeed(fopAc_ac_c* p_actor) {
    return p_actor->mMaxFallSpeed;
}

inline JntHit_c* fopAcM_GetJntHit(fopAc_ac_c* i_actor) {
    return i_actor->mJntHit;
}

inline void fopAcM_setCullSizeFar(fopAc_ac_c* i_actor, f32 i_far) {
    i_actor->mCullSizeFar = i_far;
}

inline f32 fopAcM_getCullSizeFar(fopAc_ac_c* i_actor) {
    return i_actor->mCullSizeFar;
}

inline int fopAcM_GetCullSize(fopAc_ac_c* i_actor) {
    return i_actor->mCullType;
}

inline BOOL fopAcM_CULLSIZE_IS_BOX(int i_culltype) {
    return (i_culltype >= 0 && i_culltype < 14) || i_culltype == 14;
}

inline Vec fopAcM_getCullSizeSphereCenter(fopAc_ac_c* i_actor) {
    return i_actor->mCull.mSphere.mCenter;
}

inline f32 fopAcM_getCullSizeSphereR(fopAc_ac_c* i_actor) {
    return i_actor->mCull.mSphere.mRadius;
}

inline void dComIfGs_onSwitch(int i_no, int i_roomNo);
inline void dComIfGs_offSwitch(int i_no, int i_roomNo);
inline BOOL dComIfGs_isSwitch(s32 i_no, s32 i_roomNo);
inline void dComIfGs_offActor(int i_no, int i_roomNo);

inline void fopAcM_onSwitch(fopAc_ac_c* pActor, int sw) {
    return dComIfGs_onSwitch(sw, fopAcM_GetHomeRoomNo(pActor));
}

inline void fopAcM_offSwitch(fopAc_ac_c* pActor, int sw) {
    return dComIfGs_offSwitch(sw, fopAcM_GetHomeRoomNo(pActor));
}

inline BOOL fopAcM_isSwitch(fopAc_ac_c* pActor, int sw) {
    return dComIfGs_isSwitch(sw, fopAcM_GetHomeRoomNo(pActor));
}

inline fopAc_ac_c* fopAcM_SearchByID(u32 id) {
    return (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &id);
}

inline fopAc_ac_c* fopAcM_SearchByName(s16 proc_id) {
    return (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeForPName, &proc_id);
}

inline void dComIfGs_onItem(int bitNo, int roomNo);
inline void fopAcM_onItem(fopAc_ac_c* item, int bitNo) {
    dComIfGs_onItem(bitNo, fopAcM_GetHomeRoomNo(item));
}

inline bool dComIfGs_isItem(int bitNo, int roomNo);
inline bool fopAcM_isItem(fopAc_ac_c* item, int bitNo) {
    return dComIfGs_isItem(bitNo, fopAcM_GetHomeRoomNo(item));
}

inline f32 fopAcM_searchActorDistanceY(fopAc_ac_c* actorA, fopAc_ac_c* actorB) {
    return actorB->current.pos.y - actorA->current.pos.y;
}

inline u16 fopAcM_GetSetId(fopAc_ac_c* p_actor) {
    return p_actor->mSetId;
}

inline void dComIfGs_onActor(int bitNo, int roomNo);

inline void fopAcM_onActor(fopAc_ac_c* p_actor) {
    int setId = fopAcM_GetSetId(p_actor);
    dComIfGs_onActor(setId, fopAcM_GetHomeRoomNo(p_actor));
}

inline bool fopAcM_IsFirstCreating(void* i_actor) {
    return fpcM_IsFirstCreating(i_actor);
}

void fopAcM_initManager();

void* fopAcM_FastCreate(s16 pProcTypeID, FastCreateReqFunc param_2, void* param_3, void* pData);

void fopAcM_setStageLayer(void* p_proc);

void fopAcM_setRoomLayer(void* p_proc, int roomNo);

s32 fopAcM_SearchByID(unsigned int id, fopAc_ac_c** p_actor);

s32 fopAcM_SearchByName(s16 procName, fopAc_ac_c** p_actor);

fopAcM_prm_class* fopAcM_CreateAppend();

fopAcM_prm_class* createAppend(u16 enemyNo, u32 parameters, cXyz* p_pos, int roomNo,
                               csXyz* p_angle, cXyz* p_scale, s8 subType,
                               unsigned int parentPId);

void fopAcM_Log(fopAc_ac_c* p_actor, char* str);

s32 fopAcM_delete(fopAc_ac_c* p_actor);
s32 fopAcM_delete(unsigned int actorID);

s32 fopAcM_create(char*, u32 i_parameter, cXyz* i_pos, int i_roomNo, csXyz* i_angle, cXyz* i_scale, createFunc i_createFunc);
s32 fopAcM_create(s16 i_procName, u32 i_parameter, cXyz* i_pos, int i_roomNo, csXyz* i_angle, cXyz* i_scale, s8 i_subType, createFunc i_createFunc);

inline s32 fopAcM_create(s16 i_procName, createFunc i_createFunc, void*);

void* fopAcM_fastCreate(s16 procName, u32 parameter, cXyz* p_pos, int roomNo,
                        csXyz* p_angle, cXyz* p_scale, s8 subType,
                        createFunc p_createFunc, void* p_createFuncData);

void* fopAcM_fastCreate(char* p_actorName, u32 parameter, cXyz* pActorPos, int roomNo,
                        csXyz* p_angle, cXyz* p_scale, createFunc p_createFunc,
                        void* p_createFuncData);

s32 fopAcM_createChild(s16 procName, unsigned int parentPId, u32 parameters, cXyz* p_pos,
                       int roomNo, csXyz* p_angle, cXyz* p_scale, s8 subType,
                       createFunc p_createFunc);

s32 fopAcM_createChildFromOffset(s16 procName, unsigned int parentProcID, u32 actorParams,
                                 cXyz* p_pos, int roomNo, csXyz* p_angle,
                                 cXyz* p_scale, s8 subType, createFunc p_createFunc);

void fopAcM_DeleteHeap(fopAc_ac_c* p_actor);

s32 fopAcM_callCallback(fopAc_ac_c* p_actor, heapCallbackFunc p_callbackFunc, JKRHeap* p_heap);

bool fopAcM_entrySolidHeap_(fopAc_ac_c* p_actor, heapCallbackFunc p_heapCallback, u32 size);

bool fopAcM_entrySolidHeap(fopAc_ac_c* p_actor, heapCallbackFunc p_heapCallback, u32 size);

void fopAcM_SetMin(fopAc_ac_c* p_actor, f32 minX, f32 minY, f32 minZ);

void fopAcM_SetMax(fopAc_ac_c* p_actor, f32 maxX, f32 maxY, f32 maxZ);

void fopAcM_setCullSizeBox(fopAc_ac_c* p_actor, f32 minX, f32 minY, f32 minZ, f32 maxX, f32 maxY,
                           f32 maxZ);

void fopAcM_setCullSizeSphere(fopAc_ac_c* p_actor, f32 minX, f32 minY, f32 minZ, f32 radius);

void fopAcM_setCullSizeBox2(fopAc_ac_c* p_actor, J3DModelData* p_modelData);

bool fopAcM_addAngleY(fopAc_ac_c* p_actor, s16 target, s16 step);

void fopAcM_calcSpeed(fopAc_ac_c* p_actor);

void fopAcM_posMove(fopAc_ac_c* p_actor, const cXyz* p_movePos);

void fopAcM_posMoveF(fopAc_ac_c* p_actor, const cXyz* p_movePos);

s16 fopAcM_searchActorAngleY(fopAc_ac_c* p_actorA, fopAc_ac_c* p_actorB);

s32 fopAcM_seenActorAngleY(fopAc_ac_c*, fopAc_ac_c*);

f32 fopAcM_searchActorDistance(fopAc_ac_c* p_actorA, fopAc_ac_c* p_actorB);

f32 fopAcM_searchActorDistance2(fopAc_ac_c* p_actorA, fopAc_ac_c* p_actorB);

f32 fopAcM_searchActorDistanceXZ(fopAc_ac_c* p_actorA, fopAc_ac_c* p_actorB);

f32 fopAcM_searchActorDistanceXZ2(fopAc_ac_c* p_actorA, fopAc_ac_c* p_actorB);

s32 fopAcM_rollPlayerCrash(fopAc_ac_c* i_this, f32 distAdjust, u32 flag);
s32 fopAcM_checkCullingBox(Mtx, f32, f32, f32, f32, f32, f32);
s32 fopAcM_cullingCheck(fopAc_ac_c*);
void* event_second_actor(u16);
s32 fopAcM_orderTalkEvent(fopAc_ac_c*, fopAc_ac_c*);
s32 fopAcM_orderSpeakEvent(fopAc_ac_c* i_actor);
s32 fopAcM_orderDoorEvent(fopAc_ac_c*, fopAc_ac_c*);
s32 fopAcM_orderCatchEvent(fopAc_ac_c*, fopAc_ac_c*);
s32 fopAcM_orderOtherEvent2(fopAc_ac_c*, char*, u16, u16);
s32 fopAcM_orderChangeEventId(fopAc_ac_c* i_this, s16 eventIdx, u16 flag, u16 hind);
s32 fopAcM_orderChangeEventId(fopAc_ac_c* i_this, fopAc_ac_c* i_partner, s16 eventIdx, u16 flag, u16 hind);
s32 fopAcM_orderOtherEventId(fopAc_ac_c* actor, s16 eventID, u8 mapToolID, u16 param_3,
                             u16 priority, u16 flag);
s32 fopAcM_orderPotentialEvent(fopAc_ac_c*, u16, u16, u16);
s32 fopAcM_orderItemEvent(fopAc_ac_c*);
s32 fopAcM_orderTreasureEvent(fopAc_ac_c*, fopAc_ac_c*);
fopAc_ac_c* fopAcM_getTalkEventPartner(fopAc_ac_c*);
fopAc_ac_c* fopAcM_getItemEventPartner(fopAc_ac_c*);
fopAc_ac_c* fopAcM_getEventPartner(fopAc_ac_c*);

s32 fopAcM_createItemForPresentDemo(cXyz* p_pos, int i_itemNo, u8 param_2, int i_itemBitNo,
                                    int i_roomNo, csXyz* p_angle, cXyz* p_scale);

s32 fopAcM_createItemForTrBoxDemo(cXyz* p_pos, int i_itemNo, int i_itemBitNo, int i_roomNo,
                                  csXyz* p_angle, cXyz* p_scale);

s32 fopAcM_createItemFromTable(cXyz* p_pos, int i_tableNo, int i_itemBitNo, int i_roomNo,
                               csXyz* p_angle, int param_5, cXyz * p_scale, f32* speedF,
                               f32* speedY, bool createDirect);

s32 fopAcM_createShopItem(cXyz* p_pos, int i_itemNo, csXyz* rot, int roomNo, cXyz* scale,
                          createFunc createFunc);

s32 fopAcM_createRaceItem(cXyz* p_pos, int i_itemNo, int i_itemBitNo, csXyz* rot, int roomNo,
                          cXyz* scale, int param_7);

s32 fopAcM_createIball(cXyz* p_pos, int itemTableIdx, int roomNo, csXyz* rot, int itemStealNum);

s32 fopAcM_createDemoItem(cXyz* p_pos, int itemNo, int itemBitNo, csXyz* p_angle,
                          int roomNo, cXyz* scale, u8 param_7);

s32 fopAcM_createItemForBoss(cXyz* p_pos, int param_2, int roomNo, csXyz* p_angle,
                             cXyz* p_scale, int param_8);

void* fopAcM_createItemForSimpleDemo(cXyz* p_pos, int i_itemNo, int i_roomNo,
                                     csXyz* p_angle, cXyz* p_scale, f32 speedF,
                                     f32 speedY);

s32 fopAcM_createItem(cXyz* p_pos, int itemNo, int param_3, int roomNo, int type, csXyz* p_angle,
                      int action, cXyz* p_scale);

void* fopAcM_fastCreateItem2(cXyz* p_pos, int itemNo, int param_3, int roomNo, int param_5,
                             csXyz* p_angle, int, cXyz* p_scale);

void* fopAcM_fastCreateItem(cXyz* p_pos, int i_itemNo, int i_roomNo, csXyz* p_angle,
                            cXyz* p_scale, f32 p_speedF, f32 p_speedY, f32 param_8,
                            int param_9, createFunc p_createFunc);

BOOL stealItem_CB(void* actor);

fopAc_ac_c* fopAcM_myRoomSearchEnemy(s8 roomNo);

s32 fopAcM_createDisappear(fopAc_ac_c*, cXyz*, u8, u8, u8);
void fopAcM_setCarryNow(fopAc_ac_c* i_this, int stageLayer);
void fopAcM_cancelCarryNow(fopAc_ac_c* i_this);
s32 fopAcM_otoCheck(fopAc_ac_c*, f32);
// void vectle_calc(DOUBLE_POS*, cXyz*);
// void get_vectle_calc(cXyz*, cXyz*, cXyz*);

static const char* fopAcM_getProcNameString(fopAc_ac_c* p_actor);

static fopAc_ac_c* fopAcM_findObjectCB(fopAc_ac_c* p_actor, void* p_data);

fopAc_ac_c* fopAcM_searchFromName(char* name, u32 param0, u32 param1);

fopAc_ac_c* fopAcM_findObject4EventCB(fopAc_ac_c* p_actor, void* p_data);

fopAc_ac_c* fopAcM_searchFromName4Event(char* name, s16 eventID);

s32 fopAcM_getWaterY(const cXyz*, f32*);
void fpoAcM_relativePos(fopAc_ac_c* actor, cXyz* p_inPos, cXyz* p_outPos);

void fopAcM_setGbaName(fopAc_ac_c* i_this, u8 itemNo, u8 gbaName0, u8 gbaName1);

inline fopAc_ac_c* dComIfGp_getPlayer(int);

inline s16 fopAcM_searchPlayerAngleY(fopAc_ac_c* actor) {
    return fopAcM_searchActorAngleY(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

inline f32 fopAcM_searchPlayerDistanceY(fopAc_ac_c* actor) {
    return fopAcM_searchActorDistanceY(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

inline f32 fopAcM_searchPlayerDistanceXZ2(fopAc_ac_c* actor) {
    return fopAcM_searchActorDistanceXZ2(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

inline f32 fopAcM_searchPlayerDistanceXZ(fopAc_ac_c* actor) {
    return fopAcM_searchActorDistanceXZ(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

inline f32 fopAcM_searchPlayerDistance(fopAc_ac_c* actor) {
    return fopAcM_searchActorDistance(actor, (fopAc_ac_c*)dComIfGp_getPlayer(0));
}

s8 dComIfGp_getReverb(int roomNo);

inline void fopAcM_seStartCurrent(fopAc_ac_c* actor, u32 sfxID, u32 param_2) {
    mDoAud_seStart(sfxID, &actor->current.pos, param_2, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
}

inline void fopAcM_seStart(fopAc_ac_c* actor, u32 sfxID, u32 param_2) {
    mDoAud_seStart(sfxID, &actor->mEyePos, param_2, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
}

inline void fopAcM_monsSeStart(fopAc_ac_c* actor, u32 sfxID, u32 param_2) {
    mDoAud_monsSeStart(sfxID, &actor->mEyePos, fopAcM_GetID(actor), 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
}

extern "C" {
void fopAcM_initManager__Fv(void);
void fopAcM_CreateAppend__Fv(void);
void fopAcM_DeleteHeap__FP10fopAc_ac_c(void);
void fopAcM_FastCreate__FsPFPv_iPvPv(void);
void fopAcM_Log__FPC10fopAc_ac_cPCc(void);
void fopAcM_SearchByID__FUiPP10fopAc_ac_c(void);
void fopAcM_calcSpeed__FP10fopAc_ac_c(void);
void fopAcM_callCallback__FP10fopAc_ac_cPFP10fopAc_ac_c_iP7JKRHeap(void);
void fopAcM_cancelCarryNow__FP10fopAc_ac_c(void);
void fopAcM_create__FsUsUlPC4cXyziPC5csXyzPC4cXyzScPFPv_i(void);
void fopAcM_createChild__FsUiUlPC4cXyziPC5csXyzPC4cXyzScPFPv_i(void);
void fopAcM_createDemoItem__FPC4cXyziiPC5csXyziPC4cXyzUc(void);
void fopAcM_createItem__FPC4cXyziiiPC5csXyzPC4cXyzi(void);
void fopAcM_createItemForDirectGet__FPC4cXyziiPC5csXyzPC4cXyzff(void);
void fopAcM_createItemForPresentDemo__FPC4cXyziUciiPC5csXyzPC4cXyz(void);
void fopAcM_createItemForSimpleDemo__FPC4cXyziiPC5csXyzPC4cXyzff(void);
void fopAcM_createItemForTrBoxDemo__FPC4cXyziiiPC5csXyzPC4cXyz(void);
void fopAcM_createItemFromTable__FPC4cXyziiiPC5csXyziPC4cXyzPfPfb(void);
void fopAcM_create__FsUlPC4cXyziPC5csXyzPC4cXyzSc(void);
void fopAcM_cullingCheck__FPC10fopAc_ac_c(void);
void fopAcM_delete__FP10fopAc_ac_c(void);
void fopAcM_delete__FUi(void);
void fopAcM_effHamonSet__FPUlPC4cXyzff(void);
void fopAcM_entrySolidHeap__FP10fopAc_ac_cPFP10fopAc_ac_c_iUl(void);
void fopAcM_entrySolidHeap___FP10fopAc_ac_cPFP10fopAc_ac_c_iUl(void);
void fopAcM_fastCreate__FsUlPC4cXyziPC5csXyzPC4cXyzScPFPv_iPv(void);
void fopAcM_fastCreateItem__FPC4cXyziiPC5csXyzPC4cXyzPfPfiiPFPv_i(void);
void fopAcM_fastCreateItem2__FPC4cXyziiiiPC5csXyzPC4cXyz(void);
void fopAcM_fastCreate__FPCcUlPC4cXyziPC5csXyzPC4cXyzPFPv_iPv(void);
void fopAcM_findObject4EventCB__FP10fopAc_ac_cPv(void);
void fopAcM_findObjectCB__FPC10fopAc_ac_cPv(void);
void gndCheck__11fopAcM_gc_cFPC4cXyz(void);
void fopAcM_getEventPartner__FPC10fopAc_ac_c(void);
void fopAcM_getItemEventPartner__FPC10fopAc_ac_c(void);
void fopAcM_getItemNoFromTableNo__FUc(void);
void fopAcM_getPolygonAngle__FRC13cBgS_PolyInfos(void);
void fopAcM_getPolygonAngle__FPC8cM3dGPlas(void);
void fopAcM_getProcNameString__FPC10fopAc_ac_c(void);
void fopAcM_getTalkEventPartner__FPC10fopAc_ac_c(void);
void fopAcM_getWaterStream__FPC4cXyzRC13cBgS_PolyInfoP4cXyzPii(void);
void fopAcM_getWaterY__FPC4cXyzPf(void);
void lineCheck__11fopAcM_lc_cFPC4cXyzPC4cXyzPC10fopAc_ac_c(void);
void fopAcM_orderCatchEvent__FP10fopAc_ac_cP10fopAc_ac_cUsUs(void);
void fopAcM_orderChangeEventId__FP10fopAc_ac_csUsUs(void);
void fopAcM_orderDoorEvent__FP10fopAc_ac_cP10fopAc_ac_cUsUs(void);
void fopAcM_orderItemEvent__FP10fopAc_ac_cUsUs(void);
void fopAcM_orderMapToolAutoNextEvent__FP10fopAc_ac_cUcsUsUsUs(void);
void fopAcM_orderMapToolEvent__FP10fopAc_ac_cUcsUsUsUs(void);
void fopAcM_orderOtherEvent__FP10fopAc_ac_cPCcUsUsUs(void);
void fopAcM_orderOtherEventId__FP10fopAc_ac_csUcUsUsUs(void);
void fopAcM_orderOtherEvent__FP10fopAc_ac_cP10fopAc_ac_cPCcUsUsUs(void);
void fopAcM_orderSpeakEvent__FP10fopAc_ac_cUsUs(void);
void fopAcM_orderTalkEvent__FP10fopAc_ac_cP10fopAc_ac_cUsUs(void);
void fopAcM_orderTalkItemBtnEvent__FUsP10fopAc_ac_cP10fopAc_ac_cUsUs(void);
void fopAcM_orderTreasureEvent__FP10fopAc_ac_cP10fopAc_ac_cUsUs(void);
void fopAcM_posMove__FP10fopAc_ac_cPC4cXyz(void);
void fopAcM_posMoveF__FP10fopAc_ac_cPC4cXyz(void);
void fopAcM_searchActorAngleY__FPC10fopAc_ac_cPC10fopAc_ac_c(void);
void fopAcM_searchActorDistance__FPC10fopAc_ac_cPC10fopAc_ac_c(void);
void fopAcM_searchActorDistanceXZ__FPC10fopAc_ac_cPC10fopAc_ac_c(void);
void fopAcM_searchActorDistanceXZ2__FPC10fopAc_ac_cPC10fopAc_ac_c(void);
void fopAcM_searchFromName__FPCcUlUl(void);
void fopAcM_searchFromName4Event__FPCcs(void);
void fopAcM_seenActorAngleY__FPC10fopAc_ac_cPC10fopAc_ac_c(void);
void fopAcM_setCarryNow__FP10fopAc_ac_ci(void);
void fopAcM_setCullSizeBox__FP10fopAc_ac_cffffff(void);
void fopAcM_setEffectMtx__FPC10fopAc_ac_cPC12J3DModelData(void);
void fopAcM_setRoomLayer__FPvi(void);
void fopAcM_setStageLayer__FPv(void);
void waterCheck__11fopAcM_wt_cFPC4cXyz(void);
void fpoAcM_relativePos__FPC10fopAc_ac_cPC4cXyzP4cXyz(void);
void fopAcM_SearchByName__FsPP10fopAc_ac_c(void);
void fopAcM_createChildFromOffset__FsUiUlPC4cXyziPC5csXyzPC4cXyzScPFPv_i(void);
void fopAcM_SetMin__FP10fopAc_ac_cfff(void);
void fopAcM_SetMax__FP10fopAc_ac_cfff(void);
void fopAcM_setCullSizeSphere__FP10fopAc_ac_cffff(void);
void fopAcM_setCullSizeBox2__FP10fopAc_ac_cP12J3DModelData(void);
void fopAcM_addAngleY__FP10fopAc_ac_css(void);
void fopAcM_searchActorAngleX__FPC10fopAc_ac_cPC10fopAc_ac_c(void);
void fopAcM_searchActorDistance2__FPC10fopAc_ac_cPC10fopAc_ac_c(void);
void fopAcM_rollPlayerCrash__FPC10fopAc_ac_cfUlffif(void);
void fopAcM_checkCullingBox__FPA4_fffffff(void);
void fopAcM_orderPotentialEvent__FP10fopAc_ac_cUsUsUs(void);
void fopAcM_createItemFromEnemyID__FUcPC4cXyziiPC5csXyzPC4cXyzPfPf(void);
void fopAcM_createItemForBoss__FPC4cXyziiPC5csXyzPC4cXyzffi(void);
void fopAcM_createItemForMidBoss__FPC4cXyziiPC5csXyzPC4cXyzii(void);
void fopAcM_createBokkuri__FUsPC4cXyziiiPC4cXyzii(void);
void fopAcM_createWarpHole__FPC4cXyzPC5csXyziUcUcUc(void);
void fopAcM_myRoomSearchEnemy__FSc(void);
void fopAcM_createDisappear__FPC10fopAc_ac_cPC4cXyzUcUcUc(void);
void fopAcM_otoCheck__FPC10fopAc_ac_cf(void);
void fopAcM_otherBgCheck__FPC10fopAc_ac_cPC10fopAc_ac_c(void);
void fopAcM_wayBgCheck__FPC10fopAc_ac_cff(void);
void fopAcM_plAngleCheck__FPC10fopAc_ac_cs(void);
void fopAcM_effSmokeSet1__FPUlPUlPC4cXyzPC5csXyzfPC12dKy_tevstr_ci(void);
void fopAcM_riverStream__FP4cXyzPsPff(void);
void fopAcM_carryOffRevise__FP10fopAc_ac_c(void);
void fopAcM_searchFromName4Event__FPCcs(void);
void fopAcM_GetName__FPv(void);  // mostly inlined
void fopAcM_GetID__FPCv(void);   // mostly inlined
}

#endif
