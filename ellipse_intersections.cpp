#include <vector>
#include <cmath>
#include <numbers>
#include <functional>
#include <algorithm>

struct Point {
    double x;
    double y;
};

struct Ellipse {
    Point center;
    Point size; // x = width, y = height
    double angle; // rotation in radians
};

std::vector<Point> intersections(const Ellipse& a, const Ellipse& b) {
    constexpr double pi = std::numbers::pi;
    constexpr int N = 720; // Number of samples over [0, 2π]
    constexpr double delta_t = 2 * pi / N;
    constexpr double tolerance = 1e-6;
    std::vector<Point> result;

    // Precompute constants for ellipse a
    const double h1 = a.center.x;
    const double k1 = a.center.y;
    const double a1 = a.size.x / 2.0;
    const double b1 = a.size.y / 2.0;
    const double theta1 = a.angle;
    const double cos_theta1 = std::cos(theta1);
    const double sin_theta1 = std::sin(theta1);

    // Precompute constants for ellipse b
    const double h2 = b.center.x;
    const double k2 = b.center.y;
    const double a2 = b.size.x / 2.0;
    const double b2 = b.size.y / 2.0;
    const double theta2 = b.angle;
    const double cos_theta2 = std::cos(theta2);
    const double sin_theta2 = std::sin(theta2);

    // Function to compute x(t) and y(t) on ellipse a
    auto compute_xy = [&](double t) -> Point {
        const double cos_t = std::cos(t);
        const double sin_t = std::sin(t);
        const double x = h1 + a1 * cos_t * cos_theta1 - b1 * sin_t * sin_theta1;
        const double y = k1 + a1 * cos_t * sin_theta1 + b1 * sin_t * cos_theta1;
        return { x, y };
    };

    // Function to compute the ellipse equation value E(t) for ellipse b
    auto compute_E = [&](double t) -> double {
        const Point p = compute_xy(t);
        const double X = p.x - h2;
        const double Y = p.y - k2;
        const double x_prime = cos_theta2 * X + sin_theta2 * Y;
        const double y_prime = -sin_theta2 * X + cos_theta2 * Y;
        const double E = (x_prime * x_prime) / (a2 * a2) + (y_prime * y_prime) / (b2 * b2) - 1.0;
        return E;
    };

    // Sample E(t) over [0, 2π] to find sign changes
    for (int i = 0; i < N; ++i) {
        const double t1 = i * delta_t;
        const double t2 = (i + 1) * delta_t;
        const double E1 = compute_E(t1);
        const double E2 = compute_E(t2);

        if (E1 * E2 <= 0) { // Possible root in [t1, t2]
            // Use bisection method to find the root
            double lower = t1;
            double upper = t2;
            double mid = 0.0;
            int iterations = 0;
            constexpr int max_iterations = 100;

            while (iterations < max_iterations) {
                mid = (lower + upper) / 2.0;
                const double E_mid = compute_E(mid);

                if (std::abs(E_mid) < tolerance) {
                    break; // Root found
                }

                if (E1 * E_mid < 0) {
                    upper = mid;
                } else {
                    lower = mid;
                }
                ++iterations;
            }

            // Compute intersection point and check discriminant
            const Point p = compute_xy(mid);
            const double E_final = compute_E(mid);

            if (std::abs(E_final) < tolerance * 10) { // Check discriminant
                // Avoid duplicates
                if (std::none_of(result.begin(), result.end(), [&](const Point& existing_point) {
                    return std::hypot(existing_point.x - p.x, existing_point.y - p.y) < tolerance;
                })) {
                    result.push_back(p);
                }
            }
        }
    }

    return result;
}


#include <print>

int main() {
	Ellipse a = {
		.center = Point(0, 0),
		.size = Point(2, 4),
		.angle = 0
	};
	Ellipse b = {
		.center = Point(0, 0),
		.size = Point(4, 2),
		.angle = 0
	};

	for (auto [x, y] : intersections(a, b)) {
		std::println("({}, {})", x, y);
	}
}
