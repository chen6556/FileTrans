#include "Sender.hpp"
#include <iostream>


int main(int argc, char *argv[])
{
    try
    {
        // Check command line arguments.
        if (argc != 4)
        {
            std::cerr << "Usage: Sender <host> <port> <doc_root>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(argv[1], argv[2]);
        
        Sender s(io_context, endpoints, argv[3]);

        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}