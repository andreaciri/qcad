// Auto generated by Testing Dashboard
// File        : scripts/Draw/Text/Tests/Text08.js
// Timestamp   : 2015-10-05 16:34:35
// Description : 

include('scripts/Pro/Developer/TestingDashboard/TdbTest.js');

function Text08() {
    TdbTest.call(this, 'scripts/Draw/Text/Tests/Text08.js');
}

Text08.prototype = new TdbTest();

Text08.prototype.test00 = function() {
    qDebug('running Text08.test00()...');
    this.setUp();
    this.importFile('scripts/Draw/Text/Tests/data/text08.dxf');
    this.selectAll();
    this.triggerCommand('explode');
    this.deselectAll();
    this.verifyDrawing('Text08_000.dxf');
    this.tearDown();
    qDebug('finished Text08.test00()');
};

