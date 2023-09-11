#include <iostream>
#include "readyqueue.h"
#include "pcb.h"
#include <cmath>
#include <iomanip>

using namespace std;

/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
     //TODO: add your code here
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    //TODO: add your code to release dynamically allocate memory
 
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    //TODO: add your code here
    // When adding a PCB to the queue, you must change its state to READY.
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    //TODO: add your code here
    // When removing a PCB from the queue, you must change its state to RUNNING.
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
     return data.size();
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    ProcState currentState;
    cout << "Queue: \n";
    cout << "ID" << "\t\t" << "Priority" "\t\t" << "State" << endl;
    cout << "---------------------------------------" << endl;
    for(int i = 0; i < data.size(); i++){
        currentState = data[i].getState();
        cout << data[i].getID() << "\t\t" << data[i].getPriority() << "\t\t\t\t" << data[i].formatState(currentState) << endl;
}
