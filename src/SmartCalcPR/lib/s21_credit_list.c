#include "s21_credit.h"

CrList_t *s21_CrList_create() {
  CrList_t *head = (CrList_t *)malloc(sizeof(CrList_t));
  head->next = NULL;
  return head;
}

CrList_t *s21_CrList_find_last(CrList_t *head) {
  CrList_t *ptr = head;
  while (ptr->next != NULL) {
    ptr = ptr->next;
  }
  return ptr;
}

void s21_CrList_add_node(CrList_t *head, double payment, double pay_debt,
                         double pay_percent, double remaining) {
  CrList_t *ptr = s21_CrList_find_last(head);
  CrList_t *new_node = (CrList_t *)malloc(sizeof(CrList_t));

  if (new_node != NULL) {
    ptr->next = new_node;

    new_node->next = NULL;
    new_node->payment = payment;
    new_node->pay_debt = pay_debt;
    new_node->pay_percent = pay_percent;
    new_node->remaining = remaining;
  }
}

void s21_CrList_remove(CrList_t *head) {
  CrList_t *ptr = head;
  CrList_t *remove_node = head;
  while (ptr->next != NULL) {
    remove_node = ptr;
    ptr = ptr->next;
    free(remove_node);
  }
  remove_node = ptr;
  free(remove_node);
}