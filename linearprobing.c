#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10  // Size of the hash table

// Function to calculate the hash value
int hash(int key) {
    return key % TABLE_SIZE;
}

// Function to insert a value into the hash table using linear probing
void insert(int hash_table[], int key) {
    int index = hash(key);

    // Linear probing to find the next available slot
    while (hash_table[index] != -1) {
        index = (index + 1) % TABLE_SIZE;
    }

    hash_table[index] = key;
}

// Function to search for a key in the hash table
int search(int hash_table[], int key) {
    int index = hash(key);
    int start_index = index;

    // Search through the hash table using linear probing
    while (hash_table[index] != -1) {
        if (hash_table[index] == key) {
            return index;  // Key found
        }
        index = (index + 1) % TABLE_SIZE;

        // If we return to the start index, the key is not present
        if (index == start_index) {
            break;
        }
    }
    return -1;  // Key not found
}

// Function to display the hash table
void display(int hash_table[]) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] != -1) {
            printf("Index %d: %d\n", i, hash_table[i]);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}

int main() {
    int hash_table[TABLE_SIZE];
    int choice, key, index;

    // Initialize hash table with -1 indicating empty slots
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = -1;
    }

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
                insert(hash_table, key);
                break;
            case 2:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                index = search(hash_table, key);
                if (index != -1) {
                    printf("Key %d found at index %d\n", key, index);
                } else {
                    printf("Key %d not found in the hash table.\n", key);
                }
                break;
            case 3:
                display(hash_table);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

