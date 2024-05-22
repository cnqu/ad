#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* CreateNode(int data) {
    struct node* NewNode = (struct node*)malloc(sizeof(struct node));
    NewNode->data = data;
    NewNode->left = NewNode->right = NULL;
    return NewNode;
}

struct node* insert(struct node* root, int value) {
    if (root == NULL) {
        return CreateNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

void InOrderTraversal(struct node* root) {
    if (root == NULL) {
        return;
    }
    InOrderTraversal(root->left);
    printf("%d ", root->data);
    InOrderTraversal(root->right);
}

void Mirror(struct node* root) {
    if (root == NULL) {
        return;
    } else {
        struct node* temp;
        Mirror(root->left);
        Mirror(root->right);
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

int CountNode(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return CountNode(root->left) + CountNode(root->right) + 1;
}

int CalculateHeight(struct node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int left = CalculateHeight(root->left);
        int right = CalculateHeight(root->right);
        return (left > right) ? left + 1 : right + 1;
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
            printf("\n");
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
