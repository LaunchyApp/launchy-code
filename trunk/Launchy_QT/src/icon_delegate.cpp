#include "icon_delegate.h"
#include <QPainter>
#include <QAbstractListModel>

IconDelegate::IconDelegate(QObject *parent)
: QAbstractItemDelegate(parent)
{

}

void IconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
						 const QModelIndex &index) const
{
	if (option.state & QStyle::State_Selected)
		painter->fillRect(option.rect, option.palette.highlight());

	QRect iconRect = option.rect;
	iconRect.setWidth(32);
	iconRect.setHeight(32);

	int fontHeight = painter->fontMetrics().height();
	QRect shortRect = option.rect;
	shortRect.setLeft(shortRect.left() + 38);
	shortRect.setBottom(shortRect.top() + fontHeight);

	QRect longRect = option.rect;
	longRect.setLeft(longRect.left() + 50);
	longRect.setTop(longRect.top() + fontHeight);

	painter->save();

	painter->drawText(shortRect,Qt::AlignTop, index.data(ROLE_SHORT).toString());

	painter->setPen(color);
	painter->setFont(QFont(family, size, weight, italics));

	QString full = index.data(ROLE_FULL).toString();
	full = painter->fontMetrics().elidedText(full, Qt::ElideLeft, longRect.width());
	painter->drawText(longRect, Qt::AlignTop, full);


	QIcon p = index.data(ROLE_ICON).value<QIcon>();
	p.paint(painter, iconRect);
	painter->restore();
}



QSize IconDelegate::sizeHint(const QStyleOptionViewItem & /* option */,
							 const QModelIndex & /* index */) const
{
	return QSize(10, 32);
}