#include <stdio.h>
#define MAX 4

int estado[MAX][MAX][2][MAX][MAX];

/* (c,m,b)
c= canibais, m= missionários, b= lado do barco (0=direita, 1=esquerda)
canibais e missionários no lado ESQUERDO (objetivo final)
se c>m e m!=0, canibal come missionario, deu ruim*/

void printsit(nm,nc,b,dm,dc){
    printf("\nSituação (esquerda):\nCanibais: %d\nMissionarios:%d\nBarco: %d\n",nc,nm,b);
}

void testaCaminho(int nm,int nc,int b,int dm, int dc){
    if(estado[nm][nc][b][dm][dc]==1 || nm>3 || nc>3 || nm<0 || nc <0){
        return;
    }
    //printsit(nm,nc,b,dm,dc);
    if(nc>nm && nm>0){
        printsit(nm,nc,b,dm,dc);
        printf("canibais comeram os missionários restantes no lado esquerdo!\n");
    }else{
        if(nc<nm && nm>0 && nm<3){
            printsit(nm,nc,b,dm,dc);
            printf("canibais comeram os missionários restantes no lado direito!\n");
        }else{
            if(nc==nm){
                switch(b){
                    case 0: estado[nm][nc][b][dm][dc]=1;
                            testaCaminho(nm,nc+2,1,dm,dc-2);
                            testaCaminho(nm+1,nc+1,1,dm-1,dc-1);
                            testaCaminho(nm+2,nc,1,dm-2,dc);
                            break;
                    case 1: estado[nm][nc][b][dm][dc]=1;
                            testaCaminho(nm-1,nc,0,dm+1,dc);
                            testaCaminho(nm-2,nc,0,dm+2,dc);
                            testaCaminho(nm-1,nc-1,0,dm+1,dc+1);
                            break;
                }
            }else{
                if(nc>nm){
                    switch(b){
                        case 0: estado[nm][nc][b][dm][dc]=1;
                                testaCaminho(nm+2,nc,1,dm-2,dc);
                                testaCaminho(nm,nc+2,1,dm,dc-2);
                                break;
                        case 1: estado[nm][nc][b][dm][dc]=1;
                                testaCaminho(nm,nc-1,0,dm,dc+1);
                                break;
                    }
                }else{
                    switch(b){
                        case 0: estado[nm][nc][b][dm][dc]=1;
                                testaCaminho(nm,nc+2,1,dm,dc-2);
                                testaCaminho(nm,nc+1,1,dm,dc-1);
                                break;
                        case 1: estado[nm][nc][b][dm][dc]=1;
                                testaCaminho(nm,nc-1,0,dm,dc+1);
                                break;
                    }
                }
            }
        }
    }
    if(nc==nm && nc==3){
        printsit(nm,nc,b,dm,dc);
        printf("!!!!!!!!!!!!!!!!!!\nChegaram!\n!!!!!!!!!!!!!!!!!!\n");
        return;
    }
    
}



int main(){
    /*situação: 3 missionários e canibais precisam atravessar um rio.
    o barco que eles tem só aguenta 2 pessoas por vez
    caso de um lado do rio existam mais canibais que missionários,
    os canibais irão comer os missionários.*/
    int nm = 0; //inicialmente, 0 missionários na esquerda
    int nc = 0; //inicialmente, 0 canibais na esquerda
    int b = 0;  //inicialmente, barco na direita
    int dm = 3; //inicialmente, 3 missionários na direita
    int dc = 3; //inicialmente, 3 canibais na direita
    printf("Caminho percorrido:\n");
    testaCaminho(nm,nc,b,dm,dc);
    
    return 0;
}