#ifndef MG56914_H
#define MG56914_H

//器件地址
#define	MG56914_ADDRESS 	0x92
#define MG56914_ID          0x88
#define MG56914_DEVICE      "/dev/i2c-1"

/*****************************************/
//MG56914相关寄存器
/*****************************************/

//REG0
#define MG56914_MODE_IDLE			(0)
#define MG56914_MODE_ALS			(1)
#define MG56914_MODE_PS				(2)
#define MG56914_MODE_PS_ALS			(3)

#define MG56914_WAIT_0_MS			(0<<4)		//wait time disable
#define MG56914_WAIT_2_MS			(1<<4)
#define MG56914_WAIT_4_MS			(2<<4)
#define MG56914_WAIT_8_MS			(3<<4)
#define MG56914_WAIT_12_MS          (4<<4)
#define MG56914_WAIT_20_MS          (5<<4)
#define MG56914_WAIT_30_MS          (6<<4)
#define MG56914_WAIT_40_MS          (7<<4)
#define MG56914_WAIT_50_MS          (8<<4)
#define MG56914_WAIT_75_MS          (9<<4)
#define MG56914_WAIT_100_MS         (10<<4)
#define MG56914_WAIT_150_MS         (11<<4)
#define MG56914_WAIT_200_MS         (12<<4)
#define MG56914_WAIT_300_MS         (13<<4)
#define MG56914_WAIT_400_MS         (14<<4)
#define MG56914_WAIT_SINGLE         (15<<4)

#define	MG56914_REG0x00	(MG56914_MODE_ALS | MG56914_WAIT_0_MS)

//REG1
//ALS Integration Time
#define MG56914_ALS_INTT_0			(0 << 2)
#define MG56914_ALS_INTT_8			(2 << 2)
#define MG56914_ALS_INTT_16			(3 << 2)
#define MG56914_ALS_INTT_32			(4 << 2)
#define MG56914_ALS_INTT_64			(5 << 2)
#define MG56914_ALS_INTT_128		(6 << 2)
#define MG56914_ALS_INTT_256		(7 << 2)
#define MG56914_ALS_INTT_512		(8 << 2)
#define MG56914_ALS_INTT_768		(9 << 2)
#define MG56914_ALS_INTT_1024		(10 << 2)
#define MG56914_ALS_INTT_2048		(11 << 2)
#define MG56914_ALS_INTT_4096		(12 << 2)
#define MG56914_ALS_INTT_6144		(13 << 2)
#define MG56914_ALS_INTT_8192		(14 << 2)
#define MG56914_ALS_INTT_10240      (15 << 2)

#define MG56914_ALS_GAIN_HIG		(0x00)
#define MG56914_ALS_GAIN_MID		(0x01)
#define MG56914_ALS_GAIN_UNUSED		(0x02)
#define MG56914_ALS_GAIN_LOW		(0x03)

#define	MG56914_REG0x01	(MG56914_ALS_INTT_256 | MG56914_ALS_GAIN_LOW)

//REG2
#define MG56914_REG2_BIT7TOBIT3		(0x10 << 3)

#define	MG56914_ALS_FILTER1			(0)
#define	MG56914_ALS_FILTER2			(1)
#define	MG56914_ALS_FILTER4			(2)
#define	MG56914_ALS_FILTER8			(3)
#define	MG56914_ALS_FILTER16		(4)
#define	MG56914_ALS_FILTER32		(5)
#define	MG56914_ALS_FILTER64		(6)
#define	MG56914_ALS_FILTER_UNUSED	(7)

#define	MG56914_REG0x02	(MG56914_REG2_BIT7TOBIT3 | MG56914_ALS_FILTER32)

////REG3  //PS
#define	MG56914_REG0x03             (0x00)

////REG4	//PS
#define	MG56914_REG0x04             (0x00)

//REG5	//PS
//#define	IR_ON_CTRL_OFF          (0<<5)
//#define	IR_ON_CTRL_ON			(1<<5)

#define	MG56914_REG0x05             (0x00)

//REG6
#define MG56914_INT_CTRL_ALS_OR_PS		(0x00 << 4)
#define MG56914_INT_CTRL_ALS			(0x01 << 4)
#define MG56914_INT_CTRL_PS				(0x02 << 4)
#define MG56914_INT_CTRL_UNUSED			(0x03 << 4)

#define MG56914_PS_PERIST_1				(0x00 << 2)
#define MG56914_PS_PERIST_4				(0x01 << 2)
#define MG56914_PS_PERIST_8				(0x02 << 2)
#define MG56914_PS_PERIST_16			(0x03 << 2)

#define MG56914_INT_MODE_PS_DISABLE		(0x00)
#define MG56914_INT_MODE_PS_BINARY		(0x01)
#define MG56914_INT_MODE_PS_ACTIVE		(0x02)
#define MG56914_INT_MODE_PS_FRAME		(0x03)

#define	MG56914_REG0x06			(MG56914_INT_CTRL_UNUSED | MG56914_PS_PERIST_1 | MG56914_INT_MODE_PS_DISABLE)

//REG7
#define MG56914_REG7_BIT7TOBIT4	 		(0x01 << 4)

#define MG56914_ALS_PERIST_1			(0x00 << 2)
#define MG56914_ALS_PERIST_4			(0x01 << 2)
#define MG56914_ALS_PERIST_8			(0x02 << 2)
#define MG56914_ALS_PERIST_16			(0x03 << 2)

#define MG56914_ALS_INTTY_DISABLE		(0x00)		//Interrupt Mode Selection for ALS Mode
#define MG56914_ALS_INTTY_BINARY		(0x01)
#define MG56914_ALS_INTTY_ACTIVE		(0x02)
#define MG56914_ALS_INTTY_FRAME			(0x03)

#define	MG56914_REG0x07					(MG56914_REG7_BIT7TOBIT4 | MG56914_ALS_PERIST_1 | MG56914_ALS_INTTY_DISABLE)

//REG8	Interrupt Low Threshold for ALS
#define	MG56914_REG0x08		(0x00)

//REG9	Interrupt Low Threshold for ALS
#define	MG56914_REG0x09		(0x00)

//REG0x0A	Interrupt High Threshold for ALS
#define	MG56914_REG0x0A		(0xff)

//REG0x0B	Interrupt High Threshold for ALS
#define	MG56914_REG0x0B		(0xff)

//REG0x0C	Interrupt High Threshold for PS
#define	MG56914_REG0x0C		(0x00)

//REG0x0D	Interrupt High Threshold for PS
#define	MG56914_REG0x0D		(0x00)

//REG0x0E	Interrupt High Threshold for PS
#define	MG56914_REG0x0E		(0xff)

//REG0x0F	Interrupt High Threshold for PS
#define	MG56914_REG0x0F		(0xff)

//REG0x11
#define MG56914CHIP_RESETN_RESET		(0x00 << 1)
#define MG56914CHIP_RESETN_RUN			(0x01 << 1)

#define MG56914CHIP_SLEEP				(0x01)
#define MG56914CHIP_ACTIVE				(0x00)

#define	MG56914_REG0x11		(MG56914CHIP_RESETN_RUN | MG56914CHIP_ACTIVE )

//REG0x12
#define MG56914_ALS_CMP_RESET			(0x00 << 1)
#define MG56914_ALS_CMP_RUN				(0x01 << 1)

#define MG56914_ALS_LOCK			    (0x01)
#define MG56914_ALS_UNLOCK		        (0x00)

#define	MG56914_REG0x12		(MG56914_ALS_CMP_RUN | MG56914_ALS_UNLOCK )

/*****************************************/
//
/*****************************************/
typedef	enum  als_level_t
{
    ALS_LEVEL0 = 0,
    ALS_LEVEL1,
    ALS_LEVEL2,
    ALS_LEVEL3,
    ALS_LEVEL4,
    ALS_LEVEL5,
    ALS_LEVEL6,
    ALS_LEVEL7,
    ALS_LEVEL8,
    ALS_LEVEL9,
    ALS_LEVEL10,
    ALS_LEVEL11,
    ALS_LEVEL12
}als_level;

/*****************************************/
//function
/*****************************************/
void Init_MG56914(void);
void Task_MG56914IHandler(void);


#endif
