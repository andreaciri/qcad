/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

include("../Save/Save.js");
include("scripts/File/NewFile/NewFile.js");
include("scripts/Tools/arguments.js");

/**
 * This action handles all user interaction to save drawings under a new name.
 */
function SaveAs(guiAction) {
    Save.call(this, guiAction);

    if (!isNull(guiAction)) {
        this.args = guiAction.getArguments();
    }
}

SaveAs.prototype = new Save();

SaveAs.getPreferencesCategory = function() {
    return [ qsTr("File"), qsTr("Load/Save")];
};

SaveAs.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var widgets = getWidgets(pageWidget);

    var nameFilters = RFileExporterRegistry.getFilterStrings();

    // Offer only a limited choice here as not all file format versions
    // are suitable for saving all information (e.g. 24 bit colors):
    for (var i=0; i<nameFilters.length; i++) {
        var nameFilter = nameFilters[i];
        if (File.isRecommendedVersion(nameFilter)) {
            widgets["Filter"].addItem(nameFilter);
        }
    }
};

SaveAs.prototype.beginEvent = function() {
    File.prototype.beginEvent.call(this);
    var appWin = EAction.getMainWindow();

    var nameFilters = RFileExporterRegistry.getFilterStrings();
    if (nameFilters.length===0) {
        EAction.handleUserWarning(qsTr("No export filters have been found. Aborting..."));
        this.terminate();
        return;
    }

    var nameFilter;
    var file;
    var forceOverwrite = false;

    if (!isNull(this.args) && this.args.length>=1) {
        forceOverwrite = testArgument(this.args, "-f", "-force");
        file = this.args[this.args.length-1];
        if (!new QFileInfo(file).isAbsolute()) {
            file = RSettings.getLaunchPath() + QDir.separator + file;
        }
        nameFilter = getArgument(this.args, "-t", "-filter");
    }
    else {
        var lastSaveAsFileDir = RSettings.getStringValue("SaveAs/Path", QDir.homePath());
        var defaultNameFilter = RSettings.getStringValue("SaveAs/Filter", "");
        var fileDialog = new QFileDialog(appWin);

        fileDialog.setOption(QFileDialog.DontUseNativeDialog, getDontUseNativeDialog());

        // overwrite is handled after extension has been added:
        fileDialog.setOption(QFileDialog.DontConfirmOverwrite, true);
        if (!isNull(QFileDialog.DontUseCustomDirectoryIcons)) {
            fileDialog.setOption(QFileDialog.DontUseCustomDirectoryIcons, true);
        }
        fileDialog.fileMode = QFileDialog.AnyFile;
        fileDialog.acceptMode = QFileDialog.AcceptSave;
        fileDialog.setNameFilters(nameFilters);

        var fileName = this.getDocument().getFileName();
        var fileInfo = new QFileInfo(fileName);

        var suffix = fileInfo.suffix().toLowerCase();

        if (suffix.length!==0 && !defaultNameFilter.containsIgnoreCase(suffix)) {
            // preselect first name filter that matches current extension:
            for (var i=0; i<nameFilters.length; ++i) {
                if (nameFilters[i].contains("*." + suffix)) {
                    fileDialog.selectNameFilter(nameFilters[i]);
                    break;
                }
            }
        }
        else {
            // preselect configured name filter:
            if (defaultNameFilter.length===0) {
                fileDialog.selectNameFilter(nameFilters[0]);
            }
            else {
                fileDialog.selectNameFilter(defaultNameFilter);
            }
        }

        if (fileName.length!==0) {
            fileDialog.selectFile(fileInfo.absoluteFilePath());
        }
        else {
            fileDialog.setDirectory(lastSaveAsFileDir);
        }


        fileDialog.setLabelText(QFileDialog.FileType, qsTr("Format:"));

        // global function qcadInitFileDialog may be registered to perform
        // additional initialization
        if (typeof qcadInitFileDialog!="undefined" && isFunction(qcadInitFileDialog)) {
            qcadInitFileDialog(fileDialog);
        }

        if (!fileDialog.exec()) {
            fileDialog.destroy();
            this.terminate();
            return;
        }

        RSettings.setValue("SaveAs/Path", fileDialog.directory().absolutePath());
        file = fileDialog.selectedFiles()[0];
        nameFilter = fileDialog.selectedNameFilter();
        fileDialog.destroy();
    }

    this.save(file, nameFilter, !forceOverwrite);

    var mdiArea = EAction.getMdiArea();
    if (!isNull(mdiArea)) {
        mdiArea.updateTabBar();
        NewFile.updateTitle();
    }

    this.terminate();
};

