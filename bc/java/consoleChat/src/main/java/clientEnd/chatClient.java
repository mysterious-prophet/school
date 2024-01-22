package clientEnd;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 *
 * @author mpe94
 */
public class chatClient {
    private String hostname;
    private int port;
    private String nickName;
    
    public chatClient(String hostname, int port){ //pripojeni na server, localhost + port
        this.hostname = hostname;
        this.port = port;
    }
    
    public void run(){
        try{
            Socket socket = new Socket(hostname, port);
            System.out.println("<>: connected to chat room on port: " + port);
            
            new readThread(socket, this).start(); //zahajeni cteni a psani zprav
            new writeThread(socket, this).start();
        } catch (UnknownHostException ex){
            System.out.println("<>: server not found: " + ex.getMessage());
        } catch(IOException ex){
            System.out.println("<>: i/o error: " + ex.getMessage());
        }
    }
    
    void setNickName(String nickName){
        this.nickName = nickName;
    }
    
    String getNickName(){
        return this.nickName;
    }
    
    public static void main(String[] args){
        if(args.length < 2)
            return;
        
        String hostname = args[0];
        int port = Integer.parseInt(args[1]);
        
        chatClient client = new chatClient(hostname, port);
        client.run();
    }
}
