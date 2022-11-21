#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | ColtelloExecutePrimitive.hpp |
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

#include "ColtelloKernelMemory.hpp"

namespace Coltello
{
	class ColtelloExecutePrimitive final : public Infra::NonCopyable
	{
		public:
			struct Task
			{
				PVOID WorkFunction;
				PVOID WorkParameter;
			};

			struct State
			{
				PXSGLOBALS Globals;
				PRTL_BALANCED_LINKS TrampolineParameter;
			};

		public:
			explicit ColtelloExecutePrimitive(Task& task);

		public:
			void Pump();
			void Execute();

		private:
			void SetTaskCallback(Task& task);
			void StartEtwSession();

		private:
			PCONTEXT_PAGE UserContextPage();
			PCONTEXT_PAGE KernelContextPage();

		private:
			PRTL_BALANCED_LINKS TrampolineParameter();
			PXSGLOBALS PxsGlobals();

		private:
			static void WINAPI ColtelloEtwCallback(PVOID context, PEVENT_RECORD eventRecord);

		private:
			Infra::EtwSession _traceSession;
			Infra::EtwConsumer _traceConsumer;
			ColtelloKernelMemory _kernelRegion;
			ColtelloExecutePrimitive::State _state;
	};
}