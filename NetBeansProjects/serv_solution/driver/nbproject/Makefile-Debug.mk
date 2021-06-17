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
	${OBJECTDIR}/_ext/d8a3b606/checksum.o \
	${OBJECTDIR}/_ext/d8a3b606/crypto_utili.o \
	${OBJECTDIR}/_ext/d8a3b606/encoding.o \
	${OBJECTDIR}/_ext/d8a3b606/linux_os.o \
	${OBJECTDIR}/_ext/d8a3b606/oid.o \
	${OBJECTDIR}/_ext/d8a3b606/paras_style.o \
	${OBJECTDIR}/_ext/d8a3b606/pstyl_utili.o \
	${OBJECTDIR}/_ext/d8a3b606/stri_utili.o \
	${OBJECTDIR}/_ext/b1a51e63/adler32.o \
	${OBJECTDIR}/_ext/b1a51e63/base64.o \
	${OBJECTDIR}/_ext/b1a51e63/md5.o \
	${OBJECTDIR}/_ext/b1a51e63/strptime.o \
	${OBJECTDIR}/_ext/f534dc3f/dmap64.o \
	${OBJECTDIR}/_ext/f534dc3f/linenoise.o \
	${OBJECTDIR}/_ext/f534dc3f/logger.o \
	${OBJECTDIR}/_ext/f534dc3f/memory_utility.o \
	${OBJECTDIR}/clie_bzl.o \
	${OBJECTDIR}/dstr_utili.o \
	${OBJECTDIR}/excep_msg.o \
	${OBJECTDIR}/hand_method.o \
	${OBJECTDIR}/osco_socks.o \
	${OBJECTDIR}/osev_clie.o \
	${OBJECTDIR}/pinvo.o


# C Compiler Flags
CFLAGS=-Wall -D_OSEV_CLIE -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosclient.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosclient.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosclient.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosclient.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosclient.a

${OBJECTDIR}/_ext/d8a3b606/checksum.o: ../osev_common/checksum.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/checksum.o ../osev_common/checksum.c

${OBJECTDIR}/_ext/d8a3b606/crypto_utili.o: ../osev_common/crypto_utili.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/crypto_utili.o ../osev_common/crypto_utili.c

${OBJECTDIR}/_ext/d8a3b606/encoding.o: ../osev_common/encoding.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/encoding.o ../osev_common/encoding.c

${OBJECTDIR}/_ext/d8a3b606/linux_os.o: ../osev_common/linux_os.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/linux_os.o ../osev_common/linux_os.c

${OBJECTDIR}/_ext/d8a3b606/oid.o: ../osev_common/oid.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/oid.o ../osev_common/oid.c

${OBJECTDIR}/_ext/d8a3b606/paras_style.o: ../osev_common/paras_style.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/paras_style.o ../osev_common/paras_style.c

${OBJECTDIR}/_ext/d8a3b606/pstyl_utili.o: ../osev_common/pstyl_utili.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/pstyl_utili.o ../osev_common/pstyl_utili.c

${OBJECTDIR}/_ext/d8a3b606/stri_utili.o: ../osev_common/stri_utili.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d8a3b606
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d8a3b606/stri_utili.o ../osev_common/stri_utili.c

${OBJECTDIR}/_ext/b1a51e63/adler32.o: ../osev_common/utility/adler32.c
	${MKDIR} -p ${OBJECTDIR}/_ext/b1a51e63
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b1a51e63/adler32.o ../osev_common/utility/adler32.c

${OBJECTDIR}/_ext/b1a51e63/base64.o: ../osev_common/utility/base64.c
	${MKDIR} -p ${OBJECTDIR}/_ext/b1a51e63
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b1a51e63/base64.o ../osev_common/utility/base64.c

${OBJECTDIR}/_ext/b1a51e63/md5.o: ../osev_common/utility/md5.c
	${MKDIR} -p ${OBJECTDIR}/_ext/b1a51e63
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b1a51e63/md5.o ../osev_common/utility/md5.c

${OBJECTDIR}/_ext/b1a51e63/strptime.o: ../osev_common/utility/strptime.c
	${MKDIR} -p ${OBJECTDIR}/_ext/b1a51e63
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b1a51e63/strptime.o ../osev_common/utility/strptime.c

${OBJECTDIR}/_ext/f534dc3f/dmap64.o: ../third_party/dmap64.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/dmap64.o ../third_party/dmap64.c

${OBJECTDIR}/_ext/f534dc3f/linenoise.o: ../third_party/linenoise.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/linenoise.o ../third_party/linenoise.c

${OBJECTDIR}/_ext/f534dc3f/logger.o: ../third_party/logger.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/logger.o ../third_party/logger.c

${OBJECTDIR}/_ext/f534dc3f/memory_utility.o: ../third_party/memory_utility.c
	${MKDIR} -p ${OBJECTDIR}/_ext/f534dc3f
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/f534dc3f/memory_utility.o ../third_party/memory_utility.c

${OBJECTDIR}/clie_bzl.o: clie_bzl.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clie_bzl.o clie_bzl.c

${OBJECTDIR}/dstr_utili.o: dstr_utili.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dstr_utili.o dstr_utili.c

${OBJECTDIR}/excep_msg.o: excep_msg.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/excep_msg.o excep_msg.c

${OBJECTDIR}/hand_method.o: hand_method.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hand_method.o hand_method.c

${OBJECTDIR}/osco_socks.o: osco_socks.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osco_socks.o osco_socks.c

${OBJECTDIR}/osev_clie.o: osev_clie.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_clie.o osev_clie.c

${OBJECTDIR}/pinvo.o: pinvo.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I../osev_common -I../third_party -I../osev_sdkit/storage -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pinvo.o pinvo.c

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
