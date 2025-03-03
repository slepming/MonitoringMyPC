#include "monitoringCom.hpp"
#include "terminalCommandExecute.cpp"
#include <json/value.h>
#include <string>

Json::Value connect_with_command(){
  char command[64] = "amdgpu_top -J -d";
  ExecutionCommand execCommand;
  std::string executeResult = execCommand.exec(command);
  monitoring monitoring;
  return monitoring.JsonConvert(&executeResult)[0];
}

std::string monitoring::get_metrics_gpu_device_name(){
  Json::Value full_json = connect_with_command();
  return full_json["DeviceName"].asString();
}

int monitoring::get_metrics_gpu_temp(){
  Json::Value full_json = connect_with_command();
  return full_json["Sensors"]["Edge Temperature"]["value"].asInt();
}

int monitoring::get_metrics_gpu_memory_load(){
  Json::Value full_json = connect_with_command();
  return full_json["VRAM"]["Total VRAM Usage"]["value"].asInt();
}

int monitoring::get_metrics_gpu_memory_full(){
  Json::Value full_json = connect_with_command();
  return full_json["VRAM"]["Total VRAM"]["value"].asInt();
}

int monitoring::get_metrics_gpu_activity(){
  Json::Value full_json = connect_with_command();
  return full_json["gpu_activity"]["GFX"]["value"].asInt();
}

Json::Value monitoring::get_gpu_MHZ(){
  Json::Value full_json = connect_with_command();
  Json::Value result;
  result["GFX_MCLK"] = full_json["Sensors"][ToString(GFX_MCLK)]["value"]; 
  result["GFX_SCLK"] = full_json["Sensors"][ToString(GFX_SCLK)]["value"]; 
  return result;
}


