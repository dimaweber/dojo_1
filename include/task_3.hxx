//
// Created by weber on 03.01.2024.
//

#pragma once
#include <cstdint>
#include <utility>

#include "task_2.hxx"

namespace task_3
{
class lcm
{
public:
    [[nodiscard]] uint64_t operator( ) (uint32_t m, uint32_t n) const noexcept { return calculate(m, n); }

    [[nodiscard]] uint64_t operator( ) (const std::pair<uint32_t, uint32_t>& p) const noexcept { return calculate(p.first, p.second); }

protected:
    [[nodiscard]] virtual uint64_t calculate(uint32_t m, uint32_t n) const noexcept = 0;
};

class cpp_standard_lcm : public lcm
{
public:
    using lcm::lcm;

protected:
    uint64_t calculate(uint32_t m, uint32_t n) const noexcept override;
};

class lcm_using_gcd : public lcm
{
    const task_2::cpp_standard_gcd g;

protected:
    uint64_t calculate(uint32_t m, uint32_t n) const noexcept override;
};
}  // namespace task_3
