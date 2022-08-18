#pragma once

#include "bertrand/include/bertrand/bertrand.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

namespace cntl {

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

gnuplot::~gnuplot()
{
    this->close();
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
    Require(this->pipe_status == true, "Can not close gnuplot because gnuplot was not opend.");

    this->write("quit");
    pclose(this->pipe);
    this->pipe_status = false;
}

void gnuplot::write(std::string command)
{
    Require(command.size() > 0, "The plot command is empty. The empty command can not be sent.");
    Require(this->pipe_status == true, "Gnuplot was not open via pipe");

    if (command.back() != '\n') {
        command += "\n";
    }
    fprintf(this->pipe, "%s", command.c_str());
}

void gnuplot::flush()
{
    Require(this->pipe_status == true, "Gnuplot was not open via pipe");

    fflush(this->pipe);
}

class scatter {
public:
    scatter();
    ~scatter();
    void autoscale(bool on = true);
    void grid(bool on = true);
    void plot(const double x, const double y, bool add_data = true);
    void plot(const std::vector<double>& x, const std::vector<double>& y, bool add_data = false);
    void set_xlabel(const std::string xlabel);
    void set_ylabel(const std::string ylabel);
    void set_title(const std::string title);
    void set_window_size(const unsigned int w = 640, const unsigned int h = 480);
    void show(bool pause_window = false);

private:
    gnuplot gnuplot_;
    bool is_set_plottable_data_ = false;
    std::vector<double> x_plottable_data_;
    std::vector<double> y_plottable_data_;
};

scatter::scatter()
{
    this->autoscale(true);
    this->grid(true);
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

void scatter::plot(const double x, const double y, bool add_data)
{
    if (add_data == false) {
        this->x_plottable_data_.clear();
        this->y_plottable_data_.clear();
    }

    this->x_plottable_data_.push_back(x);
    this->y_plottable_data_.push_back(y);

    this->is_set_plottable_data_ = true;
}

void scatter::plot(const std::vector<double>& x, const std::vector<double>& y, bool add_data)
{
    Require(x.size() > 0, "The size of x that will be plot must be bigger than 0.");
    Require(y.size() > 0, "The size of y that will be plot must be bigger than 0.");
    Require(x.size() == y.size(), "The size of x and y that will be plot must be same size.");

    if (add_data == false) {
        this->x_plottable_data_.clear();
        this->y_plottable_data_.clear();
    }

    this->x_plottable_data_.insert(this->x_plottable_data_.end(), x.begin(), x.end());
    this->y_plottable_data_.insert(this->y_plottable_data_.end(), y.begin(), y.end());

    this->is_set_plottable_data_ = true;
}

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

void scatter::set_title(const std::string title)
{
    std::string title_plot_command = "\"" + title + "\"";
    this->gnuplot_.write("set title " + title_plot_command);
}

void scatter::set_window_size(const unsigned int w, const unsigned int h)
{
    Require(w > 0, "Window width must be bigger than 0.");
    Require(w > 0, "Window height must be bigger than 0.");

    std::string plot_command = "set terminal qt size " + std::to_string(w) + ", " + std::to_string(h);
    this->gnuplot_.write(plot_command);
}

void scatter::show(bool pause_window)
{
    Require(this->x_plottable_data_.size() == this->y_plottable_data_.size(), "x and y that will be plot must have same size.");
    Require(this->is_set_plottable_data_ = true, "Set the plottable data using plot(), before call show()");

    std::string plot_begin_command = "plot '-' w p pt 7 lw 1.5";
    this->gnuplot_.write(plot_begin_command);

    auto plottable_data_size = this->x_plottable_data_.size();
    for (int i = 0; i < plottable_data_size; i++) {
        std::string plot_data_command = std::to_string(x_plottable_data_.at(i)) + "\t" + std::to_string(y_plottable_data_.at(i));
        this->gnuplot_.write(plot_data_command);
    }

    std::string plot_end_command = "e";
    this->gnuplot_.write(plot_end_command);
    this->gnuplot_.flush();

    if (pause_window == true) {
        std::cin.get();
    }
}

} // namespace cntl
