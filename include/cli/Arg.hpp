/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <memory>
#include <string>

#include "BaseArg.hpp"


namespace tbaricault::cli
{

    /**
     * @brief Abstract base class representing a CLI argument
     * 
     * @tparam This Concrete derived type
     */
    template<typename This>
    class Arg
        : public BaseArg
    {

        public:

            /**
             * @brief Default constructor
             */
            Arg() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Argument to copy
             */
            Arg(const Arg& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Argument to move
             */
            Arg(Arg&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Arg() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Argument to copy
             * 
             * @return Reference to this argument
             */
            Arg& operator=(const Arg& other) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Argument to move
             * 
             * @return Reference to this argument
             */
            Arg& operator=(Arg&& other) noexcept = default;

            /**
             * @brief Creates a deep copy of the argument
             * 
             * @return Pointer to the copy
             */
            virtual std::unique_ptr<BaseArg> clone() const override;

            /**
             * @brief Sets the argument name
             * 
             * @param value Argument name
             * 
             * @return Reference to this argument
             */
            This& setName(std::string value);

            /**
             * @brief Sets the argument description
             * 
             * @param value Argument description
             * 
             * @return Reference to this argument
             */
            This& setDescription(std::string value);

    };

}


#include "Arg.tpp"
