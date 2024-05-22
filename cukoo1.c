#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11

// Function prototypes
int hash1(int key);
int hash2(int key);
void insert(int key, int table1[], int table2[]);
void delete(int key, int table1[], int table2[]);
int search(int key, int table1[], int table2[]);
void displayHashtable(int table1[], int table2[]);
void menu();

int main() {
    int table1[TABLE_SIZE] = {0};
    int table2[TABLE_SIZE] = {0};
    int choice, key;

    do {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                insert(key, table1, table2);
                break;
            case 2:
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                delete(key, table1, table2);
                break;
            case 3:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                if (search(key, table1, table2) != -1) {
                    printf("Key %d found.\n", key);
                } else {
                    printf("Key %d not found.\n", key);
                }
                break;
            case 4:
                displayHashtable(table1, table2);
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (1);

    return 0;
}

// Hash function 1
int hash1(int key) {
    return key % TABLE_SIZE;
}

// Hash function 2
int hash2(int key) {
    return (key / TABLE_SIZE) % TABLE_SIZE;
}

// Insert a key into the tables
void insert(int key, int table1[], int table2[]) {
    int index1 = hash1(key);
    int index2 = hash2(key);

    if (table1[index1] == 0) {
        table1[index1] = key;
    } else if (table2[index2] == 0) {
        table2[index2] = key;
    } else {
        // If both slots are occupied, perform displacement
        int temp = table1[index1];
        table1[index1] = key;
        key = temp;

        // Re-hash displaced key
        insert(key, table2, table1);
    }
}

// Delete a key from the tables
void delete(int key, int table1[], int table2[]) {
    int index1 = hash1(key);
    int index2 = hash2(key);

    if (table1[index1] == key) {
        table1[index1] = 0;
    } else if (table2[index2] == key) {
        table2[index2] = 0;
    } else {
        printf("Key %d not found for deletion.\n", key);
    }
}

// Search for a key in the tables
int search(int key, int table1[], int table2[]) {
    int index1 = hash1(key);
    int index2 = hash2(key);

    if (table1[index1] == key) {
        return index1;
    } else if (table2[index2] == key) {
        return index2;
    } else {
        return -1; // Key not found
    }
}

// Display the hash tables
void displayHashtable(int table1[], int table2[]) {
    printf("Elements in hashtable 1: \n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d ", table1[i]);
    }
    printf("\n");

    printf("Elements in hashtable 2: \n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d ", table2[i]);
    }
    printf("\n");
}

// Display menu options
void menu() {
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Search\n");
    printf("4. Display\n");
    printf("5. Exit\n");
}

