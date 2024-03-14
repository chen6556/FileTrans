#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "Receiver.hpp"


int main(int argc, char *argv[])
{
    try
    {
        // Check command line arguments.
        if (argc != 3)
        {
            std::cerr << "Usage: http_server <port> <doc_root>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;
        
        Receiver s(io_context, std::atoi(argv[1]), argv[2]);

        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}
