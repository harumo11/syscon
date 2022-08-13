#pragma once

#include "bertrand/include/bertrand/bertrand.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

namespace controlive {

class gnuplot {
public:
    gnuplot();
    ~gnuplot();
    void write(const std::string plot_command);
    bool is_open();
    void flush();

private:
    FILE* pipe;
    bool pipe_status = false;
    bool open();
    void close();
};

gnuplot::gnuplot()
{
    if (this->open() == false) {
        this->pipe_status = false;
        std::cout << "|||[ERROR] Can not open the pipe to gnuplot. Did you install gnuplot ?" << std::endl;
        throw "Can not open the gnuplot via pipe";
    } else {
        this->pipe_status = true;
    }
}

bool gnuplot::open()
{
    errno = 0;
    this->pipe = popen("gnuplot", "w");
    if (errno == 0) {
        return true;
    } else {
        return false;
    }
}

void gnuplot::close()
{
    Require(this->pipe_status == true,
        "Can not close gnuplot because gnuplot was not opend.");

    this->write("quit");
    pclose(this->pipe);
    this->pipe_status = false;
}

void gnuplot::write(std::string command)
{
    Require(command.size() > 0, "The command is empty. The empty command can not be sent.");
    Require(this->pipe_status == true, "Gnuplot was not open via pipe");

    if (command.back() != '\n') {
        command += "\n";
    }
    fprintf(this->pipe, "%s", command.c_str());
}

void gnuplot::flush()
{
    fflush(this->pipe);
}

class scatter {
public:
    scatter();
    ~scatter();
    void autoscale(bool on = true);
    void grid(bool on = true);
    void plot(const double x, const double y, bool add = true);
    void plot(const std::vector<double>& x, const std::vector<double>& y, bool add = false);
    void set_xlabel(const std::string xlabel);
    void set_ylabel(const std::string ylabel);
    void set_window_size(const unsigned int w = 640, const unsigned int h = 480);
    void show(bool pause = false);

private:
    void plot_and_add();
    void plot_once();
    gnuplot gnuplot_;
    std::vector<double> x_plottable_data_;
    std::vector<double> y_plottable_data_;
};

scatter::scatter()
{
}

scatter::~scatter()
{
}

void scatter::autoscale(bool on)
{
    if (on == true) {
        this->gnuplot_.write("set autoscale");
    } else {
        this->gnuplot_.write("unset autoscale");
    }
}

void scatter::grid(bool on)
{
    if (on == true) {
        this->gnuplot_.write("set grid lw 1.1");
    } else {
        this->gnuplot_.write("unset grid");
    }
}

void scatter::plot(const double x, const double y, bool add)
{
    if (add == false) {
        this->x_plottable_data_.clear();
        this->y_plottable_data_.clear();
    }

    this->x_plottable_data_.push_back(x);
    this->y_plottable_data_.push_back(x);
}

void scatter::plot(const std::vector<double>& x, const std::vector<double>& y, bool add) { }

void scatter::set_xlabel(const std::string xlabel)
{
    std::string plot_command = "\"" + xlabel + "\"";
    this->gnuplot_.write("set xl " + plot_command);
}

void scatter::set_ylabel(const std::string ylabel)
{
    std::string plot_command = "\"" + ylabel + "\"";
    this->gnuplot_.write("set yl " + plot_command);
}

void scatter::set_window_size(const unsigned int w, const unsigned int h)
{
    std::string plot_command = "set terminal qt size " + std::to_string(w) + ", " + std::to_string(h);
    this->gnuplot_.write(plot_command);
}

void scatter::show(bool pause) { }

} // namespace controlive
