#include "ColtelloKernelMemory.hpp"

namespace Coltello
{
	ColtelloKernelMemory::ColtelloKernelMemory():
		_userMemory(), 
		_transport(_userMemory.Region().Size())
	{}

	void ColtelloKernelMemory::FlushUserMemory()
	{
		_transport.Write(
			_userMemory.Region().Address(),
			_userMemory.Region().Size());
	}

	PVOID ColtelloKernelMemory::GetUserAddress()
	{
		return _userMemory.Region().Address();
	}

	PVOID ColtelloKernelMemory::GetKernelAddress()
	{
		Infra::BigPoolInformation bpi;

		return 
			bpi.Locate(
			_userMemory.Region().Size(),
			NpfsDataEntrySize,
			NpfsDataEntryPoolTag);

	}
}

