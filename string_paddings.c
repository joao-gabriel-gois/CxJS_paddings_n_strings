#include <stdio.h>
#include <stdlib.h>

// Implementing in C a simple code that once broke the web becaue it got unavailable as a Npm Package (lol)
int get_str_len(char*);
char* leftpad(char*, int, char);
char* rightpad(char*, int, char);
char* symmetricalpad(char*, int, char);

int main(void) {
  char original_str[30];
  int final_len;
  char ch;
  printf("\nWelcome to String Paddings! In which string do you want to run it?\nText (max length = 30): ");
  scanf("%29[^\n]s", original_str);
  printf("\nWhat is the final size you want for it?\nInteger: ");
  scanf("%i", &final_len);
  printf("\nWhat character you want to `leftpad it`?\nCharacter: ");
  scanf(" %c", &ch);
 
  
  char* printed_str = leftpad(original_str, final_len, ch);
  printf(
    "\n\tleftpad(\"%s\", %i, '%c') => \"%s\"\n",
    original_str,
    final_len,
    ch,
    printed_str
  );
  free(printed_str);

  printed_str = rightpad(original_str, final_len, ch);
  printf(
    "\n\trightpad(\"%s\", %i, '%c') => \"%s\"\n",
    original_str,
    final_len,
    ch,
    printed_str
  );
  free(printed_str);
  
  printed_str = symmetricalpad(original_str, final_len, ch);
  printf(
    "\n\tsymmetricalpad(\"%s\", %i, '%c') => \"%s\"\n",
    original_str,
    final_len,
    ch,
    printed_str
  );
  free(printed_str);

  // printf("\nCurrent leftPad NPM Package examples:\n");
  // char* printed_str = leftpad("foo", 5, ' ');
  // printf("\tleftpad(\"foo\", 5, ' ') => \"%s\"\n", printed_str);
  // free(printed_str);

  // printed_str = leftpad("foobar", 6, ' ');
  // printf("\tleftpad(\"foobar\", 6, ' ') => \"%s\"\n", printed_str);
  // free(printed_str);

  // printed_str = leftpad("1", 2, '0');
  // printf("\tleftpad(\"1\", 2, '0') => \"%s\"\n", printed_str);
  // free(printed_str);

  // printed_str = leftpad("17", 5, '0');
  // printf("\tleftpad(\"17\", 5, '0') => \"%s\"\n", printed_str);
  // free(printed_str);

  // printf("\nAdditional example with final_len lower than the original string:\n");
  // printed_str = leftpad("Testing it!!!", 5, '+');
  // printf("\tleftpad(\"Testing it!!!\", 5, '+') => \"%s\"\n", printed_str);
  // free(printed_str);


  printf("\n");
  return 0;
}

char* leftpad(char* string, int final_len, char ch) {
  int str_len = get_str_len(string);
  int left_pad_length = final_len - str_len;
  if (left_pad_length < 0) {
    final_len = str_len;
    left_pad_length = 0;
  }
  char* new_string = malloc(final_len * sizeof(char));

  for (int i = 0; i < final_len ; ++i) {
    if (i < left_pad_length)
      new_string[i] = ch; 
    else {
      new_string[i] = string[i - left_pad_length];
    }
  }
  new_string[final_len] = '\0';

  return new_string; 
}

char* rightpad(char* string, int final_len, char ch) {
  int str_len = get_str_len(string);
  if (final_len - str_len < 0)
    final_len = str_len;
  
  char* new_string = malloc(final_len * sizeof(char));

  for (int i = 0; i < final_len ; ++i) {
    if (i < str_len)
      new_string[i] = string[i];
    else {
      new_string[i] = ch; 
    }
  }
  new_string[final_len] = '\0';

  return new_string; 
}

char* symmetricalpad(char* string, int final_len, char ch) {
  int str_len = get_str_len(string);
  int doubled_pad_length = final_len - str_len;
  if (doubled_pad_length < 0) {
    final_len = str_len;
    doubled_pad_length = 0;
  }
  int pad_length = doubled_pad_length / 2;

  char* left_padded = leftpad(string, pad_length + str_len, ch);
  str_len = pad_length + str_len;
  char* new_string = rightpad(left_padded, pad_length + str_len, ch);
  free(left_padded);

  return new_string; 
}

int get_str_len(char* string) {
  int length = 0;
  for (; string[length] != '\0'; ++length);
  return length;
}

