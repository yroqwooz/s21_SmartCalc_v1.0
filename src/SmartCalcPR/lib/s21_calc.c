#include "s21_calc.h"

double s21_calculate_all(const char *expr, int *err) {
  double res = 0;
  *err = s21_std_validator(expr);
  Node_t *head = s21_node_create();
  if (!(*err)) {
    s21_to_polish(expr, head, err);
    s21_calculate_polish_list(head, err);
  }
  Node_t *ptr = head->last_node_ptr;
  res = ptr->value;
  s21_full_free_node(head);
  return res;
}

void s21_to_polish(const char *arr, Node_t *head, int *error) {
  int arr_size = strlen(arr);
  Node_t *head_sub = s21_node_create();
  if (head != NULL && arr_size != 0) {
    for (int i = 0; i < arr_size; i++) {
      s21_polish_handler(arr, &i, head, head_sub, error);
    }
  }
  s21_node_out(head, head_sub);
  s21_full_free_node(head_sub);
}

void s21_polish_handler(const char *arr, int *o_pos, Node_t *head,
                        Node_t *head_sub, int *error) {
  if ((arr[*o_pos] >= 48 && arr[*o_pos] <= 57) || arr[*o_pos] == '.') {
    s21_num_taker(arr, o_pos, head, error);
  } else if (arr[*o_pos] != ' ' && arr[*o_pos] != '.') {
    char sign_char[5] = {0};
    int level = 0;
    bool is_binary = false;
    s21_sign_char_taker(arr, o_pos, sign_char, &level, &is_binary);
    if (sign_char[0] != '\0') {
      s21_operations_handler(level, sign_char, head, head_sub, is_binary);
    }
  }
}

void s21_num_taker(const char *arr, int *o_pos, Node_t *head, int *error) {
  char buffer[255] = {0};
  int i = 0;
  for (i = *o_pos; (arr[i] >= 48 && arr[i] <= 57) || arr[i] == '.'; i++) {
    buffer[i - *o_pos] = arr[i];
  }
  *o_pos += strlen(buffer) - 1;

  if (buffer[0] == '.' && buffer[1] == '\0') {
    *error = 1;
  }
  double res = atof(buffer);
  s21_node_add(head, -1, "\0", &res, false);
}

int s21_determine_level(char *sign_char, const char *arr, int o_pos,
                        bool *is_binary) {
  int level = 0;

  if ((sign_char[0] == '-' && arr[o_pos - 1] == '(') ||
      (sign_char[0] == '+' && arr[o_pos - 1] == '(')) {
    level = 6;
    *is_binary = false;
  } else if (sign_char[0] == '+' || sign_char[0] == '-') {
    level = 1;
  } else if (sign_char[0] == '*' || sign_char[0] == '/' ||
             sign_char[0] == 'm' || sign_char[1] == 'o' ||
             sign_char[2] == 'd') {
    //  sign_char[0] == '%' || ) {
    level = 2;
  } else if (strcmp(sign_char, "sin") || strcmp(sign_char, "cos") ||
             strcmp(sign_char, "log") || strcmp(sign_char, "tan") ||
             strcmp(sign_char, "asin") || strcmp(sign_char, "acos") ||
             strcmp(sign_char, "ln") || strcmp(sign_char, "atan")) {
    level = 3;
  } else if (sign_char[0] == '^' || strcmp(sign_char, "sqrt")) {
    level = 4;
  } else if (sign_char[0] == '(' || sign_char[0] == ')') {
    level = 5;
  } else {
    level = -1;
  }
  return level;
}

void s21_operations_handler(int level, char *operation, Node_t *head,
                            Node_t *head_sub, bool is_binary) {
  Node_t *ptr = head_sub->last_node_ptr;
  double buffer = 0.0;
  if (ptr != NULL) {
    if (level <= ptr->priority && ptr->sign_char[0] != '(' &&
        ptr->prev != NULL && ptr->priority != 6 && level != 3) {
      while (level <= ptr->priority && ptr->prev != NULL &&
             ptr->sign_char[0] != '(') {
        ptr = s21_element_shift(head, head_sub, ptr->priority, ptr->sign_char,
                                buffer, ptr->is_binary);
      }
    }
    ptr = s21_node_find_last(head_sub);
    if (ptr->sign_char[0] == '-' && ptr->priority == 6) {
      ptr = s21_element_shift(head, head_sub, ptr->priority, ptr->sign_char,
                              buffer, ptr->is_binary);
    }

    s21_node_add(head_sub, level, operation, &buffer, is_binary);
    ptr = s21_node_find_last(head_sub);
    if (ptr->sign_char[0] == ')') {
      s21_remove_node(head_sub);
      ptr = s21_node_find_last(head_sub);

      while (ptr->sign_char[0] != '(') {
        ptr = s21_element_shift(head, head_sub, ptr->priority, ptr->sign_char,
                                buffer, ptr->is_binary);
      }
      s21_remove_node(head_sub);
    }
  }
}

Node_t *s21_element_shift(Node_t *head, Node_t *head_sub, int prior, char *sign,
                          double buffer, bool binarity) {
  s21_node_add(head, prior, sign, &buffer, binarity);
  s21_remove_node(head_sub);
  Node_t *ptr = s21_node_find_last(head_sub);
  return ptr;
}

int s21_strcpy(char *src, char *dst) {
  int size = 0;
  size = s21_strlen(src);
  for (int i = 0; i < size; i++) {
    dst[i] = src[i];
  }
  return 0;
}

int s21_strlen(char *src) {
  int size = 0;
  if (src[0] != '\0') {
    for (int i = 0; src[i] != '\0'; i++) {
      size++;
    }
  }
  return size;
}

bool s21_std_validator(const char *expr) {
  bool error = 0;
  int expr_length = strlen(expr);
  int dot_amount = 0, brackets = 0;
  if (expr_length > 0 && expr_length < 256) {
    for (int o_pos = 0; o_pos < expr_length && error == false; o_pos++) {
      s21_char_handler(expr, &o_pos, &error, &dot_amount, &brackets);
    }
  } else {
    error = 1;
  }
  if (brackets != 0) {
    error = 1;
  }
  return error;
}

void s21_char_handler(const char *expr, int *o_pos, bool *error,
                      int *dot_amount, int *brackets) {
  *error = false;
  if ((expr[*o_pos] >= 48 && expr[*o_pos] <= 57) || expr[*o_pos] == '(' ||
      expr[*o_pos] == ')' || expr[*o_pos] == '+' || expr[*o_pos] == '-' ||
      expr[*o_pos] == '*' || expr[*o_pos] == '/' || expr[*o_pos] == '^' ||
      expr[*o_pos] == '%' || expr[*o_pos] == '.' || expr[*o_pos] == ' ') {
    if (expr[*o_pos] == '.') {
      *dot_amount += 1;
    }
    if ((expr[*o_pos] == '+' || expr[*o_pos] == '-' || expr[*o_pos] == '*' ||
         expr[*o_pos] == '/' || expr[*o_pos] == '^' || expr[*o_pos] == '%') &&
        ((expr[*o_pos + 1] == '+' || expr[*o_pos + 1] == '-' ||
          expr[*o_pos + 1] == '*' || expr[*o_pos + 1] == '/' ||
          expr[*o_pos + 1] == '^' || expr[*o_pos + 1] == '%'))) {
      *error = true;
    }
    if (expr[*o_pos] == '(') {
      *brackets += 1;
    }
    if (expr[*o_pos] == ')') {
      *brackets -= 1;
    }
  } else if (expr[*o_pos] == 'l' && expr[*o_pos + 1] == 'n') {
    (*o_pos)++;
  } else if ((expr[*o_pos] == 's' && expr[*o_pos + 1] == 'i' &&
              expr[*o_pos + 2] == 'n') ||
             (expr[*o_pos] == 'c' && expr[*o_pos + 1] == 'o' &&
              expr[*o_pos + 2] == 's') ||
             (expr[*o_pos] == 't' && expr[*o_pos + 1] == 'a' &&
              expr[*o_pos + 2] == 'n') ||
             (expr[*o_pos] == 'l' && expr[*o_pos + 1] == 'o' &&
              expr[*o_pos + 2] == 'g') ||
             (expr[*o_pos] == 'm' && expr[*o_pos + 1] == 'o' &&
              expr[*o_pos + 2] == 'd')) {
    (*o_pos) += 2;
  } else if ((expr[*o_pos] == 'a' && expr[*o_pos + 1] == 's' &&
              expr[*o_pos + 2] == 'i' && expr[*o_pos + 3] == 'n') ||
             (expr[*o_pos] == 'a' && expr[*o_pos + 1] == 'c' &&
              expr[*o_pos + 2] == 'o' && expr[*o_pos + 3] == 's') ||
             (expr[*o_pos] == 'a' && expr[*o_pos + 1] == 't' &&
              expr[*o_pos + 2] == 'a' && expr[*o_pos + 3] == 'n') ||
             (expr[*o_pos] == 's' && expr[*o_pos + 1] == 'q' &&
              expr[*o_pos + 2] == 'r' && expr[*o_pos + 3] == 't')) {
    (*o_pos) += 3;
  } else {
    *error = true;
  }
  if (!((expr[*o_pos] >= 48 && expr[*o_pos] <= 57) || expr[*o_pos] == '.')) {
    *dot_amount = 0;
  }
  if (*dot_amount > 1) {
    *error = true;
  }
}

void s21_sign_char_taker(const char *arr, int *o_pos, char *sign_char,
                         int *level, bool *is_binary) {
  *is_binary = false;
  if (arr[*o_pos] == '+' || arr[*o_pos] == '-' || arr[*o_pos] == '*' ||
      arr[*o_pos] == '/' || arr[*o_pos] == '(' || arr[*o_pos] == ')' ||
      arr[*o_pos] == '^' || arr[*o_pos] == '%') {
    if (arr[*o_pos] != '(' && arr[*o_pos] != ')') {
      *is_binary = true;
    }
    sign_char[0] = arr[*o_pos];
    sign_char[1] = '\0';
  } else if (arr[*o_pos] == 'l' && arr[*o_pos + 1] == 'n') {
    sign_char[0] = arr[*o_pos];
    sign_char[1] = arr[*o_pos + 1];
    sign_char[2] = '\0';
    *o_pos += 1;
  } else if ((arr[*o_pos] == 's' && arr[*o_pos + 1] == 'i' &&
              arr[*o_pos + 2] == 'n') ||
             (arr[*o_pos] == 'c' && arr[*o_pos + 1] == 'o' &&
              arr[*o_pos + 2] == 's') ||
             (arr[*o_pos] == 't' && arr[*o_pos + 1] == 'a' &&
              arr[*o_pos + 2] == 'n') ||
             (arr[*o_pos] == 'l' && arr[*o_pos + 1] == 'o' &&
              arr[*o_pos + 2] == 'g') ||
             (arr[*o_pos] == 'm' && arr[*o_pos + 1] == 'o' &&
              arr[*o_pos + 2] == 'd')) {
    if ((arr[*o_pos] == 'm' && arr[*o_pos + 1] == 'o' &&
         arr[*o_pos + 2] == 'd')) {
      *is_binary = true;
    }
    sign_char[0] = arr[*o_pos];
    sign_char[1] = arr[*o_pos + 1];
    sign_char[2] = arr[*o_pos + 2];
    sign_char[3] = '\0';
    *o_pos += 2;
  } else if ((arr[*o_pos] == 'a' && arr[*o_pos + 1] == 's' &&
              arr[*o_pos + 2] == 'i' && arr[*o_pos + 3] == 'n') ||
             (arr[*o_pos] == 'a' && arr[*o_pos + 1] == 'c' &&
              arr[*o_pos + 2] == 'o' && arr[*o_pos + 3] == 's') ||
             (arr[*o_pos] == 'a' && arr[*o_pos + 1] == 't' &&
              arr[*o_pos + 2] == 'a' && arr[*o_pos + 3] == 'n') ||
             (arr[*o_pos] == 's' && arr[*o_pos + 1] == 'q' &&
              arr[*o_pos + 2] == 'r' && arr[*o_pos + 3] == 't')) {
    sign_char[0] = arr[*o_pos];
    sign_char[1] = arr[*o_pos + 1];
    sign_char[2] = arr[*o_pos + 2];
    sign_char[3] = arr[*o_pos + 3];
    sign_char[4] = '\0';
    *o_pos += 3;
  }
  *level = s21_determine_level(sign_char, arr, *o_pos, is_binary);
}

void s21_calculate_polish_list(Node_t *head, int *error) {
  Node_t *ptr = head;
  while (ptr->next != head->last_node_ptr->next) {
    ptr = s21_calculate_polish_list_sub(head, ptr, error);
    if (ptr->sign_char[0] == '-') {
      ptr->value = 0 - ptr->value;
    }
  }
  s21_calculate_polish_list_sub(head, ptr, error);
}

Node_t *s21_calculate_polish_list_sub(Node_t *head, Node_t *ptr, int *error) {
  if (ptr->priority > 0) {
    if (ptr->is_binary == true) {
      s21_calculate_binary(ptr);
      ptr = s21_node_remove_binary(head, ptr);
    } else if (ptr->is_binary == false) {
      s21_calculate_unary(ptr, error);
      ptr = s21_node_remove_unary(head, ptr);
    }
  } else {
    ptr = ptr->next;
  }
  return ptr;
}

void s21_calculate_binary(Node_t *ptr) {
  if (ptr->sign_char[0] == '+' && ptr->priority == 1) {
    ptr->prev->prev->value = ptr->prev->prev->value + ptr->prev->value;
  } else if (ptr->sign_char[0] == '-' && ptr->priority == 1) {
    ptr->prev->prev->value = ptr->prev->prev->value - ptr->prev->value;
  } else if (ptr->sign_char[0] == '*') {
    ptr->prev->prev->value = ptr->prev->prev->value * ptr->prev->value;
  } else if (ptr->sign_char[0] == '/') {
    ptr->prev->prev->value = ptr->prev->prev->value / ptr->prev->value;
  } else if (ptr->sign_char[0] == '^') {
    ptr->prev->prev->value = pow(ptr->prev->prev->value, ptr->prev->value);
  } else if (ptr->sign_char[0] == 'm') {
    ptr->prev->prev->value = fmod(ptr->prev->prev->value, ptr->prev->value);
  }
}

void s21_calculate_unary(Node_t *ptr, int *error) {
  if (ptr->sign_char[0] == '-' && ptr->priority == 6) {
    ptr->prev->value = ptr->prev->value * -1;
  } else if (ptr->sign_char[0] == '+' && ptr->priority == 6) {
    ptr->prev->value = ptr->prev->value * 1;
  } else if (ptr->sign_char[0] == 'l' && ptr->sign_char[1] == 'n') {
    ptr->prev->value = log(ptr->prev->value);
  } else if (ptr->sign_char[0] == 'c' && ptr->sign_char[1] == 'o' &&
             ptr->sign_char[2] == 's') {
    ptr->prev->value = cos(ptr->prev->value);
  } else if (ptr->sign_char[0] == 's' && ptr->sign_char[1] == 'i' &&
             ptr->sign_char[2] == 'n') {
    ptr->prev->value = sin(ptr->prev->value);
  } else if (ptr->sign_char[0] == 't' && ptr->sign_char[1] == 'a' &&
             ptr->sign_char[2] == 'n') {
    ptr->prev->value = tan(ptr->prev->value);
  } else if (ptr->sign_char[0] == 'l' && ptr->sign_char[1] == 'o' &&
             ptr->sign_char[2] == 'g') {
    if (ptr->prev->value < 0) {
      *error = 1;
    }
    ptr->prev->value = log10(ptr->prev->value);
  } else if (ptr->sign_char[0] == 'a' && ptr->sign_char[1] == 'c' &&
             ptr->sign_char[2] == 'o' && ptr->sign_char[3] == 's') {
    ptr->prev->value = acos(ptr->prev->value);
  } else if (ptr->sign_char[0] == 'a' && ptr->sign_char[1] == 's' &&
             ptr->sign_char[2] == 'i' && ptr->sign_char[3] == 'n') {
    ptr->prev->value = asin(ptr->prev->value);
  } else if (ptr->sign_char[0] == 'a' && ptr->sign_char[1] == 't' &&
             ptr->sign_char[2] == 'a' && ptr->sign_char[3] == 'n') {
    ptr->prev->value = atan(ptr->prev->value);
  } else if (ptr->sign_char[0] == 's' && ptr->sign_char[1] == 'q' &&
             ptr->sign_char[2] == 'r' && ptr->sign_char[3] == 't') {
    ptr->prev->value = sqrt(ptr->prev->value);
  }
}