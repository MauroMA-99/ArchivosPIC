#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/3.0Labo3_Keypad.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/3.0Labo3_Keypad.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=myLibrary/lcd_2x16.c myLibrary/keypad_4x4.c myLibrary/mainLab3_4.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/myLibrary/lcd_2x16.o ${OBJECTDIR}/myLibrary/keypad_4x4.o ${OBJECTDIR}/myLibrary/mainLab3_4.o
POSSIBLE_DEPFILES=${OBJECTDIR}/myLibrary/lcd_2x16.o.d ${OBJECTDIR}/myLibrary/keypad_4x4.o.d ${OBJECTDIR}/myLibrary/mainLab3_4.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/myLibrary/lcd_2x16.o ${OBJECTDIR}/myLibrary/keypad_4x4.o ${OBJECTDIR}/myLibrary/mainLab3_4.o

# Source Files
SOURCEFILES=myLibrary/lcd_2x16.c myLibrary/keypad_4x4.c myLibrary/mainLab3_4.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega328pb"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/3.0Labo3_Keypad.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega328PB
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/myLibrary/lcd_2x16.o: myLibrary/lcd_2x16.c  .generated_files/18afaf0b63150ea1ce7cedaa32fd328ba5cef92d.flag .generated_files/906de2893ca0785e052ea1a39d6244a613469e43.flag
	@${MKDIR} "${OBJECTDIR}/myLibrary" 
	@${RM} ${OBJECTDIR}/myLibrary/lcd_2x16.o.d 
	@${RM} ${OBJECTDIR}/myLibrary/lcd_2x16.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/myLibrary/lcd_2x16.o.d" -MT "${OBJECTDIR}/myLibrary/lcd_2x16.o.d" -MT ${OBJECTDIR}/myLibrary/lcd_2x16.o  -o ${OBJECTDIR}/myLibrary/lcd_2x16.o myLibrary/lcd_2x16.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/myLibrary/keypad_4x4.o: myLibrary/keypad_4x4.c  .generated_files/3a0166af90b7f1dbe272b8e71b594c33927c2b06.flag .generated_files/906de2893ca0785e052ea1a39d6244a613469e43.flag
	@${MKDIR} "${OBJECTDIR}/myLibrary" 
	@${RM} ${OBJECTDIR}/myLibrary/keypad_4x4.o.d 
	@${RM} ${OBJECTDIR}/myLibrary/keypad_4x4.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/myLibrary/keypad_4x4.o.d" -MT "${OBJECTDIR}/myLibrary/keypad_4x4.o.d" -MT ${OBJECTDIR}/myLibrary/keypad_4x4.o  -o ${OBJECTDIR}/myLibrary/keypad_4x4.o myLibrary/keypad_4x4.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/myLibrary/mainLab3_4.o: myLibrary/mainLab3_4.c  .generated_files/c55580f765d2fda0e20f4db523cb02ba5b22e805.flag .generated_files/906de2893ca0785e052ea1a39d6244a613469e43.flag
	@${MKDIR} "${OBJECTDIR}/myLibrary" 
	@${RM} ${OBJECTDIR}/myLibrary/mainLab3_4.o.d 
	@${RM} ${OBJECTDIR}/myLibrary/mainLab3_4.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/myLibrary/mainLab3_4.o.d" -MT "${OBJECTDIR}/myLibrary/mainLab3_4.o.d" -MT ${OBJECTDIR}/myLibrary/mainLab3_4.o  -o ${OBJECTDIR}/myLibrary/mainLab3_4.o myLibrary/mainLab3_4.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/myLibrary/lcd_2x16.o: myLibrary/lcd_2x16.c  .generated_files/b03704e5af82ad316aefc4f1738c34b5905dec62.flag .generated_files/906de2893ca0785e052ea1a39d6244a613469e43.flag
	@${MKDIR} "${OBJECTDIR}/myLibrary" 
	@${RM} ${OBJECTDIR}/myLibrary/lcd_2x16.o.d 
	@${RM} ${OBJECTDIR}/myLibrary/lcd_2x16.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/myLibrary/lcd_2x16.o.d" -MT "${OBJECTDIR}/myLibrary/lcd_2x16.o.d" -MT ${OBJECTDIR}/myLibrary/lcd_2x16.o  -o ${OBJECTDIR}/myLibrary/lcd_2x16.o myLibrary/lcd_2x16.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/myLibrary/keypad_4x4.o: myLibrary/keypad_4x4.c  .generated_files/8034aa4709714ad64f1e841ca5c0ac1633eae895.flag .generated_files/906de2893ca0785e052ea1a39d6244a613469e43.flag
	@${MKDIR} "${OBJECTDIR}/myLibrary" 
	@${RM} ${OBJECTDIR}/myLibrary/keypad_4x4.o.d 
	@${RM} ${OBJECTDIR}/myLibrary/keypad_4x4.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/myLibrary/keypad_4x4.o.d" -MT "${OBJECTDIR}/myLibrary/keypad_4x4.o.d" -MT ${OBJECTDIR}/myLibrary/keypad_4x4.o  -o ${OBJECTDIR}/myLibrary/keypad_4x4.o myLibrary/keypad_4x4.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/myLibrary/mainLab3_4.o: myLibrary/mainLab3_4.c  .generated_files/808b1d8bc53f9c00b013a73cf724f089da73aa7e.flag .generated_files/906de2893ca0785e052ea1a39d6244a613469e43.flag
	@${MKDIR} "${OBJECTDIR}/myLibrary" 
	@${RM} ${OBJECTDIR}/myLibrary/mainLab3_4.o.d 
	@${RM} ${OBJECTDIR}/myLibrary/mainLab3_4.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/myLibrary/mainLab3_4.o.d" -MT "${OBJECTDIR}/myLibrary/mainLab3_4.o.d" -MT ${OBJECTDIR}/myLibrary/mainLab3_4.o  -o ${OBJECTDIR}/myLibrary/mainLab3_4.o myLibrary/mainLab3_4.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/3.0Labo3_Keypad.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega328pb ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist\${CND_CONF}\${IMAGE_TYPE}\3.0Labo3_Keypad.X.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/3.0Labo3_Keypad.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/3.0Labo3_Keypad.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega328pb ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist\${CND_CONF}\${IMAGE_TYPE}\3.0Labo3_Keypad.X.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/3.0Labo3_Keypad.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/3.0Labo3_Keypad.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/3.0Labo3_Keypad.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
