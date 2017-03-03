#include <iostream>

class Singleton {
private:
    static Singleton* s;
    std::string data;
    Singleton(){};

public:
    static Singleton* getInstance() {
        if (s != NULL) {
            return s;
        } else {
            s = new Singleton();
            s->setData("I am Singleton");
            return s;
        }
    }
    
    void setData(std::string d) {
        data = d;
    }
    
    void showData() {
        std::cout << data << std::endl;
    }

};

Singleton * Singleton::s = NULL;

int main(int argc, const char * argv[]) {
    Singleton* ins = Singleton::getInstance();
    ins->showData();
    
    return 0;
}
