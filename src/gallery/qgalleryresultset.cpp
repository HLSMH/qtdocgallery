/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtDocGallery module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qgalleryresultset_p.h"

#include "qgalleryresource.h"

QT_BEGIN_NAMESPACE

/*!
    \class QGalleryResultSet

    \ingroup gallery
    \since 1.1

    \inmodule QtGallery

    \brief The QGalleryResultSet class provides a gallery response which returns
    the results of a query.

    Implementations of QGalleryResultSet are used to return a result set in
    response to a QGalleryAbstractRequest.  A QGalleryResultSet provides
    functions for accessing identifying information and meta-data of items
    queried from a gallery.

    Only one item in a result set can be accessed at a time, so before
    information about an item can be accessed it must be selected using one of
    the fetch() functions.  When a new index is selected the result set will
    emit the currentIndexChanged() signal, and when the currently selected item
    changes the currentItemChanged() signal will be emitted.  If the
    currentIndex() contains a gallery item isValid() will return true, otherwise
    it will return false. Information identifying the current item in a result
    set can be accessed using the itemId(), itemUrl() and itemType() functions.

    For each meta-data property that can be addressed by a result set it will
    provide a unique key which queried by passing the property's name to the
    propertyKey() function.  Passing this key to the metaData() function will
    return the current item's value for that property.  Some result sets may
    contain editable meta-data values which can be changed using the
    setMetaData() function.  The attributes of a meta-data property such as
    whether it's writable can be queried from propertyAttributes() and the
    type of value that will returned by metaData() can be queried using
    propertyType().

    Whenever items are added or removed from a result set the itemsInserted()
    and itemsRemoved() signals will be emitted identifying where and how many
    items were changed.  If the meta-data of one or more items in a result set
    changes the metaDataChanged() signal will be emitted.
*/

/*!
    Constructs a new result set.

    The \a parent is passed to QGalleryAbstractResponse.
*/

QGalleryResultSet::QGalleryResultSet(QObject *parent)
    : QGalleryAbstractResponse(*new QGalleryResultSetPrivate, parent)
{
}


/*!
    \internal
*/

QGalleryResultSet::QGalleryResultSet(QGalleryResultSetPrivate &dd, QObject *parent)
    : QGalleryAbstractResponse(dd, parent)
{
}

/*!
    Destroys a result set.
*/

QGalleryResultSet::~QGalleryResultSet()
{

}

/*!
    \fn QGalleryResultSet::propertyKey(const QString &property) const

    Returns a positive integer key for a \a property name, or a negative
    integer if the property name is invalid.
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::propertyAttributes(int key) const

    Returns the attributes of the property identified by \a key.
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::propertyType(int key) const

    Returns the type of the property identified by \a key.
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::itemCount() const

    Returns the number of items in a result set.
    \since 1.1
*/

/*!
    Returns true if a result set is currently positioned on a valid item;
    otherwise returns false.

    \sa currentIndex()
    \since 1.1
*/

bool QGalleryResultSet::isValid() const
{
    const int index = currentIndex();

    return index >= 0 && index < itemCount();
}

/*!
    \fn QGalleryResultSet::itemId() const

    Returns the ID of the item a result set is currently positioned on.

    \sa currentIndex()
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::itemUrl() const

    Returns the URL of the item a result set is currently positioned on.

    \sa currentIndex(), resources()
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::itemType() const

    Returns the type of the item a result set is currently positioned on.

    \sa currentIndex()
    \since 1.1
*/

/*!
    Returns the resources of the item of a result set is currently positioned
    on.

    The default implementation returns a single resource with the URL of the
    current item, or an empty list if the current item doesn't have a valid
    URL.

    \sa currentIndex(), itemUrl()
    \since 1.1
*/

QList<QGalleryResource> QGalleryResultSet::resources() const
{
    QList<QGalleryResource> resources;

    const QUrl url = itemUrl();

    if (!url.isEmpty())
        resources.append(QGalleryResource(url));

    return resources;
}

/*!
    \fn QGalleryResultSet::metaData(int key) const

    Returns the meta-data value of the current item for \a key.
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::setMetaData(int key, const QVariant &value)

    Sets the meta-data \a value of the current item for \a key.

    Returns true if the value was changed successfully; otherwise returns
    false.
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::currentIndex() const

    Returns the index of the item a result set currently positioned on.

    \sa fetch()
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::fetch(int index)

    Moves the current position of a result set to an arbitrary \a index.

    Returns true if the result set is positioned on a valid item on return;
    otherwise returns false.
    \since 1.1
*/

/*!
    Moves the current position of the result set to the next item in the set.

    Returns true if the result set is positioned on a valid item on return;
    otherwise returns false.
    \since 1.1
*/

bool QGalleryResultSet::fetchNext()
{
    return fetch(currentIndex() + 1);
}

/*!
    Moves the current position of the result set to the previous item in the
    set.

    Returns true if the result set is positioned on a valid item on return;
    otherwise returns false.
    \since 1.1
*/

bool QGalleryResultSet::fetchPrevious()
{
    return fetch(currentIndex() - 1);
}

/*!
    Moves the current position of the result set to the first item in the set.

    Returns true if the result set is positioned on a valid item on return;
    otherwise returns false.
    \since 1.1
*/

bool QGalleryResultSet::fetchFirst()
{
    return fetch(0);
}

/*!
    Moves the current position of the result set to the last item in the set.

    Returns true if the result set is positioned on a valid item on return;
    otherwise returns false.
    \since 1.1
*/

bool QGalleryResultSet::fetchLast()
{
    return fetch(itemCount() - 1);
}

/*!
    \fn QGalleryResultSet::currentItemChanged()

    Signals that the item the result set is positioned on has changed.
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::currentIndexChanged(int index)

    Signals that a result set has been repositioned on a new \a index.
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::itemsInserted(int index, int count)

    Signals that \a count items have been inserted into a result set at
    \a index.
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::itemsRemoved(int index, int count)

    Signals that \a count items have been removed from a result set at
    \a index.
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::itemsMoved(int from, int to, int count)

    Signals that \a count items have been moved \a from an existing index \a to
    a new index.
    \since 1.1
*/

/*!
    \fn QGalleryResultSet::metaDataChanged(int index, int count, const QList<int> &keys)

    Signals that the meta-data identified by \a keys of \a count items starting
    at \a index has changed.
    \since 1.1
*/

QT_END_NAMESPACE
