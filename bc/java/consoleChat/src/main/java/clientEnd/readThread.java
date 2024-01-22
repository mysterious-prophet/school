package clientEnd;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.Socket;

/**
 *
 * @author mpe94
 */
public class readThread extends Thread{
    private BufferedReader reader;
    private Socket socket;
    private chatClient client;
    
    public readThread(Socket socket, chatClient client){
        this.socket = socket;
        this.client = client;
        
        try{
            InputStream input = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(input));
        } catch (IOException ex){
            System.out.println("<>: input stream error: " + ex.getMessage());
        }
    }
    
    @Override
    public void run(){ //zavolano pomoci .start()
        while(true){
            try{
                String response = reader.readLine(); //precteni odpovedi 
                System.out.println("\r" + response); //"\r" aby nebyla moje prazdna odpoved - premaze se, kdyz jsem ja nic nenapsal
                
                if(client.getNickName() != null){ //vypsani meho formulare pro odpoved
                    System.out.print("*[" + client.getNickName() + "]: ");
                }
            } catch (IOException ex){ //odpojeni
                System.out.println("<>: session ended");
                this.interrupt();
                //System.out.println("<>: server reading error: " + ex.getMessage());
                //ex.printStackTrace();
                break;
            }
        }
    }   
}
