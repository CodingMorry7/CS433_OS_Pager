#ifndef fifo_sim_H
#define fifo_sim_H
//============================
/*
The Header file for fifo_sim class.
This is the where initialize all the variables, creating
the struct for page, and making the functions.
*/
//============================
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
using namespace std;

class fifo_sim {
private:
  int total_faults;
  int total_time;
  int total_mem_ref;
  int total_pg_entry_faults;
  int total_Flushes;

  struct fifo_page {
    bool valid;
    bool dirty;
    int addr;
    int last_used;
  };

public:
  int fifo_search(struct fifo_page *Table, int total_faults, int file_Out);
  void Display_FIFO_Results(int total_time, int total_pg_entry_faults,
                            int total_mem_ref, int total_Flushes);
  /*
  This function helps run the Simulations for LRU, line_count, and Random.
  Param: int page_size, int phy_mem_size, int algorithm
  */
  void run_fifo_sim(int page_size, int phy_mem_size);
};
#endif
