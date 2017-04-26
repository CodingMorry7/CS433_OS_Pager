#include "fifo_sim.h"
/*
 This function searches for the entry in the Page Table.
 Params: struct page, int total_faults, int file_Out
*/
int fifo_sim::fifo_search(struct fifo_page *Table, int total_faults,
                          int file_Out) {
  int i = 0;
  while (i < total_faults) {
    if (Table[i].addr == file_Out) {
      return i; // return the entry if found.
    }
    i++;
  }
  // if the function can't find it then return -1;
  return -1;
}

/*
  This function helps display the results of the
  algorithms in a nice format.
  param int algorithm
*/
void fifo_sim::Display_FIFO_Results(int total_time, int total_pg_entry_faults,
                                    int total_mem_ref, int total_Flushes) {
  cout << "FIFO Algorithm's Results" << endl;
  cout << "=======================" << endl;
  cout << "Memory References: " << total_mem_ref << endl;
  cout << "Total Page Faults: " << total_pg_entry_faults << endl;
  cout << "Total Flush: " << total_Flushes << endl;
  cout << "Total time: " << total_time << " seconds" << endl;
  cout << "===================================" << endl;
  cout << " " << endl;
  return;
}

/*
  This function helps run the Simulations for LRU, line_count, and Random.
  Param: int page_size, int phy_mem_size, int algorithm
*/
void fifo_sim::run_fifo_sim(int page_size, int phy_mem_size) {
  // calculate the total page faults from physical memory size divided by
  // the page size. we already checked before in the main to
  // see if page_size is bigger than physical memory size.
  // cout << "Start of the Sim function" << endl; // debugging
  int total_faults = phy_mem_size / page_size;
  // initial logical variables
  int total_time = 0;
  int total_mem_ref = 0;
  int total_pg_entry_faults = 0;
  int total_Flushes = 0;

  // Grab the total_faults and read the file.
  // Read_the_File(int total_faults);

  // initialize the clock variables for the timer;
  // Also start the time.
  clock_t start;
  clock_t end;
  start = clock();

  // cout << "Start of the timer" << endl;
  // Read in the file "references.txt"
  FILE *fileptr = fopen("references.txt", "r");

  // At each Simulation start, we assume all entries in the
  // page table is invalid.
  int k = 0;
  struct fifo_page FIFO_PageTable[total_faults];
  while (k < total_faults) {
    FIFO_PageTable[k].valid = false;
    FIFO_PageTable[k].dirty = false;
    FIFO_PageTable[k].addr = 0;
    FIFO_PageTable[k].last_used = 0;
    k++;
  }
  // debugging cout << "After making the FIFO_PageTable" << endl;

  // initialize an character array for the file.
  char file_content[100];
  int line_count = 0;
  int lru = 0;

  // The file references.txt is a list of virtual memeory, or logical memory.
  // The simulator assumes the max virtual memeory 127MB
  while (fgets(file_content, sizeof file_content, fileptr) != NULL) {
    int output = atoi(file_content);

    // calculate the LSB which is used to tell if we need to Read
    // (which is even number), and to Write (which is odd number).
    bool dirty = output % 2;
    int LSB = output - dirty;

    // Find the page entry in the main memory.
    int found = fifo_search(FIFO_PageTable, total_faults, LSB);
    total_mem_ref++; // increment if page entry is found.

    // If the address was return then mark it dirty.
    if (found >= 0) {
      FIFO_PageTable[found].dirty = dirty;
      FIFO_PageTable[found].last_used = lru; // This is used for LRU algorithm.
      total_mem_ref++;
      continue;
    }
    // If it wasn't found in the memory then page fault.
    else {
      total_pg_entry_faults++; // increment the total page faults.

      // Since there is a page fault, it's time to create a new page.
      struct fifo_page new_entry;
      new_entry.valid = true;
      new_entry.dirty = dirty;
      new_entry.addr = LSB;
      new_entry.last_used = lru;

      int z;
      // calculate Fifo
      z = line_count;
      line_count++;
      line_count = line_count % total_faults;

      total_Flushes +=
          FIFO_PageTable[z].dirty; // The victim was dirty then increment flush
      FIFO_PageTable[z] =
          new_entry; // Make a new page entry to replace that spot.
      total_mem_ref++;
    } // end of the else.
  }   // end of while loop.

  // Stop the time and calculate how long it took.
  end = clock();
  total_time = end - start;
  // Print out the  results.
  Display_FIFO_Results(total_time, total_pg_entry_faults, total_mem_ref,
                       total_Flushes);
} // end of the sim function
