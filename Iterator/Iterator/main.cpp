#include <iostream>
#include <vector>

class Iterator;
class ConcreteIterator;

class Iterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual std::string currentItem() = 0;
};



class DataSet {
public:
    virtual Iterator* createIterator() = 0;
};

class ConcreteDataSet : public DataSet {
private:
    std::vector<std::string>* v;
public:
    Iterator* createIterator();
    
    ConcreteDataSet(){
        v = new std::vector<std::string>();
    }
    
    long size() {
        return v->size();
    }
    
    void add(std::string a) {
        v->push_back(a);
    }
    
    std::string getData(long i) {
        return v->at(i);
    }
    
    ~ConcreteDataSet(){
        delete v;
    }
};

class ConcreteIterator : public Iterator {
private:
    ConcreteDataSet* dataset;
    long currentIndex;
    
public:
    ConcreteIterator() {
        currentIndex = 0;
        this->dataset = new ConcreteDataSet();
    }
    
    ConcreteIterator(ConcreteDataSet* d) {
        this->dataset = d;
    }
    
    void first () {
        currentIndex = 0;
    }
    
    void next() {
        currentIndex++;
    }
    
    bool isDone() {
        return currentIndex >= dataset->size();
    }
    
    std::string currentItem() {
        return dataset->getData(currentIndex);
    }
};

Iterator* ConcreteDataSet::createIterator() {
    return new ConcreteIterator(this);
};

int main(int argc, const char * argv[]) {
    ConcreteDataSet *obj = new ConcreteDataSet();
    obj->add("Tea");
    obj->add("Juice");
    obj->add("Water");
    obj->add("Meal");
    
    Iterator *itr = obj->createIterator();
    for (itr->first(); !(itr->isDone()); itr->next()){
        std::cout << "Your Order is " << itr->currentItem() << std::endl;
    }
    return 0;
}
