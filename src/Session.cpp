#include "Session.hpp"
#include <filesystem>
#include <iostream>


Session::Session(boost::asio::ip::tcp::socket socket, const std::string &dir)
    : _socket(std::move(socket)), _dir(dir) {}

Session::~Session()
{
    _file.close();
}

void Session::start()
{
    do_read();
}

void Session::do_read()
{
    std::shared_ptr<Session> self(shared_from_this());
    _socket.async_read_some(boost::asio::buffer(_data, max_length),
        [this, self](boost::system::error_code ec, size_t length)
        {
            if (!ec)
            {
                if (length > 0)
                {
                    switch (_state)
                    {
                    case State::Waiting:
                        {
                            std::string temp(_data);
                            _dir.push_back('/');
                            _dir.append(std::filesystem::path(temp.substr(0, temp.find('?'))).filename().generic_string());
                            _file.open(_dir, std::ios_base::out | std::ios_base::binary);
                            _file_size = std::stoull(temp.substr(temp.find('?') + 1));
                            _state = State::Reading;
                        }
                        break;
                    case State::Reading:
                        _file.write(_data, length);
                        _file_size -= length;
                        if (_file_size == 0)
                        {
                            _state = State::End;
                        }
                        break;
                    case State::End:
                        std::cout << std::filesystem::path(_dir).filename() << std::endl;
                        return _socket.shutdown(boost::asio::socket_base::shutdown_both);
                    default:
                        break;
                    }
                }

                do_read();
            }
        });
}