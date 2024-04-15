/*
Ссылка на отчёт в контесте:
https://contest.yandex.ru/contest/24414/run-report/112001523/

-- ПРИНЦИП РАБОТЫ --
1. Принцип работы основан на подсчете частоты слов в исходных документов.
2. Для быстрого доступа к частотам используем хэш-таблицу (наш поисковый индекс).
3. Можно было бы использовать двоичное дерево, но тогда временная сложность выросла 
   бы до O(log n) вместо O(1), поэтому остановились на хэш таблице.
4. Первым шагом разбираем слова в каждом документе и добавляем в хэш-таблицу (поисковый индекс)
   значение идентификатора документа и частоты слова. Таким образом в хэн-таблице
   под каждым ключом "слово", хранятся все документы с количеством вхождений слов в них.
5. Вторым шагом выполняем разбор запроса на слова, выборку и суммирование частот по ним в
   хэш таблице.
6. Третий финальный шаг - вывод пяти документов в требуемом порядке.
7. К интересным особенностям решения можно отнести: использование предиката, переопределение
   операций для структуры.  
-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
1. Мы использовали полноценный уникальный индекс по словам реализованный на unordered_map,
   обеспечив количественные требования решения задачи.
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
1. Скорость вставки в хэш-таблицу О(1), но для извления слов мы используем поиск слов в цикле, 
   поэтому, поэтому временная сложность O(N), где N - количество слов. 
2. Скорость поиска аналогична и равна O(N) только из-за обработки каждого слова. Если мы будем
   выполнять поиск подготовленных слов, то скорость поиска в хэш-таблице O(1).
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
1. Пространственная сложность равна O(N), где N - количество уникальных слов в документах, 
   т.к. мы храним частоты для каждого слова.
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

    // Предикат для сортировки документов
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

typedef std::vector<FrequencyInDoc> WordFrequencyVector;

class SearchIndex:ISearchIndex {

public:
    void addDocToIndex(const Doc& doc) override {
        std::map<std::string, int16_t> wordsFrequencyInDoc;
        getWordsFrequencyFromString(doc.text, wordsFrequencyInDoc);

        for(auto wordFreq : wordsFrequencyInDoc)
            wordSearchIndex[wordFreq.first].push_back((FrequencyInDoc){doc.docId, wordFreq.second});
    };

    std::vector<int16_t> GetSearchResult(std::string req, int16_t maxResultRow = 5) override {
        
        std::vector<int16_t> searchResult;

        std::map<std::string, int16_t> wordsInRequest;  
        getWordsFrequencyFromString(req, wordsInRequest);

        std::unordered_map<int16_t, int16_t> docsRating; // DocId, WordFreq

        // Проходим по всем словам запроса и суммируем частоту слов в документах
        for(auto wordFreq : wordsInRequest){
            WordFrequencyVector* wordFrequencyVector = &wordSearchIndex[wordFreq.first];

            for (int16_t i=0; i<wordFrequencyVector->size();++i){
                FrequencyInDoc frequencyInDoc = (*wordFrequencyVector)[i];
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
    std::unordered_map<std::string, WordFrequencyVector> wordSearchIndex;

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
