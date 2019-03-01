#ifndef __FILE_VERSION_H_
#define __FILE_VERSION_H_

class FILEVERSION
{
private:
 bool GetInfo(char* filename);
 bool strncmp(char* str);
public:
 FILEVERSION(char *filename);
 ~FILEVERSION();

 char* LanguageString;

 char* CompanyName;
 char* FileDescription;
 char* FileVersion;
 char* InternalName;
 char* LegalCopyright;
 char* LegalTrademarks;
 char* OriginalFilename;
 char* ProductName;
 char* ProductVersion;
 char* PrivateBuild;
 char* SpecialBuild;
 char* Comments;

 bool enable;

 int filesize;
 char *filename;
 char *filepath;

};


#endif