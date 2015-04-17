/************************************************************************ 
* �ļ�����    User.h  
* �ļ�������  �������û������һЩ����
* �����ˣ�    XiaoHe, 2013��03��2��
* �汾�ţ�    1.0 
************************************************************************/ 

#pragma once

class CUser
{
private:
	CString m_name;
	CString m_pwd;
	CString m_newpwd;

public:
	IJXmlParser *m_pXmlParser;
	IJDCUCommand *m_pCommand;

public:
	CUser(void);
	~CUser(void);
	int SetName(CString);
	CString GetName();

	int SetPwd(CString);
	CString GetPwd();

	int SetNewPwd(CString);
	CString GetNewPwd();

	int Add(CString name,CString pwd);
	int Del(CString name);
	int Modify(CString newpwd);
};
