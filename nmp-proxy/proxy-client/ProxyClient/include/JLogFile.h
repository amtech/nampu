#ifndef _RunLogFile_h
#define _RunLogFile_h

//ʹ�ú� RUN_LOG_FILE ָ����־�ļ���

#ifndef PATH_SEP
#define PATH_SEP "\\"
#endif

inline void GetCurFilePath(string& strCurPath)
{
	int nSize = 1024;
	string strFileName;
	strFileName.assign(nSize - 1, 0);
	GetModuleFileNameA(NULL, (LPSTR)strFileName.data(), nSize);
	long lPos = strFileName.rfind("\\");
	strCurPath = strFileName.substr(0, lPos + 1);
}

inline void JLogFile(const char* szLog, ...)
{
	static string strFile;
	if(strFile.empty())
	{
		GetCurFilePath(strFile);
		strFile = strFile + "log" + PATH_SEP;
#ifdef RUN_LOG_FILE
		strFile = strFile + RUN_LOG_FILE + ".log";
#else
		strFile = strFile + "tmp.log";
#endif
	}

	//���ļ�������С
	FILE* fp = fopen(strFile.c_str(),"rb");
	if(fp)
	{
		fseek(fp,0,SEEK_END);
		if(ftell(fp) > 1024*1024*10)//10��������ļ�
		{
			fclose(fp);
			remove((strFile + ".bak").c_str());
			rename(strFile.c_str(),(strFile + ".bak").c_str());			
		}
		else
		{
			fclose(fp);
		}
	}
	fp = fopen(strFile.c_str(),"a+");
	if(fp)
	{
		//д������
		time_t tmNow = time(NULL);
		struct tm tmLocal;

#ifdef WIN32
		tmLocal = *localtime(&tmNow);
#else
		localtime_r(&tmNow, &tmLocal );
#endif
		fprintf(fp,"\r\n[%4d-%02d-%02d %02d:%02d:%02d] ",
			tmLocal.tm_year+1900, tmLocal.tm_mon+1, tmLocal.tm_mday,
			tmLocal.tm_hour, tmLocal.tm_min,tmLocal.tm_sec);

		//д����־
		va_list ap;
		va_start(ap , szLog);
		vfprintf(fp,szLog,ap);
		va_end(ap);

		fclose(fp);
	}
}


#endif//_RunLogFile_h
