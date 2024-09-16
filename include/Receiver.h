#pragma once
#include <array>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

constexpr short multicast_port = 30001;

class Receiver
{
private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    std::array<char, 1024> data_;
    void Receive(){
        socket_.async_receive_from(boost::asio::buffer(data_), sender_endpoint_, 
                                   [this](boost::system::error_code ec, std::size_t length){
                                        if(!ec){
                                            std::cout.write(data_.data(), length);
                                            std::cout << std::endl;
                                            Receive();
                                        }
                                   });
    }

public:
    Receiver(boost::asio::io_context& ioc, const boost::asio::ip::address& listen_address,
             const boost::asio::ip::address& multicast_address);
    ~Receiver();
};

Receiver::Receiver(boost::asio::io_context& ioc, const boost::asio::ip::address& listen_address,
             const boost::asio::ip::address& multicast_address): socket_(ioc)
{
    boost::asio::ip::udp::endpoint listen_endpoint(listen_address, multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);
    socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address));
    std::cout << "Subscribing to multicast" << std::endl;
    Receive();
}

Receiver::~Receiver()
{
}


