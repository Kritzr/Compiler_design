#include <stdio.h>
#include <string.h>

char table[30][3][30]; // Symbol table

void AddToTable(char Str[], int count, const char *id, const char *symbol) {
    strcpy(table[count][0], Str);
    strcpy(table[count][1], id);
    strcpy(table[count][2], symbol);
}


int Number(char Str[]) {
    for (int i = 0; Str[i] != '\0'; i++) {
        if (Str[i] < '0' || Str[i] > '9') {
            return 1;
        }
    }
    return 2;
}


int CheckKeylist(char Str[]) {
    const char keylist[][30] = {
        "int", "float", "long", "double", "char", "if", "else", "while", "do",
        "for", "printf", "scanf", "main", "include", "void", "return"
    };
    for (int i = 0; i < 16; i++) {
        if (strcmp(Str, keylist[i]) == 0) {
            return 3;
        }
    }
    return 4;
}


int Checkoper(char Str[]) {
    const char oper[][3] = {"+", "-", "*", "/", "%", "^"};
    for (int i = 0; i < 6; i++) {
        if (strcmp(Str, oper[i]) == 0) {
            return 7;
        }
    }
    return 8;
}


int Checkincr(char Str[]) {
    const char incr[][3] = {"==", "++", "--"};
    for (int i = 0; i < 3; i++) {
        if (strcmp(Str, incr[i]) == 0) {
            return 5;
        }
    }
    return 6;
}


int CheckBracket(char Str[]) {
    const char bracket[][3] = {"(", ")", "{", "}", "[", "]"};
    for (int i = 0; i < 6; i++) {
        if (strcmp(Str, bracket[i]) == 0) {
            return 9;
        }
    }
    return 10;
}


int Checkrelation(char Str[]) {
    const char relations[][3] = {"<", ">", "="};
    for (int i = 0; i < 3; i++) {
        if (strcmp(Str, relations[i]) == 0) {
            return 11;
        }
    }
    return 12;
}


int Checkspl(char Str[]) {
    const char special[][2] = {"@", "#", "$", "&", ":", ";", ",", ".", "?"};
    for (int i = 0; i < 9; i++) {
        if (strcmp(Str, special[i]) == 0) {
            return 13;
        }
    }
    return 14;
}


void Tokenize(char input[], int *count) {
    char Str[30];
    int j = 0, i = 0;

    while (input[j] != '\0') {
        if (input[j] == ' ' || input[j] == '\t' || input[j] == '\n') {
            j++;
            continue;
        }


        if (input[j] == '+' || input[j] == '-' || input[j] == '*' || input[j] == '/' ||
            input[j] == '%' || input[j] == '^' || input[j] == '=' || input[j] == '<' ||
            input[j] == '>' || input[j] == '(' || input[j] == ')' || input[j] == '{' ||
            input[j] == '}' || input[j] == '[' || input[j] == ']' || input[j] == '@' ||
            input[j] == '#' || input[j] == '$' || input[j] == '&' || input[j] == ':' ||
            input[j] == ';' || input[j] == ',' || input[j] == '.' || input[j] == '?') {

            Str[0] = input[j];
            Str[1] = '\0';

            if ((input[j] == '+' && input[j + 1] == '+') || (input[j] == '-' && input[j + 1] == '-') ||
                (input[j] == '=' && input[j + 1] == '=')) {
                Str[1] = input[j + 1];
                Str[2] = '\0';
                j++;
            }

            int isOper = Checkoper(Str);
            int isIncr = Checkincr(Str);
            int isRela = Checkrelation(Str);
            int isSpl = Checkspl(Str);
            int isBracket = CheckBracket(Str);

            if (isOper == 7) {
                printf("%s : Operator\n", Str);
                AddToTable(Str, *count, "2", "Operator");
            } else if (isIncr == 5) {
                printf("%s : Incrementor/Comparator\n", Str);
                AddToTable(Str, *count, "3", "Incrementor/Comparator");
            } else if (isRela == 11) {
                printf("%s : Relational Operator\n", Str);
                AddToTable(Str, *count, "6", "Relational Operator");
            } else if (isSpl == 13) {
                printf("%s : Special Character\n", Str);
                AddToTable(Str, *count, "7", "Special Character");
            } else if (isBracket == 9) {
                printf("%s : Bracket\n", Str);
                AddToTable(Str, *count, "5", "Bracket");
            }
            (*count)++;
            j++;
            continue;
        }


        i = 0;
        while ((input[j] >= 'a' && input[j] <= 'z') || (input[j] >= 'A' && input[j] <= 'Z') ||
               (input[j] >= '0' && input[j] <= '9') || input[j] == '_') {
            Str[i++] = input[j++];
        }
        Str[i] = '\0';

        int isNum = Number(Str);
        int isKey = CheckKeylist(Str);

        if (isNum == 2) {
            printf("%s : Constant\n", Str);
            AddToTable(Str, *count, "4", "Constant");
        } else if (isKey == 3) {
            printf("%s : Keyword\n", Str);
            AddToTable(Str, *count, "1", "Keyword");
        } else {
            printf("%s : Identifier\n", Str);
            AddToTable(Str, *count, "8", "Identifier");
        }
        (*count)++;
    }
}


int main() {
    char input[100];
    int choice, count;

    do {
        printf("Enter the string:\n");
        fgets(input, sizeof(input), stdin);
        int length = strlen(input);
        if (input[length - 1] == '\n') {
            input[length - 1] = '\0';
        }

        count = 0;
        Tokenize(input, &count);

        printf("\nSymbol Table\n");
        printf("|---------------------------|\n");
        printf("| Value\t | ID\t | Symbol\t |\n");
        printf("|---------------------------|\n");

        for (int i = 0; i < count; i++) {
            printf("| %-8s | %-4s | %-12s |\n", table[i][0], table[i][1], table[i][2]);
        }

        printf("\nDo you wish to continue? (1 for Yes, 0 for No): ");
        scanf("%d", &choice);
        getchar();  // Clear the newline character from the buffer
    } while (choice == 1);

    printf("\nProgram over");
    return 0;
}
