package bgu.spl.net.srv.ClientFrames;

import bgu.spl.net.srv.Frame;

public class Connect extends Frame {
    private String acceptVersion;
    private String host;
    private String username;
    private String password;

    public Connect(String acceptV, String host, String username, String password) {
        this.username = username;
        this.password = password;
        this.host = host;
        this.acceptVersion = acceptV;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public String getHost() {
        return host;
    }

    public String getAcceptVersion() {
        return acceptVersion;
    }

    @Override
    public String toString() {
        return username + " " + password + " " + host + " " + acceptVersion;
    }
}
