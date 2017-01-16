#ifndef _DATAPOOLDEFINE_H_
#define _DATAPOOLDEFINE_H_
#ifdef cplusplus
extern "C" {
#endif

#define   PROCESSNUM    7  //总进程数????每个信号量集中的信号量个??#define   P_STATISTIS   0  //表示统计进程
#define   P_PARAM       1  //表示参数进程
#define   P_104         2  //表示104进程
#define   P_101         3  //表示101进程
#define   P_CAN         4  //表示采集进程
#define   P_DATCOD      5  //表示加密进程
#define   P_SYNTHESIZE  6  //表示综合进程    


#define MAXDEVNUM	512
#define MAXYCNUM	128	
#define MAXYXNUM	128


typedef  struct 
{
    unsigned char OV  : 1;
    unsigned char RES : 3;
    unsigned char BL  : 1;
    unsigned char SB  : 1;
    unsigned char NT  : 1;
    unsigned char IV  : 1;
}QDS_;


typedef struct
{
	
	float Yc_Value;
	unsigned char OV ;
    unsigned char BL ;
    unsigned char SB ;
    unsigned char NT ;
    unsigned char IV ;
}YCDATA;

typedef struct
{
	unsigned int Yc_Num;
	YCDATA Yc_Data[MAXYCNUM];
}_YC;
extern _YC YC[MAXDEVNUM];

typedef struct
{
        unsigned int SPI : 1;
        unsigned int RES : 3;
        unsigned int BL  : 1;
        unsigned int SB  : 1;
        unsigned int NT  : 1;
        unsigned int IV  : 1;
}SIQ_;

typedef struct
{
        unsigned int DPI : 2;
        unsigned int RES : 2;
        unsigned int BL  : 1;
        unsigned int SB  : 1;
        unsigned int NT  : 1;
        unsigned int IV  : 1;
}DIQ_;

typedef struct
{
	unsigned int 		Year;
	unsigned int 		Month;
	unsigned int 		Date;
	unsigned int 		Hour;
	unsigned int 		Min;
	unsigned int 		Second;
	unsigned int 		Ms;
}TIMESTR;

typedef struct
{
	unsigned char 		State;
	unsigned char		BL;
	unsigned char		SB;
	unsigned char 		NT;
	unsigned char 		IV;
}YXDATA;

typedef struct
{
	unsigned int Yx_Num;
	YXDATA Yx_Data[MAXYCNUM];
}_YX;
extern _YX YX[MAXDEVNUM];

#define _MAX_SOE_NUM_    32
typedef struct
{
    unsigned short int  Channel;// Handle...
    unsigned char 		State;
	unsigned char		BL;
	unsigned char		SB;
	unsigned char 		NT;
	unsigned char 		IV;
	unsigned int 		Year;
	unsigned int 		Month;
	unsigned int 		Date;
	unsigned int 		Hour;
	unsigned int 		Min;
	unsigned int 		Second;
	unsigned int 		Ms;
    //unsigned int        Tim_S;  // from 1970-1-1 0:0:0
    //unsigned short int  Tim_MS;
}SOE__;
typedef struct
{
    unsigned int        CurPot;         // cur point
    SOE__               SOE_[_MAX_SOE_NUM_];
}_SOE;
extern _SOE SOE[MAXDEVNUM];

typedef struct
{
	unsigned int YkFlag;
	unsigned int YkPot;
	unsigned int YkState;
}_YK;
extern _YK YK[MAXDEVNUM][2];

typedef struct
{
	unsigned int CallFlag;
	unsigned int CallPot;
	unsigned int CallState;
}S_CALL;
extern S_CALL CALL[MAXDEVNUM][2];

typedef struct
{
	unsigned int TimeSynFlag;
	unsigned int TimeSynPot;
	unsigned int TimeSynState;
	TIMESTR Time;
}S_TIMESYN;
extern S_TIMESYN TIMESYN[MAXDEVNUM][2];

#define MAX_FILE_LEN 	255
#define MAX_FILE_NUM	256
#define READ_MENU		1
#define READ_FILE		2

typedef struct
{
	char Oper_ID;
	long Menu_ID;
	unsigned char Menu_Len;
	char Menu[MAX_FILE_LEN];
	unsigned char Call_Flag;
	TIMESTR StartTime;
	TIMESTR EndTime;
}FILEMENUSTR;

typedef struct
{
	unsigned char FileName_Len;
	char FileName[MAX_FILE_LEN];
	unsigned char File_Property;
	long FileSize;
	TIMESTR Time;
}FILEBASICSTR;

typedef struct
{
	unsigned int FileMenuOper;
	unsigned int MenuID;
	unsigned int FileNum;
	FILEBASICSTR File[MAX_FILE_NUM];
}FILESTR;

typedef struct
{
    unsigned int File_Oper;
	FILESTR DevFileMenu;
	char FilePath[MAX_FILE_LEN];
}FILESTRUP;
extern FILESTRUP DevFile[MAXDEVNUM];

typedef struct
{
	char File_Oper_ID;
	unsigned char FileName_Len;
	char FileName[MAX_FILE_LEN];
}FILEREADSTR;

typedef struct
{
	unsigned char File_Oper;// 1- ??????2-?????
	FILEMENUSTR FileMenu;
	FILEREADSTR	FileRead;
}FILEOPERATE;
extern FILEOPERATE FileOper[MAXDEVNUM];

typedef struct
{
	unsigned int Online_State;
}_ONLINE;
extern _ONLINE Online[MAXDEVNUM];

#define MAXSIZE 28
typedef struct
{
	unsigned int C101_Addrbytes;
	unsigned int C101_Cotbytes;
	unsigned int C101_Infobytes;
	unsigned int Call_Intervaltime;
	unsigned int C101_Jump_time;
	unsigned int Time_Interval;
	unsigned int Time_Out;
	unsigned int Repeat_Intervaltime;
	unsigned int Repeat_Count;
	unsigned int Yx_Count;
	unsigned int Yc_Count;
	unsigned int DataSn;
	
	unsigned long DeviceSn;
	unsigned char DeviceAddr[MAXSIZE];/*Style:192.168.112.128:8000*/
	unsigned int DevicePort;
	unsigned int PublicAddr;
}S_DEV_INFO;
extern S_DEV_INFO DEV_INFO[MAXDEVNUM];

typedef struct
{
	unsigned char param_flag;
}S_COM_PARA;
extern S_COM_PARA COM_PARA[MAXDEVNUM];

typedef union
{
    struct
    {
        unsigned char p_statistis:1;  // 琛ㄧず缁熻杩涚▼
        unsigned char p_param:1;      // 琛ㄧず鍙傛暟杩涚▼
        unsigned char p_104:1;        // 琛ㄧず104杩涚▼
        unsigned char p_101:1;        // 琛ㄧず101杩涚▼
        unsigned char p_can:1;        // 琛ㄧず閲囬泦杩涚▼
        unsigned char p_datcod:1;     // 琛ㄧず鍔犲瘑杩涚▼
        unsigned char p_synthesize:1; // 琛ㄧず缁煎悎杩涚▼
        unsigned char reserved  :1;
    }bit;
    unsigned char all;
}AllProcess_;

struct AllProcess__
{
    AllProcess_ Total;
};
extern struct AllProcess__  AllProcess;
void Semaphore_Delete(void);
void Shared_memory_Delete(void);
void Sem_init(void);
void Shared_memory_Release(void);
void Shared_memory_mount(void);
void Shared_memory_Apply(char Typ, char WR,unsigned int ProcessNum);
void KickDog(unsigned int processnum);

#ifdef cplusplus
}
#endif
#endif
