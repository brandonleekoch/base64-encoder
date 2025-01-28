#include <stdio.h>
#include <stdlib.h>
const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
#define BUFFER_SIZE 1024
void encode_chunk(unsigned char *input, int input_len, char *output) {
  unsigned int combined = 0;

  // Combine input bytes into a 24-bit integer
  combined = (input[0] << 16);
  if (input_len > 1) combined |= (input[1] << 8);
  if (input_len > 2) combined |= input[2];

  // Extract 6-bit groups and map to Base64 characters
  output[0] = base64_chars[(combined >> 18) & 0x3F];
  output[1] = base64_chars[(combined >> 12) & 0x3F];
  output[2] = (input_len > 1) ? base64_chars[(combined >> 6) & 0x3F] : '=';
  output[3] = (input_len > 2) ? base64_chars[(combined) & 0x3F] : '=';
  output[4] = '\0';
}

int main() {
  unsigned char input[3]; 
  char output[5];                   // 4 Base64 characters + null terminator
  int bytes_read;

  //Read input in chuncks of 3 bytes
  while ((bytes_read = fread(input, 1, 3, stdin)) > 0) {
    encode_chunk(input, bytes_read, output);
    printf("%s", output);
  }

  printf("\n");  //Print a new line at the end to promote better formatting
  return 0;
}
      
