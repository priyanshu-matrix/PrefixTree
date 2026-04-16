#include <iostream>
#include <fstream>
#include "names.h"

using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isLeaf;
    TrieNode() {
        isLeaf = false;
        for(int i = 0 ; i < 26 ; i++){
            children[i] = nullptr;
        }
    }
};

void insert(TrieNode* root, string text) {
    TrieNode* curr = root;
    for(auto& key : text) {
        int index = tolower(key) - 'a'; 
        if(index < 0 || index >= 26) continue;
        if(curr->children[index] == nullptr) {
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index]; 
    }
    curr->isLeaf = true; 
}

void print(TrieNode* root, int par, ofstream& file) {
    if (!root) return;
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            unsigned int childID = ((par * 26) + i + 1);
            file << "  Node" << par << " -> Node" << childID 
                 << " [label=\"" << char(i + 'a') << "\", weight=\"" << char(i + 'a') << "\"];\n";
            print(root->children[i], childID, file);
        }
    }
}

int main() {
    TrieNode* root = new TrieNode();
    ofstream myFile("Trie.dot");

    for(int i = 0; i < sizeoflist; i++) {
        string fruitStr = fruits[i];
        insert(root, fruitStr);
    }

    if(myFile.is_open()) {
        myFile << "digraph Trie {\n";
        print(root, 0, myFile);
        myFile << "}\n";
        myFile.close();
    } else {
        cout << "Some error occoured while opening the file" << endl;
    }

    return 0;
}
