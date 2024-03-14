#pragma once

#include <boost/asio.hpp>
#include <string>


class Receiver
{
private:
    boost::asio::ip::tcp::acceptor _acceptor;
    std::string _dir;

public:
    Receiver(boost::asio::io_context &io_context, const short port, const std::string &dir);

private:
    void do_accept();
};