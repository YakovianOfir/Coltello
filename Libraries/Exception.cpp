#include "SystemIncludes.hpp"
#include "Exception.hpp"
#include "Trace.hpp"

namespace Coltello::Infra
{
    CmdLineException::CmdLineException(const std::string& message) 
		: std::invalid_argument(message.c_str())
    {}

	RuntimeException::RuntimeException(const std::string& message)
		: std::runtime_error(message.c_str())
	{}

	void CHECK_BOOLEAN(BOOL condition, const std::string& message)
	{
		CHECK_BOOLEAN(!!condition, message);
	}

	void CHECK_ADDRESS(LPVOID address, const std::string& message)
	{
		CHECK_BOOLEAN(address != nullptr, message);
	}
	
	void CHECK_BOOLEAN(bool condition, const std::string& message)
	{
		if (!condition)
		{
			throw RuntimeException(fmt::format("{} (Code: {})", message, ::GetLastError()));
		}
	}

	void CHECK_STATUS(NTSTATUS status, const std::string& message)
	{
		if (!NT_SUCCESS(status))
		{
			throw RuntimeException(fmt::format("{} (Status: {})", message, status));
		}
	}

	void CHECK_CMDLINE(bool condition, const std::string& message)
	{
		if (!condition)
		{
			throw CmdLineException(message);
		}
	}
}
