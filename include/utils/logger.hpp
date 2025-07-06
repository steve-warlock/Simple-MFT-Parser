#pragma once
#include <fstream>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace logger {

class Logger {
  private:
  std::string logPath; 
  std::ofstream write;
  public:
  Logger(const std::string& fileName); 
  ~Logger();
  void log(const std::string& message);

};

}
