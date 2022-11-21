#include "LockBase.hpp"
#include "Exception.hpp"

namespace Coltello::Infra
{
    void LockBase::Acquire()
    {
		CHECK_BOOLEAN(TryAcquire(), "Cannot acquire lock object.");
    }
}