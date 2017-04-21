#include <iostream>

class Strategy {
public:
    virtual void applyAlgorithm() = 0;
    virtual ~Strategy(){}
};

class ConcreteStrategyA : public Strategy {
public:
    void applyAlgorithm() {
        std::cout << "A apply algorithm" << std::endl;
    }
    
    ~ConcreteStrategyA(){}
};

class ConcreteStrategyB : public Strategy {
public:
    void applyAlgorithm() {
        std::cout << "B apply algorithm" << std::endl;
    }
    
    ~ConcreteStrategyB(){}

};

class Context {
private:
    Strategy* strategy;
    
public:
    
    void setStrategy(Strategy* s) {
        if (strategy != NULL) {
            delete strategy;
        }
        
        strategy = s;
    }
    
    Strategy* getStrategy() {
        return strategy;
    }
    
    void run() {
        strategy->applyAlgorithm();
    }
    
    ~Context(){
        if (strategy != NULL) {
            delete strategy;
        }
    }
    
    
};


int main(int argc, const char * argv[]) {
    Context c;
    c.setStrategy(new ConcreteStrategyA());
    c.run();
    c.setStrategy(new ConcreteStrategyB());
    c.run();
    
    
    
    return 0;
}
