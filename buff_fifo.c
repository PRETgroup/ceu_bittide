typedef struct
{
    int value;
    int ugn;
} BittideFrame;

BittideFrame create_empty_bittide_frame() {
    BittideFrame bf = {0,0};
    return bf;
}

typedef struct {
    size_t head;
    size_t tail;
    size_t size;
    uint16_t num_elements;
    BittideFrame* data;
} BuffQueue;

BittideFrame buff_queue_read(BuffQueue* bq) {

    BittideFrame handle = bq->data[bq->tail];
    bq->tail = (bq->tail + 1) % bq->size;
    bq->num_elements--;
    return handle;
}

BittideFrame buff_queue_peek(BuffQueue* bq) {
    BittideFrame handle = bq->data[bq->tail];
    return handle;
}
int buff_queue_write(BuffQueue* bq, BittideFrame handle) {
    if (((bq->head + 1) % bq->size) == bq->tail) {
        return -1;
    }
    bq->data[bq->head] = handle;
    bq->head = (bq->head + 1) % bq->size;
    bq->num_elements++;
    return 0;
}

void fill_buffer(BuffQueue* bufferHandle, int numberOfFrames) {
    for(int i = 0; i < numberOfFrames; i++)
        buff_queue_write(bufferHandle,create_empty_bittide_frame());
}

int get_buffer_occupancy(BuffQueue* bq) {
    return bq->num_elements;
}

double get_buffer_occupancy_pcnt(BuffQueue* bq) {
    return (double)get_buffer_occupancy(bq) / (double)bq->size;
}

BuffQueue buff_make_queue(int size) {
    BuffQueue bq;
    bq.head=0;
    bq.tail=0;
    bq.size=size;
    bq.num_elements = 0;
    bq.data= malloc(sizeof(BittideFrame) * size);
    fill_buffer(&bq, size/2);
    return bq;
}