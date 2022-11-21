#include "ColtelloExecutePrimitive.hpp"

using namespace Coltello;

void wmain()
{
	ColtelloExecutePrimitive::Task kernelTask = {};

	kernelTask.WorkFunction = (PVOID) 0xDEADBEEF;
	kernelTask.WorkParameter = (PVOID) 0xDEADBEEF;

	ColtelloExecutePrimitive executePrimitive(kernelTask);

	executePrimitive.Execute();
	executePrimitive.Pump();
}