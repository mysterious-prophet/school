package serverEnd;

/**
 *
 * @author mpe94
 */

//import java.io.*;
import java.io.IOException;
import java.net.*; //sockety
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.*; //sets atd.

public class chatServer {
    private int port; //port na kterem bezi server
    private Set<String> nickNames = new HashSet<>(); //mnozina uziv. jmen, aby se neopakovala
    private Set<userThread> userThreads = new HashSet<>(); //mnozina threadu uzivatelu
    private DateTimeFormatter timeFormat = DateTimeFormatter.ofPattern("HH:mm:ss"); //format hodin pro server
    private String timestamp; //casove udaje pro server
    
    public chatServer(int port){ //nastav port
        this.port = port;
    }
    
    public void run() { //vytvor server na portu
        try (ServerSocket serverSocket = new ServerSocket(port)){ //vytvor server socket
            timestamp = getTime().format(timeFormat); //info
            System.out.println(timestamp + " <>: chat room created on port: " + port);
            
            while(true){ //user thread a user socket
                Socket socket = serverSocket.accept();
                userThread newUser = new userThread(socket, this);
                userThreads.add(newUser);                
                newUser.start();
            }
        } catch (IOException ex) {
            timestamp = getTime().format(timeFormat);
            System.out.println(timestamp + " <>: server error: " + ex.getMessage());
        }
    }
    
    public static void main(String[] args){
        if(args.length < 1){
            System.out.println("<>: syntax: 'java serverEnd.chatServer <port_number>'");
            System.exit(0);
        }
        
        int port = Integer.parseInt(args[0]);
        
        chatServer server = new chatServer(port);
        server.run();
    }
    
    void sendMessage(String message, userThread excludeUser){ //vysilani zpravy v threadu
        for(userThread iUser : userThreads){
            if(iUser != excludeUser){
                iUser.sendMessage(message);
            }
        }
    }
    
    void addNickName(String nickName){
        nickNames.add(nickName);
    }
    
    void removeUser(String nickName, userThread iUser){
        boolean removed = nickNames.remove(nickName);
        if(removed){
            userThreads.remove(iUser);
            timestamp = getTime().format(timeFormat);
            System.out.println(timestamp + " <>: user [" + nickName + "] has left");
            System.out.print(timestamp + " <>: there are currently " + this.getNickNames().size() + " users: ");
            System.out.println(this.getNickNames());
        }
    }
    
    Set<String> getNickNames(){
        return this.nickNames;
    }
    
    boolean hasUsers(){
        return !this.nickNames.isEmpty();
    }
    
    void printEnterInfo(String nickName){
        timestamp = getTime().format(timeFormat);
        System.out.println(timestamp + " <>: new user has entered the room: [" + nickName + "]"); 
        System.out.print(timestamp + " <>: there are currently " + this.getNickNames().size() + " users: ");
        System.out.println(this.getNickNames());
    }
    
    public LocalTime getTime(){
        return LocalTime.now();
    }
}
