package bgu.spl.net.srv.ServerFrames;

import bgu.spl.net.srv.Frame;

public class Error extends Frame {
    private String header;

    public Error(String header) {
        this.header = header;
    }

    public String toString() {
        return "ERROR" + '\n' + header + '\u0000';
    }

}
