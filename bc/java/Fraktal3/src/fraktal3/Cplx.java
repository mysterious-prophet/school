/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fraktal3;

/**
 *
 * @author pokorm20
 */
public class Cplx {
    double re, im;
    public Cplx(double re, double im)
    {
        this.re = re;
        this.im = im;
    }
    
    public Cplx(double re)
    {
        this(re, 0);
    }
    
    public Cplx plus(Cplx a, Cplx b)
    {
        return new Cplx(a.re+b.re, a.im+b.im);
    }
    
}
