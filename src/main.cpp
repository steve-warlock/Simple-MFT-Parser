#include <nlohmann/json.hpp>
#include <CLI/CLI.hpp>
#include <string>
#include <iostream>
#include <format>
using json = nlohmann::json;
using namespace CLI;
using namespace std;

int main(int argc, char** argv){
  App app{"MFT to JSON converter.\n Made by Steve Warlock"};
  argv = app.ensure_utf8(argv);
  std::string filepath;
  std::string output; // default one
  app.add_option("-p,--path", filepath, "MFT file to parse") -> required();
  app.add_option("-o,--output", output, "MFT file to parse") -> default_val("output");
  CLI11_PARSE(app, argc, argv);
  return 0;
}
