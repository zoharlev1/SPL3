#ifndef CONNECTION_HANDLER__
#define CONNECTION_HANDLER__

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "../include/Client.hpp"

using boost::asio::ip::tcp;

class ConnectionHandler {
private:


    const std::string host_;
    const short port_;
    boost::asio::io_service io_service_;   // Provides core I/O functionality
    tcp::socket socket_;
    //in the read- after we get okay from the server we will set all the client info
    Client *myClient_;
    bool loggedIn;

public:
    ConnectionHandler(const ConnectionHandler &sess);

    ConnectionHandler &operator=(const ConnectionHandler &other);

    //bool static loggedIn;
    ConnectionHandler(std::string host, short port, Client *myClient);

    ~ConnectionHandler();

    // Connect to the remote machine
    bool connect();

    // Read a fixed number of bytes from the server - blocking.
    // Returns false in case the connection is closed before bytesToRead bytes can be read.
    bool getBytes(char bytes[], unsigned int bytesToRead);

    // Send a fixed number of bytes from the client - blocking.
    // Returns false in case the connection is closed before all the data is sent.
    bool sendBytes(const char bytes[], int bytesToWrite);

    // Read an ascii line from the server
    // Returns false in case connection closed before a newline can be read.
    bool getLine(std::string &line);

    // Send an ascii line from the server
    // Returns false in case connection closed before all the data is sent.
    bool sendLine(std::string &line);

    // Get Ascii data from the server until the delimiter character
    // Returns false in case connection closed before null can be read.
    bool getFrameAscii(std::string &frame, char delimiter);

    // Send a message to the remote host.
    // Returns false in case connection is closed before all the data is sent.
    bool sendFrameAscii(const std::string &frame, char delimiter);

    // Close down the connection properly.
    void close();

    bool getloggedIn() { return loggedIn; }

    void setloggedIn(bool a) { loggedIn = a; }

    Client &getClient();
};

#endif