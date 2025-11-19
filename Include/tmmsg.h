#ifndef TMMSG_H
#define TMMSG_H


#define     MSG_ERROR_START     0x10000000
#define		MSG_USER_DEFINE		0x20000000


#define     MSG_ERROR_ADD       MSG_ERROR_START + 1
#define     MSG_ERROR_FIX       MSG_ERROR_START + 2

#define		MSG_USER_SH_MONI_ADD            MSG_USER_DEFINE + 0x0001		//	add monitor2
#define		MSG_USER_SH_ERROR_ADD           MSG_USER_DEFINE + 0x0002		//	add error
#define		MSG_USER_SH_ERROR_FIX           MSG_USER_DEFINE + 0x0003		//	fix error
#define		MSG_USER_SH_REMOTE_KEY          MSG_USER_DEFINE + 0x0004		//	on key
#define		MSG_USER_SH_MACHINEVERSION_DATA	MSG_USER_DEFINE + 0x0005        //	send dsp machine version
#define		MSG_USER_SH_PROMPTERROR         MSG_USER_DEFINE + 0x0006		//	send prompt error
#define		MSG_USER_SH_PROMPTNULL          MSG_USER_DEFINE + 0x0007		// 	send prompt null
#define		MSG_USER_SH_PROMPTSTOPTIMEERROR	MSG_USER_DEFINE + 0x0008		// 	send stopmachine time error

#endif // TMMSG_H
