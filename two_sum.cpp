#include "two_sum.hpp"

std::vector<int> Solution::twoSum(std::vector<int>& nums, int target){
    
    // std::vector<int> srcVec;
    // std::copy(nums.begin(), nums.end(), std::back_inserter(srcVec));
    // std::sort(nums.begin(), nums.end());

    // for(int i=0; i<nums.size(); ++i){
    //     for(int j=1; i<nums.size(); ++j){
    //         if (nums[i] + nums[j] == target)
    //             return {
    //                 (int)std::distance(srcVec.begin(), std::find(srcVec.begin(),srcVec.end(),nums[i])), 
    //                 (int)std::distance(srcVec.begin(), std::find(srcVec.begin(),srcVec.end(),nums[j]))};
    //         else if (nums[i] + nums[j] > target)
    //             break;
    //     }
    // }

    // v.1
    // for(int i=0; i<nums.size(); ++i){
    //     for(int j=1; i<nums.size(); ++j){
    //         if (nums[i] + nums[j] == target)
    //             return {i, j};
    //     }
    // }

    // v.2
    std::multimap<int, int> hashNumsPos;
        for(int i=0; i<nums.size(); ++i)
            hashNumsPos.insert(std::pair{nums[i], i});

    for(int i=0; i<nums.size(); ++i){
        int srcNum = target - nums[i];
        auto hashValRange = hashNumsPos.equal_range(srcNum);
        for(auto it=hashValRange.first; it!=hashValRange.second; ++it)
             if(it->second > i)
                return {i, it->second};
    }

    return nums;
};