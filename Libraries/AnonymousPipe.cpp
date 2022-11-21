#include "AnonymousPipe.hpp"
#include "Exception.hpp"

namespace Coltello::Infra
{
	AnonymousPipe::AnonymousPipe(ULONG bufferSize): _storageSize(bufferSize)
	{
		CHECK_BOOLEAN(::CreatePipe(
			_readEndpoint.Reference(), 
			_writeEndpoint.Reference(), 
			NULL, bufferSize),
			"Cannot create pipe.");
	}

	void AnonymousPipe::Write(PVOID dataAddress, ULONG dataSize)
	{
		CHECK_BOOLEAN(::WriteFile(
			_writeEndpoint.Get(),
			dataAddress, dataSize,
			NULL, NULL),
			"Cannot write to pipe.");
	}

	void AnonymousPipe::Write(const Buffer& data)
	{
		Write((PVOID) data.data(), (ULONG) data.size());
	}

	ULONG AnonymousPipe::StorageSize() const
	{
		return _storageSize;
	}
}