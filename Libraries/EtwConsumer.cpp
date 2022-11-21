#include "EtwConsumer.hpp"
#include "Exception.hpp"
#include "Protect.hpp"
#include "Assert.hpp"

namespace Coltello::Infra
{
	EtwConsumer::EtwConsumer(PWCHAR traceName, EtwConsumerCallback_t callback, PVOID context):
		_consumer(INVALID_PROCESSTRACE_HANDLE),
		_callback(callback),
		_context(context)
	{
		EVENT_TRACE_LOGFILEW logFile = {};

		logFile.LoggerName = traceName;
		logFile.ProcessTraceMode = PROCESS_TRACE_MODE_REAL_TIME | PROCESS_TRACE_MODE_EVENT_RECORD;
		logFile.EventRecordCallback = InternalConsumerCallback;
		logFile.Context = (PVOID) (this);

		CHECK_BOOLEAN(((_consumer = ::OpenTraceW(&logFile)) != INVALID_PROCESSTRACE_HANDLE), "Cannot create a trace session consumer.");
	}
	
	EtwConsumer::~EtwConsumer()
	{
		PROTECT_DESTRUCTOR(
		{
			if (::CloseTrace(_consumer) != ERROR_SUCCESS)
			{
				TRACE_WRN("Cannot close a trace session cosumer. [Error: ({})]", ::GetLastError());
			}
		})
	}
	
	void EtwConsumer::ProcessTraceEvents()
	{
		CHECK_BOOLEAN(::ProcessTrace(&_consumer, 1, NULL, NULL) == ERROR_SUCCESS, "Cannot delivers trace events.");
	}

	void __stdcall EtwConsumer::InternalConsumerCallback(PEVENT_RECORD eventRecord)
	{
		PROTECT_CALLBACK(
		{
			COLTELLO_ASSERT(eventRecord != nullptr);

			auto * etwConsumer = (EtwConsumer *) eventRecord->UserContext;
			
			COLTELLO_ASSERT(etwConsumer != nullptr);

			etwConsumer->_callback(etwConsumer->_context, eventRecord);
		})
	}
}