/*  MIDSEM ASSIGNMENT   */

#include <stdio.h>
#include <stdlib.h>
int maxlength=1000000;

/* Definition of a packet */
struct Packet
{
	char type_of_packet;
	double time_waiting;// this depicts the time a packet has to wait for until the packet infront of it is transmitted,i.e=time of trasmission
	/*Time of waiting of the first packet is incremented by the transmit time of the packet just dequeued before it*/
	int time_received_sec;
	struct Packet *next;

};
/* Definition of the FIFO queue for questions 1 and 2*/
struct Queue
{
	int front;
	int rear;
	struct Packet *p;
	int length;

};

/* Definition of queue functions */
int Addone(int i){

	return (i%maxlength)+1;

}
void Makenull(struct Queue *q){

	q->front=1;
	q->rear=maxlength;
	q->length=0;
	q->p=(struct Packet*)calloc(maxlength,sizeof(struct Packet));
}

int Empty(struct Queue *q){
	if(q->front==Addone(q->rear)){
		return 1;
	}
	else
		return 0;
}

struct Packet * Front(struct Queue *q){
	
	if(Empty(q)){
		printf("Queue is empty.\n");
		return 0;
}
	else
		return (q->p)+q->front;
}

void Enqueue(struct Queue *q, double time_waiting, double time_received, char type_of_packet){

	q->rear=Addone(q->rear);
	((q->p)+q->rear)->time_waiting=time_waiting;
	((q->p)+q->rear)->type_of_packet=type_of_packet;
	((q->p)+q->rear)->time_received_sec=time_received;
	(q->length)++;

}

int Dequeue(struct Queue *q){
	
	if(Empty(q)){
		printf("Queue is empty.\n");
		return 0;
	}

	else{
		q->front=Addone(q->front);
		(q->length)--;
		return 1;	}
}
/*Definition of priority queue for Q3*/
struct Packet *head, *ptr, *video_rear, *data_rear;
int length;// stores length of queue

/*Functions to perform on the special queue*/

void makenull(){

		struct Packet *ptr =(struct Packet*)malloc(sizeof(struct Packet));
		head=ptr;
		data_rear=head;
		video_rear=head;
		head->next=NULL;
		length=0;

}
void insert(int priority, double time_received_sec, double time_waiting)
{  
	int i;
	ptr=head;
	for(i=0;ptr->next!=NULL;i++){// To find the last video packet

		if((ptr->next)->type_of_packet=='d')
		{
			video_rear=ptr;
			break;
		}
		else
			ptr=ptr->next;
	}
	if(priority){//priority=1 for video and 0 for data
		struct Packet *temp,*ptr =(struct Packet*)malloc(sizeof(struct Packet));
		temp=video_rear->next;
		video_rear->next=ptr;
		video_rear=ptr;
		ptr->next=temp;
		(ptr)->type_of_packet='v';
		(ptr)->time_received_sec=time_received_sec;
		(ptr)->time_waiting=time_waiting;
	}
	else{
		struct Packet *temp,*ptr =(struct Packet*)malloc(sizeof(struct Packet));
		data_rear->next=ptr;
		data_rear=ptr;
		ptr->next=NULL;
		(ptr)->type_of_packet='d';
		(ptr)->time_received_sec=time_received_sec;
		(ptr)->time_waiting=time_waiting;
	}
	length++;
	}

void drop_packet(struct Packet *ptr){

	ptr->next=(ptr->next)->next;
	length--;

}

void dequeue()	
{  	
    ptr = head;  
    head = head->next; 
    free(ptr);   
    length--;  
} 
/* Declarations of functions */
void packet_simulation(struct Queue *, double,int);
void priority_queue(double, int);

/* Main function */
int main(){

	printf("Welcome to the midsem assignment.\n");
	printf("Which question would you like to implement?:(1,2 or 3)\n");
	int choice,i;
	double t1;
	scanf("%d",&choice);
	switch(choice){
		case 1:
	printf("This is the first question:\n");
	printf("Please enter the value of time of transmission:\n");
	scanf("%lf",&t1);
	struct Queue *q;
	q=(struct Queue*)malloc(maxlength*sizeof(struct Queue));
	Makenull(q);
	packet_simulation(q,t1,0);
	break;

		case 2:
	printf("This is the answer to the second question. \n");
	printf("Please enter the value of time of transmission:\n");
	scanf("%lf",&t1);
	printf("Please enter the amount of data packets you want to send in the burst at t=0(in terms of number of packets):\n");
	int packets;
	scanf("%d",&packets);
	q=(struct Queue*)malloc(maxlength*sizeof(struct Queue));
	Makenull(q);
	for(i=0;i<packets;i++){
		Enqueue(q,0,0,'d');
	}
	packet_simulation(q,t1,packets);
	break;

		case 3:
	printf("This is the third question:\n");
	printf("Please enter the value of time of transmission:\n");
	scanf("%lf",&t1);
	printf("Please enter the amount of data packets you want to send in the burst at t=0(in terms of number of packets):\n");
	scanf("%d",&packets);
	makenull();
	for(i=0;i<packets;i++){
		insert(0,0,0);
	}
	priority_queue(t1,packets);
	break;

	default:
	printf("Invalid option\n");

}}
/*Packets are simulated by this function for Q1 and 2*/
void packet_simulation(struct Queue *q, double t1, int packets){

	printf("Enter the time in seconds for which you want to simulate the queue:\n");
	int t_max;
	scanf("%d",&t_max);
	int i,i_max,j,k,m,transmitted_data[t_max],transmitted_video[t_max],qlength[t_max];
	double answer_array[t_max+1][6];
	double drop_percentage_data[t_max],drop_percentage_video[t_max];
	i_max=96*t_max;//1/96 seconds is chosen as the time unit
	int drop_video[t_max],drop_data[t_max],dropped_data[t_max],dropped_video[t_max],retransmitted_data_persecond[t_max];
	for(i=0;i<t_max;i++){//Initialisation of the arrays
		dropped_video[i]=0;dropped_data[i]=0;//drops of a set of packets sent in a second
		transmitted_data[i]=0;transmitted_video[i]=0;//transmits of a set of packets sent in a second
		retransmitted_data_persecond[i]=0;//re-transmits in a second
		drop_video[i]=0;drop_data[i]=0;//drops in a second
	}

	struct Packet *p1;
	for(i=0;i<=i_max;i++){
	
		Enqueue(q,0,i/96.0,'v');//Adding video packets

		if((i-48)%96==0){//Adding new data packets
        	for(k=0;k<6;k++)
        		Enqueue(q,0,i/96.0,'d');
        }

		if((i%96==0)&&((i/96)>=1)){// Retransmission occurs every second starting from t=1
				for(k=0;k<drop_data[(i-96)/96];k++){//Retransmitted data packets(dropped data packets of the previous second)
        		Enqueue(q,0,i/96.0,'d');
        		retransmitted_data_persecond[i/96]++;
     	}}
     	if(i%96==0){
			qlength[i/96]=q->length;//to calculate length of queue every second
		}
        
		for(m=0;!(Empty(q));m++){//when any packet arrives in the front of the queue it is checked for the following
			
			p1=Front(q);
			if(p1->type_of_packet=='d'){
				if(((p1->time_waiting+i/96.0)-p1->time_received_sec)>=30){//checked if it can be dropped

					dropped_data[(int)p1->time_received_sec]++;//number of packets dropped out of the packets sent in a particular second
					drop_data[i/96]++;//number of packets dropped in a second(to be retransmitted)
					Dequeue(q);
				}
				else if(p1->time_waiting<=0){//checked if it can be transmitted
					transmitted_data[(int)p1->time_received_sec]++;
					Dequeue(q);
					(p1+1)->time_waiting+=(t1);//waiting time of next packet is incremented by time to transmit
				}
				else//if none of these are possible the loop is broken
					break;
			}
			else//the above process is repeated if the packet infront is a video packet
			{
				if(((p1->time_waiting+i/96.0)-p1->time_received_sec)>=1){

					dropped_video[(int)p1->time_received_sec]++;
					drop_video[i/96]++;
					Dequeue(q);
				}
				else if(p1->time_waiting<=0){
					transmitted_video[(int)p1->time_received_sec]++;
					Dequeue(q);
					(p1+1)->time_waiting+=(t1/2);
				}
				else 
					break;
				}}	
			

			if(i)
			p1->time_waiting=p1->time_waiting-(1.0/96);//Time of waiting is reduced every iteration
}

printf("Time\tLength\tVideo drop(in %)\tData drop(in %)\tVideo sent(in kBytes)\tData sent(in kBytes)\n");
int l;
for(l=0;l<t_max;l++){
		if(!l){
		drop_percentage_data[l]=(((double)dropped_data[l])/(retransmitted_data_persecond[l]+6+packets))*100;
		}
		else
		drop_percentage_data[l]=(((double)dropped_data[l])/(retransmitted_data_persecond[l]+6))*100;
		drop_percentage_video[l]=(((double)dropped_video[l])/(96))*100;
		printf("%d\t%d\t%lf\t%lf\t%lf\t%d\t\n",l,qlength[l],drop_percentage_video[l],drop_percentage_data[l],0.5*((double)transmitted_video[l]),transmitted_data[l]);			
}}

/*Packets are simulated by this function for Q3*/

void priority_queue(double time_transmit, int packets){

	printf("Enter the time in seconds for which you want to simulate the queue:\n");
	int t_max;
	scanf("%d",&t_max);
	int i,i_max,j,k,m,transmitted_data[t_max],transmitted_video[t_max],qlength[t_max];
	double answer_array[t_max+1][6];
	double drop_percentage_data[t_max],drop_percentage_video[t_max];
	i_max=96*t_max;//1/96 seconds is chosen as the time unit
	int drop_video[t_max],drop_data[t_max],dropped_data[t_max],dropped_video[t_max],retransmitted_data_persecond[t_max];
	for(i=0;i<t_max;i++){//Initialisation of the arrays
		dropped_video[i]=0;dropped_data[i]=0;//drops of a set of packets sent in a second
		transmitted_data[i]=0;transmitted_video[i]=0;//transmits of a set of packets sent in a second
		retransmitted_data_persecond[i]=0;//re-transmits in a second
		drop_video[i]=0;drop_data[i]=0;//drops in a second
	}
	struct Packet *ptr;
	for(i=0;i<=i_max;i++){
		insert(1,i/96.0,0);//video packets addition
		if((i-48)%96==0){
			for(k=0;k<6;k++)
				insert(0,i/96.0,0);//addition of data packets
		}
		if((i%96==0)&&((i/96)>=1)){// Retransmission occurs every second starting from t=1
		for(k=0;k<drop_data[(i-96)/96];k++){//Retransmitted data packets(dropped data packets of the previous second)
				insert(0,i/96.0,0);
        		retransmitted_data_persecond[i/96]++;
     	}}

     	ptr=head;
     	for(j=0;(ptr->next)!=NULL;j++){
     		if(((ptr->next))->type_of_packet=='d')
     			{if(i/96.0-((ptr->next))->time_received_sec>=30){// dropped is delay is more than 30
     			dropped_data[(int)((ptr->next))->time_received_sec]++;
     			drop_data[i/96]++;
     			drop_packet(ptr);
     			}
     	}

     		else{
     			if(transmitted_video[(int)((ptr->next)->time_received_sec)]>=92){// dropped on this condition
     			dropped_video[(int)((ptr->next)->time_received_sec)]++;
     			drop_video[i/96]++;
     			drop_packet(ptr);
     			}
     	}

     		ptr=ptr->next;
     	}
     	ptr=head;
     	if(i%96==0){
			qlength[i/96]=length;
		}

     	if(ptr->next==NULL)
     		continue;
     	else{
     	if(((ptr->next))->time_waiting<=0){//check if transmission is possible

     		 if(((ptr->next))->type_of_packet=='d'){
     		 	transmitted_data[(int)((ptr->next))->time_received_sec]++;
     		 	dequeue();
     		 	ptr=head;
       		 	if(ptr->next==NULL)
     		 		continue;
     			((ptr->next))->time_waiting+=time_transmit;
    		 	}
    		 else{
     		 	transmitted_video[(int)((ptr->next))->time_received_sec]++;
     		 	dequeue();
     		 	ptr=head;
     		 	if(ptr->next==NULL)
     		 		continue;
     			((ptr->next))->time_waiting+=time_transmit/2;
    		 	}
    		}
    		((ptr->next))->time_waiting-=(1.0/96);

	}
	}
printf("Time   Length	Video drop(in %)	Data drop(in %)	Video sent(in kBytes)	Data sent(in kBytes)\n");
int l;
for(l=0;l<t_max;l++){
		if(!l){
		drop_percentage_data[l]=(((double)dropped_data[l])/(retransmitted_data_persecond[l]+6+packets))*100;
		}
		else
		drop_percentage_data[l]=(((double)dropped_data[l])/(retransmitted_data_persecond[l]+6))*100;
		drop_percentage_video[l]=(((double)dropped_video[l])/(96))*100;
		printf("%d\t%d\t%lf\t%lf\t%lf\t%d\t\n",l,qlength[l],drop_percentage_video[l],drop_percentage_data[l],0.5*(double)transmitted_video[l],transmitted_data[l]);			
}}
