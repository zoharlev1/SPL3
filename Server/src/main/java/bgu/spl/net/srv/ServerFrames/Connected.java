package bgu.spl.net.srv.ServerFrames;

import bgu.spl.net.srv.Frame;

public class Connected extends Frame {
    private String version;

    public Connected(String info) {
        this.version = info;
    }

    public String toString() {
        return "CONNECTED\n" + version + '\u0000';
    }
}
