
typedef struct {
    BittideFrame frame;
    double scheduledTime;
} LinkFrame;

typedef struct {
    size_t head;
    size_t tail;
    size_t size;
    uint16_t num_elements;
    LinkFrame* data;
} LinkQueue;


LinkFrame link_queue_read(LinkQueue* q) {
    LinkFrame handle = q->data[q->tail];
    q->tail = (q->tail + 1) % q->size;
    q->num_elements--;
    return handle;
}

LinkFrame make_linkframe(BittideFrame data, double deadline) {
    LinkFrame new_frame = {data, deadline};
    return new_frame;
}

LinkFrame link_queue_peek(LinkQueue* q) {
    LinkFrame handle = q->data[q->tail];
    return handle;
}

double link_get_tail_time(LinkQueue* q){
    if (q->num_elements == 0) return DBL_MAX;
    LinkFrame handle = q->data[q->tail];
    return handle.scheduledTime;
}

int link_queue_write(LinkQueue* q, LinkFrame handle) {
    if (((q->head + 1) % q->size) == q->tail) {
        return -1;
    }
    q->data[q->head] = handle;
    q->head = (q->head + 1) % q->size;
    q->num_elements++;
    return 0;
}

static int link_count = 0;
LinkQueue link_make_queue(int size) {
    LinkQueue q;
    q.head=0;
    q.tail=0;
    q.size=size;
    q.num_elements = 0;
    q.data= malloc(sizeof(LinkFrame) * size);
    return q;
}