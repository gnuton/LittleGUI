#include "Logger.h"


Logger::Logger() {
}

Logger::~Logger() {
}


void Logger::Log(LoggerFormat f, const std::string &msg) {
    std::string formattedMsg = FormatToStr[f] + msg + '\n';
    formattedMsg.resize(std::min(this->_maxBufferSize, static_cast<ushort>(formattedMsg.length())));
    writeToBuffer(formattedMsg);
}


void Logger::writeToBuffer(const std::string msg) {
    std::lock_guard<std::mutex> lock(_mtx);
    _logsBuffer.push_back(msg.c_str());
    if (_logsBuffer.size() >= _logsBufferSizeInLines)
        _logsBuffer.pop_front();
}


const std::string Logger::readBuffer() {
    std::lock_guard<std::mutex> lock(_mtx);
    std::ostringstream s;
    for (auto line : _logsBuffer) {
        s << line << '\n';
    }
    return s.str();
}


void Logger::cleanBuffer() {
    _logsBuffer.clear();
}