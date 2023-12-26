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

long int convertToLong(const std::string&  input){
    long int result = 0;
    if (!input.empty()){
        try{
            result = std::stol(input);
        }
        catch(const std::invalid_argument& e){
        }
        catch(const std::out_of_range& e){
        }
    }

    return result;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    int pid = Process::Pid();
    float cpuUsage = 0.0;
    vector<string> allStats = LinuxParser::CpuStats(pid);
    if (allStats.size() >= 22) {
        long int sysUpTime = LinuxParser::UpTime();
        long int utime = convertToLong(allStats[13]);
        long int stime = convertToLong(allStats[14]);
        long int cutime = convertToLong(allStats[15]);
        long int cstime = convertToLong(allStats[16]);
        long int starttime = convertToLong(allStats[21]);
        long hertz = sysconf(_SC_CLK_TCK);

        long int total_time = utime + stime + cutime + cstime;
        float seconds = sysUpTime - (starttime / hertz);
        cpuUsage = (seconds != 0) ? (total_time / static_cast<float>(hertz) / seconds) : 0.0;
    }
    return cpuUsage;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    int pid = Process::Pid();
    return LinuxParser::Command(pid); 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    int pid = Process::Pid();
    return LinuxParser::Ram( pid);
}

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