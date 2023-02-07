#include "inslib.h"
std::unordered_map<char*, int> BasicBlockRes;
void insert_counter(char* bb){
  BasicBlockRes[bb]++;
}

void insert_out(){
  for (const auto& [BBname, count] : BasicBlockRes) {
    printf("BasicBlock:%s, Counts:%d\n", BBname, count);
  }
}
