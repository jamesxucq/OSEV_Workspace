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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/d8a3b606/hash_table_ex.o \
	${OBJECTDIR}/_ext/d8a3b606/stri_utili.o \
	${OBJECTDIR}/_ext/b1a51e63/action_hmap.o \
	${OBJECTDIR}/_ext/f534dc3f/binary_logger.o \
	${OBJECTDIR}/builtin_command.o \
	${OBJECTDIR}/check_command.o \
	${OBJECTDIR}/clie_obje.o \
	${OBJECTDIR}/connect.o \
	${OBJECTDIR}/conv_echo.o \
	${OBJECTDIR}/conv_utili.o \
	${OBJECTDIR}/conve_command.o \
	${OBJECTDIR}/defau_utili.o \
	${OBJECTDIR}/execute.o \
	${OBJECTDIR}/extend.o \
	${OBJECTDIR}/extend/conve.o \
	${OBJECTDIR}/extend/conve_lang/clas_list.o \
	${OBJECTDIR}/extend/conve_lang/conv_gcc_cpp.o \
	${OBJECTDIR}/extend/conve_lang/conv_stri.o \
	${OBJECTDIR}/extend/conve_lang/conv_utili.o \
	${OBJECTDIR}/extend/conve_lang/conver.o \
	${OBJECTDIR}/extend/conve_lang/elang.o \
	${OBJECTDIR}/extend/conve_lang/load_conte.o \
	${OBJECTDIR}/extend/conve_lang/pars_utili.o \
	${OBJECTDIR}/extend/conve_lang/parse.o \
	${OBJECTDIR}/extend/conve_lang/pcattr.o \
	${OBJECTDIR}/extend/list.o \
	${OBJECTDIR}/extend/load.o \
	${OBJECTDIR}/extend/parse_echo/epcla.o \
	${OBJECTDIR}/extend/pretty.o \
	${OBJECTDIR}/extend/save.o \
	${OBJECTDIR}/extend/struti.o \
	${OBJECTDIR}/method.o \
	${OBJECTDIR}/options.o \
	${OBJECTDIR}/osev_bzl.o \
	${OBJECTDIR}/osev_shell.o \
	${OBJECTDIR}/parse_command.o \
	${OBJECTDIR}/parsing.o \
	${OBJECTDIR}/prepa_check.o \
	${OBJECTDIR}/prepa_prompt.o \
	${OBJECTDIR}/shel_struct.o \
	${OBJECTDIR}/stri_utili.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/modetest.o \
	${TESTDIR}/tests/objetest.o

# C Compiler Flags
CFLAGS=-Wall -D_DEBUG -D_OSEV_SHELL -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osev_shell

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osev_shell: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/osev_shell ${OBJECTFILES} ${LDLIBSOPTIONS} ../driver/dist/Debug/GNU-Linux/libosclient.a -lmbedcrypto

${OBJECTDIR}/_ext/d8a3b606/hash_table_ex.o: ../osev_common/hash_table_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/hash_table_ex.o ../osev_common/hash_table_ex.c

${OBJECTDIR}/_ext/d8a3b606/stri_utili.o: ../osev_common/stri_utili.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/stri_utili.o ../osev_common/stri_utili.c

${OBJECTDIR}/_ext/b1a51e63/action_hmap.o: ../osev_common/utility/action_hmap.c
	${MKDIR} -p ${OBJECTDIR}/_ext/b1a51e63
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b1a51e63/action_hmap.o ../osev_common/utility/action_hmap.c

${OBJECTDIR}/_ext/f534dc3f/binary_logger.o: ../third_party/binary_logger.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/binary_logger.o ../third_party/binary_logger.c

${OBJECTDIR}/builtin_command.o: builtin_command.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/builtin_command.o builtin_command.c

${OBJECTDIR}/check_command.o: check_command.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/check_command.o check_command.c

${OBJECTDIR}/clie_obje.o: clie_obje.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clie_obje.o clie_obje.c

${OBJECTDIR}/connect.o: connect.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/connect.o connect.c

${OBJECTDIR}/conv_echo.o: conv_echo.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/conv_echo.o conv_echo.c

${OBJECTDIR}/conv_utili.o: conv_utili.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/conv_utili.o conv_utili.c

${OBJECTDIR}/conve_command.o: conve_command.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/conve_command.o conve_command.c

${OBJECTDIR}/defau_utili.o: defau_utili.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/defau_utili.o defau_utili.c

${OBJECTDIR}/execute.o: execute.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/execute.o execute.c

${OBJECTDIR}/extend.o: extend.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend.o extend.c

${OBJECTDIR}/extend/conve.o: extend/conve.c
	${MKDIR} -p ${OBJECTDIR}/extend
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve.o extend/conve.c

${OBJECTDIR}/extend/conve_lang/clas_list.o: extend/conve_lang/clas_list.c
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/clas_list.o extend/conve_lang/clas_list.c

${OBJECTDIR}/extend/conve_lang/conv_gcc_cpp.o: extend/conve_lang/conv_gcc_cpp.c
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/conv_gcc_cpp.o extend/conve_lang/conv_gcc_cpp.c

${OBJECTDIR}/extend/conve_lang/conv_stri.o: extend/conve_lang/conv_stri.c
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/conv_stri.o extend/conve_lang/conv_stri.c

${OBJECTDIR}/extend/conve_lang/conv_utili.o: extend/conve_lang/conv_utili.c
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/conv_utili.o extend/conve_lang/conv_utili.c

${OBJECTDIR}/extend/conve_lang/conver.o: extend/conve_lang/conver.c
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/conver.o extend/conve_lang/conver.c

${OBJECTDIR}/extend/conve_lang/elang.o: extend/conve_lang/elang.c
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/elang.o extend/conve_lang/elang.c

${OBJECTDIR}/extend/conve_lang/load_conte.o: extend/conve_lang/load_conte.c
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/load_conte.o extend/conve_lang/load_conte.c

${OBJECTDIR}/extend/conve_lang/pars_utili.o: extend/conve_lang/pars_utili.c
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/pars_utili.o extend/conve_lang/pars_utili.c

${OBJECTDIR}/extend/conve_lang/parse.o: extend/conve_lang/parse.c
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/parse.o extend/conve_lang/parse.c

${OBJECTDIR}/extend/conve_lang/pcattr.o: extend/conve_lang/pcattr.c
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/pcattr.o extend/conve_lang/pcattr.c

${OBJECTDIR}/extend/list.o: extend/list.c
	${MKDIR} -p ${OBJECTDIR}/extend
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/list.o extend/list.c

${OBJECTDIR}/extend/load.o: extend/load.c
	${MKDIR} -p ${OBJECTDIR}/extend
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/load.o extend/load.c

${OBJECTDIR}/extend/parse_echo/epcla.o: extend/parse_echo/epcla.c
	${MKDIR} -p ${OBJECTDIR}/extend/parse_echo
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/parse_echo/epcla.o extend/parse_echo/epcla.c

${OBJECTDIR}/extend/pretty.o: extend/pretty.c
	${MKDIR} -p ${OBJECTDIR}/extend
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/pretty.o extend/pretty.c

${OBJECTDIR}/extend/save.o: extend/save.c
	${MKDIR} -p ${OBJECTDIR}/extend
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/save.o extend/save.c

${OBJECTDIR}/extend/struti.o: extend/struti.c
	${MKDIR} -p ${OBJECTDIR}/extend
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/struti.o extend/struti.c

${OBJECTDIR}/method.o: method.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/method.o method.c

${OBJECTDIR}/options.o: options.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/options.o options.c

${OBJECTDIR}/osev_bzl.o: osev_bzl.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_bzl.o osev_bzl.c

${OBJECTDIR}/osev_shell.o: osev_shell.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_shell.o osev_shell.c

${OBJECTDIR}/parse_command.o: parse_command.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_command.o parse_command.c

${OBJECTDIR}/parsing.o: parsing.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parsing.o parsing.c

${OBJECTDIR}/prepa_check.o: prepa_check.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/prepa_check.o prepa_check.c

${OBJECTDIR}/prepa_prompt.o: prepa_prompt.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/prepa_prompt.o prepa_prompt.c

${OBJECTDIR}/shel_struct.o: shel_struct.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/shel_struct.o shel_struct.c

${OBJECTDIR}/stri_utili.o: stri_utili.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stri_utili.o stri_utili.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/modetest.o ${TESTDIR}/tests/objetest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/modetest.o: tests/modetest.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/modetest.o tests/modetest.c


${TESTDIR}/tests/objetest.o: tests/objetest.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/objetest.o tests/objetest.c


${OBJECTDIR}/_ext/d8a3b606/hash_table_ex_nomain.o: ${OBJECTDIR}/_ext/d8a3b606/hash_table_ex.o ../osev_common/hash_table_ex.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/d8a3b606/hash_table_ex.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/hash_table_ex_nomain.o ../osev_common/hash_table_ex.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/d8a3b606/hash_table_ex.o ${OBJECTDIR}/_ext/d8a3b606/hash_table_ex_nomain.o;\
	fi

${OBJECTDIR}/_ext/d8a3b606/stri_utili_nomain.o: ${OBJECTDIR}/_ext/d8a3b606/stri_utili.o ../osev_common/stri_utili.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/d8a3b606/stri_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/stri_utili_nomain.o ../osev_common/stri_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/d8a3b606/stri_utili.o ${OBJECTDIR}/_ext/d8a3b606/stri_utili_nomain.o;\
	fi

${OBJECTDIR}/_ext/b1a51e63/action_hmap_nomain.o: ${OBJECTDIR}/_ext/b1a51e63/action_hmap.o ../osev_common/utility/action_hmap.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/b1a51e63
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/b1a51e63/action_hmap.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b1a51e63/action_hmap_nomain.o ../osev_common/utility/action_hmap.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/b1a51e63/action_hmap.o ${OBJECTDIR}/_ext/b1a51e63/action_hmap_nomain.o;\
	fi

${OBJECTDIR}/_ext/f534dc3f/binary_logger_nomain.o: ${OBJECTDIR}/_ext/f534dc3f/binary_logger.o ../third_party/binary_logger.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/f534dc3f/binary_logger.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/binary_logger_nomain.o ../third_party/binary_logger.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/f534dc3f/binary_logger.o ${OBJECTDIR}/_ext/f534dc3f/binary_logger_nomain.o;\
	fi

${OBJECTDIR}/builtin_command_nomain.o: ${OBJECTDIR}/builtin_command.o builtin_command.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/builtin_command.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/builtin_command_nomain.o builtin_command.c;\
	else  \
	    ${CP} ${OBJECTDIR}/builtin_command.o ${OBJECTDIR}/builtin_command_nomain.o;\
	fi

${OBJECTDIR}/check_command_nomain.o: ${OBJECTDIR}/check_command.o check_command.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/check_command.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/check_command_nomain.o check_command.c;\
	else  \
	    ${CP} ${OBJECTDIR}/check_command.o ${OBJECTDIR}/check_command_nomain.o;\
	fi

${OBJECTDIR}/clie_obje_nomain.o: ${OBJECTDIR}/clie_obje.o clie_obje.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/clie_obje.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clie_obje_nomain.o clie_obje.c;\
	else  \
	    ${CP} ${OBJECTDIR}/clie_obje.o ${OBJECTDIR}/clie_obje_nomain.o;\
	fi

${OBJECTDIR}/connect_nomain.o: ${OBJECTDIR}/connect.o connect.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/connect.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/connect_nomain.o connect.c;\
	else  \
	    ${CP} ${OBJECTDIR}/connect.o ${OBJECTDIR}/connect_nomain.o;\
	fi

${OBJECTDIR}/conv_echo_nomain.o: ${OBJECTDIR}/conv_echo.o conv_echo.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/conv_echo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/conv_echo_nomain.o conv_echo.c;\
	else  \
	    ${CP} ${OBJECTDIR}/conv_echo.o ${OBJECTDIR}/conv_echo_nomain.o;\
	fi

${OBJECTDIR}/conv_utili_nomain.o: ${OBJECTDIR}/conv_utili.o conv_utili.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/conv_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/conv_utili_nomain.o conv_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/conv_utili.o ${OBJECTDIR}/conv_utili_nomain.o;\
	fi

${OBJECTDIR}/conve_command_nomain.o: ${OBJECTDIR}/conve_command.o conve_command.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/conve_command.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/conve_command_nomain.o conve_command.c;\
	else  \
	    ${CP} ${OBJECTDIR}/conve_command.o ${OBJECTDIR}/conve_command_nomain.o;\
	fi

${OBJECTDIR}/defau_utili_nomain.o: ${OBJECTDIR}/defau_utili.o defau_utili.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/defau_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/defau_utili_nomain.o defau_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/defau_utili.o ${OBJECTDIR}/defau_utili_nomain.o;\
	fi

${OBJECTDIR}/execute_nomain.o: ${OBJECTDIR}/execute.o execute.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/execute.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/execute_nomain.o execute.c;\
	else  \
	    ${CP} ${OBJECTDIR}/execute.o ${OBJECTDIR}/execute_nomain.o;\
	fi

${OBJECTDIR}/extend_nomain.o: ${OBJECTDIR}/extend.o extend.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend_nomain.o extend.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend.o ${OBJECTDIR}/extend_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_nomain.o: ${OBJECTDIR}/extend/conve.o extend/conve.c 
	${MKDIR} -p ${OBJECTDIR}/extend
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_nomain.o extend/conve.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve.o ${OBJECTDIR}/extend/conve_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_lang/clas_list_nomain.o: ${OBJECTDIR}/extend/conve_lang/clas_list.o extend/conve_lang/clas_list.c 
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve_lang/clas_list.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/clas_list_nomain.o extend/conve_lang/clas_list.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve_lang/clas_list.o ${OBJECTDIR}/extend/conve_lang/clas_list_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_lang/conv_gcc_cpp_nomain.o: ${OBJECTDIR}/extend/conve_lang/conv_gcc_cpp.o extend/conve_lang/conv_gcc_cpp.c 
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve_lang/conv_gcc_cpp.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/conv_gcc_cpp_nomain.o extend/conve_lang/conv_gcc_cpp.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve_lang/conv_gcc_cpp.o ${OBJECTDIR}/extend/conve_lang/conv_gcc_cpp_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_lang/conv_stri_nomain.o: ${OBJECTDIR}/extend/conve_lang/conv_stri.o extend/conve_lang/conv_stri.c 
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve_lang/conv_stri.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/conv_stri_nomain.o extend/conve_lang/conv_stri.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve_lang/conv_stri.o ${OBJECTDIR}/extend/conve_lang/conv_stri_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_lang/conv_utili_nomain.o: ${OBJECTDIR}/extend/conve_lang/conv_utili.o extend/conve_lang/conv_utili.c 
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve_lang/conv_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/conv_utili_nomain.o extend/conve_lang/conv_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve_lang/conv_utili.o ${OBJECTDIR}/extend/conve_lang/conv_utili_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_lang/conver_nomain.o: ${OBJECTDIR}/extend/conve_lang/conver.o extend/conve_lang/conver.c 
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve_lang/conver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/conver_nomain.o extend/conve_lang/conver.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve_lang/conver.o ${OBJECTDIR}/extend/conve_lang/conver_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_lang/elang_nomain.o: ${OBJECTDIR}/extend/conve_lang/elang.o extend/conve_lang/elang.c 
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve_lang/elang.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/elang_nomain.o extend/conve_lang/elang.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve_lang/elang.o ${OBJECTDIR}/extend/conve_lang/elang_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_lang/load_conte_nomain.o: ${OBJECTDIR}/extend/conve_lang/load_conte.o extend/conve_lang/load_conte.c 
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve_lang/load_conte.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/load_conte_nomain.o extend/conve_lang/load_conte.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve_lang/load_conte.o ${OBJECTDIR}/extend/conve_lang/load_conte_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_lang/pars_utili_nomain.o: ${OBJECTDIR}/extend/conve_lang/pars_utili.o extend/conve_lang/pars_utili.c 
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve_lang/pars_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/pars_utili_nomain.o extend/conve_lang/pars_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve_lang/pars_utili.o ${OBJECTDIR}/extend/conve_lang/pars_utili_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_lang/parse_nomain.o: ${OBJECTDIR}/extend/conve_lang/parse.o extend/conve_lang/parse.c 
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve_lang/parse.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/parse_nomain.o extend/conve_lang/parse.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve_lang/parse.o ${OBJECTDIR}/extend/conve_lang/parse_nomain.o;\
	fi

${OBJECTDIR}/extend/conve_lang/pcattr_nomain.o: ${OBJECTDIR}/extend/conve_lang/pcattr.o extend/conve_lang/pcattr.c 
	${MKDIR} -p ${OBJECTDIR}/extend/conve_lang
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/conve_lang/pcattr.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/conve_lang/pcattr_nomain.o extend/conve_lang/pcattr.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/conve_lang/pcattr.o ${OBJECTDIR}/extend/conve_lang/pcattr_nomain.o;\
	fi

${OBJECTDIR}/extend/list_nomain.o: ${OBJECTDIR}/extend/list.o extend/list.c 
	${MKDIR} -p ${OBJECTDIR}/extend
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/list.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/list_nomain.o extend/list.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/list.o ${OBJECTDIR}/extend/list_nomain.o;\
	fi

${OBJECTDIR}/extend/load_nomain.o: ${OBJECTDIR}/extend/load.o extend/load.c 
	${MKDIR} -p ${OBJECTDIR}/extend
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/load.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/load_nomain.o extend/load.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/load.o ${OBJECTDIR}/extend/load_nomain.o;\
	fi

${OBJECTDIR}/extend/parse_echo/epcla_nomain.o: ${OBJECTDIR}/extend/parse_echo/epcla.o extend/parse_echo/epcla.c 
	${MKDIR} -p ${OBJECTDIR}/extend/parse_echo
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/parse_echo/epcla.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/parse_echo/epcla_nomain.o extend/parse_echo/epcla.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/parse_echo/epcla.o ${OBJECTDIR}/extend/parse_echo/epcla_nomain.o;\
	fi

${OBJECTDIR}/extend/pretty_nomain.o: ${OBJECTDIR}/extend/pretty.o extend/pretty.c 
	${MKDIR} -p ${OBJECTDIR}/extend
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/pretty.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/pretty_nomain.o extend/pretty.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/pretty.o ${OBJECTDIR}/extend/pretty_nomain.o;\
	fi

${OBJECTDIR}/extend/save_nomain.o: ${OBJECTDIR}/extend/save.o extend/save.c 
	${MKDIR} -p ${OBJECTDIR}/extend
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/save.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/save_nomain.o extend/save.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/save.o ${OBJECTDIR}/extend/save_nomain.o;\
	fi

${OBJECTDIR}/extend/struti_nomain.o: ${OBJECTDIR}/extend/struti.o extend/struti.c 
	${MKDIR} -p ${OBJECTDIR}/extend
	@NMOUTPUT=`${NM} ${OBJECTDIR}/extend/struti.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/extend/struti_nomain.o extend/struti.c;\
	else  \
	    ${CP} ${OBJECTDIR}/extend/struti.o ${OBJECTDIR}/extend/struti_nomain.o;\
	fi

${OBJECTDIR}/method_nomain.o: ${OBJECTDIR}/method.o method.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/method.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/method_nomain.o method.c;\
	else  \
	    ${CP} ${OBJECTDIR}/method.o ${OBJECTDIR}/method_nomain.o;\
	fi

${OBJECTDIR}/options_nomain.o: ${OBJECTDIR}/options.o options.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/options.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/options_nomain.o options.c;\
	else  \
	    ${CP} ${OBJECTDIR}/options.o ${OBJECTDIR}/options_nomain.o;\
	fi

${OBJECTDIR}/osev_bzl_nomain.o: ${OBJECTDIR}/osev_bzl.o osev_bzl.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/osev_bzl.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_bzl_nomain.o osev_bzl.c;\
	else  \
	    ${CP} ${OBJECTDIR}/osev_bzl.o ${OBJECTDIR}/osev_bzl_nomain.o;\
	fi

${OBJECTDIR}/osev_shell_nomain.o: ${OBJECTDIR}/osev_shell.o osev_shell.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/osev_shell.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_shell_nomain.o osev_shell.c;\
	else  \
	    ${CP} ${OBJECTDIR}/osev_shell.o ${OBJECTDIR}/osev_shell_nomain.o;\
	fi

${OBJECTDIR}/parse_command_nomain.o: ${OBJECTDIR}/parse_command.o parse_command.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parse_command.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parse_command_nomain.o parse_command.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parse_command.o ${OBJECTDIR}/parse_command_nomain.o;\
	fi

${OBJECTDIR}/parsing_nomain.o: ${OBJECTDIR}/parsing.o parsing.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/parsing.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/parsing_nomain.o parsing.c;\
	else  \
	    ${CP} ${OBJECTDIR}/parsing.o ${OBJECTDIR}/parsing_nomain.o;\
	fi

${OBJECTDIR}/prepa_check_nomain.o: ${OBJECTDIR}/prepa_check.o prepa_check.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/prepa_check.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/prepa_check_nomain.o prepa_check.c;\
	else  \
	    ${CP} ${OBJECTDIR}/prepa_check.o ${OBJECTDIR}/prepa_check_nomain.o;\
	fi

${OBJECTDIR}/prepa_prompt_nomain.o: ${OBJECTDIR}/prepa_prompt.o prepa_prompt.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/prepa_prompt.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/prepa_prompt_nomain.o prepa_prompt.c;\
	else  \
	    ${CP} ${OBJECTDIR}/prepa_prompt.o ${OBJECTDIR}/prepa_prompt_nomain.o;\
	fi

${OBJECTDIR}/shel_struct_nomain.o: ${OBJECTDIR}/shel_struct.o shel_struct.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/shel_struct.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/shel_struct_nomain.o shel_struct.c;\
	else  \
	    ${CP} ${OBJECTDIR}/shel_struct.o ${OBJECTDIR}/shel_struct_nomain.o;\
	fi

${OBJECTDIR}/stri_utili_nomain.o: ${OBJECTDIR}/stri_utili.o stri_utili.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/stri_utili.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../osev_common -I../third_party -I../driver -I../osev_sdkit/storage -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stri_utili_nomain.o stri_utili.c;\
	else  \
	    ${CP} ${OBJECTDIR}/stri_utili.o ${OBJECTDIR}/stri_utili_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
