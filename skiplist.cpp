/*
Code made by Shri Varshini and Shreya Vengatesh
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
const int MAX_LEVEL = 5;
const float PROBABILITY = 0.5;
class SkipListNode {
public:
    int key;
    SkipListNode** forward;

    SkipListNode(int k, int level);
    ~SkipListNode();
};

SkipListNode::SkipListNode(int k, int level) {
    key = k;
    forward = new SkipListNode*[level + 1];
    for (int i = 0; i <= level; i++) {
        forward[i] = nullptr;
    }
}

SkipListNode::~SkipListNode() {
    delete[] forward;
}

class SkipList {
private:
    int level;
    SkipListNode* header;

public:
    SkipList();
    ~SkipList();
    int randomLevel();
    SkipListNode* createNode(int key, int level);
    void insert(int key);
    void display();
    int search(int key);
    int deleteKey(int key);
};

SkipList::SkipList() {
    level = 0;
    header = new SkipListNode(-1, MAX_LEVEL);
}

SkipList::~SkipList() {
    delete header;
}

int SkipList::randomLevel() {
    int lvl = 0;
    while ((static_cast<float>(rand()) / RAND_MAX) < PROBABILITY && lvl < MAX_LEVEL) {
        lvl++;
    }
    return lvl;
}

SkipListNode* SkipList::createNode(int key, int level) {
    return new SkipListNode(key, level);
}
//method to insert a key in skiplist
void SkipList::insert(int key) {
    // Handling the case where the key is smaller than the minimum key
    if (header->forward[0] == nullptr || key < header->forward[0]->key) {
        int newLevel = randomLevel();
        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++) {
                header->forward[i] = header;
            }
            level = newLevel;
        }

        SkipListNode* newNode = createNode(key, newLevel);
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = header->forward[i];
            header->forward[i] = newNode;
        }
        return;
    }

    // Handling the case where the key is larger than the maximum key
    if (key > header->forward[0]->key) {
        SkipListNode* current = header;
        while (current->forward[0] != nullptr) {
            current = current->forward[0];
        }
        int newLevel = randomLevel();
        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++) {
                current->forward[i] = header;
            }
            level = newLevel;
        }

        SkipListNode* newNode = createNode(key, newLevel);
        for (int i = 0; i <= newLevel; i++) {
            current->forward[i] = newNode;
        }
        return;
    }

    SkipListNode* current = header;
    SkipListNode* update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(update));
    
    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];
    
    int newLevel = randomLevel();
    if (newLevel > level) {
        for (int i = level + 1; i <= newLevel; i++) {
            update[i] = header;
        }
        level = newLevel;
    }

    SkipListNode* newNode = createNode(key, newLevel);
    for (int i = 0; i <= newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

//method to delete a key in skip list
int SkipList::deleteKey(int key) {
    if (header->forward[0] == nullptr) {
        return -1;
    }

    SkipListNode* current = header;
    SkipListNode* update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(update));

    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if (current != nullptr && current->key == key) {
        for (int i = 0; i <= level; i++) {
            if (update[i]->forward[i] != current) break;
            update[i]->forward[i] = current->forward[i];
        }

        while (level > 0 && header->forward[level] == nullptr) {
            level--;
        }

        delete current;
        return 1;
    }
    else{
        return 0;
    }
}
//method to search the key in skip list
int SkipList::search(int key) {
    if (header->forward[0] == nullptr) {
        return -1;
    }

    SkipListNode* current = header;
    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    if (current != nullptr && current->key == key) {
        return 1;
    } 
    else {
        return 0;
    }
}

//method to display the skiplist
void SkipList::display() {
    printf("SkipList:\n");
    for (int i = level; i >= 0; i--) {
        printf("Level %d: ", i);
        SkipListNode* current = header->forward[i];
        while (current != nullptr) {
            printf("%d ", current->key);
            current = current->forward[i];
        }
        printf("\n");
    }
}
int main() {
    srand(time(NULL));  
    SkipList skipList;
    int choice,del,elem, key;

    while (true) {
        printf("\nSkipList Operations:\n");
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
                skipList.insert(key);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                del=skipList.deleteKey(key);
                if(del==1){
                printf("Key %d deleted\n", key);
                }
                else if(del==-1)
                {
                    printf("Skip list is empty");
                }
                else{
                    printf("key %d not found\n",key);
                }
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                elem=skipList.search(key);
                if (elem==1) {
                    printf("Key %d found in SkipList\n", key);
                }
                else if(elem==-1)
                {
                    printf("Skip list empty");
                }
                else {
                    printf("Key %d not found\n", key);
                }
                break;
            case 4:
                skipList.display();
                break;
            case 5:
                printf("Exited\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
