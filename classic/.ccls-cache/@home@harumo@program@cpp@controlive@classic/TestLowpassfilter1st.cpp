#include "Lowpassfilter1st.hpp"
#include <armadillo>
#include <cmath>
#include <iostream>
#include <matplot/matplot.h>
#include <vector>

int main(int argc, char *argv[]) {
    // generate sin(2pi*w1*t)+0.1(2pi*w2*t)
    double w1 = 3;  // 3Hz
    double w2 = 50; // 50Hz
    arma::vec t = arma::linspace(0, 10, 1000);
    arma::vec y =
        arma::sin(2 * M_PI * w1 * t) + 0.1 * arma::sin(2 * M_PI * w2 * t);

    auto figure = matplot::figure(true);

    figure->size(1920, 1080);
    matplot::yrange({-1, 1});
    matplot::subplot(2, 1, 0);
    matplot::plot(t, y);
    matplot::yrange({-1, 1});
    matplot::subplot(2, 1, 1);

    Lowpassfilter1st filter(100, 50);
    std::vector<double> y_filtered;
    for (auto &&val : y) {
        y_filtered.push_back(filter.step(val));
    }

    auto fig = matplot::plot(t, y_filtered);

    matplot::show();

    return 0;
}
