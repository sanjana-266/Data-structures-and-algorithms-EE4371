void push(double *stack, double val){
	stack[maxlength-topvalue]=val;
	topvalue++;
}
void pop(double *stack){
	topvalue--;
}
double top(double *stack){
	return stack[maxlength-topvalue+1];
}
int operator(double *stack, char op){
	double val1;
	double val2;
	val1=top(stack);
	pop(stack);
	val2=top(stack);
	pop(stack);

	switch(op){
case '+':
if (topvalue<1){
	printf("Invalid expression, '+' does not have enough operands.\n");
	return 0;
}
else{
	double val;
	val=val1+val2;
	push(stack,val);
}
break;
case '-':
if (topvalue<1){
	printf("Invalid expression, '-' does not have enough operands.\n");
	return 0;
}
else{
	double val;
	val=val1-val2;
	push(stack,val);
}
break;
case '*':
if (topvalue<1){
	printf("Invalid expression, '*' does not have enough operands.\n");
	return 0;
}
else{
	push(stack,val1*val2);
}
break;
case '/':
if (topvalue<1){
	printf("Invalid expression, '/' does not have enough operands.\n");
	return 0;
}
else{
	push(stack,val1/val2);
}
break;}}
double decimal(double a, int b){
 	double res=1;
 	int i;
 	for (i=0;i<-1*b;i++)
 		{res=res/10;}
 	return res;
}
double power(double a, int b){
 	double res=1;
 	int i;
 	for (i=0;i<b;i++)
 		{res=res*10;}
 	return res;
}