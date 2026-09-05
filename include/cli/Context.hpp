/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <vector>


namespace tbaricault::cli
{

    /**
     * @brief CLI parsing context
     */
    class Context final
    {

        public:

            /**
             * @brief Constructs a context without arguments
             */
            Context() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Context to copy
             */
            Context(const Context& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Context to move
             */
            Context(Context&& other) noexcept = default;

            /**
             * @brief Constructs a context with arguments from a null-terminated span of C strings
             * 
             * @param argv Null-terminated argument span
             */
            Context(std::span<char*> argv);

            /**
             * @brief Constructs a context with arguments from a null-terminated span of constant C strings
             * 
             * @param argv Null-terminated argument span
             */
            Context(std::span<const char*> argv);

            /**
             * @brief Constructs a context with arguments from a span of strings
             * 
             * @param argv Argument span
             */
            Context(std::span<const std::string> argv);

            /**
             * @brief Constructs a context parsing a command-line string into individual arguments
             * 
             * @param args Command-line string
             * 
             * @throws std::invalid_argument If parsing failed
             */
            Context(std::string_view args);

            /**
             * @brief Destructor
             */
            virtual ~Context() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Context to copy
             * 
             * @return Reference to this context
             */
            Context& operator=(const Context& other) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Arguments to move
             * 
             * @return Reference to this context
             */
            Context& operator=(Context&& other) noexcept = default;

            /**
             * @brief Checks whether arguments iteration is ended
             * 
             * @return `true` if ended, `false` otherwise
             */
            bool isEnded() const noexcept;

            /**
             * @brief Returns the output stream
             * 
             * @return Output stream
             */
            std::ostream& getOut() const noexcept;

            /**
             * @brief Returns the error output stream
             * 
             * @return Error output stream
             */
            std::ostream& getErr() const noexcept;

            /**
             * @brief Returns the argument count
             * 
             * @return Count
             */
            std::size_t getArgc() const noexcept;

            /**
             * @brief Returns the arguments
             * 
             * @return Arguments
             */
            std::span<const std::string> getArgv() const noexcept;

            /**
             * @brief Sets the output stream
             * 
             * @param out Output stream
             */
            void setOut(std::ostream& out) noexcept;

            /**
             * @brief Sets the error output stream
             * 
             * @param err Error output stream
             */
            void setErr(std::ostream& err) noexcept;

            /**
             * @brief Returns the current argument
             * 
             * @return Current argument
             * 
             * @throws std::runtime_error If there is no argument to retrieve
             */
            const std::string& currentArg() const;

            /**
             * @brief Iterates through the arguments
             * 
             * @return Next argument
             * 
             * @throws std::runtime_error If there is no argument left
             */
            const std::string& nextArg();


        private:

            /**
             * @brief Output stream
             */
            std::ostream* _out = &std::cout;

            /**
             * @brief Error output stream
             */
            std::ostream* _err = &std::cerr;

            /**
             * @brief Argument vector
             */
            std::vector<std::string> _argv;

            /**
             * @brief Current argument index
             */
            std::size_t _current = 0;

    };

}
