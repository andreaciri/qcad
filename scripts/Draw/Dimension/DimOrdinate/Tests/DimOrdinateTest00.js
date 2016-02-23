/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */
// Auto generated by Testing Dashboard
// File        : scripts/Draw/Dimension/DimOrdinate/Tests/DimOrdinateTest00.js
// Timestamp   : 2011-04-27 10:03:11
// Description : 

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function DimOrdinateTest00() {
    TdbTest.call(this, 'scripts/Draw/Dimension/DimOrdinate/Tests/DimOrdinateTest00.js');
}

DimOrdinateTest00.prototype = new TdbTest();

DimOrdinateTest00.prototype.test00 = function() {
    qDebug('running DimOrdinateTest00.test00()...');
    this.setUp();
    this.importFile('scripts/Draw/Dimension/Tests/drawing00.dxf');
    var p = new RVector(25.713562, 17.309298);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.MidButton, 4, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.MidButton, 0, 0);
    TdbTest.clickOnWidget('MainWindow::CadToolBar::MainToolsPanel::DimensionToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::DimensionToolsPanel::DimOrdinateButton');
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(10.559787, 19.116629);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(18.623264, -3.822571);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(23.767205, 13.555611);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(27.520893, 2.433575);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(30.857504, 18.838578);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(34.750216, 9.801924);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(35.445344, 32.741124);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(40.589285, 20.92396);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(23.489155, 13.972687);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(-0.8403, 15.084891);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(10.003685, 19.811756);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(-0.284198, 19.672731);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(18.484238, 27.319131);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(0.271904, 27.180105);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(6.110973, 37.050913);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.setZoom(7.192927390667505, new RVector(14.6038, 10.2177, 0) );
    var p = new RVector(-0.145173, 36.911887);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(44.481998, 31.211844);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.RightButton, 2, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.RightButton, 0, 0);
    this.verifyDrawing('DimOrdinateTest00_000.dxf');
    this.tearDown();
    qDebug('finished DimOrdinateTest00.test00()');
};

