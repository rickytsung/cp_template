
public class FastFourier {

}


class NTT{
	long mod;
	NTT(){
	}
	// 1 -1 , Ma = log2 of range
	void do_NTT(long[] in,int inv,final int G,final int P,final int Ma) {
		final int N=(1<<Ma);
		mod=P;
		long o;
		int u,y;
		long x,w,f;
		for(int i=0;i<N;i++) {
			u=0;
			for(int j=0;j<Ma;j++) {
				y=(1<<j);
				if((y&i)==y) {
					u|=(1<<(Ma-1-j));
				}
			}
			if(i<u) {
				o=in[i];//swap
				in[i]=in[u];
				in[u]=o;
			}
		}
		for(int k=1;k<N;k<<=1){
			w=fast(G,(long)(P-1)/(k<<1)*(P-1+inv));
			for(int j=0;j<N;j+=k<<1){
				x=1;
				for(int i=j;i<j+k;i++,x=x*w% P){
		            f=x*in[i+k]%P;
		            in[i+k]=(in[i]-f+P)%P;
		            in[i]=(in[i]+f)%P;
		        }
		    }
		}
		if(inv!=1) {
			final long iv=fast(N, mod-2);
			for(int i=0;i<N;i++) {
				in[i]*=iv;
				in[i]%=mod;
			}
		}
	}
	
	long fast(long x,long pw) {
		if(pw==1)return x;
		long h=fast(x,pw>>1);
		if((pw&1)==0) {
			return h*h%mod;
		}
		return h*h%mod*x%mod;
	}
}

/*
	public static Complex multiply(Complex a,Complex b) {
		return new Complex(a.r*b.r-a.i*b.i,a.i*b.r+a.r*b.i);
	}

	public static long round(double x) {
		long floor=(long)x;
		if(x-floor>0.5) {
			return floor+1;
		}
		return floor;
	}
*/

class FFT{
	Complex[] w;
	// 1 -1 , Ma = log2 of range
	FFT(){}
	void do_FFT(Complex[] in,int inv,final int Ma) {
		final int N=(1<<Ma);
		double d;
		final double e=(2*Math.PI/N)*inv;
		w=new Complex[N+5];
		for(int i=0;i<N;i++) {
			d=e*i;
			w[i]=new Complex(Math.cos(d),Math.sin(d));
		}
		Complex o=new Complex(0,0);
		int u,y;
		for(int i=0;i<N;i++) {
			u=0;
			for(int j=0;j<Ma;j++) {
				y=(1<<j);
				if((y&i)==y) {
					u|=(1<<(Ma-1-j));
				}
			}
			if(i<u) {
				o=in[i];//swap
				in[i]=in[u];
				in[u]=o;
			}
		}
		
		for(int i=1;i<N;i<<=1) {
			for(int j=0;j<N;j+=(i<<1)) {
				for(int k=j;k<i+j;k++) {
					o=multiply(in[i+k],w[(int)((long)(k-j)*N/i>>1)]);
					in[i+k].r=in[k].r-o.r;
					in[i+k].i=in[k].i-o.i;
					in[k].r=in[k].r+o.r;
					in[k].i=in[k].i+o.i;
				}
			}
		}
	}	
	
	Complex multiply(Complex a,Complex b) {
		return new Complex(a.r*b.r-a.i*b.i,a.i*b.r+a.r*b.i);
	}
}

class Complex{
	double r,i;
	Complex(double real,double imag){
		r=real;
		i=imag;
	}
}
