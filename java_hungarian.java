//匈牙利演算法             init vis[i], mat[i]=-1
//usage Hungarian(i,i)

public static int Hungarian(int x,int y){
	if(vis[x]==y)return 0;
    vis[x]=y;
	for(int i:e.get(x)){
		if((mat[i]==-1)||(Hungarian(mat[i],y)==1)){
			mat[i]=x;
			return 1;
		}
	}
	return 0;
}
