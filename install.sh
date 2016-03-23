#!/bin/bash

OUT=$1
mkdir -p $OUT

cd $OUT
ln -s $OLDPWD/index.html
ln -s $OLDPWD/assets
ln -s $OLDPWD/phaser
ln -s $OLDPWD/c
