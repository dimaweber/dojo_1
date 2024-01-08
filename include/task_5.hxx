//
// Created by weber on 05.01.2024.
//

#pragma once
#include <cstdint>
#include <vector>

#include "task_4.hxx"

namespace task_5
{
class sexy_prime
{
public:
    std::vector<std::pair<uint64_t, uint64_t>> operator( ) (uint64_t num) const noexcept { return calculate(num); }

protected:
    virtual std::vector<std::pair<uint64_t, uint64_t>> calculate(uint64_t num) const noexcept = 0;
};

class sexy_prime_ref : public sexy_prime
{
protected:
    std::vector<std::pair<uint64_t, uint64_t>> calculate(uint64_t num) const noexcept override;
};

class sexy_prime_impl : public sexy_prime
{
    const task_4::prime_cached_single_thread prime;

protected:
    virtual const task_4::prime& primer ( ) const { return prime; }

    std::vector<std::pair<uint64_t, uint64_t>> calculate(uint64_t num) const noexcept override;
};

class sexy_prime_impl_mt : public sexy_prime_impl
{
    const task_4::prime_thread_cached prime;

protected:
    virtual const task_4::prime& primer ( ) const { return prime; }
};

}  // namespace task_5
