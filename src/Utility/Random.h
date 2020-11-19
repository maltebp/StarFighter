#pragma once


#include <random>

class Random {
public:

    /**
     * @brief   Returns random double in interval including both eds
    */
    static double getDouble(double from, double to) {
        std::uniform_real_distribution<> distr(from, to);
        return distr(generator);
    }

    /**
     * @brief   Returns a random integer in interval including both ends
    */
    static int getInt(int from, int to) {
        std::uniform_int_distribution<> distr(from, to);
        return distr(generator);
    }


private:
    inline static std::mt19937 generator = std::mt19937(std::random_device()());
};
