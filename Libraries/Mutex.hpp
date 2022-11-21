#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | Mutex.hpp |
//
//   Abstract:
//
//      | RAII over a possession of a Windows Mutex object. |
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

#include "NonCopyable.hpp"
#include "LockBase.hpp"
#include "Handle.hpp"

namespace Coltello::Infra
{
    class Mutex final : public LockBase
    {
        public:
            explicit Mutex();

        public:
			bool TryAcquire() override;
			void Release() override;

        private:
			Handle _handle;
	};
}
