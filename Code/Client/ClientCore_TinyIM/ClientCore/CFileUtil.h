/**
 * @file CFileUtil.h
 * @author DennisMi (https://www.dennisthink.com/)
 * @brief 文件和文件夹操作的工具类
 * @version 0.1
 * @date 2019-09-23
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _DENNIS_THINK_C_FILE_UTIL_H_
#define _DENNIS_THINK_C_FILE_UTIL_H_
#include <cstdio>
#include <fstream>
#include <map>
class CFileUtil {
public:
  bool IsFileExist(const std::string strFileName);
  bool RemoveFile(const std::string strFileName);

  bool IsFolder(const std::string strFolder);
  bool CreateFolder(const std::string strFolder);
  bool RemoveFolder(const std::string strFolder);

  bool CreateFileByName(const int nFileId, const std::string FileName);
  bool GetFileSize(int &nFileSize, const std::string strFileName);
  bool OpenReadFile(const int nFileId, const std::string strFileName);

  bool OpenWriteFile(const int nFileId, const std::string strFileName);
  bool OnWriteData(const int nFileId, const char *pData, const int nDataLen);
  bool OnReadData(const int nFileId, char *pData, int &nReadLen,
                  const int nMaxDataLen);
  bool OnCloseFile(const int nFileId);
  std::string CalcHash(const std::string strFileName);

private:
  std::map<int, std::FILE *> m_ReadFileMap;
  std::map<int, std::FILE *> m_WriteFileMap;
};
#endif