#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include<string>
#include <iomanip>

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

void afisare_f(Nod *p)
{
    while(p != NULL)
    {
        cout << p->inf << "\n";
        p = p->urm;
    }
}

int transform_char_to_int_f(char word[])
{
    int value = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        value = value * 10 + (int)word[i] - 48;
    }
    return value;
}

void transform_int_to_char_f(int value, char word[])
{
    int inv = 0, cnt = 0;
    while(value)
    {
        cnt++;
        inv = inv * 10 + value % 10;
        value /= 10;
    }

    int i = 0;
    while(cnt)
    {
        word[i] = (char)(inv % 10) + 48;
        i++;
        inv /= 10;
        cnt--;
    }
    word[i] = 0;
}

bool is_letter_f(char c)
{
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return true;
    }
    return false;
}

void replace_variable_name_with_value_f(char expresie[])
{
    char aux[VAR_EXPRESSION_SIZE];
    for(int i = 0; i < strlen(expresie); i++)
    {
        if(is_letter_f(expresie[i]))
        {
            int pozitie = 0, index_var;
            char var_name[VAR_NAME_SIZE] = "";
            char value_string[MAX_VALUE_LENGTH] = "";

            while(is_letter_f(expresie[i]))
            {
                var_name[pozitie] = expresie[i];
                pozitie++;
                strcpy(expresie+i, expresie + i + 1);
            }
            var_name[pozitie] = 0;

            for(index_var = 1; index_var <= code.vars.varsNumber; index_var++)
            {
                if(strcmp(var_name, code.vars.var[index_var].name) == 0)
                {
                    break;
                }
            }
            transform_int_to_char_f(code.vars.var[index_var].value, value_string);

            strcpy(aux, expresie + i);
            strcpy(expresie + i, value_string);
            strcpy(expresie + i + strlen(value_string), aux);

        }
    }

}

bool is_while_f(LogicBlock *first)
{
    first = first->tru;

    while(first != NULL)
    {
        if(first->typeId < 0)     ///daca regasesc valoarea negativa atribuita in typeId, inseamna ca este structura repetitiva
        {
            return true;
        }
        if(first->typeId == DECISION_BLOCK)
        {
            first = first->tru;
        }
        else
        {
            first = first->next;
        }
    }
    return false;
}

int number_of_block_where_IFblock_stop(LogicBlock *step_r, LogicBlock *step_l)
{
    LogicBlock *first_r = step_r;

    while(first_r != NULL)  ///parcurg blocurile din partea dreapta a decision.ului pentru a pune -1 peste tot
    {
        first_r->typeId *= (-1);

        if(first_r->typeId == (-1) * DECISION_BLOCK)
            first_r = first_r->fls;
        else
            first_r = first_r->next;
    }


    int cnt = 0;
    while(step_l != NULL) ///parcurg blocurile din partea stanga a decisionului pentru a pune -1 peste tot
    {
        cnt++;
        step_l->typeId *= (-1);
        if(step_l->typeId > 0)  /// cand gasesc valoare pozitiva, gasesc intersectia celor doua ramuri, adica finalul if.ului
        {
            return cnt-1;
        }
        if(step_l->typeId == (-1) * DECISION_BLOCK)
            step_l = step_l->fls;
        else
            step_l = step_l->next;
    }
    return cnt;

}

void golire_valori_negative(LogicBlock *step)
{
    if(step->typeId < 0)
        step->typeId *= (-1);
    if(step->typeId == DECISION_BLOCK)
    {
        golire_valori_negative(step->tru);
        golire_valori_negative(step->fls);
    }
    else
    {
        if(step->next != NULL)
            golire_valori_negative(step->next);
    }
}

void implementare_tab_f(char code_text[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE], int number_of_tabs, int code_line_size)
{
    for(int i = 0; i < number_of_tabs; i++)
    {
        strcat(code_text[code_line_size], "\t");
    }

}

void golire_code_text_f(char code_text[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE])
{
    for(int i = 1; strlen(code_text[i]) != 0; i++)
    {
        strcpy(code_text[i], "");
    }
}

void eliminare_spatii_expresie(char expresie[])
{
    for(int i=0; i < strlen(expresie); i++)
    {
        if(expresie[i] == ' ')
        {
            strcpy(expresie + i, expresie + i + 1);
        }
    }
}

void expresie_postfixata_f(char expresie[], Sir_postfixat postfixat[], int &j)
{
    int i;

    Nod *stiva = new Nod;
    stiva = NULL;

    eliminare_spatii_expresie(expresie);

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
                    postfixat[j].nume[1] = 0;
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
                    postfixat[j].nume[1] = 0;
                    j++;
                    pop_f(stiva);
                }
                push_f(stiva, expresie[i]);
            }
        }

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

    int n = 0, i, ok = 0;

    Sir_postfixat postfixat[VAR_EXPRESSION_SIZE];

    replace_variable_name_with_value_f(expresie);    ///inlocuieste denumirea variabilelor cu valoarea lor

    for(int i = 0; i < strlen(expresie); i++)
    {
        if(strchr("+-*/", expresie[i]))
        {
            ok = 1;
            break;
        }
    }

    if(!ok)
    {
        return transform_char_to_int_f(expresie);
    }


    expresie_postfixata_f(expresie, postfixat, n);   ///formez expresia postfixata ce va contine n 'elemente'

    ///#########################################
    ///####CALCULAREA EXPRESIEI POSTFIXATA######
    ///#########################################


    Nod_postfixat *stiva = new Nod_postfixat;

    int valoare = 0;
    for(i = 0; i < n; i++)
    {
        if(strchr("0123456789", postfixat[i].nume[0])!=0)
        {
            push_int_f(stiva, transform_char_to_int_f(postfixat[i].nume));
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

bool valoare_adevar_expresie(char expresie[])
{
    char stanga[VAR_EXPRESSION_SIZE] = "", dreapta[VAR_EXPRESSION_SIZE] = "";
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

void parcurgere_lista_blocuri(LogicBlock *step, char code_text[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE], int &code_line_size, int &number_of_tabs, int number_of_IFdecisions_accesed, int number_of_blocks_inside_IFdecision)
{
    while(step != NULL)
    {
        switch(step->typeId)
        {
            case -5:
                number_of_IFdecisions_accesed = 1;
                number_of_blocks_inside_IFdecision = 1;
                step->typeId *= (-1);
                break;

            case INPUT_BLOCK:
                code_line_size++;
                implementare_tab_f(code_text, number_of_tabs, code_line_size);
                strcat(code_text[code_line_size], "cin >> ");
                strcat(code_text[code_line_size], code.vars.var[step->varId].name);
                strcat(code_text[code_line_size], ";");
                step = step->next;
                break;

            case OUTPUT_BLOCK:
                code_line_size++;
                implementare_tab_f(code_text, number_of_tabs, code_line_size);
                strcat(code_text[code_line_size], "cout << ");
                strcat(code_text[code_line_size], code.vars.var[step->varId].name);
                strcat(code_text[code_line_size], " << \"\\n\"");
                strcat(code_text[code_line_size], ";");
                step = step->next;
                break;

            case ASSIGN_BLOCK:
                code_line_size++;
                implementare_tab_f(code_text, number_of_tabs, code_line_size);
                strcat(code_text[code_line_size], code.vars.var[step->varId].name);
                strcat(code_text[code_line_size], " = ");
                strcat(code_text[code_line_size], step->varFullExpression);
                strcat(code_text[code_line_size], ";");
                step = step->next;
                break;

            case DECISION_BLOCK:
                code_line_size++;
                step->typeId *= (-1);
                implementare_tab_f(code_text, number_of_tabs, code_line_size);

                if(is_while_f(step))
                {
                    strcat(code_text[code_line_size], "while(");
                }
                else
                {
                    strcat(code_text[code_line_size], "if(");
                }

                strcat(code_text[code_line_size], step->varFullExpression);
                strcat(code_text[code_line_size], ")");

                code_line_size++;
                implementare_tab_f(code_text, number_of_tabs, code_line_size);
                strcat(code_text[code_line_size], "{");
                number_of_tabs++;

                if(is_while_f(step))
                {
                    parcurgere_lista_blocuri(step->tru, code_text, code_line_size, number_of_tabs, number_of_IFdecisions_accesed, number_of_blocks_inside_IFdecision);
                    step = step->fls;
                    number_of_tabs--;
                    code_line_size++;
                    implementare_tab_f(code_text, number_of_tabs, code_line_size);
                    strcat(code_text[code_line_size], "}");
                }
                else
                {
                    number_of_IFdecisions_accesed++;
                    number_of_blocks_inside_IFdecision = number_of_block_where_IFblock_stop(step->fls, step->tru);
                    golire_valori_negative(step);
                    parcurgere_lista_blocuri(step->tru, code_text, code_line_size, number_of_tabs, number_of_IFdecisions_accesed, number_of_blocks_inside_IFdecision);

                    number_of_IFdecisions_accesed--;
                    number_of_blocks_inside_IFdecision = 0;
                    number_of_tabs--;
                    code_line_size++;
                    implementare_tab_f(code_text, number_of_tabs, code_line_size);
                    strcat(code_text[code_line_size], "}");

                    number_of_blocks_inside_IFdecision = number_of_block_where_IFblock_stop(step->tru, step->fls);
                    int aux = number_of_blocks_inside_IFdecision; ///copie pe numarul de blocuri al ramurei else
                    golire_valori_negative(step);

                    if(number_of_blocks_inside_IFdecision) ///daca ramura else exista
                    {
                        number_of_IFdecisions_accesed++;
                        code_line_size++;
                        implementare_tab_f(code_text, number_of_tabs, code_line_size);
                        strcat(code_text[code_line_size], "else");

                        code_line_size++;
                        implementare_tab_f(code_text, number_of_tabs, code_line_size);
                        strcat(code_text[code_line_size], "{");
                        number_of_tabs++;
                        parcurgere_lista_blocuri(step->fls, code_text, code_line_size, number_of_tabs, number_of_IFdecisions_accesed, number_of_blocks_inside_IFdecision);

                        number_of_IFdecisions_accesed--;
                        number_of_blocks_inside_IFdecision = 0;
                        number_of_tabs--;
                        code_line_size++;
                        implementare_tab_f(code_text, number_of_tabs, code_line_size);
                        strcat(code_text[code_line_size], "}");
                    }

                    if(aux) ///daca else.ul exista
                    {
                        while(aux)
                        {
                            if(step->typeId == DECISION_BLOCK)
                                step = step->fls;
                            else                    ///parcurg fls sau parcurg next pana epuizez numarul de blocuri din block.ul else
                                step = step->next;
                            aux--;
                        }
                        step = step->next; ///trec la urmatorul bloc
                    }
                    else
                    {
                        step = step->fls; ///daca block.ul else nu contine nimic, trec direct la urmatorul block cu ajutorul fls.ului
                    }

                }
                break;

            case STOP_BLOCK:
                strcpy(code_text[++code_line_size], "\treturn 0;");
                strcpy(code_text[++code_line_size], "}");
                step = step->next;
                break;

            default:
                step = step->next;
                break;
        }
        if(number_of_IFdecisions_accesed)
        {
            number_of_blocks_inside_IFdecision--;
            if(!number_of_blocks_inside_IFdecision)
                break;
        }
    }
}

void output_code(LogicBlock *first_block, char code_text[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE], int &code_line_size)
{

    golire_code_text_f(code_text);

    int number_of_tabs = 0;
    code_line_size = 0;

    strcpy(code_text[++code_line_size],"#include <iostream>");
    strcpy(code_text[++code_line_size],"#include <math.h>");
    strcpy(code_text[++code_line_size],"using namespace std;");
    strcpy(code_text[++code_line_size],"int main()");
    strcpy(code_text[++code_line_size],"{");
    strcpy(code_text[++code_line_size],"\tint ");

    for(int i = 1; i <= code.vars.varsNumber; i++)
    {
        strcat(code_text[code_line_size], " ");
        strcat(code_text[code_line_size], code.vars.var[i].name);
        strcat(code_text[code_line_size], ",");
    }
    code_text[code_line_size][strlen(code_text[code_line_size]) - 1] = ';';;

    /*
    EMPTY_BLOCK 0
    START_BLOCK 1
    INPUT_BLOCK 2  ///  cin >> n
    OUTPUT_BLOCK 3 ///  cout << n;
    ASSIGN_BLOCK 4  ///  n = 3 + 3
    DECISION_BLOCK 5 ///  if else
    STOP_BLOCK 6   ///  return
    */

    LogicBlock *step = first_block;

    number_of_tabs++;
    parcurgere_lista_blocuri(step, code_text, code_line_size, number_of_tabs, 0 , 0);

}

void run_code(LogicBlock *first_block, char out_text[MAX_NUMBER_OF_CODE_LINE][MAX_LINE_OF_CODE_SIZE], int &code_line_size)
{
    char copie[MAX_LINE_OF_CODE_SIZE];
    LogicBlock *step = first_block;
    golire_code_text_f(out_text);
    code_line_size = 0;
    while(step != NULL)
    {
        switch(step->typeId)
        {
            case INPUT_BLOCK:
                strcpy(copie, step->varFullExpression);
                code.vars.var[step->varId].value = calcul_expresie_f(step->varFullExpression);
                strcpy(step->varFullExpression, copie);
                step = step->next;
                break;

            case OUTPUT_BLOCK:
                code_line_size++;
                char value_char[MAX_VALUE_LENGTH];
                transform_int_to_char_f(code.vars.var[step->varId].value, value_char);
                strcpy(out_text[code_line_size], value_char);
                step = step->next;
                break;

            case ASSIGN_BLOCK:
                strcpy(copie, step->varFullExpression);
                code.vars.var[step->varId].value = calcul_expresie_f(step->varFullExpression);
                strcpy(step->varFullExpression, copie);
                step = step->next;
                break;

            case DECISION_BLOCK:
                if(valoare_adevar_expresie(step->varFullExpression))
                {
                    step = step->tru;
                }
                else
                {
                    step = step->fls;
                }
                break;

            case STOP_BLOCK:
                step = step->next;
                break;

            default:
                step = step->next;
                break;
        }
    }
}

int file_count()
{
    int filecount = 0;
    while(1)
    {
        stringstream filename;
        filename << "./saves/interschem_" << setw(4) << setfill('0') << filecount << ".dat";
        ifstream in_b(filename.str(), ios::binary);
        if(!in_b)
        {
            break;
        }
        filecount++;
    }
    return filecount;
}

int search_block_in_allBlocks(LogicBlock *cautat)
{
    for(int i = 1; i <= code.numberOfBlocks; i++)
    {
        if(code.allBlocks[i] == cautat)
        {
            return i;
        }
    }
    return NULL;
}

int cout_to_binary_file()
{
    int filecount = file_count();

    stringstream filename;
    filename << "./saves/interschem_" << setw(4) << setfill('0') << filecount << ".dat";
    ofstream out_b(filename.str(), ios::binary);
    if(!out_b)
    {
        cout << "Cannot open file!" << endl;
        return 0;
    }

    out_b.write((char *) &code.vars.varsNumber, sizeof(int));
    out_b.write((char *) &code.numberOfBlocks, sizeof(int));

    for(int i = 1; i <= code.vars.varsNumber; i++)
    {
        out_b.write((char *) &code.vars.var[i], sizeof(Variable));
    }

    for(int i = 1; i <= code.numberOfBlocks; i++)
    {
        ///out_b.write((char *) &code.allBlocks[i], sizeof(LogicBlock));

        out_b.write((char *) &code.allBlocks[i]->block, sizeof(sf::RectangleShape));
        out_b.write((char *) &code.allBlocks[i]->blockTitle, sizeof(sf::Text));
        out_b.write((char *) &code.allBlocks[i]->blockExpression, sizeof(sf::Text));
        out_b.write((char *) &code.allBlocks[i]->blockPos, sizeof(sf::Vector2f));
        out_b.write((char *) &code.allBlocks[i]->typeId, sizeof(int));
        out_b.write((char *) &code.allBlocks[i]->varId, sizeof(int));
        out_b.write((char *) &code.allBlocks[i]->varFullExpression, sizeof(char));
        out_b.write((char *) &code.allBlocks[i]->connectionPath.hasConnection, sizeof(bool));
        out_b.write((char *) &code.allBlocks[i]->connectionPath.numberOfLinesNext, sizeof(int));
        for(int j = 1; j <= code.allBlocks[i]->connectionPath.numberOfLinesNext; j++)
        {
            out_b.write((char *) &code.allBlocks[i]->connectionPath.nextPath[j][0], sizeof(sf::Vertex));
            out_b.write((char *) &code.allBlocks[i]->connectionPath.nextPath[j][1], sizeof(sf::Vertex));
        }

        out_b.write((char *) &code.allBlocks[i]->connectionPath.numberOfLinesTru, sizeof(int));
        for(int j = 1; j <= code.allBlocks[i]->connectionPath.numberOfLinesTru; j++)
        {
            out_b.write((char *) &code.allBlocks[i]->connectionPath.truPath[j][0], sizeof(sf::Vertex));
            out_b.write((char *) &code.allBlocks[i]->connectionPath.truPath[j][1], sizeof(sf::Vertex));
        }

        out_b.write((char *) &code.allBlocks[i]->connectionPath.numberOfLinesFls, sizeof(int));
        for(int j = 1; j <= code.allBlocks[i]->connectionPath.numberOfLinesFls; j++)
        {
            out_b.write((char *) &code.allBlocks[i]->connectionPath.flsPath[j][0], sizeof(sf::Vertex));
            out_b.write((char *) &code.allBlocks[i]->connectionPath.flsPath[j][1], sizeof(sf::Vertex));
        }
        out_b.write((char *) &code.allBlocks[i]->numberOfPrevs, sizeof(int));
        for(int j = 1; j <= code.allBlocks[i]->numberOfPrevs; j++)
        {
            int indice = search_block_in_allBlocks(code.allBlocks[i]->prev[j]);
            out_b.write((char *) &indice, sizeof(int));
        }
        int indice = search_block_in_allBlocks(code.allBlocks[i]->next);
        out_b.write((char *) &indice, sizeof(int));
        indice = search_block_in_allBlocks(code.allBlocks[i]->tru);
        out_b.write((char *) &indice, sizeof(int));
        indice = search_block_in_allBlocks(code.allBlocks[i]->fls);
        out_b.write((char *) &indice, sizeof(int));
    }
    out_b.close();
    return 1;
}

int cin_from_binary_file(char file_name[])
{
    stringstream filename;
    filename << "./saves/" << file_name << ".dat";
    ifstream in_b(filename.str(), ios::binary);
    if(!in_b)
    {
        cout << "Cannot open file!" << endl;
        return 0;
    }
    in_b.read((char *) &code.vars.varsNumber, sizeof(int));
    in_b.read((char *) &code.numberOfBlocks, sizeof(int));

    for(int i = 1; i <= code.vars.varsNumber; i++)
    {
        in_b.read((char *) &code.vars.var[i], sizeof(Variable));
    }

    for(int i = 1; i <= code.numberOfBlocks; i++)
    {
        in_b.read((char *) &code.allBlocks[i]->block, sizeof(sf::RectangleShape));
        in_b.read((char *) &code.allBlocks[i]->blockTitle, sizeof(sf::Text));
        in_b.read((char *) &code.allBlocks[i]->blockExpression, sizeof(sf::Text));
        in_b.read((char *) &code.allBlocks[i]->blockPos, sizeof(sf::Vector2f));
        in_b.read((char *) &code.allBlocks[i]->typeId, sizeof(int));
        in_b.read((char *) &code.allBlocks[i]->varId, sizeof(int));
        in_b.read((char *) &code.allBlocks[i]->varFullExpression, sizeof(char));
        in_b.read((char *) &code.allBlocks[i]->connectionPath.hasConnection, sizeof(bool));

        in_b.read((char *) &code.allBlocks[i]->connectionPath.numberOfLinesNext, sizeof(int));
        for(int j = 1; j <= code.allBlocks[i]->connectionPath.numberOfLinesNext; j++)
        {
            in_b.read((char *) &code.allBlocks[i]->connectionPath.nextPath[j][0], sizeof(sf::Vertex));
            in_b.read((char *) &code.allBlocks[i]->connectionPath.nextPath[j][1], sizeof(sf::Vertex));
        }

        in_b.read((char *) &code.allBlocks[i]->connectionPath.numberOfLinesTru, sizeof(int));
        for(int j = 1; j <= code.allBlocks[i]->connectionPath.numberOfLinesTru; j++)
        {
            in_b.read((char *) &code.allBlocks[i]->connectionPath.truPath[j][0], sizeof(sf::Vertex));
            in_b.read((char *) &code.allBlocks[i]->connectionPath.truPath[j][1], sizeof(sf::Vertex));
        }

        in_b.read((char *) &code.allBlocks[i]->connectionPath.numberOfLinesFls, sizeof(int));
        for(int j = 1; j <= code.allBlocks[i]->connectionPath.numberOfLinesFls; j++)
        {
            in_b.read((char *) &code.allBlocks[i]->connectionPath.flsPath[j][0], sizeof(sf::Vertex));
            in_b.read((char *) &code.allBlocks[i]->connectionPath.flsPath[j][1], sizeof(sf::Vertex));
        }
        in_b.read((char *) &code.allBlocks[i]->numberOfPrevs, sizeof(int));
        for(int j = 1; j <= code.allBlocks[i]->numberOfPrevs; j++)
        {
            int indice;
            in_b.read((char *) &indice, sizeof(int));
            code.allBlocks[i]->prev[j] = code.allBlocks[indice];
        }
        int indice;
        in_b.read((char *) &indice, sizeof(int));
        code.allBlocks[i]->next = code.allBlocks[indice];
        in_b.read((char *) &indice, sizeof(int));
        code.allBlocks[i]->tru = code.allBlocks[indice];
        in_b.read((char *) &indice, sizeof(int));
        code.allBlocks[i]->fls = code.allBlocks[indice];

    }
    in_b.close();
    return 1;
}

