#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "algo.h"

pnode findNode(pnode head, int nodenum)
{
    while (head!=NULL&& head->node_num != nodenum)
    {
        head = head->next;
    }
    if (head==NULL)
        return NULL;
    return head;
}

void insertEdge(pnode scr, pnode des, int weight)
{
    if (scr==NULL || des==NULL) {
        return;
    }
    pedge newedge = (pedge)malloc(sizeof(edge));
    if(newedge == NULL){
        printf("fail to alloc memory\n");
        return;
    }
    newedge->next = NULL;
    newedge->weight = weight;
    newedge->endpoint = des;
    pedge tempedge =scr->edges;
    if(tempedge==NULL){
        scr->edges=newedge;
        return;
    }
    while (tempedge->next!=NULL){
        tempedge=tempedge->next;
    }
    tempedge->next=newedge;
}

char BuildGrapgh(pnode *head)
{
    char ch;
    if (*head!=NULL) {
        deleteGraph(head);
    }
    int size;
    scanf("%d", &size);
    pnode *headnode = head;
    for (int i = 0; i < size; i++)
    {
        pnode newnode = (pnode)malloc(sizeof(node));
        if(newnode == NULL){
            printf("fail to alloc memory\n");
            return;
        }
        newnode->next = NULL;
        newnode->node_num = i;
        newnode->edges = NULL;
        *headnode = newnode;
        headnode = &(*headnode)->next;
    }

    while (scanf(" %c", &ch) > 0)
    {
        if (ch == 'n')
        {
            int nodenum , weight, des;
            scanf("%d", &nodenum);
            pnode scrnode = findNode(*head, nodenum);
            while (scanf("%d", &des ) > 0)
            {
                scanf("%d",&weight);
                pnode desnode=findNode(*head, des);
                insertEdge(scrnode, desnode, weight);
            }
        }
        else
        {
            break;
        }
    }
    return ch;
}

void deleteGraph(pnode *head)
{
    pnode temp = *head;
    while (temp!=NULL)
    {
        pedge edge = temp->edges;
        while (edge!=NULL)
        {
            pedge deledge=edge;
            edge=edge->next;
            free(deledge);
        }
        temp->edges=NULL;
        pnode delnode=temp;
        temp=temp->next;
        free(delnode);
    }
    *head=NULL;
}

void printGraph(pnode head){
    while (head!=NULL)
    {
        printf("node : %d \n", head->node_num);
        if (head == NULL) {
            break;
        }
        pedge edge = head->edges;
        while (edge!=NULL)
        {
            printf("%d ---> %d weight %d , ",head->node_num ,edge->endpoint->node_num, edge->weight);
            edge = edge->next;
        }
        printf("\n\n");
        head = head->next;
    }
    printf("\n\n\n");
}
void deleteNodeEdge(pnode *head){
    pnode temp=*head;
    pedge edge = temp->edges;
    while (edge!=NULL)
    {
        pedge deledge=edge;
        edge=edge->next;
        free(deledge);
    }
    temp->edges=NULL;
}

void insertNode(pnode *head) {
    int nodenum = -1;
    int maxid = maxNumOfVertex(*head);
    scanf("%d", &nodenum);
    pnode newnode = NULL;
    newnode = findNode(*head, nodenum);
    if (newnode != NULL) {
        deleteNodeEdge(&newnode);
    } else {
        newnode = (pnode) malloc(sizeof(node));
        if(newnode == NULL){
            printf("fail to alloc memory\n");
            return;
        }
        pnode nextnode = NULL;
        int i=1;
        while (nextnode==NULL&&nodenum+i < maxid ) {
            nextnode = findNode(*head, nodenum + i++);
        }
        newnode->next = nextnode;
        newnode->node_num = nodenum;
        newnode->edges = NULL;
        pnode prenode = NULL;
        i=1;
        while (prenode==NULL&&nodenum-i>0) {
            prenode = findNode(*head, nodenum - i++);
        }
        if(prenode!=NULL){
            prenode->next=newnode;
        } else{
            *head=newnode;
        }
    }
    int weight, des;
    while (scanf("%d %d", &des, &weight) > 1) {
        pnode desnode = findNode(*head, des);
        insertEdge(newnode, desnode, weight);
    }
}

void deleteEdgeToNode(pnode head, int nodenum){
    while (head!=NULL)
    {
        if (head == NULL) {
            break;
        }
        pedge edge = head->edges;
        if(edge!=NULL&&edge->endpoint->node_num==nodenum){
            pedge temp =edge;
            head->edges=edge->next;
            free(temp);
            edge=head->edges;
        }
        while (edge!=NULL&&edge->next!=NULL)
        {
            if(edge->next->endpoint->node_num!=nodenum) {
                edge = edge->next;
            } else{
                pedge deledge = edge->next;
                edge->next=deledge->next;
                free(deledge);
            }
        }
        head = head->next;
    }
}
void deleteNode(pnode *head){
    int nodenum=-1;
    scanf("%d", &nodenum);
    pnode delnode = NULL;
    delnode = findNode(*head, nodenum);
    if(delnode==NULL){
        return;
    }
    deleteNodeEdge(&delnode);
    deleteEdgeToNode(*head,nodenum);
    pnode prev = NULL;
    pnode current = *head;
    while (current != NULL && current->node_num != nodenum) {
        prev = current;
        current = current->next;
    }
    if(prev!=NULL){
        prev->next=delnode->next;
    } else{
        *head=delnode->next;
    }
    free(delnode);
}