#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | VirtualAllocation.hpp |
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

#include "Handle.hpp"

namespace Coltello::Infra
{
	class VirtualAllocation final : public NonCopyable
	{
		public:
			explicit VirtualAllocation(ULONG size);
			virtual ~VirtualAllocation();

		public:
			PVOID Address();

		private:
			PVOID _memoryAddress;
	};
}