/*
 * Copyright © 2016 athairus
 *
 * This file is part of MicroTimer.
 *
 * MicroTimer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "testitem.h"

#include <QSGSimpleRectNode>
#include <cstdlib>

TestItem::TestItem( QQuickItem *parent ) : QQuickItem( parent ) {
    setFlag( ItemHasContents );
}

QSGNode *TestItem::updatePaintNode( QSGNode *node, QQuickItem::UpdatePaintNodeData * ) {
    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>( node );

    if( !n ) {
        n = new QSGSimpleRectNode();
        n->setColor( QColor( "#202020" ) );
    }

    n->setRect( boundingRect() );
    update();
    return n;
}
