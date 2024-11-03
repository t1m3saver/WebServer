#include "LoggerItf.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace WebServer::Log {
class BasicLogger : public LoggerItf{
public:
    BasicLogger(const std::string& prefix_) : prefix(prefix_) {}

    void Log(const std::string& message) override {
        std::string timestamp = GetCurrentTime();
        std::cout << timestamp << " " << prefix << message << std::endl;
    }

private:
    std::string GetCurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm* local_time = std::localtime(&now);

        std::ostringstream oss;
        oss << "[" 
            << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") 
            << "]";

        return oss.str();
}
private:
    std::string prefix;
};
}