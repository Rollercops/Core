/**
 * \file SMaker.hpp
 * \author fonty_j
 * \version 1.1
 * \date june 2014
 */

#ifndef		__SMAKER_HH__
# define	__SMAKER_HH__

# include	"libs.h"

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
protected:
	/**
	 * \brief Debug flag.
	 *
	 * The _debug flag controle whether the debug function will print something or not.
	 */
	static bool	_debug;
	/**
	 * \brief Output end of line format.
	 *
	 * The _eol -end of line- string is printed at the end of every printed line on every output.
	 * It allow special output format such as using "<br/>" for HTML.
	 */
	static std::string	_eol;
	/**
	 * \brief Standard end of line printing flag.
	 *
	 * The _eolStd flag controle whether the standard end of line (std::cout) is printed at the end of a line or not. When printed, it is after the _eol string.
	 */
	static bool	_eolStd;
	/**
	 * \brief Log file.
	 *
	 * The _log is the file where the log() function output can be found. Used to track program activity.
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
	 * \brief Set _debug flag.
	 *
	 * Set the static _debug flag, controling the debuging output. Call this method once on program start
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
	static void	setEol(std::string eol, bool std);
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
	template<typename T>
	SMaker &	operator<<(T s)
	{
		this->_ss << s;
		return *this;
	}
/*	void	set();*/
/*	void	clear();*/
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
	void	print(bool line = true, bool del = true);
	/**
	 * \brief Send on output in debug state.
	 *
	 * Send content on standard output (std::cout) if the _debug flag is set, else does nothing.
	 * \param line : Whether the content should be followed by an end of line or not.
	 * \param del : Whether the SMaker will delete itself when done or not.
	 */
	void	debug(bool line = true, bool del = true);
	/**
	 * \brief Log the content.
	 *
	 * Send the content to the _log file if it is openned, else does nothing.
	 * \param line : Whether the content should be followed by an end of line or not.
	 * \param del : Whether the SMaker will delete itself when done or not.
	 */
	void	log(bool line = true, bool del = true);
	/**
	 * \brief Signal a failure.
	 *
	 * Send content on the standard output (std::cout), error output (std::cerr) and the _log file (if openned). Then cast a fail with the set behavior.
	 * \param line : Whether the content should be followed by an end of line or not.
	 * \param del : Whether the SMaker will delete itself when done or not.
	 */
	void	failWithL(bool line = true); //previous: without L
protected:
	void	fail();
};

/*
** TODO
** - add throw behavior on error
** - standardize exit/throw behavior, using static configuration
** - add file management (write to, consider read from)
** - ? add getLine function
** - add clear function
** - add set function
** - general TODO & blind log
** - ? thread safety
*/

/*
** LOG
** 1.1 :
** - fusioned eol and non-eol functions
** - added eol form controle
** - added auto-destruction controle
*/

#endif //	__SMAKER_HH__
