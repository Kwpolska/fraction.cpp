/*
 * Fraction v0.1.0
 * Copyright © 2016-2017, Chris Warrick.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions, and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the author of this software nor the names of
 *    contributors to this software may be used to endorse or promote
 *    products derived from this software without specific prior written
 *    consent.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cmath>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

/**
 * Implementation of a fraction.
 */

/**
 * A fraction, represented in numerator/denominator form.
 */
class Fraction {
    public:
        /**
         * Create a fraction with the value 0.
         */
        Fraction() {
            setValue(0, 1);
        }

        /**
         * Create a new fraction.
         * @param numerator the numerator
         * @param denominator the denominator
         */
        Fraction(int numerator, int denominator) {
            setValue(numerator, denominator);
        }

        /**
         * @return the numerator
         */
        int getNumerator() {
            return numerator;
        }

        /**
         * @return the denominator
         */
        int getDenominator() {
            return denominator;
        }

        /**
         * Set the value of this fraction.
         * @param numerator the new numerator
         * @param denominator the new denominator
         */
        void setValue(int numerator, int denominator) {
            // Support negative numbers.
            if (denominator == 0) {
                throw runtime_error("Denominator cannot be zero.");
            } else if (denominator < 0) {
                // put - sign to numerator
                numerator = -numerator;
                denominator = -denominator;
            }
            // All fractions have to be simplified. To do that, we need to find the GCD of two numbers and divide.
            int c = gcd(abs(numerator), abs(denominator));

            this->numerator = numerator / c;
            this->denominator = denominator / c;
        }

        // Operations

        /**
         * Add a fraction to this fraction.
         * @param b The fraction to add.
         * @return A new fraction object that is the result of this + b.
         */
        Fraction operator+(Fraction b) {
            return addByValue(b.numerator, b.denominator);
        }

        /**
         * Subtract a fraction from this fraction.
         * @param b The fraction to subtract.
         * @return A new fraction object that is the result of this - b.
         */
        Fraction operator-(Fraction b) {
            return addByValue(-b.numerator, b.denominator);
        }

        /**
         * Multiply two fractions together.
         * @param b The fraction to multiply this by.
         * @return New fraction object that is the result of this * b.
         */

        Fraction operator*(Fraction b) {
            return Fraction(numerator * b.numerator, denominator * b.denominator);
        }

        /**
         * Divide this by another fraction.
         * @param b The fraction to divide this by.
         * @return New fraction object that is the result of this / b, or this * (1 / b).
         */
        Fraction operator/(Fraction b) {
            return Fraction(numerator * b.denominator, denominator * b.numerator);
        }

        // Helper functions

        /**
         * Return this fraction as a string.
         * @return numerator/denominator
         */
        string toString() {
            return toString(numerator, denominator);
        }

        /**
         * Return the fraction as a string, that may contain a mixed number.
         * @return numerator/denominator or integral numerator/denominator
         */
        string toMixed() {
            if (abs(numerator) >= denominator) {
                // Get out integer part
                int i = numerator / denominator;
                int n = numerator % denominator;
                string s = to_string(i);
                s += " ";
                if (n != 0) {
                    s += toString(abs(n), denominator);
                }
                return s;
            } else if (numerator == 0) {
                return string("0");
            } else {
                return toString();
            }
        }

        /**
         * Print the fraction and mixed number versions of this object.
         */
        void printBoth() {
            cout << toString() << " == " << toMixed() << endl;
        }

        /** Determine the Least Common Multiple (LCM) of two integers
         * @param a First integer
         * @param b Second integer
         * @return LCM(a, b)
         */
        int lcm(int a, int b) {
            return abs(a * b) / gcd(a, b);
        }
        /** Determine the Greatest Common Divisor (GCD) of two integers (Euclid’s Algorithm)
         * @param a First integer
         * @param b Second integer
         * @return GCD(a, b)
         */
        int gcd(int a, int b) {
            int r;
            while (b > 0) {
                r = a % b;
                a = b;
                b = r;
            }
            return a;
        }


    private:
        /**
         * The numerator of the fraction.
         */
        int numerator;

        /**
         * The denominator of the fraction.
         */
        int denominator;

        /**
         * Add a fraction by value.
         * @param bn Numerator of the fraction to add.
         * @param bd Denominator of the fraction to add.
         * @return A new fraction object that is the result of this + bn/bd.
         */
        Fraction addByValue(int bn, int bd) {
            int an = this->numerator;
            int ad = this->denominator;

            // Figure out the new denominator and the factors to get there.
            int nd = lcm(ad, bd);
            int ax = nd / ad;
            int bx = nd / bd;

            int nn = (an * ax) + (bn * bx);

            return Fraction(nn, nd);
        }

        /**
         * Return a fraction of numerator/denominator as a string.
         * @param numerator The numerator.
         * @param denominator The denominator.
         * @return numerator/denominator
         */
        string toString(int numerator, int denominator) {
            string s;
            s += to_string(numerator);
            s += "/";
            s += to_string(denominator);
            return s;
        }
};
