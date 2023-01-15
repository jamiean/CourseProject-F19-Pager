CC=g++ -g -Wall -fno-builtin

# List of source files for your pager
PAGER_SOURCES=vm_pager.cpp

# Generate the names of the pager's object files
PAGER_OBJS=${PAGER_SOURCES:.cpp=.o}

EXES=pager testbasic1 testspec testbasic2 testbasic3 testbasic4  testfile1 testSUnrefDir testSResDir testSEvi testFUnrefDirty testFResClean testFUnrefClean testSUnrefClean testSResClean testmultipleowner testSwitch1 testSwitch2 testSwitch3 testSwitch4 testFork1 testFork2 testOverFlow testOverFlow1 testFileName1 testFileName2 testNonEmpty1 testNonEmpty2 testNonEmpty3 testNonEmpty4

all: ${EXES}

# Compile the pager and tag this compilation
pager: ${PAGER_OBJS} libvm_pager.o
	./autotag.sh
	${CC} -o $@ $^

# Compile an application program
testspec: testspec.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testbasic1: testbasic1.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testbasic2: testbasic2.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testbasic3: testbasic3.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testbasic4: testbasic4.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testfile1: testfile1.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testSUnrefDir: testSUnrefDir.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testSResDir: testSResDir.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testSEvi: testSEvi.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testFUnrefDirty: testFUnrefDirty.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testFResClean:  testFResClean.4.cpp libvm_app.o
	${CC} -o $@ $^ -ldl

testFUnrefClean:  testFUnrefClean.4.cpp  libvm_app.o
	${CC} -o $@ $^ -ldl

testSUnrefClean: testSUnrefClean.4.cpp  libvm_app.o
	${CC} -o $@ $^ -ldl

testSResClean: testSResClean.4.cpp  libvm_app.o
	${CC} -o $@ $^ -ldl

testmultipleowner:	testmultipleowner.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testSwitch1:  testSwitch1.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testSwitch2:  testSwitch2.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testSwitch3:  testSwitch3.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testSwitch4:	testSwitch4.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testFork1:	testFork1.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testFork2:  testFork2.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testOverFlow:	testOverFlow.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testOverFlow1:	testOverFlow1.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testFileName1:  testFileName1.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testFileName2:	testFileName2.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testNonEmpty1:	testNonEmpty1.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testNonEmpty2:	testNonEmpty2.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testNonEmpty3:	testNonEmpty3.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl

testNonEmpty4:	testNonEmpty4.4.cpp   libvm_app.o
	${CC} -o $@ $^ -ldl
	
# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

clean:
	rm -f ${PAGER_OBJS} ${EXES}
