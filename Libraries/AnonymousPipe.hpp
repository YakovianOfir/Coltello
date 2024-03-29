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
			ULONG StorageSize() const;

		public:
			void Write(PVOID address, ULONG size);
			void Write(const Buffer& data);

		private:
			ULONG _storageSize;
			Handle _readEndpoint;
			Handle _writeEndpoint;
	};
}