#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "client.h"

static int	my_perror()
{
  write(2, "client take three parameter", 29);
  write(2, ", the pid of the server and the message\n", 41);
  write(2, "Pid must be more than 0", 23);
  return (ERROR);
}

static int	my_getnbr(char *str)
{
  int		i;
  int		c;
  int		nb;

  nb = 0;
  c = 1;
  i = 0;
  if (str[i] == '-')
    {
      i = i + 1;
      c = -c;
    }
  while (str[i])
    {
      nb = nb * 10 + str[i] - '0';
      i = i + 1;
    }
  return (nb * c);
}

static int	check_if_only_nbr(char *str)
{
  int		i;

  if (!str)
    return (ERROR);
  i = 0;
  while (str[i] >= '0' && str[i] <= '9')
    i = i + 1;
  if (str[i] == '\0')
    return (GOOD);
  if (my_getnbr(str) == 0)
    return (ERROR);
  return (ERROR);
}

static int	my_send(pid_t pid, char *str, int i, int a)
{
  if (!str)
    return (ERROR);
  i = -1;
  while (str[++i])
    {
      a = -1;
      while (++a < 8)
	{
	  if ((str[i] & 128) == 0)
	    {
	      if (((kill(pid, SIGUSR1))) == -1)
		return (write(2, "Kill failed\n", 12));
	    }
	  else
	    {
	      if ((kill(pid, SIGUSR2)) == -1)
		return (write(2, "Kill failed\n", 12));
	    }
	  str[i] = str[i] << 1;
	  usleep(20);
	}
    }
  return (GOOD);
}

int		main(int ac, char **ag)
{
  if (ac != 3 || check_if_only_nbr(ag[1]) == ERROR ||
      ag[1][0] == '\0')
    return (my_perror());
  my_send(my_getnbr(ag[1]), ag[2], 0, 0);
  return (0);
}
