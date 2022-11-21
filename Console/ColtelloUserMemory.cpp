#include "ColtelloUserMemory.hpp"

namespace Coltello
{
	ColtelloUserMemory::ColtelloUserMemory(): _userRegion(FetchMagicAllocationSize())
	{}

	Infra::VirtualAllocation& ColtelloUserMemory::Region()
	{
		return _userRegion;
	}
	
	ULONG ColtelloUserMemory::FetchMagicAllocationSize()
	{
		ULONG magicSize = 0;

		while (magicSize == 0)
		{
			magicSize = (((__rdtsc() & 0xFF000000) >> 24) * 0x5000);
		}

		return magicSize;
	}
}