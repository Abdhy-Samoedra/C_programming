#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 26;

struct Node
{
    char name[101];
    int age;
    Node *next, *prev;
};

struct Row
{
    Node *head, *tail;
} *table[SIZE];

Row *createRow()
{
    Row *row = (struct Row *)malloc(sizeof(Row));
    row->head = row->tail = 0;
    return row;
}

Node *createNode(char name[], int age)
{

    Node *node = (struct Node *)malloc(sizeof(struct Node));
    strcpy(node->name, name);
    node->age = age;
    node->next = node->prev = 0;
    return node;
}

int hash(char *name)
{
    char c = name[0];
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A';
    }
    else if (c >= 'a' && c <= 'z')
    {
        return c - 'a';
    }
    return c % SIZE;
}

void insertNode(char *name, int age)
{
    int key = hash(name);

    if (table[key] == 0)
    {
        // laci tak ada, data tidak ada
        table[key] = createRow();
        table[key]->head = table[key]->tail = createNode(name, age);
        return;
    }

    Node *node = createNode(name, age);
    node->prev = table[key]->tail;
    table[key]->tail->next = node;
    table[key]->tail = node;
}

void deleteNode(char *name)
{
    int key = hash(name);

    if (table[key] == 0)
    {
        printf("%s not found\n", name);
        return;
    }
    if (strcmp(table[key]->head->name, name) == 0)
    {
        if (table[key]->head == table[key]->tail)
        {
            free(table[key]->head);
            table[key]->head = table[key]->tail = 0;
            free(table[key]);
            table[key] = 0;
        }
        else
        {
            Node *temp = table[key]->head;
            table[key]->head = table[key]->head->next;
            table[key]->head->prev = 0;
            free(temp);
            temp = 0;
        }
    }
    else if (strcmp(table[key]->tail->name, name) == 0)
    {
        Node *temp = table[key]->tail;
        table[key]->tail = table[key]->tail->prev;
        table[key]->tail = table[key]->tail->prev;
        table[key]->tail->next = 0;
        free(temp);
    }
    else
    {
        Node *curr = table[key]->head;

        while (curr == table[key]->tail && strcmp(curr->name, name) != 0)
        {
            curr = curr->next;
        }

        if (curr == table[key]->tail)
        {
            printf("%s not found\n", name);
            return;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        free(curr);
        curr = 0;
    }
}

void view()
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d. ", i);
        Row *row = table[i];
        if (row)
        {
            Node *curr = row->head;
            while (curr)
            {
                printf("%s - %d -> ", curr->name, curr->age);
                curr = curr->next;
            }
            printf("\n");
        }
        else
        {
            printf("-\n");
        }
    }
}

int main()
{

    insertNode("budi", 20);
    insertNode("clara", 20);
    insertNode("abel", 20);
    insertNode("abdul", 20);
    insertNode("albert", 20);
    insertNode("andre", 20);
    insertNode("bjox", 20);

    deleteNode("clara");
    //	deleteNode("abdul");
    //	deleteNode("budi");
    //	deleteNode("abel");
    //

    //	for(int i=0;i<35;i++){
    //		char name[20];
    //		sprintf(name, "budi %d",i);
    //		insertNode(name,20);
    //	}

    view();

    return 0;
}