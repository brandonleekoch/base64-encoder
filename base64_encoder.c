#include <stdio.h>
#include <stdlib.h>
const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
#define BUFFER_SIZE 1024
void encode_chunk(unsigned char *input, int input_len, char *output) {
  unsigned int combined = 0;

  // Combine input bytes into a 24-bit integer
  combined |= input[0] << 16;
  if (input_len > 1) combined |= input[1] << 8;
  if (input_len > 2) combined |= input[2];

  // Extract 6-bit groups and map to Base64 characters
  output[0] = base64_chars[(combined >> 18) & 0x3F];
  output[1] = base64_chars[(combined >> 12) & 0x3F];
  output[2] = (input_len > 1) ? base64_chars[(combined >> 6) & 0x3F] : '=';
  output[3] = (input_len > 2) ? base64_chars[combined & 0x3F] : '=';
  output[4] = '\0';
}

int main() {
  // Test cases
  unsigned char input1[3] = {'M', 'a', 'n'};   // Full 3-byte input
  unsigned char input2[2] = {'M', 'a'};        // 2-byte input
  unsigned char input3[1] = {'M'};            // 1-byte input

  char output[5];  // Buffer to hold the Base64-encoded string (4 chars + '\0')

  // Test case 1: Full 3-byte input
  encode_chunk(input1, 3, output);
  printf("Input: 'Man' -> Encoded: %s\n", output);  // Expected: TWFu

  // Test case 2: 2-byte input
  encode_chunk(input2, 2, output);
  printf("Input: 'Ma' -> Encoded: %s\n", output);   // Expected: TWE=

  // Test case 3: 1-byte input
  encode_chunk(input3, 1, output);
  printf("Input: 'M' -> Encoded: %s\n", output);    // Expected: TQ==

  return 0;
}
