#include "s21_calc.h"

Node_t *s21_node_create() {
  Node_t *head = (Node_t *)malloc(sizeof(Node_t));
  head->is_binary = false;
  head->priority = 0;
  head->sign_char[0] = '\0';
  head->value = 0;
  head->next = NULL;
  head->prev = NULL;
  head->last_node_ptr = head;
  return head;
}

Node_t *s21_node_find_last(Node_t *head) {
  Node_t *ptr = head;
  if (ptr->next != NULL) {
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
  }
  return ptr;
}

void s21_set_sign_eof(char *src) {
  for (int i = 0; i < 5; i++) {
    src[i] = '\0';
  }
}

void s21_node_add(Node_t *head, int set_priority, char *set_sign_char,
                  double *value, bool is_binary) {
  Node_t *to_add = (Node_t *)malloc(sizeof(Node_t));
  if (to_add != NULL) {
    to_add->is_binary = false;
    to_add->priority = 0;
    s21_set_sign_eof(to_add->sign_char);
    if (to_add != NULL) {
      Node_t *last_node = head->last_node_ptr;

      to_add->priority = set_priority;
      to_add->is_binary = is_binary;
      if (set_sign_char[0] != '\0') {
        s21_strcpy(set_sign_char, to_add->sign_char);
      }
      if (set_priority < 0) {
        to_add->value = *value;
      } else {
        to_add->value = 0;
      }
      last_node->next = to_add;
      to_add->prev = last_node;
      head->last_node_ptr = to_add;
      to_add->next = NULL;
      to_add->last_node_ptr = NULL;
    }
  }
}
void s21_remove_node(Node_t *head) {
  Node_t *ptr = head->last_node_ptr;
  Node_t *ptr_new_last = ptr->prev;

  ptr_new_last->next = NULL;
  head->last_node_ptr = ptr_new_last;
  free(ptr);
}

void s21_full_free_node(Node_t *head) {
  Node_t *ptr = head->last_node_ptr;
  while (ptr->prev != NULL) {
    ptr->next = NULL;
    ptr->is_binary = false;
    ptr = ptr->prev;
    head->last_node_ptr = ptr;
    free(ptr->next);
  }
  free(ptr);
}

Node_t *s21_node_remove_unary(Node_t *head, Node_t *dest) {
  Node_t *ptr_value = dest->prev;
  Node_t *ptr_operator = dest;
  Node_t *ptr_after = dest->next;

  if (head->last_node_ptr == ptr_operator) {
    head->last_node_ptr = ptr_value;
  }

  ptr_value->next = ptr_after;
  if (ptr_after != NULL) {
    ptr_after->prev = ptr_value;
  }
  free(ptr_operator);
  return ptr_value;
}

Node_t *s21_node_remove_binary(Node_t *head, Node_t *dest) {
  Node_t *ptr_first_val = dest->prev->prev;
  Node_t *ptr_second_val = dest->prev;
  Node_t *ptr_operator = dest;
  Node_t *ptr_after = ptr_operator->next;

  if (head->last_node_ptr == ptr_operator) {
    head->last_node_ptr = ptr_first_val;
  }

  ptr_first_val->next = ptr_operator->next;
  if (ptr_after != NULL) {
    ptr_after->prev = ptr_first_val;
  }
  free(ptr_operator);
  free(ptr_second_val);
  return ptr_first_val;
}

void s21_node_out(Node_t *head, Node_t *head_sub) {
  while (head_sub->next != NULL) {
    Node_t *last_node = head_sub->last_node_ptr;
    s21_node_add(head, last_node->priority, last_node->sign_char,
                 &last_node->value, last_node->is_binary);
    s21_remove_node(head_sub);
  }
}

// int s21_node_print(Node_t *head) {
//   Node_t *ptr = head;
//   while (ptr->next != NULL) {
//     ptr = ptr->next;
//     printf("%lf ", ptr->value);
//   }
//   printf("\n");
//   return 0;
// }
