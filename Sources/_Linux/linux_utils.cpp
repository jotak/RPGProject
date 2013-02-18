#ifdef linux
#include "../Utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dirent.h>

errno_t fopen_s(FILE ** pFile, const char * sFilename, const char * sMode)
{
    *pFile = fopen(sFilename, sMode);
    if (*pFile == NULL) {
        return -1;
    }
    return 0;
}

// type: 0=any, 0x4=folder, 0x8=file
int getDirectoryContent(string dir, vector<string> &files, unsigned char type)
{
    DIR * dp;
    struct dirent * dirp;
    if ((dp  = opendir(dir.c_str())) == NULL)
    {
        return -1;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        if (type == 0 || type == dirp->d_type)
        {
            files.push_back(string(dirp->d_name));
        }
    }
    closedir(dp);
    return 0;
}

char sClipboard[1024];

bool copyStringToClipboard(const char * wsource)
{
    // TODO: real clipboard on linux??
    wsafecpy(sClipboard, 1024, wsource);
    return true;
}

char * getStringFromClipboard(char * sBuffer, int iBufSize)
{
    // TODO: real clipboard on linux??
    wsafecpy(sBuffer, iBufSize, sClipboard);
    return sBuffer;
}

int getAvailableDisplayModes(CoordsScreen * pResolution, int * pBpp, int iMaxEntries)
{
	// TODO: get real data
    int i = 0;
    if (i <= iMaxEntries){
        pResolution[i].x = 800;
        pResolution[i].y = 600;
        pBpp[i] = 16;
        i++;
    } else {
        return i;
    }

    if (i <= iMaxEntries) {
        pResolution[i].x = 800;
        pResolution[i].y = 600;
        pBpp[i] = 32;
        i++;
    } else {
        return i;
    }

    if (i <= iMaxEntries) {
        pResolution[i].x = 1024;
        pResolution[i].y = 768;
        pBpp[i] = 16;
        i++;
    } else {
        return i;
    }

    if (i <= iMaxEntries) {
        pResolution[i].x = 1024;
        pResolution[i].y = 768;
        pBpp[i] = 32;
        i++;
    } else {
        return i;
    }

    if (i <= iMaxEntries) {
        pResolution[i].x = 1152;
        pResolution[i].y = 864;
        pBpp[i] = 32;
        i++;
    } else {
        return i;
    }

    if (i <= iMaxEntries) {
        pResolution[i].x = 1280;
        pResolution[i].y = 768;
        pBpp[i] = 32;
        i++;
    } else {
        return i;
    }

    if (i <= iMaxEntries) {
        pResolution[i].x = 1280;
        pResolution[i].y = 960;
        pBpp[i] = 32;
        i++;
    } else {
        return i;
    }

    if (i <= iMaxEntries) {
        pResolution[i].x = 1280;
        pResolution[i].y = 1024;
        pBpp[i] = 32;
        i++;
    }

    return i;
}

#endif
