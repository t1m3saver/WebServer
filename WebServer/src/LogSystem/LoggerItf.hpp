#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <mutex>
#include <map>
#include <iostream>
#include "../Utils/fs.hpp" // 假设这个头文件中有 readConfig 的定义
namespace WebServer{
#define LOG_INFO(information) WebServer::Log::FileLogger::instance().Log(information, WebServer::Log::LogLevel::INFO)
#define LOG_DEBUG(information) WebServer::Log::FileLogger::instance().Log(information, WebServer::Log::LogLevel::DEBUG) 
#define LOG_WARN(information) WebServer::Log::FileLogger::instance().Log(information, WebServer::Log::LogLevel::WARN) 
#define LOG_ERROR(information) WebServer::Log::FileLogger::instance().Log(information, WebServer::Log::LogLevel::ERROR) 
}
namespace WebServer::Log {
enum class LogLevel {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR
};

class LoggerItf {
public:
    virtual ~LoggerItf() = default;
    virtual void Log(const std::string& message, LogLevel logLevel = LogLevel::INFO) = 0; // 确保参数一致
};

class FileLogger : public LoggerItf {
public:
    FileLogger(const std::string& filename) : filename_(filename) {
        log_file_.open(filename_, std::ios::app);
    }

    ~FileLogger() override {
        if (log_file_.is_open()) {
            log_file_.close();
        }
    }

    void Log(const std::string& message, LogLevel logLevel = LogLevel::INFO) override {
        std::lock_guard<std::mutex> lock(mutex_);
        if (log_file_.is_open()) {
            std::string timestamp = GetCurrentTime();
            log_file_ << timestamp << "[" << LogLevelToString(logLevel) << "] " << message << std::endl;
            log_file_.flush();
        }
    }
    static FileLogger& instance() {
        static std::map<std::string, std::map<std::string, std::string>> configFile = utils::fs::readConfig();
        static FileLogger logger(configFile["logger"]["outputFile"]);
        return logger; // 返回静态实例
    }

private:
    std::string GetCurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm* local_time = std::localtime(&now);
        std::ostringstream oss;
        oss << "[" << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") << "]";
        return oss.str();
    }

    std::string LogLevelToString(LogLevel logLevel) {
        switch (logLevel) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARN: return "WARN";
            case LogLevel::ERROR: return "ERROR";
            default: return "INFO"; // 默认级别
        }
    }

private:
    std::string filename_;
    std::ofstream log_file_;
    std::mutex mutex_;
};

} // namespace WebServer::Log

