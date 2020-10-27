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
    Contato(string nome = "", vector<Fone>fones = vector<Fone>()):
        nome(nome), fones(fones){}
    
    bool addFone(string id,string fone){
        if (Fone::validar(fone)){
            fones.push_back(Fone(this->fones.size(), id, fone));
            return true;
        }
        cout << "fail: telefone invalido" << endl;
        return false;
    }

    bool rmFone(int indice){
        if (indice < 0 || indice >= (int)fones.size())
            return false;
        
        fones.erase(fones.begin() + indice);
        for (int i = 0; i < (int)fones.size(); i++)
            fones[i].indice = i;
        return true;
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

    string toString(){
        stringstream ss;
        ss << nome;
        for (int i = 0; i < (int)fones.size(); i++)
            ss << fones[i];
        return ss.str();
    }
};


ostream& operator<<(ostream& ost, Contato& contato){
    ost << "- " << contato.getName() << " ";
    for (Fone fone:contato.getFones())
        ost << fone;
    return ost;
}



class Agenda{
private:
    vector<Contato>contatos;
public:
    Agenda(vector<Contato>contatos = vector<Contato>()):
    contatos(contatos){}

    int findContato(string nome){
        for (int i = 0; i < (int)contatos.size(); i++)
            if (contatos[i].getName() == nome)
                return i;
        cout << "fail: nome nao existe" << endl;
        return -1;
    }

    bool addContato(string nome, vector<Fone> fones){
        for (int i = 0; i < (int)contatos.size(); i++){
            if (contatos[i].getName() == nome){
                cout << "usuario ja existe: incluindo numeros" << endl;
                for (int j = 0; j < (int)fones.size(); j++)
                    contatos[i].addFone(fones[j].id, fones[j].fone);
                return true;
            }
        }
        contatos.push_back(Contato(nome, fones));
        return true;

    }

    bool rmContato(string nome){
        for (int i = 0; i < (int)contatos.size(); i++){
            if (contatos[i].getName() == nome){
                contatos.erase(contatos.begin() + i);
                return true;
            }
        }
        cout << "fail: nome nao existe" << endl;
        return false;
    }

    vector<Contato> search(string patern){
        vector<Contato> saida;
        for (int i = 0; i < (int)contatos.size(); i++){
            //vector<Fone> fones = contatos[i].getFones();
            string contatoinfo = contatos[i].toString();
            if (contatoinfo.find(patern) != string::npos)
                saida.push_back(contatos[i]);
        }
        if (saida.size() == 0)
            cout << "fail: nenhum resultado encontrado" << endl;
        
        return saida;
    }
        

    vector<Contato> getContatos(){
        return contatos;
    }

    Contato* getContato(string nome){
        int ind = findContato(nome);
        return &contatos[ind];
    }

};
ostream& operator<<(ostream& ost, Agenda& agenda){
    //vector<Contato> contatos = agenda.getContatos();
    for (Contato contato:agenda.getContatos())
        ost << contato << endl;
    
    return ost;
}

template <class T>
T get(stringstream& ss){
    T t;
    ss >> t;
    return t;
}

int main(){
    Agenda agenda;
    while (true){
        string line, cmd;
        getline(cin, line);
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end"){
            break;
        }else if (cmd == "addFone"){ //cmds da agenda1 atualizados para agenda2
            int indice = get<int>(ss);
            string id = get<string>(ss);
            string fone = get<string>(ss);
            agenda.getContatos()[indice].addFone(id, fone);

        }else if (cmd == "rmFone"){ // pos na agenda, 
            int indice = get<int>(ss);
            agenda.getContatos()[indice].rmFone(get<int>(ss));
            
        }else if (cmd == "showContato"){ 
            int indice = get<int>(ss);
            cout << agenda.getContatos()[indice] << endl;

        }else if (cmd == "agenda"){ //AGENDA
            if (!(agenda.getContatos().empty()))
                cout << agenda << endl;
            else
                cout << "vazio" << endl;
            
        }else if (cmd == "findbyN"){ 
            string nome = get<string>(ss);
            agenda.findContato(nome);

        }else if (cmd == "search"){
            string patern = get<string>(ss);
            vector<Contato> contatos = agenda.search(patern);
            for(Contato contato:contatos)
                cout << contato << endl;

        }else if (cmd == "addContato"){ 
            string nome = get<string>(ss);
            
            string id_fone; 
            vector<Fone> fones;
            while (ss >> id_fone){
                stringstream sif(id_fone);
                string i, f;
                getline(sif, i,':');
                sif >> f;
                fones.push_back(Fone(fones.size(),i,f));
            }
            agenda.addContato(nome,fones);
            
        }else if (cmd == "rmContato"){
            string nome = get<string>(ss);
            agenda.rmContato(nome);

        }else{
            cout << "fail: comando invalido" << endl; 
        }
    
    }
    
}

