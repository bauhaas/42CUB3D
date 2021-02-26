/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:33:39 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/26 18:02:48 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
** Fill all the required data to build a valid bmp file
*/

t_bmp	fill_bmp(t_cub *cub)
{
	t_bmp	bmp;

	bmp.signature = "BM";
	bmp.reserved = 0;
	bmp.data_offset = 54;
	bmp.size_infoheader = 40;
	bmp.wid = cub->win.wid;
	bmp.hei = cub->win.hei;
	bmp.planes = 1;
	bmp.bits_per_pixel = 32;
	bmp.size_file = bmp.data_offset + ((bmp.wid * bmp.hei) * 4);
	bmp.addr = (int *)cub->win.img.addr;
	bmp.option_null = 0;
	return (bmp);
}

/*
** Basic write : 1st header 2nd infoheader 3rd pixeldata on the same line
*/

void	write_bmp(int fd, t_bmp *bmp)
{
	int x;
	int y;

	ft_putstr_fd(bmp->signature, fd);
	write(fd, &bmp->size_file, 4);
	write(fd, &bmp->reserved, 4);
	write(fd, &bmp->data_offset, 4);
	write(fd, &bmp->size_infoheader, 4);
	write(fd, &bmp->wid, 4);
	write(fd, &bmp->hei, 4);
	write(fd, &bmp->planes, 2);
	write(fd, &bmp->bits_per_pixel, 2);
	write(fd, &bmp->option_null, 8);
	write(fd, &bmp->option_null, 8);
	write(fd, &bmp->option_null, 8);
	y = bmp->hei - 1;
	while (y >= 0)
	{
		x = -1;
		while (++x < bmp->wid)
			write(fd, &(bmp->addr[(y * bmp->wid) + x]), 4);
		y--;
	}
}

/*
** We create a bmp file and gonna fill the data for the header and infoheader
** then write them in the file.
*/

int		save_bmp(t_cub *cub)
{
	int		fd;
	t_bmp	bmp;

	fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		return (is_error("Couldn't create bmp file"));
	bmp = fill_bmp(cub);
	write_bmp(fd, &bmp);
	close(fd);
	return (1);
}
