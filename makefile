##### DIRECTORIES
SRC_DIR := src
TEST_DIR := test
INCL_DIR := include
DOC_DIR := doc
BIN_DIR := bin


##### CC PARAMS
CC := gcc
CFLAGS := -ansi -Wall -pedantic -std=gnu99 -O2
IFLAGS += -I$(INCL_DIR)
LFLAGS := $(LLFLAGS) -lMLV -lm


##### UTILS
PERCENT := %


##### MAIN TARGETS
.PHONY: all test source report clean

all: source test api-doc report;

.SECONDEXPANSION:
source: $$(patsubst $(SRC_DIR)/$$(PERCENT).c,$(BIN_DIR)/$$(PERCENT).o,$$(wildcard $(SRC_DIR)/**/*.c));

.SECONDEXPANSION:
test: $$(patsubst $(TEST_DIR)/$$(PERCENT).c,$(BIN_DIR)/$$(PERCENT).test,$$(wildcard $(TEST_DIR)/**/*.c));

report: $(DOC_DIR)/project-report.pdf;

clean: clean-bin clean-api-doc clean-report;


##### BINARIES GENERATION
.PRECIOUS: $(BIN_DIR)/%.o $(BIN_DIR)/%/
.PHONY: clean-bin

.SECONDEXPANSION:
$(BIN_DIR)/%.o: $$(patsubst $(BIN_DIR)/$$(PERCENT).o,$(SRC_DIR)/$$(PERCENT).c,$$@) | $$(@D)/
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.SECONDEXPANSION:
$(BIN_DIR)/%.test: $$(patsubst $(BIN_DIR)/$$(PERCENT).test,$(TEST_DIR)/$$(PERCENT).c,$$@) source | $$(@D)/
	$(CC) $(CFLAGS) $(IFLAGS) $(BIN_DIR)/**/*.o $< -o $@ $(LFLAGS)
	./$@

$(BIN_DIR)/%/:
	mkdir -p $(@D)

clean-bin:
	$(RM) -r $(BIN_DIR)/*


##### API DOC
.PHONY: api-doc clean-api-doc

api-doc:
	naturaldocs --project $(DOC_DIR)/gen/ --output HTML $(DOC_DIR)/api/ \
	            --input $(INCLUDE_DIR) --input $(DOC_DIR)/topics/
	$(RM) $(DOC_DIR)/gen/Menu.txt

clean-api-doc:
	$(RM) -r $(DOC_DIR)/api/*


##### REPORT
.PRECIOUS: $(DOC_DIR)/%.pdf
.PHONY: clean-report

.SECONDEXPANSION:
$(DOC_DIR)/%.pdf: $$(patsubst $$(PERCENT).pdf,$$(PERCENT).md,$$@)
	pandoc --template $(DOC_DIR)/report-template.tex --number-sections --listings --output $@ $<

clean-report:
	$(RM) -r $(DOC_DIR)/project-report.pdf
