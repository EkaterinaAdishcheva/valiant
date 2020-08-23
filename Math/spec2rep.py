from sys import stderr
from sys import argv

if len(argv) > 1:
	filename = argv[1]
else:
	filename = "spec.txt"

f = open(filename, "r", encoding = "utf-8-sig")
prefix = []
matr = []

for line in f.read().splitlines():
	if line == "":
		continue
	if line[0] == "#":
		prefix.append(line)
	else:
		larr = line.split("\t")
		matr.append(larr)

for j in range(len(matr[0])):
	if filename == "spec.txt":
		repfile = filename.replace("spec", "repertoir" + str(j))
	else:
		repfile = ( filename
			.replace("spec", "repertoir")
			.replace(".txt", "-" + str(j) + ".txt"))
	stderr.write("Creating " + repfile + "\n")
	o = open(repfile, "w+", encoding="utf-8")
	for line in prefix:
		o.write(line + "\n")
	for idx in range(len(matr)):
		o.write( matr[idx][j] + "\n" )
	o.close()


stderr.write("\n")
