
ETISS_LIBPATH=/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/lib/
ETISS_LIBRARIES= -lpthread -ldl -L"/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/lib/" -lETISS  -lpthread -ldl 
ETISS_INCLUDE_DIRS=/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/include 
ETISS_INCLUDES=$(foreach dir,$(ETISS_INCLUDE_DIRS),-I$(dir))
