#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>
#include "monitoringCom.hpp"



void gpu_mem_load_in_procent(int* load, int* full, int* variable){
  if (*load < 5 && *full == 0){
    *variable = 0;
    return;
  } 
  *variable = (*load) * 100 / (*full);
}

int main(void) {
  using namespace ftxui;
  std::string cpu_name;
  std::cout << "Введите наименование процессора из sensors: ";
  std::cin >> cpu_name;

  monitoring metrics;

  // Получение метрик для процессора
  int cpu_temp = std::stoi(metrics.get_metrics_cpu_temp(&cpu_name));
  int cpu_load = std::stoi(metrics.get_metrics_cpu_load());

  // Получение метрик для видеокарты/Графического ядра
  std::string gpuName = metrics.get_metrics_gpu_device_name();
  int gpuTemp = metrics.get_metrics_gpu_temp();
  int gpuActivity = metrics.get_metrics_gpu_activity();
  int gpuMemFull = metrics.get_metrics_gpu_memory_full();
  int gpuMemLoad = metrics.get_metrics_gpu_memory_load();
  Json::Value gpuMHZ = metrics.get_gpu_MHZ();
  
  // Вычисление процента gpuMemLoad от gpuMemFull
  int gpuMemLoadInProcent;
  if (gpuMemFull != 0) { 
    gpu_mem_load_in_procent(&gpuMemLoad, &gpuMemFull, &gpuMemLoadInProcent);
  }

  auto cell = [](const std::string t) { return text(t) | border;};
  auto ryzen = gridbox({ 
                          {window(text("Load"), text(std::to_string(cpu_load) + "%")), window(text("Temp"), text(std::to_string(cpu_temp) + " ℃"))}
  });
  auto gpu = gridbox({
    {window(text("Temp"),text(std::to_string(gpuTemp) + " ℃")), 
    window(text("VRAM load"), text(std::to_string(gpuMemLoadInProcent) + "%" + " : " + std::to_string(gpuMemLoad) + '/' + std::to_string(gpuMemFull))),
    window(text("GFX Activity"), text(std::to_string(gpuActivity) + "%")),
    window(text("Mhz"), gridbox({ 
      {
        window(text("GFX_MCLK"), text(gpuMHZ[ToString(GFX_MCLK)].asString() + " Mhz")),
        window(text("GFX_SCLK"), text(gpuMHZ[ToString(GFX_SCLK)].asString() + " Mhz"))
      } 
      }))}
  });
  auto ryzenWindow = window(text(metrics.get_cpu_name()), ryzen);
  auto rxWindow = window(text(gpuName), gpu);
  auto container = vbox(ryzenWindow, rxWindow);
 
  auto screen = Screen::Create(
    Dimension::Full(),
    Dimension::Fit(container)
  );
  Render(screen, container);
  screen.Print();
 
  return EXIT_SUCCESS;
}

