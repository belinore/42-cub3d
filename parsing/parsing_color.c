#include "../includes/cub3d.h"

// This function checks if a string has only numbers.
// It makes sure text like "123" is valid number .
// If it has any letter like "12A3" → return 0
static int	is_valid_number(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// This function checks 3 RGB parts and saves them into color box.
// It makes sure all 3 are numbers and between 0 to 255.
// If check fails → show error .
// If ok → store red, green, blue .
static int	validate_convert_rgb(char **rgb_parts, t_color *color)
{
	int	red;
	int	green;
	int	blue;

	if (!is_valid_number(rgb_parts[0]) || !is_valid_number(rgb_parts[1])
		|| !is_valid_number(rgb_parts[2]))
		return (ft_error("Error: RGB values must be numeric (0-255)"));
	red = ft_atoi(rgb_parts[0]);
	green = ft_atoi(rgb_parts[1]);
	blue = ft_atoi(rgb_parts[2]);
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0
		|| blue > 255)
		return (ft_error("RGB values must be in range 0-255"));
	color->red = red;
	color->green = green;
	color->blue = blue;
	return (0);
}

// This function reads RGB values like "50,100,200".
// It splits them into 3 parts, checks format, and sends for number checking.
// If format is not 3 values → error .
// If ok → call validate_convert_rgb().
static int	parse_rgb_values(char *rgb_str, t_color *color)
{
	char	**rgb_parts;
	int		count;
	int		result;

	rgb_parts = ft_split(rgb_str, ',');
	if (!rgb_parts)
		return (ft_error("Error: Memory allocation faild for RGB parsing"));
	count = 0;
	while (rgb_parts[count])
		count++;
	if (count != 3)
	{
		free_split(rgb_parts);
		return (ft_error("Error: RGB format must be R,G,B only 3 values"));
	}
	result = validate_convert_rgb(rgb_parts, color);
	free_split(rgb_parts);
	return (result);
}

// This function takes a color line like "F 50,20,70" and gets the "50,20,70" part.
// It skips first word (F or C) and spaces.
// Returns RGB values as new string.
static char	*extract_rgb_string(char *line)
{
	char	*rgb_str;
	int		i;
	int		j;
	int		start;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	rgb_str = malloc(i - start + 1);
	if (!rgb_str)
		return (NULL);
	j = 0;
	while (start < i)
		rgb_str[j++] = line[start++];
	rgb_str[j] = '\0';
	return (rgb_str);
}

// This is the main function that reads floor or sky color from .cub file.
// Steps:
// 1. Take the RGB string using extract_rgb_string
// 2. Check and convert it to color using parse_rgb_values
// 3. If line starts with "F " → save as floor color
// 4. If line starts with "C " → save as sky color
// 5. Free memory at end for safety
// If any error → stop safely and show message
int	parse_color_line(t_game *game, char *line)
{
	char	*rgb_str;
	t_color	color;

	rgb_str = extract_rgb_string(line);
	if (!rgb_str)
	{
		destroy_textures(game);
		return (ft_error("Memory alocation failed for color parsing"));
	}
	if (parse_rgb_values(rgb_str, &color) != 0)
	{
		free_rgb_textures(game, rgb_str);
		return (-1);
	}
	if (ft_strncmp(line, "F ", 2) == 0)
		game->floor_color = color;
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->ceiling_color = color;
	else
	{
		free_rgb_textures(game, rgb_str);
		return (ft_error("Error: Invalid color line must start with 'F ' or 'C' "));
	}
	free(rgb_str);
	return (0);
}
