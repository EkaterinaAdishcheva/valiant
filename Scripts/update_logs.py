import os

suffix = ".log"
d = os.listdir()
for f in d:
	if f[-len(suffix):] == suffix:
		sfile = f.replace(".log", "-stat.csv")
		rfile = f.replace(".log", "-reels.csv")
		if not (sfile in d and rfile in d):
			os.system("py.exe log_reader.py " + f)
