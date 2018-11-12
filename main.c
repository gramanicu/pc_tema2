// Copyright 2018 Grama Nicolae

#include <stdio.h>
#include <string.h>

#define SIZE 101

typedef unsigned char matrice[SIZE][SIZE];
typedef unsigned char vector[SIZE];

void afiseazaTabel(matrice tabel, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", tabel[i][j]);
        }
        printf("\n");
    }
}

void matriceToMini(matrice original, matrice m, int x, int y, int n) {
    int ox=0, oy=0;
    for (int i = x; i < x + n; i++) {
        for (int j = y; j < y + n; j++) {
            m[ox][oy] = original[i][j];
            oy++;
            if(oy==n) {
                oy=0;
                ox++;
            }
        }
    }
}

char verificaMini(matrice tabel, int x, int y, int n) {
    matrice mini;
    matriceToMini(tabel, mini, x, y, n);

    // verificare orizontala
    for (int i = 0; i < n; i++) {
        int count = 1;
        char c = mini[i][0];
        for (int j = 1; j < n; j++) {
            if (mini[i][j] == c) {
                count++;
            }
        }
        if (count == n) {
            return c;
        }
    }

    // verificare verticala
    for (int i = 0; i < n; i++) {
        int count = 1;
        char c = mini[0][i];
        for (int j = 1; j < n; j++) {
            if (mini[j][i] == c) {
                count++;
            }
        }
        if (count == n) {
            return c;
        }
    }

    // verificare diagonala principala

    int count = 1;
    char c = mini[0][0];
    for (int i = 1; i < n; i++) {
        if (mini[i][i] == c) count++;
    }
    if (count == n) {
        return c;
    }

    // verifica diagonala secundara
    count = 1;
    c = mini[0][n - 1];
    for (int i = 1; i < n; i++) {
        if (mini[i][n - i - 1] == c) {
            count++;
        }
    }
    if (count == n) {
        return c;
    }

    return 2;
}

// Functia care seteaza castigatorul unei matrici, in functie de coltul
// din stanga sus
void castigatorMini(matrice tabel, int X, int Y, int castigator, int n) {
    if(castigator!=2) {
        if (tabel[100][X + Y / n] == 2) tabel[100][X + Y / n] = castigator;
    }
}

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

int plaseaza(matrice tabel, int x, int y, char simbol, int n) {
    if (simbol == 'X') {
        tabel[x][y] = 1;
        castigatorMini(tabel, x - (x % n), y - (y % n), verificaMini(tabel, x - (x % n), y - (y % n), n), n);
        return 1;
    } else {
        tabel[x][y] = 0;
        castigatorMini(tabel, x - (x % n), y - (y % n), verificaMini(tabel, x - (x % n), y - (y % n), n), n);
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
        plaseaza(tabel, x, y, simbol, n);
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
            if (coordonateValide(tabel, n * n, x, y)) {
                plaseaza(tabel, x, y, player, n);
            } else {
                if (!cautaSpatiuLiber(tabel, n * n, player)) {
                    break;
                }
            }
        } else {
            printf("NOT YOUR TURN\n");
        }
    }
}

void afisareMacro(matrice tabel, int n) {
    for (int i = 0; i < n * n; i++) {
        if (tabel[100][i] == 1) {
            printf("X");
        } else if (tabel[100][i] == 0) {
            printf("0");
        } else {
            printf("-");
        }
        if (i % n == n - 1) printf("\n");
    }
    printf("\n");
}

void afiseazaMacroVector(matrice tabel, int n) {
    for (int i = 0; i < n * n; i++) {
        printf("%d ", tabel[100][i]);
    }
    printf("\n");
}

void vectorToMatrice(vector v, matrice m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = v[i * n + j];
        }
    }
}

char verificareMacro(matrice tabel, int n) {
    int cx = 0, c0 = 0;
    matrice macro;
    vectorToMatrice(tabel[100], macro, n);
    // verificare orizontala
    for (int i = 0; i < n; i++) {
        int count = 1;
        char c = macro[i][0];
        for (int j = 1; j < n; j++) {
            if (macro[i][j] == c) {
                count++;
            }
        }
        if (count == n) {
            if (macro[i][0] == 1) {
                cx++;
            } else if (macro[i][0] == 0) {
                c0++;
            }
        }
    }

    // verificare verticala
    for (int i = 0; i < n; i++) {
        int count = 1;
        char c = macro[0][i];
        for (int j = 1; j < n; j++) {
            if (macro[j][i] == c) {
                count++;
            }
        }
        if (count == n) {
            if (macro[0][i] == 1) {
                cx++;
            } else if (macro[0][i] == 0) {
                c0++;
            }
        }
    }

    // verificare diagonala principala

    int count = 1;
    char c = macro[0][0];
    for (int i = 1; i < n; i++) {
        if (macro[i][i] == c) count++;
    }
    if (count == n) {
        if (macro[0][0] == 1) {
            cx++;
        } else if (macro[0][0] == 0) {
            c0++;
        }
    }

    // verifica diagonala secundara
    count = 1;
    c = macro[0][n - 1];
    for (int i = 1; i < n; i++) {
        if (macro[i][n - i - 1] == c) {
            count++;
        }
    }
    if (count == n) {
        if (macro[0][n - 1] == 1) {
            cx++;
        } else if (macro[0][n - 1] == 0) {
            c0++;
        }
    }

    if (cx > c0) {
        return 1;
    } else if (cx < c0) {
        return 0;
    } else {
        return 2;
    }
}

int main() {
    matrice tabel;
    int n;

    memset(tabel, 2, sizeof(tabel));

    scanf("%d", & n); // citeste dimensiunea tabelului
    citesteMutari(tabel, n);
    afisareMacro(tabel, n);
    char castigator = verificareMacro(tabel, n);
    if (castigator == 1)
        printf("X won\n");
    else if (castigator == 0)
        printf("0 won\n");
    else
        printf("Draw again! Let’s play darts!\n");

    return 0;
}