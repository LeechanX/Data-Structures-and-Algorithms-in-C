#define LIMIT 100000

static int flag[LIMIT+1]={1,1};

void create_flag(void){
	int i,j;
	for(i=2;i<=LIMIT/2;i++){
		if(!flag[i])
			for(j=i*2;j<LIMIT;j+=i)
				flag[j]=1;
	}
}

int isPrim(unsigned n){
	return !flag[n];
}