#include "CFileUtil.h"
#include <fstream>
#include <stdio.h>
#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>
#include<direct.h>

/**
 * @brief 获取文件的大小
 * 
 * @param nFileSize 文件大小，返回值
 * @param strFileName 文件名称
 * @return true 获取成功
 * @return false 获取失败
 */
bool CFileUtil::GetFileSize(int& nFileSize, const std::string strFileName)
{
	FILE * pFile;
	fopen_s(&pFile,strFileName.c_str(), "r");
	if (nullptr != pFile) {
		fseek(pFile, 0L, SEEK_END);
		nFileSize = ftell(pFile);
		fclose(pFile);
		return true;
	}
	else {
		return false;
	}
}

/**
 * @brief 以只读的方式打开文件，将文件名称和文件编号关联起来
 * 
 * @param nFileId 文件ID
 * @param strFileName 文件名称
 * @return true 打开成功
 * @return false 打开失败
 */
bool CFileUtil::OpenReadFile(const int nFileId, const std::string strFileName)
{
	if (!IsFileExist(strFileName))
	{
		return false;
	}

	FILE * pFile;
	fopen_s(&pFile,strFileName.c_str(), "r");
	if (nullptr != pFile) {
		m_ReadFileMap.insert({ nFileId,pFile });
		return true;
	}
	else {
		return false;
	}
}


/**
 * @brief 以只写的方式打开文件
 * 
 * @param nFileId 文件ID
 * @param strFileName 文件名称
 * @return true 打开成功
 * @return false 打开失败
 */
bool CFileUtil::OpenWriteFile(const int nFileId, const std::string strFileName)
{
	if (IsFileExist(strFileName))
	{
		return false;
	}

	FILE * pFile;
	fopen_s(&pFile,strFileName.c_str(), "w");
	if (nullptr != pFile) {
		m_WriteFileMap.insert({ nFileId,pFile });
		return true;
	}
	else {
		return false;
	}
}

/**
 * @brief 响应文件写入数据
 * 
 * @param nFileId 文件ID
 * @param pData 数据
 * @param nDataLen 数据长度
 * @return true 成功
 * @return false 失败
 */
bool CFileUtil::OnWriteData(const int nFileId, const char * pData, const int nDataLen)
{
	auto item = m_WriteFileMap.find(nFileId);
	if (item != m_WriteFileMap.end())
	{
		auto writeSize = fwrite(pData, 1, nDataLen, item->second);
		return true;
	}
	return false;
}

/**
 * @brief 根据文件ID从文件中读取数据
 * 
 * @param nFileId 文件ID
 * @param pData 读取到的文件数据
 * @param nReadLen 实际读取到的最大数据长度
 * @param nMaxDataLen 可以读取的数据的最大长度
 * @return true 读取数据成功
 * @return false 读取数据失败
 */
bool CFileUtil::OnReadData(const int nFileId, char * pData, int& nReadLen, const int nMaxDataLen)
{
	auto item = m_ReadFileMap.find(nFileId);
	if (item != m_ReadFileMap.end())
	{
		auto readSize = fread(pData, 1, nMaxDataLen, item->second);
		if (readSize <= 0)
		{
			return false;
		}
		nReadLen = readSize;
		return true;
	}
	return false;
}

/**
 * @brief 根据文件ID关闭文件
 * 
 * @param nFileId 文件ID
 * @return true 关闭成功
 * @return false 关闭失败
 */
bool CFileUtil::OnCloseFile(const int nFileId)
{
	{
		auto item = m_ReadFileMap.find(nFileId);
		if (item != m_ReadFileMap.end())
		{
			fclose(item->second);
			m_ReadFileMap.erase(nFileId);
			return true;
		}
	}
	{
		auto item = m_WriteFileMap.find(nFileId);
		if (item != m_WriteFileMap.end())
		{
			fclose(item->second);
			m_WriteFileMap.erase(nFileId);
			return true;
		}
	}
	

	return false;
}

/**
 * @brief 根据文件名判断文件是否存在
 * 
 * @param strFileName 文件名
 * @return true 文件存在
 * @return false 文件不存在
 */
bool CFileUtil::IsFileExist(const std::string strFileName)
{
	if (_access(strFileName.c_str(), 0) == 0)
	{
		return true;
	}
	return false;
}


/**
 * @brief 
 * 
 * @param strFileName 
 * @return true 
 * @return false 
 */
bool CFileUtil::RemoveFile(const std::string strFileName)
{
	if (remove(strFileName.c_str()) == 0)
	{
		return true;
	}
	return false;
}

/**
 * @brief 判断文件夹是否存在
 * 
 * @param strFolder 文件夹名称
 * @return true 是文件夹
 * @return false 不是文件夹
 */
bool CFileUtil::IsFolder(const std::string strFolder)
{
	if (_access(strFolder.c_str(), 0) == 0)
	{
		return true;
	}
	return false;
}

/**
 * @brief 创建文件夹
 * 
 * @param strFolder 文件夹路径
 * @return true 创建成功
 * @return false 创建失败
 */
bool CFileUtil::CreateFolder(const std::string strFolder)
{
	if(_mkdir(strFolder.c_str())==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/**
 * @brief 删除文件夹
 * 
 * @param strFolder 文件
 * @return true 成功
 * @return false 失败
 */
bool CFileUtil::RemoveFolder(const std::string strFolder)
{
	if(_rmdir(strFolder.c_str()) == 0)
	{
		return true;
	}
	return false;
}


/**
 * @brief 
 * 
 * @param nFileId 
 * @param FileName 
 * @return true 
 * @return false 
 */
bool CFileUtil::CreateFileByName(const int nFileId, const std::string FileName)
{
	return false;
}

/**
 * @brief 计算文件的HASH值
 * 
 * @param strFileName 文件名称
 * @return std::string 文件的HASH值
 */
std::string CFileUtil::CalcHash(const std::string strFileName)
{
	return "";
}