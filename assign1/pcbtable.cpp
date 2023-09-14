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
   //setting capacities for the following elements
   // processes.resize(size);//sizes available inside the table 
   pcbArray = new PCB*[size];
   capacity = size;
   for (int i = 0; i < size; i++) {
      pcbArray[i] = nullptr;
   }
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
   for (int i = 0; i < capacity; i++) { // deletes PCBs pointed and points to NULL
      if (pcbArray[i] != nullptr) {
         delete pcbArray[i];
      }
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
    if (idx < capacity) {
       return pcbArray[idx];
   }
   return nullptr;
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
   if (idx < capacity) {
      pcbArray[idx] = pcb;
   }
}
