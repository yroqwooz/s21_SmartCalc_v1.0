#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 255

typedef struct Node {
  int priority;
  double value;
  char sign_char[5];
  bool is_binary;
  struct Node *next;
  struct Node *prev;
  struct Node *last_node_ptr;
} Node_t;

double s21_calculate_all(const char *expr, int *err);
bool s21_std_validator(const char *expr);
void s21_char_handler(const char *expr, int *o_pos, bool *error,
                      int *dot_amount, int *brackets);

/*NODES FUNCTIONS*/
Node_t *s21_node_create();
Node_t *s21_node_find_last(Node_t *head);
void s21_node_add(Node_t *node, int set_priority, char *set_sign_char,
                  double *value, bool is_binary);
void s21_node_remove_specific_node(Node_t *head, Node_t *dst);
int s21_node_print(Node_t *head);
void s21_node_value_print(Node_t *head);
void s21_node_print_backward(Node_t *head);
void s21_node_out(Node_t *head, Node_t *head_sub);
void s21_node_value_add(Node_t *value_list, double buffer);
void s21_remove_node(Node_t *head);
Node_t *s21_node_remove_unary(Node_t *head, Node_t *dest);
Node_t *s21_node_remove_binary(Node_t *head, Node_t *dest);
void s21_full_free_node(Node_t *head);
void s21_set_sign_eof(char *src);

int s21_node_print_data(Node_t *head);

void s21_to_polish(const char *arr, Node_t *head, int *error);
void s21_polish_handler(const char *arr, int *o_pos, Node_t *head,
                        Node_t *head_sub, int *error);
void s21_num_taker(const char *arr, int *o_pos, Node_t *head, int *error);
void s21_sign_char_taker(const char *arr, int *o_pos, char *sign_char,
                         int *level, bool *is_binary);
int s21_determine_level(char *sign_char, const char *arr, int o_pos,
                        bool *is_binary);
void s21_operations_handler(int level, char *operation, Node_t *head,
                            Node_t *head_sub, bool is_binary);
void s21_calculate_polish_list(Node_t *head, int *error);
Node_t *s21_calculate_polish_list_sub(Node_t *head, Node_t *ptr, int *error);
void s21_calculate_binary(Node_t *ptr);
void s21_calculate_unary(Node_t *ptr, int *error);

void s21_calculate_expression(double *res);
void s21_num_char_to_int(char *num, double *num_res);

void s21_subcalc(int pos, Node_t *value_list);
int s21_strcpy(char *src, char *dst);
int s21_strlen(char *src);

void s21_check_char(char *sign);

Node_t *s21_element_shift(Node_t *head, Node_t *head_sub, int prior, char *sign,
                          double buffer, bool binarity);