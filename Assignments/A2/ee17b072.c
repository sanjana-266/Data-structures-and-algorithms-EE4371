#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//                        Assignment 2                    //

/*Defining the global variables*/
double stack_array[5];
int choice=0;
int topvalue=1;
int sign=0;
int marker=0;
int maxlength=5;
int length=0;
clock_t start, end;
void parsing(char *str);
int main(){
	char str[50];
	printf("Welcome to the second assignment on the postfix tag. Please enter the string:\n");
	scanf(" %[^\n]",str);
	printf("Do you want to use array(1) or linked list implementation(2) for this problem? Enter 1 or 2:\n");
	scanf("%d",&choice);
	start=clock();
	parsing(str);}
struct node   
{  double val;   
   struct node *next;  
};  
struct node *head, *ptr;	//Definition of the linked list  

void push_linkedlist(double val)	//Function to push an element into the linked list
{  struct node *ptr =(struct node*)malloc(sizeof(struct node));   
        if(head==NULL)  
        {         
            ptr->val = val;  
            ptr -> next = NULL;  
            head=ptr;
            length++;         }   
        else   
        {  
            ptr->val = val;  
            ptr->next = head;  
            head=ptr;
            length++;  }}

int pop_linkedlist()	//Function to pop an element from the linked list
{  double item;  
    struct node *ptr;  
    if (head == NULL)  
    {  
        printf("Stack Underflow"); 
        return -1; 
    }  
    else  
    {  
        item = head->val;  
        ptr = head;  
        head = head->next;  
        free(ptr); 
        length--;         
    }  
} 
double top_linkedlist(){	//Function to retrieve the top element from the linked list
	return head->val;
}
void push(double *stack_array, double val){
	stack_array[maxlength-topvalue]=val;
	topvalue++;
}	//Function to push an element into the array stack
void pop(double *stack_array){
	topvalue--;
}	//Function to pop an element from the array stack
double top(double *stack_array){
	return stack_array[maxlength-topvalue+1];
}	//Function to retrieve the top element from the array stack

char operator(double *stack_array, char op){	//Function to perform operations for the stack
	double val1;
	double val2;
	int length_original=length;
	if(choice==1){	//Array implementation
	val1=top(stack_array);
	pop(stack_array);
	val2=top(stack_array);
	pop(stack_array);}
	else 	//Linked list implementation
	{if(head!=NULL)
	{val1=top_linkedlist();
	pop_linkedlist();}
	else if(head==NULL){
		printf("Invalid expression, '%c' does not have enough operands.\n",op);
		return 'f';
	}
    if(head!=NULL){
	val2=top_linkedlist();
	pop_linkedlist();}
	else if(head==NULL){
		printf("Invalid expression, '%c' does not have enough operands.\n",op);
		return 'f';
	}}
		
if (choice==1){
	switch(op){
case '+':
if (topvalue<1){
	printf("Invalid expression, '+' does not have enough operands.\n");
	return 'f';}
else{
	double val;
	val=val1+val2;
	push(stack_array,val);}
break;
case '-':
if (topvalue<1){
	printf("Invalid expression, '-' does not have enough operands.\n");
	return 'f';}
else{
	double val;
	val=val1-val2;
	push(stack_array,val);}
break;
case '*':
if (topvalue<1){
	printf("Invalid expression, '*' does not have enough operands.\n");
	return 'f';}
else{
	push(stack_array,val1*val2);}
break;
case '/':
if (topvalue<1){
	printf("Invalid expression, '/' does not have enough operands.\n");
	return 'f';}
else{
	push(stack_array,val1/val2);}
break;}}
else if(choice==2){
	switch(op){
case '+':
if (length_original<2){
	printf("Invalid expression, '+' does not have enough operands.\n");
	return 'f';}
else{
	double val;
	val=val1+val2;
	push_linkedlist(val);}
break;
case '-':
if (length_original<2){
	printf("Invalid expression, '-' does not have enough operands.\n");
	return 'f';}
else{
	double val;
	val=val1-val2;
	push_linkedlist(val);}
break;
case '*':
if (length_original<2){
	printf("Invalid expression, '*' does not have enough operands.\n");
	return 'f';}
else{
	push_linkedlist(val1*val2);}
break;
case '/':
if (length_original<2){
	printf("Invalid expression, '/' does not have enough operands.\n");
	return 'f';}
else{
	push_linkedlist(val1/val2);}
break;}}}

double decimal(double a, int b){	//Function to convert an array of numbers into its decimal equivalent
 	double res=1;
 	int i;
 	for (i=0;i<-1*b;i++)
 		{res=res/10;}
 	return res;
}
double power(double a, int b){	   //Function to find the result of a number raised to the power of another number
 	double res=1;
 	int i;
 	if(b>0){
 	for (i=0;i<b;i++)
 		{res=res*10;}}
 	else{
 		for(i=0;i<b;i++)
 			res=res/10;
 	}
 	return res;
}
void get_string(char *s, int m){	//Function to find the element causing an error if any
	int i=0;
	if(m){
	for(i=m+1; (s[i]!=' ')&&(s[i]!='\n');i++){
		printf("%c",s[i]);
	}
	printf("\n");}
	else{
	for(i=m; (s[i]!=' ')&&(s[i]!='\n')&&(s[i]!='	');i++){
		printf("%c",s[i]);
	}}
	printf("\n");}
		
void parsing(char *str){	//Function to parse the input string
int l;
int i;
int j=0;
int result=1;
l=strlen(str);
int stack_position=0;
for(i=0;i<strlen(str);i++){
	if (str[i]==' '||str[i]=='	'){	//Check for spaces or tabs
		marker=i;
		if(sign==1){	//Converting a number into its negative
         	if(choice==1){			
			double res=top(stack_array);
			pop(stack_array);
			push(stack_array,-1*res);}
			else if(choice==2){
			double res=top_linkedlist();
			pop_linkedlist();
			push_linkedlist(-1*res);
			}
			sign=0;
		}}

	else if (str[i]<58&&str[i]>47){	 //Check for digits
		int res=0;
     	while(str[i]<58&&str[i]>47){	//Converting into the numerical equivalent
		  res=res*10 + (int)(str[i]-'0');   	
		  i++;}
     i--;
       	if(choice==1){
     push(stack_array,res);}
     	else
     {push_linkedlist(res);}}

	else if (str[i]=='.'){		//Checking for a decimal part
		double dec_res=0;
         for (j=i+1;str[j]<58&&str[j]>47;j++){
			dec_res+=(double)(str[j]-'0')*decimal(10,i-j);}
			i=j-1;
			if(choice==1){
			double res=top(stack_array);
			pop(stack_array);
			push(stack_array,dec_res+res);}
			else
			{double res=top_linkedlist();
			pop_linkedlist();
			push_linkedlist(dec_res+res);
			}}

	else if (str[i]=='e'){		//Checking for a power of ten
		double e_res=0;
		int temp=0;
		int temp2=0;
		 for (j=i+1;str[j]<58&&str[j]>47;j++){
		 	temp=temp*10+ (int)(str[j]-'0');}
		 	e_res=power(10,temp);
		 	if(str[j]=='.'||str[j]=='+'||str[j]=='/'||str[j]=='*'||str[j]=='e'){	//Error check
		 		printf("Invalid expression due to illegal tag:");
		 		get_string(str,marker);
		 		return;
		 	}
		 	else if(str[i+1]=='-'){
		 	for (j=i+2;str[j]<58&&str[j]>47;j++){
		 	
		 	temp2=temp2*10+ (int)(str[j]-'0');}
		 	e_res=power(10,-1*temp2);
		 
		 	}

         	i=j-1;
         	if(choice==1){
         	double res=top(stack_array);
			pop(stack_array);
			push(stack_array,e_res*res);}
			else
			{double res=top_linkedlist();
			pop_linkedlist();
			push_linkedlist(e_res*res);
			}}

	else if (str[i]=='+'){		//Checking for the '+' operator
		if((str[i-1]!=' ')&&(str[i-1]!='	')&&(str[i+1]!=' ')&&(str[i+1]!='\n')&&(str[i+1]!='	')){
			printf("Invalid expression due to illegal tag:");
			get_string(str,marker);
			return;}

		result=operator(stack_array,'+');
			if (result=='f'){return;}}

	else if (str[i]=='-'){		//Checking for the '-' operator
		if(str[i+1]<58&&str[i+1]>47){
			sign=1;}
		else 
{		result=operator(stack_array,'-');
			if (result=='f'){return;}}}

	else if (str[i]=='*'){		//Checking for the '*' operator
		result=operator(stack_array,'*');
				if (result=='f'){return;}}

	else if (str[i]=='/'){		//Checking for the '/' operator
		result=operator(stack_array,'/');
				if (result=='f'){return;}}}
if(choice==1){
end=clock();
printf("The final answer is %.3lf\n. The time taken is %lf units.\n",top(stack_array),((double) (end - start)) );}
else{
end=clock();
printf("The final answer is %.3lf\n. The time taken is %lf units.\n",top_linkedlist(),((double) (end - start)) );}
}
