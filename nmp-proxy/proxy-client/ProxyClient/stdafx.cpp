
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// ProxyClient3.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

long GetMsgNumber()
{
	return CSerialLong::Instance().RequestSerialLong();
}
void ReleaseNumber(long lNumber)
{
	CSerialLong::Instance().ReleaseSerialLong(lNumber);
}


