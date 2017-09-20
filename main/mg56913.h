#ifndef MG56913_H
#define MG56913_H

//器件地址
#define	MG56913_ADDRESS 	0x82
#define MG56913_ID        0x61
#define MG56913_DEVICE    "/dev/i2c-1"

/*****************************************/
//MG56914相关寄存器
/*****************************************/

//REG0
#define MODE_IDLE			(0)
#define MODE_ALS			(1)
#define MODE_PS				(2)
#define MODE_PS_ALS		(5)
#define MODE_GES 			(0x0a)
#define MODE_GES_ALS	(0x0d)

#define WAIT_0_MS			(0<<4)		//wait time disable
#define WAIT_2_MS			(1<<4)
#define WAIT_4_MS			(2<<4)
#define WAIT_8_MS			(3<<4)
#define WAIT_12_MS		(4<<4)
#define WAIT_20_MS		(5<<4)
#define WAIT_30_MS		(6<<4)
#define WAIT_40_MS		(7<<4)
#define WAIT_50_MS		(8<<4)
#define WAIT_75_MS		(9<<4)
#define WAIT_100_MS		(10<<4)
#define WAIT_150_MS		(11<<4)
#define WAIT_200_MS		(12<<4)
#define WAIT_300_MS		(13<<4)
#define WAIT_400_MS		(14<<4)
#define WAIT_SINGLE		(15<<4)

#define	MG56913I_REG0x00	(MODE_GES | WAIT_0_MS)

//REG1
//ALS Integration Time
#define ALS_INTT_0			(0<<1)
#define ALS_INTT_8			(4<<1)
#define ALS_INTT_10			(5<<1)
#define ALS_INTT_15			(6<<1)
#define ALS_INTT_20			(7<<1)
#define ALS_INTT_35			(8<<1)
#define ALS_INTT_50			(9<<1)
#define ALS_INTT_70			(10<<1)
#define ALS_INTT_100		(11<<1)
#define ALS_INTT_150		(12<<1)
#define ALS_INTT_250		(13<<1)
#define ALS_INTT_350		(14<<1)
#define ALS_INTT_500		(15<<1)
#define ALS_INTT_750		(16<<1)
#define ALS_INTT_1000		(17<<1)
#define ALS_INTT_2000		(18<<1)
#define ALS_INTT_3000		(19<<1)
#define ALS_INTT_4000		(20<<1)
#define ALS_INTT_6000		(21<<1)
#define ALS_INTT_8000		(22<<1)
#define ALS_INTT_12000	(23<<1)
#define ALS_INTT_16000	(24<<1)

#define ALS_GAIN_MID		(0x00)
#define ALS_GAIN_LOW		(0x01)

#define	MG56913I_REG0x01	(ALS_INTT_10 | ALS_GAIN_MID)

//REG2
#define ALS_ADC_11			(0x00 << 3)
#define ALS_ADC_12			(0x01 << 3)
#define ALS_ADC_13			(0x02 << 3)
#define ALS_ADC_14			(0x03 << 3)

#define	ALS_FILTER1				(0)
#define	ALS_FILTER2				(1)
#define	ALS_FILTER4				(2)
#define	ALS_FILTER8				(3)
#define	ALS_FILTER16			(4)
#define	ALS_FILTER32			(5)
#define	ALS_FILTER64			(6)
#define	ALS_FILTER_UNUSED	(7)

#define	MG56913I_REG0x02	(ALS_ADC_12 | ALS_FILTER1)

//REG3  //PS
#define	MG56913I_REG0x03			(0x00)

//REG4	//PS
#define	MG56913I_REG0x04			(0x00)

//REG5	//PS
#define	IR_ON_CTRL_OFF		(0<<5)
#define	IR_ON_CTRL_ON			(1<<5)

#define	MG56913I_REG0x05			(IR_ON_CTRL_ON)

//REG6
#define INT_CTRL_ALS_OR_PS		(0x00 << 4)
#define INT_CTRL_ALS					(0x01 << 4)
#define INT_CTRL_PS						(0x02 << 4)

#define PS_PERIST_1						(0x00 << 2)
#define PS_PERIST_4						(0x01 << 2)
#define PS_PERIST_8						(0x02 << 2)
#define PS_PERIST_15					(0x03 << 2)

#define	MG56913I_REG0x06			(INT_CTRL_ALS | PS_PERIST_1)

//REG7
#define ALS_INT_CHSEL_0				(0x00 << 4)
#define ALS_INT_CHSEL_1				(0x01 << 4)

#define ALS_PERIST_1					(0x00 << 2)
#define ALS_PERIST_4					(0x01 << 2)
#define ALS_PERIST_8					(0x02 << 2)
#define ALS_PERIST_15					(0x03 << 2)

#define ALS_INTTY_DISABLE			(0x00)		//Interrupt Mode Selection for ALS Mode
#define ALS_INTTY_BINARY			(0x01)
#define ALS_INTTY_ACTIVE			(0x02)
#define ALS_INTTY_FRAME				(0x03)

#define	MG56913I_REG0x07					(ALS_INT_CHSEL_0 | ALS_PERIST_1 | ALS_INTTY_DISABLE)

//REG8	Interrupt Low Threshold for ALS
#define	MG56913I_REG0x08		(0x00)

//REG9	Interrupt Low Threshold for ALS
#define	MG56913I_REG0x09		(0x00)

//REG0x0A	Interrupt High Threshold for ALS
#define	MG56913I_REG0x0A		(0xff)

//REG0x0B	Interrupt High Threshold for ALS
#define	MG56913I_REG0x0B		(0xff)

//REG0x0C	Interrupt High Threshold for PS
#define	MG56913I_REG0x0C		(0x00)

//REG0x0D	Interrupt High Threshold for PS
#define	MG56913I_REG0x0D		(0x00)

//REG0x0E	Interrupt High Threshold for PS
#define	MG56913I_REG0x0E		(0xff)

//REG0x0F	Interrupt High Threshold for PS
#define	MG56913I_REG0x0F		(0xff)

//REG0x11
#define CHIP_RESETN_RESET			(0x00 << 1)
#define CHIP_RESETN_RUN				(0x01 << 1)

#define CHIP_POWER_OFF				(0x01)
#define CHIP_POWER_ON					(0x00)

#define	MG56913I_REG0x11		(CHIP_POWER_ON | CHIP_RESETN_RESET )

//REG0x12
#define ALS_CMP_RESET					(0x00 << 1)
#define ALS_CMP_RUN						(0x01 << 1)

#define ALS_LOCK			        (0x01)
#define ALS_UNLOCK		        (0x00)

#define	MG56913I_REG0x12		(ALS_CMP_RUN | ALS_LOCK )

//REG0x1B	PS

//REG0x22	PS
//REG0x23	PS


//REG0x24
#define GES_ADC_11						(0x00 << 6)
#define GES_ADC_12						(0x01 << 6)
#define GES_ADC_13						(0x02 << 6)
#define GES_ADC_14						(0x03 << 6)

#define GES_INTT_8						(0<<1)
#define GES_INTT_16						(1<<1)
#define GES_INTT_32						(2<<1)
#define GES_INTT_40						(3<<1)
#define GES_INTT_60						(4<<1)
#define GES_INTT_80						(5<<1)
#define GES_INTT_120					(6<<1)
#define GES_INTT_160					(7<<1)
#define GES_INTT_200					(8<<1)
#define GES_INTT_240					(9<<1)
#define GES_INTT_280					(10<<1)
#define GES_INTT_360					(11<<1)
#define GES_INTT_440					(12<<1)
#define GES_INTT_520					(13<<1)
#define GES_INTT_600					(14<<1)
#define GES_INTT_700					(15<<1)
#define GES_INTT_800					(16<<1)

#define GES_GAIN_MID					(0x00)
#define GES_GAIN_LOW					(0x01)

#define	MG56913I_REG0x24		(GES_ADC_11 | GES_INTT_700 | GES_GAIN_LOW)     //200

//REG0x25
#define GES_INT_DISABLE				(0<<7)
#define GES_INT_ENABLE				(1<<7)

#define GES_DATA_INDEX_1			(0<<5)
#define GES_DATA_INDEX_2			(1<<5)
#define GES_DATA_INDEX_4			(2<<5)
#define GES_DATA_INDEX_8			(3<<5)

#define	GES_IR_MODE_CURRENT		(0<<4)
#define	GES_IR_MODE_VOLTAGE		(1<<4)

#define GES_IR_BOOST_100			(0x00 << 2)
#define GES_IR_BOOST_150			(0x01 << 2)
#define GES_IR_BOOST_200			(0x02 << 2)
#define GES_IR_BOOST_300			(0x03 << 2)

#define GES_IR_DRIVE_100			(0x00)
#define GES_IR_DRIVE_50				(0x01)
#define GES_IR_DRIVE_20				(0x02)
#define GES_IR_DRIVE_10				(0x03)

#define	MG56913I_REG0x25		(GES_INT_DISABLE | GES_DATA_INDEX_8 | GES_IR_MODE_CURRENT | GES_IR_BOOST_100 | GES_IR_DRIVE_100)


/*****************************************/
//
/*****************************************/

typedef	enum
{
    Gesture_None = 	0x00,
    Gesture_UP = 		0x01,
    Gesture_DOWN = 	0x02,
    Gesture_LEFT = 	0x04,
    Gesture_RIGHT = 0x08,
    Gesture_TOP = 	0x10,
    Gesture_BOTTOM = 0x20,

}GESTURE_DIRECTION;

/*****************************************/
//function
/*****************************************/
void Init_MG56913(void);
void Task_MG56913IHandler(void);


#endif
