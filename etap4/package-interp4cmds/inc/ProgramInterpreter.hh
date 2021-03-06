#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH

#include "Scene.hh"
#include "Set4LibInterfaces.hh"
#include <string>
#include <memory>
#include "xmlinterp.hh"
#include "Configuration.hh"
#include "Port.hh"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
#define LINE_SIZE 500
using namespace std;
using namespace xercesc;
#include <iostream>

/*!
 * \brief Klasa modelująca interpreter programu.
 */
class ProgramInterpreter {
   /*!
    * \brief obiekt _Sc zawierający Scene - zbiór obiektów mobilnych.
    */
    Scene   _Scn;
   /*!
    * \brief obiekt _LibManager zawierający Set4LibInterfaces - zbiór wtyczek.
    */
    Set4LibInterfaces _LibManager;
   /*!
    * \brief ibket Socket2Serv zawierajacy numer portu do komunikacji z serwerem.
    */
    int Socket2Serv = PORT;
  public:
   /*!
    * Czyta z pliku spis wtyczek i obiektów, a następnie dodaje je do _Scn i _LibManager.
    * \param sFileName - (\b we.) nazwa pliku z spisem wtyczek i obiektów.
    * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
    * \retval false - w przeciwnym przypadku.
    */
    bool Read_XML_Config(const char* sFileName){
	Configuration   rConfig;    	
	try {
        	XMLPlatformUtils::Initialize();
   	}
   	catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return false;
   	}

   	SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   	pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   	pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   	pParser->setFeature(XMLUni::fgXercesDynamic, false);
   	pParser->setFeature(XMLUni::fgXercesSchema, true);
   	pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   	pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   	DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   	pParser->setContentHandler(pHandler);
   	pParser->setErrorHandler(pHandler);

   	try {
     
     		if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       			cerr << "!!! Plik grammar/actions.xsd, '" << endl
            	     	     << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
                    	     << endl;
                	return false;
     		}
     	pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     	pParser->parse(sFileName);
   	}
   	catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   	}
   	catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   	}
   	catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
  	 }
	_LibManager = *rConfig.LibManager;
	_Scn = *rConfig.Scn;
	return true;
   	delete pParser;
   	delete pHandler;
   	return true;
    }
/*!
 * Czyta z pliku spis poleceń, a następnie wykonuje je.
 * \param FileName_Prog - (\b we.) nazwa pliku ze spisem poleceń.
 * \retval true - jeśli wczytanie oraz wykonanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
 bool ExecProgram(const char* FileName_Prog){
  istringstream IStrm4Cmds;
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;
  Cmd4Preproc += FileName_Prog;
  FILE* pProc = popen(Cmd4Preproc.c_str(), "r");
  if (!pProc) return false;
  while (fgets(Line,LINE_SIZE,pProc)) {
  	OTmpStrm << Line;
  }
  IStrm4Cmds.str(OTmpStrm.str());
  if(pclose(pProc) != 0) return false;

  string KeyWord;
  while(!IStrm4Cmds.fail()){
  	shared_ptr<LibInterface> Wtyczka;  
  	Interp4Command *wInterf;
  	IStrm4Cmds >> KeyWord;
  	if (IStrm4Cmds.fail())
    		break;
  
  	if (!_LibManager.Find(KeyWord.c_str(),Wtyczka)){
    		cout << "Nie znaleziono wtyczki: " << KeyWord << "!!!" << endl;
    		return false;
  	}
  	wInterf = Wtyczka->CreateCmd();
  	if (!wInterf->ReadParams(IStrm4Cmds)) return false;
  	cout << "---Parametry---" << endl;
  	wInterf->PrintCmd();
  }
  return true;
 }
/*!
 * Czyta z pliku spis wtyczek i obiektów, a następnie dodaje je do _Scn i _LibManager.
 * \param sFileName - (\b we.) nazwa pliku z spisem wtyczek i obiektów.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */ 
 bool SendSceneState2Server();
};    
#endif

