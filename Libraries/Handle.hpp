#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | Handle.hpp |
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

#include "SystemIncludes.hpp"
#include "NonCopyable.hpp"

namespace Coltello::Infra
{
	class Handle final : public NonCopyable
	{
		public:
			explicit Handle(HANDLE h);
			explicit Handle();
			virtual ~Handle();

		public:
			bool Valid();
			HANDLE Get();
			const HANDLE& Get() const;
			
		public:
			PHANDLE Reference();
			void Imbue(HANDLE h);

		private:
			HANDLE _handle;
	};
}
