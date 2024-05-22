#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* head = NULL;
struct node* second = NULL;
struct node* third = NULL;

void insert_start() {
    int data;

    scanf("%d", &data);

    struct node* new = (struct node*)malloc(sizeof(struct node));
    new->data = data;
    new->next = head;
    head = new;

 
}


void create_linked_list() {
    head = (struct node*)malloc(sizeof(struct node));
    second = (struct node*)malloc(sizeof(struct node));
    third = (struct node*)malloc(sizeof(struct node));

    head->data = 10;
    head->next = second;

    second->data = 15;
    second->next = third;

    third->data = 20;
    third->next = NULL;
}


void insert_end() {
    int data;

    scanf("%d", &data);

    struct node* new = (struct node*)malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;

    struct node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new;

}
void insert_middle(int data, int pos)
{
    int i;
    struct node *newNode, *temp;

    newNode = (struct node*)malloc(sizeof(struct node));

    if(newNode == NULL)
    {
        printf("null");
    }
    else
    {
        newNode->data = data; 
        newNode->next = NULL;

        temp = head;

   
        for(i=2; i<=pos-1; i++)
        {
            temp = temp->next;

            if(temp == NULL)
                break;
        }

        if(temp != NULL)
        {

            newNode->next = temp->next; 

            temp->next = newNode;

          
        }
        else
        {
            printf("null");
        }
    }
}


void delete_start() {
    if (head == NULL) {
        printf("empty");
        return;
    }
    struct node* temp = head;
    head = head->next;
    free(temp);

  
}

void delete_end() {
    if (head == NULL) {
        printf("empty");
        return;
    }
    struct node* current = head;
    struct node* prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    if (prev == NULL) {
        head = NULL;
    } else {
        prev->next = NULL;
    }
    free(current);


}

void delete_middle() {
    if (head == NULL) {
        printf("empty");
        return;
    }
    int data;
    scanf("%d", &data);
    struct node* current = head;
    struct node* prev = NULL;
    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("not found");
        return;
    }
    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}
void display() {
    struct node* current = head;
    if (current == NULL) {
        printf("empty");
        return;
    }

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}


void search() {
int data;

scanf("%d", &data);
  struct node* current = head;
int pos = 1;
while (current != NULL && current->data != data) {
    current = current->next;
    pos++;
}
if (current == NULL) {
    printf("not found");
} else {
    printf("present");
}
  }

int main() {
create_linked_list();
int choice;
do {

  scanf("%d", &choice);
      switch (choice) {
        case 1:
            insert_start();
            break;
        case 2:
            insert_end();
            break;
        case 3:
            insert_middle(17,3);
            break;
        case 4:
            delete_start();
            break;
        case 5:
            delete_end();
            break;
        case 6:
            delete_middle();
            break;
        case 7:
            display();
            break;
        case 8:
            search();
            break;
        case 9:
           
            break;
    
           
    }
} while (choice != 9);

return 0;
}