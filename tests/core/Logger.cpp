#include <catch.hpp>
#include <core/Logger.h>
#include <iostream>

//TODO Use the lib way to run tearDown
namespace LoggerTest {
    void tearDown() {
        Logger::destroyInstance();
    }
}

TEST_CASE("Check Logger debug") {
    auto logger = Logger::createInstance();
    Logger::getInstance().lock()->Debug("MSG");
    REQUIRE(logger.lock()->readBuffer() == "[DEBUG] MSG\n");
    logger.lock()->cleanBuffer();

    DEBUG_LOG("MSG " << 1);
    REQUIRE(logger.lock()->readBuffer() == "[DEBUG] MSG 1\n");
    LoggerTest::tearDown();
}

TEST_CASE("Check Logger info") {
    auto logger = Logger::createInstance();
    Logger::getInstance().lock()->Info("MSG");
    REQUIRE(logger.lock()->readBuffer() == "[INFO] MSG\n");
    logger.lock()->cleanBuffer();

    INFO_LOG("MSG " << 1);
    REQUIRE(logger.lock()->readBuffer() == "[INFO] MSG 1\n");
    LoggerTest::tearDown();
}

TEST_CASE("Check Logger warning") {
    auto logger = Logger::createInstance();
    Logger::getInstance().lock()->Warning("MSG");
    REQUIRE(logger.lock()->readBuffer() == "[WARN] MSG\n");
    logger.lock()->cleanBuffer();

    WARN_LOG("MSG " << 1);
    REQUIRE(logger.lock()->readBuffer() == "[WARN] MSG 1\n");
    LoggerTest::tearDown();
}

TEST_CASE("Check Logger error") {
    auto logger = Logger::createInstance();
    Logger::getInstance().lock()->Error("MSG");
    REQUIRE(logger.lock()->readBuffer() == "[ERROR] MSG\n");
    logger.lock()->cleanBuffer();

    ERROR_LOG("MSG " << 1);
    REQUIRE(logger.lock()->readBuffer() == "[ERROR] MSG 1\n");
    LoggerTest::tearDown();
}

TEST_CASE("writeToBuffer must store not more then n lines where n is Logger::_maxNLinesInBuffer ") {
    int logsBufferSizeInLines = 20;
    auto logger = Logger::createInstance();
    int i = 50;
    while(--i) Logger::getInstance().lock()->Error("MSG");
    auto buffer = Logger::getInstance().lock()->readBuffer();
    auto returns = std::count_if(buffer.begin(), buffer.end(), [&](char c) { return (c == '\n'); });
    REQUIRE(returns == logsBufferSizeInLines -1);
    LoggerTest::tearDown();
}
