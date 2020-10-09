@echo off

set REELSETS=0 1 2 3
set REGEN=0
set RESPLIT=0

if "%RESPLIT%"=="1" split-spec.py all_spec.txt

for %%j in (%REGEN%) do spec2rep.py spec%%j.txt

for %%j in (%REGEN%) do reel-gen5.py %%j %%j-0 %%j-1 %%j-2 %%j-3 %%j-4

rm -rf reels.txt
for %%j in (%REELSETS%) do head -6 rset%%j.txt >> reels.txt

echo rm repertoir*.txt
rm -rf repertoir*.txt
