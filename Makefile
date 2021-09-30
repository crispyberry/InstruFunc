LEVEL = ../../..
LIBRARYNAME = InstruFunc
LOADABLE_MODULE = 1
USEDLIBS =

ifneq ($(REQUIRES_RTTI), 1)
ifneq ($(REQUIRES_EH), 1)
EXPORTED_SYMBOL_FILE = $(PROJ_SRC_DIR)/InstruFunc.exports
endif
endif

include $(LEVEL)/Makefile.common