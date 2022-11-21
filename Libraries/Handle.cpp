#include "Handle.hpp"
#include "Protect.hpp"

namespace Coltello::Infra
{
	Handle::Handle() : Handle(INVALID_HANDLE_VALUE)
	{}

	Handle::Handle(HANDLE h) : _handle(h)
	{}

	Handle::~Handle()
	{
		PROTECT_DESTRUCTOR(
		{
			if (Valid() && !::CloseHandle(_handle))
			{
				TRACE_WRN("Cannot close a valid handle object. [{}] [Error: {}]", _handle, ::GetLastError());
			}
		})
	}

	bool Handle::Valid()
	{
		return (_handle != INVALID_HANDLE_VALUE && _handle != nullptr);
	}

	HANDLE Handle::Get()
	{
		return _handle;
	}

	const HANDLE& Handle::Get() const
	{
		return _handle;
	}

	PHANDLE Handle::Reference()
	{
		COLTELLO_ASSERT(!Valid());
		
		return &_handle;
	}
	
	void Handle::Imbue(HANDLE h)
	{
		COLTELLO_ASSERT(!Valid());

		_handle = h;
	}
}