#pragma once

#include "bertrand/include/bertrand/bertrand.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>

namespace syscon {

class gnuplot {
public:
    gnuplot()
    {
        if (this->open() == false) {
            this->pipe_status = false;
            std::cout << "|||[ERROR] Can not open the pipe to gnuplot. Did you install gnuplot ?" << std::endl;
            throw "Can not open the gnuplot via pipe";
        } else {
            this->pipe_status = true;
        }
    };

    ~gnuplot()
    {
        this->close();
    };

    void write(std::string command)
    {
        Require(command.size() > 0, "The plot command is empty. The empty command can not be sent.");
        Require(this->pipe_status == true, "Gnuplot was not open via pipe");

        if (command.back() != '\n') {
            command += "\n";
        }
        fprintf(this->pipe, "%s", command.c_str());
    };

    void flush()
    {
        Require(this->pipe_status == true, "Gnuplot was not open via pipe");

        fflush(this->pipe);
    };

private:
    FILE* pipe;
    bool pipe_status = false;

    bool open()
    {
        errno = 0;
        this->pipe = popen("gnuplot", "w");
        if (errno == 0) {
            return true;
        } else {
            return false;
        }
    };

    void close()
    {
        Require(this->pipe_status == true, "Can not close gnuplot because gnuplot was not opend.");

        this->write("quit");
        pclose(this->pipe);
        this->pipe_status = false;
    };
};

class scatter {
public:
    scatter()
    {
        this->autoscale(true);
        this->grid(true);
    };

    void autoscale(bool on = true)
    {
        if (on == true) {
            this->gnuplot_.write("set autoscale");
        } else {
            this->gnuplot_.write("unset autoscale");
        }
    };

    void grid(bool on = true)
    {
        if (on == true) {
            this->gnuplot_.write("set grid lw 1.1");
        } else {
            this->gnuplot_.write("unset grid");
        }
    };

    void plot(const double x, const double y, bool add_data = true)
    {
        if (add_data == false) {
            this->x_plottable_data_.clear();
            this->y_plottable_data_.clear();
        }

        this->x_plottable_data_.push_back(x);
        this->y_plottable_data_.push_back(y);
        this->is_set_plottable_data_ = true;
    };

    void plot(const std::vector<double>& x, const std::vector<double>& y, bool add_data = false)
    {
        Require(x.size() > 0, "The size of x that will be plot must be bigger than 0.");
        Require(y.size() > 0, "The size of y that will be plot must be bigger than 0.");
        Require(x.size() == y.size(), "The data size of x and y that will be plot must be same size.");

        if (add_data == false) {
            this->x_plottable_data_.clear();
            this->y_plottable_data_.clear();
        }

        this->x_plottable_data_.insert(this->x_plottable_data_.end(), x.begin(), x.end());
        this->y_plottable_data_.insert(this->y_plottable_data_.end(), y.begin(), y.end());

        this->is_set_plottable_data_ = true;
    };

    void set_xlabel(const std::string xlabel, const unsigned int font_size = 10)
    {
        Require(font_size != 0, "Font size in x label must not be 0. But 0 is set.");

        std::string font_set_command = "set xl font \"Arial, " + std::to_string(font_size) + "\"";
        std::string xlabel_set_command = "set xl \"" + xlabel + "\"";
        this->gnuplot_.write(font_set_command);
        this->gnuplot_.write(xlabel_set_command);
    };

    void set_ylabel(const std::string ylabel, const unsigned int font_size = 10)
    {
        Require(font_size != 0, "Font size in y label must not be 0. But 0 is set.");

        std::string font_set_command = "set yl font \"Arial, " + std::to_string(font_size) + "\"";
        std::string ylabel_set_command = "set yl \"" + ylabel + "\"";
        this->gnuplot_.write(font_set_command);
        this->gnuplot_.write(ylabel_set_command);
    };

    void set_xrange(const double min, const double max)
    {
        Require(max > min, "Now, min at x axis range is bigger than max. Min must be smaller than max");

        this->autoscale(false);
        std::string xrange_set_command = "set xrange[" + std::to_string(min) + ":" + std::to_string(max) + "]";
        this->gnuplot_.write(xrange_set_command);
    };

    void set_yrange(const double min, const double max)
    {
        Require(max > min, "Now, min at y axis range is bigger than max. Min must be smaller than max");

        this->autoscale(false);
        std::string yrange_set_command = "set yrange[" + std::to_string(min) + ":" + std::to_string(max) + "]";
        this->gnuplot_.write(yrange_set_command);
    };

    void set_title(const std::string title, const unsigned int font_size = 10)
    {
        Require(font_size != 0, "Font size in title must not be 0. But 0 is set.");

        std::string font_set_command = "set title font \"Arial, " + std::to_string(font_size) + "\"";
        std::string title_set_command = "set title \"" + title + "\"";
        this->gnuplot_.write(font_set_command);
        this->gnuplot_.write(title_set_command);

        std::string title_plot_command = "\"" + title + "\"";
        this->gnuplot_.write("set title " + title_plot_command);
    };

    void set_window_size(const unsigned int w = 640, const unsigned int h = 480)
    {
        Require(w > 0, "Window width must be bigger than 0.");
        Require(w > 0, "Window height must be bigger than 0.");

        std::string plot_command = "set terminal qt size " + std::to_string(w) + ", " + std::to_string(h);
        this->gnuplot_.write(plot_command);
    };

    void show(const bool pause_window = false, const bool with_line = false, const std::string color_name = "steelblue")
    {
        Require(this->x_plottable_data_.size() == this->y_plottable_data_.size(), "x and y that will be plot must have same size.");
        Require(this->is_set_plottable_data_ = true, "Set the plottable data using plot(), before call show()");

        std::string plot_begin_command;
        if (with_line) {
            // color pallet is here. https://ayapin-film.sakura.ne.jp/Gnuplot/Primer/Misc/colornames.html
            // plot_begin_command = std::string("plot '-' with lines linewidth 3 linecolor rgbcolor ") + std::string("\'") + color_name + std::string("\'");
            plot_begin_command = std::string("plot '-' notitle with lines linewidth 3 linecolor rgbcolor ") + std::string("\'") + color_name + std::string("\'");

        } else {
            // plot_begin_command = "plot '-' with points pointtype 7 pointsize 1";
            // plot_begin_command = std::string("plot '-' with points pointtype 7 linecolor rgbcolor ") + std::string("\'") + color_name + std::string("\'");
            plot_begin_command = std::string("plot '-' notitle with points pointtype 7 linecolor rgbcolor ") + std::string("\'") + color_name + std::string("\'");
        }
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
    };

private:
    gnuplot gnuplot_;
    bool is_set_plottable_data_ = false;
    std::vector<double> x_plottable_data_;
    std::vector<double> y_plottable_data_;
};

class bode_plot {
public:
    bode_plot();
    void autoscale(bool on) {};
    void grid(bool on) {};
    void plot(const double x, const double y, bool add_data) {};
    void set_xlabel(const std::string xlabel, const unsigned int font_size) {};
    void set_ylabel(const std::string ylabel, const unsigned int font_size) {};
    void set_logscale(bool on);
    void set_xrange(const double min, const double max) {};
    void set_yrange(const double min, const double max) {};
    void set_title(const std::string title, const unsigned int font_size) {};
};

} // namespace syscon
