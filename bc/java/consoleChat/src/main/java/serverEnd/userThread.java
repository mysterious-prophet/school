package serverEnd;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

/**
 *
 * @author mpe94
 */
public class userThread extends Thread{
    private Socket socket;
    private chatServer server;
    private PrintWriter writer;
    
    public userThread(Socket socket, chatServer server){
        this.socket = socket;
        this.server = server;
    }
    
    @Override
    public void run(){
        try{
            InputStream input = socket.getInputStream(); //prichozi info
            BufferedReader reader = new BufferedReader(new InputStreamReader(input)); //precte znaky
            
            OutputStream output = socket.getOutputStream(); //odchozi zprava
            writer = new PrintWriter(output, true); //vypisovac
            
            printUsers(); //vypise novemu uzivateli seznam uzivatelu
            
            String nickName = reader.readLine(); //ulozeni uz. jmena
            server.addNickName(nickName);
            server.printEnterInfo(nickName);
            
            String serverMessage  = "<>: new user has entered: [" + nickName + "]"; //info na serveru
            server.sendMessage(serverMessage, this);
            
            String clientMessage; //uzivatelske zpravy
            
            do{
                clientMessage = reader.readLine();
                serverMessage = "[" + nickName + "]: " + clientMessage;
                server.sendMessage(serverMessage, this); //neodesilam zpravu sam sobe
            }while(!clientMessage.equals("bye")); //ukoncovaci podminka
            
            server.removeUser(nickName, this); //odebrani uzivatele
            socket.close();
            
            serverMessage = "<>: [" + nickName + "] has left";
            server.sendMessage(serverMessage, this);
        } catch (IOException ex){
            System.out.println("<>: error in userThread: " + ex.getMessage());
        }
    }
    
    void printUsers(){ //vypise pripojene uzivatele
        if(server.hasUsers()){
            writer.println("<>: connected users: " + server.getNickNames());
        } else {
            writer.println("<>: no other users!");
        }
    }
    
    void sendMessage(String message){ //vypise zpravu
        writer.println(message);
    }
    
}
