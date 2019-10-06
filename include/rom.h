/*
 * -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: 4; -*-
 * Author        : aerccu
 * Created       : 06.10.19
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ROM_H
#define ROM_H

#define RB_MAXDL            110
#define FS_LTE              30720000.0
#define CELLDROP_THRESHOLD  400.0

#include <vector>
#include <itpp/itbase.h>
#include <rtl-sdr.h>
#include "liblteutils.h"

class RomTables {
    public:
    PSSFD pssfd;
    PSSTD psstd;
    SSSFD sssfd;
    ModMap modmap;
};
extern RomTables ROMTABLES;

#endif // ROM_H