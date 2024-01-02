//
// Created by weber on 01.01.2024.
//

#include <fmt/format.h>
#include <chrono>
#include <fmt/chrono.h>
#include <spdlog/spdlog.h>

int main(int argc, const char** argv)
{
#if DEBUG
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::err);
#endif

    spdlog::info("start");

    const std::string name {argc>1?argv[1]:"World"};
    fmt::print("Hello, {}! today is {:%Y-%m-%d}\n", name, std::chrono::system_clock::now());

    spdlog::info("finish");

    return 0;
}
