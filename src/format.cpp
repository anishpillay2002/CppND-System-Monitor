#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int h = seconds/3600;
    int m = (seconds%3600)/60;
    string s = std::to_string( seconds%60);
    s = s.insert(0, 2 - s.length(), '0');
    string output = std::to_string(h)+":"+std::to_string(m)+":"+s;
    return output; 
}