#include "EtwSession.hpp"
#include "Exception.hpp"
#include "Protect.hpp"

namespace Coltello::Infra
{
	EtwSession::EtwSession(GUID& traceGuid, PWCHAR traceName): 
		_sessionDescriptor(DescriptorStorageSize(traceName)),
		_session(INVALID_PROCESSTRACE_HANDLE)
	{
		Properties()->Wnode.Guid = traceGuid;
		Properties()->Wnode.ClientContext = 1;
		Properties()->Wnode.Flags = WNODE_FLAG_TRACED_GUID;
		Properties()->Wnode.BufferSize = DescriptorStorageSize(traceName);
		Properties()->LogFileMode = EVENT_TRACE_REAL_TIME_MODE | EVENT_TRACE_SYSTEM_LOGGER_MODE;
		Properties()->LoggerNameOffset = sizeof(EVENT_TRACE_PROPERTIES);
		Properties()->MinimumBuffers = 1;
		Properties()->FlushTimer = 1;

		CHECK_BOOLEAN(::StartTraceW(
			&_session, 
			traceName, 
			Properties()) 
			== ERROR_SUCCESS, 
			"Cannot create a trace session.");
	}

	EtwSession::~EtwSession()
	{
		PROTECT_DESTRUCTOR(
		{
			Control(EVENT_TRACE_CONTROL_STOP);
		})
	}
	
	void EtwSession::Control(ULONG controlCode)
	{
		CHECK_BOOLEAN(::ControlTraceW(
			_session, NULL, 
			Properties(), 
			controlCode) 
			== ERROR_SUCCESS, 
			"Cannot control a trace session.");
	}

	void EtwSession::SetInformation(TRACE_INFO_CLASS category, Buffer& data)
	{
		CHECK_BOOLEAN(::TraceSetInformation(
			_session, 
			category, 
			(PVOID) data.data(), 
			(ULONG) data.size()) 
			== ERROR_SUCCESS, 
			"Cannot set informartion of a trace session.");
	}

	PEVENT_TRACE_PROPERTIES EtwSession::Properties()
	{
		return (PEVENT_TRACE_PROPERTIES)(_sessionDescriptor.Address());
	}

	ULONG EtwSession::DescriptorStorageSize(PWCHAR traceName)
	{
		return (ULONG)(sizeof(EVENT_TRACE_PROPERTIES) + wcslen(traceName));
	}
}