#ifndef __CSOS_CONFIG_HPP__
#define __CSOS_CONFIG_HPP__

#define COMPILER_NAME "gcc"
#define COMPILER_VERSION (__GNUC__ * 10000 \
                    	 + __GNUC_MINOR__ * 100 \
                         + __GNUC_PATCHLEVEL__)


#define VERSION                 		"0.54.00 PI"
#define NAME                    		"CS/OS"
#define RELEASE_NAME    				"Abby"
#define MACHINE							"i686"
#define NETWORKNAME						"csos"

#define CSOS_LIBVERSION					0x002615
#define CSOS_LIBVERSION_STRING			std::string("0.26.15")

#define	KEYBOARD_LANG					<dev/klang/de_de.h>

#define	LIB_TAB_SIZE					4

#define ARM
#define ARM_V6
#define BROADCOM_2835
#define HCD_DESIGNWARE_20
#define HCD_DESIGNWARE_BASE 			((void*)0x20980000)

#define CHARSIZE_X						8
#define CHARSIZE_Y						8
 
#define FRMEBUFFER_DEPTH				24 // Only Support 16 or 24    




//....................
#define RPI_BASIC_ARM_TIMER_IRQ         (1 << 0)
#define RPI_BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define RPI_BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define RPI_BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define RPI_BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define RPI_BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define RPI_BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define RPI_BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)
 //.......................                                                              
/* Version Brief:

	0.4.0:
		add Version Brief
		kernel ready
	0.51.53:
		klibc, klibcxx
		add fs
	0.52.01:
		add wchar. wtype
		add Driver random, Keyboard, cga, serial
		add Device Manager
		add Initrd
	0.53.2051:
		add wstring
	0.54.00:
		add pci
		add pagging get phys addr
		add rtl8139 drv ( 30 % )
	0.54.00 PI
		Port to Raspi
		
*/
#endif