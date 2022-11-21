#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | Exception.hpp |
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
#include <exception>
#include <stdexcept>
#include <string>

namespace Coltello::Infra
{
    class CmdLineException final : public std::invalid_argument
    {
		public:
			explicit CmdLineException(const std::string& message);
    };

	class RuntimeException final : public std::runtime_error
	{
		public:
			explicit RuntimeException(const std::string& message);
	};

    void CHECK_CMDLINE(bool condition, const std::string& message);
    void CHECK_BOOLEAN(BOOL condition, const std::string& message);
    void CHECK_BOOLEAN(bool condition, const std::string& message);
    void CHECK_ADDRESS(LPVOID address, const std::string& message);
	void CHECK_STATUS(NTSTATUS status, const std::string& message);
}
