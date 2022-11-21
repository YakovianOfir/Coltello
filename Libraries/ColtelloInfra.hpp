#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | ColtelloInfra.hpp |
//
//   Abstract:
//
//      | Baseline of the C++ Coltello ecosystem.
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

#include "Trace.hpp"
#include "Assert.hpp"
#include "NonCopyable.hpp"
#include "Exception.hpp"
#include "ILock.hpp"
#include "LockBase.hpp"
#include "Locker.hpp"
#include "Flags.hpp"
#include "Handle.hpp"
#include "Buffer.hpp"
#include "Mutex.hpp"
#include "Section.hpp"
#include "ProcessSnapshot.hpp"
#include "ImpersonationScope.hpp"
#include "PrivilegesScope.hpp"
#include "VirtualAllocation.hpp"
#include "HeapAllocation.hpp"
#include "AnonymousPipe.hpp"
#include "BigPoolInformation.hpp"
#include "EtwSession.hpp"
#include "EtwConsumer.hpp"
#include "GdiFont.hpp"
