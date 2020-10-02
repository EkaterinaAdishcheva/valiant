@echo off

set REELSETS=0 1 2 3

split-spec.py all_spec.txt

for %%j in (%REELSETS%) do spec2rep.py spec%%j.txt

for %%j in (%REELSETS%) do reel-gen5.py %%j %%j-0 %%j-1 %%j-2 %%j-3 %%j-4

del /q reels.txt
for %%j in (%REELSETS%) do head -6 rset%%j.txt >> reels.txt

echo rm repertoir*.txt
del /q repertoir*.txt
