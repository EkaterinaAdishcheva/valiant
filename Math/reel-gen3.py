# permut blocks

import re
import random as rm
import sys

n = 10
forbid_symb = "11"
forbid_len = 4

repertoir_files = ["repertoir" + suffix + ".txt" for suffix in sys.argv[2:]]
output_file = "reels" + sys.argv[1] + ".txt"
sys.stderr.write("using:\n" + "\n".join(repertoir_files) + "\n")
sys.stderr.write("output: " + output_file + "\n")

repertoirs = []
reellens = []
o = open(output_file, "w+", encoding="utf-8")

reel = 1

start_comment = []
for repertoir_file in repertoir_files:
	f = open(repertoir_file, "r", encoding = "utf-8-sig")
	repertoir  = []
	reellen    = 0
	in_start = 1
	for line in f.read().splitlines():
		if in_start:
			if re.search(r"^\s*(#|;|\/\/)", line) and not line in start_comment:
				start_comment.append(line)
				continue
		line = re.sub(r"(#|;|\/\/).*", "", line)
		line = re.sub(r"^\s+", "", line)
		line = re.sub(r"\s+$", "", line)
		line = re.sub(r"\s+", " ", line)
		
		if line == '':
			continue

		in_start = 0
		count = 1
		m = re.match("^x(\d+)\s+(.*)", line)
		if m:
			count = int(m.group(1))
			line  = m.group(2)
		if count != 0:
			for j in range(count):
				repertoir.append(line)
			reellen += (line.count(" ") + 1) * count
	repertoirs.append(repertoir)
	reellens.append(reellen)
	if forbid_symb != '':
		sys.stderr.write("reel #" + str(reel) + " len = " + str(reellen) + " " + forbid_symb + " -> " + str(repertoir.count(forbid_symb)) + "\n")
	else:
		sys.stderr.write("reel #" + str(reel) + " len = " + str(reellen) + "\n")
	reel += 1

for nn in range(n):
	for l in start_comment:
		o.write(l + "\n")
	idx1 = 0
	for r in repertoirs:
		if forbid_symb == "" or r.count(forbid_symb) == 0:
			rm.shuffle(r)
			res = r
		else:
			cnt_forbid = r.count(forbid_symb)
			tmp_r = list(filter(lambda x: x!=forbid_symb, r))

			forbid_pos = (
				[1] * cnt_forbid +
				[0] * (len(r) - cnt_forbid * (forbid_len + 1))
			)
			rm.shuffle(forbid_pos)
			res = []
			for x in forbid_pos:
				l = 1
				if x == 1:
					res.append(forbid_symb)
					l = forbid_len
				pos = rm.sample(range(len(tmp_r)), l)
				pos.sort(reverse = True)
				for p in pos:
					res.append( tmp_r.pop(p) )
		o.write("" + str(reellens[idx1]) + ":\t" + "\t".join(res) + "\n")
		idx1 += 1
	o.write("\n")
