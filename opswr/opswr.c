#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* CreateNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct node* insert(struct node* root, int value) {
    struct node* newNode = CreateNode(value);
    if (root == NULL) {
        return newNode;
    }

    struct node* current = root;
    struct node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            free(newNode);  // Value already exists in the tree
            return root;
        }
    }

    if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

void InOrderTraversal(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct node* stack[100];
    int top = -1;
    struct node* current = root;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

void Mirror(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct node* current = stack[top--];
        struct node* temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left) {
            stack[++top] = current->left;
        }
        if (current->right) {
            stack[++top] = current->right;
        }
    }
}

int CountNode(struct node* root) {
    if (root == NULL) {
        return 0;
    }

    struct node* stack[100];
    int top = -1;
    int count = 0;
    stack[++top] = root;

    while (top >= 0) {
        struct node* current = stack[top--];
        count++;

        if (current->left) {
            stack[++top] = current->left;
        }
        if (current->right) {
            stack[++top] = current->right;
        }
    }

    return count;
}

int CalculateHeight(struct node* root) {
    if (root == NULL) {
        return 0;
    }

    struct node* stack[100];
    int top = -1;
    int height = 0;

    stack[++top] = root;

    while (1) {
        int nodeCount = top + 1;
        if (nodeCount == 0) {
            return height;
        }

        height++;
        while (nodeCount > 0) {
            struct node* current = stack[top--];
            if (current->left) {
                stack[++top] = current->left;
            }
            if (current->right) {
                stack[++top] = current->right;
            }
            nodeCount--;
        }
    }
}

int main() {
    struct node* r = NULL;
    int choice;

    while (1) {
        printf("\n1. Insert");
        printf("\n2. Inorder Traversal");
        printf("\n3. Calculate Height of tree");
        printf("\n4. Count number of nodes of tree");
        printf("\n5. Mirror");
        printf("\n6. EXIT");
        printf("\nChoose any one option: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter data to insert: ");
            int n;
            scanf("%d", &n);
            r = insert(r, n);
            break;

        case 2:
            InOrderTraversal(r);
            break;

        case 3:
            printf("The height of tree is %d\n", CalculateHeight(r));
            break;

        case 4:
            printf("The number nodes in the tree are: %d\n", CountNode(r));
            break;

        case 5:
            Mirror(r);
            printf("The tree is mirrored successfully\n");
            break;

        case 6:
            exit(0);
            break;

        default:
            printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
