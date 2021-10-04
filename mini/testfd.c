/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroland <rroland@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 21:09:27 by rroland           #+#    #+#             */
/*   Updated: 2021/09/26 22:41:55 by rroland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

int fd = open("testfd", O_RDWR);
 if (fd == -1)
    return 1;
 printf("min fd: %d\n", fd);
 close(fd);
 return 0;
}