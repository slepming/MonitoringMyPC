#include <iostream>
#include <stdexcept>
#include <stdio.h>

class ExecutionCommand{
public:
  std::string exec(const char* cmd){
    char buffer[1024];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try{
      while (fgets(buffer, sizeof buffer, pipe) != NULL){
        result += buffer;
      }
    } catch(...){
      pclose(pipe);
      throw;
    }
    pclose(pipe);
    return result;
  }
};
