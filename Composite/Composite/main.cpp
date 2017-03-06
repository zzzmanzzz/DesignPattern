#include <iostream>
#include <vector>

class Component {
public:
    virtual void Operation() = 0;
};

class harddisk : public Component {
private:
    std::string harddiskID;

public:
    harddisk(std::string id):harddiskID(id) {}
 
    virtual void Operation() {
        std::cout<< "HD " + harddiskID << std::endl;
    }

};


class Server : public Component {
private:
    std::vector<Component *> elements;
    std::string name;
public:
    Server(std::string n) : name(n) {}
    virtual void Operation() {
        std::cout<< "Server name : " << name << std::endl;
        for(int i = 0 ; i < elements.size(); ++i) {
            elements[i]->Operation();
        }
    }
    void add(Component * e) {
        elements.push_back(e);
    }
};


int main(int argc, const char * argv[]) {
    Server * cluster = new Server("Cluster");
    Server * serverA = new Server("alpha");
    Server * serverB = new Server("beta");
    
    serverA->add(new harddisk("1T"));
    serverA->add(new harddisk("10T"));
    
    serverB->add(new harddisk("500G"));
    serverB->add(new harddisk("800G"));

    cluster->add(serverA);
    cluster->add(serverB);
    cluster->Operation();

    
    return 0;
}
