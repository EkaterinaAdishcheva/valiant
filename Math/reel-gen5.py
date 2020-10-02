# permut blocks

import re
import random as rm
import sys

n = 10
forbid_symb = [ "2" ]
# do not forbid "1" if two digit symbols are present
forbid_len = 4

repertoir_files = ["repertoir" + suffix + ".txt" for suffix in sys.argv[2:]]
output_file = "reels" + sys.argv[1] + ".txt"
sys.stderr.write("using:\n" + "\n".join(repertoir_files) + "\n")
sys.stderr.write("output: " + output_file + "\n")

repertoirs = []
reellens = []
forbids = []
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
	if forbid_symb:
		cnt = sum( map( lambda x: 0 < sum( map( lambda y: x.startswith(y), forbid_symb)), repertoir))
		sys.stderr.write(f"reel #{reel}; len = {reellen}; forbid ({forbid_symb}) -> {cnt}\n")
	else:
		cnt = 0
		sys.stderr.write(f"reel #{reel}; len = {reellen}\n")
	forbids.append(cnt)

	reel += 1

for nn in range(n):
	for l in start_comment:
		o.write(f"{l}\n")
	idx1 = 0
	for ir in range(len(repertoirs)):
		if not forbids[ir]:
			res = repertoirs[ir].copy()
			rm.shuffle(res)
		else:
			rep_base   = list(filter(lambda x: 0 == sum( map( lambda y: x.startswith(y), forbid_symb)), repertoirs[ir]))
			rep_forbid = list(filter(lambda x: 0  < sum( map( lambda y: x.startswith(y), forbid_symb)), repertoirs[ir]))
			rm.shuffle(rep_base)
			rm.shuffle(rep_forbid)
			
			forbid_act = forbid_len
			while (len(rep_base) - forbids[ir] * forbid_act) < 0:
				forbid_act -= 1
			if forbid_act != forbid_len:
				sys.stderr.write(f"Warning: forbid len reduced to {forbid_act}\n")

			forbid_pos = (
				['f'] * forbids[ir] +
				['base'] * (len(rep_base) - forbids[ir] * forbid_act)
			)
			rm.shuffle(forbid_pos)
			res = []
			for x in forbid_pos:
				if x == 'f':
					res.append(rep_forbid.pop())
					for _ in range(forbid_act):
						res.append(rep_base.pop())
				else: # 'base'
					res.append(rep_base.pop())
		str1 = "\t".join(res)
		o.write(f"{reellens[idx1]} {str1}\n")
		idx1 += 1
	o.write("\n")
