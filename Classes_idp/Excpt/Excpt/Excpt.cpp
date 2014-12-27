#include	"Excpt.hh"

Excpt::Excpt(char const * what)
	:_what(what),
	_wher()
{
}

Excpt::Excpt(std::string const & what)
	:_what(what),
	_wher()
{
}

Excpt::Excpt(char const * what, char const * wher)
	:_what(what),
	_wher(wher)
{
}

Excpt::Excpt(std::string const & what, std::string const & wher)
	:_what(what),
	_wher(wher)
{
}

Excpt::Excpt(Excpt const & e)
	:_what(e._what),
	_wher(e._wher)
{
}

Excpt::~Excpt() throw()
{
}

char const *	Excpt::what() const throw()
{
	return this->_what.c_str();
}

char const *	Excpt::wher() const throw()
{
	return this->_wher.c_str();
}
