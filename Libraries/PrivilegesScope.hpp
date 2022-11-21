#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | PrivilegesScope.hpp |
//
//   Author:
//
//      | Ofir Yakovian (@ofirkov) |
//
//   Environment:
//
//      | User Mode |
//
/////////////////////////////////////////////////////////////////

#include "ProcessSnapshot.hpp"

namespace Coltello::Infra
{
	class PrivilegesScope final : public NonCopyable
	{
		public:
			explicit PrivilegesScope(ULONG privilege);
			virtual ~PrivilegesScope();

		private:
			static BOOLEAN AdjustPrivilege(ULONG privilege, BOOLEAN value);

		private:
			ULONG _privilege;
			BOOLEAN _oldValue;
	};
}