#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <chrono>

class PidController
{
public:
	PidController(const double dt, const double kp, const double ki, const double kd);
	void setDt(const double dt);
	void setKp(const double kp);
	void setKi(const double ki);
	void setKd(const double kd);
	std::tuple<double, double, double, double> getGains();
	double getCurrentError();
	double step(const double r, const double y);
	void info();

private:
	std::string getExceptionMessageAboutGainInit(const std::string gain_name, const double gain_value);
	double dt_ = 0;
	double kp_ = 0;
	double ki_ = 0;
	double kd_ = 0;
	double cumulative_integral_ = 0;
	double current_error_ = 0;
	double previous_error_ = 0;
	std::chrono::time_point previous_step_time_point_;
	bool is_dt_constant_ = true;
};
