/*
*/

#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>

struct Doc{
    int16_t docId;
    std::string text;
};

typedef std::vector<Doc> SearchResult;

class ISearchIndex{
    public:
        virtual void addDocToIndex(const Doc& doc) = 0;
        virtual std::vector<int16_t> GetSearchResult(std::string req, int16_t maxResultRow = 5) = 0; 
};

struct FrequencyInDoc{
    int16_t docId;
    int16_t wordFreq;

    static bool FrequencyInDocPredicate(const FrequencyInDoc &lhs, const FrequencyInDoc &rhs){
        if (lhs.wordFreq == rhs.wordFreq)
            return lhs.docId < rhs.docId;
        else
            return lhs.wordFreq > rhs.wordFreq;
    };

    // Оператор для работы хэш таблицы
    bool operator < (const FrequencyInDoc &rhs){
        return FrequencyInDocPredicate(*this, rhs);
    };
};

struct DocRelevance{
    int16_t docId;
    int16_t relevance;
};

typedef std::vector<FrequencyInDoc> WordFrequencyHeap;

class SearchIndex:ISearchIndex {

public:
    void addDocToIndex(const Doc& doc) override {
        std::map<std::string, int16_t> wordsFrequencyInDoc;
        getWordsFrequencyFromString(doc.text, wordsFrequencyInDoc);

        // Добавдяем уникальные слова документа в индекс и
        // сортируем документы внутри слова, сразу строя рейтинг
        for(auto wordFreq : wordsFrequencyInDoc){
            wordSearchIndex[wordFreq.first].push_back((FrequencyInDoc){doc.docId, wordFreq.second});

            WordFrequencyHeap* wordFrequencyHeap = &wordSearchIndex[wordFreq.first];
            //std::sort(wordFrequencyHeap->begin(), wordFrequencyHeap->end(),  FrequencyInDoc::FrequencyInDocPredicate);
        };
    };

    std::vector<int16_t> GetSearchResult(std::string req, int16_t maxResultRow = 5) override {
        
        std::vector<int16_t> searchResult;

        std::map<std::string, int16_t> wordsInRequest;  
        getWordsFrequencyFromString(req, wordsInRequest);

        std::unordered_map<int16_t, int16_t> docsRating; // DocId, WordFreq

        // Проходим по всем словам запроса и суммируем частоту слов в документах
        for(auto wordFreq : wordsInRequest){
            WordFrequencyHeap* wordFrequencyHeap = &wordSearchIndex[wordFreq.first];

            //for (int16_t i=0; i<std::min((int16_t)maxResultRow,(int16_t)wordFrequencyHeap->size());++i){
            for (int16_t i=0; i<wordFrequencyHeap->size();++i){
                FrequencyInDoc frequencyInDoc = (*wordFrequencyHeap)[i];
                docsRating[frequencyInDoc.docId] += frequencyInDoc.wordFreq;
            };
        };

        // Сортируем результат 
        std::vector<FrequencyInDoc> resultSearchDocsSorting;
        for (auto doc : docsRating)
            resultSearchDocsSorting.push_back((FrequencyInDoc){doc.first, doc.second});
        std::sort(resultSearchDocsSorting.begin(), resultSearchDocsSorting.end(), FrequencyInDoc::FrequencyInDocPredicate);

        // Представляем результат в виде массива
        for (int16_t i=0; i<std::min((int16_t)maxResultRow,(int16_t)resultSearchDocsSorting.size());++i)
            searchResult.push_back(resultSearchDocsSorting[i].docId+1);

        return searchResult;
    }

private:
    std::unordered_map<std::string, WordFrequencyHeap> wordSearchIndex;

    void getWordsFrequencyFromString(const std::string& srcStr, std::map<std::string, int16_t>& wordsInDoc){

            int16_t wordStartPos = 0;
            int16_t wordEndPos = srcStr.find(" ");
            
            while (wordEndPos != -1){
                std::string word = srcStr.substr(wordStartPos, wordEndPos-wordStartPos);
                ++wordsInDoc[word];
                wordStartPos = wordEndPos + 1;
                wordEndPos = srcStr.find(" ", wordStartPos);
            }
            std::string word = srcStr.substr(wordStartPos, srcStr.size()-wordStartPos+1);
            ++wordsInDoc[word];   
    };
};

int main(){

    SearchIndex si;

    int16_t n;
    std::cin >> n;

    // Считываем документы и добавляем в индекс
    std::cin.ignore();
    std::vector<Doc> docs(n);
    for(int16_t i=0; i<n; ++i){
        docs[i].docId = i;
        std::getline(std::cin, docs[i].text);
        si.addDocToIndex(docs[i]);
    }

    int16_t m;
    std::cin >> m;

    // Считываем запросы
    std::cin.ignore();
    std::vector<std::string> reqs(m);
    for(int16_t i=0; i<m; ++i)
        std::getline(std::cin, reqs[i]);

    // Ищем документы по запросам в индексе
    for(int16_t i=0; i<m; ++i){
        std::vector<int16_t> searchResult = si.GetSearchResult(reqs[i]);
        for(auto docNum : searchResult)
            std::cout << docNum << " ";
        std::cout << '\n';
    }

    return 0;
}
