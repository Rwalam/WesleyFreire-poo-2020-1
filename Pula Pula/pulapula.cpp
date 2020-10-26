#include <iostream>
#include <list>
#include <sstream>
using namespace std;

class Kid{
private:
    int idade;
    string nome;

public:
    Kid(int idade, string nome){
        this->idade = idade;
        this->nome = nome;
    }
    ~Kid();
    string getNome(){
        return nome;
    }
    int getIdade(){
        return idade;
    }
    string toString(){
        stringstream ss;
        ss << nome << ":" << idade;
        return ss.str();
    }
};

class Pulapula{
private:
    list<Kid*> playing;
    list<Kid*> fila;
public:
    Pulapula(){
        
    }
    ~Pulapula(){

    }

    void arrive(Kid * kid){
        fila.push_back(kid);
    }

    void in(){
        playing.push_front(fila.back());
        fila.pop_back();
    }

    void out(){
        fila.push_front(playing.back());
        playing.pop_back(); 
    }

    Kid* remove(string name){
        for(auto it = fila.begin(); it != fila.end(); it++){
            if ((*it)->getNome() == name){
                auto kid = *it;
                fila.erase(it);
                return kid;
            }
        }
        cout << "criança não encontrada" << endl;
    }

    string toSting(){
        stringstream ss;
        ss << "=> ";
        for (Kid* kid : fila){
            ss << kid->toString() << " ";
        }
        ss << " // ";
        for (Kid* kid : playing){
            ss << kid->toString() << " ";
        }
        return ss.str();
    }
    
    
};

int main(){
    Pulapula pula;
    pula.arrive(new Kid(7, "ezin"));
    pula.arrive(new Kid(8, "jake"));
    pula.arrive(new Kid(4, "enzo"));
    cout << pula.toSting() << endl;
    pula.in();
    pula.in();
    cout << pula.toSting() << endl;
    pula.out();
    cout << pula.toSting() << endl;
    pula.remove("enz");
    cout << pula.toSting() << endl;
    pula.remove("enzo");
    cout << pula.toSting() << endl;
}