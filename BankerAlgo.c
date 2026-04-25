#include <stdio.h>

int main(){
    int n;
    int m;

    int allocation[10][10];
    int max[10][10];
    int need[10][10];

    int available[10];

    printf("Enter number of process : ");
    scanf("%d",&n);

    printf("Enter number of resources: ");
    scanf("%d",&m);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d",&allocation[i][j]);
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d",&max[i][j]);
        }
    }

    for(int i = 0; i < m; i++){
        scanf("%d",&available[i]);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int finish[10] = {0};
    int safeSeq[10];
    int k = 0;
    int work[10];

    for(int i = 0; i < m; i++){
        work[i] = available[i];
    }

    for(int count = 0; count < n; count++){
        for(int i = 0; i < n; i++){
            if(!finish[i]){
                int flag = 1;
                for(int j = 0; j < m; j++){
                    if(need[i][j] > work[j]){
                        flag = 0;
                        break;
                    }
                }
            }
        }
    }

}