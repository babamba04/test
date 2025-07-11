#include "hello_world.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Example program demonstrating the Hello World API
 * 
 * This example shows:
 * - Basic initialization and cleanup
 * - Custom configuration
 * - Error handling
 * - Various output methods
 * - Configuration management
 */

int main(void) {
    int result;
    
    printf("=== Hello World API Example ===\n\n");
    
    // Example 1: Basic usage with defaults
    printf("1. Basic usage with defaults:\n");
    result = hello_world_init(NULL);
    if (result != HELLO_WORLD_SUCCESS) {
        fprintf(stderr, "Failed to initialize: %s\n", 
                hello_world_get_error_message(result));
        return 1;
    }
    
    hello_world_print(NULL);
    printf("\n");
    
    // Example 2: Custom message
    printf("2. Custom message:\n");
    hello_world_print("Hello, Custom World!");
    printf("\n");
    
    // Example 3: Formatted output
    printf("3. Formatted output:\n");
    hello_world_printf("Hello, %s!", "Formatted");
    hello_world_printf("Count: %d, Message: %s", 42, "Hello");
    printf("\n");
    
    // Example 4: Get default message
    printf("4. Default message:\n");
    const char* default_msg = hello_world_get_default_message();
    printf("Default message is: \"%s\"\n", default_msg);
    printf("\n");
    
    // Example 5: Set custom message
    printf("5. Setting custom message:\n");
    result = hello_world_set_message("Hello, Universe!");
    if (result == HELLO_WORLD_SUCCESS) {
        hello_world_print(NULL);  // Will print the new message
    }
    printf("\n");
    
    // Example 6: Configuration management
    printf("6. Configuration management:\n");
    hello_world_config_t* config = hello_world_config_create();
    if (config != NULL) {
        config->message = strdup("Hello from config!");
        config->verbose = 1;
        config->use_colors = 1;
        
        // Reinitialize with new config
        hello_world_cleanup();
        result = hello_world_init(config);
        if (result == HELLO_WORLD_SUCCESS) {
            hello_world_print(NULL);
        }
        
        hello_world_config_free(config);
    }
    printf("\n");
    
    // Example 7: Error handling
    printf("7. Error handling:\n");
    result = hello_world_print(NULL);
    if (result != HELLO_WORLD_SUCCESS) {
        printf("Error occurred: %s\n", hello_world_get_error_message(result));
    } else {
        printf("Print successful\n");
    }
    printf("\n");
    
    // Example 8: Version information
    printf("8. Version information:\n");
    printf("API Version: %s\n", hello_world_get_version());
    printf("Initialization status: %s\n", 
           hello_world_is_initialized() ? "Initialized" : "Not initialized");
    printf("\n");
    
    // Example 9: Advanced features (if implemented)
    printf("9. Advanced features:\n");
    
    // Color output (if supported)
    result = hello_world_print_colored("Hello", "red");
    if (result != HELLO_WORLD_SUCCESS) {
        printf("Color output not supported or failed: %s\n", 
               hello_world_get_error_message(result));
    }
    
    // File output
    result = hello_world_print_to_file("Hello, File!", "example_output.txt");
    if (result == HELLO_WORLD_SUCCESS) {
        printf("Message written to example_output.txt\n");
    } else {
        printf("File output failed: %s\n", hello_world_get_error_message(result));
    }
    
    // Repeat output
    result = hello_world_print_repeat("Repeat", 3);
    if (result != HELLO_WORLD_SUCCESS) {
        printf("Repeat failed: %s\n", hello_world_get_error_message(result));
    }
    printf("\n");
    
    // Example 10: Using macros
    printf("10. Using macros:\n");
    HELLO_WORLD_QUICK();
    HELLO_WORLD_CUSTOM("Macro message");
    printf("Version via macro: %s\n", HELLO_WORLD_VERSION());
    printf("\n");
    
    // Cleanup
    printf("11. Cleanup:\n");
    result = hello_world_cleanup();
    if (result == HELLO_WORLD_SUCCESS) {
        printf("Cleanup successful\n");
    } else {
        printf("Cleanup failed: %s\n", hello_world_get_error_message(result));
    }
    
    printf("\n=== Example completed ===\n");
    return 0;
}

/**
 * Additional example functions for demonstration
 */

void example_basic_usage(void) {
    // Simple hello world
    hello_world_init(NULL);
    hello_world_print(NULL);
    hello_world_cleanup();
}

void example_with_configuration(void) {
    // Create configuration
    hello_world_config_t* config = hello_world_config_create();
    if (config != NULL) {
        config->message = strdup("Configured message");
        config->verbose = 1;
        
        // Initialize with config
        hello_world_init(config);
        hello_world_print(NULL);
        
        // Cleanup
        hello_world_cleanup();
        hello_world_config_free(config);
    }
}

void example_error_handling(void) {
    int result;
    
    // Initialize
    result = hello_world_init(NULL);
    if (result != HELLO_WORLD_SUCCESS) {
        fprintf(stderr, "Initialization failed: %s\n", 
                hello_world_get_error_message(result));
        return;
    }
    
    // Print with error checking
    result = hello_world_print("Test message");
    if (result != HELLO_WORLD_SUCCESS) {
        fprintf(stderr, "Print failed: %s\n", 
                hello_world_get_error_message(result));
    }
    
    // Cleanup
    hello_world_cleanup();
}

void example_file_operations(void) {
    // Initialize
    hello_world_init(NULL);
    
    // Write to file
    hello_world_print_to_file("Hello from file operation", "test.txt");
    
    // Cleanup
    hello_world_cleanup();
}

void example_colored_output(void) {
    // Initialize
    hello_world_init(NULL);
    
    // Print in different colors
    hello_world_print_colored("Red message", "red");
    hello_world_print_colored("Green message", "green");
    hello_world_print_colored("Blue message", "blue");
    
    // Cleanup
    hello_world_cleanup();
}