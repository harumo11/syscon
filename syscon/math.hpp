#pragma once

#include <iostream>
#include <numbers>


namespace syscon{

double T2fc(auto const T){
    return 1.0 / (static_cast<double>(T) * 2 * std::numbers::pi);
}

double wc2T(auto const T){
    return 1.0 / static_cast<double>(T);
}

double fc2wc(auto const fc){
    return 2 * std::numbers::pi * static_cast<double>(fc);
}

}

