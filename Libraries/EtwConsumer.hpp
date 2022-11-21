#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | EtwConsumer.hpp |
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
	typedef void (__stdcall * EtwConsumerCallback_t)(PVOID context, PEVENT_RECORD record);

	class EtwConsumer final : public NonCopyable
	{
		public:
			explicit EtwConsumer(PWCHAR traceName, EtwConsumerCallback_t callback, PVOID context);
			virtual ~EtwConsumer();

		public:
			void ProcessTraceEvents();

		private:
			static void WINAPI InternalConsumerCallback(PEVENT_RECORD eventRecord);

		private:
			TRACEHANDLE _consumer;
			EtwConsumerCallback_t _callback;
			PVOID _context;
	};
}