#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Version information */
#define HELLO_WORLD_VERSION_MAJOR 1
#define HELLO_WORLD_VERSION_MINOR 0
#define HELLO_WORLD_VERSION_PATCH 0

/* Configuration structure */
typedef struct {
    char* message;
    int verbose;
    char* output_file;
    int use_colors;
} hello_world_config_t;

/* Error codes */
typedef enum {
    HELLO_WORLD_SUCCESS = 0,
    HELLO_WORLD_ERROR_NULL_POINTER = -1,
    HELLO_WORLD_ERROR_INVALID_CONFIG = -2,
    HELLO_WORLD_ERROR_FILE_IO = -3,
    HELLO_WORLD_ERROR_MEMORY = -4
} hello_world_error_t;

/* Core API Functions */

/**
 * @brief Initialize the hello world system
 * @param config Configuration structure (can be NULL for defaults)
 * @return Error code (0 for success)
 */
int hello_world_init(const hello_world_config_t* config);

/**
 * @brief Clean up resources used by the hello world system
 * @return Error code (0 for success)
 */
int hello_world_cleanup(void);

/**
 * @brief Print the hello world message
 * @param message Custom message to print (NULL for default)
 * @return Error code (0 for success)
 */
int hello_world_print(const char* message);

/**
 * @brief Print hello world message with formatting
 * @param format Format string (printf-style)
 * @param ... Variable arguments
 * @return Error code (0 for success)
 */
int hello_world_printf(const char* format, ...);

/**
 * @brief Get the default hello world message
 * @return Pointer to default message string
 */
const char* hello_world_get_default_message(void);

/**
 * @brief Set a custom hello world message
 * @param message New message to use
 * @return Error code (0 for success)
 */
int hello_world_set_message(const char* message);

/* Configuration API Functions */

/**
 * @brief Create a default configuration
 * @return Pointer to new configuration structure (must be freed)
 */
hello_world_config_t* hello_world_config_create(void);

/**
 * @brief Free a configuration structure
 * @param config Configuration to free
 */
void hello_world_config_free(hello_world_config_t* config);

/**
 * @brief Load configuration from file
 * @param filename Configuration file path
 * @return Pointer to loaded configuration (must be freed)
 */
hello_world_config_t* hello_world_config_load(const char* filename);

/**
 * @brief Save configuration to file
 * @param config Configuration to save
 * @param filename Output file path
 * @return Error code (0 for success)
 */
int hello_world_config_save(const hello_world_config_t* config, const char* filename);

/* Utility Functions */

/**
 * @brief Get version string
 * @return Version string in format "major.minor.patch"
 */
const char* hello_world_get_version(void);

/**
 * @brief Get error message for error code
 * @param error_code Error code
 * @return Human-readable error message
 */
const char* hello_world_get_error_message(int error_code);

/**
 * @brief Check if hello world system is initialized
 * @return 1 if initialized, 0 otherwise
 */
int hello_world_is_initialized(void);

/* Advanced Features */

/**
 * @brief Print hello world message with colors (if supported)
 * @param message Message to print
 * @param color Color name ("red", "green", "blue", etc.)
 * @return Error code (0 for success)
 */
int hello_world_print_colored(const char* message, const char* color);

/**
 * @brief Print hello world message to file
 * @param message Message to print
 * @param filename Output file path
 * @return Error code (0 for success)
 */
int hello_world_print_to_file(const char* message, const char* filename);

/**
 * @brief Print hello world message multiple times
 * @param message Message to print
 * @param count Number of times to print
 * @return Error code (0 for success)
 */
int hello_world_print_repeat(const char* message, int count);

/* Example usage macros */
#define HELLO_WORLD_QUICK() hello_world_print(NULL)
#define HELLO_WORLD_CUSTOM(msg) hello_world_print(msg)
#define HELLO_WORLD_VERSION() hello_world_get_version()

#endif /* HELLO_WORLD_H */