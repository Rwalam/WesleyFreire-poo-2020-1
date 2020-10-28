#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <map>
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

    int getIndice(){return indice;}
    void setIndice(int indice){
        this->indice = indice;
    }
    string getID(){return id;}
    void setID(string id){
        this->id = id;
    }
    string getFone(){return fone;}
    void setFone(string fone){
        this->fone = fone;
    }

    friend ostream& operator<<(ostream& ost, Fone& fone){
    ost << "[" << fone.indice << ":" << fone.id << ":" << fone.fone << "]";
    return ost;
    }

};





class Contato{
private:
    string nome;
    vector<Fone> fones;
    bool favorited;
public:
    Contato(string nome = "", vector<Fone>fones = vector<Fone>(),bool favorited = false):
        nome(nome), fones(fones), favorited(favorited){}
    
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
            fones[i].setIndice(i);
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

    bool getFavorited(){
        return favorited;
    }

    void setFavorited(bool a){
        favorited = a;
    }

    string toString(){
        stringstream ss;
        ss << nome;
        for (int i = 0; i < (int)fones.size(); i++)
            ss << fones[i];
        return ss.str();
    }

    friend bool favoritar(string nome);
    friend ostream& operator<<(ostream& ost, Contato& contato);
};

ostream& operator<<(ostream& ost, Contato& contato){
    ost << ((contato.favorited == true) ? "@ " : "- ") << contato.nome << " ";
    for (Fone fone:contato.fones)
        ost << fone;
    return ost;
}





class Agenda{
private:
    //vector<Contato>contatos;
    //vector<Contato>favoritos;
    map<string, Contato*>contatos; //ADAPTAR O CODIGO PARA MAP
    map<string, Contato*>favoritos;
public:
    Agenda(map<string, Contato*>contatos = map<string, Contato*>()):
    contatos(contatos){}

    Contato* findContato(string nome){
        auto it = contatos.find(nome);
            if (it->second->getName() == nome)
                return it->second;
        cout << "fail: nome nao existe" << endl;
        return nullptr;
    }

    bool addContato(string nome, vector<Fone> fones){
        for (auto contato : contatos){
            if (contato.second->getName() == nome){//se ja existe incluir numeros
                cout << "usuario ja existe: incluindo numeros" << endl;
                for (int j = 0; j < (int)fones.size(); j++)
                    contato.second->addFone(fones[j].id, fones[j].fone);
                return true;
            }
        }
        Contato co = Contato(nome, fones, false);
        contatos.insert(make_pair(nome, new Contato(nome, fones, false)));
        return true;
    }

    bool rmContato(string nome){
        if (contatos.erase(nome)){
            favoritos.erase(nome);
            return true;
        }
        cout << "fail: nome nao existe" << endl;
        return false;
    }

    vector<Contato> search(string patern){
        vector<Contato> saida;
        for (auto contato : contatos){
            //vector<Fone> fones = contato.second->getFones();
            string contatoinfo = contato.second->toString();
            if (contatoinfo.find(patern) != string::npos)
                saida.push_back(*contato.second);
        }
        if (saida.size() == 0)
            cout << "fail: nenhum resultado encontrado" << endl;
        
        return saida;
    }

    vector<Contato> getContatos(){
        vector<Contato> saida;
        for (auto contato: contatos){
            saida.push_back(*contato.second);
        }
        return saida;
    }

    vector<Contato> getFavoritos(){
        vector<Contato> saida;
        for (auto contato: favoritos)
            saida.push_back(*contato.second);
        
        if (saida.size() == 0)
            cout << "nenhum contato favoritado" << endl;
        
        return saida;
    }

    Contato* getContato(string nome){
        return (contatos.find(nome) == contatos.end()) ? nullptr : contatos.at(nome);
    }

    bool favoritar(string nome){
        auto contato = contatos.find(nome);
        if (contato == contatos.end()){
            cout << "fail: contato nao existe" << endl;
            return false;
        }

        if(contato->second->getFavorited() == true){
            cout << "fail: contato ja favoritado" << endl;
            return false;
        }
        contato->second->setFavorited(true);
        favoritos.insert(*contato);
        return true;

    }

    bool desfavoritar(string nome){
        auto contato = favoritos.find(nome);
        if (contato == favoritos.end()){
            cout << "fail: contato nao existe ou nao esta favoritado" << endl;
            return false;
        }
        contato->second->setFavorited(false);
        favoritos.erase(contato);
        return true;
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
        }else if (cmd == "addFone"){
            string nome = get<string>(ss);
            string id = get<string>(ss);
            string fone = get<string>(ss);
            Contato* contato = agenda.findContato(nome);
            contato->addFone(id, fone);

        }else if (cmd == "rmFone"){ 
            string nome = get<string>(ss);
            Contato* contato = agenda.findContato(nome);
            contato->rmFone(get<int>(ss));
            
        }/* else if (cmd == "agenda"){ 
            if (!(agenda.getContatos().empty()))
                cout << agenda << endl;
            else
                cout << "vazio" << endl;
            
        } else if (cmd == "findbyN"){ 
            string nome = get<string>(ss);
            cout << *(agenda.findContato(nome)) << endl;

        } */else if (cmd == "search"){
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

        }else if (cmd == "contato"){
            string nome = get<string>(ss);
            cout << *(agenda.getContato(nome)) << endl;

        }else if (cmd == "contatos"){
            if (!(agenda.getContatos().empty()))
                cout << agenda << endl;
            else
                cout << "vazio" << endl;
        
        }else if (cmd == "favoritos"){
            vector<Contato> favoritos = agenda.getFavoritos();
            for (int i = 0; i < (int)favoritos.size(); i++)
                cout << favoritos[i] << endl;

        }else if (cmd == "favoritar"){
            string nome = get<string>(ss);
            agenda.favoritar(nome);

        }else if (cmd == "desfav"){
            string nome = get<string>(ss);
            agenda.desfavoritar(nome);
            
        }else{
            cout << "fail: comando invalido" << endl; 
        }
    
    }
    
}
