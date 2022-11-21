#include "Exception.hpp"
#include "Mutex.hpp"

namespace Coltello::Infra
{
	Mutex::Mutex() : _handle(::CreateMutexA(NULL, FALSE, NULL))
	{
		CHECK_BOOLEAN(_handle.Valid(), "Cannot create a Mutex object.");
	}

	bool Mutex::TryAcquire()
	{
		return (WaitForSingleObject(_handle.Get(), INFINITE) == WAIT_OBJECT_0);
	}

	void Mutex::Release()
	{
		CHECK_BOOLEAN(::ReleaseMutex(_handle.Get()), "Cannot create a Mutex object.");
	}
}