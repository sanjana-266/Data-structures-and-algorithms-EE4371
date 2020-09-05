#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main()
{
	int V_MAX=100,v_counter=0,i;
	float v1,v2;
	int MAX=100000000;
	printf("k\n");
	float *v=(float*)malloc(MAX*sizeof(float));
	printf("kl\n");
	for(i=0;i<MAX;i++){
	v1=V_MAX*(-1+2*rand()/RAND_MAX);
	v2=V_MAX*(-1+2*rand()/RAND_MAX);
	v_counter++;
	v[v_counter]=(abs(v2)/v2)*sqrt(v1*v1+v2*v2);}// assuming vy determines direction of total velocity
	int threshold;
	threshold=(2*V_MAX)/100;
	printf("h\n");
	float *bin[100]; 
	int c=MAX/100;
    for (i=0; i<100; i++) 
         bin[i] = (float *)malloc( c* sizeof(int)); 
	
	printf("hj\n");
	int p[100],k;
	for(i=0;i<100;i++)
		p[i]=0;
	for (i=0;i<MAX;i++){
			for(k=-50;k<50;k++){
				if(v[i]>2*k&&v[i]<(2*(k+1))){
					bin[50+k][p[50+k]]=v[i];
					p[50+k]++;
				}
			}
		}
		FILE* fp;
		fp=fopen("input.txt","w");
    if(fp==NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    
	for(i=0;i<100;i++){
		for(k=0;k<c;k++){
			fwrite()
		}
	}
	}