#ifndef __CSOS_CONFIG_HPP__
#define __CSOS_CONFIG_HPP__

#define COMPILER_NAME "gcc"
#define COMPILER_VERSION (__GNUC__ * 10000 \
                    	 + __GNUC_MINOR__ * 100 \
                         + __GNUC_PATCHLEVEL__)


#define VERSION                 		"0.54.00 PI"
#define NAME                    		"CS/OS"
#define RELEASE_NAME    				"Charlie"
#define MACHINE							"armv6zk"
#define NETWORKNAME						"csos"

#define CSOS_LIBVERSION					0x002615
#define CSOS_LIBVERSION_STRING			std::string("0.26.15")


#define	FONT_8							8
#define FONT_16							16 
#define FONT							FONT_8

#define TABSIZE_NORMAL					4
#define TABSIZE_TINY					2
#define	LIB_TAB_SIZE					TABSIZE_TINY

#define FRAMEBUFFER_DEPTH_16			16
#define FRAMEBUFFER_DEPTH_24		    24
#define FRMEBUFFER_DEPTH				FRAMEBUFFER_DEPTH_16 

#define UART_BPS_50						50
#define UART_BPS_110					110
#define UART_BPS_150					150
#define UART_BPS_300					300
#define UART_BPS_1200					1200
#define UART_BPS_2400					2400
#define UART_BPS_4800					4800
#define UART_BPS_9600					9600
#define UART_BPS_19200					19200
#define UART_BPS_38400					38400
#define UART_BPS_57600					57600
#define UART_BPS_115200					115200
#define UART_BPS_230400					230400
#define UART_BPS_460800					460800
#define UART_BPS_500000					500000
                                                                                                                                                                                               			                                                 
#define UART0_BAUD						UART_BPS_500000
#define	KEYBOARD_LANG					<dev/klang/de_de.h>
                                                 
#define ARM
#define ARM_V6
#define BROADCOM_2835
#define HCD_DESIGNWARE_20
#define HCD_DESIGNWARE_BASE 			((void*)0x20980000)


#if FONT == FONT_8
	#define CHARSIZE_X						8
	#define CHARSIZE_Y						8
	#define FONTNAME						font8x8
	#define FONT_INT						CHARSIZE_Y
#else
	#define CHARSIZE_X						12
	#define CHARSIZE_Y						16
	#define FONTNAME						font12x16
	#define FONT_INT						32
#endif





#endif