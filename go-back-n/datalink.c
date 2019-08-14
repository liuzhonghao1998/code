#include <stdio.h>
#include <string.h>
#include<stdbool.h>

#include "protocol.h"
#include "datalink.h"

#define DATA_TIMER  2000

typedef struct { unsigned char data[PKT_LEN]; }packet;

struct FRAME { 
    unsigned char kind; /* FRAME_DATA */
    unsigned char ack;
    unsigned char seq;
    unsigned char data[PKT_LEN]; 
    unsigned int  padding;
};

static unsigned char frame_nr = 0, buffer[PKT_LEN] , nbuffered = 0 , MAX_SEQ = 15;
static unsigned char frame_expected = 0 , ack_expected = 0 , next_frame_to_send = 0;
static int phl_ready = 0;
packet window[16];

static bool between( unsigned char ack) {
	if (((ack_expected <= ack) && (ack < next_frame_to_send)) || ((next_frame_to_send < ack_expected) && (ack_expected <= ack)) || ((next_frame_to_send < ack_expected) && (ack < next_frame_to_send)))
		return true;
	else 
		return false;
} 

static void put_frame(unsigned char *frame, int len)
{
    *(unsigned int *)(frame + len) = crc32(frame, len);
    send_frame(frame, len + 4);
    phl_ready = 0;
}

static void send_data_frame(void)
{ 
    struct FRAME s;

    s.kind = FRAME_DATA;
    s.seq = next_frame_to_send;
	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
    memcpy(s.data, window[next_frame_to_send].data, PKT_LEN);
    dbg_frame("Send DATA %d %d, ID %d\n", s.seq, s.ack, *(short *)s.data);

    put_frame((unsigned char *)&s, 3 + PKT_LEN);
    start_timer(next_frame_to_send, DATA_TIMER);
}

/*static void send_ack_frame(void)
{
    struct FRAME s;

    s.kind = FRAME_ACK;
    s.ack = (frame_expected) % (MAX_SEQ + 1);

    dbg_frame("Send ACK  %d\n", s.ack);

    put_frame((unsigned char *)&s, 2);
}*/

int main(int argc, char **argv)
{
    int event, arg;
    struct FRAME f;  //用于收取帧
    int len = 0;

    protocol_init(argc, argv); 
    lprintf("Designed by Liu Zhonghao, build: " __DATE__"  "__TIME__"\n");

    enable_network_layer();
	

    for (;;) {
        event = wait_for_event(&arg);

        switch (event) {
        case NETWORK_LAYER_READY:
            get_packet(window[next_frame_to_send].data);
			nbuffered++;
			//printf("发送新帧frame_expected %d，next_frame_to_send %d ,ack_expected %d ,nbuffered %d\n", frame_expected, next_frame_to_send, ack_expected, nbuffered);
            send_data_frame();
			next_frame_to_send = (next_frame_to_send + 1) % (MAX_SEQ + 1);
            break;

        case PHYSICAL_LAYER_READY:
            phl_ready = 1;
            break;

        case FRAME_RECEIVED: 
            len = recv_frame((unsigned char *)&f, sizeof f);
            if (len < 5 || crc32((unsigned char *)&f, len) != 0) {
                dbg_event("**** Receiver Error, Bad CRC Checksum\n");
                break;
            }
            /*if (f.kind == FRAME_ACK) 
                dbg_frame("Recv ACK  %d\n", f.ack);*/
            if (f.kind == FRAME_DATA) {
                dbg_frame("Recv DATA %d %d, ID %d\n", f.seq, f.ack, *(short *)f.data);
				//send_ack_frame();
                if (f.seq == frame_expected) {
                    put_packet(f.data, len - 7);
					//printf("收到帧frame_expected %d，next_frame_to_send %d ,ack_expected %d ,nbuffered %d\n", frame_expected, next_frame_to_send, ack_expected, nbuffered);
                    frame_expected = (frame_expected + 1) % (MAX_SEQ + 1);
                }
				while (between(f.ack)) {
					nbuffered--;
					//printf("开始检索frame_expected %d，next_frame_to_send %d ,ack_expected %d ,nbuffered %d\n", frame_expected, next_frame_to_send, ack_expected, nbuffered);
					stop_timer(ack_expected);
					ack_expected = (ack_expected + 1) % (MAX_SEQ + 1);
				}
            } 
            break;

        case DATA_TIMEOUT:
            dbg_event("---- DATA %d timeout\n", arg); 
			//printf("开始重发frame_expected %d，next_frame_to_send %d ,ack_expected %d ,nbuffered %d\n", frame_expected, next_frame_to_send, ack_expected, nbuffered);
			next_frame_to_send = ack_expected; 
			for (unsigned char i = 1; i <= nbuffered; i++) {
				send_data_frame();
				next_frame_to_send = (next_frame_to_send + 1 ) % (MAX_SEQ + 1);
			}
            break;
        }

        if (nbuffered < MAX_SEQ && phl_ready)
            enable_network_layer();
        else
            disable_network_layer();
   }
}
