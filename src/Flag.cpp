/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <ostream>

#include <tbaricault/str.hpp>

#include "cli/Flag.hpp"


namespace tbaricault::cli
{

    void Flag::shortHelp(const Context& context) const
    {
        std::ostream& out = context.getOut();
        out << "    --" << this->_name;
        if (this->_short)
            out << ", -" << this->_short;
        out << std::endl;
        if (!this->_description.empty())
            out << tbaricault::str::indent(this->_description, 8) << std::endl;
        return;
    }

    void Flag::extract(Context&)
    {
        this->_value = true;
        return;
    }

}
