#include <stdio.h>

#define R_MAX 2147483647 
#define nMin 10
#define nMax 100

static long long unsigned int SEED = 0x1; 

void srnd(int seed) { SEED = seed; }

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}

int fromhousemove(int kocka1,int kocka2){
    int posun;
    if ((kocka1+kocka2) > 7){
        posun = kocka1+kocka2-7;
        return posun;
        }
    else{
        posun = 0;
        return posun;
    }
}
    
int teleport(int pos_before_O,int *pos_after_H,int *pos_After_O,int t1,int tunels1[nMax][2]){
    int i;
    for(i = 0;i<t1;i++){
        if( *pos_after_H == tunels1[i][0]){
            *pos_after_H = tunels1[i][1]; 
            *pos_After_O = pos_before_O;
            return 1;
            }
        else
            continue;
        }  
    return 0;
}

        //elimination(R1,R2,Pht,Pot,Pht1,Pot1,round,player_on_turn,array);
int elimination(int Pht,int Pot,int *Pht1,int *Pot1){
    if ( *Pht1 == Pot && (Pht!=-1 || Pot!= -1)) {
        *Pht1 = Pot;
        *Pot1 = -1;
        //array[Pht1] +=1;
        return 1;
    }
    return 0 ;
}
void print_port_elim(int R1,int R2,int player_on_turn,int round,int Pht, int Pht1){
    printf("\n[%d,%d] [%d] [%d,%d] [%d] T E",round,player_on_turn,Pht,R1,R2,Pht1);
}

void print_elimination(int R1,int R2,int player_on_turn,int round,int Pht, int Pht1){
    printf("\n[%d,%d] [%d] [%d,%d] [%d] E",round,player_on_turn,Pht,R1,R2,Pht1);
}
int specialmove_1_2(int kocka1,int kocka2,int pos_before_H,int pos_before_O,int *pos_after_H,int *pos_after_O){

    if((kocka1+kocka2 == 12) && pos_before_H<pos_before_O && pos_before_H>0 && pos_before_O>0){
        *pos_after_H = pos_before_O;
        *pos_after_O = pos_before_H;
        return 1;
    }
    else if ((kocka1+kocka2 == 2) && pos_before_H>pos_before_O && pos_before_H>0 && pos_before_O>0)
    {
        *pos_after_H = pos_before_O;
        *pos_after_O = pos_before_H;
        return 1;
    }
    else
        return 0;
}
void print_port(int R1,int R2,int player_on_turn,int round,int Pht, int Pht1){
    printf("\n[%d,%d] [%d] [%d,%d] [%d] T",round,player_on_turn,Pht,R1,R2,Pht1);
}

int max(int num1,int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
void game(int n,int t,int tunels[nMax][2]){
    int array[nMax],i;
    int Pht,Pht1 = -1;
    int Pot,Pot1 = -1;
    int R1,R2;
    int round = 1;
    int player_on_turn;
    int d; //posun na drahe


    for (i = 0;i<n;i++)
        array[i] = 0;

    while(1){

        R1 = rnd(1,6);
        R2 = rnd(1,6);

        if (round%2 == 1)//{1 : -1 :-1                                          //pht = -1   poy = 1            
            player_on_turn = 1,Pht = Pot1,Pot = Pht1;  //Pht = pozicia[0],Pot = pozicia[1]; //Pht = Pot1 Pot = Pht1           vyber hraca + nastavene pht/pot
            //printf("\npred posunom         PHT  = %d POT = %d",Pht,Pot);}
        else
            player_on_turn = 2, Pht = Pot1, Pot = Pht1;  //Pht = pozicia[1];Pot = pozicia[0]; //Pht = Pot1 Pot = Pht1
            //printf("\npred posunom         PHT  = %d POT = %d",Pht,Pot);}

        if (Pht == -1){ // neposunul sa
            d = fromhousemove(R1,R2);
            if (d == 0){
                Pht1 = Pht,Pot1 = Pot;
                printf("\n[%d,%d] [%d] [%d,%d] [%d]",round,player_on_turn,Pht,R1,R2,Pht1);
                round+=1;
                continue;
            }
            else{ //posun z domca
                Pht1 = d,Pot1 = Pot; 
                if(teleport(Pot1,&Pht1,&Pot1,t,tunels) == 1){
                    if (elimination(Pht,Pot1,&Pht1,&Pot1) == 1){
                        print_port_elim(R1,R2,player_on_turn,round,Pht,Pht1);
                        array[Pht1]+=1;
                        round+=1;
                        continue;
                    }
                    print_port(R1,R2,player_on_turn,round,Pht,Pht1);
                    array[Pht1] +=1;
                    round+=1;
                    continue;
                }
                if(elimination(Pht,Pot1,&Pht1,&Pot1) == 1){
                    print_elimination(R1,R2,player_on_turn,round,Pht,Pht1);
                    array[Pht1] +=1;
                    round+=1;
                    continue;
                }
                printf("\n[%d,%d] [%d] [%d,%d] [%d]",round,player_on_turn,Pht,R1,R2,Pht1);
                array[Pht1] +=1;
                round +=1;
                continue; 
            }
        }
        else{  //auta su na drahe    
            if (specialmove_1_2(R1,R2,Pht,Pot,&Pht1,&Pot1) == 1){
                printf("\n[%d,%d] [%d] [%d,%d] [%d] S",round,player_on_turn,Pht,R1,R2,Pht1);
                array[Pht1]+=1,array[Pot1]+=1;
                round +=1;
                continue;
                }

            d = max(R1,R2);
            Pht1 = d + Pht,Pot1 = Pot;
            if(teleport(Pot1,&Pht1,&Pot1,t,tunels) == 1){
                    if (elimination(Pht,Pot1,&Pht1,&Pot1) == 1){
                        print_port_elim(R1,R2,player_on_turn,round,Pht,Pht1);
                        array[Pht1]+=1;
                        round+=1;
                        continue;
                    }
                    print_port(R1,R2,player_on_turn,round,Pht,Pht1);
                    array[Pht1]+=1;
                    round+=1;
                    continue;
                }

            if(elimination(Pht,Pot1,&Pht1,&Pot1) == 1){
                    print_elimination(R1,R2,player_on_turn,round,Pht,Pht1);
                    array[Pht1] +=1;
                    round+=1;
                    continue;
                }
            printf("\n[%d,%d] [%d] [%d,%d] [%d]",round,player_on_turn,Pht,R1,R2,Pht1); 
            array[Pht1] +=1;
            round +=1;
        }

        if (Pht1 >= n){
            printf("\nWINNER: %d",player_on_turn);
            printf("\nVISITS:");
            for(i = 0;i<n;i++){
                printf(" %d",array[i]);
            }
            break;
            }
        else
            continue;
    }
}

int main(){
    int s,t,n;
    int i = 0,k = 0;
    int enter,exit;
    int j,tmp,tmp1;
/*-----------------------------PODMIENKY 1 ----------------------------------------*/
    scanf("%d %d %d",&s,&t,&n); 
    if ( (s<=0)|| ((t*2)>=(n/2)) || (nMin > n) || (n > nMax))
        return 1;

    srnd(s);

    int tunels[nMax][2] = {0};
/*------------------------PODMIENKY 2 --------------------------------------*/
    do{
        if (t == 0)
            break;
        scanf("\n%d %d",&enter,&exit);
        if ((enter == exit) || (enter == 0) || (enter == (n-1)) ||  (exit == 0) || (exit == (n-1)) || (enter > n || enter < 1) || (exit > n || exit < 1))
            return 2;
        for(i = 0;i < t;i++){
            if (tunels[i][0] == enter)    //ci uz mame rovnaky enter do tunela
                return 2;          
                }
        for(i = 0;i < t;i++){   //5 16 --- 16 55
            if (exit == tunels[i][0]) 
                return 2;
        } 
        for(i = 0;i < t;i++){   //5 16 --- 16 55
            if (enter == tunels[i][1]) 
                return 2;
        } 
        tunels[k][0] = enter;
        tunels[k][1] = exit;
        k+=1;
    }while (k<t);
/*-----------------------------------SORT FUNKCIA-------------------------------------------------*/
    for (i = 0; i < t; ++i) 
        {
        for (j = i + 1; j < t; ++j)
            {
            if (tunels[i][0] > tunels[j][0]) 
                {
                    tmp =  tunels[i][0];
                    tmp1 = tunels[i][1];
                    tunels[i][0] = tunels[j][0];
                    tunels[i][1] = tunels[j][1];
                    tunels[j][0] = tmp;
                    tunels[j][1] = tmp1;
                }
            }
        }
/*----------------------------------VYPIS TUNELOV---------------------------------------------------*/
    if (t == 0)
        printf("TUNNELS:");
    else{
        printf("TUNNELS:");
        for(i = 0;i<t;i++)
        printf(" [%d,%d]",tunels[i][0],tunels[i][1]);
        }
    game(n,t,tunels);
    return 0;
}
