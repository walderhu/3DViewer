EXE = 3DViever
PROJECT = ./Core
BUILD_PATH = ./bin
TRASH = CMakeFiles $(PROJECT)/*.user $(PROJECT)/*.save report test.info
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	OPEN_CMD = xdg-open
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
endif

all: build run

build: $(BUILD_PATH)/$(EXE)

run: 
ifeq ($(UNAME_S),Linux)
	$(BUILD_PATH)/$(EXE)
endif

ifeq ($(UNAME_S),Darwin)
	$(BUILD_PATH)/3DViever.app/Contents/MacOS/$(EXE)
endif

clean:
	rm -rf $(TRASH)
	rm -rf *.gcno *.a *.o s21_3DViever_Tests *.gcda
	rm -rf  ./Dvi/index.html

$(BUILD_PATH)/$(EXE): | $(BUILD_PATH)
	cmake $(PROJECT) -B $(BUILD_PATH)
	make -C $(BUILD_PATH) -s

$(BUILD_PATH):
	mkdir -p $@

reset: uninstall all

leaks: $(BUILD_PATH)/$(EXE)
	valgrind --leak-check=full --track-origins=yes $(BUILD_PATH)/$(EXE)

.PHONY: test all install uninstall clean Dvi dist gcov_report clean_tests

test: uninstall $(BUILD_PATH)/s21_3DViever_Tests

tests: test

$(BUILD_PATH)/s21_3DViever_Tests: | $(BUILD_PATH)
	cmake ./Tests/ -B $(BUILD_PATH)
	make -C $(BUILD_PATH) -s
	./$(BUILD_PATH)/s21_3DViever_Tests 

gcov_report: test
	make -C $(BUILD_PATH) gcov_report -s

dvi:
	pandoc ./Dvi/index.md -o ./Dvi/index.html
	open ./Dvi/index.html

install: build

dist: 
	@tar cvzf ${EXE}.tgz $(BUILD_PATH)

uninstall: clean
	rm -rf ${BUILD_PATH}

clang:
	clang-format -n -style=google ./Core/*.cpp ./Core/*.h ./Tests/*.c ./Tests/*.h