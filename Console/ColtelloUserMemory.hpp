#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | ColtelloUserMemory.hpp |
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

#include "Coltello.hpp"

namespace Coltello
{
	class ColtelloUserMemory final : public Infra::NonCopyable
	{
		public:
			explicit ColtelloUserMemory();

		public:
			Infra::VirtualAllocation& Region();

		private:
			static ULONG FetchMagicAllocationSize();

		private:
			Infra::VirtualAllocation _userRegion;
	};
}
