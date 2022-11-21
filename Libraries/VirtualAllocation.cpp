#include "VirtualAllocation.hpp"
#include "Exception.hpp"
#include "Protect.hpp"
#include "Buffer.hpp"

namespace Coltello::Infra
{
	VirtualAllocation::VirtualAllocation(ULONG size): _regionSize(size), _regionAddress(nullptr)
	{
		_regionAddress = ::VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		CHECK_ADDRESS(_regionAddress, "No memory for virtual allocation.");
	}
	
	VirtualAllocation::~VirtualAllocation()
	{
		PROTECT_DESTRUCTOR(
		{
			if (!::VirtualFree(_regionAddress, 0, MEM_RELEASE))
			{
				TRACE_WRN("Cannot free virtual allocation ({}). [Error: ({})]", _regionAddress, ::GetLastError());
			}
		})
	}

	void VirtualAllocation::Write(const Buffer& data)
	{
		RtlCopyMemory(Address(), data.data(), data.size());
	}

	ULONG VirtualAllocation::Size()
	{
		return _regionSize;
	}

	PVOID VirtualAllocation::Address()
	{
		return _regionAddress;
	}
}
