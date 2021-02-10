/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:52:10 by clorin            #+#    #+#             */
/*   Updated: 2021/01/20 12:54:07 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void			fill_bmp_data(t_image img, int width, int height, int fd)
{
	int				i;
	int				j;
	char			*dst;

	i = height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < width)
		{
			dst = img.addr + (i * img.line_length + j * img.bits_per_pixel / 8);
			write(fd, dst, 4);
			j++;
		}
		i--;
	}
}

static void			fill_bmp_info(int width, int height, int fd)
{
	int				i;
	unsigned char	info[40];

	i = 0;
	while (i < 40)
		info[i++] = (unsigned char)0;
	info[0] = (unsigned char)40;
	i = width;
	info[4] = (unsigned char)(i % 256);
	info[5] = (unsigned char)(i / 256 % 256);
	info[6] = (unsigned char)(i / 256 / 256 % 256);
	info[7] = (unsigned char)(i / 256 / 256 / 256);
	i = height;
	info[8] = (unsigned char)(i % 256);
	info[9] = (unsigned char)(i / 256 % 256);
	info[10] = (unsigned char)(i / 256 / 256 % 256);
	info[11] = (unsigned char)(i / 256 / 256 / 256);
	info[12] = (unsigned char)1;
	info[14] = (unsigned char)32;
	write(fd, info, 40);
}

static void			fill_bmp_header(int width, int height, int fd)
{
	int				i;
	unsigned char	header[14];

	i = 0;
	while (i < 14)
		header[i++] = (unsigned int)0;
	header[0] = (unsigned char)0x42;
	header[1] = (unsigned char)0x4d;
	i = width * height * 4 + 54;
	header[2] = (unsigned char)(i % 256);
	header[3] = (unsigned char)(i / 256 % 256);
	header[4] = (unsigned char)(i / 256 / 256 % 256);
	header[5] = (unsigned char)(i / 256 / 256 / 256);
	header[10] = (unsigned char)54;
	write(fd, header, 14);
}

int					save_bmp(t_game *game)
{
	int				fd;

	fd = open(BMP_NAME, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		return (msg_err(OPEN_WRITE_FAIL, ""));
	fill_bmp_header(game->win.width, game->win.height, fd);
	fill_bmp_info(game->win.width, game->win.height, fd);
	fill_bmp_data(game->win.image, game->win.width, game->win.height, fd);
	if (close(fd) == -1)
		return (msg_err(CLOSE_FAIL, ""));
	if (!game->save)
		ft_putstr("Saved -> save.bmp\n");
	return (TRUE);
}
