
// #ifdef __GNUG__
// # pragma interface
// # pragma implementation
// #endif


#include <QApplication>
#include <iostream>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QStatusBar>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <thread>
#include "CommandInterpreter.hh"
#include "WgViewer3D.hh"
#include "SceneServer.hh"
#include "gtsDebug.hh"
#include "Port.hh"
#include "GraphicsWindow.hh"


using namespace std;



/*!
 * Nasłuchuje nowych połączeń i jeśli się pojawi, to uruchamia jego obsługę.
 * \param[in] Port - numer portu, na którym ma być prowadzony nasłuch
 *                   nowych połączeń.
 * \param[in] pScnServ - wskaźnik na obiekt serwera sceny roboczej
 *                   wykorzystywanej do obsługi nowego połączenia. 
 * \retval  0 - zakończono poprawnie pętlę nasłuchu,
 * \retval -1 - nie może utowrzyć gniazda dla nasłuchu,
 * \retval -2 - brak możliwości dowiązania do portu,
 * \retval -3 - błąd wykonania polecenie listen,
 * \retval -4 - błąd połączenia.
 */
int StartListening(int Port, SceneServer  *pScnServ)
{
  int  Socket4Listening; 
  int  Socket4Connect;

  struct sockaddr_in    cli_addr, serv_addr;
  socklen_t  ClAddrLen;



  if ((Socket4Listening = socket(AF_INET,SOCK_STREAM,0)) < 0) return -1;

  bzero((char *)&serv_addr,sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(Port);

  if (bind(Socket4Listening,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
    return -2;
  }

  ClAddrLen = sizeof(cli_addr);

   if (listen(Socket4Listening,5) < 0)  return -3;

   while (1) {
    Socket4Connect = accept(Socket4Listening,(struct sockaddr *)&cli_addr,&ClAddrLen);
    if (Socket4Connect < 0) return -4;
    pScnServ->Listing4InterpCmds(Socket4Connect);
    close(Socket4Connect);
   }
  close(Socket4Listening);
  return 0;
}



/*!
 * Funkcja wątku nasłuchiwania nowych połączeń.
 * \param[in] pScnServ - wskaźnik na obiekt serwera sceny roboczej
 *                   wykorzystywanej do obsługi nowego połączenia. 
 */
void *Listen4Connect(void *pScnServ)
{
  StartListening(PORT,reinterpret_cast<SceneServer*>(pScnServ));
  return nullptr;
}


/*!
 * Funkcja wątku obsługi poleceń, których efekt realizacji
 * ma być przekazany do serwera graficznego. Efektem tym
 * są nowe współrzędne obiektów sceny.
 * \param[in] pScnServ - wskaźnik na obiekt serwera sceny roboczej
 *                   wykorzystywanej, na które modyfikowane są położenia
 *                   obiektów sceny.
 */
void Fun_CmdsExecutor(SceneServer  *pScnServ)
{
  pScnServ->ExecCmds();
}




int main( int argc, char * argv[] ) 
{
  cout << "Port nasluchu: " << PORT << endl;

  
  SceneServer          ScnServ;

  std::thread          Th4CmdInterp(Fun_CmdsExecutor,&ScnServ);
  
  pthread_t            Thread_Receiving;

  pthread_create(&Thread_Receiving,NULL,Listen4Connect,&ScnServ);

  QApplication        App(argc,argv);
  MainWindow4Server   Win4Serv(&ScnServ.UseBuffScn());
  Win4Serv.setWindowTitle(QObject::tr("Serwer Graficzny"));
  Win4Serv.show();
  int Result = App.exec();

  ScnServ.FinishLooping();
  
  pthread_cancel(Thread_Receiving);
  Th4CmdInterp.join();
  pthread_join(Thread_Receiving,NULL);

  return Result;
}
