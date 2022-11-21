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
	class EtwConsumer final : public NonCopyable
	{
		struct CallbackDescriptor
		{
			PEVENT_RECORD_CALLBACK consumerCallback;
		};

		public:
			explicit EtwConsumer(PWCHAR traceName, CallbackDescriptor& callback);
			virtual ~EtwConsumer();

		public:
			void ProcessTraceEvents();

		private:
			static void WINAPI InternalConsumerCallback(PEVENT_RECORD eventRecord);

		private:
			TRACEHANDLE _consumer;
			CallbackDescriptor _callback;
	};
}