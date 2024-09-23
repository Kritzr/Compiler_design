#include<stdio.h>
#include<stdlib.h>
int main(){
        int n , m;
        printf("Enter the number of states:\t");
        scanf("%d", &n);
        printf("Enter the number of inputs;\t");
        scanf("%d", &m);

        int trans[n][m];
        int i , j, k, l;

        for(i = 0 ; i<n; i++){
                printf("state: q%d\t",i);
                for(j = 0 ; j<m; j++){
                    printf("input: %d\t", j);
                    scanf("%d", &trans[i][j]);
                }

        }

        int nofinals;
        printf("Enter the number of final states:\t");
        scanf("%d", &nofinals);

        int finalstates[n];
        int finalset;
        for(i=0; i<n;i++){
                finalstates[i] = 0;
        }

        printf("Enter the final states:\t");
        for(i = 0 ; i<nofinals; i++){
                scanf("%d", &finalset);
                finalstates[finalset]=1;
        }

        int minimisetable[n][n];
        //int mintrans[n][n];
        for(i=0; i<n; i++){
                for(j=0; j<n; j++){
                        minimisetable[i][j] =0;
                }
        }
        for(i = 0; i<n; i++){
                for(j=i+1; j<n; j++){
                        if(finalstates[i]!=finalstates[j]){
                                minimisetable[i][j]= 1;
                        }
                }
        }

        int change = 1;
        while(change){
                change = 0;
                for(i = 0 ; i<n; i++){
                        for(j=i+1; j<n; j++){
                                if(!minimisetable[i][j]){
                                       for(k = 0 ; k<m; k++){
                                                int s1 = trans[i][k];
                                                int s2 = trans[j][k];

                                                if(s1!=s2 &&(minimisetable[s1][s2] || minimisetable[s2][s1])){
                                                        minimisetable[i][j] = 1;
                                                        change = 1;
                                                        break;
                                       }
                                }
                        }
                }
        }
        }

        int statesets[n];
        for(i=0; i<n; i++){
                statesets[i] = i;
        }

        for(i = 0 ; i<n; i++){
                for(j = i+1; j<n; j++){
                        if(!minimisetable[i][j]){
                                statesets[j] = statesets[i];
                        }
                }
        }

        int mintrans[n][m];
        for(i= 0; i<n; i++){
                for(j = 0; j<m; j++){
                        mintrans[statesets[i]][j] = statesets[trans[i][j]];
                }
        }

       printf("krithika r - 2022503035 - minimised dfa\n");
       int display[n];
       for(i=0; i<n; i++){
               display[i] = 0;
       }
       for(i = 0 ; i<n; i++){
               if(!display[statesets[i]]){
                        printf("q%d\t", statesets[i]);
                        for(j=0; j<m; j++){
                                printf("q%d\t", mintrans[statesets[i]][j]);
                        }
                        printf("\n");
                        display[statesets[i]] = 1;
               }
       }
       return 0;
}
