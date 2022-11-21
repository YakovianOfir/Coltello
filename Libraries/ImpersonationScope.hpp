#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | ImpersonationScope.hpp |
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
	class ImpersonationScope final : public NonCopyable
	{
		public:
			explicit ImpersonationScope(const ProcessEntry& process);
			virtual ~ImpersonationScope();

		private:
			Handle _impersonationToken;
	};
}