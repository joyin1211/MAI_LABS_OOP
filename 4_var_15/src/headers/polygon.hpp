#pragma once
#include <array>
#include <cstddef>
#include <iomanip>
#include <memory>
#include <type_traits>
#include "figure.hpp"
#include "geometry_utils.hpp"

template <Scalar T, std::size_t N>
class Polygon : public Figure<T> {

public:
    Polygon() {
        for (auto& p : pts){
            p = std::make_unique<Point<T>>();
        }
    }

    Polygon(const Polygon& other) {
        for (std::size_t i = 0; i < N; i++) {
            pts[i] = std::make_unique<Point<T>>(*other.pts[i]);
        }
    }

    Polygon& operator=(const Polygon& other) {
        if (this == &other) return *this;
        for (std::size_t i = 0; i < N; i++) {
            pts[i] = std::make_unique<Point<T>>(*other.pts[i]);
        }
        return *this;
    }

    Polygon(Polygon&&) noexcept = default;
    Polygon& operator=(Polygon&&) noexcept = default;

    void read(std::istream& is) {
        for (std::size_t i = 0; i < N; i++) {
            Point<T> tmp;
            is >> tmp;
            *pts[i] = tmp;
        }
    }

    std::array<Point<T>, N> vertices() const {
        std::array<Point<T>, N> out{};
        for (std::size_t i = 0; i < N; i++) {
            out[i] = *pts[i];
        }
        return out;
    }

    double area() const override {
        const auto v = vertices();
        double s = 0.0;
        for (std::size_t i = 0; i < N; i++){
            s += cross(v[i], v[(i + 1) % N]);
        }
        return std::fabs(s) * 0.5;
    }

    Point<double> centroid() const override {
        const auto v = vertices();
        double A2 = 0.0, Cx6A = 0.0, Cy6A = 0.0;

        for (std::size_t i = 0; i < N; i++) {
            const auto& p = v[i];
            const auto& q = v[(i + 1) % N];
            const double cr = cross(p, q);
            A2 += cr;
            Cx6A += (static_cast<double>(p.x) + static_cast<double>(q.x)) * cr;
            Cy6A += (static_cast<double>(p.y) + static_cast<double>(q.y)) * cr;
        }

        if (almost_equal(A2, 0.0)) {
            double sx = 0.0, sy = 0.0;
            for (const auto& p : v) { 
                sx += p.x; sy += p.y; 
            }
            return {sx / static_cast<double>(N), sy / static_cast<double>(N)};
        }

        const double A = A2 / 2.0;
        return {Cx6A / (6.0 * A), Cy6A / (6.0 * A)};
    }

    bool equals(const Figure<T>& other) const override {
        auto* o = dynamic_cast<const Polygon<T, N>*>(&other);
        if (!o) return false;

        const auto a = vertices();
        const auto b = o->vertices();

        if constexpr (std::is_integral_v<T>) {
            for (std::size_t i = 0; i < N; i++) {
                if (a[i].x != b[i].x || a[i].y != b[i].y) {
                    return false;
                }
            }
            return true;
        } else {
            for (std::size_t i = 0; i < N; i++) {
                if (!almost_equal(static_cast<double>(a[i].x), static_cast<double>(b[i].x))) return false;
                if (!almost_equal(static_cast<double>(a[i].y), static_cast<double>(b[i].y))) return false;
            }
            return true;
        }
    }

    void print(std::ostream& os) const override {
        os << "Vertices (" << N << "): ";
        const auto v = vertices();
        for (std::size_t i = 0; i < N; i++) {
            os << v[i];
            if (i + 1 != N) os << ", ";
        }
        auto c = centroid();
        os << "\nCentroid: (" << std::fixed << std::setprecision(6) << c.x << ", " << c.y << ")";
        os << "\nArea: " << std::fixed << std::setprecision(6) << area() << "\n";
    }

private:
    std::array<std::unique_ptr<Point<T>>, N> pts{};
};

template <Scalar T, std::size_t N>
inline std::istream& operator>>(std::istream& is, Polygon<T, N>& poly) {
    poly.read(is);
    return is;
}
