#pragma once
#include "EntityFactory.h"

// ·> Macro para el registro de factorías de componentes
#define REGISTER_TYPE(klass) \
    class klass##Creator : public BaseCreator { \
    public: \
        klass##Creator() \
        { \
            EntityFactory::registerType(#klass, this); \
        } \
       virtual Component* createComponent() const { \
            return new klass(); \
        } \
    }; \
    static klass##Creator global_##klass##Creator;