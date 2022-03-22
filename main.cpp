#include <iostream>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "IO.h"


using namespace std;

int main(int argc, char ** arg) {
    ///READING THE FILE
    string input_file = arg[1];
    ifstream MyReadFile(input_file);
    vector<string> input_file_data;
    string output_name = arg[2];
    string myText;
    string output;
    while (getline(MyReadFile, myText)) {
        input_file_data.push_back(myText);
    }
    ofstream MyFile(output_name);
    IO io;
    vector<string> output_list;
    int level = 0;
    char str[20];

    ///In this column appropriate functions called according the input line
    for (string i: input_file_data) {
        if (i.substr(0, 1) == "i") {

            ///preparing the input
            i = i.substr(7);
            i = i.substr(0, i.length() - 1);
            istringstream ss(i);
            vector<string> my_inputs;
            string del;
            while (getline(ss, del, ',')) {
                my_inputs.push_back(del);
            }
            string key_value = my_inputs[0];
            string value = my_inputs[1];
            io.insert(io.root, key_value, value, &output);
        } else if (i.substr(0, 1) == "s") {
            i = i.substr(7);
            i = i.substr(0, i.length() - 1);
            io.search(io.root, i, &output);
        } else if (i.substr(0, 1) == "d") {
            i = i.substr(7);
            i = i.substr(0, i.length() - 1);
            int type = 0;
            io.searchForDeletion(io.root, i, &type, &output);
            if (type == 1) {
                io.remove(io.root, i,0);
            }

        } else if (i.substr(0, 1) == "l") {
            output_list.clear();
            io.display(io.root, str, level, &output_list);
            for (string i: output_list) {
                output += i;
            }
        }
        else if(i == ""){

        }

    }
    MyFile << output;
    return 0;
}


