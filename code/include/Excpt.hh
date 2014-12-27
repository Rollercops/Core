/**
 * \file Excpt.hh
 * \author fonty_j
 * \version 1.0
 * \date july 2014
 */

#ifndef		__EXCPT_HH__
# define	__EXCPT_HH__

# include	"libs.hh"

/**
 * \class Excpt
 * \brief Exception utility utility.
 *
 * Utility class allowing exception standardisation over the program.
 */
class		Excpt : public std::exception
{
protected:
  /**
   * \brief What error happened.
   *
   * This might contain the description of the happening error.
   */
  std::string	_what;
  /**
   * \brief Where the error happened.
   *
   * This might contain a description of where the error is happening.
   */
  std::string	_wher;
private:
  /**
   * \brief Empty contructor, NOT implemented.
   */
  Excpt();
  /**
   * \brief Copy operator, NOT implemented.
   */
  Excpt &	operator=(Excpt const &);
public:
  /**
   * \brief Constructor.
   * \param what : The _what value.
   */
  Excpt(char const * what);
  /**
   * \brief Constructor.
   * \param what : The _what value.
   */
  Excpt(std::string const & what);
  /**
   * \brief Constructor.
   * \param what : The _what value.
   * \param wher : The _wher value.
   */
  Excpt(char const * what, char const * wher);
  /**
   * \brief Constructor.
   * \param what : The _what value.
   * \param wher : The _wher value.
   */
  Excpt(std::string const & what, std::string const & wher);
  /**
   * \brief Copy contructor.
   * \param e : The Excpt object to be copied.
   */
  Excpt(Excpt const & e);
  /**
   * \brief Destructor.
   */
  virtual ~Excpt() throw();
  /**
   * \brief Give the error description.
   *
   * Return the _what value, that might contain the description of the error.
   */
  virtual char const *	what() const throw();
  /**
   * \brief Tell where the error happened.
   *
   * Return the _wher value, that might contain the description of where the error happened.
   */
  char const *	wher() const throw();
};

#endif	//	__EXCPT_HH__
