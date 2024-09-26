#include<string.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
        int numberofstates, count = 0;
        char input [25];
        printf("Krithika - dfa\n");
        printf("Enter the number of states in the dfa:\t");
        scanf("%d", &numberofstates);
        int transition[numberofstates][2] ; //as the only possible inputs are two - zero and one

        int i = 0;
        //construction of the transiton table
        for(i = 0; i<numberofstates; i++){
                printf("\n  {states, input}:{name of the transitioned state} ");
                printf("\n {q%d, 0} : ", i);
                scanf("%d", &transition[i][0]);
                printf("\n {q%d, 1}: " , i);
                scanf("%d", &transition[i][1]);
        }
        int nofinals;
        printf("\n Enter the number of finals states:\t");
        scanf("%d", &nofinals);

        int finalstate[nofinals];

        printf("\n Enter final states:");

        for(i=0; i<nofinals; i++){
                scanf("%d", &finalstate[i]);
        }
        printf("\nTRANSITION TABLE\n");
        printf("\nip\t|0\t|1\t|");
        int j;
        for(i=0; i<numberofstates;i++){
                printf("\n q%d\t|", i);
                for(j =0 ; j<2; j++){
                        printf("q%d\t|", transition[i][j]);
                }
        }
        getchar();
        do{

                printf("\nGive the input buffer: []\n");
                fgets(input, sizeof(input), stdin);
                input[strlen(input)-1] = '\0' ;
                int states = 0, value = 0;

                for(i = 0; i<strlen(input); i++){
                        int ip = input[i] - '0' ;
                        if(ip!=1 && ip!=0){
                                value = 1;
                                break;
                        }
                        states = transition[states][ip];
                }

                int check = 0;
                if(value==0){
                        for(i = 0 ; i<nofinals;i++){
                                if(states == finalstate[i]){
                                        check = 1;
                                        break;
                                }
                        }
                }

                if(check == 1){
                        printf("\nThe input buffer is accepted\n");

                }
                else{
                        printf("\nThe input buffer is not accepted\n");
                }

                printf("\n Enter 0 to exit and 1 to continue: \t:");
                scanf("%d", &count);
                getchar();
        }
        while(count == 1);
}
