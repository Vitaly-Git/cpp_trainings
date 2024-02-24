#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

class Interval{
    public:
        int begin;
        int end;
        
        bool operator < (const Interval &intRight);
        bool isMerged(const Interval &intRight);
        std::string string();
};