#include <iostream>
using namespace std;


bool strcmp(string a, string b){
        if(sizeof(a) != sizeof(b)){
            return false;
        }
        for (int i = 0; i < sizeof(a); i++){
            if (a[i] != b[i]){
                return false;
            }
        }
        return true;
    }

struct Pessoa{
    int saude = 100;
    int fome = 0;
    int necessidades = 0;
    
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
};

int main(){
    Pessoa * pessoa = new Pessoa();
    string key = " ";
    while (1){
        cin >> key;

        if (strcmp(key,"comer")){
            pessoa->comer();
            cout<<"tete";
            cout << pessoa->saude << endl;
            cout << pessoa->fome << endl;
            cout << pessoa->necessidades << endl;
        }
        if (strcmp(key,"evacuar")){
            pessoa->evacuar();
        }
    }
    
}