/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <concepts>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>

#include "Arg.hpp"
#include "Context.hpp"
#include "ShortedArg.hpp"


namespace tbaricault::cli
{

    /**
     * @brief CLI command argument
     */
    class Command final
        : public Arg<Command>
        , public ShortedArg<Command>
    {

        public:

            /**
             * @brief Error throwed when parsing failed
             */
            class ParsingError final
                : public std::exception
            {

                public:

                    /**
                     * @brief Constructs an error
                     * 
                     * @param command Command in error
                     * @param message Error message
                     */
                    ParsingError(const Command& command, std::string message);

                    /**
                     * @brief Returns the command in error
                     * 
                     * @return Command
                     */
                    const Command& getCommand() const noexcept;

                    /**
                     * @brief Returns the error message
                     * 
                     * @return The error message
                     */
                    const char* what() const noexcept override;


                private:

                    /**
                     * @brief Command in error
                     */
                    const Command& _command;

                    /**
                     * @brief Error message
                     */
                    std::string _message;

            };


            /**
             * @brief Command callback
             */
            using Callback = int (*)(const Context&, const Command&);


            /**
             * @brief Default constructor
             */
            Command();

            /**
             * @brief Copy constructor
             * 
             * @param other Command to copy
             */
            Command(const Command& other);

            /**
             * @brief Move constructor
             * 
             * @param other Command to move
             */
            Command(Command&& other) noexcept;

            /**
             * @brief Destructor
             */
            virtual ~Command() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Command to copy
             * 
             * @return Reference to this command
             */
            Command& operator=(const Command& other);

            /**
             * @brief Move assignment operator
             * 
             * @param other Command to move
             * 
             * @return Reference to this command
             */
            Command& operator=(Command&& other) noexcept;

            /**
             * @brief Returns the command full path
             * 
             * @return Full path
             */
            std::string getFullPath() const;

            /**
             * @brief Returns the command callback
             * 
             * @return Callback
             */
            Callback getCallback() const noexcept;

            /**
             * @brief Returns the argument associated to a name
             * 
             * @tparam T Argument type
             * 
             * @param name Argument name
             * 
             * @return Argument
             * 
             * @throws std::invalid_argument If argument cannot be retrieved
             */
            template<typename T = BaseArg>
                requires std::derived_from<T, BaseArg>
            const T& getArg(const std::string& name) const;

            /**
             * @brief Sets the command callback
             * 
             * @param value Callback
             * 
             * @return Reference to this command
             */
            Command& setCallback(Callback value);

            /**
             * @brief Adds an argument
             * 
             * @tparam T Argument type
             * 
             * @param arg Argument to add
             * 
             * @return Reference to this command
             * 
             * @throws std::invalid_argument If argument conflicts with current command state
             */
            template<typename T>
                requires std::derived_from<T, BaseArg>
            Command& add(const Arg<T>& arg);

            /**
             * @brief Prints help message to context
             * 
             * @param context Context to print in
             */
            void help(const Context& context);

            /**
             * @brief Prints the command short help
             * 
             * @param context Context to print in
             */
            virtual void shortHelp(const Context& context) const override;

            /**
             * @brief Parse command from context
             * 
             * @param context Context to parse
             * 
             * @return Command to execute
             * 
             * @throws ParsingError If parsing failed
             */
            Command& parse(Context& context);


        private:

            /**
             * @brief Command parent
             */
            Command* _parent = nullptr;

            /**
             * @brief Command callback
             */
            Callback _callback = nullptr;

            /**
             * @brief Argument short names
             */
            std::unordered_map<char, std::string> _shorts;

            /**
             * @brief Argument short names
             */
            std::map<std::string, std::unique_ptr<BaseArg>> _args;

            /**
             * @brief Subcommands names
             */
            std::set<std::string> _subcommands;

            /**
             * @brief Positional argument names
             */
            std::vector<std::string> _positionals;

            /**
             * @brief Optional argument names
             */
            std::set<std::string> _optionals;


            /**
             * @brief Resets subcommands parent
             */
            void _resetSubcommandsParent() noexcept;

    };

}


#include "Command.tpp"
