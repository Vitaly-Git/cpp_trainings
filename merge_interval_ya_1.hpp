#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Interval.hpp"


void merger_vector_intervals_start();

std::vector <Interval> merger_vector_intervals(std::vector <Interval> srcVector);

template <typename T>
void containerOut(T container);

std::string vectorToStr(std::vector <Interval> container);