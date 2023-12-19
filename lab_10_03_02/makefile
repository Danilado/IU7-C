CC := gcc

INCPATH := ./inc/ -I../lab_10_03_common/
SRCPATH := ./
OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

OBJECTS := $(OUTPATH)my_list.o $(OUTPATH)associative_array_impl_2.o
CHECK_OBJECTS := $(OUTPATH)check_associative_array.o

BUILDFLAGS := -lm
CFLAGS := -std=gnu99 -Wall -Wextra -pedantic -I$(INCPATH)
DEBUGFLAGS := -O0 -g3 # -fprofile-arcs -ftest-coverage

CFLAGS += $(DEBUGFLAGS)

CHECKFLAGS := -lcheck -lrt

# files

unit_tests.exe: $(OUTPATH)check_main.o $(OBJECTS) $(CHECK_OBJECTS)
	$(CC) $(CHECKFLAGS) $(BUILDFLAGS) $^ -o $@

$(OUTPATH)check_main.o : ../lab_10_03_common/check_main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)check_associative_array.o : ../lab_10_03_common/check_associative_array.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)my_list.o : ./my_list.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)associative_array_impl_2.o: ./associative_array_impl_2.c
	$(CC) $(CFLAGS) -c $< -o $@

# $(OUTPATH)%.d : */%.c
# 	$(CC) $(CFLAGS) -MM $< > $@

# %.lastbuildstate: 
# 	make clean
# 	touch $@

# debug builds part

# .PHONY: debug

# debug: CFLAGS += $(DEBUGFLAGS)
# debug: BUILDFLAGS += -fprofile-arcs -lgcov -ftest-coverage

# ifeq ($(san), asan)
# debug: CC:=clang
# debug: CFLAGS += -fsanitize=address -fno-omit-frame-pointer
# debug: BUILDFLAGS += -fsanitize=address
# debug: asan.lastbuildstate | app.exe

# else ifeq ($(san), msan)
# debug: CC:=clang
# debug: CFLAGS += -fsanitize=memory -fPIE -fno-omit-frame-pointer
# debug: BUILDFLAGS += -fsanitize=memory -fPIE
# debug: msan.lastbuildstate | app.exe

# else ifeq ($(san), ubsan)
# debug: CC:=clang
# debug: CFLAGS += -fsanitize=undefined -fno-omit-frame-pointer
# debug: BUILDFLAGS += -fsanitize=undefined
# debug: ubsan.lastbuildstate | app.exe

# else
# debug: debug.lastbuildstate | app.exe

# endif

# # test build part

# .PHONY: test_build
# test_build: CFLAGS += $(DEBUGFLAGS) $(CHECKFLAGS)
# test_build: BUILDFLAGS += -fprofile-arcs -lgcov
# test_build: debug.lastbuildstate | unit_tests.exe

# # utils part

# .PHONY: weverything
# weverything: CC:=clang
# weverything: CFLAGS += $(DEBUGFLAGS) -Weverything
# weverything: BUILDFLAGS += -fprofile-arcs -lgcov
# weverything: weverything.lastbuildstate | app.exe


.PHONY: clean
clean:
	rm -f ./*.exe ./out/* ./*.o ./*.gcov ./*.gcno ./*.gcda out.txt ./*.d ./*.lastbuildstate

.PHONY: coverage
coverage:
	cd $(OUTPATH) && gcov ./*.gcno

.PHONY: unit
unit:
	make unit_tests.exe
	./unit_tests.exe
	make coverage

# .PHONY: func
# func:
# 	make debug
# 	$(info DEBUG BUILD TEST)
# 	bash ./func_tests/scripts/func_tests.sh
# 	$(info COVERAGE)
# 	make coverage
