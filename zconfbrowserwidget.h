/*
 *  This file is part of qtzeroconf. (c) 2012 Johannes Hilden
 *  https://github.com/johanneshilden/qtzeroconf
 *
 *  qtzeroconf is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation; either version 2.1 of the
 *  License, or (at your option) any later version.
 *
 *  qtzeroconf is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
 *  Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with qtzeroconf; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#ifndef ZCONFBROWSERWIDGET_H
#define ZCONFBROWSERWIDGET_H

#include <QTreeWidget>

class ZConfBrowserWidgetPrivate;
class ZConfBrowserWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit ZConfBrowserWidget(QString serviceType, QWidget *parent = 0);
    explicit ZConfBrowserWidget(QWidget *parent = 0);
    ~ZConfBrowserWidget();

    void setCondensed(bool enabled);

protected slots:
    void addService(QString service);
    void removeService(QString service);

protected:
    ZConfBrowserWidgetPrivate *const d_ptr;

private:
    Q_DECLARE_PRIVATE(ZConfBrowserWidget);
};

#endif // ZCONFBROWSERWIDGET_H
