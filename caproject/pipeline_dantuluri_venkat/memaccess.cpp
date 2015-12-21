#include <cassert>
#include "memaccess.h"

MemaccessStage::MemaccessStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == EX);
}

void MemaccessStage::process() {

	if(ins.isLoad()){
		int addrs = ins.getAluOut();
		ins.setLoadMemData(getData(addrs));
	}else if(ins.isStore()){
		int addrs = ins.getAluOut();
		setData(addrs, ins.getB());
	}		
		
}

MemaccessStage::~MemaccessStage() {
}
