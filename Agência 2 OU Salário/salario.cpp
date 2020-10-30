#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

class Funcionario{
protected:
    string nome;
    int max_diarias; //o maximo de diarias que ele pode receber
    int qtd_diarias; //a qtd de diarias que ja recebeu
    double bonus; //o quanto de bonus ele recebeu

public:
    Funcionario(string nome = "", int max_diarias = 0):
        nome(nome), max_diarias(max_diarias), qtd_diarias(0), bonus(0.0){}

    void addDiaria(){
        if (qtd_diarias >= max_diarias){
            cout << "fail: limite de diarias atingido" << endl;
            return;
        }
        qtd_diarias++;
        
    }

    void setBonus(double bonus){
        this->bonus = bonus;
    }

    virtual string toString(){
        return "erro: toString da classe full virtual";
    };
    
    virtual double calcSalario() = 0; //calculo parcial das diarias e o bonus

    
};

class Professor : public Funcionario{
private:
    char classe;

public:
    Professor(string nome = "", char classe = ' ')
    : Funcionario{nome, 2}, classe{classe}{} 

    double calcSalario(){//sobrescreve adicionando o calculo do salario
        double valor = qtd_diarias * 100 + bonus;
        valor += ((int)(classe - 'A') * 2000 ) + 3000;
        return valor;
        
    }
    string toString(){
        stringstream ss;
        ss << "Prof " << nome << " " << "classe " << classe << "\nsalario " << this->calcSalario();
        return ss.str();
    }
};

class STA : public Funcionario{
private:
    int nivel;
    
public:
    STA(string nome = "", int nivel = 0)
    :Funcionario{nome, 1}, nivel{nivel}{}

    double calcSalario(){ //sobrescreve adicionando o calculo do salario
        double valor = qtd_diarias * 100 + bonus;
        valor += 3000 + 300 * nivel;
        return valor;
    }

    string toString(){
        stringstream ss;
        ss << "Sta " << nome << " " << "nivel " << nivel << "\nsalario " << this->calcSalario();
        return ss.str();
    }
   
};

class Terceirizado : public Funcionario{
private:
    int horas_trab;
    bool insalubre;
    
public:
    Terceirizado(string nome = "", int horas_trab = 0, bool insalubre = false)
    :Funcionario{nome, 0}, horas_trab(horas_trab), insalubre(insalubre){}

    double calcSalario(){ //sobrescreve adicionando o calculo do salario
        double valor = (4 * horas_trab) + (insalubre ? 500 : 0);
        return valor;
    }

    /* void addDiaria(){ 
        cout << "fail: terc nao pode receber diaria" << endl;
    } */

    string toString(){
        stringstream ss;
        string ins = insalubre?"insalubre":"naoInsalubre";
        ss << "Ter " << nome << " " << horas_trab << "h " << ins << "\nsalario " << this->calcSalario();
        return ss.str();
    }

};
    
/* ostream& operator<<(ostream& ost, Agenda& agenda){
    //vector<Contato> contatos = agenda.getContatos();
    for (Contato contato:agenda.getContatos())
        ost << contato << endl;
    
    return ost;
} */

template <class T>
T get(stringstream& ss){
    T t;
    ss >> t;
    return t;
}



int main(){
    map<string, Funcionario*> funcionarios;

    while (true){
        string line, cmd;
        getline(cin, line);
        stringstream ss(line);
        ss >> cmd;
        
        if (cmd == "end"){
            break;
        }else if (cmd == "addProf"){
            string nome = get<string>(ss);
            char classe = get<char>(ss);
            Funcionario* pro =  new Professor(nome, classe);
            funcionarios.insert(make_pair(nome, pro));

        }else if (cmd == "addSta"){
            string nome = get<string>(ss);
            int nivel = get<int>(ss);
            Funcionario* sta =  new STA(nome, nivel);
            funcionarios.insert(make_pair(nome, sta));

        }else if (cmd == "addTer"){
            string nome = get<string>(ss);
            int horas_trab = get<int>(ss);
            bool insalubre = (get<string>(ss) == "sim" ? 1:0);
            Funcionario* ter = new Terceirizado(nome, horas_trab, insalubre);
            funcionarios.insert(make_pair(nome, ter));

        }else if (cmd == "show"){
            string nome = get<string>(ss);
            cout << funcionarios.find(nome)->second->toString() << endl;

        }else if (cmd == "all"){
            int c = 1;
            for (auto& func : funcionarios){
                
                cout << c++ << "- " << func.second->toString() << endl;
                
            }
        }else if (cmd == "setBonus"){
            double calc = (double)get<double>(ss) / funcionarios.size();
            for (auto& func : funcionarios)
                func.second->setBonus(calc);
                

        }else{
            cout << "comando invalido" << endl; 
        }
        
    }

}
