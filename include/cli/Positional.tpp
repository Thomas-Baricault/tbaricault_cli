/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <ostream>
#include <stdexcept>

#include <tbaricault/str.hpp>
#include <tbaricault/uniconvert.hpp>

#include "Positional.hpp"


namespace tbaricault::cli
{

    template<typename T>
    void Positional<T>::shortHelp(const Context& context) const
    {
        std::ostream& out = context.getOut();
        out << "    " << this->_name << std::endl;
        if (!this->_description.empty())
            out << tbaricault::str::indent(this->_description, 8) << std::endl;
        return;
    }

    template<typename T>
    void Positional<T>::extract(Context& context)
    {
        const std::string& value = context.currentArg();
        try
        {
            this->_value = tbaricault::uniconvert::convert<std::string, T>(value);
        }
        catch (const std::invalid_argument&)
        {
            throw std::runtime_error("invalid value for '" + this->_name + "', given '" + value + "'");
        }
        return;
    }

}
