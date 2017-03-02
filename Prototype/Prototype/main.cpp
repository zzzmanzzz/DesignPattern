#include <iostream>

class Prototype {
public:
    virtual Prototype* clone() = 0;
    virtual void use() = 0;
    virtual ~Prototype() {};
};

class PrototypeA : public Prototype {
private:
    std::string data;

public:
    PrototypeA(std::string s):data(s){}
    virtual void use() {
        std::cout << data << std::endl;
    }
    virtual Prototype* clone() {
        return new PrototypeA(data);
    }
};

int main(int argc, const char * argv[]) {
    Prototype* z = new PrototypeA("ZZZZ");
    Prototype* a = z->clone();
    std::cout <<"address of z " << &z << std::endl;
    std::cout <<"address of a " << &a << std::endl;
    a->use();
    return 0;
}
