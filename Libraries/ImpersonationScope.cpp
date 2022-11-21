#include "ImpersonationScope.hpp"
#include "Exception.hpp"
#include "Protect.hpp"

namespace Coltello::Infra
{
	ImpersonationScope::ImpersonationScope(const ProcessEntry& process): _impersonationToken(process.DuplicateToken(SecurityImpersonation))
	{
		CHECK_BOOLEAN(::SetThreadToken(NULL, _impersonationToken.Get()), "Failed to impersonate token.");
	}
	
	ImpersonationScope::~ImpersonationScope()
	{
		PROTECT_DESTRUCTOR(
		{
			if (!::RevertToSelf())
			{
				TRACE_WRN("Cannot terminate the impersonation. [Error: ({})]", ::GetLastError());
			}
		})
	}
}