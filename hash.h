#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash
{
    HASH_INDEX_T rValues[5]{983132572, 1468777056, 552714139, 984953261, 261934300};
    MyStringHash(bool debug = true)
    {
        if (false == debug)
        {
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string &k) const
    {

        // Add your code here
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        // given w [0] --> w [4] = initial all 0
        std::string tempString = k;
        int index = k.size() - 1;
        int toPower = 0;

        // start from w[4]
        for (int i = 4; i >= 0; i--)
        {
            // store the string
            int highVal = std::max(0, index - 5); // number of letters left

            // string to compute hash
            std::string curr = tempString.substr(highVal, index - highVal + 1);
            // store prev string
            tempString = tempString.substr(0, highVal);

            for (int letter = curr.size() - 1; letter >= 0; letter--) // pass each letter of new string
            {
                int convert = letterDigitToNumber(curr[letter]);
                int basePow = 1;
                // not use pow
                for (int pow = 0; pow < toPower; pow++)
                {
                    basePow *= 36;
                }
                w[i] += basePow * convert;
                toPower++;
            }

            // reset the toPower
            toPower = 0;
            index = tempString.size() - 1;
        }

        // return hash funciton
        return rValues[0] * w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4] * w[4];
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        // convert everything to lower case
        HASH_INDEX_T lower = std::tolower(letter);

        // index from 0 --> 26 9 --> 35
        if (lower >= '0' && lower <= '9')
        {
            return lower - '0' + 26;
        }
        else if (lower >= 'a' && lower <= 'z')
        {
            return lower - 'a';
        }
        else
        {
            return 0;
        }
    }

    // DONE!

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed); // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for (int i{0}; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
