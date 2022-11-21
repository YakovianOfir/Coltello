#include "PrivilegesScope.hpp"
#include "Exception.hpp"
#include "Protect.hpp"

namespace Coltello::Infra
{
	PrivilegesScope::PrivilegesScope(ULONG privilege): _privilege(privilege)
	{
		_oldValue = AdjustPrivilege(privilege, TRUE);
	}

	PrivilegesScope::~PrivilegesScope()
	{
		PROTECT_DESTRUCTOR(
		{
			AdjustPrivilege(_privilege, _oldValue);
		})
	}

	BOOLEAN PrivilegesScope::AdjustPrivilege(ULONG privilege, BOOLEAN newValue)
	{
		BOOLEAN oldValue = FALSE;

		CHECK_STATUS(::RtlAdjustPrivilege(privilege, newValue, FALSE, &oldValue), "Cannot adjust privileg.");

		return oldValue;
	}
}