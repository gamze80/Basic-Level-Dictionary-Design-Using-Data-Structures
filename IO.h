//
// Created by gamze on 29.12.2021.
//



#ifndef TRIES_IO_H
#define TRIES_IO_H
#include <iostream>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class TrieNode {                          ///I define node as TrieNode class.
public:
    string value = "";
    TrieNode *children[26];
};

class IO {
public:
    TrieNode *root = getNode();

    TrieNode *getNode();


    void insert(TrieNode *root, string key, string value, string *output);

    void search(TrieNode *root, string key, string *output);

    TrieNode *remove(TrieNode *root, string key, int depth);

    bool isEmpty(TrieNode *root);

    void searchForDeletion(TrieNode *root, string key, int *whichType, string *output);
    ///This function is here for search if the wanted key is in the trie. If it is
    ///then it calls deletion function.


    void display(TrieNode *root, char *str, int level, vector<string> *output_list);

    bool isLeafNode(TrieNode *root);
};


#endif //TRIES_IO_H
