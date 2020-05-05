#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <stack>

using namespace std;

void trim(string &str);

int main() {

    string myText;
    stack<char> *pila = new stack<char>;
    stack<string> *tokens = new stack<string>;
    string tope = "", token = "";

    ifstream MyReadFile("File.html");//lee un archivo con ese nombre
    while (getline(MyReadFile, myText)) { //lee linea por linea el archivo

        if (!myText.empty()) {
            if (myText.at(0) == ' ') {
                trim(myText);
            }
        }
        int size = myText.length();

        for (int i = size-1; i >= 0; i--) {
            pila->push(myText.at(i));
        }

        while (!pila->empty()) {//repite esto hasta que se vacia la pila
            tope = pila->top();
            if (tope == "<") {//entra si encuentra un < al principio
                do {
                    tope = pila->top();
                    pila->pop();
                    token += tope;
                } while (tope != ">");//guarda en un string lo que esta dentro de los brakets incluyendolos (tags)
                tokens->push(token);
                cout << token << endl;
                token = "";//pone en null al string para que no se concatene todo el string, solo lo que necesitamos
            }
            if (!pila->empty()) {//entra aca si no es vacia la pila y si no hay un < al principio
                do {
                    tope = pila->top();
                    pila->pop();
                    token += tope;
                } while (pila->top()!='<');//guarda el texto que se encuantra entre tags
                tokens->push(token);
                cout<<token<<endl;
                token="";//pone en null al string para que no se concatene todo el string, solo lo que necesitamos
            }
        }
    }
    MyReadFile.close();
}

void trim(string &str) {
    bool end=true;
            int i = 0,n=0;
            while (end) {
                if (str.at(i) == ' ') {
                    n = i;
                    i++;
                } else {
                    end = false;
                }
            }
            str.erase(0, n + 1);
    }
