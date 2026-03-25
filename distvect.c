#include<stdio.h>

struct node{
    unsigned dist[20];
    unsigned from[20];
} rt[10];

int main(){
    int costmat[20][20];
    int nodes, i, j, k;
    int count;

    printf("\nEnter number of nodes: ");
    scanf("%d", &nodes);

    printf("\nEnter cost matrix:\n");
    for(i = 0; i < nodes; i++){
        for(j = 0; j < nodes; j++){
            scanf("%d", &costmat[i][j]);
            costmat[i][i] = 0;
            rt[i].dist[j] = costmat[i][j];
            rt[i].from[j] = j;
        }
    }

    do{
        count = 0;
        for(i = 0; i < nodes; i++){
            for(j = 0; j < nodes; j++){
                for(k = 0; k < nodes; k++){
                    if(rt[i].dist[j] > costmat[i][k] + rt[k].dist[j]){
                        rt[i].dist[j] = costmat[i][k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    } while(count != 0);

    for(i = 0; i < nodes; i++){
        printf("\nRouting table for Router %d:\n", i+1);
        for(j = 0; j < nodes; j++){
            printf("Destination %d via %d Distance %d\n",
                   j+1,
                   rt[i].from[j]+1,
                   rt[i].dist[j]);
        }
    }

    printf("\n\nFinal Distance Matrix:\n\n    ");
    for(j = 0; j < nodes; j++)
        printf("R%d  ", j+1);
    printf("\n");

    for(i = 0; i < nodes; i++){
        printf("R%d  ", i+1);
        for(j = 0; j < nodes; j++){
            printf("%-3d ", rt[i].dist[j]);
        }
        printf("\n");
    }

    printf("\n\nNext Hop Matrix:\n\n    ");
    for(j = 0; j < nodes; j++)
        printf("R%d  ", j+1);
    printf("\n");

    for(i = 0; i < nodes; i++){
        printf("R%d  ", i+1);
        for(j = 0; j < nodes; j++){
            printf("%-3d ", rt[i].from[j] + 1);
        }
        printf("\n");
    }

    return 0;
}

