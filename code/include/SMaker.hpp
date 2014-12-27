/**
 * \file SMaker.hpp
 * \author fonty_j
 * \version 1.2
 * \date december 2014
 */

#ifndef		__SMAKER_HH__
# define	__SMAKER_HH__

# include	"libs.hh"
# include	"Excpt.hh"

/**
 * \def SMAKER_EOL(x)
 * \brief Send the end of line to an output.
 *
 * This is a SMaker class related macro.<br/>
 * This macro send the standardized end of line to the parameter output.
 * \param x : The output to end the line on.
 */
# define	SMAKER_EOL(x)	((SMaker::_eolStd) ? x << SMaker::_eol << std::endl : x << SMaker::_eol)

/**
 * \class SMaker
 * \brief String management utility.
 *
 * Utility class alowing compact string manipulation and behavior standardisation over the program.
 * Consider calling the static functions setDebug, setEol and initLog when program start. Don't forget closeLog when terminating it.
 */
class		SMaker
{
public:
  /**
   * \enum FAIL_MODE
   * \brief Failure modes enumeration.
   *
   * This enumeration contains values which correspond to each failure behavior.
   */
  enum FAIL_MODE
    {
      /**
       * \brief Cast an exit on failure.
       */
      FAIL_EXIT = 0,
      /**
       * \brief Throw an exception on failure.
       */
      FAIL_THROW = 1
    };
protected:
  /**
   * \brief Standard failure mode flag.
   *
   * The _stdFail flag controle the standard behavior on failure. Default value is FAIL_EXIT.
   */
  static FAIL_MODE	_failMode;
  /**
   * \brief Debug flag.
   *
   * The _debug flag controle whether the debug function will print something or not. Default value is false.
   */
  static bool	_debug;
  /**
   * \brief Output end of line format.
   *
   * The _eol -end of line- string is printed at the end of every printed line on every output. It allow special output format such as using "<br/>" for HTML. Default value is an empty end of line.
   */
  static std::string	_eol;
  /**
   * \brief Standard end of line printing flag.
   *
   * The _eolStd flag controle whether the standard end of line (std::endl) is printed at the end of a line or not. When printed, it is after the _eol string. The default value is true.
   */
  static bool	_eolStd;
  /**
   * \brief Log file.
   *
   * The _log is the file where the log() function output can be found. Used to track program activity. There si no default log file.
   */
  static std::ofstream	_log;
  /**
   * \brief String aggregator.
   *
   * The _ss stream is an internal object used to build the string before using it.
   */
  std::stringstream	_ss;
private:
  /**
   * \brief Copy contructor, NOT implemented.
   */
  SMaker(SMaker const &);
  /**
   * \brief Copy operator, NOT implemented.
   */
  SMaker &	operator=(SMaker const &);
public:
  /**
   * \brief Constructor.
   */
  SMaker();
  /**
   * \brief Destructor.
   */
  virtual ~SMaker();
  /**
   * \brief Set the failure behavior.
   *
   * Set the static _failMode flag, controling the failure behavior. Call this method once on program start.
   */
  static void	setFailMode(FAIL_MODE fm);
  /**
   * \brief Set debug mode.
   *
   * Set the static _debug flag, controling the debuging output. Call this method once on program start.
   * \param debug : The new _debug value.
   */
  static void	setDebug(bool debug);
  /**
   * \brief Set the End of Line format.
   *
   * Set the end of line format (_eol and _eolStd) on every output. Call this method once on program start.
   * \param eol : The new _eol value.
   * \param std : The new _stdEol value.
   */
  static void	setEol(std::string const & eol, bool std);
  /**
   * \brief Open the logfile
   *
   * Open the log file, controling the log output. Call this method once on program start. This function reset the file openned each time it is called.
   * \param fnm : The log file path.
   */
  static bool	initLog(std::string const & fnm);
  /**
   * \brief Close the log file.
   */
  static bool	closeLog();
  /**
   * \brief Set the content.
   */
  void		set(std::string const & s);
  /**
   * \brief Build the string with the following element.
   *
   * The << operator add the following element to the end of the _ss aggregator.
   * \param s : The element to be aggregated.
   */
  template<typename T>
  SMaker &	operator<<(T const & s)
  {
    this->_ss << s;
    return *this;
  }
  /**
   * \brief Clear the content.
   */
  void		clear();
  /**
   * \brief Give the content.
   *
   * Give the SMaker content as a new string.
   * \param del : Whether the SMaker will delete itself when done or not.
   * \return The content string.
   */
  std::string &	str(bool del = true);
  /**
   * \brief Send on standard output.
   *
   * Send content content on standard output (std::cout).
   * \param line : Whether the content should be followed by an end of line or not.
   * \param del : Whether the SMaker will delete itself when done or not.
   */
  void		print(bool line = true, bool del = true);
  /**
   * \brief Send on output in debug state.
   *
   * Send content on standard output (std::cout) if the _debug flag is set, else does nothing.
   * \param line : Whether the content should be followed by an end of line or not.
   * \param del : Whether the SMaker will delete itself when done or not.
   */
  void		debug(bool line = true, bool del = true);
  /**
   * \brief Log the content.
   *
   * Send the content to the _log file if it is openned, else does nothing.
   * \param line : Whether the content should be followed by an end of line or not.
   * \param del : Whether the SMaker will delete itself when done or not.
   */
  void		log(bool line = true, bool del = true);
  /**
   * \brief Signal and cast a failure.
   *
   * Send content on the standard output (std::cout), error output (std::cerr) and the _log file (if openned). Then cast a fail with the set behavior.
   * \param line : Whether the content should be followed by an end of line or not.
   */
  void		failWith(bool line = true);
protected:
  /**
   * \brief Cast a failure.
   *
   * Cast a failure following the set behavior.
   */
  void		fail();
};

/*
** TODO
** - general TODO & blind log
** - move the file & thread safety stuff to a dedicated File class, SMaker has no use for thread safety for itself making it irrelevant
** {
**   - add file management (write to, consider read from)
**   - ? add getLine function
**   - ? thread safety
** }
*/

/*
** LOG
** 1.1 :
** - fusioned eol and non-eol functions
** - added eol form controle
** - added auto-destruction controle
** 1.2 :
** - added throw failure behavior
** - standardized exit/throw behavior
** - added clear function
** - added set function
*/

#endif //	__SMAKER_HH__
