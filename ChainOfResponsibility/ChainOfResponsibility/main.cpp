#include <iostream>

class Handler {
protected:
    Handler *successor;
    
public:
    Handler() {
        this->successor = NULL;
    }
    
    virtual double getDiscount(double price) = 0;
    
    void setSuccessor(Handler *h) {
        this->successor = h;
    }
    
    virtual ~Handler(){}
};

class LowPrice: public Handler {
public:
    LowPrice() {}
    virtual double getDiscount(double price) {
        if (this->successor != NULL && price > 100.0) {
            return this->successor->getDiscount(price);
        } else {
            return price * 0.9;
        }
    }
    ~LowPrice() {
        if(this->successor != NULL) {
            delete this->successor;
        }
    }
};

class HighPrice: public Handler {
public:
    HighPrice() {}
    virtual double getDiscount(double price) {
        if (this->successor != NULL && price > 1000.0) {
            return this->successor->getDiscount(price);
        } else {
            return price * 0.8;
        }
    }
    ~HighPrice() {
        if(this->successor != NULL) {
            delete this->successor;
        }
    }
};

int main(int argc, const char * argv[]) {
    Handler* h = new LowPrice();
    h->setSuccessor(new HighPrice());
    std::cout << "$50 get discount " << h->getDiscount(50.0) << std::endl;
    std::cout << "$5000 get discount " << h->getDiscount(5000.0) << std::endl;
    
    

    return 0;
}
