#ifndef __EGT3295GESTURE__
#define __EGT3295GESTURE__

#define EVENT_UNKNOWN			0
#define EVENT_HOLD				1
#define EVENT_4D_RIGHT			2
#define EVENT_4D_LEFT			3
#define EVENT_4D_UP				4
#define EVENT_4D_DOWN			5
#define EVENT_4D_AMBIGUOUS		6
#define EVENT_ZOOM_L1			7
#define EVENT_ZOOM_L2			8
#define EVENT_ZOOM_L3			9
#define EVENT_ROTATE_CL			10
#define EVENT_ROTATE_CCL		11
#define EVENT_ROTATE_START		12
#define EVENT_ROTATE_END		13
#define EVENT_TRIGGER			14

#define BASE_MODE_DISABLE		0
#define BASE_MODE_2D_HOR		1
#define BASE_MODE_2D_VERT		2
#define BASE_MODE_4D			3
#define GES_MODE_4D_ZOOM		6

#define ADV_MODE_HOLD			(1<<2)
#define ADV_MODE_HOLD_ROTATE	(3<<2)
#define ADV_MODE_ZOOM			(4<<2)		//±íÊ¾6D
#define ADV_MODE_ENGINEER		(8<<2)
// EX: set_gesture_mode(BASE_MODE_4D | ADV_MODE_HOLD)

#define CHANNEL_COUNT			4
#define BUF_SIZE				(CHANNEL_COUNT*50)

#define LIB_VERSION				"1.0.7"
#define LIB_VERSION_INT		(107)

extern unsigned char sleep_mode;
extern unsigned char zoom_delta;
extern unsigned char crosstalk_offset;
extern unsigned short crosstalks[4];
extern unsigned char ges_count;
extern unsigned short ges_raws[BUF_SIZE];

/**********************************************************************************
 * public settings for customer
 **********************************************************************************/
extern unsigned short GES_MAX_INTERNAL_TIME;	// default is   300 ms
extern unsigned short GES_MIN_INTERNAL_TIME;	// default is    20 ms
extern unsigned short GES_ZOOM_START_TIME;		// default is   400 ms
extern unsigned short GES_ZOOM_SPACING_TIME;	// default is   200 ms
extern unsigned short GES_HOLD_TIME;			// default is  800 ms (larger in ADV_MODE_HOLD_ROTATE)
extern unsigned short GES_ROTATE_START_TIME;	// default is   400 ms (larger than GES_MAX_INTERNAL_TIME)
extern unsigned short GES_ROTATE_END_TIME;		// default is   400 ms
extern unsigned short SLEEP_PERIOD;				// default is  5000 ms

extern unsigned short WORK_TH;		// defalut is 14 for 4D
extern unsigned short ZOOM_TH;		// defalut is 14
extern unsigned short HOLD_TH;		// defalut is 50
/**********************************************************************************
 * public settings for customer
 **********************************************************************************/
#endif

typedef void (*gesture_sleep_callback)(unsigned char);
typedef void (*gesture_event_callback)(unsigned char);

void set_gesture_callback(gesture_sleep_callback cb1, gesture_event_callback cb2);
void set_gesture_mode(unsigned char gm);
void add_gesture_data(unsigned short *datas);

