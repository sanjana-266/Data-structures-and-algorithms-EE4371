#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//        Assignment 3 part 2      //
static long knapsack(int *w, int W, int i, int N, int c);
int getRandom(int lower, int upper) ;
int max[20];//variables to store the maximum and minimum number of times the function is called
int min[20];

int main(){
	int i;
	int j;
	int c[20];
	float avg[20];
	for(i=0;i<20;i++){
	min[i]=1;
	max[i]=1;
	avg[i]=0;
	c[i]=1;}
	srand(time(0));	//Getting the seed for the random function
	for(i=0;i<1e4;i++){
		int N=getRandom(1,20);	//Generating a random N value
		int W=getRandom(0,(N*N)/2);	//Generating a random W value
		int w[N];
		for (j=0;j<N;j++){	//Generating random w[i] values
			w[j]=getRandom(0,N);}
		c[N-1]=knapsack(w,W,0,N,0);
		if(c[N-1]<0)
			c[N-1]=-1*c[N-1];
		avg[N-1]+=(c[N-1]/1e4);
		if(c[N-1]>max[N-1])//comparing the maximum generated until now with the new value of count, both w.r.t N
			max[N-1]=c[N-1];
		if(min[N-1]>1&&min[N-1]>c[N-1])//comparing the minimum generated until now with the new value of count, both w.r.t N
			min[N-1]=c[N-1];
		}

	printf("\tN \t\t Max \t\t Min \t \t Average\n");//printing the table
	for (i=0;i<20;i++)
		printf("%6.d \t\t %6.d \t %6.d \t \t%.6f\n",i+1,max[i],min[i],avg[i]);
	}

static long knapsack(int *w, int W, int i, int N, int c){ /*Knapsack function with a count variable
														 to count the number of times it is being called*/
	static long count;//variable to store the number of times the function is being called
	count=c;
	count++;
	if (W==0)
		return count;
	else if(W<0||i>=N)
		return -1*count;//this situation arises when none of the weights sum up to the total weight
	else if(knapsack(w,W-w[i],i+1,N,count)>0)//recursive call
		 return count;
	else 
		return knapsack(w,W,i+1,N,count);//recursive call if the previous combination of weights does not add up
	}

int getRandom(int lower, int upper) //Function to generate the random integers
{
	return(rand() % ((int)(upper) - lower + 1)) + lower;  
}