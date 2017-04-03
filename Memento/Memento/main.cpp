#include <iostream>

using namespace std;

class Memento {
private:
    int state;
    
    Memento(int s) {
        state = s;
    }
    
    int getState() {
        return state;
    }
    
    void setState (int s) {
        state = s;
    }

    friend class Originator;
};


class Originator {
private:
    int state;
    
public:
    int getState() {
        return state;
    }
    
    void setState (int s) {
        state = s;
    }
    
    void setMemento(Memento *m) {
        state = m->getState();
    }
    
    Memento* getMemento() {
        return new Memento(state);
    }
};

class CareTaker {
private:
    Memento* m;
    Originator* o;
    
public:
    CareTaker(Originator* orig): o(orig) {}
    
    void execute() {
        m = o->getMemento();
        int tmp = o->getState();
        o->setState(++tmp);
    }
    
    void rollback() {
        o->setMemento(m);
    }
};



int main(int argc, const char * argv[]) {
    Originator *originator = new Originator();
    originator->setState(0);
    
    CareTaker *caretaker = new CareTaker(originator);

    cout<<  "original state "<< originator->getState() << endl;
    caretaker->execute();
    cout<<  "after execute state "<< originator->getState() << endl;

    caretaker->rollback();
    cout<<  "after rollback state "<< originator->getState() << endl;

    
    return 0;
}
