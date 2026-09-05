/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "Arg.hpp"
#include "ValueArg.hpp"


namespace tbaricault::cli
{

    /**
     * @brief CLI positional argument
     * 
     * @tparam T Value type
     */
    template<typename T>
    class Positional
        : public Arg<Positional<T>>
        , public ValueArg<Positional<T>, T>
    {

        public:

            /**
             * @brief Default constructor
             */
            Positional() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Argument to copy
             */
            Positional(const Positional& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Argument to move
             */
            Positional(Positional&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Positional() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Argument to copy
             * 
             * @return Reference to this argument
             */
            Positional& operator=(const Positional& other) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Argument to move
             * 
             * @return Reference to this argument
             */
            Positional& operator=(Positional&& other) noexcept = default;

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
             * 
             * @warning This function will always throw for command, use `parse` instead
             */
            virtual void extract(Context& context) override;

    };

}


#include "Positional.tpp"
