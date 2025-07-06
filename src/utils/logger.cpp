#include "../../include/utils/logger.hpp"

namespace logger {
  Logger::Logger(const std::string& fileName) { 
    this -> logPath = fs::path(fs::current_path().parent_path() / "logs" / fileName).string();
    this -> write.open(this -> logPath, std::ios::trunc);
    
    if(!this -> write.is_open()) {
      std::cerr << "Error: Unable to open log file: " << this -> logPath << "\n";
                   exit(1);
    }
  }
  
  Logger::~Logger() {
    if (this -> write.is_open()) {
        this -> write.close();
    }
  }

  void Logger::log(const std::string& message) {
    // Get current timestamp
    std::time_t now = std::time(nullptr);
    char timeBuffer[20];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    
    // Write timestamp and message in the file
    this -> write << "[" << timeBuffer << "]" << message << '\n';
    this -> write.flush();
  }
  
}
