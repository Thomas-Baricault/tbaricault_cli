/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


namespace tbaricault::cli
{

    /**
     * @brief Abstract base class adding a short name to derived
     * 
     * @tparam This Concrete derived type
     */
    template<typename This>
    class ShortedArg
    {

        public:

            /**
             * @brief Default constructor
             */
            ShortedArg() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Argument to copy
             */
            ShortedArg(const ShortedArg& other) noexcept = default;

            /**
             * @brief Move constructor
             * 
             * @param other Argument to move
             */
            ShortedArg(ShortedArg&& other) noexcept;

            /**
             * @brief Destructor
             */
            virtual ~ShortedArg() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Argument to copy
             * 
             * @return Reference to this argument
             */
            ShortedArg& operator=(const ShortedArg& other) noexcept = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Argument to move
             * 
             * @return Reference to this argument
             */
            ShortedArg& operator=(ShortedArg&& other) noexcept;

            /**
             * @brief Returns the argument short name
             * 
             * @return Short name
             */
            char getShort() const noexcept;

            /**
             * @brief Sets the argument short
             * 
             * @param value Argument short
             * 
             * @return Reference to this argument
             */
            This& setShort(char value) noexcept;


        protected:

            /**
             * @brief Argument short
             */
            char _short;

    };

}


#include "ShortedArg.tpp"
