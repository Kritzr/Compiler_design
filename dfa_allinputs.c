#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int numberofstates, numberofinputs, count = 0;
    char input[25];

    printf("Krithika Ravishankar - DFA with multiple inputs\n");

    // Step 1: Get number of states
    printf("Enter the number of states in the DFA:\t");
    scanf("%d", &numberofstates);

    // Step 2: Get number of input symbols
    printf("Enter the number of input symbols:\t");
    scanf("%d", &numberofinputs);

    // Step 3: Get the actual input symbols
    char inputs[numberofinputs];
    printf("Enter the input symbols (e.g., 0 1 a b): ");
    for (int i = 0; i < numberofinputs; i++) {
        scanf(" %c", &inputs[i]);
    }

    // Step 4: Create a transition table for [numberofstates][numberofinputs]
    int transition[numberofstates][numberofinputs];

    // Step 5: Construct the transition table
    for (int i = 0; i < numberofstates; i++) {
        printf("\n  {states, input}:{name of the transitioned state} ");
        for (int j = 0; j < numberofinputs; j++) {
            printf("\n {q%d, %c} : ", i, inputs[j]);
            scanf("%d", &transition[i][j]);
        }
    }

    // Step 6: Input final states
    int nofinals;
    printf("\n Enter the number of final states:\t");
    scanf("%d", &nofinals);

    int finalstate[nofinals];
    printf("\n Enter final states (by state number): ");
    for (int i = 0; i < nofinals; i++) {
        scanf("%d", &finalstate[i]);
    }

    // Step 7: Display the updated transition table
    printf("\nTRANSITION TABLE\n");
    printf("State\\Input |");
    for (int i = 0; i < numberofinputs; i++) {
        printf(" %c\t|", inputs[i]);
    }
    printf("\n");

    for (int i = 0; i < numberofstates; i++) {
        printf(" q%d\t|", i);
        for (int j = 0; j < numberofinputs; j++) {
            printf(" q%d\t|", transition[i][j]);
        }
        printf("\n");
    }

    // Step 8: DFA simulation loop
    getchar(); // Consumes the leftover newline character
    do {
        printf("\nGive the input buffer: []\n");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';
        int state = 0, invalid = 0;

        for (int i = 0; i < strlen(input); i++) {
            int found = -1;
            
            // Check if the input character is a valid input symbol
            for (int j = 0; j < numberofinputs; j++) {
                if (input[i] == inputs[j]) {
                    found = j;
                    break;
                }
            }

            if (found == -1) { // Invalid input character
                invalid = 1;
                break;
            }

            // Move to the next state based on the input
            state = transition[state][found];
        }

        // Check if the final state is an accepting state
        int accepted = 0;
        if (!invalid) {
            for (int i = 0; i < nofinals; i++) {
                if (state == finalstate[i]) {
                    accepted = 1;
                    break;
                }
            }
        }

        // Result based on acceptance
        if (accepted && !invalid) {
            printf("\nThe input buffer is accepted\n");
        } else {
            printf("\nThe input buffer is not accepted\n");
        }

        printf("\n Enter 0 to exit and 1 to continue: \t:");
        scanf("%d", &count);
        getchar();
    } while (count == 1);

    return 0;
}
