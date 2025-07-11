# Hello World API Documentation

## Table of Contents
1. [Overview](#overview)
2. [Data Structures](#data-structures)
3. [Error Handling](#error-handling)
4. [Core API Functions](#core-api-functions)
5. [Configuration API](#configuration-api)
6. [Utility Functions](#utility-functions)
7. [Advanced Features](#advanced-features)
8. [Usage Examples](#usage-examples)
9. [Best Practices](#best-practices)

## Overview

The Hello World API provides a comprehensive set of functions for creating, configuring, and displaying hello world messages. The API is designed to be simple to use while offering advanced features for more complex applications.

### Key Features
- Simple initialization and cleanup
- Configurable message output
- File I/O support
- Color output support
- Error handling
- Configuration management

## Data Structures

### `hello_world_config_t`

Configuration structure for the hello world system.

```c
typedef struct {
    char* message;        // Custom message to display
    int verbose;          // Enable verbose output
    char* output_file;    // Output file path (NULL for stdout)
    int use_colors;       // Enable color output
} hello_world_config_t;
```

**Fields:**
- `message`: Custom message string (NULL for default "hello world")
- `verbose`: Non-zero to enable verbose output
- `output_file`: File path for output redirection (NULL for stdout)
- `use_colors`: Non-zero to enable ANSI color codes

**Example:**
```c
hello_world_config_t config = {
    .message = "Hello, Universe!",
    .verbose = 1,
    .output_file = NULL,
    .use_colors = 1
};
```

## Error Handling

### `hello_world_error_t`

Error codes returned by API functions.

```c
typedef enum {
    HELLO_WORLD_SUCCESS = 0,              // Operation successful
    HELLO_WORLD_ERROR_NULL_POINTER = -1,  // NULL pointer provided
    HELLO_WORLD_ERROR_INVALID_CONFIG = -2, // Invalid configuration
    HELLO_WORLD_ERROR_FILE_IO = -3,       // File I/O error
    HELLO_WORLD_ERROR_MEMORY = -4         // Memory allocation error
} hello_world_error_t;
```

**Error Handling Example:**
```c
int result = hello_world_print("Hello");
if (result != HELLO_WORLD_SUCCESS) {
    printf("Error: %s\n", hello_world_get_error_message(result));
}
```

## Core API Functions

### `hello_world_init()`

Initialize the hello world system.

**Signature:**
```c
int hello_world_init(const hello_world_config_t* config);
```

**Parameters:**
- `config`: Configuration structure (NULL for defaults)

**Returns:**
- `HELLO_WORLD_SUCCESS` on success
- Error code on failure

**Example:**
```c
// Initialize with default settings
int result = hello_world_init(NULL);
if (result != HELLO_WORLD_SUCCESS) {
    fprintf(stderr, "Failed to initialize: %s\n", 
            hello_world_get_error_message(result));
    return 1;
}

// Initialize with custom configuration
hello_world_config_t config = {
    .message = "Custom message",
    .verbose = 1
};
result = hello_world_init(&config);
```

### `hello_world_cleanup()`

Clean up resources used by the hello world system.

**Signature:**
```c
int hello_world_cleanup(void);
```

**Returns:**
- `HELLO_WORLD_SUCCESS` on success
- Error code on failure

**Example:**
```c
// Always cleanup before exit
int result = hello_world_cleanup();
if (result != HELLO_WORLD_SUCCESS) {
    fprintf(stderr, "Cleanup failed: %s\n", 
            hello_world_get_error_message(result));
}
```

### `hello_world_print()`

Print a hello world message.

**Signature:**
```c
int hello_world_print(const char* message);
```

**Parameters:**
- `message`: Custom message (NULL for default)

**Returns:**
- `HELLO_WORLD_SUCCESS` on success
- Error code on failure

**Example:**
```c
// Print default message
hello_world_print(NULL);

// Print custom message
hello_world_print("Hello, World!");

// Print with error handling
int result = hello_world_print("Custom message");
if (result != HELLO_WORLD_SUCCESS) {
    printf("Print failed: %s\n", hello_world_get_error_message(result));
}
```

### `hello_world_printf()`

Print a formatted hello world message.

**Signature:**
```c
int hello_world_printf(const char* format, ...);
```

**Parameters:**
- `format`: Format string (printf-style)
- `...`: Variable arguments

**Returns:**
- `HELLO_WORLD_SUCCESS` on success
- Error code on failure

**Example:**
```c
// Print formatted message
hello_world_printf("Hello, %s!", "World");

// Print with multiple arguments
hello_world_printf("Hello from %s version %s", "API", "1.0.0");

// Print with numbers
hello_world_printf("Count: %d, Message: %s", 42, "Hello");
```

### `hello_world_get_default_message()`

Get the default hello world message.

**Signature:**
```c
const char* hello_world_get_default_message(void);
```

**Returns:**
- Pointer to default message string

**Example:**
```c
const char* default_msg = hello_world_get_default_message();
printf("Default message: %s\n", default_msg);
```

### `hello_world_set_message()`

Set a custom hello world message.

**Signature:**
```c
int hello_world_set_message(const char* message);
```

**Parameters:**
- `message`: New message to use

**Returns:**
- `HELLO_WORLD_SUCCESS` on success
- Error code on failure

**Example:**
```c
// Set custom message
int result = hello_world_set_message("Hello, Universe!");
if (result == HELLO_WORLD_SUCCESS) {
    hello_world_print(NULL);  // Will print the new message
}
```

## Configuration API

### `hello_world_config_create()`

Create a default configuration structure.

**Signature:**
```c
hello_world_config_t* hello_world_config_create(void);
```

**Returns:**
- Pointer to new configuration (must be freed)
- NULL on memory allocation failure

**Example:**
```c
hello_world_config_t* config = hello_world_config_create();
if (config != NULL) {
    config->message = strdup("Custom message");
    config->verbose = 1;
    
    hello_world_init(config);
    hello_world_config_free(config);
}
```

### `hello_world_config_free()`

Free a configuration structure.

**Signature:**
```c
void hello_world_config_free(hello_world_config_t* config);
```

**Parameters:**
- `config`: Configuration to free

**Example:**
```c
hello_world_config_t* config = hello_world_config_create();
// ... use config ...
hello_world_config_free(config);
```

### `hello_world_config_load()`

Load configuration from file.

**Signature:**
```c
hello_world_config_t* hello_world_config_load(const char* filename);
```

**Parameters:**
- `filename`: Configuration file path

**Returns:**
- Pointer to loaded configuration (must be freed)
- NULL on error

**Example:**
```c
hello_world_config_t* config = hello_world_config_load("config.txt");
if (config != NULL) {
    hello_world_init(config);
    hello_world_config_free(config);
}
```

### `hello_world_config_save()`

Save configuration to file.

**Signature:**
```c
int hello_world_config_save(const hello_world_config_t* config, const char* filename);
```

**Parameters:**
- `config`: Configuration to save
- `filename`: Output file path

**Returns:**
- `HELLO_WORLD_SUCCESS` on success
- Error code on failure

**Example:**
```c
hello_world_config_t* config = hello_world_config_create();
config->message = strdup("Saved message");
config->verbose = 1;

int result = hello_world_config_save(config, "my_config.txt");
if (result != HELLO_WORLD_SUCCESS) {
    printf("Save failed: %s\n", hello_world_get_error_message(result));
}

hello_world_config_free(config);
```

## Utility Functions

### `hello_world_get_version()`

Get the API version string.

**Signature:**
```c
const char* hello_world_get_version(void);
```

**Returns:**
- Version string in format "major.minor.patch"

**Example:**
```c
printf("Hello World API Version: %s\n", hello_world_get_version());
```

### `hello_world_get_error_message()`

Get human-readable error message.

**Signature:**
```c
const char* hello_world_get_error_message(int error_code);
```

**Parameters:**
- `error_code`: Error code from API function

**Returns:**
- Human-readable error message

**Example:**
```c
int result = hello_world_print(NULL);
if (result != HELLO_WORLD_SUCCESS) {
    printf("Error: %s\n", hello_world_get_error_message(result));
}
```

### `hello_world_is_initialized()`

Check if the hello world system is initialized.

**Signature:**
```c
int hello_world_is_initialized(void);
```

**Returns:**
- 1 if initialized
- 0 if not initialized

**Example:**
```c
if (!hello_world_is_initialized()) {
    hello_world_init(NULL);
}
```

## Advanced Features

### `hello_world_print_colored()`

Print hello world message with colors.

**Signature:**
```c
int hello_world_print_colored(const char* message, const char* color);
```

**Parameters:**
- `message`: Message to print
- `color`: Color name ("red", "green", "blue", "yellow", "cyan", "magenta")

**Returns:**
- `HELLO_WORLD_SUCCESS` on success
- Error code on failure

**Example:**
```c
// Print in different colors
hello_world_print_colored("Hello", "red");
hello_world_print_colored("World", "green");
hello_world_print_colored("!", "blue");
```

### `hello_world_print_to_file()`

Print hello world message to file.

**Signature:**
```c
int hello_world_print_to_file(const char* message, const char* filename);
```

**Parameters:**
- `message`: Message to print
- `filename`: Output file path

**Returns:**
- `HELLO_WORLD_SUCCESS` on success
- Error code on failure

**Example:**
```c
// Print to file
int result = hello_world_print_to_file("Hello, File!", "output.txt");
if (result != HELLO_WORLD_SUCCESS) {
    printf("File write failed: %s\n", hello_world_get_error_message(result));
}
```

### `hello_world_print_repeat()`

Print hello world message multiple times.

**Signature:**
```c
int hello_world_print_repeat(const char* message, int count);
```

**Parameters:**
- `message`: Message to print
- `count`: Number of times to print

**Returns:**
- `HELLO_WORLD_SUCCESS` on success
- Error code on failure

**Example:**
```c
// Print message 5 times
hello_world_print_repeat("Hello", 5);

// Print with error handling
int result = hello_world_print_repeat("Test", 10);
if (result != HELLO_WORLD_SUCCESS) {
    printf("Repeat failed: %s\n", hello_world_get_error_message(result));
}
```

## Usage Examples

### Basic Usage

```c
#include "hello_world.h"

int main(void) {
    // Initialize with defaults
    if (hello_world_init(NULL) != HELLO_WORLD_SUCCESS) {
        return 1;
    }
    
    // Print default message
    hello_world_print(NULL);
    
    // Cleanup
    hello_world_cleanup();
    return 0;
}
```

### Advanced Usage

```c
#include "hello_world.h"

int main(void) {
    // Create custom configuration
    hello_world_config_t* config = hello_world_config_create();
    if (config == NULL) {
        return 1;
    }
    
    config->message = strdup("Hello, Advanced World!");
    config->verbose = 1;
    config->use_colors = 1;
    
    // Initialize with custom config
    if (hello_world_init(config) != HELLO_WORLD_SUCCESS) {
        hello_world_config_free(config);
        return 1;
    }
    
    // Use various features
    hello_world_print(NULL);
    hello_world_printf("Formatted: %s", "message");
    hello_world_print_colored("Colored", "green");
    hello_world_print_to_file("File output", "hello.txt");
    hello_world_print_repeat("Repeat", 3);
    
    // Cleanup
    hello_world_config_free(config);
    hello_world_cleanup();
    return 0;
}
```

### Error Handling Example

```c
#include "hello_world.h"
#include <stdio.h>

int main(void) {
    int result;
    
    // Initialize with error handling
    result = hello_world_init(NULL);
    if (result != HELLO_WORLD_SUCCESS) {
        fprintf(stderr, "Initialization failed: %s\n", 
                hello_world_get_error_message(result));
        return 1;
    }
    
    // Print with error handling
    result = hello_world_print("Hello, Error Handling!");
    if (result != HELLO_WORLD_SUCCESS) {
        fprintf(stderr, "Print failed: %s\n", 
                hello_world_get_error_message(result));
        hello_world_cleanup();
        return 1;
    }
    
    // Cleanup with error handling
    result = hello_world_cleanup();
    if (result != HELLO_WORLD_SUCCESS) {
        fprintf(stderr, "Cleanup failed: %s\n", 
                hello_world_get_error_message(result));
        return 1;
    }
    
    return 0;
}
```

## Best Practices

### 1. Always Check Return Values
```c
int result = hello_world_print("message");
if (result != HELLO_WORLD_SUCCESS) {
    // Handle error appropriately
}
```

### 2. Initialize Before Use
```c
if (!hello_world_is_initialized()) {
    hello_world_init(NULL);
}
```

### 3. Clean Up Resources
```c
// Always cleanup configuration
hello_world_config_t* config = hello_world_config_create();
// ... use config ...
hello_world_config_free(config);

// Always cleanup system
hello_world_cleanup();
```

### 4. Use Configuration for Complex Setups
```c
hello_world_config_t* config = hello_world_config_create();
config->message = strdup("Custom message");
config->verbose = 1;
hello_world_init(config);
// ... use system ...
hello_world_config_free(config);
```

### 5. Handle Memory Allocation
```c
char* custom_message = strdup("Custom message");
if (custom_message == NULL) {
    // Handle memory allocation failure
    return HELLO_WORLD_ERROR_MEMORY;
}
// ... use custom_message ...
free(custom_message);
```

### 6. Use Macros for Common Operations
```c
// Quick hello world
HELLO_WORLD_QUICK();

// Custom message
HELLO_WORLD_CUSTOM("My message");

// Get version
printf("Version: %s\n", HELLO_WORLD_VERSION());
```

---

*This API documentation is comprehensive and covers all public functions, data structures, and usage patterns for the Hello World API.*