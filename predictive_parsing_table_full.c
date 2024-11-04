#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void add_symbol(char *, char);
void FIND_FIRST(char *, char);
void FIND_FOLLOW(char *, char);
void FIRST_SHOW();
void FOLLOW_SHOW();
int CREATE_LL1_TABLE();
void PARSING_TABLE_SHOW(int);

int top = 0;
int t, nt, cr, count;
char FIRST[100][100], FOLLOW[100][100];
char T[100], NT[100], G[100][100], STACK[100];
int LL1[100][100];
void main() {
    int i, fl;
    char STR[100];
    printf("Krithika-predictive parser table");
    printf("Enter the number of production rules: ");
    scanf("%d", &cr);


    for (int k = 0; k < cr; k++) {
        printf("Enter production rule %d in the form A->B: ", k + 1);
        scanf("%s", G[k]);


        fl = 1;
        for (i = 0; i < nt && fl == 1; i++) {
            if (NT[i] == G[k][0]) {
                fl = 0;
            }
        }
        if (fl == 1) {
            NT[nt++] = G[k][0];
        }


        fl = 1;
        for (i = 3; G[k][i] != '\0'; i++) {
            if (!isupper(G[k][i]) && G[k][i] != '!') {
                for (int j = 0; j < t && fl == 1; j++) {
                    if (T[j] == G[k][i]) {
                        fl = 0;
                    }
                }
                if (fl == 1) {
                    T[t++] = G[k][i];
                }
                fl = 1;
            }
        }
    }

    FIRST_SHOW();
    FOLLOW_SHOW();

    T[t++] = '$';
    T[t] = '\0';

    int flag = CREATE_LL1_TABLE();
    PARSING_TABLE_SHOW(flag);
}

void FIRST_SHOW() {
    int i, j;
    char arr[100];
    for (i = 0; i < nt; i++) {
        arr[0] = '\0';
        FIND_FIRST(arr, NT[i]);
        for (j = 0; arr[j] != '\0'; j++) {
            FIRST[i][j] = arr[j];
        }
        FIRST[i][j] = '\0';
        count = 0;
    }
    printf("\nFIRST:\n\n");
    for (i = 0; i < nt; i++) {
        printf("FIRST(%c): { ", NT[i]);
        for (j = 0; FIRST[i][j + 1] != '\0'; j++) {
            printf(" %c,", FIRST[i][j]);
        }
        printf(" %c }\n", FIRST[i][j]);
    }
}

void FOLLOW_SHOW() {
    int i, j;
    char arr[100];
    for (i = 0; i < nt; i++) {
        count = 0;
        arr[0] = '\0';
        FIND_FOLLOW(arr, NT[i]);
        for (j = 0; arr[j] != '\0'; j++) {
            FOLLOW[i][j] = arr[j];
        }
        FOLLOW[i][j] = '\0';
    }
    printf("\nFOLLOW:\n\n");
    for (i = 0; i < nt; i++) {
        printf("FOLLOW(%c): { ", NT[i]);
        for (j = 0; FOLLOW[i][j + 1] != '\0'; j++) {
            printf(" %c,", FOLLOW[i][j]);
        }
        printf(" %c }\n", FOLLOW[i][j]);
    }
}

void FIND_FIRST(char *arr, char ch) {
    int i;
    if (!isupper(ch))
        add_symbol(arr, ch);
    else {
        for (i = 0; i < cr; i++) {
            if (ch == G[i][0]) {
                if (G[i][3] == '!')
                    add_symbol(arr, G[i][3]);
                else
                    FIND_FIRST(arr, G[i][3]);
            }
        }
    }
}

void FIND_FOLLOW(char arr[], char ch) {
    int i, j, k, l, fl = 1, flag = 1;
    if (ch == G[0][0])
        add_symbol(arr, '$');
    for (i = 0; i < cr; i++) {
        for (j = 3; G[i][j] != '\0' && flag == 1; j++) {
            if (ch == G[i][j]) {
                flag = 0;
                if (G[i][j + 1] != '\0' && isupper(G[i][j + 1])) {
                    for (k = 0; k < nt; k++) {
                        if (NT[k] == G[i][j + 1]) {
                            for (l = 0; FIRST[k][l] != '\0'; l++) {
                                if (FIRST[k][l] != '\0' && FIRST[k][l] != '!') {
                                    add_symbol(arr, FIRST[k][l]);
                                }
                                if (FIRST[k][l] == '!')
                                    fl = 0;
                            }
                            break;
                        }
                    }
                } else if (G[i][j + 1] != '\0' && !isupper(G[i][j + 1])) {
                    add_symbol(arr, G[i][j + 1]);
                }
                if ((G[i][j + 1] == '\0' || fl == 0) && G[i][0] != ch) {
                    fl = 1;
                    FIND_FOLLOW(arr, G[i][0]);
                }
            }
        }
    }
}

void add_symbol(char *arr, char ch) {
    int i, flag = 0;
    for (i = 0; arr[i] != '\0'; i++) {
        if (ch == arr[i]) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        arr[count++] = ch;
        arr[count] = '\0';
    }
}

int CREATE_LL1_TABLE() {
    int i, j, k, fl, pos, flag = 0;
    char arr[100];
    for (i = 0; i < cr; i++) {
        arr[0] = '\0';
        count = 0;
        FIND_FIRST(arr, G[i][3]);
        for (j = 0; j < count; j++) {
            if (arr[j] == '!') {
                FIND_FOLLOW(arr, G[i][0]);
                break;
            }
        }
        for (k = 0; k < nt; k++) {
            if (NT[k] == G[i][0]) {
                pos = k;
                break;
            }
        }
        for (j = 0; j < count; j++) {
            if (arr[j] != '!') {
                for (k = 0; k < t; k++) {
                    if (arr[j] == T[k]) {
                        if (LL1[pos][k] > 0) {
                            printf("\n\nConflict occurs between %s and %s rules!", G[LL1[pos][k] - 1], G[i]);
                            printf("\nGiven grammar is not LL(1) grammar!\n");
                            flag = 1;
                            return flag;
                        } else
                            LL1[pos][k] = i + 1;
                        break;
                    }
                }
            }
        }
    }
    return flag;
}

void PARSING_TABLE_SHOW(int flag) {
    int i, j;
    if (flag == 0) {
        printf("\n\nPredictive Parsing Table:\n\n\t");
        for (j = 0; j < t; j++) {
            printf("\t%c\t", T[j]);
        }
        printf("\n--------------------------------------------------------------------------------------------------------------");
        printf("\n\n");
        for (i = 0; i < nt; i++) {
            printf("%c\t|\t", NT[i]);
            for (j = 0; j < t; j++) {
                if (LL1[i][j] != 0)
                    printf("%s\t\t", G[LL1[i][j] - 1]);
                else
                    printf("%c\t\t", '_');
            }
            printf("\n\n");
        }
    }
}
