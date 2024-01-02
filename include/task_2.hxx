//
// Created by weber on 02.01.2024.
//

#pragma once
#include <cstdint>
#include <utility>

class gcd
{
public:
    uint64_t operator( ) (uint64_t a, uint64_t b) const noexcept { return calculate(a, b); }

    uint64_t operator( ) (std::pair<uint64_t, uint64_t> p) const noexcept { return calculate(p.first, p.second); }

protected:
    virtual uint64_t calculate(uint64_t m, uint64_t n) const noexcept = 0;
};

class cpp_standard : public gcd
{
protected:
    uint64_t calculate(uint64_t m, uint64_t n) const noexcept override;
};

class gcd_1 : public gcd
{
protected:
    uint64_t calculate(uint64_t m, uint64_t n) const noexcept override;
};

class gcd_bin : public gcd
{
protected:
    uint64_t calculate(uint64_t m, uint64_t n) const noexcept override;
};

class gcd_no_rec : public gcd
{
protected:
    uint64_t calculate(uint64_t m, uint64_t n) const noexcept override;
};
