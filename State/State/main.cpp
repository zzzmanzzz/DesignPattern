//
//  main.cpp
//  State
//
//  Created by wyatt on 2017/4/17.
//  Copyright © 2017年 wyatt. All rights reserved.
//

#include <iostream>

class State;

class Context {
private:
    State *state;
    
public:
    Context(State* s) {
        state = s;
    }
    
    void setState(State *s) {
        state = s;
    }
    
    State * getState() {
        return state;
    }
    void request();
};


class State {

public:
    virtual void handle(Context *c) = 0;
    virtual ~State(){};
};


class ConcreteStateA : public State {
public:
    void handle(Context *c);
};


class ConcreteStateB : public State {
public:
    void handle(Context *c);
};

void ConcreteStateA::handle(Context* c) {
    std::cout << "Handle State A" << std::endl;
    State *s = c->getState();
    if (s != NULL){
       // std::cout << "delete" << std::endl;
        delete s;
    }
    c->setState(new ConcreteStateB());
}

void ConcreteStateB::handle(Context* c) {
    std::cout << "Handle State B" << std::endl;
    State *s = c->getState();
    if (s != NULL){
       // std::cout << "delete" << std::endl;
        delete s;
    }
    c->setState(new ConcreteStateA());
}

void Context::request() {
    state->handle(this);
}

int main(int argc, const char * argv[]) {
    ConcreteStateA *sA = new ConcreteStateA();
    Context *c = new Context(sA);
    for(int i = 0; i < 20; ++i){
        c->request();
    }
    return 0;
}
