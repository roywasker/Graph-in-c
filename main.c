#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "algo.h"

int main(){
    char ch =' ';
    pnode head =NULL;
    int flag=0;
    while (1)
    {
        if(flag==0) {
            ch = getchar();
        }
        flag=0;
        if (ch==EOF)
        {
            break;
        }
        else if (ch=='A')
        {
            ch=BuildGrapgh(&head);
            flag=1;
            printGraph(head);
        }
        else if(ch=='B'){
            insertNode(&head);
            printGraph(head);
        } 
        else if(ch=='D'){
            deleteNode(&head);
            printGraph(head);
        } 
        else if(ch=='S'){
            shortsPath(head);
        }
        else if(ch=='T'){
            
        }     
    }
    deleteGraph(&head);
    return 0;
}