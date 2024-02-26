/**
 * @date        19-12-2023
 * @brief       Casuall template of Boost
 *              c++ async tcp server for
 *              using in projects
 * @author      Ramil
 * @copyright   (C) 2023 by not commercial
 *
 * 
                    _oo0oo_
                   o8888888o
                   88" . "88
                   (| -_- |)
                   0\  =  /0
                 ___/`---'\___
               .' \\|     |// '.
              / \\|||  :  |||// \
             / _||||| -:- |||||- \
            |   | \\\  -  /// |   |
            | \_|  ''\---/''  |_/ |
            \  .-\__  '-'  ___/-. /
          ___'. .'  /--.--\  `. .'___
       ."" '<  `.___\_<|>_/___.' >' "".
      | | :  `- \`.;`\ _ /`;.`/ - ` : | |
      \  \ `_.   \_ __\ /__ _/   .-` /  /
  =====`-.____`.___ \_____/___.-`___.-'=====
                       `=---='


  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  God Bless     No Bugs (at least in my side)

 */


#include "Server.h"

int main()
{
  io_context ioContext;
  Server server(ioContext, 43990);
  ioContext.run();
    
  return (0);
}