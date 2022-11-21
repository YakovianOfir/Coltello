#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | Coltello.hpp |
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

#include "ColtelloInfra.hpp"

typedef struct _CONTEXT_PAGE
{
	RTL_BALANCED_LINKS Header;
	UCHAR Reserved[0x50];
	WORK_QUEUE_ITEM WorkItem;
} CONTEXT_PAGE, *PCONTEXT_PAGE;

DEFINE_GUID(g_EtwTraceGuid,
	0x53636210,
	0xbe24,
	0x1264,
	0xc6, 0xa5, 0xf0, 0x9c, 0x59, 0x88, 0x1e, 0xbd);

extern WCHAR g_EtwTraceName[] = L"Coltello-ETW";
extern WCHAR g_GdiFontName[] = L"C:\\windows\\fonts\\arial.ttf";



