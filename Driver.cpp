#include "fifo_sim.h"
#include "lru_sim.h"
#include "random_sim.h"
#include <math.h>
//======================================
/*
Program Assignment 5: Simulation of Page Replacement Algorithms
Names: Chris Morikawa and Haley Minshell
Date: 12/9/2016

Assumption: We assume at the beginning of the simulator that the
physical memory is empty (i.e. all page table entries are invalid). Also
we assume that the page size(is a number of the power of 2) is either or between
256(2^8) and 8192(2^13), also the
physical memory size is by power of 2. The maximum virtual memory address is
128MB (2^27 bytes), and
the  number off addresses in the file is 5 million.

Description: This is a simulator that analyzes different memory page replacement
algorithms(Random, line_count, and LRU). The simulator will read a sequence of
logical
memory references from a file (references.txt), which contains a list of
Virtual(logical) memory
byte addresses accessed by a program. The program will output statistics for
different
algorithms such as, total number of memory references, total number of page
faults,
total number of flushes(this is when the victim page was dirty), and total time
it took.

Instructions:
Setup:
Make sure that the directory has all of our headers, .cpp files, and our Makefile.
1)Type "make" in the directory to where you want to run the program.
2)After typing make and executable is made called: "cs433_hw5"
3)To run the program type: "./cs433_hw5 <int> <int>"
**NOTE** - The two ints are for two raise to. So if you want 256 for the page size,
then type "8" for the first <int>.The first int is for page size, and the second int is for physical memory size. MAKE SURE that physical memory size is bigger than page size.
 
complier: g++
file type: source file
*/
//========================================

int main(int argc, char *argv[]) {
  // creating objects for the each of the simulators
  fifo_sim fifo;
  lru_sim lru;
  random_sim rand_;
  // initial variables for the user's commmands
  int page_pow = atoi(argv[1]);
  int phy_pow = atoi(argv[2]);
  // place holders for the values power.
  int page_size;
  int phy_mem_size;

  // If the command line has more or less values than 3.
  if (argc != 3) {
    cerr << "Sorry! That is not the correct number of command line options."
         << endl
         << "It has to be: " << argv[0] << endl
         << "<power num for page size> <power num for physical mem size> "
         << endl;
    return -1;
  }

  // If the user entered an incorrect range, then report back.
  if ((page_pow < 8) || (page_pow > 13)) {
    cerr << "Sorry but you have the incorrect number for page size" << endl
         << "The minimum is 8 and the max is 13, these numbers are used to "
            "raise "
         << "for the power of 2" << endl;
    return -1;
  }
  page_size = pow(2, page_pow); // two raised to the power between 8 and 13.
  // If the user entered an incorrect range, then report back.

  if ((phy_pow < 0) || (phy_pow > 31)) {
    cerr << "Sorry but you have the incorrect number for physcial memroy size"
         << endl
         << "The minimum is 8 and the max is 31, these numbers are used to "
            "raise "
         << "for the power of 2" << endl;
    return -1;
  }
  phy_mem_size = pow(2, phy_pow); // two raise to the power between 0 and 31.
  // If the physcial memeory size is less than the page size.
  if (phy_mem_size < page_size) {
    cerr << "ERROR!" << endl
         << "The Physical Memory size has to be bigger than the Page size."
         << endl;
    return -1;
  }
  // The start of the simulatorT.
  cout << "====================================" << endl;
  cout << "PAGE TABLE SIMULATOR" << endl;
  cout << "By Chris Morikawa and Haley Minshell" << endl;
  cout << "====================================" << endl;

  fifo.run_fifo_sim(page_size, phy_mem_size);
  lru.run_LRU_sim(page_size, phy_mem_size);
  rand_.run_Rand_sim(page_size, phy_mem_size);
  return 0;
}
