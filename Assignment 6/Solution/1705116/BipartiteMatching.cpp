#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#include<cmath>
#include<math.h>
#include <bits/stdc++.h>
#include <fstream>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#define source_parent -99
#define RSource 0
using namespace std;
class Edge
{
    int src,dest,W;

public:
    int setAllValue(int start,int End,int weightvalue )
    {
        src=start;
        dest=End;
        W=weightvalue;
    }

    int setValueStart(int start)
    {
        src=start;
    }
    int setValueEnd(int End)
    {
        dest=End;
    }
    int setValueWeight(int wv)
    {
        W=wv;
    }


    int GetFirstVertex()
    {
        return src;
    }
    int GetLastVertex()
    {
        return dest;
    }
    int GetEdgeWeight()
    {
        return W;
    }
};



class ArrayList
{

    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    Edge * List;
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int start,int item,int w) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool Empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    List = new Edge[listMaxSize] ;
    length =1 ;
}

void ArrayList::insertItem(int start,int newitem,int w)
{
    Edge * tempList ;
    if (length >= listMaxSize)
    {
        ///allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;  /// doubling memory when array is full
        tempList = new Edge[listMaxSize] ;
        int i;
        for( i = 1; i <=length ; i++ )
        {
            tempList[i] = List[i] ; ///copy all items from list to tempList
        }
        delete[] List ; ///free the memory allocated before
        List = tempList ; ///make list to point to new memory
    };
    List[length].setValueStart(start);

    List[length].setValueEnd(newitem);

    List[length].setValueWeight(w);

    ///store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{

    int i;
    for (i = 1; i <length; i++)

    {
        if( List[i].GetLastVertex() == item )
            return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) ///do not preserve order of items
{
    if ( position < 0 || position >= length )
        return ; ///nothing to remove
    List[position] = List[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE )
        return ; ///nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length)
        return NULL_VALUE ;
    return List[position].GetLastVertex() ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::Empty()
{
    if(length==0)
        return true;
    else
        return false;
}

ArrayList::~ArrayList()
{
    if(List)
        delete [] List;
    List = 0 ;
}





class Graph
{

public:
    int nVertices,nEdge;
    ArrayList  * adjList ;
    vector <pair <int,int> > vect ;

    Graph(bool dir);
    ~Graph();

    void setnVertices(int n);
    void addEdge(int n,int v,int w);
    void printGraph();
    void RemoveEdge(int u,int v);
    Edge *SearchEdge(int u,int v);
    bool isEdge(int u,int v);
    int getWeight(int u,int v);

    int FordFulkerson(int s,int t);
    bool BFS(int s,int t,int parentOnAugmentedPath[]);

    bool IsBipartite(int source);


};
bool Graph::IsBipartite(int s)
{
    int Nodecolor[nVertices-1];
    for(int i=0; i<nVertices-2; i++)
    {
        Nodecolor[i]=0;
    }
    queue<int> q;
    q.push(s);
    Nodecolor[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int v=0; v<nVertices-2; v++)
        {
            if(isEdge(u,v))
            {
                if(Nodecolor[v]==0)
                {
                    if(Nodecolor[u]==1)
                    {
                        Nodecolor[v]=2;
                    }
                    else
                    {
                        Nodecolor[v]=1;
                    }
                    q.push(v);
                }
                if(Nodecolor[u]==Nodecolor[v])
                {
                    return false;
                }
            }
        }
    }
    return true;

}
bool Graph::BFS(int s,int t,int parentOnAugmentedPath[])
{

    int visited[nVertices+1];
    for(int i=0; i<nVertices; i++)
    {
        visited[i]=0;
    }
    queue <int> q;
    q.push(s);
    visited[s]=1;
    parentOnAugmentedPath[s]=-1;

    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int v=0; v<nVertices; v++)
        {
            int list_position=adjList[u].searchItem(v);

            if(visited[v]==0 && isEdge(u,v) && adjList[u].List[list_position].GetEdgeWeight()>0)
            {
                q.push(v);
                parentOnAugmentedPath[v]=u;
                visited[v]=1;

            }
        }
    }

    if(visited[t]==1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Graph::FordFulkerson(int s,int t)
{
    int u,v;
    int parentOnAugmentedPath[nVertices];
    int max_flow=0;

    while(BFS(s,t,parentOnAugmentedPath))
    {

        int path_flow=INT_MAX;
        for(v=t; v!=s; v=parentOnAugmentedPath[v])
        {
            u=parentOnAugmentedPath[v];


            int list_position=adjList[u].searchItem(v);

            path_flow=min(path_flow,adjList[u].List[list_position].GetEdgeWeight());



        }
        int b=parentOnAugmentedPath[t];
        int a=parentOnAugmentedPath[b];
        vect.push_back(make_pair(a,b));




        for(v=t; v!=s; v=parentOnAugmentedPath[v])
        {
            u=parentOnAugmentedPath[v];
            int list_position=adjList[u].searchItem(v);
            int currentCapacity=adjList[u].List[list_position].GetEdgeWeight();

            int ResidualCapacity=currentCapacity-path_flow;

            adjList[u].List[list_position].setValueWeight(ResidualCapacity);

            if(isEdge(v,u))
            {
                int list_position=adjList[v].searchItem(u);
                int ReversecurrentCapacity=adjList[v].List[list_position].GetEdgeWeight();
                int ReverseResidualCapacity=ReversecurrentCapacity+path_flow;
                adjList[v].List[list_position].setValueWeight(ReversecurrentCapacity);
            }
            else
            {
                addEdge(v,u,path_flow);
            }


        }

        max_flow+=path_flow;
    }

    return max_flow;
}



Graph::Graph(bool dir)
{



}

Graph::~Graph()
{

    if(adjList)
        delete[] adjList;
    adjList = 0;

}
void Graph::setnVertices(int x)
{
    nVertices=x;
    adjList = new ArrayList[nVertices+2];
}

bool Graph::isEdge(int u, int v)
{
    ///returns true if (u,v) is an edge, otherwise should return false
    int check1 = adjList[u].searchItem(v);
    ///int check2 = adjList[v].searchItem(u);

    if (check1!=NULL_VALUE)
        return true;
    else
        return false;

}

void Graph:: addEdge(int u,int v,int wv )
{

    if(!isEdge(u,v))
    {

        adjList[u].insertItem(u,v,wv);

    }
}

int Graph::getWeight(int u,int v)
{
    if(u<0 || u>nVertices || v<0 || v>nVertices)
    {
        cout<<"invalid"<<endl;
    }
    else
    {

        return adjList[u].List[v].GetEdgeWeight();

    }

}

void Graph::RemoveEdge(int u, int v)
{

    if (isEdge(u,v)==false)
        return;
    else
    {

        adjList[u].removeItem(v);

    }
}
Edge *Graph:: SearchEdge(int u,int v)
{
    if(u<0 || v<0 || u>nVertices || v>nVertices)
    {
        cout<<"Invalid"<<endl;
    }
    else if(isEdge(u,v))
    {
        return &adjList[u].List[v];
    }
    else
    {

        //return NULL_VALUE;
    }

}


int main()
{

    bool dir=true;
    Graph g(dir);
    Graph ResidualGraph(dir);



    int N,M,c,StarEdge,EndEdge,source,sink,anySource;

    ifstream myfile("input.txt");

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

    g.setnVertices(N+2);
    ResidualGraph.setnVertices(N+2);
    source=N;
    sink=N+1;




    for(int EdgeNumber=0; EdgeNumber<M; EdgeNumber++)
    {

        for(int i=0; i<2; i++)
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
            }

        }

        anySource=StarEdge;



        g.addEdge(StarEdge,EndEdge,1);
        g.addEdge(EndEdge,StarEdge,1);


        ResidualGraph.addEdge(StarEdge,EndEdge,1);
        ///ResidualGraph.addEdge(EndEdge,StarEdge,1);
        ResidualGraph.addEdge(source,StarEdge,1);
        ResidualGraph.addEdge(EndEdge,sink,1);

    }
    ofstream outputfile;
    outputfile.open("matching.txt");
    if(g.IsBipartite(anySource))
    {


        int Maximum_Matching=ResidualGraph.FordFulkerson(source,sink);
        cout<<Maximum_Matching<<endl;
        outputfile<<Maximum_Matching<<"\n";
        for(int i=0;i<Maximum_Matching;i++)
        {
            cout<<ResidualGraph.vect[i].first<<" "<<ResidualGraph.vect[i].second<<endl;
            outputfile<<ResidualGraph.vect[i].first<<" "<<ResidualGraph.vect[i].second<<"\n";
        }
    }
    else
    {
        cout<<"The graph is not bipartite"<<endl;
        outputfile<<"The graph is not bipartite.\n";
    }
    outputfile.close();
}

