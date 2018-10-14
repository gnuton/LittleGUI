#ifndef LITTLEGUI_GENERICTARGETCONFIG_H
#define LITTLEGUI_GENERICTARGETCONFIG_H

#include <string>

class GenericTargetConfig: public Singleton<GenericTargetConfig> {
    friend class Singleton<GenericTargetConfig>;
    NO_COPY_AND_ASSIGN(GenericTargetConfig);

protected:
    GenericTargetConfig();

public:
    virtual void log(const std::string msg) = 0;
};

#endif //LITTLEGUI_GENERICTARGETCONFIG_H
