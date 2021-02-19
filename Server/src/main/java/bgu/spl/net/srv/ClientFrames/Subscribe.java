package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.Frame;

public class Subscribe extends Frame {
    private String destination;
    private int id;
    private int receipt;

    public Subscribe(String destination, int id, int receipt){
        this.destination = destination;
        this.id = id;
        this.receipt=receipt;
    }

    public String getDestination() {
        return destination;
    }

    public int getId() {
        return id;
    }

    public int getReceipt() {
        return receipt;
    }

    @Override
    public String toString() {
        String temp= "RECEIPT"+'\n';
        temp=temp+"receipt-id:" +receipt+ '\0';
        return temp;
    }
}
