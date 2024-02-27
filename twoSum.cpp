#include "twoSum.hpp"


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

    for(int i=0; i<nums.size(); ++i){
        for(int j=1; i<nums.size(); ++j){
            if (nums[i] + nums[j] == target)
                return {i, j};
        }
    }

    return nums;
};