// Copyright 2018 Grama Nicolae

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef char matrice[SIZE][SIZE];

// HEADERS

void afiseazaTabel(matrice tabel, int n);
void plaseaza(matrice tabel, int x, int y, char simbol);
void transforma(matrice sursa, matrice target, int n, int x, int y);
int citesteMutari(matrice tabel, matrice macro, int n);
int valabil(matrice tabel, int x, int y);
int coordonateValide(int n, int x, int y);
int cautaSpatiuLiber(matrice tabel, int n, int *col, int *line);
int castigatoare(matrice tabel, matrice macro, int n, int x, int y);
int situatie(matrice mini, matrice macro, int n, int x, int y);

// MAIN

int main() {
    matrice tabel;
    matrice macro;
    memset(tabel, -1, sizeof(tabel));
    memset(macro, -1, sizeof(macro));

    int n;
    scanf("%d", &n);

    citesteMutari(tabel, macro, n);
    afiseazaTabel(macro, n);
    // afiseazaTabel(tabel, n * n);
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
            if (tabel[i][j] != -1) {
                printf("%c", tabel[i][j]);
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
}

/*  O functie folosita pentru a simplifica anumite calcule, mutand
    informatiile dintr-un minijoc din matricea mare intr-o matrice
    mai mica. Pentru a putea face acest transfer, are nevoie de
    coordonatele din coltul din stanga sus, al minijocului.
*/
void transforma(matrice sursa, matrice target, int n, int x, int y) {
    int linie = 0, col = 0;
    for (int i = x; i < n + x; i++) {
        for (int j = y; j < n + y; j++) {
            target[linie][col++] = sursa[i][j];
        }
        col = 0;
        linie++;
    }
}

/*  Intrucat se cauta coordonatele unui mini-tabel in tabelul
    mare, e nevoie sa scoatem radical din dimensiunea n, pentru
    a afla dimensiunea unui tabel mic (n-ul original, din input)
*/
void coordonateMini(int n, int *x, int *y) {
    *x = *x - (*x % n);
    *y = *y - (*y % n);
}

//  Functie care evalueaza situatia in tabelul mini
int situatie(matrice mini, matrice macro, int n, int x, int y) {
    // verificare orizontala
    for (int i = 0; i < n; i++) {
        int count = 1;
        char c = mini[i][0];
        if (c != -1) {
            for (int j = 1; j < n; j++) {
                if (mini[i][j] == c) {
                    count++;
                }
            }
            if (count == n) {
                return valabil(macro, x, y);
            }
        }
    }

    // verificare verticala
    for (int i = 0; i < n; i++) {
        int count = 1;
        char c = mini[0][i];
        if (c != -1) {
            for (int j = 1; j < n; j++) {
                if (mini[j][i] == c) {
                    count++;
                }
            }
            if (count == n) {
                return valabil(macro, x, y);
            }
        }
    }

    // verificare diagonala principala

    int count = 1;
    char c = mini[0][0];
    if (c != -1) {
        for (int i = 1; i < n; i++) {
            if (mini[i][i] == c) {
                count++;
            }
        }
        if (count == n) {
            return valabil(macro, x, y);
        }
    }

    // verifica diagonala secundara
    count = 1;
    c = mini[0][n - 1];
    if (c != -1) {
        for (int i = 1; i < n; i++) {
            if (mini[i][n - i - 1] == c) {
                count++;
            }
        }
        if (count == n) {
            return valabil(macro, x, y);
        }
    }

    return 0;
}

/*  Functie care verifica daca a fost castigat un joc mic
    (si daca mutarea a fost castigatoare). Daca gaseste
    un joc castigat, il updateaza in tabelul macro. Daca nu
    e nimic de updatat in macro, inseamna ca mutarea nu a fost
    castigatoare.
*/
int castigatoare(matrice tabel, matrice macro, int n, int x, int y) {
    matrice mini;
    int i = x;
    int j = y;
    coordonateMini(n, &i, &j);
    transforma(tabel, mini, n, i, j);
    i = i / n;
    j = j / n;
    return situatie(mini, macro, n, i, j);
}

// Verifica daca o casuta este libera si returneaza 1 in caz
// afirmativ, respectiv 0
int valabil(matrice tabel, int x, int y) { return (tabel[x][y] == -1) ? 1 : 0; }

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
    int sus = 1, jos = 0, turn = 0, x = -1, y = -1;
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
    } while ((sus != n || jos != n) && (x == -1 && y == -1));

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
int citesteMutari(matrice tabel, matrice macro, int n) {
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
                    printf("NOT AN EMPTY CELL\n");
                    if (!cautaSpatiuLiber(tabel, n * n, &x, &y)) {
                        return 0;  // Jocul s-a terminat
                    }
                }
            } else {
                if (!cautaSpatiuLiber(tabel, n * n, &x, &y)) {
                    return 0;  // La fel ca mai sus
                }
            }
            plaseaza(tabel, x, y, player);  // Efectueaza mutarea
            if (castigatoare(tabel, macro, n, x, y)) {
                coordonateMini(n, &x, &y);
                x = x / n;
                y = y / n;
                plaseaza(macro, x, y, player);
            }
        } else {
            printf("NOT YOUR TURN\n");
        }
    }
    return 0;  // Au fost citite toate mutarile - jocul e terminat
}
