package bgu.spl.net.impl.stomp;

import bgu.spl.net.srv.*;

public class StompServer {

    public static void main(String[] args) {

        if (args.length < 2) {
            System.out.println("input:port,server");
            System.exit(1);
        }

        if (args[1].equals("tpc")) {
            Server.threadPerClient(Integer.parseInt(args[0]), StompMessagingProtocalImpl::new, EncoderDecoderImpl::new).serve();
        } else if (args[1].equals("reactor")) {
            Server.reactor(Runtime.getRuntime().availableProcessors(), Integer.parseInt(args[0]), StompMessagingProtocalImpl::new, EncoderDecoderImpl::new).serve();
        }


    }


}