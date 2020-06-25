#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include <QString>
#include <saveloadboard.h>

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    saveLoadBoard.dynamicLevelsMenu=0;              // zero dynamic board container
    saveLoadBoard.dynamicLevelsMenuStar.clear();    // = clear
    // --------------------------- basic bacgroud --------------------
    image = new QImage(15*48+16,13*48+14+60,QImage::Format_RGB32);   // 15 (+16) x 13 (+14 +60)
    image->fill(QColor(180,180,170));
    paintOnImage = new QPainter;
    paintOnImage->begin(image);

    // ------------------------ connect menu -------------------------
    connect(ui->actionWype_nij_cian,SIGNAL(triggered()),this,SLOT(clickFillWall()));
    connect(ui->actionWype_nij_pustym_blokiem,SIGNAL(triggered()),this,SLOT(clickFillEmpty()));
    connect(ui->actionPusta_ramka,SIGNAL(triggered()),this,SLOT(clickFillEmptyFrame()));
    connect(ui->actionPusty_rodek,SIGNAL(triggered()),this,SLOT(clickFillEmptyCenter()));
    connect(ui->actionMa_a_pusta_ramka,SIGNAL(triggered()),this,SLOT(clickFillSmallEmptyFrame()));
    connect(ui->actionUsu_aktualn_plansz,SIGNAL(triggered()),this,SLOT(clickDeleteActiveBoard()));
    connect(ui->actionZapisz_plik_z_planszami,SIGNAL(triggered()),this,SLOT(clickSaveFile()));
    connect(ui->actionOtw_rz_plik_z_planszami,SIGNAL(triggered()),this,SLOT(clickOpenFile()));

    //-------------------- reset counter elements at board ------------
    counterHole = 0;
    counterSteve = 0;
    counterDiamond = 0;
    counterDiamondWithoutHole = 0;

    SaveLoadBoard myAllBoard;
    selectedMenu = 0;               //select position -> empty  (0=wall 1=empty 2=door etc)
    myEditorBoard.clear();
    showEditorBoard();
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

//----------------------------------------- My function mySprintf -------------------------------------------
template<typename ... Args>
QString mySprintf(const char * format,Args ... a)       // use: s = mySpring("Its %d %s .",12,"May");
{                                                       //      s = "12 May .";
    char scream[255];
    sprintf(scream,format,a ...);
    return scream;
}
//----------------------------------------- My function mySprintf -------------------------------------------

void MainWindow2::counterElementsAtBoard(unsigned short int & diamonds, unsigned short int & holes, bool & steve, bool & diamondsWithoutHole)
{
    diamonds=0;
    holes=0;
    steve=0;
    diamondsWithoutHole=0;
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            if (myEditorBoard.get(y,x)==OneCell::CELL_DIAMOND || myEditorBoard.get(y,x)==OneCell::CELL_DIAMONDinHOLE)
            {
                diamonds++;
                if (myEditorBoard.get(y,x)==OneCell::CELL_DIAMOND)
                {
                    diamondsWithoutHole=1;
                }
            }
            if (myEditorBoard.get(y,x)==OneCell::CELL_HOLE || myEditorBoard.get(y,x)==OneCell::CELL_DIAMONDinHOLE || myEditorBoard.get(y,x)==OneCell::CELL_STEVEinHOLE)
            {
                holes++;
            }
            if (myEditorBoard.get(y,x)==OneCell::CELL_STEVE || myEditorBoard.get(y,x)==OneCell::CELL_STEVEinHOLE)
            {
                steve=1;
            }
        }
    }
}

void MainWindow2::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(10,10 + ui->menubar->height(),*image);
    painter.end();
}

void MainWindow2::myMouseClick(QMouseEvent *event)
{
    bool isChanged=false;
    if(event->buttons() == Qt::LeftButton)
    {
        short int a=getAmenuClick(event->x(),event->y());
        if (a!=-1){
            selectedMenu = a;
        }
        short int x,y;
        getXboardClick(x,y,event->x(),event->y());
        if (x!=-1 && y!=-1)
        {
            // select wall
            if (selectedMenu==0)
            {
                myEditorBoard.set(y,x,OneCell::CELL_WALL);
                isChanged=true;
            }
            // select door
            if (selectedMenu==2)
            {
                isChanged=true;
                myEditorBoard.set(y,x,OneCell::CELL_DOOR);
            }
            // select empty
            if (selectedMenu==1)
            {
                isChanged=true;
                if (myEditorBoard.get(y,x)==OneCell::CELL_STEVEinHOLE)
                {
                    myEditorBoard.set(y,x,OneCell::CELL_STEVE);
                }
                else
                    if (myEditorBoard.get(y,x)==OneCell::CELL_DIAMONDinHOLE)
                    {
                        myEditorBoard.set(y,x,OneCell::CELL_DIAMOND);
                    }
                    else
                    {
                        myEditorBoard.set(y,x,OneCell::CELL_EMPTY);
                    }
            }
            // select steve
            if (selectedMenu==3)
            {
                isChanged=true;
                //delete old steve
                if (myEditorBoard.pos_Steve_x!=-1)
                {
                    myEditorBoard.set(myEditorBoard.pos_Steve_y,myEditorBoard.pos_Steve_x,myEditorBoard.get(myEditorBoard.pos_Steve_y,myEditorBoard.pos_Steve_x)==OneCell::CELL_STEVE?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
                }
                //add new steve
                if (myEditorBoard.get(y,x)==OneCell::CELL_HOLE || myEditorBoard.get(y,x)==OneCell::CELL_DIAMONDinHOLE)
                {
                    myEditorBoard.set(y,x,OneCell::CELL_STEVEinHOLE);
                }
                else
                {
                    myEditorBoard.set(y,x,OneCell::CELL_STEVE);
                }
            }
            // select hole
            if (selectedMenu==4)
            {
                isChanged=true;
                if (myEditorBoard.get(y,x)==OneCell::CELL_STEVE || myEditorBoard.get(y,x)==OneCell::CELL_STEVEinHOLE)
                {
                    myEditorBoard.set(y,x,OneCell::CELL_STEVEinHOLE);
                }
                else
                    if (myEditorBoard.get(y,x)==OneCell::CELL_DIAMOND || myEditorBoard.get(y,x)==OneCell::CELL_DIAMONDinHOLE)
                    {
                        myEditorBoard.set(y,x,OneCell::CELL_DIAMONDinHOLE);
                    }
                    else
                    {
                        myEditorBoard.set(y,x,OneCell::CELL_HOLE);
                    }
            }
            // select diamond
            if (selectedMenu==5)
            {
                isChanged=true;
                if (myEditorBoard.get(y,x)==OneCell::CELL_HOLE || myEditorBoard.get(y,x)==OneCell::CELL_STEVEinHOLE || myEditorBoard.get(y,x)==OneCell::CELL_DIAMONDinHOLE)
                {
                    myEditorBoard.set(y,x,OneCell::CELL_DIAMONDinHOLE);
                }
                else
                {
                    myEditorBoard.set(y,x,OneCell::CELL_DIAMOND);
                }
            }
            // select arrow up
            if (selectedMenu==6)
            {
                isChanged=true;
                //delete old arrow
                if (myEditorBoard.pos_arrow_x!=-1)
                {
                    myEditorBoard.set(myEditorBoard.pos_arrow_y,myEditorBoard.pos_arrow_x,OneCell::CELL_EMPTY);
                }
                myEditorBoard.set(y,x,OneCell::CELL_ARROW_UP);
            }
            // select arrow down
            if (selectedMenu==7)
            {
                isChanged=true;
                //delete old arrow
                if (myEditorBoard.pos_arrow_x!=-1)
                {
                    myEditorBoard.set(myEditorBoard.pos_arrow_y,myEditorBoard.pos_arrow_x,OneCell::CELL_EMPTY);
                }
                myEditorBoard.set(y,x,OneCell::CELL_ARROW_DOWN);
            }
            // select arrow left
            if (selectedMenu==8)
            {
                isChanged=true;
                //delete old arrow
                if (myEditorBoard.pos_arrow_x!=-1)
                {
                    myEditorBoard.set(myEditorBoard.pos_arrow_y,myEditorBoard.pos_arrow_x,OneCell::CELL_EMPTY);
                }
                myEditorBoard.set(y,x,OneCell::CELL_ARROW_LEFT);
            }
            // select arrow right
            if (selectedMenu==9)
            {
                isChanged=true;
                //delete old arrow
                if (myEditorBoard.pos_arrow_x!=-1)
                {
                    myEditorBoard.set(myEditorBoard.pos_arrow_y,myEditorBoard.pos_arrow_x,OneCell::CELL_EMPTY);
                }
                myEditorBoard.set(y,x,OneCell::CELL_ARROW_RIGHT);
            }
        }
        int nrCurrentIndex = ui->comboBox->currentIndex();
        if (nrCurrentIndex!=-1 && isChanged)
        {
            int nrCurrentIndex = ui->comboBox->currentIndex();
            ui->comboBox->setItemText(nrCurrentIndex,mySprintf("Level %d *",nrCurrentIndex+1));
        }
    }
    showEditorBoard();
}

void MainWindow2::mousePressEvent(QMouseEvent *event)
{
    myMouseClick(event);
}

void MainWindow2::mouseMoveEvent(QMouseEvent *event)
{
    if (getAmenuClick(event->x(),event->y())==-1)
    {
        myMouseClick(event);
    }
}

short int MainWindow2::getAmenuClick(unsigned short int x, unsigned short y)
{
    for (unsigned short int i=0; i<10; i++)
    {
        if (x>=10+35+51*i && x<=10+35+51*i+48 && y>=6+10+ui->menubar->height() && y<=54+10+ui->menubar->height())
        {
            return i;
        }
    }
    return -1;
}

void MainWindow2::getXboardClick(short int & x, short int & y, unsigned short int xInForm, unsigned short int yInForm)
{
    x=-1;
    y=-1;
    const unsigned short int position_board=60;
    for (unsigned short int yyy=0; yyy<13; yyy++)
    {
        for (unsigned short int xxx=0; xxx<15; xxx++)
        {
            if (xInForm>=10+xxx*49+1 && xInForm<=10+xxx*49+1+48 && yInForm>=position_board+yyy*49+1+10+ui->menubar->height() && yInForm<=position_board+yyy*49+1+48+10+ui->menubar->height())
            {
                x=xxx;
                y=yyy;
            }
        }
    }
}

void MainWindow2::clickFillWall()
{
    int nrCurrentIndex = ui->comboBox->currentIndex();
    if (nrCurrentIndex!=-1)
    {
        int nrCurrentIndex = ui->comboBox->currentIndex();
        ui->comboBox->setItemText(nrCurrentIndex,mySprintf("Level %d *",nrCurrentIndex+1));
    }
    myEditorBoard.clearToWall();
    showEditorBoard();
}

void MainWindow2::clickFillEmpty()
{
    int nrCurrentIndex = ui->comboBox->currentIndex();
    if (nrCurrentIndex!=-1)
    {
        int nrCurrentIndex = ui->comboBox->currentIndex();
        ui->comboBox->setItemText(nrCurrentIndex,mySprintf("Level %d *",nrCurrentIndex+1));
    }
    myEditorBoard.clear();
    showEditorBoard();
}

void MainWindow2::clickFillEmptyFrame()
{
    int nrCurrentIndex = ui->comboBox->currentIndex();
    if (nrCurrentIndex!=-1)
    {
        int nrCurrentIndex = ui->comboBox->currentIndex();
        ui->comboBox->setItemText(nrCurrentIndex,mySprintf("Level %d *",nrCurrentIndex+1));
    }
    myEditorBoard.clear();
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            if (y>0 && y<12 && x>0 && x<14)
            {
                myEditorBoard.set(y,x,OneCell::CELL_EMPTY);
            }
            else
            {
                myEditorBoard.set(y,x,OneCell::CELL_WALL);
            }
        }
    }
    showEditorBoard();
}

void MainWindow2::clickFillEmptyCenter()
{
    int nrCurrentIndex = ui->comboBox->currentIndex();
    if (nrCurrentIndex!=-1)
    {
        int nrCurrentIndex = ui->comboBox->currentIndex();
        ui->comboBox->setItemText(nrCurrentIndex,mySprintf("Level %d *",nrCurrentIndex+1));
    }
    myEditorBoard.clear();
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            if (y>2 && y<10 && x>3 && x<11)
            {
                myEditorBoard.set(y,x,OneCell::CELL_EMPTY);
            }
            else
            {
                myEditorBoard.set(y,x,OneCell::CELL_WALL);
            }

        }
    }
    showEditorBoard();
}

void MainWindow2::clickFillSmallEmptyFrame()
{
    int nrCurrentIndex = ui->comboBox->currentIndex();
    if (nrCurrentIndex!=-1)
    {
        int nrCurrentIndex = ui->comboBox->currentIndex();
        ui->comboBox->setItemText(nrCurrentIndex,mySprintf("Level %d *",nrCurrentIndex+1));
    }
    myEditorBoard.clear();
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            if ((y==3 && x>3 && x<11)||(y==9 && x>3 && x<11)||(x==4 && y>3 && y<9)||(x==10 && y>3 && y<9))
            {
                myEditorBoard.set(y,x,OneCell::CELL_WALL);
            }
            else
            {
                myEditorBoard.set(y,x,OneCell::CELL_EMPTY);
            }

        }
    }
    showEditorBoard();
}

void MainWindow2::clickDeleteActiveBoard()
{
    int nrCurrentIndex = ui->comboBox->currentIndex();
    if (nrCurrentIndex==-1)
    {
        QMessageBox::critical(this, "Zestaw jest pusty!", "Zestaw nie posiada żadnych plansz." );
        return;
    }
    // ---------- removing the board from the board store --------
    saveLoadBoard.deleteBoard(nrCurrentIndex);

    // ---- removing the name "level x+1 from the comboBox -------
    saveLoadBoard.dynamicLevelsMenu--;
    saveLoadBoard.dynamicLevelsMenuStar.remove(nrCurrentIndex); //delete

    // ---------- clear all levels of comboBox and add all -------
    ui->comboBox->clear();
    unsigned short int levels;
    for (levels=0; levels<saveLoadBoard.dynamicLevelsMenu;levels++)
    {
        ui->comboBox->addItem(mySprintf("Level %d %c",levels+1,saveLoadBoard.dynamicLevelsMenuStar[levels]));
    }

    //    if (ui->comboBox->count()>0)
    //    {
    ui->comboBox->setCurrentIndex(0);
    //    }
    myEditorBoard.load(saveLoadBoard.getBoard(0));
    showEditorBoard();
    QMessageBox::about(this, "Usunięto planszę!", mySprintf("Plansza [Level %d] została usunięta z zestawu!\nPlanszom znajdującym się za nią nadano nową numerację.",nrCurrentIndex+1));
}

void MainWindow2::clickSaveFile()
{
    if (saveLoadBoard.isEmpty())
    {
        QMessageBox::about(this, "Nie zapisano!", "Brak dodanych plansz w zestawie.");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Zapisz plik z planszami", "/home/sokoban/plansza.sbm","Plik SokobanMax (*.sbm)");
    if (filePath!=NULL)
    {
        if (saveLoadBoard.saveToFile(filePath)!=0)
        {
            QMessageBox::critical(this, "Nie zapisano!", "Podczas zapisu wystąpił błąd!");
        }
        else
        {
            QMessageBox::about(this, "Zestaw zapisany!", "Poprawnie zapisano zestaw plansz do pliku.");
        }
    }
}

void MainWindow2::clickOpenFile()
{
    QMessageBox msg;
    msg.setText("Otwierasz nowy plik więc Twoja aktualna praca w edytorze plansz zostanie utracona!");
    msg.setInformativeText("Czy na pewno chcesz otworzyć nowy plik?");
    msg.setStandardButtons(QMessageBox::Open | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Cancel);
    int ret = msg.exec();
    switch (ret)
    {
        case QMessageBox::Open :
        {
            QString filePath = QFileDialog::getOpenFileName(this, "Otwórz plik z planszami", "/home/sokoban/plansza.sbm","Plik SokobanMax (*.sbm)");
            if (filePath==NULL)
            {
                return;
            }
            // --- read file ---
            unsigned short int errorCode=saveLoadBoard.openFromFile(filePath);
            if (errorCode!=0)
            {
                switch (errorCode) {
                    case 1 : QMessageBox::critical(this, "Błąd odczytu!", "Plik nie zawiera plansz SokobanMax lub jest uszkodzony!");break;
                    case 2 : QMessageBox::critical(this, "Błąd odczytu!", "Podczas odczytu pliku z planszami wystąpił błąd!");break;
                }
            }
            else
            {
                myEditorBoard.clear();
                saveLoadBoard.dynamicLevelsMenu = saveLoadBoard.getCounterLevels();
                saveLoadBoard.dynamicLevelsMenuStar.clear();
                ui->comboBox->clear();
                for (unsigned short int i=0;i<saveLoadBoard.getCounterLevels();i++)
                {
                    ui->comboBox->addItem(mySprintf("Level %d", i+1));
                    saveLoadBoard.dynamicLevelsMenuStar.push_back(' ');
                }
                myEditorBoard.load(saveLoadBoard.getBoard(0));  //display the first board
                showEditorBoard();
                ui->comboBox->setCurrentIndex(0);               //active first level in comboBox
                QMessageBox::about(this, "Zestaw odczytany!", "Plik z planszami załadowano poprawnie!");
            }
            break;
        }
    }
}

void MainWindow2::showEditorBoard()
{
    const unsigned short int position_board=60;
    paintOnImage->fillRect(QRect(0,0,15*48+16,position_board),QColor(255,180,170));
    paintOnImage->fillRect(QRect(0,position_board,15*48+16,13*48+14+position_board),QColor(180,180,170));
    QRectF source(0, 0, 47, 47);

    //-------------------------- drawing a grid --------------------------
    paintOnImage->setPen(QColor(0,0,0));
    for (unsigned short int y=0; y<14; y++)
    {
        paintOnImage->drawLine(0,y*49+position_board,15*48+16,y*49+position_board);
    }
    for (unsigned short int x=0; x<16; x++)
    {
        paintOnImage->drawLine(x*49,position_board,x*49,13*48+14+position_board);
    }

    //----------------------- drawing a menu grid ------------------------
    paintOnImage->setPen(QColor(255,215,215));
    for (unsigned short int a=0; a<2; a++)
    {
        paintOnImage->drawLine(32,a*51+3,32+10*48+32,a*51+3);
        paintOnImage->drawLine(32,a*51+4,32+10*48+32,a*51+4);
        paintOnImage->drawLine(32,a*51+5,32+10*48+32,a*51+5);
    }
    for (unsigned short int a=0; a<11; a++)
    {
        paintOnImage->drawLine(32+51*a,5,32+51*a,54);
        paintOnImage->drawLine(33+51*a,5,33+51*a,54);
        paintOnImage->drawLine(34+51*a,5,34+51*a,54);
    }

    //----------------------- drawing a menu object ----------------------
    paintOnImage->drawImage(QRectF(35     ,6,48,48),QImage(":/img/wall.png"),source);
    paintOnImage->drawImage(QRectF(35+51*2,6,48,48),QImage(":/img/door.png"),source);
    paintOnImage->drawImage(QRectF(35+51*3,6,48,48),QImage(":/img/steve.png"),source);
    paintOnImage->drawImage(QRectF(35+51*4,6,48,48),QImage(":/img/hole.png"),source);
    paintOnImage->drawImage(QRectF(35+51*5,6,48,48),QImage(":/img/diamond.png"),source);
    paintOnImage->drawImage(QRectF(35+51*6,6,48,48),QImage(":/img/arrowUp.png"),source);
    paintOnImage->drawImage(QRectF(35+51*7,6,48,48),QImage(":/img/arrowDown.png"),source);
    paintOnImage->drawImage(QRectF(35+51*8,6,48,48),QImage(":/img/arrowLeft.png"),source);
    paintOnImage->drawImage(QRectF(35+51*9,6,48,48),QImage(":/img/arrorRight.png"),source);
    counterElementsAtBoard(counterDiamond,counterHole,counterSteve,counterDiamondWithoutHole);
    paintOnImage->setPen(QColor(0,0,0));
    paintOnImage->drawText(35+51*3,52,QString::number(counterSteve));
    paintOnImage->drawText(35+51*4,52,QString::number(counterHole));
    paintOnImage->drawText(35+51*5,52,QString::number(counterDiamond));

    //------------------- drawing a frame at selected menu ---------------
    paintOnImage->setPen(QColor(0,0,0));
    //    paintOnImage->drawRect(32+51*selectedMenu,3,53,53);
    paintOnImage->drawRect(33+51*selectedMenu,4,51,51);
    paintOnImage->drawRect(34+51*selectedMenu,5,49,49);
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            switch (myEditorBoard.get(y,x)) {
                case OneCell::CELL_EMPTY:
                {
                    break;
                }
                case OneCell::CELL_WALL:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/wall.png"),source);
                    break;
                }
                case OneCell::CELL_DOOR:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/door.png"),source);
                    break;
                }
                case OneCell::CELL_STEVE:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/steve.png"),source);
                    break;
                }
                case OneCell::CELL_HOLE:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/hole.png"),source);
                    break;
                }
                case OneCell::CELL_DIAMOND:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/diamond.png"),source);
                    break;
                }
                case OneCell::CELL_DIAMONDinHOLE:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/diamondHole.png"),source);
                    break;
                }
                case OneCell::CELL_STEVEinHOLE:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/steveHole.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_UP:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/arrowUp.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_DOWN:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/arrowDown.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_LEFT:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/arrowLeft.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_RIGHT:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/arrorRight.png"),source);
                    break;
                }
            }
        }
    }
    repaint();
}

void MainWindow2::on_pushButton_clicked()   //clicked "dodaj do zestawu"
{
    if (counterHole!=counterDiamond || counterSteve==0 || counterHole==0 || counterDiamond==0 || counterDiamondWithoutHole==0)
    {
        QMessageBox::critical(this, "Nie można dodać tej planszy - Jest nieprawidłowa!", "Sprawdź czy:\n1. Na planszy występuje przynajmniej jedna dziura, diament i Steve\n2. Liczba diamentów jest równa liczbie dziur,\n3. Przynajmniej jeden diament stoi poza dziurą." );
        return;
    }
    int nrCurrentIndex = ui->comboBox->currentIndex();
    // ---------- clear all levels of comboBox and add all -------
    ui->comboBox->clear();
    unsigned short int levels;
    for (levels=0; levels<saveLoadBoard.dynamicLevelsMenu;levels++)
    {
        ui->comboBox->addItem(mySprintf("Level %d %c", levels+1, saveLoadBoard.dynamicLevelsMenuStar[levels]));
    }
    if (nrCurrentIndex==-1)
    {
        // ---------- add new level -----------------------
        ui->comboBox->addItem(mySprintf("Level %d",levels+1));
        saveLoadBoard.dynamicLevelsMenu=levels+1;
        saveLoadBoard.dynamicLevelsMenuStar.push_back(' ');
        ui->comboBox->setCurrentIndex(levels);

        // ------- saving the current board to memory -----
        saveLoadBoard.addNewBoard(myEditorBoard.getBoardToVector());
    }
    else
    {
        ui->comboBox->setCurrentIndex(nrCurrentIndex);
        //        dynamicLevelsMenu[nrCurrentIndex]=nrCurrentIndex+1;     //Level x *  -> Level x
        saveLoadBoard.dynamicLevelsMenuStar[nrCurrentIndex]=' ';
        ui->comboBox->setItemText(nrCurrentIndex,mySprintf("Level %d",nrCurrentIndex+1));
        // ------- saving the current board to memory -----
        saveLoadBoard.addBoard(myEditorBoard.getBoardToVector(),nrCurrentIndex);
    }
    QMessageBox::about(this, "Udało się!", mySprintf("Plansza [Level %d] została zaktualizowana!",ui->comboBox->currentIndex()+1));
}

void MainWindow2::on_pushButton_2_clicked()     //clicked +nowa
{
    unsigned short int tmpSize = saveLoadBoard.dynamicLevelsMenu;
    if (tmpSize>=120)
    {
        QMessageBox::critical(this, "Nie można dodać planszy!", "Maksymalnie może być 120 plansz w jednym pliku." );
        return;
    }
    unsigned short int levels;
    // ---------- clear all levels of comboBox and add all -------
    ui->comboBox->clear();
    for (levels=0; levels<tmpSize;levels++)
    {
        ui->comboBox->addItem(mySprintf("Level %d %c", levels+1, saveLoadBoard.dynamicLevelsMenuStar[levels]));
    }
    ui->comboBox->addItem(mySprintf("Level %d *",levels+1));
    saveLoadBoard.dynamicLevelsMenu=levels+1;
    saveLoadBoard.dynamicLevelsMenuStar.push_back('*');
    ui->comboBox->setCurrentIndex(levels);
    // ------- saving the current board to memory -----
    saveLoadBoard.addNewBoard();                                  //add empty board (without argument)
    //    myEditorBoard.load(saveLoadBoard.getBoard(levels));     //refresh board
    //    showEditorBoard();                                      //show new/empty board
}

void MainWindow2::on_comboBox_activated(int index)
{
    // --- Refresh : clear all levels of comboBox and add all ----
    unsigned short int levels;
    unsigned short int tmpSize = saveLoadBoard.dynamicLevelsMenu;
    ui->comboBox->clear();
    for (levels=0; levels<tmpSize;levels++)
    {
        ui->comboBox->addItem(mySprintf("Level %d %c", levels+1, saveLoadBoard.dynamicLevelsMenuStar[levels]));
    }

    ui->comboBox->setCurrentIndex(index);
    myEditorBoard.load(saveLoadBoard.getBoard(index));
    showEditorBoard();
}
