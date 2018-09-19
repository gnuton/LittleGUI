#ifndef LITTLEGUI_LOGGER_H
#define LITTLEGUI_LOGGER_H

#include "Singleton.h"

class Logger: public Singleton<Logger> {
    friend class Singleton<Logger>;
    Logger();

public:
    virtual ~Logger();
    static void TerminateLogger();
    std::string readLogs();

};


#endif //LITTLEGUI_LOGGER_H
