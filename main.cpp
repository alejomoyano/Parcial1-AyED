#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <list>

using namespace std;

class tokenhtml{

public:
    virtual void show()=0;
    void contenido(stack<string> t, list<string> *l, string tag);
};

void tokenhtml::contenido(stack<string> t,list<string> *l, string tag) {
    int aux=t.size();
    while(!t.empty()){
        if(t.top()==("</"+tag+">")) {
            t.pop();
            do {
                string top = t.top();
                if(top!="</"+tag+">"||top!="<"+tag+">"){
                    l->push_front(top); //ordena la lista de atras para adelante(desp podemos recorrerla de adelante
                    cout<<"tag agregado: "<<top<<endl;   // para atras) agreaga solo el contenido, los tags q lo contienen no van.
                }
                t.pop();
            } while (t.top()!=("<"+tag+">"));
        } else{
            t.pop();
        }
    }

}

class html: protected tokenhtml{
    string name; //nombre del tag
    list<string> *lista=new list<string>; //guarda el contenido del tag
public:
    html(stack<string> t);
    void show();
};

html::html(stack<string> t){
    this->name="html";
    this->contenido(t, lista, name);
}

void html::show() {

}

class body: protected tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    body(stack<string> t);
    void show();
};

body::body(stack<string>t) {
    this->name="body";
    this->contenido(t,lista,name);
}

void body::show() {
    cout<<"pesao"<<endl;
}

class h1: protected tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    h1(stack<string> t);
    void show();
};

h1::h1(stack<string>t) {
    this->name="h1";
    this->contenido(t,lista,name);
}
void h1::show() {

}

class p: protected tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    p(stack<string> t);
    void show();
};

p::p(stack<string>t) {
    this->name="p";
    this->contenido(t,lista,name);
}

void p::show() {

}

class table: protected tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    table(stack<string> t);
    void show();
};

table::table(stack<string>t) {
    this->name="table";
    this->contenido(t,lista,name);
}

void table::show() {

}

class tr: protected tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    tr(stack<string> t);
    void show();
};

tr::tr(stack<string>t) {
    this->name="tr";
    this->contenido(t,lista,name);
}

void tr::show() {

}

class th: protected tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    th(stack<string> t);
    void show();
};

th::th(stack<string>t) {
    this->name="th";
    this->contenido(t,lista,name);
}

void th::show() {

}

class td: protected tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    td(stack<string> t);
    void show();
};

td::td(stack<string>t) {
    this->name="td";
    this->contenido(t,lista,name);
}

void td::show() {

}

class listaTokens{
public:
    listaTokens() {};

};

void trim(string &str);

int main() {

    stack<string> *tokens=new stack<string>;
    string myText, str_auxiliar = " ", str_auxiliar2 = " ";
    stack<char> *pila = new stack<char>;
    string tope = " ";
    int p = 0, f = 0;
    string token=" ";

    bool error = true;
// Read from the text file
    ifstream MyReadFile("File.html");

// Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText)) {

        if (myText != "") {
            if (myText.at(0) == ' ') {
                trim(myText);
            }
            int size = myText.length();

            for (int i = size - 1; i >= 0; i--) {
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
//                    cout << token << endl;
                    token = "";//pone en null al string para que no se concatene todo el string, solo lo que necesitamos
                }
                if (!pila->empty()) {//entra aca si no es vacia la pila y si no hay un < al principio
                    do {
                        tope = pila->top();
                        pila->pop();
                        token += tope;
                    } while (pila->top() != '<');//guarda el texto que se encuantra entre tags
                    tokens->push(token);
//                    cout << token << endl;
                    token = "";//pone en null al string para que no se concatene todo el string, solo lo que necesitamos
                }
            }
        }
    }
    MyReadFile.close();
    table test(*tokens);

//    cout<<endl<<"PILA: \n"<<endl;
//    int sizefinal=tokens->size();
//    for(int i=0; i<sizefinal; i++){
//       cout<<tokens->top()<<endl;
//        tokens->pop();
//    }
//    cout<<"doneeeee"<<endl;
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
