#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <iomanip>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

void LinuxParser::removeSubstring(std::string& mainString, const std::string& substringToRemove) {
    // Find the position of the substring in the main string
    size_t pos = mainString.find(substringToRemove);

    // Check if the substring is found
    if (pos != std::string::npos) {
        // Erase the substring from the main string
        mainString.erase(pos, substringToRemove.length());
    }
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {   
  string line;
  string key;
  string value;
  long totalMemory = -1;
  long availableMemory = -1;
  float utilizationPercent = -1.0;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      line.erase(std::remove(line.begin(), line.end(), ' '),line.end());
      std::replace(line.begin(), line.end(), ':', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") {
          LinuxParser::removeSubstring(value, "kB");
          if (std::all_of(value.begin(), value.end(), isdigit)) {
            totalMemory = std::stoi(value);
          }
        }        
        if (key == "MemAvailable") {
          LinuxParser::removeSubstring(value, "kB");
          if (std::all_of(value.begin(), value.end(), isdigit)) {
            availableMemory = std::stoi(value);
          }
        }
        if (totalMemory != -1 && availableMemory != -1){
          utilizationPercent = (float(totalMemory - availableMemory)/totalMemory) ; 
          return utilizationPercent;
        }
      }
    }
  }
  return utilizationPercent; 
}

// TODO: Read and return the system uptime
long int LinuxParser::UpTime() { 
  long int uptime;
  double idleTime;
  std::ifstream uptimeFile("/proc/uptime");
  if (uptimeFile.is_open()) {
      std::string line;
      std::getline(uptimeFile, line);
      std::istringstream iss(line);
      
      iss >> uptime >> idleTime;
      uptimeFile.close();
  } 
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> usageData;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
      std::string line;
      std::getline(filestream, line);
      std::istringstream iss(line);
      // removeSubstring(iss, "cpu");
      string num;
      while (iss >> num) {
        if(num!="cpu")
          usageData.push_back(num);
      }
      filestream.close();
    }
    return usageData;
  }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {   
  int totalProcesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::string line;
    while (std::getline(filestream, line)) {
      
      std::istringstream iss(line);
      string field;
      while (iss >> field) {
        if(field!="processes")
          break;
        iss>>totalProcesses;
        return totalProcesses;
      }
    }
  }
  return totalProcesses;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  int runningProcesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::string line;
    while (std::getline(filestream, line)) {
      std::istringstream iss(line);
      string field;
      while (iss >> field) {
        if(field!="procs_running")
          break;
        iss>>runningProcesses;
        return runningProcesses;
      }
    }
  }
  return runningProcesses;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::string line = " ";
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +  kCmdlineFilename);
  if (filestream.is_open()) {
    
    while (std::getline(filestream, line)) {
      return line;
    }
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {   
  string mem_util;
  int decimalPoints = 2;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    std::string line;
    while (std::getline(filestream, line)) {
      std::istringstream iss(line);
      string field;
      while (iss >> field) {
        if(field!="VmSize:")
          break;
        iss>>mem_util;
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(decimalPoints) << std::stof(mem_util)/1000;
        mem_util = oss.str();
        return mem_util;
      }
    }
  }
  return mem_util;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string uid;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    std::string line;
    while (std::getline(filestream, line)) {
      
      std::istringstream iss(line);
      string field;
      while (iss >> field) {
        if(field!="Uid:")
          break;
        iss>>uid;
        return uid;
      }
    }
  }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid=LinuxParser::Uid(pid);
  std::ifstream filestream("/etc/passwd");
  if (filestream.is_open()) {
    std::string line;
    while (std::getline(filestream, line)) {
      std::vector<std::string> elements;
      std::istringstream iss(line);
      std::string element;
      while (std::getline(iss, element, ':')) {
          elements.push_back(element);
      }
      if (elements[2] == uid){
        return elements[0];
      }
    }
  }
  return uid;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::UpTime(int pid) {
  vector<string> allStats =LinuxParser::CpuStats( pid);
  float hertz = sysconf(_SC_CLK_TCK);
  float uptime = std::stof(allStats[21]);
  int upTimePid = UpTime() - (uptime/hertz);
  return upTimePid;
}

vector<string> LinuxParser::CpuStats(int pid){
  vector<string> allStats;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
      std::string line;
      std::getline(filestream, line);
      std::istringstream iss(line);
      // removeSubstring(iss, "cpu");
      string num;
      while (iss >> num) {
        allStats.push_back(num);
      }
      filestream.close();
  }
  return allStats;
}


// int main(){
//   vector<string> a = LinuxParser::CpuUtilization();
//   for(auto i:a){
//     std::cout<<"Answere "<<i<<"\n";
//   }
//   // std::cout<<"Answer "<<a<<"\n";
// }