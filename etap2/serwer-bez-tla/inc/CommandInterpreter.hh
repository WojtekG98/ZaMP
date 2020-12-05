#ifndef COMMANDINTERPRETER_HH
#define COMMANDINTERPRETER_HH


#include "CommandBuffer.hh"
#include "BufferedScene.hh"

/*!
 * \brief Interpreter poleceń dla serwera
 *
 * Plik zawiera definicję klasy modelującej interpreter
 * poleceń dla serwera.
 */


/*!
 * \brief Interpreter poleceń dla serwera
 *
 * Modeluje interpreter poleceń wysyłanych do serwera.
 */
class CommandInterpreter {
   /*!
    * \brief Buffor poleceń, które ma wykonać serwer
    */
    CommandBuffer  _CmdBuff;
  /*!
   * \brief
   */
   bool _ContinueListening = true;
  private:
  /*!
   * \brief Rozpoznaje polecenie i je wykonuje.
   */
  bool InterpCmd(const std::string &rCmdLine, BufferedScene &rBScn);
  public:
   /*!
    * \brief Dodaje nowe polecenie do kolejki, które ma wykonać serwer.
    */
    void AddCmd(const char* sCmdLine);
   /*!
    * \brief Wykonuje polecenie, które jest jako pierwsze w kolejce.
    */
    bool ExecCmd(BufferedScene &rBScn);

   /*!
    * \brief
    */
    bool ShouldContinueListening() const { return _ContinueListening; }
   /*!
    * \brief
    */
    void MarkContinueListening() { _ContinueListening = true; }
   /*!
    * \brief
    */
    void CancelContinueListening() { _ContinueListening = false; }
};

#endif
