#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | ColtelloKernelMemory.hpp |
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

#include "ColtelloUserMemory.hpp"

namespace Coltello
{
	class ColtelloKernelMemory final : public Infra::NonCopyable
	{
		public:
			explicit ColtelloKernelMemory();

		public:
			PVOID GetUserAddress();
			PVOID GetKernelAddress();
			void FlushUserMemory();

		private:
			static const ULONG NpfsDataEntrySize = ((ULONG) 0x30);
			static const ULONG NpfsDataEntryPoolTag = ((ULONG) 'rFpN');

		private:
			ColtelloUserMemory _userMemory;
			Infra::AnonymousPipe _transport;
	};
}
