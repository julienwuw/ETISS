
from FaultXML import *


fboot = Fault()
fboot.triggers_ = Trigger.timeTrigger("core0",1000000000)
fboot.actions_ = Action.commandAction("core0::OR1KVCPU","boot")



trigger = Trigger.variableValueTrigger("core0::OR1KVCPU","ex_pc",256+16+8)
trigger = Trigger.countTrigger(trigger,3)
fault = Fault()
fault.id_ = 2
fault.name_ = "TEST"
fault.actions_ = Action.bitflipAction("core0::OR1KVCPU","R1",1)
fault.triggers_ = trigger

fdeboot = Fault()
fdeboot.triggers_ = Trigger.timeRelativeTrigger("core0::OR1KVCPU",10000000) #1000 cpu cycles
fdeboot.actions_ = Action.commandAction("core0::OR1KVCPU","deboot")
fedbootact = Action.injectionAction(fdeboot)

fault.actions_.append(fedbootact)


print fault.toXML()



with open("../../../faults.xml","w+") as f:
	f.write("<faults>\n")
	f.write(fboot.toXML(offset="\t",isPartOfList=True))
	f.write("\n")
	f.write(fault.toXML(offset="\t",isPartOfList=True))
	f.write("\n</faults>")


