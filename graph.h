#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

pnode findNode(pnode head, int nodenum);
char BuildGrapgh(pnode *head);
void insertNode(pnode *head);
void deleteNode(pnode *head);
void printGraph(pnode head); //for self debug
void deleteGraph(pnode *head);
void shortsPath(pnode head);
void TSP(pnode head);
void deleteEdgeToNode(pnode head, int nodenum);
void insertEdge(pnode scr, pnode des, int weight);
void deleteNodeEdge(pnode *head);

#endif
