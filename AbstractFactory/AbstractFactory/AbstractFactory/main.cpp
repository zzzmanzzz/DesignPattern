#include <iostream>


class Token  {
public:
    virtual void print() = 0;
    virtual ~Token(){};
};

class BigToken :public Token {
public:
    BigToken(){}
    virtual void print() {
        std::cout<< "I am big coin" <<std::endl;
    }
    ~BigToken(){}
};

class SmallToken :public Token {
public:
    SmallToken(){}
    virtual void print() {
        std::cout<< "I am small coin" <<std::endl;
    }
    ~SmallToken(){}
};

class TokenMachine {
public:
    virtual Token* getToken() = 0;
    virtual ~TokenMachine(){};
};

class BigTokenMachine : public TokenMachine {
    
public:
    BigTokenMachine(){};
    virtual Token* getToken() {
        return new BigToken();
    }
    ~BigTokenMachine(){}
    
};

class SmallTokenMachine : public TokenMachine {
public:
    SmallTokenMachine(){};
    virtual Token* getToken() {
        return new SmallToken();
    }
    ~SmallTokenMachine(){}
};



int main(int argc, const char * argv[]) {
    TokenMachine *bigMachine = new BigTokenMachine();
    TokenMachine *smallMachine = new SmallTokenMachine();
    
    Token *bt = bigMachine->getToken();
    Token *st = smallMachine->getToken();
    
    bt->print();
    st->print();
    
    delete bt;
    delete st;
    delete bigMachine;
    delete smallMachine;
   
    return 0;
}
