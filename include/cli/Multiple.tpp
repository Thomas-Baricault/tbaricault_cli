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

#include "Multiple.hpp"


namespace tbaricault::cli
{

    template<typename T>
    const std::string& Multiple<T>::getValueName() const noexcept
    {
        return (this->_valueName);
    }

    template<typename T>
    Multiple<T>& Multiple<T>::setValueName(std::string value)
    {
        this->_valueName = std::move(value);
        return (*this);
    }

    template<typename T>
    void Multiple<T>::shortHelp(const Context& context) const
    {
        std::ostream& out = context.getOut();
        out << "    --" << this->_name;
        if (this->_short)
            out << ", -" << this->_short;
        out << " <" << this->_valueName << ">..." << std::endl;
        if (!this->_description.empty())
            out << tbaricault::str::indent(this->_description, 8) << std::endl;
        return;
    }

    template<typename T>
    void Multiple<T>::extract(Context& context)
    {
        if (context.isEnded())
            throw std::runtime_error("option '" + this->_name + "' requires an argument");
        const std::string& value = context.nextArg();
        try
        {
            this->_value.emplace_back(tbaricault::uniconvert::convert<std::string, T>(value));
        }
        catch (const std::invalid_argument&)
        {
            throw std::runtime_error("invalid value for '" + this->_name + "', given '" + value + "'");
        }
        return;
    }

}
