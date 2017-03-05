#include <iostream>

class MobileGame{
public:
    virtual void play() = 0;
};

class Plateform {
public:
    virtual void display(std::string) = 0;
};

class Android : public Plateform {
public:
    virtual void display(std::string s) {
        std::cout<< "Android display :" << s << std::endl;
    }
};

class iPhone : public Plateform {
public:
    virtual void display(std::string s) {
        std::cout<< "iPhone display :" << s << std::endl;
    }
};


class AgeOfTrump : public MobileGame {
private:
    Plateform *plateform;
    
public:
    AgeOfTrump(Plateform* p) {
        this->plateform = p;
    }
    
    virtual void play() {
        plateform->display("AgeOfTrump");
        
    }
};

class AgeOfTrumpEnhancement : public MobileGame {
private:
    Plateform *plateform;
    
public:
    AgeOfTrumpEnhancement(Plateform* p) {
        this->plateform = p;
    }
    
    virtual void play() {
        plateform->display("AgeOfTrumpEnhancement");
        
    }
};


int main(int argc, const char * argv[]) {
    MobileGame* androidCommon = new AgeOfTrump(new Android());
    androidCommon->play();
    
    MobileGame* iPhoneCommon = new AgeOfTrump(new iPhone());
    iPhoneCommon->play();
    
    MobileGame* androidEnhancement = new AgeOfTrumpEnhancement(new Android());
    androidEnhancement->play();
    
    MobileGame* iPhoneEnhancement = new AgeOfTrumpEnhancement(new iPhone());
    iPhoneEnhancement->play();

    
    return 0;
}
