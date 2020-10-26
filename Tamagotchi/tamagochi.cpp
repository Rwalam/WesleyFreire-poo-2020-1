#include <iostream>
#include "tamagochi.h"


Pet::Pet(int energyMax, int hungryMax, int cleanMax){
    this-> energyMax = energyMax;
    this-> hungryMax = hungryMax;
    this-> cleanMax = cleanMax;
    energy = energyMax;
    hungry = hungryMax;
    clean = cleanMax;
    diamonds = age = 0;
    alive = true;
}

int Pet::getClean(){
    return clean;
}

int Pet::getEnergy(){
    return energy;
}

int Pet::getHungry(){
    return hungry;
}

string Pet::toString(){
    stringstream saida;
    saida << "E:" << energy << "/" << energyMax << ", "; 
    saida << "S:" << hungry << "/" << hungryMax << ", ";
    saida << "D:" << diamonds << ", I:" << age << endl;
    return saida.str();
}

void Pet::play(){
    if (!isAlive()) return;
    energy -= 2;
    if (energy < 0)
        energy = 0;
    
    hungry -= 1;

    clean  -= 3;
    if (clean < 0)
        clean = 0;

    diamonds += 1;
    age += 1;

    process();
}

void Pet::shower(){
    if (!isAlive()) return;
    energy -= 3;
    if (energy < 0)
        energy = 0;
    
    hungry -= 1;

    clean = cleanMax;

    if (clean < 0)
        clean = 0;

    age += 2;

    process();
}

void Pet::eat(){
    if (!isAlive()) return;
    energy -= 1;
    if (energy < 0)
        energy = 0;
    
    hungry += 4;
    if (hungry > hungryMax)
        hungry = hungryMax;
    
    clean  -= 2;
    if (clean < 0)
        clean = 0;

    diamonds += 1;
    age += 1;

    process();
}

void Pet::sleep(){
    if (!isAlive()) return;

    if (energy > 5){
        cout << "fail: nao esta com sono" << endl;
        return;
    }
    
    int turnos = energyMax - energy;
    energy = energyMax;

    age += turnos;

    energy = energyMax;

    process();
}



void Pet::process(){
    if (energy == 0 || hungry == 0 || clean == 0)
        alive = false;
}
bool Pet::isAlive(){
    if(alive) return true;
    
    cout << "fail: pet esta morto" << endl;
    return false;
}


int main(){
    Pet * tam = new Pet(15,20,20);
    cout << tam->toString() << endl;
    tam->eat();
    cout << tam->toString() << endl;
    tam->sleep();
}