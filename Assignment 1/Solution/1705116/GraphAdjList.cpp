#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#include <chrono>
#include<math.h>
using namespace std::chrono;

using namespace std;

class Queue
{

    int queueIniSize ;
    int queueMaxSize;
    int* data;
    int length;
    int Front;
    int Rear;
public:
    Queue();
    ~Queue();
    void Enqueue(int item);
    int Dequeue();
    bool Empty();

};
Queue::Queue()
{
    queueIniSize =2;
    queueMaxSize=queueIniSize;
    data = new int[queueMaxSize];
    length=0;
    Front=0;
    Rear=0;

}
void Queue::Enqueue(int item)
{
    if(length==queueMaxSize)
    {
        int* tempData;
        queueMaxSize=2*queueMaxSize;
        tempData=new int[queueMaxSize];
        int i,j;
        j=0;
        for(i=Rear; i<length; i++)
        {
            tempData[j++]=data[i];
        }
        Rear =0;
        Front=length;
        delete[] data;
        data=tempData;
    }
    data[Front]=item;
    Front = (Front+1)%queueMaxSize;
    length++;

}

bool Queue::Empty()
{

    if(length==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Queue::Dequeue()
{

    if(length==0)
    {
        return NULL_VALUE;

    }
    int item=data[Rear];
    Rear=(Rear+1)%queueMaxSize;
    length--;
    return item;
}
Queue::~Queue()
{

    if(data)
    {
        delete[] data;
        data=0;
    }
}

class ArrayList
{
    int * List;
    int length;
    int listMaxSize;
    int listIniSize;
public:
    ArrayList();
    ~ArrayList();
    int searchItem(int item);
    void insertItem(int item);
    void removeItem(int item);
    void removeItemAt(int item);
    int getItem(int position);
    int getLength();
    bool Empty();
    void printList();
};


ArrayList :: ArrayList()
{
    listIniSize=2;
    listMaxSize=listIniSize;
    List=new int[listMaxSize];
    length=0;
}

void ArrayList::insertItem(int newitem)
{

    int * tempList;
    if(length == listMaxSize)
    {
        listMaxSize=2*listMaxSize;
        tempList=new int[listMaxSize];
        int i;
        for(i=0; i<length; i++)
        {
            tempList[i]=List[i];
        }
        delete[] List;
        List=tempList;
    }
    List[length]=newitem;
    length++;
}

int ArrayList:: searchItem(int item)
{
    int i=0;
    for(i=0; i<length; i++)
    {
        if(List[i]==item)
        {

            return i;
        }
    }
    return NULL_VALUE;
}


void ArrayList::removeItemAt(int position)
{
    if(position<0 || position >=length)
        return ;
    List[position]=List[length-1];
    length--;
}

void ArrayList::removeItem(int item)
{
    int position;
    position=searchItem(item);
    if(position==NULL_VALUE )
        return;
    removeItemAt(position);
}

int ArrayList::getItem(int position)
{
    if(position<0 || position>=length)
        return NULL_VALUE;
    return List[position];

}

int ArrayList::getLength()
{
    return length;
}

bool ArrayList::Empty()
{

    if(length==0)
        return true ;
    else
        return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
    {
        cout<<List[i];
        cout<<"Current Size: "<<listMaxSize<<"current length: "<<length<<endl;

    }
}

ArrayList::~ArrayList()
{
    if(List)
        delete[] List;
    List=0;
}


class Graph
{
    int nVertices,nEdges;
    bool directed;
    ArrayList * adjList;
    int *parent,*color,*Distance;
    int *dparent,*dcolor;
    int *discovery,*finish;
public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int n,int v);
    void removeEdge(int u,int v);
    bool isEdge(int u,int v);
    int getOutDegree(int u);
    int getInDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u,int v);
    int getDist(int u,int v);
    void printGraph();
    void BFS(int source);

    void DFS(int source);
    void DFS_visit(int source,int time);

    int getUndirDegree(int u);


};


Graph::Graph(bool dir)
{
    nVertices=0;
    nEdges=0;
    adjList=0;
    directed=dir;
    parent=new int[nVertices];
    color=new int[nVertices];
    Distance=new int[nVertices];
}

void Graph::setnVertices(int x)
{
    nVertices=x;
    adjList=new ArrayList[nVertices];
    parent=new int[nVertices];
    color=new int[nVertices];
    Distance=new int[nVertices];
    dparent=new int[nVertices];
    dcolor=new int[nVertices];
    discovery=new int[nVertices];
    finish=new int[nVertices];

}

bool Graph:: addEdge(int u,int v)
{

    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        return false;
    }
    if(!isEdge(u,v))
    {
        adjList[u].insertItem(v);
        if(!directed)
        {
            adjList[v].insertItem(u);
        }
        this->nEdges++;
        return true;

    }




}
void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Entered vertices is invalid"<<endl;
        return;
    }
    if(isEdge(u,v)==false)
    {
        return;
    }
    else
    {
        this->nEdges--;
        adjList[u].removeItem(v);
        if(!directed)
        {
            adjList[v].removeItem(u);
        }
    }
}

bool Graph::isEdge(int u,int v)
{
    int check1 = adjList[u].searchItem(v);
    int check2 = adjList[v].searchItem(u);
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Entered vertices is invalid"<<endl;

    }
    else if(check1!=NULL_VALUE || check2!=NULL_VALUE )
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Graph::getInDegree(int u)
{
    if(u<0 || u>=nVertices)
    {
        cout<<"Entered vertices is invalid"<<endl;

    }
    else
    {
        int degree=0;
        for(int i=0; i<nVertices; i++)
        {
            if(i==u)
            {
                continue;
            }
            if(adjList[i].searchItem(u)!=NULL_VALUE )
                degree++;
        }
        return degree;

    }

}
int Graph::getUndirDegree(int u)
{
    if(u<0 || u>=nVertices)
    {
        cout<<"Entered vertices is invalid"<<endl;

    }

    else
    {
        int degree =0;
        for(int i=0; i<adjList[u].getLength(); i++)
        {
            if(u==adjList[u].getItem(i))
            {
                degree=degree+2;
            }
            else
            {
                degree++;
            }
        }
        return degree;
    }
}
int Graph::getOutDegree(int u)
{
    if(u<0 || u>=nVertices)
    {
        cout<<"Entered vertices is invalid"<<endl;

    }

    else
    {
        return adjList[u].getLength();
    }
}


void Graph::printAdjVertices(int u)
{
    if(u<0 || u>=nVertices)
    {
        cout<<"Entered vertices is invalid"<<endl;
        return;
    }

    for(int i=0; i<adjList[u].getLength(); i++)

    {
        cout<<adjList[u].getItem(i)<<" ";
    }
    cout<<endl;
}
bool Graph::hasCommonAdjacent(int u,int v)
{
    for(int i=0; i<adjList[u].getLength(); i++)
    {
        for(int j=0; j<adjList[v].getLength(); j++)
        {
            if( adjList[u].getItem(i)==adjList[v].getItem(j));
            {
                return true;
            }
        }
    }
    return false;
}


void Graph::BFS(int source)
{
    if(source<0 || source>=nVertices)
    {
        cout<<"Entered vertices is invalid"<<endl;
        return;
    }
    Queue Q;
    for(int i=0; i<nVertices; i++)
    {
        color[i]=WHITE;
        parent[i]=-1;
        Distance[i]=0;
    }
    Q.Enqueue(source);
    color[source]=GREY;
    cout<<source<<" ";
    while(!Q.Empty())
    {

        int current=Q.Dequeue();
        for(int a=0; a<nVertices; a++)
        {
            if(isEdge(current,a)&& color[a]==WHITE)
            {
                Q.Enqueue(a);
                color[a]=GREY;
                Distance[a]=Distance[current]+1;
                parent[a]=current;
                cout<<a<<" ";
            }
        }
        color[current]=BLACK;
    }
}

int Graph::getDist(int u,int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout<<"Entered vertices is invalid"<<endl;

    }
    else
    {
        cout<<"BFS visited nodes: ";
        auto start = high_resolution_clock::now();
        BFS(u);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout <<"\nTime for BFS:"<<duration.count() <<endl;
        return Distance[v];

    }

}

void Graph::printGraph()
{
    cout<<"\nNumber of vertices:"<<nVertices<<"\nNumber of Edges:"<<nEdges<<endl;
    for(int i=0; i<nVertices; i++)
    {
        cout<<i<<":";
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            cout<<adjList[i].getItem(j)<<"->";

        }
        cout<<endl;
    }
}

void Graph::DFS_visit(int source,int time)
{
    dcolor[source]=GREY;
    time=time+1;
    discovery[source]=time;

    cout<<source<<"  ";
    for(int a=0; a<nVertices; a++)
    {
        if(isEdge(source,a)&& dcolor[a]==WHITE)

        {

            parent[a]=source;

            DFS_visit(a,time);
        }
    }

    dcolor[source]=BLACK;
    time+=1;
    finish[source]=time;


}

void Graph::DFS(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        dcolor[i]=WHITE;
    }
    int time=0;
    cout<<"\nDFS visited nodes:";
    DFS_visit(source,time);
    cout<<endl;



}



Graph::~Graph()
{

    if(adjList)
        delete adjList;
    adjList=0;
    if(parent)
        delete []parent;
    parent=0;
    if(color)
        delete []color;
    color=0;
    if(Distance)
        delete []Distance;
    Distance=0;
}




int main()
{
    int n;
    int choice;
    bool dir;
    cout<<"Enter your choice: \n";
    cout<<"1.Directed graph.....2.Undirected graph"<<endl;
    cin>>choice;
    if(choice==1)
        dir=true;
    else if(choice==2)
        dir==false;
    Graph g(dir);

    cout<<"Statistics?-->press 's' or Normal operation?---> press 'n' "<<endl;
    char com;
    cin>>com;
    if(com=='n')
    {
        cout<<"Enter number of vertices:";
        cin>>n;
        g.setnVertices(n);

    }
    else if(com=='s')
    {
        cout<<"press '11' "<<endl;
    }


    while(1)
    {

        cout<<"1.Add edge"<<endl;
        cout<<"2.Remove Edge"<<endl;
        cout<<"3.Check if Edge"<<endl;
        cout<<"4.Get Degree"<<endl;
        cout<<"5.Check Adjacent Vertices"<<endl;
        cout<<"6.Print Adjacent Vertices"<<endl;
        cout<<"7.getDist between two vertices"<<endl;
        cout<<"8.Print graph"<<endl;
        cout<<"9.DFS(source): "<<endl;
        cout<<"10.Exist"<<endl;
        cout<<"11.Statistics"<<endl;
        int ch;
        cin>>ch;
        if(ch==1)
        {
            cout<<"Add Edge(u,v)"<<endl;
            cout<<"Enter the edges"<<endl;
            int u,v;
            cin>>u;
            cin>>v;

            if(g.addEdge(u,v))
            {
                cout<<"Yes .Edge added"<<endl;
            }
            else
            {
                cout<<"No.Edge added failed because of exist or other "<<endl;
            }

        }
        else if(ch==2)
        {
            cout<<"Remove Edge(u,v)"<<endl;
            cout<<"Enter the edges"<<endl;
            int u,v;
            cin>>u;
            cin>>v;
            g.removeEdge(u,v);

        }
        else if(ch==3)
        {
            cout<<"check if edge(u,v)"<<endl;
            cout<<"Enter the edges"<<endl;
            int u,v;
            cin>>u;
            cin>>v;
            if(g.isEdge(u,v))
            {
                cout<<"Edge exist"<<endl;

            }
            else
            {
                cout<<"No edge"<<endl;

            }
        }
        else if(ch==4)
        {

            cout<<"Get Degree(u)"<<endl;
            int u;

            cin>>u;


            if(!dir)
            {
                cout<<"Degree of u:"<<g.getUndirDegree(u)<<endl;
            }
            else
            {
                cout<<"OutDegree of u: "<<g.getOutDegree(u)<<endl;
                cout<<"InDegree of u: "<<g.getInDegree(u)<<endl;

            }


        }

        else if(ch==5)
        {

            cout<<"check adjacent(u,v)"<<endl;
            int u,v;
            cout<<"Enter the vertices: "<<endl;
            cin>>u;
            cin>>v;
            if(g.hasCommonAdjacent(u,v))
            {
                cout<<"has adjacent vertices"<<endl;

            }
            else
            {
                cout<<"Has no adjacent vertices"<<endl;

            }



        }

        else if(ch==6)
        {

            cout<<"Print adjacent vertices of : "<<endl;
            int u;
            cin>>u;
            cout<<endl;
            g.printAdjVertices(u);
            cout<<endl;

        }
        else if(ch==7)
        {
            cout<<"Shortest distance between (u,v): "<<endl;
            int u,v;
            cin>>u;
            cin>>v;
            cout<<"Shortest distance="<<g.getDist(u,v)<<endl;

        }
        else if(ch==8)
        {
            cout<<"print Graph"<<endl;
            g.printGraph();
        }
        else if(ch==9)
        {

            cout<<"Enter the source node:"<<endl;
            int u;
            cin>>u;

            auto start = high_resolution_clock::now();
            g.DFS(u);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout <<"Time for DFS:"<<duration.count() <<endl;

        }
        else if(ch==10)
        {

            break;
        }

        else if(ch==11)
        {
            cout<<"Enter number of nodes:";
            int v;
            cin>>v;
            g.setnVertices(v);

            int edgelimit=(v*v-v)/8;

            int x=int(log2(edgelimit/v));

            int E[x];

            int RT[10];
            for(int i=0; i<=x; i++)
            {
                E[i]=pow(2,i)*v;


            }


            for(int i=0; i<=x; i++)
            {

                for(int j=0; j<E[i]; j++)
                {

                    int p=rand()%v;
                    int q=rand()%v;
                    g.addEdge(p,q);

                }
                for(int j=0; j<10; j++)
                {
                    int u =rand()%v;
                    cout<<j<<" th:"<<u<<endl;

                    if(u<0 || u>v)
                    {
                        cout<<"Entered vertices is invalid\n"<<endl;

                    }
                    else

                    {
                        cout<<"h1"<<endl;

                        auto start = high_resolution_clock::now();
                        g.BFS(u);
                        cout<<"h2"<<endl;
                        auto stop = high_resolution_clock::now();
                        auto duration = duration_cast<microseconds>(stop - start);
                        cout <<"BFS::Nodes:"<<v<<" and Edges:"<<E[i]<<" Time:"<<duration.count()<<endl;
                        RT[j]=duration.count();



                    }

                }
                int sum=0;
                for(int t=0; t<10; t++)
                {
                    sum+=RT[t];
                }
                cout<<"Average Time:"<<sum/10<<endl;

            }
        }
    }
}


