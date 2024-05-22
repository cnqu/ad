#include <stdio.h>

#define SIZE 11

int hashTable[SIZE] = {0};

int hash(int key) {
    return key % SIZE;
}

void insert(int key) {
    int index = hash(key);
    int i = 0;

    while (hashTable[(index + i) % SIZE] != 0) {
        i++;
        if (i == SIZE) {
            printf("Hash table is full!\n");    
            return;
        }
    }
    hashTable[(index + i) % SIZE] = key;
}

void display() {
    printf("Hash Table:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d: %d\n", i, hashTable[i]);
    }
}

void search(int key) {
    int index = hash(key);
    int i = 0;

    while (hashTable[(index + i) % SIZE] != key) {
        i++;
        if (hashTable[(index + i) % SIZE] == 0 || i == SIZE) {
            printf("Key not found!\n");
            return;
        }
    }
    printf("Key %d found at index %d\n", key, (index + i) % SIZE);
}

int main() {
    int choice, key;

    do {
        printf("\nMenu:\n");
        printf("1. Insert key\n");
        printf("2. Display hash table\n");
        printf("3. Search for a key\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                display();
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
