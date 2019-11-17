# CSCI-2270-


#include "Graph.hpp"
#include <iostream>
#include <string>
using namespace std;

void Graph::addVertex(string name)
{
  bool found = false;
  for (int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i]->name == name)
    {
      found == true;
    }
  }

  if (found == false)
  {
    vertex *ver = new vertex;
    ver-> name = name;
    vertices.push_back(ver);
  }
}

void Graph:: addEdge(string v1, string v2)
{
  for (int i = 0; i < vertices.size(); i++)
  {
    if (vertices[i]-> name == v1)
    {
      for (int j = 0; j < vertices.size(); j++)
      {
        if (vertices[j]->name == v2 && i != j)
        {
          adjVertex e0;
          e0.v = vertices[j];
          vertices[i]->adj.push_back(e0);


          // add the second edge
          adjVertex e1;
          e1.v = vertices[i];
          vertices[j]-> adj.push_back(e1);
        }
      }
    }
  }
}


void Graph::displayEdges()
{
  for (unsigned int i = 0; i < vertices.size(); i++)
  {
    cout << vertices[i]->name << " --> ";

    for (unsigned int j = 0; j < vertices[i]->adj.size(); j++)
    {
        cout << " " << vertices[i]->adj[j].v->name;
    }
    cout <<endl;
  }

}


void Graph::breadthFirstTraverse(string sourceVertex)
{
  vertex* start;
  for (unsigned int i=0; i<vertices.size(); i++)
  {

		if (vertices[i]->name == sourceVertex)
    {

			start = vertices[i];
			cout<< "Starting vertex (root): " << start->name << "-> ";
			break;
		}

	}
  start->visited = true;
  start->distance = 0;
  // queue = new queue();
    queue<vertex*> queue;
	queue.push(start);

  while(!queue.empty())
  {
    vertex* n = queue.front();
    queue.pop();

    for (unsigned int i = 0; i <  n->adj.size(); i++)
    {
      if (!n->adj[i].v->visited)
      {
        n->adj[i].v->visited = true;
        n->adj[i].v->distance = n->distance + 1;
        cout << n->adj[i].v->name <<"("<< n->adj[i].v->distance <<")"<< " ";
        queue.push(n->adj[i].v);
      }
    }
  n-> visited = true;
  }

}

void DFS(int v, bool visited[], vector<vertex*> vertices)
{
    visited[v] = true;

    for ( unsigned int i = vertices[v]->distance; i < vertices[v]->adj.size(); i++)
    {
        if (visited[i] != true)
        {
            cout << "Calling DFS on " << vertices[i]-> name <<endl;
            DFS(i, visited, vertices);
        }
    }
}


int Graph::getConnectedComponents()
{
     bool *visited = new bool[vertices.size()];
    int count = 0;
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
      visited[i] = false;
    }

    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        if (visited[i] == false)
        {
            cout << "visited" <<endl;
            DFS(i, visited, vertices);
            count++;
        }
    }
    return count;
}



bool checkHelper(string sourceVertex, vector<vertex*> &vec)
{
  vertex* start;

  for (unsigned int i = 0; i < vec.size(); i++)
  {
    if (vec[i] -> name == sourceVertex)
    {
      start = vec[i];
    }
  }

  start -> visited = true;
  start -> color = "green";
  queue<vertex*> q;

  q.push(start);

  while(!q.empty())
  {
    vertex* n = q.front();
    q.pop();

    for (unsigned int j = 0; j < n -> adj.size(); j++)
    {
      if (n -> adj[j].v -> visited == false)
      {
        if (n -> color == "red")
        {
          n-> adj[j].v -> color = "green";
        }
        else
        {
          n-> adj[j].v-> color = "red";
        }

        n -> adj[j].v -> visited = true;
        n -> adj[j].v -> distance = n -> distance +1;
        q.push(n-> adj[j].v);
      }
      else
      {
        if (n-> color == n -> adj[j].v -> color)
        {
          return false;
        }
      }
    }
  }
  return true;
}



bool Graph::checkBipartite()
{
  for (unsigned int i = 0; i < vertices.size(); i++)
  {
    vertex* v =  vertices[i];
    bool check;

    if ( v-> visited == false)
    {
      check = checkHelper(v-> name, vertices);
    }
    if (check == false)
    {
      return false;
    }
  }
  return true;


}
