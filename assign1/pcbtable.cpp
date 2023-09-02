/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Kenny Liu
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   //Initialize the size of the PCBTable
   capacity = size;

   //Initialize the PCB array with the given capacity
   pcbArray = new PCB*[capacity];

   //Initialize all PCB pointers to nullptr
   for (int i = 0; i < capacity; i++) {
      pcbArray[i] = nullptr;
   }
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
   // Delete all the PCBs in the table and release memory
   for (int i = 0; i < capacity; i++) {
      delete pcbArray[i];
   }

   //Release memory for the PCB array
   delete[] pcbArray;
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    //Check if idx is within the valid range
   if (idx < capacity) {
      return pcbArray[idx];
   } else {
      // Handle out-of-range error
    return NULL;
   }
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    // Check if idx is within the valid range
   if (idx < capacity) {
      // Delete the existing PCB at idx if it exists
      delete pcbArray[idx];

      // Assign the new PCB pointer to the specified index
      pcbArray[idx] = pcb;
   } else {
      // Handle out-of-range error (do nothing)
   }
}
