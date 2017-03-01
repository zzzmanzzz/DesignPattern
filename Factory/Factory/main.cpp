#include <iostream>


class Device {
protected:
    std::string spec;
public:
    virtual void show()=0;
};

class DeviceFactory {
private:
    Device* dev;
    
public:
    virtual Device* createDevice() = 0 ;
    Device* newDevice(){
        dev = createDevice();
        return dev;
    };
};

class Smartphone : public Device {

    
public:
    Smartphone() {
        spec = "smaptphone";
    }
    virtual void show() {
        std::cout << spec << std::endl;
    }
};

class Notebook : public Device {
private:
    std::string spec;
    
public:
    Notebook() {
        spec = "notebook";
    }
    virtual void show() {
        std::cout << spec << std::endl;
    }
};

class SmartphoneFactory : public DeviceFactory{
public:
    virtual Smartphone* createDevice() {
        return new Smartphone();
    }
};

class NotebookFactory : public DeviceFactory {
public:
    virtual Notebook* createDevice () {
        return new Notebook();
    }
};


int main(int argc, const char * argv[]) {
    DeviceFactory* notebookFactory = new NotebookFactory();
    DeviceFactory* smartphoneFactory = new SmartphoneFactory();
    
    Device* nb = notebookFactory->newDevice();
    Device* sp = smartphoneFactory->newDevice();
    
    nb->show();
    sp->show();
    
    
    return 0;
}
