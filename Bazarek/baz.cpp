#include <stdio.h>
#include <stdbool.h>

bool parzysta(long n) {
    if(n % 2) {
        return false;
    } else {
        return true;
    }
}

//funkcja zwraca wartości dodatnie dla nieujemnych danych
long dodaj(long minus, long plus) {
    if(minus == -1 || plus == -1) {
        return -1;
    } else {
        return plus - minus;
    }
}

int main() {
    long i = 0;
    long produkty = 0;
    long dni = 0;
    long long tmp = 0;
    long long tmp2 = 0;
    long pytanie = 0;
    long long odpowiedz = 0;

    (void)scanf("%ld", &produkty);

    long ceny[produkty];
    long long sumy_czesciowe[produkty];
    //największa liczba na lewo od punktu
    long najwieksza_nparz_l[produkty];
    long najwieksza_parz_l[produkty];
    //najmniejsza na prawo od ORAZ W punkcie
    long najmniejsza_nparz_p[produkty];
    long najmniejsza_parz_p[produkty];

    for(i = 0; i < produkty; ++i) {
        (void)scanf("%ld", &ceny[i]);
    }

    for(i = produkty-1; i >= 0; i--) {
        sumy_czesciowe[i] = tmp + ceny[i];
        tmp = sumy_czesciowe[i];
    }

    tmp = -1;
    for(i = 0; i < produkty; ++i) {
        najwieksza_nparz_l[i] = tmp;
        if(!parzysta(ceny[i])) {
            tmp = ceny[i];
        }
    }
    tmp = -1;
    for(i = 0; i < produkty; ++i) {
        najwieksza_parz_l[i] = tmp;
        if(parzysta(ceny[i])) {
            tmp = ceny[i];
        }
    }
    tmp = -1;
    for (i = produkty - 1; i >= 0; --i) {
        if (!parzysta(ceny[i])) {
            najmniejsza_nparz_p[i] = ceny[i];
            tmp = najmniejsza_nparz_p[i];
        }
        else {
            najmniejsza_nparz_p[i] = tmp;
        }
    }
    tmp = -1;
    for (i = produkty - 1; i >= 0; --i) {
        if (parzysta(ceny[i])) {
            najmniejsza_parz_p[i] = ceny[i];
            tmp = najmniejsza_parz_p[i];
        }
        else {
            najmniejsza_parz_p[i] = tmp;
        }
    }

    (void)scanf("%ld", &dni);
    for (i = 0; i < dni; ++i) {
        (void)scanf("%ld", &pytanie);
        if (pytanie > produkty) {
            odpowiedz = -1;
        }
        else {
            odpowiedz = sumy_czesciowe[produkty - pytanie];
            tmp = odpowiedz;
            if (tmp % 2 == 0) {
                tmp = dodaj(najwieksza_nparz_l[produkty - pytanie], najmniejsza_parz_p[produkty - pytanie]);
                tmp2 = dodaj(najwieksza_parz_l[produkty - pytanie], najmniejsza_nparz_p[produkty - pytanie]);
                //if (pytanie == 1 )
                if (tmp == -1 && tmp2 == -1) {
                    odpowiedz = -1;
                }
                else if (tmp == -1) {
                    odpowiedz -= tmp2;
                }
                else if (tmp2 == -1) {
                    odpowiedz -= tmp;
                    //tmp zakładamy dodatnie
                }
                else if (tmp2 > tmp) {
                    odpowiedz -= tmp;
                }
                else {
                    odpowiedz -= tmp2;
                }
            }
        }
        printf("%lld\n", odpowiedz);
    }
    return 0;
}