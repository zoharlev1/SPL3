package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.Frame;

public class Send extends Frame {
    private String destination;
    private String messageFrame;
    private int subscriptionId;

    public Send(String destination, String messageFrame) {
        this.destination = destination;
        this.messageFrame = messageFrame;
    }

    public String getDestination() {
        return destination;
    }

    public String getMessageFrame() {
        return messageFrame;
    }

    @Override
    public String toString() {
        return null;
    }
}
