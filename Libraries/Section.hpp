#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | Section.hpp |
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

#include "NonCopyable.hpp"
#include "Handle.hpp"
#include <string>

namespace Coltello::Infra
{
	class Section final : public NonCopyable
	{
		class View final : public NonCopyable
		{
			public:
				explicit View(Handle& section, ULONG size);
				virtual ~View();

			public:
				PVOID Address();

			private:
				PVOID _mappedAddress;
		};

		public:
			explicit Section(const std::wstring& name);

		public:
			View MapView(ULONG size);

		private:
			Handle _handle;
	};
}
