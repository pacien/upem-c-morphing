api-doc:
	$(eval TMPDIR := $(shell mktemp -d))
	naturaldocs --project $(TMPDIR) --input include/ --input doc/topics/ --output HTML doc/api/
	$(RM) -r $(TMPDIR)

report:
	pandoc --template doc/report-template.tex --number-sections --listings \
	       --output doc/project-report.pdf doc/project-report.md
