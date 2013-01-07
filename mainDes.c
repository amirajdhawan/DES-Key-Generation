#include<stdio.h>
#include"BitOperations.h"
#include"keyGeneration.h"

void main(int argv, char *argc[]){
    int x=3,i,j;
    char tempkey[8],key[8],c0d0[7],c0[4],d0[4];
    char **cd;
    char **roundkeys;
   
   cd=(char **) malloc(17*sizeof(char *));
    for(i=0;i<17;i++){
        cd[i]=(char *) malloc(7*sizeof(char));
    }
    
    roundkeys=(char **) malloc(16*sizeof(char *));
    for(i=0;i<16;i++){
        roundkeys[i]=(char *) malloc(6*sizeof(char));
    }
    
    do{
        getKey(key);
        for(i=0;i<8;i++){
            printf("%X",key[i]);
            tempkey[i]=key[i];
        }
        printf("\n");
    } while(!isValid(tempkey));
   /*For testing 
    key[0]=0x13;
    key[1]=0x34;
    key[2]=0x57;
    key[3]=0x79;
    key[4]=0x9B;
    key[5]=0xBC;
    key[6]=0xDF;
    key[7]=0xF1;
   */
    splitkey(key,c0d0);
    printf("\nc0d0->  ");
    for(i=0;i<7;i++){
        displayIntToBinary(c0d0[i],8);
        printf(" ");
    }
    printf("\nKey->  ");
    for(i=0;i<8;i++){
        displayIntToBinary(key[i],8);
        printf(" ");
    }
    splitc0d0(c0,d0,c0d0);
    printf("\nC0->  ");
    for(i=0;i<4;i++){
        displayIntToBinary(c0[i],8);
        printf(" ");
    }
    adjustD(d0);
    printf("\nD0->  ");
    for(i=0;i<4;i++){
        displayIntToBinary(d0[i],8);
        printf(" ");
    }
    permuteCD(c0,d0,cd);
    genRoundKeys(cd,roundkeys);
    displayRoundKeys(roundkeys);
}
