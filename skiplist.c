#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEVEL 4  // Maximum level of the skip list

// Node structure for Skip List
typedef struct SkipNode {
    int key;
    struct SkipNode **forward;
} SkipNode;

// Skip List structure
typedef struct SkipList {
    int level;
    struct SkipNode *header;
} SkipList;

// Function to create a new node
SkipNode* createNode(int key, int level) {
    SkipNode *node = (SkipNode *)malloc(sizeof(SkipNode));
    node->key = key;
    node->forward = (SkipNode **)malloc(sizeof(SkipNode*) * (level + 1));
    for (int i = 0; i <= level; i++) {
        node->forward[i] = NULL;
    }
    return node;
}

// Function to initialize a skip list
SkipList* createSkipList() {
    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    list->level = 0;
    list->header = createNode(INT_MIN, MAX_LEVEL);
    return list;
}

// Function to generate a random level for a node
int randomLevel() {
    int level = 0;
    while (rand() % 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// Function to insert a key into the skip list
void insert(SkipList *list, int key) {
    SkipNode *update[MAX_LEVEL + 1];
    SkipNode *current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    int lvl = randomLevel();
    if (lvl > list->level) {
        for (int i = list->level + 1; i <= lvl; i++) {
            update[i] = list->header;
        }
        list->level = lvl;
    }

    SkipNode *newNode = createNode(key, lvl);
    for (int i = 0; i <= lvl; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

// Function to delete a key from the skip list
void deleteKey(SkipList *list, int key) {
    SkipNode *update[MAX_LEVEL + 1];
    SkipNode *current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    SkipNode *target = current->forward[0];
    if (target && target->key == key) {
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->forward[i] != target) {
                break;
            }
            update[i]->forward[i] = target->forward[i];
        }
        free(target);

        while (list->level > 0 && list->header->forward[list->level] == NULL) {
            list->level--;
        }
        printf("Deleted %d from the skip list.\n", key);
    } else {
        printf("Key %d not found in the skip list.\n", key);
    }
}

// Function to search for a key in the skip list
void search(SkipList *list, int key) {
    SkipNode *current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];

    if (current && current->key == key) {
        printf("Key %d found in the skip list.\n", key);
    } else {
        printf("Key %d not found in the skip list.\n", key);
    }
}

// Function to display the skip list
void display(SkipList *list) {
    printf("\nSkip List:\n");
    for (int i = list->level; i >= 0; i--) {
        SkipNode *node = list->header->forward[i];
        printf("Level %d: ", i);
        while (node) {
            printf("%d -> ", node->key);
            node = node->forward[i];
        }
        printf("NULL\n");
    }
}

// Main function with dynamic input
int main() {
    SkipList *list = createSkipList();
    int choice, key;

    while (1) {
        printf("\nSkip List Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(list, key);
                display(list);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(list, key);
                display(list);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(list, key);
                break;
            case 4:
                display(list);
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}
