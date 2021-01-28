#include "PosixUtil.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

void PosixUtil::CreatePath(const char* szPath) {
	struct stat st;
	char mkcmd[1024];
	if (stat(szPath, &st) == -1) {
#ifdef WIN32
		_snprintf(mkcmd, 1024, "mkdir -p %s", szPath);
#else
		snprintf(mkcmd, 1024, "mkdir -p %s", szPath);
#endif
		system(mkcmd);
	}
}

void PosixUtil::CopyFile(const char* src, const char* dst) {
	char buf[BUFSIZ];
	size_t size;

	FILE* source = fopen(src, "rb");
	FILE* dest = fopen(dst, "wb");  //TODO: crashes if directory doesn't exist!!!

	while ((size = fread(buf, 1, BUFSIZ, source))>0) {
		fwrite(buf, 1, size, dest);
	}

	fclose(source);
	fclose(dest);
}