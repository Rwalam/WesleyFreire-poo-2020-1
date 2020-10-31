#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;



class Conta{
protected:
    int id;
    float saldo;
    string idCliente;
    string type;

public:

    Conta(int id = 0, float saldo = 0, string idCliente = "", string type = ""):
        id{id}, saldo{0}, idCliente{idCliente}, type{type} {}

    int getId(){return id;}
    
    virtual void atualizacaoMensal() = 0;

    void sacar(float valor){
        if ((saldo - valor) <= 0){
            cout << "fail: saldo insuficiente\nvoce possui apeas R$: " << saldo << endl; 
            return;
        }
        saldo -= valor;
    }
    void depositar(float valor){
        saldo += valor;
    }
    void transferir(Conta* conta,float valor){
        if ((saldo - valor) <= 0){
            cout << "fail: saldo insuficiente\nvoce possui apeas R$: " << saldo << endl; 
            return;
        }
        saldo -= valor;
        conta->saldo += valor;
    }


    friend ostream& operator<<(ostream& ost, Conta& conta){
        ost << conta.id << ":" << conta.idCliente << ":" << conta.saldo << ":" << conta.type;
        return ost;
    } 
    friend class Cliente;
};


class ContaC : public Conta{
private:
    float tarifaMensal;
    
public:
    ContaC(int id = 0, string idCliente = "", float tarifaMensal = 0):
        Conta{id, 0, idCliente, "CC"}, tarifaMensal{tarifaMensal} {}

    void atualizacaoMensal(){
        saldo -= tarifaMensal;
    }

};


class ContaP : public Conta{
private:
    float rendimento;

public:
    ContaP(int id = 0, string idCliente = "", float rendimento = 0):
        Conta{id, 0, idCliente, "CP"}, rendimento{rendimento} {}

    void atualizacaoMensal(){
        saldo += saldo*rendimento;

    }
};


class Cliente{
private:
    string id;
    vector<Conta*> contas;
public:
    Cliente(string& id) {
        static int key = 0;
        ContaC* cc = new ContaC(key++,id,20);
        ContaP* cp = new ContaP(key++,id,0.01);
        contas.push_back(cc);
        contas.push_back(cp);

        /* for (auto contas : cli->contas){
            static int keyall = 0;
            allcontas.insert(make_pair(keyall++, contas));
            //cout << "valor da chave de all cont " << keyall << endl;
        } */
    }

    vector<Conta*> getContas(){
        return contas;
    }
    
    friend class Agencia;
    
};


class Agencia{
private:
    map<string, Cliente*> clientes;
    map<int, Conta*> allcontas;
public:

    void adicionarCliente(string id){
        if (clientes.find(id) != clientes.end()){
            cout << "cliente ja existe" << endl;
            return;            
        }
        Cliente* cli = new Cliente(id);
        clientes.insert(make_pair(id,cli));
        
        for (auto contas : cli->contas){
            static int keyall = 0;
            allcontas.insert(make_pair(keyall++, contas));
            //cout << "valor da chave de all cont " << keyall << endl;
        }
        

    }

    map<string, Cliente*> getClientes(){return clientes;}

    map<int, Conta*> getAllcontas(){return allcontas;}

};



template <class T>
T get(stringstream& ss){
    T t;
    ss >> t;
    return t;
}

int main(){
    Agencia agencia;

    while (true){
        string line, cmd;
        getline(cin, line);
        stringstream ss(line);
        ss >> cmd;
        
        if (cmd == "end"){
            break;
        }else if (cmd == "addCli"){
            string nome = get<string>(ss);
            agencia.adicionarCliente(nome);

        }else if (cmd == "show"){
            for (auto conta : agencia.getAllcontas())
                cout << *conta.second << endl;
            
        }else if (cmd == "deposito"){
            int key = get<int>(ss);
            float valor = get<int>(ss);
            agencia.getAllcontas().find(key)->second->depositar(valor);

        }else if (cmd == "saque"){
            int key = get<int>(ss);
            float valor = get<int>(ss);
            agencia.getAllcontas().find(key)->second->sacar(valor);
        }else if (cmd == "transf"){
            int key1 = get<int>(ss);
            int key2 = get<int>(ss);
            Conta* c1 = agencia.getAllcontas().find(key1)->second;
            Conta* c2 = agencia.getAllcontas().find(key2)->second;
            float valor = get<int>(ss);
            c1->transferir(c2, valor);
            
        }else if (cmd == "update"){
            for (auto conta : agencia.getAllcontas())
                conta.second->atualizacaoMensal();

        }else{
            cout << "comando invalido" << endl;
        }
        
    }
}
