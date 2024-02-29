import java.util.*;
public class MainFun {
	public static void main(String[] args) {
		//this is for some paste code
	}
}

class SCC{
	Stack<Integer> st=new Stack<>();
	ArrayList<ArrayList<Integer>> e;
	final int Maxn = 0; //rememeber this
	boolean[] ins=new boolean[Maxn];
	int[] dfs=new int[Maxn];
	int[] low=new int[Maxn];
	int[] scc=new int[Maxn];
	int o,t=0,no=1;
	SCC(ArrayList<ArrayList<Integer>> g,int s,int t){
		e=g;
		for(int i=s;i<=t;i++) {
			if(dfs[i]!=0) {
				tarjan(i);
			}
		}
	}
	void tarjan(int x) {
        dfs[x]=low[x]=++t;
        ins[x]=true;
        st.push(x);
        for(int i:e.get(x)) {
            if(dfs[i]==0) {
                tarjan(i);
                low[x]=Math.min(low[x],low[i]);
            }
            else if(ins[i]) {
                low[x]=Math.min(low[x],dfs[i]);
            }
        }
        if(!ins[x])return;
        if(dfs[x]==low[x]) {
            while(true) {
                o=st.pop();
                ins[o]=false;
                scc[o]=no;
                if(o==x)break;
            }
            no++;    
        }
        ins[x]=false;
    }
}

