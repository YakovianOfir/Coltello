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

#include "Buffer.hpp"
#include "Handle.hpp"

namespace Coltello::Infra
{
	class VirtualAllocation final : public NonCopyable
	{
		public:
			explicit VirtualAllocation(ULONG size);
			virtual ~VirtualAllocation();

		public:
			ULONG Size();
			PVOID Address();

		public:
			void Write(const Buffer& data);

		private:
			ULONG _regionSize;
			PVOID _regionAddress;
	};
}