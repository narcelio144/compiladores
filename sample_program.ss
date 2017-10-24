type meuArray = array [10] of integer
type arrayChar = array [10] of char
type customInt = integer

type minhaStruct = struct {
	x,y : integer;
	z : arrayChar
}

function declaracaoFuncao(n : integer) : integer{
	var a,b : integer;
	var c,d,e,f,g : boolean;
	var h : char;
	var s : strinh;
	a = 1;
	b = 2;
	d = true;
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
	p = declaracaoFuncao2(e);
	return p*3;
}

function declaracaoFuncao2(c : char) : integer{
	var k,i : 	integer;
	if (c == 'a'){
		var a : integer;
		a = 2;
		k = --k*a++;
	}
	do{
		var x : integer;
		x = k/2;
		k = k*x;
	} while (k >= 6 && k <= 323);
	return k*3+i;
}
