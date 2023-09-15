#include <iostream>
#include "readyqueue.h"
#include "pcb.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue(int initialCapacity) : arraySize(0), capacity(initialCapacity) {
    arrqueue = new PCB*[capacity];
}

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    delete[] arrqueue;
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    if (arraySize == capacity) {
        // Double the capacity and reallocate memory for the array
        capacity *= 2;
        PCB** newArr = new PCB*[capacity];
        
        // Copy elements from the old array to the new array
        for (int i = 0; i < arraySize; i++) {
            newArr[i] = arrqueue[i];
        }
        
        // Deallocate memory for the old array
        delete[] arrqueue;
        
        // Update arrqueue to point to the new array
        arrqueue = newArr;
    }
    int insertIndex = arraySize;
    // Find the correct position to insert the process based on its priority
    for (int i = 0; i < arraySize; i++) {
        if (pcbPtr->getPriority() > arrqueue[i]->getPriority()) {
            insertIndex = i;
            break;
        }
    }
    // Shift elements to make room for the new process
    for (int i = arraySize; i > insertIndex; i--) {
        arrqueue[i] = arrqueue[i - 1];
    }

    // Insert the process at the correct position
    arrqueue[insertIndex] = pcbPtr;
    arraySize++;

    // Set the state of the inserted process
    pcbPtr->setState(ProcState::READY);
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    if (arraySize == 0) {
        return nullptr; // Return nullptr when the queue is empty
    }

    int priority = 0;
    PCB *priorityreturn;
    for (int i = 1; i < arraySize; i++) {
        if (arrqueue[priority]->getPriority() < arrqueue[i]->getPriority()) {
            priority = i;
        }
    }
    priorityreturn = arrqueue[priority];
    // Set the state of the removed process to RUNNING
    priorityreturn->setState(ProcState::RUNNING);

    for (int i = priority; i < arraySize - 1; i++) {
        arrqueue[i] = arrqueue[i + 1];
    }
    arraySize--;

    return priorityreturn;
}
/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return arraySize;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
  for(int i = 0; i < arraySize; i++){
    arrqueue[i]->display();
  }
}
