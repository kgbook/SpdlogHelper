//
// Created by cory on 2023/11/11.
//

#include <stdarg.h>
#include "ALog.h"

#ifdef ENABLE_SPDLOG

#include "spdlog/logger.h"
#include "spdlog/fmt/bundled/printf.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define     LOG_FILE_NAME  "example.log"
#define     LOG_LEVEL_CONSOLE  SPDLOG_LEVEL_INFO

//#define     ENABLE_LOG_FILE
#ifdef ENABLE_LOG_FILE
#include "spdlog/sinks/rotating_file_sink.h"

#define     LOG_LEVEL_FILE     SPDLOG_LEVEL_WARN
#define     LOG_FILE_MAX_NUM    5
#define     KB      (1000)
#define     MB      (1000 * KB)
#endif

class ALOG {
public:
    static ALOG *getInstance();

    template<typename ... Args>
    void verbose(const char * fmt, const Args &... args) {
        logger_->trace(fmt::sprintf(fmt, args ...)); // NOLINT
        logger_->flush();
    }

    template<typename ... Args>
    void debug(const char *fmt, const Args &... args) {
        logger_->debug(fmt::sprintf(fmt, args ...)); // NOLINT
        logger_->flush();
    }

    template<typename ... Args>
    void info(const char *fmt, const Args &... args) {
        logger_->info(fmt::sprintf(fmt, args ...)); // NOLINT
        logger_->flush();
    }

    template<typename ... Args>
    void error(const char *fmt, const Args &... args) {
        logger_->error(fmt::sprintf(fmt, args ...)); // NOLINT
        logger_->flush();
    }

    template<typename ... Args>
    void warning(const char *fmt, const Args &... args) {
        logger_->warn(fmt::sprintf(fmt, args ...)); // NOLINT
        logger_->flush();
    }

    template<typename ... Args>
    void critical(const char *fmt, const Args &... args) {
        logger_->critical(fmt::sprintf(fmt, args ...)); // NOLINT
        logger_->flush();
    }

private:
    ALOG();
    ~ALOG();

    ALOG(ALOG &) = delete;
    ALOG &operator=(ALOG &) = delete;

private:
    std::shared_ptr<spdlog::logger> logger_;
};

ALOG::ALOG() : logger_(nullptr) {
    try {
        std::vector<spdlog::sink_ptr> sinks;
        spdlog::sink_ptr console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(static_cast<spdlog::level::level_enum>(LOG_LEVEL_CONSOLE)); // 默认串口日志等级为 debug, 避免送测抓取日志不全
        sinks.push_back(console_sink);
#ifdef ENABLE_LOG_FILE
        spdlog::sink_ptr file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(LOG_FILE_NAME, 10 * MB, LOG_FILE_MAX_NUM);
        file_sink->set_level(static_cast<spdlog::level::level_enum>(LOG_LEVEL_FILE));
        sinks.push_back(file_sink);
#endif
        logger_ = std::make_shared<spdlog::logger>(LOG_FILE_NAME, std::begin(sinks), std::end(sinks));
        logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e][pid%P][tid%t][%l]%v");
        logger_->set_level(static_cast<spdlog::level::level_enum>(LOG_LEVEL_CONSOLE));
        spdlog::register_logger(logger_);
    }
    catch (const spdlog::spdlog_ex &err) {
        const std::string reason = std::string("spdlog exception: ") + err.what();
        fprintf(stderr, "%s\n", reason.c_str());
    }
}

ALOG::~ALOG() {
    spdlog::drop_all();
}

ALOG *ALOG::getInstance() {
    static ALOG instance;
    return &instance;
}

void __ComLog(int level, const char *tag, const char *func, int line, const char* fmt, ...) {
    va_list ap;
    char buffer[4096];

    va_start(ap, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, ap);
    va_end(ap);

    switch (level) {
    case SPDLOG_LEVEL_TRACE: {
        ALOG::getInstance()->verbose("[%s][%s#%d]%s", tag, func, line, buffer);
        break;
    }
    case SPDLOG_LEVEL_DEBUG:{
        ALOG::getInstance()->debug("[%s][%s#%d]%s", tag, func, line, buffer);
        break;
    }
    case SPDLOG_LEVEL_INFO: {
        ALOG::getInstance()->info("[%s][%s#%d]%s", tag, func, line, buffer);
        break;
    }
    case SPDLOG_LEVEL_WARN: {
        ALOG::getInstance()->warning("[%s][%s#%d]%s", tag, func, line, buffer);
        break;
    }
    case SPDLOG_LEVEL_ERROR:{
        ALOG::getInstance()->error("[%s][%s#%d]%s", tag, func, line, buffer);
        break;
    }
    case SPDLOG_LEVEL_CRITICAL:{
        ALOG::getInstance()->critical("[%s][%s#%d]%s", tag, func, line, buffer);
        break;
    }
    case SPDLOG_LEVEL_OFF: break;
    }
}

#endif