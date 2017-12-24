//
// Created by FyS on 24/12/17.
//

#ifndef FREESOULS_RANGE_HPP
#define FREESOULS_RANGE_HPP

#include <zconf.h>
#include <algorithm>

namespace fys::utils {

    template<typename T = uint>
    class Range {

    public:
        ~Range() = default;
        Range(T minX, T maxX, T minY, T maxY) :
                _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY) {}
        Range(T&& minX, T&&maxX, T&& minY, T&&maxY) noexcept :
                _minX(std::move(minX)), _maxX(std::move(maxX)), _minY(std::move(minY)), _maxY(std::move(maxY)) {}
        Range(const Range& range) = default;
        Range(Range &&range) noexcept = default;

        inline bool operator()(T x, T y) const noexcept {
            return (x >= _minX && y <= _maxX) && (y >= _minY && y <= _maxY);
        }

        inline std::pair<T, T> x() const {
            return std::make_pair(_minX, _maxX);
        }

        inline std::pair<T, T> y() const {
            return std::make_pair(_minY, _maxY);
        }

    private:
        T _minX;
        T _maxX;
        T _minY;
        T _maxY;
    };

}

#endif //FREESOULS_RANGE_HPP
