/*
    Copyright (C) 2010 Michael Rahr

    This file is part of SqueezeRemote.

    SqueezeRemote is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    SqueezeRemote is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SqueezeRemote.  If not, see <http://www.gnu.org/licenses/>.
*/



#ifndef FLICKABLE_H
#define FLICKABLE_H

class QMouseEvent;
class QPoint;
class QWidget;

class FlickableTicker;
class FlickablePrivate;

class Flickable
{
public:

    Flickable();
    virtual ~Flickable();

    void setThreshold(int threshold);
    int threshold() const;
    void setOffset(int offset);

    void setAcceptMouseClick(QWidget *target);

    void handleMousePress(QMouseEvent *event);
    void handleMouseMove(QMouseEvent *event);
    void handleMouseRelease(QMouseEvent *event);

protected:

    virtual QPoint scrollOffset() const = 0;
    virtual void setScrollOffset1(const QPoint &offset) = 0;
    virtual void setEndScroll() =0;

private:
    void tick();

private:
    FlickablePrivate *d;
    friend class FlickableTicker;
};

#endif // FLICKABLE_H
