#pragma once
#include <fstream>
#include <mutex>
#include <string>
#include <iostream>

#include <ctime>
#include <iomanip>
#include <sstream>

namespace Core {
    class Logger {
    private:
        static std::string GetTimestamp() {
            auto now = std::time(nullptr);
            struct tm tm;
            localtime_s(&tm, &now);
            std::ostringstream oss;
            oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
            return oss.str();
        }

        static void WriteToFile(const std::string& message) {
            static std::mutex mtx;
            std::lock_guard<std::mutex> lock(mtx);
            std::ofstream logFile("proxy.log", std::ios::app);
            if (logFile.is_open()) {
                logFile << message << "\n";
            }
        }

    public:
        static void Log(const std::string& message) {
            WriteToFile("[" + GetTimestamp() + "] " + message);
        }

        static void Error(const std::string& message) {
            WriteToFile("[" + GetTimestamp() + "] [错误] " + message);
        }

        static void Info(const std::string& message) {
            WriteToFile("[" + GetTimestamp() + "] [信息] " + message);
        }

        static void Warn(const std::string& message) {
            WriteToFile("[" + GetTimestamp() + "] [警告] " + message);
        }

        static void Debug(const std::string& message) {
            WriteToFile("[" + GetTimestamp() + "] [调试] " + message);
        }
    };
}
