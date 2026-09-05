/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "ValueArg.hpp"


namespace tbaricault::cli
{

    template<typename This, typename T>
    ValueArg<This, T>::operator const T&() const noexcept
    {
        return (this->_value);
    }

    template<typename This, typename T>
    const T& ValueArg<This, T>::getValue() const noexcept
    {
        return (this->_value);
    }

}
