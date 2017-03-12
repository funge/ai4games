#!/bin/sh

n=`wc -l < copyrightNotice.txt`

for i in `ls *.{h,cpp}`; do
   sed -i \"1,$n d\" $i
   # sed appends files, but we want to insert
   # so we have to first add a blank line, append, then delete the blank line
   sed -i \"1 i \\ \" $i
   sed -i \"1 r copyrightNotice.txt\" $i
   sed -i \"1 d\" $i
done
