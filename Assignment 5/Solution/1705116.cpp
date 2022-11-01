#define INF 99999
#include<iostream>
using namespace std;



void floydWarshall (int G[][],int V)
{

    int dist[V][V], i, j, k;
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] =G[i+1][j+1];

    for (k = 0; k < V; k++)
    {

        for (i = 0; i < V; i++)
        {

            for (j = 0; j < V; j++)
            {

                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }



}



int main()
{


    int V,E;
    cin>>V>>E;
    int G[v+1][v+1];
    for(int i=1;i<=V;i++)
    {
        for(int j=1;j<=V;j++)
        {
            G[i][j]=INF;
        }
    }
    for(int i=1;i<=E;i++)
    {
        int V1,E1,w;
        cin>>V1>>E1>>w;
        G[V1][E1]=w;
    }


    floydWarshall (&G,V);


}


