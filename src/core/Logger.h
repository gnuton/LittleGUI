#ifndef LITTLEGUI_LOGGER_H
#define LITTLEGUI_LOGGER_H

#include <map>
#include "Singleton.h"
#include "Macros.h"
#include <sstream>
#include <list>
#include <mutex>

enum LoggerFormat { debug, info, warning, error };

#define FORMAT(ITEMS) ((static_cast<std::ostringstream &>(std::ostringstream().seekp( 0, std::ios_base::cur ) << ITEMS )).str())
#define DEBUG_LOG(ITEMS) (Logger::getInstance().lock()->Debug(FORMAT(ITEMS)))
#define INFO_LOG(ITEMS)  (Logger::getInstance().lock()->Info(FORMAT(ITEMS)))
#define WARN_LOG(ITEMS)  (Logger::getInstance().lock()->Warning(FORMAT(ITEMS)))
#define ERROR_LOG(ITEMS) (Logger::getInstance().lock()->Error(FORMAT(ITEMS)))


class Logger: public Singleton<Logger> {
    friend class Singleton<Logger>;
    NO_COPY_AND_ASSIGN(Logger);

protected:
    Logger();

public:
    virtual ~Logger();
    std::map<LoggerFormat, const char*> FormatToStr = {
        {LoggerFormat::debug, "[DEBUG] "},
        {LoggerFormat::info, "[INFO] "},
        {LoggerFormat::warning, "[WARN] "},
        {LoggerFormat::error, "[ERROR] "}};

    virtual void Log(LoggerFormat f, const std::string& msg);
    void Debug(const std::string& msg)   { this->Log(LoggerFormat::debug, msg); }
    void Info(const std::string& msg)    { this->Log(LoggerFormat::info, msg); }
    void Warning(const std::string& msg) { this->Log(LoggerFormat::warning, msg); }
    void Error(const std::string& msg)   { this->Log(LoggerFormat::error, msg); }

    const std::string readBuffer();
    void cleanBuffer();

private:
    void writeToBuffer(const std::string msg);
    void writeToTarget(const std::string msg);

    const ushort _maxNCharsPerLineInBuffer = 128;
    std::list<std::string> _logsBuffer;
    const ushort _maxNLinesInBuffer = 20; // TODO this may be hardware dependent. For now let's stick to something small.
    std::mutex _mtx;
};

#endif //LITTLEGUI_LOGGER_H
