#include <QtGui>
#include <QApplication>
#include <sstream>
#include "R2.h"
//#include "sudoku.h"

const int X = 0; const int Y = 1;

const int GRID_LOCATION[2] = {20, 20};
const int CELL_SIZE = 50;
const int CELL_SPACING = CELL_SIZE;
const int CELL_FONT_SIZE = 20;

const int SOLVE_BUTTON_SIZE[2] = {80, 40};
const int SOLVE_BUTTON_LOCATION[2] = {CELL_SPACING*9 + GRID_LOCATION[X] + 20, CELL_SPACING*9 + GRID_LOCATION[Y] - SOLVE_BUTTON_SIZE[Y]};
const int FRAME_SIZE[2] = {SOLVE_BUTTON_LOCATION[X] + SOLVE_BUTTON_SIZE[X] + 20, SOLVE_BUTTON_LOCATION[Y] + SOLVE_BUTTON_SIZE[Y]+ 20};

int blahh [9][9] =  {{0, 0, 3, 8, 0, 0, 0, 0, 2}, 
			{0, 0, 5, 0, 2, 0, 0, 0, 0},
			{8, 0, 0, 4, 0, 0, 0, 0, 1},
			{0, 3, 7, 5, 0, 2, 0, 4, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 2, 0, 9, 0, 6, 1, 5, 0},
			{1, 0, 0, 0, 0, 9, 0, 0, 6},
			{0, 0, 0, 0, 6, 0, 4, 0, 0},
			{2, 0, 0, 0, 0, 5, 9, 0, 0}}; 

int main (int argc, char **argv) {
	QApplication app(argc, argv);

		
	QFrame *pqf = new QFrame();
	pqf -> setGeometry(50, 100, FRAME_SIZE[X], FRAME_SIZE[Y]);

	QValidator *validator = new QIntValidator(1, 9, pqf);

	// 2D array of QLineEdit pointers
	QLineEdit *cells[9][9];
	QFont cellFont; 	// Set cell font
	cellFont.setPointSize(CELL_FONT_SIZE);
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			cells[i][j] = new QLineEdit(pqf);
			cells[i][j]->setGeometry(GRID_LOCATION[X]+CELL_SPACING*j, GRID_LOCATION[Y]+CELL_SPACING*i, CELL_SIZE, CELL_SIZE);
			cells[i][j]->setAlignment(Qt::AlignCenter);
			cells[i][j]->setFont(cellFont);
			
			cells[i][j]->setMaxLength(1);			// Allow only 1 character
			cells[i][j]->setValidator(validator);		// Allow only digits to be entered
			
			// Fill cell with initial number
			std::stringstream ss;
			if (blahh[i][j] == 0)
				ss << "";
			else
				ss << blahh[i][j];
			cells[i][j]->setText(QString::fromStdString(ss.str()));
		}
	}
		
	// Create Solve button
	QPushButton *pButton = new QPushButton ("Solve!", pqf);
	pButton->setGeometry(SOLVE_BUTTON_LOCATION[X], SOLVE_BUTTON_LOCATION[Y], SOLVE_BUTTON_SIZE[X], SOLVE_BUTTON_SIZE[Y]);	
	//pButton-> setStyleSheet("border: none; margin: 0; padding: 0;");		//Change style of button
	pButton-> setParent(pqf);
		
	R2 *pr2 = new R2(&app);
	pr2 -> pOut = &cells;
//	pr2 -> pIn  = cells[2][2];
	QObject::connect(pButton, SIGNAL(pressed()),  pr2, SLOT(pushed()));
		
	pqf->show();

/*	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			delete(cells[i][j]);
	
		}
	}
*/
	return app.exec();
}


#include <QtGui>
#include <sstream>
#include "R2.h"
#include "sudoku.h"

R2::R2(QObject *parent): QObject(parent)
{}

void R2::copy() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::stringstream ss;
			ss << "";
			if ((*pOut)[i][j]->text() == ss.str().c_str()) {
				Out[i][j] = 0;
			} else {
				Out[i][j] = (*pOut)[i][j]->text().toInt(&ok, 10);
				(*pOut)[i][j]->setReadOnly(true);
				QFont newFont((*pOut)[i][j]->font());
				newFont.setBold(true);
				(*pOut)[i][j]->setFont(newFont);
			}
		}
		
	 }
}

void R2::pushed() {
	R2::copy();
	solve (Out, In);
	std::stringstream ss;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) {
				ss.str("");
				ss << In[i][j];
				(*pOut)[i][j]->setText(QString(ss.str().c_str()));
		}
	
	 }

}
#ifndef R2_H
#define R2_H

#include <QtGui>
class R2 : public QObject {
	Q_OBJECT

public: 
	R2(QObject *parent=0);
	QLineEdit *(*pOut)[9][9];
	QLineEdit *(*pIn)[9][9];
	int Out [9][9];
	int In [9][9];
	void copy();
	bool ok;

public slots:
	void pushed();
};

#endif

#include "R2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'R2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_R2[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       4,    3,    3,    3, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_R2[] = {
    "R2\0\0pushed()\0"
};

void R2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        R2 *_t = static_cast<R2 *>(_o);
        switch (_id) {
        case 0: _t->pushed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData R2::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject R2::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_R2,
      qt_meta_data_R2, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &R2::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *R2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *R2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_R2))
        return static_cast<void*>(const_cast< R2*>(this));
    return QObject::qt_metacast(_clname);
}

int R2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE