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
#define RSource -9
using namespace std;
class Edge
{

    int src,dest;
    double W;
public:
    int setAllValue(int start,int End,double weightvalue )
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
        src=End;
    }
    int setValueWeight(int wv)
    {
        src=wv;
    }


    int GetFirstVertex()
    {
        return src;
    }
    int GetLastVertex()
    {
        return dest;
    }
    double GetEdgeWeight()
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
    void insertItem(int item,double w) ;
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

void ArrayList::insertItem(int newitem,double w)
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

    List[length].setValueEnd(newitem);
    List[length].setValueWeight(w);
    ///store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i;
    for (i = 1; i <= length; i++)
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
/*
void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", List[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}
*/
ArrayList::~ArrayList()
{
    if(List)
        delete [] List;
    List = 0 ;
}





class Graph
{

public:


    double * dist;
    int * parent;
    int *color;
    double *Bellman_dist;
    int *Bellman_parent;
    bool isNegativeWeightCycle=false;

    double ** distanceMatrix;
    int ** parentMatrix;
    int ** weight;


public:
    int nVertices,nEdge;
    ArrayList  * adjList ;

    Graph(bool dir);
    ~Graph();

    void setnVertices(int n);
    void addEdge(int n,int v,double w);
    void printGraph();
    void RemoveEdge(int u,int v);
    Edge *SearchEdge(int u,int v);
    void reweightEdge(int n,int v,double w);
    bool isEdge(int u,int v);
    double getWeight(int u,int v);


    void Dijkstra(int source);
    bool BellmanFord(int source);
    void Result(int source,int destination);
    bool Continue();

    void floydWarshall();
    void JohnsonsAlgorith();


    double getShortestPathWeight(int u,int v);
    void printShortestPath(int u, int v);
    void printDistanceMatrix();
    void printPredecessorMatrix();
    void cleanSpInfo();


};

Graph::Graph(bool dir)
{



}

Graph::~Graph()
{

    if(adjList)
        delete[] adjList;
    adjList = 0;

    if(parent)
        delete[] parent;
    parent = 0;

    if(color)
        delete[] color;
    color = 0;

    if(distanceMatrix)
        delete[] distanceMatrix;
    distanceMatrix = 0;

    if(parentMatrix)
        delete[] parentMatrix;
    parentMatrix = 0;

    if(dist)
        delete[] dist;
    dist = 0;

    if(Bellman_dist)
        delete[] Bellman_dist;
    Bellman_dist = 0;

    if(Bellman_parent)
        delete[] Bellman_parent;
    Bellman_parent= 0;





}
void Graph::setnVertices(int x)
{



    nVertices=x;
    if(adjList!=0)
        delete[] adjList ; ///delete previous list
    adjList = new ArrayList[nVertices+1] ;





    Bellman_parent=new int[nVertices+1];
    Bellman_dist=new double[nVertices+1];



    dist=new double[nVertices+1];
    parent=new int[nVertices+1];



    distanceMatrix=new double*[nVertices+1];
    parentMatrix=new int*[nVertices+1];

    color=new int[nVertices+1];



    distanceMatrix = new double*[nVertices+1];
    for(int i=1; i<=nVertices; i++)
    {
        distanceMatrix[i] = new double[nVertices+1];

    }


    parentMatrix = new int*[nVertices+1];
    for(int i=1; i<=nVertices; i++)
    {
        parentMatrix[i] = new int[nVertices+1];

    }
}

bool Graph::isEdge(int u, int v)
{
    ///returns true if (u,v) is an edge, otherwise should return false
    int check1 = adjList[u].searchItem(v);
    int check2 = adjList[v].searchItem(u);

    if (check1!=NULL_VALUE || check2!=NULL_VALUE)
        return true;
    else
        return false;

}

void Graph:: addEdge(int u,int v,double wv )
{
    /*
    if(u<0 || u>nVertices || v<0 || v>nVertices)
    {
        cout<<"Edgeadd error"<<endl;
    }
    */
    if(!isEdge(u,v))
    {
        adjList[u].insertItem(v,wv) ;

        //if(!directed) adjList[v].insertItem(u) ;

    }


}

double Graph::getWeight(int u,int v)
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

void Graph::printGraph()
{

    for(int i=1; i<=nVertices; i++)
    {
        printf("%d:", i);
        for(int j=1; j<=adjList[i].getLength(); j++)
        {
            cout<<adjList[i].List[j].GetLastVertex()<<"("<<getWeight(i,j)<<")"<<"-->";
        }
        printf("\n");
    }
}

void Graph::RemoveEdge(int u, int v)
{

    if (isEdge(u,v)==false)
        return;
    /*
    else if(u<0 || v<0 || u>nVertices || v>nVertices)
        return;
    */
    else
    {

        adjList[u].removeItem(v);
        /*
        if(!directed && u!=v)
            adjList[v].removeItem(u);
            */
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

void Graph:: reweightEdge(int u,int v,double w)
{
    if(isEdge(u,v))
    {
        adjList[u].List[v].setValueWeight(w);
    }
    else
    {
        addEdge(u,v,w);
    }
}

bool Graph::Continue()
{
    for(int i=1; i<=nVertices; i++)
    {
        if(color[i]==WHITE)
        {
            return true;
        }
    }
    return false;
}


void Graph::Dijkstra(int source)
{
    ///Initialize part

    dist[source]=0;
    color[source]=WHITE;
    parent[source]=source_parent;

    for(int v=1; v<=nVertices; v++)
    {

        if(v!=source)
        {
            dist[v]=INFINITY;

            parent[v]=-1;
            color[v]=WHITE;
        }
    }



    while(Continue())
    {

        /// ExtractMin from visiting vertex

        int currentSource;
        int minIndex;
        for(int k=1; k<=nVertices; k++)
        {
            if(color[k]==WHITE)
            {
                minIndex=k;
                break;
            }
        }
        for(int i=1; i<=nVertices; i++)
        {


            if(dist[minIndex] >dist[i] && color[i]==WHITE)
            {
                minIndex=i;
            }
        }
        currentSource=minIndex;
        color[currentSource]=BLACK;


        /// Relaxation Part

        for(int v=1; v<=nVertices; v++)
        {

            if(isEdge(currentSource,v) && color[v]!=BLACK)
            {

                double alternetWay=dist[currentSource]+abs(adjList[currentSource].List[v].GetEdgeWeight());
                if(alternetWay<dist[v])
                {
                    dist[v]=alternetWay;
                    parent[v]=currentSource;

                }
            }
        }

    }

}

bool Graph::BellmanFord(int source)
{

    Bellman_dist[source]=0;
    Bellman_parent[source]=source_parent;

    ///Initialize  distance [v] value as Infinte except source and parent[each_vertex]=-1 except source

    for(int v=1; v<=nVertices; v++)
    {
        if(v!=source)
        {
            Bellman_dist[v]=INT_MAX;
            Bellman_parent[v]=-1;
        }
    }


    ///Relaxation: Makes (nVertices-1) passes and relaxing each edge

    for(int i=1; i<=nVertices-1; i++)
    {
        for(int j=1; j<=nVertices; j++)
        {

            int u=i,v=j;

            if(isEdge(u,v))
            {
                double weight=adjList[u].List[v].GetEdgeWeight();

                if(Bellman_dist[u]!=INT_MAX && Bellman_dist[u]+weight<Bellman_dist[v])
                {

                    Bellman_dist[v]=Bellman_dist[u]+weight;
                    Bellman_parent[v]=u;

                }

            }

        }

    }

    ///Test whether solution is exist or not

    for(int i=1; i<=nVertices-1; i++)
    {
        for(int j=1; j<=nVertices; j++)
        {

            int u=i,v=j;

            if(isEdge(u,v))
            {
                double weight=adjList[u].List[v].GetEdgeWeight();

                if(Bellman_dist[u]!=INT_MAX && Bellman_dist[u]+weight<Bellman_dist[v])
                {
                    return true;
                }

            }

        }

    }

    return false;
}


void Graph:: JohnsonsAlgorith()
{
    double h[nVertices+1];
    double newPathWeight;
    int randomSource=RSource;
    for(int i=1; i<=nVertices; i++)
    {
        addEdge(randomSource,i,0);
    }

    if(BellmanFord(randomSource))
    {
        cout<<"There is a negative weight cycle"<<endl;
    }
    else
    {

        for(int i=1; i<=nVertices; i++)
        {
            h[i]=Bellman_dist[i];
        }


        for(int i=1; i<=nVertices; i++)
        {

            for(int j=1; j<=nVertices; j++)
            {

                int u=i,v=j;

                if(isEdge(u,v))
                {

                    newPathWeight=adjList[u].List[v].GetEdgeWeight()+h[u]-h[v];
                    reweightEdge(u,v,newPathWeight);
                }

            }

        }


        for(int v=1; v<=nVertices; v++)
        {

            Dijkstra(v);
            for(int i=1; i<=nVertices; i++)
            {
                double originalGraphShortestDistance=dist[i]+h[i]-h[v];
                distanceMatrix[v][i]=originalGraphShortestDistance;
                parentMatrix[v][i]=parent[i];
            }
        }



    }


    for(int i=1; i<=nVertices; i++)
    {
        RemoveEdge(randomSource,i);
    }



}


void Graph::floydWarshall()
{


    for(int i=1; i<=nVertices; i++)
    {
        for(int j=1; j<=nVertices; j++)
        {

            if(i==j)
            {
                distanceMatrix[i][j]=0;
                parentMatrix[i][j]=-1;
            }
            else if(isEdge(i,j))
            {
                distanceMatrix[i][j]=weight[i][j];
                parentMatrix[i][j]=i;
            }
            else
            {
                distanceMatrix[i][j]=INT_MAX;
                parentMatrix[i][j]=-1;
            }

        }

        for(int k=1; k<=nVertices; k++)
        {
            for(int i=1; i<=nVertices; i++)
            {
                for(int j=1; j<=nVertices; j++)
                {

                    if(distanceMatrix[i][j]>distanceMatrix[i][k] + distanceMatrix[k][j])
                    {
                        distanceMatrix[i][j]=distanceMatrix[i][k] + distanceMatrix[k][j];
                        parentMatrix[i][j]=i;

                    }
                }
            }


        }
    }

}

void Graph::Result(int source,int destination)
{


    cout<<"Shortest Path Weight:"<<getShortestPathWeight(source,destination)<<endl;


    stack<int> stk;
    stk.push(destination);
    int x= parentMatrix[source][destination];
    while (x!=-1)
    {

        stk.push(x);
        x= parentMatrix[source][x];

    }
    while(!stk.empty())
    {
        int st=stk.top();
        stk.pop();
        if(st!=source)
        {
            cout<<st<<"("<<distanceMatrix[source][st]<<")"<<"--> ";
        }
        else
        {
            cout<<st<<"-->";
        }

    }
    cout<<endl;


}

void Graph::cleanSpInfo()
{

    for(int i=1; i<=nVertices; i++)
    {
        for(int j=1; j<=nVertices; j++)
        {
            distanceMatrix[i][j]=INT_MAX;
            parentMatrix[i][j]=-1;
        }
    }
    cout<<"APSP matrices cleared"<<endl;

}
void Graph:: printPredecessorMatrix()
{
    for(int i=1; i<=nVertices; i++)
    {
        for(int j=1; j<=nVertices; j++)
        {

            if(!(distanceMatrix[i][j]=INT_MAX))
            {
                cout<<distanceMatrix[i][j]<<" ";
            }
            else
            {
                cout<<"NIL"<<" ";
            }

        }
        cout<<endl;
    }
}
void Graph:: printDistanceMatrix()
{
    for(int i=1; i<=nVertices; i++)
    {
        for(int j=1; j<=nVertices; j++)
        {

            if(!(parentMatrix[i][j]=-1))
            {
                cout<<parentMatrix[i][j]<<" ";
            }
            else
            {
                cout<<"INF"<<" ";
            }

        }
        cout<<endl;
    }
}

void Graph::printShortestPath(int source, int destination)
{
    stack<int> stk;
    stk.push(destination);
    int x= parentMatrix[source][destination];
    while (x!=-1)
    {

        stk.push(x);
        x= parentMatrix[source][x];

    }
    while(!stk.empty())
    {
        int st=stk.top();
        stk.pop();
        if(st!=source)
        {
            cout<<st<<"("<<distanceMatrix[source][st]<<")"<<"--> ";
        }
        else
        {
            cout<<st<<"-->";
        }

    }
    cout<<endl;
}
double Graph:: getShortestPathWeight(int u,int v)
{
    return distanceMatrix[u][v];
}



int main()
{

    bool dir=true;
    Graph g(dir);



    int N,M,w,StarEdge,EndEdge,source,destination;

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


    g.setnVertices(N);



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


                    w=x;
                }
            }

        }


        cout<<"S:"<<StarEdge<<"E:"<<EndEdge<<"w:"<<w<<endl;
        g.addEdge(StarEdge,EndEdge,w);
    }

    cout<<"Graph created\n"<<endl;

    while(1)
    {
        cout<<endl;
        cout<<"1.To clear APSP info"<<endl;
        cout<<"2.Implement Floyd-Warshall Algorithm"<<endl;
        cout<<"3.Implement Johnson’s Algorithm"<<endl;
        cout<<"4.Shortest path with edge"<<endl;
        cout<<"5: Prints the graph in adjacency list with edge weight"<<endl;
        cout<<"6.Prints the distance matrix"<<endl;
        cout<<"7.Prints predecessor matrix "<<endl;
        cout<<"8. or greater value for exist()"<<endl;




        int C;
        cin>>C;
        if(C==1)
        {
            g.cleanSpInfo();
        }
        else if(C==2)
        {

            g.floydWarshall();
            cout<<"Floyd-Warshall algorithm implemented"<<endl;

        }

        else if(C==3)
        {

            g.JohnsonsAlgorith();
            cout<<"Johnsons algorithm implemented"<<endl;

        }
        else if(C==4)
        {
            int s1,d1;
            cin>>s1;
            cin>>d1;
            g.getShortestPathWeight(s1,d1);
            g.printShortestPath(s1,d1);
        }

        else if(C==5)
        {
            g.printGraph();
        }
        else if(C==6)
        {
            g.printDistanceMatrix();
        }
        else if(C==7)
        {
            g.printPredecessorMatrix();
        }
        else if(C>=8)
        {
            return 0;
        }

    }

}
