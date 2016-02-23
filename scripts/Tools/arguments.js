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

/**
 * \return The argument after the first one of the given flags or the given default value.
 *
 * \param args Array of strings (program arguments)
 * \param shortFlag E.g. "-o"
 * \param longFlag E.g. "-output"
 */
function getArgument(args, shortFlag, longFlag, def) {
    var ret = getArguments(args, shortFlag, longFlag);
    if (ret.length===0) {
        return def;
    }
    return ret[0];
}

/**
 * \return Array of all arguments after the given flags or an empty array.
 *
 * \param args Array of strings (program arguments)
 * \param shortFlag E.g. "-o"
 * \param longFlag E.g. "-output"
 */
function getArguments(args, shortFlag, longFlag) {
    var start = 0;
    var done = false;
    var ret = [];
    var i;

    do {
        done = true;
        i = args.indexOf(shortFlag, start);
        if (i!==-1) {
            if (i+1 < args.length) {
                ret.push(args[i+1]);
                start=i+2;
                done = false;
            }
        }

        for (var k=start; k<args.length; k++) {
            if (args[k].indexOf(longFlag+"=")===0) {
                var j=args[k].indexOf("=");
                ret.push(args[k].substr(j+1));
                start=k+1;
                done = false;
            }
        }
    } while (!done);

    return ret;
}

function getIntArgument(args, shortFlag, longFlag, def) {
    var ret = getArgument(args, shortFlag, longFlag);
    if (ret===undefined) {
        return def;
    }
    return parseInt(ret, 10);
}

function getFloatArgument(args, shortFlag, longFlag, def) {
    var ret = getArgument(args, shortFlag, longFlag);
    if (ret===undefined) {
        return def;
    }
    return parseFloat(ret);
}

function getColorArgument(args, shortFlag, longFlag, def) {
    var ret = getArgument(args, shortFlag, longFlag);
    if (ret===undefined) {
        return def;
    }
    return new RColor(ret);
}

function getBoxArgument(args, shortFlag, longFlag, def) {
    var ret = getArgument(args, shortFlag, longFlag);
    if (ret===undefined) {
        return def;
    }
    var parts = ret.split(',');
    if (parts.length!==4) {
        return def;
    }
    for (var i=0; i<parts.length; i++) {
        parts[i] = parseFloat(parts[i]);
    }

    return new RBox(new RVector(parts[0], parts[1]), new RVector(parts[0] + parts[2], parts[1] + parts[3]));
}

/**
 * \return True if the given arguments contain one of the given flags.
 */
function testArgument(args, shortFlag, longFlag) {
    if (shortFlag!=="" && args.indexOf(shortFlag)!==-1) {
        return true;
    }
    if (longFlag!=="") {
        if (args.indexOf(longFlag)!==-1) {
            return true;
        }
        for (var k=0; k<args.length; k++) {
            if (args[k].indexOf(longFlag+"=")===0) {
                return true;
            }
        }
    }

    return false;
}

function printArgument(name, prop) {
    var spc = "";
    if (name.length<32) {
        spc = new Array(32 - name.length).join(" ");
    }

    print(" ", name, spc, ":", prop);
}
