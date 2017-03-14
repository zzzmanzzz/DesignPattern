#include <iostream>
#include <vector>

class Recever {
private:
    int data;

public:
    Recever(int d):data(d) {}
    int& getData() {
        return data;
    }
    
    void setData(int d) {
        data = d;
    }
};

class Command
{
public:
    virtual void execute() = 0;
};

class addOne : public Command{
private:
    Recever *rec;
public:
    addOne(Recever* r) {
        rec = r;
    }
    
    void execute() {
        int t = rec->getData();
        rec->setData(t+1);
    }
};

class timesTwo : public Command{
private:
    Recever *rec;
public:
    timesTwo(Recever* r) {
        rec = r;
    }
    
    void execute() {
        int t = rec->getData();
        rec->setData(t*2);
    }
};

class Invoker {
private:
    std::vector<Command*> v;
    
public:
    void setCommand(Command* c) {
        v.push_back(c);
    }
    
    void executeAll() {
        for(int i = 0; i!= v.size(); ++i ) {
            v[i]->execute();
        }
    }
};



int main(int argc, const char * argv[]) {
    Recever *r = new Recever(55);
    std::cout << r->getData() <<std::endl;
    Command *add1 = new addOne(r);
    Command *times2 = new timesTwo(r);
    Invoker i;
    i.setCommand(add1);
    i.setCommand(times2);
    i.executeAll();
    std::cout << r->getData() <<std::endl;
    return 0;
}
