#include "wolf3d.h"

int		map_searcher(t_mlx * list)
{
	char	*str;
	char	*str2;
	int		fd;

	if (!(str = (char *)malloc(sizeof(char) * 12)))
		ft_fail("Error: Couldn't allocate memory.", list);
	ft_strcpy(str, "./maps/map");
	str2 = ft_itoa(MENU_MNB);
	str = ft_strcat(str, str2);
	free(str2);
	fd = open(str, O_RDONLY);
	free(str);
	if (fd < 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
