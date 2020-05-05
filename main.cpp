#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <list>

using namespace std;

typedef struct {}T;

class tokenhtml{

public:
    virtual void show()=0;
};

class html: protected tokenhtml{
    list<string> *lista=new list<string>;
public:
    void contenido(stack<string> t);
    void show();
};

void html::contenido(stack<string> t) {
    int aux=t.size();
    int
    for(int i=0;i<aux;i++){
        if(t.top()==("</html>")) {
            do {
                string top = t.top();
                lista->push_back(top);
                cout << "tag final: " << top << endl;
                t.pop();
            } while (t.top() != ("<html>"));
        }
    }
}

void html::show() {

}

class body: protected tokenhtml{
    list<string> *lista=new list<string>;
public:
    void contenido(stack<string> t);
    void show();
};

void body::contenido(stack<string> t) {
    int aux=t.size();
    for(int i=0;i<aux;i++){
        if(t.top()==("</body")) {
            do {
                string top = t.top();
                lista->push_back(top);
                cout << "tag final: " << top << endl;
                t.pop();
            } while (t.top() != ("<body>"));
        }
    }
}

void body::show() {
}

class h1: protected tokenhtml{
    list<string> *lista=new list<string>;
public:
    void contenido(stack<string> t);
    void show();
};

void h1::contenido(stack<string> t) {
    int aux=t.size();
    for(int i=0;i<aux;i++){
        if(t.top()==("</h1>")) {
            do {
                string top = t.top();
                lista->push_back(top);
                cout << "tag final: " << top << endl;
                t.pop();
            } while (t.top() != ("<h1>"));
        }
    }
}

void h1::show() {

}

class p: protected tokenhtml{
    list<string> *lista=new list<string>;
public:
    void contenido(stack<string> t);
    void show();
};

void p::contenido(stack<string> t) {
    int aux=t.size();
    for(int i=0;i<aux;i++){
        if(t.top()==("</p>")) {
            do {
                string top = t.top();
                lista->push_back(top);
                cout << "tag final: " << top << endl;
                t.pop();
            } while (t.top() != ("<p>"));
        }
    }
}

void p::show() {

}

class table: protected tokenhtml{
    list<string> *lista=new list<string>;
public:
    void contenido(stack<string> t);
    void show();
};

void table::contenido(stack<string> t) {
    int aux=t.size();
    for(int i=0;i<aux;i++){
        if(t.top()==("</table>")) {
            do {
                string top = t.top();
                lista->push_back(top);
                cout << "tag final: " << top << endl;
                t.pop();
            } while (t.top() != ("<table>"));
        }
    }
}

void table::show() {

}

class tr: protected tokenhtml{
    list<string> *lista=new list<string>;
public:
    void contenido(stack<string> t);
    void show();
};

void tr::contenido(stack<string> t) {
    int aux=t.size();
    for(int i=0;i<aux;i++){
        if(t.top()==("</tr>")) {
            do {
                string top = t.top();
                lista->push_back(top);
                cout << "tag final: " << top << endl;
                t.pop();
            } while (t.top() != ("<tr>"));
        }
    }
}

void tr::show() {

}

class th: protected tokenhtml{
    list<string> *lista=new list<string>;
public:
    void contenido(stack<string> t);
    void show();
};

void th::contenido(stack<string> t) {
    int aux=t.size();
    for(int i=0;i<aux;i++){
        if(t.top()==("</th>")) {
            do {
                string top = t.top();
                lista->push_back(top);
                cout << "tag final: " << top << endl;
                t.pop();
            } while (t.top() != ("<th>"));
        }
    }
}

void th::show() {

}

class td: protected tokenhtml{
    list<string> *lista=new list<string>;
public:
    void contenido(stack<string> t);
    void show();
};

void td::contenido(stack<string> t) {
    int aux=t.size();
    for(int i=0;i<aux;i++){
        if(t.top()==("</td>")) {
            do {
                string top = t.top();
                lista->push_back(top);
                cout << "tag final: " << top << endl;
                t.pop();
            } while (t.top() != ("<td>"));
        }
    }
}

void td::show() {

}

//void tokenhtml::parsing(stack<string> tokens,string str){
//    int aux=tokens.size();
//    list<string> *salida=new list<string>;
//    stack<string> *body=new stack<string>;
//    string a="";
//    string con="";
//
//    for(int i=0;i<aux;i++){
//        if(tokens.top()==("</"+str+">")){
//            string top=tokens.top();
//            cout<<"tag final: "<<top<<endl;);
//            stack<string> *body=new stack<string>;
//            tokens.pop();
//            if(tokens.top().front()!='<'){
//                con=tokens.top();
//                tokens.pop();
//            }
//        }else if(tokens.top()==("<"+str+">")){
//            a=tokens.top().substr(1,tokens.top().length()-2);
//            cout<<"tag de inicio: "<<tokens.top()<<endl;
//            cout<<"nombre del tag(string 'a'): "<<a<<endl;
//            tokens.pop();
//        }else{
//            body->push(tokens.top());
//            tokens.pop();
//        }
//    }
//    while(!body->empty()) {
//        cout << body->top() << endl;
//        body->pop();
//    }
//
//    salida->push_back(a); //agrega a la lista el nombre del tag
//    salida->push_back(con); //agrega el contenido del tag
////    if(body->top().front()!='<'){ //si lo q le sigue a ese tag no es otro tag, es cuerpo entonces lo agrega a la lista
////        salida->push_back(body->top());
////        body->pop();
////    }
//    cout<<endl<<"Contenido de la lista Salida: \n"<<endl;
//    for(string n:*salida){
//        cout<<n<<endl;
//    }
//}


string intermedio(string cadena,int p, int size);
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
            //cout<<myText<<endl;
            // Output the text from the file
            for(int i = 0; i<myText.length(); i++) {
                if (myText.at(i) == '<') {
                    p = i;
                }
                if (myText.at(i) == '>') {
                    f = i + 1;
                    str = myText.substr(p, f);
                    tokens->push(str);
                    cout <<"agregado a la pila: "<<str << endl;
                    for (int i=f; i<myText.length(); i++) {
                        string subs=" ";
                        if (myText.at(i) == '<') {
                            subs = myText.substr(f, i - f);
                            cout <<"Intermedio agregado a la pila:"<<subs << endl;
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
    //prueba->parsing(*tokens,"html");
    //prueba2->parsing(*tokens,"p");

    cout<<endl<<"PILA: \n"<<endl;
    int sizefinal=tokens->size();
    for(int i=0; i<sizefinal; i++){
       cout<<tokens->top()<<endl;
        tokens->pop();
    }
    cout<<"doneeeee"<<endl;
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
