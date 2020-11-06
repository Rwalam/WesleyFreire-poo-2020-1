#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

//g++ vetinterativo.cpp -o vet -Wall -std=c++14
//mostra o vetor
void vet_show(vector<int>& vet){
    cout << "[ ";
    for(size_t i = 0; i < vet.size(); i++){
        cout << vet[i] << " ";
    }
    cout << "]\n";
}

void vet_rshow(vector<int>& vet){
    vector<int>::reverse_iterator rit;
    cout << "[ ";
    for (rit = vet.rbegin(); rit != vet.rend(); rit++){
        cout << *rit << " ";
    }
    cout << "]\n";
}

//retorna o índice que contém value ou -1 se não existir
bool vet_find(vector<int>& vet, int value){
    vector<int>::iterator it;
    int aux = 0;
    bool found = false;
    cout <<  "[ ";
    for (it = vet.begin(); it != vet.end(); it++, aux++){
        if (*it == value){
            cout << aux << " ";
            found = true;
        }       
    }
    cout << "]\n";

    return found ? true : false;

}

void vet_removebyelem(vector<int>& vet, int elem){

    vector<int>::iterator it;

    it = vet.begin();
    while (it != vet.end()){
        if (*it == elem){
            it = vet.erase(it);
        }
        else{
            it++;
        }
    }
    return;
}

void vet_removebyindice(vector<int>& vet, int ind){
    vector<int>::iterator it;
    it = vet.begin();
    vet.erase(it+ind);

}



int main(){
    vector<int> vet;
    string line;
    while(true){
        getline(cin, line);
        stringstream ss(line);
        cout << "$" << line << "\n";
        string cmd;
        ss >> cmd; //pegando o primeiro token

        if(line == "end"){
            break;
        }else if(cmd == "add"){
            int value;
            while(ss >> value) //enquanto conseguir retirar valores
                vet.push_back(value);
        
        }else if(cmd == "show"){
            vet_show(vet);
            
        }else if(cmd == "rshow"){
            vet_rshow(vet);

        }else if(cmd == "find"){
            int elem;
            while(ss >> elem)
                if (!vet_find(vet, elem))
                    cout << "elemento nao existe" << endl;
                   
        }else if(cmd == "rmi"){
            int pos;
            while(ss >> pos)
                vet_removebyindice(vet, pos);

        }else if(cmd == "ins"){
            int elem, pos;
            vector<int>::iterator it = vet.begin(); 
            while(ss >> pos >> elem)
                vet.insert(it + pos, elem);

        }else if(cmd == "rma"){
            int elem;
            while(ss >> elem)
                vet_removebyelem(vet, elem);

        }else{
            cout << "Comando invalido\n";
        }
    }

    return 0;
}