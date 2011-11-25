#ifndef _PACKET_H_
#define _PACKET_H_

struct pktHdr {
	char pType;
};

struct pktBody {
	int xPos;
	int yPos;
};

#endif
