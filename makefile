# makefile

# コンパイルしたいファイル
Target = Main.cpp
Library = Color.cpp ColorData.cpp Rect.cpp Binary.cpp

# フォルダ名を実行ファイル名にする
ExeName = $(lastword $(subst /, ,$(dir $(realpath $(Target)))))

$(ExeName) : $(Target) $(Library) 
	g++ -std=c++0x -O0 -Wall -o $(ExeName) $(Target) $(Library) 

.PHONY: clean
clean :
	rm -f $(ExeName)
