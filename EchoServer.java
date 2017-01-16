
import java.net.*;
import java.io.*;
import java.nio.*;

public class EchoServer {
    public static void main(String[] args) throws IOException {


        int portNumber = 12345;
        byte[] bytes={1,2,3,4,5};

        try (
                ServerSocket serverSocket =
                new ServerSocket(portNumber);
                Socket clientSocket = serverSocket.accept();     
                PrintWriter out =
                new PrintWriter(clientSocket.getOutputStream(), true);                   
                DataInputStream in = 
                new DataInputStream(clientSocket.getInputStream());
            ) {

            while (true) {

                //in.read(test);
                //float f = ByteBuffer.wrap(test).order(ByteOrder.BIG_ENDIAN).getFloat();   //a good way if we are not sure about the endian of the data
                //this works as client sends data in network byte order 
                //which is big endian happens to be 
                //the byte order used by java
                /*
                for(int i=0;i<1540;i++){
                    byte v = in.readByte();
                    System.out.printf("%d ",v);
                }
                System.out.println("");
                */

                int num = in.readInt(); 
                System.out.println("point num is "+num);
                for(int i=0;i<2;i++){
                    float val = in.readFloat();
                    in.read(bytes);
                    ByteBuffer bb = ByteBuffer.wrap(bytes);

                    short OV = 
                        (short)(bb.get() & 
                        (short)0xff);
                    short BL = 
                        (short)(bb.get() & 
                        (short)0xff);
                    short SB = 
                        (short)(bb.get() &
                        (short)0xff);
                    short NT =
                        (short)(bb.get() & 
                        (short)0xff);
                    short IV =
                        (short)(bb.get() & 
                        (short)0xff);
                    System.out.println(
                                        "val is " + val+
                                        " OV is "+OV+
                                        " BL is "+BL+
                                        " SB is "+SB+
                                        " NT is "+NT+
                                        " IV is "+IV);
                }
                in.skipBytes(1540 - num * 12 ); 
                //skip left bytes for this device
            }
        } catch (IOException e) {
            System.out.println("Exception caught when trying to listen on port "
                    + portNumber + " or listening for a connection");
            System.out.println(e.getMessage());
        }
    }
}


