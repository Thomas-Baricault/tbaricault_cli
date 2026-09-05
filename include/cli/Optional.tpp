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

#include "Optional.hpp"


namespace tbaricault::cli
{

    template<typename T>
    const T& Optional<T>::getValue() const noexcept
    {
        if (this->_value.has_value())
            return (this->_value.value());
        else
            return (this->_default);
    }

    template<typename T>
    Optional<T>& Optional<T>::setValueName(std::string value)
    {
        this->_valueName = std::move(value);
        return (*this);
    }

    template<typename T>
    Optional<T>& Optional<T>::setDefault(T value)
    {
        this->_default = std::move(value);
        return (*this);
    }

    template<typename T>
    void Optional<T>::shortHelp(const Context& context) const
    {
        std::ostream& out = context.getOut();
        out << "    --" << this->_name;
        if (this->_short)
            out << ", -" << this->_short;
        out << " <" << this->_valueName << '=' << tbaricault::uniconvert::convert<T, std::string>(this->_default) << '>' << std::endl;
        if (!this->_description.empty())
            out << tbaricault::str::indent(this->_description, 8) << std::endl;
        return;
    }

    template<typename T>
    void Optional<T>::extract(Context& context)
    {
        if (context.isEnded())
            throw std::runtime_error("option '" + this->_name + "' requires an argument");
        const std::string& value = context.nextArg();
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
