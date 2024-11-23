#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false !true

int get_str_len(char*);
char* alloc_writeable_str(char*);
void concat(char**, char*);
void slice(char**, int, int);
bool includes(char*, char*);
int indexOf(char*, char*);
int lastIndexOf(char*, char*);
void toUpperCase(char*);
void toLowerCase(char*);
void capitalize(char*);
void trimLeft(char**);
void trimRight(char**);
void trim(char**);
bool startsWith(char*, char*, int);
bool endsWith(char*, char*, int);
void replace(char**, char*, char*);
void replaceAll(char**, char*, char*);

int main(void) {
  char* test_string = alloc_writeable_str("Testing it");
  char* to_concat = ", right now!";

  printf("Original String: %s\n", test_string);
  // pop(&test_string);
  // printf("String after pop: %s\n", test_string);
  concat(&test_string, to_concat);
  printf("String after concat ', right now!': %s\n", test_string);
  slice(&test_string, 2, 9);
  printf("String after slice from 2 (inc.) to 9 (exc.): %s\n", test_string);

  bool includes_ting = includes(test_string, "ting");
  printf("Checking includes for for valid substr 'ting': %s\n", includes_ting == true ? "true" : "false");
  bool includes_stin = includes(test_string, "stin");
  printf("Checking includes for for valid substr 'stin': %s\n", includes_stin == true ? "true" : "false");
  bool includes_ting_anagram = includes(test_string, "tnig"); // this is the source of has_char based previous impl
  printf("Checking includes for for invalid substr 'tnig': %s\n", includes_ting_anagram == true ? "true" : "false");
  bool includes_corinthians = includes(test_string, "corinthians");
  printf("Checking includes for for invalid substr 'corinthians': %s\n", includes_corinthians == true ? "true" : "false");

  int first_i_occur = indexOf(test_string, "i");
  printf("\nFirst 'i' occurence: %i\n", first_i_occur);
  int last_i_occur = lastIndexOf(test_string, "i");
  printf("Last 'i' occurence: %i\n", last_i_occur);

  char* new_str = alloc_writeable_str("lalalalalol");
  int first_occur = indexOf(new_str, "lal");
  printf("First 'lal' occurence of new_str ('%s'): %i\n", new_str, first_occur);
  int last_occur = lastIndexOf(new_str, "lal");
  printf("Last 'lal' occurence of new_str ('%s'): %i\n", new_str, last_occur);

  toUpperCase(test_string);
  toUpperCase(new_str);
  printf("\nUppercased strings: %s | %s\n", test_string, new_str);

  toLowerCase(test_string);
  toLowerCase(new_str);
  printf("Lowercased strings: %s | %s\n", test_string, new_str);

  capitalize(test_string);
  capitalize(new_str);
  printf("Capitalized strings: %s | %s\n", test_string, new_str);

  char* trim_test_str = alloc_writeable_str("  okdoki  ");
  printf("\nTesting trim (before): \"%s\"\n", trim_test_str);
  trim(&trim_test_str);
  printf("Testing trim (after): \"%s\"\n", trim_test_str);

  bool startsWithOk = startsWith(trim_test_str, "ok", 0); // true
  bool hasOkInIndex3 = startsWith(trim_test_str, "ok", 3); // true
  bool hasOkInIndex4 = startsWith(trim_test_str, "ok", 4); // false
  printf("\nDoes \"%s\" starts with: \"ok\"? %s\n", trim_test_str, startsWithOk == true ? "Yes!" : "No!");
  printf("Does \"%s\" starts with: \"ok\" from index 3? %s\n", trim_test_str, hasOkInIndex3 == true ? "Yes!" : "No!");
  printf("Does \"%s\" starts with: \"ok\" from index 4? %s\n", trim_test_str, hasOkInIndex4 == true ? "Yes!" : "No!");

  bool endsWithDoki = endsWith(trim_test_str, "doki", get_str_len(trim_test_str)); // true
  bool endsWithDokiEndingAtLenMinus2 = endsWith(trim_test_str, "doki", get_str_len(trim_test_str) - 2); // false
  bool endsWithDoEndingAtLenMinus2 = endsWith(trim_test_str, "do", get_str_len(trim_test_str) - 2); // true
  printf("\nDoes \"%s\" ends with: \"doki\"? %s\n", trim_test_str, endsWithDoki == true ? "Yes!" : "No!");
  printf("Does \"%s\" ends with: \"doki\" from index `length - 2`? %s\n", trim_test_str, endsWithDokiEndingAtLenMinus2 == true ? "Yes!" : "No!");
  printf("Does \"%s\" ends with: \"do\" from index `length - 2`? %s\n",  trim_test_str, endsWithDoEndingAtLenMinus2 == true ? "Yes!" : "No!");
  
  replace(&trim_test_str, "do", " corinthians ");
  printf("\nReplacing first \"do\" with \" corinthians \": %s\n", trim_test_str);

  char* replace_all_str = alloc_writeable_str("My dog is a cute dog. I love my dog, dog! Right?");
  replaceAll(&replace_all_str, "dog", "cat");
  printf("\nReplacing all \"dog\" matches with \"cat\": \"%s\"\n", replace_all_str);


  free(test_string);
  free(new_str);
  free(trim_test_str);
  free(replace_all_str);
  return 0;
}


int get_str_len(char* string) {
  int length = 0;
  for (; string[length] != '\0'; ++length);
  return length;
}

char* alloc_writeable_str(char* string) {
  int str_len = get_str_len(string);
  char* copy = malloc(sizeof(char) * (str_len + 1));
  if (copy == NULL) return "\0";

  int i = 0;
  for(; i < str_len; ++i)
    copy[i] = string[i];
  copy[i] = '\0';

  return copy;
}

void concat(char** string, char* to_concat) {
  int str_len = get_str_len(*string);
  int str_to_contat_len = get_str_len(to_concat);
  char* new_string = malloc((str_len + str_to_contat_len + 1) * sizeof(char));
  if (new_string == NULL) return;
  int i = 0;
  for (; i < str_len; ++i) {
    new_string[i] = (*string)[i];
  }
  for (; i < str_len + str_to_contat_len; ++i) {
    // despite '-' operand for indexes are dangerous, this is fine
    // because it will surely starts with i == str_len, so the min value
    // for 'i', at this point, is 0
    new_string[i] = to_concat[i - str_len];
  }

  new_string[i] = '\0';

  free(*string);
  *string = new_string;
}

void slice(char** string, int start_index_inc, int end_index_exc) {
  if (
    start_index_inc < 0 || end_index_exc > get_str_len(*string)
      || start_index_inc >= end_index_exc || *string[0] == '\0'
  ) return;

  int length = end_index_exc - start_index_inc;
  char* new_string = malloc((length + 1) * sizeof(char));
  if (new_string == NULL) return;
  int i = 0;
  while (i < length) {
    new_string[i] = (*string)[i + start_index_inc];
    i++;
  }
  new_string[i] = '\0';
  
  free(*string);
  *string = new_string;
}

bool includes(char* string, char* substr) {
  for (int i = 0; string[i] != '\0'; ++i) {
    int j = 0;
    while (substr[j] != '\0' && string[i + j] == substr[j]) j++;
    if (substr[j] == '\0') return true;
  }
  return false;
}

int indexOf(char* string, char* substr) {
  for (int i = 0; string[i] != '\0'; ++i) {
    int j = 0;
    // loops through all the substr if its chars stills equals to string one
    while (substr[j] != '\0' && string[i + j] == substr[j]) j++;
    // if the condition was satisfied and the substr was totally iterated
    // then return the index of the main string where the substr was found
    if (substr[j] == '\0') return i;
  }
  return -1;
}

int lastIndexOf(char* string, char* substr) {
  for (int i = get_str_len(string) - 1; i != 0; --i) {
    int j = get_str_len(substr) - 1;
    // reversely loops through all the substr if its chars stills equals to substr
    for (; string[i] == substr[j] && j != 0; --j) {
      i--;
    };
    if (j == 0) return i;
  }
  return -1;
}

void toUpperCase(char* string) {
  int i = 0;
  while (string[i] != '\0') {
    if ((int) string[i] >= 97 && (int) string[i] <= 122)
      string[i] = string[i] - 32;
    i++;
  }
}

void toLowerCase(char* string) {
  int i = 0;
  printf("Before lowercasing: %s\n", string);
  while (string[i] != '\0') {
    if ((int) string[i] >= 65 && (int) string[i] <= 90)
      string[i] = string[i] + 32;
    i++;
  }
}

void capitalize(char* string) {
  if (string == NULL || string[0] == '\0') return;
  char ch_str[] = { string[0], '\0' };
  toUpperCase(ch_str);
  string[0] = ch_str[0];
}

void trimLeft(char** string) {
  if (*string == NULL || (*string)[0] == '\0') return;
  int i = 0;
  while ((*string)[i] == ' ') i++;
  int str_len = get_str_len(*string);
  char* new_string = malloc((str_len + 1 - i)  * sizeof(char));
  if (new_string == NULL) return;
  
  int j = 0;
  while(j < str_len - i) {
    new_string[j] = (*string)[i + j];
    j++;
  }
  new_string[j] = '\0';
  
  free(*string);
  *string = new_string;
}

void trimRight(char** string) {
  if (*string == NULL || (*string)[0] == '\0') return;
  int str_len = get_str_len(*string);
  int i = str_len - 1;
  while ((*string)[i] == ' ') i--;
  i = i < 0 ? 0 : i;
  char* new_string = malloc((str_len + 1 - i)  * sizeof(char));
  if (new_string == NULL) return;

  int j = 0;
  while (j <= i) {
    new_string[j] = (*string)[j];
    j++;
  }
  new_string[j] = '\0';
  
  free(*string);
  *string = new_string;
}

void trim(char** string) {
  trimLeft(string);
  trimRight(string);
}

bool startsWith(char* string, char* substr, int fromIndex) {
    int str_len = get_str_len(string);
    if (fromIndex < 0 || fromIndex >= str_len) return false;

    for (int i = 0; substr[i] != '\0'; i++) {
      if (string[fromIndex + i] != substr[i]) return false;
    }
    return true;
}

bool endsWith(char* string, char* substr, int toIndex) {
  int str_len = get_str_len(string);
  if (substr[0] == '\0' || toIndex > str_len || toIndex < 0) return false;

  int i = toIndex - 1; // toIndex is exclusive, so to include the correct value for i we need to decrement 1
  int j = get_str_len(substr) - 1;
  while (j >= 0) {
    if (string[i] != substr[j]) return false;
    j--; i--;
  }

  return true;
}

// replace (wihtout regexp, for now - maybe think about a separate lib for regexp handler, then inmproove it)
void replace(char** string, char* match, char* new_substr) {
  int str_match_len = get_str_len(match);
  if (str_match_len == 0 || get_str_len(new_substr) == 0) return;

  int match_start_i_inc = indexOf(*string, match);
  if (match_start_i_inc == -1) return;
  int match_end_i_exc = match_start_i_inc + str_match_len;

  char* string_copy_bf_match = alloc_writeable_str(*string);
  char* string_copy_af_match = alloc_writeable_str(*string);
  slice(&string_copy_bf_match, 0, match_start_i_inc);
  if (match_end_i_exc < get_str_len(*string)) {
    slice(&string_copy_af_match, match_end_i_exc, get_str_len(*string));
  }
  else {
    string_copy_af_match[0] = '\0';
  }

  if (get_str_len(string_copy_bf_match) > 0  && get_str_len(string_copy_af_match) > 0) {
    concat(&string_copy_bf_match, new_substr);
    concat(&string_copy_bf_match, string_copy_af_match);
  }

  free(*string);
  free(string_copy_af_match);
  *string = string_copy_bf_match;
}

void replaceAll(char** string, char* match, char* new_substr) {
  while (indexOf(*string, match) != -1) {
    replace(string, match, new_substr);
  }
}
