#include <iostream>
#include <list>
#include <sstream>
using namespace std;

class Espiral{
private:
    string nome;
    int qtd;
    float preco;
public:
    Espiral(string nome = "empty", int qtd = 0, float preco = 0.0):
    nome(nome), qtd(qtd), preco(preco){}

    string toString(){
        stringstream ss;
        ss << " [ "<< nome << " : "<< qtd << " U : " << preco << " RS]";
        return ss.str();
    }

    string getNome(){return nome;}
    int getQtd(){return qtd;}
    float getPreco(){return preco;}
    void setNome(string nome){this->nome = nome;}
    void setQtd(int qtd){this->qtd = qtd;}
    void setPreco(float preco){this->preco = preco;}
    
};


class Junkfood{
private:
    list<Espiral> espirais;
    float saldo;
    int prodMax;

public:
    Junkfood(int nEsps, int prodMax){
        this->prodMax = prodMax;
        for(int i = 0; i < nEsps; i++)
            espirais.push_back(Espiral());
    }

    string toString(){
        stringstream ss;
        int n = 0;
        ss << "saldo: " << saldo << endl;
        for (Espiral espiral : espirais)
            ss << n++ << espiral.toString() << endl;

        return ss.str();
    }

    bool inserirDinheiro(float valor){
        saldo += valor;
    }

    float pedirTroco(){
        cout << "voce recebeu " << saldo << "RS" << endl;
        saldo = 0;
    }

    bool vender(int indice){
        if (indice >= espirais.size()){
            cout << "fail: indice nao existe" << endl;
            return false;
        }

        int n = 0;
        for(auto it = espirais.begin(); it != espirais.end(); it++){
            if (n == indice){
                if ((*it).getQtd() == 0){
                   cout << "fail: espiral sem produtos" << endl;
                   return false;
                }
                if ((*it).getPreco() > saldo){
                    cout << "fail: saldo insuficiente" << endl;
                    return false;
                }
                
                (*it).setQtd((*it).getQtd()-1);
                cout << "voce comprou um " << (*it).getNome() << endl;
                return true;
            }

            n++;
        }
            
    }

    bool alterarEspiral(int indice, string nome, int qtd, float preco){
        if (indice >= espirais.size()){
            cout << "fail: indice nao existe" << endl;
            return false;
        }
        if (qtd > prodMax){
            cout << "fail: limite excedido" << endl;
            return false;
        }

        int n = 0;
        for(auto it = espirais.begin(); it != espirais.end(); it++){
            if (n == indice){
                (*it).setNome(nome);
                (*it).setQtd(qtd);
                (*it).setPreco(preco);
                return true;
            }
            n++;
        }
    }

    float getSaldo(){return saldo;}

};


int main(){
    Junkfood maquina(5, 5);

    while(true){
        cout << "digite um comando" << endl;
        string line, cmd;
        getline(cin, line);
        stringstream ss(line);
        ss >> cmd;
        if(cmd == "end"){
            break;
        }
        if (cmd == "show"){
           cout << maquina.toString() << endl;
        }
        if (cmd == "set"){
            int indice;
            string nome;
            int qtd;
            float preco;
            ss >> indice >> nome >> qtd >> preco;
            maquina.alterarEspiral(indice, nome, qtd, preco);
        }
        if (cmd == "dinheiro"){
            float valor;
            ss >> valor;
            maquina.inserirDinheiro(valor);
        }
        if (cmd == "troco"){
            maquina.pedirTroco();
        }
        if (cmd == "comprar"){
            int indice;
            ss >> indice;
            maquina.vender(indice);
        }
        cout << "fail: Comando inexistente" << endl;
    }

}
