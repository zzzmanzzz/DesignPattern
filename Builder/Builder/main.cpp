#include <iostream>
#include <string>


class DeviceBuilder {
public:
    virtual void create () = 0;
    virtual void setScreen() {};
    virtual void setKeyboard() {};
    virtual void setTouchscreen() {};
};


class DeviceCreater {
private:
    DeviceBuilder* devBuilder;
public:
    DeviceCreater(){};
    void setBuilder(DeviceBuilder* d) {
        
        devBuilder = d;
    }
    
    void createDevice(std::string dev) {
    
        if (dev == "smartphone") {
            devBuilder->create();
            devBuilder->setTouchscreen();
        }
        else if (dev == "notebook") {
            devBuilder->create();
            devBuilder->setKeyboard();
            devBuilder->setScreen();
        } else {
            std::cout << "unknown type " << dev << std::endl;
            exit(1);
        }
        
    }
};

class Notebook {
public:
    std::string screen;
    std::string keyboard;
    Notebook(){}
    void setScreen(std::string s) {
        screen = s;
    }
    void setKeyboard(std::string k) {
        keyboard = k;
    }
    
    void spec() {
        std::cout << "Notebook has " << screen << ", "<< keyboard <<std::endl;
    }
};

class Smartphone {
private:
    std::string touchscreen;

public:
    Smartphone(){}
    void setTouchscreen(std::string t) {
        touchscreen = t;
    }
    
    void spec() {
        std::cout << "Smartphone has " << touchscreen <<std::endl;
    }
};

class NotebookBuilder : public DeviceBuilder {
private:
    Notebook *nb;
    
public:
    NotebookBuilder(){};
    virtual void create() {
        std::cout<< "creating notebook" << std::endl;
        nb = new Notebook();
        
    }
    
    virtual void setScreen() {
        std::cout << " set 4K screen" << std::endl;
        nb->setScreen("4K");
    }
    
    virtual void setKeyboard() {
        std::cout << " set common keyboard" << std::endl;
        nb->setKeyboard("common keyboard");
    }
    
    Notebook* getNotebook() {
        return nb;
    }

};


class SmartphoneBuilder : public DeviceBuilder {
private:
    Smartphone *sp;
    
public:
    SmartphoneBuilder(){};
    virtual void create() {
        std::cout<< "creating smartphone" << std::endl;
        sp = new Smartphone();
        
    }
    
    virtual void setTouchscreen() {
        std::cout << " set Retina screen" << std::endl;
        sp->setTouchscreen("Retina");
    }
    
    Smartphone* getSmartphone() {
        return sp;
    }
    
};




int main(int argc, const char * argv[]) {
    SmartphoneBuilder* sb = new SmartphoneBuilder();
    DeviceCreater dc;
    
    dc.setBuilder(sb);
    dc.createDevice("smartphone");
    Smartphone* s = sb->getSmartphone();
    s->spec();
    
    NotebookBuilder* nb = new NotebookBuilder();
    dc.setBuilder(nb);
    dc.createDevice("notebook");
    Notebook* n = nb->getNotebook();
    n->spec();
    
    return 0;
}
