#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
#define debug(x)    x
// print value of debug variable
//#define debug(x)    clog << #x << " = " << x << endl

// print a debug string
#define debugs(str) //clog << str << endl
#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define repd(a, b)   for(int a = 0; a < (b); debug(++a))
#define all(a)      (a).begin(),(a).end()

using namespace std;

////////////////////////////// I/O /////////////////////////
#define BASE 10
#define OUTPUT_LENGTH 10
#define BUFFER_SIZE 1024

// buffer stdin
char inputbuffer[BUFFER_SIZE];

int c;
bool negative_input;
// read a number from stdin into var
#define readn(var)  var = 0;                                \
                    c = fgetc(stdin);                       \
                    if (c == '-') {                         \
                        negative_input = true;              \
                        c = fgetc(stdin);                   \
                    } else negative_input = false;          \
                    while (true) {                          \
                        if (c < '0') break;                 \
                        var = var * 10 + (c - '0');         \
                        c = fgetc(stdin);                   \
                    }                                       \
                    if (negative_input) var = -var;         \
                    debug(var);

// create output buffer
char outputbuffer[OUTPUT_LENGTH];

// write var as number to stdout
#define write(var) if (var == 0) { \
    putc('0', stdout); \
    }else{ \
    char pos = OUTPUT_LENGTH; \
    while (var != 0) { \
        char rem = var % BASE; \
        var = var/BASE; \
        outputbuffer[--pos] = rem + '0'; \
    } \
    for (char p = pos; p < OUTPUT_LENGTH; p++ ) { \
        putc(outputbuffer[p], stdout); \
    } \
}   \
putc('\n', stdout);

////////////////////////////// Graph ///////////////////////
typedef struct Edge tEdge;
typedef struct Vertex tVertex;
typedef struct Graph tGraph;

struct Edge {
    int weight;
    tVertex* vertices[2];
/*
// cannot be disabled for sorting
    Edge() {};

private:
    Edge(const Edge&);   */ 
};


struct Vertex {
    short elevation;
    tVertex* parent;

// disable the following for e.g. sorting
    Vertex() {};

private:
    Vertex(const Vertex&); // non-copyable, C++98 style
};

#define debugEdge(pedge)        debug(pedge);                                                       \
                                debug(pedge->weight);                                               \
                                debugVertex(pedge->vertices[0]);                                    \
                                debugVertex(pedge->vertices[1]);

#define debugVertex(pvertex)    debug(pvertex);                                                     \
                                debug(pvertex->elevation);                                          \
                                debug(pvertex->parent);

// get the set of a vertex by following its parents
#define getSet(pvertex)         while(pvertex != pvertex->parent) {                                 \
                                    debugVertex(pvertex); pvertex = pvertex->parent;                \
                                }

// make set_a a subset of set_b and update the whole hierarchy to set_b as parent, starting at pvertex_upd
#define joinSets(pvertex_a, pvertex_b, pvertex_upd)     tVertex *bufferSet;                         \
                                                        pvertex_a->parent = pvertex_b;              \
                                                        pvertex_a = pvertex_upd;                    \
                                                        while (pvertex_a->parent != pvertex_b) {    \
                                                            bufferSet = pvertex_a;                  \
                                                            pvertex_a = pvertex_a->parent;          \
                                                            bufferSet->parent = pvertex_b;          \
                                                        }

struct Graph {
    tVertex* vertices;
    tEdge* edges;
};

#define debugGraph(g, vertexc, edgec)   rep(v, vertexc) {                                           \
                                            tVertex* pvertex = &g.vertices[v];                      \
                                            debugVertex(pvertex);                                   \
                                        }                                                           \
                                        rep(e, edgec) {                                             \
                                            tEdge* pedge = &g.edges[e];                             \
                                            debugEdge(pedge);                                       \
                                        }

tGraph graph;

// sort edges ascending
// example usage: sort(graph.edges, graph.edges + pathsc, EdgeWeightSorter);
bool EdgeWeightSorter(const tEdge& a, const tEdge& b) { return a.weight < b.weight; }

////////////////////////////// Task ////////////////////////

int main(int argc, char* argv[]) {
    //ios_base::sync_with_stdio(false); // do not mix up c with c++ IO !
    //cin.tie(NULL);                    // manually flush cout
    //cout.precision(10);
    setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

    short citiesc;

    readn(citiesc);
    graph.vertices = new tVertex[citiesc];

    int pathsc;
    readn(pathsc);
    graph.edges = new tEdge[pathsc];

    rep(city, citiesc) {
        short elevation;
        readn(elevation);
        tVertex *pvertex = &graph.vertices[city];
        pvertex->elevation = elevation;
        pvertex->parent = pvertex;
        debugVertex(pvertex);
    }
    
    rep(path, pathsc) {
        short start = 0, end = 0;
        readn(start);
        readn(end);
        tVertex *pstart = &graph.vertices[start];
        tVertex *pend = &graph.vertices[end];

        short elevation = pend->elevation - pstart->elevation;
        if (elevation < 0) elevation = -elevation;

        debug(elevation);
        graph.edges[path].weight = elevation;
        graph.edges[path].vertices[0] = pstart;
        graph.edges[path].vertices[1] = pend;
    }

    sort(graph.edges, graph.edges + pathsc, EdgeWeightSorter);
    debugs("sorted");
    debugGraph(graph, citiesc, pathsc);

    int accumulatedWeight = 0;

    //////// MST /////// KRUSKAL ///////////
    tVertex *startSet, *endSet;
    rep(path, pathsc) {
        tEdge *edge = &graph.edges[path];
        debugEdge(edge);
        
        startSet = edge->vertices[0];
        getSet(startSet);
        
        endSet = edge->vertices[1];
        getSet(endSet);

        if (startSet != endSet) {
            accumulatedWeight += edge->weight;
            joinSets(startSet, endSet, edge->vertices[0]);
        }
    }

    write(accumulatedWeight);

    //cout.flush();
    return 0;
}
