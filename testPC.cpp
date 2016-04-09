#include "PC.h"

using namespace std;

int main()
{	
	PC* myPC = new PC();
	cout << "Expected 1: " << myPC->isEmpty() << endl;

	vector<Instruction> vec1;

	myPC = new PC(vec1);
	cout << "Expected 1: " << myPC->isEmpty() << endl;    

}
