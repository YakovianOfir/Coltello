#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | GdiFont.hpp |
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
#include <string>

namespace Coltello::Infra
{
	class FontOverwriteScope final : public NonCopyable
	{
		public:
			explicit FontOverwriteScope(PWCHAR path);
			virtual ~FontOverwriteScope();

		public:
			static void AddResource(PWCHAR path);
			static void RemoveResource(PWCHAR path);

		private:
			std::wstring _targetFontPath;
	};
}
