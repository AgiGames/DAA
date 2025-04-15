#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct Node {

    int number;
    char encodingChar;
    struct Node* leftChild;
    struct Node* rightChild;

};
typedef struct Node Node;

void swapNodes(Node** a, Node** b) {

    Node* temp = *a;
    *a = *b;
    *b = temp;

}

struct MinHeap {

    Node** nodes;
    int size;
    int currentSize;

};
typedef struct MinHeap MinHeap;

MinHeap* createNewMinHeap(int heapSize, char* characters, int* frequencies) {

    MinHeap* newMinHeap = (MinHeap* ) malloc(sizeof(MinHeap));
    newMinHeap->nodes = (Node**) calloc(heapSize, sizeof(Node*));
    newMinHeap->size = heapSize;
    newMinHeap->currentSize = heapSize;
    
    for(int i = 0; i < heapSize; i++) {
        newMinHeap->nodes[i] = (Node* ) calloc(1, sizeof(Node));
        newMinHeap->nodes[i]->leftChild = NULL;
        newMinHeap->nodes[i]->rightChild = NULL;
        newMinHeap->nodes[i]->encodingChar = characters[i];
        newMinHeap->nodes[i]->number = frequencies[(unsigned char) characters[i]];
    }

    return newMinHeap;

}

void minHeapify(MinHeap* heap, int ithNodeIdx) {

    int leftChildIdx = 2 * ithNodeIdx + 1;
    int rightChildIdx = 2 * ithNodeIdx + 2;
    int smallest = ithNodeIdx;

    if (leftChildIdx < heap->currentSize && heap->nodes[leftChildIdx]->number < heap->nodes[smallest]->number) {
        smallest = leftChildIdx;
    }

    if (rightChildIdx < heap->currentSize && heap->nodes[rightChildIdx]->number < heap->nodes[smallest]->number) {
        smallest = rightChildIdx;
    }

    if (smallest != ithNodeIdx) {
        swapNodes(&heap->nodes[ithNodeIdx], &heap->nodes[smallest]);
        minHeapify(heap, smallest);
    }

}

void buildHeap(MinHeap* heap) {

    int lastNonLeafIdx = (heap->size / 2) - 1;
    for(int i = lastNonLeafIdx; i >= 0; i--) {
        minHeapify(heap, i);
    }

}

void insertNode(MinHeap* heap, Node* newNode) {

    if (heap->currentSize == heap->size) {
        printf("HEAP IS FULL!\n");
        return;
    }

    int i = heap->currentSize;
    heap->nodes[i] = newNode;
    heap->currentSize++;

    while (i > 0) {
        int parentIdx = (i - 1) / 2;
        if (heap->nodes[parentIdx]->number <= heap->nodes[i]->number) {
            break;
        }

        swapNodes(&heap->nodes[i], &heap->nodes[parentIdx]);
        i = parentIdx;
    }

}

Node* deleteNode(MinHeap* heap) {

    if(heap->currentSize == 0) {
        printf("HEAP IS EMPTY!\n");
        return NULL;
    }

    Node* deletedNode = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->currentSize - 1];
    heap->currentSize--;
    minHeapify(heap, 0);

    return deletedNode;

}

void printMinHeap(MinHeap* heap) {
    printf("\nMin Heap Structure:\n");
    printf("-----------------------------------------\n");
    printf("Index\t|\tChar\t|\tFrequency\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < heap->size; i++) {
        printf("%d\t|\t'%c'\t|\t%d\n", i, heap->nodes[i]->encodingChar, heap->nodes[i]->number);
    }

    printf("-----------------------------------------\n");
}

void freeMinHeap(MinHeap* heap) {

    if (heap == NULL) return;

    for (int i = 0; i < heap->size; i++) {
        free(heap->nodes[i]);
    }

    free(heap->nodes);

    free(heap);

}

struct Table {

    int freq[256];
    char chars[256];
    int numCharsVisited;

};
typedef struct Table Table;

Table* createNewTable() {

    Table* newTable = calloc(1, sizeof(Table));
    return newTable;

}

void getCharsAndFreq(Table* charFreqTable, char* string) {

    int n = strlen(string);
    
    for(int i = 0; i < n; i++) {
        char ithChar = string[i];
        if(charFreqTable->freq[(unsigned char) ithChar] == 0) {
            charFreqTable->chars[charFreqTable->numCharsVisited] = ithChar;
            charFreqTable->numCharsVisited++;
        }
        charFreqTable->freq[(unsigned char) ithChar]++;
    }

}

void printTable(Table* charFreqTable) {

    printf("\nCharacter Frequency Table:\n");
    printf("--------------------------\n");
    printf("Char\t|\tFrequency\n");
    printf("--------------------------\n");

    for (int i = 0; i < charFreqTable->numCharsVisited; i++) {
        char c = charFreqTable->chars[i];
        printf("'%c'\t|\t%d\n", c, charFreqTable->freq[(unsigned char)c]);
    }

    printf("--------------------------\n");
    printf("Total\t|\t%d\n", charFreqTable->numCharsVisited);
    printf("--------------------------\n");

}

void freeTable(Table* table) {

    free(table);

}

void DFS(Node* ithNode, char path[], int numVisitedDepths) {

    if(ithNode->encodingChar != '\0') {
        path[numVisitedDepths] = '\0';
        printf("'%c'\t|\t%s\n", ithNode->encodingChar, path);
    }
    if(ithNode->leftChild != NULL) {
        path[numVisitedDepths] = '0';
        DFS(ithNode->leftChild, path, numVisitedDepths + 1);
    }
    if(ithNode->rightChild != NULL) {
        path[numVisitedDepths] = '1';
        DFS(ithNode->rightChild, path, numVisitedDepths + 1);
    }

}

void doHuffmanCoding(MinHeap* heap) {

    while(heap->currentSize > 1) {
        Node* minNodeOne = deleteNode(heap);
        Node* minNodeTwo = deleteNode(heap);
        Node* newNode = (Node* ) calloc(1, sizeof(Node));
        newNode->encodingChar = '\0';
        newNode->number = minNodeOne->number + minNodeTwo->number;
        newNode->leftChild = minNodeOne;
        newNode->rightChild = minNodeTwo;
        insertNode(heap, newNode);
    }
    char path[1000] = {0};
    printf("\nHuffman Codes:\n");
    printf("--------------------\n");
    printf("Char\t|\tCode\n");
    printf("--------------------\n");
    DFS(heap->nodes[0], path, 0);

}

int main() {

    Table* charFreqTable = createNewTable();
    char string[1000] = {0};

    printf("Enter your string: ");
    scanf("%s", string);

    getCharsAndFreq(charFreqTable, string);
    printTable(charFreqTable);

    MinHeap* minHeap = createNewMinHeap(charFreqTable->numCharsVisited,
                                        charFreqTable->chars, charFreqTable->freq);
    buildHeap(minHeap);
    printMinHeap(minHeap);
    
    doHuffmanCoding(minHeap);

    freeTable(charFreqTable);
    freeMinHeap(minHeap);

    return 0;

}
