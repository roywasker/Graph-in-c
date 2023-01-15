#include <stdio.h>
#include <stdlib.h>
#include "algo.h"

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
void add(linnode **head, int nodenum , int weight){
    linnode *newnode = (linnode*)malloc(sizeof(linnode));
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
    //free(newnode);
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

/*void printList(linnode* head) {
    linnode* current = head;
    while (current != NULL) {
        printf("Node number: %d, weight: %d\n", current->nodenum, current->weight);
        current = current->next;
    }
    printf("\n");
}*/

int dijkstra(pnode head, int scr ,int des , int numofvertex){
    int result=-1;
    if(head == NULL){
        return result;
    }
    linnode *queue = NULL;
    pnode currnode = NULL;
    int *pnode =(int*) malloc(sizeof (int)*numofvertex);
    int *pdist =(int*) malloc(sizeof (int)*numofvertex);
    int *prev =(int*) malloc(sizeof (int)*numofvertex);
    int *pvisited =(int*) malloc(sizeof (int)*numofvertex);
    for (int i = 0; i <numofvertex; ++i) {
        pnode[i] = i;
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
    free(pnode);
    free(pdist);
    free(prev);
    free(pvisited);
    return result;
}