# java-c-Y

The demo shows the communication between a java server and C client on tcp socket on a little endian machine. 

The data which is sent out by C client covers the float, int and char to show the way to deal with endian issue and unsigned char in java.


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




