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
     * @brief CLI optional argument that can be invoked multiple times
     * 
     * @tparam T Value type
     */
    template<typename T>
    class Multiple final
        : public Arg<Multiple<T>>
        , public ShortedArg<Multiple<T>>
        , public ValueArg<Multiple<T>, std::vector<T>>
    {

        public:

            /**
             * @brief Default constructor
             */
            Multiple() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Argument to copy
             */
            Multiple(const Multiple& other) = default;

            /**
             * @brief Move constructor
             * 
             * @param other Argument to move
             */
            Multiple(Multiple&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~Multiple() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Argument to copy
             * 
             * @return Reference to this argument
             */
            Multiple& operator=(const Multiple& other) = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Argument to move
             * 
             * @return Reference to this argument
             */
            Multiple& operator=(Multiple&& other) noexcept = default;

            /**
             * @brief Returns the argument value name
             * 
             * @return Value name
             */
            const std::string& getValueName() const noexcept;

            /**
             * @brief Sets the argument value name
             * 
             * @param value Argument value name
             * 
             * @return Reference to this argument
             */
            Multiple& setValueName(std::string value);

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
             * @brief Value name
             */
            std::string _valueName;

    };

}


#include "Multiple.tpp"
