//
// Created by weber on 01.01.2024.
//

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <iostream>

#include "task_1.hxx"

int main (int argc, const char** argv)
{
#if DEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::err);
#endif

    spdlog::info("start task 1");

    fmt::print("Task 1. enter number: ");
    uint64_t num;
    std::cin >> num;
    Plain_C_3 obj;
    fmt::print("answer is : {}", obj(num));

    spdlog::info("finish task 1");

    return 0;
}
