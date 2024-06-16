#include "parsing_grep.h"

char parse_args(int argc, char *argv[], Option *o, char *files[], int *file_c,
                Pattern *p) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && (int)strlen(argv[i]) > 1) {
      for (int j = 1; j < (int)strlen(argv[i]); j++) {
        char res = handle_flag(argv[i][j], argv[i][j + 1], o, p, argv[i + 1]);
        if (res != 0 && res != 'e') {
          return res;
        }
        if (res == 'e') {
          o->is_pattern = true;
          char *buf = strchr(argv[i], 'e') + 1;
          p->val[p->count] = malloc(1000);
          strcpy(p->val[(p->count)++], buf);
          break;
        }
      }
      strcpy(argv[i], "");
    }
  }

  for (int j = 1; j < argc; j++) {
    if (!strcmp(argv[j], "")) {
      continue;
    }
    if (!o->is_pattern) {
      o->is_pattern = true;
      p->val[p->count] = malloc(1000);
      strcpy(p->val[(p->count)++], argv[j]);
    } else {
      files[(*file_c)++] = argv[j];
    }
  }
  return 0;
}

char handle_flag(char flag, char next_char, Option *o, Pattern *p,
                 char *next_arg) {
  switch (flag) {
    case 'i':
      o->is_register_ignore = true;
      break;
    case 'v':
      o->is_invert_results = true;
      break;
    case 's':
      o->is_file_error_ignore = true;
      break;
    case 'c':
      o->is_match_count = true;
      break;
    case 'n':
      o->is_num_row = true;
      break;
    case 'l':
      o->is_only_filename = true;
      break;
    case 'f':
      if (next_char != 0) {
        o->is_pattern = true;
        p->val[p->count] = malloc(1000);
        strcpy(p->val[(p->count)++], ".");
        break;
      }
      o->is_pattern = true;
      handle_pattern_file(next_arg, p);
      strcpy(next_arg, "");
      break;
    case 'h':
      o->is_filename_ignore = true;
      break;
    case 'e':
      if (next_char != 0) {
        o->is_pattern = true;
        return flag;
      }
      o->is_pattern = true;
      p->val[p->count] = malloc(1000);
      strcpy(p->val[(p->count)++], next_arg);
      strcpy(next_arg, "");
      break;
    case 'o':
      o->is_only_match = true;
      break;
    default:
      return flag;
  }
  return 0;
}

void handle_pattern_file(char *filename, Pattern *p) {
  FILE *fstream = fopen(filename, "r");
  if (!fstream) {
    char error[100] = "grep: ";
    strcat(error, filename);
    strcat(error, ": No such file or directory\n");
    perror(error);
    free_string(p->count, p->val);
    exit(1);
  }
  char buf[100];

  while (fgets(buf, sizeof(buf), fstream)) {
    delete_new_line(buf);
    p->val[p->count] = malloc(1000);
    strcpy(p->val[(p->count)++], buf);
  }
  fclose(fstream);
}