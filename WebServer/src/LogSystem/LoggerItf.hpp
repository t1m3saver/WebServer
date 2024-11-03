#include <string>
#define LOG_INFO(LOGGER, information) LOGGER.Log(information, LogLevel::INFO)
#define LOG_DEBUG(LOGGER, information) LOGGER.Log(information, LogLevel::DEBUG) 
#define LOG_WARN(LOGGER, information) LOGGER.Log(information, LogLevel::WARN) 
#define LOG_ERROR(LOGGER, information) LOGGER.Log(information, LogLevel::ERROR) 

namespace WebServer::Log {
enum class LogLevel{
    DEBUG = 0,
    INFO,
    WARN,
    ERROR
};
class LoggerItf{
public:
    virtual ~LoggerItf() = default;
    virtual void Log(const std::string& messange, LogLevel logLevel) = 0;
};

}