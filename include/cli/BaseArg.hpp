/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <memory>
#include <string>

#include "Context.hpp"


namespace tbaricault::cli
{

    /**
     * @brief Abstract base class representing a CLI argument
     */
    class BaseArg
    {

        public:

            /**
             * @brief Default constructor
             */
            BaseArg() noexcept = default;

            /**
             * @brief Copy constructor
             * 
             * @param other Argument to copy
             */
            BaseArg(const BaseArg& other) noexcept = default;

            /**
             * @brief Move constructor
             * 
             * @param other Argument to move
             */
            BaseArg(BaseArg&& other) noexcept = default;

            /**
             * @brief Destructor
             */
            virtual ~BaseArg() noexcept = default;

            /**
             * @brief Copy assignment operator
             * 
             * @param other Argument to copy
             * 
             * @return Reference to this argument
             */
            BaseArg& operator=(const BaseArg& other) noexcept = default;

            /**
             * @brief Move assignment operator
             * 
             * @param other Argument to move
             * 
             * @return Reference to this argument
             */
            BaseArg& operator=(BaseArg&& other) noexcept = default;

            /**
             * @brief Constructs a deep copy of the argument
             * 
             * @return Pointer to the copy
             */
            virtual std::unique_ptr<BaseArg> clone() const = 0;

            /**
             * @brief Returns the argument name
             * 
             * @return Name
             */
            const std::string& getName() const noexcept;

            /**
             * @brief Returns the argument description
             * 
             * @return Description
             */
            const std::string& getDescription() const noexcept;

            /**
             * @brief Prints the argument short help
             * 
             * @param context Context to print in
             */
            virtual void shortHelp(const Context& context) const = 0;

            /**
             * @brief Parse and extract arg from context
             * 
             * @param context Context to parse
             * 
             * @throws std::runtime_error If parsing failed
             */
            virtual void extract(Context& context);


        protected:

            /**
             * @brief Argument name
             */
            std::string _name;

            /**
             * @brief Argument description
             */
            std::string _description;

    };

}
