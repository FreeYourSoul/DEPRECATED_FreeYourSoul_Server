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
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/MemoryManagement/CharacterMemManager.o \
	${OBJECTDIR}/MemoryManagement/InstanceElemDODMemManager.o \
	${OBJECTDIR}/MemoryManagement/PlayerDODMemManager.o \
	${OBJECTDIR}/MemoryManagement/PlayersBagContentDODMemManager.o \
	${OBJECTDIR}/Server/ActionDispatcher.o \
	${OBJECTDIR}/Server/ActionThreads/DatabaseAction.o \
	${OBJECTDIR}/Server/ActionThreads/FightAction.o \
	${OBJECTDIR}/Server/ActionThreads/InventoryAction.o \
	${OBJECTDIR}/Server/ActionThreads/MapAction.o \
	${OBJECTDIR}/Server/Authenticator.o \
	${OBJECTDIR}/Server/Logs/Logs.o \
	${OBJECTDIR}/Server/Map/InstanceElem.o \
	${OBJECTDIR}/Server/Map/Map.o \
	${OBJECTDIR}/Server/Player/Character.o \
	${OBJECTDIR}/Server/Player/Item/MagicAsset.o \
	${OBJECTDIR}/Server/Player/Item/StatAsset.o \
	${OBJECTDIR}/Server/Player/PlayerBags.o \
	${OBJECTDIR}/Server/Player/PlayerBagsContents.o \
	${OBJECTDIR}/Server/Player/PlayerPosition.o \
	${OBJECTDIR}/Server/Player/Team.o \
	${OBJECTDIR}/Server/ServerProxy.o \
	${OBJECTDIR}/Server/ServerWorker.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11 -g3 -pedantic -Wall -Wextra
CXXFLAGS=-std=c++11 -g3 -pedantic -Wall -Wextra

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/freeyoursoulserver

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/freeyoursoulserver: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	clang++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/freeyoursoulserver ${OBJECTFILES} ${LDLIBSOPTIONS} -lzmq -pthread

${OBJECTDIR}/MemoryManagement/CharacterMemManager.o: MemoryManagement/CharacterMemManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/MemoryManagement
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MemoryManagement/CharacterMemManager.o MemoryManagement/CharacterMemManager.cpp

${OBJECTDIR}/MemoryManagement/InstanceElemDODMemManager.o: MemoryManagement/InstanceElemDODMemManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/MemoryManagement
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MemoryManagement/InstanceElemDODMemManager.o MemoryManagement/InstanceElemDODMemManager.cpp

${OBJECTDIR}/MemoryManagement/PlayerDODMemManager.o: MemoryManagement/PlayerDODMemManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/MemoryManagement
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MemoryManagement/PlayerDODMemManager.o MemoryManagement/PlayerDODMemManager.cpp

${OBJECTDIR}/MemoryManagement/PlayersBagContentDODMemManager.o: MemoryManagement/PlayersBagContentDODMemManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/MemoryManagement
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MemoryManagement/PlayersBagContentDODMemManager.o MemoryManagement/PlayersBagContentDODMemManager.cpp

${OBJECTDIR}/Server/ActionDispatcher.o: Server/ActionDispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/ActionDispatcher.o Server/ActionDispatcher.cpp

${OBJECTDIR}/Server/ActionThreads/DatabaseAction.o: Server/ActionThreads/DatabaseAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/ActionThreads
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/ActionThreads/DatabaseAction.o Server/ActionThreads/DatabaseAction.cpp

${OBJECTDIR}/Server/ActionThreads/FightAction.o: Server/ActionThreads/FightAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/ActionThreads
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/ActionThreads/FightAction.o Server/ActionThreads/FightAction.cpp

${OBJECTDIR}/Server/ActionThreads/InventoryAction.o: Server/ActionThreads/InventoryAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/ActionThreads
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/ActionThreads/InventoryAction.o Server/ActionThreads/InventoryAction.cpp

${OBJECTDIR}/Server/ActionThreads/MapAction.o: Server/ActionThreads/MapAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/ActionThreads
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/ActionThreads/MapAction.o Server/ActionThreads/MapAction.cpp

${OBJECTDIR}/Server/Authenticator.o: Server/Authenticator.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Authenticator.o Server/Authenticator.cpp

${OBJECTDIR}/Server/Logs/Logs.o: Server/Logs/Logs.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/Logs
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Logs/Logs.o Server/Logs/Logs.cpp

${OBJECTDIR}/Server/Map/InstanceElem.o: Server/Map/InstanceElem.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/Map
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Map/InstanceElem.o Server/Map/InstanceElem.cpp

${OBJECTDIR}/Server/Map/Map.o: Server/Map/Map.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/Map
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Map/Map.o Server/Map/Map.cpp

${OBJECTDIR}/Server/Player/Character.o: Server/Player/Character.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/Player
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Player/Character.o Server/Player/Character.cpp

${OBJECTDIR}/Server/Player/Item/MagicAsset.o: Server/Player/Item/MagicAsset.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/Player/Item
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Player/Item/MagicAsset.o Server/Player/Item/MagicAsset.cpp

${OBJECTDIR}/Server/Player/Item/StatAsset.o: Server/Player/Item/StatAsset.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/Player/Item
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Player/Item/StatAsset.o Server/Player/Item/StatAsset.cpp

${OBJECTDIR}/Server/Player/PlayerBags.o: Server/Player/PlayerBags.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/Player
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Player/PlayerBags.o Server/Player/PlayerBags.cpp

${OBJECTDIR}/Server/Player/PlayerBagsContents.o: Server/Player/PlayerBagsContents.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/Player
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Player/PlayerBagsContents.o Server/Player/PlayerBagsContents.cpp

${OBJECTDIR}/Server/Player/PlayerPosition.o: Server/Player/PlayerPosition.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/Player
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Player/PlayerPosition.o Server/Player/PlayerPosition.cpp

${OBJECTDIR}/Server/Player/Team.o: Server/Player/Team.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server/Player
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/Player/Team.o Server/Player/Team.cpp

${OBJECTDIR}/Server/ServerProxy.o: Server/ServerProxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/ServerProxy.o Server/ServerProxy.cpp

${OBJECTDIR}/Server/ServerWorker.o: Server/ServerWorker.cpp 
	${MKDIR} -p ${OBJECTDIR}/Server
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Server/ServerWorker.o Server/ServerWorker.cpp

${OBJECTDIR}/main.o: main.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/freeyoursoulserver

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
