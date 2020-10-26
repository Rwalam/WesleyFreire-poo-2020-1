#include <iostream>
#include <sstream>

#ifndef TAMAG
#define TAMAG
using namespace std;

class Pet{
private:
    int energyMax, hungryMax, cleanMax;
    int energy, hungry, clean;
    int diamonds;
    int age;
    bool alive;
    //os metodos set são chamados pelos métodos de ação eat, sleep, ...
    void setEnergy(int value);
    void setHungry(int value);
    void setClean(int value);
    void process();
    bool isAlive();
public:
    Pet(int energyMax, int hungryMax, int cleanMax);
    int getClean();
    int getHungry();
    int getEnergy();
    int getEnergyMax();
    int getCleanMax();
    int getHungryMax();

    string toString();
    void play();
    void shower();
    void eat();
    void sleep();
    
};


#endif