#ifndef MISC_HPP
# define MISC_HPP

# include <random>

using namespace std;

inline float getRand(float low, float high)
{
    static random_device dev;
    static mt19937 rng(dev());
    uniform_real_distribution<float> dist(low, high);
    return (dist(rng));
}

#endif
