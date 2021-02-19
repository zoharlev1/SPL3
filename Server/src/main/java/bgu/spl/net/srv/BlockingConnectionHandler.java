package bgu.spl.net.srv;

import bgu.spl.net.api.StompMessagingProtocol;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.net.Socket;

public class BlockingConnectionHandler<T> implements Runnable, ConnectionHandler<T> {

    private final StompMessagingProtocol protocol;
    private final EncoderDecoderImpl<T> encdec;
    private final Socket sock;
    private BufferedInputStream in;
    private BufferedOutputStream out;
    private volatile boolean connected = true;

    public BlockingConnectionHandler(Socket sock, EncoderDecoderImpl<T> reader, StompMessagingProtocol protocol) {
        this.sock = sock;
        this.encdec = reader;
        this.protocol = protocol;
    }

    @Override
    public void run() {
        try (Socket sock = this.sock) { //just for automatic closing
            int read;

            in = new BufferedInputStream(sock.getInputStream());
            out = new BufferedOutputStream(sock.getOutputStream());

            while (!protocol.shouldTerminate() && connected && (read = in.read()) >= 0) {
                Frame nextMessage = encdec.decodeNextByteFrame((byte) read);

                if (nextMessage != null) {
                    protocol.process(nextMessage);

                }
            }

        } catch (IOException ex) {

        }

    }

    @Override
    public void close() {
        connected = false;
        try {
            sock.close();
        } catch (IOException e) {
        }
        ;
    }

    @Override
    public void send(T msg) {
        try {
            out = new BufferedOutputStream(sock.getOutputStream());
            out.write(encdec.encode((msg.toString())));
            out.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    //Connection handler will initialize protocal from BaseServer
    public void initialize(int id, Connections connections) {
        this.protocol.start(id, connections);
    }
}
