#ifndef __Processor_H__
#define __Processor_H__

class Processor {
public:
	Processor();
	Processor(bool batch, bool debug, bool printMemoryContents);
	beginExecution();
private:
	bool batchMode;
	bool debugMode;
	bool printMemoryContentsMode;


};

#endif