#!/bin/bash

outdir=ep2-Thiago-Wilson

if [ ! -d $outdir ]; then
  mkdir $outdir
fi

contents="src/ CMakeLists.txt LEIAME models/*.obj models/*.mtl textures/*.png textures/*.jpg ime.*"
cp -r $contents $outdir

tar -caf $outdir.tgz $outdir

rm -rf $outdir

