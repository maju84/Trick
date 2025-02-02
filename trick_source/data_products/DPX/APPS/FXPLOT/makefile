
# $Id: makefile 3163 2013-08-16 22:30:39Z tdowlen $

include ${TRICK_HOME}/makefiles/Makefile.common

RM = rm -rf
CC = cc
CPP = c++

DPX_DIR = ../..

CFLAGS = -g -Wall

INCDIRS = -I${DPX_DIR} -I../../.. -I/usr/include/libxml2 -I$(MOTIF_HOME)/include -I$(TRICK_HOME)/trick_source/data_products/fermi-ware

OBJDIR = object_${TRICK_HOST_CPU}
LIBDIR = ${DPX_DIR}/lib_${TRICK_HOST_CPU}

ifeq ($(TRICK_HOST_TYPE), Linux)
    LIBRTDEF = -lrt
else
    LIBRTDEF =
endif

ifeq ($(TRICK_HOST_TYPE), Darwin)
     INCDIRS += -I/usr/X11/include
     XLIBS = -L${MOTIF_HOME}/lib -lXm -L/usr/X11R6/lib -lXt -lX11
else
     ifneq (${MOTIF_HOME},/usr)
         XLIBS = -L${MOTIF_HOME}/lib64 -L${MOTIF_HOME}/lib
     endif
     XLIBS += -lXm -lXt -lX11
endif

ifneq ($(HDF5),)
HDF5_LIBRARY = -L$(HDF5)/lib -L$(HDF5)/lib64 -lhdf5_hl -lhdf5 -lsz
endif

DP_LIBS       = -L../../../lib_${TRICK_HOST_CPU} -llog -lvar -leqparse -L${TRICK_HOME}/lib_${TRICK_HOST_CPU} -ltrick_units
DPX_LIBS      = -L${DPX_DIR}/lib_${TRICK_HOST_CPU} -lDPC -lDPM
FERMI_WARE_LIB = $(TRICK_HOME)/trick_source/data_products/fermi-ware/object_${TRICK_HOST_CPU}/libfermi.a

ALL_LIBS = $(DPX_LIBS) $(FERMI_WARE_LIB) ${DP_LIBS} ${TRICK_UNIT_LIBS} $(LIBXML) ${HDF5_LIBRARY} -ldl $(FERMI_WARE_DIR)

#############################################################################
##                            MODEL TARGETS                                ##
#############################################################################

C_OBJECT_FILES = $(OBJDIR)/parse_format.o \
    $(OBJDIR)/post_dialog.o

CXX_OBJECT_FILES = $(OBJDIR)/fermi_view.o \
    $(OBJDIR)/fxplot.o \
    $(OBJDIR)/curve_view_node.o \
    $(OBJDIR)/plot_view_node.o \
    $(OBJDIR)/table_view_node.o \
    $(OBJDIR)/page_view_node.o \
    $(OBJDIR)/product_view_node.o

OBJECT_FILES = $(C_OBJECT_FILES) $(CXX_OBJECT_FILES)


all: $(OBJDIR)/fxplot

$(OBJDIR)/fxplot: ${LIBDIR}/libDPM.a ${LIBDIR}/libDPC.a $(OBJECT_FILES)
	@echo "===== Making fxplot ====="
	${CPP} ${CFLAGS} ${INCDIRS} -o $@ $(OBJECT_FILES) ${ALL_LIBS} ${XLIBS} ${LIBRTDEF}

$(C_OBJECT_FILES) : $(OBJDIR)/%.o : %.c
	${CC} ${CFLAGS} ${INCDIRS} -c $< -o $@

$(CXX_OBJECT_FILES) : $(OBJDIR)/%.o : %.cpp
	${CPP} ${CFLAGS} ${INCDIRS} -c $< -o $@

$(OBJECT_FILES) : | $(OBJDIR)

$(OBJDIR) :
	@ mkdir $@

${LIBDIR}/libDPM.a:
	@echo "===== Making libDPM.a ====="
	$(MAKE) -C ${DPX_DIR}/DPM

${LIBDIR}/libDPC.a:
	@echo "===== Making libDPC.a ====="
	$(MAKE) -C ${DPX_DIR}/DPC

clean:
	${RM} $(OBJDIR)

spotless: clean

fxplot: ../../../lib_${TRICK_HOST_CPU}/liblog.a \
  ../../../lib_${TRICK_HOST_CPU}/libvar.a \
  ../../../lib_${TRICK_HOST_CPU}/libeqparse.a


# Dependencies
