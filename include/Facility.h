#ifndef FACILITY_H
#define FACILITY_H

#include <string>

class Facility 
{
private:
    std::string ID;       
    std::string Name;     
    std::string Building; 
    std::string Category; 

public:
    
    Facility();//constructor
    Facility(std::string id, std::string name, std::string building, std::string category);//constructor overloader
    ~Facility();//destructor

    //mutators
    void setID(std::string id);
    void setName(std::string name);
    void setBuilding(std::string building);
    void setCategory(std::string category);

    //accessors
    std::string getId() const;
    std::string getName() const;
    std::string getBuilding() const;
    std::string getCategory() const;

    void display() const;
};

#endif
