##### DIRECTORIES
SRC_DIR := src
TEST_DIR := test
INCL_DIR := include
DOC_DIR := doc
BIN_DIR := bin


##### OUTPUT FILES
BIN := morph
ARCHIVE := upem-c-morphing-adam-pacien.tar.gz
LOG := commits.log
REPORT := project-report.pdf


##### CC PARAMS
CC := gcc
CFLAGS := -ansi -Wall -pedantic -std=gnu99 -O2
IFLAGS += -I$(INCL_DIR)
LFLAGS := $(LLFLAGS) -lMLV -lm


##### UTILS
PERCENT := %


##### MAIN TARGETS
.PHONY: all check build objects report clean

all: build check api-doc report;

build: objects $(BIN_DIR)/$(BIN);

.SECONDEXPANSION:
objects: $$(patsubst $(SRC_DIR)/$$(PERCENT).c,$(BIN_DIR)/$$(PERCENT).o,$$(wildcard $(SRC_DIR)/**/*.c));

.SECONDEXPANSION:
check: $$(patsubst $(TEST_DIR)/$$(PERCENT).c,$(BIN_DIR)/$$(PERCENT).test,$$(wildcard $(TEST_DIR)/**/*.c));

report: $(DOC_DIR)/$(REPORT) $(DOC_DIR)/$(LOG);

clean: clean-bin clean-api-doc clean-report clean-archive;

archive: $(ARCHIVE);


##### BINARIES GENERATION
.PRECIOUS: $(BIN_DIR)/%.o $(BIN_DIR)/%/
.PHONY: clean-bin

.SECONDEXPANSION:
$(BIN_DIR)/%.o: $$(patsubst $(BIN_DIR)/$$(PERCENT).o,$(SRC_DIR)/$$(PERCENT).c,$$@) | $$(@D)/
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.SECONDEXPANSION:
$(BIN_DIR)/%.test: $$(patsubst $(BIN_DIR)/$$(PERCENT).test,$(TEST_DIR)/$$(PERCENT).c,$$@) objects | $$(@D)/
	$(CC) $(CFLAGS) $(IFLAGS) $(BIN_DIR)/**/*.o $< -o $@ $(LFLAGS)
	./$@

$(BIN_DIR)/$(BIN): $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) $(IFLAGS) $(BIN_DIR)/**/*.o $< -o $@ $(LFLAGS)

$(BIN_DIR)/%/:
	mkdir -p $(@D)

clean-bin:
	$(RM) -r $(BIN_DIR)/*


##### API DOC
.PHONY: api-doc clean-api-doc

api-doc:
	naturaldocs --rebuild --project $(DOC_DIR)/gen/ --output HTML $(DOC_DIR)/api/ \
	                      --input $(INCL_DIR) --input $(DOC_DIR)/topics/
	$(RM) $(DOC_DIR)/gen/Menu.txt

clean-api-doc:
	$(RM) -r $(DOC_DIR)/api/*


##### REPORT
.PRECIOUS: $(DOC_DIR)/%.pdf $(DOC_DIR)/$(LOG)
.PHONY: clean-report

.SECONDEXPANSION:
$(DOC_DIR)/%.pdf: $$(patsubst $$(PERCENT).pdf,$$(PERCENT).md,$$@)
	pandoc --template $(DOC_DIR)/report-template.tex --number-sections --listings --output $@ $<

$(DOC_DIR)/$(LOG):
	git log > $@

clean-report:
	$(RM) $(DOC_DIR)/$(REPORT)
	$(RM) $(DOC_DIR)/$(LOG)


##### ARCHIVE
.PRECIOUS: $(ARCHIVE)
.PHONY: clean-archive

$(ARCHIVE): check clean report
	touch $@
	tar --exclude-vcs --exclude=./$@ -zcvf ./$@ .

clean-archive:
	$(RM) $(ARCHIVE)
