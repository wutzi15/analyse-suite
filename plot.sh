#!/bin/sh

#  plot.sh
#  Analyse Suite
#
#  Created by Wutzi on 14.03.11.
#  Copyright 2011 me. All rights reserved.
#cd $1
for file in *  ; do
/sw3/bin/gnuplot <<EOF
set term png
set output "$file.png"
set xrange [840:848]
set yrange [-70:-10]
set ylabel "dB"
set xlabel "Wavelength in nm"
plot "$file" using 1:2 with lines
EOF
done

mkdir plots
for pl in *.png; do
mv $pl plots/$pl
done

cd plots

rm *_dist*
rm *peak*
rm *only*
rm *ana*
