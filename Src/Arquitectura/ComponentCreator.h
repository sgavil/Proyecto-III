#pragma once
#include "EntityFactory.h"

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