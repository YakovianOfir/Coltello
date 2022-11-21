#include "ProcessSnapshot.hpp"
#include "Exception.hpp"
#include "Trace.hpp"

namespace Coltello::Infra
{
	ProcessEntry::ProcessEntry(): _entry {}
	{
		_entry.dwSize = sizeof(PROCESSENTRY32W);
	}
	
	DWORD ProcessEntry::Pid() const
	{
		return _entry.th32ProcessID;
	}
	
	DWORD ProcessEntry::ParentPid() const
	{
		return _entry.th32ParentProcessID;
	}
	
	DWORD ProcessEntry::ThreadsCount() const
	{
		return _entry.cntThreads;
	}

	std::string ProcessEntry::ToString() const
	{
		return fmt::format("[PID: ({})] [PPID: ({})] [Threads: ({})]", Pid(), ParentPid(), ThreadsCount());
	}
	
	std::wstring ProcessEntry::ExecutableName() const
	{
		return std::wstring(_entry.szExeFile);
	}

	PPROCESSENTRY32W ProcessEntry::AsNative()
	{
		return &_entry;
	}

	HANDLE ProcessEntry::Open() const
	{
		HANDLE processHandle = NULL;

		CHECK_BOOLEAN(::OpenProcess(MAXIMUM_ALLOWED, FALSE, Pid()), "Cannot open handle to process.");

		return processHandle;
	}

	HANDLE ProcessEntry::OpenToken() const
	{
		HANDLE tokenHandle = NULL;

		Handle processHandle(Open());

		CHECK_BOOLEAN(::OpenProcessToken(processHandle.Get(), MAXIMUM_ALLOWED, &tokenHandle), "Cannot open handle to token.");

		return tokenHandle;
	}

	HANDLE ProcessEntry::DuplicateToken(const SECURITY_IMPERSONATION_LEVEL& level) const
	{
		HANDLE localTokenHandle = NULL;

		Handle remoteTokenHandle(OpenToken());

		CHECK_BOOLEAN(::DuplicateToken(remoteTokenHandle.Get(), level, &localTokenHandle), "Cannot duplicate token handle.");

		return localTokenHandle;
	}
	
	ProcessSnapshot::ProcessSnapshot(): _snapshot(::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0))
	{
		CHECK_BOOLEAN(_snapshot.Valid(), "Failed to initialize Toolhelp snapshot.");
		
		CHECK_BOOLEAN(::Process32FirstW(_snapshot.Get(), _currentEntry.AsNative()), "Cannot obtain Toolhelp snapshot entry.");
	}
	
	bool ProcessSnapshot::MoveNext()
	{
		RtlZeroMemory(_currentEntry.AsNative(), sizeof(PROCESSENTRY32W));

		return !!::Process32NextW(_snapshot.Get(), _currentEntry.AsNative());
	}
	
	ProcessEntry ProcessSnapshot::Current()
	{
		return _currentEntry;
	}

	ProcessEntry ProcessSnapshot::GetByName(const std::wstring& name)
	{
		ProcessSnapshot snapshot;

		do
		{
			ProcessEntry entry(snapshot.Current());

			if (entry.ExecutableName().find(name) == std::string::npos)
			{
				continue;
			}

			return entry;
		} 
		while (snapshot.MoveNext());

		throw RuntimeException("Cannot find requested process.");
	}
}