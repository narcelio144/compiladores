with open("rule_length_out","w") as out:
	with open("ss_grammar","r") as grammar:
		for line in grammar:
			out.write("vec_rules.push_back(make_pair("+line.split()[0]+","+str(len(line.split('->')[1].split()))+"));\n")
