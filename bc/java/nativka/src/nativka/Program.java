
package nativka;


public class Program {

    public native void pozdrav(String text);
    static
    {
        System.loadLibrary("Dll1");
    }
    public static void main(String[] args) {
       Program prog = new Program();
    }
    
}
