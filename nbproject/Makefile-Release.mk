#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW_TDM-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/App.o \
	${OBJECTDIR}/Ordersheet.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/C/wxWidgets-3.0.3/lib/gcc_dll/libwxmsw30u.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/product-ordersheet.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/product-ordersheet.exe: /C/wxWidgets-3.0.3/lib/gcc_dll/libwxmsw30u.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/product-ordersheet.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/product-ordersheet ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/App.o: App.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -s -I/C/wxWidgets-3.0.3/include -I/C/wxWidgets-3.0.3/lib/gcc_lib/mswu -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/App.o App.cpp

${OBJECTDIR}/Ordersheet.o: Ordersheet.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -s -I/C/wxWidgets-3.0.3/include -I/C/wxWidgets-3.0.3/lib/gcc_lib/mswu -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Ordersheet.o Ordersheet.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
