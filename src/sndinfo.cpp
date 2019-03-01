#include "stdafx.h"
#include "hpci.h"

HINSTANCE hInst;
HWND hmWnd,hwWnd,hpw[20];
RECT winbox;
int actpage = 0;
HRESULT hResult;

const char supported[] = "supported";
const char notsupported[] = "not supported";
const char end[] = "\r\n";

int SensauraLogo = 0;
char buf[256];
int cdev = 1;
HWND logwnd;

const char sep[] = "---------------------------------------------------------------------\r\n";
const char label1[] = "Sound Interfaces Info v1.72\r\n";
const char label2[] = "(c) Rainbow '2003-2005\r\n";
const char label3[] = "PCI devices\r\n";

const char* sensauralogo1 = "Software\\Sensaura\\Audio3D\\Settings";
const char* sensauralogo2 = ".DEFAULT\\Software\\Sensaura\\Audio3D\\Settings";
const char* sensauralogoregname = "SplashScreen";

int EAXUnifiedVersion = 0;

LRESULT CALLBACK WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WaitWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void InitProperty(HWND hWnd);
void ViewTabPage(int curt,HWND hWnd);
LRESULT CALLBACK pWndProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc5(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc6(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc7(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc8(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc9(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc10(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc11(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc12(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc13(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc14(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc15(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc16(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc17(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK pWndProc18(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AboutProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AllPCIProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
void A3D1SupportedTest(HWND hWnd);
void A3D2SupportedTest(HWND hWnd);
void A3D3SupportedTest(HWND hWnd);
void A3D4SupportedTest(HWND hWnd);
void A3D5SupportedTest(HWND hWnd);
void DirectSoundTest(HWND hDlg);
void OpenALSupportedTest(HWND hWnd);
void EAX1SupportedTest(HWND hWnd);
void EAX2SupportedTest(HWND hWnd);
void EAX3SupportedTest(HWND hWnd);
void EAX4SupportedTest(HWND hWnd);
void EAX5SupportedTest(HWND hWnd);
void WaveOutTest(HWND hWnd);
void MIDITest(HWND hWnd);
void SensauraSupportedTest(HWND hWnd);
void I3DL2SupportedTest(HWND hWnd);
void EAXUnifiedSupportedTest(int testversion,HWND hWnd,LPGUID lpGuid);
void AddToLog(const char* sbuf);
void ViewQuerySupport(LPKSPROPERTYSET prop,THIS_ REFGUID guid,int flag,char* name);
void ClearLog(void);
void SaveLog(HWND hDlg);
bool BoolQuerySupport(LPKSPROPERTYSET prop,THIS_ REFGUID guid,int flag,char* name);
void ASIOSupportedTest(HWND hWnd);
void LowLevelScan(HWND hWnd,bool onlyaudio);
int drvUnLoad(const char* name);
void CheckEffect(char *effectname, GUID guid, LPDIRECTSOUNDBUFFER8 dsb8);

BOOL CALLBACK EAX1SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext);
BOOL CALLBACK EAX2SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext);
BOOL CALLBACK EAX3SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext);
BOOL CALLBACK EAX4SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext);
BOOL CALLBACK EAX5SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext);
BOOL CALLBACK SensauraSupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext);
BOOL CALLBACK I3DL2SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext);

BOOL CALLBACK DSEnumCallback8(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext);

char *sysadr;
char exeFileName[MAX_PATH + 1]; // буфер для имени файла
char *onlyFileName;
char exePathName[MAX_PATH + 1];
char TempPathBuffer[MAX_PATH + 1];

const char *drvname = "rdrv.sys";
char fulldrvname[256];

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,int       nCmdShow)
{
 MSG msg;
 hInst = hInstance;

 static char mutexname[] = "sndinfo";
 HANDLE hh = OpenMutex(MUTEX_ALL_ACCESS, false, mutexname);
 if (hh == 0) hh = CreateMutex(0, false, mutexname);
  else return 0;

 // получение полного имени запускаемого файла
 GetModuleFileName(NULL, exeFileName, MAX_PATH + 1);
 
 // выкалупывание имени без пути
 onlyFileName = exeFileName + lstrlen(exeFileName) - 1;
 for (int i = lstrlen(exeFileName) - 1; i >= 0;i++)
 {
  if (onlyFileName[0] == '\\')
  {
   onlyFileName++;
   break;
  }
  onlyFileName--;
 }
 memset(exePathName,0,(MAX_PATH + 1) * sizeof(char));
 memcpy(exePathName,exeFileName,(onlyFileName - exeFileName)* sizeof(char));

 // временная папка
 GetTempPath(MAX_PATH,TempPathBuffer);

 sysadr = 0;
 // пытаемся вытащить драйвер из ресурсов
 HRSRC rc=NULL;
 HGLOBAL hgl=NULL;
 // поиск в ресурсах
 rc=FindResource(hInst,MAKEINTRESOURCE(IDR_SYS1),"sys");
 if (rc != NULL)
 {
  // получение указателя на ресурс
  hgl=LoadResource(hInst,rc);
  if (hgl != NULL)
  {
   sysadr = (char*)LockResource(hgl);
   if (sysadr != 0)
   {
    //wsprintf(fulldrvname,"%s%s",exePathName,drvname);
	wsprintf(fulldrvname,"%s%s",TempPathBuffer,drvname);	   
	HANDLE hh = CreateFile(fulldrvname,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	DWORD testlen;
	WriteFile(hh,sysadr,SizeofResource(NULL,rc),&testlen,NULL);
    CloseHandle(hh);
   }
  }
 }

 // ищем ветку для настроек ZoomFX
 HKEY hkey;
 unsigned long size = 8;
 unsigned long ptype = REG_DWORD;
 unsigned char tmp[8];
 int val_zero=0;

 SensauraLogo = 0x00;
 // открытие соответствующего раздела в реестре
 if (RegOpenKey(HKEY_CURRENT_USER,sensauralogo1,&hkey) == ERROR_SUCCESS)
 {
  // прибивание sensaura logo
  if (RegQueryValueEx(hkey,sensauralogoregname,NULL,&ptype,tmp,&size) == ERROR_SUCCESS)
  {
   if (tmp[0] == 0) SensauraLogo = 0x10;
    else SensauraLogo = 0x11;
   RegSetValueEx(hkey,sensauralogoregname,NULL,REG_DWORD,(LPBYTE)&val_zero,sizeof(DWORD));
  }
  RegCloseKey(hkey);
 }
 else
 if (RegOpenKey(HKEY_USERS,sensauralogo2,&hkey) == ERROR_SUCCESS)
 {
  // прибивание sensaura logo
  if (RegQueryValueEx(hkey,sensauralogoregname,NULL,&ptype,tmp,&size) == ERROR_SUCCESS)
  {
   if (tmp[0] == 0) SensauraLogo = 0x20;
    else SensauraLogo = 0x21;
   RegSetValueEx(hkey,sensauralogoregname,NULL,REG_DWORD,(LPBYTE)&val_zero,sizeof(DWORD));
  }
  RegCloseKey(hkey);
 }

 CoInitialize(NULL);

 hwWnd = CreateDialog(hInst, (LPCTSTR)IDD_WAIT, HWND_DESKTOP, (DLGPROC)WaitWndProc );

 hmWnd = CreateDialog(hInst, (LPCTSTR)IDD_MAINDLG, HWND_DESKTOP, (DLGPROC)WndProc );

 DestroyWindow(hwWnd);

 while (GetMessage(&msg, NULL, 0, 0))
 {
  TranslateMessage(&msg);
  DispatchMessage(&msg);
 }

 return msg.wParam;
}

void ClearLog(void)
{
 SendDlgItemMessage(logwnd,IDC_LOG,WM_SETTEXT,0,(LPARAM)"");
}

void AddToLog(const char* sbuf)
{
 SendDlgItemMessage(logwnd,IDC_LOG,EM_REPLACESEL,0,(LPARAM)sbuf);
}

LRESULT CALLBACK WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
       InitProperty(hDlg);
       ViewTabPage(0,hDlg);
       GetWindowRect(hDlg,&winbox);
       MoveWindow(hDlg,GetSystemMetrics(SM_CXSCREEN)/2-(winbox.right-winbox.left)/2,GetSystemMetrics(SM_CYSCREEN)/2-(winbox.bottom-winbox.top)/2,winbox.right-winbox.left,winbox.bottom-winbox.top,TRUE);
       break;
  case WM_COMMAND:
       switch (LOWORD(wParam))
       {
		case ID_EXIT:
			 SendMessage(hDlg, WM_DESTROY, 0, 0);
             break;
        case ID_SAVELOGAS:
			 SaveLog(hDlg);
			 break;
        case ID_ABOUT:
			 DialogBox(hInst,MAKEINTRESOURCE(IDD_ABOUT),hDlg,(DLGPROC)AboutProc);
			 break;
        case ID_ALLPCIDEVICES:
			 DialogBox(hInst,MAKEINTRESOURCE(IDD_ALLPCIDEVICES),hDlg,(DLGPROC)AllPCIProc);
			 break;
	   }
	   break;
  case WM_CLOSE:
  case WM_DESTROY:
	   drvUnLoad(drvname);
	   DeleteFile(fulldrvname);
	   CoUninitialize();

   	   // восстановление sensaura logo
       if (SensauraLogo == 0x11)
	   {
	    HKEY hkey;
		int val_one=1;
        // открытие соответствующего раздела в реестре
        if (RegOpenKey(HKEY_CURRENT_USER,sensauralogo1,&hkey) == ERROR_SUCCESS)
		{
         RegSetValueEx(hkey,sensauralogoregname,NULL,REG_DWORD,(LPBYTE)&val_one,sizeof(DWORD));
		}
        RegCloseKey(hkey);
	   }
	   else
       if (SensauraLogo == 0x21)
	   {
	    HKEY hkey;
	    int val_one=1;
        // открытие соответствующего раздела в реестре
        if (RegOpenKey(HKEY_USERS,sensauralogo2,&hkey) == ERROR_SUCCESS)
		{		 
         RegSetValueEx(hkey,sensauralogoregname,NULL,REG_DWORD,(LPBYTE)&val_one,sizeof(DWORD));
		}
        RegCloseKey(hkey);
	   }

	   PostQuitMessage(0);
       break;
  case WM_NOTIFY:
	  {
       LPNMHDR pnmh = (LPNMHDR) lParam;
       switch (pnmh->code)
       {
        case TCN_SELCHANGE:
             ViewTabPage(TabCtrl_GetCurSel(GetDlgItem(hDlg,IDC_TAB1)),hDlg);
             break;
       }
       break;
	  }
  case WM_SIZE:
	   ViewTabPage(actpage,hDlg);
	   break;
 }
 return FALSE;
}

LRESULT CALLBACK AboutProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
 switch (iMsg)
 {
  case WM_INITDIALOG:
	   GetWindowRect(hDlg,&winbox);
	   MoveWindow(hDlg,GetSystemMetrics(SM_CXSCREEN)/2-(winbox.right-winbox.left)/2,GetSystemMetrics(SM_CYSCREEN)/2-(winbox.bottom-winbox.top)/2,winbox.right-winbox.left,winbox.bottom-winbox.top,TRUE);
       break;
  case WM_COMMAND :
       switch (LOWORD (wParam))
	   {
        case IDOK :
             EndDialog (hDlg, 0);
             return TRUE;
	   }
       break;
 }
 return FALSE;
}

void ViewFileInfo(char *filename)
{
 FILEVERSION *fv = new FILEVERSION(filename);

 if (fv->enable == true)
 {
  AddToLog(fv->filename);
  AddToLog(end);

  wsprintf(buf," size: %d bytes\r\n",fv->filesize);
  AddToLog(buf);

  wsprintf(buf," path: %s\r\n",fv->filepath);
  AddToLog(buf);

  if (fv->CompanyName != 0)
  {
   wsprintf(buf," Company Name: %s\r\n",fv->CompanyName); AddToLog(buf);
  }
  if (fv->LegalCopyright != 0)
  {
   wsprintf(buf," Legal Copyright: %s\r\n",fv->LegalCopyright); AddToLog(buf);
  }
  if (fv->LegalTrademarks != 0)
  {
   wsprintf(buf," Legal Trademarks: %s\r\n",fv->LegalTrademarks); AddToLog(buf);
  }
  if (fv->ProductName != 0)
  {
   wsprintf(buf," Product Name: %s\r\n",fv->ProductName); AddToLog(buf);
  }
  if (fv->ProductVersion != 0)
  {
   wsprintf(buf," Product Version: %s\r\n",fv->ProductVersion); AddToLog(buf);
  }
  if (fv->FileVersion != 0)
  {
   wsprintf(buf," File Version: %s\r\n",fv->FileVersion); AddToLog(buf);
  }
  if (fv->FileDescription != 0)
  {
   wsprintf(buf," File Description: %s\r\n",fv->FileDescription); AddToLog(buf);
  }
  if (fv->InternalName != 0)
  {
   wsprintf(buf," Internal Name: %s\r\n",fv->InternalName); AddToLog(buf);
  }
  if (fv->OriginalFilename != 0)
  {
   wsprintf(buf," Original Filename: %s\r\n",fv->OriginalFilename); AddToLog(buf);
  }
  if (fv->PrivateBuild != 0)
  {
   wsprintf(buf," Private Build: %s\r\n",fv->PrivateBuild); AddToLog(buf);
  }
  if (fv->SpecialBuild != 0)
  {
   wsprintf(buf," Special Build: %s\r\n",fv->SpecialBuild); AddToLog(buf);
  }
  if (fv->Comments != 0)
  {
   wsprintf(buf," Comments: %s\r\n",fv->Comments); AddToLog(buf);
  }

  AddToLog(end);
 }

 delete fv;
}

void InitProperty(HWND hWnd)
{
 TCITEM tci[20];
 tci[0].mask = TCIF_TEXT;
 tci[0].pszText = "WaveOut";
 tci[1].mask = TCIF_TEXT;
 tci[1].pszText = "DirectSound";
 tci[2].mask = TCIF_TEXT;
 tci[2].pszText = "A3D (1.0)";
 tci[3].mask = TCIF_TEXT;
 tci[3].pszText = "A3D2 (1.2)";
 tci[4].mask = TCIF_TEXT;
 tci[4].pszText = "A3D3";
 tci[5].mask = TCIF_TEXT;
 tci[5].pszText = "A3D4 (2.0)";
 tci[6].mask = TCIF_TEXT;
 tci[6].pszText = "A3D5 (3.0)";
 tci[7].mask = TCIF_TEXT;
 tci[7].pszText = "OpenAL";
 tci[8].mask = TCIF_TEXT;
 tci[8].pszText = "I3DL2";
 tci[9].mask = TCIF_TEXT;
 tci[9].pszText = "Sensaura";
 tci[10].mask = TCIF_TEXT;
 tci[10].pszText = "EAX1";
 tci[11].mask = TCIF_TEXT;
 tci[11].pszText = "EAX2";
 tci[12].mask = TCIF_TEXT;
 tci[12].pszText = "EAX3";
 tci[13].mask = TCIF_TEXT;
 tci[13].pszText = "EAX4";
 tci[14].mask = TCIF_TEXT;
 tci[14].pszText = "EAX5";
 tci[15].mask = TCIF_TEXT;
 tci[15].pszText = "MIDI";
 tci[16].mask = TCIF_TEXT;
 tci[16].pszText = "ASIO";
 tci[17].mask = TCIF_TEXT;
 tci[17].pszText = "Low level";

 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),0,&tci[0]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),1,&tci[1]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),2,&tci[2]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),3,&tci[3]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),4,&tci[4]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),5,&tci[5]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),6,&tci[6]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),7,&tci[7]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),8,&tci[8]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),9,&tci[9]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),10,&tci[10]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),11,&tci[11]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),12,&tci[12]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),13,&tci[13]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),14,&tci[14]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),15,&tci[15]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),16,&tci[16]);
 TabCtrl_InsertItem(GetDlgItem(hWnd,IDC_TAB1),17,&tci[17]);

 int curpos = 0;
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETRANGE,0,MAKELPARAM(0, 18));
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;

 hpw[0] = CreateDialog(hInst,(LPCTSTR)IDD_WAVEOUTINFO, GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc12); 
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[1] = CreateDialog(hInst,(LPCTSTR)IDD_DSOUNDINFO,  GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc4); 
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[2] = CreateDialog(hInst,(LPCTSTR)IDD_A3D1INFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc10);
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[3] = CreateDialog(hInst,(LPCTSTR)IDD_A3D2INFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc11);
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[4] = CreateDialog(hInst,(LPCTSTR)IDD_A3D3INFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc1);
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[5] = CreateDialog(hInst,(LPCTSTR)IDD_A3D4INFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc2);
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[6] = CreateDialog(hInst,(LPCTSTR)IDD_A3D5INFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc3); 
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[7] = CreateDialog(hInst,(LPCTSTR)IDD_OPENALINFO,  GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc5); 
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[8] = CreateDialog(hInst,(LPCTSTR)IDD_I3DL2INFO,   GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc15); 
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[9] = CreateDialog(hInst,(LPCTSTR)IDD_SENSAURAINFO,GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc13); 
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[10]= CreateDialog(hInst,(LPCTSTR)IDD_EAX1INFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc6); 
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[11]= CreateDialog(hInst,(LPCTSTR)IDD_EAX2INFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc7); 
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[12]= CreateDialog(hInst,(LPCTSTR)IDD_EAX3INFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc8);
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[13]= CreateDialog(hInst,(LPCTSTR)IDD_EAX4INFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc9);
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[14]= CreateDialog(hInst,(LPCTSTR)IDD_EAX5INFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc18);
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[15]= CreateDialog(hInst,(LPCTSTR)IDD_MIDIINFO,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc14);
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[16]= CreateDialog(hInst,(LPCTSTR)IDD_ASIO,        GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc16);
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
 hpw[17]= CreateDialog(hInst,(LPCTSTR)IDD_LOWLEVEL,    GetDlgItem(hWnd,IDC_TAB1),(DLGPROC)pWndProc17);
 SendDlgItemMessage(hwWnd,IDC_STARTPROGRESS,PBM_SETPOS,curpos,0); curpos++;
/* 
 ShowWindow(hwWnd,SW_HIDE);
 UpdateWindow(hwWnd);

 ShowWindow(hmWnd,SW_SHOW);
 UpdateWindow(hmWnd);
 SetForegroundWindow(hmWnd);
 SetFocus(hmWnd);
 */
}

void ViewTabPage(int curt,HWND hWnd)
{
 RECT rect,rectc;
 int xres,yres;

 GetClientRect(hWnd,&rect);
 xres = rect.right-rect.left;
 yres = rect.bottom-rect.top;

 MoveWindow(GetDlgItem(hWnd,IDC_TAB1),0,0,xres,yres,TRUE);

 GetClientRect(GetDlgItem(hWnd,IDC_TAB1),&rect);
 TabCtrl_AdjustRect(GetDlgItem(hWnd,IDC_TAB1),FALSE,&rect); 
 ShowWindow(hpw[actpage],SW_HIDE);
 MoveWindow(hpw[curt],rect.left,rect.top,rect.right - rect.left,rect.bottom - rect.top,TRUE);
 GetClientRect(hpw[curt],&rectc);
 MoveWindow(GetDlgItem(hpw[curt],IDC_LOG),0,0,rectc.right,rectc.bottom,TRUE);
 ShowWindow(hpw[curt],SW_SHOW);
 UpdateWindow(hpw[curt]);
 actpage = curt;
}

LRESULT CALLBACK pWndProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   A3D3SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   A3D4SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   A3D5SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc4(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   DirectSoundTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc5(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   OpenALSupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc6(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   EAX1SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc7(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   EAX2SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc8(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   EAX3SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc9(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   EAX4SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc10(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   A3D1SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc11(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   A3D2SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc12(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
       WaveOutTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc13(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
       SensauraSupportedTest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc14(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
       MIDITest(hDlg);
       break;
 }
 return FALSE;
}

LRESULT CALLBACK pWndProc15(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
       I3DL2SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

bool BoolTestEAX2Prop(LPKSPROPERTYSET propset)
{
 if (BoolQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_NONE,"DSPROPERTY_EAXLISTENER_NONE") == false &&
	 BoolQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_NONE,"DSPROPERTY_EAXBUFFER_NONE") == false)
 {
  return false;
 }
 return true;
}

void TestEAX2Prop(LPKSPROPERTYSET propset)
{
 AddToLog("Listener properties:\r\n");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_NONE,"DSPROPERTY_EAXLISTENER_NONE");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_ALLPARAMETERS,"DSPROPERTY_EAXLISTENER_ALLPARAMETERS");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_ROOM,"DSPROPERTY_EAXLISTENER_ROOM");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_ROOMHF,"DSPROPERTY_EAXLISTENER_ROOMHF");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_ROOMROLLOFFFACTOR,"DSPROPERTY_EAXLISTENER_ROOMROLLOFFFACTOR");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_DECAYTIME,"DSPROPERTY_EAXLISTENER_DECAYTIME");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_DECAYHFRATIO,"DSPROPERTY_EAXLISTENER_DECAYHFRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_REFLECTIONS,"DSPROPERTY_EAXLISTENER_REFLECTIONS");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_REFLECTIONSDELAY,"DSPROPERTY_EAXLISTENER_REFLECTIONSDELAY");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_REVERB,"DSPROPERTY_EAXLISTENER_REVERB");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_REVERBDELAY,"DSPROPERTY_EAXLISTENER_REVERBDELAY");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_ENVIRONMENT,"DSPROPERTY_EAXLISTENER_ENVIRONMENT");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_ENVIRONMENTSIZE,"DSPROPERTY_EAXLISTENER_ENVIRONMENTSIZE");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_ENVIRONMENTDIFFUSION,"DSPROPERTY_EAXLISTENER_ENVIRONMENTDIFFUSION");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_AIRABSORPTIONHF,"DSPROPERTY_EAXLISTENER_AIRABSORPTIONHF");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_FLAGS,"DSPROPERTY_EAXLISTENER_FLAGS");

 AddToLog("Buffer properties:\r\n");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_NONE,"DSPROPERTY_EAXBUFFER_NONE");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_ALLPARAMETERS,"DSPROPERTY_EAXBUFFER_ALLPARAMETERS");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_DIRECT,"DSPROPERTY_EAXBUFFER_DIRECT");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_DIRECTHF,"DSPROPERTY_EAXBUFFER_DIRECTHF");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_ROOM,"DSPROPERTY_EAXBUFFER_ROOM");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_ROOMHF,"DSPROPERTY_EAXBUFFER_ROOMHF");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_ROOMROLLOFFFACTOR,"DSPROPERTY_EAXBUFFER_ROOMROLLOFFFACTOR");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_OBSTRUCTION,"DSPROPERTY_EAXBUFFER_OBSTRUCTION");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_OBSTRUCTIONLFRATIO,"DSPROPERTY_EAXBUFFER_OBSTRUCTIONLFRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_OCCLUSION,"DSPROPERTY_EAXBUFFER_OCCLUSION");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_OCCLUSIONLFRATIO,"DSPROPERTY_EAXBUFFER_OCCLUSIONLFRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_OCCLUSIONROOMRATIO,"DSPROPERTY_EAXBUFFER_OCCLUSIONROOMRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_OUTSIDEVOLUMEHF,"DSPROPERTY_EAXBUFFER_OUTSIDEVOLUMEHF");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_AIRABSORPTIONFACTOR,"DSPROPERTY_EAXBUFFER_AIRABSORPTIONFACTOR");
 ViewQuerySupport(propset,DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_FLAGS,"DSPROPERTY_EAXBUFFER_FLAGS");
}

bool BoolTestEAX3Prop(LPKSPROPERTYSET propset)
{
 if (BoolQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_NONE,"DSPROPERTY_EAXLISTENER_NONE") == false &&
	 BoolQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_NONE,"DSPROPERTY_EAXBUFFER_NONE") == false)
 {
  return false;
 }
 return true;
}

void TestEAX3Prop(LPKSPROPERTYSET propset)
{
 AddToLog("Listener properties:\r\n");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_NONE,"DSPROPERTY_EAXLISTENER_NONE");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ALLPARAMETERS,"DSPROPERTY_EAXLISTENER_ALLPARAMETERS");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ENVIRONMENT,"DSPROPERTY_EAXLISTENER_ENVIRONMENT");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ENVIRONMENTSIZE,"DSPROPERTY_EAXLISTENER_ENVIRONMENTSIZE");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ENVIRONMENTDIFFUSION,"DSPROPERTY_EAXLISTENER_ENVIRONMENTDIFFUSION");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ROOM,"DSPROPERTY_EAXLISTENER_ROOM");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ROOMHF,"DSPROPERTY_EAXLISTENER_ROOMHF");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ROOMLF,"DSPROPERTY_EAXLISTENER_ROOMLF");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_DECAYTIME,"DSPROPERTY_EAXLISTENER_DECAYTIME");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_DECAYHFRATIO,"DSPROPERTY_EAXLISTENER_DECAYHFRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_DECAYLFRATIO,"DSPROPERTY_EAXLISTENER_DECAYLFRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_REFLECTIONS,"DSPROPERTY_EAXLISTENER_REFLECTIONS");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_REFLECTIONSDELAY,"DSPROPERTY_EAXLISTENER_REFLECTIONSDELAY");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_REFLECTIONSPAN,"DSPROPERTY_EAXLISTENER_REFLECTIONSPAN");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_REVERB,"DSPROPERTY_EAXLISTENER_REVERB");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_REVERBDELAY,"DSPROPERTY_EAXLISTENER_REVERBDELAY");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_REVERBPAN,"DSPROPERTY_EAXLISTENER_REVERBPAN");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ECHOTIME,"DSPROPERTY_EAXLISTENER_ECHOTIME");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ECHODEPTH,"DSPROPERTY_EAXLISTENER_ECHODEPTH");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_MODULATIONTIME,"DSPROPERTY_EAXLISTENER_MODULATIONTIME");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_MODULATIONDEPTH,"DSPROPERTY_EAXLISTENER_MODULATIONDEPTH");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_AIRABSORPTIONHF,"DSPROPERTY_EAXLISTENER_AIRABSORPTIONHF");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_HFREFERENCE,"DSPROPERTY_EAXLISTENER_HFREFERENCE");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_LFREFERENCE,"DSPROPERTY_EAXLISTENER_LFREFERENCE");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ROOMROLLOFFFACTOR,"DSPROPERTY_EAXLISTENER_ROOMROLLOFFFACTOR");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_FLAGS,"DSPROPERTY_EAXLISTENER_FLAGS");
 
 AddToLog("Buffer properties:\r\n");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_NONE,"DSPROPERTY_EAXBUFFER_NONE");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_ALLPARAMETERS,"DSPROPERTY_EAXBUFFER_ALLPARAMETERS");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_OBSTRUCTIONPARAMETERS,"DSPROPERTY_EAXBUFFER_OBSTRUCTIONPARAMETERS");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_OCCLUSIONPARAMETERS,"DSPROPERTY_EAXBUFFER_OCCLUSIONPARAMETERS");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_EXCLUSIONPARAMETERS,"DSPROPERTY_EAXBUFFER_EXCLUSIONPARAMETERS");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_DIRECT,"DSPROPERTY_EAXBUFFER_DIRECT");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_DIRECTHF,"DSPROPERTY_EAXBUFFER_DIRECTHF");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_ROOM,"DSPROPERTY_EAXBUFFER_ROOM");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_ROOMHF,"DSPROPERTY_EAXBUFFER_ROOMHF");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_OBSTRUCTION,"DSPROPERTY_EAXBUFFER_OBSTRUCTION");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_OBSTRUCTIONLFRATIO,"DSPROPERTY_EAXBUFFER_OBSTRUCTIONLFRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_OCCLUSION,"DSPROPERTY_EAXBUFFER_OCCLUSION");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_OCCLUSIONLFRATIO,"DSPROPERTY_EAXBUFFER_OCCLUSIONLFRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_OCCLUSIONROOMRATIO,"DSPROPERTY_EAXBUFFER_OCCLUSIONROOMRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_OCCLUSIONDIRECTRATIO,"DSPROPERTY_EAXBUFFER_OCCLUSIONDIRECTRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_EXCLUSION,"DSPROPERTY_EAXBUFFER_EXCLUSION");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_EXCLUSIONLFRATIO,"DSPROPERTY_EAXBUFFER_EXCLUSIONLFRATIO");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_OUTSIDEVOLUMEHF ,"DSPROPERTY_EAXBUFFER_OUTSIDEVOLUMEHF ");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_DOPPLERFACTOR,"DSPROPERTY_EAXBUFFER_DOPPLERFACTOR");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_ROLLOFFFACTOR,"DSPROPERTY_EAXBUFFER_ROLLOFFFACTOR");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_ROOMROLLOFFFACTOR,"DSPROPERTY_EAXBUFFER_ROOMROLLOFFFACTOR");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_AIRABSORPTIONFACTOR,"DSPROPERTY_EAXBUFFER_AIRABSORPTIONFACTOR");
 ViewQuerySupport(propset,DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_FLAGS,"DSPROPERTY_EAXBUFFER_FLAGS");
}

bool BoolTestEAX4Prop(LPKSPROPERTYSET propset)
{
 if (BoolQuerySupport(propset,EAXPROPERTYID_EAX40_Context,EAX4CONTEXT_NONE,"EAXCONTEXT_NONE") == false &&
	 BoolQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_NONE,"EAXSOURCE_NONE") == false)
 {
  return false;
 }
 return true;
}

void TestEAX4Prop(LPKSPROPERTYSET propset)
{
 AddToLog("Context properties:\r\n");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Context,EAX4CONTEXT_NONE,"EAXCONTEXT_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Context,EAX4CONTEXT_ALLPARAMETERS,"EAXCONTEXT_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Context,EAX4CONTEXT_PRIMARYFXSLOTID,"EAXCONTEXT_PRIMARYFXSLOTID");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Context,EAX4CONTEXT_DISTANCEFACTOR,"EAXCONTEXT_DISTANCEFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Context,EAX4CONTEXT_AIRABSORPTIONHF,"EAXCONTEXT_AIRABSORPTIONHF");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Context,EAX4CONTEXT_HFREFERENCE,"EAXCONTEXT_HFREFERENCE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Context,EAX4CONTEXT_LASTERROR,"EAXCONTEXT_LASTERROR");

 AddToLog("FXSlot0 properties:\r\n");  
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot0,EAX4FXSLOT_PARAMETER,"EAXFXSLOT_PARAMETER");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot0,EAX4FXSLOT_NONE,"EAXFXSLOT_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot0,EAX4FXSLOT_ALLPARAMETERS,"EAXFXSLOT_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot0,EAX4FXSLOT_LOADEFFECT,"EAXFXSLOT_LOADEFFECT");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot0,EAX4FXSLOT_VOLUME,"EAXFXSLOT_VOLUME");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot0,EAX4FXSLOT_LOCK,"EAXFXSLOT_LOCK");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot0,EAX4FXSLOT_FLAGS,"EAXFXSLOT_FLAGS");

 AddToLog("FXSlot1 properties:\r\n");  
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot1,EAX4FXSLOT_PARAMETER,"EAXFXSLOT_PARAMETER");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot1,EAX4FXSLOT_NONE,"EAXFXSLOT_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot1,EAX4FXSLOT_ALLPARAMETERS,"EAXFXSLOT_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot1,EAX4FXSLOT_LOADEFFECT,"EAXFXSLOT_LOADEFFECT");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot1,EAX4FXSLOT_VOLUME,"EAXFXSLOT_VOLUME");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot1,EAX4FXSLOT_LOCK,"EAXFXSLOT_LOCK");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot1,EAX4FXSLOT_FLAGS,"EAXFXSLOT_FLAGS");

 AddToLog("FXSlot2 properties:\r\n");  
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot2,EAX4FXSLOT_PARAMETER,"EAXFXSLOT_PARAMETER");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot2,EAX4FXSLOT_NONE,"EAXFXSLOT_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot2,EAX4FXSLOT_ALLPARAMETERS,"EAXFXSLOT_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot2,EAX4FXSLOT_LOADEFFECT,"EAXFXSLOT_LOADEFFECT");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot2,EAX4FXSLOT_VOLUME,"EAXFXSLOT_VOLUME");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot2,EAX4FXSLOT_LOCK,"EAXFXSLOT_LOCK");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot2,EAX4FXSLOT_FLAGS,"EAXFXSLOT_FLAGS");

 AddToLog("FXSlot3 properties:\r\n");  
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot3,EAX4FXSLOT_PARAMETER,"EAXFXSLOT_PARAMETER");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot3,EAX4FXSLOT_NONE,"EAXFXSLOT_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot3,EAX4FXSLOT_ALLPARAMETERS,"EAXFXSLOT_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot3,EAX4FXSLOT_LOADEFFECT,"EAXFXSLOT_LOADEFFECT");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot3,EAX4FXSLOT_VOLUME,"EAXFXSLOT_VOLUME");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot3,EAX4FXSLOT_LOCK,"EAXFXSLOT_LOCK");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_FXSlot3,EAX4FXSLOT_FLAGS,"EAXFXSLOT_FLAGS");

 AddToLog("Source properties:\r\n");  
  
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_NONE,"EAXSOURCE_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_ALLPARAMETERS,"EAXSOURCE_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_OBSTRUCTIONPARAMETERS,"EAXSOURCE_OBSTRUCTIONPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_OCCLUSIONPARAMETERS,"EAXSOURCE_OCCLUSIONPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_EXCLUSIONPARAMETERS,"EAXSOURCE_EXCLUSIONPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_DIRECT,"EAXSOURCE_DIRECT");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_DIRECTHF,"EAXSOURCE_DIRECTHF");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_ROOM,"EAXSOURCE_ROOM");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_ROOMHF,"EAXSOURCE_ROOMHF");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_OBSTRUCTION,"EAXSOURCE_OBSTRUCTION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_OBSTRUCTIONLFRATIO,"EAXSOURCE_OBSTRUCTIONLFRATIO");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_OCCLUSION,"EAXSOURCE_OCCLUSION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_OCCLUSIONLFRATIO,"EAXSOURCE_OCCLUSIONLFRATIO");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_OCCLUSIONROOMRATIO,"EAXSOURCE_OCCLUSIONROOMRATIO");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_OCCLUSIONDIRECTRATIO,"EAXSOURCE_OCCLUSIONDIRECTRATIO");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_EXCLUSION,"EAXSOURCE_EXCLUSION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_EXCLUSIONLFRATIO,"EAXSOURCE_EXCLUSIONLFRATIO");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_OUTSIDEVOLUMEHF,"EAXSOURCE_OUTSIDEVOLUMEHF");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_DOPPLERFACTOR,"EAXSOURCE_DOPPLERFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_ROLLOFFFACTOR,"EAXSOURCE_ROLLOFFFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_ROOMROLLOFFFACTOR,"EAXSOURCE_ROOMROLLOFFFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_AIRABSORPTIONFACTOR,"EAXSOURCE_AIRABSORPTIONFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_FLAGS,"EAXSOURCE_FLAGS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_SENDPARAMETERS,"EAXSOURCE_SENDPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_ALLSENDPARAMETERS,"EAXSOURCE_ALLSENDPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_OCCLUSIONSENDPARAMETERS,"EAXSOURCE_OCCLUSIONSENDPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_EXCLUSIONSENDPARAMETERS,"EAXSOURCE_EXCLUSIONSENDPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX40_Source,EAX4SOURCE_ACTIVEFXSLOTID,"EAXSOURCE_ACTIVEFXSLOTID");
}

bool BoolTestEAX5Prop(LPKSPROPERTYSET propset)
{
 if (BoolQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_NONE,"EAXCONTEXT_NONE") == false &&
	 BoolQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_NONE,"EAXSOURCE_NONE") == false)
 {
  return false;
 }
 return true;
}

void TestEAX5Prop(LPKSPROPERTYSET propset)
{
 AddToLog("Context properties:\r\n");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_NONE,"EAXCONTEXT_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_ALLPARAMETERS,"EAXCONTEXT_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_PRIMARYFXSLOTID,"EAXCONTEXT_PRIMARYFXSLOTID");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_DISTANCEFACTOR,"EAXCONTEXT_DISTANCEFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_AIRABSORPTIONHF,"EAXCONTEXT_AIRABSORPTIONHF");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_HFREFERENCE,"EAXCONTEXT_HFREFERENCE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_LASTERROR,"EAXCONTEXT_LASTERROR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_SPEAKERCONFIG,"EAXCONTEXT_SPEAKERCONFIG");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_EAXSESSION,"EAXCONTEXT_EAXSESSION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_MACROFXFACTOR,"EAXCONTEXT_MACROFXFACTOR");

 AddToLog("FXSlot0 properties:\r\n");  
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot0,EAX5FXSLOT_PARAMETER,"EAXFXSLOT_PARAMETER");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot0,EAX5FXSLOT_NONE,"EAXFXSLOT_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot0,EAX5FXSLOT_ALLPARAMETERS,"EAXFXSLOT_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot0,EAX5FXSLOT_LOADEFFECT,"EAXFXSLOT_LOADEFFECT");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot0,EAX5FXSLOT_VOLUME,"EAXFXSLOT_VOLUME");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot0,EAX5FXSLOT_LOCK,"EAXFXSLOT_LOCK");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot0,EAX5FXSLOT_FLAGS,"EAXFXSLOT_FLAGS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot0,EAX5FXSLOT_OCCLUSION,"EAXFXSLOT_OCCLUSION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot0,EAX5FXSLOT_OCCLUSIONLFRATIO,"EAXFXSLOT_OCCLUSIONLFRATIO");
 
 AddToLog("FXSlot1 properties:\r\n");  
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot1,EAX5FXSLOT_PARAMETER,"EAXFXSLOT_PARAMETER");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot1,EAX5FXSLOT_NONE,"EAXFXSLOT_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot1,EAX5FXSLOT_ALLPARAMETERS,"EAXFXSLOT_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot1,EAX5FXSLOT_LOADEFFECT,"EAXFXSLOT_LOADEFFECT");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot1,EAX5FXSLOT_VOLUME,"EAXFXSLOT_VOLUME");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot1,EAX5FXSLOT_LOCK,"EAXFXSLOT_LOCK");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot1,EAX5FXSLOT_FLAGS,"EAXFXSLOT_FLAGS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot1,EAX5FXSLOT_OCCLUSION,"EAXFXSLOT_OCCLUSION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot1,EAX5FXSLOT_OCCLUSIONLFRATIO,"EAXFXSLOT_OCCLUSIONLFRATIO");

 AddToLog("FXSlot2 properties:\r\n");  
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot2,EAX5FXSLOT_PARAMETER,"EAXFXSLOT_PARAMETER");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot2,EAX5FXSLOT_NONE,"EAXFXSLOT_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot2,EAX5FXSLOT_ALLPARAMETERS,"EAXFXSLOT_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot2,EAX5FXSLOT_LOADEFFECT,"EAXFXSLOT_LOADEFFECT");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot2,EAX5FXSLOT_VOLUME,"EAXFXSLOT_VOLUME");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot2,EAX5FXSLOT_LOCK,"EAXFXSLOT_LOCK");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot2,EAX5FXSLOT_FLAGS,"EAXFXSLOT_FLAGS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot2,EAX5FXSLOT_OCCLUSION,"EAXFXSLOT_OCCLUSION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot2,EAX5FXSLOT_OCCLUSIONLFRATIO,"EAXFXSLOT_OCCLUSIONLFRATIO");

 AddToLog("FXSlot3 properties:\r\n");  
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot3,EAX5FXSLOT_PARAMETER,"EAXFXSLOT_PARAMETER");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot3,EAX5FXSLOT_NONE,"EAXFXSLOT_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot3,EAX5FXSLOT_ALLPARAMETERS,"EAXFXSLOT_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot3,EAX5FXSLOT_LOADEFFECT,"EAXFXSLOT_LOADEFFECT");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot3,EAX5FXSLOT_VOLUME,"EAXFXSLOT_VOLUME");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot3,EAX5FXSLOT_LOCK,"EAXFXSLOT_LOCK");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot3,EAX5FXSLOT_FLAGS,"EAXFXSLOT_FLAGS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot3,EAX5FXSLOT_OCCLUSION,"EAXFXSLOT_OCCLUSION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_FXSlot3,EAX5FXSLOT_OCCLUSIONLFRATIO,"EAXFXSLOT_OCCLUSIONLFRATIO");

 AddToLog("Source properties:\r\n");  
  
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_NONE,"EAXSOURCE_NONE");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_ALLPARAMETERS,"EAXSOURCE_ALLPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_OBSTRUCTIONPARAMETERS,"EAXSOURCE_OBSTRUCTIONPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_OCCLUSIONPARAMETERS,"EAXSOURCE_OCCLUSIONPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_EXCLUSIONPARAMETERS,"EAXSOURCE_EXCLUSIONPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_DIRECT,"EAXSOURCE_DIRECT");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_DIRECTHF,"EAXSOURCE_DIRECTHF");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_ROOM,"EAXSOURCE_ROOM");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_ROOMHF,"EAXSOURCE_ROOMHF");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_OBSTRUCTION,"EAXSOURCE_OBSTRUCTION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_OBSTRUCTIONLFRATIO,"EAXSOURCE_OBSTRUCTIONLFRATIO");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_OCCLUSION,"EAXSOURCE_OCCLUSION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_OCCLUSIONLFRATIO,"EAXSOURCE_OCCLUSIONLFRATIO");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_OCCLUSIONROOMRATIO,"EAXSOURCE_OCCLUSIONROOMRATIO");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_OCCLUSIONDIRECTRATIO,"EAXSOURCE_OCCLUSIONDIRECTRATIO");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_EXCLUSION,"EAXSOURCE_EXCLUSION");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_EXCLUSIONLFRATIO,"EAXSOURCE_EXCLUSIONLFRATIO");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_OUTSIDEVOLUMEHF,"EAXSOURCE_OUTSIDEVOLUMEHF");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_DOPPLERFACTOR,"EAXSOURCE_DOPPLERFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_ROLLOFFFACTOR,"EAXSOURCE_ROLLOFFFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_ROOMROLLOFFFACTOR,"EAXSOURCE_ROOMROLLOFFFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_AIRABSORPTIONFACTOR,"EAXSOURCE_AIRABSORPTIONFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_FLAGS,"EAXSOURCE_FLAGS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_SENDPARAMETERS,"EAXSOURCE_SENDPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_ALLSENDPARAMETERS,"EAXSOURCE_ALLSENDPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_OCCLUSIONSENDPARAMETERS,"EAXSOURCE_OCCLUSIONSENDPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_EXCLUSIONSENDPARAMETERS,"EAXSOURCE_EXCLUSIONSENDPARAMETERS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_ACTIVEFXSLOTID,"EAXSOURCE_ACTIVEFXSLOTID");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_MACROFXFACTOR,"EAXSOURCE_MACROFXFACTOR");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_SPEAKERLEVELS,"EAXSOURCE_SPEAKERLEVELS");
 ViewQuerySupport(propset,EAXPROPERTYID_EAX50_Source,EAX5SOURCE_ALL2DPARAMETERS,"EAXSOURCE_ALL2DPARAMETERS");
}

IA3d5 *gpA3d5 = NULL;

BOOL CALLBACK A3DEnumCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{
 IA3d5 *gpA3d = 0;
 HRESULT hResult;
 int queryversion = (int)lpContext;

 if (lstrlen((char*)lpcstrModule) == 0)
 {
  wsprintf(buf,"--- %s\r\n",(char*)lpcstrDescription);
  AddToLog(buf);
 }
 else
 {
  wsprintf(buf,"--- %s [%s]\r\n",(char*)lpcstrDescription,(char*)lpcstrModule);
  AddToLog(buf);
 }

 if (lpGuid == 0)
 {
  AddToLog("GUID: default\r\n");
 }
 else
 {
  wsprintf(buf,"GUID: 0x%X%X%X%X\r\n",lpGuid->Data1,lpGuid->Data2,lpGuid->Data3,lpGuid->Data4);
  AddToLog(buf);
 }

 switch (queryversion)
 {
  case 3:
	   AddToLog("A3D3 - ");
       hResult = CoCreateInstance(CLSID_A3dApi, NULL, CLSCTX_INPROC_SERVER, IID_IA3d3, (void **)&gpA3d);
       if(hResult != S_OK) goto nosupp2;
       hResult = gpA3d->Init(lpGuid,A3D_DIRECT_PATH_A3D | A3D_1ST_REFLECTIONS | A3D_DISABLE_FOCUS_MUTE | A3D_DISABLE_SPLASHSCREEN | A3D_GEOMETRIC_REVERB | A3D_OCCLUSIONS | A3D_REVERB, A3DRENDERPREFS_DEFAULT);
       if(hResult != S_OK) goto nosupp;
	   break;
  case 4:
	   AddToLog("A3D4 (2.0) - ");
       hResult = CoCreateInstance(CLSID_A3dApi, NULL, CLSCTX_INPROC_SERVER, IID_IA3d4, (void **)&gpA3d);
       if(hResult != S_OK) goto nosupp2;
       hResult = gpA3d->Init(lpGuid,A3D_DIRECT_PATH_A3D | A3D_1ST_REFLECTIONS | A3D_DISABLE_FOCUS_MUTE | A3D_DISABLE_SPLASHSCREEN | A3D_GEOMETRIC_REVERB | A3D_OCCLUSIONS | A3D_REVERB, A3DRENDERPREFS_DEFAULT);
       if(hResult != S_OK) goto nosupp;
	   break;
  case 5:
	   AddToLog("A3D5 (3.0) - ");
       gpA3d = gpA3d5;
       hResult = gpA3d->InitEx(lpGuid,A3D_DIRECT_PATH_A3D | A3D_1ST_REFLECTIONS | A3D_DISABLE_FOCUS_MUTE | A3D_DISABLE_SPLASHSCREEN | A3D_GEOMETRIC_REVERB | A3D_OCCLUSIONS | A3D_REVERB, A3DRENDERPREFS_DEFAULT,0,A3D_CL_NORMAL);
       if(hResult != S_OK) goto nosupp;
	   break;    
 }
 
 AddToLog(supported);
 AddToLog(end);

 wsprintf(buf,"IsFeatureAvailable:\r\n");
 AddToLog(buf);
 AddToLog(" A3D_1ST_REFLECTIONS:\t");
 if (gpA3d->IsFeatureAvailable(A3D_1ST_REFLECTIONS) == FALSE) 
  AddToLog(notsupported);
 else
  AddToLog(supported);
 AddToLog(end);

 AddToLog(" A3D_OCCLUSIONS:\t");
 if (gpA3d->IsFeatureAvailable(A3D_OCCLUSIONS) == FALSE)
  AddToLog(notsupported);
 else
  AddToLog(supported);
 AddToLog(end);

 A3DCAPS_HARDWARE A3Dhard;
 memset(&A3Dhard,0,sizeof(A3DCAPS_HARDWARE));
 A3Dhard.dwSize = sizeof(A3DCAPS_HARDWARE);
 hResult = gpA3d->GetHardwareCaps(&A3Dhard);
 if(hResult != S_OK)
 {
  wsprintf(buf,"Error in GetHardwareCaps() - ");
  AddToLog(buf);
  if (hResult == E_POINTER) 
  {
   wsprintf(buf,"E_POINTER\r\n");
   AddToLog(buf);
  }
  if (hResult == A3DERROR_FUNCTION_NOT_VALID_BEFORE_INIT) 
  {
   wsprintf(buf,"A3DERROR_FUNCTION_NOT_VALID_BEFORE_INIT\r\n");
   AddToLog(buf);
  }
  return 0;
 }

 wsprintf(buf,"Hardware caps:\r\n");
 AddToLog(buf);
 
 wsprintf(buf," dwFlags:\t\t\t");
 AddToLog(buf);
 if (A3Dhard.dwFlags & A3D_DIRECT_PATH_A3D)
 {
  wsprintf(buf,"A3D_DIRECT_PATH_A3D");
  AddToLog(buf);
 }
 else
 {
  if (A3Dhard.dwFlags & A3D_DIRECT_PATH_GENERIC)
  {
   wsprintf(buf,"A3D_DIRECT_PATH_GENERIC");
   AddToLog(buf);
  }
  else
  {
   wsprintf(buf,"0x%X\r\n",A3Dhard.dwFlags);
   AddToLog(buf);
  }
 }
 if (A3Dhard.dwFlags & A3D_1ST_REFLECTIONS) 
 {
  wsprintf(buf,", A3D_1ST_REFLECTIONS");
  AddToLog(buf);
 }
 if (A3Dhard.dwFlags & A3D_GEOMETRIC_REVERB)
 {
  wsprintf(buf,", A3D_GEOMETRIC_REVERB");
  AddToLog(buf);
 }
 if (A3Dhard.dwFlags & A3D_OCCLUSIONS)
 {
  wsprintf(buf,", A3D_OCCLUSIONS");
  AddToLog(buf);
 }
 if (A3Dhard.dwFlags & A3D_REVERB)
 {
  wsprintf(buf,", A3D_REVERB");
  AddToLog(buf);
 }

 AddToLog(end);

 wsprintf(buf," dwOutputChannels:\t%d\r\n",A3Dhard.dwOutputChannels);
 AddToLog(buf);
 wsprintf(buf," dwMinSampleRate:\t%d\r\n",A3Dhard.dwMinSampleRate);
 AddToLog(buf);
 wsprintf(buf," dwMaxSampleRate:\t%d\r\n",A3Dhard.dwMaxSampleRate);
 AddToLog(buf);
 wsprintf(buf," dwMax2DBuffers:\t\t%d\r\n",A3Dhard.dwMax2DBuffers);
 AddToLog(buf);
 wsprintf(buf," dwMax3DBuffers:\t\t%d\r\n",A3Dhard.dwMax3DBuffers);
 AddToLog(buf);

 A3DCAPS_SOFTWARE A3Dsoft;
 memset(&A3Dsoft,0,sizeof(A3DCAPS_SOFTWARE));
 A3Dsoft.dwSize = sizeof(A3DCAPS_SOFTWARE);
 hResult = gpA3d->GetSoftwareCaps(&A3Dsoft);
 if(hResult != S_OK)
 {
  wsprintf(buf,"Error in GetSoftwareCaps() - ");
  AddToLog(buf);
  if (hResult == E_POINTER)
  {
   wsprintf(buf,"E_POINTER\r\n");
   AddToLog(buf);
  }
  if (hResult == A3DERROR_FUNCTION_NOT_VALID_BEFORE_INIT)
  {
   wsprintf(buf,"A3DERROR_FUNCTION_NOT_VALID_BEFORE_INIT\r\n");
   AddToLog(buf);
  }
  return 0;
 }
 wsprintf(buf,"Software caps:\r\n");
 AddToLog(buf);
 wsprintf(buf," dwFlags:\t\t\t");
 AddToLog(buf);
 if (A3Dsoft.dwFlags & A3D_DIRECT_PATH_A3D)
 {
  wsprintf(buf,"A3D_DIRECT_PATH_A3D");
  AddToLog(buf);
 }
 else
 {
  if (A3Dsoft.dwFlags & A3D_DIRECT_PATH_GENERIC)
  {
   wsprintf(buf,"A3D_DIRECT_PATH_GENERIC");
   AddToLog(buf);
  }
  else
  {
   wsprintf(buf,"0x%X\r\n",A3Dhard.dwFlags);
   AddToLog(buf);
  }
 }
 if (A3Dsoft.dwFlags & A3D_1ST_REFLECTIONS) 
 {
  wsprintf(buf,", A3D_1ST_REFLECTIONS");
  AddToLog(buf);
 }
 if (A3Dsoft.dwFlags & A3D_GEOMETRIC_REVERB)
 {
  wsprintf(buf,", A3D_GEOMETRIC_REVERB");
  AddToLog(buf);
 }
 if (A3Dsoft.dwFlags & A3D_OCCLUSIONS)
 {
  wsprintf(buf,", A3D_OCCLUSIONS");
  AddToLog(buf);
 }
 if (A3Dsoft.dwFlags & A3D_REVERB)
 {
  wsprintf(buf,", A3D_REVERB");
  AddToLog(buf);
 }
 AddToLog(end);

 wsprintf(buf," dwVersion:\t\t%d.%d\r\n",(A3Dsoft.dwVersion/10),A3Dsoft.dwVersion - (A3Dsoft.dwVersion/10)*10);
 AddToLog(buf);
 wsprintf(buf," dwOutputChannels:\t%d\r\n",A3Dsoft.dwOutputChannels);
 AddToLog(buf);
 wsprintf(buf," dwMinSampleRate:\t%d\r\n",A3Dsoft.dwMinSampleRate);
 AddToLog(buf);
 wsprintf(buf," dwMaxSampleRate:\t%d\r\n",A3Dsoft.dwMaxSampleRate);
 AddToLog(buf);
 wsprintf(buf," dwMax2DBuffers:\t\t%d\r\n",A3Dsoft.dwMax2DBuffers);
 AddToLog(buf);
 wsprintf(buf," dwMax3DBuffers:\t\t%d\r\n",A3Dsoft.dwMax3DBuffers);
 AddToLog(buf);
 AddToLog(end);

 return TRUE;
nosupp:;
 switch (queryversion)
 {
  case 3:
	   gpA3d->Release();
	   break;
  case 4:
	   gpA3d->Release();
	   break;
 }
nosupp2:;
 AddToLog(notsupported);
 AddToLog(end);
 AddToLog(end);
 return TRUE;
}

BOOL CALLBACK A3DENUMCALLBACK(LPGUID lpGuid,LPCWSTR lpcstrDescription,LPCWSTR lpcstrModule,LPVOID lpContext)
{
 return A3DEnumCallback(lpGuid,(char*)lpcstrDescription,(char*)lpcstrModule,lpContext);
}

void A3D5SupportedTest(HWND hWnd)
{
 logwnd = hWnd;

 ViewFileInfo("a3dapi.dll");

 CoInitialize(NULL);

 hResult = CoCreateInstance(CLSID_A3dApi, NULL, CLSCTX_INPROC_SERVER, IID_IA3d5, (void **)&gpA3d5);
 if(hResult != S_OK)
 {
  AddToLog("A3D5 (3.0) - ");
  AddToLog(notsupported);
  AddToLog(end);
  return;
 }

 hResult = gpA3d5->A3dEnumerate(A3DENUMCALLBACK,(void*)5);
 if(hResult != S_OK)
 {
  AddToLog("A3D5 (3.0) - Error in A3dEnumerate()\r\n");
 }

 try
 {
  gpA3d5->Release();
 }
 catch(...) {}
 gpA3d5 = NULL;

 CoUninitialize();
}

void A3D4SupportedTest(HWND hWnd)
{
 IA3d4 *gpA3d4 = NULL;
 logwnd = hWnd;

 ViewFileInfo("a3dapi.dll");
 
 CoInitialize(NULL);

 hResult = CoCreateInstance(CLSID_A3dApi, NULL, CLSCTX_INPROC_SERVER, IID_IA3d4, (void **)&gpA3d4);
 if(hResult != S_OK)
 {
  AddToLog("A3D4 (2.0) - ");
  AddToLog(notsupported);
  AddToLog(end);
  return;
 }
 try
 {
  gpA3d4->Release();
 }
 catch(...) {}
 gpA3d4 = NULL;
 
 DirectSoundEnumerate(A3DEnumCallback,(void*)4);

 CoUninitialize();
}

void A3D3SupportedTest(HWND hWnd)
{
 IA3d3 *gpA3d3 = NULL;
 logwnd = hWnd;

 ViewFileInfo("a3dapi.dll");

 CoInitialize(NULL);
 
 hResult = CoCreateInstance(CLSID_A3dApi, NULL, CLSCTX_INPROC_SERVER, IID_IA3d3, (void **)&gpA3d3);
 if(hResult != S_OK)
 {
  AddToLog("A3D3 - ");
  AddToLog(notsupported);
  AddToLog(end);
  return;
 }

 try
 {
  gpA3d3->Release();
 }
 catch(...) {}
 gpA3d3 = NULL;

 DirectSoundEnumerate(A3DEnumCallback,(void*)3);

 CoUninitialize();
}

BOOL CALLBACK A3D1EnumCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{
 HRESULT hResult;
 LPDIRECTSOUND dsgpA3d = 0;
 IA3d2 *gpA3dl;
 int queryversion = (int)lpContext;
 
 if (lstrlen((char*)lpcstrModule) == 0)
 {
  wsprintf(buf,"--- %s\r\n",(char*)lpcstrDescription);
  AddToLog(buf);
 }
 else
 {
  wsprintf(buf,"--- %s [%s]\r\n",(char*)lpcstrDescription,(char*)lpcstrModule);
  AddToLog(buf);
 }

 if (lpGuid == 0)
 {
  AddToLog("GUID: default\r\n");
 }
 else
 {
  wsprintf(buf,"GUID: 0x%X%X%X%X\r\n",lpGuid->Data1,lpGuid->Data2,lpGuid->Data3,lpGuid->Data4);
  AddToLog(buf);
 }

 switch (queryversion)
 {
  case 1:
       AddToLog("A3D1 (1.0) - ");
	   hResult = CoCreateInstance(CLSID_A3d, NULL, CLSCTX_INPROC_SERVER, IID_IDirectSound, (void **)&dsgpA3d);
	   if(hResult != S_OK) goto nosupp2;
	   hResult = dsgpA3d->QueryInterface(IID_IA3d,(void**)&gpA3dl);
	   if(hResult != S_OK) goto nosupp;
	   break;
  case 2:
	   AddToLog("A3D2 (1.2) - ");
	   hResult = CoCreateInstance(CLSID_A3d, NULL, CLSCTX_INPROC_SERVER, IID_IDirectSound, (void **)&dsgpA3d);
	   if(hResult != S_OK) goto nosupp2;
	   hResult = dsgpA3d->QueryInterface(IID_IA3d2,(void**)&gpA3dl);
	   if(hResult != S_OK) goto nosupp;
	   break;
 }

 hResult = dsgpA3d->Initialize(lpGuid);
 if(hResult != S_OK) goto nosupp;

 AddToLog(supported);
 AddToLog(end);

 if (queryversion == 2)
 {
  A3DCAPS_HARDWARE A3Dhard;
  memset(&A3Dhard,0,sizeof(A3DCAPS_HARDWARE));
  A3Dhard.dwSize = sizeof(A3DCAPS_HARDWARE);
  hResult = gpA3dl->GetHardwareCaps(&A3Dhard);
  if(hResult != S_OK)
  {
   wsprintf(buf,"Error in GetHardwareCaps()\r\n");
   AddToLog(buf);
  }
  else
  {
   AddToLog("Hardware caps:\r\n");
   wsprintf(buf," dwFlags: 0x%X\r\n",A3Dhard.dwFlags);
   AddToLog(buf);
  }

  A3DCAPS_SOFTWARE A3Dsoft;
  memset(&A3Dsoft,0,sizeof(A3DCAPS_SOFTWARE));
  A3Dsoft.dwSize = sizeof(A3DCAPS_SOFTWARE);
  hResult = gpA3dl->GetSoftwareCaps(&A3Dsoft);
  if(hResult != S_OK)
  {
   wsprintf(buf,"Error in GetSoftwareCaps() - ");
   AddToLog(buf);
  }
  else
  {
   wsprintf(buf,"Software caps:\r\n");
   AddToLog(buf);
   wsprintf(buf," dwFlags: 0x%X\r\n",A3Dsoft.dwFlags);
   AddToLog(buf);
   wsprintf(buf," dwVersion: %d.%d\r\n",(A3Dsoft.dwVersion/10),A3Dsoft.dwVersion - (A3Dsoft.dwVersion/10)*10);
   AddToLog(buf);
  }
 }

 dsgpA3d->Release();
 AddToLog(end);
 
 return TRUE;

nosupp:;
 dsgpA3d->Release();
nosupp2:;
 AddToLog(notsupported);
 AddToLog(end);
 AddToLog(end);
 
 return TRUE;
}

void A3D2SupportedTest(HWND hWnd)
{
 LPDIRECTSOUND dsgpA3d = 0;
 logwnd = hWnd;

 ViewFileInfo("a3d.dll");

 CoInitialize(NULL);
 hResult = CoCreateInstance(CLSID_A3d, NULL, CLSCTX_INPROC_SERVER, IID_IDirectSound, (void **)&dsgpA3d);
 if(hResult != S_OK)
 {
  hResult = CoCreateInstance(CLSID_A3d, NULL, CLSCTX_INPROC_SERVER, IID_IDirectSound, (void **)&dsgpA3d);
 } 

 if(hResult != S_OK)
 {
  AddToLog("A3D1 (1.2) - ");
  AddToLog(notsupported);
  AddToLog(end);
  return;
 }

 dsgpA3d->Release();

 DirectSoundEnumerate(A3D1EnumCallback,(void*)2);

 CoUninitialize();
}

void A3D1SupportedTest(HWND hWnd)
{
 LPDIRECTSOUND dsgpA3d = 0;
 logwnd = hWnd;
 
 ViewFileInfo("a3d.dll");

 CoInitialize(NULL);

 hResult = CoCreateInstance(CLSID_A3d, NULL, CLSCTX_INPROC_SERVER, IID_IDirectSound, (void **)&dsgpA3d);
 if(hResult != S_OK)
 {
  hResult = CoCreateInstance(CLSID_A3d, NULL, CLSCTX_INPROC_SERVER, IID_IDirectSound, (void **)&dsgpA3d);
 } 
 if(hResult != S_OK)
 {
  AddToLog("A3D1 (1.0) - ");
  AddToLog(notsupported);
  AddToLog(end);
  return;
 }

 dsgpA3d->Release();

 DirectSoundEnumerate(A3D1EnumCallback,(void*)1);
 
 CoUninitialize();
}

typedef void* (__cdecl *ALCOpenDevice)(unsigned char *);
ALCOpenDevice alcOpenDevice;
typedef void (__cdecl *ALCCloseDevice)(void *);
ALCCloseDevice alcCloseDevice;
typedef void* (__cdecl *ALCCreateContext)(void *,int *);
ALCCreateContext alcCreateContext;
typedef char (__cdecl *ALCMakeContextCurrent)(void *);
ALCMakeContextCurrent alcMakeContextCurrent;
typedef unsigned char* (__cdecl *ALCGetString)(void *,ALCenum);
ALCGetString alcGetString;
typedef ALCenum (__cdecl *ALCGetError)(void *device);
ALCGetError alcGetError;
typedef void (__cdecl *ALCDestroyContext)(void *);
ALCDestroyContext alcDestroyContext;
typedef unsigned char* (__cdecl *ALGetString)(ALenum);
ALGetString alGetString;
typedef void (__cdecl *ALCGetIntegerv)(void *,ALCenum,ALCsizei,ALCint*);
ALCGetIntegerv alcGetIntegerv;
typedef ALboolean (__cdecl *ALIsExtensionPresent)(char*);
ALIsExtensionPresent alIsExtensionPresent;
typedef ALenum (__cdecl *ALGetEnumValue)(char*);
ALGetEnumValue alGetEnumValue;
typedef ALint (__cdecl *ALGetInteger)(ALenum);
ALGetInteger alGetInteger;

void OpenALSupportedTest(HWND hWnd)
{
 logwnd = hWnd;
 HMODULE hLib;
 void *pDevice;
 void *pContext;
 ALenum err;
 int param1,param2;

 ViewFileInfo("openal32.dll");

 AddToLog("OpenAL - ");

 hLib = LoadLibrary("openal32.dll");
 if (hLib == NULL) goto ns;

 (FARPROC &)alcOpenDevice = GetProcAddress(hLib, "alcOpenDevice");
 if (alcOpenDevice == NULL) goto frl;
 (FARPROC &)alcCloseDevice = GetProcAddress(hLib, "alcCloseDevice");
 if (alcCloseDevice == NULL) goto frl;
 (FARPROC &)alcCreateContext = GetProcAddress(hLib, "alcCreateContext");
 if (alcCreateContext == NULL) goto frl;
 (FARPROC &)alcMakeContextCurrent = GetProcAddress(hLib, "alcMakeContextCurrent");
 if (alcMakeContextCurrent == NULL) goto frl;
 (FARPROC &)alcGetString = GetProcAddress(hLib, "alcGetString");
 if (alcGetString == NULL) goto frl;
 (FARPROC &)alcGetError = GetProcAddress(hLib, "alcGetError");
 if (alcGetError == NULL) goto frl;
 (FARPROC &)alcDestroyContext = GetProcAddress(hLib, "alcDestroyContext");
 if (alcDestroyContext == NULL) goto frl;
 (FARPROC &)alGetString = GetProcAddress(hLib, "alGetString");
 if (alGetString == NULL) goto frl;
 (FARPROC &)alcGetIntegerv = GetProcAddress(hLib, "alcGetIntegerv");
 if (alcGetIntegerv == NULL) goto frl;
 (FARPROC &)alIsExtensionPresent = GetProcAddress(hLib, "alIsExtensionPresent");
 if (alIsExtensionPresent == NULL) goto frl;
 (FARPROC &)alGetEnumValue = GetProcAddress(hLib, "alGetEnumValue");
 if (alGetEnumValue == NULL) goto frl;
 (FARPROC &)alGetInteger = GetProcAddress(hLib, "alGetInteger");
 if (alGetInteger == NULL) goto frl;

 pDevice = alcOpenDevice(NULL);
 if (!pDevice) goto frl;

 pContext = alcCreateContext(pDevice, NULL);
 err = alcGetError(pDevice);
 if (err != ALC_NO_ERROR)
 {
  wsprintf(buf,"OpenAL error: %s\r\n",alcGetString(pDevice, err));
  AddToLog(buf);
  goto frl;
 }
  
 alcMakeContextCurrent(pContext);
 err = alcGetError(pDevice);
 if (err != ALC_NO_ERROR)
 {
  wsprintf(buf,"OpenAL error: %s\r\n",alcGetString(pDevice, err));
  AddToLog(buf);
  goto frl;
 }

 AddToLog(supported);
 AddToLog(end);
 AddToLog(end);

 wsprintf(buf,"ALC_DEFAULT_DEVICE_SPECIFIER: %s\r\n",alcGetString(pDevice, ALC_DEFAULT_DEVICE_SPECIFIER));
 AddToLog(buf);
 wsprintf(buf,"ALC_DEVICE_SPECIFIER: %s\r\n",alcGetString(pDevice, ALC_DEVICE_SPECIFIER));
 AddToLog(buf);
 wsprintf(buf,"ALC_EXTENSIONS: %s\r\n",alcGetString(pDevice, ALC_EXTENSIONS));
 AddToLog(buf);

 alcGetIntegerv(pDevice,ALC_MAJOR_VERSION,4,&param1);
 alcGetIntegerv(pDevice,ALC_MINOR_VERSION,4,&param2);
 wsprintf(buf,"\r\nALC version: %d.%d\r\n\r\n",param1,param2);
 AddToLog(buf);

 wsprintf(buf,"AL_VERSION: %s\r\n",alGetString(AL_VERSION));
 AddToLog(buf);
 wsprintf(buf,"AL_RENDERER: %s\r\n",alGetString(AL_RENDERER));
 AddToLog(buf);
 wsprintf(buf,"AL_VENDOR: %s\r\n",alGetString(AL_VENDOR));
 AddToLog(buf);
 
 // преобразование расширений
 {
  int lenext = lstrlen((char*)alGetString(AL_EXTENSIONS));
  char *alext = (char*)alGetString(AL_EXTENSIONS); 
  char *ext = new char[lenext + 1];
  ZeroMemory(ext,lenext + 1);
  for (int i = 0; i<lenext;i++)
  {
   if (alext[i] >= ' ' && alext[i] <= '~') ext[i] = alext[i];
    else ext[i] = ' ';
  }
  wsprintf(buf,"AL_EXTENSIONS: %s\r\n",ext);
  AddToLog(buf);
  delete ext;
 }

 AddToLog(end);

 if (alIsExtensionPresent("EAX-RAM") == AL_TRUE)
 {
  ALenum g_eXRAMSize, g_eXRAMFree;

  g_eXRAMSize = alGetEnumValue("AL_EAX_RAM_SIZE");
  g_eXRAMFree = alGetEnumValue("AL_EAX_RAM_FREE");

  AddToLog("EAX-RAM extension:\r\n");
  wsprintf(buf,"  AL_EAX_RAM_SIZE: %d (%d mb)\r\n",alGetInteger(g_eXRAMSize), alGetInteger(g_eXRAMSize)/(1024*1024));
  AddToLog(buf);
  wsprintf(buf,"  AL_EAX_RAM_FREE: %d (%d mb)\r\n",alGetInteger(g_eXRAMFree), alGetInteger(g_eXRAMFree)/(1024*1024));
  AddToLog(buf);
 }

 alcMakeContextCurrent(NULL);
 alcDestroyContext(pContext);
 alcCloseDevice(pDevice);

 FreeLibrary(hLib);
 return;

frl:;
 FreeLibrary(hLib);
ns:;
 AddToLog(notsupported);
 AddToLog(end);
}

void DirectSoundTest(HWND hWnd)
{
 logwnd = hWnd;
 DWORD dxv;
 char v[] = "";
 char av[] = "a";
 char bv[] = "b";
 char cv[] = "c";
 char *lver = 0;

 GetDXVersion(&dxv,0,0);

 DWORD dxl,dxh,dxll;

 dxll = dxv & 0xff;
 dxl = (dxv & 0xff00) >> 8;
 dxh = (dxv & 0xff0000) >> 16;

 switch (dxll)
 {
  case 0:
	   lver = v;
	   break;
  case 1:
	   lver = av;
	   break;
  case 2:
	   lver = bv;
	   break;
  case 3:
	   lver = cv;
	   break;
 }

 wsprintf(buf,"DirectX version: %d.%d%s\r\n",dxh,dxl,lver);
 AddToLog(buf);

 DirectSoundEnumerate(DSEnumCallback8,0);
}

void WaveOutTest(HWND hWnd)
{
 WAVEOUTCAPS woc;
 int devcnt;

 logwnd = hWnd;
 devcnt = waveOutGetNumDevs();
 wsprintf(buf,"WaveOut devices: %d\r\n",devcnt);
 AddToLog(buf);

 for (int i=0;i<devcnt;i++)
 {
  waveOutGetDevCaps(i,&woc,sizeof(WAVEOUTCAPS));
  wsprintf(buf,"\r\n--- %s\r\n",(int)woc.szPname);
  AddToLog(buf);
  
  wsprintf(buf," manufacturer ID: 0x%X (%s)\r\n",(int)woc.wMid,GetManString(woc.wMid));
  AddToLog(buf);
  wsprintf(buf," product ID: 0x%X (%s)\r\n",(int)woc.wPid,GetProductString(woc.wMid,woc.wPid));
  AddToLog(buf);
  wsprintf(buf," version of the driver: %d.%d\r\n",HIBYTE(woc.vDriverVersion),LOBYTE(woc.vDriverVersion));
  AddToLog(buf);
  wsprintf(buf," channels: %d\r\n",(int)woc.wChannels);
  AddToLog(buf);
  AddToLog(" standart formats:\r\n");
  if (woc.dwFormats == WAVE_INVALIDFORMAT)
  {
   AddToLog("  no ");
   AddToLog(supported);
   AddToLog(end);
  }
  else
  {
   if ((woc.dwFormats & WAVE_FORMAT_1M08) != 0)
    AddToLog("  11.025 kHz, Mono, 8-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_1S08) != 0)
    AddToLog("  11.025 kHz, Stereo, 8-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_1M16) != 0)
    AddToLog("  11.025 kHz, Mono, 16-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_1S16) != 0)
    AddToLog("  11.025 kHz, Stereo, 16-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_2M08) != 0)
    AddToLog("  22.05 kHz, Mono, 8-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_2S08) != 0)
    AddToLog("  22.05 kHz, Stereo, 8-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_2M16) != 0)
    AddToLog("  22.05 kHz, Mono, 16-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_2S16) != 0)
    AddToLog("  22.05 kHz, Stereo, 16-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_4M08) != 0)
    AddToLog("  44.1 kHz, Mono, 8-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_4S08) != 0)
    AddToLog("  44.1 kHz, Stereo, 8-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_4M16) != 0)
    AddToLog("  44.1 kHz, Mono, 16-bit\r\n");
   if ((woc.dwFormats & WAVE_FORMAT_4S16) != 0)
    AddToLog("  44.1 kHz, Stereo, 16-bit\r\n");
  }
  
  AddToLog("Optional functionality supported by the device:\r\n");
  if ((woc.dwSupport & WAVECAPS_VOLUME) != 0)
   AddToLog(" - volume control\r\n");
  if ((woc.dwSupport & WAVECAPS_LRVOLUME) != 0)
   AddToLog(" - separate left and right volume control\r\n");
  if ((woc.dwSupport & WAVECAPS_PITCH) != 0)
   AddToLog(" - pitch control\r\n");
  if ((woc.dwSupport & WAVECAPS_PLAYBACKRATE) != 0)
   AddToLog(" - playback rate control\r\n");
  if ((woc.dwSupport & WAVECAPS_SYNC) != 0)
   AddToLog(" - the driver is synchronous and will block while playing a buffer\r\n");
  if ((woc.dwSupport & WAVECAPS_SAMPLEACCURATE) != 0)
   AddToLog(" - returns sample-accurate position information\r\n");
 }


 int N = mixerGetNumDevs ();
 wsprintf(buf,"\r\nMixers: %d\r\n",N);
 AddToLog(buf);
 for (i = 0; i < N; i++) 
 {
  MIXERCAPS Caps;

  mixerGetDevCaps (i, &Caps, sizeof (Caps));

  wsprintf(buf,"\r\n--- %s\r\n",Caps.szPname);
  AddToLog(buf);        
  wsprintf(buf,"  manufacturer ID: 0x%X (%s)\r\n",Caps.wMid,GetManString(Caps.wMid));
  AddToLog(buf);        
  wsprintf(buf,"  product ID: 0x%X (%s)\r\n",Caps.wPid,GetProductString(Caps.wMid,Caps.wPid));
  AddToLog(buf);        
  wsprintf(buf,"  version of the driver: %d.%d\r\n",HIBYTE(Caps.vDriverVersion),LOBYTE(Caps.vDriverVersion));
  AddToLog(buf);        
  wsprintf(buf,"  fdwSupport: 0x%X\r\n",Caps.fdwSupport);
  AddToLog(buf);        
  wsprintf(buf,"  number of audio line: %d\r\n",Caps.cDestinations);
  AddToLog(buf);        
 }


 N = auxGetNumDevs ();
 wsprintf(buf,"\r\nAux devices: %d\r\n",N);
 AddToLog(buf);
 for (i = 0; i < N; i++) 
 {
  AUXCAPS Caps;

  auxGetDevCaps (i, &Caps, sizeof (Caps));

  wsprintf(buf,"\r\n--- %s\r\n",Caps.szPname);
  AddToLog(buf);
  wsprintf(buf,"  manufacturer ID: 0x%X (%s)\r\n",Caps.wMid,GetManString(Caps.wMid));
  AddToLog(buf);
  wsprintf(buf,"  product ID: 0x%X (%s)\r\n",Caps.wPid,GetProductString(Caps.wMid,Caps.wPid));
  AddToLog(buf);
  wsprintf(buf,"  version of the driver: %d.%d\r\n",HIBYTE(Caps.vDriverVersion),LOBYTE(Caps.vDriverVersion));
  AddToLog(buf);

  AddToLog("  Type of the auxiliary audio output:\r\n");
  if ((Caps.wTechnology&AUXCAPS_AUXIN) != 0)
   AddToLog("   - Audio output from auxiliary input jacks.\r\n");
  if ((Caps.wTechnology&AUXCAPS_CDAUDIO) != 0)
   AddToLog("   - Audio output from an internal CD-ROM drive.\r\n");

  //wsprintf(buf,"  wReserved1: %d\r\n",Caps.wReserved1);
  //AddToLog(buf);
  
  AddToLog("  Optional functionality supported by the auxiliary audio device:\r\n");
  if ((Caps.dwSupport&AUXCAPS_LRVOLUME) != 0)
   AddToLog("   - Supports separate left and right volume control.\r\n");
  if ((Caps.dwSupport&AUXCAPS_VOLUME) != 0)
   AddToLog("   - Supports volume control.\r\n");
 }
}

void MIDITest(HWND hWnd)
{
 MIDIOUTCAPS woc;
 int devcnt;

 logwnd = hWnd;
 devcnt = midiOutGetNumDevs();
 wsprintf(buf,"MidiOut devices: %d\r\n",devcnt);
 AddToLog(buf);

 for (int i=0;i<devcnt;i++)
 {
  midiOutGetDevCaps(i,&woc,sizeof(MIDIOUTCAPS));
  wsprintf(buf,"\r\n--- %s\r\n",(int)woc.szPname);
  AddToLog(buf);
  
  wsprintf(buf,"manufacturer ID: 0x%X (%s)\r\n",(int)woc.wMid,GetManString(woc.wMid));
  AddToLog(buf);
  wsprintf(buf,"product ID: 0x%X (%s)\r\n",(int)woc.wPid,GetProductString(woc.wMid,woc.wPid));
  AddToLog(buf);
  wsprintf(buf,"version of the driver: %d.%d\r\n",HIBYTE(woc.vDriverVersion),LOBYTE(woc.vDriverVersion));
  AddToLog(buf);
  AddToLog("technology:\r\n");
  if ((woc.wTechnology & MOD_FMSYNTH) != 0)
   AddToLog(" the device is an FM synthesizer\r\n");
  if ((woc.wTechnology & MOD_MAPPER) != 0)
   AddToLog(" the device is the Microsoft MIDI mapper\r\n");
  if ((woc.wTechnology & MOD_MIDIPORT) != 0)
   AddToLog(" the device is a MIDI hardware port\r\n");
  if ((woc.wTechnology & MOD_SQSYNTH) != 0)
   AddToLog(" the device is a square wave synthesizer\r\n");
  if ((woc.wTechnology & MOD_SYNTH) != 0)
   AddToLog(" the device is a synthesizer\r\n");
  if ((woc.wTechnology & MOD_WAVETABLE) != 0)
   AddToLog(" the device is a hardware wavetable synthesizer\r\n");
  if ((woc.wTechnology & MOD_SWSYNTH) != 0)
   AddToLog(" the device is a software synthesizer\r\n");
  wsprintf(buf,"voices: %d\r\n",woc.wVoices);
  AddToLog(buf);
  wsprintf(buf,"notes: %d\r\n",woc.wNotes);
  AddToLog(buf);
  wsprintf(buf,"channel mask: 0x%X\r\n",woc.wChannelMask);
  AddToLog(buf);
  AddToLog("optional functionality supported by the device:\r\n");
  if ((woc.dwSupport & MIDICAPS_VOLUME) != 0)
   AddToLog(" - volume control\r\n");
  if ((woc.dwSupport & MIDICAPS_LRVOLUME) != 0)
   AddToLog(" - separate left and right volume control\r\n");
  if ((woc.dwSupport & MIDICAPS_CACHE) != 0)
   AddToLog(" - patch caching\r\n");
  if ((woc.dwSupport & MIDICAPS_STREAM) != 0)
   AddToLog(" - direct support midi stream\r\n");
 }
}

void ViewQuerySupport(LPKSPROPERTYSET prop,THIS_ REFGUID guid,int flag,char* name)
{
 HRESULT hr;
 ULONG support = 0;
 int k = 0,l = 0;
 hr = prop->QuerySupport(guid,flag,&support);
 if (FAILED(hr))
 {
  wsprintf(buf," %s - %s\r\n",name,notsupported);
  AddToLog(buf);
  return;
 }

 wsprintf(buf," %s - ",name);
 AddToLog(buf);

 if (support & KSPROPERTY_SUPPORT_GET == KSPROPERTY_SUPPORT_GET) 
 {
  k = 1;
 }
 if (support & KSPROPERTY_SUPPORT_SET == KSPROPERTY_SUPPORT_SET) 
 {
  l = 1;
 }
 if (l == 0 && k == 0) 
  AddToLog(notsupported);
 else
 {
  AddToLog(supported);
  AddToLog(" (");
  if (k == 1 && l == 1) AddToLog("get, set)");
  else
  {
   if (k == 1) AddToLog("get");
   if (l == 1) AddToLog("set");
   AddToLog(")");
  }
 }
 AddToLog(end);
 return;
}


bool BoolQuerySupport(LPKSPROPERTYSET prop,THIS_ REFGUID guid,int flag,char* name)
{
 HRESULT hr;
 ULONG support = 0;
 int k = 0,l = 0;
 hr = prop->QuerySupport(guid,flag,&support);
 if (FAILED(hr)) return false;
 
 if (support & KSPROPERTY_SUPPORT_GET == KSPROPERTY_SUPPORT_GET) 
 {
  k = 1;
 }
 if (support & KSPROPERTY_SUPPORT_SET == KSPROPERTY_SUPPORT_SET) 
 {
  l = 1;
 }
 if (l == 0 && k == 0) return false;
 return true;
}

void EAXUnifiedSupportedTest(int testversion,HWND hWnd,LPGUID lpGuid)
{
 LPDIRECTSOUND ds = 0;
 LPDIRECTSOUNDBUFFER prbuf = 0,secbuf = 0;
 HRESULT hr = 0;
 DWORD dwScratch = 0;
 int lenvinfo;
 char *verbuf;
 VS_FIXEDFILEINFO *vsfi;
 UINT uSize;
 int ver;
 DSBUFFERDESC desc;
 LPDIRECTSOUND3DLISTENER list = 0;
 LPDIRECTSOUND3DBUFFER sec3dbuf = 0;;
 LPKSPROPERTYSET propset = 0;
 ULONG support = 0;
 WAVEFORMATEX wf;

 hr = CoCreateInstance(CLSID_EAXDirectSound, NULL, CLSCTX_INPROC_SERVER, IID_IDirectSound, (void**)&ds);
 if (FAILED(hr)) return;

 hr = ds->Initialize(lpGuid);
 if (FAILED(hr)) 
 {
  if (!ds) ds->Release();
  return;
 }
 lenvinfo = GetFileVersionInfoSize("eax.dll",&dwScratch);
 verbuf = (char*)malloc(lenvinfo);
 if(GetFileVersionInfo("eax.dll",dwScratch,lenvinfo,verbuf)!=0)
 {
  VerQueryValue(verbuf,"\\\0",(void**)(&vsfi),&uSize);
  ver = HIWORD(vsfi->dwProductVersionMS);
  if (ver < testversion)
  {
   ds->Release();
   return;
  }
 }  

 hr = ds->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);
 if (FAILED(hr)) goto ncs;
  
 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
 hr = ds->CreateSoundBuffer(&desc, &prbuf, NULL);
 if (FAILED(hr)) goto ncs;

 hr = prbuf->QueryInterface(IID_IDirectSound3DListener,(void**)&list);
 if (FAILED(hr)) goto nbs;

 ZeroMemory( &wf, sizeof(WAVEFORMATEX));
 wf.wFormatTag = WAVE_FORMAT_PCM;
 wf.nChannels = 1;
 wf.nSamplesPerSec = 11025;
 wf.nAvgBytesPerSec = 22050;
 wf.nBlockAlign = 2;
 wf.wBitsPerSample = 16;
 wf.cbSize = 0;

 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_CTRL3D;
 desc.dwBufferBytes = 1024;
 desc.lpwfxFormat = &wf;
 hr = ds->CreateSoundBuffer(&desc, &secbuf, NULL);
 if (FAILED(hr)) goto nls;

 hr = secbuf->QueryInterface(IID_IDirectSound3DBuffer,(void **)&sec3dbuf);
 if (FAILED(hr)) goto nss;
 
 hr = sec3dbuf->QueryInterface(IID_IKsPropertySet, (void**)&propset);
 if (FAILED(hr)) goto ns3s;

 wsprintf(buf,"EAX Unified - found (v %d.0) - ",ver);
 AddToLog(buf);

 switch (testversion)
 {
  case 2:
	   if (BoolTestEAX2Prop(propset) == false)
	   {
        wsprintf(buf,"property for %d.0 version %s\r\n\r\n",testversion,notsupported);
        AddToLog(buf);
		break;
	   }
	   AddToLog(supported);
	   AddToLog(end);
       wsprintf(buf,"test property for %d.0 version\r\n\r\n",testversion);
       AddToLog(buf);
	   TestEAX2Prop(propset);
       break;
  case 3:
	   if (BoolTestEAX3Prop(propset) == false)
	   {
        wsprintf(buf,"property for %d.0 version %s\r\n\r\n",testversion,notsupported);
        AddToLog(buf);
		break;
	   }
	   AddToLog(supported);
	   AddToLog(end);
       wsprintf(buf,"test property for %d.0 version\r\n\r\n",testversion);
       AddToLog(buf);
	   TestEAX3Prop(propset);
       break;
  case 4:
	   if (BoolTestEAX4Prop(propset) == false)
	   {
        wsprintf(buf,"property for %d.0 version %s\r\n\r\n",testversion,notsupported);
        AddToLog(buf);
		break;
	   }
	   AddToLog(supported);
	   AddToLog(end);
       wsprintf(buf,"test property for %d.0 version\r\n\r\n",testversion);
       AddToLog(buf);
	   TestEAX4Prop(propset);
       break;
  case 5:
	   if (BoolTestEAX5Prop(propset) == false)
	   {
        wsprintf(buf,"property for %d.0 version %s\r\n\r\n",testversion,notsupported);
        AddToLog(buf);
		break;
	   }
	   AddToLog(supported);
	   AddToLog(end);
       wsprintf(buf,"test property for %d.0 version\r\n\r\n",testversion);
       AddToLog(buf);
	   TestEAX5Prop(propset);
       break;
 }

 if (!propset) propset->Release(); 
ns3s:
 if (!sec3dbuf) sec3dbuf->Release(); 
nss:;
 if (!secbuf) secbuf->Release();
nls:;
 if (!list) list->Release();
nbs:;
 if (!prbuf) prbuf->Release();
ncs:;
 if (!ds) ds->Release();
 CoUninitialize();
}

void SaveLog(HWND hWnd)
{
 int hFile;
 OPENFILENAME ofn;
 static char szFilter[] = "log files (*.log)\0*.log\0\0";
 static char szFileName[_MAX_PATH];
 char szTitleName[_MAX_FNAME + _MAX_EXT];
 char *tempbuf = 0;
 int templen;

 memset(&ofn,0,sizeof(OPENFILENAME));

 ofn.lStructSize       = sizeof (OPENFILENAME);
 ofn.hwndOwner         = hWnd;
 ofn.lpstrFilter       = szFilter;
 ofn.lpstrFile         = szFileName;
 ofn.nMaxFile          = _MAX_PATH;
 ofn.lpstrFileTitle    = szTitleName;
 ofn.nMaxFileTitle     = _MAX_FNAME + _MAX_EXT;
 ofn.Flags             = OFN_HIDEREADONLY | OFN_EXTENSIONDIFFERENT | OFN_OVERWRITEPROMPT;
 ofn.lpstrDefExt       = "*.log";
 ofn.lpstrTitle        = "Save Log";
 if(!GetSaveFileName(&ofn)) return;

 hFile = _lcreat(szFileName, 0);
 if (hFile == -1) return;
 _llseek(hFile, 0, 2);

 _lwrite(hFile,sep,lstrlen(sep));
 _lwrite(hFile,label1,lstrlen(label1));
 _lwrite(hFile,label2,lstrlen(label2));
 _lwrite(hFile,sep,lstrlen(sep));
 for (int i = 0;i < 18;i++)
 {
  templen = SendDlgItemMessage(hpw[i],IDC_LOG,WM_GETTEXTLENGTH,0,0);
  tempbuf = (char*)malloc(templen+10);
  memset(tempbuf,0,templen);
  SendDlgItemMessage(hpw[i],IDC_LOG,WM_GETTEXT,(WPARAM)templen,(LPARAM)tempbuf);
  tempbuf[templen-1] = 0x0a;
  _lwrite(hFile,tempbuf,templen);
  _lwrite(hFile,sep,lstrlen(sep));
  free(tempbuf);
 }

// _lwrite(hFile,(char*)biosparam.font8x8,256*8);
 _lclose(hFile);
}


void EAX1SupportedTest(HWND hWnd)
{
 DirectSoundEnumerate(EAX1SupportedTestCallback,(LPVOID)hWnd);
}

BOOL CALLBACK EAX1SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{
 HWND hWnd = (HWND)lpContext;
 logwnd = hWnd;
 LPDIRECTSOUND ds = 0;
 LPDIRECTSOUNDBUFFER prbuf = 0,secbuf = 0;
 HRESULT hr = 0;
 DSBUFFERDESC desc;
 LPDIRECTSOUND3DLISTENER list = 0;
 LPDIRECTSOUND3DBUFFER sec3dbuf = 0;
 LPKSPROPERTYSET propset = 0;
 ULONG support = 0;
 WAVEFORMATEX wf;
 bool testpass = false;

 if (lstrlen(lpcstrModule) == 0)
 {
  wsprintf(buf,"--- %s\r\n",lpcstrDescription);
  AddToLog(buf); 
 }
 else
 {
  wsprintf(buf,"--- %s [%s]\r\n",lpcstrDescription, lpcstrModule);
  AddToLog(buf); 
 }
 
 AddToLog("EAX 1 - ");

 CoInitialize(NULL);
 // для отвязки от DirectSoundCreate - делаем инициализацию через стандартный COM
 hr = CoCreateInstance(CLSID_DirectSound,
          NULL, 
          CLSCTX_INPROC_SERVER,
          IID_IDirectSound,
          (LPVOID*) &ds);
 if (FAILED(hr)) goto ns;

 hr = ds->Initialize(lpGuid);
 if (FAILED(hr)) goto ncs;

 hr = ds->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);
 if (FAILED(hr)) goto ncs;
  
 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
 hr = ds->CreateSoundBuffer(&desc, &prbuf, NULL);
 if (FAILED(hr)) goto ncs;

 hr = prbuf->QueryInterface(IID_IDirectSound3DListener,(void**)&list);
 if (FAILED(hr)) goto nbs;

 ZeroMemory( &wf, sizeof(WAVEFORMATEX));
 wf.wFormatTag = WAVE_FORMAT_PCM;
 wf.nChannels = 1;
 wf.nSamplesPerSec = 11025;
 wf.nAvgBytesPerSec = 22050;
 wf.nBlockAlign = 2;
 wf.wBitsPerSample = 16;
 wf.cbSize = 0;

 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_CTRL3D;
 desc.dwBufferBytes = 1024;
 desc.lpwfxFormat = &wf;
 hr = ds->CreateSoundBuffer(&desc, &secbuf, NULL);
 if (FAILED(hr)) goto nls;

 hr = secbuf->QueryInterface(IID_IDirectSound3DBuffer,(void **)&sec3dbuf);
 if (FAILED(hr)) goto nss;
 
 hr = sec3dbuf->QueryInterface(IID_IKsPropertySet, (void**)&propset);
 if (FAILED(hr)) goto ns3s;

 hr = propset->QuerySupport(DSPROPSETID_EAX_ReverbProperties,DSPROPERTY_EAX_ALL,&support);
 if (FAILED(hr)) goto nps;
 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(DSPROPSETID_EAXBUFFER_ReverbProperties,DSPROPERTY_EAXBUFFER_ALL,&support);
 if (FAILED(hr)) goto nps;
 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 AddToLog(supported);
 AddToLog(end);
 AddToLog(end);

 wsprintf(buf,"Listener properties:\r\n");
 AddToLog(buf);

 ViewQuerySupport(propset,DSPROPSETID_EAX_ReverbProperties,DSPROPERTY_EAX_ALL,"DSPROPERTY_EAX_ALL");
 ViewQuerySupport(propset,DSPROPSETID_EAX_ReverbProperties,DSPROPERTY_EAX_ENVIRONMENT,"DSPROPERTY_EAX_ENVIRONMENT");
 ViewQuerySupport(propset,DSPROPSETID_EAX_ReverbProperties,DSPROPERTY_EAX_VOLUME,"DSPROPERTY_EAX_VOLUME");
 ViewQuerySupport(propset,DSPROPSETID_EAX_ReverbProperties,DSPROPERTY_EAX_DECAYTIME,"DSPROPERTY_EAX_DECAYTIME");
 ViewQuerySupport(propset,DSPROPSETID_EAX_ReverbProperties,DSPROPERTY_EAX_DAMPING,"DSPROPERTY_EAX_DAMPING");

 wsprintf(buf,"Buffer properties:\r\n");
 AddToLog(buf);

 ViewQuerySupport(propset,DSPROPSETID_EAXBUFFER_ReverbProperties,DSPROPERTY_EAXBUFFER_ALL,"DSPROPERTY_EAXBUFFER_ALL");
 ViewQuerySupport(propset,DSPROPSETID_EAXBUFFER_ReverbProperties,DSPROPERTY_EAXBUFFER_REVERBMIX,"DSPROPERTY_EAXBUFFER_REVERBMIX");

 AddToLog(end);

 testpass = true;

nps:;
 if (!propset) propset->Release(); 
ns3s:
 if (!sec3dbuf) sec3dbuf->Release(); 
nss:;
 if (!secbuf) secbuf->Release();
nls:;
 if (!list) list->Release();
nbs:;
 if (!prbuf) prbuf->Release();
ncs:;
 if (!ds) ds->Release();
ns:;
 
 if (testpass == false)
 {
  AddToLog(notsupported);
  AddToLog(end);
  AddToLog(end);
 }

 CoUninitialize();
 return TRUE;
}

void EAX2SupportedTest(HWND hWnd)
{
 logwnd = hWnd;
 ViewFileInfo("eax.dll");
 DirectSoundEnumerate(EAX2SupportedTestCallback,(LPVOID)hWnd);
}

BOOL CALLBACK EAX2SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{
 HWND hWnd = (HWND)lpContext;
 logwnd = hWnd;
 LPDIRECTSOUND ds = 0;
 LPDIRECTSOUNDBUFFER prbuf = 0,secbuf = 0;
 HRESULT hr = 0;
 DSBUFFERDESC desc;
 LPDIRECTSOUND3DLISTENER list = 0;
 LPDIRECTSOUND3DBUFFER sec3dbuf = 0;;
 LPKSPROPERTYSET propset = 0;
 ULONG support = 0;
 WAVEFORMATEX wf;
 bool testpass = false;

 if (lstrlen(lpcstrModule) == 0)
 {
  wsprintf(buf,"--- %s\r\n",lpcstrDescription);
  AddToLog(buf); 
 }
 else
 {
  wsprintf(buf,"--- %s [%s]\r\n",lpcstrDescription, lpcstrModule);
  AddToLog(buf); 
 }

 AddToLog("EAX 2 - ");

 CoInitialize(NULL);
 // для отвязки от DirectSoundCreate - делаем инициализацию через стандартный COM
 hr = CoCreateInstance(CLSID_DirectSound,
          NULL, 
          CLSCTX_INPROC_SERVER,
          IID_IDirectSound,
          (LPVOID*) &ds);
 if (FAILED(hr)) goto ns;

 hr = ds->Initialize(lpGuid);
 if (FAILED(hr)) goto ncs;
 
 hr = ds->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);
 if (FAILED(hr)) goto ncs;
  
 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
 hr = ds->CreateSoundBuffer(&desc, &prbuf, NULL);
 if (FAILED(hr)) goto ncs;

 hr = prbuf->QueryInterface(IID_IDirectSound3DListener,(void**)&list);
 if (FAILED(hr)) goto nbs;

 ZeroMemory( &wf, sizeof(WAVEFORMATEX));
 wf.wFormatTag = WAVE_FORMAT_PCM;
 wf.nChannels = 1;
 wf.nSamplesPerSec = 11025;
 wf.nAvgBytesPerSec = 22050;
 wf.nBlockAlign = 2;
 wf.wBitsPerSample = 16;
 wf.cbSize = 0;

 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_CTRL3D;
 desc.dwBufferBytes = 1024;
 desc.lpwfxFormat = &wf;
 hr = ds->CreateSoundBuffer(&desc, &secbuf, NULL);
 if (FAILED(hr)) goto nls;

 hr = secbuf->QueryInterface(IID_IDirectSound3DBuffer,(void **)&sec3dbuf);
 if (FAILED(hr)) goto nss;
 
 hr = sec3dbuf->QueryInterface(IID_IKsPropertySet, (void**)&propset);
 if (FAILED(hr)) goto ns3s;

 hr = propset->QuerySupport(DSPROPSETID_EAX20_ListenerProperties,DSPROPERTY_EAX2LISTENER_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;
 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(DSPROPSETID_EAX20_BufferProperties,DSPROPERTY_EAX2BUFFER_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;
 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 
 AddToLog(supported);
 AddToLog(end);
 AddToLog(end);

 testpass = true;

 TestEAX2Prop(propset);

nps:;
 if (!propset) propset->Release(); 
ns3s:
 if (!sec3dbuf) sec3dbuf->Release(); 
nss:;
 if (!secbuf) secbuf->Release();
nls:;
 if (!list) list->Release();
nbs:;
 if (!prbuf) prbuf->Release();
ncs:;
 if (!ds) ds->Release();
ns:;

 if (testpass == false)
 {
  AddToLog(notsupported);
  AddToLog(end);

  EAXUnifiedSupportedTest(2,hWnd,lpGuid);
 }
 
 AddToLog(end);
 CoUninitialize();
 return TRUE;
}

void EAX3SupportedTest(HWND hWnd)
{
 logwnd = hWnd;
 ViewFileInfo("eax.dll");

 DirectSoundEnumerate(EAX3SupportedTestCallback,(LPVOID)hWnd);
}

BOOL CALLBACK EAX3SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{
 HWND hWnd = (HWND)lpContext;
 logwnd = hWnd;
 LPDIRECTSOUND ds = 0;
 LPDIRECTSOUNDBUFFER prbuf = 0,secbuf = 0;
 HRESULT hr = 0;
 DSBUFFERDESC desc;
 LPDIRECTSOUND3DLISTENER list = 0;
 LPDIRECTSOUND3DBUFFER sec3dbuf = 0;;
 LPKSPROPERTYSET propset = 0;
 ULONG support = 0;
 WAVEFORMATEX wf;
 bool testpass = false;

 if (lstrlen(lpcstrModule) == 0)
 {
  wsprintf(buf,"--- %s\r\n",lpcstrDescription);
  AddToLog(buf); 
 }
 else
 {
  wsprintf(buf,"--- %s [%s]\r\n",lpcstrDescription, lpcstrModule);
  AddToLog(buf); 
 }

 AddToLog("EAX 3 - ");

 CoInitialize(NULL);
 // для отвязки от DirectSoundCreate - делаем инициализацию через стандартный COM
 hr = CoCreateInstance(CLSID_DirectSound,
          NULL, 
          CLSCTX_INPROC_SERVER,
          IID_IDirectSound,
          (LPVOID*) &ds);
 if (FAILED(hr)) goto ns;

 hr = ds->Initialize(lpGuid);
 if (FAILED(hr)) goto ncs;
 
 hr = ds->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);
 if (FAILED(hr)) goto ncs;
  
 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
 hr = ds->CreateSoundBuffer(&desc, &prbuf, NULL);
 if (FAILED(hr)) goto ncs;

 hr = prbuf->QueryInterface(IID_IDirectSound3DListener,(void**)&list);
 if (FAILED(hr)) goto nbs;

 ZeroMemory( &wf, sizeof(WAVEFORMATEX));
 wf.wFormatTag = WAVE_FORMAT_PCM;
 wf.nChannels = 1;
 wf.nSamplesPerSec = 11025;
 wf.nAvgBytesPerSec = 22050;
 wf.nBlockAlign = 2;
 wf.wBitsPerSample = 16;
 wf.cbSize = 0;

 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_CTRL3D;
 desc.dwBufferBytes = 1024;
 desc.lpwfxFormat = &wf;
 hr = ds->CreateSoundBuffer(&desc, &secbuf, NULL);
 if (FAILED(hr)) goto nls;

 hr = secbuf->QueryInterface(IID_IDirectSound3DBuffer,(void **)&sec3dbuf);
 if (FAILED(hr)) goto nss;
 
 hr = sec3dbuf->QueryInterface(IID_IKsPropertySet, (void**)&propset);
 if (FAILED(hr)) goto ns3s;

 hr = propset->QuerySupport(DSPROPSETID_EAX30_ListenerProperties,DSPROPERTY_EAX3LISTENER_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;
 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(DSPROPSETID_EAX30_BufferProperties,DSPROPERTY_EAX3BUFFER_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;
 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;
 
 AddToLog(supported);
 AddToLog(end);
 AddToLog(end);

 testpass = true;

 TestEAX3Prop(propset);

nps:;
 if (!propset) propset->Release();
ns3s:;
 if (!sec3dbuf) sec3dbuf->Release(); 
nss:;
 if (!secbuf) secbuf->Release();
nls:;
 if (!list) list->Release();
nbs:;
 if (!prbuf) prbuf->Release();
ncs:;
 if (!ds) ds->Release();
ns:;

 if (testpass == false)
 {
  AddToLog(notsupported);
  AddToLog(end);

  EAXUnifiedSupportedTest(3,hWnd,lpGuid);
 }
 
 AddToLog(end);
 CoUninitialize();
 return TRUE;
}

void EAX4SupportedTest(HWND hWnd)
{
 logwnd = hWnd;
 ViewFileInfo("eax.dll");

 DirectSoundEnumerate(EAX4SupportedTestCallback,(LPVOID)hWnd);
}

BOOL CALLBACK EAX4SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{
 HWND hWnd = (HWND)lpContext;
 logwnd = hWnd;
 LPDIRECTSOUND ds = 0;
 LPDIRECTSOUNDBUFFER prbuf = 0,secbuf = 0;
 HRESULT hr = 0;
 DSBUFFERDESC desc;
 LPDIRECTSOUND3DLISTENER list = 0;
 LPDIRECTSOUND3DBUFFER sec3dbuf = 0;;
 LPKSPROPERTYSET propset = 0;
 ULONG support = 0;
 WAVEFORMATEX wf;
 bool testpass = false;

 if (lstrlen(lpcstrModule) == 0)
 {
  wsprintf(buf,"--- %s\r\n",lpcstrDescription);
  AddToLog(buf); 
 }
 else
 {
  wsprintf(buf,"--- %s [%s]\r\n",lpcstrDescription, lpcstrModule);
  AddToLog(buf); 
 }
 
 AddToLog("EAX 4 - ");

 CoInitialize(NULL);
 // для отвязки от DirectSoundCreate - делаем инициализацию через стандартный COM
 hr = CoCreateInstance(CLSID_DirectSound,
          NULL, 
          CLSCTX_INPROC_SERVER,
          IID_IDirectSound,
          (LPVOID*) &ds);
 if (FAILED(hr)) goto ns;

 hr = ds->Initialize(lpGuid);
 if (FAILED(hr)) goto ncs;
 
 hr = ds->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);
 if (FAILED(hr)) goto ncs;
  
 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
 hr = ds->CreateSoundBuffer(&desc, &prbuf, NULL);
 if (FAILED(hr)) goto ncs;

 hr = prbuf->QueryInterface(IID_IDirectSound3DListener,(void**)&list);
 if (FAILED(hr)) goto nbs;

 ZeroMemory( &wf, sizeof(WAVEFORMATEX));
 wf.wFormatTag = WAVE_FORMAT_PCM;
 wf.nChannels = 1;
 wf.nSamplesPerSec = 11025;
 wf.nAvgBytesPerSec = 22050;
 wf.nBlockAlign = 2;
 wf.wBitsPerSample = 16;
 wf.cbSize = 0;

 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_CTRL3D;
 desc.dwBufferBytes = 1024;
 desc.lpwfxFormat = &wf;
 hr = ds->CreateSoundBuffer(&desc, &secbuf, NULL);
 if (FAILED(hr)) goto nls;

 hr = secbuf->QueryInterface(IID_IDirectSound3DBuffer,(void **)&sec3dbuf);
 if (FAILED(hr)) goto nss;
 
 hr = sec3dbuf->QueryInterface(IID_IKsPropertySet, (void**)&propset);
 if (FAILED(hr)) goto ns3s;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX40_Context,EAX4CONTEXT_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX40_FXSlot0,EAX4FXSLOT_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX40_FXSlot1,EAX4FXSLOT_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX40_FXSlot2,EAX4FXSLOT_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX40_FXSlot3,EAX4FXSLOT_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX40_Source,EAX4SOURCE_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 AddToLog(supported);
 AddToLog(end);
 AddToLog(end);

 testpass = true;

 TestEAX4Prop(propset);

nps:;
 if (!propset) propset->Release(); 
ns3s:
 if (!sec3dbuf) sec3dbuf->Release(); 
nss:;
 if (!secbuf) secbuf->Release();
nls:;
 if (!list) list->Release();
nbs:;
 if (!prbuf) prbuf->Release();
ncs:;
 if (!ds) ds->Release();
ns:;

 if (testpass == false)
 {
  AddToLog(notsupported);
  AddToLog(end);

  EAXUnifiedSupportedTest(4,hWnd,lpGuid);
 }

 AddToLog(end);
 CoUninitialize();
 
 return TRUE;
}

void SensauraSupportedTest(HWND hWnd)
{
 DirectSoundEnumerate(SensauraSupportedTestCallback,(LPVOID)hWnd);
}

BOOL CALLBACK SensauraSupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{
 HWND hWnd = (HWND)lpContext;
 logwnd = hWnd;
 LPDIRECTSOUND ds = 0;
 LPDIRECTSOUNDBUFFER prbuf = 0,secbuf = 0;
 HRESULT hr = 0;
 DSBUFFERDESC desc;
 LPDIRECTSOUND3DLISTENER list = 0;
 LPDIRECTSOUND3DBUFFER sec3dbuf = 0;;
 LPKSPROPERTYSET propset = 0;
 ULONG support = 0;
 WAVEFORMATEX wf;
 bool testpass = false;

 if (lstrlen(lpcstrModule) == 0)
 {
  wsprintf(buf,"--- %s\r\n",lpcstrDescription);
  AddToLog(buf); 
 }
 else
 {
  wsprintf(buf,"--- %s [%s]\r\n",lpcstrDescription, lpcstrModule);
  AddToLog(buf); 
 }

 AddToLog("Sensaura ZoomFX - ");
 
 CoInitialize(NULL);
 // для отвязки от DirectSoundCreate - делаем инициализацию через стандартный COM
 hr = CoCreateInstance(CLSID_DirectSound,
          NULL, 
          CLSCTX_INPROC_SERVER,
          IID_IDirectSound,
          (LPVOID*) &ds);
 if (FAILED(hr)) goto ns;

 hr = ds->Initialize(lpGuid);
 if (FAILED(hr)) goto ncs;
 
 hr = ds->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);
 if (FAILED(hr)) goto ncs;
  
 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
 hr = ds->CreateSoundBuffer(&desc, &prbuf, NULL);
 if (FAILED(hr)) goto ncs;

 hr = prbuf->QueryInterface(IID_IDirectSound3DListener,(void**)&list);
 if (FAILED(hr)) goto nbs;

 ZeroMemory( &wf, sizeof(WAVEFORMATEX));
 wf.wFormatTag = WAVE_FORMAT_PCM;
 wf.nChannels = 1;
 wf.nSamplesPerSec = 11025;
 wf.nAvgBytesPerSec = 22050;
 wf.nBlockAlign = 2;
 wf.wBitsPerSample = 16;
 wf.cbSize = 0;

 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_CTRL3D;
 desc.dwBufferBytes = 1024;
 desc.lpwfxFormat = &wf;
 hr = ds->CreateSoundBuffer(&desc, &secbuf, NULL);
 if (FAILED(hr)) goto nls;

 hr = secbuf->QueryInterface(IID_IDirectSound3DBuffer,(void **)&sec3dbuf);
 if (FAILED(hr)) goto nss;
 
 hr = sec3dbuf->QueryInterface(IID_IKsPropertySet, (void**)&propset);
 if (FAILED(hr)) goto ns3s;

 hr = propset->QuerySupport(DSPROPSETID_ZOOMFX_BufferProperties,DSPROPERTY_ZOOMFXBUFFER_ALL,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 AddToLog(supported);
 AddToLog(end);
 AddToLog(end);
 
 wsprintf(buf,"properties:\r\n");
 AddToLog(buf);
 ViewQuerySupport(propset,DSPROPSETID_ZOOMFX_BufferProperties,DSPROPERTY_ZOOMFXBUFFER_ALL,"DSPROPERTY_ZOOMFXBUFFER_ALL");
 ViewQuerySupport(propset,DSPROPSETID_ZOOMFX_BufferProperties,DSPROPERTY_ZOOMFXBUFFER_BOX,"DSPROPERTY_ZOOMFXBUFFER_BOX");
 ViewQuerySupport(propset,DSPROPSETID_ZOOMFX_BufferProperties,DSPROPERTY_ZOOMFXBUFFER_ORIENTATION,"DSPROPERTY_ZOOMFXBUFFER_ORIENTATION");
 ViewQuerySupport(propset,DSPROPSETID_ZOOMFX_BufferProperties,DSPROPERTY_ZOOMFXBUFFER_MACROFX_EFFECT,"DSPROPERTY_ZOOMFXBUFFER_MACROFX_EFFECT");

 AddToLog(end);
 testpass = true;

nps:;
 if (!propset) propset->Release(); 
ns3s:
 if (!sec3dbuf) sec3dbuf->Release(); 
nss:;
 if (!secbuf) secbuf->Release();
nls:;
 if (!list) list->Release();
nbs:;
 if (!prbuf) prbuf->Release();
ncs:;
 if (!ds) ds->Release();
ns:;
 if (testpass == false)
 {
  AddToLog(notsupported);
  AddToLog(end);
  AddToLog(end);
 }

 CoUninitialize();
 return TRUE;
}

void I3DL2SupportedTest(HWND hWnd)
{
 DirectSoundEnumerate(I3DL2SupportedTestCallback,(LPVOID)hWnd);
}

BOOL CALLBACK I3DL2SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{
 HWND hWnd = (HWND)lpContext;
 logwnd = hWnd;
 LPDIRECTSOUND ds = 0;
 LPDIRECTSOUNDBUFFER prbuf = 0,secbuf = 0;
 HRESULT hr = 0;
 DSBUFFERDESC desc;
 LPDIRECTSOUND3DLISTENER list = 0;
 LPDIRECTSOUND3DBUFFER sec3dbuf = 0;;
 LPKSPROPERTYSET propset = 0;
 ULONG support = 0;
 WAVEFORMATEX wf;
 bool testpass = false;

 if (lstrlen(lpcstrModule) == 0)
 {
  wsprintf(buf,"--- %s\r\n",lpcstrDescription);
  AddToLog(buf); 
 }
 else
 {
  wsprintf(buf,"--- %s [%s]\r\n",lpcstrDescription, lpcstrModule);
  AddToLog(buf); 
 }

 AddToLog("I3DL2 - ");

 CoInitialize(NULL);
 // для отвязки от DirectSoundCreate - делаем инициализацию через стандартный COM
 hr = CoCreateInstance(CLSID_DirectSound,
          NULL, 
          CLSCTX_INPROC_SERVER,
          IID_IDirectSound,
          (LPVOID*) &ds);
 if (FAILED(hr)) goto ns;

 hr = ds->Initialize(lpGuid);
 if (FAILED(hr)) goto ncs;
 
 hr = ds->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);
 if (FAILED(hr)) goto ncs;
  
 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
 hr = ds->CreateSoundBuffer(&desc, &prbuf, NULL);
 if (FAILED(hr)) goto ncs;

 hr = prbuf->QueryInterface(IID_IDirectSound3DListener,(void**)&list);
 if (FAILED(hr)) goto nbs;

 ZeroMemory( &wf, sizeof(WAVEFORMATEX));
 wf.wFormatTag = WAVE_FORMAT_PCM;
 wf.nChannels = 1;
 wf.nSamplesPerSec = 11025;
 wf.nAvgBytesPerSec = 22050;
 wf.nBlockAlign = 2;
 wf.wBitsPerSample = 16;
 wf.cbSize = 0;

 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_CTRL3D;
 desc.dwBufferBytes = 1024;
 desc.lpwfxFormat = &wf;
 hr = ds->CreateSoundBuffer(&desc, &secbuf, NULL);
 if (FAILED(hr)) goto nls;

 hr = secbuf->QueryInterface(IID_IDirectSound3DBuffer,(void **)&sec3dbuf);
 if (FAILED(hr)) goto nss;
 
 hr = sec3dbuf->QueryInterface(IID_IKsPropertySet, (void**)&propset);
 if (FAILED(hr)) goto ns3s;
 
 // проверка всех параметров
 hr = propset->QuerySupport(DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_ALL,&support);
 if (FAILED(hr)) goto nps;
 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_ALL,&support);
 if (FAILED(hr)) goto nps;
 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 AddToLog(supported);
 AddToLog(end);
 AddToLog(end);
 AddToLog("Listener properties:\r\n");

 // параметры слушателя
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_ALL,"DSPROPERTY_I3DL2LISTENER_ALL");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_ROOMHF,"DSPROPERTY_I3DL2LISTENER_ROOMHF");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_ROOMROLLOFFFACTOR,"DSPROPERTY_I3DL2LISTENER_ROOMROLLOFFFACTOR");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_DECAYTIME,"DSPROPERTY_I3DL2LISTENER_DECAYTIME");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_DECAYHFRATIO,"DSPROPERTY_I3DL2LISTENER_DECAYHFRATIO");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_REFLECTIONS,"DSPROPERTY_I3DL2LISTENER_REFLECTIONS");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_REFLECTIONSDELAY,"DSPROPERTY_I3DL2LISTENER_REFLECTIONSDELAY");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_REVERB,"DSPROPERTY_I3DL2LISTENER_REVERB");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_REVERBDELAY,"DSPROPERTY_I3DL2LISTENER_REVERBDELAY");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_DIFFUSION,"DSPROPERTY_I3DL2LISTENER_DIFFUSION");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_DENSITY,"DSPROPERTY_I3DL2LISTENER_DENSITY");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_ListenerProperties,DSPROPERTY_I3DL2LISTENER_HFREFERENCE,"DSPROPERTY_I3DL2LISTENER_HFREFERENCE");

 wsprintf(buf,"Buffer properties:\r\n");
 AddToLog(buf);

 // параметры буфера
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_ALL,"DSPROPERTY_I3DL2BUFFER_ALL");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_OBSTRUCTIONALL,"DSPROPERTY_I3DL2BUFFER_OBSTRUCTIONALL");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_OCCLUSIONALL,"DSPROPERTY_I3DL2BUFFER_OCCLUSIONALL");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_DIRECT,"DSPROPERTY_I3DL2BUFFER_DIRECT");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_DIRECTHF,"DSPROPERTY_I3DL2BUFFER_DIRECTHF");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_ROOM,"DSPROPERTY_I3DL2BUFFER_ROOM");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_ROOMHF,"DSPROPERTY_I3DL2BUFFER_ROOMHF");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_ROOMROLLOFFFACTOR,"DSPROPERTY_I3DL2BUFFER_ROOMROLLOFFFACTOR");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_OBSTRUCTION,"DSPROPERTY_I3DL2BUFFER_OBSTRUCTION");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_OBSTRUCTIONLFRATIO,"DSPROPERTY_I3DL2BUFFER_OBSTRUCTIONLFRATIO");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_OCCLUSION,"DSPROPERTY_I3DL2BUFFER_OCCLUSION");
 ViewQuerySupport(propset,DSPROPSETID_I3DL2_BufferProperties,DSPROPERTY_I3DL2BUFFER_OCCLUSIONLFRATIO,"DSPROPERTY_I3DL2BUFFER_OCCLUSIONLFRATIO");

 AddToLog(end);
 testpass = true;

nps:;
 if (!propset) propset->Release(); 
ns3s:
 if (!sec3dbuf) sec3dbuf->Release(); 
nss:;
 if (!secbuf) secbuf->Release();
nls:;
 if (!list) list->Release();
nbs:;
 if (!prbuf) prbuf->Release();
ncs:;
 if (!ds) ds->Release();
ns:;
 if (testpass == false)
 {
  AddToLog(notsupported);
  AddToLog(end);
  AddToLog(end);
 }
 
 CoUninitialize();
 return TRUE;
}

LRESULT CALLBACK pWndProc16(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
       ASIOSupportedTest(hDlg);
       break;
 }
 return FALSE;
}

bool loadAsioDriver(char *name);

struct asiosampletypes
{
 int param;
 char *name;
};

asiosampletypes sampletypes[] = {
	{0,  "ASIOSTInt16MSB"},
	{1,	 "ASIOSTInt24MSB"},
	{2,	 "ASIOSTInt32MSB"},
	{3,	 "ASIOSTFloat32MSB"},
	{4,	 "ASIOSTFloat64MSB"},

	{8,	 "ASIOSTInt32MSB16"},
	{9,	 "ASIOSTInt32MSB18"},
	{10, "ASIOSTInt32MSB20"},
	{11, "ASIOSTInt32MSB24"},
	
	{16, "ASIOSTInt16LSB"},
	{17, "ASIOSTInt24LSB"},
	{18, "ASIOSTInt32LSB"},
	{19, "ASIOSTFloat32LSB"},
	{20, "ASIOSTFloat64LSB"},

	{24, "ASIOSTInt32LSB16"},
	{25, "ASIOSTInt32LSB18"},
	{26, "ASIOSTInt32LSB20"},
	{27, "ASIOSTInt32LSB24"},

	{32, "ASIOSTDSDInt8LSB1"},
	{33, "ASIOSTDSDInt8MSB1"},
	{40, "ASIOSTDSDInt8NER8"}
};

char *unknownparam = "Unknown";

char *GetNameSampleType(int param)
{
 for (int i = 0;i < sizeof(sampletypes)/sizeof(asiosampletypes);i++)
 {
  if (sampletypes[i].param == param)
  {
   return sampletypes[i].name;
  }
 }
 return unknownparam;
}

void ASIOSupportedTest(HWND hWnd)
{
 AsioDriverList *adl;
 LPASIODRVSTRUCT lads;
 int numdrv;

 logwnd = hWnd;

 adl = new AsioDriverList;

 wsprintf(buf,"ASIO drivers: %d\r\n",adl->numdrv);
 AddToLog(buf);

 if (adl->numdrv == 0) return;
 lads = adl->lpdrvlist;

 ASIODriverInfo info;

 for (numdrv = adl->numdrv;numdrv > 0;numdrv--)
 {
  wsprintf(buf,"\r\n--- %s\r\n",lads->drvname);
  AddToLog(buf);
  wsprintf(buf,"Driver ID:\t\t\t%d\r\n",lads->drvID);
  AddToLog(buf);
  wsprintf(buf,"Driver path:\t\t%s\r\n",lads->dllpath);
  AddToLog(buf);
  wsprintf(buf,"CLSID:\t\t\t0x%X%X%X%X\r\n",lads->clsid.Data1,lads->clsid.Data2,lads->clsid.Data3,lads->clsid.Data4);
  AddToLog(buf);

  if (loadAsioDriver(lads->drvname))
  {
   ZeroMemory(&info,sizeof(ASIODriverInfo));
   if (ASIOInit (&info) == ASE_OK)
   {
    wsprintf(buf,"ASIO version:\t\t%d\r\n",info.asioVersion);
    AddToLog(buf);
    wsprintf(buf,"Driver version:\t\t%d\r\n",info.driverVersion);
    AddToLog(buf);
	long inchan = 0, outchan = 0;
	if (ASIOGetChannels(&inchan, &outchan) == ASE_OK)
	{
     wsprintf(buf,"Input channels:\t\t%d\r\n",inchan);
     AddToLog(buf);
     wsprintf(buf,"Output channels:\t\t%d\r\n",outchan);
     AddToLog(buf);    
	}
	else
	{
     AddToLog("Input channels:\terror\r\nOutput channels:\terror\r\n");
	}
    
	long latin,latout;
	if (ASIOGetLatencies(&latin, &latout) == ASE_OK)
	{
     wsprintf(buf,"Input latency:\t\t%d\r\n",latin);
     AddToLog(buf);
     wsprintf(buf,"Output latency:\t\t%d\r\n",latout);
     AddToLog(buf);    
	}
	else
	{
     AddToLog("Input latency:\terror\r\nOutput latency:\terror\r\n");
	}

	long minbuf, maxbuf, pref,gra;
	if (ASIOGetBufferSize(&minbuf, &maxbuf, &pref, &gra) == ASE_OK)
	{
     wsprintf(buf,"Min buffer size:\t\t%d\r\n",minbuf);
     AddToLog(buf);
     wsprintf(buf,"Max buffer size:\t\t%d\r\n",maxbuf);
     AddToLog(buf);
     wsprintf(buf,"Preferred buffer size:\t%d\r\n",pref);
     AddToLog(buf);
     wsprintf(buf,"Granularity:\t\t%d\r\n",gra);
     AddToLog(buf);
	 
	}
	else
	{
     AddToLog("Min buffer size:\terror\r\nMax buffer size:\terror\r\nPreferred buffer size:\terror\r\nGranularity:\terror\r\n");
	}

	AddToLog("ASIOOutputReady\t\t");
	if(ASIOOutputReady() == ASE_OK)
     AddToLog(supported);
	else
     AddToLog(notsupported);
	AddToLog(end);

	AddToLog("Sample rate:\r\n");

    wsprintf(buf," 8000 Hz\t\t\t%s\r\n",ASIOCanSampleRate(8000) == ASE_OK ? supported : notsupported);
    AddToLog(buf);
    wsprintf(buf," 11025 Hz\t\t%s\r\n",ASIOCanSampleRate(11025) == ASE_OK ? supported : notsupported);
    AddToLog(buf);
    wsprintf(buf," 16000 Hz\t\t%s\r\n",ASIOCanSampleRate(16000) == ASE_OK ? supported : notsupported);
    AddToLog(buf);
    wsprintf(buf," 22050 Hz\t\t%s\r\n",ASIOCanSampleRate(22050) == ASE_OK ? supported : notsupported);
    AddToLog(buf);
    wsprintf(buf," 32000 Hz\t\t%s\r\n",ASIOCanSampleRate(32000) == ASE_OK ? supported : notsupported);
    AddToLog(buf);
    wsprintf(buf," 44100 Hz\t\t%s\r\n",ASIOCanSampleRate(44100) == ASE_OK ? supported : notsupported);
    AddToLog(buf);
    wsprintf(buf," 48000 Hz\t\t%s\r\n",ASIOCanSampleRate(48000) == ASE_OK ? supported : notsupported);
    AddToLog(buf);
    wsprintf(buf," 88200 Hz\t\t%s\r\n",ASIOCanSampleRate(88200) == ASE_OK ? supported : notsupported);
    AddToLog(buf);
    wsprintf(buf," 96000 Hz\t\t%s\r\n",ASIOCanSampleRate(96000) == ASE_OK ? supported : notsupported);
    AddToLog(buf);
    wsprintf(buf," 176400 Hz\t\t%s\r\n",ASIOCanSampleRate(176400) == ASE_OK ? supported : notsupported);
    AddToLog(buf);
    wsprintf(buf," 192000 Hz\t\t%s\r\n",ASIOCanSampleRate(192000) == ASE_OK ? supported : notsupported);
    AddToLog(buf);

    ASIOChannelInfo channelInfo;

    AddToLog("Input channels:\r\n");

	ASIOError res;
    for (int i = 0; i < inchan; i++)
	{
	 channelInfo.channel = i;
	 channelInfo.isInput = ASIOTrue;
     res = ASIOGetChannelInfo(&channelInfo);
     if (res != ASE_OK)
      wsprintf(buf," channel: %d - error\r\n",i);
	 else
 	  wsprintf(buf," channel: %d (%s) - %s\r\n",i,channelInfo.name,GetNameSampleType(channelInfo.type));
     AddToLog(buf);
	}

	AddToLog("Output channels:\r\n");
	for (i = 0; i < outchan; i++)
	{
	 channelInfo.channel = i;
	 channelInfo.isInput = ASIOFalse;
     res = ASIOGetChannelInfo(&channelInfo);
     if (res != ASE_OK)
      wsprintf(buf," channel: %d - error\r\n",i);
	 else
 	  wsprintf(buf," channel: %d (%s) - %s\r\n",i,channelInfo.name,GetNameSampleType(channelInfo.type));
     AddToLog(buf);
	}

	ASIOExit();
   }
  }

  lads = lads->next;
 }
 
 delete(adl);

}


LRESULT CALLBACK pWndProc17(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
       LowLevelScan(hDlg,true);
       break;
 }
 return FALSE;
}

SC_HANDLE hSCManager,hService;
HANDLE hDevice;

bool DriverLoad(const char* name)
{
 BOOL status;
 char lpBuffer[256];

 memset(lpBuffer,0,sizeof(lpBuffer));

 hSCManager=NULL;
 hService=NULL;

 hSCManager=OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
 if (hSCManager == 0) return false;

// GetCurrentDirectory(256, lpBuffer);
 strcpy(lpBuffer,TempPathBuffer);
// strcat(lpBuffer,"\\");
 strcat(lpBuffer,name);

 hService = CreateService(hSCManager,name,name,SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER,SERVICE_DEMAND_START,SERVICE_ERROR_NORMAL,lpBuffer,NULL,NULL,NULL,NULL,NULL);
 if (hService == 0) 
 {
  if (GetLastError() != ERROR_SERVICE_EXISTS) return false;
 }

 hService=OpenService(hSCManager,name,SERVICE_ALL_ACCESS);

 status = StartService(hService,0,NULL);
 if(status == 0)
 {
  DWORD w = GetLastError();
  if (GetLastError() != ERROR_SERVICE_ALREADY_RUNNING) return false;
 }

 hDevice = CreateFile ("//./rdrv", GENERIC_READ,
                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                        NULL, OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL, NULL);

 return true;
}

//-------------------------------------------------------------------
int drvUnLoad(const char* name)
{
 SERVICE_STATUS ServiceStatus;
 int status;
 status=FALSE;

 if (hDevice!=INVALID_HANDLE_VALUE)
 {
  CloseHandle(hDevice);
  hDevice=INVALID_HANDLE_VALUE;
 }

 if (hService) 
 {
  ControlService(hService,SERVICE_CONTROL_STOP,&ServiceStatus);
  DeleteService(hService);
  CloseServiceHandle(hService); 
 }

 CloseServiceHandle(hSCManager);

 return status;
}

typedef struct _PCIDEV
{
 unsigned int bus;
 unsigned int dev;
 unsigned int fn;
 unsigned int reg;
 int retv;
} PCIDEV;

char tmstr[512];

#define FIRST_IOCTL_INDEX 0x800
#define FILE_DEVICE_myDrv 0x00008000

#define IOCTL_PCI_DIRECT_READ CTL_CODE(FILE_DEVICE_myDrv, FIRST_IOCTL_INDEX + 102, METHOD_BUFFERED, FILE_ANY_ACCESS)

char *GetSubDeviceIdClass(DWORD ven, DWORD dev, DWORD subven, DWORD subdev)
{
 int i;
 for(i = 0;i<sizeof(PciSubDevTable)/sizeof(PCI_SUBDEVTABLE);i++)
 {
  if (PciSubDevTable[i].VenId == ven &&
	  PciSubDevTable[i].DevId == dev &&
	  PciSubDevTable[i].SubVenId == subven &&
	  PciSubDevTable[i].SubDevId == subdev)
  {
   wsprintf(tmstr,"%s",PciSubDevTable[i].Chip);
   return tmstr;
  }
 }
 tmstr[0] = 0;
 return tmstr;
}

char *GetDeviceIdClass(DWORD ven, DWORD dev)
{
 int i;
 for(i = 0;i<sizeof(PciDevTable)/sizeof(PCI_DEVTABLE);i++)
 {
  if (PciDevTable[i].VenId == ven &&
	  PciDevTable[i].DevId == dev)
  {
   if (lstrlen(PciDevTable[i].Chip) == 0)
    wsprintf(tmstr,"%s",PciDevTable[i].ChipDesc);
   else
   if (lstrlen(PciDevTable[i].ChipDesc) == 0)
    wsprintf(tmstr,"%s",PciDevTable[i].Chip);
   else
    wsprintf(tmstr,"%s/%s",PciDevTable[i].Chip,PciDevTable[i].ChipDesc);
   return tmstr;
  }
 }
 tmstr[0] = 0;
 return tmstr;
}

char *GetVendorIdClass(DWORD code)
{
 int i;
 for(i = 0;i<sizeof(PciVenTable)/sizeof(PCI_VENTABLE);i++)
 {
  if (PciVenTable[i].VenId == code)
  {
   if (lstrlen(PciVenTable[i].VenFull) > 1) return PciVenTable[i].VenFull;
   return "";
  }
 }
 tmstr[0] = 0;
 return tmstr;
}

char *GetNameClass(DWORD code)
{
 int i;
 unsigned char c1,c2,c3;
 c1 = (unsigned char)((code & 0xff0000) >> 16);
 c2 = (unsigned char)((code & 0x00ff00) >> 8);
 c3 = (unsigned char)((code & 0x0000ff));

 for(i = 0;i<sizeof(PciClassCodeTable)/sizeof(PCI_CLASSCODETABLE);i++)
 {
  if (c1 == PciClassCodeTable[i].BaseClass &&
	  c2 == PciClassCodeTable[i].SubClass &&
	  c3 == PciClassCodeTable[i].ProgIf)
  {
   wsprintf(tmstr,"%s %s %s",PciClassCodeTable[i].BaseDesc,PciClassCodeTable[i].SubDesc,PciClassCodeTable[i].ProgDesc);
   return tmstr;
  }
 }

 for(i = 0;i<sizeof(PciClassCodeTable)/sizeof(PCI_CLASSCODETABLE);i++)
 {
  if (c1 == PciClassCodeTable[i].BaseClass &&
	  c2 == PciClassCodeTable[i].SubClass)
  {
   wsprintf(tmstr,"%s %s",PciClassCodeTable[i].BaseDesc,PciClassCodeTable[i].SubDesc);
   return tmstr;
  }
 }

 tmstr[0] = 0;
 return tmstr;
}


bool loaddrv = false;

void LowLevelScan(HWND hWnd, bool onlyaudio)
{
 logwnd = hWnd;

 AddToLog("Low level PCI information:\r\n");


 OSVERSIONINFO os;
 memset(&os,0,sizeof(OSVERSIONINFO));
 os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

 if (GetVersionEx(&os) == FALSE || 
	 os.dwPlatformId != VER_PLATFORM_WIN32_NT)
 {
  wsprintf(buf,"Current version of Windows %s\r\n", notsupported);
  AddToLog(buf);
  return;
 }

 if (loaddrv == false && DriverLoad(drvname) == false)
 {
  drvUnLoad(drvname);
  AddToLog("Can't load driver\r\n");
  return;
 }

 loaddrv = true;

 DWORD test[256];
 DWORD ReturetLength = 0;
 
 PCIDEV pci;

 DWORD bus, dev, fn = 0, adr;
 DWORD code;

 for(bus = 0; bus < 256; bus++)
 {
  for(dev = 0; dev < 32; dev++)
  {
   for(fn = 0; fn < 8; fn++)
   {
    pci.bus = bus;
    pci.dev = dev;
    pci.fn = fn;
    pci.reg = 8;
	pci.retv = 4;
    DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);
    code = test[0] >> 8;

    if(code != 0xffffff && ((onlyaudio == true && code == 0x040100) || onlyaudio == false))
	{
     wsprintf(buf,"\r\nbus: %d, device: %d, function: %d\r\n", bus, dev, fn);
	 AddToLog(buf);
     wsprintf(buf,"class:\t\t0x%X (%s)\r\n", code, GetNameClass(code));
	 AddToLog(buf);

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 8;
	 pci.retv = 1;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);
     
     wsprintf(buf,"revision:\t\t0x%X\r\n", test[0]);
	 AddToLog(buf);

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0;
	 pci.retv = 2;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);
     
     wsprintf(buf,"vendor id:\t\t0x%X - %s\r\n", test[0], GetVendorIdClass(test[0]));
	 AddToLog(buf);     

	 DWORD ven = test[0];
 
     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 2;
	 pci.retv = 2;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

	 wsprintf(buf,"device id:\t\t0x%X - %s\r\n", test[0],GetDeviceIdClass(ven,test[0]));
	 AddToLog(buf);

	 DWORD devid = test[0];

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x2c;
	 pci.retv = 2;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

	 if (test[0] == 0)
	  wsprintf(buf,"sub vendor id:\t0x%X\r\n",test[0]);
	 else
      wsprintf(buf,"sub vendor id:\t0x%X - %s\r\n",test[0],GetVendorIdClass(test[0]));
	 AddToLog(buf);

	 DWORD subven = test[0];

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x2e;
	 pci.retv = 2;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

     char *ptr = GetSubDeviceIdClass(ven,devid,subven,test[0]);
	 if (ptr[0] == 0)
      ptr = GetDeviceIdClass(ven,test[0]);
     if (ptr[0] == 0)
 	  wsprintf(buf,"sub device id:\t0x%X\r\n",test[0]);
	 else
	  wsprintf(buf,"sub device id:\t0x%X - %s\r\n",test[0],ptr);
	 AddToLog(buf);

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x3c;
	 pci.retv = 1;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

     wsprintf(buf,"Interrut line:\t0x%X (%d)\r\n",test[0],test[0]);
	 AddToLog(buf);

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x3d;
	 pci.retv = 1;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

     wsprintf(buf,"Interrut pin:\t0x%X\r\n",test[0]);
	 AddToLog(buf);
     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x0c;
	 pci.retv = 1;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

     wsprintf(buf,"Cashe line size:\t0x%X\r\n",test[0]);
	 AddToLog(buf);

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x0d;
	 pci.retv = 1;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

     wsprintf(buf,"Latency timer:\t0x%X (%d)\r\n",test[0],test[0]);
	 AddToLog(buf);

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x0e;
	 pci.retv = 1;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

     wsprintf(buf,"Header type:\t0x%X\r\n",test[0]);
	 AddToLog(buf);

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x0f;
	 pci.retv = 1;
     DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

     wsprintf(buf,"BIST:\t\t0x%X\r\n",test[0]);
	 AddToLog(buf);

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x3e;
	 pci.retv = 1;    
	 DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

     wsprintf(buf,"Min_GNT:\t0x%X\r\n",test[0]);
	 AddToLog(buf);

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x3f;
	 pci.retv = 1;    
	 DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

     wsprintf(buf,"Max_lat:\t\t0x%X\r\n",test[0]);
	 AddToLog(buf);
     
	 for (adr = 0x10;adr < 0x28; adr += 4)
	 {
      pci.bus = bus;
      pci.dev = dev;
      pci.fn = fn;
      pci.reg = adr;
	  pci.retv = 4;    
	  DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

      wsprintf(buf,"Base address:\t0x%X\r\n",test[0] & 0xfffffff0);
 	  AddToLog(buf);

	 }

     pci.bus = bus;
     pci.dev = dev;
     pci.fn = fn;
     pci.reg = 0x30;
	 pci.retv = 4;    
	 DeviceIoControl(hDevice, IOCTL_PCI_DIRECT_READ, &pci, sizeof(PCIDEV), &test, 4, &ReturetLength, NULL);

     wsprintf(buf,"ROM address:\t0x%X\r\n",test[0]);
	 AddToLog(buf);

	}
   }
  }
 }
}

void SavePCILog(HWND hWnd)
{
 int hFile;
 OPENFILENAME ofn;
 static char szFilter[] = "log files (*.log)\0*.log\0\0";
 static char szFileName[_MAX_PATH];
 char szTitleName[_MAX_FNAME + _MAX_EXT];
 char *tempbuf = 0;
 int templen;

 memset(&ofn,0,sizeof(OPENFILENAME));

 ofn.lStructSize       = sizeof (OPENFILENAME);
 ofn.hwndOwner         = hWnd;
 ofn.lpstrFilter       = szFilter;
 ofn.lpstrFile         = szFileName;
 ofn.nMaxFile          = _MAX_PATH;
 ofn.lpstrFileTitle    = szTitleName;
 ofn.nMaxFileTitle     = _MAX_FNAME + _MAX_EXT;
 ofn.Flags             = OFN_HIDEREADONLY | OFN_EXTENSIONDIFFERENT | OFN_OVERWRITEPROMPT;
 ofn.lpstrDefExt       = "*.log";
 ofn.lpstrTitle        = "Save PCI Log";
 if(!GetSaveFileName(&ofn)) return;

 hFile = _lcreat(szFileName, 0);
 if (hFile == -1) return;
 _llseek(hFile, 0, 2);

 _lwrite(hFile,sep,lstrlen(sep));
 _lwrite(hFile,label1,lstrlen(label1));
 _lwrite(hFile,label2,lstrlen(label2));
 _lwrite(hFile,label3,lstrlen(label3));
 _lwrite(hFile,sep,lstrlen(sep));

 templen = SendDlgItemMessage(hWnd,IDC_LOG,WM_GETTEXTLENGTH,0,0);
 tempbuf = (char*)malloc(templen+10);
 memset(tempbuf,0,templen);
 SendDlgItemMessage(hWnd,IDC_LOG,WM_GETTEXT,(WPARAM)templen,(LPARAM)tempbuf);
 tempbuf[templen-1] = 0x0a;
 _lwrite(hFile,tempbuf,templen);
 _lwrite(hFile,sep,lstrlen(sep));
 free(tempbuf);

 _lclose(hFile);
}

void ResizeALLPCI(HWND hWnd)
{
 RECT rect;
 int xres,yres;

 GetClientRect(hWnd,&rect);
 xres = rect.right-rect.left;
 yres = rect.bottom-rect.top;
 MoveWindow(GetDlgItem(hWnd,IDC_LOG),0,0,xres,yres,TRUE);
}

LRESULT CALLBACK AllPCIProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
 switch (iMsg)
 {
  case WM_INITDIALOG:
	   GetWindowRect(hDlg,&winbox);
	   MoveWindow(hDlg,GetSystemMetrics(SM_CXSCREEN)/2-(winbox.right-winbox.left)/2,GetSystemMetrics(SM_CYSCREEN)/2-(winbox.bottom-winbox.top)/2,winbox.right-winbox.left,winbox.bottom-winbox.top,TRUE);
	   LowLevelScan(hDlg,false);
       SendDlgItemMessage(hDlg,IDC_LOG,EM_SETSEL,0,1);
	   ResizeALLPCI(hDlg);
	   break;
  case WM_CLOSE:
	   EndDialog (hDlg, 0);
	   break;
  case WM_COMMAND:
       switch (LOWORD(wParam))
       {
        case ID_SAVELOGAS:
			 SavePCILog(hDlg);
			 break;
	   }
	   break;
  case WM_SIZE:
	   ResizeALLPCI(hDlg);
	   break;
 }
 return FALSE;
}
/*      
char *geterr(HRESULT hr)
{
 switch (hr)
 {
  case DSERR_ALLOCATED:
	   return "DSERR_ALLOCATED";
	   break;
  case DSERR_BADFORMAT:
	   return "DSERR_BADFORMAT";
	   break;
  case DSERR_BUFFERTOOSMALL:
	   return "DSERR_BUFFERTOOSMALL";
	   break;
  case DSERR_CONTROLUNAVAIL:
	   return "DSERR_CONTROLUNAVAIL";
	   break;
  case DSERR_DS8_REQUIRED: 
	   return "DSERR_DS8_REQUIRED";
	   break;
  case DSERR_INVALIDCALL:
	   return "DSERR_INVALIDCALL";
	   break;
  case DSERR_INVALIDPARAM:
	   return "DSERR_INVALIDPARAM";
	   break;
  case DSERR_NOAGGREGATION:
	   return "DSERR_NOAGGREGATION";
	   break;
  case DSERR_OUTOFMEMORY:
	   return "DSERR_OUTOFMEMORY";
	   break;
  case DSERR_UNINITIALIZED:
	   return "DSERR_UNINITIALIZED";
	   break;
  case DSERR_UNSUPPORTED:
	   return "DSERR_UNSUPPORTED";
	   break;
  case DSERR_FXUNAVAILABLE:
	   return "DSERR_FXUNAVAILABLE";
	   break;
  case DS_OK:
	   return "DS_OK";
	   break;
  case DS_NO_VIRTUALIZATION:
	   return "DS_NO_VIRTUALIZATION";
	   break;
  case DSERR_ACCESSDENIED:
	   return "DSERR_ACCESSDENIED";
	   break;
  case DSERR_ALREADYINITIALIZED :
	   return "DSERR_ALREADYINITIALIZED ";
	   break;
  case DSERR_BADSENDBUFFERGUID:
	   return "DSERR_BADSENDBUFFERGUID";
	   break; 
  case DSERR_BUFFERLOST:
	   return "DSERR_BUFFERLOST";
	   break; 
  case DSERR_GENERIC:
	   return "DSERR_GENERIC";
	   break; 
  case DSERR_NODRIVER:
	   return "DSERR_NODRIVER";
	   break;
  case DSERR_OBJECTNOTFOUND:
	   return "DSERR_OBJECTNOTFOUND";
	   break;
  case DSERR_OTHERAPPHASPRIO:
	   return "DSERR_OTHERAPPHASPRIO";
	   break;
  case DSERR_PRIOLEVELNEEDED:
	   return "DSERR_PRIOLEVELNEEDED";
	   break;
  case DSERR_SENDLOOP:
	   return "DSERR_SENDLOOP";
	   break;
 }
 return "no";
}
*/
BOOL CALLBACK DSEnumCallback8(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{
 int vds = 8; // поддерживаемая версия
 LPDIRECTSOUND8 ds = 0;
 HRESULT hr = 0;
 DSCAPS dscaps;

 if (lstrlen(lpcstrModule) == 0)
 {
  wsprintf(buf,"\r\n--- %s\r\n",lpcstrDescription);
  AddToLog(buf); 
 }
 else
 {
  wsprintf(buf,"\r\n--- %s [%s]\r\n",lpcstrDescription, lpcstrModule);
  AddToLog(buf); 
 }

 if (lpGuid == 0)
 {
  AddToLog("GUID: default\r\n");
 }
 else
 {
  wsprintf(buf,"GUID: 0x%X%X%X%X\r\n",lpGuid->Data1,lpGuid->Data2,lpGuid->Data3,lpGuid->Data4);
  AddToLog(buf);
 }

 // для отвязки от DirectSoundCreate - делаем инициализацию через стандартный COM
 CoInitialize(NULL);

 // пытаемся создать объект DS8
 hr = CoCreateInstance(CLSID_DirectSound8,NULL,CLSCTX_INPROC_SERVER,IID_IDirectSound8,(LPVOID*) &ds);
 if (FAILED(hr))
 {
  // пытаемся создать объект DS
  hr = CoCreateInstance(CLSID_DirectSound,NULL,CLSCTX_INPROC_SERVER,IID_IDirectSound,(LPVOID*) &ds);
  if (FAILED(hr)) goto ns;
  vds = 2;
 }

 hr = ds->Initialize(lpGuid);
 if (FAILED(hr)) goto ncs;
 
 hr = ds->SetCooperativeLevel(logwnd, DSSCL_EXCLUSIVE);
 if (FAILED(hr)) goto ncs;
 
 memset(&dscaps, 0, sizeof(DSCAPS));
 dscaps.dwSize = sizeof(DSCAPS);
 hr = ds->GetCaps(&dscaps);
 if (FAILED(hr)) goto ncs;

 // для ds8 - специальная проверка на сертификацию
 if (vds == 8)
 {
  DWORD sert = -1;
  ds->VerifyCertification(&sert);
  if (!FAILED(hr))
  {
   if (sert == DS_CERTIFIED)
    AddToLog("This driver has been tested and certified by Microsoft\r\n"); 
  }
 }
 else
 // для ds - обычная проверка
 if ((dscaps.dwFlags & DSCAPS_CERTIFIED) != 0) 
 {
  AddToLog("This driver has been tested and certified by Microsoft\r\n"); 
 }

 if ((dscaps.dwFlags & DSCAPS_CONTINUOUSRATE) != 0) 
 {
  wsprintf(buf,"Secondary sample rate (Hz): %d - %d\r\n",dscaps.dwMinSecondarySampleRate,dscaps.dwMaxSecondarySampleRate);
  AddToLog(buf); 
 }

 wsprintf(buf,"Primary buffers: count: %d\r\n ",dscaps.dwPrimaryBuffers);
 AddToLog(buf); 
 if ((dscaps.dwFlags & DSCAPS_PRIMARY16BIT) != 0) AddToLog("16 bit ");
 if ((dscaps.dwFlags & DSCAPS_PRIMARY8BIT) != 0)  AddToLog("8 bit ");
 if ((dscaps.dwFlags & DSCAPS_PRIMARYSTEREO) != 0) AddToLog("stereo ");
 if ((dscaps.dwFlags & DSCAPS_PRIMARYMONO) != 0) AddToLog("mono ");
 AddToLog(end);

 AddToLog("Secondary buffers:\r\n ");
 if ((dscaps.dwFlags & DSCAPS_SECONDARY16BIT) != 0) AddToLog("16 bit ");
 if ((dscaps.dwFlags & DSCAPS_SECONDARY8BIT) != 0) AddToLog("8 bit ");
 if ((dscaps.dwFlags & DSCAPS_SECONDARYSTEREO) != 0) AddToLog("stereo ");
 if ((dscaps.dwFlags & DSCAPS_SECONDARYMONO) != 0) AddToLog("mono ");
 AddToLog(end);
 
 AddToLog("Hardware buffers:\r\n");
 AddToLog(" 2D:\r\n");
 wsprintf(buf,"  all: %d, free: %d\r\n",dscaps.dwMaxHwMixingAllBuffers,dscaps.dwFreeHwMixingAllBuffers);
 AddToLog(buf); 
 wsprintf(buf,"  static: %d, free: %d\r\n",dscaps.dwMaxHwMixingStaticBuffers,dscaps.dwFreeHwMixingStaticBuffers);
 AddToLog(buf); 
 wsprintf(buf,"  streaming: %d, free: %d\r\n",dscaps.dwMaxHwMixingStreamingBuffers,dscaps.dwFreeHwMixingStreamingBuffers);
 AddToLog(buf); 
 AddToLog(" 3D:\r\n");
 wsprintf(buf,"  all: %d, free: %d\r\n",dscaps.dwMaxHw3DAllBuffers,dscaps.dwFreeHw3DAllBuffers);
 AddToLog(buf); 
 wsprintf(buf,"  static: %d, free: %d\r\n",dscaps.dwMaxHw3DStaticBuffers,dscaps.dwFreeHw3DStaticBuffers);
 AddToLog(buf); 
 wsprintf(buf,"  streaming: %d, free: %d\r\n",dscaps.dwMaxHw3DStreamingBuffers,dscaps.dwFreeHw3DStreamingBuffers);
 AddToLog(buf); 

 wsprintf(buf,"Total memory on sound card: %d\r\n",dscaps.dwTotalHwMemBytes);
 AddToLog(buf); 
 wsprintf(buf,"Free memory on sound card: %d\r\n",dscaps.dwFreeHwMemBytes);
 AddToLog(buf); 

 if (vds == 2) goto ncs; // если ds, то завершаем

 LPDIRECTSOUNDBUFFER prbuf,secbuf;
 prbuf = secbuf = 0;
 LPDIRECTSOUNDBUFFER8 dsb8;
 dsb8 = 0;
 DSBUFFERDESC desc;
 WAVEFORMATEX wf;

 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_PRIMARYBUFFER;
 hr = ds->CreateSoundBuffer(&desc, &prbuf, NULL);
 if (FAILED(hr)) goto ncs;

 ZeroMemory( &wf, sizeof(WAVEFORMATEX));
 wf.wFormatTag = WAVE_FORMAT_PCM;
 wf.nChannels = 1;
 wf.nSamplesPerSec = 11025;
 wf.nAvgBytesPerSec = 22050;
 wf.nBlockAlign = 2;
 wf.wBitsPerSample = 16;
 wf.cbSize = 0;

 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_CTRLFX;
 desc.dwBufferBytes = 10*1024;
 desc.lpwfxFormat = &wf;
 hr = ds->CreateSoundBuffer(&desc, &secbuf, NULL);
 if (FAILED(hr)) goto nbs;

 hr = secbuf->QueryInterface(IID_IDirectSoundBuffer8 ,(void**)&dsb8);
 if (FAILED(hr)) goto nss;
 
 AddToLog("Effects:\r\n");
 CheckEffect(" - chorus: ",					GUID_DSFX_STANDARD_CHORUS, dsb8);
 CheckEffect(" - compressor: ",				GUID_DSFX_STANDARD_COMPRESSOR, dsb8);
 CheckEffect(" - distortion: ",				GUID_DSFX_STANDARD_DISTORTION, dsb8);
 CheckEffect(" - echo: ",					GUID_DSFX_STANDARD_ECHO, dsb8);
 CheckEffect(" - eargle: ",					GUID_DSFX_STANDARD_GARGLE, dsb8);
 CheckEffect(" - I3DL2 reverb: ",			GUID_DSFX_STANDARD_I3DL2REVERB, dsb8);
 CheckEffect(" - parametric equalizer: ",	GUID_DSFX_STANDARD_PARAMEQ, dsb8);
 CheckEffect(" - wave reverb: ",			GUID_DSFX_WAVES_REVERB, dsb8);
 
 if (!dsb8) dsb8->Release();
nss:;
 if (!secbuf) secbuf->Release();
nbs:;
 if (!prbuf) prbuf->Release();
ncs:;
 if (!ds) ds->Release();
ns:;
 CoUninitialize();
 return TRUE; 
}

void CheckEffect(char *effectname, GUID guid, LPDIRECTSOUNDBUFFER8 dsb8)
{
 DSEFFECTDESC dsEffect;
 memset(&dsEffect, 0, sizeof(DSEFFECTDESC));
 dsEffect.dwSize = sizeof(DSEFFECTDESC);
 dsEffect.dwFlags = 0;
 dsEffect.guidDSFXClass = guid;
 HRESULT hr;
 DWORD result;  // One element for each effect.

 AddToLog(effectname); 
 hr = dsb8->SetFX(1, &dsEffect, &result);

 if (!FAILED(hr))
 {
  switch (result)
  {
   case DSFXR_LOCHARDWARE:
	    AddToLog("hardware\r\n");
        break;
   case DSFXR_LOCSOFTWARE:
        AddToLog("software\r\n");
        break;
   case DSFXR_UNALLOCATED:
        AddToLog("unallocated\r\n");
        break;
   case DSFXR_FAILED:
        AddToLog("failed\r\n");
        break;
   case DSFXR_PRESENT:
        AddToLog("present\r\n");
        break;
  }
 }
 else
 {
  AddToLog(notsupported);
  AddToLog(end);
 }
}

LRESULT CALLBACK WaitWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   GetWindowRect(hDlg,&winbox);
	   SetWindowPos(hDlg,HWND_TOPMOST,GetSystemMetrics(SM_CXSCREEN)/2-(winbox.right-winbox.left)/2,GetSystemMetrics(SM_CYSCREEN)/2-(winbox.bottom-winbox.top)/2,winbox.right-winbox.left,winbox.bottom-winbox.top,SWP_NOSIZE);
       break;
  case WM_DESTROY:
	   KillTimer(hDlg,1);
	   break;
 }
 return FALSE;
}
 
LRESULT CALLBACK pWndProc18(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
 switch (message)
 {
  case WM_INITDIALOG:
	   EAX5SupportedTest(hDlg);
       break;
 }
 return FALSE;
}

void EAX5SupportedTest(HWND hWnd)
{
 logwnd = hWnd;
 //ViewFileInfo("eax.dll");

 DirectSoundEnumerate(EAX5SupportedTestCallback,(LPVOID)hWnd);
}

BOOL CALLBACK EAX5SupportedTestCallback(LPGUID lpGuid,LPCSTR lpcstrDescription,LPCSTR lpcstrModule,LPVOID lpContext)
{
 HWND hWnd = (HWND)lpContext;
 logwnd = hWnd;
 LPDIRECTSOUND ds = 0;
 LPDIRECTSOUNDBUFFER prbuf = 0,secbuf = 0;
 HRESULT hr = 0;
 DSBUFFERDESC desc;
 LPDIRECTSOUND3DLISTENER list = 0;
 LPDIRECTSOUND3DBUFFER sec3dbuf = 0;;
 LPKSPROPERTYSET propset = 0;
 ULONG support = 0;
 WAVEFORMATEX wf;
 bool testpass = false;

 if (lstrlen(lpcstrModule) == 0)
 {
  wsprintf(buf,"--- %s\r\n",lpcstrDescription);
  AddToLog(buf); 
 }
 else
 {
  wsprintf(buf,"--- %s [%s]\r\n",lpcstrDescription, lpcstrModule);
  AddToLog(buf); 
 }
 
 AddToLog("EAX 5 - ");

 CoInitialize(NULL);
 // для отвязки от DirectSoundCreate - делаем инициализацию через стандартный COM
 hr = CoCreateInstance(CLSID_DirectSound,
          NULL, 
          CLSCTX_INPROC_SERVER,
          IID_IDirectSound,
          (LPVOID*) &ds);
 if (FAILED(hr)) goto ns;

 hr = ds->Initialize(lpGuid);
 if (FAILED(hr)) goto ncs;
 
 hr = ds->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE);
 if (FAILED(hr)) goto ncs;
  
 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
 hr = ds->CreateSoundBuffer(&desc, &prbuf, NULL);
 if (FAILED(hr)) goto ncs;

 hr = prbuf->QueryInterface(IID_IDirectSound3DListener,(void**)&list);
 if (FAILED(hr)) goto nbs;

 ZeroMemory( &wf, sizeof(WAVEFORMATEX));
 wf.wFormatTag = WAVE_FORMAT_PCM;
 wf.nChannels = 1;
 wf.nSamplesPerSec = 11025;
 wf.nAvgBytesPerSec = 22050;
 wf.nBlockAlign = 2;
 wf.wBitsPerSample = 16;
 wf.cbSize = 0;

 ZeroMemory(&desc, sizeof(DSBUFFERDESC));
 desc.dwSize = sizeof(DSBUFFERDESC); 
 desc.dwFlags = DSBCAPS_CTRL3D;
 desc.dwBufferBytes = 1024;
 desc.lpwfxFormat = &wf;
 hr = ds->CreateSoundBuffer(&desc, &secbuf, NULL);
 if (FAILED(hr)) goto nls;

 hr = secbuf->QueryInterface(IID_IDirectSound3DBuffer,(void **)&sec3dbuf);
 if (FAILED(hr)) goto nss;
 
 hr = sec3dbuf->QueryInterface(IID_IKsPropertySet, (void**)&propset);
 if (FAILED(hr)) goto ns3s;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX50_Context,EAX5CONTEXT_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX50_FXSlot0,EAX5FXSLOT_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX50_FXSlot1,EAX5FXSLOT_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX50_FXSlot2,EAX5FXSLOT_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX50_FXSlot3,EAX5FXSLOT_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 hr = propset->QuerySupport(EAXPROPERTYID_EAX50_Source,EAX5SOURCE_ALLPARAMETERS,&support);
 if (FAILED(hr)) goto nps;

 if ((support & (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) != 
	            (KSPROPERTY_SUPPORT_GET|KSPROPERTY_SUPPORT_SET)) goto nps;

 // пытаемся инициализировать EAX5

 EAX50SESSIONPROPERTIES eaxSession;
 
 eaxSession.ulEAXVersion = EAX_50;
 eaxSession.ulMaxActiveSends = 4;

 hr = propset->Set(EAXPROPERTYID_EAX50_Context, EAX5CONTEXT_EAXSESSION, NULL, 0, &eaxSession, sizeof(EAX50SESSIONPROPERTIES));
 if (FAILED(hr)) goto nps;	 

 AddToLog(supported);
 AddToLog(end);
 AddToLog(end);

 testpass = true;

 TestEAX5Prop(propset);

nps:;
 if (!propset) propset->Release(); 
ns3s:
 if (!sec3dbuf) sec3dbuf->Release(); 
nss:;
 if (!secbuf) secbuf->Release();
nls:;
 if (!list) list->Release();
nbs:;
 if (!prbuf) prbuf->Release();
ncs:;
 if (!ds) ds->Release();
ns:;

 if (testpass == false)
 {
  AddToLog(notsupported);
  AddToLog(end);

  EAXUnifiedSupportedTest(5,hWnd,lpGuid);
 }

 AddToLog(end);
 CoUninitialize();
 
 return TRUE;
}


