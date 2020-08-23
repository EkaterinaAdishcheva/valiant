#
# Log reader for SlotsSumilator
# Version 1.1
#

import sys
import re

if len(sys.argv) > 1:
    inf = open(sys.argv[1], "r")
    if sys.argv[1][-4:] == ".log":
    	sfile = sys.argv[1].replace(".log", "-stat.csv")
    	rfile = sys.argv[1].replace(".log", "-reels.csv")
    else:
    	sfile = sys.argv[1] + ".csv"
    	rfile = sys.argv[1] + "-reels.txt"
    sys.stderr.write( f"Reading {sys.argv[1]}\n" )
    sys.stderr.write( f"Reels to {rfile}\n" )
    sys.stderr.write( f"Tabular to {sfile}\n" )
    sfile = open(sfile, "w")
    rfile = open(rfile, "w")
else:
    inf = sys.stdin
    sfile = sys.stdout
    rfile = sys.stdout
reellen = 500
    
# skip summary
while 1:
	line = inf.readline()
	if line == "":
		sys.stderr.write( "No reels marker\n" )
		exit(1)
	if line.find("<REELS>") >= 0:
		break

# Print reels
reels = []
cur_set = 0
while 1:
	line = inf.readline()
	if line.find("</REELS>") >= 0:
		break
	if line != "\n" and line[0] != "#":
		line = line[:-1]
		reel = line[line.find("-") + 1:].split()
		cur_set.append( reel )
	if line[0] == "#":
		if cur_set:
			reels.append(cur_set)
		cur_set = []
if cur_set:
	reels.append(cur_set)

max_len = max([max([len(x) for x in r]) for r in reels])
max_len = max(reellen, max_len)
for j in range(max_len):
	for k in range(len(reels)):
		set1 = reels[k]
		rfile.write(str(j + 1));
		for r in set1:
			if j < len(r):
				rfile.write("\t" + r[j])
			else:
				rfile.write("\t")
		rfile.write("\t\t" if k != len(reels) - 1 else "")
	rfile.write("\n");

while 1:
	line = inf.readline()
	if line == "":
		sys.stderr.write( "No tabular marker\n" )
		exit(1)
	if line.find("<TABULAR>") >= 0:
		break
# Print tables
mode = 0
#  0 - none
#  1 - data
tables = []
for line in inf.readlines():
	if line == "\n":
		if mode != 0:
			tables.append( table )
		mode = 0
		continue
	if mode == 0:
		table = { "content" : [ line[:-1] ], "height" : 1 }
		mode = 1
		continue
	table["content"].append(line[:-1])
	table["width"] = line.count("\t") + 1
	table["height"] += 1
if mode != 0:
	tables.append( table )

max_height = max( [rec["height"] for rec in tables] )

print( "max_height", max_height )
for table in tables:
	print( table["content"][0], ":", table["height"], "x", table["width"] )

for j in range(max_height):
	line = []
	for table in tables:
		if j < table["height"]:
			line.append( table["content"][j]
				+ "\t" * (table["width"] - 1
					- table["content"][j].count("\t")))
		else:
			line.append( "\t" * (table["width"] - 1))
	sfile.write( "\t\t".join( line ) + "\n" )

