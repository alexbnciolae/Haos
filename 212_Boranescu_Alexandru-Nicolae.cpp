#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unordered_map>

using namespace std;

class cont
{
protected:
    string detinator;
    int zi;
    int luna;
    int an;
    double sold;
    int ID;
    static int nrConturi;

public:
    cont (string, int, int,int, double);
    cont (const cont&); //cont (const cont&)
    virtual ~cont()
    {
        nrConturi--;
    };

    virtual void citire (istream &in);
    virtual void afisare(ostream &out);

    cont& operator=(const cont &p); //cont& operator=(const cont &p);
    friend istream& operator>>(istream&, cont&);
    friend ostream& operator<<(ostream&, cont&);
    static void afisare_nrcont()
    {
        cout << "Banca noastra gestioneaza: " << nrConturi << endl;
    }

    int getIDCont() const
    {
        return ID;
    }

    virtual void tranzactie(double suma)
    {
        sold = sold+suma;
    }
};

int cont::nrConturi;

cont::cont (string detinator = "", int zi = 0, int luna = 0, int an = 0, double sold = 0)
{
    this -> detinator = detinator;

    try
    {
        if (zi < 0)
            throw zi;
        this -> zi = zi;
    }
    catch (int x)
    {
        cout<<"Eroare in constructor, numarul de zile nu pot fi negative.\n";
        exit(EXIT_FAILURE);
    }

    try
    {
        if (luna<0)
            throw luna;
        this -> luna = luna;
    }
    catch (int x)
    {
        cout<<"Eroare in constructor, numarul de luni nu pot fi negative.\n";
        exit(EXIT_FAILURE);
    }

    try
    {
        if (an<0)
            throw an;
        this -> an = an;
    }
    catch (int x)
    {
        cout<<"Eroare in constructor, numarul de ani nu pot fi negative.\n";
        exit(EXIT_FAILURE);
    }

    try
    {
        if (sold<0)
            throw sold;
        this->sold = sold;
    }
    catch (double x)
    {
        cout<<"Eroare in constructor, numarul de sold nu pot fi negative.\n";
        exit(EXIT_FAILURE);
    }
    nrConturi++;
    ID = nrConturi;
}


cont:: cont (const cont &p)
{
    detinator = p.detinator;
    zi = p.zi;
    luna = p.luna;
    an = p.an;
    sold = p.sold;
    nrConturi++;
}


cont& cont:: operator= (const cont &p)
{
    if (this!=&p)
    {
        detinator = p.detinator;
        zi = p.zi;
        luna = p.luna;
        an = p.an;
        sold = p.sold;
    }
    return *this;
}

istream& operator>>(istream& in,cont& f)
{
    f.citire(in);
    return in;
}

ostream& operator<<(ostream& out, cont& f)
{
    f.afisare(out);
    return out;
}

void cont::citire(istream &in)
{
    cout<<endl;

    cout<<"Nume detinator: ";
    getline(in, detinator);
    //in>>detinator;

    cout<<"Zi: ";
    in>>zi;

    cout<<"Luna: ";
    in>>luna;

    cout<<"An: ";
    in>>an;

    cout<<"Sold curent: ";
    in>>sold;

}

void cont::afisare(ostream &out)
{
    out<<"Nume detinator: "<<detinator<<"\n";
    out<<"Zi: "<<zi<<"\n";
    out<<"Luna: "<<luna<<"\n";
    out<<"An: "<<an<<"\n";
    out<<"Sold: "<<sold<<"\n";
    out<<endl;
}

class cont_economii:public cont
{
private:
    double rata_dobanda;
    int timp_rata_dobanda;
    vector<double> react;
public:
    cont_economii (string, int, int,int, double, double, int, vector<double>);
    cont_economii (const cont_economii&);
    ~cont_economii() {};

    void citire (istream &in);
    void afisare(ostream &out);

    cont_economii& operator=(const cont_economii &p);
    void tanzactie (string);
    // friend istream& operator>>(istream&, cont_economii&);
    // friend ostream& operator<<(ostream&, cont_economii&);

    /// void tranzactie (string, double);

    int get_timp_rata_dobanda()
    {
        return timp_rata_dobanda;
    };

};


cont_economii::cont_economii(string detinator = "", int zi = 0, int luna = 0, int an = 0, double sold = 0, double rata_dobanda = 0, int timp_rata_dobanda = 0, vector<double> react = {}):cont(detinator, zi, luna, an, sold)
{
    this -> rata_dobanda = rata_dobanda;
    this -> timp_rata_dobanda = timp_rata_dobanda;
    int i = 0;
    for(i = 0; i < timp_rata_dobanda; i++)
    {
        this->react.push_back(react[i]);
    }
}

cont_economii::cont_economii(const cont_economii & x):cont(x)
{
    rata_dobanda = x.rata_dobanda;
    timp_rata_dobanda = x.timp_rata_dobanda;
    int i;
    for(i = 0; i < timp_rata_dobanda; i++)
    {
        this->react.push_back(x.react[i]);
    }
}

cont_economii& cont_economii:: operator= (const cont_economii &x)
{
    if (this!=&x)
    {
        rata_dobanda = x.rata_dobanda;
        timp_rata_dobanda = x.timp_rata_dobanda;
        int i;
        for(i = 0; i < timp_rata_dobanda; i++)
        {
            this->react.push_back(x.react[i]);
        }
    }
    return *this;
}

void cont_economii::citire(istream& in)
{
    cont::citire(in);
    cout<<"Rata dobanzii (in procente) este: ";
    in>>rata_dobanda;

    cout<<"Timp de rata al dobanzii este: ";
    in>>timp_rata_dobanda;

    int i;
    double sumaDobanda;
    for(i = 0; i < timp_rata_dobanda; i++)
    {
        sumaDobanda = sold * (rata_dobanda/100);
        sold = sold + sumaDobanda;
        react.push_back(sold);
    }
}


void cont_economii::afisare(ostream& out)
{
    cont::afisare(out);
    out<<"Rata dobanzii este: "<<rata_dobanda<<endl;
    out<<"Timpul de rata al dobanzii este: "<<timp_rata_dobanda<<endl;

    int i;
    for(i = 0; i < timp_rata_dobanda; i++)
    {
        out<<"Dupa dobanda "<<i+1<<" soldul este: "<<react[i]<<endl;
    }
}

istream& operator>>(istream& in, cont_economii& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, cont_economii& p)
{
    p.afisare(out);
    return out;
}

/*void cont_economii::tranzactie(string trans, double suma)
{
    cont::tranzactie(trans, suma);
    if(trans == "depunere" || trans == "Depunere")
        react.push_back(sold);

    if(trans == "retragere" || trans == "Retragere")
        react.push_back(sold);

}*/
///=============================================

class cont_curent:public cont
{
private:
    int tranzactii_gratuite;
public:
    cont_curent (string, int, int,int, double, int);
    cont_curent (const cont_curent&);
    ~cont_curent() {};

    void citire (istream &in);
    void afisare(ostream &out);

    cont_curent& operator=(const cont_curent &p);
    //friend istream& operator>>(istream&, cont_curent&);
    //friend ostream& operator<<(ostream&, cont_curent&);

    void tranzactie(string,double);
};

cont_curent::cont_curent(string detinator = "", int zi = 0, int luna = 0, int an = 0, double sold = 0, int tranzactii_gratuite = 0):cont(detinator, zi, luna, an, sold)
{
    this -> tranzactii_gratuite = tranzactii_gratuite;
}

cont_curent::cont_curent (const cont_curent& x):cont(x)
{
    tranzactii_gratuite = x.tranzactii_gratuite;
}

cont_curent& cont_curent:: operator= (const cont_curent &x)
{
    if (this!=&x)
    {
        tranzactii_gratuite = x.tranzactii_gratuite;
    }
    return *this;
}

void cont_curent::citire(istream& in)
{
    cont::citire(in);
    cout<<"Numarul de tranzactii gratuite: ";
    in>>tranzactii_gratuite;
}


void cont_curent::afisare(ostream& out)
{
    cont::afisare(out);
    out<<"Numarul de tranzactii gratuite: "<<tranzactii_gratuite;
}

void cont_curent::tranzactie(string trans, double suma)
{
    double comision;
    if(trans == "banca mea" && tranzactii_gratuite>0)
        comision = 0;
    else
    {
        cout<<"Comisionul retragerii/platii este: ";
        cin>>comision;
    }

    if(trans == "alta banca" || trans == "online" || tranzactii_gratuite == 0)
        sold = sold - comision - suma;

    if(trans == "banca mea" && tranzactii_gratuite > 0)
    {
        tranzactii_gratuite--;
        sold = sold - suma;
    }
}


template <class T>
class GestionareConturi
{
private:
    int citireNrConturi;
    vector <int> IDuri;
    vector<T> conturi;
public:
    GestionareConturi(int citireNrConturi = 0, vector <T> conturi = {}, vector<int>IDuri = {})
    {
        this -> citireNrConturi = citireNrConturi;
        // Conturi = new T[citireNrConturi];
        // for(int i = 0; i<citireNrConturi; i++)
        //     this->Conturi[i] = Conturi[i];
        this->conturi = conturi;
        for(auto & it : IDuri)
            this->IDuri.push_back(it);
    }

    GestionareConturi(const GestionareConturi& v)
    {
        this -> citireNrConturi = v.citireNrConturi;
        for(auto & it : v.conturi)
            this->conturi.push_back(it);
        for(auto & it : v.IDuri)
            this->IDuri.push_back(it);
    }

    ~GestionareConturi() {};
    void citire (istream& in)
    {
        cout<<endl;
        cout<<"Citim numarul de conturi: ";
        in>>citireNrConturi;

        double suma;
        bool opt;
        //g.Conturi = new T[citireNrConturi];
        cout<<"Introducem obiectele: \n";
        cont c;
        for(int i = 0; i<citireNrConturi; i++)
        {
            in.get();

            in>>c;
            conturi.push_back(c);
            cout<<"Facem vreo depunere? (0 = Nu / 1 = Da): ";
            cin>>opt;

            while(opt == 1)
            {
                cout<<"Suma adaugata este: ";
                cin>>suma;
                conturi[i].tranzactie(suma);
                cout<<"Facem vreo depunere? (0 = Nu / 1 = Da): ";
                cin>>opt;
            }

        }
    }
    friend istream& operator >>(istream &in, GestionareConturi <T> &g)
    {
        g.citire(in);
        return in;
    }

    GestionareConturi& operator +=(T& v)
    {
        IDuri.push_back(v.getIDCont());
        conturi.push_back(v);
        citireNrConturi++;
        return *this;
    }

    friend ostream& operator <<(ostream &out, GestionareConturi <T> &g)
    {
        out<<endl;
        out<<"Avem numarul urmator de conturi: "<<g.citireNrConturi<<"\n";
        for(int i = 0; i<g.citireNrConturi; i++)
            out << g.conturi[i] << "\n";
        return out;
    }


};

template <>
class GestionareConturi <cont_economii>
{
private:
    int citireNrConturi;
    vector <int> IDuri;
    vector<cont_economii> conturi;
public:
    GestionareConturi(int citireNrConturi = 0, vector <cont_economii> conturi = {}, vector<int>IDuri = {})
    {
        this -> citireNrConturi = citireNrConturi;
        // Conturi = new cont_economii[citireNrConturi];
        // for(int i = 0; i<citireNrConturi; i++)
        //     this->Conturi[i] = Conturi[i];
        this->conturi = conturi;
        for(auto & it : IDuri)
            this->IDuri.push_back(it);
    }

    GestionareConturi(const GestionareConturi& v)
    {
        this -> citireNrConturi = v.citireNrConturi;
        for(auto & it : v.conturi)
            this->conturi.push_back(it);
        for(auto & it : v.IDuri)
            this->IDuri.push_back(it);
    }

    ~GestionareConturi() {};
    void citire (istream& in)
    {
        cout<<endl;
        cout<<"Citim numarul de conturi: ";
        in>>citireNrConturi;

        double suma;
        bool opt;
        //g.Conturi = new cont_economii[citireNrConturi];
        cout<<"Introducem obiectele: \n";
        cont_economii c;
        for(int i = 0; i<citireNrConturi; i++)
        {
            in.get();
            in>>c;
            conturi.push_back(c);

        }
    }
    friend istream& operator >>(istream &in, GestionareConturi <cont_economii> &g)
    {
        g.citire(in);
        return in;
    }

    GestionareConturi& operator +=(cont_economii& v)
    {
        IDuri.push_back(v.getIDCont());
        conturi.push_back(v);
        citireNrConturi++;
        return *this;
    }
    void afisare(ostream& out)
    {
        out<<endl;
        out<<"Avem numarul urmator de conturi: "<<citireNrConturi<<"\n";
        for(int i = 0; i<citireNrConturi; i++)
            if(conturi[i].get_timp_rata_dobanda() == 12)
            {
                out << conturi[i] << "\n";
            }
    }
    friend ostream& operator <<(ostream &out, GestionareConturi <cont_economii> &g)
    {
        g.afisare(out);
        return out;
    }
};

template <>
class GestionareConturi<cont_curent>
{
private:
    int citireNrConturi;
    vector <int> IDuri;
    vector<cont_curent> conturi;
public:
    GestionareConturi(int citireNrConturi = 0, vector <cont_curent> conturi = {}, vector<int>IDuri = {})
    {
        this -> citireNrConturi = citireNrConturi;
        // Conturi = new cont_curent[citireNrConturi];
        // for(int i = 0; i<citireNrConturi; i++)
        //     this->Conturi[i] = Conturi[i];
        this->conturi = conturi;
        for(auto & it : IDuri)
            this->IDuri.push_back(it);
    }

    GestionareConturi(const GestionareConturi& v)
    {
        this -> citireNrConturi = v.citireNrConturi;
        for(auto & it : v.conturi)
            this->conturi.push_back(it);
        for(auto & it : v.IDuri)
            this->IDuri.push_back(it);
    }

    ~GestionareConturi() {};
    void citire (istream& in)
    {
        cout<<endl;
        cout<<"Citim numarul de conturi: ";
        in>>citireNrConturi;


        string operatiune;
        double suma;
        bool op;

        //g.Conturi = new cont_curent[g.citireNrConturi];
        cout<<"Introducem obiectele: \n";
        cont_curent c;
        for(int i = 0; i<citireNrConturi; i++)
        {
            in.get();
            in>>c;
            conturi.push_back(c);
            cout<<"Vrem sa facem vreo retragere/plata? (0 = Nu / 1 = Da):";
            cin>>op;
            while(op == 1)
            {
                in.get();
                cout<<"Unde vrem sa facem retragerea/plata? (online / alta banca / banca mea): ";
                getline(cin,operatiune);

                cout<<"Ce suma vrem sa retragem din cont?: ";
                cin>>suma;

                conturi[i].tranzactie(operatiune, suma);
                cout<<"Vrem sa facem vreo retragere/plata? (0 = Nu / 1 = Da):";
                cin>>op;

            }
        }
    }
    friend istream& operator >>(istream &in, GestionareConturi <cont_curent> &g)
    {
        g.citire(in);
        return in;
    }

    GestionareConturi& operator +=(cont_curent& v)
    {
        IDuri.push_back(v.getIDCont());
        conturi.push_back(v);
        citireNrConturi++;
        return *this;
    }

    friend ostream& operator <<(ostream &out, GestionareConturi <cont_curent> &g)
    {
        out<<endl;
        out<<"Avem numarul urmator de conturi: "<<g.citireNrConturi<<"\n";
        for(int i = 0; i<g.citireNrConturi; i++)
            out << g.conturi[i] << "\n";
        return out;
    }


};

void menu_output()
{
    cout<<"\nGESTIUNEA UNOR CONTURI DE BANCA\n";
    cout<<"\n\t\tMENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citeste informatii despre conturi si le afisam. (clasa de baza)";
    cout<<"\n";
    cout<<"2. Depunere suma in conturi --- TEMPLATE (cont).";
    cout<<"\n";
    cout<<"3. Citirea si afisarea conturilor de economii cu 12 luni timp de de rata doabanda  --- TEMPLATE (conturi economii - SPECIALIZARE).";
    cout<<"\n";
    cout<<"4. Operatiuni pe contul curent --- TEMPLATE(cont curent-SPECIALIZARE).";
    cout<<"\n";
    cout<<"5. Folosim operatorul += pentru clasa cont si template-ul cont.";
    cout<<"\n";
    cout<<"6. Folosim operatorul += pentru clasa conturi economii si template-ul cont economii.";
    cout<<"\n";
    cout<<"7. Folosim operatorul += pentru clasa cont curent  si template-ul cont cont curent.";
    cout<<"\n";
    cout<<"0. Iesire.";
    cout<<"\n";
}
void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;
    int n=0;
    cont *v;

    do
    {
        menu_output();
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;

        if(option == 1)
        {
            cout<<"Introduceti numarul de obiecte citite: ";
            cin>>n;

            v = new cont[n];

            if(n>0)
            {
                for(int i = 0; i<n; i++)
                {
                    cin.get();
                    cin>>v[i];
                }

                for(int i = 0; i<n; i++)
                {
                    cout<<v[i]<<endl;
                }

            }
        }

        if(option == 2)
        {
            GestionareConturi <cont> x;
            cin>>x;
            cout<<x;
        }

        if(option == 3)
        {
            GestionareConturi <cont_economii> x;
            cin>>x;
            cout<<x;
        }

        if(option == 4)
        {
            GestionareConturi <cont_curent> x;
            cin>>x;
            cout<<x;
        }

        if(option == 5)
        {
            cont y;
            cout<<"Vrem sa adaugam obiectul: ";
            cout<<endl;
            cin.get();
            cin>>y;

            GestionareConturi <cont> x;
            cin>>x;

            x += y;
            cout<<x;
        }

        if(option == 6)
        {
            cont_economii y;
            cout<<"Vrem sa adaugam obiectul: ";
            cout<<endl;
            cin.get();
            cin>>y;

            GestionareConturi <cont_economii> x;
            cin>>x;

            x += y;
            cout<<x;
        }

        if(option == 7)
        {
            cont_curent y;
            cout<<"Vrem sa adaugam obiectul: ";
            cout<<endl;
            cin.get();
            cin>>y;

            GestionareConturi <cont_curent> x;
            cin>>x;
            x += y;
            cout<<x;
        }

        if (option==0)
        {
            cout<<"\nEXIT\n\n";
        }
        if (option<0||option>8)
        {
            cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option!=0);
}
int main()
{
    menu();
    return 0;
}
