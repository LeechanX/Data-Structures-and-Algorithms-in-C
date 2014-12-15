int isPalindrome(unsigned n){
	unsigned leftdiv=10;
	int np=1;
	if(n<leftdiv)
		return 1;
	while(n>leftdiv){
		leftdiv*=10;
		np++;
	}
	leftdiv/=10;
	//now np是位数
	np/=2;
	int i=0;
	unsigned left,right,leftnumb=n,rightnumb=n;
	while(i<np){
		left=leftnumb/leftdiv;
		right=rightnumb%10;
		if(left!=right)
			break;
		leftnumb=leftnumb%leftdiv;
		leftdiv/=10;
		rightnumb/=10;
		i++;
	}
	if(i<np)
		return 0;
	return 1;
}