#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <map>

struct Doc{
    int16_t docId;
    std::string text;
};

struct WordFrequencyInDoc{
    std::string word;
    int16_t docId;
    int16_t wordFreq;
};

struct DocRelevance{
    int16_t docId;
    int16_t relevance;
};

//typedef std::priority_queue<WordFrequencyInDoc> WordFrequencyHeap;
typedef std::unordered_map<int16_t, int16_t> WordFrequencyInDoc; // Doc, Freq

class SearchIndex
{
public:
    void addDocToIndex(Doc doc){

    };

private:
    std::unordered_map<std::string, WordFrequencyInDoc> wordSearchIndex;
    void addWordToIndex(Doc doc){

    };
};

int main(){



    return 0;
}
