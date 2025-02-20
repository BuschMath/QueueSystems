#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

/**
 * @file Distribution.h
 * @brief Abstract base class for random variate distributions.
 *
 * This class provides a generic interface for probability distributions.
 * Derived classes must implement the sample() method to return a random
 * variate following the specific distribution.
 */
class Distribution {
public:
    /**
     * @brief Virtual destructor.
     *
     * Ensures proper cleanup of derived class resources.
     */
    virtual ~Distribution() {}

    /**
     * @brief Generate a random sample from the distribution.
     *
     * @return double A random variate.
     */
    virtual double sample() = 0;
};

#endif // DISTRIBUTION_H

