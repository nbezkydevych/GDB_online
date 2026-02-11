
#include <stdio.h>
#include <stdbool.h>

#define SIZE 5  // Size of circular buffer

typedef struct {
    float buffer[SIZE];
    int head; // write position
    int tail; // read position
    int count; // number of elements
} CircularBuffer;

// Initialize the buffer
void initBuffer(CircularBuffer* cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// Check if buffer is full
bool isFull(CircularBuffer* cb) {
    return cb->count == SIZE;
}

// Check if buffer is empty
bool isEmpty(CircularBuffer* cb) {
    return cb->count == 0;
}

// Enqueue (write to buffer)
bool enqueue(CircularBuffer* cb, float data) {
    if (isFull(cb)) {
        printf("Buffer is full!\n");
        return false;
    }

    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % SIZE;
    cb->count++;
    return true;
}

// Dequeue (read from buffer)
bool dequeue(CircularBuffer* cb, float* data) {
    if (isEmpty(cb)) {
        printf("Buffer is empty!\n");
        return false;
    }

    if (data)
    {
        *data = cb->buffer[cb->tail];
    }
    
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count--;
    return true;
}

//Peek first item from buffer without removing the item
bool peekFirst(CircularBuffer* cb, float* data) {
    if (isEmpty(cb)) {
        printf("Buffer is empty!\n");
        return false;
    }

    int lastIndex = (cb->head - 1 + SIZE) % SIZE; // Get the index of the last item
    if (data)
    {
        *data = cb->buffer[lastIndex];
    }
    
    return true;
}

// Peek last item from buffer without removing the item
bool peekLast(CircularBuffer* cb, float* data) {
    if (isEmpty(cb)) {
        printf("Buffer is empty!\n");
        return false;
    }

    if (data)
    {
        *data = cb->buffer[cb->tail];
    }
    
    return true;
}

// Overwriting enqueue
void forceEnqueue(CircularBuffer* cb, int data) {
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % SIZE;

    if (isFull(cb)) {
        // Overwrite: move tail forward too
        cb->tail = (cb->tail + 1) % SIZE;
    } else {
        cb->count++;
    }
}

// Print the buffer (for testing)
void printBuffer(CircularBuffer* cb) {
    printf("Buffer contents: ");
    int index = cb->tail;
    for (int i = 0; i < cb->count; i++) {
        printf("%.01f ", cb->buffer[index]);
        index = (index + 1) % SIZE;
    }
    printf("\n");
}

// Print the buffer (for testing)
void printRawBuffer(CircularBuffer* cb) {
    printf("Raw Buffer contents: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%.01f ", cb->buffer[i]);
    }
    printf("\n");
}

// Example usage
int main() {
    CircularBuffer cb;
    initBuffer(&cb);

    enqueue(&cb, 10);
    enqueue(&cb, 20);
    enqueue(&cb, 30);
    printBuffer(&cb);
    printRawBuffer(&cb);

    float value;
    peekLast(&cb, &value);
    printf("Peek Last: %.01f\n", value);
    peekFirst(&cb, &value);
    printf("Peek First: %.01f\n", value);
    dequeue(&cb, &value);
    printf("Dequeued: %.01f\n", value);
    printBuffer(&cb);
    printRawBuffer(&cb);

    enqueue(&cb, 40);
    enqueue(&cb, 50);
    printBuffer(&cb);
    printRawBuffer(&cb);

    enqueue(&cb, 60);  // This should fail (buffer full)
    printBuffer(&cb);
    printRawBuffer(&cb);

    enqueue(&cb, 70);  // This should fail (buffer full)
    forceEnqueue(&cb, 70);
    printBuffer(&cb);
    printRawBuffer(&cb);

    return 0;
}

