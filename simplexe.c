#include <stdio.h>
#define MAX_SLACK 10
#define MAX_VARS 10

struct simplexe {
    int m; //number of constraints
    int n; //number of variable (slack ones not included)
    double tableau[MAX_SLACK + 1][MAX_SLACK + MAX_VARS + 1]; // tableau including RHS and slack variables
};



void inputproblem(struct simplexe *s) {
    
    
    printf("Enter the number of constrains: ");
    scanf("%d", &s->m);
    
    printf("Enter the number of original variables: ");
    scanf("%d", &s->n);

    for (int i=0; i <= s->m; i++) //init the tab at 0 so when everything else is filled the one who don't are alr at 0
    {
        for (int j=0; j <= s->m + s->n ; j++) {
            s->tableau[i][j]=0;
        }
    }

    
    printf("Enter the coefficients of the target (equation economique): ");
    for (int i=0; i < s->n; i++) {
        scanf("%lf", &s->tableau[s->m][i]);
    }
    
    printf("Entrer the coefficients of the constraints(end with RHS): ");
    for (int i=0; i < s->m; i++)
    {
        printf("Constraint: %d", i+1);
        for (int j=0; j < s->n ; j++) {
            scanf("%lf", &s->tableau[i][j]);
        }
        scanf("%lf", &s->tableau[i][s->n + s->m]); // adding the RHS skiping to the last column of each row
    }
    
    for(int i=0; i<s->m; i++) {
        s->tableau[i][s->n + i] = 1.0; //adding the slack vars coeff
    }
}


void print_tableau(simplexe *s) {
    
}