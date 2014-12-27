#include	"SMaker.hpp"

int		test();

int			main(int argc, char** argv)
{
	SMaker::setFailMode(SMaker::FAIL_THROW);
	SMaker::setDebug(true);
	SMaker::initLog("SMaker_test_log.txt");
	return test();
}

int		test()
{
	//test every function from SMaker
	if (false)
		return 1;
	return 0;
}
