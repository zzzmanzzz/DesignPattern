#include <iostream>

class WebClientInterface {
public:
    virtual void getData() = 0;
};

class WebClient : public WebClientInterface {
public:
    WebClient(){
        std::cout << "heavy initialization process" << std::endl;
    }
    void getData() {
        std::cout << "get data"<< std::endl;
    }
};

class Proxy : public WebClientInterface {
public:
    Proxy(){}
    void getData(){
        std::cout << "call from Proxy" << std::endl;
        WebClient wc;
        wc.getData();
    }
};


int main(int argc, const char * argv[]) {
    Proxy p;
    p.getData();
    return 0;
}
