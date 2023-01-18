#include <stdio.h>
#include <stdlib.h>
#include "algo.h"
#include "string.h"

#define maxint 2147483647

void shortsPath(pnode head){
    if(head == NULL){
        return;
    }
    int scr=-1 , des=-1 ,shortsPath=-1;
    scanf("%d %d",&scr , &des);
    int numofvertex= maxNumOfVertex(head);
    shortsPath = dijkstra(head,scr,des ,numofvertex+1);
    if(shortsPath==-1){
        printf("Dijsktra shortest path: -1 \n");
        return;
    }
    printf("Dijsktra shortest path: %d \n",shortsPath);
}

int dijkstra(pnode head, int scr ,int des , int numofvertex){
    int result=-1;
    if(head == NULL){
        return result;
    }
    linnode *queue = NULL;
    pnode currnode = NULL;
    int *pdist =(int*) malloc(sizeof (int)*numofvertex);
    int *prev =(int*) malloc(sizeof (int)*numofvertex);
    int *pvisited =(int*) malloc(sizeof (int)*numofvertex);
    if(pdist == NULL||prev == NULL||pvisited == NULL){
        printf("fail to alloc memory\n");
        exit(1);
    }
    for (int i = 0; i <numofvertex; ++i) {
        pdist[i] = maxint;
        prev[i] = -1;
        pvisited[i] = 0;
        if (findNode(head, i) == NULL) {
            pvisited[i] = 1;
        }
    }
    pdist[scr]=0;
    add(&queue ,scr ,0);
    while (queue!=NULL){
        int n = pop(&queue);
        currnode = findNode(head , n);
        pvisited[currnode->node_num]=1;
        pedge edge = currnode->edges;
        while (edge!=NULL){
            if(pvisited[edge->endpoint->node_num]==1) {
                edge=edge->next;
                continue;
            }
            int newdist = pdist[currnode->node_num] + edge->weight;
            if(newdist < pdist[edge->endpoint->node_num]){
                pdist[edge->endpoint->node_num]=newdist;
                int test =edge->endpoint->node_num;
                add(&queue , test,newdist);
                prev[edge->endpoint->node_num] = currnode->node_num;
            }
            edge=edge->next;
        }
    }
    result = pdist[des];
    free(pdist);
    free(prev);
    free(pvisited);
    if (result == maxint){
        return -1;
    }
    return result;
}

void add(linnode **head, int nodenum , int weight){
    linnode *newnode = (linnode*)malloc(sizeof(linnode));
    if(newnode == NULL){
        printf("fail to alloc memory\n");
        return;
    }
    newnode->next = NULL;
    newnode->weight = weight;
    newnode->nodenum = nodenum;
    if(*head == NULL || (*head)->weight > weight) {
        newnode->next = *head;
        *head = newnode;
        return;
    }

    linnode *current = *head;
    while(current->next != NULL && current->next->weight < weight) {
        current = current->next;
    }

    newnode->next = current->next;
    current->next = newnode;
}

int pop(linnode **head){
    int nodenum = -1;
    if(*head == NULL){
        return nodenum;
    }
    linnode *delnode = *head;
    nodenum=(*head)->nodenum;
    *head=(*head)->next;
    free(delnode);
    return nodenum;
}

int maxNumOfVertex(pnode head){
    int max=0;
    while (head!=NULL){
        if(head->node_num > max){
            max =head->node_num;
        }
        head=head->next;
    }
    return max;
}

void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void TSP(pnode head)
{
    int shortpath =maxint;
    int *pshortpath = &shortpath;
    int size=0;
    scanf("%d", &size);

    int *arr = (int *)(calloc(size, sizeof(int)));
    if(arr == NULL){
        printf("fail to alloc memory\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    permotion(head,0, arr, size ,pshortpath);
    free(arr);

    if (shortpath == maxint)
    {
        shortpath = -1;
    }
    printf("TSP shortest path: %d \n", shortpath);
}

void permotion(pnode head , int start, int *arr, int size , int *shortpath)
{
    if (start == size - 1)
    {
        miniperm( head, arr, size,shortpath);
        return;
    }
    for (int i = start; i < size; ++i)
    {
        swap(arr, start, i);
        permotion( head, start + 1, arr, size,shortpath);
        swap(arr, start, i);
    }
}

void miniperm(pnode head , int *arr, int size,int *shortpath)
{
    int maxid = maxNumOfVertex(head);
    int temp = 0;
    for (int i = 0; i < size - 1; i++)
    {
        int path = dijkstra(head, arr[i], arr[i + 1],maxid+1);
        if (path == -1)
        {
            return;
        }
        temp += path;
    }
    if (temp < *shortpath)
    {
        *shortpath = temp;
    }
}