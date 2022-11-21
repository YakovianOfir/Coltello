#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | AnonymousPipe.hpp |
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

#include "Handle.hpp"
#include "Buffer.hpp"

namespace Coltello::Infra
{
	class AnonymousPipe final : public NonCopyable
	{
		public:
			explicit AnonymousPipe(ULONG bufferSize);

		public:
			void Write(const Buffer& data);

		private:
			Handle _readEndpoint;
			Handle _writeEndpoint;
	};
}