
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
    BittideFrame frame;
    double scheduledTime;
} LinkFrame;

typedef struct {
    size_t head;
    size_t tail;
    size_t size;
    LinkFrame* data;
} queue_t;

static queue_t all_queues[256]; //max 256 links in this case

LinkFrame queue_read(int id) {

    LinkFrame handle = all_queues[id].data[all_queues[id].tail];
    all_queues[id].tail = (all_queues[id].tail + 1) % all_queues[id].size;
    return handle;
}

LinkFrame queue_peek(int id) {
    LinkFrame handle = all_queues[id].data[all_queues[id].tail];
    return handle;
}

double get_tail_time(int id){
    LinkFrame handle = all_queues[id].data[all_queues[id].tail];
    return handle.scheduledTime;
}

int queue_write(int id, LinkFrame handle) {
    if (((all_queues[id].head + 1) % all_queues[id].size) == all_queues[id].tail) {
        return -1;
    }
    all_queues[id].data[all_queues[id].head] = handle;
    all_queues[id].head = (all_queues[id].head + 1) % all_queues[id].size;
    return 0;
}

static int count = 0;
int make_queue(int size) {
    all_queues[count].head=0;
    all_queues[count].tail=0;
    all_queues[count].size=size;
    all_queues[count].data= malloc(sizeof(LinkFrame) * size);
    return count++;
}