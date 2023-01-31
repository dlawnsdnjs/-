#include <string>
#include <cstring>

class Packet{
    protected:
    std::string type;
    public:
    Packet(std::string type){
        this->type = type;
    }
    std::string getPacket(){
        return type;
    }
};

class loginPacket : public Packet{
    private:
    std::string ID;
    std::string PW;
    public:
    loginPacket(std::string ID, std::string PW):Packet("Login"){
        this->ID = ID;
        this->PW = PW;
    }
    std::string getPacket(){
        std::string packet = type + "#" + ID + "#" + PW;
        return packet;
    }
};

class registerPacket : public Packet{
    private:
    std::string ID;
    std::string PW;
    std::string NICK;
    public:
    registerPacket(std::string ID, std::string PW, std::string NICK): Packet("Register"){
        this->ID = ID;
        this->PW = PW;
        this->NICK = NICK;
    }
    std::string getPacket(){
        std::string packet = type + "#" + ID + "#" + PW + "#" + NICK;
        return packet;
    }
};

class messagePacket : public Packet{
    private:
    std::string NICK;
    std::string text;
    public:
    messagePacket(std::string NICK, std::string text):Packet("message"){
        this->NICK = NICK;
        this->text = text;
    }
    std::string getPacket(){
        std::string packet = type + "#" + text;
        return packet;
    }
};