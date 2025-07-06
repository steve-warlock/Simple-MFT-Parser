// command line parser
#include <CLI/CLI.hpp>

// std
#include <string>

#include "../include/mft_parser.hpp"

using namespace CLI;
using namespace std;

int main(int argc, char** argv){
  App app{"MFT to JSON converter.\n Made by Steve Warlock"};
  argv = app.ensure_utf8(argv);
  std::string filePath;
  std::string outputPath; // default one
  app.add_option("-p,--path", filePath, "MFT file to parse") -> required();
  app.add_option("-o,--output", outputPath, "MFT file to parse") -> default_val("./output/output.json");
  CLI11_PARSE(app, argc, argv);
  parser::MFTParser mft_parser(filePath, outputPath);
  return 0;
}
