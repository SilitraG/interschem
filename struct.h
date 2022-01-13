struct Nod   ///stiva pentru operanzi
{
    char inf;
    Nod *urm;
};

struct Nod_postfixat   ///stiva pentru operanzi
{
    int inf;
    Nod_postfixat *urm;
};

struct Sir_postfixat          ///sir de caractere pentru fiecare val din exprsie.
{
    char nume[200];     ///consideram ca o valoare poate avea cel putin o cifra
};
