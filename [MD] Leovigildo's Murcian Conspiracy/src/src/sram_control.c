#include "genesis.h"
#include "main.h"

/////////////////////////////////////////////////////////////////
//
// u8 initSRAM(){
// inicializa la SRAM
//
/////////////////////////////////////////////////////////////////
u8 initSRAM(){

	num_executions = 0;

	// Activar el acceso a SRAM
	SRAM_enable();

	// Si ya se ha escrito previamente en la SRAM lugar se cargan
	// los datos en las variables y buffers correspondientes
	if(SRAM_readWord(SRAM_CONTROL_POS_VALUE) == SRAM_CONTROL_VALUE){

		loadNumExecutionsSRAM();	// Numero de veces que se ha ejecutado del juego
		readRecordsTableSRAM();
	}
	else{ // En caso de se primera ejecucion escribir los valores inciales en la SRAM

		writeControlValueSRAM();	// escribimos el valor de control

		initRecords();              // inicia la tabla de records
		writeRecordsTableSRAM();
	}

	// Escribir numero de ejecuciones actualizado
	num_executions++;
	writeNumExecutionsSRAM();	// (macro)

	// Desconectar el accceso a SRAM
	SRAM_disable();

	// Devolver true para indicar que el acceso ha sido correcto
	return 1;
}

/////////////////////////////////////////////////////////////////
//
// void writeRecordsTableSRAM(){
// escribe la tabla de records en la sram
//
/////////////////////////////////////////////////////////////////
void writeRecordsTableSRAM(){

	u8 i, c;	// Indices

	for( i = 0; i < NUM_REGISTERS_RECORDS; i++){

		// Escribir nombres
		for( c = 0; c < 12; c++ )
			SRAM_writeByte(SRAM_RECORDS_TABLE_POS + (i * SIZE_RECORDS_REGISTER) + c, namesTable[i][c]);

		// Escribir puntuacion
		SRAM_writeLong(SRAM_RECORDS_TABLE_POS + (i * SIZE_RECORDS_REGISTER) + 12, pointsTable[i]);

		// escribe fase
		SRAM_writeByte(SRAM_RECORDS_TABLE_POS + (i * SIZE_RECORDS_REGISTER) + 15, stagesTable[i]);
	}

    SRAM_writeLong(SRAM_RECORDS_TABLE_POS + (i * SIZE_RECORDS_REGISTER) + 16, ad.achievements);
}


/////////////////////////////////////////////////////////////////
//
// void readRecordsTableSRAM(){
// lee la tabla de records en la sram
//
/////////////////////////////////////////////////////////////////
void readRecordsTableSRAM(){

	u8 i, c;	// Indices

	for( i  = 0; i < NUM_REGISTERS_RECORDS; i++){

		// Leer nombres
		for( c = 0; c < 12; c++ )
			namesTable[i][c] = SRAM_readByte(SRAM_RECORDS_TABLE_POS + (i * SIZE_RECORDS_REGISTER) + c);

		// Leer puntuacion
		pointsTable[i] = SRAM_readLong(SRAM_RECORDS_TABLE_POS + (i * SIZE_RECORDS_REGISTER) + 12);

		stagesTable[i] = SRAM_readByte(SRAM_RECORDS_TABLE_POS + (i * SIZE_RECORDS_REGISTER) + 15);
	}

    ad.achievements = SRAM_readLong(SRAM_RECORDS_TABLE_POS + (i * SIZE_RECORDS_REGISTER) + 16);
}

