/*
 * SIVolumeUnitSystem.h is part of Brewtarget, and is Copyright Philip G. Lee
 * (rocketman768@gmail.com), 2009-2011.
 *
 * Brewtarget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Brewtarget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SIVOLUMEUNITSYSTEM_H
#define _SIVOLUMEUNITSYSTEM_H

class SIVolumeUnitSystem;

#include <QMap>
#include "UnitSystem.h"

class SIVolumeUnitSystem : public UnitSystem
{
public:
   SIVolumeUnitSystem();
   QString displayAmount( double amount, Unit* units = 0 ); /* Inherited from UnitSystem */
   double qstringToSI( QString qstr ); /* Inherited from UnitSystem */
   Unit* thicknessUnit(); /* Inherited from UnitSystem */

private:
   static void ensureMapIsSetup();

   // Tries to find 'name' in the QMap 'nameToUnit'. Returns 0 on failure.
   static Unit* getUnit(const QString& name);

   static QMap<QString, Unit*> nameToUnit;
   static bool isMapSetup;
};

#endif /*_SIVOLUMEUNITSYSTEM_H*/
