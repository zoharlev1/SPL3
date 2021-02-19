package bgu.spl.net.srv;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class BookClubMember {
    private String username;
    private String password;
    private volatile boolean isActive;
    private int connectionId;
    private Map<String, Integer> subscriptionToId;
    private Integer counter;

    public BookClubMember(String username, String password, int connectionId) {
        this.username = username;
        this.password = password;
        this.connectionId = connectionId;
        isActive = false;
        subscriptionToId = new ConcurrentHashMap<String, Integer>();
        counter = 1;
    }


    public void setActive(boolean active) {
        isActive = active;
    }

    public boolean isActive() {
        return isActive;
    }

    public String getPassword() {
        return password;
    }

    public void insertSubId(String genre) {
        subscriptionToId.putIfAbsent(genre, counter);
        counter++;
    }

    public void unSub(String genre) {
        subscriptionToId.remove(genre);
    }

    public int getConnectionId() {
        return connectionId;
    }

    public Integer getCounterFromMap(String genre) {
        if (subscriptionToId.get(genre) == null)
            return -1; //in case we dont subscribe to the genre but we still want to add book
        return subscriptionToId.get(genre);
    }

    public String getUsername() {
        return username;
    }
}
