package bgu.spl.net.srv;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.srv.ClientFrames.Connect;
import bgu.spl.net.srv.ClientFrames.*;

import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class EncoderDecoderImpl<T> implements MessageEncoderDecoder<String> {
    private byte[] bytes = new byte[1 << 10]; //start with 1k
    private int len = 0;
    private List<String> input = new LinkedList<String>();

    @Override
    public String decodeNextByte(byte nextByte) {

        if (nextByte == '\u0000') {
            return popString();
        }

        pushByte(nextByte);
        return null; //not a line yet
    }


    public Frame decodeNextByteFrame(byte read) {
        String frameString = decodeNextByte(read);


        if(frameString != null && frameString!="null") {

            String[] frameArr = stringtoFrame(frameString);

            int index=0;
            if(frameArr[0].equals("")){
                index=1;}
            if(frameArr.length>1) {
                switch (frameArr[index]) {
                    case "CONNECT":
                        Connect curr = new Connect(frameArr[index + 1].split(":")[1], frameArr[index + 2].split(":")[1], frameArr[index + 3].split(":")[1], frameArr[index + 4].split(":")[1]);
                        return curr;
                    case "DISCONNECT":
                        return new Disconnect(Integer.parseInt(frameArr[index + 1].split(":")[1]));
                    case "SEND":
                        String msg = "";
                        for (int i = index + 2; i < frameArr.length; i++) {
                            msg = msg + frameArr[i];
                        }
                        return new Send(frameArr[index + 1].split(":")[1], msg);

                    case "SUBSCRIBE":
                        return new Subscribe(frameArr[index + 1].split(":")[1], Integer.parseInt(frameArr[index + 2].split(":")[1]), Integer.parseInt(frameArr[index + 3].split(":")[1]));


                    case "UNSUBSCRIBE":
                        return new Unsubscribe(Integer.parseInt(frameArr[index + 2].split(":")[1]), frameArr[index + 1].split(":")[1], Integer.parseInt(frameArr[index + 3].split(":")[1]));
                }
            }

        }

        return null; //not a line yet
    }




    private void pushByte(byte nextByte) {
        if (len >= bytes.length) {
            bytes = Arrays.copyOf(bytes, len * 2);
        }

        bytes[len++] = nextByte;
    }

    private String popString() {
        String result = new String(bytes, 0, len, StandardCharsets.UTF_8);
        len = 0;
        return result;
    }

    @Override
    public byte[] encode(String message) {
        return (message.toString() + "\n").getBytes(); //uses utf8 by default
    }


public String[] stringtoFrame(String frameString) {
    String[] parts = frameString.split("\n");
    return parts;
}

}



