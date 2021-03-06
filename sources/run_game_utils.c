/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:37:46 by hde-oliv          #+#    #+#             */
/*   Updated: 2021/09/02 19:19:48 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

void	move_player_up(t_game *game, int *moves)
{
	char	pos;

	if (valid_move(game, game->heroine_x, game->heroine_y - 1, &pos))
	{
		if (pos == 'C')
			game->coins--;
		if (pos != 'E')
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win, game->bg->ptr, \
									game->heroine_x * 16, game->heroine_y * 16);
			game->heroine_y--;
			(*moves)++;
		}
		else if (pos == 'E' && !game->coins)
			end_game(game);
	}
}

void	move_player_down(t_game *game, int *moves)
{
	char	pos;

	if (valid_move(game, game->heroine_x, game->heroine_y + 1, &pos))
	{
		if (pos == 'C')
			game->coins--;
		if (pos != 'E')
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win, game->bg->ptr, \
									game->heroine_x * 16, game->heroine_y * 16);
			game->heroine_y++;
			(*moves)++;
		}
		else if (pos == 'E' && !game->coins)
			end_game(game);
	}
}

void	move_player_left(t_game *game, int *moves)
{
	char	pos;

	if (valid_move(game, game->heroine_x - 1, game->heroine_y, &pos))
	{
		if (pos == 'C')
			game->coins--;
		if (pos != 'E')
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win, game->bg->ptr, \
									game->heroine_x * 16, game->heroine_y * 16);
			game->heroine_x--;
			(*moves)++;
		}
		else if (pos == 'E' && !game->coins)
			end_game(game);
	}
}

void	move_player_right(t_game *game, int *moves)
{
	char	pos;

	if (valid_move(game, game->heroine_x + 1, game->heroine_y, &pos))
	{
		if (pos == 'C')
			game->coins--;
		if (pos != 'E')
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win, game->bg->ptr, \
									game->heroine_x * 16, game->heroine_y * 16);
			game->heroine_x++;
			(*moves)++;
		}
		else if (pos == 'E' && !game->coins)
			end_game(game);
	}
}

int	valid_move(t_game *game, int wanted_x, int wanted_y, char *pos)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = -1;
	tmp = game->map->rows;
	while (i++ <= wanted_y && tmp)
	{
		j = -1;
		while (j++ <= wanted_x)
		{
			if (i == wanted_y && j == wanted_x)
			{
				if (((char *)(tmp->content))[j] != '1')
				{
					*pos = ((char *)(tmp->content))[j];
					if (((char *)(tmp->content))[j] == 'C')
						((char *)(tmp->content))[j] = '0';
					return (1);
				}
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
