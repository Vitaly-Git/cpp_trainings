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

    for (int_t pos = 0; pos < cheatSheet.size(); ++pos){
        
        result = false;

        Node * currentNode = root;        
        int_t offset = 0;

        //while ((pos + offset) < cheatSheet.size()){
        while (pos < cheatSheet.size()){
            char symbolToFind = cheatSheet[pos + offset];

            if (currentNode->childNodes.count(symbolToFind) == 0){
                if (result == true){
                    --pos;
                    break;
                } else {
                    return false;
                }
            }
            currentNode = currentNode->childNodes[symbolToFind];
            if (currentNode->isTerminal){
                //pos = pos + offset;
                //result = true;

                char symbolNext = cheatSheet[pos + 1];
                if (currentNode->childNodes.count(symbolNext) == 0){
                    result = true;
                    break;
                } else {
                    result = false;
                    ++pos;
                    continue;
                }

            } else {
                result = false;
            }
            ++pos;
            //++offset;
        }
        //pos = pos + offset;
    }

    return result;
    //return true;
}