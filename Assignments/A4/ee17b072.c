#include<stdio.h>
#include <math.h>
#include <stdlib.h>
// ASSIGNMENT 4 //
static float total_time;
static float delay;

int nextTime(float rateParameter)
{	return (int)(-logf(1.0f - (float) random() / (RAND_MAX )) / rateParameter);
}

typedef struct{
	int id; // packet id
	int t0; // arrival time of packet
	int priority; // higher means more important
	char contents[80]; // contents of packet
} PACKET;

struct Queue{//queue functions
	int length;
	int front;
	int rear;
	int *array;
};

struct Queue* MakeNull(int length){
	struct Queue* queue=(struct Queue*)malloc(sizeof(struct Queue));
	queue->length=length;
	queue->front=0;
	queue->rear=-1;
	queue->array=(int *)malloc(sizeof(int));
	return queue;
}

int isEmpty(struct Queue* q){//check for empty queue
	return q->rear<q->front; 
}

int number_elements(struct Queue* q){ //check for no. of elements in queue
	return q->rear-q->front+1;
}

int checkFull(struct Queue* q){// check is queue is full
	if(q->length==number_elements(q))
		return 1;
	return 0;
}

void enqueue(struct Queue* q, int x){
	q->array[(++q->rear)%(q->length)] = x;
}
int dequeue(struct Queue* q,int N){
	if(isEmpty(q)){
		return -1;
	}
	int a=q->array[((q->front)++%N)];
	return a;
}

int packet_simulation(int N, double l, double mu){
	
	PACKET *p;
	p = (PACKET *)malloc(sizeof(PACKET));//packet allocation
	struct Queue* q = MakeNull(N);//creates a queue
	int i=0; 
	int drop=0;
	int t_arrival;
	float forward_time=1/mu;//forward time is the time at which a packet leaves the queue
	do{
		p->id=i;
		t_arrival=nextTime(l);
		if(t_arrival>forward_time){
			delay+=t_arrival-forward_time;//average time spent by a packet in queue
		}
		int j=1;
		while(t_arrival-j*forward_time>=0){
			if(number_elements(q)>0){
				dequeue(q,N);//forwarding
			}
			else
				break;
			j++;

		}
		total_time+=t_arrival;
		p->t0=total_time;
		if(number_elements(q)<N){
			enqueue(q,p->id);//queueing packets
		}
		else{
			drop=drop+1;//dropping packets
		}
	}while(++p!=NULL&&++i<1000);//increment the packet pointer
	return drop;
	}

	int main(){
	int n;
	double l;
	double u;
	printf("Welcome to the fourth Assignment. Enter the values of N, l(rate parameter) and u:\n");
	scanf("%d,%lf,%lf",&n,&l,&u);
	float total_t;
	int drop=packet_simulation(n,l,u);
	printf("N \tl \t\tmu \tAvg-delay \tPercentage-drop \tTime-per-packet\n");
	printf("%d \t%f \t%f \t%f \t%f \t%f\n",n,l,u,delay/1000,(float)drop/10,total_time/1000);

	}