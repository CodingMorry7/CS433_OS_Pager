#ifndef random_sim_H
#define random_sim_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
using namespace std;

class random_sim {
private:
  int total_faults;
  int total_time;
  int total_mem_ref;
  int total_pg_entry_faults;
  int total_Flushes;

  struct rand_page {
    bool valid;
    bool dirty;
    int addr;
    int last_used;
  };

public:
  int rand_search(struct rand_page *Table, int total_faults, int file_Out);
  void Display_Random_Results(int total_time, int total_pg_entry_faults,
                              int total_mem_ref, int total_Flushes);
  void run_Rand_sim(int page_size, int phy_mem_size);
};
#endif
