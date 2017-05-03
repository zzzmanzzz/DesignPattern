#include <iostream>
#include <vector>

class Visitor;

class Element{
public:
    virtual void Accept(Visitor &) = 0;
};

class ConcreteElement:public Element{
public:
    void Accept(Visitor &v);
};

class Visitor {
public:
    virtual void VisitConcreteElement(ConcreteElement *) = 0;
};

class ConcreteVisitor : public Visitor {
public:
    void VisitConcreteElement(ConcreteElement *) {
        std::cout << "ConcreteVisitor::VisitConcreteElement()\n";
    }
    
};

void ConcreteElement::Accept(Visitor &v) {
    std::cout << "ConcreteElement::Accept()\n";
    v.VisitConcreteElement(this);
}

int main(int argc, const char * argv[]) {
    std::vector<Element*> elements;
    ConcreteElement *ele = new ConcreteElement();

    elements.push_back(ele);
    
    ConcreteVisitor * visitor = new ConcreteVisitor();

    for (int i=0; i < elements.size(); i++)
    {
        elements[i]->Accept(*visitor);
    }
    
     return 0;
}
