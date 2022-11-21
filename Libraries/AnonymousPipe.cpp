#include "AnonymousPipe.hpp"
#include "Exception.hpp"

namespace Coltello::Infra
{
	AnonymousPipe::AnonymousPipe(ULONG bufferSize)
	{
		CHECK_BOOLEAN(::CreatePipe(
			_readEndpoint.Reference(), 
			_writeEndpoint.Reference(), 
			NULL, bufferSize),
			"Cannot create pipe.");
	}

	void AnonymousPipe::Write(const Buffer& data)
	{
		CHECK_BOOLEAN(::WriteFile(
			_writeEndpoint.Get(), 
			(PVOID) data.data(), 
			(DWORD) data.size(), 
			NULL, NULL), 
			"Cannot write to pipe.");
	}
}