#ifndef MONITORING_COMPONENT
#define MONITORING_COMPONENT
#include <json/reader.h>
#include <json/value.h>
#include <string>

class monitoring{
  public:
  std::string get_metrics_cpu_temp();
  std::string get_metrics_cpu_load();

  // gpu
  int get_metrics_gpu_temp();
  int get_metrics_gpu_activity();
  int get_metrics_gpu_memory_full();
  int get_metrics_gpu_memory_load();
  std::string get_metrics_gpu_device_name();
  Json::Value get_gpu_MHZ();

  Json::Value JsonConvert(std::string* content){
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(content->c_str(), root);
    if (!parsingSuccessful) std::runtime_error("reader.parse() failed!");
    return root;
  } 
};

enum Mhz{
  GFX_MCLK,
  GFX_SCLK
};

inline const char* ToString(Mhz value){
  switch (value){
    case GFX_MCLK: return "GFX_MCLK";
    case GFX_SCLK: return "GFX_SCLK";
    default: return "None";
  }
}

#endif // !MONITORING_COMPONENT
