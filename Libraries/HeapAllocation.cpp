#include "HeapAllocation.hpp"
#include "Exception.hpp"
#include "Protect.hpp"

namespace Coltello::Infra
{
	HeapAllocation::HeapAllocation(ULONG size): _memoryAddress(nullptr)
	{
		_memoryAddress = ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, size);

		CHECK_ADDRESS(_memoryAddress, "No memory for heap allocation.");
	}
	
	HeapAllocation::~HeapAllocation()
	{
		PROTECT_DESTRUCTOR(
		{
			if (!::HeapFree(::GetProcessHeap(), 0, _memoryAddress))
			{
				TRACE_WRN("Cannot free heap allocation ({}). [Error: ({})]", _memoryAddress, ::GetLastError());
			}
		})
	}

	PVOID HeapAllocation::Address()
	{
		return _memoryAddress;
	}
}
