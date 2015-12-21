#include <cassert>
#include "stage.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "memaccess.h"
#include "writeback.h"

AbstractStage::getPcPtr AbstractStage::getPc = NULL;
AbstractStage::setPcPtr AbstractStage::setPc = NULL;
AbstractStage::getNextInsPtr AbstractStage::getNextIns = NULL;
AbstractStage::getRegPtr AbstractStage::getReg = NULL;
AbstractStage::setRegPtr AbstractStage::setReg = NULL;
AbstractStage::getDataPtr AbstractStage::getData = NULL;
AbstractStage::setDataPtr AbstractStage::setData = NULL;
AbstractStage::setStopSimulationPtr AbstractStage::stopSimulation = NULL;
AbstractStage::getCyclePtr AbstractStage::getCycle = NULL;
AbstractStage::incStatisticsPtr AbstractStage::incStatistics = NULL;


AbstractStage::AbstractStage(StageType _type, AbstractStage *_prevStage) : stalled(false), type(_type), 
                                                                         prevStage(_prevStage) {
  if (prevStage != NULL)
    prevStage->nextStage = this;
  nextStage = NULL;
}

AbstractStage* AbstractStage::createStage(StageType _type, AbstractStage *_prevStage) {
  // Create a new stage of type _type and set the previous stage to _prevStage
  // Return the newly created stage
    Instruction *noopIns = new Instruction();
    AbstractStage *returnStage=NULL;
    switch (_type){
    case 0: returnStage = new FetchStage(_type,_prevStage);
	    break;
    case 1: returnStage = new DecodeStage(_type,_prevStage);
            break;
    case 2: returnStage = new ExecuteStage(_type,_prevStage);
	    break;
    case 3: returnStage = new MemaccessStage(_type,_prevStage);
            break;
    case 4: returnStage = new WritebackStage(_type,_prevStage);
            break;
    default : returnStage->setInstruction(*noopIns);
    }
    return returnStage;
}

void AbstractStage::setStalled() {
  stalled = true; 
  if (prevStage)
    prevStage->setStalled();
}

void AbstractStage::setUnstalled() { 
  stalled = false; 
  if (prevStage)
    prevStage->setUnstalled();
}

void AbstractStage::updateDependences(int _srcCycle) {
	AbstractStage *pstage=prevStage;
	while(pstage!=NULL){
		Instruction pins = pstage->getInstruction();
		if(pins.getSrcCycle1() == _srcCycle)
			pins.setSrcCycle1(0);
		if(pins.getSrcCycle2() == _srcCycle)
			pins.setSrcCycle2(0);
		pstage->setInstruction(pins);
		pstage->setUnstalled();
		pstage = pstage->prevStage;
	}
  // This function is used to notify (and possibly unstall) the consumer instruction that was stalled
  // due to the current instruction (i.e., producer instruction) of this stage
}

void AbstractStage::setInstruction(Instruction& _ins) {
  ins = _ins;
}

Instruction& AbstractStage::getInstruction() {
  return ins;
}

AbstractStage::~AbstractStage() {
}
