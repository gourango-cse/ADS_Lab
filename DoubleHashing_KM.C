#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10  // Size of the hash table

// Hash functions
int hash1(int key) {
    return key % TABLE_SIZE;
}

int hash2(int key) {
    return 1 + (key % (TABLE_SIZE - 1));
}

// Function to insert a key using double hashing
void insert(int hash_table[], int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;

    // Try to find a free slot using double hashing
    while (hash_table[(index + i * step) % TABLE_SIZE] != -1 && i < TABLE_SIZE) {
        i++;
    }

    if (i < TABLE_SIZE) {
        hash_table[(index + i * step) % TABLE_SIZE] = key;
    } else {
        printf("Hash table is full. Cannot insert key %d.\n", key);
    }
}

// Function to search for a key using double hashing
int search(int hash_table[], int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;

    // Try to find the key using double hashing
    while (i < TABLE_SIZE) {
        int probe_index = (index + i * step) % TABLE_SIZE;
        if (hash_table[probe_index] == key) {
            return probe_index;  // Key found
        }
        if (hash_table[probe_index] == -1) {
            break;  // Key not found
        }
        i++;
    }
    return -1;  // Key not found
}

// Function to delete a key using double hashing
void delete(int hash_table[], int key) {
    int index = hash1(key);
    int step = hash2(key);
    int i = 0;

    // Try to find the key using double hashing
    while (i < TABLE_SIZE) {
        int probe_index = (index + i * step) % TABLE_SIZE;
        if (hash_table[probe_index] == key) {
            hash_table[probe_index] = -2;  // Mark as deleted
            printf("Key %d deleted from index %d\n", key, probe_index);
            return;
        }
        if (hash_table[probe_index] == -1) {
            break;  // Key not found
        }
        i++;
    }

    printf("Key %d not found in the hash table. Cannot delete.\n", key);
}

// Function to display the hash table
void display(int hash_table[]) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] != -1 && hash_table[i] != -2) {
            printf("Index %d: %d\n", i, hash_table[i]);
        } else if (hash_table[i] == -2) {
            printf("Index %d: Deleted\n", i);
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
        printf("4. Delete\n");
        printf("5. Exit\n");
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
                printf("Enter the key to delete: ");
                scanf("%d", &key);
                delete(hash_table, key);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
