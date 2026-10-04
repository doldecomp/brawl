// SHADOW of BrawlHeaders/so/sound/so_sound_3d_generator_accesser_impl.h: with FT_MODULE_BUILDER the GeneratorInstance layout is the
// real one (id + generator pointer, 8 bytes) and the DOL helper functions used by the fighter-side accesser are declared.
#pragma once

#include <StaticAssert.h>
#include <snd/snd_3d_generator.h>
#include <types.h>

class soSound3dGeneratorAccesser {
protected:
#ifdef FT_MODULE_BUILDER
    struct GeneratorInstance {
        int m_id;
        snd3DGenerator* m_soundGenerator;
        void initialize();
    };
    void allocateInstance(GeneratorInstance* inst, Vec3f* pos);
    void freeInstance(GeneratorInstance* inst);
#else
    struct GeneratorInstance {
        int m_0;
        snd3DGenerator m_soundGenerator;
    };
#endif

public:
#ifdef FT_MODULE_BUILDER
    virtual ~soSound3dGeneratorAccesser() { }
    virtual void activate(Vec3f* pos) = 0;
    virtual void deactivate() = 0;
#else
    virtual ~soSound3dGeneratorAccesser();
    virtual void activate(Vec3f* pos);
    virtual void deactivate();
#endif
#ifdef FT_MODULE_BUILDER
    virtual GeneratorInstance* getInstance(int idx) = 0;
#else
    virtual void getInstance();
#endif
};

class soSound3dGeneratorAccesserImpl : public soSound3dGeneratorAccesser {
    GeneratorInstance m_generatorInstance;

public:
    virtual ~soSound3dGeneratorAccesserImpl();
    virtual void activate(Vec3f* pos);
    virtual void deactivate();
    virtual GeneratorInstance* getInstance(int);
};
#ifndef FT_MODULE_BUILDER
static_assert(sizeof(soSound3dGeneratorAccesserImpl) == 16, "Class is wrong size!");
#endif