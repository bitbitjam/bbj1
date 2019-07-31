#ifndef _SRAM_HEADER_H_
#define _SRAM_HEADER_H_

/////////////////////////////////////////////////
// Posisiones
#define SRAM_CONTROL_POS_VALUE		    0x0000
#define SRAM_NUM_EXECUTIONS_POS_VALUE	0x0002
#define SRAM_RECORDS_TABLE_POS		    0x0004

////////////////////////////////////////////////
// valores
#define SRAM_CONTROL_VALUE			    3011

#define NUM_REGISTERS_RECORDS		    10
#define SIZE_RECORDS_REGISTER			16	// (char * 11 + long + u8 = 16 bytes por registro)

//////////////////////////////////////////////
// globales
u16 num_executions;

/////////////////////////////////////////////
// funciones
u8 initSRAM();
void writeRecordsTableSRAM();
void readRecordsTableSRAM();

///////////////////////////////////////////
// macros
#define writeNumExecutionsSRAM(); \
	SRAM_writeWord(SRAM_NUM_EXECUTIONS_POS_VALUE, num_executions);

#define loadNumExecutionsSRAM(); \
	num_executions = SRAM_readWord(SRAM_NUM_EXECUTIONS_POS_VALUE);

#define writeControlValueSRAM(); \
	SRAM_writeWord(SRAM_CONTROL_POS_VALUE, SRAM_CONTROL_VALUE);

#endif
