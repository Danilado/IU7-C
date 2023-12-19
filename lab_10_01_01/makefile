CC := gcc

INCPATH := ./inc/
SRCPATH := ./src/
CHECKPATH := ./unit_tests/
OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

SRCS := $(wildcard $(SRCPATH)*.c)
SRCS := $(SRCS:.c=.d)
SRCS := $(subst $(SRCPATH), $(OUTPATH), $(SRCS))
OBJECTS := $(OUTPATH)my_list.o $(OUTPATH)item.o
CHECK_OBJECTS := $(OUTPATH)check_my_list.o $(OUTPATH)check_item.o

BUILDFLAGS := -lm
CFLAGS := -std=gnu99 -Wall -Wextra -pedantic -I$(INCPATH)
DEBUGFLAGS := -O0 -g3 -fprofile-arcs -ftest-coverage
CHECKFLAGS := -lcheck -lrt

include $(SRCS)

# release build part

.PHONY: release
release: CFLAGS += -O3 -g0 -DNDEBUG
release: release.lastbuildstate | app.exe

# files

app.exe: $(OUTPATH)main.o $(OBJECTS)
	$(CC) $(BUILDFLAGS) $^ -o $@

unit_tests.exe: $(OUTPATH)check_main.o $(OBJECTS) $(CHECK_OBJECTS)
	$(CC) $(CHECKFLAGS) $(BUILDFLAGS) $^ -o $@

$(OUTPATH)%.o : */%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)%.d : */%.c
	$(CC) $(CFLAGS) -MM $< > $@

%.lastbuildstate: 
	make clean
	touch $@

# debug builds part

.PHONY: debug

debug: CFLAGS += $(DEBUGFLAGS)
debug: BUILDFLAGS += -fprofile-arcs -lgcov -ftest-coverage

ifeq ($(san), asan)
debug: CC:=clang
debug: CFLAGS += -fsanitize=address -fno-omit-frame-pointer
debug: BUILDFLAGS += -fsanitize=address
debug: asan.lastbuildstate | app.exe

else ifeq ($(san), msan)
debug: CC:=clang
debug: CFLAGS += -fsanitize=memory -fPIE -fno-omit-frame-pointer
debug: BUILDFLAGS += -fsanitize=memory -fPIE
debug: msan.lastbuildstate | app.exe

else ifeq ($(san), ubsan)
debug: CC:=clang
debug: CFLAGS += -fsanitize=undefined -fno-omit-frame-pointer
debug: BUILDFLAGS += -fsanitize=undefined
debug: ubsan.lastbuildstate | app.exe

else
debug: debug.lastbuildstate | app.exe

endif

# test build part

.PHONY: test_build
test_build: CFLAGS += $(DEBUGFLAGS) $(CHECKFLAGS)
test_build: BUILDFLAGS += -fprofile-arcs -lgcov
test_build: debug.lastbuildstate | unit_tests.exe

# utils part

.PHONY: weverything
weverything: CC:=clang
weverything: CFLAGS += $(DEBUGFLAGS) -Weverything
weverything: BUILDFLAGS += -fprofile-arcs -lgcov
weverything: weverything.lastbuildstate | app.exe


.PHONY: clean
clean:
	rm -f ./*.exe ./out/* ./*.o ./*.gcov ./*.gcno ./*.gcda out.txt ./*.d ./*.lastbuildstate

.PHONY: coverage
coverage:
	cd $(OUTPATH) && gcov ./*.gcno

.PHONY: unit
unit:
	make test_build
	./unit_tests.exe
	make coverage

.PHONY: func
func:
	make debug
	$(info DEBUG BUILD TEST)
	bash ./func_tests/scripts/func_tests.sh
	$(info COVERAGE)
	make coverage
