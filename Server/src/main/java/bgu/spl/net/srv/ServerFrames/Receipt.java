package bgu.spl.net.srv.ServerFrames;

import bgu.spl.net.srv.Frame;

public class Receipt extends Frame {
    private int receiptId;

    public Receipt(int receiptId){
        this.receiptId = receiptId;
    }

    @Override
    public String toString() {
        return "RECEIPT "+ '\n' +"receipt-id:"+receiptId + '\u0000';
    }
}
