#include <iostream>

int main(){

    std::string s;
    std::string t;
    std::getline(std::cin, s);
    std::getline(std::cin, t);

    bool isSequence = false;

    int64_t idxS = 0;
    for(int64_t idxT=0; idxT<t.size(); ++idxT){
        if (s[idxS] == t[idxT]){
            ++idxS;
            if (idxS==s.size()){
                isSequence = true;
                break;
            }
        }
    }

    std::cout << (isSequence ? "True" : "False");

    return 0;
}

// #include <unordered_set>

// int main(){

//     std::string s;
//     std::string t;
//     std::getline(std::cin, s);
//     std::getline(std::cin, t);

//     std::unordered_set<char> strSymbS;
//     std::unordered_set<char> strSymbT;
//     strSymbS.insert(s.begin(), s.end());
//     strSymbT.insert(t.begin(), t.end());

//     // bool isSequence = true;
//     // for(char ch : s)
//     //     if (strSymb.find(ch)==strSymb.end()){
//     //         isSequence = false;
//     //         break;
//     //     }

//     bool isSequence = true;
//     for(char ch : strSymbS)
//         if (strSymbT.find(ch)==strSymbT.end()){
//             isSequence = false;
//             break;
//         }

//     std::cout << (isSequence ? "True" : "False");

//     return 0;
// }