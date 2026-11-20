#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

class Complex {
private:
    double real;
    double imag;

public:
    // Default constructor (0 + 0j)
    Complex() : real(0.0), imag(0.0) {}

    // Converting constructor from real part only (R + 0j)
    Complex(double r) : real(r), imag(0.0) {}

    // Parameterised constructor for full complex number (a + bj)
    Complex(double r, double i) : real(r), imag(i) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }

    // Magnitude: |Z| = sqrt(real^2 + imag^2)
    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    // Overload + (Series combination)
    Complex operator+(const Complex& o) const {
        return Complex(real + o.real, imag + o.imag);
    }

    // Overload -
    Complex operator-(const Complex& o) const {
        return Complex(real - o.real, imag - o.imag);
    }

    // Overload * : (a + bj)(c + dj) = (ac - bd) + j(ad + bc)
    Complex operator*(const Complex& o) const {
        return Complex(real * o.real - imag * o.imag, real * o.imag + imag * o.real);
    }

    // Overload / : (a + bj) / (c + dj) = [(ac + bd) + j(bc - ad)] / (c^2 + d^2)
    Complex operator/(const Complex& o) const {
        double denom = o.real * o.real + o.imag * o.imag;
        if (denom == 0.0) {
            std::cout << "[Math Error: Complex Division by Zero Impedance!] ";
            return Complex(NAN, NAN);
        }
        return Complex((real * o.real + imag * o.imag) / denom,
                       (imag * o.real - real * o.imag) / denom);
    }

    // Overload ==
    bool operator==(const Complex& o) const {
        const double EPS = 1e-9;
        return (std::abs(real - o.real) < EPS) && (std::abs(imag - o.imag) < EPS);
    }

    // Overload << for rectangular display: a + bj or a - bj
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << std::fixed << std::setprecision(2) << c.real;
        if (c.imag >= 0) {
            os << " + " << c.imag << "j";
        } else {
            os << " - " << -c.imag << "j";
        }
        return os;
    }
};

int main() {
    std::cout << "=== Q7: DESIGN A COMPLEX-NUMBER CLASS (AC CIRCUIT CALCULATOR) ===\n\n";

    std::cout << "--- 1. COMPONENT IMPEDANCES (R, L, C at w = 1000 rad/s) ---\n";
    // Circuit parameters:
    // R = 100 ohms
    // L = 0.1 H -> wL = 1000 * 0.1 = 100 ohms -> ZL = 0 + 100j
    // C = 10 uF (10e-6 F) -> 1/(wC) = 1 / (1000 * 10e-6) = 100 ohms -> ZC = 0 - 100j
    double R = 100.0;
    double omega = 1000.0;
    double L = 0.1;
    double C = 10e-6;

    Complex ZR(R);                         // 100 + 0j
    Complex ZL(0.0, omega * L);            // 0 + 100j
    Complex ZC(0.0, -1.0 / (omega * C));   // 0 - 100j

    std::cout << "Resistor   ZR: " << ZR << ", |ZR| = " << ZR.magnitude() << " ohms\n";
    std::cout << "Inductor   ZL: " << ZL << ", |ZL| = " << ZL.magnitude() << " ohms\n";
    std::cout << "Capacitor  ZC: " << ZC << ", |ZC| = " << ZC.magnitude() << " ohms\n";

    std::cout << "\n--- 2. SERIES RLC CIRCUIT IMPEDANCE (Zseries = ZR + ZL + ZC) ---\n";
    Complex Z_series = ZR + ZL + ZC;
    std::cout << "Z_series: " << Z_series << ", |Z_series| = " << Z_series.magnitude() << " ohms\n";
    std::cout << "Hand Calculation: (100 + 0j) + (0 + 100j) + (0 - 100j) = 100.00 + 0.00j, |Z| = 100.00 ohms (Resonance!)\n";

    std::cout << "\n--- 3. PARALLEL RL BRANCH (Z_parallel = (ZR * ZL) / (ZR + ZL)) ---\n";
    Complex Z_par_num = ZR * ZL;
    Complex Z_par_den = ZR + ZL;
    Complex Z_parallel = Z_par_num / Z_par_den;
    std::cout << "Z_par_num: " << Z_par_num << '\n';
    std::cout << "Z_par_den: " << Z_par_den << '\n';
    std::cout << "Z_parallel: " << Z_parallel << ", |Z_parallel| = " << Z_parallel.magnitude() << " ohms\n";
    std::cout << "Hand Calculation: (100 * 100j) / (100 + 100j) = 10000j / (100 + 100j) = 50.00 + 50.00j, |Z| = 70.71 ohms\n";

    std::cout << "\n--- 4. SAFE DIVISION BY ZERO IMPEDANCE TEST ---\n";
    Complex Z_zero(0.0, 0.0);
    Complex badDiv = ZR / Z_zero;
    std::cout << "ZR / Z_zero result: " << badDiv << " (Safely caught, no crash)\n";

    return 0;
}
