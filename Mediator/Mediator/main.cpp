#include <iostream>
class Colleague;
class Mediator;
class Ftp;
class Websocket;
class Server;

class Colleague {
protected:
    Mediator *mediator;
    
    Colleague(Mediator* m) {
        mediator = m;
    }
    
    virtual void sendData(std::string data) = 0;
    virtual void receiveData(std::string data) = 0;
  
};

class Mediator {
public:
    virtual void sendData(std::string data, Colleague *c) = 0;
};

class Ftp : public Mediator {
private:
    Server* sender;
    Server* receiver;
    
public:
    void setServers(Server* sender, Server* receiver) {
        this->sender = sender;
        this->receiver = receiver;
    }
    
    void sendData(std::string data, Colleague *s);
    
};

class Websocket : public Mediator {
private:
    Server* sender;
    Server* receiver;
    
public:
    void setServers(Server* sender, Server* receiver) {
        this->sender = sender;
        this->receiver = receiver;
    }
    
    void sendData(std::string data, Colleague *s);
};



class Server:public Colleague {
private:
    std::string serverName;
public:
    Server(Mediator *m, std::string name) : Colleague(m), serverName(name){}
    void sendData(std::string d) {
        mediator->sendData(d, this);
    }
    void receiveData(std::string d) {
        std::cout<< serverName <<" get data " << d << std::endl;
    }
};

void Ftp::sendData(std::string data, Colleague *s) {
    std::cout<<"send data "<< data << " via ftp" << std::endl;

    if (s == receiver) {
        receiver->receiveData(data);
    } else {
        sender->receiveData(data);
    }
}

void Websocket::sendData(std::string data, Colleague *s) {
    std::cout<<"send data "<< data << " via websocket" << std::endl;
    if (s == receiver) {
        receiver->receiveData(data);
    } else {
        sender->receiveData(data);
    }
}

int main(int argc, const char * argv[]) {
    Ftp* ftp = new Ftp();
    Websocket* websocket = new Websocket();
    
    Server* s1 = new Server(ftp, "server 1");
    Server* s2 = new Server(ftp, "server 2");
    
    Server* s3 = new Server(ftp, "server 3");
    Server* s4 = new Server(ftp, "server 4");
    
    ftp->setServers(s1, s2);
    websocket->setServers(s3, s4);
    s1->sendData("hi");
    s2->sendData("hihi");
    s3->sendData("Yo");
    s4->sendData("YoYo");

    

       return 0;
}
