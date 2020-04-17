/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"
#include <unistd.h>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
    vector<vector<double>> dist;
    vector<vector<Vertex<T>*> > pred;

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	for (auto &v : vertexSet){
	    v->dist=INT64_MAX;
	    v->path= NULL;
	}
    Vertex<T> *s = findVertex(orig);
	s->dist=0;

	queue<Vertex<T>*> Q;
	Q.push(s);
	while(!Q.empty()){
	    Vertex<T> *tmp = Q.front();
	    Q.pop();
	    for (auto &w : tmp->adj){
	        if(w.dest->dist==INT64_MAX){
	            Q.push(w.dest);
	            w.dest->dist=tmp->dist +1;
	            w.dest->path=tmp;
	        }
	    }
	}
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for (auto &v : vertexSet){
        v->dist=INT64_MAX;
        v->path= NULL;
    }
    Vertex<T> *s = findVertex(origin);
    s->dist=0;

    MutablePriorityQueue<Vertex<T> > Q;
    Q.insert(s);

    while(!Q.empty()){
        Vertex<T> *tmp = Q.extractMin();
        for (auto &w : tmp->adj){
            if(w.dest->dist>tmp->dist + w.weight){
                w.dest->dist=tmp->dist + w.weight;
                w.dest->path=tmp;
                if (!Q.inQueue(w.dest))
                    Q.insert(w.dest);
                else
                    Q.decreaseKey(w.dest);

            }
        }
    }

}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    for (auto &v : vertexSet){
        v->dist=INT64_MAX;
        v->path= NULL;
    }
    Vertex<T> *s = findVertex(orig);
    s->dist=0;

    for(int i=1;i<=vertexSet.size()-1;i++){
        for (auto &v : vertexSet){
            for(auto&w : v->adj){
                if(w.dest->dist>v->dist + w.weight){
                    w.dest->dist=v->dist+w.weight;
                    w.dest->path=v;
                }
            }
        }
    }
    for (auto &v : vertexSet){
        for(auto&w : v->adj){
            if(w.dest->dist>v->dist + w.weight){
                cout << "There are cycles of negative weight\n";
            }
        }
    }

}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	Vertex<T>*VertexBehind = findVertex(dest)->path;
	while(VertexBehind!=NULL){
	    res.push_back(VertexBehind->info);
        VertexBehind=VertexBehind->getPath();
	}
	reverse(res.begin(),res.end());
	res.push_back(dest);
	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    dist.clear();
	dist= vector<vector<double>>(vertexSet.size(), vector<double>(vertexSet.size(), INT64_MAX));
	pred.clear();
	pred= vector<vector<Vertex<T>*>>(vertexSet.size(), vector<Vertex<T>*>(vertexSet.size(), NULL));

	for (int i=0; i<dist.size();i++){
	    dist[i][i]=0;
	}

	for (int v=0;v<vertexSet.size();v++){
	    for(int e=0;e< vertexSet[v]->adj.size();e++){
            for (int ve=0;ve<vertexSet.size();ve++) { // encontrar qual o index do vertice de destino no adj
                if (vertexSet[ve]==vertexSet[v]->adj[e].dest){
                    dist[v][ve]=vertexSet[v]->adj[e].weight;
                    pred[v][ve]=vertexSet[v];
                }
            }
	    }
	}

	for (int k=0;k<vertexSet.size();k++){
	    for(int i=0;i<vertexSet.size();i++){
	        for(int j=0;j<vertexSet.size();j++){
	            if(dist[i][j]>dist[i][k]+dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
	        }
	    }
	}

	/* printing pred
	for(int i=0;i<pred.size();i++){
	    for(int j=0;j<pred.size();j++) {
	        if(i!=j)
                cout << pred[i][j]->getInfo() << " ";
            else
                cout << 0 << " ";
        }
	    cout << endl;
	}*/


}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
    int indexDest, indexOrig;

    for (int i=0; i<vertexSet.size();i++){
        if(vertexSet[i]==findVertex(dest)){
            res.push_back(vertexSet[i]->info);
            indexDest=i;
        }
        else if(vertexSet[i]==findVertex(orig)){
            indexOrig=i;
        }
    }
    Vertex<T> * before = pred[indexOrig][indexDest];
    res.push_back(before->getInfo());
    while(before!=findVertex(orig)){
        for (int i=0; i<vertexSet.size();i++){
            if(vertexSet[i]==findVertex(before->getInfo())) {
                before = pred[indexOrig][i];
                res.push_back(before->getInfo());
                break;
            }
        }
    }
    reverse(res.begin(),res.end());
	return res;
}


#endif /* GRAPH_H_ */
