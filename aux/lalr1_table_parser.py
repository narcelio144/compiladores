with open("table_out","w") as out:
	out.write("//Table generated by http://jsmachines.sourceforge.net/machines/lalr1.html")
	with open("table.csv","r") as table:
		header = table.readline().split(',')
		for i,line in enumerate(table):
			out.write("\n//State: "+str(i)+"\n")
			for j,word in enumerate(line.split(',')):
				if j == 0:
					continue
				word = word.replace(u'\xa0', u' ')
				if (word.isspace()):
					continue
				else:
					s = list(word)
					if s[0] == 's':
						s[0] = ''
					if s[0] == 'r':
						s[0] = '-'
					s = "".join(s)
					out.write("actionTable["+str(i)+"]["+header[j]+"] = "+s+";\n")
