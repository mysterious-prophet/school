/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package druhy;

/**
 *
 * @author pokorm20
 */
public class prvek {

    public int getData() {
        return data;
    }

    public void setData(int data) {
        this.data = data;
    }

    public prvek getDalsi() {
        return dalsi;
    }

    public void setDalsi(prvek dalsi) {
        this.dalsi = dalsi;
    }
    int data;
    private prvek dalsi;
    public prvek(int data, prvek dalsi)
    {
        this.data = data;
        this.dalsi = dalsi;
    }
    
}
