#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <iostream>

using std::string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    Processor::cpuStats = LinuxParser::CpuUtilization();
    float cpuSum = 0;
    float deltaSum = 0.0;
    int cpuIdle = 0;
    int deltaCpuIdle = 0;
    float cpuUsagePct = 0.0;
    for(auto& n:cpuStats){
        cpuSum+=std::stoi(n);
    }
    
    deltaSum = cpuSum - lastCpuSum;
    cpuIdle = std::stoi(cpuStats[3]);
    deltaCpuIdle = cpuIdle - lastCpuIdle;
    float deltaCpuUsed = deltaSum - deltaCpuIdle;
    if (deltaSum==0){
        deltaSum = 0.1;
    }
    cpuUsagePct = (deltaCpuUsed/deltaSum);
    Processor::lastCpuIdle = cpuIdle;
    Processor::lastCpuSum = cpuSum;
    Processor::lastCpuUsagePct = cpuUsagePct;

    return cpuUsagePct; 
}

// int main(){
//     float cpuPct = Processor().Utilization();
//     // for(auto i:a){
//     //     std::cout<<"Answere "<<i<<"\n";
//     // }
//     std::cout<<"Answer "<<cpuPct<<"\n";
// }