CC = gcc
CFLAGS = -Wall -Werror -Wextra -c -std=c11
CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -c -std=c++17 -pedantic

make all:
	make install
	make install_tetris_cli
	make install_snake_cli

install:
	mkdir -p games
	touch games/record_snake.txt
	cd gui/desktop && qmake
	$(MAKE) -C gui/desktop
	mv gui/desktop/snake games
	make clean

install_tetris_cli:
	mkdir -p games
	touch games/record_tetris.txt
	$(CC) $(CFLAGS) brick_game/tetris/*.c gui/cli/*.c -lncurses
	$(CC) *.o -o games/tetris_cli -lncurses
	rm *.o

install_snake_cli:
	mkdir -p games
	touch games/record_snake.txt
	$(CXX) $(CXXFLAGS) brick_game/snake/*.cpp gui/cli/*.c -lncurses
	$(CXX) *.o -o games/snake_cli -lncurses
	rm *.o

uninstall:
	rm -rf games

dist:
	mkdir -p snake_dist
	cp -r brick_game snake_dist
	cp -r gui snake_dist
	cp -r controller snake_dist
	cp -r test snake_dist
	cp Makefile snake_dist
	cp Doxyfile snake_dist
	tar -cvzf snake_dist.tgz snake_dist
	rm -rf snake_dist

dvi:
	doxygen
	xdg-open doxygen/html/index.html

snake.a:
	$(CXX) $(CXXFLAGS) brick_game/snake/model_snake.cpp
	ar rcs snake.a *.o
	rm *.o

test: snake.a
	$(CXX) $(CXXFLAGS) test/*.cpp
	$(CXX) -L. -I. -o test_back *.o snake.a -lgtest -pthread
	rm *.o
	./test_back

gcov_report:
	mkdir -p report
	$(CXX) $(CXXFLAGS) -fprofile-arcs -ftest-coverage brick_game/snake/model_snake.cpp
	ar rcs snake_gcov.a *.o
	ranlib snake_gcov.a
	rm *.o
	$(CXX) $(CXXFLAGS) -fprofile-arcs -ftest-coverage test/*.cpp
	$(CXX) -L. -I. -o test_gcov *.o snake_gcov.a -lgcov -pthread -lgtest
	./test_gcov
	gcov -o . brick_game/snake/model_snake.cpp
	lcov -b ./ -d . --gcov-tool /usr/bin/gcov -c -o output.info --no-external
	genhtml -o report/ output.info
	xdg-open report/index.html

rebuild:
	make uninstall
	make all

clean:
	rm -f gui/desktop/*.o gui/desktop/moc_predefs.h gui/desktop/moc_view.cpp gui/desktop/Makefile gui/desktop/.qmake.stash
	rm -f *.o *.a test_back *.gcno *.gcda *.gcov *.info test_gcov
	rm -fr report doxygen

valgrind:
	valgrind  --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test_back

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n brick_game/tetris/*.c brick_game/tetris/*.h gui/cli/*.c gui/cli/*.h test/*.cpp test/*.h
	clang-format -n brick_game/snake/*.cpp brick_game/snake/*.h controller/snake/*.cpp controller/snake/*.h gui/desktop/*.cpp gui/desktop/*.h

.PHONY: all install uninstall install_tetris_cli install_snake_cli dvi dist snake.a test gcov_report rebuild valgrind clang clean