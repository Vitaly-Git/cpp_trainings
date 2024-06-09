#include <iostream>
#include <vector>
#include <algorithm>

struct Good{
    std::int64_t weight;
    std::int64_t price;
    std::vector<std::int64_t> goodsIdxs;
};

int main(){
    
    std::int64_t n, M;
    std::cin >> n >> M ;

    typedef std::vector<Good> RowWeights;
    std::vector<RowWeights> goodsRow(n);

    std::vector<Good> goods(n);
    for (std::int64_t i=0; i<n; ++i)
        std::cin>>goods[i].weight >> goods[i].price;

    // std::sort(goods.begin(), goods.end(), [](auto& lhs, auto& rhs){
                
    //         if (lhs.weight != rhs.weight)
    //             return lhs.weight < rhs.weight;
    //         else    
    //             return lhs.price < rhs.price;
    //     });


    for (std::int64_t g=0; g<n; ++g){

        goodsRow[g] = RowWeights(M+1);

        std::int64_t curRowIdx = g;
        std::int64_t prevRowIdx = g-1;

        std::int64_t curWeight = goods[g].weight;
        std::int64_t curPrice = goods[g].price;

        for (std::int64_t w=1; w<=M; ++w){
            
            std::int64_t weightRemind = w - curWeight;

            std::int64_t prevPrice = 0;
            std::int64_t prevWeight = 0;
            std::int64_t prevRemindPrice = 0;
            std::int64_t prevRemindWeight = 0;
            
            if (prevRowIdx >= 0){
                prevPrice = goodsRow[prevRowIdx][w].price;
                prevWeight = goodsRow[prevRowIdx][w].weight;
                if (weightRemind > 0)
                    prevRemindPrice = goodsRow[prevRowIdx][weightRemind].price;
                    prevRemindWeight = goodsRow[prevRowIdx][weightRemind].weight;
            }

            if (prevRowIdx < 0){
                if (weightRemind >= 0){
                    goodsRow[curRowIdx][w].price = curPrice;
                    goodsRow[curRowIdx][w].weight = curWeight;
                    goodsRow[curRowIdx][w].goodsIdxs.push_back(g+1);
                } else {
                    goodsRow[curRowIdx][w].price = 0;
                    goodsRow[curRowIdx][w].weight = 0;
                    goodsRow[curRowIdx][w].goodsIdxs.clear();
                }
            }else if (weightRemind < 0){
                goodsRow[curRowIdx][w].price = prevPrice;
                goodsRow[curRowIdx][w].weight = prevWeight;
                goodsRow[curRowIdx][w].goodsIdxs = goodsRow[prevRowIdx][w].goodsIdxs;
            } else if (weightRemind == 0) {
                if (prevPrice > curPrice){
                    goodsRow[curRowIdx][w].price = prevPrice;
                    goodsRow[curRowIdx][w].weight = prevWeight;
                    goodsRow[curRowIdx][w].goodsIdxs = goodsRow[prevRowIdx][w].goodsIdxs;
                } else {
                    goodsRow[curRowIdx][w].price = curPrice;
                    goodsRow[curRowIdx][w].weight = curWeight;
                    goodsRow[curRowIdx][w].goodsIdxs.push_back(g+1);
                }
            } else {
                if (prevPrice > (curPrice + prevRemindPrice)){
                    goodsRow[curRowIdx][w].price = prevPrice;
                    goodsRow[curRowIdx][w].weight = prevWeight;
                    goodsRow[curRowIdx][w].goodsIdxs = goodsRow[prevRowIdx][w].goodsIdxs;
                } else {
                    goodsRow[curRowIdx][w].price = curPrice + prevRemindPrice;
                    goodsRow[curRowIdx][w].weight = curWeight + prevRemindWeight; 
                    goodsRow[curRowIdx][w].goodsIdxs = goodsRow[prevRowIdx][weightRemind].goodsIdxs;
                    goodsRow[curRowIdx][w].goodsIdxs.push_back(g+1);
                }
            }
        }
    }
        
    std::cout << goodsRow[n-1][M].goodsIdxs.size() << "\n";
    
    std::sort(goodsRow[n-1][M].goodsIdxs.begin(), goodsRow[n-1][M].goodsIdxs.end(), [](auto& lhs, auto& rhs){
            return lhs > rhs;
    });

    for (auto item : goodsRow[n-1][M].goodsIdxs)
        std::cout << item << " ";

    return 0;
}