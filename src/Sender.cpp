#include "Sender.hpp"
#include <filesystem>


Sender::Sender(boost::asio::io_context &io_context, const boost::asio::ip::tcp::resolver::results_type &endpoints, const std::string &dir)
    : _io_context(io_context), _socket(io_context)
{
    _file.open(dir, std::ios_base::in | std::ios_base::binary);
    _file_size = std::filesystem::file_size(std::filesystem::path(dir));

    std::memcpy(_data, dir.c_str(), dir.size());
    _data[dir.size()] = '?';
    std::string num = std::to_string(_file_size);
    std::memcpy(_data + dir.size() + 1, num.c_str(), num.size());

    do_connect(endpoints);
}

void Sender::do_connect(const boost::asio::ip::tcp::resolver::results_type &endpoints)
{
    boost::asio::async_connect(_socket, endpoints,
        [this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint)
        {
            if (!ec)
            {
                _socket.write_some(boost::asio::buffer(_data, max_length));

                do_write();
            }
        });
}

void Sender::do_write()
{
    if (_file_size >= max_length)
    {
        _file.read(_data, max_length);
        _file_size -= max_length;
    }
    else
    {
        if (_file_size > 0)
        {
            _file.read(_data, _file_size);
            _file_size = 0;
        }
        else
        {
            _file.close();
        }
    }

    _socket.async_write_some(
        boost::asio::buffer(_data, _file.gcount()),
        [this](boost::system::error_code ec, size_t /*length*/)
        {
            if (!ec)
            {
                do_write();
            }
        });
}