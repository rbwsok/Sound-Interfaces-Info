#include "stdafx.h"

FILEVERSION::FILEVERSION(char *infilename)
{
 LanguageString = 0;
 CompanyName = 0;
 FileDescription = 0;
 FileVersion = 0;
 InternalName = 0;
 LegalCopyright = 0;
 LegalTrademarks = 0;
 OriginalFilename = 0;
 ProductName = 0;
 ProductVersion = 0;
 PrivateBuild = 0;
 SpecialBuild = 0;
 Comments = 0;
 filename = 0;
 filepath = 0;
 enable = GetInfo(infilename);
}

FILEVERSION::~FILEVERSION()
{
 delete [] LanguageString;
 delete [] CompanyName;
 delete [] FileDescription;
 delete [] FileVersion;
 delete [] InternalName;
 delete [] LegalCopyright;
 delete [] LegalTrademarks;
 delete [] OriginalFilename;
 delete [] ProductName;
 delete [] ProductVersion;
 delete [] PrivateBuild;
 delete [] SpecialBuild;
 delete [] Comments;
 delete [] filename;
 delete [] filepath;
}

bool FILEVERSION::strncmp(char* str)
{
 int cnt = lstrlen(str);
 for (int i = 0; i < lstrlen(str);i++)
  if (str[i] != ' ') return true;
 return false;
}

bool FILEVERSION::GetInfo(char* filename)
{
 char tmps[1024];
 char *tmp = tmps;
 char szResource[80];
 DWORD dwScratch = 0;
 int *pdwLangChar;

 FILEVERSION::filename = new char[lstrlen(filename) + 1];
 wsprintf(FILEVERSION::filename,"%s",filename);
 
 char* ptr;

 if (SearchPath(0,filename,0,1024,tmps,&ptr) == 0) return false;
 
 if (tmps >= ptr) return false;
 filepath = new char [ptr - tmps + 1];
 ZeroMemory(filepath,ptr - tmps + 1);
 CopyMemory(filepath,tmps,ptr - tmps);

 HANDLE hFile = CreateFile(tmps,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
 if (hFile == INVALID_HANDLE_VALUE) 
 {
  int t = GetLastError();
  filesize = 0;
 }
 else
 {
  filesize = GetFileSize(hFile,0);
  CloseHandle(hFile);
 }

 int lenvinfo = GetFileVersionInfoSize(filename,&dwScratch);
 if (lenvinfo == NULL) return false;
 char* verbuf = new char[lenvinfo];
 if (GetFileVersionInfo(filename,0,lenvinfo,verbuf) == FALSE)
  goto noinfo;
 
 unsigned int uSize;
 if (VerQueryValue (verbuf,"\\VarFileInfo\\Translation",(void**)(&pdwLangChar),&uSize) == false)
  goto noinfo;

 VerLanguageName(LOWORD (*pdwLangChar),tmp,1024);
 LanguageString = new char [lstrlen(tmp) + 1];
 wsprintf(LanguageString,"%s",tmp); 

 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\Comments",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   Comments = new char [lstrlen(tmp) + 1];
   wsprintf(Comments,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\CompanyName",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   CompanyName = new char [lstrlen(tmp) + 1];
   wsprintf(CompanyName,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\FileDescription",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   FileDescription = new char [lstrlen(tmp) + 1];
   wsprintf(FileDescription,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\FileVersion",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   FileVersion = new char [lstrlen(tmp) + 1];
   wsprintf(FileVersion,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\InternalName",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   InternalName = new char [lstrlen(tmp) + 1];
   wsprintf(InternalName,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\LegalCopyright",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   LegalCopyright = new char [lstrlen(tmp) + 1];
   wsprintf(LegalCopyright,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\LegalTrademarks",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   LegalTrademarks = new char [lstrlen(tmp) + 1];
   wsprintf(LegalTrademarks,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\OriginalFilename",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   OriginalFilename = new char [lstrlen(tmp) + 1];
   wsprintf(OriginalFilename,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\ProductName",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   ProductName = new char [lstrlen(tmp) + 1];
   wsprintf(ProductName,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\ProductVersion",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   ProductVersion = new char [lstrlen(tmp) + 1];
   wsprintf(ProductVersion,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\PrivateBuild",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   PrivateBuild = new char [lstrlen(tmp) + 1];
   wsprintf(PrivateBuild,"%s",tmp); 
  }
 }
 wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\SpecialBuild",LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));
 if (VerQueryValue (verbuf,szResource,(void**)(&tmp),&uSize) == TRUE)
 {
  if (strncmp(tmp) == true)
  {
   SpecialBuild = new char [lstrlen(tmp) + 1];
   wsprintf(SpecialBuild,"%s",tmp); 
  }
 }

 return true;
noinfo:;
 delete [] verbuf;
 return false;
}