#include "ExponentialDistribution.h"
#include <chrono>

/**
 * @brief Constructor for ExponentialDistribution.
 *
 * Initializes the rate parameter and seeds the random number generator.
 *
 * @param lambda The rate parameter (λ) for the exponential distribution.
 */
ExponentialDistribution::ExponentialDistribution(double lambda)
    : lambda_(lambda), distribution_(lambda)
{
    // Seed the generator with the current time for randomness.
    generator_.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

/**
 * @brief Destructor for ExponentialDistribution.
 */
ExponentialDistribution::~ExponentialDistribution() {
    // No dynamic memory to free.
}

/**
 * @brief Generate a random sample from the exponential distribution.
 *
 * Uses the C++11 <random> library to sample a random variate.
 *
 * @return double A random variate from the exponential distribution.
 */
double ExponentialDistribution::sample() {
    return distribution_(generator_);
}
