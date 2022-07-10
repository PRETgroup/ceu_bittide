
typedef struct {
    BittideFrame frame;
    double scheduledTime;
} LinkFrame;

typedef struct {
    size_t head;
    size_t tail;
    size_t size;
    LinkFrame* data;
} LinkQueue;

static LinkQueue all_link_queues[256]; //max 256 links in this case


LinkFrame link_queue_read(int id) {

    LinkFrame handle = all_link_queues[id].data[all_link_queues[id].tail];
    all_link_queues[id].tail = (all_link_queues[id].tail + 1) % all_link_queues[id].size;
    return handle;
}

LinkFrame make_linkframe(BittideFrame data, double deadline) {
    LinkFrame new_frame = {data, deadline};
    return new_frame;
}

LinkFrame link_queue_peek(int id) {
    LinkFrame handle = all_link_queues[id].data[all_link_queues[id].tail];
    return handle;
}

double link_get_tail_time(int id){
    LinkFrame handle = all_link_queues[id].data[all_link_queues[id].tail];
    return handle.scheduledTime;
}

int link_queue_write(int id, LinkFrame handle) {
    if (((all_link_queues[id].head + 1) % all_link_queues[id].size) == all_link_queues[id].tail) {
        return -1;
    }
    all_link_queues[id].data[all_link_queues[id].head] = handle;
    all_link_queues[id].head = (all_link_queues[id].head + 1) % all_link_queues[id].size;
    return 0;
}

static int link_count = 0;
int link_make_queue(int size) {
    all_link_queues[link_count].head=0;
    all_link_queues[link_count].tail=0;
    all_link_queues[link_count].size=size;
    all_link_queues[link_count].data= malloc(sizeof(LinkFrame) * size);
    return link_count++;
}