# Hello World Project Makefile

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = 

# Directories
SRCDIR = hello_world
OBJDIR = obj
BINDIR = bin
DOCDIR = docs

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Target executable
TARGET = $(BINDIR)/hello_world

# Documentation files
DOCS = README.md API_DOCUMENTATION.md

# Default target
all: $(TARGET)

# Create directories
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link executable
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Install (copy to system path)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	rm -f /usr/local/bin/hello_world

# Run the program
run: $(TARGET)
	./$(TARGET)

# Test the program
test: $(TARGET)
	@echo "Running basic test..."
	@./$(TARGET) | grep -q "hello world" && echo "✓ Test passed" || echo "✗ Test failed"

# Generate documentation
docs: $(DOCS)
	@echo "Documentation files:"
	@for doc in $(DOCS); do echo "  - $$doc"; done

# Check code style
style:
	@echo "Checking code style..."
	@if command -v clang-format >/dev/null 2>&1; then \
		clang-format --dry-run --Werror $(SRCDIR)/*.c $(SRCDIR)/*.h; \
	else \
		echo "clang-format not found, skipping style check"; \
	fi

# Static analysis
analyze:
	@echo "Running static analysis..."
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c99 $(SRCDIR)/; \
	else \
		echo "cppcheck not found, skipping static analysis"; \
	fi

# Memory check with valgrind
memcheck: $(TARGET)
	@echo "Running memory check..."
	@if command -v valgrind >/dev/null 2>&1; then \
		valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET); \
	else \
		echo "valgrind not found, skipping memory check"; \
	fi

# Package for distribution
package: clean all docs
	@echo "Creating package..."
	@mkdir -p hello_world-$(shell date +%Y%m%d)
	@cp -r $(SRCDIR) hello_world-$(shell date +%Y%m%d)/
	@cp $(DOCS) hello_world-$(shell date +%Y%m%d)/
	@cp Makefile hello_world-$(shell date +%Y%m%d)/
	@tar -czf hello_world-$(shell date +%Y%m%d).tar.gz hello_world-$(shell date +%Y%m%d)/
	@rm -rf hello_world-$(shell date +%Y%m%d)
	@echo "Package created: hello_world-$(shell date +%Y%m%d).tar.gz"

# Show help
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  install   - Install to system path"
	@echo "  uninstall - Remove from system path"
	@echo "  run       - Build and run the program"
	@echo "  test      - Run basic tests"
	@echo "  docs      - Show documentation files"
	@echo "  style     - Check code style"
	@echo "  analyze   - Run static analysis"
	@echo "  memcheck  - Run memory check with valgrind"
	@echo "  package   - Create distribution package"
	@echo "  help      - Show this help message"

# Phony targets
.PHONY: all clean install uninstall run test docs style analyze memcheck package help

# Dependencies
-include $(OBJECTS:.o=.d)

# Generate dependency files
$(OBJDIR)/%.d: $(SRCDIR)/%.c | $(OBJDIR)
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(OBJDIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$