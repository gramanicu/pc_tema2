// Copyright 2018 Grama Nicolae

#include <stdio.h>
#include <string.h>

#define SIZE 31

typedef unsigned char matrice[SIZE][SIZE];


char verificaMini(matrice tabel, int x, int y) {
    char castigator=2;
    //verifica linii
    for(int i=x;i<=x+2;i++){
        if((tabel[i][y]==tabel[i][y+1]) && (tabel[i][y]==tabel[i][y+2])){
            castigator = tabel[i][y];
            return castigator;
        }
    }

    //verifica coloane
    for(int i=y;i<=y+2;i++){
        if((tabel[x][i]==tabel[x+1][i]) && (tabel[x][i]==tabel[x+2][i])){
            castigator = tabel[x][i];
            return castigator;
        }
    }


    //verifica diagonale
        if((tabel[x][y]==tabel[x+1][y+1]) && (tabel[x][y]==tabel[x+2][y+2])){
            castigator = tabel[x][y]; 
        } else {
            if((tabel[x][y+2]==tabel[x+1][y+1]) && (tabel[x][y+2]==tabel[x+2][y])){
                castigator = tabel[x][y]; 
                return castigator;
            }
        }

    return castigator;
}

void castigatorMini(matrice tabel, int X, int Y, int castigator) {
    if(tabel[30][X+Y/3]==2) tabel[30][X+Y/3] = castigator;
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

int plaseaza(matrice tabel, int x, int y, char simbol) {
    if (simbol == 'X') {
        tabel[x][y] = 1;
        castigatorMini(tabel, x-(x%3), y-(y%3), verificaMini(tabel, x-(x%3), y- (y%3)));
        return 1;
    } else {
        tabel[x][y] = 0;
        castigatorMini(tabel, x-(x%3), y-(y%3), verificaMini(tabel, x-(x%3), y- (y%3)));
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


void afisareMacro(matrice tabel, int n) {
    for(int i=0;i<n*3;i++) {
        if(tabel[30][i]==1) {
            printf("X");
        } else if(tabel[30][i]==0) {
            printf("0");
        } else {
            printf("-");
        }
        if(i%n == n-1) printf("\n");
    }
    printf("\n");
}

void afiseazaMacroVector(matrice tabel, int n) {
    for(int i=0; i<n*3;i++) {
        printf("%d ", tabel[30][i]);
    }
    printf("\n");
}

/*
Pentru a face verificarile corecte, trebuie luat in calcul si cazul 
matricei macro 1*1 sau 2*2.
De asemenea, codul trebuie evaluat pentru cazuri mai mari de 3*3, 
dar chiar si de 3*3.
In ultimul rand, codul de diag principala e gresit iar cel de diag secundara
nu exista
*/
char verificareMacro(matrice tabel, int n) {
    int cx=0, c0=0;

    // verificare verticala
    for(int i=0; i<n*3-3; i+=3) {
        if(tabel[30][i]==tabel[30][i+1] && tabel[30][i]==tabel[30][i+2]) {
            if(tabel[30][i]==1) cx++;
            else if(tabel[30][i]==0) c0++;
        }
    }

    // verificare orizontala

    for(int i=0; i<n; i++) {
        if(tabel[30][i]==tabel[30][i+3] && tabel[30][i]==tabel[30][i+6]) {
            if(tabel[30][i]==1) cx++;
            else if(tabel[30][i]==0) c0++;
        }
    }

    // verificare diagonala principala

     for(int i=0; i<n*3-3; i+=3) {
        if(tabel[30][i]==tabel[30][i+3] && tabel[30][i]==tabel[30][i+6]) {
            if(tabel[30][i]==1) cx++;
            else if(tabel[30][i]==0) c0++;
        }
    }

    if(cx>c0) return 1;
    else if(cx<c0) return 0;
    else return 2;
}

int main() {
    matrice tabel;
    int n;

    memset(tabel, 2, sizeof(tabel));

    scanf("%d", & n); // citeste dimensiunea tabelului
    citesteMutari(tabel, n);
    afisareMacro(tabel, n);

    afiseazaMacroVector(tabel, n);

    char castigator = verificareMacro(tabel,n);
    if(castigator==1) printf("X won\n");
    else if(castigator==0) printf("0 won\n");
    else printf("Draw again! Let’s play darts!\n");

    return 0;
}