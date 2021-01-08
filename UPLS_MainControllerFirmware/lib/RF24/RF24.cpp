/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */


#include "nRF24L01.h"
#include "RF24.h"
#include <string.h>

#define _NRF24L01P_SPI_MAX_DATA_RATE     10000000

/****************************************************************************/

inline void RF24::beginTransaction()
{
	_csn = 0;
}

/****************************************************************************/

inline void RF24::endTransaction() 
{
    _csn = 1;
}

/****************************************************************************/

uint8_t RF24::read_register(uint8_t reg, uint8_t* buf, uint8_t len)
{
	uint8_t status;
	
	beginTransaction();
	
	status = _SPI.write( R_REGISTER | ( REGISTER_MASK & reg ) );
	while ( len-- )
	  *buf++ = _SPI.write(0xff);
	
	endTransaction();
	
	return status;
}

/****************************************************************************/

uint8_t RF24::read_register(uint8_t reg)
{
	uint8_t result;
	
	beginTransaction();
	
	_SPI.write( R_REGISTER | ( REGISTER_MASK & reg ) );
	result = _SPI.write(0xff);
	
	endTransaction();
	
	return result;
}

/****************************************************************************/

uint8_t RF24::write_register(uint8_t reg, const uint8_t* buf, uint8_t len)
{
	uint8_t status;
	
	beginTransaction();
	
	status = _SPI.write( W_REGISTER | ( REGISTER_MASK & reg ) );
	while ( len-- )
	  _SPI.write(*buf++);
	
	endTransaction();
	
	return status;
}

/****************************************************************************/

uint8_t RF24::write_register(uint8_t reg, uint8_t value)
{
	uint8_t status;
	
	beginTransaction();
	status = _SPI.write( W_REGISTER | ( REGISTER_MASK & reg ) );
	_SPI.write(value);
	endTransaction();
	
	return status;
}

/****************************************************************************/

uint8_t RF24::write_payload(const void* buf, uint8_t data_len, const uint8_t writeType)
{
	uint8_t status;
	const uint8_t* current = reinterpret_cast<const uint8_t*>(buf);
	
	data_len = rf24_min(data_len, payload_size);
	uint8_t blank_len = dynamic_payloads_enabled ? 0 : payload_size - data_len;
	
	beginTransaction();

	status = _SPI.write( writeType );
	while ( data_len-- )
		_SPI.write(*current++);
	while ( blank_len-- )
	  _SPI.write(0);
	
	endTransaction();
	
	return status;
}

/****************************************************************************/

uint8_t RF24::read_payload(void* buf, uint8_t data_len)
{
	uint8_t status;
	uint8_t* current = reinterpret_cast<uint8_t*>(buf);
	
	if (data_len > payload_size) data_len = payload_size;
	uint8_t blank_len = dynamic_payloads_enabled ? 0 : payload_size - data_len;
	
	beginTransaction();

	status = _SPI.write( R_RX_PAYLOAD );
	while ( data_len-- )
		*current++ = _SPI.write(0xFF);
	
	while ( blank_len-- )
		_SPI.write(0xff);
	
	endTransaction();
	
	return status;
}

/****************************************************************************/

uint8_t RF24::flush_rx(void)
{
  return spiTrans( FLUSH_RX );
}

/****************************************************************************/

uint8_t RF24::flush_tx(void)
{
  return spiTrans( FLUSH_TX );
}

/****************************************************************************/

uint8_t RF24::spiTrans(uint8_t cmd){

  uint8_t status;
  
  beginTransaction();
  status = _SPI.write( cmd );
  endTransaction();
  
  return status;
}

/****************************************************************************/

uint8_t RF24::get_status(void)
{
  return spiTrans(RF24_NOP);
}

/****************************************************************************/

RF24::RF24(PinName mosi, PinName miso, PinName sck, PinName csn, PinName ce) :
	_ce(ce), _csn(csn), p_variant(false), _SPI(mosi, miso, sck),
	payload_size(32), dynamic_payloads_enabled(false), addr_width(5), csDelay(5)//,pipe0_reading_address(0)
{
	pipe0_reading_address[0] = 0;

    _SPI.frequency(_NRF24L01P_SPI_MAX_DATA_RATE/5);     // 2Mbit, 1/5th the maximum transfer rate for the SPI bus
    _SPI.format(8,0);                                   // 8-bit, ClockPhase = 0, ClockPolarity = 0

    _t.start();
}

/****************************************************************************/

void RF24::setChannel(uint8_t channel)
{
	const uint8_t max_channel = 125;
	write_register(RF_CH, rf24_min(channel,max_channel));
}

uint8_t RF24::getChannel()
{
	return read_register(RF_CH);
}
/****************************************************************************/

void RF24::setPayloadSize(uint8_t size)
{
  payload_size = rf24_min(size,32);
}

/****************************************************************************/

uint8_t RF24::getPayloadSize(void)
{
	return payload_size;
}

/****************************************************************************/

#if !defined (MINIMAL)

static const char rf24_datarate_e_str_0[] = "1MBPS";
static const char rf24_datarate_e_str_1[] = "2MBPS";
static const char rf24_datarate_e_str_2[] = "250KBPS";
static const char * const rf24_datarate_e_str_P[] = {
  rf24_datarate_e_str_0,
  rf24_datarate_e_str_1,
  rf24_datarate_e_str_2,
};
static const char rf24_model_e_str_0[] = "nRF24L01";
static const char rf24_model_e_str_1[] = "nRF24L01+";
static const char * const rf24_model_e_str_P[] = {
  rf24_model_e_str_0,
  rf24_model_e_str_1,
};
static const char rf24_crclength_e_str_0[] = "Disabled";
static const char rf24_crclength_e_str_1[] = "8 bits";
static const char rf24_crclength_e_str_2[]= "16 bits" ;
static const char * const rf24_crclength_e_str_P[] = {
  rf24_crclength_e_str_0,
  rf24_crclength_e_str_1,
  rf24_crclength_e_str_2,
};
static const char rf24_pa_dbm_e_str_0[] = "PA_MIN";
static const char rf24_pa_dbm_e_str_1[] = "PA_LOW";
static const char rf24_pa_dbm_e_str_2[] = "PA_HIGH";
static const char rf24_pa_dbm_e_str_3[] = "PA_MAX";
static const char * const rf24_pa_dbm_e_str_P[] = {
  rf24_pa_dbm_e_str_0,
  rf24_pa_dbm_e_str_1,
  rf24_pa_dbm_e_str_2,
  rf24_pa_dbm_e_str_3,
};

#endif
/****************************************************************************/

bool RF24::begin(void)
{
	uint8_t setup = 0;
	  
	//_SPI.begin();
	ce(0);
	csn(1);
	
	// Must allow the radio time to settle else configuration bits will not necessarily stick.
	// This is actually only required following power up but some settling time also appears to
	// be required after resets too. For full coverage, we'll always assume the worst.
	// Enabling 16b CRC is by far the most obvious case if the wrong timing is used - or skipped.
	// Technically we require 4.5ms + 14us as a worst case. We'll just call it 5ms for good measure.
	// WARNING: Delay is based on P-variant whereby non-P *may* require different timing.
	wait_ms(5);
	
	// Reset NRF_CONFIG and enable 16-bit CRC.
	write_register( NRF_CONFIG, 0x0C ) ;
	
	// Set 1500uS (minimum for 32B payload in ESB@250KBPS) timeouts, to make testing a little easier
	// WARNING: If this is ever lowered, either 250KBS mode with AA is broken or maximum packet
	// sizes must never be used. See documentation for a more complete explanation.
	setRetries(5,15);
	
	// Reset value is MAX
	//setPALevel( RF24_PA_MAX ) ;
	
	// check for connected module and if this is a p nRF24l01 variant
	//
	if( setDataRate( RF24_250KBPS ) )
	{
		p_variant = true ;
	}
	setup = read_register(RF_SETUP);
	/*if( setup == 0b00001110 )     // register default for nRF24L01P
	{
	  p_variant = true ;
	}*/
	
	// Then set the data rate to the slowest (and most reliable) speed supported by all
	// hardware.
	setDataRate( RF24_1MBPS ) ;
	
	// Initialize CRC and request 2-byte (16bit) CRC
	//setCRCLength( RF24_CRC_16 ) ;
	
	// Disable dynamic payloads, to match dynamic_payloads_enabled setting - Reset value is 0
	toggle_features();
	write_register(FEATURE, 0);
	write_register(DYNPD, 0);
	dynamic_payloads_enabled = false;
	
	// Reset current status
	// Notice reset and flush is the last thing we do
	write_register(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );
	
	// Set up default configuration.  Callers can always change it later.
	// This channel should be universally safe and not bleed over into adjacent
	// spectrum.
	setChannel(76);
	
	// Flush buffers
	flush_rx();
	flush_tx();
	
	powerUp(); //Power up by default when begin() is called
	
	// Enable PTX, do not write CE high so radio will remain in standby I mode ( 130us max to transition to RX or TX instead of 1500us from powerUp )
	// PTX should use only 22uA of power
	write_register(NRF_CONFIG, ( read_register(NRF_CONFIG) ) & ~_BV(PRIM_RX) );
	
	// if setup is 0 or ff then there was no response from module
	return ( setup != 0 && setup != 0xff );
}

/****************************************************************************/

bool RF24::isChipConnected()
{
	uint8_t setup = read_register(SETUP_AW);
	if(setup >= 1 && setup <= 3)
	{
		return true;
	}
	
	return false;
}

/****************************************************************************/

void RF24::startListening(void)
{	
	write_register(NRF_CONFIG, read_register(NRF_CONFIG) | _BV(PRIM_RX));
	write_register(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );
	
	ce(1);
	// Restore the pipe0 adddress, if exists
	if (pipe0_reading_address[0] > 0)
	  write_register(RX_ADDR_P0, pipe0_reading_address, addr_width);	
	else
		closeReadingPipe(0);
	
	// Flush buffers
	//flush_rx();
	if(read_register(FEATURE) & _BV(EN_ACK_PAY))
		flush_tx();
	
	// Go!
	//delayMicroseconds(100);
}

/****************************************************************************/
static const uint8_t child_pipe_enable[] =
{
	ERX_P0, ERX_P1, ERX_P2, ERX_P3, ERX_P4, ERX_P5
};

void RF24::stopListening(void)
{  
	ce(0);
	
	wait_us(txDelay);
	
	if(read_register(FEATURE) & _BV(EN_ACK_PAY))
	{
		wait_us(txDelay); //200
		flush_tx();
	}
	//flush_rx();
	write_register(NRF_CONFIG, ( read_register(NRF_CONFIG) ) & ~_BV(PRIM_RX) );
	
	write_register(EN_RXADDR, read_register(EN_RXADDR) | _BV(child_pipe_enable[0])); // Enable RX on pipe0
}

/****************************************************************************/

void RF24::powerDown(void)
{
  ce(0); // Guarantee CE is low on powerDown
  write_register(NRF_CONFIG,read_register(NRF_CONFIG) & ~_BV(PWR_UP));
}

/****************************************************************************/

//Power up now. Radio will not power down unless instructed by MCU for config changes etc.
void RF24::powerUp(void)
{
   uint8_t cfg = read_register(NRF_CONFIG);

   // if not powered up then power up and wait for the radio to initialize
   if (!(cfg & _BV(PWR_UP))){
      write_register(NRF_CONFIG, cfg | _BV(PWR_UP));

      // For nRF24L01+ to go from power down mode to TX or RX mode it must first pass through stand-by mode.
	  // There must be a delay of Tpd2stby (see Table 16.) after the nRF24L01+ leaves power down mode before
	  // the CEis set high. - Tpd2stby can be up to 5ms per the 1.0 datasheet
      wait_ms(5);
   }
}

/******************************************************************/

//Similar to the previous write, clears the interrupt flags
bool RF24::write( const void* buf, uint8_t len, const bool multicast )
{
	//Start Writing
	startFastWrite(buf,len,multicast);
	
	while( !( get_status()  & ( _BV(TX_DS) | _BV(MAX_RT) ))) { ; }
    
	ce(0);

	uint8_t status = write_register(NRF_STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );

	//Max retries exceeded
	if( status & _BV(MAX_RT))
	{
		flush_tx(); //Only going to be 1 packet int the FIFO at a time using this method, so just flush
		return 0;
	}
	//TX OK 1 or 0
	return 1;
}

bool RF24::write( const void* buf, uint8_t len )
{
	return write(buf,len,0);
}
/****************************************************************************/

//For general use, the interrupt flags are not important to clear
bool RF24::writeBlocking( const void* buf, uint8_t len, uint32_t timeout )
{
	//Block until the FIFO is NOT full.
	//Keep track of the MAX retries and set auto-retry if seeing failures
	//This way the FIFO will fill up and allow blocking until packets go through
	//The radio will auto-clear everything in the FIFO as long as CE remains high

	uint32_t timer = millis();							  //Get the time that the payload transmission started

	while( ( get_status()  & ( _BV(TX_FULL) ))) {		  //Blocking only if FIFO is full. This will loop and block until TX is successful or timeout

		if( get_status() & _BV(MAX_RT)){					  //If MAX Retries have been reached
			reUseTX();										  //Set re-transmit and clear the MAX_RT interrupt flag
			if(millis() - timer > timeout) { return 0; }		  //If this payload has exceeded the user-defined timeout, exit and return 0
		}
  	}

  	//Start Writing
	startFastWrite(buf,len,0);								  //Write the payload if a buffer is clear

	return 1;												  //Return 1 to indicate successful transmission
}

/****************************************************************************/

void RF24::reUseTX() 
{
	write_register(NRF_STATUS,_BV(MAX_RT) );			  //Clear max retry flag
	spiTrans( REUSE_TX_PL );
	ce(0);										  //Re-Transfer packet
	ce(1);
}

/****************************************************************************/

bool RF24::writeFast( const void* buf, uint8_t len, const bool multicast )
{
	//Block until the FIFO is NOT full.
	//Keep track of the MAX retries and set auto-retry if seeing failures
	//Return 0 so the user can control the retries and set a timer or failure counter if required
	//The radio will auto-clear everything in the FIFO as long as CE remains high

	#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
		uint32_t timer = millis();
	#endif
	
	while( ( get_status()  & ( _BV(TX_FULL) ))) {			  //Blocking only if FIFO is full. This will loop and block until TX is successful or fail

		if( get_status() & _BV(MAX_RT)){
			//reUseTX();										  //Set re-transmit
			write_register(NRF_STATUS,_BV(MAX_RT) );			  //Clear max retry flag
			return 0;										  //Return 0. The previous payload has been retransmitted
															  //From the user perspective, if you get a 0, just keep trying to send the same payload
		}
		#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
			if(millis() - timer > 95 ){			
				errNotify();
				#if defined (FAILURE_HANDLING)
				return 0;							
				#endif
			}
		#endif
  	}
		     //Start Writing
	startFastWrite(buf,len,multicast);

	return 1;
}

bool RF24::writeFast( const void* buf, uint8_t len )
{
	return writeFast(buf,len,0);
}

/****************************************************************************/

//Per the documentation, we want to set PTX Mode when not listening. Then all we do is write data and set CE high
//In this mode, if we can keep the FIFO buffers loaded, packets will transmit immediately (no 130us delay)
//Otherwise we enter Standby-II mode, which is still faster than standby mode
//Also, we remove the need to keep writing the config register over and over and delaying for 150 us each time if sending a stream of data

void RF24::startFastWrite( const void* buf, uint8_t len, const bool multicast, bool startTx){ //TMRh20

	//write_payload( buf,len);
	write_payload( buf, len,multicast ? W_TX_PAYLOAD_NO_ACK : W_TX_PAYLOAD ) ;
	if(startTx){
		ce(1);
	}

}

/****************************************************************************/

//Added the original startWrite back in so users can still use interrupts, ack payloads, etc
//Allows the library to pass all tests
void RF24::startWrite( const void* buf, uint8_t len, const bool multicast ){

    // Send the payload

    //write_payload( buf, len );
    write_payload( buf, len,multicast? W_TX_PAYLOAD_NO_ACK : W_TX_PAYLOAD ) ;
    ce(1);
    wait_us(10);
  
    ce(0);


}

/****************************************************************************/

bool RF24::rxFifoFull()
{
	return read_register(FIFO_STATUS) & _BV(RX_FULL);
}
/****************************************************************************/

bool RF24::txStandBy(){

    #if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
		uint32_t timeout = millis();
	#endif
	while( ! (read_register(FIFO_STATUS) & _BV(TX_EMPTY)) ){
		if( get_status() & _BV(MAX_RT)){
			write_register(NRF_STATUS,_BV(MAX_RT) );
			ce(0);
			flush_tx();    //Non blocking, flush the data
			return 0;
		}
		#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
			if( millis() - timeout > 95){
				errNotify();
				#if defined (FAILURE_HANDLING)
				return 0;	
				#endif
			}
		#endif
	}

	ce(0);			   //Set STANDBY-I mode
	return 1;
}

/****************************************************************************/

bool RF24::txStandBy(uint32_t timeout, bool startTx){

    if(startTx)
	{
	  stopListening();
	  ce(1);
	}
	uint32_t start = millis();

	while( ! (read_register(FIFO_STATUS) & _BV(TX_EMPTY)) ){
		if( get_status() & _BV(MAX_RT)){
			write_register(NRF_STATUS,_BV(MAX_RT) );
				ce(0);										  //Set re-transmit
				ce(1);
				if(millis() - start >= timeout){
					ce(0); flush_tx(); return 0;
				}
		}
		#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
			if( millis() - start > (timeout+95)){
				errNotify();
				#if defined (FAILURE_HANDLING)
				return 0;	
				#endif
			}
		#endif
	}

	
	ce(0);				   //Set STANDBY-I mode
	return 1;

}

/****************************************************************************/

void RF24::maskIRQ(bool tx, bool fail, bool rx){

	uint8_t config = read_register(NRF_CONFIG);
	/* clear the interrupt flags */
	config &= ~(1 << MASK_MAX_RT | 1 << MASK_TX_DS | 1 << MASK_RX_DR);
	/* set the specified interrupt flags */
	config |= fail << MASK_MAX_RT | tx << MASK_TX_DS | rx << MASK_RX_DR;
	write_register(NRF_CONFIG, config);
}

/****************************************************************************/

uint8_t RF24::getDynamicPayloadSize(void)
{
	uint8_t result = 0;
	
	beginTransaction();
	
	_SPI.write( R_RX_PL_WID );
	result = _SPI.write(0xff);
	
	endTransaction();
	
	if(result > 32) 
	{
		flush_rx();
		wait_ms(2);
		return 0; 
	}
	
	return result;
}

/****************************************************************************/

bool RF24::available(void)
{
	return available(NULL);
}

/****************************************************************************/

bool RF24::available(uint8_t* pipe_num)
{
	if (!( read_register(FIFO_STATUS) & _BV(RX_EMPTY) ))
	{
		// If the caller wants the pipe number, include that
		if ( pipe_num )
		{
			uint8_t status = get_status();
			*pipe_num = ( status >> RX_P_NO ) & 0x07;
		}
		return 1;
	}
	
	return 0;
}

/****************************************************************************/

void RF24::read( void* buf, uint8_t len )
{
	// Fetch the payload
	read_payload( buf, len );
	
	//Clear the two possible interrupt flags with one command
	write_register(NRF_STATUS,_BV(RX_DR) | _BV(MAX_RT) | _BV(TX_DS) );
}

/****************************************************************************/

void RF24::whatHappened(bool& tx_ok,bool& tx_fail,bool& rx_ready)
{
	// Read the status & reset the status in one easy call
	// Or is that such a good idea?
	uint8_t status = write_register(NRF_STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );
	
	// Report to the user what happened
	tx_ok = status & _BV(TX_DS);
	tx_fail = status & _BV(MAX_RT);
	rx_ready = status & _BV(RX_DR);
}

/****************************************************************************/

void RF24::openWritingPipe(uint64_t value)
{
	// Note that AVR 8-bit uC's store this LSB first, and the NRF24L01(+)
	// expects it LSB first too, so we're good.
	
	write_register(RX_ADDR_P0, reinterpret_cast<uint8_t*>(&value), addr_width);
	write_register(TX_ADDR, reinterpret_cast<uint8_t*>(&value), addr_width);
	
	
	//const uint8_t max_payload_size = 32;
	//write_register(RX_PW_P0,rf24_min(payload_size,max_payload_size));
	write_register(RX_PW_P0,payload_size);
}

/****************************************************************************/
void RF24::openWritingPipe(const uint8_t *address)
{
	// Note that AVR 8-bit uC's store this LSB first, and the NRF24L01(+)
	// expects it LSB first too, so we're good.
	
	write_register(RX_ADDR_P0,address, addr_width);
	write_register(TX_ADDR, address, addr_width);
	
	//const uint8_t max_payload_size = 32;
	//write_register(RX_PW_P0,rf24_min(payload_size,max_payload_size));
	write_register(RX_PW_P0,payload_size);
}

/****************************************************************************/
static const uint8_t child_pipe[] =
{
	RX_ADDR_P0, RX_ADDR_P1, RX_ADDR_P2, RX_ADDR_P3, RX_ADDR_P4, RX_ADDR_P5
};
static const uint8_t child_payload_size[] =
{
	RX_PW_P0, RX_PW_P1, RX_PW_P2, RX_PW_P3, RX_PW_P4, RX_PW_P5
};


void RF24::openReadingPipe(uint8_t child, uint64_t address)
{
	// If this is pipe 0, cache the address.  This is needed because
	// openWritingPipe() will overwrite the pipe 0 address, so
	// startListening() will have to restore it.
	if (child == 0){
		memcpy(pipe0_reading_address, &address, addr_width);
	}
	
	if (child <= 6)
	{
		// For pipes 2-5, only write the LSB
		if ( child < 2 )
			write_register(child_pipe[child], reinterpret_cast<const uint8_t*>(&address), addr_width);
		else
			write_register(child_pipe[child], reinterpret_cast<const uint8_t*>(&address), 1);
		
		write_register(child_payload_size[child], payload_size);
		
		// Note it would be more efficient to set all of the bits for all open
		// pipes at once.  However, I thought it would make the calling code
		// more simple to do it this way.
		write_register(EN_RXADDR,read_register(EN_RXADDR) | _BV(child_pipe_enable[child]));
	}
}

/****************************************************************************/
void RF24::setAddressWidth(uint8_t a_width)
{
	if(a_width -= 2)
	{
		write_register(SETUP_AW, a_width % 4);
		addr_width = (a_width % 4) + 2;
	}
	else
	{
        write_register(SETUP_AW, 0);
        addr_width = 2;
    }
}

/****************************************************************************/

void RF24::openReadingPipe(uint8_t child, const uint8_t *address)
{
	// If this is pipe 0, cache the address.  This is needed because
	// openWritingPipe() will overwrite the pipe 0 address, so
	// startListening() will have to restore it.
	if (child == 0){
		memcpy(pipe0_reading_address,address,addr_width);
	}
	if (child <= 6)
	{
		// For pipes 2-5, only write the LSB
		if ( child < 2 )
			write_register(child_pipe[child], address, addr_width);
		else
			write_register(child_pipe[child], address, 1);

		write_register(child_payload_size[child],payload_size);
	
		// Note it would be more efficient to set all of the bits for all open
		// pipes at once.  However, I thought it would make the calling code
		// more simple to do it this way.
		write_register(EN_RXADDR,read_register(EN_RXADDR) | _BV(child_pipe_enable[child]));
	}
}

/****************************************************************************/

void RF24::closeReadingPipe( uint8_t pipe )
{
	write_register(EN_RXADDR,read_register(EN_RXADDR) & ~_BV(child_pipe_enable[pipe]));
}

/****************************************************************************/

void RF24::toggle_features(void)
{
    beginTransaction();
	_SPI.write( ACTIVATE );
    _SPI.write( 0x73 );
	endTransaction();
}

/****************************************************************************/

void RF24::enableDynamicPayloads(void)
{
	// Enable dynamic payload throughout the system
	
	//toggle_features();
	write_register(FEATURE,read_register(FEATURE) | _BV(EN_DPL) );
	
	// Enable dynamic payload on all pipes
	//
	// Not sure the use case of only having dynamic payload on certain
	// pipes, so the library does not support it.
	write_register(DYNPD,read_register(DYNPD) | _BV(DPL_P5) | _BV(DPL_P4) | _BV(DPL_P3) | _BV(DPL_P2) | _BV(DPL_P1) | _BV(DPL_P0));
	
	dynamic_payloads_enabled = true;
}

/****************************************************************************/
void RF24::disableDynamicPayloads(void)
{
	// Disables dynamic payload throughout the system.  Also disables Ack Payloads
	
	//toggle_features();
	write_register(FEATURE, 0);
	
	// Disable dynamic payload on all pipes
	//
	// Not sure the use case of only having dynamic payload on certain
	// pipes, so the library does not support it.
	write_register(DYNPD, 0);
	
	dynamic_payloads_enabled = false;
}

/****************************************************************************/

void RF24::enableAckPayload(void)
{
	//
	// enable ack payload and dynamic payload features
	//
	
	//toggle_features();
	write_register(FEATURE,read_register(FEATURE) | _BV(EN_ACK_PAY) | _BV(EN_DPL) );
	
	//
	// Enable dynamic payload on pipes 0 & 1
	//
	
	write_register(DYNPD,read_register(DYNPD) | _BV(DPL_P1) | _BV(DPL_P0));
	dynamic_payloads_enabled = true;
}

/****************************************************************************/

void RF24::enableDynamicAck(void)
{
	//
	// enable dynamic ack features
	//
    //toggle_features();
    write_register(FEATURE,read_register(FEATURE) | _BV(EN_DYN_ACK) );
}

/****************************************************************************/

void RF24::writeAckPayload(uint8_t pipe, const void* buf, uint8_t len)
{
	const uint8_t* current = reinterpret_cast<const uint8_t*>(buf);
	
	uint8_t data_len = rf24_min(len,32);
	
	beginTransaction();

	_SPI.write(W_ACK_PAYLOAD | ( pipe & 0x07 ) );
	while ( data_len-- )
		_SPI.write(*current++);

	endTransaction();
}

/****************************************************************************/

bool RF24::isAckPayloadAvailable(void)
{
	return ! (read_register(FIFO_STATUS) & _BV(RX_EMPTY));
}

/****************************************************************************/

bool RF24::isPVariant(void)
{
	return p_variant ;
}

/****************************************************************************/

void RF24::setAutoAck(bool enable)
{
	if ( enable )
		write_register(EN_AA, 0x3F);
	else
		write_register(EN_AA, 0);
}

/****************************************************************************/

void RF24::setAutoAck( uint8_t pipe, bool enable )
{
	if ( pipe <= 6 )
	{
		  uint8_t en_aa = read_register( EN_AA ) ;
		  
		  if( enable )
			  en_aa |= _BV(pipe) ;
		  else
			  en_aa &= ~_BV(pipe) ;
		  
		  write_register( EN_AA, en_aa ) ;
	}
}

/****************************************************************************/

bool RF24::testCarrier(void)
{
	return ( read_register(CD) & 1 );
}

/****************************************************************************/

bool RF24::testRPD(void)
{
	return ( read_register(RPD) & 1 ) ;
}

/****************************************************************************/

void RF24::setPALevel(uint8_t level)
{
	uint8_t setup = read_register(RF_SETUP) & 0xF8;
	
	if(level > 3) 							// If invalid level, go to max PA
		level = (RF24_PA_MAX << 1) + 1;		// +1 to support the SI24R1 chip extra bit
	else
		level = (level << 1) + 1;	 		// Else set level as requested
	
	write_register( RF_SETUP, setup |= level ) ;	// Write it to the chip
}

/****************************************************************************/

uint8_t RF24::getPALevel(void)
{
	return (read_register(RF_SETUP) & (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH))) >> 1;
}

/****************************************************************************/

bool RF24::setDataRate(rf24_datarate_e speed)
{
	bool result = false;
	uint8_t setup = read_register(RF_SETUP) ;
	
	// HIGH and LOW '00' is 1Mbs - our default
	setup &= ~(_BV(RF_DR_LOW) | _BV(RF_DR_HIGH)) ;
	
#if !defined(F_CPU) || F_CPU > 20000000
		txDelay=250;
#else //16Mhz Arduino
		txDelay=85;
#endif

	if( speed == RF24_250KBPS )
	{
		// Must set the RF_DR_LOW to 1; RF_DR_HIGH (used to be RF_DR) is already 0
		// Making it '10'.
		setup |= _BV( RF_DR_LOW ) ;
		
#if !defined(F_CPU) || F_CPU > 20000000
		txDelay=450;
#else //16Mhz Arduino
		txDelay=155;
#endif
	}
	else
	{
		// Set 2Mbs, RF_DR (RF_DR_HIGH) is set 1
		// Making it '01'
		if ( speed == RF24_2MBPS )
		{
			setup |= _BV(RF_DR_HIGH);

#if !defined(F_CPU) || F_CPU > 20000000
			txDelay=190;
#else //16Mhz Arduino
			txDelay=65;
#endif
		}
	}

	write_register(RF_SETUP,setup);
	
	// Verify our result
	if ( read_register(RF_SETUP) == setup )
		result = true;

	return result;
}

/****************************************************************************/

rf24_datarate_e RF24::getDataRate( void )
{
	rf24_datarate_e result ;
	uint8_t dr = read_register(RF_SETUP) & (_BV(RF_DR_LOW) | _BV(RF_DR_HIGH));
	
	// switch uses RAM (evil!)
	// Order matters in our case below
	if ( dr == _BV(RF_DR_LOW) )
	{
		// '10' = 250KBPS
		result = RF24_250KBPS ;
	}
	else if ( dr == _BV(RF_DR_HIGH) )
	{
		// '01' = 2MBPS
		result = RF24_2MBPS ;
	}
	else
	{
		// '00' = 1MBPS
		result = RF24_1MBPS ;
	}
	return result ;
}

/****************************************************************************/

void RF24::setCRCLength(rf24_crclength_e length)
{
	uint8_t config = read_register(NRF_CONFIG) & ~( _BV(CRCO) | _BV(EN_CRC)) ;
	
	// switch uses RAM (evil!)
	if ( length == RF24_CRC_DISABLED )
	{
		// Do nothing, we turned it off above.
	}
	else if ( length == RF24_CRC_8 )
	{
		config |= _BV(EN_CRC);
	}
	else
	{
		config |= _BV(EN_CRC);
		config |= _BV( CRCO );
	}
	write_register( NRF_CONFIG, config ) ;
}

/****************************************************************************/

rf24_crclength_e RF24::getCRCLength(void)
{
	rf24_crclength_e result = RF24_CRC_DISABLED;
	
	uint8_t config = read_register(NRF_CONFIG) & ( _BV(CRCO) | _BV(EN_CRC)) ;
	uint8_t AA = read_register(EN_AA);
	
	if ( config & _BV(EN_CRC ) || AA)
	{
		if ( config & _BV(CRCO) )
			result = RF24_CRC_16;
		else
			result = RF24_CRC_8;
	}
	
	return result;
}

/****************************************************************************/

void RF24::disableCRC( void )
{
	uint8_t disable = read_register(NRF_CONFIG) & ~_BV(EN_CRC) ;
	write_register( NRF_CONFIG, disable ) ;
}

/****************************************************************************/
void RF24::setRetries(uint8_t delay, uint8_t count)
{
	write_register(SETUP_RETR,(delay&0xf)<<ARD | (count&0xf)<<ARC);
}