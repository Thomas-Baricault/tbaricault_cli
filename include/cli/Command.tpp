/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "Command.hpp"


namespace tbaricault::cli
{

    template<typename T>
        requires std::derived_from<T, BaseArg>
    const T& Command::getArg(const std::string& name) const
    {
        if (this->_args.contains(name))
            return (*static_cast<const T*>(this->_args.at(name).get()));
        throw std::invalid_argument("no argument names '" + name + "'");
    }

    template<typename T>
        requires std::derived_from<T, BaseArg>
    Command& Command::add(const Arg<T>& arg)
    {
        if (arg.getName().length() < 2)
            throw std::invalid_argument("invalid argument name '" + arg.getName() + "': argument name length cannot be less than 2");
        if (this->_args.contains(arg.getName()))
            throw std::invalid_argument("invalid argument name '" + arg.getName() + "': duplicated argument name");
        const auto* ptr = dynamic_cast<const ShortedArg<T>*>(&arg);
        if (ptr)
        {
            if (ptr->getShort() && this->_shorts.contains(ptr->getShort()))
                throw std::invalid_argument("invalid argument short name '" + std::string(1, ptr->getShort()) + "': duplicated argument short name");
            this->_shorts[ptr->getShort()] = arg.getName();
        }
        else
            this->_positionals.push_back(arg.getName());
        this->_args[arg.getName()] = std::make_unique<T>(static_cast<const T&>(arg));
        if (auto* commandPtr = dynamic_cast<Command*>(this->_args.at(arg.getName()).get()))
        {
            this->_subcommands.insert(arg.getName());
            commandPtr->_parent = this;
        }
        else if (ptr)
            this->_optionals.insert(arg.getName());
        return (*this);
    }

}
