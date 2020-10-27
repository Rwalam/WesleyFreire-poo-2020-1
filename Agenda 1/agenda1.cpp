#include <iostream>
#include <list>
#include <vector>
#include <sstream>
using namespace std;

class Fone{
private:
public:
    int indice;
    string id;
    string fone;
    Fone(int indice, string id = "", string fone = ""){
        this->indice = indice;
        this->id = id;
        this->fone = fone;
    }
    static bool validar(string numero){
        string valid = "0123456789()-.";
        for (char c : numero)
            if (valid.find(c) == string::npos)
                return false;
        return true;
    }

};

ostream& operator<<(ostream& ost, const Fone& fone){
    ost << "[" << fone.indice << ":" << fone.id << ":" << fone.fone << "]";
    return ost;
}


class Contato{
private:
    string nome;
    vector<Fone> fones;
public:
    Contato(string nome = "", vector<Fone> fones = vector<Fone>()):
        nome(nome), fones(fones)
    {}
    
    bool addFone(string id,string fone){
        if (Fone::validar(fone)){
            fones.push_back(Fone(this->fones.size(), id, fone));
        }else{
            cout << "fail: telefone invalido" << endl;
        }
        
        
    }

    bool rmFone(int indice){
        if (indice < 0 || indice >= (int)fones.size())
            return false;
        
        fones.erase(fones.begin() + indice);
        for (int i = 0; i < fones.size(); i++)
            fones[i].indice = i;

    }
    int getIndice(){
        return fones.size();
    }
    string getName(){
        return nome;
    }

    vector<Fone> getFones(){
        return fones;
    }
};


ostream& operator<<(ostream& ost, Contato& contato){
    ost << "- " << contato.getName() << " ";
    for (Fone fone:contato.getFones())
        ost << fone;
    return ost;
}

template <class T>
T get(stringstream& ss){
    T t;
    ss >> t;
    return t;
}

int main(){
    Contato contato;
    while (true){
        string line, cmd;
        getline(cin, line);
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end"){
            break;
        }else if (cmd == "init"){
            contato = Contato(get<string>(ss));
        }else if (cmd == "add"){
            string id = get<string>(ss);
            string fone = get<string>(ss);
            contato.addFone(id, fone);
        }else if (cmd == "rm"){
            contato.rmFone(get<int>(ss));
            
        }else if (cmd == "show"){
            cout << contato << endl;
        }else{
            cout << "fail: comando invalido" << endl; 
        }
        
        
        
        
    }
    
}
