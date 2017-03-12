#include <iostream>

class DButility{
public:
    virtual void process() = 0;
    virtual ~DButility() {};
};

class ThirdPartyDB {
public:
    void useDB(){
        std::cout << "use 3rd party db" << std::endl;
    };
};

class Adapter : public DButility {
private:
    ThirdPartyDB* tdb;

public:
    Adapter(){
        tdb = new ThirdPartyDB();
    }
    
    virtual void process() {
        std::cout<<"use atapter drive old class" << std::endl;
        tdb->useDB();
    }
    ~Adapter(){
        delete tdb;
    }
};

int main(int argc, const char * argv[]) {
    Adapter a;
    a.process();
    
    return 0;
}
