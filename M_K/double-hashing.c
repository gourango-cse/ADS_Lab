#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 13 // Size of the hash table
#define EMPTY -1      // Empty slot indicator

// Hash table
int hashTable[TABLE_SIZE];

// Hash functions
int hash1(int key) {
    return key % TABLE_SIZE;
}

int hash2(int key) {
    return 1 + (key % (TABLE_SIZE - 1));
}

// Insert a key into the hash table
void insert(int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;

    while (hashTable[(index + i * step) % TABLE_SIZE] != EMPTY && i < TABLE_SIZE) {
        i++;
    }

    if (i < TABLE_SIZE) {
        hashTable[(index + i * step) % TABLE_SIZE] = key;
        printf("Inserted key %d at index %d\n", key, (index + i * step) % TABLE_SIZE);
    } else {
        printf("Hash table is full. Cannot insert key %d\n", key);
    }
}

// Search for a key in the hash table
void search(int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;

    while (hashTable[(index + i * step) % TABLE_SIZE] != EMPTY && i < TABLE_SIZE) {
        if (hashTable[(index + i * step) % TABLE_SIZE] == key) {
            printf("Key %d found at index %d\n", key, (index + i * step) % TABLE_SIZE);
            return;
        }
        i++;
    }

    printf("Key %d not found\n", key);
}

// Display the hash table
void display() {
    int i;
    printf("Hash Table:\n");
    for (i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != EMPTY) {
            printf("Index %d: %d\n", i, hashTable[i]);
        } else {
            printf("Index %d: EMPTY\n", i);
        }
    }
}

// Main function
int main() {
    int choice, key;
    int i;

    // Initialize hash table
    for (i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = EMPTY;
    }

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            insert(key);
            break;
        case 2:
            printf("Enter key to search: ");
            scanf("%d", &key);
            search(key);
            break;
        case 3:
            display();
            break;
        case 4:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
