#include "LoggerItf.hpp"
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <mutex>

namespace  WebServer::Log {
class FileLogger : public LoggerItf {
public:
    static FileLogger& getInstance(const){

    }
    void Log(const std::string& message, LogLevel logLevel = LogLevel::INFO) override {
        std::lock_guard<std::mutex> lock(mutex_);
        if (log_file_.is_open()) {
            std::string timestamp = GetCurrentTime();
            log_file_ << timestamp << "[" << LogLevelToString(logLevel) << "]" << message << std::endl;
            log_file_.flush();
        }
    }
private:
    FileLogger(const std::string& filename) : filename_(filename) {
        log_file_.open(filename_, std::ios::app);
    }

    ~FileLogger() {
        if (log_file_.is_open()) {
            log_file_.close();
        }
    }


    std::string GetCurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm* local_time = std::localtime(&now);

        std::ostringstream oss;
        oss << "[" 
            << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") 
            << "]";

        return oss.str();
    }
    std::string LogLevelToString(LogLevel logLevel){
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

}