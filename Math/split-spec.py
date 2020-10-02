#
# Split spec
#

import sys
import re

if len(sys.argv) > 1:
    inf = open(sys.argv[1], "r")
else:
    inf = sys.stdin

# Print spec lines
lines = []
num_files = 0
first = 1
while 1:
	line = inf.readline()
	if line == "":
		break
	if line == "\n":
		break
	line = line[:-1]
	idx = 0
	for ll in line.split("\t\t"):
		if first:
			lines.append( [] )
			num_files += 1
		lines[idx].append( ll )
		idx += 1
	first = 0

for j in range(num_files):
	outf = f"spec{j}.txt"
	sys.stderr.write( f"Creating {outf}\n" )
	out = open(outf, "w")
	for line in lines[j]:
		out.write(line + "\n")
