#include <stdio.h>
#include <string.h>
#include <ctype.h>

int np;
char mat[10][10];
char first[10][10];
char follow[10][10];
char symbols[20];
int symbol_count = 0;

void find_first(int i, int j) {
    char symbol = mat[i][j];

    if (symbol == '!') {
        if (!strchr(first[mat[i][0]], '!')) {
            strncat(first[mat[i][0]], "!", 1);
        }
    } else if (!isupper(symbol)) {
        if (!strchr(first[mat[i][0]], symbol)) {
            strncat(first[mat[i][0]], &symbol, 1);
        }
    } else {
        for (int prod = 0; prod < np; prod++) {
            if (mat[prod][0] == symbol) {
                if (!isupper(mat[prod][1])) {
                    if (!strchr(first[mat[i][0]], mat[prod][1])) {
                        strncat(first[mat[i][0]], &mat[prod][1], 1);
                    }
                } else {
                    find_first(prod, 1);
                    for (int x = 0; first[mat[prod][1]][x] != '\0'; x++) {
                        if (!strchr(first[mat[i][0]], first[mat[prod][1]][x])) {
                            strncat(first[mat[i][0]], &first[mat[prod][1]][x], 1);
                        }
                    }
                }
            }
        }
    }
}

void find_follow(char c) {
    for (int i = 0; i < np; i++) {
        for (int j = 1; mat[i][j] != '#' && mat[i][j] != '\0'; j++) {
            if (mat[i][j] == c) {
                if (mat[i][j + 1] != '#' && mat[i][j + 1] != '\0') {
                    if (!isupper(mat[i][j + 1])) {
                        if (!strchr(follow[c], mat[i][j + 1])) {
                            strncat(follow[c], &mat[i][j + 1], 1);
                        }
                    } else {
                        for (int x = 0; first[mat[i][j + 1]][x] != '\0'; x++) {
                            if (!strchr(follow[c], first[mat[i][j + 1]][x]) && first[mat[i][j + 1]][x] != '!') {
                                strncat(follow[c], &first[mat[i][j + 1]][x], 1);
                            }
                        }
                        if (strchr(first[mat[i][j + 1]], '!')) {
                            if (mat[i][j + 2] == '\0' || mat[i][j + 2] == '#') {
                                find_follow(mat[i][0]);
                                for (int x = 0; follow[mat[i][0]][x] != '\0'; x++) {
                                    if (!strchr(follow[c], follow[mat[i][0]][x])) {
                                        strncat(follow[c], &follow[mat[i][0]][x], 1);
                                    }
                                }
                            }
                        }
                    }
                }
                if (mat[i][j + 1] == '#' || mat[i][j + 1] == '\0') {
                    if (mat[i][0] != c) {
                        for (int x = 0; follow[mat[i][0]][x] != '\0'; x++) {
                            if (!strchr(follow[c], follow[mat[i][0]][x])) {
                                strncat(follow[c], &follow[mat[i][0]][x], 1);
                            }
                        }
                    }
                }
            }
        }
    }
}

int is_symbol_present(char c) {
    for (int i = 0; i < symbol_count; i++) {
        if (symbols[i] == c) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char production[20], lhs, start_symbol;

    printf("Enter the number of productions: ");
    scanf("%d", &np);

    for (int i = 0; i < np; i++) {
        printf("Production %d: ", i + 1);
        scanf("%s", production);

        lhs = production[0];
        mat[i][0] = lhs;

        if (!is_symbol_present(lhs)) {
            symbols[symbol_count++] = lhs;
        }

        start_symbol = mat[0][0];

        for (int j = 3, k = 1; production[j] != '\0'; j++, k++) {
            mat[i][k] = production[j];
            if (!is_symbol_present(production[j])) {
                symbols[symbol_count++] = production[j];
            }
        }
        mat[i][strlen(production) - 3 + 1] = '#';
    }

    follow[start_symbol][0] = '$';

    for (int i = 0; i < np; i++) {
        find_first(i, 0);
    }

    for (int i = 0; i < np; i++) {
        find_follow(mat[i][0]);
    }

    printf("\nProductions\n");
    for (int i = 0; i < np; i++) {
        printf("\n%c -> ", mat[i][0]);
        for (int j = 1; mat[i][j] != '#' && mat[i][j] != '\0'; j++) {
            printf("%c ", mat[i][j]);
        }
    }

    printf("\n\nFirst Of: \n");
    for (int i = 0; i < np; i++) {
        printf("\n%c = { ", mat[i][0]);
        for (int j = 0; first[mat[i][0]][j] != '\0'; j++) {
            printf("%c ", first[mat[i][0]][j]);
        }
        printf("}");
    }
    for (int i = 0; i < symbol_count; i++) {
        if (!isupper(symbols[i])) {
            printf("\n%c = { %c }", symbols[i], symbols[i]);
        }
    }

    printf("\n\nFollow Of: \n");
    for (int i = 0; i < np; i++) {
        printf("\n%c = { ", mat[i][0]);
        for (int j = 0; follow[mat[i][0]][j] != '\0'; j++) {
            printf("%c ", follow[mat[i][0]][j]);
        }
        printf("}");
    }

    printf("\n\nTotal unique symbols: %d\n", symbol_count);
    printf("Symbols: { ");
    for (int i = 0; i < symbol_count; i++) {
        printf("%c ", symbols[i]);
    }
    printf("}\n");

    return 0;
}
