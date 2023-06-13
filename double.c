#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dlistnode {
    char name[20];
    struct dlistnode* llink;
    struct dlistnode* rlink;
} dlistnode;

void init(dlistnode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

void print_dlist(dlistnode* phead, dlistnode* current) {
    dlistnode* p;
    for (p = phead->rlink; p != phead; p = p->rlink) {
        if (p == current)
            printf("| [0]%s | -> ", p->name);
        else
            printf("| %s | -> ", p->name);
    }
    printf("\n");
}

void dinsert(dlistnode* before, const char* name) {
    dlistnode* newnode = (dlistnode*)malloc(sizeof(dlistnode));
    strcpy(newnode->name, name);
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void delete(dlistnode* head, dlistnode* removed) {
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

int main(void) {
    dlistnode* head = (dlistnode*)malloc(sizeof(dlistnode));
    init(head);

    char menu;
    char fruitName[20];
    dlistnode* current = head;

    while (1) {
        printf("**** MENU ****\n");
        printf("n) next fruit\n");
        printf("p) previous fruit\n");
        printf("d) delete the current fruit\n");
        printf("i) insert fruit after current fruit\n");
        printf("o) output the fruit list\n");
        printf("e) exit the program\n\n");
        printf("****************\n");
        printf("Enter the menu: ");
        scanf(" %c", &menu);

        switch (menu) {
        case 'n':
            if (current->rlink != head)
                current = current->rlink;
            break;
        case 'p':
            if (current->llink != head)
                current = current->llink;
            break;
        case 'd':
            if (current != head) {
                dlistnode* temp = current;
                current = current->llink;
                delete(head, temp);
            }
            break;
        case 'i':
            printf("Enter the fruit name to insert: ");
            scanf("%s", fruitName);
            dinsert(current, fruitName);
            current = current->rlink;
            break;
        case 'o':
            printf("Fruit list:\n");
            print_dlist(head, current);
            break;
        case 'e':
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid menu option.\n");
            break;
        }
    }

    return 0;
}
