#include <iostream>
#include <vector>
#include <set>

typedef std::int64_t int_t;
typedef std::string str_t;
typedef std::vector<str_t> vec_str_t;

struct Node{
    char symbol;
    std::vector<Node*> childNodes;
    std::set<char> childSymbols;
    bool isTerminal = false;
};


str_t isGoodCheatSheet(const str_t& cheatSheet, const vec_str_t& words){
    str_t result = "YES";


    return result;
}

Node* createPrefixTree(const vec_str_t& words){
    Node* root = new Node();
    for (str_t word : words)
        addWordToTree(root, word);
    return root;
} 

Node* addWordToTree(Node* root, const str_t& word){

    Node* currentNode = root;

    for (char symbol : word){

        if (currentNode->childSymbols.find(symbol) == currentNode->childSymbols.end()){
            Node* newNode = new Node();
            newNode->symbol = symbol;
            newNode->childNodes.clear();
            newNode->childSymbols.clear();
            newNode->isTerminal = false;

            currentNode->childNodes.push_back(newNode);
            currentNode->childSymbols.insert(symbol);
            currentNode = newNode;
        }
    
    currentNode->isTerminal = true;

    return currentNode;
}


int main(){

    // Ввод исходных данных
    str_t cheatSheet;
    std::getline(std::cin, cheatSheet);

    int_t n;
    std::cin >> n;

    vec_str_t words(n);
    for(int_t i = 0; i<n; ++i)
        std::getline(std::cin, words[i]);

    // Проверяем хорошая подсказка или нет
    std::cout << isGoodCheatSheet(cheatSheet, words);

    return 0;
}

