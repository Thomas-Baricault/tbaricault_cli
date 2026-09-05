/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "Arg.hpp"
#include "ShortedArg.hpp"
#include "ValueArg.hpp"


namespace tbaricault::cli
{

    /**
     * @brief CLI flag argument
     */
    class Flag final
        : public Arg<Flag>
        , public ShortedArg<Flag>
        , public ValueArg<Flag, bool>
    {

        public:

            /**
             * @brief Default constructor
             */
            Flag() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Argument to copy
             */
            Flag(const Flag& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Argument to move
             */
            Flag(Flag&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Flag() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Argument to copy
             * 
             * @return Reference to this argument
             */
            Flag& operator=(const Flag& other) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Argument to move
             * 
             * @return Reference to this argument
             */
            Flag& operator=(Flag&& other) noexcept = default;

            /**
             * @brief Prints the argument short help
             * 
             * @param context Context to print in
             */
            virtual void shortHelp(const Context& context) const override;

            /**
             * @brief Parse and extract arg from context
             * 
             * @param context Context to parse
             * 
             * @throws std::runtime_error If parsing failed
             */
            virtual void extract(Context& context) override;

    };

}
