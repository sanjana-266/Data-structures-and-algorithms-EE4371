#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Final Exam Q1 */

/* Function declarations */
int* check_path (int i, int j);

/* Variables needed */
float value[1000][310000];// Value array
int wt_size=0;// total number of weights
int temp;
int wt[1000];// array of weights
double val[1000];// array of values
int k=0;

int main(){	
  
	char filename[50];
	FILE *fptr;
	printf("Enter the filename to be opened\n");
	scanf("%s",filename);
    /*  open the file for reading */
    fptr=fopen(filename,"r");
    if(fptr==NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

	while(fscanf(fptr,"%d",&temp)==1)// storing the weights and values
	{
        wt_size+=1;
        wt[wt_size]=temp;
        val[wt_size]=(log10(temp))/2;
    }
	int k=pow(wt_size,0.5)*10000;// maximum total weight(W) possible

    for(int i=0;i<=wt_size;i++)
    {
		for(int j=0;j<=k;j++)// creating the K table using dynamic programming
		{
        	if(i==0) 
        		value[i][j]=0;
			else
			{
				if(wt[i]>j)
				{
			    	value[i][j]=value[i-1][j];
		        }
				else
				{
		        	if(value[i-1][j]>(value[i-1][j-wt[i]]+val[i]))
			    		value[i][j]=value[i-1][j];
		           
		           	else
		              value[i][j]=value[i-1][j-wt[i]]+val[i];
		        }
            }
        }
    }
       int *ans;
       int index;
       for(int j=k;j>=0;j--){// start checking from maximum total weight if the condition is satisfied
       ans=check_path(wt_size,j);// to find the total number of weights selected for that particular value of total weight

       if((10000*pow(ans[0],0.5))>j)// limiting condition
       {
          index=j;
          break;// once the condition is satisfied, we can stop, since this will be the optimal value
       }
       }
       printf("Total value is %f.\nNumber of elements in sack is %d.\n",value[wt_size][index],ans[0]);
       printf("Selected weights are:\n");
       for(int j=ans[0];j>0;j--){
           printf("%d 	",wt[ans[j]]);
       }
       printf("\n");
return 0;
}

int path[1000];

int* check_path (int size, int j){
  int k=1;
  while( size>0 && j>0)
  {
  	if(value[size-1][j]==value[size][j])
    size--;
    
    else
    {
 		path[k]=size;
    	k+=1;
    	j=j-wt[size];
    	size--;
    }
  }
  path[0]=k-1;// stores total number of weights
  return path;// returns array pointer corresponding to the selected weights
}
