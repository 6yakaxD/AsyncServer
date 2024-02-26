/**
 * @date        19-12-2023
 * @brief       Casuall template of Boost
 *              c++ async tcp server for
 *              using in projects
 * @author      Ramil
 * @copyright   (C) 2023 by not commercial
 */

/*-------------------------[ Boost ]---------------------------*/
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

/*-------------------------[ Other ]--------------------------*/
#include <iostream>
#include <vector>
#include <string>
#include <thread>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)

using namespace boost::asio;

class Server
{
public:
  ip::tcp::acceptor acceptor_;

public:
  Server(io_context& ioContext, int port) : acceptor_(ioContext, ip::tcp::endpoint(ip::tcp::v4(), port))
  {
    StartAccept();

    std::cout << "[Server]: Started" << std::endl;
  }

  void StartAccept();

  void HandleClient(std::shared_ptr<ip::tcp::socket> socket);
    
};