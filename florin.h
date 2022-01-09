#include <iostream>
#include <cstring>

using namespace std;

void push_f(Nod *& S, char c) ///adaugare operanzi pe stiva de char.uri
{
    Nod *nou = new(Nod);
    nou->inf = c;
    nou->urm = S;
    S = nou;
}

void push_int_f(Nod_postfixat *& S, int c) ///adaugare el int pe stiva de int.uri
{
    Nod_postfixat *nou = new(Nod_postfixat);
    nou->inf = c;
    nou->urm = S;
    S = nou;
}

char top_f(Nod *S)
{
    return S->inf;
}

int top_int_f(Nod_postfixat *S)
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

void pop_int_f(Nod_postfixat *& S)
{
    Nod_postfixat *nou = new(Nod_postfixat);
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

int transformare_int_f(char cuv[])
{
    int nr = 0;
    for(int i = 0; i < strlen(cuv); i++)
    {
        nr = nr * 10 + (int)cuv[i] - 48;
    }
    return nr;
}

void expresie_postfixata_f(char expresie[], Sir_postfixat postfixat[], int &j)
{
    int i;

    Nod *stiva = new Nod;
    stiva = NULL;

    j = 0;

    for(i = 0; i < strlen(expresie); i++)                   ///parcurgem expresia
    {
        if(strchr("0123456789", expresie[i]) != 0)          ///cand gasim valoare/numar/variabila
        {
            int poz = 0;
            while(strchr("0123456789", expresie[i]) != 0)   ///Parcurgem pana la operand
            {
                postfixat[j].nume[poz] = expresie[i];      ///mutam valoarea variabilei(insiruirea de cifre intepretate ca si caractere), pe pozitia coresp. in sirul postfixat
                poz++; i++;
            }
            postfixat[j].nume[poz] = 0;
            i--;
            j++;   ///actualizam indicele pozitiei pt sirul postfixat
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
        cout<<"Sir postfixat: ";
        for(int k = 0; k < j; k++)   ///afisare sir postfixat ////////COUT PARTIAL
        {
            cout << postfixat[k].nume;
        }
        cout << "\nStiva:\n";
        afisare(stiva);             ///afisare stiva/////////COUT PARTIAL
        cout <<"\n\n";

    }
    while(stiva != NULL)
    {
        postfixat[j].nume[0] = top_f(stiva);
        j++;
        pop_f(stiva);
    }

}

int calcul_expresie_f(char expresie[])
{

    int n = 0, i;

    Sir_postfixat postfixat[200];

    expresie_postfixata_f(expresie, postfixat, n);          ///formez expresia postfixata ce va contine n 'elemente'

    for(i = 0; i < n; i++)
    {
        cout << postfixat[i].nume << "-";
    }

    ///#########################################
    ///####CALCULAREA EXPRESIEI POSTFIXATA######
    ///#########################################



    Nod_postfixat *stiva = new Nod_postfixat;

    int valoare = 0;
    for(i = 0; i < n; i++)
    {
        if(strchr("0123456789", postfixat[i].nume[0])!=0)
        {
            push_int_f(stiva, transformare_int_f(postfixat[i].nume));
        }
        else
        {
            int dreapta = top_int_f(stiva);
            pop_int_f(stiva);

            int stanga = top_int_f(stiva);
            pop_int_f(stiva);


            switch (postfixat[i].nume[0])
            {
                case '+': valoare = stanga + dreapta;
                    break;
                case '-': valoare = stanga - dreapta;
                    break;
                case '*': valoare = stanga * dreapta;
                    break;
                case '/':
                    try{
                        if(dreapta != 0)
                        {
                            valoare = stanga / dreapta;
                        }
                        else
                        {
                            throw(404);
                        }
                    }
                    catch (int error)
                    {
                        cout << "\nDivide by zero error encountered\n";
                    }
                    break;

                default:
                    break;
            }



            push_int_f(stiva, valoare);
        }
    }
    valoare = top_int_f(stiva);
    pop_int_f(stiva);


    for(int i = 0; i < n; i++)
    {
        while(strlen(postfixat[i].nume) != 0)
        {
            strcpy(postfixat[i].nume, postfixat[i].nume + 1); ///eliberarea caracterelor din sirul postfixat
        }
    }

    return valoare;

}

int valoare_adevar_expresie(char expresie[])
{
    char stanga[256]="", dreapta[256]="";
    int i = 0;
    int poz_stanga = 0, poz_dreapta = 0, poz_operand = 0;
    while(strchr("<>=!",expresie[i]) == 0)
    {
        if(expresie[i] != ' ')
        {
            stanga[poz_stanga] = expresie[i];   ///salvez sirul din partea stanga a operandului in sirul stanga
            poz_stanga++;
        }
        i++;
    }

    char operand[4]="";
    while(strchr("<>=!", expresie[i]) != 0)
    {
        if(expresie[i] != ' ')
        {
            operand[poz_operand] = expresie[i]; ///salvez operandul
            poz_operand++;
        }
        i++;
    }

    while(strchr("<>=!",expresie[i]) == 0)
    {
        if(expresie[i] != ' ')
        {
            dreapta[poz_dreapta] = expresie[i];   ///salvez sirul din partea dreapta a operandului in sirul dreapta
            poz_dreapta++;
        }
        i++;
    }
    int val_stanga = calcul_expresie_f(stanga); ///atribui valoarea expresiei din sirul stanga
    int val_dreapta = calcul_expresie_f(dreapta);  ///atribui valoarea expresiei din sirul dreapta

    if (val_stanga == 404)
        return 404;

    switch (operand[0])
    {
        case '<':
            if(operand[1] == '=')
            {
                if(val_stanga <= val_dreapta)
                    return true;
                return false;
            }
            else
            {
                if(val_stanga < val_dreapta)
                    return true;
                return false;
            }
            break;


        case '>':
            if(operand[1] == '=')
            {
                if(val_stanga >= val_dreapta)
                    return true;
                return false;
            }
            else
            {
                if(val_stanga > val_dreapta)
                    return true;
                return false;
            }
            break;

        case '!':
            if(val_stanga != val_dreapta)
                return true;
            return false;

        case '=':
            if(val_stanga == val_dreapta)
                return true;
            return false;
    }

}

void output_code(LogicBlock *first_block, Variables vars, char code_text[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE], int &code_line_size)
{
    /*
    EMPTY_BLOCK 0
    START_BLOCK 1
    INPUT_BLOCK 2  ///  cin >> n
    OUTPUT_BLOCK 3 ///  cout << n;
    ASSIGN_BLOCK 4  ///  n = 3 + 3
    DECISION_BLOCK 5 ///  if else
    STOP_BLOCK 6   ///  return
    */

    code_line_size = 0;
    strcpy(code_text[++code_line_size],"#include <iostream>");
    strcpy(code_text[++code_line_size],"#include <math.h>");
    strcpy(code_text[++code_line_size],"using namespace std;");
    strcpy(code_text[++code_line_size],"int main()");
    strcpy(code_text[++code_line_size],"{");
    strcpy(code_text[++code_line_size],"\tint ");

    LogicBlock *step = first_block;

    for(int i = 1; i <= code.vars.varsNumber; i++)
    {
        strcat(code_text[code_line_size], " ");
        strcat(code_text[code_line_size], code.vars.var[i].name);
        strcat(code_text[code_line_size], ",");
    }
    strcat(code_text[code_line_size], "\b;");



    strcpy(code_text[++code_line_size], "\treturn 0;");
    strcpy(code_text[++code_line_size], "}");

    ///verificare
    cout <<"\n\nSource Code: \n\n";
    for(int i = 1; i <= code_line_size; i++)
    {
        cout << code_text[i] << "\n";
    }

    if(step->typeId == 5)
    {
        if(step->tru)
            step = step->tru;
        else
            step = step->fls;
    }
    else
        first_block = first_block->next;
}
