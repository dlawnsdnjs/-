#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

class Packet{
    protected:
    string type;
    public:
    Packet(string type){
        this->type = type;
    }
    string getPacket(){
        return type;
    }
};

class loginPacket : public Packet{
    private:
    string ID;
    string PW;
    public:
    loginPacket(string ID, string PW):Packet("Login"){
        this->ID = ID;
        this->PW = PW;
    }
    string getPacket(){
        string packet = type + "#" + ID + "#" + PW;
        return packet;
    }
};

class registerPacket : public Packet{
    private:
    string ID;
    string PW;
    string NICK;
    public:
    registerPacket(string ID,string PW, string NICK): Packet("Register"){
        this->ID = ID;
        this->PW = PW;
        this->NICK = NICK;
    }
    string getPacket(){
        string packet = type + "#" + ID + "#" + PW + "#" + NICK;
        return packet;
    }
};

class messagePacket : public Packet{
    private:
    string NICK;
    string text;
    public:
    messagePacket(string NICK, string text):Packet("message"){
        this->NICK = NICK;
        this->text = text;
    }
    string getPacket(){
        string packet = type + "#" +NICK+"#"+ text;
        return packet;
    }
};

class respondPacket : public Packet{
    private:
    bool state;
    public:
    respondPacket(bool state):Packet("respond"){
        this->state = state;
    }
    string getPacket(){
        string packet = type + "#";
        if(state){
            packet += "true";
        }else{
            packet += "false";
        }
        return packet;
    }
};

vector<string> split(string input, char delimiter) {
    vector<string> result;
    stringstream ss(input);
    string tmp;
 
    while (getline(ss, tmp, delimiter)) result.push_back(tmp);
 
    return result;
}

vector<string> packetsplit(string input){
    return split(input, '#');
}