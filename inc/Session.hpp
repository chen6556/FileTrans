#pragma once

#include <memory>
#include <boost/asio.hpp>
#include <fstream>


class Session : public std::enable_shared_from_this<Session>
{
private:
    boost::asio::ip::tcp::socket _socket;
    static const int max_length = 4096;
    char _data[max_length];
    std::string _dir;
    size_t _file_size = 0;
    std::ofstream _file;
    enum State {Waiting, Reading, End} _state = State::Waiting;

public:
    Session(boost::asio::ip::tcp::socket socket, const std::string &dir);

    ~Session();

    void start();

private:
    void do_read();

};