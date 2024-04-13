/*



*/


#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <map>

struct Doc{
    int16_t docId;
    std::string text;
};

typedef std::vector<Doc> SearchResult;

class ISearchIndex{
    public:
        virtual void addDocToIndex(const Doc& doc) = 0;
        virtual std::vector<int16_t> GetSearchResult(std::string req) = 0; 
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

typedef std::priority_queue<WordFrequencyInDoc> WordFrequencyHeap;
typedef std::unordered_map<int16_t, int16_t> WordFrequencyInDoc; // Doc, Freq

class SearchIndex:ISearchIndex
{
public:
    void addDocToIndex(const Doc& doc) override {
        std::map<std::string, int16_t> wordsInDoc;
        int16_t wordStartPos = 0;
        int16_t wordEndPos = doc.text.find(" ");
        
        while (wordEndPos != -1){
            std::string word = doc.text.substr(wordStartPos, wordEndPos-wordStartPos+1);
            ++wordsInDoc[word];
            wordEndPos = doc.text.find(" ");
            wordStartPos = wordEndPos + 1;
            wordEndPos = doc.text.find(" ");
        }
        std::string word = doc.text.substr(wordStartPos, doc.text.size()-wordStartPos+1);
        ++wordsInDoc[word];       
        
        for(auto wordFreq : wordsInDoc){
            wordSearchIndex[wordFreq.first].push({doc.docId, wordsInDoc[word]});
        }
    };
    std::vector<int16_t> GetSearchResult(std::string req) override {

    }

private:
    std::unordered_map<std::string, WordFrequencyHeap> wordSearchIndex;
    void addWordToIndex(Doc doc){

    };
};

int main(){

    SearchIndex si;

    int16_t n;
    std::cin >> n;

    std::vector<Doc> docs(n);
    for(int16_t i=0; i<n; ++i){
        docs[i].docId = i;
        std::getline(std::cin, docs[i].text);
        si.addDocToIndex(docs[i]);
    }

    int16_t m;
    std::vector<std::string> reqs(m);
    for(int16_t i=0; i<m; ++i){       
        std::getline(std::cin, reqs[i]);
        std::vector<int16_t> searchResult = si.GetSearchResult(reqs[i]);

        for(auto docNum : searchResult){
            if (i>0)
                std::cout << " ";
            std::cout << docNum;    
        }
    }

    return 0;
}
