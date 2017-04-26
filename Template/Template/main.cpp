#include <iostream>

class TemplateClass {
public:
    void method() {
        std::cout << "call template method" << std::endl;
        opA();
        opB();
    }
    
    virtual void opA() = 0;
    virtual void opB() = 0;
};

class ConcreteTemplate : public TemplateClass {
public:
    void opA() {
        std::cout << "call opA method" << std::endl;
    }
    
    void opB() {
        std::cout << "call opB method" << std::endl;
    }
};


int main(int argc, const char * argv[]) {
    TemplateClass* t = new ConcreteTemplate();
    t->method();
    return 0;
}
