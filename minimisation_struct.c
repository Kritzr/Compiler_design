#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STATES 100
#define MAX_INPUTS 10
struct DFA
{

    int noOfStates;
    int inputs;
    int startState;
    int finalStates[MAX_STATES];
    int noOfFinalStates;
    int transitions[MAX_STATES][MAX_INPUTS];
};
typedef struct DFA DFA;

int in(int *arr, int size, int val)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == val)
        {
            return 1;
        }
    }
    return 0;
}

int isFinalState(int state, DFA dfa)
{
    for (int i = 0; i < dfa.noOfFinalStates; i++)
    {
        if (state == dfa.finalStates[i])
        {
            return 1;
        }
    }
    return 0;
}

int distinguishable(int state1, int state2, int distinguishTable[MAX_STATES][MAX_STATES], DFA dfa)
{
    if (distinguishTable[state1][state2])
    {
        return 1;
    }
    for (int i = 0; i < dfa.inputs; i++)
    {
        int t1 = dfa.transitions[state1][i];
        int t2 = dfa.transitions[state2][i];
        if (distinguishTable[t1][t2] || distinguishTable[t2][t1])
        {
            return 1;
        }
    }
    return 0;
}
DFA minimizeDFA(DFA *dfa)
{
    int distinguishTable[MAX_STATES][MAX_STATES];
    memset(distinguishTable, 0, sizeof(distinguishTable));

    for (int i = 0; i < MAX_STATES; i++)
    {
        for (int j = 0; j < MAX_STATES; j++)
        {
            if (isFinalState(i, *dfa) && !isFinalState(j, *dfa))
            {
                distinguishTable[i][j] = 1;
                distinguishTable[j][i] = 1;
            }
            else if (isFinalState(j, *dfa) && !isFinalState(i, *dfa))
            {
                distinguishTable[i][j] = 1;
                distinguishTable[i][j] = 1;
            }
        }
    }

    int changed;
    do
    {
        changed = 0;
        for (int i = 0; i < dfa->noOfStates; i++)
        {
            for (int j = 0; j < dfa->noOfStates; j++)
            {
                if (!distinguishTable[i][j] && distinguishable(i, j, distinguishTable, *dfa))
                {
                    changed = 1;
                    distinguishTable[i][j] = 1;
                }
            }
        }
    } while (changed);

    int newStateMap[MAX_STATES];
    for (int i = 0; i < dfa->noOfStates; i++)
    {
        newStateMap[i] = i;
    }

    for (int i = 0; i < dfa->noOfStates; i++)
    {
        for (int j = 0; j < dfa->noOfStates; j++)
        {
            if (!distinguishTable[i][j])
            {
                newStateMap[j] = newStateMap[i];
            }
        }
    }

    DFA minimizedDFA;
    minimizedDFA.noOfStates = 0;
    minimizedDFA.inputs = dfa->inputs;
    minimizedDFA.startState = newStateMap[dfa->startState];
    int usedState[MAX_STATES] = {-1};
    int used = 0;
    int stateNumber[MAX_STATES] = {0};
    for (int i = 0; i < dfa->noOfStates; i++)
    {
        if (!in(usedState, used, newStateMap[i]))
        {
            int current = newStateMap[i];
            usedState[used++] = current;
            stateNumber[current] = used - 1;
            minimizedDFA.noOfStates++;
        }
    }
    int matched[MAX_STATES] = {0};
    int noOfFinalStates = 0;
    int finalStateMap[MAX_STATES] = {0};
    for (int i = 0; i < dfa->noOfStates; i++)
    {
        if (in(dfa->finalStates, dfa->noOfFinalStates, i) && !finalStateMap[newStateMap[i]])
        {
            finalStateMap[newStateMap[i]] = 1;
            minimizedDFA.finalStates[noOfFinalStates++] = stateNumber[newStateMap[i]];
        }
        if (!matched[newStateMap[i]])
        {

            for (int j = 0; j < dfa->inputs; j++)
            {

                minimizedDFA.transitions[stateNumber[newStateMap[i]]][j] = stateNumber[newStateMap[dfa->transitions[i][j]]];
            }
            matched[newStateMap[i]] = 1;
        }
    }

    minimizedDFA.noOfFinalStates = noOfFinalStates;
    minimizedDFA.inputs = dfa->inputs;
    minimizedDFA.startState = stateNumber[newStateMap[dfa->startState]];

    return minimizedDFA;
}

void linePrint()
{
    for (int i = 0; i < 55; i++)
    {
        printf("_");
    }
    printf("\n");
}
void displayDFA(DFA min)
{
    linePrint();
    printf("| States |");
    for (int i = 0; i < min.inputs; i++)
    {
        printf(" %3d |", i);
    }
    printf("\n");

    linePrint();
    for (int i = 0; i < min.noOfStates; i++)
    {
        if (i == min.startState)
        {
            printf("->");
        }
        if (in(min.finalStates, min.noOfFinalStates, i))
        {
            printf("*");
        }
        printf("| %3d ", i);
        for (int j = 0; j < min.inputs; j++)
        {
            printf("| %3d ", min.transitions[i][j]);
        }
        printf("|");
        printf("\n");
        linePrint();
        printf("\n");
    }
}

int main()
{
    DFA dfa;

    printf("Enter the number of states in the DFA: ");
    scanf("%d", &dfa.noOfStates);

    printf("Enter the number of input symbols: ");
    scanf("%d", &dfa.inputs);

    printf("Enter the start state: ");
    scanf("%d", &dfa.startState);

    printf("Enter the number of final states: ");
    scanf("%d", &dfa.noOfFinalStates);

    printf("Enter the final states:\n");
    for (int i = 0; i < dfa.noOfFinalStates; i++)
    {
        scanf("%d", &dfa.finalStates[i]);
    }

    printf("Enter the transition table (State Transition for each input):\n");
    for (int i = 0; i < dfa.noOfStates; i++)
    {
        for (int j = 0; j < dfa.inputs; j++)
        {
            printf("δ(q%d, %d) -> ", i, j);
            scanf("%d", &dfa.transitions[i][j]);
        }
    }

    printf("\nOriginal DFA:\n");
    displayDFA(dfa);

    DFA minimizedDFA = minimizeDFA(&dfa);

    printf("\nMinimized DFA:\n");
    displayDFA(minimizedDFA);

    return 0;
}
