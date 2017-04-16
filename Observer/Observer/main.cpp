#include <iostream>
#include<vector>

class Subject;

class Observer {
public:
    Subject *sub;
    virtual void update() = 0;
};

class Subject {
public:
    std::vector<Observer *> observers;
    
    void attach(Observer *o) {
        observers.push_back(o);
    }
    
    void detach(Observer *o) {}
    
    void notify() {
        for(int i = 0 ; i < observers.size(); ++i) {
            observers[i]->update();
        }
    }
    
    virtual void setState(int s) = 0;
    virtual int getState() = 0;
};

class ConcreteSubject :public Subject{
private:
    int state;

public:
    void setState(int s) {
        state = s;
        notify();
    }
    
    int getState() {
        return state;
    }

};



class ConcreteObserverA : public Observer {
private:
    int state;
    
public:
    ConcreteObserverA(Subject *s) {
        this->sub = s;
        this->sub->attach(this);
    }
    
    void update() {
        state = sub->getState();
        std::cout<< "ConcreteObserverA update state : " << state<< std::endl;
    }
    
};

class ConcreteObserverB : public Observer {
private:
    int state;
    
public:
    ConcreteObserverB(Subject *s) {
        this->sub = s;
        this->sub->attach(this);
    }
    
    void update() {
        state = sub->getState();
        std::cout<< "ConcreteObserverB update state : " << state<< std::endl;
    }
    
};


int main(int argc, const char * argv[]) {
    Subject* S = new ConcreteSubject();
    Observer* A  = new ConcreteObserverA(S);
    Observer* B  = new ConcreteObserverB(S);
    S->setState(999);
    
    
    return 0;
}
