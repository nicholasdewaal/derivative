
#include <iostream>
#include <functional>
using namespace std;
typedef function<double (const double&)> lambda_fl_fl;

auto Powered = [](const int& n)
{
    return [=](const double& x)
    {
        auto result = 1.;
        for (auto i = 1; i <= n; i++)
            result = result * x;
        return result;
    };
};

auto Derivative = [](const lambda_fl_fl& f, const double& h)
{
    return [=](const double& xx)
    {
        return (-f(xx + 2 * h) + 8 * f(xx + h) - 8 * f(xx - h)
            + f(xx - 2 * h)) / (12 * h); // numerical differentiation
    };
};

lambda_fl_fl NthDerivative(lambda_fl_fl f, const int& n, const double& h)
{
    // For demonstration of deeply layered closures only.  Numerical
    // differentiation for multiple derivatives is better done differently.
    for (auto i = 0; i < n; i++)
        f = Derivative(f, h);
    return f;
}

void PrintResults(const lambda_fl_fl& func_to_prime, const int& num_deriv,
                  const double& h, char const * f_descript,
                  const double vals[], const int& num_vals)
{
    auto nth_deriv = NthDerivative(func_to_prime, num_deriv, h);
    cout << "\n" << f_descript << " DERIVATIVE NUM " << num_deriv << endl;
    for (auto i = 0; i < num_vals; i++ )
        cout << "At " << vals[i] << ": " << nth_deriv(vals[i]) << endl;
}

int main()
{
    auto squared = Powered(2);
    auto sixthed = Powered(6);
    double const vals[] = {0., 3., 5.};
    auto num_vals = 3;
    double h = 0.5;
    for (auto i = 1; i <= 3; i++)
        PrintResults(squared, i, h, "x^2", vals, num_vals);

    for (auto i = 1; i <= 7; i++) // numerical error might propogate catastrophically.
        PrintResults(sixthed, i, h, "x^6", vals, num_vals);
    return 0;
}


/*
# in python:

def powered(n):
    return lambda x: x ** n


def derivative(f, h):
    return lambda x: (-f(x + 2 * h) + 8 * f(x + h) - 8 * f(x - h)
            + f(x - 2 * h)) / (12 * h) # numerical differentiation


def nth_derivative(f, n, h):
    for _ in range(n):
        f = derivative(f, h)
    return f


def print_results(func_to_prime, num_deriv, h, f_descript, vals):

    nth_deriv = nth_derivative(func_to_prime, num_deriv, h)
    print "\n", f_descript, " DERIVATIVE NUM ", num_deriv
    for val in vals:
         print "At", str(val) + ":", nth_deriv(val)


def main():
    vals = [0., 3., 5.]
    h = 0.5
    squared = powered(2)
    sixthed = powered(6)
    for i in range(3):
        print_results(squared, i+1, h, "x^2", vals)

    for i in range(7): # numerical error might propogate to breakdown.
        print_results(sixthed, i+1, h, "x^6", vals)

if __name__ == "__main__":
    main()
*/

