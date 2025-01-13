#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7

int hashTable[TABLE_SIZE];
int size = 0;

// Initialize the hash table
void initializeTable() {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1; // -1 indicates an empty slot
    }
}

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Insert a value using quadratic probing
void insert(int key) {
    if (size == TABLE_SIZE) {
        printf("Hash table is full.\n");
        return;
    }

    int hashIndex = hashFunction(key);
    int i = 0;

    while (hashTable[(hashIndex + i * i) % TABLE_SIZE] != -1) {
        i++;
        if (i == TABLE_SIZE) {
            printf("Unable to insert key %d. Table is full.\n", key);
            return;
        }
    }

    int index = (hashIndex + i * i) % TABLE_SIZE;
    hashTable[index] = key;
    size++;
    printf("Key %d inserted successfully at index %d.\n", key, index);
}

// Search for a value using quadratic probing
void search(int key) {
    int hashIndex = hashFunction(key);
    int i = 0;

    while (hashTable[(hashIndex + i * i) % TABLE_SIZE] != -1) {
        if (hashTable[(hashIndex + i * i) % TABLE_SIZE] == key) {
            printf("Key %d found at index %d.\n", key, (hashIndex + i * i) % TABLE_SIZE);
            return;
        }
        i++;
        if (i == TABLE_SIZE) {
            break;
        }
    }

    printf("Key %d not found.\n", key);
}

// Display the hash table
void display() {
    int i;
    printf("Hash Table:\n");
    for (i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != -1)
            printf("Index %d: %d\n", i, hashTable[i]);
        else
            printf("Index %d: Empty\n", i);
    }
}

// Main function
int main() {
    int choice, key;

    initializeTable();

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
