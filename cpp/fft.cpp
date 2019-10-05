namespace fft {
    inline uint8_t countBin(uint32_t x) {
        for (uint8_t i = 0; i != 32; ++i) {
            if (x & 1) {
                return i;
            }
            x >>= 1;
        }
        return 32;
    }

    inline uint32_t reverse(uint32_t x) {
        uint32_t res = 0;
        for (uint8_t i = 0; i != 32; ++i) {
            res <<= 1;
            res |= x & 1;
            x >>= 1;
        }
        return res;
    }

    inline uint32_t highestBit(uint32_t x) {
        if (x == 0) {
            return 0;
        }
        uint32_t cnt = 0;
        while (x != 0) {
            cnt++;
            x >>= 1;
        }
        x = 1;
        return x << (--cnt);
    }

    template <typename T>
    void fft(std::vector<T>& a, std::vector<T>& b, bool invert) {
        const T PI = acos(-1);
        uint32_t n = a.size();
        uint32_t shift = 32 - countBin(n);
        for (uint32_t i = 1; i < n; ++i) {
            uint32_t j = reverse(i << shift);
            if (i < j) {
                std::swap(a[i], a[j]);
                std::swap(b[i], b[j]);
            }
        }
        for (uint32_t len = 2; len <= n; len <<= 1) {
            uint32_t halfLen = len >> 1;
            T angle = 2 * PI / len * (invert ? -1 : 1);
            T wLenA = cos(angle);
            T wLenB = sin(angle);
            for (uint32_t i = 0; i < n; i += len) {
                T wA = 1;
                T wB = 0;
                for (uint32_t j = 0; j != halfLen; ++j) {
                    T uA = a[i + j];
                    T uB = b[i + j];
                    T vA = a[i + j + halfLen] * wA - b[i + j + halfLen] * wB;
                    T vB = a[i + j + halfLen] * wB + b[i + j + halfLen] * wA;
                    a[i + j] = uA + vA;
                    b[i + j] = uB + vB;
                    a[i + j + halfLen] = uA - vA;
                    b[i + j + halfLen] = uB - vB;
                    T nextWA = wA * wLenA - wB * wLenB;
                    wB = wA * wLenB + wB * wLenA;
                    wA = nextWA;
                }
            }
        }
        if (invert) {
            for (uint32_t i = 0; i != n; ++i) {
                a[i] /= n;
                b[i] /= n;
            }
        }
    }

    

    template <typename T = uint32_t, typename F = double, T Base = T(-1)>
    std::vector<T> multiply(const std::vector<T>& a, const std::vector<T>& b) {
        uint32_t resultSize = highestBit(std::max(a.size(), b.size()) - 1) << 2;
        resultSize = std::max(resultSize, 2u);

        std::vector<F> aReal(resultSize);
        std::vector<F> aImaginary(resultSize);
        std::vector<F> bReal(resultSize);
        std::vector<F> bImaginary(resultSize);

        for (size_t i = 0; i != a.size(); ++i) {
            aReal[i] = a[i];
        }
        for (size_t i = 0; i != b.size(); ++i) {
            bReal[i] = b[i];
        }

        fft(aReal, aImaginary, false);
        fft(bReal, bImaginary, false);

        for (size_t i = 0; i != resultSize; ++i) {
            F real = aReal[i] * bReal[i] - aImaginary[i] * bImaginary[i];
            aImaginary[i] = aImaginary[i] * bReal[i] + bImaginary[i] * aReal[i];
            aReal[i] = real;
        }

        fft(aReal, aImaginary, true);

        std::vector<T> result(resultSize);
        if (Base != T(-1)) {
            T carry = 0;
            for (size_t i = 0; i != resultSize; ++i) {
                carry += round(aReal[i]);
                result[i] = carry % Base;
                carry /= Base;
            }
        } else {
            for (size_t i = 0; i != resultSize; ++i) {
                result[i] = round(aReal[i]);
            }
        }
        return result;
    }
};