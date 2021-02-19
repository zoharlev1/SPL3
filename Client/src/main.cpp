#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <thread>
#include <KeyboardInput.hpp>
#include <ServerReader.hpp>


using namespace std;

int main() {
    bool login = false;
    while (!login) {
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        vector<string> strs;
        string output = "";
        boost::split(strs, line, boost::is_any_of(" "));


        if (strs[0] == "login") {
            login = true;
            vector<string> portHost;
            boost::split(portHost, strs[1], boost::is_any_of(":"));

            short myShort = boost::lexical_cast<short>(portHost[1]);
            Client bookWorm = Client(strs[2], strs[3]);
            ConnectionHandler handler(portHost[0], myShort, &bookWorm);
            if (!handler.connect()) {
                std::cerr << "Cannot connect to " << portHost[0] << ":" << myShort << std::endl;
                return 1;
            }

            output = output + "CONNECT" + '\n';

            output = output + "accept version:1.2" + '\n';

            output = output + "host:stomp.cs.bgu.ac.il" + '\n';

            output = output + "login:" + strs[2] + '\n';

            output = output + "password:" + strs[3] + '\n';

            output = output + '\n';

            output = output + '\0';

            handler.sendFrameAscii(output, '\0');
            string ans = "";

            handler.getLine(ans);
            vector<string> input;
            boost::split(input, ans, boost::is_any_of("\n"));


            if (input[0] == "CONNECTED") {
                handler.setloggedIn(true);
                //initiate thread for reading and writing
                Keyboardinput keyBoardInput(handler);
                std::thread keyboardinputThread(&Keyboardinput::input, &keyBoardInput);
                ServerReader serverReader(handler);
                std::thread serverreaderThread(&ServerReader::read, &serverReader);

                keyboardinputThread.join();
                serverreaderThread.join();


            } else if (input[0] == "ERROR") {
                cout << input[1] << endl;
            }


        }
    }
    return 0;
}