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
// File        : scripts/Modify/Mirror/Tests/MirrorTest01.js
// Timestamp   : 2011-08-05 17:05:14
// Description : 

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function MirrorTest01() {
    TdbTest.call(this, 'scripts/Modify/Mirror/Tests/MirrorTest01.js');
}

MirrorTest01.prototype = new TdbTest();

MirrorTest01.prototype.test00 = function() {
    qDebug('running MirrorTest01.test00()...');
    this.setUp();
    this.importFile('scripts/Modify/Mirror/Tests/data/polyline.dxf');
    this.selectAll();
    TdbTest.clickOnWidget('MainWindow::CadToolBar::MainToolsPanel::ModifyToolsPanelButton');
    TdbTest.clickOnWidget('MainWindow::CadToolBar::ModifyToolsPanel::MirrorButton');
    var p = new RVector(-0.166667, 20.188906);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    var p = new RVector(40.25, 19.688906);
    this.sendMouseEventModelPos(QEvent.MouseButtonPress, p, Qt.LeftButton, 1, 0);
    this.dlgStart();
    this.dlgAppendCode('var map = new Map()');
    this.dlgAppendCode("map.put('DialogOpenedByTdb/Mode', 'KeepOriginal')");
    this.dlgAppendCode("map.put('DialogOpenedByTdb/UseCurrentAttributes', false)");
    this.dlgAppendCode("WidgetFactory.restoreState(dialog, 'DialogOpenedByTdb', undefined, false, undefined, map)");
    this.dlgEnd();
    this.sendMouseEventModelPos(QEvent.MouseButtonRelease, p, Qt.LeftButton, 0, 0);
    this.verifyDrawing('MirrorTest01_000.dxf');
    this.tearDown();
    qDebug('finished MirrorTest01.test00()');
};

