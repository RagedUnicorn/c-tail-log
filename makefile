APP = ctail
WRITER = writer

SRCEXT = c
SRCDIR = src
SRCDIR_TOOLS = tools
OBJDIR = obj
BINDIR = bin

SRCS := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS := $(shell find $(SRCDIR) -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
SRCS_TOOLS := $(shell find $(SRCDIR_TOOLS) -name '*.$(SRCEXT)')
SRCDIRS_TOOLS := $(shell find $(SRCDIR_TOOLS) -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
OBJS := $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS))
OBJS_TOOLS := $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS_TOOLS))

DEBUG = -g
CFLAGS = -std=c90 -Wall -pedantic -ansi -c $(DEBUG)

.PHONY: all clean distclean

all: $(BINDIR)/$(APP)
writer: $(BINDIR)/$(WRITER)

$(BINDIR)/$(APP): buildapprepo $(OBJS)
	@mkdir -p `dirname $@`
	@echo "Linking $@..."
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

${BINDIR}/$(WRITER): buildtoolrepo $(OBJS_TOOLS)
	@mkdir -p `dirname $@`
	@echo "Linking $@..."
	@$(CC) ${OBJS_TOOLS} $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.$(SRCEXT)
	@echo "Generating dependencies for $<..."
	@$(call make-depend,$<,$@,$(subst .o,.d,$@))
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) -r $(OBJDIR)

distclean: clean
	$(RM) -r $(BINDIR)

buildapprepo:
	@$(call make-app-repo)

buildtoolrepo:
	@$(call make-tool-repo)

define make-tool-repo
	for dir in $(SRCDIRS_TOOLS); \
		do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
endef

define make-app-repo
	for dir in $(SRCDIRS); \
		do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
endef
