#include <iostream>

class Salary {
public:
    virtual double getSalary() = 0;
    virtual ~Salary(){}
};


class PrimarySalary : public Salary {
private:
    double salary;
    
public:
    PrimarySalary(){
        salary = 0;
    }
    
    PrimarySalary(double salary) {
        this->salary = salary;
    }
    
    double getSalary() {
        std::cout << "Primary salary is: " << salary << std::endl;
        return salary;
    }
};


class Decorator : public PrimarySalary {
private:
    PrimarySalary *ps;
    
public:
    Decorator(PrimarySalary *p) {
        ps = p;
    }
    
    double getSalary() {
        return ps->getSalary();
    }
    
    ~Decorator() {
        delete ps;
    }

};


class TeamBonus : public Decorator {
public:
    TeamBonus(PrimarySalary *p):Decorator(p) {}
    double getSalary() {
        double tmp = Decorator::getSalary();
        std::cout<< "Team bonus is: " << tmp * 0.2 << std::endl;
        return tmp * 1.2;
    }
};

class PersonalBonus : public Decorator {
public:
    PersonalBonus(PrimarySalary *p):Decorator(p) {}
    double getSalary() {
        double tmp = Decorator::getSalary();
        std::cout<< "Personal bonus is: " << tmp * 0.1 << std::endl;
        return tmp * 1.1;
    }
};


int main(int argc, const char * argv[]) {
    Salary *p = new PersonalBonus(new TeamBonus(new PrimarySalary(20000)));
    double totalSalary = p->getSalary();
    std::cout << "total salary is: "<< totalSalary << std::endl;
    delete p;
    return 0;
}
