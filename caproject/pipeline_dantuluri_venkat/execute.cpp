#include <cassert>
#include "execute.h"

ExecuteStage::ExecuteStage(StageType _type, AbstractStage *_prevStage) : AbstractStage(_type, _prevStage) {
  assert(prevStage->getType() == ID);
}

void ExecuteStage::process() {
	switch(ins.getType()){
	case 0: return;
	case 1: ins.setAluOut(ins.getA()+ins.getB());
		break;
	case 2: ins.setAluOut(ins.getA()-ins.getB());
		break;
	case 3: ins.setAluOut(ins.getA()*ins.getB());
		break;
	case 4: ins.setAluOut((int)ins.getA()/ins.getB());
		break;
	case 5: ins.setAluOut(ins.getA()^ins.getB());
		break;
	case 6: ins.setAluOut(ins.getA()&ins.getB());
		break;
	case 7: ins.setAluOut(ins.getA()|ins.getB());
		break;
	case 8: ins.setAluOut(ins.getA()+ins.getImmidiate());
		break;
	case 9: ins.setAluOut(ins.getA()-ins.getImmidiate());
		break;
	case 10: ins.setAluOut(ins.getA()+ins.getImmidiate());
		break;
	case 11: ins.setAluOut(ins.getA()+ins.getImmidiate());
		break;
	case 12:if(ins.getA()==0){
			setPc(getPc() + ins.getImmidiate()*4);
		}
		break;
	case 13:if(ins.getA()!=0){
			setPc(getPc() + ins.getImmidiate()*4);
		}
		break;
	}
}

ExecuteStage::~ExecuteStage() {
}
