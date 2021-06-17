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
CND_PLATFORM=None-Linux
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
	${OBJECTDIR}/OSEVConne.o \
	${OBJECTDIR}/OSEVContain.o \
	${OBJECTDIR}/OSVBase.o \
	${OBJECTDIR}/clie_bzl.o \
	${OBJECTDIR}/clie_obje.o \
	${OBJECTDIR}/excep_msg.o \
	${OBJECTDIR}/hand_method.o \
	${OBJECTDIR}/osco_socks.o \
	${OBJECTDIR}/osev_clie_cpp.o \
	${OBJECTDIR}/osev_common/action_hmap.o \
	${OBJECTDIR}/osev_common/checksum.o \
	${OBJECTDIR}/osev_common/encoding.o \
	${OBJECTDIR}/osev_common/hash_table_ex.o \
	${OBJECTDIR}/osev_common/linux_os.o \
	${OBJECTDIR}/osev_common/md5.o \
	${OBJECTDIR}/osev_common/oid.o \
	${OBJECTDIR}/osev_common/paras_style.o \
	${OBJECTDIR}/osev_common/string_utility.o \
	${OBJECTDIR}/pinvo.o \
	${OBJECTDIR}/stri_utili.o


# C Compiler Flags
CFLAGS=-Wall -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64

# CC Compiler Flags
CCFLAGS=-Wall -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64
CXXFLAGS=-Wall -D_LARGEFILE64_SOURCE -D_FILEOFFSET_BITS==64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosclie_cpp.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosclie_cpp.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libosclie_cpp.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/OSEVConne.o: OSEVConne.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/OSEVConne.o OSEVConne.cpp

${OBJECTDIR}/OSEVContain.o: OSEVContain.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/OSEVContain.o OSEVContain.cpp

${OBJECTDIR}/OSVBase.o: OSVBase.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/OSVBase.o OSVBase.cpp

${OBJECTDIR}/clie_bzl.o: clie_bzl.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clie_bzl.o clie_bzl.c

${OBJECTDIR}/clie_obje.o: clie_obje.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clie_obje.o clie_obje.c

${OBJECTDIR}/excep_msg.o: excep_msg.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/excep_msg.o excep_msg.c

${OBJECTDIR}/hand_method.o: hand_method.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hand_method.o hand_method.c

${OBJECTDIR}/osco_socks.o: osco_socks.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osco_socks.o osco_socks.c

${OBJECTDIR}/osev_clie_cpp.o: osev_clie_cpp.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_clie_cpp.o osev_clie_cpp.cpp

${OBJECTDIR}/osev_common/action_hmap.o: osev_common/action_hmap.c
	${MKDIR} -p ${OBJECTDIR}/osev_common
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_common/action_hmap.o osev_common/action_hmap.c

${OBJECTDIR}/osev_common/checksum.o: osev_common/checksum.c
	${MKDIR} -p ${OBJECTDIR}/osev_common
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_common/checksum.o osev_common/checksum.c

${OBJECTDIR}/osev_common/encoding.o: osev_common/encoding.c
	${MKDIR} -p ${OBJECTDIR}/osev_common
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_common/encoding.o osev_common/encoding.c

${OBJECTDIR}/osev_common/hash_table_ex.o: osev_common/hash_table_ex.c
	${MKDIR} -p ${OBJECTDIR}/osev_common
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_common/hash_table_ex.o osev_common/hash_table_ex.c

${OBJECTDIR}/osev_common/linux_os.o: osev_common/linux_os.c
	${MKDIR} -p ${OBJECTDIR}/osev_common
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_common/linux_os.o osev_common/linux_os.c

${OBJECTDIR}/osev_common/md5.o: osev_common/md5.c
	${MKDIR} -p ${OBJECTDIR}/osev_common
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_common/md5.o osev_common/md5.c

${OBJECTDIR}/osev_common/oid.o: osev_common/oid.c
	${MKDIR} -p ${OBJECTDIR}/osev_common
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_common/oid.o osev_common/oid.c

${OBJECTDIR}/osev_common/paras_style.o: osev_common/paras_style.c
	${MKDIR} -p ${OBJECTDIR}/osev_common
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_common/paras_style.o osev_common/paras_style.c

${OBJECTDIR}/osev_common/string_utility.o: osev_common/string_utility.c
	${MKDIR} -p ${OBJECTDIR}/osev_common
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/osev_common/string_utility.o osev_common/string_utility.c

${OBJECTDIR}/pinvo.o: pinvo.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pinvo.o pinvo.c

${OBJECTDIR}/stri_utili.o: stri_utili.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stri_utili.o stri_utili.c

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
