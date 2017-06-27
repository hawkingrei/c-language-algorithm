#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STAILQ_ENTRY(type)   \
struct {                     \
  struct type *stqe_next;    \
}

struct mbuf {
    uint32_t           magic;   /* mbuf magic (const) */
    STAILQ_ENTRY(mbuf) next;    /* next mbuf */
    uint8_t            *pos;    /* read marker */
    uint8_t            *last;   /* write marker */
    uint8_t            *start;  /* start of buffer (const) */
    uint8_t            *end;    /* end of buffer (const) */
};

#define STAILQ_HEAD(name, type)                                         \
struct name {                                                           \
    struct type *stqh_first; /* first element */                        \
    struct type **stqh_last; /* addr of last next element */            \
}

STAILQ_HEAD(mhdr, mbuf);

#define STAILQ_NEXT(elm, field)    ((elm)->field.stqe_next)

#define STAILQ_INSERT_TAIL(head, elm, field) do {   \
  STAILQ_NEXT((elm), field) = NULL;                 \
  *(head)->stqh_last = (elm);                       \
  (head)->stqh_last = &STAILQ_NEXT((elm), field);   \
} while (0)