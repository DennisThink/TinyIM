#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include "CFileUtil.h"


TEST_CASE("CreateFile") {
	CFileUtil util;	
}

TEST_CASE("RemoveFile") {

}

TEST_CASE("ReadFile") {
	CFileUtil util;
	std::string strReadName = "E:\\GitHub\\DennisThinkIM\\源代码\\Client\\ClientCore_TinyIM\\bin\\Debug\\Read.txt";
	int nReadFileId = 15;

	std::string strWriteName = "E:\\GitHub\\DennisThinkIM\\源代码\\Client\\ClientCore_TinyIM\\bin\\Debug\\Write.txt";
	int nWriteFileId = 16;
	CHECK(util.OpenReadFile(nReadFileId, strReadName));
	util.RemoveFile(strWriteName);
	CHECK(util.OpenWriteFile(nWriteFileId, strWriteName));
	char buff[1024] = { 0 };
	int nReadLen = 0;
	int nCount = 0;
	bool bRead = util.OnReadData(nReadFileId, buff, nReadLen, 1024);
	while (bRead)
	{
		CHECK(util.OnWriteData(nWriteFileId, buff, nReadLen));
		std::cout << "Write "<< nCount << std::endl;
		nCount++;
		bRead = util.OnReadData(nReadFileId, buff, nReadLen, 1024);
	}
	CHECK(util.OnCloseFile(nReadFileId));
	CHECK(util.OnCloseFile(nWriteFileId));
	CHECK(util.RemoveFile(strWriteName));
}
