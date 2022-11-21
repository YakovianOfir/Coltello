#include "Section.hpp"
#include "Exception.hpp"
#include "Protect.hpp"

namespace Coltello::Infra
{
	Section::View::View(Handle& section, ULONG size): _mappedAddress(nullptr)
	{
		_mappedAddress = ::MapViewOfFile(section.Get(), FILE_MAP_ALL_ACCESS, 0, 0, size);

		CHECK_ADDRESS(_mappedAddress, "Cannot map a view of a section.");
	}
	
	Section::View::~View()
	{
		PROTECT_DESTRUCTOR(
		{
			if (!::UnmapViewOfFile(_mappedAddress))
			{
				TRACE_WRN("Cannot unmap a view of a section. [{}]", _mappedAddress);
			}
		})
	}

	PVOID Section::View::Address()
	{
		return _mappedAddress;
	}

	Section::Section(const std::wstring& name)
	{
		UNICODE_STRING sectionName = {};
		OBJECT_ATTRIBUTES objectAttributes = {};

		RtlInitUnicodeString(&sectionName, name.c_str());

		InitializeObjectAttributes(
			&objectAttributes,
			&sectionName,
			OBJ_CASE_INSENSITIVE,
			NULL,
			NULL);

		CHECK_STATUS(::ZwOpenSection(_handle.Reference(), MAXIMUM_ALLOWED, &objectAttributes), "Cannot open section.");
	}

	Section::View Section::MapView(ULONG size)
	{
		return Section::View(_handle, size);
	}
}