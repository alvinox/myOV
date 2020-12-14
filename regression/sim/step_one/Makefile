ifeq ($(OVPATH), )
    $(error cannot find environment variable: OVPATH)
endif

include $(OVPATH)/simulator/Makefile.include

CC       = clang
OBJDIR   = obj
BUILDDIR = build

HFILES = sim.h \

CFILES = sim.c \

CPLUSPLUSFILES =  \

DEPS = $(HFILES) Makefile 

OBJS = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(CFILES)))
OBJ_OWNS = $(patsubst %.o, %$(OBJ_TYPE).o, $(OBJS))

OBJS_PLUSPLUS = $(addprefix $(OBJDIR)/, $(patsubst %.cc, %.o, $(CPLUSPLUSFILES)))
OBJ_OWNS_PLUSPLUS = $(patsubst %.o, %$(OBJ_TYPE).o, $(OBJS_PLUSPLUS))

INC = -I./ \
      -I$(OVPATH)/simulator/$(INFRA_DIR)

CFLAGS += $(INC)

LDFLAGS  += -L$(OVPATH)/simulator/$(BUILD_DIR)
LIB_DEPS += -l$(MODULE)

EXEC = "step_one"

.PHONY: $(EXEC)
$(EXEC): $(OBJDIR) $(OBJ_OWNS) $(OBJ_OWNS_PLUSPLUS)
	$(CC) $(OPTIONS) $(OBJ_OWNS) $(OBJ_OWNS_PLUSPLUS) $(LDFLAGS) $(LIB_DEPS) -o $(EXEC)

$(OBJDIR):
	@if [ ! -d "$(OBJDIR)" ]; then echo "mkdir -p $(OBJDIR)"; mkdir -p "$(OBJDIR)"; fi

$(OBJ_OWNS):$(OBJDIR)/%$(OBJ_TYPE).o:./%.c $(DEPS)
	$(CC) -c $(OPTIONS) $(CFLAGS) $< -o $(@)

$(OBJ_OWNS_PLUSPLUS):$(OBJDIR)/%$(OBJ_TYPE).o:./%.cc $(DEPS)
	$(CC) -c $(OPTIONS) $(CFLAGS) $< -o $(@)

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
