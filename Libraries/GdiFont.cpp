#include "GdiFont.hpp"
#include "Exception.hpp"
#include "Protect.hpp"

namespace Coltello::Infra
{
	FontOverwriteScope::FontOverwriteScope(PWCHAR path): _targetFontPath(path)
	{
		RemoveResource(_targetFontPath.data());
	}
	
	FontOverwriteScope::~FontOverwriteScope()
	{
		PROTECT_DESTRUCTOR(
		{
			AddResource(_targetFontPath.data());
		})
	}
	
	void FontOverwriteScope::AddResource(PWCHAR path)
	{
		CHECK_BOOLEAN(::AddFontResourceExW(path, 0, NULL), "Cannot add font.");
	}
	
	void FontOverwriteScope::RemoveResource(PWCHAR path)
	{
		CHECK_BOOLEAN(::RemoveFontResourceExW(path, 0, NULL), "Cannot remove font.");
	}
}