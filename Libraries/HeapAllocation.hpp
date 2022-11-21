#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | HeapAllocation.hpp |
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
	class HeapAllocation final : public NonCopyable
	{
		public:
			explicit HeapAllocation(ULONG size);
			virtual ~HeapAllocation();

		public:
			PVOID Address();

		private:
			PVOID _memoryAddress;
	};
}