//
// Created by weber on 01.01.2024.
//

#pragma once
#include <cstdint>

namespace task_1
{
class Sum_3_5
{
public:
    virtual ~Sum_3_5( ) = default;

    uint64_t operator( ) (uint64_t n) { return result(n); }

    uint64_t result (uint64_t n) { return calculate(n); }

protected:
    virtual uint64_t calculate(uint64_t n) = 0;
};

class Plain_C_1 : public Sum_3_5
{
public:
    using Sum_3_5::Sum_3_5;

protected:
    uint64_t calculate(uint64_t n) override;
};

class Plain_C_2 : public Sum_3_5
{
public:
    using Sum_3_5::Sum_3_5;

protected:
    uint64_t calculate(uint64_t n) override;
};

class Plain_C_3 : public Sum_3_5
{
public:
    using Sum_3_5::Sum_3_5;

protected:
    uint64_t calculate(uint64_t n) override;
};

class Thread_C_1 : public Sum_3_5
{
public:
    using Sum_3_5::Sum_3_5;

protected:
    uint64_t calculate(uint64_t n) override;
};

class Thread_C_2 : public Sum_3_5
{
public:
    using Sum_3_5::Sum_3_5;

protected:
    uint64_t calculate(uint64_t n) override;
};
}  // namespace task_1
