/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include "cli/BaseArg.hpp"


namespace tbaricault::cli
{

    const std::string& BaseArg::getName() const noexcept
    {
        return (this->_name);
    }

    const std::string& BaseArg::getDescription() const noexcept
    {
        return (this->_description);
    }

    void BaseArg::extract(Context&)
    {
        throw std::runtime_error("`extract` isn't implemented");
    }

}
