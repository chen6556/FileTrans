#pragma once

#include <boost/asio.hpp>
#include <fstream>


class Sender
{
private:
    boost::asio::io_context &_io_context;
    boost::asio::ip::tcp::socket _socket;
    std::ifstream _file;
    size_t _file_size = 0;
    static const size_t max_length = 4096;
    char _data[max_length] = {'\0'};

public:
    Sender(boost::asio::io_context &io_context, const boost::asio::ip::tcp::resolver::results_type &endpoints, const std::string &dir);

private:
    void do_connect(const boost::asio::ip::tcp::resolver::results_type &endpoints);

    void do_write();

};