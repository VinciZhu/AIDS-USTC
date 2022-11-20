#define LIST_INIT_SIZE 100
#define LIST_INC_SIZE 20

typedef char ElemType;
typedef struct LNode {
  ElemType data;
  struct LNode *next;
} LNode, *LinkList;

void InitList_L(LinkList &L);

void DestroyList_L(LinkList &L);

bool ListEmpty_L(LinkList L);

int ListLength_L(LinkList L);

int LocateItem_L(LinkList L, ElemType e);

bool GetItem_L(LinkList L, int i, ElemType &e);

bool ListInsert_L(LinkList &L, int i, ElemType e);

bool ListDelete_L(LinkList &L, int i, ElemType &e);

void ListTraverse_L(LinkList L);