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
    virtual void show()=0;
    void contenido(list<string> t, list<string> *l, string tag);
    list<tokenhtml*> getTokenList() {return *tokenlist;}
    virtual list<string> getContenido()=0;
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
    string getName(){return name;}
    list<string> getContenido() {return *lista;}
};

html::html(list<string> t) {
    this->name = "html";
    this->contenido(t, lista, name);
}

void html::show() {
    cout << name << endl;
}
//---------------------------------------------------------------------------------------------------------------------
class body: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    body(list<string> t);
    void show();
    string getName(){return name;}
    list<string> getContenido() {return *lista;}
};

body::body(list<string>t) {
    this->name="body";
    this->contenido(t,lista,name);
}

void body::show() {
    cout << "\t" << name << endl;
}
//---------------------------------------------------------------------------------------------------------------------
class h1: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    h1(list<string> t);
    void show();
    string getName(){return name;}
    list<string> getContenido() {return *lista;}
};

h1::h1(list<string>t) {
    this->name="h1";
    this->contenido(t,lista,name);
}

void h1::show() {
    cout << "\t" << "\t" << name << " " << getContenido().front() << endl;
}
//---------------------------------------------------------------------------------------------------------------------
class p: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    p(list<string> t);
    void show();
    string getName(){return name;}
    list<string> getContenido() {return *lista;}
};

p::p(list<string>t) {
    this->name="p";
    this->contenido(t,lista,name);
}

void p::show() {
    cout << "\t" << "\t" << name << " " << getContenido().front() << endl;
}
//---------------------------------------------------------------------------------------------------------------------
class table: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    list<tokenhtml*> *tokenlist=new list<tokenhtml*>;
    table(list<string> t);
    void show();
    string getName(){return name;}
    list<string> getContenido() {return *lista;}
};

table::table(list<string>t) {
    this->name="table";
    this->contenido(t,lista,name);
}

void table::show() {
    cout << "\t" << "\t" << name << endl;
}
//---------------------------------------------------------------------------------------------------------------------
class tr: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    list<tokenhtml*> *tokenlist=new list<tokenhtml*>;
    tr(list<string> t);
    void show();
    string getName(){return name;}
    list<string> getContenido() {return *lista;}
};

tr::tr(list<string>t) {
    this->name="tr";
    this->contenido(t,lista,name);
}

void tr::show() {
    cout << "\t" << "\t" << "\t" << name << endl;
}
//---------------------------------------------------------------------------------------------------------------------
class th: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    th(list<string> t);
    void show();
    string getName(){ return name;}
    list<string> getContenido() {return *lista;}
};

th::th(list<string>t) {
    this->name="th";
    this->contenido(t,lista,name);
}

void th::show() {
    cout << "\t" << "\t" << "\t" << "\t" << name << " " << getContenido().front() << endl;
}
//---------------------------------------------------------------------------------------------------------------------
class td: public tokenhtml{
    string name;
    list<string> *lista=new list<string>;
public:
    td(list<string> t);
    void show();
    string getName(){ return name;}
    list<string> getContenido() {return *lista;}
};

td::td(list<string>t) {
    this->name="td";
    this->contenido(t,lista,name);
}

void td::show() {
    cout << "\t" << "\t" << "\t" << "\t" << name << " " << getContenido().front() << endl;
}
//---------------------------------------------------------------------------------------------------------------------

void trim(string &str);

int main() {

    list<string> *tokens = new list<string>;
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


    // ------ PARSING --------

    list<string> auxList, auxList2;

    if(tokens->front()=="<html>") {
        tokens->pop_front();
        tokens->pop_back();
        tokenhtml *html1=new html(*tokens);
        if (tokens->front() == "<body>") {
            tokens->pop_front();
            tokens->pop_back();
            tokenhtml *b = new body(*tokens);
            html1->getTokenList().push_back(b);
            for (string s:b->getContenido()) {
                if (s == "<h1>") {
                    tokens->pop_front();

                    auxList.push_back((string) tokens->front());
                    tokenhtml *h11=new h1(auxList);
                    tokens->pop_front();

                    //h11->setContent();
                    auxList.pop_back();
                    b->getTokenList().push_back(h11);
                    tokens->pop_front();
                }
                if (s == "<p>") {
                    tokens->pop_front();

                    auxList.push_back((string) tokens->front());
                    tokenhtml *p1=new p(auxList);
                    tokens->pop_front();

                    //h11->setContent();
                    auxList.pop_back();

                    b->getTokenList().push_back(p1);
                    tokens->pop_front();

                }
                if (s == "<table>") {
                    tokens->pop_front();
                    tokens->pop_back();
                    tokenhtml *table1 = new table(*tokens);
                    for (string s:table1->getContenido()) {
                        if (s == "<tr>") {
                            tokens->pop_front();
                            while(tokens->front() != "</tr>"){
                                auxList.push_back((string) tokens->front());
                                tokens->pop_front();
                            }
                            tokens->pop_front();
                            tokenhtml *tr1 = new tr(auxList);
                            for (string s:auxList){
                                if (s == "<th>") {
                                    auxList.pop_front();
                                    auxList2.push_back((string )auxList.front());
                                    tokenhtml *th1=new th(auxList2);
                                    auxList.pop_front();

                                    //h11->setContent();
                                    auxList2.pop_back();

                                    tr1->getTokenList().push_back(th1);
                                    auxList.pop_front();
                                }
                                if (s == "<td>") {
                                    auxList.pop_front();
                                    auxList2.push_back((string )auxList.front());
                                    tokenhtml *td1=new td(auxList2);
                                    auxList.pop_front();

                                    //h11->setContent();
                                    auxList2.pop_back();

                                    tr1->getTokenList().push_back(td1);
                                    auxList.pop_front();
                                }
                            }
                        }
                    }
                }
            }
        }
        while(!html1->getTokenList().empty()) {
            html1->getTokenList().front()->show();
            html1->getTokenList().pop_front();
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