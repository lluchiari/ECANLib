#ifndef _ECAN_LIB_
#define _ECAN_LIB_




void ECANInitialize();


void ECANSetOperationMode();
void ECANSetMask();

void ECANSetTxIdleLevel();
    


void ECANRead();

void ECANWrite(long, char[8], int, char);





#endif