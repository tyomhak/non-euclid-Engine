#pragma once

#include <iostream>
#include <string_view>
#include <format>

namespace njin
{
    class Logger
    {
    public:
        template<typename... Args>
        static void Log(const std::string_view fmt, Args&&... args)
        {
            std::cout << std::vformat(fmt, std::make_format_args(args...)) << std::endl;
        }

        static inline void Log(const std::string_view msg) {
            std::cout << msg << std::endl;
        }

        template<typename... Args>
        static void Error(const std::string_view fmt, Args&&... args)
        {
            std::cout << "Error: " << std::vformat(fmt, std::make_format_args(args...)) << std::endl;
        }

        static inline void Error(const std::string_view msg) {
            std::cout << "Error: " << msg << std::endl;
        }

        template<typename... Args>
        static void Warning(const std::string_view fmt, Args&&... args)
        {
            std::cout << "Warning: " << std::vformat(fmt, std::make_format_args(args...)) << std::endl;
        }

        static inline void Warning(const std::string_view msg) {
            std::cout << "Warning: " << msg << std::endl;
        }

        
    };





}