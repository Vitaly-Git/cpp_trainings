/*
   Ссылка на отчёт в контесте:
   https://contest.yandex.ru/contest/26133/run-report/115194980/

-- ПРИНЦИП РАБОТЫ --
   Интересная задача :) объединяет несколько спринтов :)
1. Сначала показалась достаточно понятной, т.к. нужно выполнить поиск подстрок в строке.
2. Даже если не думать о текущем спринте, то начинаешь думать, про использование мапов или чего-то
   подобного для быстрого поиска.
3. Так же анализирую структуру мапа, понимаешь, что поиск будет осуществляться алгоритмической скоростью, т.к.  
   в основе будет лежать дерево.
4. Тут же вспоминаешь текущий спринт и понимаешь, что это во многом эквивалент префиксного дерева, 
   но префиксное дерево возможно будет эффективнее.
5. И с этими радостными мыслями ещё раз перечитал про префиксное дерево и реализовал его.
6. Но дальше ждал сюрприз, который не учел: Нам же надо фактически перебрать каждое слово с каждым, чтобы понять
   что строка может сосять из их комбинаций.
7. Наивным решением был бы перебор или рекурсия, но после курса алгоритмов эти варианты стараешься избегать, т.к. там сразу 
   сложность вырастет до ЭН в квадрате (минимум).
8. Вспомнил предыдущий спринт и динамическое программирование, т.к. без него тут сложно достичь оптимального результата.
9. Стал думать, как можно хранить перестановки слов.
9.1. Подумал про матрицу, где можно по строкам смотреть наслоение слов - нооо размер был бы большой, и реализация не самая простая.
9.2. Подумал про хранение позиций в мапе, но это опять постоянный логорифмический поиск.
9.3. Стал читать и смотреть дополнительно, как можно сделать оптимально.
10. В итоге оказалось проще чем думал, но надо было посмотреть с другой стороны.
10.1. Логика заключается в том, что мы идем последовательно и запоминаем позиции, с которых
      может начаться новое слово, и всё.
10.2. Таким образом, если последняя позиция будет на месте последней буквы шпаргалки, то мы смогли собрать слово.
10.3. Реализовал решение :)
-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
1. Мы идем последовательно по каждой букве.
2. Проверяем все возможные комбинации слов.
3. Вывод делаем только если все доступные слова слились в цепочку и последнее слово завершилось
   на последнем символе шпаргалки.
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
1. O(L) - сложность построения префиксного дерева, L — суммарная длина слов во множестве.
2. O(n⋅∣Σ∣) - поиск в префиксном дереве одного слова, с переходом по ребрам.
3. Фактически мы ищем каждое слово N раз, по количеству букв в строке.
4. Поэтому, итоговая сложность равна: O(N*N)
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
1. Дерево храним ребрами, и в крайнем случае, нам может понадобиться O(L) места,
   где L - сумма длин всех слов.
2. Так же храним массив разрешенных начал новых слов, его длина равна
   длине шпаргалки N.
3. В итоге, в худшем случаем мы выделим место под слова и строку O(L) + O(N),
   приводим к максимальному, и получаем O(N).
*/

#include <iostream>
#include <vector>
#include <map>

typedef std::int64_t int_t;
typedef std::string str_t;
typedef std::vector<str_t> vec_str_t;

struct Node{
    char symbol;
    std::map<char, Node*> childNodes;
    bool isTerminal = false;
};

str_t isGoodCheatSheet(const str_t& cheatSheet, const vec_str_t& words);
Node* createPrefixTree(const vec_str_t& words);
Node* addWordToPrefixTree(Node* root, const str_t& word);
bool isStringConsistFromWords(const str_t& cheatSheet, Node * root);

int main(){

    // Ввод исходных данных
    str_t cheatSheet;
    std::getline(std::cin, cheatSheet);

    int_t n;
    std::cin >> n;

    std::cin.ignore();
    vec_str_t words(n);
    for(int_t i = 0; i<n; ++i)
        std::getline(std::cin, words[i]);

    // Проверяем хорошая шпаргалка или нет
    std::cout << isGoodCheatSheet(cheatSheet, words);

    return 0;
}

str_t isGoodCheatSheet(const str_t& cheatSheet, const vec_str_t& words){

    str_t result = "YES";
    Node* root = createPrefixTree(words);

    if (isStringConsistFromWords(cheatSheet, root))
        result = "YES";
    else
        result = "NO";

    return result;
}

Node* createPrefixTree(const vec_str_t& words){
    Node* root = new Node();
    for (str_t word : words)
        addWordToPrefixTree(root, word);
    return root;
} 

Node* addWordToPrefixTree(Node* root, const str_t& word){

    Node* currentNode = root;

    for (char symbol : word){

        if (currentNode->childNodes.count(symbol) == 0){
            Node* newNode = new Node();
            newNode->symbol = symbol;
            newNode->childNodes.clear();
            newNode->isTerminal = false;

            currentNode->childNodes[symbol] = newNode;
            currentNode = newNode;
        } else {
            currentNode = currentNode->childNodes[symbol];
        }
    };

    currentNode->isTerminal = true;

    return currentNode;
}

bool isStringConsistFromWords(const str_t& cheatSheet, Node * root){
    
    bool result = false;

    // Создадим массив для запоминания позиций заверешения предыдущего и начала следующего слова.
    // Размер "+1", т.к. ставим признак после завершения предыдущего слова.
    std::vector<int_t> posEnabledForWordBegin(cheatSheet.size()+1);
    posEnabledForWordBegin[0] = 1;

    for (int_t posInCheatSheet = 0; posInCheatSheet < cheatSheet.size(); ++posInCheatSheet){

        bool findPosPreviousWord = (posEnabledForWordBegin[posInCheatSheet]>0);

        if (!findPosPreviousWord)
            continue;

        Node * currentNode = root;        
        int_t posNextLetter = 0;

        while ((posInCheatSheet + posNextLetter) < cheatSheet.size()){

            int_t letterPosToCheck = posInCheatSheet + posNextLetter;
            char symbolToCheck = cheatSheet[letterPosToCheck];

            if (currentNode->childNodes.count(symbolToCheck) == 0)
                break;

            currentNode = currentNode->childNodes[symbolToCheck];
            
            if (currentNode->isTerminal)
                posEnabledForWordBegin[letterPosToCheck+1] = letterPosToCheck+1;

            ++posNextLetter;
        }

    }

    bool lastPosIsEndOfTheLastWord = (posEnabledForWordBegin[posEnabledForWordBegin.size()-1] > 0);

    return lastPosIsEndOfTheLastWord;

}