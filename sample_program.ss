type meuArray = array [10] of integer
type arrayChar = array [10] of char
type customInt = integer

function declaracaoFuncao2(c : char) : integer{
	var k,i : 	integer;
	var a,j : boolean;

	k=1;
	
	a = 2;
	j=true;
	k = --k*a++;

	if( a == j){
		var i : integer;
	}

	

	do{
		var x : integer;
		x = k/2;
		k = k*x;
	} while (k >= 6 && k <= 323);
	return k*3+i;

}

function declaracaoFuncao(n : integer) : integer{
	var a,b,redecl,x : integer;
	var redecl : char;
	var c,d,e,f,g : boolean;
	var h : char;
	var s : string;
	a = 1;
	b = 2;
	d = true;
	naodecl = "batata";
	{
		var x : integer;
		x = b + 2;
		{
			var y,z : integer;
			y = x - 1;
			z = x + 1;
		}
	}
	e = false;
	a = ((b + 2)*3-1)/2;
	c = !(d && e) || f;
	s = "batata";

	if (c){
		var x,y,z : boolean;
		x = y || z;
	}
	if(n == 0)
		return 1;
	x = declaracaoFuncao2(e);
	return x*3;
}
