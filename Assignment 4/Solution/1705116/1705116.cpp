#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <fstream>
#include<iostream>
#define rootNode 0
#include <bits/stdc++.h>

using namespace std;


class Edge
{

public:
    int s,d,w;
};


struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode*next;

};

struct AdjList
{
    struct AdjListNode* head;

};

struct Graph
{
    int V,E;
    Edge* edge;
    struct AdjList*Array;
};

struct AdjListNode *newAdjListNode(int dest,int weight)
{
    struct AdjListNode* newNode=(struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest=dest;
    newNode->weight=weight;
    newNode->next=NULL;
    return newNode;
};

struct Graph* createGraph(int V,int E)
{
    struct Graph* graph=(struct Graph*)malloc(sizeof(struct Graph));

    graph->V=V;
    graph->E =E;
    graph->edge=new Edge[E];

    graph->Array=(struct AdjList*)malloc(V * sizeof(struct AdjList));
    for(int i=0; i<V; ++i)
    {
        graph->Array[i].head=NULL;

    }
    return graph;
};

void addEdge(struct Graph* graph,int src,int dest,int weight)
{
    struct AdjListNode * newNode=newAdjListNode(dest,weight);
    newNode->next=graph->Array[src].head;
    graph->Array[src].head=newNode;


    newNode=newAdjListNode(src,weight);
    newNode->next=graph->Array[dest].head;
    graph->Array[dest].head=newNode;

}

struct MinHeapNode
{
    int v;
    int key;

};

struct MinHeap
{
    int Size;
    int capacity;
    int *pos;
    struct MinHeapNode**Ara;

};

struct MinHeapNode* newMinHeapNode(int v,int key)
{
    struct MinHeapNode* minHeapNode=(struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v=v;
    minHeapNode->key=key;
    return minHeapNode;

};
struct MinHeap * createMinHeap(int capacity)
{
    struct MinHeap * minHeap=(struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos=(int *)malloc(capacity*sizeof(int));
    minHeap->Size=0;
    minHeap->capacity=capacity;
    minHeap->Ara=(struct MinHeapNode**)malloc(capacity*sizeof(struct MinHeapNode*));
    return minHeap;

};

void swapMinHeapNode(struct MinHeapNode** a,struct MinHeapNode** b)
{
    struct MinHeapNode* t=*a;
    *a = *b;
    *b=t;

}

void minHeapify(struct MinHeap* minHeap,int idx)
{
    int smallest,left,right;
    smallest=idx;
    left=2*idx+1;
    right=2*idx+2;
    if(left<minHeap->Size && minHeap->Ara[left]->key<minHeap->Ara[smallest]->key)
    {
        smallest=left;

    }
    if(right<minHeap->Size && minHeap->Ara[right]->key<minHeap->Ara[smallest]->key)
    {
        smallest=right;

    }
    if(smallest!=idx)
    {
        MinHeapNode* smallestNode=minHeap->Ara[smallest];

        MinHeapNode* idxNode=minHeap->Ara[idx];

        minHeap->pos[smallestNode->v]=idx;
        minHeap->pos[idxNode->v]=smallest;
        swapMinHeapNode(&minHeap->Ara[smallest],&minHeap->Ara[idx]);
        minHeapify(minHeap,smallest);
    }

}


void buildMinHeap(struct MinHeap* minHeap,int sz)
{
    int startIndex=(sz/2)-1;
    for(int i=startIndex;i>=0;i--)
    {
        minHeapify(minHeap,i);
    }
}

int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->Size==0;
}
struct MinHeapNode* extractMin(struct MinHeap*minHeap)
{
    if(isEmpty(minHeap))
    {
        return NULL;
    }
    struct MinHeapNode* root = minHeap->Ara[0];
    struct MinHeapNode* lastNode=minHeap->Ara[minHeap->Size-1];
    minHeap->Ara[0]=lastNode;

    minHeap->pos[root->v]=minHeap->Size-1;
    minHeap->pos[lastNode->v]=0;
    --minHeap->Size;
    minHeapify(minHeap,0);
    return root;
};

void decreaseKey(struct MinHeap*minHeap,int v,int key)
{
    int i=minHeap->pos[v];

    minHeap->Ara[i]->key=key;
    while(i!=rootNode && minHeap->Ara[i]->key<minHeap->Ara[(i-1)/2]->key)
    {
        minHeap->pos[minHeap->Ara[i]->v]=(i-1)/2;
        minHeap->pos[minHeap->Ara[(i-1)/2]->v]=i;
        swapMinHeapNode(&minHeap->Ara[i],&minHeap->Ara[(i-1)/2]);
        i=(i-1)/2;
    }
}

bool isInMinHeap(struct MinHeap* minHeap,int v)
{

    if(minHeap->pos[v]<=minHeap->Size)
    {
        return true;
    }
    return false;
}


void printArr(int arr[],int n)
{
    cout<<"Root Node = "<<rootNode<<endl;
    for(int i=0; i<n; ++i)
    {
        if(i!=rootNode)
        {
            cout<<arr[i]<<"  "<<i<<endl;
        }

    }
}

void PrimMST(struct Graph* graph)
{
    int V=graph->V;
    int parent[V];
    int key[V];

    struct MinHeap* minHeap =createMinHeap(V);

    for(int v=0; v<V; ++v)
    {
        if(v!=rootNode)
        {
        parent[v]=-1;
        key[v]=INT_MAX;
        minHeap->Ara[v]=newMinHeapNode(v,key[v]);
        minHeap->pos[v]=v;
        }

    }

    key[rootNode]=0;
    minHeap->Ara[rootNode]=newMinHeapNode(rootNode,key[rootNode]);

    minHeap->pos[rootNode]=rootNode;
    minHeap->Size=V;
    buildMinHeap(minHeap,V);

    while(!isEmpty(minHeap))
    {
        struct MinHeapNode* minHeapNode=extractMin(minHeap);
        int u=minHeapNode->v;

        struct AdjListNode* pCrawl=graph->Array[u].head;
        while(pCrawl!=NULL)
        {
            int v=pCrawl->dest;

            if( isInMinHeap(minHeap,v) && pCrawl->weight<key[v])
            {
                key[v]=pCrawl->weight;
                parent[v]=u;

                decreaseKey(minHeap,v,key[v]);
            }
            pCrawl=pCrawl->next;
        }
    }
    cout<<"Prim's Algorithm:"<<endl;

    printArr(parent,V);
}

class subset
{
public:
    int Kparent;
    int Rank;

};

int Find(subset subsets[],int i)
{
    if(subsets[i].Kparent!=i)
    {
        subsets[i].Kparent=Find(subsets,subsets[i].Kparent);
    }
    return subsets[i].Kparent;
}

void Union(subset subsets[],int x,int y)
{
    int xroot=Find(subsets,x);
    int yroot=Find(subsets,y);
    if(subsets[xroot].Rank<subsets[yroot].Rank)
    {
        subsets[xroot].Kparent=yroot;

    }
    else if(subsets[xroot].Rank>subsets[yroot].Rank)
    {
        subsets[yroot].Kparent=xroot;
    }
    else
    {
        subsets[yroot].Kparent=xroot;
        subsets[xroot].Rank++;
    }
}

int myComp(const void *a,const void * b)
{
    Edge* a1= (Edge*)a;
    Edge* b1= (Edge*)b;
    return a1->w - b1->w;
}

void KruskalMST(Graph* graph)
{
    int V=graph->V;
    Edge result[V];
    int e=0;
    int i=0;
   qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    subset * subsets=new subset[(V*sizeof(subset))];
    for(int v=0; v<V; ++v)
    {
        subsets[v].Kparent=v;
        subsets[v].Rank=0;
    }
    while(e<V-1 && i<graph->E)
    {
        Edge next_edge=graph->edge[i++];
        int x=Find(subsets,next_edge.s);
        int y=Find(subsets,next_edge.d);
        if(x!=y)
        {
            result[e++]=next_edge;
            Union(subsets,x,y);

        }
    }
    int sum=0;
    for(i=0; i<e; ++i)
    {
        sum+=result[i].w;

    }

    cout<<sum<<endl;
    cout<<"Kruskal's algorithm:"<<endl;
     for(i=0; i<e; ++i)
    {
        sum+=result[i].w;
        cout<<result[i].s<<"  "<<result[i].d<<endl;
    }

}


int main()
{

    int N,M,weight,StarEdge,EndEdge;
    ifstream myfile("myfile.txt");

    for(int i=0; i<2; i++)
    {
        int x;
        if(myfile >>x)
        {
            if(i==0)
            {

                N=x;

            }
            else if(i==1)
            {

                M=x;

            }
        }

    }

    struct Graph* graph=createGraph(N,M);


    for(int EdgeNumber=0; EdgeNumber<M; EdgeNumber++)
    {
        for(int i=0; i<3; i++)
        {
            int x;
            if(myfile >>x)
            {
                if(i==0)
                {

                    StarEdge=x;
                }
                else if(i==1)
                {
                    EndEdge=x;
                }
                else if(i==2)
                {
                    weight=abs(x);
                }
            }
        }

        addEdge(graph,StarEdge,EndEdge,weight);

        graph->edge[EdgeNumber].s=StarEdge;
        graph->edge[EdgeNumber].d=EndEdge;
        graph->edge[EdgeNumber].w=weight;

    }


    KruskalMST(graph);
    PrimMST(graph);
    return 0;


}


