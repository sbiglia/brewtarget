/*
 * style.h is part of Brewtarget, and is Copyright Philip G. Lee
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

#ifndef _STYLE_H
#define _STYLE_H
#include <exception>
#include <QString>
#include <QStringList>
#include "observable.h"
#include <QDomNode>
#include "BeerXMLElement.h"

class Style;

class Style : public Observable, public BeerXMLElement
{
public:

   Style();
   Style(const QDomNode& styleNode);

   friend bool operator<(Style &s1, Style &s2);
   friend bool operator==(Style &s1, Style &s2);

   enum Type { TYPELAGER=0, TYPEALE, TYPEMEAD, TYPEWHEAT, TYPEMIXED, TYPECIDER, NUMTYPES };

   virtual void fromNode(const QDomNode& node); // From BeerXMLElement
   virtual void toXml(QDomDocument& doc, QDomNode& parent); // From BeerXMLElement
   
   void setName( const QString& var );
   void setCategory( const QString& var );
   void setCategoryNumber( const QString& var );
   void setStyleLetter( const QString& var );
   void setStyleGuide( const QString& var );
   void setType( Type t );
   void setOgMin( double var );
   void setOgMax( double var );
   void setFgMin( double var );
   void setFgMax( double var );
   void setIbuMin( double var );
   void setIbuMax( double var );
   void setColorMin_srm( double var );
   void setColorMax_srm( double var );
   void setCarbMin_vol( double var );
   void setCarbMax_vol( double var );
   void setAbvMin_pct( double var );
   void setAbvMax_pct( double var );
   void setNotes( const QString& var );
   void setProfile( const QString& var );
   void setIngredients( const QString& var );
   void setExamples( const QString& var );

   QString getName() const;
   QString getCategory() const;
   QString getCategoryNumber() const;
   QString getStyleLetter() const;
   QString getStyleGuide() const;
   const Type getType() const;
   const QString getTypeString() const;
   double getOgMin() const;
   double getOgMax() const;
   double getFgMin() const;
   double getFgMax() const;
   double getIbuMin() const;
   double getIbuMax() const;
   double getColorMin_srm() const;
   double getColorMax_srm() const;
   double getCarbMin_vol() const;
   double getCarbMax_vol() const;
   double getAbvMin_pct() const;
   double getAbvMax_pct() const;
   QString getNotes() const;
   QString getProfile() const;
   QString getIngredients() const;
   QString getExamples() const;

private:

   // Mandatory fields.
   QString name;
   static const int version = 1;
   QString category;
   QString categoryNumber;
   QString styleLetter;
   QString styleGuide;
   Type type;
   double ogMin;
   double ogMax;
   double fgMin;
   double fgMax;
   double ibuMin;
   double ibuMax;
   double colorMin_srm;
   double colorMax_srm;
   
   // Optional fields
   double carbMin_vol;
   double carbMax_vol;
   double abvMin_pct;
   double abvMax_pct;
   QString notes;
   QString profile;
   QString ingredients;
   QString examples;

   void setDefaults();
   bool isValidType( const QString &str );
   static QStringList types;
};

inline bool StylePtrLt( Style* lhs, Style* rhs)
{
   return *lhs < *rhs;
}

inline bool StylePtrEq( Style* lhs, Style* rhs)
{
   return *lhs == *rhs;
}

struct Style_ptr_cmp
{
   bool operator()( Style* lhs, Style* rhs)
   {
      return *lhs < *rhs;
   }
};

struct Style_ptr_equals
{
   bool operator()( Style* lhs, Style* rhs )
   {
      return *lhs == *rhs;
   }
};

#endif //_STYLE_H
