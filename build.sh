#!/bin/sh

# シェルスクリプトがおいてあるディレクトリを取得
DIRNAME=$(dirname $(readlink -f $0))

# カレントディレクトリを記録
CURDIR=$PWD

# EXE名前など
EXENAME=Graphics
SRCNAME=src
BINNAME=bin

SRCDIR=$DIRNAME/$SRCNAME
BINDIR=$DIRNAME/$BINNAME

# コンパイル
cd $SRCDIR
make

# 実行ファイルを移動
cd $DIRNAME
mkdir -p $BINDIR
mv $SRCDIR/$EXENAME $BINDIR/$EXENAME

