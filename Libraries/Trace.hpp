#pragma once

/////////////////////////////////////////////////////////////////
//
//   Copyright (c) Ofir Yakovian. All rights reserved.
//
//   Module Name:
//
//      | Trace.hpp |
//
//   Abstract:
//
//      | Destines a formatted message to the System debugging port,
//      | automatically displayed in the Debugger Command window on
//      | the host computer. Generally, messages sent to this port
//      | might not arrive under Global Flags prohibition.
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

#include <sstream>
#include <iostream>
#include <thread>
#include <string>
#include <fmt\core.h>
#include <fmt\format.h>
#include "SystemNatives.hpp"

namespace Coltello::Infra
{
    enum class TraceLevel
    {
        Information = 0,
        Warning = 1,
        Error = 2,
        Verbose = 3
    };

    std::string TraceLevelToString(const TraceLevel& level);

    template<typename... TArgs>
    void TraceMessage(
        const TraceLevel& level,
        const std::string& function,
        const std::string& format,
        const TArgs&... args) noexcept
    {
        try
        {
            std::ostringstream os;

            os << "[Coltello] ["
                << TraceLevelToString(level)
                << "] (T: [" << std::this_thread::get_id() << "]) "
                << function << "(): "
                << fmt::format(format, args...)
                << std::endl;

            std::cout << os.str();
        }
        catch (...)
        {}
    }
}

#define TRACE_INF(__Format, ...) Coltello::Infra::TraceMessage(Coltello::Infra::TraceLevel::Information, __FUNCTION__, __Format, ##__VA_ARGS__)
#define TRACE_ERR(__Format, ...) Coltello::Infra::TraceMessage(Coltello::Infra::TraceLevel::Error, __FUNCTION__, __Format, ##__VA_ARGS__)
#define TRACE_WRN(__Format, ...) Coltello::Infra::TraceMessage(Coltello::Infra::TraceLevel::Warning, __FUNCTION__, __Format, ##__VA_ARGS__)
#define TRACE_VRB(__Format, ...) Coltello::Infra::TraceMessage(Coltello::Infra::TraceLevel::Verbose, __FUNCTION__, __Format, ##__VA_ARGS__)
#define DEBUG_ONLY(__Expression) __Expression
