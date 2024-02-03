#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <boost/asio.hpp>
#include <vector>
#include <string>
#include <thread>
#include "shellapi.h"

#include "Data.h"

#include "json.hpp"

#define _CRT_SECURE_NO_WARNINGS



#pragma warning (disable : 4996)

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost::asio;



class Server
{

public:
    ip::tcp::acceptor acceptor_;

    std::vector<ip::tcp::socket> clients;

    

public:

    Server(io_context& ioContext, int port) : acceptor_(ioContext, ip::tcp::endpoint(ip::tcp::v4(), port))
    {
        StartAccept();
    
        std::cout << "[Server]: Started" << std::endl;
        g_data.SendInformationNotification("Resto", "Server Started");
    }

    void StartAccept()
    {
        auto socket = std::make_shared<ip::tcp::socket>(acceptor_.get_executor());

        acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code& error)
            {
                if (!error)
                {

                    HandleClient(socket);
                    
                }
                StartAccept();
            });
    }



    void HandleClient(std::shared_ptr<ip::tcp::socket> socket)
    {
        std::thread([this, socket]()
            {
                try
                {
                    std::cout << "[Server]: New client connected IP -> " << socket->remote_endpoint();
                    g_data.COUT_CurrTime();

                    while (true)
                    {
                        boost::system::error_code error;

                        // Recieve
                        char data[1024];
                        size_t length = socket->read_some(buffer(data), error);

                        // �������� ����ok
                        if (error == error::eof)
                        {
                            std::cout << "[Server]: Client disconnected -> " << socket->remote_endpoint() << std::endl;
                            break;
                        }
                        else if (error)
                        {
                            throw boost::system::system_error(error);
                        }


                        std::string request(data, length);


                        std::vector<std::string> tokens;
                        size_t pos = 0, found;
                        while ((found = request.find("#", pos)) != std::string::npos)
                        {
                            tokens.push_back(request.substr(pos, found - pos));
                            pos = found + 1;
                        }
                        tokens.push_back(request.substr(pos));

                        if (tokens.size() >= 2)
                        {
                            
                            std::string requestType = tokens[0];
                            std::string requestData = tokens[1];
                            std::cout << "[Client]: " << requestType << "#" << requestData << std::endl;


                            // [ ������� ]


                            if (requestType == "AUTH")
                            {

                            }


                        }

                       

                        if (error == error::eof)
                        {
                            std::cout << "[Server]: Client disconnected -> " << socket->remote_endpoint() << std::endl;
                            break;
                        }
                        else if (error)
                        {
                            throw boost::system::system_error(error);
                        }

                    }
                }
                catch (std::exception& e)
                {
                    std::cerr << "Exception: " << e.what() << std::endl;
                }
                



            }).detach();
    }


    
    
    
};