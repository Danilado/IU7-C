CC := gcc

INCPATH := ./inc/
SRCPATH := ./src/
CHECKPATH := ./unit_tests/
OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

SRCS := $(wildcard $(SRCPATH)*.c)
SRCS := $(SRCS:.c=.d)
SRCS := $(subst $(SRCPATH), $(OUTPATH), $(SRCS))

BUILDFLAGS := -lm
CFLAGS := -std=gnu99 -O0 -g3 -Wall -Wextra -I$(INCPATH)
DEBUGFLAGS := -O0 -g3
CHECKFLAGS := -lcheck -lrt

ifeq ($(libtype), dynamic)
LIBS := $(OUTPATH)libdynarr.so
CFLAGS += -fPIC
BUILDFLAGS += -L$(OUTPATH) -ldynarr
LD_LIBRARY_PATH += $(OUTPATH)

else ifeq ($(libtype), ldl)
LIBS := $(OUTPATH)libdynarr.so
CFLAGS += -DLDL -I./unit_tests/
BUILDFLAGS += -ldl

else ifeq ($(libtype), static)
LIBS := $(OUTPATH)libdynarr.a
BUILDFLAGS += -L$(OUTPATH) -ldynarr

else
$(info falling to static lib type)
LIBS := $(OUTPATH)libdynarr.a
BUILDFLAGS += -L$(OUTPATH) -ldynarr
endif

OBJECTS := $(OUTPATH)my_argparse.o
CK_OBJECTS := $(OUTPATH)check_dynarr.o

# release build part

.PHONY: release
release: CFLAGS += -O3 -g0 -DNDEBUG
release: release.lastbuildstate | app.exe

# files
app.exe: $(OUTPATH)main.o $(LIBS) $(OBJECTS)
	$(CC) $< $(OBJECTS) -o $@ $(BUILDFLAGS)

unit_tests.exe: $(OUTPATH)check_main.o $(LIBS) $(OBJECTS) $(CK_OBJECTS)
	$(CC) $< $(OBJECTS) $(CK_OBJECTS) $(CHECKFLAGS) $(BUILDFLAGS) -o $@

$(OUTPATH)%.o : */%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)lib%.a : $(OUTPATH)%.o
	ar cr $@ $<
	ranlib $@ 

$(OUTPATH)lib%.so : $(OUTPATH)%.o
	gcc -o $@ -shared $<

$(OUTPATH)%.d : */%.c
	$(CC) $(CFLAGS) -MM $< > $@

%.lastbuildstate: 
	make clean
	touch $@

# debug builds part

.PHONY: debug

debug: CFLAGS += $(DEBUGFLAGS)
# debug: BUILDFLAGS += -fprofile-arcs -lgcov -ftest-coverage

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
# test_build: BUILDFLAGS += -fprofile-arcs -lgcov
test_build: debug.lastbuildstate | unit_tests.exe

# utils part

.PHONY: weverything
weverything: CC:=clang
weverything: CFLAGS += $(DEBUGFLAGS) -Weverything
# weverything: BUILDFLAGS += -fprofile-arcs -lgcov
weverything: weverything.lastbuildstate | app.exe


.PHONY: clean
clean:
	rm -f ./*.exe ./out/* ./*.o ./*.gcov ./*.gcno ./*.gcda out.txt ./*.d ./*.lastbuildstate

.PHONY: coverage
coverage:
# cd $(OUTPATH) && gcov ./*.gcno
	$(info Я убрал coverage, потому что он ломает линковку)

.PHONY: unit
unit: unit_tests.exe
	./unit_tests.exe
	make coverage

.PHONY: func
func: debug
	$(info DEBUG BUILD TEST)
	bash ./func_tests/scripts/func_tests.sh
	$(info COVERAGE)
	make coverage

include $(SRCS)
