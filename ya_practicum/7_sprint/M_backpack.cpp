#include <iostream>
#include <vector>

struct Good{
    std::int64_t weight;
    std::int64_t price;
};

int main(){
    
    std::int64_t M, n;
    std::cin >> M >> n;

    typedef std::vector<std::int64_t> RowWeights;
    std::vector<RowWeights> goodsRow;

    std::vector<Good> goods(n);

    for (std::int64_t i=0; i<n; ++i)
        std::cin>>goods[i].weight >> goods[i].price;

    for (std::int64_t g=0; g<n; ++g){

        std::int64_t curWeight = goods[g].weight;
        std::int64_t curPrice = goods[g].price;


    }
        



    for (std::int64_t w=0; w<M; ++w){

        for (std::int64_t w=0; w<M; ++w){


        }

    }



}


return 0;
}