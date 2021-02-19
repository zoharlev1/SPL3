package bgu.spl.net.srv;

import bgu.spl.net.api.StompMessagingProtocol;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.function.Supplier;

public abstract class BaseServer<T> implements Server<T> {

    private final int port;
    private final Supplier<StompMessagingProtocalImpl> protocolFactory;
    private final Supplier<EncoderDecoderImpl> encdecFactory;
    private ServerSocket sock;
    private int connectionHandlerId = 1;
    private ConnectionsImpl connections = new ConnectionsImpl();

    public BaseServer(
            int port,
            Supplier<StompMessagingProtocalImpl> protocolFactory,
            Supplier<EncoderDecoderImpl> encdecFactory) {

        this.port = port;
        this.protocolFactory = protocolFactory;
        this.encdecFactory = encdecFactory;
        this.sock = null;
    }

    @Override
    public void serve() {

        try (ServerSocket serverSock = new ServerSocket(port)) {
            this.sock = serverSock; //just to be able to close
            while (!Thread.currentThread().isInterrupted()) {
                Socket clientSock = serverSock.accept();
                StompMessagingProtocol protocol = protocolFactory.get();
                protocol.start(connectionHandlerId, connections);
                BlockingConnectionHandler handler = new BlockingConnectionHandler(
                        clientSock,
                        encdecFactory.get(),
                        protocol);
                //initializing protocol with connection handler unique id that will match user unique id
                handler.initialize(connectionHandlerId, connections);
                connections.addConnectionHandler(connectionHandlerId, handler);
                connectionHandlerId++;
                execute(handler);
            }
        } catch (IOException ex) {
        }

        System.out.println("server closed!!!");
    }

    @Override
    public void close() throws IOException {
        if (sock != null)
            sock.close();
    }

    protected abstract void execute(BlockingConnectionHandler<T> handler);

}
