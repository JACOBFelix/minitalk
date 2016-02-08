#include <unistd.h>
#include <signal.h>

static void	my_putchar(char c)
{
  write(1, &c, 1);
}

static void	my_putnbr(int nb)
{
  int	i;

  i = 1;
  if (nb < 0)
    {
      nb = -nb;
      my_putchar('-');
    }
  while (nb / i > 9)
    i = i * 10;
  while (i > 0)
    {
      my_putchar((nb / i) % 10 + '0');
      i = i / 10;
    }
}

void		print_my_pid(void)
{
  my_putnbr(getpid());
  my_putchar('\n');
}

void		my_serv(int sig)
{
  static char	car = 0;
  static int	i = 0;

  car = car << 1;
  if (sig == SIGUSR2)
    car = car + 1;
  i = i + 1;
  if (i == 8)
    {
      my_putchar(car);
      i = 0;
    }
}

int		main(void)
{
  int		pid;

  print_my_pid();
  if ((signal(SIGUSR1, my_serv)) == SIG_ERR)
    {
      write(2, "Signal failed\n", 13);
      return (-1);
    }
  if ((signal(SIGUSR2, my_serv)) == SIG_ERR)
    {
      write(2, "Signal failed\n", 13);
      return (-1);
    }
  while (1)
    ;
}
