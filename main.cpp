#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <list>

using namespace std;

class tokenhtml{
    list<tokenhtml*> *tokenlist=new list<tokenhtml*>;
public:
    list<string> lista;
    virtual void show()=0;
    void contenido(list<string> t, list<string> *l, string tag);
    list<string> getContenido() {return lista;}
    list<tokenhtml*> getTokenList() {return *tokenlist;}
};

void tokenhtml::contenido(list<string> t,list<string> *l, string tag) {
    cout<<"Ejecutando metodo 'contenido' del objeto "<<tag<<endl;
    while(!t.empty()){
        if(t.front()==("<"+tag+">")) {
            t.pop_front();
            while (t.front()!=("</"+tag+">")){
                string top = t.front();
                if(top!="</"+tag+">"||top!="<"+tag+">"){
                    l->push_back(top); //ordena la lista de atras para adelante(desp podemos recorrerla de adelante
                    cout<<"tag agregado: "<<top<<endl;
                }
                t.pop_front();
            }
        } else{
            t.pop_front();
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------
class html: public tokenhtml{
    string name; //nombre del tag
    list<string> *lista=new list<string>; //guarda el contenido del tag, en strings
public:
    html(list<string> t);
    void show();
};

html::html(list<string> t) {
    this->name = "html";
    this->contenido(t, lista, name);
}

void html::show() {

}
//---------------------------------------------------------------------------------------------------------------------
class body: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    body(list<string> t);
    void show();
};

body::body(list<string>t) {
    this->name="body";
    this->contenido(t,lista,name);
}

void body::show() {
    cout<<"pesao"<<endl;
}
//---------------------------------------------------------------------------------------------------------------------
class h1: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    h1(list<string> t);
    void show();
};

h1::h1(list<string>t) {
    this->name="h1";
    this->contenido(t,lista,name);
}

void h1::show() {

}
//---------------------------------------------------------------------------------------------------------------------
class p: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    p(list<string> t);
    void show();
};

p::p(list<string>t) {
    this->name="p";
    this->contenido(t,lista,name);
}

void p::show() {

}
//---------------------------------------------------------------------------------------------------------------------
class table: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    list<tokenhtml*> *tokenlist=new list<tokenhtml*>;
    table(list<string> t);
    void show();
};

table::table(list<string>t) {
    this->name="table";
    this->contenido(t,lista,name);
}

void table::show() {

}
//---------------------------------------------------------------------------------------------------------------------
class tr: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    list<tokenhtml*> *tokenlist=new list<tokenhtml*>;
    tr(list<string> t);
    void show();
};

tr::tr(list<string>t) {
    this->name="tr";
    this->contenido(t,lista,name);
}

void tr::show() {

}
//---------------------------------------------------------------------------------------------------------------------
class th: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    th(list<string> t);
    void show();
};

th::th(list<string>t) {
    this->name="th";
    this->contenido(t,lista,name);
}

void th::show() {

}
//---------------------------------------------------------------------------------------------------------------------
class td: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    td(list<string> t);
    void show();
};

td::td(list<string>t) {
    this->name="td";
    this->contenido(t,lista,name);
}

void td::show() {

}
//---------------------------------------------------------------------------------------------------------------------

void trim(string &str);

int main() {

    list<string> *tokens=new list<string>;
    string myText, str_auxiliar = " ", str_auxiliar2 = " ";
    stack<char> *pila = new stack<char>;
    string tope = " ";
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
                    if(token.at(0)==' ')token.erase(0,1);
                    tokens->push_back(token);
//                    cout << token << endl;
                    token = "";//pone en null al string para que no se concatene todo el string, solo lo que necesitamos
                }
                if (!pila->empty()) {//entra aca si no es vacia la pila y si no hay un < al principio
                    do {
                        tope = pila->top();
                        pila->pop();
                        token += tope;
                    } while (pila->top() != '<');//guarda el texto que se encuantra entre tags
                    if(token.at(0)==' ')token.erase(0,1);
                    tokens->push_back(token);
//                    cout << token << endl;
                    token = "";//pone en null al string para que no se concatene todo el string, solo lo que necesitamos
                }
            }
        }
    }
    MyReadFile.close();
    if(tokens->front()=="<html>") {
        tokenhtml *html1=new html(*tokens);
        if (html1->getContenido().front() == "<body>") {
            tokenhtml *b=new body(html1->getContenido());
            html1->getTokenList().push_back(b);
            for (string s:b->getContenido()) {
                if (s == "<h1>") {
                    tokenhtml *h11=new h1(b->getContenido());
                    b->getTokenList().push_back(h11);
                }
                if (s == "<p>") {
                    tokenhtml *p1=new p(b->getContenido());
                    b->getTokenList().push_back(p1);
                }
                if (s == "<table>") {
                    tokenhtml *table1=new table(b->getContenido());
                    for (string s:table1->getContenido()) {
                        if (s == "<tr>") {
                            tr tr(table1->getContenido());
                        }
                    }
                }
            }
        }
    }



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
