#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100




struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};




struct Stack {
    struct Node* items[MAX_STACK_SIZE];
    int top;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}


int isEmpty(struct Stack* stack) {
    return (stack->top == -1);
}


void push(struct Stack* stack, struct Node* item) {
    if (stack->top == MAX_STACK_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->items[++stack->top] = item;
}

struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}


struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}


struct Node* findMin(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}


struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
 
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

    
        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}


void inOrderTraversal(struct Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}


void preOrderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}


void postOrderTraversal(struct Node* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}
//without recurrsion
struct Node* insertwr(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    struct Node* current = root;
    struct Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            // Duplicate value, do not insert
            return root;
        }
    }

    struct Node* newNode = createNode(value);
    if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}



struct Node* deleteNodewr(struct Node* root, int value) {
    struct Node* current = root;
    struct Node* parent = NULL;

    while (current != NULL && current->data != value) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        // Node with the given value not found
        return root;
    }

    if (current->left == NULL) {
        struct Node* temp = current->right;
        free(current);
        if (parent == NULL) {
            return temp;
        }
        if (current == parent->left) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
    } else if (current->right == NULL) {
        struct Node* temp = current->left;
        free(current);
        if (parent == NULL) {
            return temp;
        }
        if (current == parent->left) {
            parent->left = temp;
        } else {
            parent->right = temp;
        }
    } else {
        struct Node* successor = findMin(current->right);
        current->data = successor->data;
        current->right = deleteNode(current->right, successor->data);
    }

    return root;
}

void inOrderTraversalwr(struct Node* root) {
    if (root == NULL)
        return;

    struct Stack* stack = createStack();
    struct Node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }

        current = pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }

    free(stack);
}

void preOrderTraversalwr(struct Node* root) {
    if (root == NULL)
        return;

    struct Stack* stack = createStack();
    push(stack, root);

    while (!isEmpty(stack)) {
        struct Node* current = pop(stack);
        printf("%d ", current->data);

        // Push right child first to ensure left child is processed first (LIFO)
        if (current->right != NULL)
            push(stack, current->right);    
        if (current->left != NULL)
            push(stack, current->left);
    }

    free(stack);
}

void postOrderTraversalwr(struct Node* root) {
    if (root == NULL)
        return;

    struct Stack* stack1 = createStack();
    struct Stack* stack2 = createStack();

    push(stack1, root);

    while (!isEmpty(stack1)) {
        struct Node* current = pop(stack1);
        push(stack2, current);

        if (current->left != NULL)
            push(stack1, current->left);
        if (current->right != NULL)
            push(stack1, current->right);
    }

    // Print nodes from the second stack in reverse order
    while (!isEmpty(stack2)) {
        printf("%d ", pop(stack2)->data);
    }

    free(stack1);
    free(stack2);
}


int main() {
    
    int c;
    
    struct Node* root = NULL;

    
  
while(1)
{
    printf("#1 In-order traversal: \n");
 printf("#2 Pre-order traversal: \n");
   printf("#3 Post-order traversal: \n");
      printf("#4 delete: \n");
         printf("#5 insert: \n");
                  printf("#6 insert without recurrsion: \n");
         printf("#7 delete without recurreion: \n");
          printf("#8 inorder ecurreion: \n");
           printf("#9 preorder without recurreion: \n");
           printf(" # 10 postorder without recurreion: \n");

 printf("enter choice: ");
scanf("%d",&c);
    int d;
    
    switch(c)
    {
        case 1:inOrderTraversal(root);
                printf("\n");
                break;
        case 2: preOrderTraversal(root);
                printf("\n");
                break;
        case 3: postOrderTraversal(root);
                 printf("\n");
                 break;
        case 4: printf("enter the number to be  deleted");
                scanf("%d",&d);
        root = deleteNode(root, d);
          inOrderTraversal(root);
    printf("\n");
        break;
        
        // case 5:  {
        //             int e;
        //             printf("Enter the number to be inserted: ");
        //             scanf("%d", &e);
        //             root = insert(root, e);
        //             printf("In-order traversal after insertion: ");
        //             inOrderTraversal(root);
        //             printf("\n");
        //         }
                
           case 5:     {int e;
                    for(int i=0;i<5;i++)
                    {
                        printf("Enter the number to be inserted: ");
                    scanf("%d", &e);
                    root = insert(root, e);
                    }
                    printf("In-order traversal after insertion: ");
                    inOrderTraversal(root);
                    printf("\n");
                }
                break;
                case 6:{int e;
                    for(int i=0;i<5;i++)
                    {
                        printf("Enter the number to be inserted: ");
                    scanf("%d", &e);
                    root = insertwr(root, e);
                    }
                    printf("In-order traversal after insertion: ");
                    inOrderTraversal(root);
                    printf("\n");
                }
                break;
                
        case 7:
        deleteNodewr(root, d);
          inOrderTraversal(root);
    printf("\n");
    break;
      case 8:
                printf("In-order traversal without recursion: ");
                inOrderTraversalwr(root);
                printf("\n");
                break;
                  case 9:
                printf("In-order traversal without recursion: ");
                preOrderTraversalwr(root);
                printf("\n");
                break;
                  case 10:
                printf("In-order traversal without recursion: ");
                postOrderTraversalwr(root);
                printf("\n");
                break;
        default:printf("invalid\n");
   
    }
}
    return 0;
}




