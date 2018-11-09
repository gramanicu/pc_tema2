// Copyright 2018 Grama Nicolae

#include <stdio.h>
#include <string.h>

#define SIZE 30

typedef unsigned char matrice[SIZE][SIZE];

int valabil(matrice tabel, int x, int y) {
    return (tabel[x][y] == 2) ? 1 : 0;
}

int coordonateValide(matrice tabel, int n, int x, int y) {
    if ((x >= n) || (y >= n)) {
        printf("INVALID INDEX\n");
        return 0;
    } else {
        if (valabil(tabel, x, y)) {
            return 1;
        } else {
            printf("NOT AN EMPTY CELL\n");
            return 0;
        }
    }
}

int plaseaza(matrice tabel, int x, int y, char simbol) {
    if (simbol == 'X') {
        tabel[x][y] = 1;
        return 1;
    } else {
        tabel[x][y] = 0;
        return 1;
    }
    return 0;
}

int cautaSpatiuLiber(matrice tabel, int n, char simbol) {
    int sus = 0, jos = 0, turn = 0, x = 0, y = 0;

    do {
        if (turn == 0) {
            for (int i = 0; i < n - jos; i++) {
                if (valabil(tabel, jos + i, i)) {
                    x = i + jos;
                    y = i;
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
                    break;
                }
            }
            sus++;
            turn = 0;
        }
    } while ((sus != 9 || jos != 9) && x == 0 && y == 0);

    if (sus == 9 && jos == 9) {
        printf("FULL BOARD\n");
        return 0;
    } else {
        plaseaza(tabel, x, y, simbol);
    }

    return 1;
}

void citesteMutari(matrice tabel, int n) {
    int m, i, x, y;
    char player, last = '0';

    scanf("%d", & m); // citeste  numarul de mutari
    for (i = 0; i < m; i++) {
        scanf(" %c", & player);
        scanf("%d", & x);
        scanf("%d", & y);
        if (player != last) {
            last = player;
            if (coordonateValide(tabel, n * 3, x, y)) {
                plaseaza(tabel, x, y, player);
            } else {
                if (!cautaSpatiuLiber(tabel, n * 3, player)) {
                    break;
                }
            }
        } else {
            printf("NOT YOUR TURN\n");
            i--;
        }
    }
}

void afiseazaTabel(matrice tabel, int n) {
    int i, j;
    for (i = 0; i < n * 3; i++) {
        for (j = 0; j < n * 3; j++) {
            printf("%d ", tabel[i][j]);
        }
        printf("\n");
    }
}

int main() {
    matrice tabel;
    int n;

    memset(tabel, 2, sizeof(tabel));

    scanf("%d", & n); // citeste dimensiunea tabelului
    citesteMutari(tabel, n);
    afiseazaTabel(tabel, n);

    return 0;
}