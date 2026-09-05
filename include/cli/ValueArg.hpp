/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


namespace tbaricault::cli
{

    /**
     * @brief Abstract base class adding a value to derived
     * 
     * @tparam This Concrete derived type
     * @tparam T Value type
     */
    template<typename This, typename T>
    class ValueArg
    {

        public:

            /**
             * @brief Default constructor
             */
            ValueArg() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Argument to copy
             */
            ValueArg(const ValueArg& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Argument to move
             */
            ValueArg(ValueArg&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~ValueArg() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Argument to copy
             * 
             * @return Reference to this argument
             */
            ValueArg& operator=(const ValueArg& other) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Argument to move
             * 
             * @return Reference to this argument
             */
            ValueArg& operator=(ValueArg&& other) noexcept = default;

            /**
             * @brief Equivalent to `getValue()`
             */
            operator const T&() const noexcept;

            /**
             * @brief Returns the argument value
             * 
             * @return Argument value
             */
            virtual const T& getValue() const noexcept;


        protected:

            /**
             * @brief Argument value
             */
            T _value = T{};

    };

}


#include "ValueArg.tpp"
