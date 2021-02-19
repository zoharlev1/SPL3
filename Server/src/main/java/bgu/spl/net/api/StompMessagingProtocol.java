package bgu.spl.net.api;

import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.Frame;

public interface StompMessagingProtocol  {
	/**
	 * Used to initiate the current client protocol with it's personal connection ID and the connections implementation
	**/
    void start(int connectionId, Connections connections);
    
    void process(Frame message);
	
	/**
     * @return true if the connection should be terminated
     */
    boolean shouldTerminate();
}
