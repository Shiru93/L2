#include <stdio.h>
#include <stdlib.h>
#include "chemin.h"

int chercher_chemin_rec(int** lab, int n, int lc, int cc) {
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int new_lc;
    int new_cc;

    if (lc == n-1 && cc == n-1) {
        lab[lc][cc] = 3;
        return 1;
    }
    
    lab[lc][cc] = 4;
    
    for (int d = 0; d < 4; d++) {
        new_lc = lc + directions[d][0];
        new_cc = cc + directions[d][1];
        
        if (new_lc >= 0 && new_lc < n && new_cc >= 0 && new_cc < n) {
            if (lab[new_lc][new_cc] == 0 || (new_lc == n-1 && new_cc == n-1)) {
                if (chercher_chemin_rec(lab, n, new_lc, new_cc)) {
                    if(new_lc > lc) lab[new_lc -1][new_cc] = 5;
                    if(new_lc < lc) lab[new_lc +1][new_cc] = 6;
                    if(new_cc > cc) lab[new_lc][new_cc -1] = 7;
                    if(new_cc < cc) lab[new_lc][new_cc +1] = 8;
                    return 1;
                }
            }
        }
    }
    
    lab[lc][cc] = 2;
    return 0;
}

int chercher_chemin(int **lab, int n) {
    if (lab[0][0] != 0) {
        return 0;
    }
    return chercher_chemin_rec(lab, n, 0, 0);
}