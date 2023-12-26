#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return _pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    int pid = Process::Pid();
    vector<string> allStats = LinuxParser::CpuStats(pid);
    long int sysUpTime = LinuxParser::UpTime();
    long int utime = std::stol(allStats[13]);
    long int stime = std::stol(allStats[14]);
    long int cutime = std::stol(allStats[15]);
    long int cstime = std::stol(allStats[16]);
    long int starttime = std::stol(allStats[21]);
    long hertz = sysconf(_SC_CLK_TCK);

    long int total_time = utime + stime + cutime + cstime;
    float seconds = sysUpTime - (starttime / hertz);
    float cpuUsage = total_time / static_cast<float>(hertz) /seconds;
    // Process::setCpuUtil(cpuUsage);
    return cpuUsage;
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return _user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    int pid = Process::Pid();
    return LinuxParser::UpTime( pid);
 }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& other) const { 
    return _cpuUtil > other._cpuUtil; 
}


// int main(){
//   Process a = Process();
//   a.setPid(1);
//   a.setPid(1);
//   std::cout<<a.Pid()<<"\n";
//   std::cout<<a.CpuUtilization()<<"\n";
//   std::cout<<a.UpTime()<<"\n";
//   std::cout<<a.UpTime()<<"\n";
// }