#include "merge_interval_ya_1.hpp"


void merger_vector_intervals_start(){

    std::vector <Interval> srcVector = {{2,6},{7,8},{1,3},{8,10}};

    std::cout << "src vector: " << vectorToStr(srcVector) << std::endl;

    std::vector <Interval> resultVector = merger_vector_intervals(srcVector);

    std::cout << "src vector after merge: " << vectorToStr(srcVector) << std::endl;

    std::cout << "merget vector" << vectorToStr(resultVector) << std::endl;

}

std::vector <Interval> merger_vector_intervals(std::vector<Interval> srcVector){

    std::vector <Interval> resultVector(0);

    if (srcVector.size() == 0)
        return srcVector;
    
    std::sort(srcVector.begin(), srcVector.end());
    std::cout << "src vector after sort: " << vectorToStr(srcVector) << std::endl;

    resultVector.push_back(srcVector[0]);
    
    int resultIndex = 0;
    for (auto it = srcVector.begin(); it != srcVector.end(); ++it){

        if (resultVector[resultIndex].isMerged(*it)){
            resultVector[resultIndex].begin = std::min(resultVector[resultIndex].begin, it->begin);
            resultVector[resultIndex].end = std::max(resultVector[resultIndex].end, it->end);
        } else {
            ++resultIndex;
            resultVector.push_back(*it);
        }

    }
    return resultVector;
}

template <typename T>
void containerOut(T container){
    for(auto it : container){
        if (it != container.begin())
            std::cout << " ";
        std::cout << *it;
    }
}

std::string vectorToStr(std::vector <Interval> container){
    std::string resultStr;
    for(auto it=container.begin(); it!=container.end(); ++it){
         if (it != container.begin())
             resultStr = resultStr + " ";
         resultStr = resultStr + it->string();
    }
    return resultStr;
}