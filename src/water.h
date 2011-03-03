/*
 * water.h is part of Brewtarget, and is Copyright Philip G. Lee
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

#ifndef _WATER_H
#define	_WATER_H

#include <string>
#include <exception>
#include <QDomNode>
#include "observable.h"
#include "BeerXMLElement.h"
#include <QString>

class Water;
class WaterException;

class Water : public Observable, public BeerXMLElement
{
   //Q_OBJECT
public:
   Water();
   Water( const QDomNode& waterNode );

   friend bool operator<(Water &w1, Water &w2);
   friend bool operator==(Water &w1, Water &w2);

   virtual void fromNode(const QDomNode& node); // From BeerXMLElement
   virtual void toXml(QDomDocument& doc, QDomNode& parent); // From BeerXMLElement
   
   QString getName() const;
   double getAmount_l() const;
   double getCalcium_ppm() const;
   double getBicarbonate_ppm() const;
   double getSulfate_ppm() const;
   double getChloride_ppm() const;
   double getSodium_ppm() const;
   double getMagnesium_ppm() const;
   double getPh() const;
   QString getNotes() const;

//public slots:
   void setName( const QString &var );
   void setAmount_l( double var );
   void setCalcium_ppm( double var );
   void setSulfate_ppm( double var );
   void setBicarbonate_ppm( double var );
   void setChloride_ppm( double var );
   void setSodium_ppm( double var );
   void setMagnesium_ppm( double var );
   void setPh( double var );
   void setNotes( const QString &var );
   
private:
   QString name;
   static const int version = 1;
   double amount_l;
   double calcium_ppm;
   double bicarbonate_ppm;
   double sulfate_ppm;
   double chloride_ppm;
   double sodium_ppm;
   double magnesium_ppm;
   double ph;
   QString notes;

   void setDefaults();
};

inline bool WaterPtrLt( Water* lhs, Water* rhs)
{
   return *lhs < *rhs;
}

inline bool WaterPtrEq( Water* lhs, Water* rhs)
{
   return *lhs == *rhs;
}

struct Water_ptr_cmp
{
   bool operator()( Water* lhs, Water* rhs)
   {
      return *lhs < *rhs;
   }
};

struct Water_ptr_equals
{
   bool operator()( Water* lhs, Water* rhs )
   {
      return *lhs == *rhs;
   }
};

#endif	/* _WATER_H */

