#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>
using namespace std;

ifstream f("text.in");
class carte
{
private:
    char denumire_carte[256];
    char autor_principal[256];
    char al_doilea_autor[256];
    int numar_pagini;
    float pret;
    float rating;
public:

    carte(char*, char*, char*, int, float, float);              //constructor initializare
    carte (carte&);                                          //constructor copiere
    ~carte();                                              //destructor
    void set_denumire_carte(char*);                         //set
    void set_autor_principal(char*);                        //set
    void set_al_doilea_autor(char*);                        //set
    void set_numar_pagini(int);                            //set
    void set_pret(float);                                  //set
    void set_rating(float);                                //set
    void afisare(ostream &out);
    void citire(istream &in);
    char* get_denumire_carte()                              //get
    {
        return denumire_carte;
    };

    char* get_autor_princiapl()                             //get
    {
        return autor_principal;
    };

    char* get_al_doilea_autor()                             //get
    {
        return al_doilea_autor;
    };

    int get_numar_pagini()                                 //get
    {
        return numar_pagini;
    };

    float get_pret ()                                        //get
    {
        return pret;
    };
    float get_rating()                                      //get
    {
        return rating;
    };

    friend istream& operator>>(istream &in, carte& z);  ///supraincarcare pe >>
    friend ostream& operator<<(ostream &out, carte& z); ///supraincarcare pe <<
    carte& operator = (carte &z);
    bool operator>(carte& z1) ///supraincarcare operator >
    {
        if(rating > z1.rating)
            return true;
        else
            return false;
    }
    bool operator<(carte& z1) ///supraincarcare operator <
    {
        if(rating < z1.rating)
            return true;
        else
            return false;
    }
};

carte::carte(char* denumire_carte = NULL, char* autor_principal = NULL, char* al_doilea_autor = NULL, int numar_pagini = 0, float pret = 0, float rating = 0)
{
    strcpy(denumire_carte, denumire_carte);
    strcpy(autor_principal, autor_principal);
    strcpy(al_doilea_autor, al_doilea_autor);
    this->numar_pagini = numar_pagini;
    this->pret = pret;
    this->rating = rating;
}

carte::carte(carte &z)
{
    strcpy(denumire_carte, z.denumire_carte);
    strcpy(autor_principal, z.autor_principal);
    strcpy(al_doilea_autor, z.al_doilea_autor);
    this->numar_pagini = z.numar_pagini;
    this->pret = z.pret;
    this->rating = z.rating;
}

carte::~carte()
{
    strcpy(denumire_carte,"");
    strcpy(autor_principal,"");
    strcpy(al_doilea_autor,"");
    this->numar_pagini = 0;
    this->pret = 0;
    this->rating = 0;
}
void carte::set_denumire_carte(char *dc)
{
    strcpy(denumire_carte, dc);
}

void carte::set_autor_principal(char *ap)
{
    strcpy(autor_principal, ap);
}

void carte::set_al_doilea_autor(char *ada)
{
    strcpy(al_doilea_autor, ada);
}

void carte::set_numar_pagini(int np)
{
    numar_pagini = np;
}

void carte::set_pret(float p)
{
    pret = p;
}

void carte::set_rating(float r)
{
    rating = r;
}

void carte::citire(istream &in)
{

    cout<<"Avem cartea: ";
    in.getline(denumire_carte, 256);
    cout<<denumire_carte<<endl;

    cout<<"Autorul principal este: ";
    in.getline(autor_principal, 256);
    cout<<autor_principal<<endl;

    cout<<"Al doilea autor este: ";
    in.getline(al_doilea_autor, 256);
    cout<<al_doilea_autor<<endl;

    cout<<"Numarul de pagini al cartii este: ";
    in>>numar_pagini;
    if (numar_pagini <= 1)
    {
        while(numar_pagini <= 1)
        {
            cout<<"Numarul de pagini este invalid, introduce un numar de pagini valid mai mare decat 1: ";
            in>>numar_pagini;
        }
    }
    cout<<numar_pagini<<endl;

    cout<<"Pretul cartii in lei este: ";
    in>>pret;
    if (pret < 0)
    {
        while(pret < 0)
        {
            cout<<"Pretul este invalid, introduce un pret mai mare sau egal decat 0: ";
            in>>pret;
        }
    }
    cout<<pret<<endl;

    cout<<"Cartea are o evaluare de nota: ";
    in>>rating;
    if (rating < 1 || rating > 10)
    {
        while(rating < 1 || rating > 10)
        {
            cout<<"Nota este invalida, introduce un numar intre 1 si 10: ";
            in>>rating;
        }
    }
    cout<<rating<<endl<<endl;

}

istream& operator>>(istream& in, carte& z)
{
    z.citire(in);
    return in;
}

void carte::afisare(ostream &out)
{
    cout<<"Avem cartea: ";
    out<<denumire_carte<<endl;

    cout<<"Autorul principal este: ";
    out<<autor_principal<<endl;

    cout<<"Al doilea autor este: ";
    out<<al_doilea_autor<<endl;

    cout<<"Numarul de pagini al cartii este: ";
    out<<numar_pagini<<endl;

    cout<<"Pretul cartii in lei este: ";
    out<<pret<<endl;

    cout<<"Cartea are o evaluare de nota: ";
    out<<rating<<endl;
}

ostream& operator<<(ostream& out, carte& z)
{
    z.afisare(out);
    return out;
}

carte& carte::operator=(carte &z)
{
    strcpy(denumire_carte, z.denumire_carte);
    strcpy(autor_principal, z.autor_principal);
    strcpy(al_doilea_autor, z.al_doilea_autor);
    numar_pagini = z.numar_pagini;
    pret = z.pret;
    rating = z.rating;
}

void menu_output()
{
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Afisam cartile."<<"\n";
    cout<<"2. Citim carti."<<"\n";
    cout<<"3. Adaugam o carte noua."<<"\n";
    cout<<"4. Compara doua carti."<<"\n";
    cout<<"5. Schimba ordinea cartilor deja adaugate."<<"\n";
    cout<<"6. Modifica informatiile unei carti."<<"\n";

    printf("0. Iesire.");
    printf("\n");
}

void menu()
{
    int i,n,j;
    j=0;
    carte *v = new carte[100], aux;
    int option;///optiunea aleasa din meniu
    option=0;
    cout<<"Aceasta este simularea unei baze de date cu carti."<<endl;
    cout<<"Pentru a incepe, alegeti optiunea 2 pentru a citi primele carti."<<endl;
    do
    {
        menu_output();

        printf("\nIntroduceti numarul actiunii: ");
        scanf("%d", &option);

        cout<<endl;

        if (option == 1)
        {
            if (j == 0)
                cout<<"Nu sunt carti citite. Alege optiunea 2.";
            else
            {
                cout<<"Avem "<<j<<" carti."<<endl<<endl;
                for(i=0; i<j; i++)
                    cout<<v[i]<<endl;
            }

            cout<<endl;
        }
        if (option==2)
        {
            if(j!=0)
            {
                cout<<"Sunt carti citite, alege optiunea 3 pentru a adauga alte carti."<<endl;
            }
            else{
            cout<<"Cate carti citim?: ";
            cin>>n;
            j=n;
            cout<<endl;
            for(i=0; i<j; i++)
            {
                cin.get();
                cin>>v[i];
            }

            cout<<endl;
            }
        }
        if (option==3)
        {
            if(j == 0)
                cout<<"Nu sunt carti citite. Alege optiunea 2."<<endl;
            else
            {
                cin.get();
                cin>>v[j];
                for(i=0; i<=j; i++)
                    cout<<v[i]<<endl;
                j++;

                cout<<endl;
            }
        }

        if (option==4)
        {
            if(j == 0)
                cout<<"Nu sunt carti citite. Alege optiunea 2."<<endl;
            else
            {
                int c1, c2;
                cout<<"Alege un numar al cartii intre 1 si "<<j<<"."<<endl<<endl;
                cout<<"Comparam cartea: ";
                cin>>c1;
                while (c1 > j || c1 <= 0)
                {
                    cout<<"Nu exista aceasta carte, introduceti un numar al cartii intre 1 si "<<j<<": ";
                    cin>>c1;
                    cout<<endl;
                }
                cout<<"cu cartea: ";
                cin>>c2;
                while (c2 > j || c2 <= 0)
                {
                    cout<<"Nu exista aceasta carte, introduceti un numar al cartii intre 1 si "<<j<<": ";
                    cin>>c2;
                    cout<<endl;
                }
                cout<<endl;

                if(v[c1-1]>v[c2-1])
                    cout<<"Cartea "<<c1<<" este mai buna.";
                if (v[c1-1]<v[c2-1])
                    cout<<"Cartea "<<c2<<" este mai buna.";
                if(!(v[c1-1]>v[c2-1]) and !(v[c1-1]<v[c2-1]))
                    cout<<"Cartile sunt la fel de bune.";
                cout<<endl;
            }
        }
        if (option==5)
        {
            if(j == 0)
                cout<<"Nu sunt carti citite. Alege optiunea 2."<<endl;
            else
            {
                carte aux;
                int s1, s2;
                cout<<"Poti alege un numar de carti intre 1 si "<<j<<"."<<endl<<endl;
                cout<<"Schimbam cartea: ";
                cin>>s1;
                while (s1 > j || s1 <= 0)
                {
                    cout<<"Nu exista aceasta carte, introduceti un numar al cartii intre 1 si "<<j<<": ";
                    cin>>s1;
                    cout<<endl;
                }
                cout<<"cu cartea: ";
                cin>>s2;
                while (s2 > j || s2 <= 0)
                {
                    cout<<"Nu exista aceasta carte, introduceti un numar al cartii intre 1 si "<<j<<": ";
                    cin>>s2;
                    cout<<endl;
                }
                cout<<endl;

                aux = v[s1-1];
                v[s1-1] = v[s2 - 1];
                v[s2 - 1] = aux;

                for(i=0; i<j; i++)
                    cout<<v[i]<<endl;

                cout<<endl;
            }
        }

        if( option == 6)
        {
            if(j == 0)
                cout<<"Nu sunt carti citite. Alege optiunea 2."<<endl;
            else
            {
                int m1, pag;
                float nr;
                cout<<"Alege un numar al cartii intre 1 si "<<j<<"."<<endl<<endl;
                cout<<"Vrem sa modificam informatii din cartea : ";
                cin>>m1;
                cout<<endl;

                while (m1 > j || m1 <= 0)
                {
                    cout<<"Nu exista aceasta carte, introduceti un numar al cartii intre 1 si "<<j<<": ";
                    cin>>m1;
                    cout<<endl;
                }
                char *yes = "y", *n = "n", *citire, *sir;


                cin.get();
                cout<<"Vrei sa modifici numele cartii? (y/n): ";
                cin.getline(citire, 256);

                if (strcmp(yes, citire) == 0)
                {
                    cout<<"Noul nume al cartii este: ";
                    cin.getline(sir, 256);
                    v[m1-1].set_denumire_carte(sir);
                }

                cout<<endl;
                cout<<"Vrei sa modifici numele primului autor? (y/n): ";
                cin.getline(citire, 256);

                if (strcmp(yes, citire) == 0)
                {
                    cout<<"Noul nume al primului autor al cartii este: ";
                    cin.getline(sir, 256);
                    v[m1-1].set_autor_principal(sir);
                }

                cout<<endl;
                cout<<"Vrei sa modifici numele autorului secund? (y/n): ";
                cin.getline(citire, 256);

                if(strcmp(yes, citire) == 0)
                {
                    cout<<"Noul nume al autorului secund este: ";
                    cin.getline(sir, 256);
                    v[m1-1].set_al_doilea_autor(sir);
                }

                cout<<endl;
                cout<<"Vrei sa modifici numarul de pagini al cartii? (y/n): ";
                cin.getline(citire, 256);

                if(strcmp(yes, citire) == 0)
                {
                    cout<<"Noul numar de pagini al cartii este: ";
                    cin>>pag;
                    while(pag <= 1)
                    {
                        cout<<"Pretul este invalid, introduce un numar de pagini mai mare decat 0: ";
                        cin>>pag;
                    }
                    v[m1-1].set_numar_pagini(pag);
                    cin.get();
                }

                cout<<endl;
                cout<<"Vrei sa modifici pretul cartii? (y/n): ";
                cin.getline(citire, 256);

                if (strcmp(yes, citire) == 0)
                {
                    cout<<"Noul pret al cartii este: ";
                    cin>>nr;
                    while(nr < 0)
                    {
                        cout<<"Pretul este invalid, introduce un pret mai mare sau egal decat 0: ";
                        cin>>nr;
                    }
                    v[m1-1].set_pret(nr);
                    cin.get();
                }

                cout<<endl;
                cout<<"Vrei sa modifici nota cartii? (y/n): ";
                cin.getline(citire, 256);

                if(strcmp(yes, citire) == 0)
                {
                    cout<<"Noua nota a cartii este: ";
                    cin>>nr;
                    while(nr < 1 || nr > 10)
                    {
                        cout<<"Nota este invalida, introduce un numar intre 1 si 10: ";
                        cin>>nr;
                    }
                    v[m1-1].set_rating(nr);
                }
            }
        }
        if (option==0)
        {
            printf("\nEXIT!\n");
        }
        if (option<0||option>6)
        {
            printf("\nSelectie invalida\n");
        }
        cout<<"\n";
        system("pause"); ///Pauza - Press any key to continue...
        //system("cls");

    }
    while(option!=0);
    delete []v;
}
int main()
{
    menu();
    return 0;
}
