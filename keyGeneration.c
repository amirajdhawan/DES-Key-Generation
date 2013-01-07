#include<stdio.h>
#include<string.h>

int isValid(char *key){
    int count,i,j,res;
    count = 0;
    for(j = 0;j < 8;j++){ 
        for(i = 0;i < 8;i++){
            if((key[j] & 0x01) == 1)
                count++;
            key[j] >>= 1;
        }
    }
    
    res = ((count%2) == 0) ? 0:1;
    
    if(res == 0)
        printf("Key not valid. Re-enter.");
    return res;
}

void getKey(char *key){
    char stringkey[256];
    int flag=0,i;
    do{

        printf("Enter Phrase(Minimum 8 chars): ");
        scanf("%255s",stringkey);
        if(strlen(stringkey)<8)
            printf("Phrase Smaller then required!");
        //printf("%s",stringkey);
        else
            flag=1;
    } while(flag==0);
    
    for(i = 0;i < 8; i++){
        key[i] = stringkey[i];
        //printf("%X",key[i]);
    }
}
void splitkey(char *key, char *c0d0){
    int i,j,k,val,index;
    int initialPermutationOfKeys[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
    for(i = 0;i < 8;i++)
        c0d0[i] = 0;
    for(i = 0;i < 56;i++){
        j=(initialPermutationOfKeys[i] ) / 8;
        k=7-(initialPermutationOfKeys[i]-1) % 8;
        
        if(getbit(key[j],k,8) == 1){
            //if(i == 1)
                //printf("In Loop: %d, %d, %d\n",getbit(key[j],k,8),j,k);
                /*c0d0[i/7]=setbit(c0d0[i/7],i%7,8);
           else
                c0d0[7]=setbit(c0d0[7],i%7,8);
        */
            c0d0[i/8]=setbit(c0d0[i/8],7-i%8,8);
        }
    }
}
void splitc0d0(char *c0, char *d0, char *c0d0){
    int i;
    for(i=0;i<4;i++)
        c0[i]=c0d0[i];
    for(i=0;i<4;i++)
        d0[i]=c0d0[3+i];
    c0[3]=0xF0 & c0[3];
    d0[0]=0x0F & d0[0];

}
void adjustD(char *d0){
    int i,j,gb;
    for(j=0;j<4;j++){
        for(i=0;i<4;i++){
            d0[i]<<=1;
            if(getbit(d0[(i+1)%4],7,8) == 1)
                d0[i]=setbit(d0[i],0,8);
            else
                d0[i]=clearbit(d0[i],0,8);
        }
    }
}

void unadjustD(char *d0){
    int i,j;
    for(j=0;j<4;j++){
        for(i=3;i>0;i--){
            d0[i]>>=1;
            if(getbit(d0[(i-1)%4],0,8) == 1)
                d0[i]=setbit(d0[i],7,8);
            else
                d0[i]=clearbit(d0[i],7,8);
        }
        d0[0]>>=1;
    }
}

void permuteCD(char *c0, char *d0, char **cd){
    int i,j;
    char c[17][4],d[17][4];
    for(i=0;i<4;i++){
        c[0][i]=c0[i];
        d[0][i]=d0[i];
    }
    printf("\n");
    for(i=1;i<17;i++){
        for(j=0;j<4;j++){
            c[i][j]=c[i-1][j];
            d[i][j]=d[i-1][j];
        }
        if(i==1 | i==2 | i==9 | i==16){
            clrshift(c[i],1);
            clrshift(d[i],1);
        }
        else{
            clrshift(c[i],1);
            clrshift(d[i],1);
            clrshift(c[i],1);
            clrshift(d[i],1);
        }
    }
    int x=0;
    for(i=0;i<17;i++){
        unadjustD(d[i]);
        for(j=0;j<3;j++){
            cd[i][j]=c[i][j];
            cd[i][j+4]=d[i][j+1];
        }
    }
    for(i=0;i<17;i++){
        for(j=0;j<4;j++){
            
            if(getbit(c[i][3],7-j,8)==1)
                cd[i][3]=setbit(cd[i][3],7-j,8);
            else
                cd[i][3]=clearbit(cd[i][3],7-j,8);
            
            if(getbit(d[i][0],j,8)==1)
                cd[i][3]=setbit(cd[i][3],j,8);
            else
                cd[i][3]=clearbit(cd[i][3],j,8);
         }
    }
    for(i=0;i<17;i++){
        for(j=0;j<7;j++){
            displayIntToBinary(cd[i][j],8);
            printf(" ");
        }
        printf("\n");
    }
}

void genRoundKeys(char **cd, char **rk){
    int permutate[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
    int i,j,loc,k;
    for(i=0;i<16;i++)
        for(j=0;j<6;j++)
            rk[i][j]=0;

    for(i=0;i<16;i++){
        for(j=0;j<48;j++){
            loc=(permutate[j]-1)/8;
            k=7-(permutate[j]-1)%8;
           // if(j==4 && i==0)
            //    printf("%d,%d,%d",loc,k,permutate[j]);
            if(getbit(cd[i+1][loc],k,8)==1){
                rk[i][j/8]=setbit(rk[i][j/8],7-j%8,8);
             }
            else
                rk[i][j/8]=clearbit(rk[i][j/8],7-j%8,8);
        }
    }
}

void displayRoundKeys(char **rk){
    int i,j;
    for(i=0;i<16;i++){
        printf("\nRound Number-> %d\n",i+1);
        for(j=0;j<6;j++){
            displayIntToBinary(rk[i][j],8);
            printf(" ");
        }
        printf("\n\n");
    }
}
