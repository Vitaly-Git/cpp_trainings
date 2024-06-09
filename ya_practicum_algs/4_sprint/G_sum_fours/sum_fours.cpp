#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Fours{
    int one;
    int two;
    int three;
    int four;

    bool operator == (const Fours rhs){
        return this->one == rhs.one &&
            this->two == rhs.two &&
            this->three == rhs.three &&
            this->four == rhs.four;
    };

    bool operator < (const Fours rhs){

        if (this->one < rhs.one)
            return true;
        else if (this->one > rhs.one)
            return false;

        if (this->two < rhs.two)
            return true;
        else if (this->two > rhs.two)
            return false;

        if (this->three < rhs.three)
            return true;
        else if (this->three > rhs.three)
            return false;

        if (this->four < rhs.four)
            return true;
        else if (this->four > rhs.four)
            return false;

        return false;
    };
};

struct FoursHash
{
    std::size_t operator()(const Fours& k) const
    {
        return std::hash<int>()(k.one) ^
            (std::hash<int>()(k.two) << 1) ^
            (std::hash<int>()(k.three) << 2) ^
            (std::hash<int>()(k.four) << 3);
    }
};
 
struct FoursEqual
{
    bool operator()(const Fours& lhs, const Fours& rhs) const{
        return lhs.one == rhs.one &&
            lhs.two == rhs.two &&
            lhs.three == rhs.three &&
            lhs.four == rhs.four;
    }
};


bool operator < (const Fours& lhs, const Fours& rhs){
        
    if (lhs.one < rhs.one)
        return true;
    else if (lhs.one > rhs.one)
        return false;

    if (lhs.two < rhs.two)
        return true;
    else if (lhs.two > rhs.two)
        return false;

    if (lhs.three < rhs.three)
        return true;
    else if (lhs.three > rhs.three)
        return false;

    if (lhs.four < rhs.four)
        return true;
    else if (lhs.four > rhs.four)
        return false;

    return false;
};

void findFours(const std::vector<int>& srcVector, int sumPlan, int sumFact, int curDepth, int startPos,
    std::vector<int>& curVecFours,
    std::unordered_map<Fours, int, FoursHash, FoursEqual>& mapFoursVecPos,
    std::vector<Fours>& vecFours);

int main(){

    int l;
    int sumPlan;
    std::cin >> l >> sumPlan;

    std::vector<int> srcVector(l);
    for (int i=0; i<l; ++i)
        std::cin >> srcVector[i];
    std::sort(srcVector.begin(), srcVector.end());    

    std::unordered_map<Fours, int, FoursHash, FoursEqual> mapFoursVecPos;
    std::vector<Fours> vecFours;

    int curDepth = 0;
    int sumFact = 0;
    std::vector<int> curVecFours;
    findFours(srcVector, sumPlan, sumFact, curDepth, 0, curVecFours, mapFoursVecPos, vecFours);

    std::cout << mapFoursVecPos.size() << '\n';

    std::vector<std::vector<int>> vecCout;
    for (int i=0; i<vecFours.size(); ++i)
        vecCout.push_back(
            {
                vecFours[i].one,
                vecFours[i].two,
                vecFours[i].three,
                vecFours[i].four                
            });

    std::sort(vecCout.begin(), vecCout.end());
    for (int i=0; i<vecCout.size(); ++i){
        
        // std::cout << vecFours[i].one  << " ";
        // std::cout << vecFours[i].two  << " ";
        // std::cout << vecFours[i].three  << " ";
        // std::cout << vecFours[i].four;
        // std::cout << '\n';

        for (int j=0; j<4; ++j){
            if (j>0)
                std::cout << " ";
            std::cout << vecCout[i][j];
        }
        std::cout << '\n';
    }

    return 0;
}

void findFours(const std::vector<int>& srcVector, int sumPlan, int sumFact, int curDepth, int startPos,
    std::vector<int>& curVecFours,
    std::unordered_map<Fours, int, FoursHash, FoursEqual>& mapFoursVecPos,
    std::vector<Fours>& vecFours){

    if (curDepth >= 4)
        return;

    ++curDepth;

    for (int i = startPos; i<(int)(srcVector.size()-(4-curDepth)); ++i){

        int curValue = srcVector[i];
        int sumFactCur = sumFact + curValue;
        //curVecFours.push_back(curValue);

        // if (sumFactCur > sumPlan)
        //     break;

        if (curDepth == 4){

            if (sumPlan > 0 && sumFactCur > sumPlan)
                break;

            // if (sumPlan < 0 && sumFactCur > sumPlan)
            //      break;

            if (sumFactCur == sumPlan){
                
                //curVecFours.push_back(curValue);
                // std::vector<int> saveVector(curVecFours);
                // // saveVector.insert(saveVector.begin(), curVecFours.begin(), curVecFours.end());
                // std::sort(saveVector.begin(), saveVector.end());

                Fours checkMap = {
                    curVecFours[0],
                    curVecFours[1],
                    curVecFours[2],
                    curValue,
                };

                if (checkMap.one > checkMap.two)
                    std::swap(checkMap.one, checkMap.two);
                if (checkMap.one > checkMap.three)
                    std::swap(checkMap.one, checkMap.three);
                if (checkMap.one > checkMap.four)
                    std::swap(checkMap.one, checkMap.four);

                if (checkMap.two > checkMap.three)
                    std::swap(checkMap.two, checkMap.three);
                if (checkMap.two > checkMap.four)
                    std::swap(checkMap.two, checkMap.four);

                if (checkMap.three > checkMap.four)
                    std::swap(checkMap.three, checkMap.four);

                if (mapFoursVecPos[checkMap] == 0){

                    //std::vector<int> saveVector(curVecFours);
                    // saveVector.insert(saveVector.begin(), curVecFours.begin(), curVecFours.end());
                    //std::sort(saveVector.begin(), saveVector.end());

                    vecFours.push_back(checkMap);
                    mapFoursVecPos[checkMap] = 1;
                }
                break;
            }
        } else if (curDepth < 4){
            curVecFours.push_back(curValue);
            findFours(srcVector, sumPlan, sumFactCur, curDepth, i+1, curVecFours, mapFoursVecPos, vecFours);
            curVecFours.erase(curVecFours.cend()-1);
        }
    }

    --curDepth;
}