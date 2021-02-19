package bgu.spl.net.srv;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.ClientFrames.*;
import bgu.spl.net.srv.ServerFrames.Connected;
import bgu.spl.net.srv.ServerFrames.Error;
import bgu.spl.net.srv.ServerFrames.Message;
import bgu.spl.net.srv.ServerFrames.Receipt;

import java.util.Map;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class StompMessagingProtocalImpl implements StompMessagingProtocol {
    private int connectionId;
    private ConnectionsImpl connections = new ConnectionsImpl();

    @Override
    public void start(int connectionId, Connections connections) {
        this.connectionId = connectionId;
        this.connections = (ConnectionsImpl) connections;

    }

    @Override
    public void process(Frame message) {

        if (message instanceof Connect) {
            String currUserName = ((Connect) message).getUsername();
            //checking if user exists in our database
            if (BookClubDataBase.nameUserMap.containsKey(currUserName)) {
                //user exists in database - checking if passwords match
                if (BookClubDataBase.nameUserMap.get(currUserName).getPassword().equals(((Connect) message).getPassword())) {
                    //user exists and passwords match - checking if user is active, if so sending error
                    //if not establishing connection and sending connected frame to client
                    if (BookClubDataBase.nameUserMap.get(currUserName).isActive()) {
                        Error alreadyLogged = new Error("User already logged in");
                        connections.send(connectionId, alreadyLogged);
                    } else {
                        BookClubDataBase.nameUserMap.get(currUserName).setActive(true);
                        Connected connected = new Connected(((Connect) message).getAcceptVersion());
                        connections.send(connectionId, connected);
                    }
                } else {
                    Error wrongPass = new Error("Wrong password");
                    connections.send(connectionId, wrongPass);
                    connections.disconnect(connectionId);
                }
            }
            // user does not exist initializing new one
            else {
                BookClubMember curr = new BookClubMember(currUserName, ((Connect) message).getPassword(), connectionId);
                BookClubDataBase.idMemberMap.putIfAbsent(connectionId, curr);
                BookClubDataBase.nameUserMap.putIfAbsent(currUserName, curr);
                Connected success = new Connected("version:1.2");
                BookClubDataBase.nameUserMap.get(currUserName).setActive(true);
                connections.send(connectionId, success);
            }
        }
        if (message instanceof Subscribe) {
            BookClubDataBase.genreMap.putIfAbsent(((Subscribe) message).getDestination(), new ConcurrentLinkedQueue<BookClubMember>());
            BookClubDataBase.genreMap.get(((Subscribe) message).getDestination()).add(BookClubDataBase.idMemberMap.get(connectionId));
            Receipt receiptSub = new Receipt(((Subscribe) message).getReceipt());
            BookClubDataBase.idMemberMap.get(connectionId).insertSubId(((Subscribe) message).getDestination());
            connections.send(connectionId, receiptSub);

        }

        if (message instanceof Unsubscribe) {
            String des = ((Unsubscribe) message).getDestination();
            BookClubDataBase.genreMap.get(des).remove(BookClubDataBase.idMemberMap.get(connectionId));
            BookClubDataBase.idMemberMap.get(connectionId).unSub(des);
            Receipt receiptSub = new Receipt(((Unsubscribe) message).getReceipt());
            connections.send(connectionId, receiptSub);
        }

        if (message instanceof Send) {
            Message output = new Message(BookClubDataBase.idMemberMap.get(connectionId).getCounterFromMap(((Send) message).getDestination()), ConnectionsImpl.messageId.intValue(), ((Send) message).getDestination(), ((Send) message).getMessageFrame());
            ConnectionsImpl.messageId.getAndIncrement();
            connections.send(((Send) message).getDestination(), output);
        }

        if (message instanceof Disconnect) {
            BookClubDataBase.idMemberMap.get(connectionId).setActive(false);
            Receipt rec = new Receipt(((Disconnect) message).getReceipt());

            BookClubMember toRemove = BookClubDataBase.idMemberMap.get(connectionId);
            //removing this cleint from all subscriptions
            synchronized (this) {
                for (Map.Entry<String, ConcurrentLinkedQueue<BookClubMember>> entry : BookClubDataBase.genreMap.entrySet()) {
                    for (BookClubMember x : entry.getValue()) {
                        if (x.getConnectionId() == connectionId)
                            entry.getValue().remove(x);
                    }
                }
                BookClubDataBase.idMemberMap.remove(connectionId);
                BookClubDataBase.nameUserMap.remove(toRemove.getUsername());
            }

            //send receipt
            connections.send(connectionId, rec);
            //need to delete all
            connections.disconnect(connectionId);

        }


    }


    @Override
    public boolean shouldTerminate() {
        return false;
    }
}
