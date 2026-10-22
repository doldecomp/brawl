#pragma once

#include <StaticAssert.h>
#include <GX.h>
#include <mt/mt_vector.h>
#include <nw4r/g3d/g3d_rescommon.h>
#include <nw4r/g3d/g3d_restex.h>
#include <types.h>

namespace nw4r {
    namespace g3d {
    
// Forward declarations
class ResFile;

        struct ResTexSrtData {
            union {
                struct {
                    int _pad : 25;
                    bool m_flag6 : 1; // & 0x40
                    bool m_flag5 : 1; // & 0x20
                    bool m_flag4 : 1; // & 0x10
                    bool m_flag3 : 1; // & 8
                    bool m_flag2 : 1; // & 4
                    bool m_flag1 : 1; // & 2
                    bool m_flag0 : 1; // & 1
                };
                u32 m_flags;
            };
            char _4[4];
            Vec2f m_range;
            char _16[4];
            Vec2f m_pos;
            char _28[560];
        };

        class ResTexSrt : public ResCommon<ResTexSrtData> {
        public:
            inline ResTexSrt(void* data) : ResCommon(data) {}

            bool SetMapMode(u32, u32, int, int);
        };


        struct ResTexObjData {
            int _0;
            GXTexObj m_texObjs[8];
        };

        class ResTexObj : public ResCommon<ResTexObjData> {
        public:
            inline ResTexObj(void* data) : ResCommon(data) {}

            GXTexObj* GetTexObj(GXTexMapID);
        };

        struct GenModeData {
            u8 m_numTexGens;
            u8 m_numLightChans;
            u8 m_activeTevStages;
            u8 m_numIndTexStages;
        };
        struct MiscData {
            u8 m_depthTestBeforeTexture;
            s8 m_lightSet;
            s8 m_fogSet;
            u8 m_pad;
            u8 m_indirectMethod1;
            u8 m_indirectMethod2;
            u8 m_indirectMethod3;
            u8 m_indirectMethod4;
            s8 m_normMapRefLight1;
            s8 m_normMapRefLight2;
            s8 m_normMapRefLight3;
            s8 m_normMapRefLight4;
        };

        struct ResMatData {
            u32 m_size;
            s32 m_offToMdl;
            s32 m_name;
            u32 m_id;
            u32 m_flags;

            GenModeData m_genData;
            MiscData m_misc;

            s32 m_offToShaders;
            u32 m_numTextures;
            s32 m_offToMatRefs;

            s32 m_offToFurData;
            s32 m_offToUserDataoffToUserData;
            s32 m_offToDisplayLists;

            ResTexObjData m_resTexObjData;

            char _320[100];

            ResTexSrtData m_resTexSrtData;


        };
        static_assert(sizeof(ResMatData) == 1008, "Class is wrong size!");
        // there may be more after this? Check the file format. This is just to verify that offsets are correct
        // Needs verification

        struct ResTevColorDL {
            union {
                struct
                {
                    u8 m_tevColor[3][20];
                    u8 _padding[4];
                    u8 m_tevKColor[4][10];
                    u8 _padding2[0x18];
                } dl;
                u8 data[0x80];
            };
        };

        class ResMatTevColor : public ResCommon<ResTevColorDL> {
        private:
        public:
            void GXSetTevColor(u32 id, GXColor color);
        };

        class ResMat : public ResCommon<ResMatData> {
        public:
            inline ResMat() : ResCommon() {}
            inline ResMat(void* data) : ResCommon(data) {}

            void Bind(const nw4r::g3d::ResFile file);
            void Release();
            void ForceBindTex(ResTex,const char*);
            void DCStore(bool sync);
        };
    } // namespace g3d
} // namespace nw4r
