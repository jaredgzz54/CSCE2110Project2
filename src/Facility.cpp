#include "Facility.h"
#include <iostream>

Facility::Facility() : ID(""), Name(""), Building (""), Category(""){}
Facility::Facility(std::string id, std::string name, std::string building, std::string category): ID(id), Name(name), Building(building), Category(category){}
Facility::~Facility()
{
    cout << "Destructor has been called" << endl;
}


//mutators
void Facility::setID(std::string id)
{
    ID = id;
}
void Facility::setName(std::string name)
{
    Name = name;
}
void Facility::setBuilding(std::string building)
{
    Building = building;
}
void Facility::setCategory(std::string category)
{
    Category = category;
}



//accessors
std::string Facility::getId() const{return ID;}
std::string Facility::getName() const {return Name; }
std::string Facility::getBuilding() const {return Building;}
std::string Facility::getCategory() const {return Category;}

void Facility::display() const 
{
    std::cout << ID << " | " << Name << " | " << Building << " | " << Category << std::endl;
}