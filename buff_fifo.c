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
    BittideFrame* data;
} BuffQueue;

static BuffQueue all_buff_queues[256]; //max 256 buffs in this case
BittideFrame buff_queue_read(int id) {

    BittideFrame handle = all_buff_queues[id].data[all_buff_queues[id].tail];
    all_buff_queues[id].tail = (all_buff_queues[id].tail + 1) % all_buff_queues[id].size;
    return handle;
}

BittideFrame buff_queue_peek(int id) {
    BittideFrame handle = all_buff_queues[id].data[all_buff_queues[id].tail];
    return handle;
}
int buff_queue_write(int id, BittideFrame handle) {
    if (((all_buff_queues[id].head + 1) % all_buff_queues[id].size) == all_buff_queues[id].tail) {
        return -1;
    }
    all_buff_queues[id].data[all_buff_queues[id].head] = handle;
    all_buff_queues[id].head = (all_buff_queues[id].head + 1) % all_buff_queues[id].size;
    return 0;
}

void fill_buffer(int bufferHandle, int numberOfFrames) {
    for(int i = 0; i < numberOfFrames; i++)
        buff_queue_write(bufferHandle,create_empty_bittide_frame());
}

int get_buffer_occupancy(int id) {
    return all_buff_queues[id].head-all_buff_queues[id].tail;
}

static int buff_count = 0;
int buff_make_queue(int size) {
    all_buff_queues[buff_count].head=0;
    all_buff_queues[buff_count].tail=0;
    all_buff_queues[buff_count].size=size;
    all_buff_queues[buff_count].data= malloc(sizeof(BittideFrame) * size);
    return buff_count++;
}