#Script for generating C++ code for the auxiliary table, containing each rule size and left element

with open("rule_length_out","w") as out:
	with open("ss_grammar","r") as grammar:
		for line in grammar:
			left = line.split()[0]
			right = line.split('->')[1].split()
			e = "''"
			while e in right:
				right.remove(e)
			out.write("vec_rules.push_back(make_pair("+left+",")
			out.write(str(len(right))+"));\n")
