#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H

#include "Distribution.h"
#include <random>

/**
 * @file ExponentialDistribution.h
 * @brief Concrete class for the exponential distribution.
 *
 * Implements an exponential distribution with a specified rate parameter λ.
 * The sample() method returns a random variate based on the exponential distribution,
 * using the C++11 <random> library.
 */
class ExponentialDistribution : public Distribution {
public:
    /**
     * @brief Constructor.
     *
     * @param lambda The rate parameter (λ) for the exponential distribution.
     */
    ExponentialDistribution(double lambda);

    /**
     * @brief Destructor.
     */
    virtual ~ExponentialDistribution();

    /**
     * @brief Generate a random sample from the exponential distribution.
     *
     * @return double A random variate.
     */
    virtual double sample() override;

private:
    double lambda_; ///< Rate parameter for the distribution.
    std::default_random_engine generator_; ///< Random number generator.
    std::exponential_distribution<double> distribution_; ///< Exponential distribution object.
};

#endif // EXPONENTIALDISTRIBUTION_H

