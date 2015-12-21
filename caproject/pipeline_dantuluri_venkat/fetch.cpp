#include <cassert>
#include "fetch.h"

FetchStage::FetchStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage == NULL);
}

void FetchStage::process() {
if(!stalled){
  int pc = getPc();
  ins = getNextIns();
  ins.setFetchedAtCycle(getCycle());
  incStatistics(FETCHEDINS); 
  setPc(pc+4);
}
   
}

FetchStage::~FetchStage() {
}
