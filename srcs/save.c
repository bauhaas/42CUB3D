/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:33:39 by bahaas            #+#    #+#             */
/*   Updated: 2021/02/25 16:11:34 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_bmp	fill_bmp(t_cub *cub)
{
	t_bmp	bmp;
	char	*signature;

	signature = "BM";
	bmp.signature = signature;
	bmp.reserved = 0;
	bmp.data_offset = 54;
	bmp.size_infoheader = 40;
	bmp.wid = cub->win.wid;
	bmp.hei = cub->win.hei;
	bmp.planes = 1;
	bmp.bpp = 32;
	bmp.size_file = bmp.data_offset + ((bmp.wid * bmp.hei) * 4);
	bmp.addr = (int *)cub->win.img.addr;
	bmp.padding_trash = 0;
	return (bmp);
}

void	write_bmp(int fd, t_bmp bmp)
{
	int x;
	int y;
	int	mix_planes_bpp;

	y = bmp.hei - 1;
	mix_planes_bpp = bmp.bpp;
	mix_planes_bpp = (mix_planes_bpp << 16) + bmp.planes;
	ft_putstr_fd(bmp.signature, fd);
	write(fd, &bmp.size_file, 4);
	write(fd, &bmp.reserved, 4);
	write(fd, &bmp.data_offset, 4);
	write(fd, &bmp.size_infoheader, 4);
	write(fd, &bmp.wid, 4);
	write(fd, &bmp.hei, 4);
	write(fd, &mix_planes_bpp, 4);
	write(fd, &bmp.padding_trash, 8);
	write(fd, &bmp.padding_trash, 8);
	write(fd, &bmp.padding_trash, 8);
	while (y >= 0)
	{
		x = 0;
		while (x < bmp.wid)
			write(fd, &(bmp.addr[(y * bmp.wid) + x++]), 4);
		y--;
	}
}

int		save_bmp(t_cub *cub)
{
	int		fd;
	t_bmp	bmp;

	fd = open("screen.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		return (is_error("Couldn't create bmp file"));
	bmp = fill_bmp(cub);
	write_bmp(fd, bmp);
	close(fd);
	return (1);
}
