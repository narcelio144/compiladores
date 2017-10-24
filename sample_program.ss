function fib(n:integer) : integer{
	if (n < 2)
		return n;
	else
		return fib(n-1)+fib(n-2);
}

function fibFat(n:integer) : integer{
	var i,f : integer;
	i = 0;
	f = 1;
	while (i <= n){
		f=f*fib(i);
		i=i+1;
	}
	return f;
}
