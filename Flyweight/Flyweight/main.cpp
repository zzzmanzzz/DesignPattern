#include <iostream>
#include <map>

class Flyweight{
public:
    virtual void create(std::string table) = 0;
    virtual void update(std::string data) = 0;
};


class DBUtility : public Flyweight {
private:
    std::string dbtype;
public:
    DBUtility(std::string db) {
        if(db == "mongodb") {
            dbtype = "mongo";
        } else if(db == "mysql") {
            dbtype = "mysql";
        } else {
            throw "Unknow db type :" + db;
        }
    }
    
    virtual void create(std::string table) {
        std::cout << "creat table " << table << " in " << dbtype << std::endl;
    }
    
    virtual void update(std::string data) {
        std::cout << "update data " << data << " in table " << dbtype << std::endl;
    }
    ~DBUtility(){}
    
};

class DBPool {
private:
    std::map<std::string, Flyweight*> flyweightPool;
    
public:
    DBPool(){};
    Flyweight* getDB(std::string db){
        std::map<std::string, Flyweight*>::iterator itr;
        if ( (itr = flyweightPool.find(db)) != flyweightPool.end()) {
            std::cout << "use old db " << db << std::endl;
            return itr->second;
        } else {
            std::cout << "create new db " << db << std::endl;
            Flyweight* newdb = new DBUtility(db);
            flyweightPool[db]= newdb;
            return newdb;
        }
    }
};


int main(int argc, const char * argv[]) {
    DBPool dbp;
    Flyweight* mgo = dbp.getDB("mongodb");
    mgo->create("inventory");
    mgo->update("tools");
    
    Flyweight* mysql = dbp.getDB("mysql");
    mysql->create("payment");
    mysql->update("price");
    
    Flyweight* newmysql = dbp.getDB("mysql");
    
    std::cout << "old mysql address = " << mysql << std::endl;
    std::cout << "new mysql address = " << newmysql << std::endl;
 
    
    return 0;
}
