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
                    cout<<"tag final: "<<top<<endl;                      // para atras) agreaga solo el contenido, los tags q lo contienen no van.
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
    cout<<"pesao"<<endl;
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
    this->name="h1";
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
    string apilando = " ";
    int p = 0, f = 0;
    string str=" ";

    bool error = true;
// Read from the text file
    ifstream MyReadFile("File.html");

// Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText)) {

        if (myText != "") {
            if (myText.at(0) == ' ') {
                trim(myText);
            }
//            cout<<myText<<endl;
            for(int i = 0; i<myText.length(); i++) {
                if (myText.at(i) == '<') {
                    p = i;
                }
                if (myText.at(i) == '>') {
                    f = i + 1;
                    str = myText.substr(p, f);
                    tokens->push(str);
//                    cout <<"agregado a la pila: "<<str << endl;
                    for (int i=f; i<myText.length(); i++) {
                        string subs=" ";
                        if (myText.at(i) == '<') {
                            subs = myText.substr(f, i - f);
//                            cout <<"Intermedio agregado a la pila:"<<subs << endl;
                            if (subs != " ") {
                                tokens->push(subs);
                            }
                        }
                    }
                }


            }
        }
    }
    MyReadFile.close();
    tr test(*tokens);

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
