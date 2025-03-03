#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

char *dict_lookup(char *key, DictEntry dictionary[], int dict_size) {
    for (int i = 0; i < dict_size; i++) {
        if (strcmp(key, dictionary[i].key) == 0) {
            return dictionary[i].value;
        }
    }
    return "";
}

// Function to process hundreds place
void process_hundreds(char *group, DictEntry dictionary[], int dict_size, char *group_word) {
    strcat(group_word, dict_lookup((char[]){group[0], '\0'}, dictionary, dict_size));
    strcat(group_word, " hundred ");
}

// Function to process tens and ones
void process_tens_ones(char *tens_ones, DictEntry dictionary[], int dict_size, char *group_word) {
    if (tens_ones[0] != '1' && tens_ones[1] != '0') {
        char tens[3] = {tens_ones[0], '0', '\0'};
        strcat(group_word, dict_lookup(tens, dictionary, dict_size));
        strcat(group_word, " ");
        if (tens_ones[1] != '0') {
            strcat(group_word, dict_lookup((char[]){tens_ones[1], '\0'}, dictionary, dict_size));
            strcat(group_word, " ");
        }
    } else {
        strcat(group_word, dict_lookup(tens_ones, dictionary, dict_size));
        strcat(group_word, " ");
    }
}


// Function to process a group of 3 digits
void process_group(char *group, DictEntry dictionary[], int dict_size, char *group_word) {
    int group_len = strlen(group);

    if (group_len == 3) {
        process_hundreds(group, dictionary, dict_size, group_word);
        char tens_ones[3] = {group[1], group[2], '\0'};
        process_tens_ones(tens_ones, dictionary, dict_size, group_word);

    } else if (group_len == 2) {
        char tens_ones[3] = {group[0], group[1], '\0'};
        process_tens_ones(tens_ones, dictionary, dict_size, group_word);

    } else if (group_len == 1) {
        strcat(group_word, dict_lookup(group, dictionary, dict_size));
        strcat(group_word, " ");
    }
}

// Function to build the auxiliary string for magnitudes
void build_aux_string(char *aux, int magnitude_power) {
    strcpy(aux, "1");
    for (int j = 0; j < magnitude_power * 3; j++) {
        strcat(aux, "0");
    }
}

// Function to store groups of digits
void store_groups(char *num, char groups[][4], int *group_index) {
    int len = strlen(num);
    for (int i = len - 1; i >= 0; i -= 3) {
        int start = (i - 2 >= 0) ? i - 2 : 0;
        int group_len = i - start + 1;
        strncpy(groups[*group_index], num + start, group_len);
        groups[*group_index][group_len] = '\0';
        (*group_index)++;
    }
}

// Function to print group and magnitude words
void print_group_magnitude(char *group_word, char *aux, int magnitude_power, DictEntry dictionary[], int dict_size) {
    printf("%s", group_word);
    if (magnitude_power > 0) {
        build_aux_string(aux, magnitude_power);
        char *magnitude_word = dict_lookup(aux, dictionary, dict_size);
        printf("%s ", magnitude_word);
    }
}

void convert_number(char *num, DictEntry dictionary[], int dict_size, int group_count) {
    char groups[group_count][4];
    int group_index = 0;

    store_groups(num, groups, &group_index); // Store the groups


    char aux[16];
    int magnitude_power = group_count - 1;
    int i = group_count - 1;

    while (i >= 0) {
        char group_word[200] = "";
        process_group(groups[i], dictionary, dict_size, group_word);

        print_group_magnitude(group_word, aux, magnitude_power, dictionary, dict_size); // Print

        magnitude_power--;
        i--;
    }
    printf("\n");
}

void number_to_words(char *num, DictEntry dictionary[], int dict_size) {
  int len = strlen(num);
  int group_count = (len + 2) / 3;
  convert_number(num, dictionary, dict_size, group_count);
}
int main() {
    DictEntry dictionary[] = {
        {"0", "zero"}, {"1", "one"}, {"2", "two"}, {"3", "three"}, {"4", "four"},
        {"5", "five"}, {"6", "six"}, {"7", "seven"}, {"8", "eight"}, {"9", "nine"},
        {"10", "ten"}, {"11", "eleven"}, {"12", "twelve"}, {"13", "thirteen"},
        {"14", "fourteen"}, {"15", "fifteen"}, {"16", "sixteen"}, {"17", "seventeen"},
        {"18", "eighteen"}, {"19", "nineteen"}, {"20", "twenty"}, {"30", "thirty"},
        {"40", "forty"}, {"50", "fifty"}, {"60", "sixty"}, {"70", "seventy"},
        {"80", "eighty"}, {"90", "ninety"}, {"100", "hundred"}, {"1000", "thousand"},
        {"1000000", "million"}, {"1000000000", "billion"}, {"1000000000000", "trillion"}
    };
    int dict_size = sizeof(dictionary) / sizeof(dictionary[0]);

    char num[] = "12524523525";
    number_to_words(num, dictionary, dict_size);

     strcpy(num, "1234");
     number_to_words(num, dictionary, dict_size);

    return 0;
}