#include "Receiver.hpp"
#include "Session.hpp"
#include <signal.h>


Receiver::Receiver(boost::asio::io_context &io_context, const short port, const std::string &dir)
    : _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    _dir(dir)
{
    do_accept();
}

void Receiver::do_accept()
{
    _acceptor.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<Session>(std::move(socket), _dir)->start();
            }

            do_accept();
        });
}  
