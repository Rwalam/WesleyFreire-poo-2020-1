#include <iostream>
#include <cstdio>
#include <clocale>
#include <sstream>

using namespace std;

class Carro{
private:
    float m_gas;
    float m_gasMax;
    int   m_pass;
    int   m_passMax;
    float m_km;
public:
    Carro(float gas = 0.0, float gasMax = 10, int pass = 0, int passMax = 2, float km = 0){
        m_gas = gas;
        m_gasMax = gasMax;
        m_pass = pass;
        m_passMax = passMax;
        m_km = km;
    }
    ~Carro(){
        cout << "carro destruido" << endl;
    }

    bool in(){
        if (m_pass < m_passMax)
            m_pass += 1;
        else
            cout << "fail: limite de pessoas atingido" << endl;
        
    } //embarcar

    bool out(){
        if (m_pass < m_passMax)
            m_pass -= 1;
        else
            cout << "fail: nao ha ninguem no carro" << endl;
        
    } //desembarcar

    void fuel(float value){
        if (m_gas+value < m_gasMax)
            m_gas += value;
        else
            m_gas = 100;
    } //abastecer

    bool drive(float distance){
        if (m_gas*10 >= distance && m_pass > 0){
            return true;
        }else if(m_pass <= 0){
            cout << "fail: nao ha ninguem no carro" << endl;
        }else{
            cout << "fail: gasolina insuficiente" << endl;
            return false;
        }
    } //dirigir

    string show(){
        stringstream saida;
        saida << "pass: " << m_pass << ", gas: " << m_gas << ", km: " << m_km; //nao endl
        return saida.str();
    }
};


int main(){
    Carro a;
    cout << a.show() << endl;
    a.drive(10);
    a.in();
    a.drive(10);
    a.fuel(100);
    a.show();

}


