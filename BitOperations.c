#include <stdio.h>

void displayIntToBinary(int val,int bits){
	int n;
	for(n = 0; n < bits; n++){
		if((val & 0x80) != 0)
			printf("1");
		else
			printf("0");
		val<<=1;
	}
}

int setbit(int val, int index, int bits){
    if(index < bits)
        return val | (0x01 << (index));
    else
        return val;
}

int getbit(int val, int index, int bits){
    if(index < bits)
       return ((0x01 << index) & val) >> index;
    else
        return val;
}

int clearbit(int val, int index, int bits){
    if(index < bits)
        return val & ~(0x01 << (index));
    else
        return val;
}

void clrshift(char *val, int shift){
    int i = 0,j,gb;
    for(i = 0;i < shift; i++){
        
        gb=getbit(val[0],7,8);
        
        for(i=0;i<4;i++){
            val[i]<<=1;
            if(i!=3){
                if(getbit(val[(i+1)%4],7,8)==1 ? 1:0)
                    val[i]=setbit(val[i],0,8);
                else
                    val[i]=clearbit(val[i],0,8);
            }
        }
        if(gb==1)
            val[3]=setbit(val[3],4,8);
        else
            val[3]=clearbit(val[3],4,8);
    }
}

