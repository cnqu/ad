#include <stdio.h>
#include <stdlib.h>



struct Node{
    int data;
    struct Node* left;
    struct  Node* right;
    int height;
};

int height(struct Node* root)
{
    if(root==NULL)
    return 0;

    return root->height;

}

int max(int a,int b){
    return (a>b)?a:b;
}


struct Node*  createNode(int value){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->data=value;
    newNode->left=newNode->right=NULL;
    newNode->height=1;
    return newNode;

} 

int getBalance(struct Node* root){
    if(root==NULL){
        return 0;
    }

    return height(root->left)-height(root->right);

}
struct Node* leftRotate(struct Node* x){
    struct Node* y=x->right;
    struct Node* T2=y->left;

    y->left=x;
    x->right=T2;

    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;

    return y;
}

struct Node* rightRotate(struct Node* y){
    struct Node* x=y->left;
    struct Node* T2=x->right;

    x->right=y;
    y->left=T2;

    x->height=max(height(x->left),height(x->right))+1;
    y->height=max(height(y->left),height(y->right))+1;

    return x;
}

struct Node* insert(struct Node* root, int value){
    if (root==NULL){
        return createNode(value);
    }

    if(value<root->data){
        root->left= insert(root->left,value);

    }
    else if(value>root->data){
         root->right= insert(root->right,value);
    }
    else{
        return root;
    }

    root->height=max(height(root->left),height(root->right))+1;

    int balance=getBalance(root);
// LL
        if(balance>1 && value<root->left->data){
        
        return rightRotate(root);
                  }

    // RR
     if(balance<-1 && value>root->right->data){
        return rightRotate(root);
    }
    
    //LR
if(balance>1 && value>root->left->data){
    root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    //RL

    if(balance<-1 && value<root->right->data){
root->right=rightRotate(root->right);
        return rightRotate(root);
    }


return root;


}


struct Node* findMin(struct Node* node){
    while(node->left!=NULL){
        node=node->left;
    }
    return node;
}

struct Node* delete(struct Node* root, int value) {
    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = delete(root->left, value);
    else if (value > root->data)
        root->right = delete(root->right, value);
    else {
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
        root->right = delete(root->right, temp->data);
    }

    // Recalculate height
    root->height = 1 + max(height(root->left), height(root->right));

    // Check balance factor
    int balance = getBalance(root);

    // Four cases for rotation
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void preOrder(struct Node* root){
    if(root!=NULL){
        printf("%d ",root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main(){
    struct Node* root=NULL;
    int c,e;

    while(1){
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Preorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&c);

        switch(c){
            case 1:
            printf("Enter the element to insert: ");
            scanf("%d",&e);
            root=insert(root,e);
            break;

            case 2:
            printf("Enter the element to delete: ");
            scanf("%d",&e);
            root=delete(root,e);
            break;

            case 3:
            printf("Preorder Traversal: ");
            preOrder(root);
            printf("\n");
            break;

            case 4:
            exit(0);
            break;

            default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}


