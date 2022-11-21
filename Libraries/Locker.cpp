#include "Locker.hpp"
#include "Exception.hpp"
#include "Protect.hpp"

namespace Coltello::Infra
{
    Locker::Locker(LockBase& lockObject) : Locker(lockObject, Policy::ForceLock)
    {}

    Locker::Locker(LockBase& lockObject, const Policy& lockPolicy) : _lockObject(lockObject), _isLocked(false)
    {
        _isLocked = _lockObject.TryAcquire();

		CHECK_BOOLEAN(lockPolicy == Policy::TryLock || _isLocked, "Cannot acquire lock according to policy.");
    }

    Locker::~Locker()
    {
        PROTECT_DESTRUCTOR(
        {
            if (_isLocked)
            {
                _lockObject.Release();
            }
        })
    }

    bool Locker::IsAcquired() const
    {
        return _isLocked;
    }
}
