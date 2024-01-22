package clientEnd;

import java.io.Console;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

/**
 *
 * @author mpe94
 */
public class writeThread extends Thread  {
    private PrintWriter writer;
    private Socket socket;
    private chatClient client;
    
    public writeThread(Socket socket, chatClient client){
        this.socket = socket;
        this.client = client;
        
        try{
            OutputStream output = socket.getOutputStream();
            writer = new PrintWriter(output, true);
        } catch (IOException ex){
            System.out.println("<>: output stream error: " + ex.getMessage());
        }
    }
    
    @Override
    public void run(){
        Console console = System.console();
        
        String nickName = console.readLine("\n<>: enter a nickname: ");
        client.setNickName(nickName);
        writer.println(nickName);
        
        String message;       
        do{
            message = console.readLine("*[" + nickName + "]: ");
            writer.println(message);
        } while(!message.equals("bye"));
        
        try{
            socket.close();            
        } catch(IOException ex){
            System.out.println("<>: server writing error: " + ex.getMessage());
        }
    }
}
