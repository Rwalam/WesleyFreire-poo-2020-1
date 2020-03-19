#include <iostream>
#include <vector>

using namespace std;


struct Pessoa{
    int saude;
    int fome;
    int necessidades;
    int grana;
    int conta;
    

    bool trabalhar(){
        if (this->saude > 0){
            this->fome += 20;
            this->saude -= 20;
            if (this->fome > 100){
                this->fome = 100;
            }
            return true;
        }
        cout << "va se tratar\n";
        return false;
    }

    bool comer(){
        if (this->fome > 20){
            this->fome -= 20;
            this->saude += 10;
            this->necessidades += 30;
            if (this->fome > 100){
                this->fome = 100;
            }
            return true;
        }
        cout << "sem fome\n";
        return false;
    }

    bool evacuar(){
        if (this->necessidades > 0){
            this->necessidades = 0;
            this->fome += 20;
            return true;
        }
        cout << "sem vontade\n";
        return false;
    }

    Pessoa();
    ~Pessoa();

};
Pessoa::Pessoa(){
}

Pessoa::~Pessoa(){
}

struct Geladeira{
    int capacidade = 100;
    int consumo_energia = 0;
    Pessoa * p{nullptr};

    
    
    bool pagar_energia(){
        if (this->consumo_energia > 0){
            Pessoa;
            return true;
        }
        cout << "sem debito\n";
        return false;
    }
    
};


int main(){
    Pessoa * pessoa = new Pessoa();

    while (1){
        string line;
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if ((cmd == "comer")){
            pessoa->comer();
            cout<<"teste";
            cout << pessoa->saude << endl;
            cout << pessoa->fome << endl;
            cout << pessoa->necessidades << endl;
        }
        if ((key,"evacuar")){
            pessoa->evacuar();
        }
    }

    delete pessoa;
}