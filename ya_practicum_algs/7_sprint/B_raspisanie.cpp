#include <iostream>
#include <algorithm>
#include <vector>

struct Lesson{
    float begin;
    float end;
};

int main(){

    std::int32_t n;
    std::cin >> n;

    std::vector<Lesson> lessons(n);
    for(std::int32_t i=0; i<n; ++i)
        std::cin >> lessons[i].begin >> lessons[i].end;

    std::sort(lessons.begin(), lessons.end(), [](Lesson& lhs, Lesson& rhs){
        if (lhs.end != rhs.end)
            return lhs.end < rhs.end;
        else
            return lhs.begin < rhs.begin;
    });

    std::int32_t totalLessons = 0;    
    std::vector<Lesson> lessonsResult(n);

    for(std::int32_t i=0; i<n; ++i){
        
        if (i>0){
            if (lessons[i].begin < lessonsResult[totalLessons-1].end)
                continue;
        }

        ++totalLessons;
        lessonsResult[totalLessons-1].begin = lessons[i].begin;
        lessonsResult[totalLessons-1].end = lessons[i].end;
    }

    std::cout << totalLessons << '\n';
    for(std::int32_t i=0; i<totalLessons; ++i){
        std::cout << lessonsResult[i].begin << " " << lessonsResult[i].end << '\n';
    }

    return 0;
}