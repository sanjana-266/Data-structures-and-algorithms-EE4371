#include<stdio.h>
#include<stdlib.h>

//           Assignment 1         //
int greedy(int *array,int nodes,int *colour);
int main(){
	FILE *fptr;
    char filename[15];
    char nodes;
    int i;
    int j=0;
    printf("Enter the filename to be opened \n");
    scanf("%s", filename);
    /*  open the file for reading */
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    nodes=fgetc(fptr);//gets the number of vertices
    nodes=(int)(nodes-'0');
    char c=fgetc(fptr);
    if(c>47&&c<58){//checking for two-digit number of nodes
    	nodes=(10*nodes)+(int)(c-'0');
    }
    int array[nodes][nodes];//array to store the graph
    char node[2*nodes];//array to store the names of the vertices
    int colour[nodes];//array to assign colour to the vertices
    for(i=0;i<nodes;i++)//initialisation of colour array, uncoloured vertices have colour=0
    	colour[i]=0;
    char a;
    i=0;
    while(i<2*nodes){//storing the names of the vertices
    	a=fgetc(fptr);
    	if(a!='\n'){
    	node[i]=a;
    	i++;} }
    i=0;
    while(i<nodes){//storing the graph points
    	while(j<nodes){
    	a=fgetc(fptr);
    	if(a=='1'||a=='0'){
    	array[i][j]=(int)(a-'0');
    	j++;}}
    	j=0;
    	i++;}

    int newcolour=greedy(array,nodes,colour);//greedy algorithm is called
    for(i=0;i<newcolour;i++){
    	printf("The following turns can be performed at the same time:");
    	for(j=0;j<nodes;j++){
    	if(colour[j]==i+1){
    		printf("%c%c%c",node[2*j],node[2*j+1],' ');}}
    		printf("\n");}
    		fclose(fptr);}

int greedy(int *array,int nodes,int *colour){
	int i;
	int j;
	int m;
	int newcolour=1;//indicates the initial colour, the uncoloured vertices have colour zero
	int marker=2;//true
	for(i=0;i<nodes;i++){
		if(colour[i]==0){//assign a new colour to the first uncoloured vertex
			colour[i]=newcolour;
			newcolour++;//newcolour gets updated with the next number representing the next colour
		}
		for(j=0;j<nodes;j++){
			if(colour[j]==0){//check for next uncoloured vertex
				for(m=0;m<nodes;m++){
					if(colour[m]==newcolour-1){
						if(*(array+j*nodes+m)==1){
							/*check if previously coloured vertices of the colour in question 
							have an incompatibility with the next uncoloured vertex*/
							marker=1;//incompatibility exists
						}}}
				if(marker==2){
					colour[j]=newcolour-1;//if not assign the colour to this vertex
				}
				else
					marker=2;//else reinitialise the marker
			}}}
	return newcolour-1;//return the total number of colours
}