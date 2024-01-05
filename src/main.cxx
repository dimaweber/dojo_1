//
// Created by weber on 01.01.2024.
//

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <iostream>

#include "task_1.hxx"
#include "task_2.hxx"
#include "task_3.hxx"
#include "task_4.hxx"

int main (int /*argc*/, const char** /*argv*/)
{
#if DEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::err);
#endif

    {
        spdlog::info("start task 1");

        fmt::print("Task 1. enter number: ");
        uint64_t num;
        std::cin >> num;
        task_1::Plain_C_3 obj;
        fmt::print("answer is : {}\n", obj(num));

        spdlog::info("finish task 1");
    }

    {
        fmt::print("Task 2. enter 2 numbers: ");
        uint64_t m, n;
        std::cin >> m >> n;
        task_2::gcd_no_rec obj;
        fmt::print("gcd for {} and {} is {}\n", m, n, obj(m, n));
    }

    {
        fmt::print("Task 3. enter 2 numbers: ");
        uint64_t m, n;
        std::cin >> m >> n;
        task_3::lcm_using_gcd obj;
        fmt::print("lcm for {} and {} is {}\n", m, n, obj(m, n));
    }

    {
        fmt::print("Task 4. enter the number: ");
        uint64_t num;
        std::cin >> num;
        task_4::l_prime_cached obj;
        fmt::print("greatest prime_cached before {} is {}\n", num, obj(num));
    }
    return 0;
}
