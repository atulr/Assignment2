# Example makefile for compiling trax code
# Note, rt.s and rt.bc are temporary files used by the makefile
# pre.ll and post.ll are human readable LLVM bitcode for debugging purposes

# Height and width for the executable
WIDTH=512
HEIGHT=512

# The source file with the main() function
SOURCES := $(wildcard *.cc)
SOURCE=raytrace.cc sphere.cc
#SOURCE=example.cpp


# The names for your binary executable and trax assembly
BINARYOUTPUT=run_rt
TRAXOUTPUT=rt-llvm.s

# The directory for SimHWRT
# SIMDIR=../../SimHWRT/trunk
# Josef's directory style
SIMDIR=../../sim

# The bin directory for llvm. Should be linked in LLVM_Trax if you  ran setup.sh
BINDIR=../bin

# The lib directory with trax_cpp.cpp
LIBDIR=../lib

# The include directory inside LLVM_Trax
INCLUDEDIR=../include

# The path to the linker directory
LINKERDIR=../linker

# Cornell Scene
VIEWFILE=\"${SIMDIR}/views/cornell_obj.view\"
MODELFILE=\"${SIMDIR}/test_models/cornell/CornellBox.obj\"
LIGHTFILE=\"${SIMDIR}/lights/cornell.light\"
# Conference Scene
# VIEWFILE=\"${SIMDIR}/views/conference.view\"
# MODELFILE=\"${SIMDIR}/test_models/conference.iw\"
# LIGHTFILE=\"${SIMDIR}/lights/conference.light\"

# Should not need to edit below this point unless you know what you're doing
# The compiler to use for the executable
CXX=g++
CXXFILENAMES=-DVIEWFILE=${VIEWFILE} -DMODELFILE=${MODELFILE} -DLIGHTFILE=${LIGHTFILE}
CXXFLAGS=-DTRAX=0 -DWIDTH=${WIDTH} -DHEIGHT=${HEIGHT} ${CXXFILENAMES} -I${SIMDIR} -I${INCLUDEDIR}
CXXSIMFILES=${SIMDIR}/LoadMemory.cc ${SIMDIR}/OBJLoader.cc ${SIMDIR}/IWLoader.cc ${SIMDIR}/BVH.cc ${SIMDIR}/Grid.cc ${SIMDIR}/Camera.cc ${SIMDIR}/ReadLightfile.cc ${SIMDIR}/ReadViewfile.cc ${SIMDIR}/Material.cc ${SIMDIR}/Triangle.cc ${SIMDIR}/MTLLoader.cc ${SIMDIR}/PPM.cc ${LIBDIR}/trax_cpp.cpp

# Front end compiler to use for trax target
# For the default mac build
TRAXC=llvm-gcc
# For compiling on the CADE machines
# TRAXC=/usr/local/stow/llvm-gcc/llvm-gcc4.2-2.6/bin/g++
# If you prefer clang it might work.
# TRAXC=clang
TRAXCFLAGS=-DTRAX=1 -I${INCLUDEDIR}

all: mkdirs ${BINARYOUTPUT} ${TRAXOUTPUT}
default: mkdirs ${BINARYOUTPUT} ${TRAXOUTPUT}

${BINARYOUTPUT}: ${SOURCES}
	@echo "Building ${BINARYOUTPUT}"
	@${CXX} ${SOURCES} ${CXXSIMFILES} ${CXXFLAGS} -o ${BINARYOUTPUT}

${TRAXOUTPUT}: rt.s
	@echo "Writing ${TRAXOUTPUT}"
	@${LINKERDIR}/ln.py rt.s > ${TRAXOUTPUT}

mkdirs:
	@mkdir -p objs;

objs/%.bc: %.cc
	@echo "Building $<"
	@${TRAXC} -emit-llvm ${TRAXCFLAGS} -o $@ -c $<

OBJS := $(addprefix objs/, $(notdir $(SOURCES:.cc=.bc)))

rt.s: ${OBJS} ${INCLUDEDIR}/trax.hpp
	@${BINDIR}/llvm-ld ${OBJS} -o rt
	@${BINDIR}/llvm-dis rt.bc -o pre.ll
	@${BINDIR}/opt rt.bc -O3 -inline-threshold 200000000 -o rt.bc
	@${BINDIR}/llvm-dis rt.bc -o post.ll
	@${BINDIR}/llc rt.bc -o rt.s -march=trax

clean:
	rm -rf objs/ rt.s rt.bc pre.ll post.ll ${TRAXOUTPUT} ${BINARYOUTPUT} out.png *~ 
