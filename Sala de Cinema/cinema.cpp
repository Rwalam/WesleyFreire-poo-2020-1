#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Cliente{
    string id;
    string fone;
    bool livre;
    Cliente(string id = "", string fone = "", bool livre = true):
        id(id), fone(fone), livre(livre){}
    string toString(){
        stringstream ss;
        if (livre == true)
            ss << "- ";
        else
            ss << id << ":" << fone;
        
        return ss.str();
    }
};

struct Sala{ 
    vector<Cliente> cadeiras;

    Sala(int lotacao):
        cadeiras(lotacao){
        
    }

    string toString(){
        stringstream ss;
        for(auto cliente : cadeiras)
            ss << cliente.toString() << " ";
        return ss.str();
    }


    bool ingresar(string id,string fone, int indice){ //reservar
        //int size = sizeof(cadeiras)/sizeof(Cliente);
        if (cadeiras[indice].livre == false){
            cout << "cadeira ocupada" << endl;
            return false;   
        }
        if (indice >= (int)cadeiras.size() || indice < 0){
            cout << "indice invalido" << endl;
            return false;
        }
        for(auto cliente : cadeiras){
            if (cliente.id == id){
                cout << "já esta no cinema" << endl;
                return false;
            }
        }
        cadeiras[indice] = Cliente(id, fone, false);
        return true;
    }

    bool cancelar(string id){ //cancelar
        int indice = 0;
        for(auto cliente : cadeiras){
            if (cliente.id == id){
                cadeiras[indice].livre = true;
                return true;
            }
            indice++;
        }
        cout << "ninguem com esse nome" << endl;
        return false;
    }

};

int main(){
    Sala sala(10);
    cout << sala.toString() << endl;
    sala.ingresar("w","77", 5);
    cout << sala.cadeiras[5].livre << endl;
    sala.cancelar("w");
    cout << sala.cadeiras[5].livre << endl; 
    sala.ingresar("j","55", 4);
    cout << sala.toString() << endl;
}