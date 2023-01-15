#ifndef _ALGO_H_
#define _ALGO_H_

#include "graph.h"

typedef struct Node {
    int nodenum;
    int weight;
    struct Node* next;
}linnode, *plinnode;

void shortsPath(pnode head);
void add(linnode **head, int nodenum , int weight);
int pop(linnode **head);
int maxNumOfVertex(pnode head);
int dijkstra(pnode head, int scr ,int des ,int numofvertex);

#endif