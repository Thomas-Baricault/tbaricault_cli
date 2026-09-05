/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "cli/Flag.hpp"
#include "cli/utils.hpp"


namespace tbaricault::cli
{

    int run(Command command, Context context)
    {
        try
        {
            Command& result = command.parse(context);
            if (result.getArg<Flag>("help").getValue())
                command.help(context);
            else if (result.getCallback())
                return (result.getCallback()(context, result));
            return (0);
        }
        catch (const Command::ParsingError& e)
        {
            context.getErr()
                << "Error: " << e.what() << std::endl
                << "Try '" << e.getCommand().getFullPath() << " --help' for more informations" << std::endl;
            return (1);
        }
    }

}
