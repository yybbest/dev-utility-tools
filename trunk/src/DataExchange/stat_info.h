#ifndef STAT_INFO_H
#define STAT_INFO_H

#include <string>


struct stStatInfo
{
     std::string m_strPath;
	 int m_FolderNum;
	 int m_FileNum;
	 
	 stStatInfo()
	 {
	      m_FolderNum = 0;
	      m_FileNum = 0;
	 }
};




















#endif