#include <stdio.h>
#include <unordered_map>
extern "C" std::unordered_map<char*, int> BasicBlockRes;
extern "C" void insert_counter(char* bb);
extern "C" void insert_out();

