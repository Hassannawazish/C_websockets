#include <iostream>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <thread>

using namespace std;
using tcp = boost::asio::ip::tcp;
int main(){
    auto const address = boost::asio::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short >(std::atoi("8083"));

    boost::asio::io_context ioc{1};
    tcp::acceptor acceptor{ioc, {address, port}};

    while(1)
    {
        tcp::socket socket{ioc};
        acceptor.accept(socket);
        std::cout<<"socket accepted"<<endl;

        thread{[q = move(socket)]() mutable{
            boost::beast::websocket::stream<tcp::socket> ws  {move(q)};
            ws.accept();

            while(1){
                 boost::beast::flat_buffer buffer;
                 ws.read(buffer);

                 auto out = boost::beast::buffers_to_string(buffer.cdata());
                 cout<<out<<endl;
            }
        }}.detach();

    }
    return 0;
}
