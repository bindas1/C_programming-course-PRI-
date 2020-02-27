//  main.c
//  obrazxcode
//  Created by Bartłomiej Binda on 29/10/2018.
//  Copyright © 2018 Bartłomiej Binda. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 100

typedef struct obraz{
    int wysokosc;
    int szerokosc;
    int type;
    char nazwa[40];
    int szintensywnosc;
    int kolor_dom[3];
    float histogram[8];
}obraz;

const char *typyOb[] = {"B8", "B16", "B32", "C24", "C16"};
obraz tablica[SIZE];

int sprDost(int tab[], int size);
void dodObraz(obraz *ob);
void czytObraz(obraz ob);
void zmienParametr(obraz *ob);
void czysc ( void );
void kasObraz(int *tab, obraz *ob, int komorka);
void sortWys(obraz *tablica, int tab[], int size);
void sortSzer(obraz *tablica, int tab[], int size);
void sortWek(obraz *tablica, int tab[], int size);
void zmienTab(obraz *tablica, int tab[], int size);

int main()
{
    int tab[SIZE]={0};
    int komorka; // uzywana do sprawdzania ktora komorka jest wolna
    char option = ' ';
    while(option != 'q'){
        printf("Podaj zmienna: \n -'+': dodawanie obrazu do struktury\n -'-': kasowanie wskazanego obrazu przez uzytkownika\n");
        puts(" -'w': wyswietlanie wskazanego obrazu przez uzytkownika\n -'z': zmiana dowolnie wybranego parametru przez uzytkownika\n -'s': sortowanie wszystkich obrazow po danym kryterium\n -'q': Wyjscie z programu");
        option = getchar();
        fpurge(stdin);
        //czysc();
        switch(option){
            case '+':
                komorka = sprDost(tab, SIZE);
                if (komorka == -1)
                    puts("W tablicy nie ma miejsca na kolejny obraz! :(");
                else{
                    dodObraz(&tablica[komorka]);
                    tab[komorka] = 1;
                }
                fpurge(stdin);
                //czysc();
                break;
            case '-':
                puts( "Ktora obraz chcesz skasowac (podaj nr 1-100)" );
                scanf("%d", &komorka);
                kasObraz(tab, &tablica[komorka-1], komorka - 1);
                fpurge(stdin);
                //czysc()
                // ? czy musze kasowac czy moge przy wyswietlaniu po prostu pisac ze nie ma go w liscie
                break;
            case 'q':
                printf( "Milo bylo. \n" );
                break;
            case 'w':
                // wyswietlanie obrazow ? wszystkie czy jeden ?
                puts( "Ktory obraz chcesz odczytac (1-100)?" );
                scanf("%d", &komorka);
                if( 1 == tab[komorka-1] )
                    czytObraz(tablica[komorka-1]);
                else
                    printf( "Nie ma obrazu o tym numerze. Sprobuj wyswietlic inny numer nastepnym razem. :(\n" );
                // czysc();
                fpurge(stdin);
                break;
            case 's':
                puts( "Jak chcesz posortowac obrazy?\n -'w': wysokoscia (malejaco)\n -'s': szerokoscia (malejaco)\n -'k': wektorem koloru dominujacego (malejaco)" );
                char wyb = getchar();
                switch(wyb){
                    case 'w':
                        sortWys(tablica, tab, SIZE);
                        break;
                    case 's':
                        sortSzer(tablica, tab, SIZE);
                        break;
                    case 'k':
                        sortWek(tablica, tab, SIZE);
                        break;
                }
                //czysc()
                fpurge(stdin);
                // sortowanie
                break;
            case 'z':
                puts( "Ktory obraz chcesz zmienic (1-100)?" );
                scanf("%d", &komorka);
                fpurge(stdin);
                if(tab[komorka] == 0)
                    puts( "Nie ma obrazu o tym numerze. Sprobuj ponownie z innym." );
                else
                    zmienParametr(&tablica[komorka-1]);
                fpurge(stdin);
                //czysc();
                //zmiana dowolnego parametru
                break;
            default:
                // system("clear");
                puts( "Wybierz literke ktora zostala opisana w menu! " );
                break;
                
        }
    }
    
    
    return 0;
}

int sprDost(int tab[], int size){
    for( int i = 0; i < size; i++ ){
        if (tab[i] == 0)
            return i;
    }
    return -1;
}

void dodObraz(obraz *ob){
    //system("clear");
    int i;
    printf("Podaj wysokosc obrazu: ");
    scanf("%d", &ob->wysokosc);
    
    printf("Podaj szerokosc obrazu: ");
    scanf("%d", &ob->szerokosc);
    
    printf("Podaj typ obrazu: (0 -> B8, 1 -> B16, 2->B32, 3->C24, 4->C16: ");
    scanf("%d", &ob->type);
    
    printf("Podaj nazwe obrazu: ");
    scanf("%s", ob->nazwa);
    
    printf("Podaj srednia znormalizowana intensywnosc obrazu: ");
    scanf("%d", &ob->szintensywnosc);
    
    printf("Podaj kolor dominujacy obrazu: ");
    for( i = 0; i < 3; i++ )
        scanf("%d", &ob->kolor_dom[i]);
    /*
     printf("Podaj histogram znormalizowany obrazu: ");
     for( i = 0; i < 8; i++ )
     scanf("%f", &ob->histogram[i]);*/
    puts("");
    
}

void zmienParametr(obraz *ob){
    //system("clear");
    puts( "Wybierzesz co chcesz zmienic w obrazie: \n -'w': wysokosc\n -'s': szerokosc\n -'n': nazwe\n -'t': typ\n -'i': srednia znormalizowana intensywnosc" );
    puts(" -'d': kolor dominujacy\n -'h': histogram");
    char c = getchar();
    fpurge(stdin);
    //czysc();
    switch (c){
        case 'w':
            printf("Podaj nowa wysokosc obrazu: ");
            scanf("%d", &ob->wysokosc);
            break;
        case 's':
            printf("Podaj nowa szerokosc obrazu: ");
            scanf("%d", &ob->szerokosc);
            break;
        case 'n':
            printf("Podaj nowa nazwe obrazu: ");
            scanf("%s", ob->nazwa);
            break;
        case 't':
            printf("Podaj typ obrazu: (0 -> B8, 1 -> B16, 2->B32, 3->C24, 4->C16: ");
            scanf("%d", &ob->type);
            break;
        case 'i':
            printf("Podaj srednia znormalizowana intensywnosc obrazu: ");
            scanf("%d", &ob->szintensywnosc);
            break;
        case 'd':
            printf("Podaj kolor dominujacy obrazu: ");
            for( int i = 0; i < 3; i++ )
                scanf("%d", &ob->kolor_dom[i]);
            break;
        case 'h':
            printf("Podaj histogram znormalizowany obrazu: ");
            for( int i = 0; i < 8; i++ )
                scanf("%f", &ob->histogram[i]);
            break;
        default:
            puts( "Wybierz literke ktora zostala opisana w menu! " );
            break;
    }
    puts("");
    fpurge(stdin);
    
}

void czytObraz(obraz ob){
    //system("clear");
    printf("Rozdzielczosc: %dx%d, \"%s\", Typ: %s, Srednia znormalizowana intensywnosc: %d, Kolor dominujacy: [", ob.wysokosc, ob.szerokosc, ob.nazwa, typyOb[ob.type], ob.szintensywnosc);
    /*for( int i = 0; i < 2; i++ )
     printf("%d, ", ob.kolor_dom[i]);
     printf("%d] Histogram znormalizowany: [", ob.kolor_dom[2]);
     for( int j = 0; j < 7; j++)
     printf("%.2f, ", ob.histogram[j]);
     printf("%.2f]\n", ob.histogram[7]);*/
    puts("");
    
}

void kasObraz(int *tab, obraz *ob, int komorka){
    int i;
    if(1 != tab[komorka])
        puts( "Nie ma obrazu o tym numerze!!! Sprobuj ponownie. " );
    else{
        tab[komorka] = 0;
        ob->wysokosc = 0;
        ob->szerokosc = 0;
        strcpy(ob->nazwa, "");
        ob->szintensywnosc = 0;
        for( i = 0; i < 3; i++ )
            ob->kolor_dom[i] = 0;
        for( i = 0; i < 8; i++ )
            ob->histogram[i] = 0;
    }
    
}

void sortWys(obraz *tablica, int tab[], int size){
    obraz pom;
    for( int i = 0; i<size; i++ ){
        for( int j = 0; j<size-1; j++ ){
            if ( tablica[j].wysokosc < tablica[j+1].wysokosc ){
                pom = tablica[j+1];
                tablica[j+1] = tablica[j];
                tablica[j] = pom;
            }
        }
    }
    zmienTab(tablica, tab, size);
}

void sortSzer(obraz *tablica, int tab[], int size){
    obraz pom;
    for( int i = 0; i<size; i++ ){
        for( int j = 0; j<size-1; j++ ){
            if ( tablica[j].szerokosc < tablica[j+1].szerokosc ){
                pom = tablica[j+1];
                tablica[j+1] = tablica[j];
                tablica[j] = pom;
            }
        }
    }
    zmienTab(tablica, tab, size);
}

void sortWek(obraz *tablica, int tab[], int size){
    obraz pom;
    for( int i = 0; i<size; i++ ){
        for( int j = 0; j<size-1; j++ ){
            if ( tablica[j].kolor_dom[0]*tablica[j].kolor_dom[0] + tablica[j].kolor_dom[1]*tablica[j].kolor_dom[1] + tablica[j].kolor_dom[2]*tablica[j].kolor_dom[2] < tablica[j+1].kolor_dom[0]*tablica[j+1].kolor_dom[0] + tablica[j+1].kolor_dom[1]*tablica[j+1].kolor_dom[1] + tablica[j+1].kolor_dom[2]*tablica[j+1].kolor_dom[2] ){
                pom = tablica[j+1];
                tablica[j+1] = tablica[j];
                tablica[j] = pom;
            }
        }
    }
    zmienTab(tablica, tab, size);
}

void czysc ( void ) {
    char c;
    do
        c = getchar();
    while ( c != '\n' && c != EOF );
}

void zmienTab(obraz *tablica, int tab[], int size){
    for( int i = 0; i<size; i++ ){
        if(tablica[i].wysokosc == 0 && tablica[i].szerokosc == 0)
            tab[i] = 0;
        else
            tab[i] = 1;
    }
}
