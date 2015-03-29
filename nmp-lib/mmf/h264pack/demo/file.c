#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include "file.h"

/*--------------- 720P����֡��ʽ begin ---------------------*/
typedef 	unsigned char BYTE;
typedef 	unsigned short WORD;
typedef 	unsigned int  DWORD;
typedef		unsigned long long DWORD64;

typedef struct _HI_VIDEO_INFO_S
{
	WORD				wImageWidth;	//ͼ����
	WORD				wImageHeight;	//ͼ��߶�
	BYTE				byEncodeType;	//��Ƶ�����ʽ0-h264 1-mjpeg 2-jpeg
	BYTE				byFrameRate;	//֡��(����)
	BYTE				byPal;			//��ʽ		0-n��1-pal��
	BYTE				byRes[1];
}HI_VIDEO_INFO_S,*LPHI_VIDEO_INFO_S;

typedef struct _HI_AUDIO_INFO_S
{
	BYTE		byAudioSamples;			//������	0--8k 1--16k 2-32k
	BYTE		byEncodeType;			//��Ƶ�����ʽ0--pcm 1-g711a 2-g711u 3--g726
	BYTE		byAudioChannels;		//ͨ����		��ֻ֧��1	
	BYTE		byAudioBits;			//λ��			16bit
	BYTE		byRes[4];
}HI_AUDIO_INFO_S, *LPHI_AUDIO_INFO_S;

typedef struct _HI_FRAME_HEAD_S
{
	WORD		wFrameFlag;				//0x3448 magic data
	BYTE		wFrameType;				//I-0x7 p--0x8 b--0xb A--0xa
	BYTE		byRsvd[1];				//����
	DWORD		dwFrameNo;				//֡��
	DWORD		dwTime;					//ϵͳʱ��
	DWORD		dwFrameSize;			//����������
	DWORD64		dw64TimeStamp;			//ʱ��� 
	union
	{
		HI_VIDEO_INFO_S	unVideoInfo;
		HI_AUDIO_INFO_S	unAudioInfo;
	};
}HI_FRAME_HEAD_S, *LPHI_FRAME_HEAD_S;

/*--------------- 720P����֡��ʽ end ---------------------*/



//////////////////////////////////////////////////////////////

// CpuType
typedef enum _J_CPU_TYPE {	
	Encoder_DM365	= 0,
	Encoder_DM368	= 1,
	Encoder_DM8127	= 2,
	Encoder_DM8168	= 3,
	Encoder_HI		= 0x100-1,
	Encoder_3507	= 0x100,
	Encoder_3510,
	Encoder_3511,
	Encoder_3512,
	Encoder_3515,
	Encoder_3516,
	Encoder_3517,
	Encoder_3518,
	Encoder_3520,
	Encoder_3521,
	Encoder_3531,
	Encoder_3532,
	Encoder_3531_3532,
}J_CPU_TYPE_E;

#define _READER_T_JXJ		0x204A584A	//  JXJ
#define _READER_MAGIC_JXJ	0x3448
#define _READER_T_JPF		0x204A5046	//  JPF
#define _READER_MAGIC_JPF	0x0132DCA9	// 20110505


// �ļ�ͷ��Ϣ begin
typedef struct _file_head_1000_s {
	unsigned int		m_dwMagic;			// ħ����           _READER_T_JXJ
	unsigned int		m_dwVersion;		// �汾             0x01000002
	unsigned int		m_lTimeZone;		// ʱ��             0
	unsigned short		m_iFileOffset;		// �ļ�ƫ����       sizeof(file_index_1001_t)
	unsigned short		m_iUserOffset;		// �û�ƫ����       0
}file_head_1000_t;
// �ļ�ͷ��Ϣ end

// �ļ�����λ����Ϣ begin
typedef struct _file_index_1001_s {
	unsigned int			m_lFrameCount;		// ֡��             0
	unsigned int			res1;				// ����1
	unsigned long long		m_tStart;			// ��ʼʱ��         0
	unsigned long long		m_tEnd;				// ����ʱ��         0
	unsigned int			m_dwSize;			// ��С             0xFFFFFFFF
	unsigned int			m_dwProtocal;		// Э������         _READER_T_JPF
	unsigned int			m_dwEncoder;		// ������           J_CPU_TYPE_E
	unsigned int			res2;				// ����2
}file_index_1001_t;
// �ļ�����λ����Ϣ end

// J_CODEC_TYPE_E: ��������
typedef enum _J_CODEC_TYPE
{
  	J_CODEC_UNKNOWN = 0,

  	J_VIDEO_CODEC_START = 10,
  	J_VIDEO_H264,
  	J_VIDEO_MPEG4,
  	J_VIDEO_MJPEG,
  	J_VIDEO_CODEC_END,

  	J_AUDIO_CODEC_START = 20,
 	J_AUDIO_G711A,
  	J_AUDIO_G711U,
  	J_AUDIO_CODEC_END,

  	J_PRIVATE_CODEC_START = 30,
	J_HIK_CODEC,
	J_AHUA_CODEC,
	J_PRIVATE_CODEC_END
}J_CODEC_TYPE_E;

// WEB��֡����
typedef enum _J_FRAME_TYPE {
	J_UNKNOWN_FRAME = 0,
	J_VIDEO_I_FRAME,
	J_VIDEO_P_FRAME,
	J_VIDEO_B_FRAME,
	J_AUDIO_FRAME,
	J_GENERIC_FRAME
}J_FRAME_TYPE_E;



typedef struct __video_frame_spec
{
  unsigned short width;     // ���
  unsigned short height;    // �߶�
} _video_frame_spec_t;

typedef struct __audio_frame_spec
{
  unsigned short fps;       // ��Ƶ֡��
  unsigned short reserved;  // �����ֶ�,����
} _audio_frame_spec_t;

typedef union __frame_spec
{
  _video_frame_spec_t video_spec;
  _audio_frame_spec_t audio_spec;
} _frame_spec_t;


typedef struct _web_frame_head_s {
	unsigned int	magic_no;        // 0x0132DCA9 -- 20110505
	unsigned int	frame_num;       // ֡��
	unsigned int	frame_type;      // J_FRAME_TYPE_E
	unsigned int	codec;           // J_CODEC_TYPE_E
    _frame_spec_t   spec;
	unsigned int	timestamp_sec;   // ʱ���,��
	unsigned int	timestamp_usec;  // ʱ���,΢��
	unsigned int	size;            // ��ʶdata[0]�е����ݴ�С
}web_frame_head_t;

/////////////////////////////////////////////////////////////


int file_open(char *file_name)
{
    int fd;
    if((fd = open(file_name, O_RDONLY)) < 0)
    {
        printf("err: open file %s\n", file_name);
    }
    return fd;
}

int file_close(int fd)
{
    if(fd) 
        return close(fd);
    else
	return -1;
    
}

int file_read(int fd, char *buf, int size, int *fr_type)
{

    HI_FRAME_HEAD_S *fr_head = (HI_FRAME_HEAD_S*)buf;

    int ret = -1;
    int fr_size = 0;

    ret = read(fd, fr_head, sizeof(HI_FRAME_HEAD_S));
	if(ret != sizeof(HI_FRAME_HEAD_S))
	{
		if(lseek(fd, 0, SEEK_SET) < 0)
        {
            printf("err: lseek fd:%d\n", fd);
        }
        return (-1);
	}

    if((fr_head->dwFrameSize) && (fr_head->dwFrameSize < size))
    {
        fr_size = fr_head->dwFrameSize;
        //I-0x7 p--0x8 b--0xb A--0xa
        *fr_type = (fr_head->wFrameType == 0x7)?0x01:((fr_head->wFrameType == 0x8)?0x02:0x03);     
        //printf("read: read fd:%d, size:%d\n", fd, fr_size);
        
        if(read(fd, buf + 0 /*sizeof(HI_FRAME_HEAD_S)*/, fr_size) != fr_size)
        {
            printf("err: read fd:%d, size:%d\n", fd, fr_size);
            if(lseek(fd, 0, SEEK_SET) < 0)
            {
                printf("err: lseek fd:%d\n", fd);
            }
            return (-1);
        }
        else
        {
            return (fr_size);
        }
    }
    return -1;
}


int f3520_hdr_skip(int fd)
{
    return lseek(fd, sizeof(file_head_1000_t)+sizeof(file_index_1001_t), SEEK_SET);
}





inline int f3520_read(int fd, char *buf, int size, int *fr_type, unsigned int *t)
{
    
    web_frame_head_t *fr_head = (web_frame_head_t*)buf;

    int ret = -1;
    int fr_size = 0;

    ret = read(fd, fr_head, sizeof(web_frame_head_t));
	if(ret != sizeof(web_frame_head_t))
	{
		if(f3520_hdr_skip(fd) < 0)
        {
            printf("err: lseek fd:%d\n", fd);
        }
        return (-1);
	}

    if((fr_head->size) && (fr_head->size < size))
    {
        fr_size = fr_head->size;

        *fr_type = fr_head->frame_type;
        *t = (fr_head->timestamp_sec *1000 + fr_head->timestamp_usec/1000);
        if(read(fd, buf + 0, fr_size) != fr_size)
        {
            printf("err: read fd:%d, size:%d\n", fd, fr_size);
    		if(f3520_hdr_skip(fd) < 0)
            {
                printf("err: lseek fd:%d\n", fd);
            }
            return (-1);
        }
        else
        {
            return (fr_size);
        }
    }
    return -1;
}

int f3520_read_a(int fd, char *buf, int size, int *fr_type)
{
    int frame_size;
    static unsigned int p_time = 0;
    unsigned int t;
    
    while(1)
    {
        if((frame_size = f3520_read(fd, buf, size, fr_type, &t)) < 0 
                || (*fr_type) != J_AUDIO_FRAME)
        {
            continue;
        }
        else
            break;
    }
    if(p_time)
    {
        printf("                VIDEO d:%d\n", t - p_time);
    }
    p_time = t; 



    return frame_size;
}

int f3520_read_v(int fd, char *buf, int size, int *fr_type)
{
    int frame_size;
    static unsigned int p_time = 0;
    unsigned int t;
    
    while(1)
    {
        if((frame_size = f3520_read(fd, buf, size, fr_type, &t)) < 0 
                || (*fr_type) == J_AUDIO_FRAME)
        {
            continue;
        }
        else
            break;
    }
    if(p_time)
    {
        printf("AUDIO d:%d\n", t - p_time);
    }
    p_time = t; 


    return frame_size;
}
