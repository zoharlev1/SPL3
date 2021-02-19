package bgu.spl.net.srv.ServerFrames;

import bgu.spl.net.srv.Frame;

import java.util.concurrent.atomic.AtomicInteger;

public class Message extends Frame {
    private int subscribtion;
    private String messageId;
    private String destination;
    private String messageBody;

    public Message(int subscribtion, int messageId, String destination, String messageBody) {
        this.subscribtion = subscribtion;
        this.messageId = Integer.toString(messageId);
        this.destination = destination;
        this.messageBody = messageBody;
    }

    @Override
    public String toString() {
        return "MESSAGE " + '\n' + "subscription:" + subscribtion + '\n' + "Message-id:" + messageId + '\n' + "destination:" + destination + '\n' + messageBody + '\u0000';
    }


    public void setSubscribtion(int numSub) {
        this.subscribtion = numSub;
    }
}
