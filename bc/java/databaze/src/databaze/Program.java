
package databaze;

import java.sql.DriverManager;
import java.sql.*;


public class Program {

    static String ovladac = "org.apache.derby.jdbc.ClientDriver";
    static String pripojovaciRetezec = "jdbc:derby://localhost:1527/kniha";
    static String dotaz = "SELECT * FROM ZAZNAM";
    static String vlozeni = "INSERT INTO ZAZNAM VALUES (4, 'Jmeno Prijmeni', 'Titul', 'Cena')";
    static String agregace = "select sum(CENA) from zaznam";
    static String vlozeni2 = "INSERT INTO ZAZNAM VALUES (?, ?, ?, ?)";
    
   static void priprava() throws ClassNotFoundException{
        Class.forName(ovladac);
    }
   
   static void vypis()
   {
       try(Connection pripojeni = DriverManager.getConnection(pripojovaciRetezec, "uzivatel", "heslo");
               Statement prikaz = pripojeni.createStatement();
           ResultSet vysledek = prikaz.executeQuery(dotaz);)
       {
           while(vysledek.next())
           {
               System.out.println(vysledek.getString("Autor")+ ": " + vysledek.getString(3) + " (" + vysledek.getInt(4) + ")");
           }
           
       }

       catch(Exception e)
       {
           System.out.println(e.getMessage());
       }
   }
   
   
   public static void vlozeniDat() throws SQLException{
       try(Connection pripojeni = DriverManager.getConnection(pripojovaciRetezec, "uzivatel", "heslo");
               Statement prikaz = pripojeni.createStatement();
               //sem nepatri int n = ...
                )
       {
           int n = prikaz.executeUpdate(vlozeni);
           System.out.println(n);
           
       }
       catch(Exception e)
       {
           System.out.println(e.getMessage());
       }
       
   }
   
   public static int uhrnaCena()
   {
       try(Connection pripojeni = DriverManager.getConnection(pripojovaciRetezec, "uzivatel", "heslo");
               Statement prikaz = pripojeni.createStatement();
           ResultSet vysledek = prikaz.executeQuery(agregace);)
       {
           if(vysledek.next()){
               return vysledek.getInt(1);
           }
           else
               return 0;
       }
       catch(Exception e)
       {
           System.out.println(e.getMessage());
       }
       return -1;    
       
   }
   
   
   public static void vlozeniDat2()
   {
       try(Connection pripojeni = DriverManager.getConnection(pripojovaciRetezec, "uzivatel", "heslo");
               PreparedStatement prikaz = pripojeni.prepareStatement(vlozeni2))
       {
           int cena = 100; 
           prikaz.setInt(1, 5);
           prikaz.setString(2, "Jmeno Prijmeni");
           prikaz.setString(3, "Titul");
           prikaz.setInt(4, cena);
           prikaz.executeUpdate();
       }
       catch(Exception e)
       {
           System.out.println(e.getMessage());
       }
       
   }
   
   
   //
   
    
    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        
        priprava();
        vypis();
        vlozeniDat();
        vypis();
        System.out.println(uhrnaCena());
        vlozeniDat2();
        vypis();
        System.out.println(uhrnaCena());
        
    }
    
}
