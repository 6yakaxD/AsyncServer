#include "Server.h"


void Server::StartAccept()
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

void Server::HandleClient(std::shared_ptr<ip::tcp::socket> socket)
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

          // error check
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


            // [ Requests ]


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