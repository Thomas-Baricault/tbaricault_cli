/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <stdexcept>

#include "cli/Context.hpp"


namespace tbaricault::cli
{

    Context::Context(std::span<char*> argv)
    {
        for (char* arg : argv)
            this->_argv.emplace_back(arg);
        return;
    }

    Context::Context(std::span<const char*> argv)
    {
        for (const char* arg : argv)
            this->_argv.emplace_back(arg);
        return;
    }

    Context::Context(std::span<const std::string> argv)
    {
        for (const std::string& arg : argv)
            this->_argv.push_back(arg);
        return;
    }

    Context::Context(std::string_view args)
    {
        std::string arg;
        bool readed = false;
        bool escaped = false;
        char quotes = '\0';
        for (char c : args)
        {
            if (escaped)
            {
                readed = true;
                arg += c;
            }
            else if (c == '\\')
            {
                escaped = true;
            }
            else if (c == quotes)
            {
                quotes = '\0';
            }
            else if (quotes == '\0' && (c == '"' || c == '\''))
            {
                readed = true;
                quotes = c;
            }
            else if (std::isspace(c))
            {
                if (readed)
                    this->_argv.push_back(arg);
                readed = false;
                arg.clear();
            }
            else
            {
                readed = true;
                arg += c;
            }
        }
        if (escaped)
            throw std::invalid_argument("expecting character after '\\'");
        if (quotes)
            throw std::invalid_argument("unclosed quotes");
        if (!arg.empty())
            this->_argv.push_back(arg);
        return;
    }

    bool Context::isEnded() const noexcept
    {
        return (this->_current == this->_argv.size());
    }

    std::ostream& Context::getOut() const noexcept
    {
        return (*this->_out);
    }

    std::ostream& Context::getErr() const noexcept
    {
        return (*this->_err);
    }

    std::size_t Context::getArgc() const noexcept
    {
        return (this->_argv.size());
    }

    std::span<const std::string> Context::getArgv() const noexcept
    {
        return (this->_argv);
    }

    void Context::setOut(std::ostream& out) noexcept
    {
        this->_out = &out;
        return;
    }

    void Context::setErr(std::ostream& err) noexcept
    {
        this->_err = &err;
        return;
    }

    const std::string& Context::currentArg() const
    {
        if (this->_current == 0)
            throw std::runtime_error("no argument to retrieve");
        return (this->_argv[this->_current - 1]);
    }

    const std::string& Context::nextArg()
    {
        if (this->isEnded())
            throw std::runtime_error("no argument left");
        return (this->_argv[this->_current++]);
    }

}
