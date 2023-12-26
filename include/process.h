#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
    public:
    int Pid();                               // TODO: See src/process.cpp
    std::string User();                      // TODO: See src/process.cpp
    std::string Command();                   // TODO: See src/process.cpp
    float CpuUtilization();                  // TODO: See src/process.cpp
    std::string Ram();                       // TODO: See src/process.cpp
    long int UpTime();                       // TODO: See src/process.cpp
    bool operator<(Process const& a) const;  // TODO: See src/process.cpp
    float _cpuUtil;
    void setPid(int pid){
        _pid =pid;
    }
    void setUser(std::string user){
        _user =user;
    }
    void setCmd(std::string cmd){
        _cmd =cmd;
    }
    void setCpuUtil(float cpuUtil){
        _cpuUtil =cpuUtil;
    }
    void setRam(std::string ram){
        _ram =ram;
    }
    void setUpTime(long int upTime){
        _upTime =upTime;
    }
    
    // TODO: Declare any necessary private members
    private:
    int _pid;
    std::string _user;
    std::string _cmd;
    
    std::string _ram;
    long int _upTime;
};

#endif