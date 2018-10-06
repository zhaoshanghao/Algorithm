#define N 10
#define INFINITY  32768
#define True 1
#define False 0
#define Error -1
#define Ok 1

#include "stdlib.h"
#include "stdio.h"

typedef enum{DG,DN,UDG,UDN}GraphKind;
typedef char VertexData;

typedef struct ArcNode1
{
	int adj;
} ArcNode1;

typedef struct
{
	VertexData vexs[N];
	ArcNode1 arcs[N][N];
	int vexnum1,arcnum1;
	GraphKind kind1;
}AdjMatrix;

/*..............................  */
typedef struct ArcNode2
{
	int adjvex;
	struct ArcNode2 *nextarc;
} ArcNode2;

typedef struct VertexNode
{
	VertexData data;
	ArcNode2 *firstarc;
}VertexNode;

typedef struct
{
	VertexNode vertex[N];
	int vexnum2,arcnum2;
	GraphKind kind2;
}AdjList;
/*.............................*/

typedef struct Node
{
	int data;
	struct Node *next;
}LinkQueueNode;

typedef struct
{
	LinkQueueNode *front;
	LinkQueueNode *rear;
}LinkQueue;

int InitQueue(LinkQueue *Q)
{
	Q->front=(LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if(Q->front!=NULL)
	{
		Q->rear=Q->front;
		Q->front->next=NULL;
		return(True);
	}
	else  
		return(False);
}

int EnterQueue(LinkQueue *Q,int x)
{
	LinkQueueNode *NewNode;
	NewNode=(LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if(NewNode!=NULL)
	{
		NewNode->data=x;
		NewNode->next=NULL;
		Q->rear->next=NewNode;
		Q->rear=NewNode;
		return(True);
	}
	else 
		return(False);
}

int DeleteQueue(LinkQueue *Q,int *x)
{
	LinkQueueNode *p;
	if(Q->front==Q->rear)
		return(False);
	p=Q->front->next;
	Q->front->next=p->next;
    if(Q->rear==p)
		Q->rear=Q->front;
	*x=p->data;
	free(p);
	return(True);
}

int IsEmpty(LinkQueue *Q)
{
	if(Q->front==Q->rear)
		return(True);
	else 
		return(False);
}
/*..........................*/

typedef struct node1
{
	char data;
	struct node1 *next;
}Node1, *LinkList1;

typedef struct node2
{
	char data1;
	char data2;
	struct node2 *next;
}Node2, *LinkList2;

int a[2];
int visited[N];

int LocateVertex1(AdjMatrix *G1,VertexData v)
{
	int k,j=Error;
	for(k=0;k<G1->vexnum1;k++)
		if(G1->vexs[k]==v)
		{
			j=k;
			break;
		}
	return(j);
}

int CreateUDG1(AdjMatrix *G1,LinkList1 *bt,LinkList2 *br)
{
	int i,j,k;
	Node1 *r,*p;
	Node2 *s,*q;
	VertexData v1,v2;
	(*bt)=(LinkList1)malloc(sizeof(Node1));
	(*br)=(LinkList2)malloc(sizeof(Node2));
	(*bt)->next=NULL;
	(*br)->next=NULL;
	r=*bt;   
	s=*br;
	printf("\ninput G->vexnum,G->arcnum\n");
	scanf("%d,%d",&(G1->vexnum1),&(G1->arcnum1));
	getchar();
	a[0]=G1->vexnum1; a[1]=G1->arcnum1;
	for(i=0;i<G1->vexnum1;i++)
		for(j=0;j<G1->vexnum1;j++)
			G1->arcs[i][j].adj=0;
	printf("input G->vexs\n");
	for(i=0;i<G1->vexnum1;i++)
	{
		scanf("%c",&(G1->vexs[i]));
		p=(Node1*)malloc(sizeof(Node1));
		p->data=G1->vexs[i];
		p->next=NULL;
		r->next=p;
		r=p;
	}
	getchar( );
	printf("input G v1,v2\n");
	for(k=0;k<G1->arcnum1;k++)
	{ 
		scanf("%c",&v1);
		scanf("%c",&v2);
		getchar( );
		q=(Node2*)malloc(sizeof(Node2));
		q->data1=v1;
		q->data2=v2;
		q->next=NULL;
		s->next=q;
		s=q;
		i=LocateVertex1(G1,v1);
		j=LocateVertex1(G1,v2);
		G1->arcs[i][j].adj=1;
		G1->arcs[j][i].adj=1;
	}
	return(Ok);
}
/*........................*/

int LocateVertex2(AdjList *G2,VertexData v)
{
	int k,j=Error;
	for(k=0;k<G2->vexnum2;k++)
		if(G2->vertex[k].data==v)
		{
			j=k;
			break;
		}
	return(j);
}

int CreateUDG2(AdjList *G2,LinkList1 L,LinkList2 M)
{
	int i,j,k;
	//char ch;
	Node1 *m,*t;
	Node2 *n,*s;
	ArcNode2 *p,*r;
	VertexData v1,v2;
	G2->vexnum2=a[0];  G2->arcnum2=a[1];
	for(i=0;i<G2->vexnum2;i++)
	{ 
		m=L->next; 
		t=m;
		G2->vertex[i].data=t->data;
		L->next=L->next->next;
		free(m);
		G2->vertex[i].firstarc=NULL;
	}
	for(k=0;k<G2->arcnum2;k++)
	{
		s=M->next;  
		n=s;
		v1=n->data1;  
		v2=n->data2;
		M->next=M->next->next;
		free(s);
		i=LocateVertex2(G2,v1);
		j=LocateVertex2(G2,v2);
		if(G2->vertex[i].firstarc==NULL)
		{
			p=(ArcNode2*)malloc(sizeof(ArcNode2));
			if(p==NULL)
				return(False);
			G2->vertex[i].firstarc=p;
			p->adjvex=j;
			p->nextarc=NULL;
		}
		else
		{
			r=G2->vertex[i].firstarc;
			while(r->nextarc!=NULL)
			r=r->nextarc;
			p=(ArcNode2*)malloc(sizeof(ArcNode2));
			if(p==NULL)
				return(False);
			r->nextarc=p;
			p->adjvex=j;
			p->nextarc=NULL;
		}
		if(G2->vertex[j].firstarc==NULL)
		{
			p=(ArcNode2*)malloc(sizeof(ArcNode2));
			if(p==NULL)
				return(False);
			G2->vertex[j].firstarc=p;
			p->adjvex=i;
			p->nextarc=NULL;
		}
		else
		{
			r=G2->vertex[j].firstarc;
			while(r->nextarc!=NULL)
			r=r->nextarc;
			p=(ArcNode2*)malloc(sizeof(ArcNode2));
			if(p==NULL)
				return(False);
			r->nextarc=p;
			p->adjvex=i;
			p->nextarc=NULL;
		}	
	}
	return(Ok);
}
/*............................*/

void Depth1(AdjMatrix g1,int vo)
{
	int vj;
	printf("%c",g1.vexs[vo]);
	visited[vo]=True;
	for(vj=0;vj<g1.vexnum1;vj++)
		if((!visited[vj])&&(g1.arcs[vo][vj].adj==1))
	Depth1(g1,vj);
}

void Depth2(AdjList g2,int vo)
{
	ArcNode2 *p;
	printf("%c",g2.vertex[vo].data);
	visited[vo]=True;
	p=g2.vertex[vo].firstarc;
	while(p!=NULL)
	{
		if(!visited[p->adjvex])
		Depth2(g2,p->adjvex);
		p=p->nextarc;
	}
}

void Breadth1(AdjMatrix g1,int vo)
{
	int vi,vj;
	LinkQueue Q;
	InitQueue(&Q);
	visited[vo]=True;
	EnterQueue(&Q,vo);
	while(!IsEmpty(&Q))
	{
		DeleteQueue(&Q,&vi);
		printf("%c",g1.vexs[vi]);
		for(vj=0;vj<g1.vexnum1;vj++)
			if((!visited[vj])&&(g1.arcs[vi][vj].adj==1))
			{
				visited[vj]=True;
				EnterQueue(&Q,vj);
			}
	}
}

void Breadth2(AdjList g2,int vo)
{
	ArcNode2 *p;
	int vi;
	LinkQueue Q;
	InitQueue(&Q);
	visited[vo]=True;
	EnterQueue(&Q,vo);
	while(!IsEmpty(&Q))
	{
		DeleteQueue(&Q,&vi);
		printf("%c",g2.vertex[vi].data);
		p=g2.vertex[vi].firstarc;
		while(p!=NULL)
		{
			if(!visited[p->adjvex])
			{
				visited[p->adjvex]=True;
				EnterQueue(&Q,p->adjvex);
			}
			p=p->nextarc;
		}
	}
}

void Traverse1(AdjMatrix g1)
{
	int vi;
	for(vi=0;vi<g1.vexnum1;vi++)
		visited[vi]=False;
	printf("\nThe order of G1 Depth\n");
	for(vi=0;vi<g1.vexnum1;vi++)
	{
		if(!visited[vi])
		{
			Depth1(g1,vi);    
			printf("\n");
		}
	}
	for(vi=0;vi<g1.vexnum1;vi++)
		visited[vi]=False;
	printf("\nThe order of G1 Breadth\n");
	for(vi=0;vi<g1.vexnum1;vi++)
	{
		if(!visited[vi])
		{
			Breadth1(g1,vi);    
			printf("\n");
		}
	}
}

void Traverse2(AdjList g2)
{
	int vi;
	for(vi=0;vi<g2.vexnum2;vi++)
	visited[vi]=False;
	printf("\nThe order of G2 Depth\n");
	for(vi=0;vi<g2.vexnum2;vi++)
	{
		if(!visited[vi])
		{
			Depth2(g2,vi); 
			printf("\n");
		}
	}
	for(vi=0;vi<g2.vexnum2;vi++)
		visited[vi]=False;
	printf("\nThe order of G2 Breadth\n");
	for(vi=0;vi<g2.vexnum2;vi++)
    {
		if(!visited[vi])
		{
			Breadth2(g2,vi);   
			printf("\n");
		}
	}
}

main( )
{ 
	LinkList1 L;
	LinkList2 M;
	AdjMatrix g1;
	AdjList g2;
	CreateUDG1(&g1,&L,&M);
	CreateUDG2(&g2,L,M);
	Traverse1(g1);
	Traverse2(g2);
}
