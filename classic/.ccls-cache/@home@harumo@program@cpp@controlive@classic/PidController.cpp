#include "PidController.hpp"
#include <sstream>

PidController::PidController() { }

PidController::PidController(const double dt, const double kp, const double ki,
    const double kd)
{
    this->setDt(dt);
    this->setKp(kp);
    this->setKi(kd);
    this->setKd(kd);
}

void PidController::setDt(const double dt)
{
    if (dt <= 0) {
        this->is_dt_constant_ = false;
    } else {
        this->is_dt_constant_ = true;
        this->dt_ = dt;
    }
}

void PidController::setKp(const double kp)
{
    if (kp < 0) {
        throw this->getExceptionMessageAboutGainInit("kp", kp);
    } else {
        this->kp_ = kp;
    }
}

void PidController::setKi(const double ki)
{
    if (ki < 0) {
        throw this->getExceptionMessageAboutGainInit("ki", ki);
    } else {
        this->ki_ = ki;
    }
}

void PidController::setKd(const double kd)
{
    if (kd < 0) {
        throw this->getExceptionMessageAboutGainInit("kd", kd);
    } else {
        this->kd_ = kd;
    }
}

std::tuple<double, double, double, double> PidController::getGains()
{
    return { this->dt_, this->kp_, this->ki_, this->kd_ };
}

double PidController::getCurrentError() { return this->current_error_; }

void PidController::info()
{
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "PID controller information" << std::endl;
    std::cout << "dt \t = \t " << this->dt_ << std::endl;
    std::cout << "kp \t = \t " << this->kp_ << std::endl;
    std::cout << "ki \t = \t " << this->ki_ << std::endl;
    std::cout << "kd \t = \t " << this->kd_ << std::endl;
    std::cout << "error \t = \t" << this->current_error_ << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}

std::string PidController::getExceptionMessageAboutGainInit(
    const std::string parameter_name, const double gain_value)
{
    std::stringstream error_message;
    error_message << parameter_name << " gain value is not good. " << std::endl;
    error_message << parameter_name << " gain should be bigger than 0. "
                  << std::endl;
    error_message << "But, " << parameter_name << " is " << gain_value
                  << std::endl;
    return error_message.str();
}

double PidController::step(const double target_data, const double latest_data)
{

    // If dt is not constant, calculate dt
    if (this->is_dt_constant_ == false) {
        this->dt_ = std::chrono::duration<double>(
            std::chrono::steady_clock::now()
            - this->previous_step_time_point_)
                        .count();
    }

    // calculate error
    this->previous_error_ = this->current_error_;
    this->current_error_ = target_data - latest_data;

    // calculate proportional
    double proportional_output = this->kp_ * this->current_error_;

    // calculate integral
    this->cumulative_integral_ += this->current_error_ * this->dt_;
    double integral_output = this->ki_ * this->cumulative_integral_;

    // calculate derivative
    double derivative = (this->current_error_ - this->previous_error_) / this->dt_;
    double derivative_output = this->kd_ * derivative;

    // calculate output
    double u = proportional_output + integral_output + derivative_output;

    // save current time for next calcuration
    this->previous_step_time_point_ = std::chrono::steady_clock::now();

    return u;
}
