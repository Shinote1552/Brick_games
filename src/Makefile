CPP=g++ -std=c++17
СС=gcc -std=c11
CFLAGS = -I/mingv64/include
#
INSTALL_FILES = brick_game/tetris/*.c brick_game/snake/model/*.cc gui/cli/*.c brick_game.a -lncurses
CC_FILES = brick_game/tetris/*.c gui/cli/*.c brick_game.a -lncurses
#
INSTALL_TEST = brick_game/tetris/*.c brick_game/snake/model/*.cc brick_game.a
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
FLAGSCH = -lcheck
TARGET = brick_game
TETRIS_CLI_TARGET = brick_game/build_models/cli_main.c brick_game/controller/controller_tetris.c
TETRIS_DESKTOP_TARGET = brick_game/build_models/tetris_desktop.cc brick_game/controller/controller_tetris.cc
SNAKE_CLI_TARGET = brick_game/build_models/cli_main.c brick_game/controller/controller_snake.cc
SNAKE_DESKTOP_TARGET = brick_game/build_models/snake_desktop.cc brick_game/controller/controller_snake.cc
GOOGLETESTFLAG = -lgtest

ifeq ($(shell uname),Linux)
	FLAGSCH += -lm -lsubunit -lpthread -lrt
else
	FLAGSCH = -lcheck -lpthread
endif

INSTALL_DIR = ..

all: install

win64: win_tetris_cli win_snake_cli tetris_desktop_win snake_desktop_win

win_tetris_cli:
	@ mkdir -p ../build_models/Win64x_cli
	gcc -I/ucrt64/include/ncurses -o  ../build_models/Win64x_cli/Win64x_tetris_cli brick_game/tetris/tetris.c brick_game/controller/controller_tetris.c brick_game/build_models/cli_main.c gui/cli/frontend_cli.c -lncursesw -mconsole

win_snake_cli:
	@ mkdir -p ../build_models/Win64x_cli
	g++ -I/ucrt64/include/ncurses -o ../build_models/Win64x_cli/Win64x_snake_cli brick_game/snake/model/snake.cc brick_game/controller/controller_snake.cc brick_game/build_models/cli_main.c gui/cli/frontend_cli.c -lncursesw -mconsole

tetris_desktop_win:
	@ cp -f brick_game/build_models/tetris_desktop/view.h gui/desktop/View/
	@ cd gui/desktop/View/ && qmake && make
	@ cd ../../../
	@ mkdir -p ../build_models/tetris_desktop
	@ cp gui/desktop/View/release/View.exe ../build_models/tetris_desktop/Win64x_tetris.exe
	# ../build_models/tetris_desktop/View.exe

snake_desktop_win:
	@ cp -f brick_game/build_models/snake_desktop/view.h gui/desktop/View/
	@ cd gui/desktop/View/ && qmake && make
	@ cd ../../../
	@ mkdir -p ../build_models/snake_desktop
	@ cp gui/desktop/View/release/View.exe ../build_models/snake_desktop/Win64x_snake.exe
	# ../build_models/snake_desktop/View

install: tetris_cli snake_cli tetris_desktop snake_desktop

run_tc:
	../build_models/tetris_cli

run_td:
	../build_models/tetris_desktop/View

run_sc:
	../build_models/snake_cli

run_sd:
	../build_models/snake_desktop/View

tetris_cli: backend.a
	@ mkdir -p ../build_models
	@ $(CC) $(CFLAGS) $(CC_FILES) $(TETRIS_CLI_TARGET) -o ../build_models/tetris_cli
	# @ ../build_models/tetris_cli

tetris_desktop:
	@ cp -f brick_game/build_models/tetris_desktop/view.h gui/desktop/View/
	@ cd gui/desktop/View/ && qmake && make
	@ cd ../../../
	@ mkdir -p ../build_models/tetris_desktop
	@ cp gui/desktop/View/View.app/Contents/MacOS/View ../build_models/tetris_desktop
	# ../build_models/tetris_desktop/View

snake_cli: backend.a
	@ mkdir -p ../build_models
	@ $(CPP) $(CFLAGS) $(INSTALL_FILES) $(SNAKE_CLI_TARGET) -o ../build_models/snake_cli
	# @ ../build_models/snake_cli

snake_desktop:
	@ cp -f brick_game/build_models/snake_desktop/view.h gui/desktop/View/
	@ cd gui/desktop/View/ && qmake && make
	@ cd ../../../
	@ mkdir -p ../build_models/snake_desktop
	@ cp gui/desktop/View/View.app/Contents/MacOS/View ../build_models/snake_desktop
	# ../build_models/snake_desktop/View

uninstall_win:
	@ rm -rf ../build_models	

uninstall:
	@ rm -rf ../build_models/tetris_cli
	@ rm -rf ../build_models/snake_cli
	@ rm -rf ../build_models/snake_desktop/View
	@ rm -rf ../build_models/tetris_desktop/View
	@ rm -rf ../build_models

clean_win: clean_qt uninstall_win
	@ rm -rf *.o *.a *.gcno *.gcda *.info report *.dvi *.aux *.log
	@ rm -rf res.info res_filtered.info test test_g
	@ rm -rf gui/desktop/View/release
	@ rm -rf gui/desktop/View/debug


clean_qt:
	@ cd gui/desktop/View/ && make clean;
	@ cd ../../../

clean: clean_qt uninstall
	@ rm -rf *.o *.a *.gcno *.gcda *.info report *.dvi *.aux *.log
	@ rm -rf res.info res_filtered.info test test_g

test: backend.a
	@ $(CPP) $(INSTALL_TEST) --coverage brick_game/tests/test.c -o test $(FLAGSCH)
	@ $(CPP) $(GOOGLETESTFLAG) $(INSTALL_TEST) --coverage brick_game/tests/test_g.cc -o test_g $(FLAGSCH)
	@ ./test
	@ ./test_g

backend.a: backend.o
	@ ar rcs $(TARGET).a *.o
	@ ranlib $(TARGET).a

backend.o:
	@ $(CC) -c ./brick_game/tetris/*.c
	@ $(CPP) -c ./brick_game/snake/model/*.cc

dvi:
	@ cat ../README_RUS.md

manual.dvi: dvi

dist: dvi

gcov_report: test
	@ lcov --ignore-errors usage,inconsistent -t "result" -o res.info -c -d .
	@ lcov --extract res.info '*/brick_game/tetris/' '*/brick_game/snake/model/' -o res_filtered.info
	@ genhtml -o report res_filtered.info
	@ open report/index.html
	@ rm -rf *gcda *gcno res.info res_filtered.info test test_g

clang:
	@ clang-format -style=Google -n gui/cli/*.c gui/cli/*.h
	@ clang-format -style=Google -n gui/desktop/View/*.cc gui/desktop/View/*.h
	@ clang-format -style=Google -n brick_game/build_models/*.c
	@ clang-format -style=Google -n brick_game/build_models/snake_desktop/*.h brick_game/build_models/tetris_desktop/*.h
	@ clang-format -style=Google -n brick_game/common/*.h
	@ clang-format -style=Google -n brick_game/controller/*.c brick_game/controller/*.h brick_game/controller/*.cc
	@ clang-format -style=Google -n brick_game/snake/model/*.cc brick_game/snake/model/*.h
	@ clang-format -style=Google -n brick_game/tetris/*.c brick_game/tetris/*.h
	@ clang-format -style=Google -n brick_game/tetris/*.c brick_game/tetris/*.h
	@ clang-format -style=Google -n brick_game/tests/*.c brick_game/tests/*.cc

clang_install:
	@ clang-format -style=Google -i gui/cli/*.c gui/cli/*.h
	@ clang-format -style=Google -i gui/desktop/View/*.cc gui/desktop/View/*.h
	@ clang-format -style=Google -i brick_game/build_models/*.c
	@ clang-format -style=Google -i brick_game/build_models/snake_desktop/*.h brick_game/build_models/tetris_desktop/*.h
	@ clang-format -style=Google -i brick_game/common/*.h
	@ clang-format -style=Google -i brick_game/controller/*.c brick_game/controller/*.h brick_game/controller/*.cc
	@ clang-format -style=Google -i brick_game/snake/model/*.cc brick_game/snake/model/*.h
	@ clang-format -style=Google -i brick_game/tetris/*.c brick_game/tetris/*.h
	@ clang-format -style=Google -i brick_game/tests/*.c brick_game/tests/*.cc


rebuild: clean install

.PHONY: all install unistall clean test dvi dist gcov_report clang
