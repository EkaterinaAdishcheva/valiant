@echo off
rm -v reels?.txt

spec2rep.py spec0.txt
rem spec2rep.py spec1.txt
rem spec2rep.py spec2.txt
rem spec2rep.py spec3.txt

reel-gen3.py 0 0-0 0-1 0-2 0-3 0-4
reel-gen3.py 1 1-0 1-1 1-2 1-3 1-4
reel-gen3.py 2 2-0 2-1 2-2 2-3 2-4
reel-gen3.py 3 3-0 3-1 3-2 3-3 3-4

rm -rf reels.txt
for %%j in (reels?.txt) do head -6 %%j >> reels.txt

