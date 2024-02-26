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

#define _CRT_SECURE_NO_WARNINGS

#pragma warning (disable : 4996)

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

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