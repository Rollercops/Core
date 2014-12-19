#include	"SMaker.h"

bool		SMaker::_debug(false);
std::string	SMaker::_eol("");
bool		SMaker::_eolStd(false);
std::ofstream	SMaker::_log;

SMaker::SMaker()
	:_ss()
{
}

SMaker::~SMaker()
{
}

void		SMaker::setDebug(bool debug)
{
	SMaker::_debug = debug;
}

void		SMaker::setEol(std::string eol, bool std)
{
	SMaker::_eol = eol;
	SMaker::_eolStd = std;
}

bool		SMaker::initLog(std::string const & fnm)
{
	if (SMaker::_log.is_open())
		SMaker::closeLog();
	SMaker::_log.open(fnm.c_str());
	return SMaker::_log.is_open();
}

bool		SMaker::closeLog()
{
	SMaker::_log.close();
	return (!SMaker::_log.is_open());
}
/*
void		SMaker::set()
{
}

void		SMaker::clear()
{
}
*/
std::string &	SMaker::str(bool del)
{
	std::string*	str(new std::string(this->_ss.str()));
	
	if (del)
		delete this;
	return *str;
}

void		SMaker::print(bool line, bool del)
{
	std::cout << this->_ss.str();
	if (line)
		SMAKER_EOL(std::cout);
	if (del)
		delete this;
}

void		SMaker::debug(bool line, bool del)
{
	if (this->_debug)
	{
		std::cout << this->_ss.str();
		if (line)
			SMAKER_EOL(std::cout);
	}
	if (del)
		delete this;
}

void		SMaker::log(bool line, bool del)
{
	if (this->_log.is_open())
	{
		this->_log << this->_ss.str();
		if (line)
			SMAKER_EOL(this->_log);
	}
	if (del)
		delete this;
}

void		SMaker::failWithL(bool line)//previous without L 
{
	this->print(line, false);
	std::cerr << this->_ss.str();
	if (line)
		SMAKER_EOL(std::cerr);
	this->log(line, false);
	this->fail();
}

void		SMaker::fail()
{
	// error etc... management
	delete this;
	// exit/throw
}