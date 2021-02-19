package bgu.spl.net.srv;

import bgu.spl.net.srv.ServerFrames.Message;

import java.io.IOException;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

public class ConnectionsImpl implements Connections<Frame> {
    private ConcurrentHashMap<Integer, ConnectionHandler> connectionHandlerMap = new ConcurrentHashMap<Integer, ConnectionHandler>();

    public ConcurrentHashMap<Integer, ConnectionHandler> getConnectionHandlerMap() {
        return connectionHandlerMap;
    }

    public static AtomicInteger messageId = new AtomicInteger(1);

    @Override
    public boolean send(int connectionId, Frame msg) {
        ConnectionHandler curr = connectionHandlerMap.get(connectionId);
        if (curr != null) {
            curr.send(msg.toString());
            return true;
        }
        return false;
    }

    @Override
    public void send(String channel, Frame msg) {

        if (BookClubDataBase.genreMap.containsKey(channel)) {
            for (BookClubMember x : BookClubDataBase.genreMap.get(channel)) {
                if (msg instanceof Message) {
                    ((Message) msg).setSubscribtion(x.getCounterFromMap(channel));
                }
                int currId = x.getConnectionId();
                connectionHandlerMap.get(currId).send(msg.toString());
            }
        }
    }

    @Override
    public void disconnect(int connectionId) {
        try {
            connectionHandlerMap.get(connectionId).close();
        } catch (IOException e) {
        }
        ;
        connectionHandlerMap.remove(connectionId);

    }

    public void addConnectionHandler(int key, ConnectionHandler handler) {
        connectionHandlerMap.putIfAbsent(key, handler);
    }
}
