/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <ostream>
#include <stdexcept>

#include <tbaricault/str.hpp>

#include "cli/Command.hpp"
#include "cli/Flag.hpp"


namespace tbaricault::cli
{

    Command::ParsingError::ParsingError(const Command& command, std::string message)
        : _command(command)
        , _message(std::move(message))
    {
        return;
    }

    const Command& Command::ParsingError::getCommand() const noexcept
    {
        return (this->_command);
    }

    const char* Command::ParsingError::what() const noexcept
    {
        return (this->_message.c_str());
    }

    Command::Command()
        : Arg::Arg()
        , ShortedArg::ShortedArg()
    {
        this->add(Flag()
            .setName("help")
            .setShort('h')
            .setDescription("Show help message")
        );
        return;
    }

    Command::Command(const Command& other)
        : Arg::Arg(other)
        , ShortedArg::ShortedArg(other)
        , _parent(nullptr)
        , _callback(other._callback)
        , _shorts(other._shorts)
        , _subcommands(other._subcommands)
        , _positionals(other._positionals)
        , _optionals(other._optionals)
    {
        for (const auto& [name, arg] : other._args)
            this->_args[name] = (*arg).clone();
        this->_resetSubcommandsParent();
        return;
    }

    Command::Command(Command&& other) noexcept
        : Arg::Arg(std::move(other))
        , ShortedArg::ShortedArg(std::move(other))
        , _parent(other._parent)
        , _callback(other._callback)
        , _shorts(std::move(other._shorts))
        , _args(std::move(other._args))
        , _subcommands(std::move(other._subcommands))
        , _positionals(std::move(other._positionals))
        , _optionals(std::move(other._optionals))
    {
        other._parent = nullptr;
        other._callback = nullptr;
        this->_resetSubcommandsParent();
        return;
    }

    Command& Command::operator=(const Command& other)
    {
        if (&other == this)
            return (*this);
        Arg::operator=(other);
        ShortedArg::operator=(other);
        this->_parent = nullptr;
        this->_callback = other._callback;
        this->_shorts = other._shorts;
        this->_args.clear();
        for (const auto& [name, arg] : other._args)
            this->_args[name] = (*arg).clone();
        this->_resetSubcommandsParent();
        this->_subcommands = other._subcommands;
        this->_positionals = other._positionals;
        this->_optionals = other._optionals;
        return (*this);
    }

    Command& Command::operator=(Command&& other) noexcept
    {
        if (&other == this)
            return (*this);
        Arg::operator=(std::move(other));
        ShortedArg::operator=(std::move(other));
        this->_parent = other._parent;
        this->_callback = other._callback;
        this->_shorts = std::move(other._shorts);
        this->_args = std::move(other._args);
        this->_resetSubcommandsParent();
        this->_subcommands = std::move(other._subcommands);
        this->_positionals = std::move(other._positionals);
        this->_optionals = std::move(other._optionals);
        other._parent = nullptr;
        other._callback = nullptr;
        return (*this);
    }

    std::string Command::getFullPath() const
    {
        std::string result = this->_name;
        Command* command = this->_parent;
        while (command)
            result = command->_name + ' ' + result;
        return (result);
    }

    Command::Callback Command::getCallback() const noexcept
    {
        return (this->_callback);
    }

    Command& Command::setCallback(Callback value)
    {
        this->_callback = value;
        return (*this);
    }

    void Command::help(const Context& context)
    {
        std::ostream& out = context.getOut();
        out << "USAGE:" << std::endl << "    " << this->getFullPath();
        for (const auto& name : this->_positionals)
            out << " <" << name << '>';
        if (!this->_optionals.empty())
            out << " [OPTIONS]";
        if (!this->_subcommands.empty())
            out << "    " << this->_name << " <SUBCOMMAND>" << std::endl;
        out << std::endl;
        if (!this->_description.empty())
            out << std::endl << std::endl << "DESCRIPTION:" << std::endl << tbaricault::str::indent(this->_description, 4) << std::endl;
        if (!this->_subcommands.empty())
        {
            out << std::endl << std::endl << "SUBCOMMANDS:" << std::endl;
            for (const auto& name : this->_subcommands)
            {
                out << std::endl;
                this->_args.at(name)->shortHelp(context);
            }
        }
        if (!this->_positionals.empty())
        {
            out << std::endl << std::endl << "ARGUMENTS:" << std::endl;
            for (const auto& name : this->_positionals)
            {
                out << std::endl;
                this->_args.at(name)->shortHelp(context);
            }
        }
        if (!this->_optionals.empty())
        {
            out << std::endl << std::endl << "OPTIONS:" << std::endl;
            for (const auto& name : this->_optionals)
            {
                out << std::endl;
                this->_args.at(name)->shortHelp(context);
            }
        }
        return;
    }

    void Command::shortHelp(const Context& context) const
    {
        std::ostream& out = context.getOut();
        out << "  " << this->_name;
        if (this->_short)
            out << ", " << this->_short;
        out << std::endl;
        if (!this->_description.empty())
            out << tbaricault::str::indent(this->_description, 6) << std::endl;
        return;
    }

    Command& Command::parse(Context& context)
    {
        try
        {
            bool ignore = false;
            std::size_t i = 0;
            while (!context.isEnded())
            {
                const std::string& arg = context.nextArg();
                if (!ignore)
                {
                    if (arg == "--")
                    {
                        ignore = true;
                        continue;
                    }
                    if (arg == "-h" || arg == "--help")
                    {
                        this->_args.at("help")->extract(context);
                        return (*this);
                    }
                    if (arg.starts_with("-"))
                    {
                        if (arg.starts_with("--"))
                        {
                            std::string s = arg.substr(2);
                            if (!this->_optionals.contains(s))
                                throw std::runtime_error("unknown option '--" + s + "'");
                            this->_args.at(s)->extract(context);
                        }
                        else
                        {
                            for (char c : arg.substr(1))
                            {
                                if (this->_shorts.contains(c))
                                {
                                    const std::string& name = this->_shorts.at(c);
                                    if (this->_optionals.contains(name))
                                    {
                                        this->_args.at(name)->extract(context);
                                        continue;
                                    }
                                }
                                throw std::runtime_error("unknown option '-" + std::string(1, c) + "'");
                            }
                        }
                        continue;
                    }
                }
                if (i == 0)
                {
                    const std::string& name = (
                        arg.length() == 0 && this->_shorts.contains(arg[0])
                            ? this->_shorts.at(arg[0])
                            : arg
                    );
                    if (this->_subcommands.contains(name))
                        return static_cast<Command*>(this->_args.at(name).get())->parse(context);
                }
                if (i == this->_positionals.size())
                    throw std::runtime_error("too many arguments provided");
                this->_args.at(this->_positionals.at(i++))->extract(context);
            }
            if (i < this->_positionals.size())
                throw std::runtime_error("too few arguments provided");
            return (*this);
        }
        catch (const ParsingError& e)
        {
            throw e;
        }
        catch (const std::exception& e)
        {
            throw ParsingError(*this, e.what());
        }
    }

    void Command::_resetSubcommandsParent() noexcept
    {
        for (const auto& name : this->_subcommands)
            static_cast<Command*>(this->_args.at(name).get())->_parent = this;
        return;
    }

}
