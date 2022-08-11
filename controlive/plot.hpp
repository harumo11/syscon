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
    bool pipe_state = false;
    bool open_gnuplot();
    void close_gnuplot();
};

gnuplot::gnuplot()
{
    if (this->open_gnuplot() == false) {
        this->pipe_state = false;
        std::cout << "|||[ERROR] Can not open the pipe to gnuplot. Did you install gnuplot ?" << std::endl;
        throw "Can not open the gnuplot via pipe";
    } else {
        this->pipe_state = true;
    }
}

bool gnuplot::open_gnuplot()
{
    errno = 0;
    this->pipe = popen("gnuplot", "w");
    if (errno == 0) {
        return true;
    } else {
        return false;
    }
}

void gnuplot::close_gnuplot()
{
    Require(this->pipe_state == true, "Can not close gnuplot because gnuplot was not opend.");

    pclose(this->pipe);
    this->pipe_state = false;
}

void gnuplot::write(std::string command)
{
    Require(command.size() > 0, "The command is empty. The empty command can not be sent.");

    if (command.back() != '\n') {
        command += "\n";
    }
    fprintf(this->pipe, "%s", command.c_str());
}

void gnuplot::flush()
{
    fflush(this->pipe);
}

} // namespace controlive
