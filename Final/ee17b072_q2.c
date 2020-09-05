#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*             Final Examination Question 2             */

/* Declaration of tree functions */
int MAX=1000;

/* Nodes of the 4-way tree */
struct node
{
	int num_dig;
	float pxd;
	float pyd;
	struct node* child[4];
	struct node* last_nodes[150];
	int number_of_children;
};struct node *p;
 
/* Each particle */
struct Particle{

	int px[11];
	float pxd;
	int py[11];
	float pyd;
	float vx;
	float vy;
};struct node *pr;

int a,b,c,d;

struct node * Newnode( struct node * Node, float pxd, float pyd, int condition, int num_dig)// function to make the tree
{
	switch (condition)
	{
		case  1 :// first branch
		if(num_dig==10){// the number of digits are equal to 10, in the last step
			p=(struct node*)malloc(sizeof(struct node));
			Node->last_nodes[a]=p;
			p->pxd=pxd;
			p->pyd=pyd;
			Node->number_of_children=a+1;
			p=(struct node*)malloc(sizeof(struct node)); 
		if (Node->child[0]==NULL)// if not already allocated
			Node->child[0]=p;
		else
			p=Node->child[0];
		p->num_dig=num_dig;
			a++;// variable to store the number of last children(leaves)
			return NULL;}
		p=(struct node*)malloc(sizeof(struct node)); 
		if (Node->child[0]==NULL)
			Node->child[0]=p;
		else
			p=Node->child[0];
		p->num_dig=num_dig;
	
		return p;	
		break;

		case  2 :// second branch
		if(num_dig==10){
			p=(struct node*)malloc(sizeof(struct node));
			Node->last_nodes[b]=p;
			p->pxd=pxd;
			p->pyd=pyd;
			Node->number_of_children=b+1;
			p=(struct node*)malloc(sizeof(struct node)); 
		if (Node->child[1]==NULL)
			Node->child[1]=p;
		else
			p=Node->child[1];
			b++;
		p=(struct node*)malloc(sizeof(struct node)); 
		if (Node->child[1]==NULL)
			Node->child[1]=p;
		else
			p=Node->child[1];
		p->num_dig=num_dig;
		
		return p;	
		break;

		case  3 :// third branch
		if(num_dig==10){
			p=(struct node*)malloc(sizeof(struct node));
			Node->last_nodes[c]=p;
			p->pxd=pxd;
			p->pyd=pyd;
			Node->number_of_children=c+1;
			c++;
			p=(struct node*)malloc(sizeof(struct node)); 
		if (Node->child[2]==NULL)
			Node->child[2]=p;
		else
			p=Node->child[2];
		p->num_dig=num_dig;
			return NULL;}
		p=(struct node*)malloc(sizeof(struct node)); 
		if (Node->child[2]==NULL)
			Node->child[2]=p;
		else
			p=Node->child[2];
		p->num_dig=num_dig;
	
		return p;	
		break;

		case  4 :// fourth branch
		if(num_dig==10){
			p=(struct node*)malloc(sizeof(struct node));
			Node->last_nodes[d]=p;
			p->pxd=pxd;
			p->pyd=pyd;
			Node->number_of_children=d+1;
			p=(struct node*)malloc(sizeof(struct node)); 
		if (Node->child[3]==NULL)
			Node->child[3]=p;
		else
			p=Node->child[3];
			p->num_dig=num_dig;
			d++;
			return NULL;}

		p=(struct node*)malloc(sizeof(struct node)); 
		if (Node->child[3]==NULL)
			Node->child[3]=p;
		else
			p=Node->child[3];
		p->num_dig=num_dig;
		return p;	
		break;


}
}}

struct node* SearchParent (struct node *root, struct Particle *p)// to detetrmine the parent of a particular particle
{
	int i,j;
	for(i=0;i<11;i++)
	{
		if(p->px[i]==0&&p->py[i]==0)// to determine the branch
			j=0;

		else if(p->px[i]==1&&p->py[i]==0)
			j=1;

		else if(p->px[i]==0&&p->py[i]==1)
			j=2;

		else if(p->px[i]==1&&p->py[i]==1)
			j=3;

		if((root->child[j])->num_dig==10)// if the num_dig variable is 10, then the leaf has been reached
		{
			return root;
		}
		else
			root=root->child[j]; // otherwise, search further
	}
}

void FindForce (struct node *Parent, struct Particle *p, float *fx, float *fy)// computation of the force
{
	int i;
	float x,y;
	int p1;
	p1=Parent->number_of_children;// number of leaves of the parent(closest particles)
	for(i=0;i<p1;i++)
	{	
		x=-(((Parent->last_nodes[i])->pxd)-(p->pxd));// distance b/w them in x direction
		y=-(((Parent->last_nodes[i])->pyd)-(p->pyd));// distance b/w them in y direction
		(*fx)+=x/pow((x*x+y*y),1.5);// force b/w them in x direction
		(*fy)+=y/pow((x*x+y*y),1.5);// force b/w them in y direction
	}

}

void decimal_to_binary(float p, struct Particle *p1, char coord){// conversion to binary upto 10 places

	if(coord=='x')
	{
		int i;
		if(p>0)// sign bit(MSB)
			(p1->px)[0]=0;
		else
			(p1->px)[0]=1;

		for (i=1;i<=10;i++)// conversion upto 10 bits
		{	
			p=2*p;
			if(p>1)
			{
				(p1->px)[i]=1;
				p=p-1;	
			}
			else
				(p1->px)[i]=0;

		}
	}	
	else
	{
		int i;
		if(p>0)
			(p1->py)[0]=0;
		else
			(p1->py)[0]=1;

		for (i=1;i<=10;i++)
		{	
			p=2*p;
			if(p>1)
			{
				(p1->py)[i]=1;
				p=p-1;	
			}
			else
				(p1->py)[i]=0;	
		}	
	}
}	

static int v_counter;

void dist(float *vx, float *vy)
{
	int V_MAX=100,i;
	float v1,v2;
	float *v=(float*)malloc(MAX*sizeof(float));
	v1=V_MAX*(-1+2*rand()/RAND_MAX);
	v2=V_MAX*(-1+2*rand()/RAND_MAX);
	v_counter++;
	v[v_counter]=(abs(v2)/v2)*sqrt(v1*v1+v2*v2);// assuming vy determines direction of total velocity
	int threshold;
	threshold=(2*V_MAX)/100;
	float *bin[100]; 
	int c=MAX/100;
    for (i=0; i<100; i++) 
         bin[i] = (float *)malloc( c* sizeof(int)); 
	int p[100],k;
	for(i=0;i<100;i++)// sorting
		p[i]=0;
	for (i=0;i<MAX;i++){
			for(k=-50;k<50;k++){
				if(v[i]>2*k&&v[i]<(2*(k+1))){
					bin[50+k][p[50+k]]=v[i];
					p[50+k]++;
				}
			}
		}
	}
int main(){
struct Particle *p;
int i;
p=(struct Particle*)malloc(MAX*sizeof(struct Particle)); 
/* Particle initialisation */
for(i=0;i<MAX;i++)
{
	(p+i)->pxd=-1+2*rand()/RAND_MAX;// random float between -1 and 1
	float pxd=(p+i)->pxd; // variable pxd stores the decimal value of the x coordinate
	(p+i)->pyd=-1+2*rand()/RAND_MAX;
	float pyd=(p+i)->pyd; // variable pyd stores the decimal value of the y coordinate
	dist(&((p+i)->vx),&((p+i)->vy));
	decimal_to_binary(pxd,(p+i),'x'); // array px stores the binary value of the x coordinate
	decimal_to_binary(pyd,(p+i),'y'); // array py stores the binary value of the y coordinate
}
int t,j;
int t_max=10;
float vx,vy,sx,sy,fx,fy,dt=0.01;

/*Placing particles in the tree*/
struct node *root,*temproot;
root=(struct node*)malloc(sizeof(struct node));// creates main root of the tree

for(t=0;t<t_max;t++)// for each time interval
{
	for(i=0;i<MAX;i++)// for each particle
	{	
		a=0;
		b=0;
		c=0;
		d=0;
		temproot=root;

		for(j=0;j<11;j++)
		{

			if((p+i)->px[j]==0&&(p+i)->py[j]==0)
			{
				temproot=Newnode(temproot,(p+i)->pxd,(p+i)->pyd,1,j);// assigns temproot to the root of the subtree the particle belongs to
			}
			else if((p+i)->px[j]==1&&(p+i)->py[j]==0)
			{
				temproot=Newnode(temproot,(p+i)->pxd,(p+i)->pyd,2,j);
			}
			else if((p+i)->px[j]==0&&(p+i)->py[j]==1)
			{
				temproot=Newnode(temproot,(p+i)->pxd,(p+i)->pyd,3,j);
			}
			else if((p+i)->px[j]==1&&(p+i)->py[j]==1)
			{
				temproot=Newnode(temproot,(p+i)->pxd,(p+i)->pyd,4,j);
			}
		}
	}

	for(i=0;i<MAX;i++)// finding the force by checking which particles are the particle's neighbours
	{	
		temproot=root;
		struct node *parent= SearchParent(temproot,(p+i));
		FindForce(parent,(p+i),&fx,&fy);
		vx=(p+i)->vx;
		vy=(p+i)->vy;
		sx=vx*dt+0.5*fx*dt*dt;// displacement in x direction
		sy=vy*dt+0.5*fy*dt*dt;// displacement in y direction
		(p+i)->vx=vx+fx*dt;// velocity in x direction
		(p+i)->vy=vy+fy*dt;// velocity in y direction
		(p+i)->pxd+=sx;// new position in x direction
		(p+i)->pyd+=sy;// new position in y direction

		if((p+i)->pxd>1||(p+i)->pxd<-1)// checking for out of boundary condition
		{
			(p+i)->vx*=-1;// reversing normal velocity
			if((p+i)->pxd)
				(p+i)->pxd=0.99999999;// making sure the particle is inside the boundary
			else
				(p+i)->pxd=-0.99999999;
		}
		if((p+i)->pyd>1||(p+i)->pyd<-1)
		{
			(p+i)->vy*=-1;
			if((p+i)->pyd)
				(p+i)->pyd=0.99999999;
			else
				(p+i)->pyd=-0.99999999;
		}
	}
}}