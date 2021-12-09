#include <iostream>
#include <cstring>

using namespace std;

struct Nod   ///stiva pentru operanzi
    {
        char inf;
        Nod *urm;
    }*stiva;

struct Valoare                                           ///sir de caractere pentru fiecare val din exprsie.
    {
        char nume[200];                                      ///consideram ca o valoare poate avea cel putin o cifra
    }postfixat[256];

void push_f(Nod *& S, char c)
{
    Nod *nou = new(Nod);
    nou->inf = c;
    nou->urm = S;
    S = nou;
}

char top_f(Nod *S)
{
    return S->inf;
}

void pop_f(Nod *& S)
{
    Nod *nou = new(Nod);
    nou = S;
    S = S ->urm;
    delete(nou);
}

int prioritate_f(char c1, char c2)
{
    if(c1 == '*' || c1 == '/' || c1 == '+' || c1 == '-')
    {
        if(c2 == '+' || c2 == '-')
        {
            return 1;
        }
    }
    return 0;
}

void afisare(Nod *p)
{
    while(p != NULL)
    {
        cout << p->inf << "\n";
        p = p->urm;
    }
}
void expresie_postfixata_f(char expresie[256], Valoare postfixat[256], int &j)
{
    int i;

    stiva = NULL;

    j = 0;

    for(i = 0; i < strlen(expresie); i++)                   ///parcurgem expresia
    {
        if(strchr("0123456789", expresie[i]) != 0)          ///cand gasim valoare/numar/variabila
        {
            /*
            int inceput = i;                                ///salvam poz de inceput
            while(strchr("0123456789", expresie[i]) == 0)
            {
                i++;                                        ///continuam pana la operand
            }
            strncpy(postfixat[j].nume, expresie + inceput, i - inceput); ///mutam valoarea variabilei(insiruirea de cifre intepretate ca si caractere), in sirul de postfixat
            */
            postfixat[j].nume[0] = expresie[i];
            j++;
        }
        else
        {
            if(expresie[i] == ')')                          ///caz in care se deschide paranteza
            {
                while(top_f(stiva) != '(')
                {
                    postfixat[j].nume[0] = top_f(stiva);
                    j++;
                    pop_f(stiva);
                }
                pop_f(stiva);
            }
            else
            {
                while(stiva != NULL && prioritate_f(top_f(stiva), expresie[i]) != 0) ///caz in care semnul din varful stivei e mai imp decat cel actual din expresie
                {
                    postfixat[j].nume[0] = top_f(stiva);
                    j++;
                    pop_f(stiva);
                }
                push_f(stiva, expresie[i]);
            }
        }

        for(int k = 0; k < j; k++)
        {
            cout << postfixat[k].nume << " ";
        }
        cout << "\n";
        afisare(stiva);
        cout <<"\n\n";

    }
    while(stiva != NULL)
    {
        postfixat[j].nume[0] = top_f(stiva);
        j++;
        pop_f(stiva);
    }

}

void calcul_expresie_f(char expresie[256])
{


    int n = 0, i;

    expresie_postfixata_f(expresie, postfixat, n);          ///formez expresia postfixata ce va contine n 'elemente'


    for(i = 0; i < n; i++)
    {
        cout << postfixat[i].nume << " ";
    }

    ///calculez expresia postfixata

}

void expresie_f(char expresie[256])
{


}
