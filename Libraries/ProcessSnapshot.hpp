#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | ProcessSnapshot.hpp |
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
#include "Handle.hpp"
#include <string>

namespace Coltello::Infra
{
	class ProcessEntry final
	{
		public:
			explicit ProcessEntry();

		public:
			DWORD Pid() const;
			DWORD ParentPid() const;
			DWORD ThreadsCount() const;
			std::string ToString() const;
			std::wstring ExecutableName() const;

		public:
			HANDLE Open() const;
			HANDLE OpenToken() const;
			HANDLE DuplicateToken(const SECURITY_IMPERSONATION_LEVEL& level) const;

		private:
			PPROCESSENTRY32W AsNative();

		private:
			friend class ProcessSnapshot;

		private:
			PROCESSENTRY32W _entry;
	};

	class ProcessSnapshot final : public NonCopyable
	{
		public:
			explicit ProcessSnapshot();

		public:
			bool MoveNext();
			ProcessEntry Current();

		public:
			static ProcessEntry GetByName(const std::wstring& name);
		
		private:
			Handle _snapshot;
			ProcessEntry _currentEntry;
	};
}