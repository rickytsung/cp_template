
public class transform {

}

/*
inv 1=SOS(or transform) -1=Mobius(inverse or)
swap in[mouse]+=(in[i^mouse]*inv); => AndTransform
code:

public static void SOS(long[] in,final int sz,final int inv) {
		final int N=(1<<sz);
		for(int i=1;i<N;i<<=1) {
			for(int mouse=0;mouse<N;mouse++) {
				if((i&mouse)!=0) {
					in[mouse]+=(in[i^mouse]*inv);
				}
			}
		}
	}
 */

class Convolution{
	Convolution(){}
	/*
	 * Compute C[i]=A[x]*B[y] for all x|y = i :
	 * A'=OrTrans(A)
	 * B'=OrTrans(B)
	 * C'=A'*B'
	 * C=OrInvTrans(C')
	 */
	void OrTransform(long[] in,final int sz,final int inv) {
		final int N=(1<<sz);
		for(int i=1;i<N;i<<=1) {
			for(int mouse=0;mouse<N;mouse++) {
				if((i&mouse)!=0) {
					in[mouse]+=(in[i^mouse]*inv);
				}
			}
		}
	}
	
	void OrTransform(long[] in,final int sz,final int inv,final long mod) {
		final int N=(1<<sz);
		for(int i=1;i<N;i<<=1) {
			for(int mouse=0;mouse<N;mouse++) {
				if((i&mouse)!=0) {
					in[mouse]+=(in[i^mouse]*inv)+mod;
					in[mouse]%=mod;
				}
			}
		}
	}
	
	void AndTransform(long[] in,final int sz,final int inv) {
		final int N=(1<<sz);
		for(int i=1;i<N;i<<=1) {
			for(int mouse=0;mouse<N;mouse++) {
				if((i&mouse)!=0) {
					in[i^mouse]+=(in[mouse]*inv);
				}
			}
		}
	}
	
	void AndTransform(long[] in,final int sz,final int inv,final long mod) {
		final int N=(1<<sz);
		for(int i=1;i<N;i<<=1) {
			for(int mouse=0;mouse<N;mouse++) {
				if((i&mouse)!=0) {
					in[i^mouse]+=(in[mouse]*inv)+mod;
					in[i^mouse]%=mod;
				}
			}
		}
	}
	
	void XorTransform(long[] in,final int sz,final int inv) {
		long x;
		final int N=(1<<sz);
		for(int i=1;i<N;i<<=1) {
			for(int mouse=0;mouse<N;mouse++) {
				if((i&mouse)!=0) {
					x=in[mouse];
					in[mouse]=in[i^mouse];
					in[i^mouse]+=x;
					in[mouse]-=x;
				}
			}
		}
		if(inv==-1) {
			for(int i=0;i<N;i++) {
				in[i]/=N;
			}
		}
	}
	
	void XorTransform(long[] in,final int sz,final int inv,final long mod) {
		long x;
		final int N=(1<<sz);
		for(int i=1;i<N;i<<=1) {
			for(int mouse=0;mouse<N;mouse++) {
				if((i&mouse)!=0) {
					x=in[mouse];
					in[mouse]=in[i^mouse];
					in[i^mouse]+=x+mod;
					in[mouse]-=x-mod;
					in[i^mouse]%=mod;
					in[mouse]%=mod;
				}
			}
		}
		if(inv==-1) {
			final long iv=fast(N,mod-2,mod);
			for(int i=0;i<N;i++) {
				in[i]*=iv;
				in[i]%=mod;
			}
		}
    }
	
	//A + B => C
    void SubSetSum(long[] A,long[] B,long C[],int sz,long mod) {
    	final int max=sz;
		final int maxn=(1<<max);
		long[][] f=new long[max+1][maxn];
		long[][] g=new long[max+1][maxn];
		long[][] h=new long[max+1][maxn];
		int[] bitcount=new int[maxn];
		int cnt;
    	for(int i=0;i<maxn;i++) {
			cnt=0;
			for(int j=1;j<maxn;j<<=1) {
				if((i&j)!=0) {
					cnt++;
				}
			}
			bitcount[i]=cnt;
		}
		for(int i=0;i<maxn;i++) {
			f[bitcount[i]][i]=A[i];
			g[bitcount[i]][i]=B[i];
		}
		for(int i=0;i<=max;i++) {
			OrTransform(f[i],max,1,mod);
			OrTransform(g[i],max,1,mod);
		}
		
		for(int j=0;j<=max;j++) {
			for(int k=0;k<=j;k++) {
				for(int i=0;i<maxn;i++) {
					h[j][i]+=(f[k][i]*g[j-k][i])%mod+mod;
					h[j][i]%=mod;
				}
			}
		}
		
		for(int i=0;i<=max;i++) {
			OrTransform(h[i],max,-1,mod);
		}
		for(int i=0;i<maxn;i++) {
			C[i]=h[bitcount[i]][i];
		}
    }
    
    long fast(long x,long pw,long mod) {
		if(pw<=0)return 1;
		if(pw==1)return x;
		long h=fast(x,pw>>1,mod);
		if((pw&1)==0) {
			return h*h%mod;
		}
		return h*h%mod*x%mod;
	}
}


