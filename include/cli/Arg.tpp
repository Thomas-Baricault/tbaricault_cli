/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "Arg.hpp"


namespace tbaricault::cli
{

    template<typename This>
    std::unique_ptr<BaseArg> Arg<This>::clone() const
    {
        return (std::make_unique<This>(*static_cast<const This*>(this)));
    }

    template<typename This>
    This& Arg<This>::setName(std::string value)
    {
        this->_name = std::move(value);
        return (static_cast<This&>(*this));
    }

    template<typename This>
    This& Arg<This>::setDescription(std::string value)
    {
        this->_description = std::move(value);
        return (static_cast<This&>(*this));
    }

}
