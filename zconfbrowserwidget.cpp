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

#include <QDebug>
#include "zconfbrowserwidget.h"
#include "zconfservicebrowser.h"

class ZConfBrowserWidgetPrivate
{
public:
    ZConfBrowserWidgetPrivate(ZConfBrowserWidget *widget)
        : q(widget),
          browser(0)
    {
        q->setColumnCount(6);
        QStringList headers;
        q->setHeaderLabels(headers << QObject::tr("Service")
                                   << QObject::tr("Domain")
                                   << QObject::tr("Host")
                                   << QObject::tr("Protocol")
                                   << QObject::tr("IP")
                                   << QObject::tr("Port"));

        q->setColumnWidth(0, 170);
    }

    void init(QString serviceType)
    {
        delete browser;
        browser = new ZConfServiceBrowser(q);
        type = serviceType;
        QObject::connect(browser, SIGNAL(serviceEntryAdded(QString)), q, SLOT(addService(QString)));
        QObject::connect(browser, SIGNAL(serviceEntryRemoved(QString)), q, SLOT(removeService(QString)));
        q->clear();
        browser->browse(type);
    }

    ZConfBrowserWidget  *const q;
    ZConfServiceBrowser *browser;
    QString              type;
};

/*!
    \class ZConfBrowserWidget

    \brief QTreeWidget-based widget for browsing and displaying available
    Zeroconf services on the local network.
 */

/*!
    Creates a ZConfBrowserWidget object using the provided service type.
 */
ZConfBrowserWidget::ZConfBrowserWidget(QString serviceType, QWidget *parent)
    : QTreeWidget(parent),
      d_ptr(new ZConfBrowserWidgetPrivate(this))
{
    d_ptr->init(serviceType);
}

/*!
    Convenience constructor that uses "_http._tcp" as service type.
 */
ZConfBrowserWidget::ZConfBrowserWidget(QWidget *parent)
    : QTreeWidget(parent),
      d_ptr(new ZConfBrowserWidgetPrivate(this))
{
    d_ptr->init("_http._tcp");
}

/*!
    Destroys the ZConfBrowserWidget object.
 */
ZConfBrowserWidget::~ZConfBrowserWidget()
{
    delete d_ptr;
}

/*!
    Enables/disables condensed list mode. In condensed mode, only service name,
    domain and host name is shown in the list.
 */
void ZConfBrowserWidget::setCondensed(bool enabled)
{
    for (int i = 3; i < 7; i++) setColumnHidden(i, enabled);
    setRootIsDecorated(!enabled);
}

void ZConfBrowserWidget::addService(QString service)
{
    QTreeWidgetItem *parent = 0;
    for (int i = 0; i < topLevelItemCount(); i++) {
        QTreeWidgetItem *item = topLevelItem(i);
        if (service == item->text(0)) {
            parent = item;
            break;
        }
    }
    ZConfServiceEntry serviceEntry = d_ptr->browser->serviceEntry(service);
    if (!serviceEntry.isValid())
        return;         // No service entry with that name found.
    if (!parent) {
        parent = new QTreeWidgetItem(this);
        parent->setText(0, service);
        parent->setText(1, serviceEntry.domain);
        parent->setText(2, serviceEntry.host);
        parent->setText(5, QString::number(serviceEntry.port));
    }

    QTreeWidgetItem *entry = new QTreeWidgetItem(parent);
    entry->setText(0, service);
    entry->setText(1, serviceEntry.domain);
    entry->setText(3, serviceEntry.protocolName());
    entry->setText(4, serviceEntry.ip);
    entry->setText(5, QString::number(serviceEntry.port));
}

void ZConfBrowserWidget::removeService(QString service)
{
    int count = topLevelItemCount();
    int i = 0;
    while (i < count) {
        QTreeWidgetItem *item = topLevelItem(i);
        if (service == item->text(0)) {
            delete item;
            --count;
        } else {
            ++i;
        }
    }
}
