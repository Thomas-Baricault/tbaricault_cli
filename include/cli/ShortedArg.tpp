/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "ShortedArg.hpp"


namespace tbaricault::cli
{

    template<typename This>
    ShortedArg<This>::ShortedArg(ShortedArg&& other) noexcept
        : _short(other._short)
    {
        other._short = '\0';
        return;
    }

    template<typename This>
    ShortedArg<This>& ShortedArg<This>::operator=(ShortedArg&& other) noexcept
    {
        if (&other == this)
            return (*this);
        this->_short = other._short;
        other._short = '\0';
        return (*this);
    }

    template<typename This>
    char ShortedArg<This>::getShort() const noexcept
    {
        return (this->_short);
    }

    template<typename This>
    This& ShortedArg<This>::setShort(char value) noexcept
    {
        this->_short = value;
        return (static_cast<This&>(*this));
    }

}
