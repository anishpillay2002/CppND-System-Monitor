#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 float lastCpuUsagePct = 0.0;
 int lastCpuSum = 0;
 int lastCpuIdle = 0;
 std::vector<std::string> cpuStats;
};

#endif