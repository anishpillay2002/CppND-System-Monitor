#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
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
            removeSubstring(value, "kB");
            if (std::all_of(value.begin(), value.end(), isdigit)) {
                totalMemory = std::stoi(value);
            }
            }        
            if (key == "MemAvailable") {
            removeSubstring(value, "kB");
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