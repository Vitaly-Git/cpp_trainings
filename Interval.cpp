#include "Interval.hpp"

bool Interval::operator < (const Interval &intRight){
    return begin < intRight.begin;
}

bool Interval::isMerged(const Interval &intRight){
    return (begin >= intRight.begin && begin <= intRight.end) ||
        (end >= intRight.begin && end <= intRight.end) ||
        (intRight.begin >= begin && intRight.begin <= end) ||
        (intRight.end >= begin && intRight.end <= end);
}

std::string Interval::string(){
    std::string resStr = "";
    resStr += "{" + std::to_string(this->begin) + " " + std::to_string(this->end) + "}";
    return resStr;
}