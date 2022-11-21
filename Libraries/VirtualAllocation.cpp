#include "VirtualAllocation.hpp"
#include "SystemNatives.hpp"
#include "Exception.hpp"
#include "Protect.hpp"

namespace Coltello::Infra
{
	VirtualAllocation::VirtualAllocation(ULONG size): _memoryAddress(nullptr)
	{
		_memoryAddress = ::VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		CHECK_ADDRESS(_memoryAddress, "No memory for virtual allocation.");
	}
	
	VirtualAllocation::~VirtualAllocation()
	{
		PROTECT_DESTRUCTOR(
		{
			if (!::VirtualFree(_memoryAddress, 0, MEM_RELEASE))
			{
				TRACE_WRN("Cannot free virtual allocation ({}). [Error: ({})]", _memoryAddress, ::GetLastError());
			}
		})
	}

	PVOID VirtualAllocation::Address()
	{
		return _memoryAddress;
	}
}
