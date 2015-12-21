#include <cassert>
#include "decode.h"

DecodeStage::DecodeStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == IF);
}

void DecodeStage::process() {
	
	if(ins.isStalled()){
		setStalled();
	}
	if(!stalled){
		if(ins.isBranch()){
			int regValueOfArg1 = getReg(ins.getArg1());
			ins.setA(regValueOfArg1);
		}else if(ins.isStore()){
			int regValueOfArg2 = getReg(ins.getArg2());
			ins.setA(regValueOfArg2);
			int regValueOfArg1 = getReg(ins.getArg1());
			ins.setB(regValueOfArg1);
		}else{
			int regValueOfArg2 = getReg(ins.getArg2());
	                ins.setA(regValueOfArg2);
	                int regValueOfArg3 = getReg(ins.getArg3());
	                ins.setB(regValueOfArg3);
		}
	}
	
}

DecodeStage::~DecodeStage() {
}
