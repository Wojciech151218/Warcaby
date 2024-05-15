#include "Auxilary.h"
sfColor hex_to_sfColor(const char* hex) {
    // Check if the input starts with '#'
    if (hex[0] != '#') {
        fprintf(stderr, "Invalid hexadecimal color format\n");
        exit(EXIT_FAILURE);
    }

    // Convert the hexadecimal string to integer values for red, green, and blue components
    unsigned int r, g, b;
    sscanf_s(hex, "#%02x%02x%02x", &r, &g, &b);

    // Create and return an sfColor structure
    sfColor color;
    color.r = (sfUint8)r;
    color.g = (sfUint8)g;
    color.b = (sfUint8)b;
    color.a = 255; // Set alpha to full opacity
    return color;
}
char* sum_strings(char* str1, char* str2) {
    char* result = malloc(strlen(str1) + strlen(str2) + 1);  // +1 for the null-terminator
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}