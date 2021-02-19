package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.Frame;

public class Disconnect extends Frame {
    private int receipt;

    public Disconnect(int receipt){
        this.receipt = receipt;
    }

    public int getReceipt() {
        return receipt;
    }

    @Override
    public String toString() {
        return null;
    }
}
