#include	"Excpt.hh"

int		test();

int		main()
{
  return test();
}

int		test()
{
  try
    {
      throw Excpt("Test error.");
    }
  catch (Excpt const & e)
    {
      std::cout << e.what() << std::endl;
      return 0;
    }
  return 1;
}
