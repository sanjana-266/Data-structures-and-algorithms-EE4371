#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#define Nmax 100

// #define RAND_MAX 100

static int drp;
static float tot_time;
static float fwdtime=0,delay=0;

// float nextTime(float rateParameter)
// {	float c=0;
// 	// return (int)(-logf(1.0f - (float) random() / (RAND_MAX + 1)) / rateParameter);
// 	c= (float)(logf(1.0f - (float) random() / (RAND_MAX + 1)) / rateParameter);
// 	// printf("next time is %d\n",c);
// 	return c;
// }

int nextTime(float rateParameter)
{	int c=0;
	// return (int)(-logf(1.0f - (float) random() / (RAND_MAX + 1)) / rateParameter);
	c= (int)(-logf(1.0f - (float) random() / (RAND_MAX + 1)) / rateParameter);
	// printf("next time is %d\n",c);
	return c;
}

typedef struct{
	int id; // packet id
	int t0; // arrival time of packet
	int priority; // higher means more important
	char contents[80]; // contents of packet
} PACKET;

// PACKET *p;
// p = (PACKET *)malloc(sizeof(PACKET));


//Implement Queue

//Array of pointers
//Circular


// operations needed:
// MakeNull(length);
// 1. insert(q,x) inserts x at rear of the Queue
// 2. x=remove(q) deletes element from queue q and sets x to its contents
// 3.bool n=isempty(q) returns false or true depending on whether or not the queue contains any elements

struct Queue{
	int length;
	int front;
	int rear;
	int *array;
};

struct Queue* MakeNull(int length){
	struct Queue* queue=(struct Queue*)malloc(sizeof(struct Queue));
	queue->length=length;
	//queue->priority=0;
	queue->front=0;
	queue->rear=-1;
	queue->array=(int *)malloc(sizeof(int));
	return queue;
}

int isEmpty(struct Queue* q){
	return q->rear<q->front; //returns 0 if q.rear is smaller than q.front
}

int number(struct Queue* q){ //no. of elements in queue
	return q->rear-q->front+1;
}

int checkFull(struct Queue* q){
	if(q->length==number(q))
		return 1;
	return 0;
}

void insert(struct Queue* q, int x){
	q->array[(++q->rear)%(q->length)] = x;
	// printf("inserting %d\n",x);
}
//------------------------------
// not correct
int drop(struct Queue* q,int N){
	if(isEmpty(q)){
		return -1;
	}
	int x=q->array[((q->front)++%N)];
	drp++;
	// printf("dropping %d\n",x);
	return x;
}
//---------------------------
int forward(struct Queue* q,int N){
	if(isEmpty(q)){
		return -1;
	}
	int x=q->array[((q->front)++%N)];
	// drp++;
	// printf("dropping %d\n",x);
	return x;
}

void simulate(int N,double lam,double mu){
	PACKET *p;
	p = (PACKET *)malloc(sizeof(PACKET));
	struct Queue* q = MakeNull(N);
	int i=0; int dropped;
	// int delay=0;
	int c=0;
	while(p++!=NULL && i<100){
		(p)->id=i++;
		p->t0=nextTime(lam);
		tot_time+=p->t0;
		// printf("i is %d\n",i);
		// printf("id is %d\n",p->id);
		if(number(q)>0){
			c=forward(q,N);
			printf("forwarding %d\n",c);
			
		}
		if(i>N){
			// c++;
			
			dropped=drop(q,N);
			if(dropped==-1){
				printf("Cannot drop, Empty queue\n");
				exit(0);
			}
			insert(q,p->id);
		}
		else{
			// tot_time+=nextTime(lam);
			insert(q,p->id);
		}
		// tot_time+=nextTime(lam);
	}
	// printf("c is %d",c++);

}

void simulate2(int N,float lam,float mu){
	PACKET *p;
	p = (PACKET *)malloc(sizeof(PACKET));
	struct Queue* q = MakeNull(N);
	int fwd2=0,dropped,i=0,c;
	while(i<Nmax && p!=NULL){
		(p)->id=i++;
		p->t0=nextTime(lam);
		tot_time+=p->t0;
		delay=delay+p->t0-nextTime(mu);
		fwdtime+=nextTime(mu);
		// fwd2=drop(q,N); //forwarding
		// if(fwd2==-1){
		// 	printf("Cannot drop, Empty queue\n");
		// 	exit(0);
		// }
		if(number(q)>0){
			c=forward(q,N);
			printf("forwarding %d\n",c);
			
		}
		//to be queued elements
		if(number(q)==N){
			// c++;
			
			dropped=drop(q,N);
			if(dropped==-1){
				printf("Cannot drop, Empty queue\n");
				exit(0);
			}
			insert(q,p->id);
		}
		else{
			// tot_time+=nextTime(lam);
			insert(q,p->id);
		}

	}
}

void simulate3(int N,float lam,float mu){
	PACKET *p;
	p = (PACKET *)malloc(sizeof(PACKET));
	struct Queue* q = MakeNull(N);
	float tot_next_time=0,tot_fwd_time=0;
	int i=0; int fwd;
	while(i<Nmax && p++!=NULL){
		// fwd=nextTime(mu);
		(p)->id=i++;
		// p->t0=nextTime(lam);
		tot_fwd_time+=mu;
		arr=nextTime(lam);
		p->t0=arr;
		tot_next_time+=arr;
		int count=0;
		if(number(q)>0 && number(q)<=N){
			forward(q,N);
		}
		//--------------------check delay and edit------------
		if(number(q)>=N){
			drop(p);
			++p->id=i++;
		}
		else if(number(q)<N){
			insert(q,p->id)
		}
		// (p)->id=i++;
		// p->t0=tot_next_time;
		// if(tot_next_time->)

	}

}

//if queue grows large,packets are dropped
int main(){
	float lam,mu;
	int N;
	scanf("%d",&N);
	scanf("%f",&lam);
	scanf("%f",&mu);
	float timespent=0,per_drop=0;
	simulate2(N,lam,mu);
	printf("total time: %f\n",tot_time);
	printf("total delay: %f\n",delay/Nmax);
	printf("fwd time: %f\n",fwdtime);

	printf("percentage package drop %f\n",drp*1.0/Nmax*100);
	return 0;
}
