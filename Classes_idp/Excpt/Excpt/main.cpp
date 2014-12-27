#include	"Excpt.hh"

int			test();

int			main()
{
	return test();
}

int			test()
{
	try
	{
		throw Excpt("Test error.");
	}
	catch (Excpt const & e)
	{
		e.what();
		return 0;
	}
	return 1;
}
