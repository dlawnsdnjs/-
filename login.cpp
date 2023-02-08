#include <iostream>
#include <fstream>
#include "packet.cpp"
using namespace std;


bool signup(string ID, string PW, string NICK){
    ifstream ifs(".\\userdata.txt");
    if(ifs.fail()){
        cout << "no file" << endl;
    }else{
        char line[256] = "";
        while(ifs.getline(line, 256)){
            vector<string> str = split(line, '#');
            if(ID == str.front()){
                return false;
            }
        }
    }

    ofstream ofs1(".\\userdata.txt");    
    ofs1 << ID + "#" + PW + "#" + NICK << endl;

    return true;
}

bool login(string ID, string PW){
    ifstream ifs(".\\userdata.txt");
    if(ifs.fail()){
        return false;
    }else{
        char line[256] = "";
        while(ifs.getline(line, 256)){
            vector<string> str = split(line, '#');
            if(ID == str.front()){
                if(PW == str.at(1)){
                    return true;
                }
            }
        }
    }
    return true;
}