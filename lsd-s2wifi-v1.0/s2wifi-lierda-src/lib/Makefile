#
# @file Makefile
# @brief submakefile
#
# Copyright (C) 2006-2011, toby
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# @author toby.zhang <toby.chs@gmail.com>
# @date 2011-6-23 22:10:36
# @version 0.01
#
# This file is pary of makefile project.
#

include $(MAKEROOT)/common.mk

SRCS := $(wildcard *.c)

OBJS := $(patsubst %.c,%.o,$(SRCS))

.PHONY : all
all : $(OBJS)

