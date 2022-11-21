#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | EtwSession.hpp |
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

#include "HeapAllocation.hpp"
#include "Buffer.hpp"

namespace Coltello::Infra
{
	class EtwSession final : public NonCopyable
	{
		public:
			explicit EtwSession(GUID& traceGuid, PWCHAR traceName);
			virtual ~EtwSession();

		public:
			void Control(ULONG controlCode);
			void SetInformation(TRACE_INFO_CLASS category, Buffer& data);

		private:
			PEVENT_TRACE_PROPERTIES Properties();

		private:
			static ULONG DescriptorStorageSize(PWCHAR traceName);

		private:
			TRACEHANDLE _session;
			HeapAllocation _sessionDescriptor;
	};
}