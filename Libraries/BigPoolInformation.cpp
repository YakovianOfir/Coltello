#include "BigPoolInformation.hpp"
#include "Exception.hpp"
#include "Assert.hpp"

namespace Coltello::Infra
{
	BigPoolInformation::BigPoolInformation(): _poolData(SystemPoolDataSize)
	{
		ULONG resultLength = 0;

		CHECK_STATUS(::NtQuerySystemInformation(
			SystemBigPoolInformation,
			_poolData.Address(),
			SystemPoolDataSize,
			&resultLength),
			"Cannot capture big pool allocations.");
	}

	PVOID BigPoolInformation::Locate(ULONG allocationSize, ULONG entrySize, ULONG poolTag)
	{
		ULONG_PTR resultAddress = 0;

		for (ULONG i = 0; i < AsNative()->Count; i++)
		{
			PSYSTEM_BIGPOOL_ENTRY entry = &AsNative()->AllocatedInfo[i];
			
			if (entry->TagUlong != poolTag)
			{
				continue;
			}
			
			if (entry->SizeInBytes == (allocationSize + SystemPageSize) || entry->SizeInBytes == (allocationSize + entrySize))
			{
				resultAddress = (ULONG_PTR)entry->VirtualAddress & ~1;

				break;
			}
		}

		COLTELLO_ASSERT(resultAddress != 0);

		return (PVOID)(resultAddress + entrySize);
	}

	PSYSTEM_BIGPOOL_INFORMATION BigPoolInformation::AsNative()
	{
		return (PSYSTEM_BIGPOOL_INFORMATION)(_poolData.Address());
	}
}