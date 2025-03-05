#include "monitoringCom.hpp"
#include <cstdlib>
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <stdexcept>
#include <string>
#include "terminalCommandExecute.cpp"

std::string monitoring::get_metrics_cpu_temp(std::string* cpu_name){
  ExecutionCommand execution;
  std::string fullJson = execution.exec("sensors -j");
  if (fullJson == "") std::runtime_error("execution.exec() failed!");
  Json::Value root = JsonConvert(&fullJson);
  return root[cpu_name->size() > 5 ? *cpu_name : "k10temp-pci-00c3"]["Tctl"]["temp1_input"].asString();
}
std::string monitoring::get_metrics_cpu_load(){
  ExecutionCommand execution;
  std::string fullJson = execution.exec("mpstat -o JSON");
  Json::Value root = JsonConvert(&fullJson);
  double usr = root["sysstat"]["hosts"][0]["statistics"][0]["cpu-load"][0]["usr"].asDouble();
  double sys = root["sysstat"]["hosts"][0]["statistics"][0]["cpu-load"][0]["sys"].asDouble();
  double iowait = root["sysstat"]["hosts"][0]["statistics"][0]["cpu-load"][0]["iowait"].asDouble();
  double irq = root["sysstat"]["hosts"][0]["statistics"][0]["cpu-load"][0]["irq"].asDouble();
  double soft = root["sysstat"]["hosts"][0]["statistics"][0]["cpu-load"][0]["soft"].asDouble();
  double result = usr + sys + iowait + irq + soft;
  return std::to_string(result);
}
std::string monitoring::get_cpu_name(){
  ExecutionCommand execution;
  std::string fullJson = execution.exec("lscpu -J");
  Json::Value root = JsonConvert(&fullJson);
  return root["lscpu"][7]["data"].asString();
}
