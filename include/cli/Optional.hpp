/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <optional>
#include <string>

#include "Arg.hpp"
#include "ShortedArg.hpp"
#include "ValueArg.hpp"


namespace tbaricault::cli
{

    /**
     * @brief CLI optional argument
     * 
     * @tparam T Value type
     */
    template<typename T>
    class Optional final
        : public Arg<Optional<T>>
        , public ShortedArg<Optional<T>>
        , public ValueArg<Optional<T>, std::optional<T>>
    {

        public:

            /**
             * @brief Default constructor
             */
            Optional() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Argument to copy
             */
            Optional(const Optional& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Argument to move
             */
            Optional(Optional&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Optional() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Argument to copy
             * 
             * @return Reference to this argument
             */
            Optional& operator=(const Optional& other) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Argument to move
             * 
             * @return Reference to this argument
             */
            Optional& operator=(Optional&& other) noexcept = default;

            /**
             * @brief Sets the argument value name
             * 
             * @param value Argument value name
             * 
             * @return Reference to this argument
             */
            Optional& setValueName(std::string value);

            /**
             * @brief Sets the argument default value
             * 
             * @param value Argument default value
             * 
             * @return Reference to this argument
             */
            Optional& setDefault(T value);

            /**
             * @brief Returns the argument value
             * 
             * @return Argument value
             */
            virtual const T& getValue() const noexcept override;

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


        private:

            /**
             * @brief Argument value name
             */
            std::string _valueName;

            /**
             * @brief Argument default value
             */
            T _default = T{};

    };

}


#include "Optional.tpp"
