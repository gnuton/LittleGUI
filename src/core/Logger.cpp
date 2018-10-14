#include "Logger.h"


Logger::Logger() {
}

Logger::~Logger() {
}


void Logger::Log(LoggerFormat f, const std::string &msg) {
    std::string formattedMsg = FormatToStr[f] + msg + '\n';
    formattedMsg.resize(std::min(this->_maxNCharsPerLineInBuffer, static_cast<ushort>(formattedMsg.length())));
    writeToBuffer(formattedMsg);
    writeToTarget(formattedMsg);
}


void Logger::writeToBuffer(const std::string msg) {
    std::lock_guard<std::mutex> lock(_mtx);
    _logsBuffer.push_back(msg.c_str());
    if (_logsBuffer.size() >= _maxNLinesInBuffer)
        _logsBuffer.pop_front();
}
void Logger::writeToTarget(const std::string msg) {

}

const std::string Logger::readBuffer() {
    std::lock_guard<std::mutex> lock(_mtx);
    std::ostringstream s;
    for (auto line : _logsBuffer) {
        s << line;
    }
    return s.str();
}


void Logger::cleanBuffer() {
    _logsBuffer.clear();
}