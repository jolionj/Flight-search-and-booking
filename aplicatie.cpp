//Toma Alexandru-Ionel // 322AC

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
using namespace std;

void menu_operator();
void operator_login();
void menu_utilizator();
void adaugare_zbor();
void stergere_zbor();
void creare_cont();
void autentificare();
void cautare_zbor();
void rezervare();
void detalii_zbor(int nr);
void menu_utilizator_aut();
int litere(string input);
void data_curenta();
int verif_data(int x, int y , int z);

string op_username="admin";
string op_password="admin";

string username_g[100]={"andrei","matei","ulise"}; int utilizator_l=2;
string password_g[100]={"and19","matei","troian"};

string mail_g[100]={"andrei@yahoo.com","matei@gamil.com","ulise@yahoo.ro"};

string zbor_plecare_g[100]={"Bucuresti","Madrid","Roma"}; int zbor_l=2;
string zbor_sosire_g[100]={"Amsterdam","Berlin","Paris"};

string zbor_plecare_tara_g[100]={"Romania","Spania","Italia"};
string zbor_sosire_tara_g[100]={"Olanda","Germania","Franta"};

int zi_curent=0;
int luna_curent=0;
int an_curent=0;

int zi_g[100]={20,15,12};
int luna_g[100]={12,1,4};
int an_g[100]={2021,2020,2019};

int zbor_loc_disp[100]={100,45,120};
int zbor_loc_rez[100]={20,60,30};

class Zbor{
public:
    string zbor_plecare;
    string zbor_sosire;
    string tara_plecare;
    string tara_sosire;
    int zi;
    int luna;
    int an;
    int loc_disp;
    int loc_rez;
};

class Utilizator{
public:
    string username;
    string password;
    string mail;
    string password_rsa;
};

class RSA{
public:
    int x, y, n, t, i, flag;
    long int e[50], d[50], temp[50], j;
    char en[50], m[50];
    char msg[100];

    void rsa_p(char mesaj[100]){

       x=5;

   flag = prime(x);
   if(flag == 0)
   {
      cout << "\nPrimul numar nu este prim.\n";
      exit(0);
   }

   y=11;

   flag = prime(y);
   if(flag == 0 || x == y)
   {
      cout << "\nAl doilea numar nu este prim.\n";
      exit(0);
   }

   strcpy(msg,mesaj);

   for(i = 0; msg[i] != NULL; i++)
      m[i] = msg[i];
   n = x * y;
   t = (x - 1) * (y - 1);

    encryption_key();
    encrypt();
    decrypt();

    }

    int prime(long int pr)
{
   int i;
   j = sqrt(pr);
   for(i = 2; i <= j; i++)
   {
      if(pr % i == 0)
         return 0;
   }
   return 1;
 }

void encryption_key()
{
   int k;
   k = 0;
   for(i = 2; i < t; i++)
   {
      if(t % i == 0)
         continue;
      flag = prime(i);
      if(flag == 1 && i != x && i != y)
      {
         e[k] = i;
         flag = cd(e[k]);
         if(flag > 0)
         {
            d[k] = flag;
            k++;
         }
         if(k == 99)
         break;
      }
   }
}

long int cd(long int a)
{
   long int k = 1;
   while(1)
   {
      k = k + t;
      if(k % a == 0)
         return(k/a);
   }
}

void encrypt()
{
   long int pt, ct, key = e[0], k, len;
   i = 0;
   len = strlen(msg);

   while(i != len)
   {
      pt = m[i];
      pt = pt - 96;
      k = 1;
      for(j = 0; j < key; j++)
      {
         k = k * pt;
         k = k % n;
      }
      temp[i] = k;
      ct= k + 96;
      en[i] = ct;
      i++;
   }
   en[i] = -1;
}

void decrypt()
{
   long int pt, ct, key = d[0], k;
   i = 0;
   while(en[i] != -1)
   {
      ct = temp[i];
      k = 1;
      for(j = 0; j < key; j++)
      {
         k = k * ct;
         k = k % n;
      }
      pt = k + 96;
      m[i] = pt;
      i++;
   }
   m[i] = -1;
}
};

Zbor z1[100];
Utilizator u1[100];
RSA r1;

void data_curenta(){

    time_t now = time(0);
    tm *ltm = localtime(&now);
    zi_curent=ltm->tm_mday;
    luna_curent=1+ltm->tm_mon;
    an_curent=1900+ltm->tm_year;

}

void menu_general(){

    cout << "Aplicatie cautare si rezervare zboruri." << endl;

    int select1=0;
    while(select1!=3){
        cout << "Meniu principal:" << endl;
        cout << "1. Operator" << endl;
        cout << "2. Utilizator" << endl;
        cout << "3. Inchide" << endl;
        cin >> select1;

    if(select1==1) operator_login();

    if(select1==2) menu_utilizator();

    }

    cout << "Operatiune terminata." << endl;
}

void operator_login(){

    cout << endl;
    int select2=0;
    string login_u,login_p;

    cout << "Meniul operator necesita login." << endl;

    while (select2==0){

        cout << "Username: "; cin >> login_u;
        cout << "Password: "; cin >> login_p;

        try{
            if(login_u==op_username && login_p==op_password){
                cout << endl << "Autentificare reusita."<< endl;
                select2=1;
                menu_operator();
        }

        else{
            select2=0;
            throw login_u;
            break;
        }
        }

        catch (...) {
         cout << "Numele de utilizator si parola nu se potrivesc"<< endl;
        }


    }

}

void menu_operator(){

    int select1=0;
    while(select1!=3){
        cout << "Meniu operator:" << endl;
        cout << "1. Adaugare zbor" << endl;
        cout << "2. Stergere zbor" << endl;
        cout << "3. Inapoi" << endl;
        cin >> select1;

    if(select1==1) adaugare_zbor();

    if(select1==2) stergere_zbor();

    }

}

void menu_utilizator(){
    cout <<endl;
    int select1=0;
    while(select1!=3){
        cout << "Meniu utilizator:" << endl;
        cout << "1. Creare cont" << endl;
        cout << "2. Autentificare" << endl;
        cout << "3. Inapoi" << endl;
        cin >> select1;

    if(select1==1) creare_cont();

    if(select1==2) autentificare();


    }

}

int verif_data(int x, int y , int z){

    if(z>an_curent) return 1;
    else if (z<an_curent) return 0;
    else{
        if(y>luna_curent) return 1;
        else if (y<luna_curent) return 0;
        else {
            if(x>zi_curent) return 1;
            else if(x<zi_curent) return 1;
            else return 1;
        }
    }
}

void adaugare_zbor(){

    cout << "Adaugare zbor:" << endl;

    string s1,s2,s3,s4;

    int d1,d2,d3;

    int select1=0;
    while(select1!=1){

        try {

        cout << "Plecare zbor locatie: "; cin >> s1;
        cout << "Sosire zbor locatie: "; cin >> s2;
        cout << "Plecare zbor tara: "; cin >> s3;
        cout << "Sosire zbor tara: "; cin >> s4;
        cout << "Zi plecare: "; cin >> d1;
        cout << "Luna plecare: "; cin >> d2;
        cout << "An plecare: "; cin >> d3;


    if(litere(s1)==0){
            cout<<"Plecare zbor locatie format gresit."<<endl;
        throw s1;
    }
    else if(litere(s2)==0){
            cout<<"Sosire zbor locatie format gresit."<<endl;
        throw s2;
    }
    else if(litere(s3)==0){
            cout<<"Plecare zbor tara format gresit."<<endl;
        throw s3;
    }
    else if(litere(s4)==0){
        cout<<"Sosire zbor tara format gresit."<<endl;
        throw s4;
    }
    else if(d1<0 || d1>31){
            cout<<"Zi plecare format gresit."<<endl;
        throw d1;
    }
    else if(d2<0 || d2>12){
            cout<<"Luna plecare format gresit."<<endl;
        throw d2;
    }
    else if(verif_data(d1,d2,d3)==0){
            cout<<"An plecare format gresit."<<endl;
        throw d3;
    }
    else{
        break;
    }
            }
    catch (...) {
         cout<<"Adaugare zbor esuat. Incercati din nou."<<endl;
        }
    }

    zbor_l++;
    z1[zbor_l].zbor_plecare=s1;
    z1[zbor_l].zbor_sosire=s2;
    z1[zbor_l].tara_plecare=s3;
    z1[zbor_l].tara_sosire=s4;
    z1[zbor_l].zi=d1;
    z1[zbor_l].luna=d2;
    z1[zbor_l].an=d3;

    cout << "Zbor adaugat. "<< endl;
}

int litere(string input){
	for (int i = 0; i < input.size(); i++)
	{
		int uppercaseChar = toupper(input[i]);
		if (uppercaseChar < 'A' || uppercaseChar > 'Z')
		{
			return 0;
		}
	}
	return 1;
}

void stergere_zbor(){

    int x=-1;
    cout << "Pentru stergrea zborului trebuie sa cunoasteti numarul aferent." << endl;
    cout << "Folositi comanda de cautare zbor pentru a afla numarul." << endl;
    cout << "Stergere zbor." << endl;
    cout << "Introduceti numarul:" << endl;
    cin >> x;

    for(int i=x; i<zbor_l; i++){

        z1[i].zbor_plecare=z1[i+1].zbor_plecare;
        z1[i].zbor_sosire=z1[i+1].zbor_sosire;

    }
    zbor_l--;

    cout << "Zbor sters. "<< endl;
}

void creare_cont(){

    cout << "Creare cont." << endl;

    string s1,s2,s3,s4;

    int select1=0;
    while(select1!=1){

        try {

        cout << "Username: "; cin >> s1;
        cout << "Password: "; cin >> s2;
        cout << "Password repetare: "; cin >> s3;
        cout << "Email: "; cin >> s4; cout << endl;


    if(s1==s2){
            cout<<"Username si parola sunt identice."<<endl;
        throw s2;
    }
    else if(s2!=s3){
            cout<<"Parola difera de cea repetata."<<endl;
        throw s2;
    }
    else if(s2.length()<5){
            cout<<"Parola e prea slaba."<<endl;
        throw s2;
    }
    else if(s4.find('@')>s4.length()){
        cout<<"Format email incorect."<<endl;
        throw s4;
    }
    else{

        break;
    }
            }
    catch (...) {
         cout<<"Creare cont esuat. Incercati din nou."<<endl;
        }
    }

    utilizator_l++;
    u1[utilizator_l].username=s1;
    u1[utilizator_l].password=s2;

    cout << "Cont creat." << endl;
}

void autentificare(){
    cout <<endl;
    cout << "Autentificare" << endl;

    string s1,s2;
    int i,x=0;
    int select2=0;

    while (select2==0){

        cout << "Username: "; cin >> s1;
        cout << "Password: "; cin >> s2;

        try{

        for(i=x; i<=utilizator_l; i++){

            if(s1==u1[i].username && s2==u1[i].password){
            cout << endl << "Autentificare reusita."<< endl;
            select2=1;
            menu_utilizator_aut();
        }

        }

            if(select2==0){
                throw s1;

            }
        }

        catch (...) {
         cout << "Numele de utilizator si parola nu se potrivesc"<< endl;
        }


        }


}

void menu_utilizator_aut(){

    int select1=0;
    while(select1!=3){
        cout << "Meniu utilizator:" << endl;
        cout << "1. Cautare zbor" << endl;
        cout << "2. Rezervare" << endl;
        cout << "3. Inapoi" << endl;
        cin >> select1;

    if(select1==1) cautare_zbor();

    if(select1==2) rezervare();


    }



}

void cautare_zbor(){

    string s1,s2;

    int select1=0;
    while(select1!=6){
        cout << "Meniu cautare zbor:" << endl;
        cout << "1. Dupa localitate plecare" << endl;
        cout << "2. Dupa localitate sosire" << endl;
        cout << "3. Dupa data" << endl;
        cout << "4. Dupa tara plecare" << endl;
        cout << "5. Dupa tara sosire" << endl;
        cout << "6. Inapoi" << endl;
        cin >> select1;


    try{

    if(select1==1){
        cout << "Introduceti localitate plecare:" << endl;
        cin>>s1;

        for(int i=0; i<=zbor_l; i++){
            if(z1[zbor_l].zbor_plecare==s1){
                detalii_zbor(zbor_l);
                select1=6;
                break;
            }
            else{
                throw s1;
                break;
            }
        }
    }

    if(select1==2){
        cout << "Introduceti localitate sosire:" << endl;
        cin>>s1;

        for(int i=0; i<=zbor_l; i++){
            if(z1[zbor_l].zbor_sosire==s1){
                detalii_zbor(zbor_l);
                select1=6;
                break;
            }
            else{
                throw s1;
                break;
            }
        }
    }

    if(select1==3){

    }

    if(select1==4){

    }

    if(select1==5){



    }

    }

     catch (...) {
         cout<<"Nu exista."<<endl;
     }
    }

}

void rezervare(){

    int x=-1;
    int y=0;

    cout << "Rezervare loc zbor."<<endl;
    cout << "Pentru rezervarea locurilor unui zbor trebuie sa cunoasteti numarul aferent." << endl;
    cout << "Folositi comanda de cautare zbor pentru a afla numarul." << endl;

    int select1=0;
    while(select1!=1){

        try{

        cout << "Introduceti numarul zborului:" << endl;
        cin >> x;

        if(z1[x].loc_disp==0){
            cout<<"Zborul nu mai are locuri disponibile."<<endl;
        }
        else{
            cout << "Zborul are " << z1[x].loc_disp << endl;
            cout << "Introduceti cate locuri doriti sa rezervati:" << endl;
            cin >> y;
        }

        if(z1[x].loc_disp<y){
            throw y;
        }
        else{
            z1[x].loc_disp=z1[x].loc_disp-y;
            z1[x].loc_rez=z1[x].loc_rez+y;
            cout << "Zbor rezervat." << endl;
            cout << y <<" locuri au fost rezervate pentru zborul cu numarul "<< x <<endl;
            break;

        }
        }
        catch(...) {
            cout << "Numarul de locuri pe care doriti sa il rezervati este mai mare decat locurile disponibile." << endl;

        }


    }

}

void detalii_zbor(int nr){
    cout<<"Detalii zbor cu numarul: "<<nr<<endl;
    cout<<"Plecare locatie: "<<z1[nr].zbor_plecare<<endl;
    cout<<"Sosire locatie: "<<z1[nr].zbor_sosire<<endl;
    cout<<"Plecare tara: "<<z1[nr].tara_plecare<<endl;
    cout<<"Sosire tara: "<<z1[nr].tara_sosire<<endl;
    cout<<"Data plecare: "<<z1[nr].zi<<"."<<z1[nr].luna<<"."<<z1[nr].an<<endl;
    cout<<"Locuri rezervate: "<<z1[nr].loc_rez<<endl;
    cout<<"Locuri libere: "<<z1[nr].loc_disp<<endl;
}

void citire_date(){

    for(int i=0; i<=zbor_l; i++){

        z1[i].zbor_plecare=zbor_plecare_g[i];
        z1[i].zbor_sosire=zbor_sosire_g[i];
        z1[i].loc_disp=zbor_loc_disp[i];
        z1[i].loc_rez=zbor_loc_rez[i];
        z1[i].tara_plecare=zbor_plecare_tara_g[i];
        z1[i].tara_sosire=zbor_sosire_tara_g[i];
        z1[i].zi=zi_g[i];
        z1[i].luna=luna_g[i];
        z1[i].an=an_g[i];

    }

    for(int i=0; i<=utilizator_l; i++){

        u1[i].username=username_g[i];
        u1[i].password=password_g[i];

    }
}

void rsa_apelare(){

    char aux[100];

    for(int i=0; i<=utilizator_l; i++){
        strcpy(aux, u1[i].password.c_str());
        r1.rsa_p(aux);
        u1[i].password_rsa=r1.en;
    }
    cout<<"Date criptate."<<endl;
}

int main(){

    data_curenta();

    citire_date();

    menu_general();

    rsa_apelare();

}
