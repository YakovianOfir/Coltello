#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | BigPoolInformation.hpp |
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

#include "VirtualAllocation.hpp"

namespace Coltello::Infra
{
	class BigPoolInformation final : public NonCopyable
	{
		public:
			explicit BigPoolInformation();

		public:
			PVOID Locate(ULONG allocationSize, ULONG entrySize, ULONG poolTag);

		private:
			PSYSTEM_BIGPOOL_INFORMATION AsNative();

		private:
			static const ULONG SystemPageSize = 4 * 1024;
			static const ULONG SystemPoolDataSize = 32 * 1024 * 1024;

		private:
			VirtualAllocation _poolData;
	};
}