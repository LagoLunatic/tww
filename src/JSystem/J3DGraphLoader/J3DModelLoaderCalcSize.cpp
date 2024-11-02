//
// Generated by dtk
// Translation Unit: J3DModelLoaderCalcSize.cpp
//

#include "JSystem/J3DGraphLoader/J3DModelLoaderCalcSize.h"
#include "JSystem/J3DGraphLoader/J3DMaterialFactory.h"
#include "JSystem/J3DGraphLoader/J3DMaterialFactory_v21.h"
#include "JSystem/J3DGraphLoader/J3DShapeFactory.h"
#include "JSystem/J3DGraphLoader/J3DJointFactory.h"
#include "JSystem/JSupport/JSupport.h"
#include "dolphin/os/OS.h"

/* 802FD828-802FD868       .text countMaterialNum__14J3DModelLoaderFPCv */
u16 J3DModelLoader::countMaterialNum(const void* i_data) {
    const JUTDataFileHeader* header = (const JUTDataFileHeader*)i_data;
    const JUTDataBlockHeader* block = &header->mFirstBlock;
    for (int i = 0; i < header->mBlockNum; block = block->getNext(), i++) {
        if (block->mType == 'MAT3') {
            return ((const J3DMaterialBlock*)block)->mMaterialNum;
        }
    }
    return 0;
}

/* 802FD868-802FDA10       .text calcLoadSize__14J3DModelLoaderFPCvUl */
u32 J3DModelLoader::calcLoadSize(const void* i_data, u32 i_flags) {
    u32 flags;
    u32 size = 0;
    const JUTDataFileHeader* header = (const JUTDataFileHeader*)i_data;
    const JUTDataBlockHeader* block = &header->mFirstBlock;
    u32 i = 0;
    flags = (u32)i_flags;
    size += sizeof(J3DModelData);
    for (; i < header->mBlockNum; i++) {
        switch (block->mType) {
        case 'INF1':
            size += calcSizeInformation((J3DModelInfoBlock*)block, flags);
            break;
        case 'JNT1':
            size += calcSizeJoint((J3DJointBlock*)block);
            break;
        case 'MAT2':
            break;
        case 'MAT3':
            size += calcSizeMaterial((J3DMaterialBlock*)block, flags);
            break;
        case 'SHP1':
            size += calcSizeShape((J3DShapeBlock*)block, flags);
            break;
        case 'TEX1':
            size += calcSizeTexture((J3DTextureBlock*)block);
            break;
        case 'EVP1':
            break;
        case 'DRW1':
            break;
        case 'VTX1':
            break;
        default:
            OSReport("Unknown data block\n");
            break;
        }
        block = block->getNext();
    }
    return size;
}

/* 802FDA10-802FDB0C       .text calcLoadMaterialTableSize__14J3DModelLoaderFPCv */
u32 J3DModelLoader::calcLoadMaterialTableSize(const void* i_data) {
    u32 size = 0;
    const JUTDataFileHeader* header = (const JUTDataFileHeader*)i_data;
    const JUTDataBlockHeader* block = &header->mFirstBlock;
    bool hasTextureTable = false;
    u32 i = 0;
    size += sizeof(J3DMaterialTable);
    for (; i < header->mBlockNum; i++) {
        switch (block->mType) {
        case 'MAT2':
            break;
        case 'MAT3':
            size += calcSizeMaterialTable((const J3DMaterialBlock*)block, 0x51100000);
            break;
        case 'TEX1':
            size += calcSizeTextureTable((const J3DTextureBlock*)block);
            hasTextureTable = true;
            break;
        default:
            OSReport("Unknown data block\n");
            break;
        }
        block = block->getNext();
    }

    if (!hasTextureTable) {
        size += 0xC;
    }
    return size;
}

/* 802FDB0C-802FDD28       .text calcLoadBinaryDisplayListSize__14J3DModelLoaderFPCvUl */
u32 J3DModelLoader::calcLoadBinaryDisplayListSize(const void* i_data, u32 i_flags) {
    u32 size = 0;
    const JUTDataFileHeader* header = (const JUTDataFileHeader*)i_data;
    const JUTDataBlockHeader* block = &header->mFirstBlock;
    u32 i = 0;
    size += sizeof(J3DModelData);
    for (; i < header->mBlockNum; i++) {
        switch (block->mType) {
        case 'INF1':
            size += calcSizeInformation((const J3DModelInfoBlock*)block, (u32)i_flags);
            break;
        case 'JNT1':
            size += calcSizeJoint((const J3DJointBlock*)block);
            break;
        case 'SHP1':
            size += calcSizeShape((const J3DShapeBlock*)block, (u32)i_flags);
            break;
        case 'TEX1':
            size += calcSizeTexture((const J3DTextureBlock*)block);
            break;
        case 'MDL3':
            size += calcSizeMaterialDL((const J3DMaterialDLBlock*)block, i_flags);
            break;
        case 'MAT2':
            break;
        case 'MAT3': {
            u32 matFlags = 0x50100000;
            matFlags |= (u32)i_flags & 0x03000000;
            mpMaterialBlock = (const J3DMaterialBlock*)block;
            u32 matType = getBdlFlag_MaterialType((u32)i_flags);
            if (matType == 0) {
                field_0x18 = 1;
                size += calcSizeMaterial((const J3DMaterialBlock*)block, matFlags);
            } else if (matType == 0x2000) {
                field_0x18 = 1;
                size += calcSizePatchedMaterial((const J3DMaterialBlock*)block, matFlags);
            }
            break;
        }
        case 'EVP1':
            break;
        case 'DRW1':
            break;
        case 'VTX1':
            break;
        default:
            OSReport("Unknown data block\n");
            break;
        }
        block = block->getNext();
    }
    return size;
}

/* 802FDD28-802FDDB4       .text calcSizeInformation__14J3DModelLoaderFPC17J3DModelInfoBlockUl */
u32 J3DModelLoader::calcSizeInformation(const J3DModelInfoBlock* i_block, u32 i_flags) {
    u32 size = 0;
    switch ((i_flags | i_block->mFlags) & 0xF) {
    case 0: // TODO: enum for mtxcalc type (and other load flags)
        size = sizeof(J3DMtxCalcBasic);
        break;
    case 1:
        size = sizeof(J3DMtxCalcSoftimage);
        break;
    case 2:
        size = sizeof(J3DMtxCalcMaya);
        break;
    default:
        break;
    }
    mpModelHierarchy = JSUConvertOffsetToPtr<J3DModelHierarchy>(i_block, i_block->mpHierarchy);
    return size;
}

/* 802FDDB4-802FDDE0       .text calcSizeJoint__14J3DModelLoaderFPC13J3DJointBlock */
u32 J3DModelLoader::calcSizeJoint(const J3DJointBlock* i_block) {
    u32 size = 0;
    if (i_block->mpNameTable) {
        size = 0x10;
    }
    size += i_block->mJointNum * sizeof(J3DJoint*);
    size += i_block->mJointNum * sizeof(J3DJoint);
    return size;
}

/* 802FDDE0-802FDECC       .text calcSizeMaterial__18J3DModelLoader_v26FPC16J3DMaterialBlockUl */
u32 J3DModelLoader_v26::calcSizeMaterial(const J3DMaterialBlock* i_block, u32 i_flags) {
    u32 size = 0;
    J3DMaterialFactory factory(*i_block);
    u32 count = i_block->mMaterialNum;
    u32 uniqueCount = factory.countUniqueMaterials();
    if (i_block->mpNameTable) {
        size = 0x10;
    }
    size += count * sizeof(J3DMaterial*);
    if (i_flags & 0x00200000) {
        size += ALIGN_NEXT(uniqueCount * sizeof(J3DMaterial), 0x20);
    }
    if (i_flags & 0x00200000) {
        for (u32 i = 0; i < uniqueCount; i++) {
            size += factory.calcSize(NULL, J3DMaterialFactory::MATERIAL_TYPE_NORMAL, i, i_flags);
        }
    }
    for (u32 i = 0; i < count; i++) {
        size += factory.calcSize(NULL, J3DMaterialFactory::MATERIAL_TYPE_NORMAL, i, i_flags);
    }
    return size;
}

/* 802FDECC-802FDF70       .text calcSizeShape__14J3DModelLoaderFPC13J3DShapeBlockUl */
u32 J3DModelLoader::calcSizeShape(const J3DShapeBlock* i_block, u32 i_flags) {
    u32 size = 0;
    J3DShapeFactory factory(*i_block);
    int count = i_block->mShapeNum;
    if (i_block->mpNameTable) {
        size = 0x10;
    }
    size += count * sizeof(J3DShape*);
    size += factory.calcSizeVcdVatCmdBuffer(count);
    for (J3DModelHierarchy* hierarchy = mpModelHierarchy; hierarchy->mType != 0; hierarchy = hierarchy + 1) {
        if (hierarchy->mType == 0x12) {
            size += factory.calcSize(hierarchy->mValue, i_flags);
        }
    }
    return size;
}

/* 802FDF70-802FDF8C       .text calcSizeTexture__14J3DModelLoaderFPC15J3DTextureBlock */
u32 J3DModelLoader::calcSizeTexture(const J3DTextureBlock* i_block) {
    u32 size = 0;
    if (i_block->mpNameTable) {
        size = 0x10;
    }
    return size + 0xC;
}

/* 802FDF8C-802FE01C       .text calcSizeMaterialTable__18J3DModelLoader_v26FPC16J3DMaterialBlockUl */
u32 J3DModelLoader_v26::calcSizeMaterialTable(const J3DMaterialBlock* i_block, u32 i_flags) {
    u32 size = 0;
    u32 count = i_block->mMaterialNum;
    J3DMaterialFactory factory(*i_block);
    if (i_block->mpNameTable) {
        size = 0x10;
    }
    size += count * sizeof(J3DMaterial*);
    for (u32 i = 0; (u16)i < count; i++) {
        size += factory.calcSize(NULL, J3DMaterialFactory::MATERIAL_TYPE_NORMAL, (u16)i, i_flags);
    }
    return size;
}

/* 802FE01C-802FE03C       .text calcSizeTextureTable__14J3DModelLoaderFPC15J3DTextureBlock */
u32 J3DModelLoader::calcSizeTextureTable(const J3DTextureBlock* i_block) {
    return calcSizeTexture(i_block);
}

/* 802FE03C-802FE0CC       .text calcSizePatchedMaterial__14J3DModelLoaderFPC16J3DMaterialBlockUl */
u32 J3DModelLoader::calcSizePatchedMaterial(const J3DMaterialBlock* i_block, u32 i_flags) {
    u32 size = 0;
    u32 count = i_block->mMaterialNum;
    J3DMaterialFactory factory(*i_block);
    if (i_block->mpNameTable) {
        size = 0x10;
    }
    size += count * sizeof(J3DMaterial*);
    for (u32 i = 0; (u16)i < count; i++) {
        size += factory.calcSize(NULL, J3DMaterialFactory::MATERIAL_TYPE_PATCHED, (u16)i, i_flags);
    }
    return size;
}

/* 802FE0CC-802FE1A4       .text calcSizeMaterialDL__14J3DModelLoaderFPC18J3DMaterialDLBlockUl */
u32 J3DModelLoader::calcSizeMaterialDL(const J3DMaterialDLBlock* i_block, u32 i_flags) {
    u32 size = 0;
    J3DMaterialFactory factory(*i_block);
    if (!field_0x18) {
        u32 count = i_block->mMaterialNum;
        if (i_block->mpNameTable) {
            size = 0x10;
        }
        size += count * sizeof(J3DLockedMaterial*);
        for (u32 i = 0; (u16)i < count; i++) {
            size += factory.calcSize(NULL, J3DMaterialFactory::MATERIAL_TYPE_LOCKED, (u16)i, (u32)i_flags);
        }
    } else {
        u32 count = i_block->mMaterialNum;
        for (u32 i = 0; (u16)i < count; i++) {
            size += factory.calcSize((J3DMaterial*)this, J3DMaterialFactory::MATERIAL_TYPE_LOCKED, (u16)i, i_flags);
        }
    }
    return size;
}
