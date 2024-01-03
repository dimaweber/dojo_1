#include "task_1.hxx"

#include <spdlog/spdlog.h>

#include <cstdint>
#include <thread>

uint64_t task_1::Plain_C_1::calculate(uint64_t n)
{
    uint64_t accum {0};
    for ( uint64_t i = 1; i <= n; i++ )
        if ( i % 3 == 0 )
            accum += i;
        else if ( i % 5 == 0 )
            accum += i;
    return accum;
}

uint64_t task_1::Plain_C_2::calculate(uint64_t n)
{
    uint64_t accum {0};
    for ( uint64_t i = 1; i <= n; i++ )
        if ( i % 3 == 0 || i % 5 == 0 )
            accum += i;
    return accum;
}

uint64_t task_1::Plain_C_3::calculate(uint64_t n)
{
    uint64_t accum {0};
    for ( uint64_t i = 0; i <= n; i += 3 )
        accum += i;
    for ( uint64_t i = 0; i <= n; i += 5 )
        accum += i;
    for ( uint64_t i = 0; i <= n; i += 15 )
        accum -= i;
    return accum;
}

uint64_t task_1::Thread_C_1::calculate(uint64_t n)
{
    auto calc = [n] (uint64_t& out, uint64_t step) {
        out = 0;
        for ( uint64_t i = 0; i <= n; i += step )
            out += i;
    };

    uint64_t out_3;
    uint64_t out_5;
    uint64_t out_15;

    auto t1 = std::thread(calc, std::ref(out_3), 3);
    auto t2 = std::thread(calc, std::ref(out_5), 5);
    auto t3 = std::thread(calc, std::ref(out_15), 15);

    t1.join( );
    t2.join( );
    t3.join( );

    return out_3 + out_5 - out_15;
}

uint64_t task_1::Thread_C_2::calculate(uint64_t n)
{
    auto calc = [] (uint64_t& out, uint64_t l, uint64_t h, uint64_t step) {
        out = 0;
        l   = l == 0 ? 0 : (((l - 1) / step) + 1) * step;
        spdlog::debug("modified range: {}..{}", l, h);
        for ( uint64_t i = l; i <= h; i += step )
            out += i;

        spdlog::debug("result is {}", out);
    };

    uint64_t out_3_l, out_3_h;
    uint64_t out_5_l, out_5_h;
    uint64_t out_15_l, out_15_h;

    uint64_t lower_min = 0;
    uint64_t lower_max = n / 2;
    uint64_t upper_min = n / 2 + 1;
    uint64_t upper_max = n;

    spdlog::debug("n:{} low: {}..{}   hi: {}..{}", n, lower_min, lower_max, upper_min, upper_max);

    auto t1_l = std::thread(calc, std::ref(out_3_l), lower_min, lower_max, 3);
    auto t1_h = std::thread(calc, std::ref(out_3_h), upper_min, upper_max, 3);
    auto t2_l = std::thread(calc, std::ref(out_5_l), lower_min, lower_max, 5);
    auto t2_h = std::thread(calc, std::ref(out_5_h), upper_min, upper_max, 5);
    auto t3_l = std::thread(calc, std::ref(out_15_l), lower_min, lower_max, 15);
    auto t3_h = std::thread(calc, std::ref(out_15_h), upper_min, upper_max, 15);

    t1_l.join( );
    t1_h.join( );
    t2_l.join( );
    t2_h.join( );
    t3_l.join( );
    t3_h.join( );

    return out_3_l + out_3_h + out_5_l + out_5_h - out_15_l - out_15_h;
}
