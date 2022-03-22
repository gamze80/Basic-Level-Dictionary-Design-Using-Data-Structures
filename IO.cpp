//
// Created by gamze on 29.12.2021.
//

#include <iostream>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
#include <map>
#include "IO.h"
using namespace std;
TrieNode *IO::getNode() {
    TrieNode *pNode = new TrieNode;
    for (auto &i: pNode->children)
        i = NULL;
    return pNode;
}

void IO::insert(TrieNode *root, string key, string value, string *output) {
    TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
    }

    if (pCrawl->value == value) {
        *output += '"';
        *output += key;
        *output += '"';
        *output += " already exists\n";
    } else if (pCrawl->value == "") {
        *output += '"';
        *output += key;
        *output += '"';
        *output += " was added\n";
        pCrawl->value = value;
    } else if (pCrawl->value != value) {
        *output += '"';
        *output += key;
        *output += '"';
        *output += " updated\n";
        pCrawl->value = value;
    }

}

void IO::search(TrieNode *root, string key, string *output) {
    int control = 0;
    TrieNode *pCrawl = root;

    for (char i: key) {
        int index = i - 'a';
        if (!pCrawl->children[index])
            break;

        pCrawl = pCrawl->children[index];
        control++;
    }
    if (control == key.length() && pCrawl->value != "") {
        *output += '"';
        *output += "The English equivalent is ";
        *output += pCrawl->value;
        *output += '"';
        *output += "\n";

    } else if (control == 0) {
        *output += '"';
        *output += "no record";
        *output += '"';
        *output += "\n";
    } else if (control < key.length()) {
        *output += '"';
        *output += "incorrect Dothraki word";
        *output += '"';
        *output += "\n";
    } else if (control == key.length() && pCrawl->value == "") {
        *output += '"';
        *output += "not enough Dothraki word";
        *output += '"';
        *output += "\n";
    }
}


///this is useful for if we want to delete something we are checking that is trie empty.
bool IO::isEmpty(TrieNode *root) {
    for (int i = 0; i < 26; i++)
        if (root->children[i])
            return false;
    return true;
}


TrieNode *IO::remove(TrieNode *root, string key, int depth = 0) {
    if (!root)
        return NULL;


    if (depth == key.size()) {


        if (root->value != "")
            root->value = "";

        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }

        return root;
    }

    // If not last character, recur for the child
    int index = key[depth] - 'a';
    root->children[index] =
            remove(root->children[index], key, depth + 1);

    // If root does not have any child, and it is not end of another word.
    if (isEmpty(root) && root->value == "") {
        delete (root);
        root = NULL;
    }

    return root;
}

void IO::searchForDeletion(TrieNode *root, string key, int *whichType, string *output) {
    int control = 0;
    TrieNode *pCrawl = root;

    for (char i: key) {
        int index = i - 'a';
        if (!pCrawl->children[index])
            break;

        pCrawl = pCrawl->children[index];
        control++;
    }
    if (control == key.length() && pCrawl->value != "") {
        *whichType = 1;
        *output += '"';
        *output += key;
        *output += '"';
        *output += " deletion is successful\n";

    } else if (control == 0) {
        *whichType = 2;
        *output += '"';
        *output += "no record";
        *output += '"';
        *output += "\n";


    } else if (control < key.length()) {
        *whichType = 3;
        *output += '"';
        *output += "incorrect Dothraki word";
        *output += '"';
        *output += "\n";

    } else if (control == key.length() && pCrawl->value == "") {
        *whichType = 4;
        *output += '"';
        *output += "not enough Dothraki word";
        *output += '"';
        *output += "\n";
    }
}


void IO::display(TrieNode *root, char str[], int level, vector<string> *output_list) {


    if ((isLeafNode(root) | root->value != "")) {
        str[level] = '\0';
        string a;
        a += "-";
        a += str;
        a += "(";
        a += root->value;
        a += ")";
        a += "\n";
        output_list->push_back(a);
    }

    int i;
    for (i = 0; i < 26; i++) {
        if (root->children[i]) {
            str[level] = i + 'a';
            display(root->children[i], str, level + 1, output_list);
        }
    }
}


///this function used inside display method. If we are reaching the leaf nodes that means our word is ended.
bool IO::isLeafNode(TrieNode *root) {
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL)
            return false;
    }
    return true;
}

