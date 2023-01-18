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
void swap(int *arr, int i, int j);
void miniperm(pnode head , int *arr, int size,int *shortpath);
void permotion(pnode head , int start, int *arr, int size , int *shortpath);
void TSP(pnode head);

#endif