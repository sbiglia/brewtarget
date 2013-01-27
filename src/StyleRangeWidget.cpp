/*
 * StyleRangeWidget.cpp is part of Brewtarget, and is Copyright Philip G. Lee
 * (rocketman768@gmail.com), 2009-2013.
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

#include "StyleRangeWidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QPalette>
#include <QApplication>
#include <QRectF>
#include <QFont>

StyleRangeWidget::StyleRangeWidget(QWidget* parent)
   : QWidget(parent),
     _min(0.0),
     _max(1.0),
     _styleMin(0.25),
     _styleMax(0.75),
     _val(0.5),
     _valText("0.500"),
     _prec(3),
     _tickInterval(0),
     _smallTickInterval(0)
{
   setMinimumSize( 32, 16 );
   setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Fixed );
   repaint();
}

void StyleRangeWidget::setStyleRange( double min, double max )
{
   _styleMin = min;
   _styleMax = max;
   update();
}

void StyleRangeWidget::setRange( double min, double max )
{
   _min = min;
   _max = max;
   update();
}

void StyleRangeWidget::setValue(double value)
{
   _val = value;
   _valText = QString("%1").arg(_val, 0, 'f', _prec);
   update();
}

void StyleRangeWidget::setValue(QString const& value)
{
   _valText = value;
   _val = value.toDouble();
   update();
}

void StyleRangeWidget::setPrecision(int precision)
{
   _prec = precision;
   update();
}

void StyleRangeWidget::setTickMarks( double primaryInterval, double secondaryInterval )
{
   _tickInterval = primaryInterval;
   _smallTickInterval = secondaryInterval;
   
   update();
}

QSize StyleRangeWidget::sizeHint() const
{
   static const QSize hint(64,16);
   
   return hint;
}

void StyleRangeWidget::paintEvent(QPaintEvent* event)
{
   static const QPalette palette(QApplication::palette());
   static const int rectHeight = 16;
   static const int textWidth  = 48;
   static const int indWidth   = 4;
   static const QColor bgRectColor(QColor(121,201,121));//(palette.color(QPalette::Active, QPalette::Button));
   static const QColor fgRectColor(0,127,0);
   static const QColor indColor(QColor(255,255,255));
   static const QColor textColor(0,127,0);
   static const QFont textFont("Arial", 14, QFont::Black);
   
   QPainter painter(this);
   float rectWidth   = 512;
   float fgRectLeft  = rectWidth/(_max-_min) * (_styleMin-_min);
   float fgRectWidth = rectWidth/(_max-_min) * (_styleMax-_styleMin);
   float indX        = rectWidth/(_max-_min) * (_val-_min);
   float indLeft;
   
   // Make sure all coordinates are valid.
   fgRectLeft  = qBound( 0.f, fgRectLeft, rectWidth);
   fgRectWidth = qBound( 0.f, fgRectWidth, rectWidth-fgRectLeft);
   indX        = qBound( 0.f, indX, rectWidth-indWidth/2 );
   indLeft     = qBound( 0.f, indX-indWidth/2, rectWidth );
   
   painter.save();
      painter.setPen(Qt::NoPen);
      // Scale coordinates so that 'rectWidth' units == width()-textWidth-2 pixels.
      painter.scale( (width()-textWidth-2)/rectWidth, 1.0 );
      
      // Draw the background rectangle.
      painter.setBrush(bgRectColor);
      painter.drawRect( QRectF(0, 0, rectWidth, rectHeight) );
      
      // Draw the style "foreground" rectangle.
      painter.setBrush(fgRectColor);
      painter.drawRect( QRectF(fgRectLeft, 0, fgRectWidth, rectHeight) );
      
      // Draw the indicator.
      painter.setBrush(indColor);
      painter.drawRect( QRectF(indLeft, 0, indWidth, rectHeight) );
      
      // Draw the primary ticks.
      if( _tickInterval > 0.0 )
      {
         for( double currentTick = _min+_tickInterval; currentTick <= _max; currentTick += _tickInterval )
         {
            painter.translate( rectWidth/(_max-_min) * _tickInterval, 0);
            painter.drawLine( QPointF(0,0), QPointF(0,rectHeight) );
         }
      }
   painter.restore();
   
   painter.translate( width() - textWidth - 2, 0 );
   // Draw the text.
   painter.setPen(textColor);
   painter.setFont(textFont);
   painter.drawText( 0, 0, textWidth, 16, Qt::AlignRight | Qt::AlignVCenter, _valText );
}
