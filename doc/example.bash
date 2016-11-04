#!/usr/bin/env bash

# an example of filepath

# find a filepath binary

PWD=$(pwd)

FILEPATH=$(which filepath)

if [[ ! ${FILEPATH} ]] ; then

    FILEPATH="${PWD}/../filepath"

elif [ ! -f "${FILEPATH}" ]; then

    echo "You probably need to build filepath for this to work."
    exit
fi
# OK we have a binary

#find a web browser
BROWSER=
Browser_List="sensible-browser lynx links2 elinks w3m links  chromium-browser opera chrome NOTHING"

for BR in ${Browser_List}; 
do
    WBR=$(which "${BR}")

    if [[ ${WBR} ]] ; then
	BROWSER="${WBR}"
    fi
    
    if [[ ${BROWSER} ]] ; then
	break
    fi
done

# get full path
BROWSER=$( ${FILEPATH} ${BROWSER} )

if [[ $BROWSER ]] ; then

    FILEPATH_HTML=$(${FILEPATH} "filepath.html")

    "${BROWSER}" "${FILEPATH_HTML}"
else
    echo "Don't you have a web browser on this thing?"
fi



# OK we have a binary



