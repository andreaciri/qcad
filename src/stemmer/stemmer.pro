include( ../../shared.pri )
SOURCES = \
    RStemmer.cpp
HEADERS = \
    RStemmer.h

TEMPLATE = lib
CONFIG += plugin
TARGET = qcadstemmer
LIBS += -lstemmer
OTHER_FILES += stemmer.dox
DEFINES += QCADSTEMMER_LIBRARY

POST_TARGETDEPS += ../../$$ROUTDIR/$${RLIBPRE}stemmer$${RLIBPOST}
