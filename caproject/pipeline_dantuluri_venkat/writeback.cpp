#include <cassert>
#include "writeback.h"

WritebackStage::WritebackStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == MEM);
}

void WritebackStage::process() {

	if(!ins.isStore() && !ins.isBranch()){
		if(ins.isLoad()){
			setReg(ins.getArg1(),ins.getLoadMemData());
		}else if(ins.isAluReg() || ins.isAluImm()){
			setReg(ins.getArg1(),ins.getAluOut());
		}
		updateDependences(ins.getFetchedAtCycle());
	}
}

WritebackStage::~WritebackStage() {
}
