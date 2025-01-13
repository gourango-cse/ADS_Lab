#include <stdio.h>
#include <stdlib.h>

#define SIZE 7  // Size of the hash table

int hashTable[SIZE];

// Initialize hash table
void initHashTable() {
    int i;
    for (i = 0; i < SIZE; i++) {
        hashTable[i] = -1; // -1 indicates an empty slot
    }
}

// Hash function
int hashFunction(int key) {
    return key % SIZE;
}

// Insert a key into the hash table
void insert(int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (hashTable[index] != -1) {
        index = (index + 1) % SIZE; // Linear probing
        if (index == originalIndex) {
            printf("Hash table is full. Cannot insert %d.\n", key);
            return;
        }
    }
    hashTable[index] = key;
    printf("Inserted %d at index %d.\n", key, index);
}

// Search for a key in the hash table
void search(int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (hashTable[index] != -1) {
        if (hashTable[index] == key) {
            printf("%d found at index %d.\n", key, index);
            return;
        }
        index = (index + 1) % SIZE; // Linear probing
        if (index == originalIndex) {
            break;
        }
    }
    printf("%d not found in the hash table.\n", key);
}

// Display the hash table
void display() {
    int i;
    printf("Hash table:\n");
    for (i = 0; i < SIZE; i++) {
        if (hashTable[i] != -1) {
            printf("Index %d: %d\n", i, hashTable[i]);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}

int main() {
    int choice, key;
    initHashTable();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
