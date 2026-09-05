/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "Context.hpp"
#include "Command.hpp"


namespace tbaricault::cli
{

    /**
     * @brief Runs a CLI in a context
     * 
     * @param command Entrypoint command
     * @param context Context to run in
     * 
     * @return Error code
     */
    int run(Command command, Context context);

}
