﻿#include "Server.h"



int main()
{
  io_context ioContext;
  Server server(ioContext, 43990);
  ioContext.run();
    
  return (0);
}

