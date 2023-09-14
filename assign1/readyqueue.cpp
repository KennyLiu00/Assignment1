#ifndef READYQUEUE_H
#define READYQUEUE_H
#include <iostream>
#include "readyqueue.h"
#include "pcb.h"


using namespace std;

/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue() : /*Q{}*/ { //Q starts with an empty array
     count = 0; //initializing the number of elements that will be in the heap
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
  // When adding a PCB to the queue, you must change its state to READY.
  
  if(count >= MAX) //if the queue is full
    return;

  else // queue is not full
  {
    Q[count] = pcbPtr; // adding pcb into the queue
    count++; // increment size
    pcbPtr->setState(ProcState::READY); // state to ready
    trickleup(); // pcb needs to be swapped until in the right location
  }
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
  if(count == 0) //if there is no elements inside of the heap
  {
    return NULL; //since it is empty, it will be NULL
  }

// Reheapifying - after last job is replaced as root, need to trickle down to ensure it is in the right location

  PCB* to_remove = Q[0]; // variable to return the removed PCB; pointing at highest priority (root)
  Q[0] = Q[count - 1]; // move the last job to the front/root
  count--; // decrement, since we are removing
  to_remove->setState(ProcState::RUNNING); // state to running

  int currentIndex = 0; // keep track of the current index, 0 is the root
  int bigger_child = currentIndex; // holds location of the bigger child
  
  while(currentIndex < count) // runs until currentIndex exceeds count or no longer need to swap
  {
    bigger_child = getBiggerChild(currentIndex); // gets bigger child of parent
    if(bigger_child != -1 && Q[bigger_child]->getPriority() > Q[currentIndex]->getPriority()) // the child is not -1 (error) and the bigger child is greater than the currentIndex
    {
      swap(Q[bigger_child], Q[currentIndex]); // swap both elements
      currentIndex = bigger_child; // updating currentIndex
    }
    else // no need to swap so break out of loop
    {
      break;
    }
  } 
  return to_remove; // returns PCB removed
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
     return count;//return the size of the array
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    if(count == 0)//if the queue is empty
  {
      cout << "Display Processes in ReadyQueue:" << endl;//set that as the statement to follow the test outputs (such as the last line of test1)
  }
  else // regular case - if there are elements inside the array
  {
    cout << "Display Processes in ReadyQueue:" << endl;//following the test outputs
    for(int i=0; i<count; i++)//reads through the size of array
      { 
        Q[i]->display();//display the following statements from the pcb.h file
      }
    cout << endl;
  }
}
/**
  @ brief Get the bigger child from the heap
  */
int ReadyQueue::getBiggerChild(int index) 
{
  // LC and RC are indexes
  int LC = (2 * index) + 1;  //left child
  int RC = (2 * index) + 2;  //right child 

  if(LC >= count-1 && RC >= count-1) // both are beyond count-1 - error
    return -1;
  else if(LC >= count-1) // LC beyond count-1
    return RC;
  else if(RC >= count-1) // RC beyond count-1 
    return LC;
  else // regular case - both NOT beyond count-1 
  {
    if(Q[LC]->getPriority() > Q[RC]->getPriority()) // LC has higher priority
	    return LC; // set it as left child
    else
	    return RC; // set it as right child
  }
}
/*
Swap function: set two values to switch values

NOTE: WAS NOT USED TO RUN THE PROGRAM, BUT USED AS A TEST
  
*/
void ReadyQueue::swapFunc(int x, int y) // original int x int y
  {
	// Swap only if both indexes are legal
	if (x < count && y < count) {
		PCB* temp = Q[x]; 
		Q[x] = Q[y];
		Q[y] = temp;
	  }
  }

/*
trickleup(): used to get the root of the heap array
*/
void ReadyQueue::trickleup()
{
  int j = count-1; // last job's location
  int parent; // sucessor of child
  
  while(j > 0) // until j reaches 0
  {
    if(j%2 == 0) // is even
      parent = ((j-2)/2); 
    else  //is odd
      parent = ((j-1)/2);

    if(Q[j]->getPriority() > Q[parent]->getPriority()) // if child is bigger swap and update j
    { 
      swap(Q[j], Q[parent]);//call the swap function
      j = parent; // update index
    }
    else  
      return;
  }  
}

#endif
