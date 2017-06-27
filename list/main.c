#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(void)
{
  struct mhdr *mhdr = malloc(sizeof(struct mhdr));
  mhdr->stqh_first = NULL;
  mhdr->stqh_last  = &mhdr->stqh_first;

  int i;
  for (i = 0; i < 16; i++) {
    struct mbuf *mbuf = malloc(sizeof(struct mbuf));
    STAILQ_INSERT_TAIL(mhdr, mbuf, next);
    printf("%p ", mbuf);
  }
  printf(" ");

  for (i = 0; i < 16; i++) {
    struct mbuf *mbuf = mhdr->stqh_first;
    printf("%p ", mbuf);
    mhdr->stqh_first = mhdr->stqh_first->next.stqe_next;
  }
  printf(" ");

  return 0;
}
