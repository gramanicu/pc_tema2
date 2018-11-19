// Copyright 2018 Grama Nicolae

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef char matrice[SIZE][SIZE];

// HEADERS

void afiseazaTabel(matrice tabel, int n);
int valabil(matrice tabel, int x, int y);
int coordonateValide(int n, int x, int y);
int cautaSpatiuLiber(matrice tabel, int n, int *col, int *line);
void citesteMutari(matrice tabel, int n);
void plaseaza(matrice tabel, int x, int y, char simbol);

// MAIN

int main() {
    matrice tabel;
    memset(tabel, 0, sizeof(tabel));

    int n;
    scanf("%d", &n);

    citesteMutari(tabel, n);
    afiseazaTabel(tabel, n * n);
    return 0;
}

// FUNCTIONS

void plaseaza(matrice tabel, int x, int y, char simbol) {
    tabel[x][y] = simbol;
}

// Functie care afiseaza o matrice de dimensiune n * n
// ATENTIE - nu afiseaza matricea mare ! ( pentru a afisa
// matricea mare, foloseste n*n la apelare )
void afiseazaTabel(matrice tabel, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%c ", tabel[i][j]);
        }
        printf("\n");
    }
}

// Verifica daca o casuta este libera si returneaza 1 in caz
// afirmativ, respectiv 0
int valabil(matrice tabel, int x, int y) { return (tabel[x][y] == 0) ? 1 : 0; }

/*  Valideaza coordonatele :
        1. Sunt mai mari sau egale cu 0
        2. Se incadreaza in limitele tabelului
    Daca toate conditiile sunt indeplinite,indentindent returneaza 1
    Daca nu sunt valide, afiseaza mesajul de eroare si returneaza 0
*/
int coordonateValide(int n, int x, int y) {
    if ((x < 0) || (y < 0) || (x >= n) || (y >= n)) {
        printf("INVALID INDEX\n");
        return 0;
    }
    return 1;
}

/*  Functie care cauta spatiu liber pe diagonale, in mod alternativ.
    Daca nu gaseste spatiu, inseamna ca matricea este ocupata total
    si jocul s-a terminat. In acest caz afiseaza mesajul de eroare si
    returneaza 0. Daca a gasit o casuta neocupata, modifica x si y
    si returneaza 1
*/
int cautaSpatiuLiber(matrice tabel, int n, int *line, int *col) {
    int sus = 0, jos = 0, turn = 0, x = 0, y = 0;
    do {
        if (turn == 0) {
            for (int i = 0; i < n - jos; i++) {
                if (valabil(tabel, jos + i, i)) {
                    x = i + jos;
                    y = i;
                    sus = 0;
                    jos = 0;
                    break;
                }
            }
            jos++;
            turn = 1;
        } else {
            for (int i = 0; i < n - sus; i++) {
                if (valabil(tabel, i, i + sus)) {
                    x = i;
                    y = i + sus;
                    sus = 0;
                    jos = 0;
                    break;
                }
            }
            sus++;
            turn = 0;
        }
    } while ((sus != n || jos != n) && x == 0 && y == 0);

    if (sus == n && jos == n) {
        printf("FULL BOARD\n");
        return 0;
    } else {
        *line = x;
        *col = y;
    }

    return 1;
}

/*  Functie de citire a mutarilor. Dupa ce face toate verificarile (inclusiv
   daca casuta e valida si sa caute un loc liber in caz negativ), efectueaza
   mutarea. Daca nu a gasit niciun loc liber, inseamna ca jocul s-a terminat
*/
void citesteMutari(matrice tabel, int n) {
    int m, i, x, y;
    char player, last = '0';

    scanf("%d", &m);  // Citeste  numarul de mutari
    for (i = 0; i < m; i++) {
        scanf(" %c", &player);
        scanf("%d", &x);
        scanf("%d", &y);

        if (player != last) {  // Verifica daca a facut mutarea cine era la rand
            last = player;
            if (coordonateValide(n * n, x, y)) {
                if (!valabil(tabel, x, y)) {
                    if (!cautaSpatiuLiber(tabel, n, &x, &y)) {
                        // Daca nu a gasit spatiu liber, inseamna ca jocul s-a
                        // terminat
                        break;  // Nu mai citeste alte mutari
                    }
                }
                plaseaza(tabel, x, y, player);
            }
        } else {
            printf("NOT YOUR TURN\n");
        }
    }
}
