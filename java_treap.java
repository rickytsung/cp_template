// cpp https://github.com/radoslav11/Implicit-treap/blob/master/implicit_treap.cpp
public class treapy {

}

class Treap{
    long val,lt=0,min=(1<<30);
    int pri,size=1,rev=0;
    Treap[] tr=new Treap[2];
    /*
    public static Treap Merge(Treap a,Treap b) {
        if(a==null)return b;
        if(b==null)return a;
        a.Move();
        b.Move();
        if(a.pri<b.pri) {
            a.tr[1]=Merge(a.tr[1],b);
            if(a!=null)a.Reset();
            return a;
        }
        else {
            b.tr[0]=Merge(a,b.tr[0]);
            if(b!=null)b.Reset();
            return b;
        }
    }

   //lf ~ R-1 and R ~ rt

    public static Treap[] Split(Treap a,int R) {
        if(a==null)return new Treap[] {null,null};
        a.Move();
        if(L<=((a.tr[0]==null)?0:a.tr[0].size)) {
            Treap[] left=Split(a.tr[0],L);
            a.tr[0]=left[1];
            if(a!=null)a.Reset();
            return new Treap[] {left[0],a};
        }
        else {
            Treap[] right=Split(a.tr[1],L-((a.tr[0]==null)?0:a.tr[0].size)-1);
            a.tr[1]=right[0];
            if(a!=null)a.Reset();
            return new Treap[] {a,right[1]};
        }
    }
    */
    Treap(long v){
        val=min=v;
        pri=(int)(Math.random()*1000000000);
    }

    void Reset() {
        if(this==null)return;
        size=1;
        min=val;
        if(tr[0]!=null) {
            min=Math.min(min,tr[0].min);
            size+=tr[0].size;
        }
        if(tr[1]!=null) {
            min=Math.min(min,tr[1].min);
            size+=tr[1].size;
        }
    }

    void Move() {
        if(this==null)return;
        if(lt!=0) {
            if(tr[0]!=null) {
                tr[0].lt+=lt;
                tr[0].min+=lt;
                tr[0].val+=lt;
            }
            if(tr[1]!=null) {
                tr[1].lt+=lt;
                tr[1].min+=lt;
                tr[1].val+=lt;
            }
            lt=0;
        }
        if(rev!=0) {
            rev=0;
            if(tr[0]!=null) {
                tr[0].rev^=1;
            }
            if(tr[1]!=null) {
                tr[1].rev^=1;
            }
            Treap temp=tr[0];
            tr[0]=tr[1];
            tr[1]=temp;
         }
    }
}
