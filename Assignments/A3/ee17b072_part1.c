#include<stdio.h>
#include<math.h>
float value[1000][310000];//Value array
int temp;//temporary storage
int size=0;//number of weights
int w[1000];//array of weights
double logw[1000];//Contains log of weights
int k=0;
int path[1000];
int* pathfinder(int i,int j){
  int k=1;
  while( i>0 & j>0){
   
    if(value[i-1][j]==value[i][j]){
    	i=i-1;
    }
    else{
	//printf("%d %d %f\n",i,j,value[i][j]);
 	path[k]=i;
        k+=1;
        j=j-w[i];
        i=i-1;
    }
  }
  path[0]=k-1;
  return path;
}
int main(){	
        //Reading file name
	char fileName[50];
	printf("Enter the inputfile name:");
	scanf("%s",fileName);
        //filename Read
        //Opening file
	FILE* file = fopen(fileName, "r"); 
	if(!file){
	printf("\n Unable to open : %s ", fileName);
	return -1;
	}
	printf("file read\n");
	//File is read
        //Storing Weights
	while ( fscanf(file, "%d", &temp) == 1 ){
              size+=1;
              w[size]=temp;
              logw[size]=(log(temp))/log(100);
              //logw[size]=temp;
             
        }
        /*
        logw[1]=1;
        logw[2]=2;
        logw[3]=5;
        logw[4]=6;
        */
        printf("Weights Stored\n");
        //Weights Stored
        
        //Maximum Weight required will be sqrt(max(k))*10000
        int k=sqrt(size)*10000;
        //int k=8;
        //Filling the values of the table
        for (int i=0;i<=size;i++){
	    for (int j=0;j<=k;j++){
                 if(i==0) value[i][j]=0;
		 else{
			if (w[i]>j){
			   value[i][j]=value[i-1][j];
		        }
			else{
		           if(value[i-1][j]>(value[i-1][j-w[i]]+logw[i])){
			      value[i][j]=value[i-1][j];
		           }
		           else{
		              value[i][j]=value[i-1][j-w[i]]+logw[i];
		           }
		        }
                  }
            }
        }
       printf("Values Stored\n");
       /*
        for(int i=0;i<=size;i++){
           for(int j=0;j<=k;j++){
              printf("%.1f ",value[i][j]);
           }
           printf("\n"); 
         }*/
       int* way;
       int index;
       for(int j=k;j>=0;j--){
       	way=pathfinder(size,j);
        if((10000*sqrt(way[0]))>j){
           index=j;
           break;
        }
       }
       printf("Value is %f\nnumber of elements in sack is %d, index is %d\n",value[size][index],way[0],index);
       printf("weights taken are  ");
       for(int j=way[0];j>0;j--){
           printf("%d, ",w[way[j]]);
       }
       printf("\n");
return 0;
}