package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.Frame;

public class Unsubscribe extends Frame {
    private int id;
    private String destination;
    private int receipt;


    public Unsubscribe(int id, String destination, int receipt) {
        this.id = id;
        this.destination = destination;
        this.receipt = receipt;
    }

    public int getId() {
        return id;
    }

    public String getDestination() {
        return destination;
    }

    public int getReceipt() {
        return receipt;
    }

    @Override
    public String toString() {
        return null;
    }
}
